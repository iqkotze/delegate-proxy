> Generated file. Renew with `cmake --build <dir> --target param-docs`.

# DeleGate parameter reference

## ABORTLOG

Syntax: `ABORTLOG=LogFilename`

Default: `${LOGDIR}/abort/${PORT}`

[ungeprüft] Log file written on abnormal termination

```
ABORTLOG=abort.log
```

Source: `delegate/src/delegated.cpp`

## ACTDIR

Syntax: `ACTDIR=dirPath`

Default: `${DGROOT?&/act:/tmp/delegate}`

Directory of temporary files of active servers, removed at termination

```
ACTDIR=/var/spool/delegate/act
```

Source: `delegate/src/delegated.cpp`

## ADMDIR

Syntax: `ADMDIR=dirPath`

Default: `${VARDIR}/adm`

Directory of generated administration files, such as shutout, passwords and counters

```
ADMDIR=/var/spool/delegate/adm
```

Source: `delegate/src/delegated.cpp`

## ADMIN

Syntax: `ADMIN=user@host.domain`

Default: `root@localhost (set at build time with -DADMIN)`

E-mail address of the administrator, shown in messages and sent as FTP password

```
ADMIN=admin@example.com
```

Source: `delegate/src/delegated.cpp`

## ADMINPASS

Syntax: `ADMINPASS=password`

Default: `none (built-in value set at build time with -DADMINPASS)`

[ungeprüft] Password checked against the built-in ADMINPASS when ADMIN is verified

```
ADMINPASS=secret
```

Source: `delegate/src/editconf.cpp`

## ARPCONF

Syntax: `ARPCONF=name:value`

Default: `command:arp %A`

[ungeprüft] ARP lookup settings: command, cache-file, cache-size, cache-expire

```
ARPCONF=cache-expire:120
```

Source: `delegate/src/inets.cpp`

## AUTH

Syntax: `AUTH=what:authProto:who`

Default: `none`

Authorize who to do what, with authentication by authProto

```
AUTH=admin:-pam:user
```

Source: `delegate/src/access.cpp`

## AUTHORIZER

Syntax: `AUTHORIZER=authServList[@realmValue][:connMap]`

Default: `none`

Authentication server; access requires a valid user name and password

```
AUTHORIZER=-anonftp
```

Source: `delegate/src/access.cpp`

## BASEURL

Syntax: `BASEURL=URL`

Default: `none`

Base of the virtual URL of this server, embedded in generated absolute URLs

```
BASEURL=http://wwwserver/news
```

Source: `delegate/src/ddi.cpp`

## CACHE

Syntax: `CACHE=cacheControl[,cacheControl]*[:connMap]`

Default: `none (cache is enabled if CACHEDIR is usable)`

Enable (do), disable (no) or use read-only (ro) the cache

```
CACHE=do
```

Source: `delegate/src/conf.cpp`

## CACHEARC

Syntax: `CACHEARC=path`

Default: `none`

[ungeprüft] Path of the cache archive

```
CACHEARC=/var/spool/delegate/cache.arc
```

Source: `delegate/src/conf.cpp`

## CACHEDIR

Syntax: `CACHEDIR=dirPath`

Default: `${VARDIR}/cache`

Directory of the cache files; it must be readable and writable

```
CACHEDIR=/var/spool/delegate/cache
```

Source: `delegate/src/conf.cpp`

## CACHEFILE

Syntax: `CACHEFILE=fileNameSpec`

Default: `$[server:%P/%L/%p]`

Format of the file name of a cache file, derived from server and URL

```
CACHEFILE='$[server:%P]/$[hash:%H]/$[server:%L/%p]'
```

Source: `delegate/src/conf.cpp`

## CAPSKEY

Syntax: `CAPSKEY=opaque`

Default: `none`

Key that enables functions that are disabled by default

```
CAPSKEY=abcdef0123456789
```

Source: `delegate/src/caps.cpp`

## CERTDIR

Syntax: `CERTDIR=dir`

Default: `${ETCDIR}/certs`

Directory with the certificates and keys used by SSLway

```
CERTDIR=/etc/delegate/certs
```

Source: `delegate/src/filter.cpp`

## CGIENV

Syntax: `CGIENV=name[,name]*`

Default: `*`

Environment variables passed to CGI programs

```
CGIENV=PATH,LANG
```

Source: `delegate/src/cgi.cpp`

## CHARCODE

Syntax: `CHARCODE=[inputCode/]outputCode[:[tosv][:connMap]]`

Default: `none`

Convert the character code of relayed text to outputCode (JIS, EUC, SJIS, UTF8, ASCII)

```
CHARCODE=UTF8
```

Source: `delegate/src/textconv.cpp`

## CHARMAP

Syntax: `CHARMAP=mapType:charMap[,charMap]*[:tosv]`

Default: `none`

Map characters of relayed text to other characters

```
CHARMAP=ascii:a-z/A-Z,A-Z/a-z
```

Source: `delegate/src/textconv.cpp`

## CHARSET

Syntax: `CHARSET=[inputCode/]outputCode[:[tosv][:connMap]]`

Default: `none`

[ungeprüft] Same as CHARCODE

```
CHARSET=UTF8
```

Source: `delegate/src/textconv.cpp`

## CHROOT

Syntax: `CHROOT=dirPath`

Default: `none`

Change the root of the file system with chroot(2) at start; super-user only

```
CHROOT=/var/delegate-root
```

Source: `delegate/src/delegated.cpp`

## CLUSTER

Syntax: `CLUSTER=[protoList]:ServerList`

Default: `none`

Define alternative servers used when the connection to a server or proxy fails

```
CLUSTER=http:www1,www2,www3..8080
```

Source: `delegate/src/service.cpp`

## CMAP

Syntax: `CMAP=resultStr:mapName:connMap`

Default: `none`

Map the current connection (protocol, destination, source) to a value for mapName

```
CMAP=sslway:FSV:telnet:hostA:*
```

Source: `delegate/src/master.cpp`

## CONFOPT

Syntax: `CONFOPT=type:sub`

Default: `none`

[ungeprüft] Marker line of the generated configuration form, with the form type

```
CONFOPT=type:sub
```

Source: `delegate/src/form2conf.cpp`

## CONNECT

Syntax: `CONNECT=connSeq[:connMap]`

Default: `c,i,m,h,y,v,s,d:*:*:*`

Order of connection methods tried for the target server

```
CONNECT=s,d
```

Source: `delegate/src/master.cpp`

## COUNTER

Syntax: `COUNTER=listOfCounterControl`

Default: `no`

Access counters: do, total, acc, ssi, ref, err, ro, no

```
COUNTER=do
```

Source: `delegate/src/bcounter.cpp`

## CRON

Syntax: `CRON="minute hour day month dayOfWeek action"`

Default: `none`

Run an action at times given in crontab(5) format

```
CRON="0 3 * * * -expire 3"
```

Source: `delegate/src/croncom.cpp`

## CRONS

Syntax: `CRONS="minute hour day month dayOfWeek action"`

Default: `none`

[ungeprüft] Like CRON, but appended to the schedule evaluated per session

```
CRONS="0 3 * * * -expire 3"
```

Source: `delegate/src/croncom.cpp`

## CRYPT

Syntax: `CRYPT=pass:key`

Default: `none`

[ungeprüft] Key of the encryption of messages between DeleGates; pass: asks for the key

```
CRYPT=pass:secret
```

Source: `delegate/src/dgauth.cpp`

## DATAPATH

Syntax: `DATAPATH=dirPath[:dirPath]*`

Default: `.;${DGROOT};${STARTDIR};${EXECDIR}`

Directories searched for data files given as relative paths, for example in MOUNT

```
DATAPATH=".:/var/www"
```

Source: `delegate/src/delegated.cpp`

## DELAY

Syntax: `DELAY=what:seconds`

Default: `reject:60,unknown:60,reject_p:0,unknown_p:0,error:30`

Delay in seconds before the response to repeated rejects, unknowns or errors

```
DELAY=reject:30,unknown:30
```

Source: `delegate/src/env.cpp`

## DELEGATE

Syntax: `DELEGATE=gwHost:Port[:ProtoList]`

Default: `current host and port`

Gateway host and port written into rewritten URLs; superseded by BASEURL and RELAY

```
DELEGATE=gwhost:8080
```

Source: `delegate/src/svport.cpp`

## DEST

Syntax: `DEST=host:port[/udp][:srcHostList]`

Default: `none`

Server that a SockMux server relays to with tcprelay, or udprelay if /udp is given

```
DEST=hostT:111
```

Source: `delegate/src/delegated.cpp`

## DGCONF

Syntax: `DGCONF=dir/file`

Default: `${EXECDIR}/${EXECNAME}.conf;${EXECDIR}/../etc/${EXECNAME}.conf`

Configuration file loaded at start if it exists

```
DGCONF=/etc/delegate/delegated.conf
```

Source: `delegate/src/delegated.cpp`

## DGDEF

Syntax: `DGDEF=name[,flags]:data`

Default: `none`

[ungeprüft] Define a named data item; flags conn, url, ei and si select the evaluation

```
DGDEF=greeting:hello
```

Source: `delegate/src/env.cpp`

## DGOPTS

Syntax: `DGOPTS=opt[;opt]*`

Default: `none`

Command line options given as a parameter, for options without name=value form

```
DGOPTS="-P8080;-v"
```

Source: `delegate/src/delegated.cpp`

## DGPATH

Syntax: `DGPATH=dirPath[:dirPath]*`

Default: `+:.:${HOME}/delegate:${EXECDIR}:${ETCDIR}`

Search path of parameter files; + stands for the directory of the calling file

```
DGPATH="+:.:${HOME}/delegate"
```

Source: `delegate/src/script.cpp`

## DGROOT

Syntax: `DGROOT=dirPath`

Default: `${STARTDIR}/DGROOT if it exists, else ${HOME}/delegate, /var/spool/delegate-${OWNER} or /tmp/delegate-${OWNER}`

Root directory of all DeleGate files (log, cache, work, etc, adm, act, tmp)

```
DGROOT=/var/spool/delegate
```

Source: `delegate/src/conf.cpp`

## DGSIGN

Syntax: `DGSIGN=signatureSpec`

Default: `V.R.P/Y.M.D`

Form of the version signature shown to clients and servers; x hides a part

```
DGSIGN=V.x.x/Y.x.x
```

Source: `delegate/src/version.cpp`

## DNSCONF

Syntax: `DNSCONF=what:value`

Default: `none`

Settings of the DNS server: para, domain, origin, admin, serial, refresh, retry, mx

```
DNSCONF=domain:my.domain
```

Source: `delegate/src/domain.cpp`

## DYCONF

Syntax: `DYCONF=[conditions]parameters`

Default: `none`

Load parameters from a file, CGI or inline list at the start of each session

```
DYCONF="file:path.txt"
```

Source: `delegate/src/env.cpp`

## DYLIB

Syntax: `DYLIB=libfilePattern[,libfilePattern]*`

Default: `dglib%s.so,lib%s.so.0.9.8,lib%s.so,lib%s.so.1.0.0,lib%s.so.10,lib%s.so.6,lib%s.so.4,lib%s.so.1,lib%s.so.0,lib%s.so.0.9.7,%s`

File name patterns for dynamic libraries; + stands for the default list

```
DYLIB="+,lib*.so.0.9.7"
```

Source: `delegate/filters/dl.cpp`

## EDITOR

Syntax: `EDITOR=command`

Default: `vi`

[ungeprüft] Editor for the parameters of an executable file; VISUAL is tried next, then vi

```
EDITOR=vi
```

Source: `delegate/src/dgsign.cpp`

## ENTR

Syntax: `ENTR=proto://host:port/path`

Default: `none`

[ungeprüft] Open an entrance for a protocol on a host and port

```
ENTR=http://localhost:8080/
```

Source: `delegate/src/svport.cpp`

## ERRORLOG

Syntax: `ERRORLOG=LogFilename`

Default: `${LOGDIR}/errors.log`

Log file for errors

```
ERRORLOG=errors.log
```

Source: `delegate/src/delegated.cpp`

## ETCDIR

Syntax: `ETCDIR=dirPath`

Default: `${VARDIR}/etc`

Directory of persistent configuration and management files

```
ETCDIR=/etc/delegate
```

Source: `delegate/src/delegated.cpp`

## EXECAUTH

Syntax: `EXECAUTH=pass:users:caps`

Default: `none`

[ungeprüft] Password, user list and capabilities required to run the executable file

```
EXECAUTH=secret:root:*
```

Source: `delegate/src/dgsign.cpp`

## EXPIRE

Syntax: `EXPIRE=validity[/custody][:connMap]`

Default: `1h (HTTP, Gopher), 1d (FTP)`

Validity period of cached data in days, hours, minutes or seconds

```
EXPIRE=1d
```

Source: `delegate/src/conf.cpp`

## EXPIRELOG

Syntax: `EXPIRELOG=LogFilename`

Default: `${LOGDIR}/expire.log`

Log file of the expiration by -Fexpire or the -expire action of CRON

```
EXPIRELOG=expire.log
```

Source: `delegate/src/croncom.cpp`

## FCL

Syntax: `FCL=[-s,][-p,][-w,]command`

Default: `none`

Filter between client and DeleGate

```
FCL=sslway
```

Source: `delegate/src/filter.cpp`

## FFROMCL

Syntax: `FFROMCL=[-s,][-p,][-w,]command`

Default: `none`

Filter from client to DeleGate

```
FFROMCL=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FFROMMD

Syntax: `FFROMMD=[-s,][-p,][-w,]command`

Default: `none`

Filter from MASTER to this DeleGate

```
FFROMMD=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FFROMSV

Syntax: `FFROMSV=[-s,][-p,][-w,]command`

Default: `none`

Filter from server to DeleGate

```
FFROMSV=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FILETYPE

Syntax: `FILETYPE=suffix:gopherType:altText:iconName:contentType`

Default: `built-in table, starting with .txt:0:TXT:text:text/plain`

Map a file name suffix to Gopher type, icon and content type

```
FILETYPE=".txt:0:TXT:text:text/plain"
```

Source: `delegate/src/filetype.cpp`

## FMD

Syntax: `FMD=[-s,][-p,][-w,]command`

Default: `none`

Filter between MASTER and this DeleGate

```
FMD=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FORWARD

Syntax: `FORWARD=gatewayURL[-_-connMap]`

Default: `none`

Forward requests matching connMap to the proxy given as URL

```
FORWARD=ssltunnel://user:pass@proxyhost:8080-_-https:sslhost
```

Source: `delegate/src/master.cpp`

## FSV

Syntax: `FSV=[-s,][-p,][-w,]command`

Default: `none`

Filter between server and DeleGate

```
FSV=sslway
```

Source: `delegate/src/filter.cpp`

## FTOCL

Syntax: `FTOCL=[-s,][-p,][-w,]command`

Default: `none`

Filter from DeleGate to client

```
FTOCL=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FTOMD

Syntax: `FTOMD=[-s,][-p,][-w,]command`

Default: `none`

Filter from this DeleGate to MASTER

```
FTOMD=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FTOSV

Syntax: `FTOSV=[-s,][-p,][-w,]command`

Default: `none`

Filter from DeleGate to server

```
FTOSV=filter.cfi
```

Source: `delegate/src/filter.cpp`

## FTPCONF

Syntax: `FTPCONF=ftpControl[:{sv|cl}]`

Default: `none`

FTP settings such as nopasv, noport, noxdc, rawxdc

```
FTPCONF=nopasv
```

Source: `delegate/src/ftp.cpp`

## FTPTUNNEL

Syntax: `FTPTUNNEL=host:port[:path]`

Default: `none`

[ungeprüft] Reach servers through an FTP server that opens a CONNECT tunnel

```
FTPTUNNEL=ftphost:21:tunnel
```

Source: `delegate/src/ftp.cpp`

## FUNC

Syntax: `FUNC=name`

Default: `name of the executable file`

[ungeprüft] Function to run when no -F option is given

```
FUNC=ver
```

Source: `delegate/src/delegated.cpp`

## GATEWAY

Syntax: `GATEWAY=gatewayURL[-_-connMap]`

Default: `none`

[ungeprüft] Same as FORWARD

```
GATEWAY=socks://sockshost:1080
```

Source: `delegate/src/master.cpp`

## HOME

Syntax: `HOME=dirPath`

Default: `home directory of the owner`

[ungeprüft] Home directory used when DGROOT is derived as ${HOME}/delegate

```
HOME=/home/delegate
```

Source: `delegate/src/conf.cpp`

## HOSTLIST

Syntax: `HOSTLIST=listName:HostList`

Default: `none`

Define a named host list that other host lists can refer to

```
HOSTLIST=".localnet:localhost,./32,192.168.*"
```

Source: `delegate/src/hostlist.cpp`

## HOSTS

Syntax: `HOSTS=nameList[/addrList]`

Default: `localhost/127.0.0.1`

Host name and address pairs that override DNS, NIS and /etc/hosts

```
HOSTS=www.example.com/192.0.2.10
```

Source: `delegate/src/inets.cpp`

## HTMLCONV

Syntax: `HTMLCONV=convList`

Default: `deent`

Conversions of HTML text: deent, enent, fullurl

```
HTMLCONV=deent,fullurl
```

Source: `delegate/rary/html.cpp`

## HTMUX

Syntax: `HTMUX=sv[:[hostList][:portList]] | HTMUX=cl:host:port | HTMUX=px:host:port`

Default: `none`

Accept requests through a HTMUX server on another host; requires CAPSKEY

```
HTMUX=cl:192.168.1.1:9876
```

Source: `delegate/src/master.cpp`

## HTTPCONF

Syntax: `HTTPCONF=what:conf`

Default: `welcome:welcome.{dgp,shtml,html,cgi},index.{dgp,shtml,html,cgi},-dir.html`

HTTP specific settings: welcome files, timeouts (tout-), limits (max-), header rules

```
HTTPCONF=max-cka:100
```

Source: `delegate/src/httpd.cpp`

## HUPENV

Syntax: `HUPENV=value`

Default: `none`

[ungeprüft] Value passed as HUPENV to a service restarted by a hangup

```
HUPENV=reload
```

Source: `delegate/src/delegated.cpp`

## ICP

Syntax: `ICP=icpServerList[:icpServerSpec[:connMap]]`

Default: `none`

ICP servers asked for a cached resource when icp is in the CONNECT sequence

```
ICP=icphost
```

Source: `delegate/src/icp.cpp`

## ICPCONF

Syntax: `ICPCONF={icpMaxima|icpConf}`

Default: `para:2,hitage:1d,hitobjage:1h,hitobjsize:1024,nofetch:1d,timeout:2.0`

Configuration of the DeleGate as ICP server: para, hitage, hitobjage, hitobjsize, timeout

```
ICPCONF=para:4,hitage:2d
```

Source: `delegate/src/icp.cpp`

## IMAGEDIR

Syntax: `IMAGEDIR=dirPath`

Default: `none`

[ungeprüft] Directory of the icon images referred to by Gopher menus

```
IMAGEDIR=/var/www/icons
```

Source: `delegate/src/delegated.cpp`

## INETD

Syntax: `INETD="port sockType proto waitStat uid execPath argList"`

Default: `none`

Start a DeleGate on connection to a port, in the notation of inetd.conf

```
INETD="8080 stream tcp nowait - /usr/sbin/delegated delegated SERVER=http"
```

Source: `delegate/src/inetd.cpp`

## INPARAM

Syntax: `INPARAM=file`

Default: `none`

[ungeprüft] Enables the import of parameters at run time; the value is not evaluated

```
INPARAM=/var/spool/delegate/params
```

Source: `delegate/src/delegated.cpp`

## INVITE

Syntax: `INVITE=value`

Default: `none`

[ungeprüft] Value passed to the teleport server together with TUNNEL

```
INVITE=*
```

Source: `delegate/src/delegated.cpp`

## IPV6

Syntax: `IPV6=name[:no]`

Default: `4map on, 6also off, 4also off`

[ungeprüft] IPv6 handling; 4map unifies mapped addresses, 6also and 4also add the other family

```
IPV6=6also
```

Source: `delegate/src/inets.cpp`

## LDPATH

Syntax: `LDPATH=dirPath[;dirPath]*`

Default: `${ETCDIR};${LIBDIR};${EXECDIR};${STARTDIR};${HOME}/lib;/usr/local/lib;/usr/lib;/lib`

Directories searched for the dynamic libraries named by DYLIB

```
LDPATH="/usr/local/lib;/usr/lib"
```

Source: `delegate/src/delegated.cpp`

## LIBDIR

Syntax: `LIBDIR=dirPath`

Default: `${VARDIR}/lib`

[ungeprüft] Directory of library files, the first entry of the default LIBPATH

```
LIBDIR=/var/spool/delegate/lib
```

Source: `delegate/src/delegated.cpp`

## LIBPATH

Syntax: `LIBPATH=dirPath[:dirPath]*`

Default: `.;${STARTDIR};${LIBDIR};${EXECDIR};${ETCDIR}`

Directories searched for library files such as parameter files, CFI scripts and filters

```
LIBPATH=".:/etc/delegate"
```

Source: `delegate/src/delegated.cpp`

## LINGER

Syntax: `LINGER=seconds`

Default: `30`

[ungeprüft] Linger time in seconds of the output side of sockets

```
LINGER=10
```

Source: `delegate/src/delegated.cpp`

## LOG

Syntax: `LOG=proto:filters:logform:pathform`

Default: `none`

[ungeprüft] Additional log file for a protocol, with filter, format and path

```
LOG=http:*:%C:http.log
```

Source: `delegate/src/delegated.cpp`

## LOGCENTER

Syntax: `LOGCENTER=host:port`

Default: `none (an empty value selects www.delegate.org:8000)`

[ungeprüft] Log center that the server opens a UDP client connection to

```
LOGCENTER=logcenter.example.com:8000
```

Source: `delegate/src/delegated.cpp`

## LOGDIR

Syntax: `LOGDIR=dirPath`

Default: `${VARDIR}/log`

Directory of the log files

```
LOGDIR='log[date+/y%y/m%m/%d]'
```

Source: `delegate/src/delegated.cpp`

## LOGFILE

Syntax: `LOGFILE=[LogFilename]`

Default: `${LOGDIR}/${PORT}`

Log file of the DeleGate; empty value stops logging

```
LOGFILE='${PORT}[date+.%d]'
```

Source: `delegate/src/delegated.cpp`

## M17N

Syntax: `M17N=on | M17N=off`

Default: `off`

[ungeprüft] Enable the m17n library for character code conversion

```
M17N=on
```

Source: `delegate/src/delegated.cpp`

## MAILSPOOL

Syntax: `MAILSPOOL=pop://user@host`

Default: `none`

[ungeprüft] POP server that holds the mail spool for -Fpoprelay and -Fpopdown

```
MAILSPOOL=pop://user@mailhost
```

Source: `delegate/src/pop.cpp`

## MANAGER

Syntax: `MANAGER=user@host.domain`

Default: `none`

[ungeprüft] Obsolete alias of ADMIN

```
MANAGER=admin@example.com
```

Source: `delegate/src/delegated.cpp`

## MASTER

Syntax: `MASTER=host:port[/masterControl][:dstHostList]`

Default: `none`

Upstream generalist DeleGate that this DeleGate forwards requests to

```
MASTER=host2:8080
```

Source: `delegate/src/master.cpp`

## MASTERP

Syntax: `MASTERP=[host:port]`

Default: `none`

Start a MASTER DeleGate private to this DeleGate

```
MASTERP=localhost:8081
```

Source: `delegate/src/delegated.cpp`

## MAXIMA

Syntax: `MAXIMA=what:number[,what:number]*`

Default: `listen:20,delegated:64,standby:32,ftpcc:16,...`

Maxima of resources: processes, connections, queue sizes and similar

```
MAXIMA=delegated:256,listen:1024
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `bps` | `bps:N` | `0 (unlimited)` | Maximum transmission speed of HTTP and FTP data; k and m units are allowed | `MAXIMA=bps:128k` |
| `conpch` | `conpch:N` | `0 (unlimited)` | Maximum number of connections at a time per client host | `MAXIMA=conpch:20` |
| `contry` | `contry:N` | `2` | [ungeprüft] Number of connection trials to a server | `MAXIMA=contry:3` |
| `delegated` | `delegated:N` | `64 (adapted to the memory size at start)` | Maximum number of DeleGate processes running at a time | `MAXIMA=delegated:256` |
| `erestart` | `erestart:N` | `1` | [ungeprüft] Maximum number of restarts after an error, used with TIMEOUT erestart | `MAXIMA=erestart:3` |
| `fdset` | `fdset:N` | `64` | [ungeprüft] Base size of the descriptor set, extended by three per delegated process | `MAXIMA=fdset:128` |
| `ftpcc` | `ftpcc:N` | `16` | Maximum number of FTP connection cache servers to a host (shared with nntpcc and svcc) | `MAXIMA=ftpcc:4` |
| `http-cka` | `http-cka:N` | `50` | Maximum requests per keep-alive connection; replaced by HTTPCONF max-cka | `MAXIMA=http-cka:50` |
| `http-ckapch` | `http-ckapch:N` | `8` | Maximum keep-alive connections per client host; replaced by HTTPCONF max-ckapch | `MAXIMA=http-ckapch:8` |
| `listen` | `listen:N` | `20` | Maximum size of the queue of an entrance port | `MAXIMA=listen:1024` |
| `nntpcc` | `nntpcc:N` | `16` | Maximum number of NNTP connection cache processes to a host (shared with ftpcc and svcc) | `MAXIMA=nntpcc:4` |
| `randenv` | `randenv:N` | `1024` | Randomization range of the environment variables base | `MAXIMA=randenv:1024` |
| `randfd` | `randfd:N` | `32` | Randomization range of the client socket descriptor | `MAXIMA=randfd:32` |
| `randstack` | `randstack:N` | `64` | Randomization range of the stack base for security | `MAXIMA=randstack:32` |
| `restart` | `restart:N` | `0` | [ungeprüft] Restart the server after N accepted connections | `MAXIMA=restart:10000` |
| `service` | `service:N` | `0 (unlimited)` | Maximum number of services per delegated process | `MAXIMA=service:1000` |
| `sockrecv` | `sockrecv:N` | `65536` | [ungeprüft] Maximum size of the socket receive buffer in bytes | `MAXIMA=sockrecv:131072` |
| `socksend` | `socksend:N` | `16384` | [ungeprüft] Maximum size of the socket send buffer in bytes | `MAXIMA=socksend:32768` |
| `standby` | `standby:N` | `32` | Maximum number of standby processes | `MAXIMA=standby:16` |
| `svcc` | `svcc:N` | `16` | [ungeprüft] Maximum number of connection cache servers (shared with ftpcc and nntpcc) | `MAXIMA=svcc:4` |
| `udprelay` | `udprelay:N` | `32` | Maximum number of parallel UDP relay clients | `MAXIMA=udprelay:64` |
| `winmtu` | `winmtu:N` | `0` | Maximum unit of send() on Win32 | `MAXIMA=winmtu:1024` |

Source: `delegate/src/env.cpp`

## MHGWCONF

Syntax: `MHGWCONF=hide:fname:vlist:users:hides`

Default: `none`

[ungeprüft] Mail header hiding rules of the mail-to-HTTP gateway

```
MHGWCONF=hide:From:*:*:from
```

Source: `delegate/src/nntpgw.cpp`

## MIMECONV

Syntax: `MIMECONV=mimeConv[,mimeConv]`

Default: `none (empty if CHARCODE is given)`

MIME encoding and decoding in NNTP, POP and SMTP: thru, charcode, nospenc, textonly, alt

```
MIMECONV=charcode
```

Source: `delegate/mimekit/mime.cpp`

## MOUNT

Syntax: `MOUNT="vURL rURL [MountOptions]"`

Default: `/* SERVER_URL*`

Map the virtual URL vURL to and from the real URL rURL

```
MOUNT="/abc/* http://host/*"
```

Source: `delegate/src/mount.cpp`

## MYAUTH

Syntax: `MYAUTH=username:password[:connMap]`

Default: `none`

User name and password sent to an upstream server or proxy

```
MYAUTH=user:pass:socks
```

Source: `delegate/src/access.cpp`

## NNTPCONF

Syntax: `NNTPCONF=what:conf`

Default: `upact:600/300/60`

NNTP settings such as pathhost and upact (update of the active list cache)

```
NNTPCONF=upact:600/300/120
```

Source: `delegate/src/nntp.cpp`

## OVERRIDE

Syntax: `OVERRIDE=master:port:param`

Default: `none`

[ungeprüft] Value forwarded as OVERRIDE header to the MASTER DeleGate

```
OVERRIDE=masterhost:8080:CACHE=no
```

Source: `delegate/src/service.cpp`

## OWNER

Syntax: `OWNER=user[/group][:srcHostList]`

Default: `nobody`

User and group the DeleGate runs as after start (effective for super-user only)

```
OWNER=nobody/nogroup
```

Source: `delegate/src/master.cpp`

## PAMCONF

Syntax: `PAMCONF=name:value`

Default: `none`

[ungeprüft] Settings of PAM authentication: baseurl, url and port

```
PAMCONF=port:8000
```

Source: `delegate/src/access.cpp`

## PASSWD

Syntax: `PASSWD=domain:user:pass:key`

Default: `none`

[ungeprüft] Key for a password domain (imp, ext, sudo, exec) in the key store of the executable

```
PASSWD=ext::pass:secret
```

Source: `delegate/src/delegated.cpp`

## PERMIT

Syntax: `PERMIT=ProtoList:dstHostList:srcHostList`

Default: `none`

Permit accesses with the given protocols, to the given servers, from the given clients

```
PERMIT="*:*:.localnet"
```

Source: `delegate/src/service.cpp`

## PGP

Syntax: `PGP=mode[,mode]*`

Default: `none`

[ungeprüft] PGP processing of mail messages; sign, mime, encr, decr, vrfy

```
PGP=sign,mime
```

Source: `delegate/mimekit/pgp.cpp`

## PIDFILE

Syntax: `PIDFILE=fileName`

Default: `${ACTDIR}/pid/${PORT}`

File that records the process ID of the DeleGate

```
PIDFILE=/var/run/delegate-8080.pid
```

Source: `delegate/src/delegated.cpp`

## POPCONF

Syntax: `POPCONF=listmax:N`

Default: `none`

[ungeprüft] POP settings; listmax sets the maximum number of listed messages

```
POPCONF=listmax:100
```

Source: `delegate/src/pop.cpp`

## PORT

Syntax: `PORT=port[,port]*`

Default: `none`

Open entrance ports in addition to the -P option

```
PORT=9023
```

Source: `delegate/src/svport.cpp`

## PROTOLOG

Syntax: `PROTOLOG=[LogFilename][:logFormat]`

Default: `${LOGDIR}/${PORT}.${PROTO}`

Protocol log in httpd or wu-ftp compatible format

```
PROTOLOG="access.log"
```

Source: `delegate/src/delegated.cpp`

## PROXY

Syntax: `PROXY=host:port[:dstHostList]`

Default: `none`

Upstream proxy for HTTP, FTP and Telnet, optionally for dstHostList only

```
PROXY=proxyhost:8080:!*.localdomain
```

Source: `delegate/src/master.cpp`

## REACHABLE

Syntax: `REACHABLE=dstHostList`

Default: `*`

Accept only requests directed to servers in dstHostList

```
REACHABLE="*.my.domain"
```

Source: `delegate/src/master.cpp`

## REJECT

Syntax: `REJECT=ProtoList:dstHostList:srcHostList`

Default: `none`

Reject accesses with the given protocols, to the given servers, from the given clients

```
REJECT="pop//DELE:mail-server:mail-client"
```

Source: `delegate/src/service.cpp`

## RELAY

Syntax: `RELAY=relayTypeList[:connMap]`

Default: `delegate,nojava:*:*:.localnet;vhost,nojava:http:{*:80}:.localnet;proxy`

Proxying mode of the DeleGate as HTTP server: proxy, delegate, vhost, no, nojava, noapplet

```
RELAY="proxy:*:*:*"
```

Source: `delegate/src/access.cpp`

## RELIABLE

Syntax: `RELIABLE=srcHostList`

Default: `.localnet`

Accept only requests from clients in srcHostList

```
RELIABLE="192.168.*"
```

Source: `delegate/src/master.cpp`

## REMITTABLE

Syntax: `REMITTABLE=ProtoList`

Default: `* for a generalist, . for a specialist`

Protocols that may be relayed to servers; + adds to the default list

```
REMITTABLE="+,ssltunnel"
```

Source: `delegate/src/delegated.cpp`

## RESOLV

Syntax: `RESOLV=[resolver[,resolver]*]`

Default: `cache,file,nis,dns,sys`

Resolvers to use and their order: cache, file, nis, dns, sys

```
RESOLV=cache,dns,sys
```

Source: `delegate/src/inets.cpp`

## RES_AF

Syntax: `RES_AF=afOrder`

Default: `46`

Order of the address families to look up: 46, 64, 4 or 6

```
RES_AF=64
```

Source: `delegate/src/inets.cpp`

## RES_CONF

Syntax: `RES_CONF=URL`

Default: `file:/etc/resolv.conf`

Location of the resolv.conf file read by the built-in resolver

```
RES_CONF=file:/etc/resolv.conf
```

Source: `delegate/src/inets.cpp`

## RES_DEBUG

Syntax: `RES_DEBUG=number`

Default: `none`

Debug logging level of the built-in resolver

```
RES_DEBUG=1
```

Source: `delegate/src/inets.cpp`

## RES_EXPIRE

Syntax: `RES_EXPIRE=seconds[/onmem[/dnsrr]]`

Default: `none`

[ungeprüft] Expiration time in seconds of the host cache of the resolver

```
RES_EXPIRE=300
```

Source: `delegate/src/inets.cpp`

## RES_LOG

Syntax: `RES_LOG=path`

Default: `none`

[ungeprüft] File to which the resolver appends its log

```
RES_LOG=/var/spool/delegate/log/resolv.log
```

Source: `delegate/src/inets.cpp`

## RES_NS

Syntax: `RES_NS=nsList`

Default: `taken from RES_CONF`

DNS servers to use, optionally through a Socks V5 server

```
RES_NS=192.168.1.1,END.
```

Source: `delegate/src/inets.cpp`

## RES_RR

Syntax: `RES_RR=HostList`

Default: `*`

Round robin over the IP addresses of the listed hosts

```
RES_RR=""
```

Source: `delegate/src/inets.cpp`

## RES_VRFY

Syntax: `RES_VRFY=""`

Default: `none`

Verify results of reverse lookups by a forward lookup

```
RES_VRFY=""
```

Source: `delegate/src/inets.cpp`

## RES_WAIT

Syntax: `RES_WAIT=seconds:hostname`

Default: `10:WwW.DeleGate.ORG`

Wait at start until the resolver can resolve hostname, for at most seconds

```
RES_WAIT=0
```

Source: `delegate/src/inets.cpp`

## RIDENT

Syntax: `RIDENT=ridentType[,ridentType]*`

Default: `none`

Forward (server) or receive (client) client socket information between DeleGates

```
RIDENT=server
```

Source: `delegate/src/rident.cpp`

## ROUTE

Syntax: `ROUTE=proto://host:port/-_-dstHostList:srcHostList`

Default: `none`

Forward requests for dstHostList from srcHostList to a server; generalizes MASTER and PROXY

```
ROUTE=delegate://masterhost:8080/-_-*:*
```

Source: `delegate/src/master.cpp`

## RPORT

Syntax: `RPORT={tcp|udp}[:host]`

Default: `none`

Separate response connection from the MASTER DeleGate, used together with MASTER

```
RPORT=tcp
```

Source: `delegate/src/filter.cpp`

## SAC

Syntax: `SAC=clientHost[/port][:user:pass[@host]]`

Default: `none`

[ungeprüft] Simulate an access of a client for the access control check

```
SAC=192.168.1.5/1024
```

Source: `delegate/src/access.cpp`

## SCREEN

Syntax: `SCREEN={reject|accept}[:listName]`

Default: `none`

Black (reject) or white (accept) list of client hosts, updated without restart

```
SCREEN=reject
```

Source: `delegate/src/delegated.cpp`

## SERVER

Syntax: `SERVER=protocol[://host[:portNum]][:-:MountOptions]`

Default: `delegate`

Protocol with clients and default server; SERVER=delegate makes a generalist

```
SERVER=telnet
```

Source: `delegate/src/service.cpp`

## SERVICE

Syntax: `SERVICE=name:[port[/udp]][:service]`

Default: `none`

[ungeprüft] Define a service name with a port, or as an alias of an existing service

```
SERVICE=myhttp:8080:http
```

Source: `delegate/src/service.cpp`

## SHARE

Syntax: `SHARE=dirPatternList`

Default: `empty`

Make matching files and directories accessible to all users (mode 0666 and 0777)

```
SHARE="cache/*,log/*"
```

Source: `delegate/src/delegated.cpp`

## SMTPCONF

Syntax: `SMTPCONF=what:conf`

Default: `none`

SMTP settings such as MX, reject and bgdatasize

```
SMTPCONF=bgdatasize:64K
```

Source: `delegate/src/smtp.cpp`

## SMTPGATE

Syntax: `SMTPGATE=dirPath`

Default: `${ETCDIR}/smtpgate`

Configuration directory of the SMTP to SMTP or NNTP gateway

```
SMTPGATE=/etc/delegate/smtpgate
```

Source: `delegate/src/smtpgate.cpp`

## SMTPSERVER

Syntax: `SMTPSERVER=host[:port]`

Default: `none`

[ungeprüft] SMTP server through which the DeleGate sends its own mail (port 25 by default)

```
SMTPSERVER=mailhost:25
```

Source: `delegate/src/smtp.cpp`

## SOCKMUX

Syntax: `SOCKMUX=host:port:option[,option]*`

Default: `none`

Multiplex the connection between chained DeleGates on one persistent SockMux connection

```
SOCKMUX=hostA:8000:acc
```

Source: `delegate/src/master.cpp`

## SOCKOPT

Syntax: `SOCKOPT=[no]name[:value]`

Default: `reuse`

Set socket options such as reuse, share, shut or buffer sizes

```
SOCKOPT=noreuse
```

Source: `delegate/src/inets.cpp`

## SOCKS

Syntax: `SOCKS=host[:[port][/socksOpt][:dstHostList[:srcHostList]]]`

Default: `none`

Connect via a Socks server (version 5; -4 selects version 4, -r remote name resolution)

```
SOCKS="sockshost:1080:!.localnet,!*.my.domain"
```

Source: `delegate/src/socks.cpp`

## SOCKSTAP

Syntax: `SOCKSTAP=ProtoList[:[dstHostList][:[srcHostList][:params]]]`

Default: `none`

Interpret the protocol relayed over SOCKS, so the DeleGate acts as server for it

```
SOCKSTAP=http,ftp
```

Source: `delegate/src/service.cpp`

## SOXCONF

Syntax: `SOXCONF=confSpec[,confSpec]*`

Default: `none`

Configuration of SockMux, for example crypt:no and packsize:SIZE

```
SOXCONF=crypt:no
```

Source: `delegate/src/sox.cpp`

## SRCIF

Syntax: `SRCIF=host[:[port][:connMap]]`

Default: `*:*:*:*:*`

Source address and port of connections to servers, and port for accepting data connections

```
SRCIF="*:8020-8120:ftp-data"
```

Source: `delegate/src/master.cpp`

## SSLTUNNEL

Syntax: `SSLTUNNEL=host:port`

Default: `none (port 8080 if omitted)`

HTTP proxy with the CONNECT method used as circuit level proxy for other protocols

```
SSLTUNNEL=proxyhost:8080
```

Source: `delegate/src/master.cpp`

## STATFILE

Syntax: `STATFILE=path`

Default: `none`

[ungeprüft] File to which status lines with a time stamp are written

```
STATFILE=/var/spool/delegate/status
```

Source: `delegate/src/delegated.cpp`

## STDOUTLOG

Syntax: `STDOUTLOG=LogFilename`

Default: `${LOGDIR}/stdout.log`

[ungeprüft] Log file that receives the standard output of the server

```
STDOUTLOG=stdout.log
```

Source: `delegate/src/delegated.cpp`

## STLS

Syntax: `STLS=stlsSpecs[,sslwayCom][:connMap]`

Default: `none`

Start SSL/TLS by STARTTLS negotiation with client (fcl) or server (fsv)

```
STLS="fsv,-fcl"
```

Source: `delegate/src/stls.cpp`

## SUDOAUTH

Syntax: `SUDOAUTH=pass:users:caps`

Default: `none`

[ungeprüft] Like EXECAUTH, applied when the executable file runs with super-user rights

```
SUDOAUTH=secret:root:*
```

Source: `delegate/src/dgsign.cpp`

## SYSLOG

Syntax: `SYSLOG=[syslogOpts,][syslogServ]`

Default: `none`

Send log data to a syslog server, a local file or the local syslog

```
SYSLOG=syslog://loghost:514
```

Source: `delegate/src/syslog.cpp`

## TELNETCONF

Syntax: `TELNETCONF=keepalive:seconds`

Default: `none`

[ungeprüft] Telnet settings; keepalive sets the keep-alive interval, 30 if 0

```
TELNETCONF=keepalive:30
```

Source: `delegate/src/telnet.cpp`

## THRUWAY_ENTR

Syntax: `THRUWAY_ENTR=host:port`

Default: `none`

[ungeprüft] Destination of Thruwayd, comparable to MASTER

```
THRUWAY_ENTR=desthost:8080
```

Source: `delegate/src/thruwayd.cpp`

## THRUWAY_EXIT

Syntax: `THRUWAY_EXIT=host:port`

Default: `none`

[ungeprüft] Mediator DeleGate of Thruwayd, comparable to SERVER

```
THRUWAY_EXIT=mediator:8080
```

Source: `delegate/src/thruwayd.cpp`

## TIMEOUT

Syntax: `TIMEOUT=what:seconds[,what:seconds]*`

Default: `dns:10,acc:10,con:10,lin:30,...`

Timeout periods in seconds; 0 means unlimited; units d, h and m are allowed

```
TIMEOUT=dns:5,con:20
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `acc` | `acc:T` | `10` | Accept from a client, including the FTP data connection | `TIMEOUT=acc:30` |
| `authorizer` | `authorizer:T` | `0 (unlimited)` | Expiration of an authorization by AUTHORIZER | `TIMEOUT=authorizer:600` |
| `bind` | `bind:T` | `0` | [ungeprüft] Binding of ports | `TIMEOUT=bind:10` |
| `bindenter` | `bindenter:T` | `5` | [ungeprüft] Binding of entrance ports on restart | `TIMEOUT=bindenter:10` |
| `cc` | `cc:T` | `180` | [ungeprüft] Keep a connection cache alive | `TIMEOUT=cc:300` |
| `cfistat` | `cfistat:T` | `1` | Status information from a filter started with -s | `TIMEOUT=cfistat:2` |
| `con` | `con:T` | `10` | Connection to the server | `TIMEOUT=con:20` |
| `daemon` | `daemon:T` | `0 (unlimited)` | Lifetime of the delegated process | `TIMEOUT=daemon:86400` |
| `defreeze` | `defreeze:T` | `60` | [ungeprüft] Idle time after which a frozen server is revived | `TIMEOUT=defreeze:120` |
| `dgnonce` | `dgnonce:T` | `60` | Lifetime of the nonce of AUTHORIZER=-dgauth | `TIMEOUT=dgnonce:120` |
| `dns` | `dns:T` | `10` | DNS lookup | `TIMEOUT=dns:5` |
| `dnsinv` | `dnsinv:T` | `6` | DNS inverse lookup | `TIMEOUT=dnsinv:3` |
| `erestart` | `erestart:T` | `0` | [ungeprüft] Restart after an error, used with MAXIMA erestart | `TIMEOUT=erestart:10` |
| `ftpcc` | `ftpcc:T` | `120` | Keep an FTP connection cache alive | `TIMEOUT=ftpcc:300` |
| `greeting` | `greeting:T` | `0` | [ungeprüft] Wait for the greeting message of a server | `TIMEOUT=greeting:10` |
| `hello` | `hello:T` | `30` | HELLO negotiation with the MASTER | `TIMEOUT=hello:60` |
| `htmuxskew` | `htmuxskew:T` | `300` | [ungeprüft] Maximum time difference tolerated by HTMUX | `TIMEOUT=htmuxskew:600` |
| `http-cka` | `http-cka:T` | `10` | Keep-alive connection of HTTP; replaced by HTTPCONF tout-cka | `TIMEOUT=http-cka:10` |
| `http-ckamg` | `http-ckamg:T` | `2` | [ungeprüft] Margin of the HTTP keep-alive timeout | `TIMEOUT=http-ckamg:3` |
| `http-poll-qbody` | `http-poll-qbody:T` | `15` | [ungeprüft] Polling of the body of an HTTP request | `TIMEOUT=http-poll-qbody:30` |
| `http-wait-qbody` | `http-wait-qbody:T` | `30` | [ungeprüft] Wait for the body of an HTTP request | `TIMEOUT=http-wait-qbody:60` |
| `ident` | `ident:T` | `1` | Connection to the Ident server | `TIMEOUT=ident:2` |
| `idle` | `idle:T` | `600` | Same as io | `TIMEOUT=idle:300` |
| `io` | `io:T` | `600` | General I/O without data transmission | `TIMEOUT=io:300` |
| `lin` | `lin:T` | `30` | LINGER for output | `TIMEOUT=lin:10` |
| `login` | `login:T` | `60` | Login to a proxy (Telnet, FTP, SOCKS) | `TIMEOUT=login:120` |
| `nis` | `nis:T` | `3` | NIS lookup | `TIMEOUT=nis:2` |
| `nntpcc` | `nntpcc:T` | `300` | Keep an NNTP connection cache alive | `TIMEOUT=nntpcc:600` |
| `restart` | `restart:T` | `0 (unlimited)` | Restart the server at every period | `TIMEOUT=restart:1d` |
| `rident` | `rident:T` | `1` | Receiving RIDENT=client information | `TIMEOUT=rident:2` |
| `shutout` | `shutout:T` | `1800` | Time until the emergency shutout set on a fatal error is disarmed | `TIMEOUT=shutout:0` |
| `silence` | `silence:T` | `0 (unlimited)` | No transmission from client or server, for tcprelay only | `TIMEOUT=silence:600` |
| `spawn` | `spawn:T` | `10000` | [ungeprüft] Spawn timeout; no use of the value found in the code | `TIMEOUT=spawn:20000` |
| `standby` | `standby:T` | `30` | Keep delegated alive on standby for the next client | `TIMEOUT=standby:60` |
| `takeover` | `takeover:T` | `5` | Take over a download to the cache after the client disconnected | `TIMEOUT=takeover:10` |
| `vsapacc` | `vsapacc:T` | `0` | [ungeprüft] Accept through a VSAP server | `TIMEOUT=vsapacc:60` |
| `waitchild` | `waitchild:T` | `3` | [ungeprüft] Wait for child processes to terminate | `TIMEOUT=waitchild:5` |

Source: `delegate/src/env.cpp`

## TLS

Syntax: `TLS=stlsSpecs[,sslwayCom][:connMap]`

Default: `none`

[ungeprüft] Same as STLS

```
TLS=fcl
```

Source: `delegate/src/stls.cpp`

## TLSCONF

Syntax: `TLSCONF=tlsConf[,tlsConf]*`

Default: `scache:do,xcache:do`

TLS settings such as session caches, log detail and libraries

```
TLSCONF="libs:crypto+ssl"
```

Source: `delegate/src/filter.cpp`

## TMPDIR

Syntax: `TMPDIR=dirPath`

Default: `${DGROOT?&/tmp:/tmp/delegate}`

Directory of invisible temporary files

```
TMPDIR=/var/spool/delegate/tmp
```

Source: `delegate/src/delegated.cpp`

## TRACELOG

Syntax: `TRACELOG=LogFilename`

Default: `${LOGDIR}/ptrace.log`

Log file for the signal trace written with the -T option

```
TRACELOG=ptrace.log
```

Source: `delegate/src/delegated.cpp`

## TUNNEL

Syntax: `TUNNEL=tunnelType:script`

Default: `none`

Communicate with an upstream DeleGate through the standard I/O of a script

```
TUNNEL=tty7:tunnel.shio
```

Source: `delegate/src/delegated.cpp`

## UMASK

Syntax: `UMASK=mask`

Default: `umask of the invoker`

Octal mask for file creation, set with umask(2)

```
UMASK=022
```

Source: `delegate/src/conf.cpp`

## URICONV

Syntax: `URICONV={convSpec|defElem|defAttr}`

Default: `shown by URICONV=dump`

Select the URI rewriting applied to the attributes of HTML tags

```
URICONV=dump
```

Source: `delegate/rary/html.cpp`

## VARDIR

Syntax: `VARDIR=dirPath`

Default: `${DGROOT?&:/var/spool/delegate}`

Base directory of CACHEDIR, ETCDIR, ADMDIR, LOGDIR and WORKDIR; obsolete, use DGROOT

```
VARDIR=/var/spool/delegate
```

Source: `delegate/src/delegated.cpp`

## VISUAL

Syntax: `VISUAL=command`

Default: `vi`

[ungeprüft] Editor for the argument encode and decode function; EDITOR is tried next, then vi

```
VISUAL=vi
```

Source: `delegate/src/dgsign.cpp`

## VSAP

Syntax: `VSAP=host:port`

Default: `none`

VSAP server used to accept from or connect to clients through a remote host

```
VSAP=firewall:8000
```

Source: `delegate/src/vsap.cpp`

## WORKDIR

Syntax: `WORKDIR=dirPath`

Default: `${VARDIR}/work/${PORT}`

Working directory of the server, where core files are dumped

```
WORKDIR=/var/spool/delegate/work
```

Source: `delegate/src/delegated.cpp`

## XCOM

Syntax: `XCOM=filterCommand`

Default: `none`

Command run with SERVER=exec; its standard I/O is bound to the client socket

```
XCOM=/bin/date
```

Source: `delegate/src/filter.cpp`

## XFIL

Syntax: `XFIL=filterCommand`

Default: `none`

Command run with SERVER=exec; its standard I/O is piped to the DeleGate, which relays it

```
XFIL="/bin/cat"
```

Source: `delegate/src/filter.cpp`

## YYCONF

Syntax: `YYCONF=name[:value]`

Default: `none`

Environment of the yyMux user session, such as HOME, PATH and SHELL

```
YYCONF="SHELL:/bin/sh"
```

Source: `delegate/src/X.cpp`

## YYMUX

Syntax: `YYMUX=host[:port][:connMap]`

Default: `none`

YYMUX server used as upstream proxy to tunnel and multiplex connections

```
YYMUX=hostX:6010
```

Source: `delegate/src/X.cpp`
