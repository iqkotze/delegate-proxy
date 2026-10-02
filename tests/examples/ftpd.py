#!/usr/bin/env python3
"""Minimal anonymous FTP server for the examples test.

Usage: ftpd.py <port> <directory>
Supports USER, PASS, SYST, FEAT, PWD, CWD, CDUP, TYPE, PASV, EPSV, SIZE, MDTM, LIST, NLST, RETR, QUIT.
"""
import os
import socketserver
import sys
import socket
import time


class Handler(socketserver.StreamRequestHandler):
    def reply(self, text):
        self.wfile.write(text.encode() + b"\r\n")

    def path(self, arg):
        base = "" if arg.startswith("/") else self.cwd.lstrip("/")
        full = os.path.normpath(os.path.join(self.root, base, arg.lstrip("/")))
        return full if full.startswith(self.root) else self.root

    def data_conn(self):
        if self.pasv is None:
            return None
        self.reply("150 Opening data connection")
        conn, _ = self.pasv.accept()
        self.pasv.close()
        self.pasv = None
        return conn

    def listing(self, arg, names):
        target = self.path(arg) if arg and not arg.startswith("-") else self.path("")
        lines = []
        if os.path.isdir(target):
            for n in sorted(os.listdir(target)):
                p = os.path.join(target, n)
                if names:
                    lines.append(n)
                else:
                    kind = "d" if os.path.isdir(p) else "-"
                    lines.append("%srw-r--r-- 1 ftp ftp %8d Jan  1 00:00 %s" % (kind, os.path.getsize(p), n))
        elif os.path.exists(target):
            lines.append(os.path.basename(target))
        return "".join(l + "\r\n" for l in lines).encode()

    def handle(self):
        self.root = os.path.realpath(self.server.root)
        self.cwd = "/"
        self.pasv = None
        self.reply("220 example FTP server ready")
        while True:
            line = self.rfile.readline()
            if not line:
                return
            text = line.decode(errors="replace").strip()
            com, _, arg = text.partition(" ")
            com = com.upper()
            sys.stderr.write("ftpd< %s\n" % text)
            if com == "USER":
                self.reply("331 Send password")
            elif com == "PASS":
                self.reply("230 Logged in")
            elif com == "SYST":
                self.reply("215 UNIX Type: L8")
            elif com == "FEAT":
                self.reply("211-Features\r\n SIZE\r\n MDTM\r\n211 End")
            elif com == "PWD":
                self.reply('257 "%s"' % self.cwd)
            elif com in ("CWD", "CDUP"):
                new = self.path(".." if com == "CDUP" else arg)
                if os.path.isdir(new):
                    self.cwd = "/" if new == self.root else "/" + os.path.relpath(new, self.root)
                    self.reply("250 OK")
                else:
                    self.reply("550 No such directory")
            elif com in ("TYPE", "MODE", "STRU", "NOOP"):
                self.reply("200 OK")
            elif com in ("PASV", "EPSV"):
                self.pasv = socket.socket()
                self.pasv.bind(("127.0.0.1", 0))
                self.pasv.listen(1)
                port = self.pasv.getsockname()[1]
                if com == "PASV":
                    self.reply("227 Entering Passive Mode (127,0,0,1,%d,%d)" % (port >> 8, port & 255))
                else:
                    self.reply("229 Entering Extended Passive Mode (|||%d|)" % port)
            elif com == "SIZE":
                p = self.path(arg)
                if os.path.isfile(p):
                    self.reply("213 %d" % os.path.getsize(p))
                else:
                    self.reply("550 No such file")
            elif com == "MDTM":
                p = self.path(arg)
                if os.path.isfile(p):
                    self.reply("213 " + time.strftime("%Y%m%d%H%M%S", time.gmtime(os.path.getmtime(p))))
                else:
                    self.reply("550 No such file")
            elif com in ("LIST", "NLST"):
                conn = self.data_conn()
                if conn is None:
                    self.reply("425 Use PASV first")
                    continue
                conn.sendall(self.listing(arg, com == "NLST"))
                conn.close()
                self.reply("226 Done")
            elif com == "RETR":
                p = self.path(arg)
                if not os.path.isfile(p):
                    self.reply("550 No such file")
                    continue
                conn = self.data_conn()
                if conn is None:
                    self.reply("425 Use PASV first")
                    continue
                with open(p, "rb") as f:
                    conn.sendall(f.read())
                conn.close()
                self.reply("226 Done")
            elif com == "QUIT":
                self.reply("221 Bye")
                return
            else:
                self.reply("502 Not implemented")


class Server(socketserver.ThreadingTCPServer):
    allow_reuse_address = True
    daemon_threads = True


if __name__ == "__main__":
    srv = Server(("127.0.0.1", int(sys.argv[1])), Handler)
    srv.root = sys.argv[2]
    srv.serve_forever()
