#!/usr/bin/env python3
# Minimal HTTP/1.1 keep-alive origin for load tests.
# Usage: load-origin.py <port> [bind-address]
import asyncio
import resource
import sys

BODY = b"smoke-ok\n"
RESPONSE = (b"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n" % len(BODY)) + BODY


async def handle(reader, writer):
    try:
        while True:
            head = await reader.readuntil(b"\r\n\r\n")
            writer.write(RESPONSE)
            if b"connection: close" in head.lower():
                break
            await writer.drain()
    except (asyncio.IncompleteReadError, ConnectionError, asyncio.LimitOverrunError):
        pass
    finally:
        writer.close()


async def main(port, addr):
    server = await asyncio.start_server(handle, addr, port, backlog=4096)
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    soft, hard = resource.getrlimit(resource.RLIMIT_NOFILE)
    resource.setrlimit(resource.RLIMIT_NOFILE, (hard, hard))
    asyncio.run(main(int(sys.argv[1]), sys.argv[2] if len(sys.argv) > 2 else "127.0.0.1"))
