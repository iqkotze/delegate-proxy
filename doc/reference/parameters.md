> Generated file. Renew with `cmake --build <dir> --target param-docs`.

# DeleGate parameter reference

## ABORTLOG

Syntax: `ABORTLOG=LogFilename`

Default: `${LOGDIR}/abort/${PORT}`

Log file written on abnormal termination

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

Password checked against the built-in ADMINPASS when ADMIN is verified

```
ADMINPASS=secret
```

Source: `delegate/src/editconf.cpp`

## ARPCONF

Syntax: `ARPCONF=name:value`

Default: `command:arp %A`

ARP lookup settings: command, cache-file, cache-size, cache-expire

```
ARPCONF=cache-expire:120
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `cache-expire` | `cache-expire:seconds` | `60` | Seconds an ARP cache entry stays valid | `ARPCONF=cache-expire:120` |
| `cache-file` | `cache-file:path` | `${ACTDIR}/delegate-arp` | File that holds the ARP cache | `ARPCONF=cache-file:/run/delegate/arp` |
| `cache-size` | `cache-size:N` | `256` | Stores the value in the cache expire variable, like cache-expire; the size is not set | `ARPCONF=cache-size:256` |
| `command` | `command:commandLine` | `arp %A` | Command that looks up the MAC address of an IP address (%A) | `ARPCONF="command:arp -n %A"` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `auth` | `auth` | `off` | [ungeprüft] Cache responses to requests with authentication | `CACHE=auth` |
| `do` | `do` | `on` | Create CACHEDIR if it does not exist and enable the cache | `CACHE=do` |
| `no` | `no` | `off` | Disable the cache | `CACHE=no` |
| `nounify` | `nounify` | `off` | [ungeprüft] Do not unify the URLs of cache entries | `CACHE=nounify` |
| `ro` | `ro` | `off` | Use the cache read-only | `CACHE=ro` |

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

Directory with the certificates and keys of SSLway, also the generated default certificate

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

Same as CHARCODE

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `None` | `None (N)` | `not in the default order` | Do not connect | `CONNECT=N` |
| `cache` | `cache (c)` | `in the default order` | Search the cache without connecting | `CONNECT=c,d` |
| `direct` | `direct (d)` | `in the default order` | Connect directly to the target server; tcp also selects it | `CONNECT=d` |
| `ftp` | `ftp (f)` | `not in the default order` | [ungeprüft] Connect with the built-in FTP | `CONNECT=f,d` |
| `gateway` | `gateway (g)` | `not in the default order` | [ungeprüft] Connect via a gateway | `CONNECT=g,d` |
| `https` | `https (h)` | `in the default order` | Connect via an SSL tunnel on HTTP | `CONNECT=h,d` |
| `icp` | `icp (i)` | `in the default order` | Connect via a PROXY hinted by an ICP server | `CONNECT=c,i,d` |
| `internal` | `internal (l)` | `not in the default order` | [ungeprüft] Connect to an internal service | `CONNECT=l,d` |
| `master` | `master (m)[/p]` | `in the default order` | Connect via a PROXY or a MASTER DeleGate | `CONNECT=m,d` |
| `proxy` | `proxy (p)` | `not in the default order` | Connect via a PROXY server | `CONNECT=p,d` |
| `socks` | `socks (s)` | `in the default order` | Connect via SOCKS servers | `CONNECT=s,d` |
| `teleport` | `teleport (t)` | `not in the default order` | [ungeprüft] Connect via a teleport tunnel | `CONNECT=t,d` |
| `udp` | `udp (u)` | `not in the default order` | Connect by UDP | `CONNECT=u` |
| `vsap` | `vsap (v)[/arg]` | `in the default order` | Connect via a VSAP server | `CONNECT=v,d` |
| `yymux` | `yymux (y)` | `in the default order` | Connect via a YYMUX server | `CONNECT=y,d` |

Source: `delegate/src/master.cpp`

## COUNTER

Syntax: `COUNTER=listOfCounterControl`

Default: `no`

Access counters: do, total, acc, ssi, ref, err, ro, no

```
COUNTER=do
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `acc` | `acc` | `off` | Enable an access counter for each requested URL | `COUNTER=acc` |
| `all` | `all` | `off` | Same as do | `COUNTER=all` |
| `debug` | `debug[N]` | `off` | Debug level of the counters, hexadecimal | `COUNTER=debug1` |
| `do` | `do` | `off` | Enable all counters: total, acc, ssi, ref and err | `COUNTER=do` |
| `err` | `err` | `off` | Enable the error counters for SMTP | `COUNTER=err` |
| `inc` | `inc` | `off` | [ungeprüft] Increment the counters | `COUNTER=inc` |
| `mntpr` | `mntpR` | `off` | [ungeprüft] Use the counter of the real URL (rURL) of the MOUNT point | `COUNTER=mntpR` |
| `mntpv` | `mntpV` | `off` | Use the counter of the MOUNT point (vURL) instead of each URL | `COUNTER=mntpV` |
| `no` | `no` | `on` | Disable all counters | `COUNTER=no` |
| `ref` | `ref` | `off` | Enable the referrer counters for the HTTP Referer field | `COUNTER=ref` |
| `ro` | `ro` | `off` | Enable the counters in read-only mode | `COUNTER=ro` |
| `ssi` | `ssi` | `off` | Enable the access counters for SSI PAGE_COUNT | `COUNTER=ssi` |
| `total` | `total` | `off` | Enable the total hit counter of the server | `COUNTER=total` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `error` | `error:seconds` | `30` | [ungeprüft] Delay after communication errors; parsed, the code using it is commented out | `DELAY=error:30` |
| `reject` | `reject:seconds` | `60` | Maximum delay before continuous Reject responses of DeleGate or MOUNTed servers | `DELAY=reject:30` |
| `reject_p` | `reject_p:seconds` | `0` | Maximum delay before continuous Reject responses of the origin server | `DELAY=reject_p:10` |
| `unknown` | `unknown:seconds` | `60` | Maximum delay before continuous Unknown responses of DeleGate or MOUNTed servers | `DELAY=unknown:30` |
| `unknown_p` | `unknown_p:seconds` | `0` | Maximum delay before continuous Unknown responses of the origin server | `DELAY=unknown_p:10` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `conn` | `name,conn:data` | `off` | Substitute connection information into the data | `DGDEF=name,conn:data` |
| `ei` | `name,ei:data` | `off` | [ungeprüft] Flag: evaluate on initialization | `DGDEF=name,ei:data` |
| `si` | `name,si:data` | `off` | [ungeprüft] Flag: substitute on initialization | `DGDEF=name,si:data` |
| `url` | `name,url:data` | `off` | [ungeprüft] Flag: the data is a URL | `DGDEF=name,url:data` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `acctcp` | `acctcp` | `off` | Accept DNS queries over TCP | `DNSCONF=acctcp` |
| `admin` | `admin:Email` | `ADMIN` | Mail address of the administrator in the SOA record | `DNSCONF=admin:root@my.domain` |
| `cltcp` | `cltcp` | `off` | [ungeprüft] Use TCP for DNS messages on the client side | `DNSCONF=cltcp` |
| `dbgvul` | `dbgvul` | `off` | [ungeprüft] Skip the overrun check of the question section, for debugging | `DNSCONF=dbgvul` |
| `domain` | `domain:FQDN` | `domain of the host of DeleGate` | Domain name used in the SOA record | `DNSCONF=domain:my.domain` |
| `expire` | `expire:period` | `14d` | Expire period of the SOA record | `DNSCONF=expire:14d` |
| `minttl` | `minttl:period` | `6h` | Minimum TTL of the SOA record | `DNSCONF=minttl:6h` |
| `mx` | `mx:FQDN` | `primary host of -MX.host or the inquired host` | Host name returned in MX records | `DNSCONF=mx:mail.my.domain` |
| `origin` | `origin:FQDN` | `host name of the host of DeleGate` | Host name used in the SOA record | `DNSCONF=origin:ns.my.domain` |
| `para` | `para:N` | `2` | Number of parallel server processes | `DNSCONF=para:4` |
| `refresh` | `refresh:period` | `6h` | Refresh interval of the SOA record | `DNSCONF=refresh:6h` |
| `retry` | `retry:period` | `10m` | Retry interval of the SOA record | `DNSCONF=retry:10m` |
| `serial` | `serial:N` | `date and hour of the last configuration change` | Serial number of the SOA record | `DNSCONF=serial:2026100201` |
| `svtcp` | `svtcp` | `off` | [ungeprüft] Use TCP for DNS messages on the server side | `DNSCONF=svtcp` |

Source: `delegate/src/domain.cpp`

## DYCONF

Syntax: `DYCONF=[conditions]parameters`

Default: `none`

Load parameters from a file, CGI or inline list at the start of each session

```
DYCONF="file:path.txt"
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `arg` | `arg:{listOfParameters}` | `none` | Load the listed parameters | `DYCONF="arg:{SERVER=tcprelay://sv1:1234;TIMEOUT=io:3}"` |
| `cgi` | `cgi:path` | `none` | Load parameters generated by the CGI program path | `DYCONF=cgi:path.cgi` |
| `clif` | `clif/hostList` | `none` | Condition: the interface of the client connection is included in hostList | `DYCONF="clif/localhost,file:path.txt"` |
| `debug` | `debug` | `off` | Enable logging for debugging of DYCONF | `DYCONF="debug,file:path.txt"` |
| `excl` | `excl[/number]` | `off` | Condition: exclusive with other DYCONFs | `DYCONF="excl,file:path.txt"` |
| `file` | `file:path` | `none` | Load parameters from the file path | `DYCONF=file:path.txt` |
| `from` | `{from/hostList}` | `none` | Condition: the client host is in hostList | `DYCONF="{from/.localnet},file:path.txt"` |
| `peek` | `peek/bytes` | `4k` | Maximum number of bytes peeked from the request | `DYCONF="peek/1k,file:path.txt"` |
| `poll` | `poll/seconds` | `15.0` | Timeout of polling for the request | `DYCONF="poll/5,file:path.txt"` |
| `qrex` | `qrex/pattern` | `none` | Condition: the request matches the pattern | `DYCONF="{qrex/[a-z][0-9]*},arg:{SERVER=tcprelay://sv1:1234}"` |
| `qstr` | `qstr/string` | `none` | Condition: the request contains the sub-string | `DYCONF="qstr/GET,file:path.txt"` |
| `skip` | `skip` | `off` | Purge the peeked data before starting the relay | `DYCONF="skip,file:path.txt"` |

Source: `delegate/src/env.cpp`

## DYLIB

Syntax: `DYLIB=libfilePattern[,libfilePattern]*`

Default: `lib%s.so,lib%s.so.0,lib%s.so.1,%s`

File name patterns for the dynamic libraries of PAM, m17n and regex; + stands for the default list

```
DYLIB="+,lib*.so.2"
```

Source: `delegate/filters/dl.cpp`

## EDITOR

Syntax: `EDITOR=command`

Default: `vi`

Editor for the parameters of an executable file; VISUAL is tried next, then vi

```
EDITOR=vi
```

Source: `delegate/src/dgsign.cpp`

## ENTR

Syntax: `ENTR=proto://host:port/path`

Default: `none`

Open an entrance for a protocol on a host and port

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `bounce` | `bounce:{no\|do\|th\|cb\|rl}` | `no` | FTP Bounce: reject (no), permit (do), ignore (th), convert to EPRT (cb), per REJECT (rl) | `FTPCONF=bounce:no` |
| `ccx` | `ccx:{any\|anytype\|autosvcc\|command\|response}` | `none` | Character code conversion of commands and responses; any, anytype, autosvcc, command, response | `FTPCONF=ccx:command` |
| `chokedata` | `chokedata:N` | `0` | [ungeprüft] Limit the data transfer | `FTPCONF=chokedata:1024` |
| `debug` | `debug:N` | `0` | Debug flags of the FTP processing, decimal or 0xHEX | `FTPCONF=debug:1` |
| `default` | `default` | `none` | Reset all FTPCONF settings to their defaults | `FTPCONF=default` |
| `dfltuser` | `dfltuser:user` | `none` | [ungeprüft] Default user name | `FTPCONF=dfltuser:anonymous` |
| `doeprt` | `doeprt[:sv]` | `off` | Use EPRT instead of PORT with FTP servers | `FTPCONF=doeprt:sv` |
| `doepsv` | `doepsv[:{sv\|cl}]` | `off` | Use EPSV instead of PASV, with servers (sv) or clients (cl) | `FTPCONF=doepsv:sv` |
| `forcexdc` | `forcexdc` | `off` | Enable the XDC mode even if the destination server is on the same host | `FTPCONF=forcexdc` |
| `ftp_on_http` | `ftp_on_http` | `off` | [ungeprüft] Handle FTP on an HTTP connection | `FTPCONF=ftp_on_http` |
| `hideserv` | `hideserv` | `off` | Do not relay the opening message of the server to the client | `FTPCONF=hideserv` |
| `immport` | `immport[:cl]` | `off` | Do not postpone the PORT command with the client | `FTPCONF=immport` |
| `lpr_nowait` | `lpr_nowait` | `off` | [ungeprüft] Do not wait for the completion of LPR printing | `FTPCONF=lpr_nowait` |
| `maxreload` | `maxreload:N` | `8192` | Maximum size of a cache file reloaded without verification | `FTPCONF=maxreload:8192` |
| `nodata` | `nodata` | `off` | Do nothing for data connections | `FTPCONF=nodata` |
| `noepsv` | `noepsv[:cl]` | `off` | Do not accept EPSV from clients | `FTPCONF=noepsv` |
| `nomlsx` | `nomlsx` | `off` | Do not support MLST and MLSD for clients | `FTPCONF=nomlsx` |
| `nopasv` | `nopasv[:{sv\|cl}]` | `off` | Disable the PASV command for data connections, on the server or client side | `FTPCONF=nopasv:sv` |
| `noport` | `noport[:{sv\|cl}]` | `off` | Disable the PORT command for data connections, on the server or client side | `FTPCONF=noport:cl` |
| `nostat` | `nostat` | `off` | [ungeprüft] Sets a flag for the STAT command with servers that no code reads | `FTPCONF=nostat` |
| `nounesc` | `nounesc` | `off` | Do not unescape %XX in arguments sent to the server | `FTPCONF=nounesc` |
| `noxdc` | `noxdc[:{sv\|cl}]` | `off` | Disable the XDC mode for data transmission on the control connection | `FTPCONF=noxdc` |
| `nullpwd` | `nullpwd` | `off` | Allow the response 257  to the PWD command | `FTPCONF=nullpwd` |
| `pasvdebug` | `pasvdebug` | `off` | [ungeprüft] Debug output of PASV handling | `FTPCONF=pasvdebug` |
| `proxy` | `proxy:host` | `none` | Commands that select the target server in proxy mode: user, open, site, path | `FTPCONF=proxy:proxyhost` |
| `proxyauth` | `proxyauth[:{userhostmap\|hostmap\|usergen\|authgen}]` | `off` | Authenticate as a proxy FTP server; user@server is split into user and server | `FTPCONF=proxyauth` |
| `rawxdc` | `rawxdc[:{sv\|cl}]` | `off` | Transmit data in XDC mode without BASE64 encoding | `FTPCONF=rawxdc` |
| `swmaster` | `swmaster` | `off` | Switch the server by user@site in the MASTER DeleGate | `FTPCONF=swmaster` |
| `thruesc` | `thruesc[:{user\|pass\|path}]` | `off` | Pass %XX notation through without unescaping for the user name, password or path | `FTPCONF=thruesc:path` |
| `timeout` | `timeout:seconds` | `300` | Timeout in seconds for data from the server and from the client | `FTPCONF=timeout:60` |
| `uno` | `uno:string` | `none` | [ungeprüft] Unique name string | `FTPCONF=uno:name` |
| `usdelim` | `usdelim:delimiters` | `*%#` | Characters usable instead of @ in user@site | `FTPCONF=usdelim:*%#` |
| `waitssl` | `waitssl` | `off` | Wait for SSL before returning the 150 response | `FTPCONF=waitssl` |

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

Function to run when no -F option is given

```
FUNC=ver
```

Source: `delegate/src/delegated.cpp`

## GATEWAY

Syntax: `GATEWAY=gatewayURL[-_-connMap]`

Default: `none`

Same as FORWARD

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `debug` | `debug` | `off` | [ungeprüft] Log the HTML conversion | `HTMLCONV=debug` |
| `deent` | `deent` | `on` | Decode entity symbols appearing in multi-byte charset text | `HTMLCONV=deent` |
| `defattr` | `defattr:+,attrList` | `none` | Define the HTML attributes considered by the URI rewriting, like URICONV defattr | `HTMLCONV=defattr:+,SRC` |
| `defelem` | `defelem:+,elemList` | `none` | Define the HTML elements considered by the URI rewriting, like URICONV defelem | `HTMLCONV=defelem:+,IMG` |
| `dump` | `dump` | `off` | Show the current URI conversion settings | `HTMLCONV=dump` |
| `enent` | `enent` | `off` | Encode entity symbols appearing outside multi-byte charset text | `HTMLCONV=enent` |
| `fullurl` | `fullurl` | `off` | Convert all URLs to full URLs; equals URICONV=full:+,-HREF/BASE | `HTMLCONV=fullurl` |
| `killtag` | `killtag:tagList` | `none` | Disable the listed tags in HTML responses, like HTTPCONF kill-tag | `HTMLCONV=killtag:SCRIPT` |
| `normal` | `normal` | `off` | Normalize MOUNTed URLs that contain ../ | `HTMLCONV=normal` |
| `partial` | `partial` | `off` | Represent MOUNTed URLs as partial URLs if possible | `HTMLCONV=partial` |
| `pre` | `pre` | `off` | [ungeprüft] Convert plain text to HTML with PRE | `HTMLCONV=pre` |
| `uri` | `uri:convSpec` | `none` | Set the URI conversion, like URICONV | `HTMLCONV=uri:full:+` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `acc-encoding` | `acc-encoding:encoding [-thrugzip]` | `-thrugzip` | Accept-Encoding sent to the server; identity disables encodings | `HTTPCONF=acc-encoding:identity` |
| `add-head` | `add-head:name:body` | `none` | Add a header field to forwarded requests and responses | `HTTPCONF=add-head:X-Proxy:delegate` |
| `add-ihead` | `add-ihead:name:body` | `none` | Add a header field to requests and responses before DeleGate interprets them | `HTTPCONF=add-ihead:Pragma:no-cache` |
| `add-iqhead` | `add-iqhead:name:body` | `none` | Add a header field to requests before DeleGate interprets them | `HTTPCONF=add-iqhead:Pragma:no-cache` |
| `add-irhead` | `add-irhead:name:body` | `none` | Add a header field to responses before DeleGate interprets them | `HTTPCONF=add-irhead:Pragma:no-cache` |
| `add-qhead` | `add-qhead:name:body` | `none` | Add a header field to forwarded requests; %a etc. insert client information | `HTTPCONF="add-qhead:X-Forwarded-For:%a"` |
| `add-rhead` | `add-rhead:name:body` | `none` | Add a header field to forwarded responses | `HTTPCONF=add-rhead:X-Proxy:delegate` |
| `applet` | `applet:warn` | `off` | [ungeprüft] Warn about APPLET tags in responses | `HTTPCONF=applet:warn` |
| `badhead` | `badhead:rej` | `off` | Reject requests with a bad header | `HTTPCONF=badhead:rej` |
| `belocal` | `belocal:types` | `shtml` | [ungeprüft] Types of files evaluated locally | `HTTPCONF=belocal:shtml` |
| `bugs` | `bugs:bugList` | `none` | Disable features to bypass bugs, such as no-gzip, no-keepalive, no-chunked or thru-304 | `HTTPCONF=bugs:no-gzip` |
| `cache` | `cache:{any\|nolastmod\|302\|cookie\|vary\|less-reload\|auth}` | `none` | [ungeprüft] Allow caching of responses that are not cached by default | `HTTPCONF=cache:nolastmod,cookie` |
| `ccx-url-ie` | `ccx-url-ie:nameList` | `ie,ei,ENCODING` | URL query names whose value names the input character set | `HTTPCONF=ccx-url-ie:ie,enc` |
| `chunked-cleng` | `chunked-cleng:N` | `0` | [ungeprüft] Content-Length values below this size are dropped from chunked responses | `HTTPCONF=chunked-cleng:65536` |
| `cka-cfi` | `cka-cfi` | `off` | Keep the client connection alive even with an external filter (FCL, FTOCL) | `HTTPCONF=cka-cfi` |
| `clauth` | `clauth:{force-basic\|thru-digest}` | `none` | [ungeprüft] Client authentication: force Basic or pass Digest through | `HTTPCONF=clauth:thru-digest` |
| `clver` | `clver:{1.0\|0.9rej}` | `HTTP/1.1` | Act as an HTTP/1.0 server against clients, without chunked encoding; 0.9rej rejects HTTP/0.9 | `HTTPCONF=clver:1.0` |
| `cryptcookie` | `cryptCookie:cookieList:key` | `none` | Encrypt the listed Set-Cookie attributes and return them only to their originator | `HTTPCONF="cryptCookie:UserID@.example.com:secret"` |
| `default-vhost` | `default-vhost:host` | `none` | Host name added as Host field to requests without a Host field | `HTTPCONF=default-vhost:www.example.com` |
| `deletecookie` | `deleteCookie:cookieList` | `none` | [ungeprüft] Delete the listed cookies | `HTTPCONF=deleteCookie:UserID@.example.com` |
| `dgcroute` | `dgcroute:no` | `on` | [ungeprüft] no disables routing of the DeleGate specific headers to the upstream | `HTTPCONF=dgcroute:no` |
| `dumpstat` | `dumpstat` | `off` | [ungeprüft] Dump the status of the HTTP processing | `HTTPCONF=dumpstat` |
| `gen-encoding` | `gen-encoding:encoding` | `gzip` | Content encoding applied to data sent to the client; only gzip exists | `HTTPCONF=gen-encoding:identity` |
| `halfdup` | `halfdup` | `off` | Forbid full-duplex use of an SSLtunnel by the CONNECT method | `HTTPCONF=halfdup` |
| `ignif` | `ignif` | `off` | Ignore the If-* header fields of requests | `HTTPCONF=ignif` |
| `kill-head` | `kill-head:headerList` | `none` | Erase the listed header fields from both requests and responses | `HTTPCONF=kill-head:Via` |
| `kill-ihead` | `kill-ihead:headerList` | `none` | Erase the listed fields from requests and responses before DeleGate interprets them | `HTTPCONF=kill-ihead:Pragma` |
| `kill-iqhead` | `kill-iqhead:headerList` | `none` | Erase the listed fields from requests before DeleGate interprets them | `HTTPCONF=kill-iqhead:Pragma,Cache-Control` |
| `kill-irhead` | `kill-irhead:headerList` | `none` | Erase the listed fields from responses before DeleGate interprets them | `HTTPCONF=kill-irhead:Pragma` |
| `kill-qhead` | `kill-qhead:headerList` | `none` | Erase the listed header fields from requests before forwarding to the server | `HTTPCONF=kill-qhead:Referer` |
| `kill-rhead` | `kill-rhead:headerList` | `none` | Erase the listed header fields from responses before forwarding to the client | `HTTPCONF=kill-rhead:Set-Cookie` |
| `kill-tag` | `kill-tag:tagList` | `none` | Disable the listed tags in text/html responses | `HTTPCONF=kill-tag:SCRIPT,APPLET` |
| `kill-xhead` | `kill-xhead:headerList` | `none` | [ungeprüft] Erase the listed fields from requests and responses, applied to input and output | `HTTPCONF=kill-xhead:Via` |
| `kill-xqhead` | `kill-xqhead:headerList` | `none` | [ungeprüft] Erase the listed fields from requests, applied to input and output | `HTTPCONF=kill-xqhead:Referer` |
| `kill-xrhead` | `kill-xrhead:headerList` | `none` | [ungeprüft] Erase the listed fields from responses, applied to input and output | `HTTPCONF=kill-xrhead:Set-Cookie` |
| `max-buff-reqbody` | `max-buff-reqbody:size` | `1M` | Maximum size of the buffered request body | `HTTPCONF=max-buff-reqbody:1M` |
| `max-cka` | `max-cka:N` | `50` | Maximum number of requests relayed on a keep-alive connection | `HTTPCONF=max-cka:100` |
| `max-ckapch` | `max-ckapch:N` | `8` | Maximum number of keep-alive connections per client host | `HTTPCONF=max-ckapch:8` |
| `max-gw-reqline` | `max-gw-reqline:size` | `512` | Maximum length of a request line forwarded to a server of another protocol | `HTTPCONF=max-gw-reqline:512` |
| `max-hops` | `max-hops:N` | `20` | Maximum number of hops in the chain of HTTP proxies | `HTTPCONF=max-hops:20` |
| `max-paras` | `max-paras:N` | `5` | [ungeprüft] Maximum number of parallel connections | `HTTPCONF=max-paras:5` |
| `max-reqhead` | `max-reqhead:size` | `12k` | Maximum length of the request header | `HTTPCONF=max-reqhead:12k` |
| `max-reqline` | `max-reqline:size` | `8k` | Maximum length of the request line | `HTTPCONF=max-reqline:8k` |
| `max-reshead-peep` | `max-reshead-peep:size` | `1024` | Size of the response header peeked for inspection | `HTTPCONF=max-reshead-peep:1024` |
| `max-ssl-turns` | `max-ssl-turns:N` | `100` | Maximum number of request and response pairs on an SSLtunnel; 0 derives it from max-cka | `HTTPCONF=max-ssl-turns:100` |
| `methods` | `methods:methodList` | `OPTIONS,GET,HEAD,POST,PUT,...` | Limit or add accepted HTTP methods; -NAME removes, +,NAME adds, * accepts any | `HTTPCONF=methods:GET,HEAD` |
| `min-chunked` | `min-chunked:size` | `4k` | Responses with a Content-Length below this size are not sent chunked | `HTTPCONF=min-chunked:4k` |
| `min-gzip` | `min-gzip:size` | `256` | Bodies smaller than this size are not gzip encoded | `HTTPCONF=min-gzip:256` |
| `modwatch` | `modwatch:notifyto[=addr],approver[=hosts]` | `off` | [ungeprüft] Watch modified pages; notifyto sets the mail address, approver the approving hosts | `HTTPCONF=modwatch:notifyto=admin@example.com` |
| `no-cache` | `no-cache:no-cache` | `no-cache is honored` | [ungeprüft] With no-cache in the list, the no-cache directive no longer prevents caching | `HTTPCONF=no-cache:no-cache` |
| `no-delay` | `no-delay` | `off` | Set TCP_NODELAY on the client connection | `HTTPCONF=no-delay` |
| `nolog` | `nolog:codeType[:connMap]` | `none` | Response codes or Content-Types not written to the access log | `HTTPCONF="nolog:302,304,image"` |
| `nomenu` | `nomenu` | `off` | [ungeprüft] Do not put the menu into generated pages | `HTTPCONF=nomenu` |
| `nvhost` | `nvhost` | `none` | [ungeprüft] Accepted without effect; MOUNT option nvhost sets virtual hosts | `HTTPCONF=nvhost` |
| `nvserv` | `nvserv:{noauto\|auto\|alias\|gen\|none}` | `noauto` | Detection of name based virtual servers in MOUNT parameters | `HTTPCONF=nvserv:auto` |
| `passesc` | `passesc:escChars` | `%C (control characters)` | [ungeprüft] Characters escaped in passwords | `HTTPCONF=passesc:%C` |
| `pathext` | `pathext:ext` | `none` | [ungeprüft] Extension inserted into the path to select variant files | `HTTPCONF=pathext:-ja` |
| `post-ccx-type` | `post-ccx-type:typeList` | `application/x-www-form-urlencoded` | Content-Types of request bodies converted by CHARCODE | `HTTPCONF=post-ccx-type:+,multipart/form-data` |
| `proxycontrol` | `proxycontrol[:{on\|off\|mark}]` | `off` | Use the string after ?_? in the request URL as control information for DeleGate | `HTTPCONF=proxycontrol:on` |
| `replace-head` | `replace-head:name:body` | `none` | Replace the header fields of the name in forwarded requests and responses | `HTTPCONF=replace-head:Via:proxy` |
| `replace-ihead` | `replace-ihead:name:body` | `none` | Replace the header fields of the name in requests and responses before interpretation | `HTTPCONF=replace-ihead:Pragma:no-cache` |
| `replace-iqhead` | `replace-iqhead:name:body` | `none` | Replace the header fields of the name in requests before DeleGate interprets them | `HTTPCONF=replace-iqhead:Pragma:no-cache` |
| `replace-irhead` | `replace-irhead:name:body` | `none` | Replace the header fields of the name in responses before DeleGate interprets them | `HTTPCONF=replace-irhead:Pragma:no-cache` |
| `replace-qhead` | `replace-qhead:name:body` | `none` | Replace the header fields of the name in forwarded requests | `HTTPCONF=replace-qhead:Referer:http://x.y.z` |
| `replace-rhead` | `replace-rhead:name:body` | `none` | Replace the header fields of the name in forwarded responses | `HTTPCONF=replace-rhead:Server:proxy` |
| `rvers` | `rvers:versionList` | `HTTP` | Accepted versions in the status line of server responses; +,NAME adds, * accepts any | `HTTPCONF=rvers:+,ICY` |
| `search` | `search:scriptPath` | `none` | CGI script applied to all URLs with a search part (?query) | `HTTPCONF=search:/usr/lib/cgi-bin/search.cgi` |
| `session` | `session[:cookie]` | `off` | Enable session management based on Cookie; the ID is passed as X_COOKIE_SESSION | `HTTPCONF=session` |
| `svauth` | `svauth:{no-basic\|less-basic}` | `none` | no-basic stops forwarding Basic authorization; less-basic delays it until the server asks | `HTTPCONF=svauth:no-basic` |
| `svver` | `svver:1.0` | `HTTP/1.1` | Act as an HTTP/1.0 client against servers | `HTTPCONF=svver:1.0` |
| `thru-type` | `thru-type:typeList` | `application/zip,application/x-rpm,application/microsoftpatch` | [ungeprüft] Content-Types passed through without interpretation; +,type adds | `HTTPCONF=thru-type:+,application/pdf` |
| `thru-ua` | `thru-UA:uaList` | `none` | [ungeprüft] User-Agent patterns passed through unchanged | `HTTPCONF=thru-UA:Mozilla*` |
| `tout-buff-reqbody` | `tout-buff-reqbody:period` | `5` | Maximum time to buffer the request message to the server | `HTTPCONF=tout-buff-reqbody:5` |
| `tout-buff-resbody` | `tout-buff-resbody:period` | `8` | Maximum time to buffer the response message to the client | `HTTPCONF=tout-buff-resbody:8` |
| `tout-cka` | `tout-cka:period` | `10` | Maximum time to keep a connection with the client alive | `HTTPCONF=tout-cka:10` |
| `tout-cka-resp` | `tout-cka-resp:period` | `10` | Timeout for the response line on a reused server connection | `HTTPCONF=tout-cka-resp:10` |
| `tout-ckamg` | `tout-ckamg:period` | `2` | Margin added to the keep-alive timeout | `HTTPCONF=tout-ckamg:3` |
| `tout-in-reqbody` | `tout-in-reqbody:period` | `15` | Maximum time to wait for further data of the request body | `HTTPCONF=tout-in-reqbody:15` |
| `tout-pack-intvl` | `tout-pack-intvl:period` | `10.0` | Maximum interval between packets relayed on an SSLtunnel by the CONNECT method | `HTTPCONF=tout-pack-intvl:10` |
| `tout-reqbody` | `tout-reqbody:period` | `120` | Timeout for relaying the request body | `HTTPCONF=tout-reqbody:60` |
| `tout-resp` | `tout-resp:period` | `0` | Maximum time to wait for the response from the server; 0 uses TIMEOUT io | `HTTPCONF=tout-resp:60` |
| `tout-threadp` | `tout-threadp:seconds` | `30` | Seconds to wait for the request body thread | `HTTPCONF=tout-threadp:30` |
| `tout-wait-badsv` | `tout-wait-badsv:period` | `3` | Maximum period to care for a server with a bad protocol | `HTTPCONF=tout-wait-badsv:3` |
| `tout-wait-reqbody` | `tout-wait-reqbody:period` | `30` | Maximum time to wait for the first data of the request body | `HTTPCONF=tout-wait-reqbody:30` |
| `urlesc` | `urlesc[:escChars]` | `none` | Characters of the request URL escaped as %XX before processing; empty means <> | `HTTPCONF=urlesc:<>` |
| `urlsearch` | `urlsearch:all` | `none` | [ungeprüft] Search URLs to rewrite in any text, not only in HTML tags | `HTTPCONF=urlsearch:all` |
| `urlunifyports` | `urlunifyports` | `off` | [ungeprüft] Unify default port numbers in URLs | `HTTPCONF=urlunifyports` |
| `ver` | `ver:1.0` | `HTTP/1.1` | Act as an HTTP/1.0 client and server | `HTTPCONF=ver:1.0` |
| `warn-reqline` | `warn-reqline:size` | `1024` | Header length from which a suspicious header is logged | `HTTPCONF=warn-reqline:1024` |
| `watchmod` | `watchmod:notifyto[=addr],approver[=hosts]` | `off` | [ungeprüft] Same as modwatch | `HTTPCONF=watchmod:notifyto=admin@example.com` |
| `welcome` | `welcome:fileList` | `welcome.{dgp,shtml,html,cgi},index.{dgp,shtml,html,cgi},-dir.html` | Candidate index files for URLs ending with /; -dir.html is the built-in index generator | `HTTPCONF=welcome:index.html,-dir.html` |
| `xferlog` | `xferlog:ftp` | `off` | Also record FTP and HTTP transactions in xferlog format | `HTTPCONF=xferlog:ftp` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `debug` | `debug:N` | `0` | Level of debug logging | `ICPCONF=debug:1` |
| `hitage` | `hitage:period` | `1d` | Valid age of cached data reported as HIT | `ICPCONF=hitage:2d` |
| `hitobjage` | `hitobjage:period` | `1h` | Valid age of cached data sent as HIT_OBJ | `ICPCONF=hitobjage:30m` |
| `hitobjsize` | `hitobjsize:bytes` | `1024` | Maximum size of cached data sent as HIT_OBJ | `ICPCONF=hitobjsize:2048` |
| `nofetch` | `nofetch:period` | `1d` | [ungeprüft] Parsed but not used by the ICP code | `ICPCONF=nofetch:1d` |
| `para` | `para:N` | `2` | Number of parallel ICP-DeleGate servers | `ICPCONF=para:4` |
| `timeout` | `timeout:seconds` | `2.0` | Default timeout when waiting for a response | `ICPCONF=timeout:3.0` |

Source: `delegate/src/icp.cpp`

## IMAGEDIR

Syntax: `IMAGEDIR=dirPath`

Default: `none`

Directory of the icon images referred to by Gopher menus

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

Enables the import of parameters at run time; the value is not evaluated

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

IPv6 handling; 4map unifies mapped addresses, 6also and 4also add the other family

```
IPV6=6also
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `4also` | `4also[:no]` | `off` | [ungeprüft] Turn IPV6_V6ONLY off on IPv6 sockets | `IPV6=4also` |
| `4map` | `4map[:no]` | `on` | Unify IPv4-mapped IPv6 addresses with IPv4 addresses | `IPV6=4map:no` |
| `6also` | `6also[:no]` | `off` | Open entrance sockets as IPv6 sockets that also accept IPv4 | `IPV6=6also` |

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

Directory of library files, referred to as ${LIBDIR} in LIBPATH

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

Linger time in seconds of the output side of sockets

```
LINGER=10
```

Source: `delegate/src/delegated.cpp`

## LOG

Syntax: `LOG=proto:filters:logform:pathform`

Default: `none`

Additional log file for a protocol, with filter, format and path

```
LOG=http:*:%C:http.log
```

Source: `delegate/src/delegated.cpp`

## LOGCENTER

Syntax: `LOGCENTER=host:port`

Default: `none (an empty value selects www.delegate.org:8000)`

Log center that the server opens a UDP client connection to

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

Enable the m17n library for character code conversion

```
M17N=on
```

Source: `delegate/src/delegated.cpp`

## MAILSPOOL

Syntax: `MAILSPOOL=pop://user@host`

Default: `none`

POP server that holds the mail spool for -Fpoprelay and -Fpopdown

```
MAILSPOOL=pop://user@mailhost
```

Source: `delegate/src/pop.cpp`

## MANAGER

Syntax: `MANAGER=user@host.domain`

Default: `none`

Obsolete alias of ADMIN

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

Default: `listen:somaxconn,delegated:auto,standby:32,ftpcc:16,...`

Maxima of resources: processes, connections, queue sizes and similar

```
MAXIMA=delegated:256,listen:1024
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `bps` | `bps:N` | `0 (unlimited)` | Maximum transmission speed of HTTP and FTP data in bits per second; k and m units are allowed | `MAXIMA=bps:128k` |
| `conpch` | `conpch:N` | `0 (unlimited)` | Maximum number of connections at a time per client host | `MAXIMA=conpch:20` |
| `contry` | `contry:N` | `2` | [ungeprüft] Number of connection trials to a server | `MAXIMA=contry:3` |
| `delegated` | `delegated:N` | `min(available memory / 4 MiB, (open file limit - 64) / 2, 4096), at least 64` | Maximum number of DeleGate processes running at a time | `MAXIMA=delegated:256` |
| `erestart` | `erestart:N` | `1` | Maximum number of restarts after an error, used with TIMEOUT erestart | `MAXIMA=erestart:3` |
| `fdset` | `fdset:N` | `64` | Base size of the descriptor set, extended by three per delegated process | `MAXIMA=fdset:128` |
| `ftpcc` | `ftpcc:N` | `16` | Maximum number of FTP connection cache servers to a host (shared with nntpcc and svcc) | `MAXIMA=ftpcc:4` |
| `http-cka` | `http-cka:N` | `50` | Maximum requests per keep-alive connection; replaced by HTTPCONF max-cka | `MAXIMA=http-cka:50` |
| `http-ckapch` | `http-ckapch:N` | `8` | Maximum keep-alive connections per client host; replaced by HTTPCONF max-ckapch | `MAXIMA=http-ckapch:8` |
| `listen` | `listen:N` | `net.core.somaxconn of the kernel (4096 if unreadable)` | Maximum size of the queue of an entrance port | `MAXIMA=listen:1024` |
| `nntpcc` | `nntpcc:N` | `16` | Maximum number of NNTP connection cache processes to a host (shared with ftpcc and svcc) | `MAXIMA=nntpcc:4` |
| `randenv` | `randenv:N` | `1024` | Randomization range of the environment variables base | `MAXIMA=randenv:1024` |
| `randfd` | `randfd:N` | `32` | Randomization range of the client socket descriptor | `MAXIMA=randfd:32` |
| `randstack` | `randstack:N` | `64` | Randomization range of the stack base for security | `MAXIMA=randstack:32` |
| `restart` | `restart:N` | `0` | Restart the server after N accepted connections | `MAXIMA=restart:10000` |
| `service` | `service:N` | `0 (unlimited)` | Maximum number of services per delegated process | `MAXIMA=service:1000` |
| `sockrecv` | `sockrecv:N` | `65536` | Maximum size of the socket receive buffer in bytes | `MAXIMA=sockrecv:131072` |
| `socksend` | `socksend:N` | `16384` | Maximum size of the socket send buffer in bytes | `MAXIMA=socksend:32768` |
| `standby` | `standby:N` | `32` | Maximum number of standby processes | `MAXIMA=standby:16` |
| `svcc` | `svcc:N` | `16` | Maximum number of connection cache servers (shared with ftpcc and nntpcc) | `MAXIMA=svcc:4` |
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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `hide` | `hide:fname:vlist:users:hides` | `none` | [ungeprüft] Rule that hides mail header fields; fname, value patterns, users and hidden parts | `MHGWCONF=hide:From:*:*:from` |
| `winsize` | `winsize` | `none` | [ungeprüft] Accepted and ignored | `MHGWCONF=winsize` |

Source: `delegate/src/nntpgw.cpp`

## MIMECONV

Syntax: `MIMECONV=mimeConv[,mimeConv]`

Default: `none (empty if CHARCODE is given)`

MIME encoding and decoding in NNTP, POP and SMTP: thru, charcode, nospenc, textonly, alt

```
MIMECONV=charcode
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `all` | `all` | `none` | Enable all MIME encoding and decoding of header and body | `MIMECONV=all` |
| `alt` | `alt:{first\|unfold}` | `none` | Keep the first alternative (first) or all alternatives (unfold) of multipart/alternative | `MIMECONV=alt:first` |
| `charcode` | `charcode` | `none` | Enable only the character code conversion | `MIMECONV=charcode` |
| `dec` | `dec` | `none` | Enable MIME decoding of header and body | `MIMECONV=dec` |
| `enc` | `enc` | `none` | Enable MIME encoding of header and body | `MIMECONV=enc` |
| `headmask` | `headmask:{fieldList\|-ng2ml}` | `none` | [ungeprüft] Header fields kept in the message; -ng2ml selects the list for news to mail | `MIMECONV=headmask:-ng2ml` |
| `nomapemail` | `nomapemail:{addrList}` | `none` | E-mail addresses that are not mapped | `MIMECONV="nomapemail:{admin@example.com}"` |
| `nospenc` | `nospenc` | `off` | Disable the special encoding of the space in non-ASCII text of MIME headers | `MIMECONV=nospenc` |
| `qy` | `qy` | `off` | [ungeprüft] Add the QY marker | `MIMECONV=qy` |
| `rewaddr` | `rewaddr:maskList:format` | `none` | Rewrite E-mail addresses in the header and the body | `MIMECONV=rewaddr:_Email:%l@%r` |
| `textonly` | `textonly` | `off` | Keep only the first text/* part of a multipart/* message | `MIMECONV=textonly` |
| `thru` | `thru` | `none` | Disable all MIME encoding and decoding | `MIMECONV=thru` |
| `zero` | `zero:{none\|utf8\|kill}` | `none` | [ungeprüft] Treatment of zero-width characters | `MIMECONV=zero:utf8` |

Source: `delegate/mimekit/mime.cpp`

## MOUNT

Syntax: `MOUNT="vURL rURL [MountOptions]"`

Default: `/* SERVER_URL*`

Map the virtual URL vURL to and from the real URL rURL

```
MOUNT="/abc/* http://host/*"
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `-b` | `-b,conditionList` | `none` | Conditions applied only in response rewriting; -b.condition for a single one | `MOUNT="/* http://origin.example.com/* -b,from={.localnet}"` |
| `-f` | `-f,conditionList` | `none` | Conditions applied only in request rewriting; -f.condition for a single one | `MOUNT="/* http://origin.example.com/* -f,from={.localnet}"` |
| `again` | `again` | `off` | [ungeprüft] Apply the MOUNT again to the rewritten URL | `MOUNT="/* http://origin.example.com/* again"` |
| `asis` | `asis` | `off` | Do not rewrite the response | `MOUNT="/* http://origin.example.com/* asis"` |
| `asproxy` | `asproxy` | `any` | Condition: the request has a full URL, DeleGate is accessed as a proxy; !asproxy is the opposite | `MOUNT="/* http://origin.example.com/* asproxy"` |
| `auth` | `auth={HostList}` | `any` | Condition: password authentication succeeded with an AUTHORIZER host in HostList | `MOUNT="/* http://origin.example.com/* auth={authhost}"` |
| `authorizer` | `authorizer=authServList` | `AUTHORIZER` | AUTHORIZER applied to this MOUNT point, overriding the command line one | `MOUNT="/* http://origin.example.com/* authorizer=-list{user:pass}"` |
| `authru` | `authru` | `off` | Pass user@domain through to the server (FTP, POP, NNTP) | `MOUNT="/* http://origin.example.com/* authru"` |
| `avhost` | `avhost={HostList}` | `any` | Address based virtual hosting; same as vhost | `MOUNT="/* http://origin.example.com/* avhost={www.example.com}"` |
| `avserv` | `avserv[=host]` | `none` | IP address based server; all aliases and addresses of the server are MOUNTed | `MOUNT="/* http://origin.example.com/* avserv"` |
| `baseurl` | `BASEURL=URL` | `BASEURL` | Base URL of this MOUNT point, overriding BASEURL | `MOUNT="/* http://origin.example.com/* BASEURL=http://www.example.com/news"` |
| `cache` | `cache=no` | `cache on` | Disable the cache for the server of this MOUNT point; NNTP also knows no-article and no-list | `MOUNT="/* http://origin.example.com/* cache=no"` |
| `cgi` | `cgi` | `off` | [ungeprüft] Execute the target as CGI | `MOUNT="/* http://origin.example.com/* cgi"` |
| `charcode` | `charcode=charCode` | `CHARCODE` | Character code conversion of this MOUNT point, overriding CHARCODE | `MOUNT="/* http://origin.example.com/* charcode=euc-jp"` |
| `charset` | `charset=charCode` | `CHARCODE` | Same as charcode | `MOUNT="/* http://origin.example.com/* charset=euc-jp"` |
| `counter` | `COUNTER=listOfCounterControl` | `COUNTER` | Counter control of this MOUNT point, overriding COUNTER | `MOUNT="/* http://origin.example.com/* COUNTER=do"` |
| `default` | `default` | `off` | [ungeprüft] Default MOUNT used when no other matches | `MOUNT="/* http://origin.example.com/* default"` |
| `delay` | `delay=seconds` | `none` | [ungeprüft] Delay before the response | `MOUNT="/* http://origin.example.com/* delay=1"` |
| `direction` | `direction={fo\|bo\|bif}` | `both` | Apply the MOUNT to forward only (fo), backward only (bo), or backward if forward was applied (bif) | `MOUNT="/* http://origin.example.com/* direction=fo"` |
| `dst` | `dst={HostList}` | `any` | Condition: the destination host is included in HostList | `MOUNT="/* http://origin.example.com/* dst={origin.example.com}"` |
| `dstproto` | `dstproto={ProtoList}` | `any` | Condition: the protocol of the destination server is in ProtoList | `MOUNT="/* http://origin.example.com/* dstproto={http}"` |
| `expire` | `expire=period` | `EXPIRE` | Validity of the cache of this MOUNT point, overriding EXPIRE | `MOUNT="/* http://origin.example.com/* expire=1d"` |
| `expires` | `expires=period` | `none` | Add an Expires field to each HTTP response; + or - prefix is relative to the original | `MOUNT="/* http://origin.example.com/* expires=1d"` |
| `ffromsv` | `ffromsv=filterCommand` | `FFROMSV` | Filter for data from the server, applied to this MOUNT point | `MOUNT="/* http://origin.example.com/* ffromsv=filter.cfi"` |
| `fileis` | `fileis=type` | `none` | [ungeprüft] Condition on the type of the local file | `MOUNT="/* http://origin.example.com/* fileis=dir"` |
| `forbidden` | `forbidden` | `off` | Reject the request as forbidden, same as rcode=403 | `MOUNT="/* http://origin.example.com/* forbidden"` |
| `from` | `from={HostList}` | `any` | Condition: the client is included in HostList | `MOUNT="/* http://origin.example.com/* from={.localnet}"` |
| `fsv` | `fsv=filterCommand` | `FSV` | Filter between server and DeleGate, applied to this MOUNT point | `MOUNT="/* http://origin.example.com/* fsv=sslway"` |
| `ftocl` | `ftocl=filterCommand` | `FTOCL` | External filter for this MOUNT point, overriding FTOCL | `MOUNT="/* http://origin.example.com/* ftocl=filter.cfi"` |
| `ftosv` | `ftosv=filterCommand` | `FTOSV` | Filter for data to the server, applied to this MOUNT point | `MOUNT="/* http://origin.example.com/* ftosv=filter.cfi"` |
| `ftpconf` | `FTPCONF=ftpControl` | `FTPCONF` | FTPCONF applied only to this MOUNT point | `MOUNT="/* http://origin.example.com/* FTPCONF=nopasv"` |
| `ftpxhttp` | `ftpxhttp` | `off` | [ungeprüft] FTP: serve FTP over an HTTP connection | `MOUNT="/* http://origin.example.com/* ftpxhttp"` |
| `genvhost` | `genvhost[=host]` | `none` | Generate the Host field of the forwarded request | `MOUNT="/* http://origin.example.com/* genvhost=www.example.com"` |
| `hide` | `hide={GroupList}` | `none` | NNTP: patterns of news group names hidden from clients | `MOUNT="/* http://origin.example.com/* hide={alt.*,!alt.comp*}"` |
| `host` | `host={HostList}` | `any` | Condition: the client connected via a network interface included in HostList | `MOUNT="/* http://origin.example.com/* host=*:8080"` |
| `htmlconv` | `htmlconv=convList` | `HTMLCONV` | [ungeprüft] HTML conversion of this MOUNT point | `MOUNT="/* http://origin.example.com/* htmlconv=deent"` |
| `httpconf` | `HTTPCONF=what:conf` | `HTTPCONF` | HTTPCONF applied only to this MOUNT point | `MOUNT="/* http://origin.example.com/* HTTPCONF=max-cka:10"` |
| `ident` | `ident` | `any` | Condition: the user name of the client got from the Ident server | `MOUNT="/* http://origin.example.com/* ident"` |
| `logindir` | `logindir` | `off` | [ungeprüft] FTP: start in the login directory | `MOUNT="/* http://origin.example.com/* logindir"` |
| `master` | `master=host:port` | `MASTER` | Upstream MASTER DeleGate for this MOUNT point, overriding MASTER | `MOUNT="/* http://origin.example.com/* master=masterhost:8080"` |
| `maxima` | `MAXIMA=bps:speed` | `MAXIMA bps` | Maximum transmission speed of this MOUNT point | `MOUNT="/* http://origin.example.com/* MAXIMA=bps:128k"` |
| `method` | `method={methodList}` | `any` | Condition: the request method is included in methodList | `MOUNT="/* http://origin.example.com/* method={GET,HEAD}"` |
| `moved` | `moved[={300\|301\|302\|303}]` | `302` | Do not relay but answer with a redirect to the real URL | `MOUNT="/* http://origin.example.com/* moved=301"` |
| `mybase` | `mybase=URL` | `none` | [ungeprüft] Base of the URL that refers to DeleGate itself | `MOUNT="/* http://origin.example.com/* mybase=http://www.example.com/"` |
| `noanon` | `noanon` | `off` | [ungeprüft] FTP: refuse anonymous logins | `MOUNT="/* http://origin.example.com/* noanon"` |
| `nocase` | `nocase` | `off` | Ignore the case of characters in URL path matching | `MOUNT="/* http://origin.example.com/* nocase"` |
| `noseek` | `noseek` | `off` | [ungeprüft] FTP gateway: do not seek in files | `MOUNT="/* http://origin.example.com/* noseek"` |
| `nvhost` | `nvhost={HostList}` | `any` | Name based virtual hosting; -thru passes the client virtual name to the server | `MOUNT="/* http://origin.example.com/* nvhost=www.example.com"` |
| `nvserv` | `nvserv[=host]` | `none` | Name based virtual server; the host name sent to the server defaults to the host of rURL | `MOUNT="/* http://origin.example.com/* nvserv=www.example.com"` |
| `odst` | `odst={HostList}` | `any` | Condition: the original destination of the TCP connection (NAT) is included in HostList | `MOUNT="/* http://origin.example.com/* odst={192.0.2.10}"` |
| `onerror` | `onerror[={listOfCodes}]` | `none` | Use this MOUNT to substitute the response when an error 4xx or 5xx occurred | `MOUNT="/* http://origin.example.com/* onerror={401,407}"` |
| `owner` | `owner` | `off` | MOUNT set dynamically from a remote DeleGate | `MOUNT="/* http://origin.example.com/* owner"` |
| `path` | `path={HostList}` | `any` | Condition: all hosts passed through are included in HostList | `MOUNT="/* http://origin.example.com/* path={.localnet}"` |
| `pathext` | `pathext=ext` | `none` | [ungeprüft] Extension inserted into the path of local files | `MOUNT="/* http://origin.example.com/* pathext=-ja"` |
| `pathhost` | `pathhost=PathHost` | `none` | [ungeprüft] NNTP: logical PathHost of the server of this MOUNT point | `MOUNT="/* http://origin.example.com/* pathhost=example.com"` |
| `pri` | `pri=number` | `0` | Priority of the MOUNT; larger values are tested first | `MOUNT="/* http://origin.example.com/* pri=1"` |
| `proxy` | `proxy=host:port` | `PROXY` | Upstream proxy for this MOUNT point, overriding PROXY | `MOUNT="/* http://origin.example.com/* proxy=proxyhost:8080"` |
| `public` | `public` | `off` | Do not apply access restrictions such as PERMIT to this MOUNT point | `MOUNT="/* http://origin.example.com/* public"` |
| `px-thruresp` | `px-thruresp` | `off` | [ungeprüft] HTTP: pass the response of the proxy through | `MOUNT="/* http://origin.example.com/* px-thruresp"` |
| `qhost` | `qhost={HostList}` | `any` | [ungeprüft] Condition on the host of the request | `MOUNT="/* http://origin.example.com/* qhost={www.example.com}"` |
| `qmatch` | `qmatch=pattern` | `any` | Condition: the pattern matches a string in the request header | `MOUNT="/* http://origin.example.com/* qmatch=User-Agent:*compatible*"` |
| `rcode` | `rcode={300\|...\|306\|403\|404}` | `none` | Answer with the given status code | `MOUNT="/* http://origin.example.com/* rcode=403"` |
| `realm` | `realm=realmString` | `none` | HTTP: realm of the authentication | `MOUNT="/* http://origin.example.com/* realm=intranet"` |
| `recursive` | `recursive` | `off` | [ungeprüft] HTTP: the target is another MOUNT of this DeleGate | `MOUNT="/* http://origin.example.com/* recursive"` |
| `referer` | `referer` | `off` | Apply the rewriting only to the Referer field to be forwarded; synonym of where=ref | `MOUNT="/* http://origin.example.com/* referer"` |
| `resolv` | `resolv` | `off` | [ungeprüft] Resolve the host name of the MOUNT target | `MOUNT="/* http://origin.example.com/* resolv"` |
| `rewaddr` | `rewaddr={headerList}:addrFormat` | `none` | NNTP: rewrite E-mail addresses in the listed header fields or the body | `MOUNT="/* http://origin.example.com/* rewaddr={From,Body}:%l@%r"` |
| `rhead` | `rhead=header` | `none` | Response header in MIME format | `MOUNT="/* http://origin.example.com/* rhead=X-Test:1"` |
| `rhost` | `rhost={HostList}` | `any` | [ungeprüft] Condition on the host of the response | `MOUNT="/* http://origin.example.com/* rhost={origin.example.com}"` |
| `rident` | `rident[=no]` | `per RIDENT` | Forward (or stop forwarding) RIDENT information to the MOUNTed server | `MOUNT="/* http://origin.example.com/* rident"` |
| `ro` | `ro` | `off` | Read only; inhibits POST in NNTP and is the default of origin FTP | `MOUNT="/* http://origin.example.com/* ro"` |
| `robots` | `robots={no\|ok}` | `no for NNTP and FTP, ok otherwise` | Disallow or allow retrievals from robots | `MOUNT="/* http://origin.example.com/* robots=no"` |
| `rserv` | `rserv=host[:port]` | `none` | Real host name or address and port of the target server of a virtual server | `MOUNT="/* http://origin.example.com/* rserv=192.0.2.123"` |
| `rw` | `rw` | `off` | Read and write; lets an origin FTP DeleGate write to local files | `MOUNT="/* http://origin.example.com/* rw"` |
| `search` | `search:script` | `none` | HTTP: local search script for URLs with ?query; search:- ignores the global HTTPCONF search | `MOUNT="/* http://origin.example.com/* search:/usr/lib/cgi-bin/search.cgi"` |
| `servon` | `servon={init\|user\|pass}` | `after the first path command` | FTP: timing of the connection to the MOUNTed server | `MOUNT="/* http://origin.example.com/* servon=init"` |
| `sign` | `sign[=key]` | `off` | Sign Content-MD5 with a password or RSA | `MOUNT="/* http://origin.example.com/* sign"` |
| `sni` | `sni={HostList}` | `any` | Condition: the TLS server name indicated by the client is included in HostList | `MOUNT="/* http://origin.example.com/* sni={www.example.com}"` |
| `src` | `src={HostList}` | `any` | Condition: same as via | `MOUNT="/* http://origin.example.com/* src={proxy1}"` |
| `srcproto` | `srcproto={ProtoList}` | `any` | Condition: the protocol of the client | `MOUNT="/* http://origin.example.com/* srcproto={http}"` |
| `stls` | `stls=stlsSpecs` | `STLS` | STARTTLS settings of this MOUNT point | `MOUNT="/* http://origin.example.com/* stls=fsv"` |
| `thru` | `thru` | `off` | [ungeprüft] Relay the response without interpretation | `MOUNT="/* http://origin.example.com/* thru"` |
| `timeout` | `timeout=period` | `none` | [ungeprüft] FTP: timeout for the MOUNTed server | `MOUNT="/* http://origin.example.com/* timeout=60"` |
| `udst` | `udst={HostList}` | `any` | Condition: the host in a full URL is included in HostList; used with referer | `MOUNT="/* http://origin.example.com/* udst={origin.example.com}"` |
| `unknown` | `unknown` | `off` | Reject the request as unknown, same as rcode=404 | `MOUNT="/* http://origin.example.com/* unknown"` |
| `upact` | `upact=Invoke/Reload/Posted` | `NNTPCONF upact` | NNTP: update times of the LIST cache for this MOUNT point only | `MOUNT="/* http://origin.example.com/* upact=600/300/60"` |
| `uriconv` | `uriconv=convSpec` | `URICONV` | [ungeprüft] URI conversion of this MOUNT point | `MOUNT="/* http://origin.example.com/* uriconv=full:+"` |
| `useproxy` | `useproxy[=proxyURI]` | `none` | Answer 305 Use Proxy; direct or no URI gives Set-Proxy: DIRECT | `MOUNT="/* http://origin.example.com/* useproxy=direct"` |
| `verify` | `verify[=key]` | `off` | Verify Content-MD5 with a password or RSA | `MOUNT="/* http://origin.example.com/* verify"` |
| `vhost` | `vhost={HostList}` | `any` | Condition: the Host field of the request is included in HostList; enables virtual host rewriting | `MOUNT="/* http://origin.example.com/* vhost={www.example.com}"` |
| `via` | `via={HostList}` | `any` | Condition: at least one host passed through on the way is included in HostList | `MOUNT="/* http://origin.example.com/* via={proxy1}"` |
| `where` | `where=ref` | `none` | [ungeprüft] Place where the rewriting is applied | `MOUNT="/* http://origin.example.com/* where=ref"` |
| `withquery` | `withquery` | `any` | Condition: the requested URL has a ?query part | `MOUNT="/* http://origin.example.com/* withquery"` |
| `withssl` | `withssl[={cl\|sv\|nocl\|nosv}]` | `any` | Condition: the client side connection is encrypted with SSL or TLS | `MOUNT="/* http://origin.example.com/* withssl"` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `auth` | `auth:srcHostList` | `none` | Force AUTHINFO at the start of a session for clients in srcHostList | `NNTPCONF=auth:.localnet` |
| `authcom` | `authcom:commandList` | `none` | NNTP commands that need authentication | `NNTPCONF=authcom:POST` |
| `dispensable` | `dispensable` | `off` | Continue the client session even if a server is disconnected | `NNTPCONF=dispensable` |
| `expire.list` | `expire.list:period` | `10m` | [ungeprüft] Expiration of cached lists and authentication data in the NNTP gateway | `NNTPCONF=expire.list:10m` |
| `log` | `log:Q` | `off` | Log the NNTP requests when the value contains Q | `NNTPCONF=log:Q` |
| `nice` | `nice:N` | `none` | Set the nice value | `NNTPCONF=nice:5` |
| `nntpcc` | `nntpcc:N` | `1` | Number of NNTP connection caches; 0 disables the connection cache | `NNTPCONF=nntpcc:0` |
| `nomapemail` | `nomapemail:addrList` | `none` | E-mail addresses that are not mapped | `NNTPCONF=nomapemail:admin@example.com` |
| `ondemand` | `ondemand` | `off` | Postpone the connection to a server until data from it is needed | `NNTPCONF=ondemand` |
| `overview.fmt` | `overview.fmt:{FieldList}` | `{Subject,From,Date,Message-ID,References,Bytes,Lines}` | Fields of the XOVER response generated by DeleGate | `NNTPCONF="overview.fmt:{Subject,From,Date}"` |
| `pathhost` | `pathhost:Server/PathHost` | `none` | Define a logical PathHost name for the physical Server host | `NNTPCONF=pathhost:wall.example.com/example.com` |
| `penalty` | `penalty:seconds` | `0` | [ungeprüft] Seconds of delay applied as penalty | `NNTPCONF=penalty:3` |
| `popcc` | `popcc:N` | `1` | [ungeprüft] Number of POP connection caches | `NNTPCONF=popcc:1` |
| `posterbase` | `posterbase:base` | `mbox@host.domain` | [ungeprüft] Base address for the mapping of poster E-mail addresses | `NNTPCONF=posterbase:poster` |
| `resplog` | `resplog:file` | `none` | [ungeprüft] File where responses are logged | `NNTPCONF=resplog:resp.log` |
| `server` | `server:host[:port][/groupList]` | `none` | NNTP servers for HTTP requests with nntp://*/... or news: URLs | `NNTPCONF=server:news.example.com` |
| `upact` | `upact:Invoke/Reload/Posted` | `600/300/60` | Expire times in seconds of the active list cache; Posted applies after a posting | `NNTPCONF=upact:600/300/120` |
| `upconf` | `upconf:N` | `1800` | [ungeprüft] Update interval of the configuration | `NNTPCONF=upconf:60` |
| `xerrors` | `xerrors:N` | `0` | [ungeprüft] Number of errors after which the session exits | `NNTPCONF=xerrors:10` |
| `xover` | `xover:N` | `2000` | Maximum number of articles in an XOVER range | `NNTPCONF=xover:1000` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `baseurl` | `baseurl:URL` | `none` | [ungeprüft] Base URL of the PAM authentication server | `PAMCONF=baseurl:http://pamhost` |
| `port` | `port:N` | `0` | [ungeprüft] Port of the PAM authentication server | `PAMCONF=port:8000` |
| `url` | `url:URL` | `none` | [ungeprüft] URL of the PAM authentication server | `PAMCONF=url:http://pamhost/auth` |

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

PGP processing of mail messages; sign, mime, encr, decr, vrfy

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

POP settings; listmax sets the maximum number of listed messages

```
POPCONF=listmax:100
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `listmax` | `listmax:N` | `30` | Maximum number of listed messages | `POPCONF=listmax:100` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `delegate` | `delegate` | `on for .localnet` | Work as a DeleGate proxy that accepts /-_-URL and rewrites URLs in responses | `RELAY=delegate` |
| `noapplet` | `noapplet` | `off` | Disable only APPLET tags in relayed responses | `RELAY=delegate,noapplet` |
| `nojava` | `nojava` | `on for delegate and vhost` | Disable APPLET, EMBED and OBJECT tags in relayed responses | `RELAY=delegate,nojava` |
| `novhost` | `novhost` | `off` | Disable relaying by the Host field | `RELAY=novhost` |
| `origdst` | `origdst` | `off` | [ungeprüft] Relay to the original destination of the connection | `RELAY=origdst` |
| `proxy` | `proxy` | `on for all clients` | Work as a standard CERN compatible HTTP proxy that accepts full URLs | `RELAY=proxy` |
| `tproxy` | `tproxy` | `off` | Same as vhost | `RELAY=tproxy` |
| `vhost` | `vhost` | `on for http:*:80 from .localnet` | Relay to the server given in the Host field (transparent proxy) | `RELAY=vhost` |
| `y11` | `y11` | `off` | [ungeprüft] Allow relaying for the Y11 protocol | `RELAY=y11` |
| `yy` | `yy` | `off` | [ungeprüft] Allow relaying for the YYMUX protocol | `RELAY=yy` |

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

Expiration time in seconds of the host cache of the resolver

```
RES_EXPIRE=300
```

Source: `delegate/src/inets.cpp`

## RES_LOG

Syntax: `RES_LOG=path`

Default: `none`

File to which the resolver appends its log

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

Define a service name with a port, or as an alias of an existing service

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `allow` | `allow:nohelo` | `off` | Accept clients that do not send HELO | `SMTPCONF=allow:nohelo` |
| `auth` | `auth[:{plain\|login}]` | `off` | [ungeprüft] Enable AUTH handling for the methods PLAIN and LOGIN | `SMTPCONF=auth:plain` |
| `bcc` | `bcc:emailAddr[:srcHostList]` | `none` | Append emailAddr to the list of recipients | `SMTPCONF=bcc:archive@example.com` |
| `bgdatasize` | `bgdatasize:N[K]` | `64K` | Relay data larger than N bytes in the background without waiting for the response to QUIT | `SMTPCONF=bgdatasize:64K` |
| `callback` | `callback[:[T][:srcHostList]]` | `off` | Call back the SMTP server of the client on HELO; delay up to T seconds if there is none | `SMTPCONF=callback` |
| `helodomain` | `helodomain:domainList` | `none` | Reject clients whose HELO domain does not match the list | `SMTPCONF=helodomain:example.com` |
| `maxrcpt` | `maxrcpt:N` | `0 (unlimited)` | Maximum number of recipients accepted by RCPT commands | `SMTPCONF=maxrcpt:100` |
| `mboxcase` | `mboxcase` | `off` | Keep the case of recipient mailbox names; they are lower-cased by default | `SMTPCONF=mboxcase` |
| `mladmin` | `mladmin:addr` | `none` | Administrator address written into the messages of the mailing list gateway | `SMTPCONF=mladmin:admin@example.com` |
| `mlhost` | `mlhost:host` | `none` | Host name of the mailing list addresses generated by the news to mail gateway | `SMTPCONF=mlhost:ml.example.com` |
| `mlsolt` | `mlsolt:string` | `none` | Salt for the encrypted stamps of the mailing list gateway | `SMTPCONF=mlsolt:salt` |
| `mx` | `MX:server[:domain]` | `{-MX.*,*}` | SMTP server to forward mails to; -MX.* is the MX of the recipient domain | `SMTPCONF="MX:smtpserver"` |
| `myname` | `myname:name` | `none` | Name of this host shown to clients and servers in the greeting and HELO | `SMTPCONF=myname:mail.example.com` |
| `reject` | `reject:cond[+cond]*` | `nohelo` | Reject DATA or the session on nohelo, nofrom, pipeline, nomx, notselfmx or notmxhelo | `SMTPCONF=reject:nomx+nohelo+nofrom` |
| `srcroute` | `srcroute` | `off` | Tolerate source routes in recipient addresses by removing them | `SMTPCONF=srcroute` |
| `thrudata` | `thrudata:period` | `30` | Maximum time to wait for DATA from the client while buffering | `SMTPCONF=thrudata:30` |
| `tout-req` | `tout-req:period` | `60` | Timeout for requests from the client | `SMTPCONF=tout-req:60` |
| `tout-resp` | `tout-resp:period` | `300` | Timeout for a response from the server | `SMTPCONF=tout-resp:300` |

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

SMTP server through which the DeleGate sends its own mail (port 25 by default)

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `buffsize` | `buffsize:size[kiosc][:connMap]` | `none` | Size of the socket buffers; k kilo, i input, o output, s server, c client | `SOCKOPT=buffsize:64kis` |
| `connctrl` | `[no]connctrl` | `connctrl` | Connect control (retry and timeout); noconnctrl disables it | `SOCKOPT=noconnctrl` |
| `keepalive` | `keepalive:value[:connMap]` | `none` | [ungeprüft] SO_KEEPALIVE of sockets | `SOCKOPT=keepalive:on` |
| `linger` | `linger:value[:connMap]` | `none` | [ungeprüft] SO_LINGER of sockets | `SOCKOPT=linger:3` |
| `reuse` | `[no]reuse` | `reuse` | Instant reuse of a port number (SO_REUSEADDR) | `SOCKOPT=noreuse` |
| `share` | `[no]share` | `noshare` | Simultaneous use of a port (SO_REUSEPORT) | `SOCKOPT=share` |
| `shut` | `[no]shut` | `shut` | Call shutdown on a socket before closing it | `SOCKOPT=noshut` |
| `shutdown` | `shutdown:g[:connMap]` | `none` | Graceful shutdown for HTTP responses, effective on Win32 | `SOCKOPT=shutdown:g` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `acc` | `acc:tcp:rhost:rport:lhost:lport` | `none` | [ungeprüft] Accept a remote port for forwarding to a local server | `SOXCONF=acc:tcp:hostA:9023:localhost:23` |
| `allow` | `allow:acc` | `off` | [ungeprüft] Allow remote requests to accept connections | `SOXCONF=allow:acc` |
| `cork` | `cork:on` | `off` | [ungeprüft] Release TCP_CORK of the SockMux connection after output | `SOXCONF=cork:on` |
| `crypt` | `crypt:no` | `on` | no or off disables the encryption of SockMux packets | `SOXCONF=crypt:no` |
| `dhkey` | `dhkey:N` | `2` | Diffie-Hellman key group; a non-numeric value turns it off | `SOXCONF=dhkey:2` |
| `noconndata` | `noconndata` | `off` | [ungeprüft] Do not send data with the connect request | `SOXCONF=noconndata` |
| `nodelay` | `nodelay:on` | `off` | Set TCP_NODELAY on the SockMux connection when on | `SOXCONF=nodelay:on` |
| `nopush` | `nopush:on` | `off` | [ungeprüft] Flush the SockMux connection with TCP_NOPUSH off after output | `SOXCONF=nopush:on` |
| `packsize` | `packsize:size` | `16k` | Size of a SockMux packet, at least 128 and at most 16k | `SOXCONF=packsize:16k` |
| `private` | `private` | `off` | [ungeprüft] Make the SockMux private to the parent DeleGate | `SOXCONF=private` |

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

File to which status lines with a time stamp are written

```
STATFILE=/var/spool/delegate/status
```

Source: `delegate/src/delegated.cpp`

## STDOUTLOG

Syntax: `STDOUTLOG=LogFilename`

Default: `${LOGDIR}/stdout.log`

Log file that receives the standard output of the server

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `fcl` | `[-]fcl[/im][/ssl]` | `off` | Use SSL with the client; the session ends if SSL is unavailable, - makes it optional | `STLS=fcl` |
| `fsv` | `[-]fsv[/im][/ssl]` | `off` | Use SSL with the server; the session ends if SSL is unavailable, - makes it optional | `STLS=fsv` |
| `im` | `[-]imSec` | `im0.25` | Wait time for an implicit SSL handshake from the client; -im disables it | `STLS=fcl,im0.5` |
| `mitm` | `[-]mitm` | `off` | Behave like -fcl,-fsv; with - only for the server name prefix -mitm. | `STLS=mitm` |
| `opt` | `opt` | `off` | Make the following specifications optional, like the - prefix | `STLS=opt,fcl` |
| `ssl` | `/ssl` | `off` | Use AUTH SSL instead of AUTH TLS (for FTP) | `STLS=fsv/ssl` |

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `-fname` | `-fname` | `daemon` | Use the facility name instead of daemon | `SYSLOG=-flocal1` |
| `-sname` | `-sname` | `none` | Severity (priority) used for debug messages, name or number | `SYSLOG=-serr` |
| `-vC` | `-vC` | `off` | [ungeprüft] Sets a flag that no code reads | `SYSLOG=-vC` |
| `-vD` | `-vD` | `off` | Without the host name | `SYSLOG=-vD` |
| `-vH` | `-vH` | `off` | Without the syslog header | `SYSLOG=-vH,file:/var/log/delegate/syslog.log` |
| `-vM` | `-vM` | `off` | [ungeprüft] Sets a flag that no code reads | `SYSLOG=-vM` |
| `-vN` | `-vN` | `off` | Without the program name | `SYSLOG=-vN` |
| `-vP` | `-vP` | `off` | Without the process ID | `SYSLOG=-vP` |
| `-vQ` | `-vQ` | `off` | Without the priority | `SYSLOG=-vQ` |
| `-vS` | `-vS` | `off` | Without PROTOLOG | `SYSLOG=-vS,file:/var/log/delegate/syslog.log` |
| `-vT` | `-vT` | `off` | Without the time stamp | `SYSLOG=-vT` |
| `-vc` | `-vc` | `off` | [ungeprüft] Sets a flag that no code reads | `SYSLOG=-vc` |
| `-vs` | `-vs` | `off` | Without LOGFILE | `SYSLOG=-vs,file:/var/log/delegate/syslog.log` |
| `-vt` | `-vt` | `off` | Terse LOGFILE | `SYSLOG=-vt,file:/var/log/delegate/syslog.log` |

Source: `delegate/src/syslog.cpp`

## TELNETCONF

Syntax: `TELNETCONF=keepalive:seconds`

Default: `none`

Telnet settings; keepalive sets the keep-alive interval, 30 if 0

```
TELNETCONF=keepalive:30
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `keepalive` | `keepalive:seconds` | `none` | Keep-alive interval; 0 selects 30 seconds | `TELNETCONF=keepalive:30` |

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
| `bind` | `bind:T` | `0` | Binding of ports | `TIMEOUT=bind:10` |
| `bindenter` | `bindenter:T` | `5` | Binding of entrance ports on restart | `TIMEOUT=bindenter:10` |
| `cc` | `cc:T` | `180` | Keep a connection cache alive | `TIMEOUT=cc:300` |
| `cfistat` | `cfistat:T` | `1` | Status information from a filter started with -s | `TIMEOUT=cfistat:2` |
| `con` | `con:T` | `10` | Connection to the server | `TIMEOUT=con:20` |
| `daemon` | `daemon:T` | `0 (unlimited)` | Lifetime of the delegated process | `TIMEOUT=daemon:86400` |
| `defreeze` | `defreeze:T` | `60` | [ungeprüft] Idle time after which a frozen server is revived | `TIMEOUT=defreeze:120` |
| `dgnonce` | `dgnonce:T` | `60` | Lifetime of the nonce of AUTHORIZER=-dgauth | `TIMEOUT=dgnonce:120` |
| `dns` | `dns:T` | `10` | DNS lookup | `TIMEOUT=dns:5` |
| `dnsinv` | `dnsinv:T` | `6` | DNS inverse lookup | `TIMEOUT=dnsinv:3` |
| `erestart` | `erestart:T` | `0` | Restart after an error, used with MAXIMA erestart | `TIMEOUT=erestart:10` |
| `ftpcc` | `ftpcc:T` | `120` | Keep an FTP connection cache alive | `TIMEOUT=ftpcc:300` |
| `greeting` | `greeting:T` | `0` | Wait for the greeting message of a server | `TIMEOUT=greeting:10` |
| `hello` | `hello:T` | `30` | HELLO negotiation with the MASTER | `TIMEOUT=hello:60` |
| `htmuxskew` | `htmuxskew:T` | `300` | [ungeprüft] Maximum time difference tolerated by HTMUX | `TIMEOUT=htmuxskew:600` |
| `http-cka` | `http-cka:T` | `10` | Keep-alive connection of HTTP; replaced by HTTPCONF tout-cka | `TIMEOUT=http-cka:10` |
| `http-ckamg` | `http-ckamg:T` | `2` | Margin added to the HTTP keep-alive timeout; replaced by HTTPCONF tout-ckamg | `TIMEOUT=http-ckamg:3` |
| `http-poll-qbody` | `http-poll-qbody:T` | `15` | Wait for further data of an HTTP request body; replaced by HTTPCONF tout-in-reqbody | `TIMEOUT=http-poll-qbody:30` |
| `http-wait-qbody` | `http-wait-qbody:T` | `30` | Wait for the first data of an HTTP request body; replaced by HTTPCONF tout-wait-reqbody | `TIMEOUT=http-wait-qbody:60` |
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
| `vsapacc` | `vsapacc:T` | `0` | Accept through a VSAP server | `TIMEOUT=vsapacc:60` |
| `waitchild` | `waitchild:T` | `3` | Wait for child processes to terminate | `TIMEOUT=waitchild:5` |

Source: `delegate/src/env.cpp`

## TLS

Syntax: `TLS=stlsSpecs[,sslwayCom][:connMap]`

Default: `none`

Same as STLS

```
TLS=fcl
```

Source: `delegate/src/stls.cpp`

## TLSCONF

Syntax: `TLSCONF=tlsConf[,tlsConf]*`

Default: `scache:do,xcache:do`

TLS settings such as session caches, shutdown alert and log detail

```
TLSCONF="scache:no,shutdown"
```

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `cache` | `cache:[do\|no]` | `scache:do,xcache:do` | Enables or disables all caches | `TLSCONF=cache:no` |
| `context` | `context:string` | `SSLway` | Session id context of the server | `TLSCONF=context:dg1` |
| `debug` | `debug` | `off` | Reports the use of the session and certificate caches on stderr | `TLSCONF=debug` |
| `libs` | `libs:libname[+libname]` | `ignored` | Obsolete; OpenSSL is linked directly and the setting is ignored | `TLSCONF=libs:crypto+ssl` |
| `scache` | `scache:[do\|no\|acc\|con]` | `do` | Enables or disables the session caches for accepted (acc) and outgoing (con) connections | `TLSCONF=scache:no` |
| `shutdown` | `shutdown[:none\|flush\|wait[.ms]\|acc\|con]` | `flush` | Shutdown alert (close notify): flush answers the alert of the peer, wait also sends it | `TLSCONF=shutdown:wait.300` |
| `sni` | `sni:[only\|warn]` | `none` | Refuses (only) or warns (warn) when no certificate exists for the requested server name | `TLSCONF=sni:only` |
| `xcache` | `xcache:[do\|no]` | `do` | Enables or disables the cache of the certificate context | `TLSCONF=xcache:no` |

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

Editor for the argument encode and decode function; EDITOR is tried next, then vi

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

| Option | Syntax | Default | Description | Example |
|---|---|---|---|---|
| `CHROOT` | `CHROOT:dir` | `none` | [ungeprüft] Accepted and ignored | `YYCONF=CHROOT:/` |
| `HISTFILE` | `HISTFILE:file` | `none` | HISTFILE of the yyMux user session | `YYCONF=HISTFILE:/tmp/yy.hist` |
| `HOME` | `HOME:dir` | `none` | HOME of the yyMux user session | `YYCONF=HOME:/home/user` |
| `LD_LIBRARY_PATH` | `LD_LIBRARY_PATH:dirList` | `none` | LD_LIBRARY_PATH of the yyMux user session | `YYCONF=LD_LIBRARY_PATH:/usr/lib` |
| `OWNER` | `OWNER:user` | `none` | [ungeprüft] Accepted and ignored | `YYCONF=OWNER:nobody` |
| `PATH` | `PATH:dirList` | `none` | PATH of the yyMux user session | `YYCONF=PATH:/usr/bin:/bin` |
| `PROMPT` | `PROMPT:string` | `none` | Prompt (PS1) of the yyMux user session | `YYCONF=PROMPT:yy$` |
| `SHELL` | `SHELL:path` | `none` | SHELL of the yyMux user session | `YYCONF=SHELL:/bin/sh` |
| `STLS` | `STLS` | `off` | [ungeprüft] Use TLS for the yyMux connection | `YYCONF=STLS` |
| `YYUID` | `YYUID:uid` | `none` | [ungeprüft] User ID of the yyMux user session | `YYCONF=YYUID:1000` |
| `accept` | `accept` | `off` | [ungeprüft] Open a server socket that accepts yyMux connections | `YYCONF=accept` |
| `forkpty` | `forkpty:command` | `none` | [ungeprüft] Command used to start a pseudo terminal session | `YYCONF=forkpty:dgforkpty` |
| `persistent` | `persistent[:period]` | `off` | [ungeprüft] Keep the session persistent; the period in minutes is the resume hold time | `YYCONF=persistent:10` |
| `sttyraw` | `sttyraw:command` | `none` | [ungeprüft] Command that sets the terminal to raw mode | `YYCONF=sttyraw:stty raw` |

Source: `delegate/src/X.cpp`

## YYMUX

Syntax: `YYMUX=host[:port][:connMap]`

Default: `none`

YYMUX server used as upstream proxy to tunnel and multiplex connections

```
YYMUX=hostX:6010
```

Source: `delegate/src/X.cpp`
