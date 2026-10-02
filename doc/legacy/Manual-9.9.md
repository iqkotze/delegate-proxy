DeleGate reference manual version 9.9

-----

**The Reference Manual of DeleGate version 9.9**
[(+10.X)](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Version10)

*Copyright (c) 1994-2000 Yutaka Sato
<ysato AT etl.go.jp>
<y DOT sato AT delegate.org>*

*Copyright (c) 1994-2000 Electrotechnical Laboratory (ETL), AIST, MITI*

*Copyright (c) 2001-2014 National Institute of Advanced Industrial Science and Technology (AIST)*

*AIST-Product-ID: 2000-ETL-198715-01, H14PRO-049, H15PRO-165, H18PRO-443*

*Permission to use this material for evaluation, copy this material for
your own use, and distribute the copies via publicly accessible on-line
media, without fee, is hereby granted provided that the above copyright
notice and this permission notice appear in all copies.
**AIST makes no representations about the accuracy or suitability of this
material for any purpose. it is provided “as is”, without any express
or implied warranties.***

-----

This document is written based on the latest version of DeleGate version 9.X,
and partially on [version 10.X](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Version10).
Comments about this document are expected to be directed to
<mailto:feedback@delegate.org>
to be open and shared at
<http://www.delegate.org/feedback/>.
Watch **DeleGate Home Page** at
<http://www.delegate.org/>
to see the latest status.
Beginners are recommended to read a short tutorial at
<http://www.delegate.org/delegate/tutorial/>
also.
A collection of usage examples at
<http://www.delegate.org/delegate/HowToDG.shtml> might be helpful to see what you can do with DeleGate.
A list of related documents is at
<http://www.delegate.org/documents/>.

-----

[[help](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?_help)
[search](http://www.delegate.org/fsx/search?index=man&sort=url)
[decomp](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.whole)
[parts](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.parts)
[skeleton](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.skeleton)
[frame](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/$%7BSELF%7D?_frames)
]
… these links are active only when accessed via origin HTTP-DeleGate

PERMUTED INDEX

[-F](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_Func)
[-P](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P)
[-Q](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P)
[-f](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_f)
[-r](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_r)
[-v](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_v)
[-d](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_d)
[-D](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_D)
[ADMIN](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ADMIN)
[AF_LOCAL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AF_LOCAL)
[Aging](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#aging)
[AUTH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTH)
[AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER)
[BASEURL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#BASEURL)
[CACHE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHE)
[CACHEFILE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHEFILE)
[CAPSKEY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CAPSKEY)
[CERTDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CERTDIR)
[CGIENV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CGIENV)
[CHARCODE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARCODE)
[CHARMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARMAP)
[CHOKE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHOKE)
[CHROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHROOT)
[CLUSTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CLUSTER)
[CMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CMAP)
[CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT)
[COUNTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTER)
[COUNTERDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTERDIR)
[CRON](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CRON)
[DATAPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DATAPATH)
[DELAY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DELAY)
[DELEGATE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DELEGATE)
[DGCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGCONF)
[DGOPTS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGOPTS)
[DGPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGPATH)
[DGROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT)
[DGSIGN](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGSIGN)
[DNSCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DNSCONF)
[DYCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DYCONF)
[DYLIB](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DYLIB)
[EXPIRE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#EXPIRE)
[FCL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FCL)
[FFROMCL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FFROMMD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FFROMSV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FMD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FSV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FTOMD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FTOSV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter-params)
[FILETYPE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FILETYPE)
[FORWARD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FORWARD)
[FTOCL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FTOCL)
[FTPCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FTPCONF)
[HOSTLIST](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTLIST)
[HOSTS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTS)
[HTMLCONV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTMLCONV)
[HTMUX](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTMUX)
[HTTPCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTTPCONF)
[ICP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ICP)
[ICPCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ICPCONF)
[INETD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#INETD)
[LDPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LDPATH)
[LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH)
[LOGDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGDIR)
[LOGFILE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGFILE)
[MASTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTER)
[MASTERP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTERP)
[MAXIMA](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MAXIMA)
[MIMECONV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MIMECONV)
[MOUNT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MOUNT)
[MountOptions](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountOptions)
[MYAUTH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MYAUTH)
[NNTPCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#NNTPCONF)
[OWNER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#OWNER)
[PERMIT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PERMIT)
[PORT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PORT)
[PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROTOLOG)
[PROXY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROXY)
[REACHABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REACHABLE)
[REJECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REJECT)
[RELAY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELAY)
[RELIABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELIABLE)
[REMITTABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REMITTABLE)
[RESOLV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESOLV)
[RES_AF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_AF)
[RES_CONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_CONF)
[RES_DEBUG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_DEBUG)
[RES_NS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_NS)
[RES_RR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_RR)
[RES_VRFY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_VRFY)
[RES_WAIT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_WAIT)
[RIDENT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RIDENT)
[ROUTE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ROUTE)
[RPORT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RPORT)
[SCREEN](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SCREEN)
[SERVER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER)
[SHARE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SHARE)
[SMTPCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SMTPCONF)
[SMTPGATE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SMTPGATE)
[SockMux](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_SockMux)
[SOCKOPT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKOPT)
[SOCKS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKS)
[SOCKSTAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKSTAP)
[SOXCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOXCONF)
[SOCKMUX](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKMUX)
[SRCIF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF)
[SSLTUNNEL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSLTUNNEL)
[STLS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#STLS)
[SYSLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SYSLOG)
[TIMEOUT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TIMEOUT)
[TLSCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TLSCONF)
[TUNNEL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TUNNEL)
[UMASK](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#UMASK)
[URICONV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#URICONV)
[VSAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#VSAP)
[XCOM](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#XCOM)
[XFIL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#XFIL)
[YYCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#YYCONF)
[YYMUX](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#YYMUX)

`CFI CU-SeeMe DGAuth DNS FTP Gopher HostList HTTP ICP IMAP LDAP NNTP PAM POP ProtoList SMTP SockMux Socks SSI.shtml SSL TCPrelay Telnet UDPrelay Whois FTPxHTTP X YYsh YYMUX`

INDEX

[NAME](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#NAME)

[SYNOPSIS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SYNOPSIS)

[DESCRIPTION](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DESCRIPTION)

[OPTIONS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#OPTIONS) ( `-P -Q -f -r -v -d -D -F name=value` )

[Terminology](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#terminology)

[Parameters](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PARAMETERS) [General](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#general) : `SERVER ADMIN OWNER CRON INETD HOSTLIST CLUSTER CMAP DYCONF DYLIB LDPATH LIBPATH DATAPATH DGCONF DGPATH DGOPTS DGSIGN SOCKOPT PORT` [Routing](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#routing) : `FORWARD ROUTE MASTER MASTERP PROXY YYMUX SOCKS SOCKSTAP SSLTUNNEL VSAP CONNECT SRCIF TUNNEL RPORT` [Access control](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#acl) : `PERMIT REJECT REMITTABLE REACHABLE RELIABLE SCREEN RELAY AUTH AUTHORIZER MYAUTH RIDENT` [Resource usage restriction](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#resource) : `MAXIMA TIMEOUT DELAY CHOKE` [Cache control](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#caching) : `CACHE EXPIRE CACHEFILE ICP` [Mount](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#mounting) : `MOUNT MountOptions URICONV BASEURL DELEGATE` [Data conversion](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#conversion) : `CHARCODE CHARMAP HTMLCONV MIMECONV` [Filter control](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter) : `FCL FTOCL FFROMCL FSV FTOSV FFROMSV FMD FTOMD FFROMMD XCOM XFIL` [Local file usage](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#localfile) : `CHROOT DGROOT SHARE UMASK LOGDIR LOGFILE PROTOLOG COUNTER COUNTERDIR Aging` [Host name resolution](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#resolver) : `HOSTS RESOLV RES_CONF RES_NS RES_AF RES_RR RES_VRFY RES_WAIT RES_DEBUG` [Protocol specific](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#protospec) : `HTTPCONF FILETYPE CGIENV ICPCONF FTPCONF NNTPCONF SMTPCONF SMTPGATE DNSCONF`

[ProtoList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ProtoList)

[HostList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList)

[Parameter Substitution](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Substitution)

[CFI and CFI Script](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CFIscript)

[Proxying by URL Redirection](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGproxy)

[Protocol Specific Issue and Examples](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ProtoSpec) `TCPrelay UDPrelay SockMux Socks DGAuth PAM HTTP SSI.shtml ICP FTP Telnet POP IMAP SMTP NNTP LDAP Whois X Gopher SSL DNS CU-SeeMe`

[Reserved Names](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESERVED)

[AF_LOCAL Sockets](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AF_LOCAL)

[Customization](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#customize)

[Platform Specific Issue](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Platforms) ( [Unix](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Unix) [MS-Windows](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MSWin) [OS/2](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#OS2) )

[Defense Against Attackers](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense)

[Gentle Restart](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESTART)

[Functions](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Functions)

[FILES](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FILES)

[ACRONYMS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Acronyms)

[SEE ALSO](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SeeAlso)

[AUTHOR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Author)

[FEEDBACK](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FEEDBACK)

[DISTRIBUTION](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DISTRIBUTION)

```bash
--------- --------- --------- --------- --------- --------- --------- ---------
DELEGATED(8)                MAINTENANCE COMMANDS                   DELEGATED(8)
```

**NAME**

delegated - DeleGate server
**SYNOPSIS**

`delegated`[-P*port*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P)
[[-f]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_f)
[[-r]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_r)
[[-F*func*]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_Func)
[[-v[vdts]]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_v)
[[+=configfile]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_+=)
[[*name*=*value*]*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_parameter)
[[–]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_--)
**DESCRIPTION**

DeleGate is a multipurpose proxy server which relays various application
protocols on TCP/IP or UDP/IP, including[HTTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_HTTP),
[FTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_FTP),
[Telnet](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_Telnet),
[NNTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_NNTP),
[SMTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_SMTP),
[POP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_POP),
[IMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_IMAP),
[LPR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_LPR),
[LDAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_LDAP),
[ICP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_ICP),
[DNS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_DNS),
[SSL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_SSL),
[Socks](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_Socks),
and more.
DeleGate mediates communication between servers and clients where direct
communication is impossible, inefficient, or inconvenient.

DeleGate works as an *application level proxy* which interprets relayed
protocol (control sequence and data structure) between a client and a server;
various value added services are realized for recognized protocol.
Also DeleGate works as a *circuit level proxy* which literally conveys
transmission between a client and a server of arbitrary protocols
on [TCP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_tcprelay) or [UDP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_udprelay).

DeleGate can be used to enforce [*access control*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#acl)
restricting remittable protocols,
reachable servers, and acceptable clients.
DeleGate forces delay for penalty on repetition of forbidden access,
or make [defense](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense)
shutting down service and sending automatic reports to administrator
on suspicion of attack.
A basic [*logging*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#logging) on circuit level
common to arbitrary protocol
and protocol dependent logging in some common formats
are supported for some protocols.

DeleGate can act as a kind of
*application level**[router](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#routing)*,
controlling direct or indirect routes toward a destination server
by selecting upstream proxy or Socks server.
One of exploitable routes toward a server will be selected or tried in order
depending on application protocol, destination host and source client.

As an application level proxy, DeleGate interpretively relays
various application protocols, providing various value added services
including[*caching*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#caching)
or [*conversion*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#conversion)
for relayed data, of which structure depends on each application protocol.
Based on interpretation of application protocols,
DeleGate can be used as a *protocol gateway*
which translates between client-side protocol and server-side protocol.

As a circuit level proxy, a DeleGate server literally conveys transmission
bound to a specified server of a specified application protocol on TCP or UDP,
or toward arbitrary servers based on Socks protocol.

As an application level proxy, DeleGate provides virtual view for resources
in other servers, by aliasing, merging, and hiding real names
(like URL which identifies a resource or a service) in real servers.
It is like a generalized mechanism of NFS file mount,
but unlikely it is realized by rewriting content of data.
In other words, this is a mapping (rewriting)
of virtual names in client
to/from real names in server,
where names are embedded in a protocol dependent data structure
on request/response messages between a client and a server.
With this function named[*mounting*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#mounting),
for example, a resource
<http://hostiN/> is shown to client as if it is <http://hostx/iN/>.
MOUNT can be used to
[*customize*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#customize)
built-in icons and messages of DeleGate too.

Communication between client and DeleGate or between DeleGate and server
can be filtered or translated by user defined[*filter*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#filter)
programs attached to DeleGate using a simple scheme named
[CFI](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CFIscript) (Common Filter Interface).
Existing filter programs, from standard input to standard output,
can be used as a CFI program without modification.
Besides filtering by external programs,
some of frequently used filtering operations are built-in to DeleGate,
including [HTTP header removal](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httpconf_killhead)
and [generation](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httpconf_addhead).

All of[local files](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#localfile)
of DeleGate, including log files and cache files,
are placed under an individual root directory ([DGROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT))
as private files belong to the owner of the DeleGate by default.
But to share them among different users,
the path name, owner, and access permission of each file can be customized.
Also log file name can be parameterized with date value for
[aging](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#aging),
and cache file name can be parameterized with hash value to distribute
cache disks.

Although DeleGate can be controlled by a lot of options,
only[-P*port*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P) option and
[SERVER=*protocol*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER) parameter
are mandatory to operate in most case.
The -P option specifies on which *port* DeleGate receives
requests from clients. [SERVER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER)
parameter specifies in which *protocol*
DeleGate communicates with clients, and optionally to which destination server
it will relay the communication.

Options can be loaded from local or remote resources
with “+=*URL*” notation,
typically from a local file like “+=/path/of/parameters”
(see[Parameter Substitution](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#term_SUBSTITUTION))
(see [DGCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGCONF) also)

**OPTIONS**

```bash
   -P option  --  entrance port(s) to the DeleGate
              ==  -Pport[,port]*
        port  ==  [host:]portNum[/udp][/admin][/protocolName]
     portNum  ==  number[-number]
```

This option specifies on which *entrance port* DeleGate receives
requests from clients.
As a typical example, “-P8080” means it accepts request on TCP port
numbered 8080 on any network interface belong to the host machine.
When the host has multiple interfaces or multiple IP addresses
assigned to a single physical interface, you can select one of them
with the specification format -P*host*:*portNum*, like
“-Plocalhost:8080” for example.
A DeleGate server can accept from multiple ports or (limited) multiple
network interfaces by -P*port*,*port*,…

When no *host* is specified, only IPv4 addresses are accepted.
That is, -P8080 is the abbreviation of “-P0.0.0.0:8080”.
To specify IPv6 address here, substitute each colon symbol in the
IPv6 address notation with an under score symbol. Fore example,
“-P__:8080” means accepting at port 8080 with the wild card address
of IPv6 “::”. If necessary, a scope-ID can be specified with “%” symbol,
like “-Pfe80__12_34%en0:8080” for example.

Note: See[SRCIF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF)
as to selection of a source address of an outgoing connection.

An entrance port is made as a TCP port by default except UDP based
application protocol (dns, icp, cuseeme, udprelay) is specified in
SERVER=*protocol* parameter.
And regardless of the protocol specified in SERVER, it can be
made as a UDP port with postfix “/udp” like -P*port*/udp.

If “/*protocolName*” is specified, as “-P21/ftp,80/http,1080/socks”
for example, the DeleGate will act in the specified application protocol
on the specified port, rather than in the default protocol specified in
the SERVER parameter.

This option MUST be specified except in following cases.
It is ignored when the DeleGate is invoked from [inetd(8)](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#inetd),
or in most case of -F*function* option,
or when running as a [*tunnel server*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#tunnel)
with SERVER=“tunnel1”.

```bash
   -Q option* --  entrance port to the DeleGate
              ==  -Qport
```

-Q option can be used to specify multiple entrance ports separately in
multiple options.
For example, a set of of options “-Q21 -Q80 -Q1080” is equivalent to
a single option “-P21,80,1080”.

```bash
   -f option  --  foreground execution
              ==  -f[v]
```

If specified, DeleGate runs in foreground keeping connected with
current control tty so that it can be killed with SIGINT from the tty,
and staying at (without changing[work directory](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#WORKDIR) from)
the current directory.
With -fv option, the output to the LOGFILE is also put to the console.

```bash
   -r option  --  restart
```

If specified, currently running DeleGate on the same entrance port if exist
is finalized before starting this DeleGate.
It has the same effect as doing[-Fkill](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#func_kill) before start.

```bash
   -v option  --  logging level control
              ==  -v[vdtsau]
```

If specified, DeleGate will run in foreground like -f and
log will be put on the control tty, not to[LOGFILE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGFILE)
and [PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROTOLOG).
More detailed log than that
of -v can be got using -vv option. Similarly you can control the
detailness of log to be written into logfile by -vd, -vt or -vs options;
-vd makes logs detailed with debug information whereas
-vt makes it terse and
-vs makes logging stop and be silent;
this option has similar effect with LOGFILE=””.
Another option -va makes hidden log in the most detailed level (that of -vd)
which is output only when some kind of ABORT occurred to cause
[emergency shutout](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense).
-vu puts logging level back to usual one.

```bash
   -d option  --  debugging of sub components
              ==  -d[hst]
```

-dh enables detailed logging of[HostList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList) matching.
-ds enables logging of socket manipulation including bind(), accept()
and connect().
-dt enables detailed logging of the activity of each thread with its thread-id.

```bash
   -D option  --  disabling sub components
              ==  -D[t]
```

-Dt disables the usage of thread (for SSL and gzip) to force using process.

```bash
   -S option  --  watch SIGCHLD signal
```

If specified, zombie processes of DeleGate will be
immediately swept by watching the SIGCHLD signal. This option might
be the default in future releases.

```bash
   -T option  --  trace system calls
              ==  -T[xsdt]*
```

If specified, signals occurred in DeleGate processes
will be watched by the parent DeleGate using “ptrace(2)” then recorded
into TRACELOG. If -Tx is specified, DeleGate process which is going
to execute “execve(2)” system call will be trapped and killed. This
will be useful for security enhancement preventing any unexpected
execve() which can be the method of intruders.
This -T option automatically turn on -S option to immediately respond to
events occurred in children, but you can turn off it by adding “s”
flag like “-Ts”. Adding “d” flag like “-Txd” will make logging detailed,
while adding “t” flag like “-Txt” will make logging terse.

```bash
   -F option  --  extra function
              ==  -Ffunction
```

If specified, DeleGate will work as a
program of specified *function* rather than a DeleGate server.
For example, “delegated -Fkill -P*port*” means to kill the
DeleGate running on the *port*.
“[-Fimp](http://www.delegate.org/delegate/implant/)”
is a function to edit implanted parameters in the executable file
of DeleGate, to control authentication and capabilities (who can do what with
the DeleGate), and to configure fixed (not overwritable) parameters
of the executable file.
The usage is shown with “delegated -Fimp -h”.
With -Fcgi, DeleGate act as a cgi program which is invoked from a HTTP server.
A list of [available functions](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Functions) will be shown
with -Fhelp.

```bash
   -- option  --  hiding command line arguments
```

If specified, command line arguments before “–” are left visible to
ps(1) command (with pstat(2) system call) on most of Unix systems.
Without this, any arguments are hidden by default.

```bash
   parameter  ==  name=value
```

Other options are specified in *name*=*value*
format which is named a *parameter*.
Parameters can be given as environment variables as well as command line
arguments.
For *name* parameter, the environment variable DG_*name* is
retrieved prior to *name*.
Command line options with “-” prefix listed above can be given as a
parameter like DGOPTS=”-P8080;-v” for example.

```bash
   conditional parameter == (condition)parameter
```

Some parameters and -v option can be restricted to be applied conditionally,
by prefixing “(*condition*)” to a parameter.
Currently, *condition* is a list of client host which is described
in[HostList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList).
For example, “(.localnet)-vs” specifies to suppress logging when the client
is from local networks.
Parameters which can be conditional with this prefix are:
BASEURL, DELAY, DELEGATE,
FCL, FSV, FFROMCL, FFROMSV, FTOCL, FTOSV,
LOGFILE, MAXIMA, RIDENT and TIMEOUT.
This mechanism does not work for UDP sockets.

```bash
   -e option  ==  -ename=value
```

This is similar to *name*=*value* except that
this *name*=*value* pair will be set as
an environment variable to be inherited to child processes
like filter programs and CGI programs.

Terminology

delegated
:   A server process of DeleGate
and the standard file name of a DeleGate program;
the trailing “d” implies “daemon” or server (by convention on Unix)

specialist
:   A DeleGate configured to talk a specified client-side protocol
(with SERVER=*proto*)

generalist
:   Also called MASTER-DeleGate which can talk arbitrary client-side
protocol which will be determined at run-time
(with SERVER=“delegate”) where clients are DeleGate
which use this DeleGate as an upstream proxy
(pointing by a MASTER parameter).

bound DeleGate
:   DeleGate bound to a specified destination server
(with SERVER=*proto*://*host*)

unbound DeleGate
:   DeleGate not bound to any destination server
(without SERVER=*proto*://*host*)

*P*-DeleGate (ex. HTTP-DeleGate)
:   DeleGate communicate with clients in protocol *P*

*Q*/*P*-DeleGate (ex. FTP/HTTP-DeleGate)
:   DeleGate communicate with clients in protocol *P*
and communicate with servers in protocol *Q*

*P* proxy (ex. HTTP proxy)
:   A proxy server which communicates with clients in protocol *P*

[ProtoList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ProtoList)
:   a list of protocols

[HostList](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList)
:   a list of hosts or networks

dstHostList
:   a HostList of destination (servers)

srcHostList
:   a HostList of source (clients)

*item*(*N*) (ex. gethostbyname(2))
:   reference to *item*
described in the section *N* of Unix online manuals

**PARAMETERS**

In the following list, parameters marked with “*” are
repeatable like *name*=*value1* *name*=*value2*
… *name*=*valueN*.
If the same parameter is defined both in environment and
command line, the one in command line precedes to the one in environment.
If other non-repeatable names are repeated, the lastly given value is taken.

Parameters marked with “+” can NOT be given in “+=*parameters*” scripts.
Those parameters (including DGROOT, CHROOT, LDPATH, and DYLIB)
need to be specified in command-line arguments
or “implanted” into the executable file of DeleGate with
the[-Fimp](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_Func) option.

General

Parameters in this category are used to control common attributes
of DeleGate independently of the purpose of usage or
target application protocol.

|                                                                                      |                                                                                          |                       |                                                                                                         |
|--------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|-----------------------|---------------------------------------------------------------------------------------------------------|
|                                                                                      |name                                                                                      |value format           |functionality                                                                                            |
|–                                                                                     |–––––                                                                                     |——————                 |–––––––––––––––––                                                                                        |
|                                                                                      |[`SERVER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER)    |*proto*://*host*:*port*|client-side protocol and default server                                                                  |
|                                                                                      |[`ADMIN`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ADMIN)      |*user*@*host*.*domain* |E-mail addr. of the admin. of this DeleGate                                                              |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params)|[`OWNER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#OWNER)      |*user*[/*group*]       |with who’s access right this DeleGate runs                                                               |
|*                                                                                     |[`CRON`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CRON)        |*crontab-spec*         |*cron* compatible scheduler of actions                                                                   |
|*                                                                                     |[`INETD`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#INETD)      |*inetd-conf*           |*inetd* like server configuration notation                                                               |
|*                                                                                     |[`HOSTLIST`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTLIST)|*name*:*hostList*      |define a named [*HostList*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList)|
|*                                                                                     |[`CLUSTER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CLUSTER)  |*protocol*:*hostList*  |define a cluster of servers                                                                              |
|*                                                                                     |[`CMAP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CMAP)        |*map-spec*             |mapping table about the current connection                                                               |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params)|[`DYLIB`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DYLIB)      |*patternList*          |file-name patterns of dynamic libraries                                                                  |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params)|[`LDPATH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LDPATH)    |*dir*;*dir*;…          |search path for DYLIB                                                                                    |
|                                                                                      |[`LIBPATH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH)  |*dir*:*dir*:…          |search path for library files                                                                            |
|                                                                                      |[`DATAPATH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DATAPATH)|*dir*:*dir*:…          |search path for data files                                                                               |
|                                                                                      |[`DGPATH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGPATH)    |*dir*:*dir*:…          |search path for SUBSTITUTION resources                                                                   |
|*                                                                                     |[`DYCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DYCONF)    |*conditions*:*path*    |dynamic configuration based on request                                                                   |
|                                                                                      |[`DGCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGCONF)    |*dir*/*file*           |the file of configuration parameters                                                                     |
|                                                                                      |[`DGOPTS`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGOPTS)    |*option*;*option*;…    |list of command line options                                                                             |
|                                                                                      |[`PORT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PORT)        |*portList*             |reserve entrance ports like -P option                                                                    |
|Routing                                                                               |                                                                                          |                       |                                                                                                         |

These parameters control the indirect routing toward the target server
exploiting upstream proxies or Socks servers on the way to servers.
If any target hosts are directly reachable on IP level from your
DeleGate’s host,
these parameters may not necessary.
Besides these parameters,[ICP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ICP) and [MOUNT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MOUNT)
have something to do with routing based on application protocols.

| |                                                                                            |                             |                                                      |
|-|--------------------------------------------------------------------------------------------|-----------------------------|------------------------------------------------------|
|–|–––––                                                                                       |——————                       |–––––––––––––––––                                     |
|*|[`FORWARD`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FORWARD)    |*proxy*-_-*proto*:*dst*:*src*|forward to *proxy* when from *src* to *dst* in *proto*|
|*|[`ROUTE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ROUTE)        |*proxy*-_-*dst*:*src*        |forward to *proxy* when from *src* to *dst*           |
|*|[`MASTER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTER)      |*host*:*port*                |connect via the upstream DeleGate                     |
| |[`MASTERP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTERP)    |[*host*:*port*]              |invoke a MASTER private to this DeleGate              |
|*|[`PROXY`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROXY)        |*host*:*port*                |connect via the upstream proxy                        |
|*|[`YYMUX`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#YYMUX)        |*host*[:*port*]              |connect via the YYMUX server                          |
|*|[`SOCKS`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKS)        |*host*[:*port*]              |connect via the socks server                          |
| |[`SSLTUNNEL`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSLTUNNEL)|*host*:*port*                |connect via the SSL tunnel for HTTPS                  |
| |[`VSAP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#VSAP)          |*host*:*port*                |accept/connect via a remote host                      |
|*|[`CONNECT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT)    |ca,ma,di,so,…                |the order of trials of connection types               |
|*|[`SRCIF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF)        |*host*[:*port*]              |source address of connection to server                |
| |[`TUNNEL`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TUNNEL)      |*type*:*scriptPath*          |connect via the tunnel on serial line                 |
| |[`RPORT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RPORT)        |{tcp                         |udp}[:*host*]                                         |

Access control

These parameters control who (client) can access to what (server)
and how (protocol).
The basic policy of default access control is designed so that
clients on networks local to the host of DeleGate are permitted
to access to any server.
Note that the default value of[REMITTABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REMITTABLE) depends on
[SERVER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER), and
IP-level reachability to DeleGate on a multi-homed host
may be restricted by -P*host*:*port* option.

**You must most carefully configure these parameters
so that this DeleGate does not introduce a security hole,
especially when it is running on a host
which is directly accessible to/from the internet.**

| |                                                                                              |                                 |                                           |
|-|----------------------------------------------------------------------------------------------|---------------------------------|-------------------------------------------|
|–|–––––                                                                                         |——————                           |–––––––––––––––––                          |
|*|[`PERMIT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PERMIT)        |*proto*:*dst*:*src*              |protocols/servers/clients to be permitted  |
|*|[`REJECT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REJECT)        |*proto*:*dst*:*src*              |protocols/servers/clients to be rejected   |
| |[`REMITTABLE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REMITTABLE)|*ProtoList*                      |protocols remittable to the server         |
|*|[`REACHABLE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REACHABLE)  |*dstHostList*                    |only specified server hosts are reachable  |
|*|[`RELIABLE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELIABLE)    |*srcHostList*                    |accept only from the specified client hosts|
|*|[`SCREEN`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SCREEN)        |*{reject                         |accept}*                                   |
|*|[`RELAY`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELAY)          |proxy                            |delegate                                   |
|*|[`AUTH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTH)            |*what*:*aproto*:*users*          |authorized users for remote administration |
|*|[`AUTHORIZER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER)|*serv*:*proto*:*dst*:*src*       |authentication server                      |
|*|[`MYAUTH`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MYAUTH)        |*user*:*pass*:*proto*:*dst*:*src*|authentication client                      |
| |[`RIDENT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RIDENT)        |client                           |server                                     |

Resource usage restriction

These parameters can be useful where available resources are
in severe condition; when the host of DeleGate is heavy loaded,
network bandwidth is narrow, or response from server can be slow.

|             |                                                                                        |                         |                                    |
|-------------|----------------------------------------------------------------------------------------|-------------------------|------------------------------------|
|–            |–––––                                                                                   |——————                   |–––––––––––––––––                   |
|*            |[`MAXIMA`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MAXIMA)  |*what*:*number*          |maxima of parallel sessions and etc.|
|*            |[`TIMEOUT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TIMEOUT)|*what*:*seconds*         |timeout of connection and etc.      |
|*            |[`DELAY`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DELAY)    |*what*:*seconds*         |delay for penalty                   |
|*            |[`CHOKE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHOKE)    |*Delay*:*Clnt*:*UA*:*Ref*|choking robots                      |
|Cache control|                                                                                        |                         |                                    |

Enable or disable cache and specify validity of cached data.
Usage of cache is controlled in context of routing by[CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT) too.
Removing stale cache file can be done periodically using
[CRON](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CRON).

| |                                                                                            |                 |                                   |
|-|--------------------------------------------------------------------------------------------|-----------------|-----------------------------------|
|–|–––––                                                                                       |——————           |–––––––––––––––––                  |
| |[`CACHE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHE)        |do               |no                                 |
|*|[`EXPIRE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#EXPIRE)      |*days*           |*hours*                            |
| |[`CACHEFILE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHEFILE)|*fileNameSpec*   |in which file cache data are stored|
|*|[`ICP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ICP)            |*icpClientConfig*|configuration as an ICP client     |

Mount

Provide virtual view for other server(s) by URL mapping,
filtering and aliasing resource names,
to merge multiple servers,
to translate between different protocols,
to export internal servers,
and so on.
Also MOUNT can be used to[customize](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#customize)
or replace built-in icons and messages.

| |                                                                                          |                           |                                        |
|-|------------------------------------------------------------------------------------------|---------------------------|----------------------------------------|
|–|–––––                                                                                     |——————                     |–––––––––––––––––                       |
|*|[`MOUNT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MOUNT)      |“*vURL **rURL **opt*”******|map virtual *URL* to/from real *URL*    |
|*|[`URICONV`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#URICONV)  |*convList*:*attrList*      |control URI rewriting with MOUNT        |
| |[`BASEURL`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#BASEURL)  |*URL*                      |the base of (virtual) URL of this server|
| |[`DELEGATE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DELEGATE)|*host*:*port*              |limited form of BASEURL                 |

Data conversion

Parameters to control built-in converter for text type data.

|              |                                                                                          |      |                 |
|--------------|------------------------------------------------------------------------------------------|------|-----------------|
|–             |–––––                                                                                     |——————|–––––––––––––––––|
|*             |[`CHARCODE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARCODE)|JIS   |EUC              |
|*             |[`CHARMAP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARMAP)  |[jis  |ucs]:a-z/A-Z     |
|              |[`HTMLCONV`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTMLCONV)|deent |enent            |
|              |[`MIMECONV`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MIMECONV)|thru  |charcode         |
|Filter control|                                                                                          |      |                 |

Insert a filter program on the way to/from client or server
to convert data transmitted between them.

| |                                                                                  |               |                                       |
|-|----------------------------------------------------------------------------------|---------------|---------------------------------------|
|–|–––––                                                                             |——————         |–––––––––––––––––                      |
| |[`FCL`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FCL)  |*filterCommand*|filter between client and DeleGate     |
| |`FTOCL`                                                                           |*filterCommand*|filter from DeleGate to client         |
| |`FFROMCL`                                                                         |*filterCommand*|filter from client to DeleGate         |
| |`FSV`                                                                             |*filterCommand*|filter between server and DeleGate     |
| |`FTOSV`                                                                           |*filterCommand*|filter from DeleGate to server         |
| |`FFROMSV`                                                                         |*filterCommand*|filter from server to DeleGate         |
| |`FMD`                                                                             |*filterCommand*|filter between MASTER and this DeleGate|
| |`FTOMD`                                                                           |*filterCommand*|filter from this DeleGate to MASTER    |
| |`FFROMMD`                                                                         |*filterCommand*|filter from MASTER to this DeleGate    |
| |[`XCOM`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#XCOM)|*filterCommand*|execute a command as a server          |
| |`XFIL`                                                                            |*filterCommand*|execute a filter as a server           |

Local file usage

All of local files are integrated under DGROOT by default.
You should not change nor specify these parameters if not necessary.

|                                                                                       |                                                                                              |                |                                          |
|---------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------|----------------|------------------------------------------|
|–                                                                                      |–––––                                                                                         |——————          |–––––––––––––––––                         |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params) |[`CHROOT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHROOT)        |*dirPath*       |change the root of file system at start   |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params) |[`DGROOT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT)        |*dirPath*       |root directory of all of DeleGate files   |
|*[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params)|[`SHARE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SHARE)          |*dirPatternList*|files to be shared among users            |
|[+](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#extern-params) |[`UMASK`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#UMASK)          |*mask*          |umask value in octal                      |
|                                                                                       |[`VARDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#VARDIR)        |*dirPath*       |default base of log and cache             |
|                                                                                       |[`CACHEDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHEDIR)    |*dirPath*       |where cache files are placed              |
|                                                                                       |[`ADMDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ADMDIR)        |*dirPath*       |where dynamic administration files are    |
|                                                                                       |[`ETCDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ETCDIR)        |*dirPath*       |where persistent management files are     |
|                                                                                       |[`LOGDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGDIR)        |*dirPath*       |where DeleGate logs are                   |
|                                                                                       |`LOGFILE`                                                                                     |*LogFilename*   |where DeleGate makes logging              |
|                                                                                       |`PROTOLOG`                                                                                    |*LogFilename*   |httpd or wu-ftp compatible log file       |
|                                                                                       |`ERRORLOG`                                                                                    |*LogFilename*   |where DeleGate make error logging         |
|                                                                                       |`TRACELOG`                                                                                    |*LogFilename*   |where signal trace (by -T) is put         |
|                                                                                       |`EXPIRELOG`                                                                                   |*LogFilename*   |file which records expire log             |
|                                                                                       |`WORKDIR`                                                                                     |*dirPath*       |where DeleGate should dump core (-_-;     |
|                                                                                       |`ACTDIR`                                                                                      |*dirPath*       |where temporary files are placed          |
|                                                                                       |`TMPDIR`                                                                                      |*dirPath*       |where invisible temporary files are placed|
|                                                                                       |`PIDFILE`                                                                                     |*fileName*      |where the DeleGate’s PID is recorded      |
|                                                                                       |[`COUNTERDIR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTERDIR)|*dirPath*       |base directory of counters                |
|                                                                                       |[`COUNTER`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTER)      |*CounterOptions*|access counters                           |
|Host name resolution                                                                   |                                                                                              |                |                                          |

Resolve host name to/from IP address using DNS, NIS or local file.

|                 |                                                                                            |                |                                         |
|-----------------|--------------------------------------------------------------------------------------------|----------------|-----------------------------------------|
|–                |–––––                                                                                       |——————          |–––––––––––––––––                        |
|*                |[`HOSTS`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTS)        |*host*/*addr*,… |private host/address mapping             |
|                 |[`RESOLV`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESOLV)      |file,nis,dns,sys|the order of resolvers to be used        |
|                 |[`RES_WAIT`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_WAIT)  |sec:host        |wait for resolver to be ready            |
|                 |[`RES_CONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_CONF)  |*URL*           |where *resolv.conf* is                   |
|                 |[`RES_NS`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_NS)      |*host*[:*port*] |DNS server to be used                    |
|                 |[`RES_AF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_AF)      |46              |64                                       |
|                 |[`RES_RR`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_RR)      |*HostList*      |enable Round Robin of IP-addresses       |
|                 |[`RES_VRFY`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_VRFY)  |“”              |enable double check of reverse resolution|
|                 |[`RES_DEBUG`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_DEBUG)|*number*        |debugging level of name resolution       |
|Protocol specific|                                                                                            |                |                                         |

| |                                                                                          |                         |                                         |
|-|------------------------------------------------------------------------------------------|-------------------------|-----------------------------------------|
|–|–––––                                                                                     |——————                   |–––––––––––––––––                        |
|*|[`HTTPCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTTPCONF)|*what*:*conf*            |HTTP specific configuration              |
| |[`FILETYPE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FILETYPE)|*suffix*:*fileType***    |mapping from filename to data type & etc.|
| |[`CGIENV`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CGIENV)    |*name*,*name*,…          |environment variables to be passed to CGI|
|*|[`ICPCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ICPCONF)  |*icpServerConfig*        |configuration as an ICP server           |
|*|[`FTPCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FTPCONF)  |*what*[:*conf*]          |FTP specific configuration               |
|*|[`NNTPCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#NNTPCONF)|*what*:*conf*            |NNTP specific configuration              |
|*|[`SMTPCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SMTPCONF)|*what*:*conf*            |SMTP specific configuration              |
| |[`SMTPGATE`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SMTPGATE)|*dirPath*                |SMTP to SMTP/NNTP g.w. configuration     |
|*|[`DNSCONF`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DNSCONF)  |*what*:*conf*            |configuration as a DNS server            |
|*|[`SOCKSTAP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKSTAP)|*proto*[:[*dst*][:*src*]]|interpret the protocol over SOCKS        |

```bash
SERVER parameter*   ==  SERVER=protocol[://host[:portNum]][:-:MountOptions]
           portNum  ==  [+|-]number
                    --  default: SERVER=delegate
```

SERVER=*protocol*
specifies the protocol to be used for communication with clients,
which will be the default protocol with servers.

Example: a SERVER parameter for unbound Telnet-DeleGate

`SERVER=telnet`
If SERVER=“delegate” is given, the DeleGate will become a
*generalist* (or MASTER-DeleGate),
which acts as an upstream DeleGate of other DeleGates.
**Note that a *generalist* can remit arbitrary protocols by default,
so that it can be dangerous
without enough consideration on access control**
(see[REMITTABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#REMITTABLE)).
A generalist automatically detects multiple protocol,
including HTTP, proxy-Whois,
as well as DeleGate original protocol.

If no destination server (*host*) is specified,
it is to be be given by client somehow at run-time,
on application level in protocol dependent way.

Several protocols including “http” and “socks” have inherent and automatic way
to do proxying. Some protocols, like “ftp” and “pop”, with a subprotocol to
*login* to server are naturally extended so that information about
destination server is encoded as *user*@*host* for *user name*
as login information.
Some protocols, including “whois” and “gopher”, in which the first message is
sent from client side, typically as a query message,
the message is extended (without changing the specification)
to include information about destination server.
Some of other protocols like “telnet” have interaction with user on a client
program thus can be extended with login dialogue for proxying.

The protocol with server is implicitly expected to be the same with the
protocol with the client.
Some protocols like HTTP have their inherent way to specify the protocol with
the destination server.
Otherwise it must be explicitly given with MOUNT parameter, like
MOUNT=”/news/* nntp://server/*” for example.

SERVER=*protocol*://*host*:*portNum* specifies the URL of
destination server.
The “:*portNum*” part is omittable as usual in URL
if the number is that of standard port number of the *protocol*.
A list of protocols and standard port numbers recognized by
the DeleGate is available at:
“http://*delegate*/-/builtin/mssgs/config.dhtml”.

Port mapping:
If a *portNum* is prefixed with “-” or “+”,
it means mapping the port number of the[entrance](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#entrance) port
adding the specified offset,
or using the port number as is by “-” with empty *portNum*.

Example: forwarding multiple ports to an another host

`-P21,23,25,80 SERVER=tcprelay://host:-/`

A special hostname [”`odst.-`”](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#odst.-) can be used
to refer the original destination host when the incoming data is
forwarded by NAT.

Example: forwarding NAT to the original destination via a SOCKS proxy

`-P9999 SERVER=tcprelay://odst.-:- SOCKS=sockshost`

**Note that a DeleGate bound to a specific server is not disabled to
work as a proxy for arbitrary servers.
Proxying ability must be restricted if necessary, using
PERMIT, REACHABLE and RELAY parameters.**

If a SERVER parameter is with “:-:*MountOptions*”,
the SERVER parameter will be dynamically selected if the condition
specified in the[MountOptions](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountOptions)
is evaluated to be true.
As a special case, “:-:via=*HostList*” can be abbreviated
as “:-:*HostList*”.

Example: selecting an appropriate NNTP server for a client

`SERVER="nntp://newsserver1:-:from={*.dom1}"   SERVER="nntp://newsserver2:-:from={*.dom2}"`

Example: {NNTP,SMTP,POP}-DeleGate as a single server

`-P119,110,25   SERVER="nntp://nntpserver:-:{*:119}"   SERVER="smtp://smtpserver:-:{*:25}"   SERVER="pop://popserver:-:{*:110}"`

```bash
ADMIN parameter     ==  ADMIN=user@host.domain
                    --  default: built in at compile time
```

This parameter must be correctly given especially when the DeleGate runs on
a host directly reachable to/from internet.
This E-mail address will be used as follows:

| |                                                                                                                                                                                                 |
|-|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|-|Shown in (error) messages to clients, as the name of the administrator of this DeleGate (HTTP, etc.).                                                                                            |
|-|Shown in opening messages or in a help message to clients, as the name of the administrator (FTP, NNTP, Telnet).                                                                                 |
|-|Sent as a default user name (in PASS command) on anonymous access to FTP servers.                                                                                                                |
|-|Sent as sender name (in FROM command) in access to remote SMTP server on verification by AUTH=[anonftp:smtp-vrfy](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#smtp-vrfy).|
|-|Report messages are sent to the address on occurrence of fatal signals                                                                                                                           |

```bash
OWNER parameter*    ==  OWNER=user[/group][:srcHostList]
                    --  default: OWNER="nobody/nogroup"
                    --  restriction: super-user only on most of Unix
                    --  restriction: setting the user of a service on Windows
```

This parameter is effective only when the invoker is a super-user.
If specified, the DeleGate will run with the right of specified
user, calling setuid(2) and setgid(2) system calls. User and group
can be specified either in symbolic name or in id-number prefixed
with “#” like “#1234”.

If *srcHostList* is specified, owner of this DeleGate will be set to
the user when the client host is included in the list. The user
name “*” will be substituted by the user name of the client when
it can be got from an[Identification](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Ident) server on the client host.

Example:
run with the user ID corresponding to the user name of the client

`OWNER="*:*@*".`

On Windows, `OWNER=`*user* may be specified when it is
invoked as a service, to set the user of the DeleGate service to be created.
With empty user name as `OWNER=""`, the user name is got from
the `USERNAME` environment variable. The password can be specified
with a `PASS=`*pass* parameter or an environment variable, or
it will be asked on the console.

```bash
CRON parameter*     ==  CRON="crontab-spec"
       crontab-spec ==  minute hour day month dayOfWeek action
                    --  default: none
```

Cause an action at a time specified in the format of *crontab-spec*
which is compatible with that of standard crontab(5) of *cron*(8)
servers in Unix systems.
If the action is prefixed with “/” then it is an external action
which will be executed by the system(3) function. If the action is
prefixed with “-” then it is a built-in internal action of DeleGate.

|                   |                                                                                                     |
|-------------------|-----------------------------------------------------------------------------------------------------|
|`-suspend N`       |– suspend for *N* seconds                                                                            |
|`-restart`         |– [restart](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESTART) the DeleGate|
|`-exit`            |– finish the DeleGate                                                                                |
|`-expire N`        |– execute expiration for $CACHEDIR by “-atime +*N*d”                                                 |
|`-system command`  |– execute *command* as a shell command                                                               |
|`/dir/command args`|– equiv. to “-system */dir/command* *args*”                                                          |
|`- args`           |– equiv. to “*/dir*/delegated *args*”                                                                |
|`-Ffunc args`      |– equiv. to “*/dir*/delegated -F*func* *args*”                                                       |

Example:

`CRON="0 0 * * * -restart"   CRON="0 3 * * * -expire 3" (this is equivalent to followings)   CRON="0 3 * * * -Fexpire /path/of/cache -rm -atime +3 -sum"   CRON="0 3 * * * /path/of/delegated -Fexpire /path/of/cache -rm -atime +3 -sum"`

```bash
INETD parameter*    ==  INETD="inetd-conf"
        inetd-conf  ==  port sockType proto waitStat uid execPath argList
              port  ==  [host:]portNum
          sockType  ==  stream | dgram
             proto  ==  tcp | udp
          waitStat  ==  nowait ("wait" is not yet supported)
                    --  default: none
```

Invoke a new DeleGate process with the specified configuration when
a request is arrived at the specified port. The format of the
*inetd-conf* specification is like that of standard inetd.conf(5)
in Unix systems.  
A default value of each field can be represented by “-”.
Default values of *sockType*, *proto* and *waitStat*
are “stream”, “tcp” and “nowait” respectively.
The *uid* field will be used as[OWNER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#OWNER) parameter in the invoked process.
Specifying “-” as *uid* value means
invoking DeleGate without OWNER parameter.
If *execPath* is “-”,
it means to start child DeleGate process with the given *argList.*
The configuration of the parent DeleGate process is inherited to
child DeleGates. For example, when a parent DeleGate is invoked
like:

`delegated ADMIN=foo EXPIRE=1 INETD=conf1 INETD=conf2`
these ADMIN and EXPIRE parameters are inherited to DeleGates
described in *conf1* and *conf2*.

Example:

INETD=“8080 stream tcp nowait nobody - SERVER=http”

INETD=“8080 - - - nobody - SERVER=http” (equivalent to the above)

INETD=“8119 - - - - - SERVER=nntp://nntpserver/”

INETD=“8888 - - - - /bin/date date” (equivalent to the following)

INETD=“8888 - - - - - SERVER=exec XCOM=”/bin/date date”’

INETD=“8888 dgram udp - - /bin/date date”

INETD=“localhost:8888 - - - - - /bin/sh sh”

INETD=+=/path/of/inetd.conf (load configuration from a file)

```bash
HOSTLIST parameter* ==  HOSTLIST=listName:HostList
```

Define a named[*HostList*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostList) with the name *listName*.
A named HostList can be referred in other HostLists.
If multiple HOSTLIST parameters with the same *listName* are defined,
the lastly defined one is referred.
If a *HostList* is prefixed with “+,”
like HOSTLIST=”*listName*:+,*newHostList*”
then the *newHostList* is appended to the current definition of the list.

Predefined named HostList:

HOSTLIST=[.localnet](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#localnet):localhost,./.,-/.,.o/.”

HOSTLIST=`.socksdst:!.localnet`

Example:

// redefine .localnet

HOSTLIST=”.localnet:localhost,./32,192.168.*”

// exclude localhost form the predefined .localnet

HOSTLIST=”.localnet:+,!localhost”

```bash
CLUSTER parameter*  ==  CLUSTER=[protoList]:ServerList
        ServerList  ==  [/R,]Server[,ServerList]
            Server  ==  Host[..Port]
```

The `CLUSTER` parameter defines an ordered set of alternative or
complemental servers (origin or proxy).
It is referred when DeleGate failed to connect or authenticate with
an upstream proxy server or an origin server.
It is applied to proxy server specified in
`MASTER`, `PROXY`, `SSLTUNNEL`, `SOCKS`,
or an origin server specified in `SERVER` or
in the right-hand of `MOUNT`.

If a list is prefixed with “/R”, the servers in the list are tried
in random order (the first server to be tried is selected randomly and
other servers are tried in the round-robin order).
It could be useful for load balancing among equivalent (proxy) servers.

The retrial by this parameter is commonly applied to servers of any protocols
in the phase of establishment of a TCP connection to a server.
The retrial covers the authentication phase for several protocols.
In HTTP origin/gateway servers, the retrial may be caused depending on
the response from the server, including the response code 503
(Service Unavailable) and 404 (Not Found) for example.

Example:

CLUSTER=http:www1,www2,www3..8080 MOUNT=”/* <http://www1/\>*”  
CLUSTER=ftp:ftp1,ftp2,ftp3 MOUNT=”/* <ftp://ftp1/\>*”  
CLUSTER=http-proxy:/R,px1..8080,px2..9090,px3..8080 PROXY=px1:8080  
CLUSTER=socks:/R,sock1,sock2,sock3 SOCKS=socks1

```bash
CMAP parameter*     ==  CMAP=resultStr:mapName:connMap
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
```

A generic parameter to make some parameters be conditional on the current connection.
When the protocol, the destination and the source
of the current connection match the *connMap*,
this map is enabled providing *resultStr* string
to be used for *mapName*.

Not only host name/address but also port number of destination servers
can be used for matching in[*dstHostList*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#portList).
A typical usage of this parameter is for applying
[*filter*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#cond-filter) conditionally.

```bash
TLSCONF parameter*  ==  TLSCONF=tlsConf[,tlsConf]*
           tlsConf  ==  what:value
                    --  default: TLSCONF=scache:do,xcache:do
```

-v[d|s]
:   specify the detailness of logging of TLS setup and relay.
“-vd” make logging detailed whereas “-vs” suppresses any logging.

scache[:[do]|no|acc|con]
:   enable or disable the session caches.
By default, both session caches for accept and connect are enabled.
“no” disables both of these caches. “acc” enables only the cache
for clients. “con” enables only the cache for servers.

xcache[:[do]|no|acc|con]
:   enable or disable the context cache for certificates of this DeleGate.

shutdown | shutdown:flush | shutdown:wait | shutdown:none
:   enable sending the shutdown alert (close notify) to the peer
before disconnection.
It is enabled by default for FTP (TLSCONF=“shutdown” is preset for
SERVER=“ftp” or SERVER=“ftps”).

libs:*libname*[+*libname*]
:   specify the dynamic libraries for SSL in the order to be loaded instead
of the default ones, as TLSCONF=“libs:crypto+ssl” for example.
A *libname* can be with a version number like “libssl.so.0.9.8” or
in a full-path name like “/usr/local/lib/libcrypto.0.9.8.dylib”.

```bash
STLS parameter*     ==  STLS=stlsSpecs[,sslwayCom][:connMap]
         stlsSpecs  ==  [-]stlsSpec[/im][/ssl][,stlsSpecs]
          stlsSpec  ==  fsv | fcl | mitm | imimSec
         sslwayCom  ==  {sslway [-Vrfy] [-CApath dir] ...}
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
                    --  restriction: applicable to HTTP, FTP, SMTP, POP, IMAP, SOCKS
                    --  required: SSLway
```

This parameter controls the initiation of SSL (TLS) based on a negotiation
between client and server in each application protocol.
The common scheme of the negotiation is known as “STARTTLS”.
“fsv” specifies using SSL with server and “fcl” specifies using SSL with client.
When SSL is not supported on a connection, the STARTTLS negotiation will fail
and the connection will be closed by default.
To continue a session even when SSL is not available,
prefix “-” to “fsv” or “fcl”.

If “fcl” is specified, a client may start SSL without STARTTLS negotiation.
Such implicit SSL negotiation from the client-side is detected by peeping
a SSL hand-shake packet on the connection from the client-side at the
beginning of a session for a certain period specified with im*imSec*.
The default value is “im0.25” (250m seconds).
“-im” disables this implicit SSL negotiation.
If a *stlsSpec* is followed with “/im” as STLS=“fsv/im” for example,
SSL with the peer (with the server in this case) is applied without
the STARTTLS negotiation.

If “mitm” is specified, it behaves like “-fcl,-fsv” that is
if SSL is enabled in the client side then SSL on the server side is enabled.
It can be used with a HTTP proxy DeleGate as a “secure proxy” or “SSL-tunnel”
to peep the bidirectional communication in CONNECT method,
relaying it as a usual HTTP applying filters and cache.
(“mitm” means “Man-In-The-Middle” mode)
If it is set optional as “STLS=-mitm” then the MITM mode is activated
only when the client specified the server name prefixing with “-mitm.”
as “https://-mitm.host.domain/” for “<https://host.domain/>”.

If non default SSLway command path or options are necessary to be used,
the SSLway command can be specified after *stlsSpecs* as
STLS=“fcl,sslway -Vrfy -cert mycert.pem” for example.

Example:

`STLS="fcl"` – use SSL with client (exit the session if not available)  
`STLS="-fcl"` – use SSL with client if available  
`STLS="fsv,-fcl"` – use SSL with server, and with client if available  
`STLS="fsv/ssl" SERVER="ftp"` – use AUTH SSL instead of AUTH TLS  
`STLS="fsv,im0.5" SERVER="ftp"` – automatic detection of implicit/explicit SSL server

```bash
CERTDIR parameter   ==  CERTDIR=dir
                    --  default: ${ETCDIR}/certs
                    --  version: DeleGate/9.8.0 + OpenSSL0.9.8g or laters
```

CERTDIR specifies the directory as the repository of certificates to be used
by[SSLway](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_SSL).
Certificate files in the directory are named as follows.
All of these files are optional.

`me.pem` – my certificate
:   The certificate of this DeleGate to be sent to clients (and to servers
if requested).
It may contain the private-key too.
It can be a chained certificate followed with the certificates of
intermediate CAs.

`me-key.pem` – my private-key
:   This file is necessary if the private-key for `me.pem` is not
contained in itself.

`me-key.pas` – the pass-phrase for my private-key
:   This file is necessary if the private-key in `me-key.pem` is
encrypted.

`common.pas` – the pass-phrase common to private-keys
:   This file can be used as the default pass-phrase common to
all encrypted private-keys.

`dhparam.pem` – DH PARAMETERS
:   This file is necessary to enable ciphers using Diffie-Hellman algorithm.

`sn.domain.pem` – the certificate for SNI
:   The certificate for the *domain* indicated by SNI
(Server Name Indication).
Like me.pem, it may be in the combination of
sn.*domain*-key.pem and sn.*domain*-key.pas (or common.pas).

`sa.address.pem` – my certificate to clients
:   The certificate to be sent to clients when accessed via the network
interface with *address* (ex. “sa.127.0.0.1.pem”).

`to-sv.pem` – my certificate to servers
:   The certificate like me.pem which is sent to servers only.

`to-cl.pem` – my certificate to clients
:   The certificate like me.pem which is sent to clients only.

`ca-sv.pem` – servers’ CAs’ certificates
:   The certificates of CAs to be used to verify acceptable certificates
shown by servers. It may contain CRL too.

`ca-sv/` – directory of certificates of servers’ CAs
:   each *certificate* is named with
‘openssl x509 -hash -noout < *certificate*.pem’

`ca-cl.pem` – clients’ CAs’ certificates
:   The certificates of CAs to be used to verify acceptable certificates
shown by clients. It may contain CRL too.

`ca-cl/` – directory of certificates of clients’ CAs
:   each *certificate* is named with
‘openssl x509 -hash -noout < *certificate*.pem’

```bash
DGCONF parameter    ==  DGCONF=dir/file
                    --  default: DGCONF='${EXECDIR}/${EXECNAME}.conf'
```

DGCONF specifies the file of configuration parameters to be loaded,
if exists, on the invocation.
The default value is relative to the name of the executable file of
DeleGate. For example, if the path of the executable is
“X:/path/of/dg9_4_1.exe” then DGCONF=“X:/path/of/dg9_4_1.conf”.

```bash
DYCONF parameter*   ==  DYCONF=[conditions]parameters
        parameters  ==  file:path | cgi:path | arg:{listOfParameters}
                    --  default: none
```

DYCONF specifies configuration parameters to be loaded dynamically
on the beginning of relaying application protocol
after the acception of a TCP connection from a client
before starting a session over it.
The loading of parameters can be conditional based on the specified
*conditions*,
and the parameter value can be generated and/or evaluated
on each loading.

A condition for loading can be based on the identity (address or name)
of the host of a client which is requesting over the new connection.
Or it can be based on the content (sub-string or pattern) of
the initial request data which is sent from a client over a connection.
The request data is polled for a specified period (15sec. by default)
and peeked by a specified size (4K bytes at max. by default).

Conditions:

`qstr/string` … matching by request sub-string

`qreq/pattern` … matching by request pattern

`{from/hostList}` … matching by client hosts

`excl[/number]` … exclusive with other DYCONFs

`poll/seconds` … timeout of polling request [4k]

`peek/bytes` … max. bytes of peeking request [15.0s]

`skip` … purge peeked data before starting relay

`debug` … enable logging for debugging of DYCONF

Example:

`DYCONF="file:path.txt" # load parameters from path.txt   DYCONF="cgi:path.cgi" # load parameters generated by path.cgi   DYCONF="qstr/string,arg:{SERVER=tcprelay://sv1:1234;TIMEOUT=io:3}"   DYCONF="{qrex/[a-z][0-9]*},arg:{SERVER=tcprelay://sv1:1234}"`

```bash
DYLIB parameter     ==  DYLIB=libfilePattern[,libfilePattern]*
                    --  default: DYLIB='dglib*.so,lib*.so,dglib*.dylib,lib*.dylib'
```

DYLIB specifies a list of file name patterns for dynamic linking
library files to be retrieved. The character “*” in each pattern is
replaced with the library name to be retrieved, for example with
a pattern “lib*.so”, “libssl.so” is retrieved for “ssl”.
A special pattern “+” means to include the default list.
If a pattern is not in full-path format, the library file will be
retrieved in some directories which depends on the system configuration
or an environment variable like LD_LIBRARY_PATH or so.
A pattern can be in full-path like “/usr/local/ssl/lib/lib*.so”, or
without “*” character like “/usr/local/ssl/lib/libssl.so”.

Example:

`DYLIB="" ... disable dynamic linking   DYLIB="lib*.so,lib*.so.1"   DYLIB="libz.so,libssl.so"   DYLIB="+,lib*.so.0.9.7"   DYLIB="/usr/lib/libz.so.1,/lib/libssl.so"`

```bash
LDPATH parameter    ==  LDPATH=dirPath[;dirPath]*
                    --  default: LDPATH='${LIBDIR};${EXECDIR};${HOME}/lib;/usr/lib;/lib'
```

Specify where dynamic libraries ([DYLIB](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DYLIB)) are searched.

```bash
LIBPATH parameter   ==  LIBPATH=dirPath[:dirPath]*
                    --  default: LIBPATH='.:${STARTDIR}:${LIBDIR}:${EXECDIR}:${ETCDIR}'
```

Library files, including parameter files,
CFI scripts and filter programs,
are searched in multiple directories in order specified in LIBPATH
if it is specified as relative path.
By default, LIBPATH is a ordered list of the following directories:

`WORKDIR` (.) – the working directory  
`STARTDIR` – the directory where the DeleGate is invoked  
`LIBDIR` – `${DGROOT}/lib` by default  
`EXECDIR` – the directory where the executable file of DeleGate is placed  
`ETCDIR` – `${DGROOT}/etc` by default

```bash
DATAPATH parameter  ==  DATAPATH=dirPath[:dirPath]*
                    --  default: DATAPATH='.:${DGROOT}:${STARTDIR}
```

The list of directories each contains data files to be provided to
client. This parameter is used by a DeleGate which generates response
data from local file specified in relative path like
MOUNT=”/*path*/* file:*dir*/*”.

```bash
DGPATH parameter    ==  DGPATH=dirPath[:dirPath]*
                    --  default: DGPATH='+:.:${HOME}/delegate:${EXECDIR}:${ETCDIR}'
```

The search path of parameter files.
A special directory name “+” stands for the place
where the “caller” resource
(a parameter file referring the parameter file) is.

```bash
DGSIGN parameter    ==  DGSIGN=signatureSpec
                    --  default: DGSIGN="V.R.P/Y.M.D"
```

Specify the signature of the DeleGate to be shown to client or server.
The full form signature “Version.Revision.Patch (Month Day, Year)” is
represented as “V.R.P/Y.M.D”. To hide the a specific part, replace the
corresponding character with “x”. For example, DGSIGN=“V.x.x/Y.x.x”
will make signature like “DeleGate/9.x.x (x x, 2005)”.

```bash
DGOPTS parameter    ==  DGOPTS=opt[,opt]*
                    --  default: none
```

A list of command line options.
This may be useful when those options like -P or -v,
not in *name*=*value* format,
are to be given in an environment variable.

```bash
SOCKOPT parameter*  ==  SOCKOPT=[no]name[:value]
                    --  default: reuse
```

Set socket options.

[reuse] | noreuse
:   enables instant reuse of a port number. (SO_REUSEADDR)

share | [noshare]
:   enables simultaneous use of a port. (SO_REUSEPORT)

[shut] | noshut
:   do shutdown(socket,SD_SEND) before closing a socket

shutdown:g[:*connMap*]
:   do graceful shutdown (for HTTP response) on Win32

buffsize:*size*[kiosc][:*connMap*]
:   set the size of socket buffers.
The *size* value can be followed with following specifiers:

```
`k` -- size in kilo bytes  
`i` -- input buffer (SO\_RCVBUF)  
`o` -- output buffer (SO\_SNDBUF)  
`s` -- socket to server  
`c` -- socket from client  

For example, SOCKOPT="buffsize:2kis" set the size of the socket buffer
to receive data from a server to 2048 bytes.
Multiple buffer size specifications can be concatenated with "+".
For example,
SOCKOPT="buffsize:2k" is equivalent to
SOCKOPT="buffsize:2kis+2kos+2kic+2koc:\*:\*:\*".
```

```bash
PORT parameter      ==  PORT=port[,port]*
              port  ==  [host:]portNum[/udp]
           portNum  ==  number[-number]
                    --  default: none
```

Make entrance ports as -P option does.

```bash
FORWARD parameter*  ==  FORWARD=gatewayURL[-_-connMap]
        gatewayURL  ==  gwproto://[user:pass@]gwhost[:gwport]
           connMap  ==  protoList:dstHostList:srcHostList
                    --  default: none
```

Forwards a request
toward a proxy server specified in *gatewayURL*
if the request matches the condition specified in *connMap*,
that is, the request is in a protocol listed in *protoList* and
for servers listed in *dstHostList* and
from clients in *srcHostList*.
If *connMap* is omitted, any request are forwarded to the
*gatewayURL* unconditionally.
If an authentication information is given as “*user*:*pass*@”
prefixed to *gwhost*, it is used on the authentication phase
after the connection with the *gwhost*.

FORWARD is a generalized notation of ROUTE and
the following two notations are equivalent.

[ROUTE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#ROUTE)=*gwproto*://*gwhost*:*gwport*/-_-*dstHostList*:*srcHostList*  
FORWARD=*gwproto*://*gwhost*:*gwport*/-_-*:*dstHostList*:*srcProtoList*

For special *gwproto*, FORWARD works as a generalized notation of
MASTER, PROXY, SOCKS and SSLTUNNEL as follows.

delegate – forward to a DeleGate
:   [MASTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTER)=*gwhost*:*gwport*:*dstHostList*  
FORWARD=delegate://*gwhost*:*gwport*/-_-*:*dstHostList*:*

http, ftp, telnet – forward to an application level proxy (HTTP, FTP, or Telnet)
:   [PROXY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROXY)=*gwhost*:*gwport*:*dstHostList*  
FORWARD=*gwproto*://*gwhost*:*gwport*/-_-*:*dstHostList*:*

socks – forward to a SOCKS server
:   [SOCKS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKS)=*gwhost*:*gwport*[/*socksOpt*]:*dstHostList*:*srcHostList*  
FORWARD=socks://*gwhost*:*gwport*[/*socksOpt*]-_-*:*dstHostList*:*srcHostList*

ssltunnel – forward to a SSL-tunnel (HTTP proxy with the CONNECT method)
:   [SSLTUNNEL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSLTUNNEL)=*gwhost*:*gwport*  
FORWARD=“ssltunnel://*gwhost*:*gwport*/-_-*:*:*”

direct – directly connect to the server
:   [CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT)=“direct:*protoList*:*dstHostList*:*srcHostList*”  
FORWARD=“direct-_-*protoList*:*dstHostList*:*srcHostList*”

noroute – don’t try connection to the server
:   [CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT)=“cache:*protoList*:*dstHostList*:*srcHostList*”  
FORWARD=“noroute-_-*protoList*:*dstHostList*:*srcHostList*”

If multiple FORWARD parameters are specified, they are tried in the order
of the definition.
If multiple routes to the destination server are available,
specified with a mixture of FORWARD and other parameters
(MASTER, PROXY, SOCKS or SSLTUNNEL),
the route defined by FORWARD is tried in precedence defined by “proxy” or
“master” in [CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT).

Example: a gateway for HTTP clients to a HTTPS server reachable via SSLtunnel with authentication

`MOUNT="/* https://sslhost/*"    STLS=fsv:https:sslhost   FORWARD=ssltunnel://user:pass@proxyhost:8080-_-https:sslhost`

```bash
ROUTE parameter*    ==  ROUTE=proto://host:port/-_-dstHostList:srcHostList
                    --  default: none
```

Forwards requests from hosts in *srcHostList*
to the resources listed in *dstHostList*
toward the server at *host*:*port*
in *proto* protocol.
ROUTE is a generalized notation for MASTER and PROXY.
MASTER=”*host*:*port*:*dstHostList*” is the abbreviation of
ROUTE=“delegate://*host*:*port*/-_-*dstHostList*:*”.
PROXY=”*host*:*port*:*dstHostList*”
with SERVER=*proto* is equals to
ROUTE=”*proto*://*host*:*port*/-_-*dstHostList*:*”.

A host specification in the *dstHostList* may be
prefixed with “*proto*://”
to restrict the protocol to be forwarded. For example,
ROUTE=“http://*host*:*port*/-_-{ftp://*}:*”
means that only access to FTP servers are forwarded
to the HTTP-proxy at “http://*host*:*port*/”.

A host specification in the *dstHostList* can be restricted further
with port number.
For example, ROUTE=“http://*host*:*port*/-_-{*:21}:*” means that
only accesses to the port number 21 (FTP service) is forwarded to the
proxy.

```bash
MASTER parameter*   ==  MASTER=host:port[/masterControl][:dstHostList]
                    --  default: none
```

This parameter specifies an upstream generalist DeleGate (MASTER-DeleGate)
to which this DeleGate will forward requests.
Forwarding to a MASTER-DeleGate can be filtered
by postfixing “:*dstHostList*”;
only request toward destination servers listed in *dstHostList* are
forwarded to the MASTER-DeleGate.
When multiple MASTERs are given, they are tried in order until connection
to a MASTER succeed.

Optional “/*masterControl*” can be:

cache – use the MASTER only if cache hits in the MASTER  
teleport – make a persistent *Teleport* connection to the MASTER

```bash
MASTERP parameter   ==  MASTERP=[host:port]
                    --  default: none
```

Invoke a MASTER-DeleGate private to this DeleGate.
HTTP-DeleGate working as a gateway to another protocol needs
MASTER-DeleGate to do *connection cache* for FTP and NNTP.
MASTERP may be specified with MASTER to force data caching at
the local host when the MASTER is running at a remote host.

```bash
RPORT parameter     ==  RPORT={tcp|udp}[:host]
                    --  default: none
```

This parameter should be used together with MASTER parameter.
If specified, a connection (for response data transfer) from the
MASTER-DeleGate to this DeleGate is established separately from the
connection (for request data transfer) from the DeleGate to its
MASTER-DeleGate. A specified type of response connection will be
made from the MASTER toward the delegate at the specified host.

```bash
PROXY parameter*    ==  PROXY=host:port[:dstHostList]
                    --  default: none
                    --  restriction: applicable to HTTP, FTP, Telnet
```

Specify an upstream proxy (specialist DeleGate or standard proxies)
to which the DeleGate should forward requests.
If *dstHostList* is specified, forwarding to the upstream proxy
is done only when the destination host is in the list.
Only HTTP, FTP, and Telnet specialist DeleGate can specify this parameter.

Example:

`SERVER=http PROXY=proxyhost:8080:!*.localdomain   SERVER=ftp PROXY=proxyhost:proxyport`

```bash
SOCKS parameter*    ==  SOCKS=host[:[port][/socksOpt][:dstHostList[:srcHostList]]]
          socksOpt  ==  [ -4 | -r ]*
                    --  default: none
```

Specify to use Socks server on *host*. The server is expected
to recognize Socks version 5 protocol. If the server supports only
version 4, specify “-4” option like “SOCKS=*host*:*port*/-4”.

The “-r” option controls which of DeleGate or Socks server does the name
resolution (from the host name of a target host to its IP address).
With a SocksV4 server, name resolution is done by DeleGate by default.
“-r” option make the resolution be delegated to the server
(This is applicable if the server supports extended Socks4A protocol).
With a SocksV5 server, name resolution is delegated to the server
by default, and “-r” option make the resolution be done locally by DeleGate.

By default, the connection establishment via Socks will be tried
after all of other trials failed, but you can control the order by
the[CONNECT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CONNECT) parameter.

If the *dstHostList* part is omitted, the default value for it is
“![.localnet](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#localnet)”. This default value can be changed
by redefining the named HostList “[.socksdst](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTLIST_predef)”
which is predefined as `HOSTLIST=".socksdst:!.localnet"`

Example:

`CONNECT=s,d SOCKS="sockshost:1080:!.localnet,!*.my.domain"`

```bash
SSLTUNNEL parameter ==  SSLTUNNEL=host:port
                    --  default: none
```

Use a HTTP proxy with the standard *SSL tunneling* feature
(on HTTP with CONNECT method)
running at *host*:*port* as a circuit level proxy
for target servers of arbitrary protocols.

```bash
VSAP parameter      ==  VSAP=host:port
                    --  default: none
```

Specify a VSAP server to be used for accepting from clients or for
connecting to clients. VSAP is a remote socket mapping server
which enables servers to accept a TCP connection via a remote host
as well as to connect via a remote host.

Example:

// VSAP server  
`firewall% delegated -P8000 SERVER=vsap PORT=8080-8090`
// accept via VSAP
to provide internal servers for external clients  
`internal% delegated -P8080@firewall:8000 ...`
// connect via VSAP,
working as a proxy server for internal clients  
`internal% delegated -P8080 CONNECT="{vsap/firewall:8000}" ...`
// accept and connect via VSAP server  
`internal% delegated -P8080 VSAP=firewall:8000 ...`

```bash
YYMUX parameter*    ==  YYMUX=host[:port][:connMap]
           connMap  ==  ProtoList[:dstHostList[:srcHostList]]
                    --  default: none
```

This parameter specifies a[YYMUX server](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_YYMUX)
to be used as an upstream proxy server of this DeleGate.
The connection established to the YYMUX server, to be used to
tunnel and multiplex TCP/IP connections over it, is retained
as if it is persistent.
If the tunnel is broken before the disconnection of the tunneled
TCP/IP connections, for example when the host of this DeleGate
changed its IP-address, the YYMUX tunnel is reconnected and
restored based on the resumption protocol of the YYMUX protocol.

```bash
YYCONF parameter*   ==  YYCONF=name[:value]
                    --  default: none
```

Example:

`YYMUX="HOME:/user/xxxx"   YYMUX="SHELL:/bin/csh -l"`

```bash
CONNECT parameter*  ==  CONNECT=connSeq[:connMap]
           connSeq  ==  connType[,connType]*
          connType  ==  cache|icp|proxy|master|https|vsap|direct|socks|udp
           connMap  ==  ProtoList[:dstHostList[:srcHostList]]
                    --  default: CONNECT="c,i,m,h,y,v,s,d:*:*:*"
```

This parameter controls the order of trials for connection to the
target server using several connection method as followings:

*connType*:

|      |                                                                                                 |
|------|-------------------------------------------------------------------------------------------------|
|cache |– CACHE search (without connection)                                                              |
|icp   |– via a PROXY hinted by ICP server                                                               |
|proxy |– via a PROXY server                                                                             |
|master|– via a PROXY or a MASTER-DeleGate server                                                        |
|https |– via a SSLTUNNEL (SSL tunnel on HTTP)                                                           |
|yymux |– via a [YYMUX](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#YYMUX) server|
|vsap  |– via a VSAP server                                                                              |
|direct|– direct connection to the target server                                                         |
|socks |– via SOCKS servers                                                                              |
|udp   |– by UDP                                                                                         |
|None  |– don’t connect                                                                                  |

Each connection type can be abbreviated by the first character as
{c,i,m,d,v,s,u} respectively.  
If ProtoList and dstHostList are given, this control is applied only
to the protocols and hosts included in the lists. For example,
to use cached data in a host which is not connected to external networks,
specify as CONNECT=“cache:*:!./@”.

Note:
In current implementation, “cache” will be tried first anyway if it is
included in the *connSeq*.

A combination of -P*port* with CONNECT=udp relays from TCP client
to UDP server,
and -P*port*/udp with non-udp CONNECT relays from UDP client
to TCP server.

```bash
SRCIF parameter*    ==  SRCIF=host[:[port][:connMap]]
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: SRCIF="*:*:*:*:*"
```

This parameter is useful for DeleGate running on a multi-homed host or
on a host behind a firewall with packet filtering.

This parameter specifies the source address (of a network interface) of each
connection to a server.
This can be useful when the host of DeleGate has multiple network interfaces.
Also it can be used to specify the port to be used for accepting
a client connection by a SOCKS-DeleGate or a FTP-DeleGate.

In most cases, a special pattern “*” as *host* or *port* specifies
the wild-card IP address or port number.
In some cases, the special pattern “*” is used for the desired address and number
which is specified by a protocol,
like a port for[FTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_FTP) data connection (by PORT or PASV)
or a port for [SOCKS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_Socks) (BIND and UDP-ASSOCIATE).
To explicitly specify the wild-card as an IP address and port number,
use “0.0.0.0” as *host* and “0” as *port* respectively.

Example:

`SRCIF="*:0:ftp-data"`
// use a random port number for FTP data connection  
`SRCIF="*:8020-8120:ftp-data"`
// use a port number in the specified range  
`SRCIF="150.29.202.120:*:tcpbind"`
// use the specified address to accept via SOCKS  
`SRCIF="150.29.202.120:*:udpbind"`
// use the specified address to relay UDP on SOCKS

The port for “ftp-data” connection which is assigned on demand and notified
to the peer,
that is from client to server by PORT or from server to client by PASV,
can be controlled separately by “ftp-data-port” or “ftp-data-pasv” respectively.
The source port for data connection, which is established from server to
client for PORT or from client to server for PASV,
can be controlled by “ftp-data-src”.

```bash
TUNNEL parameter    ==  TUNNEL=tunnelType:script
        tunnelType  ==  tty7
                    --  default: none
```

If specified, communication with an upstream DeleGate will be *tunneled*
via the standard input/output of the command.
The tunnel can be made of any kind of channel,
a raw serial line for example,
as long as it provides bi-directional transmission on it.
Possibly it may be the channel to the DeleGate
which will be invoked from inetd at remote host.

Currently, the *tunnelType* must be “tty7” which means
transmission between DeleGates is done in 7bits stream.
When the type is “tty7”, how the TUNNEL is established is described
in the specified *SHIO-script* file.
See “src/sample.shio” in the distribution package.
The name of a script file must be specified either in absolute path,
or in relative file name which will be retrieved in[LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH).
The upstream DeleGate for TUNNEL must be invoked with
`SERVER="tunnel1"`.

Example: make a tunnel without login dialogue

`TUNNEL=tty7:tunnel.shio`

[content of tunnel.shio]  
`o rsh host delegated SERVER=tunnel1\n   i READY\r\n   =`
Example: make a tunnel with login dialogue

`TUNNEL=tty7:tunnel.shio`

[content of tunnel.shio]  
`o telnet hostname\n   i login:    o username\n   i Password:   o password\n   i %    o delegated SERVER=tunnel1 \n   i READY\r   i \n   =`
As shown in above examples, the first line in a *SHIO-script* file is
expected to be a shell command like “o *command*\n” to establish a
connection to a remote server.
Another way to establish a connection is putting “c *host*:*port*”
on the first line. No shell nor shell command is invoked in this case.

```bash
PERMIT parameter*   ==  PERMIT=connMap
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
```

A PERMIT parameter specifies what kind of accesses should be
permitted by this DeleGate. An access will be permitted if the
access is from a client host included in *srcHostList*,
and to a server host included in *dstHostList*,
and with a protocol included in *ProtoList*.

If multiple PERMIT parameters are given,
an access will be permitted if at least one of
those PERMITs indicates permission.
If no PERMIT parameter is given, access permission is controlled
by REMITTABLE, REACHABLE and RELIABLE parameters which can be
defined explicitly or implicitly depending on SERVER parameter.

Example:
unlimited permission to hosts on local net while only <http://www> to others

`PERMIT="*:*:.localnet"   PERMIT="http:www:*"`

The special pattern “*” in *ProtoList* (*dstHostList*) means
all of permitted protocols (servers), which may be explicitly
defined with REMITTABLE (REACHABLE) parameters. These parameters
limits the widest possible permission. A protocol (server) is not permitted
if it is not permitted in REMITTABLE (REACHABLE) parameters defined
implicitly or explicitly.
Similarly, if more than one RELIABLE parameters are given explicitly,
they limit the widest acceptable clients in *srcHostList* of PERMIT.

The host specifications in the *dstHostList* can be further restricted
with port number like “*host*:*portNumList*”.
For example, PERMIT=“telnet:{*:23}:*” means permitting
telnet to any host but only on the standard port number (23).

A protocol name in the *ProtoList* can be modified with port number
and method like “*protocolName*/*portNumList*/*methodList*”
to restrict accessible ports and methods in the protocol.
For example, a series of PERMIT parameters,
PERMIT=“ftp//readonly:*Servers*:*Clients*”
PERMIT=“ftp:*:*”
means inhibiting uploading to *Servers* from *Clients*
while allowing uploading among other combinations of servers and clients.

When multiple DeleGate servers are chained using MASTER or PROXY
parameter, the original client identification information got at
the first DeleGate server (at the entrance of the chain) can be
forwarded to the upstream DeleGate server using [RIDENT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RIDENT)
parameter and will be examined using PERMIT parameter.

```bash
REJECT parameter*   ==  REJECT=connMap
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
```

REJECT parameter specifies what kind of access is to be rejected
in the same syntax with [PERMIT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PERMIT).
It can be more convenient than PERMIT
when cases to be rejected are exceptional and
are easier to describe than cases to be permitted.

Example:
forbid mail-clients to remove message on mail-servers

`REJECT="pop//DELE:mail-server:mail-client"   REJECT="imap//EXPUNGE:mail-server:mail-client"`

```bash
REMITTABLE parameter == REMITTABLE=ProtoList
                    --  default: REMITTABLE="*" for generalist
                    --  default: REMITTABLE="." for specialist
```

Only protocols (to the server) listed in *ProtoList* will be permitted
by this DeleGate.  
For generalist (a DeleGate with SERVER=“delegate” parameter) any
protocols are permitted by default. For specialist, only the protocol
specified in the SERVER parameter (which can be represented by “.”)
is permitted by default.

If a protocol name is followed by “/*portNumList*”,
only ports listed in
the PortList is permitted.
A *PortList* can be followed by “/*methodList*” which restricts
available methods in the protocol.
A pseudo method “readonly” is used to prohibit methods for modification.
For example, REMITTABLE=“ftp//readonly” make a FTP-DeleGate be
“read only” which inhibits uploading to FTP servers.

Protocol Specific Default:

generalist-DeleGate
:   REMITTABLE=”*” –
any protocol is remittable

HTTP-DeleGate
:   REMITTABLE=“http,https/{80,443},gopher,ftp,wais,cgi,ssi”
– usual protocols expected to be relayed by HTTP-proxies

Telnet-DeleGate
:   REMITTABLE=“telnet/23” –
restricted to be accessible only toward standard Telnet port (23).
This restriction can be disarmed by specifying like REMITTABLE=“telnet”.

Exception:

When the current destination server is determined by
a MOUNT parameter like
MOUNT=”*Path1* *Proto*://*Server*/*Path2*”,
the protocol *Proto* is automatically allowed as a destination
protocol with *Server*, regardless of REMITTABLE restriction.

If the first member of a list is “+”, it means the default list of
permitted protocols. For example, REMITTABLE=”+,-https/80,-wais,file”
with SERVER=http means REMITTABLE=“http,https/443,gopher,ftp,file”.

Note that “https” implies that non-HTTPS protocol on the SSLtunnel may
be detected and rejected.
If arbitrary protocol is to be relayed on the SSLtunnel,
specify “ssltunnel” instead of “https” like REMITTABLE=”+,ssltunnel”.

```bash
REACHABLE parameter* ==  REACHABLE=dstHostList
                    --  default: REACHABLE="*" (any host is reachable)
```

Only requests directed to the servers on the hosts (or networks)
listed in *dstHostList* will be accepted by the DeleGate.
When you use[multiple](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#multiRELIABLEs) REACHABLE parameters,
you must be certain of the meaning.

```bash
RELIABLE parameter* ==  RELIABLE=srcHostList
                    --  default: RELIABLE=".localnet"
```

Only requests sent from clients on hosts (or networks)
listed in *srcHostList*
will be accepted by the DeleGate.
By default, only accesses from client hosts on networks
local to the host of the DeleGate (.localnet)
are permitted.

Note that multiple RELIABLE parameters like
RELIABLE=*Hosts1* RELIABLE=*Hosts2* will be interpreted
being simply concatenated into a single RELIABLE=”*Hosts1*,*Hosts2*”,
which will NOT mean “*Hosts1 or Hosts2*”
if *Hosts1* or *Hosts2* includes some[negation](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostListNegation) or
[composite](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HostListComposite) operators.
You are recommended to use multiple PERMIT parameters instead
if you are not sure what does these mean.

```bash
RELAY parameter*    ==  RELAY=relayTypeList[:connMap]
     relayTypeList  ==  relayType[,relayType]*
         relayType  ==  proxy | delegate | vhost | no | nojava | noapplet
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: RELAY="delegate,nojava:*:*:.localnet"
                                 RELAY="vhost,nojava:http:{*:80}:.localnet"
                                 RELAY="proxy:*:*:*"
```

This parameter controls in which way the DeleGate works as a HTTP server.
DeleGate as a HTTP proxy server works in two ways (proxying modes):
as a standard (CERN compatible) HTTP proxy which accepts full URL
in a request (“proxy” *relayType*),
and as a DeleGate original proxy which accepts[/-_-*URL*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGproxy) in a request
and rewrites URLs in the response (“delegate” *relayType*).
In a full specification format with “:*connMap*”,
available proxying modes
can be classified by combination of server protocol, server host and
client host.

RELAY=“no” means working as an origin HTTP server without relaying
(Origin HTTP server is a usual server which accepts requests in usual
format, not in format for proxies, that is URL in request is neither
in full format nor in “/-_-” format, but in absolute format).

So called “transparent-proxy” ability is enabled by “RELAY=vhost”.
RELAY=“vhost” can be used for origin HTTP server with relaying to arbitrary
virtual hosts. This option enables a HTTP request to be forwarded to
arbitrary destination server, indicated in “Host:” field in request header,
without explicit MOUNT. This automatic relaying is done only when the
request URL is not MOUNTed, thus is not so likely because most DeleGate
working as origin server have MOUNT parameter for the root URL (”/*”).

With “nojava” combined with other *relayType*, <APPLET>,
<EMBED> and <OBJECT> tags relayed in the *relayType*
will be disabled (being replaced with <killed-*TagName*>).
With “noapplet”, only <APPLET> tags are disabled.
When the *relayType* “delegate” is enabled by a RELAY parameter,
using “nojava” like the default shown above is strongly recommended.

Example:

RELAY=no … do not work as a proxy (origin server only)

RELAY=proxy … CERN compatible mode only

RELAY=delegate … DeleGate mode only (/-_-URL)

RELAY=proxy,delegate … both CERN and DeleGate mode

RELAY=proxy,noapplet … inhibit <APPLET> tag to be relayed by proxy

Default:

Both “proxy” and “delegate” modes are allowed to users on “.localnet”,
while only “proxy” mode is allowed to other users.

```bash
SCREEN parameter ==  SCREEN={reject|accept}
                    --  default: none
```

This parameter enables dynamically updating the black/white list for
screening clients without restarting DeleGate.
SCREEN overrides other access control specified by RELIABLE or PERMIT.
In combination with “-Eri” option, the screening is done without starting
the interpritation of the application layer protocol.
“reject” indicates forbidding only client hosts listed in the list, while
“accept” indicates allowing only client hosts listed in the list.
The list is given as a text file including an IP-address or a MAC-address
per line.
With SCREEN=“reject”, the text file DGROOT/etc/hosts.d/reject.txt is seen.
With SCREEN=“accept”, the text file DGROOT/etc/hosts.d/accept.txt is seen.

Note: the arp command must be available by your DeleGate to use MAC-address
based screening.

```bash
AUTH parameter*     ==  AUTH=what:authProto:who
                    --  default: none
```

Authorize *who* to do *what*.
Authentication of user will be done using protocol specified in
*authProto*.
Identification about “*who the client’s user is*”
is done based on Identification protocol to the client host
if it supports the protocol.
Otherwise FTP-server may be used as an authentication server.

In HTTP-DeleGate, user declares “*who am i*” giving an
Authorization header (in request message), which consists of
*Username*:*Password*,
where *Username* can be in a form of *User*@*Host*.

Given a set of *User*, *Host* and *Password*,
DeleGate tries to login to the (FTP) server on *Host*
with *User* and *Password*.
If succeed, then the client is authenticated to be
*User*@*Host*.

Currently following categories of authentication/authorization
are supported:

– in any protocol DeleGate –

AUTH=“admin[:*authServ*[:[*listOfUsers*][:*listOfHosts*]]]”
:   Enables the remote configuration and administration of DeleGate via
HTTP (or HTTPS) at “http://*delegateHost*:*Port*/-/admin/”.
It allows a user to do remote administration
if the user is authenticated with[*authServ*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authServ),
and if the user is in *listOfUsers*. For example,
`AUTH=admin:-pam:user` authorizes the *user* if
authenticated with PAM.
`AUTH=admin` is the abbreviation of `AUTH="admin:-pam:%O"`
where “%O” represents the owner of this DeleGate process.
Empty *authServ* as
`AUTH=admin::user:pass` means authorizing
the username *user* with password *pass*.
If “:*listOfHosts*” is specified, users to be authorized must access
from a client hosts in the list.

```
A DeleGate of arbitrary protocol (regardless of SERVER=*protocol*)
can have a port for remote administration
by specifying a port devoted to administration with "/admin" modifier like
"-P*userPort*,*adminPort*/admin" option.
  
Example:

`SERVER=pop -P110,9110/admin AUTH=admin::admin:password`  
The URL for remote administration of this DeleGate (as a POP proxy) is
"https://*delegateHost*:9110/-/admin/"
```

– in FTP server and FTP/HTTP gateway –

AUTH=“anonftp:*:*passWord*”
:   If specified, A DeleGate forwards E-mail address of a client’s user
(which is declared by the user) to the target FTP server as an
anonymous password.
Without this AUTH, HTTP-DeleGate will send ADMIN’s E-mail address
by default.

```
The E-mail address must be in the form of *user*@*host*,
otherwise (if the *host* part is not given) the FTP login is
rejected by DeleGate.
  
HTTP-DeleGate asks anonymous users to declare his/her E-mail address
as *Username* part in Authorization.
If *passWord* field is specified as "\*" (i.e. AUTH="anonftp:\*:\*"),
then any *Password* in the Authorization will be acceptable.  
In FTP-DeleGate, the E-mail address must be given as a password (in PASS
command) for the anonymous user, and the password is used for matching
with *passWord* too.
  
The second field must be "\*" in current implementation.
```

AUTH=“anonftp:smtp-vrfy:*”
:   If specified, DeleGate verifies (using the SMTP protocol) the validity
of E-mail address given by anonymous users.
In HTTP-DeleGate, the E-mail address must be given as *Username*
part in Authorization.
In FTP-Delegate, it must be given as a password for the anonymous
user.
With this AUTH, invalid E-mail addresses can be rejected.
When the address is valid but is in a format like “*user*@*host*”,
it will be expanded automatically to a FQDN format like
“[user@host.domain](mailto:user@host.domain)”.  
If the third field is “-” (i.e. AUTH=“anonftp:smtp-vrfy:-@*”)
only the connectivity to mail server at “host.domain” is checked.

– in proxy and origin HTTP server –

AUTH=proxy:{ident|auth|pauth}
:   Specify identification/authorization protocols for the
DeleGate as a HTTP proxy server.
This parameter is checked only when access control for user
is specified in PERMIT or RELIABLE.

```
|  |  |
| --- | --- |
| ident | -- Identification protocol [default] |
| pauth | -- Use Proxy-Authorization field "user@host:password" |
| auth | -- Use Authorization field "user@host:password" |


Example:

`AUTH=proxy:auth PERMIT="*:*:{*,!?}@*"`
// Any user at any host is allowed as long as he/she is identified.
Note:

When the client does not support Proxy-Authentication,
you are obliged to use "proxy:auth" for Authentication.
In such case, note that the client cannot access
resources which requires Authentication.
```

In the case where the FTP-server based authentication is used,
a recommended user name of the authorization information is
e-mail address like “*user*@*host*.*domain*”
so that it can be commonly used for both AUTH=“anonftp” and AUTH=“proxy”.

```bash
AUTHORIZER parameter* ==  AUTHORIZER=authServList[@realmValue][:connMap]
       authServList  ==  [authForw,]authServ[,authServ]* | & | *
           authForw  ==  -map{inPat}{localPat}{fwdPat} | -strip | -fwd
           authServ  ==  authHost[/portNum][(reprUser)]
           authHost  ==  hostName | hostAddr
         realmValue  ==  word | {words separated with space}
            connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
                    --  restriction: applicable to Telnet, FTP, NNTP, SMTP, IMAP,
                                     Socks, SockMux, and HTTP
```

Specify the server for authentication and authorization (“auth-server”).
If specified, an access by a client is not permitted without
authenticated successfully by the auth-server,
sending an appropriate pair of user-name and pass-word
over the application protocol.
Two special *authServ* “-none” and “-never” are exceptions
to make authentication unnecessary.
If *authServ* is followed by “(*reprUser*)”, the users
successfully authenticated in the *authServ* are represented by
*reprUser* as a representative user.

Note that even a client authorized by an auth-server is not permitted
if the client’s host does not pass other access controls
([RELIABLE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELIABLE) and [PERMIT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PERMIT)).
To permit any authorized client regardless of its host, specify as
RELIABLE=”[-a/](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#iType)*”. Also RELIABLE=”*” works for this purpose
but is not safe on modifications of configuration and DeleGate.

Adding *connMap*, an auth-server can be selected conditionally on
a combination of destination protocol, server host and client host.
The *authServList* is a host name of authentication server, or a
list of host names of authentication servers.
If *authServList* is followed with “@*realmValue*”, the value is
used to define the realm of protection space in HTTP-DeleGate.
It can be overridden by MountOption “realm=realmValue” for each MOUNT point.

Currently, the default protocol of remote authentication/authorization server
is that of FTP protocol with USER and PASS commands. Thus any real FTP
server can be used as an authentication/authorization server of DeleGate.
Another way of maintaining DeleGate’s own lists for
authentication/authorization is using
[-Fauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#func_auth) function.

There are built-in auth-servers to be used as *authServ* as follows:

`-none` – allow without caring if authentication is given or not

`-never` – disallow without careing if authentication is given or not

`-any` – any combination of username + password is acceptable

`-anonftp` – username is “ftp” or “anonymous” and password includes “@”

`-dgauth[.realm]` – password is sent safely as a digest (HTTP and APOP)

`-pam/service` – username + password is checked by PAM

`-list{user:pass,...}` – the pair of username and password is in the list

`-userpass/user/pass` – equivalent to `-list{user:pass}`

`-hostlist/ListName` – client’s host is in the HOSTLIST=*ListName*:*HostList*

`-fail.badpass` – disallow if the username exists but password is wrong

`-fail.nopass` – disallow if password is not given or empty

`-cmd{cmd arg ...}{ENV=val ...}` – external command for authentication

`-ntht` – NTLM over HTTP (Win32 only)

`-login` – logon to the local host (Win32 only)

`-man` – manual authentication on demand

DGAuth: `-dgauth[.realm][{user:pass,...}]`:   Authentication scheme based on digested password, specific to each
application protocol, is enabled with “AUTHORIZER=-dgauth”.
This kind of authentication scheme,
at least APOP proxy or HTTP Digest/Basic gateway does,
requires the original cleartext of password.
A simple way to do so is giving directly a list of pairs of username
and password as
`-dgauth{user1:pass1,user2:pass2,...}`.
Another way is storing passwords by DeleGate with
`"-Fauth -a username:password -dgauth"`.
Since passwords for -dgauth is stored in encrypted form, a keyword is
required for the encryption.
Specify the keyword as CRYPT=pass:*keyword*
or answer it interactively afterwards.
Otherwise, DGAuth can be delegated to a remote[DGAuth server](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_DGAuth).
DGAuth generates a session identifier which is retained identically
during the session started by an authentication,
then passed to CFI/CGI programs in environment variable “X_DIGEST_SESSION”
and can be logged into [PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#http_session_log).

```
Example:

// a HTTP proxy or server with the Digest authentication with clients.  
`SERVER=http AUTHORIZER=-dgauth`  
// a POP proxy which uses APOP authentication with clients.  
`SERVER=pop MOUNT="* pop://server/*" AUTHORIZER=-dgauth`
```

PAM: `-pam[/service]`
:   On platforms where PAM (Pluggable Authentication Modules) is available,
it can be used for authentication with the syntax
`AUTHORIZER="-pam/service"`,
for example as AUTHORIZER=”-pam/passwd”, AUTHORIZER=”-pam/ftp” and so on.

```
Note that most of PAM authentications need to be executed under the
privilege of superuser on Unix (with OWNER="root" option).
But you can avoid running your DeleGate with superuser privilege by
installing external program "dgpam" under [DGROOT/subin/](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#subin).
Also PAM authentication can be delegated to a remote
[PAM server](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_PAM).
```

LIST: `-list{user[:pass],...}`
:   An element of the list can be *user* only without “:*pass*”
which means matching *user* name only and don’t care the password.
In the “-list{*user*:*pass*,…}”, substitution by
“[[date+*format*]](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#aging)”
can be used in *user* and *pass*.
For example, AUTHORIZER=”-list{guest:[date+%y%m]}” means accepting
usrename “guest” with password “0405” in May 2004.

```
Example:

`AUTHORIZER="-list{u1:p1,u2:p2}(local),-pam,-none(anonymous)"`
  
// a user may be authenticated as "local" or as some user name in PAM,  
// or "anonymous" otherwise
```

CMD: `-cmd{cmd arg ...}[{ENV=val ...}[{input-pattern}]]`
:   Do the authentication with an external command *cmd*.
Values to be used the authentication to be passed to the command is
specified with the format as “%[format](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen)”
like `%U` for username and `%P` for password.
A parameter can be passed in command-line argument,
in environment variable or in the standard input of the command.
If the environment and *input-pattern* is omitted as
`AUTHORIZER="-cmd{cmd}`,
the pair of user name and password is passed by default
as if implicitly specified as
`AUTHORIZER="-cmd{cmd}{DG_USER=%U DG_PASS=%P}{USER %U\nPASS %P\n}`”.

```
The result of the authentication by the command is shown in its output string
or by its exit code.
The command may puts a string to its standard output to show the result
in the form of a status response of the FTP protocol, that is,
"230" for success and "530" for failure.
Otherwise the exit code of the process is used, the value zero for success
and non-zero values for failure.

Example: passing username in argument while password in environment variable

`AUTHORIZER="-cmd{myauth %U}{MYPASS=%P}"`

[the content of the `myauth` command]
  
`#!/bin/sh  
if [ "$1" = "user1" -a "$MYPASS" = "pass1" ]; then  
  echo "230 SUCCESS"  
else  
  echo "530 FAILURE"  
fi`
```

AUTHFORW: `-map{inPat}{localPat}{fwdPat} | -strip | -fwd`:   (available only in FTP and POP currently)  
The “-map” prefix is used to split incoming authentication information
of USER and PASS (in *inPat* pattern) into a pair of authentications,
the one to be used locally by *authServList* (in *localPat*) and
another to be forwarded to the server (in *fwdPat*).
Each authentication information to be matched or generated is represented
by a string of a pair of a user name and a password as
“*username*:*password*”.
If the username string generated by *fwdPat* ends with a substring as
“@*Host*” then it is striped and the *Host* is used as
the destination server.
The string is matched and generated by the pattern specification format
common to the one used for pattern matching in the[MOUNT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountComplex) parameter.

```
Example: -strip



`1A) AUTHORIZER="-map{%S@%S:%S@%S}{%(0):%(2)}{%(1):%(3)},-list{u1:p1},-pam"`

`1B) AUTHORIZER="-strip,-list{u1:p1},-pam"` ## equiv. to the above
:   incoming auth. <-- USER user1@user2@host2 + PASS pass1@pass2  
    local auth. by u1 or PAM <-- USER user1 + PASS pass1  
    outgoing to the server h2 <-- USER user2 + PASS pass2


Example: -fwd



`2A) AUTHORIZER="-map{%S:%S}{%S:%S}{%S:%S},-list{u1:p1},-pam"`

`2B) AUTHORIZER="-fwd,-list{u1:p1},-pam"` ## equiv. to the above


Example:



`3A) AUTHORIZER="-map{%S}{%S}{},-list{u1:p1},-pam"`

`3B) AUTHORIZER="-list{u1:p1},-pam"` ## equiv. to the above


As shown in the above example 1),
`"-strip"` is used to support a nested username and password
as USER "u1@u2@u3@h3@h2@h1" and PASS "p1@p2@p3".
It strips the first element before '@' in the USER and PASS to be used
for local authentication, strips the last element after '@' in USER as
the destination server, then forwards remaining string
to the destination server.
`"-fwd"` specifies to use the same USER and PASS both for the
local authentication and the authentication with a server.
```

If only authentication of user is necessary without authorization,
the following special name will be useful as a *authServList*.

“&” – the client host (user name on the client host is required)  
“*” – any *authHost* specified by the client as “*user*@*authHost*”

Example:

// clients from outside of local.domain is required authentication  
`SERVER=telnet AUTHORIZER="&:::!*.local.domain"`
// any clients is allowed if the user is authenticated with localhost  
`SERVER=telnet AUTHORIZER="localhost" RELIABLE="*"`
// using DeleGate’s own list of “-socksusers” maintained with
“[-Fauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#func_auth)”  
`SERVER=socks AUTHORIZER=-socks.users`

```bash
MYAUTH parameter*   ==  MYAUTH=username:password[:connMap]
                    --  default: none
                    --  restriction: applicable to Socks, VSAP, SMTP, and HTTP
```

Specify authorization information to be sent to an upstream server/proxy.
Special characters in *username* or *password* must be escaped
with “%*XX*” where *XX* is hexadecimal representation of
a character code (see ascii(7)).
Special characters to be escaped are:
TAB (”%09”), SPACE (”%20”), ‘”’ (”%22”), ‘%’ (”%25”), ‘:’ (”%3A”),
‘{’ (”%7B”), and ‘}’ (”%7D”).

The pair of username+password which is sent from a client can be forwarded
to the server by MYAUTH=”[%U:%P](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen)”
(supported in HTTP and FTP only).

NOTE:
For authentication with proxies, it is strongly recommended to use
[FORWARD](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FORWARD) with a gateway-URL including
authentication information instead of MYAUTH.
For example,
`SOCKS=host:port` with `MYAUTH=user:pass`
can be represented as
`FORWARD=socks://user:pass@host:port`.

Example:

`MYAUTH=userS:passS:socks   MYAUTH=userV:passV:vsap   MYAUTH=userM:passM:smtp:smtpserverM   MYAUTH=userH:passH:http:httpserverH   MYAUTH=userP:passP:http-proxy:httpproxyP`

```bash
RIDENT parameter    ==  RIDENT=ridentType[,ridentType]*
       ridentType   ==  client | server
                    --  default: none
```

If RIDENT=“server” is specified, identification information about the
client socket got by getsockname(2) and getpeername(2) will be
forwarded to the PROXY or MASTER-DeleGate which will receive the
information by RIDENT=“client”, and will use it for access control.
A DeleGate server with RIDENT=“client” can accept both from DeleGate
with RIDENT=“server” and other proxy servers with no RIDENT support.
An intermediate DeleGate in a chain of cascaded DeleGate servers
should be given RIDENT=“client,server”.

Example:

`host1# delegated -P8080 RIDENT=server MASTER=host2:8080   host2# delegated -P8080 RIDENT=client`

```bash
MAXIMA parameter*   ==  MAXIMA=what:number,...
                    --  default: MAXIMA=listen:20,ftpcc:2,...
```

Specify the maximum number of resource usage, processes, connections, etc.

|                                                                                        | |                                                                                                                             |
|----------------------------------------------------------------------------------------|-|-----------------------------------------------------------------------------------------------------------------------------|
|[randstack](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense)|–|randomization range of stack base for security [32]                                                                          |
|randenv                                                                                 |–|randomization range of environment variables base [1024]                                                                     |
|randfd                                                                                  |–|randomization range of client socket file-descriptor [32]                                                                    |
|listen                                                                                  |–|max. size of the queue for [entrance](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#entrance) port [20]|
|delegated                                                                               |–|max. number of DeleGate processes runnable at a time [64]                                                                    |
|service                                                                                 |–|max. number of services per delegated process [unlimited]                                                                    |
|standby                                                                                 |–|max. number of standby process [32]                                                                                          |
|conpch                                                                                  |–|max. number of connections at a time per client host [unlimited]                                                             |
|ftpcc                                                                                   |–|max. number of FTP connection cache servers to a host [16]                                                                   |
|nntpcc                                                                                  |–|max. number of NNTP connection cache processes to a host[16]                                                                 |
|http-cka                                                                                |–|(replaced by HTTPCONF=[max-cka)](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#max-cka)                |
|http-ckapch                                                                             |–|(replaced by HTTPCONF=[max-ckapch](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#max-ckapch))          |
|udprelay                                                                                |–|max. number of parallel UDPrelay client [32]                                                                                 |
|winmtu                                                                                  |–|max. unit of send() on Win32 [1024]                                                                                          |

```bash
TIMEOUT parameter*  ==  TIMEOUT=what:seconds,...
                    --  default: TIMEOUT=dns:10,acc:10,con:10,lin:30,...
```

Specify timeout period (in seconds by default) of *what*.The timeout value “0” means “*never timeout*” (unlimited).
The unit of period is second by default,
but can be changed like 1d(day), 1h(hour), 1m(minute).

|                                                                                      | |                                                                                                                                                                        |
|--------------------------------------------------------------------------------------|-|------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|[shutout](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense)|–|disarming emergent shutout set on fatal error [1800]                                                                                                                    |
|dns                                                                                   |–|for DNS lookup [10]                                                                                                                                                     |
|dnsinv                                                                                |–|for DNS inverse lookup [6]                                                                                                                                              |
|nis                                                                                   |–|for NIS lookup [3]                                                                                                                                                      |
|acc                                                                                   |–|for accept from client (include FTP data connection) [10]                                                                                                               |
|con                                                                                   |–|for connection to the server [10]                                                                                                                                       |
|lin                                                                                   |–|LINGER for output [30]                                                                                                                                                  |
|authorizer                                                                            |–|expiration of authorization by [AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER) [unlimited]                                 |
|dgnonce                                                                               |–|for AUTHORIZER=[-dgauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#dgauth) (lifetime of “nonce”) [60]                                         |
|ident                                                                                 |–|for connection to Ident server [1]                                                                                                                                      |
|rident                                                                                |–|for receiving [RIDENT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RIDENT)=client info. [1.0]                                                   |
|io                                                                                    |–|general I/O (no data transmission) [600]                                                                                                                                |
|silence                                                                               |–|no data transmission either from client or server [0] (applicable only to [tcprelay](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_tcprelay))|
|hello                                                                                 |–|for HELLO negotiation with the MASTER [30]                                                                                                                              |
|login                                                                                 |–|for login to proxy (Telnet,FTP,SOCKS) [60]                                                                                                                              |
|daemon                                                                                |–|delegated [unlimited]                                                                                                                                                   |
|restart                                                                               |–|cause [restart](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESTART) at every specified period [unlimited]                                      |
|standby                                                                               |–|keep the delegated alive on standby for next client [30]                                                                                                                |
|takeover                                                                              |–|taking over a downloading to cache after client’s disconnection [5]  (after the disconnection of the client which initiated the downloading)                            |
|ftpcc                                                                                 |–|for keeping alive FTP Connection Cache [120]                                                                                                                            |
|nntpcc                                                                                |–|for keeping alive NNTP Connection Cache [300]                                                                                                                           |
|http-cka                                                                              |–|(replaced by HTTPCONF=[tout-cka](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#tout-cka))                                                         |
|cfistat                                                                               |–|for status information from [-s](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#cfistat),filter [1.0]                                              |

```bash
DELAY parameter*    ==  DELAY=what:seconds
                    --  default: DELAY=reject:60,unknown:60,...
```

Delay for specified seconds before doing *what*.

|         | |                                                          |
|---------|-|----------------------------------------------------------|
|reject   |–|continuous Reject resp. from self or MOUNTed servers [60] |
|unknown  |–|continuous Unknown resp. from self or MOUNTed servers [60]|
|reject_p |–|continuous Reject resp. from origin server [0]            |
|unknown_p|–|continuous Unknown resp. from origin server [0]           |

Each value specifies the maximum delay time and delay time increases
according as the error count increases.

```bash
CHOKE parameter*    ==  CHOKE=Choking:Client:Ua:Referer:Url:Server:Protocol
                    --  default: none
```

This parameter integrates clients-choking functions
scattered around parameters and options including
DELAY, MAXIMA, MOUNT, RELIABLE, SCREEN, and -Eri.
It is mainly intended to choke robots, spammers and attackers,
but can be applied generally to any clients.

At the first field, *Choking* specifies restriction to be applied
to a request.
Following fields specifies a set of conditions to detect requests
to which the *Choking* is applied.
A *Choking* is applied when all of conditions match the specified
conditions (to be combined by AND operation).
All of condition fields can be empty and an empty filed is regarded as matched.
A series of empty conditions to the end can be omitted.

Multiple CHOKE parameters can be specified and are combined by OR operation.
CHOKE parameters are scanned in the specified order and the scanning
stops at the firstly matched CHOKE.

To test if CHOKE parameters work as intended, an option “-Fchoke” is provided. It is applied to[PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROTOLOG) file in an [extended common logfile format](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httplog) (extended by “%X” to record Referer and User-Agent). For example it is used as bellow:
:   `% delegated CHOKE=... -Fchoke < 80.http`

At the beginning of each line in output, “-Fchoke” inserts the result of robot detection and access control.

“-Fchoke” with “-sa” option simulates access control parameters including CHOKE, RELIABLE, REACHABLE, REMITTABLE, PERMIT, REJECT, and SCREEN.
:   `% delegated RELIABLE=... REACHABLE=... CHOKE=... -Fchoke -sa < 80.http`

```bash
MOUNT parameter*    ==  MOUNT="vURL rURL [MountOptions]"
                    --  default: MOUNT="/* SERVER_URL*"
```

Map *vURL* to/from the *rURL*.
URLs matches with *vURL* in a request message from a client
are rewritten to *rURL* and forwarded to a server, and
URLs matches with *rURL* in a response message from the server
is rewritten to *vURL* and forwarded to the client.
What is rewritten by MOUNT in each protocol is like follows:

[HTTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTTP_mount) – URL or part of it appeared in header or HTML body (tags)

[FTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FTP_MOUNT) – file name in command and status response

[NNTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#NNTP_mount) – newsgroup name in command, status response, and user data (header)

POP – user and host name in USER,PASS,APOP command

IMAP – user and host name in LOGIN command

SMTP – mail address in the RCPT command

Telnet – hostname and port number of destination server

[LDAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LDAP_MOUNT) – base object name in requests/responses

If a *vURL* is terminated with “*”
then partially matched path is also rewritten.
If a *rURL* is terminated with “*” then remaining part
in the partially matched path will be copied after the *rURL*.

Example: a MOUNT for HTTP-DeleGate

`MOUNT="/abc/* http://host/*"`
// rewrites “/abc/def” to/from “http://*host*/def”

If “=” is specified as *vURL* or *rURL*,
it means mount *as is* without
rewriting for the *vURL* in a request,
or rewriting for *rURL* in a response.

The port number of the destination server (in *rURL*)
can be prefixed with “-” or “+”
to be determined dynamically
by offsetting from the port number of the entransport,
as in [SERVER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#portmap) parameter.

A special host name `"odst.-"` in *rURL* (or in the SERVER
parameter) represents the original destination host of the TCP connection
from the client via NAT (provided by iptables on Linux).
It can be used to configure a transparent proxy (or gateway)
for arbitrary protocols.
The original destination port number can be referred with “-” as “odst.-:-”.
The number can be mapped with an offset value as “-8000” or “+8000” for example.
The name “odst.-” can be used in the “[rserv](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#nvserv)” MountOption
too.

If the *rURL* is of “file:*path*” and the *path* is
a relative one, then the data file is searched under the
[DGROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT) directory or directories listed in
[DATAPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DATAPATH).

If a *rURL* is prefixed as “`vurl:`*rURL*”, the rewritten
URL (in a request message) from *vURL* to *rURL* will be
rewritten by another MOUNT again.
This recursive MOUNT is not applied to the rewriting a URL in response data
from *rURL* to *vURL*,
therefore it does not work as expected in HTTP where such reverse rewriting
of URL in response is expected too.

Example: recursive MOUNT

`MOUNT="/x/* vurl:/f/x/*"   MOUNT="/y/* vurl:/f/y/*"   MOUNT="/f/* ftp://server/*"`
// “`/x/path`” is rewritten to “`ftp://server/x/path`”  
// “`ftp://server/x/path`” is rewritten to “`/f/x/path`”

**Abbreviations**

To make configurations be simple and reusable, special abbreviated
formats of URL can be used in MOUNT parameter.
If “=” is specified as *protocol-name*, *host-name*
or *port-number* in *rURL* which consists of
*protocol-name*://*host-name*:*port-number*/*url-path*,
then it represents that of the DeleGate itself (i.e. that of *vURL*).
URLs beginning with “//” represents further abbreviations,
“///*path*” for “=://=:=/*path*” (in the same protocol,host and port)
and
“//*serv*…” for “=://*serv*…” (in the same protocol).

Abbreviated *host-name* and *port-number* is substituted by
that of the virtual host (given in HTTP Host: field) if exists,
or by that of the real interface with the client.
To explicitly specify the real interface, use “-P” for
“*host-name*:*port-number* part like “http://-P/*path*”.

Example: abbreviation in *rURL* of MOUNT parameter

// DeleGate’s parameters: SERVER=http -Pdhost:9080 …  
// Requested URL: <http://vhost:9080/x/>  
`MOUNT="/x/* =://=:=/y/*" -> http://vhost:9080/y/    MOUNT="/x/* ///y/*" -> (the abbreviation of the above)    MOUNT="/x/* //-P/y/*" -> http://dhost:9080/y/    MOUNT="/x/* =://serv/y/*" -> http://serv:80/y/    MOUNT="/x/* //serv/y/*" -> (the abbreviation of the above)    MOUNT="/x/* //serv:=/y/*" -> http://serv:9080/y/    MOUNT="/x/* //=:9088/y/*" -> http://vhost:9088/y/    MOUNT="/x/* https://=/y/*" -> https://vhost:443/y/`
**Complex Matching and Rewriting**

A pattern following “*%” in *vURL* and *rURL* represents
a pattern for complex matching specified in the format like that of scanf(3).
Each format specification consists of a specification following “%”,
like “%c”, “%[a-z]” and so on.
The extended format “%S” has variable meanings determined by its
adjacent character, i.e. “%S*x*” means “%[^*x*]*x*”:
ex. “%S.” for “%[^.].” and “%S/” for “%[^/]/”.
“%(*N*)” in *rURL* means copying *N*th element in
*vURL*.
If a *vURL* pattern ends with “$” character, then complete
matching to the end of URL string is required.

Example: complex matching and rewriting

`// Requested URL: http://dhost/x/abc/def    MOUNT="/x/*%S/%S ///y/*%S.%S" -> http://dhost/y/abc.def    MOUNT="/x/*%S/%S ///y/*%(1)/%(0)" -> http://dhost/y/def/abc    MOUNT="/x/*%1[a-z]%S http://w/*%S/%S" -> http://w/a/bc/def`

```bash
MountOptions == option[,option]*
```

MountOptions is a list of options, to make MOUNT be conditional,
or to apply some functions only to MOUNTed URLs.
Some of them are common to any protocol
and others are specific to a protocol ([HTTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HTTP_mount),
[NNTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#NNTP_mount)
).

**CONDITIONS:**

The first group of options are to make MOUNT be conditional
depending on source and destination (client and server).
When a MOUNT parameter have a *MountOption*
including one or more conditions,
the MOUNT will be ignored without all of conditions are true.

from={*HostList*} – from the client.
:   true if the client is included in the *HostList*.

via={*HostList*} – via the host.
:   true if at least one host passed through on the way
is included in the *HostList*.

path={*HostList*} – through the hosts.
:   true if all of hosts passed through is included in the *HostList*.

auth={*HostList*} – authorized by the host.
:   true if a password based authentication succeeded with a
[AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER) host listed in the *HostList*.

withssl
:   true if the client-side connection is encrypted with SSL or TLS

sni={*HostList*} – name based virtual hosting based on SNI/TLS
:   true if the TLS client connected to the DeleGate with the hostname
(server name indicated in TLS protocol) included in *HostList*.
host={*HostList*} – interface host with the client.
:   true if the client has connected to the DeleGate via the specified network
interface included in the *HostList*.  
Note that this option is applicable to any client side protocol, that is,
not only HTTP-DeleGate but also DeleGate for FTP, POP, NNTP, etc. can
switch destination server based on the client side interface if
its has an IP address distinguishable from others.  
When the DeleGate is acting as an origin HTTP server and a virtual
host name is shown in “Host: host” field in the request message,
the virtual name is examined prior to the real host name. If
multiple virtual names are bound to the same IP-address,
prefix “-” to the virtual hostname like “host=-hostname” to
distinguish among virtual names.
odst={*HostList*} – NAT based virtual hosting:   true if the original destination of the TCP connection from the client
is included in the *HostList*. This option is available on Linux
with NAT (by iptables) on Linux.
The original destination can be used as the real destination with a
special host name “[odst.-](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#odst.-)”.

dst={*HostList*} – to the server.
:   true if the destination host is included in the *HostList*.
This option will be useful when “=” is used
as the right hand of MOUNT.

udst={*HostList*}
:   true if the host in the site part of a full-URL (as <http://site/path>)
is included in the *HostList*.
This option will be used with the “referer” MountOption to rewrite URL
in the “Referer” field.

direction=*Direction* – request or response
:   true when the MOUNT parameter is applied to specified *Direction*
which is one of followings:

```
fo -- apply forward (request rewriting) only

bo -- apply backward (response rewriting) only

bif -- apply backward if it was applied forward
```

-f,*conditionList* – conditions applied only in request rewriting

-b,*conditionList* – conditions applied only in response rewriting

-f.*condition* – a condition applied only in request rewriting

-b.*condition* – a condition applied only in response rewriting

-x.*condition* – a condition to be applied to both directions
:   “avhost” and “nvhost” are conditions tested only in request rewriting
by default. These conditions come to be tested also in response rewriting
by prefixing “-x.” as “-x.nvhost=*host*”.

pri=*signedFloatNumber* – priority of this MOUNT parameter
:   a MOUNT parameter with larger priority value is tested prior to
another with lower priority. The default priority value is zero.

nocase – ignore character case in URL path matching

These *HostList* should be a list of *host*:*port*,
where :*port* part can be omitted when it is not to be cared.
The *host* part can be represented as “*”
when the difference of network interface is not to be cared.

Example:

// switch MOUNT depending on from which interface the client is  
`MOUNT="* URL1 host=this-host"   MOUNT="* URL2 host=localhost"`
// switch MOUNT depending on from which port the client is  
`-P70,80   MOUNT="* URL1 host=*:70"   MOUNT="* URL2 host=*:80"`

**CONTROLS**:

The second group of options are to control the behaviors of DeleGate
which are local to the MOUNT point.

public – allow public access
:   do not apply any access restriction (by [PERMIT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PERMIT) etc.)
to this MOUNT point.

rident[=no] – forward [RIDENT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RIDENT) information to server
:   forward (or stop forwarding) RIDENT information to the MOUNTed server
regardless of the RIDENT=server parameter.

ro – allow read only.
:   applicable to NNTP (inhibit POST command) and origin FTP (default).

rw – allow both read and write.
:   allow origin FTP-DeleGate to write to its local files.

cache=no – disable cache.
:   disable any usage of cache for the server of this MOUNT point.

expire=*period* – validity of cache
:   expire period of the MOUNT point, overriding the global
[EXPIRE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#EXPIRE) parameter.

expires=*period* – validity of each response
:   if specified, “Expires:” field is added into each HTTP response message.
If the *period* begins with ‘+’ or ‘-’, like “expire=+1d”, and if
the original message has “Expires:” header, then the expire date is
relative to the original expiration date.

ftocl=*filterCommand* – apply external filter
:   apply the filter to the MOUNT point,
overriding the global [FTOCL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#FTOCL) parameter.

charcode=*charCode* – code conversion.
:   code conversion specific to this mount point,
overriding the global [CHARCODE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARCODE) parameter.
proxy=*host*:*port* – upstream proxy server

master=*host*:*port* – upstream MASTER-DeleGate:   use an upstream proxy server for the MOUNT point,
instead of the one specified in the global[MASTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTER) or
[PROXY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROXY) parameter.

MAXIMA=bps:*speed* – maximum transmission speed
:   choke the speed of the date transmission (HTTP and FTP) as
MAXIMA=bps:128k for example.

```bash
URICONV parameter*  ==  URICONV={convSpec|defElem|defAttr}
          convSpec  ==  convList:attrList
           defElem  ==  defelem:+,elemnameList
           defAttr  ==  defattr:+,attrnameList
                    --  default: it will be shown by URICONV=dump
```

Specify which kind of URI rewriting should be applied to which kind
of attributes of tags in HTML document. The *convList* is a list of
following items.

|       | |                                                      |
|-------|-|------------------------------------------------------|
|mount  |–|rewriting by MOUNT                                    |
|normal |–|normalize MOUNTed URL if it includes “../” in URL-path|
|partial|–|represent (MOUNTed) URLs as partial URLs if possible  |
|full   |–|convert all of URLs to full URLs                      |

The special *convList* URICONV=”+” means loading the default URICONV
configuration (no *attrList* in this case in the current implementation).
The *attrList* is a list of attributes names each may be postfixed
with an element name. A special attributes name “+” means the
default set of attributes. An attribute prefixed with “-”
character is excluded from the calculated set of attributes.

Another special *convList* URICONV=“where:any” enables searching URL
to be rewritten not only in HTML tags but also
in XML, JavaScript, CSS (Cascading Style Sheets) and SWF (Shockwave Flush).

Example:

URICONV=mount,normal,partial:+ – might be the default after Ver.6  
URICONV=full:+,-HREF/BASE – rewrite everything except HREF/BASE  
URICONV=dump – show the current URICONV config.  
URICONV=+ URICONV=mount:-SRC/IMG URICONV=full:SRC/IMG

```bash
BASEURL parameter   ==  BASEURL=URL
                    --  default: none
```

The base of (virtual) URL of this server which will be embedded
in each absolute URL generated by the DeleGate: ex. icon URLs
in HTML pages generated by NNTP/HTTP gateway DeleGate.

When an origin/gateway HTTP-DeleGate received “Host:*vhost1*” in
a request header, it overrides BASEURL=“http://*vhost0*” parameter
to have “*vhost1*” be the base URL of the DeleGate.
To override the “Host:” header by BASEURL, prefix “-” to a host name as
BASEURL=“http://-*vhost0*”.

Example:

`MOUNT='/* nntp://newsserver/*" BASEURL="http://wwwserver/news"`
// this will be useful when a HTTP server “<http://wwwserver>” is mapping  
// its path “/news” to the root of this HTTP-DeleGate.

```bash
DELEGATE parameter  ==  DELEGATE=gwHost:Port[:ProtoList]
                    --  default: DELEGATE=currentHost:currentPort
```

This parameter seems to be almost superseded by BASEURL, RELAY, and
URICONV parameters.

Originally, this parameter is introduced to control proxying mode for
non-CERN HTTP type proxy (including gopher proxy) by rewriting a *URL*
(or pointer) with[*gateway*-_-*URL*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGproxy)
or *proto*://*gwHost:Port*/-_-*URL* notation,
where the *gwHost:Port* part is generated and embedded by DeleGate.

This parameter is introduced to customize the representation of
the *gwHost:Port* part.
It is a representation of the entrance port of this DeleGate
which must be resolvable and reachable from clients.
To make it be most usable, the default value of *gwHost* is
that of current network interface of the host of this DeleGate
through which the current client reached to this DeleGate,
and it is represented in raw IP address number so that clients can
reach the DeleGate even if they don’t know how to resolve
the host name of the DeleGate.

Exceptionally, if the entrance port is specified with
with an explicit network interface like “-P*host*:*port*,
the default value of DELEGATE is set to the *host*:*port*.

By specifying an optional *ProtoList*,
you can limit to which protocols this proxying is applied.
URLs (or pointers) in a response message are rewritten
prefixed with “*proto*://*gwHost:Port*/-_-” so that
the request to it is directed again to this DeleGate
(at *gwHost*:*Port*), if the protocol is included in
the *ProtoList*.

Thus you can disable the proxying mode specifying non existing
entrance port and an empty *ProtoList* like DELEGATE=”-:0:-all”.
But this can be done more simply by RELAY parameter and it is
disabled by default in recent versions.

```bash
COUNTER parameter   ==  COUNTER=listOfCounterControl
    counterControl  ==  do | total | acc | ssi | ref | err | ro | no | mntpV
                    --  default: COUNTER=no
                    --  restriction: applicable to HTTP, SMTP, FTP and DNS
```

Specify the usage of access counters.

(CAUTION: the current implementation of the counter in DeleGate/9.X
is tentative thus the location and the format of the counter file might be
modified and become incompatible in future)

`do` – enable all counters including “total,acc,ssi,ref,err”

`total` – enable the total hit counter of this server

`acc` – enable access counters for each access to each URL

`ssi` – enable access counters for SSI (by PAGE_COUNT in .shtml)

`ref` – enable referrer counters for HTTP “Referer:”

`err` – enable error counters (for SMTP)

`ro` – enable counters in read-only

`no` – disable counters [default]

`mntpV` – use the counter of the MOUNT point (vURL) instead of each URL

If enabled with `COUNTER="do"`, all access counters for any
requests, referrers, and errors are incremented.
If enabled with `"total"`, the access counter for any requests
to this server is incremented.
If enabled with `"acc"`, access counters for any requests
to each target *URL* is incremented.
If enabled with `"ssi"`, only the access counter for the URL
of a SHTML page including a SSI `PAGE_COUNT` reference
is incremented when the page is accessed.
If enabled with `"ref"`, the referrer counter of the URL in the
HTTP “Referer:” fields is incremented.

Each access counter is stored in a file at
“`ADMDIR`/counts/access/*URL*#count”.
Each counter file starts with a line consists of the numbers of accesses
in ASCII decimal format so that it can be initialized or modified manually.
The line can contain three numbers;
the first one is the total count,
the second one is the count excluding repetitive accesses from
the same client,
and the third one is the count excluding repetitive access from
one of recent ten clients.
Each count are represented as `%T`, `%U`
and `%V` respectively in the format string described below.

The counter can be displayed in a specified format using[SSI](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSI.shtml) as the `PAGE_COUNT`
or `COUNTER` value.
If no “url” attribute is specified in a tag, the URL of the SHTML file
containing the tag is implied.
Counter values are converted to a printable character string following
to the format string given in the “`fmt=`…” attribute.
The default format is “`%T`”.

Format Specifiers:

`%T` – total count

`%U` – the count excluding repetitive accesses form a client

`%V` – the count excluding repetitive accesses from recent 10 clients

`%N` – the number of networks [ 0 - 1023 ]

`%M` – the map of networks

`%L` – the list of the last ten clients

`%mT %mU %mV` – mean counts per day

`%mHT %mHU %mHV` – mean counts per hour

`%tC` – the time of the first count (counter creation)

`%tT %tU %tV` – the time of update of each count

The specifier `%N` represents the number of networks of clients
where each network is with net-mask of 10 bits (0xFFC00000 255.192.0.0/10).
This means that the whole IPv4 address space is divided into 1024 networks.
So the `%N` represents the distribution of clients onto networks
over the address space as a coverage value in per-mill.
`%M` shows the distribution of clients as a visual map.

Example:

<!--#echo var=PAGE\_COUNT -->

<!--#echo var=COUNTER -->

<!--#echo var=COUNTER fmt="%T hits since %tC" -->

<!--#echo var=COUNTER url="*URL*" -->

<!--#echo var=COUNTER fmt="%U/%T hits" -->

<!--#echo var=COUNTER url="*URL*" fmt="%U/%T hits" -->

The total count is displayed by `TOTAL_HITS` tag or by
`COUNTER` tag with “`sel=total`”.
The referrer counter of a URL is incremented when the URL is in “Referer:”
header in a HTTP request.
Each referrer counter is stored in a file at
“`ADMDIR`/counts/referer/*URL*#count-ref”.
The referrer counter can be displayed with “`sel=ref`”
attribute in the `COUNTER` tag.

Example:

<!--#echo var=TOTAL\_HITS -->

<!--#echo var=COUNTER sel=total -->

<!--#echo var=COUNTER url="*URL*" fmt="%U/%T refs" sel=ref -->

Enabling all counters for each URL can be expensive and/or unnecessary.
You can reduce counters by using the counter of a MOUNT point as the
representative, or using only total access counters of the server.
In the following example, counters for all URLs is enabled by default
(with `COUNTER=do`),
while counters for URLs under `/srv1/` is represented by
the counter of `/srv1/`,
and only the server’s total counter and SSI counters are enabled for
URLs under `/mine/`.
As shown in this example, `COUNTER` can be specified as a
MountOption of which initial value is inherited from the
`COUNTER` parameter.

Example:

```bash
    COUNTER=do
    MOUNT="/srv1/* http://srv1/*  COUNTER=mntpV"
    MOUNT="/mine/* file:dirpath/* COUNTER=no,total,ssi"
```

```bash
COUNTERDIR parameter  ==  COUNTERDIR=dirPath
                    --  default: COUNTERDIR='${ADMDIR}/counts[date+/year%y/week%W]'
```

Specify the base directory under which[counter](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTER) files are
placed, if the COUNTER paramer is specified to enable counters (as COUNTER=do).
Note that the directory is aged weekly by default (by “%W” in the [aging](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#aging) notation).
It can consume too many files for counters (the size will not be so much
but the number of files can be too many).
You can stop the aging as in DeleGate/9.X in which the directory was not aged
as if sepecified like COUNTERDIR=’${ADMDIR}/counts’ (hard coded in the program
thus was not configurable).
Or you can age the files yearly as COUNTERDIR=’${ADMDIR}/counts[date+/year%y]’.

```bash
CACHE parameter*    ==  CACHE=cacheControl[,cacheControl]*[:connMap]
      cacheControl  ==  do | no | ro
           connMap  ==  ProtoList[:[dstHostList][:srcHostList]]
                    --  default: none
                    --  restriction: applicable to HTTP, FTP, NNTP and Gopher
```

Specify a restriction of cache usage.

`do` – create[CACHEDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CACHEDIR) if not exist (to enable cache)

`no` – disable cache

`ro` – use cache in read-only

Cache is enabled by default.
Cache will be disabled if the CACHEDIR directory does not exist,
or it is not readable and writable by the DeleGate,
or CACHE=“no” is specified,
or “cache” is not included in CONNECT.

```bash
EXPIRE parameter*   ==  EXPIRE=validity[/custody][:connMap]
           connMap  ==  ProtoList:dstHostList:srcHostList
          validity  ==  period
           custody  ==  period
            period  ==  Num[d|h|m|s]
                    --  default: EXPIRE=1h
```

EXPIRE specifies the term of validity of cached data, in unit of
days, hours, minutes, or seconds. Validity does not mean active removal of
cached data by DeleGate; DeleGate merely ignores cached data if it
is older than the specified term.

```bash
CACHEFILE parameter ==  CACHEFILE=fileNameSpec
                    --  default: CACHEFILE='$[server:%P/%L/%p]'
```

CACHEFILE specifies how the file name of a cache file is formed.
The name is derived mainly from informations about server host and
requested URL.
Those informations are specified in the format “$[server:*format*]”
where the *format* is a sequence of symbols each refers a part of an URL
*scheme*://*host*.*d2*.*d1*:*port*/*path*
as follows:

|    | |                       |                                           |
|----|-|-----------------------|-------------------------------------------|
|`%P`|–|*scheme*               |Protocol name part                         |
|`%L`|–|*host*.*d2*.*d1*:*port*|Login (or site) part                       |
|`%H`|–|*host*.*d2*.*d1*       |Host name                                  |
|`%T`|–|*port*                 |Port number                                |
|`%h`|–|*d1*/*d2*/*host*       |hierarchical host name directory           |
|`%d`|–|*d1*/*d2*              |hierarchical domain name directory         |
|`%1`|–|*d1*                   |top level domain                           |
|`%2`|–|*d2*                   |second level domain                        |
|`%p`|–|*path*                 |URL-path part                              |
|`%Q`|–|*host*.*d2*.*d1*.*d0*  |use FQDN of a host name (like %Q%L or %Q%H)|

Another formatting pattern is “$[hash:*format*]” which
hashes a string generated by *format* into
hexadecimal value ranging from `"00"` to `"1f"`.
This will be useful to divide a single huge directory containing all
servers into 32 small directories, which can be on physically
different disks.

Example:

`CACHEFILE='$[server:%P]/$[hash:%H]/$[server:%L/%p]'`

```bash
ICP parameter*      ==  ICP=icpServerList[:icpServerSpec[:connMap]]
     icpServerList  ==  icpServer[,icpServer]*
         icpServer  ==  icpHost[/icpType/proxyPort/icpPort]
     icpServerSpec  ==  icpOptions:proxyPort:icpPort
           connMap  ==  ProtoList:dstHostList:srcHostList
                    --  default: none
                    --  restriction: applicable to {HTTP,FTP}-DeleGate
```

If specified, and if “icp” is included in the CONNECT sequence,
a HTTP-DeleGate will try to get a requested resource
from specified ICP server.
The meaning and default value of each field is as follows:

*icpHost*:
:   The host name or IP address of the ICP server [localhost]

*icpType*:
:   |  |  |
| — | — |
| `s` | – the ICP server is a “sibling” [default] |
| `p` | – the ICP server is a “parent” |
| `l` | – the ICP server is a “listener” which never respond |
| `n` | – the ICP server is a navigation proxy |
| `o` | – require HIT_OBJ response |
| `H` | – the object server is a HTTP proxy [default] |
| `D` | – the object server is a MASTER-DeleGate. |
| `O` | – the object server is an origin server. |

*proxyPort*:
:   The port number of the corresponding object server [8080].

*icpPort*:
:   The port number of ICP protocol [3130].

*icpOptions*:
:   |  |  |
| — | — |
| timeout/*N* | – period to wait response as an ICP client (in seconds)[2.0] |
| `parent` | – mark the default type of *icpServers* as “parent” |
| `listener` | – mark the default type of *icpServers* as “listener” |
| `hitobj` | – enable HIT_OBJ for all *icpServers* by default |
| `Origin` | – object servers are origin server |
| `DeleGate` | – object servers are DeleGate |

Example:

`ICP=icphost`
// This is the simplest usage which is the abbreviation of  
// ICP=“icphost/sH/8080/3130:timeout/2.0:8080:3130:*:*:*”

`ICP="host0"   ICP="host0//8080/3130"   ICP="host0::8080:3130"   ICP="host1:timeout/1.0:::http,ftp:!*.my.domain:*.my.domain"   ICP="host1,host2/O/80/13130:timeout/2.0:8080:3130"`

```bash
CHARCODE parameter* ==  CHARCODE=[inputCode/]outputCode[:[tosv][:connMap]]
        outputCode  ==  charCode
          charCode  ==  iso-2022-jp | euc-jp | shift_jis | utf-8 | us-ascii |
                               JIS | EUC | SJIS | UTF8 | ASCII | guess
           connMap  ==  [ProtoList][:[dstHostList][:[srcHostList]]]
                    --  restriction: applicable to HTTP, FTP, SMTP, POP,
                                     NNTP, Telnet, Tcprelay
                    --  default: none
```

If specified, DeleGate will convert the JIS code in text type response
message into the specified character code.
When UTF8 is specified, a mapping table necessary for conversion between
Unicode and JIS code is downloaded automatically from the server
at Unicode.Org via DeleGate.ORG.

The pseudo code name “guess” means not doing conversion but supplement
the “charset” attribute in “Content-Type” header in a message
when it is lacking, guessing it from the body of the message.
This is useful when a viewer program (ex. a web browser)
of the message is not localized to Japanese thus non-ASCII codes like
EUC-JP are guessed as European or so by the viewer.

If “`tosv`” is specified, the conversion is applied to
the request message (or a message toward a server).
The conversion is also applied to fragments of Japanese text in a HTTP request
message encoded in “%XX” in its request URL or in the body of a POST
message (when it is encoded in Content-Type: application/x-www-form-urlencoded).
The set of values of Content-Type to which the conversion is applied can be
specified with HTTPCONF=[post-ccx-type](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#post-ccx-type).

The application of the conversion can be limited only to a specified
set of protocols, servers and clients specified with *connMap*.
In the *connMap*, the default value of *ProtoList*,
*dstHostList* and *srcHostList* is “*” which matches
any protocols or hosts.

Example: send response in UTF8 to clients and send request
in Shift_JIS to HTTP servers

`CHARCODE=UTF8 CHARCODE=SJIS:tosv:http`

For the FTP protocol, the conversion is applied only to the data
of the ASCII type relayed on the data-connections by default.
It is applied also to binary data or data on the control-connection
with FTPCONF=“ccx:any”.

To enable this parameter for internet-mail/news protocols
(SMTP, POP and NNTP),
also [MIMECONV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MIMECONV) parameter must be specified
so that it enables character conversion (enabled by default).

A HTTP client can override this specification by sending its choice
in “Accept-Language” field in a request message,
which may be configurable in each client (WWW browser).
For example, if
“Accept-Language: (charcode=EUC)” is sent in a request from client,
the response text will be converted into EUC regardless of CHARCODE
specification of the DeleGate. If
“Accept-Language: (charcode=THRU)” is specified,
any conversion specified by the administrator of this DeleGate is disabled.

```bash
CHARMAP parameter*  ==  CHARMAP=mapType:charMap[,charMap]*[:tosv]
           mapType  ==  ascii | ucs | jis | ucsjis | jisucs
           charMap  ==  inCharCode1[-inCharCode2]/outCharCode2[-[outCharCode2]]
          charCode  ==  hexa-decimal code | single ASCII character
                    --  default: none
```

If specified, a character in texts relayed in a message of an application
protocol is mapped to another character.
By default, the mapping is applied to the response data to client.
It can be applied to the request data to server specifying “`:tosv`”.

A character to be mapped is represented in a hexa-decimal value of it
(represented in more than 2 columns), or a direct character in a single columns.
The characters in the JIS X 0208 character set encoded in the variants of its
encoding (ISO-2022-JP, EUC-JP, and Shift_JIS) are represented in
its JIS code value without the most significant bits (8080) as “2121”.
The characters in the JIS X 0212 character set are represented in its
JIS code value prefixed with “1” as “1222F”.

If *inCharCode2* and *outCharCode2* is specified, each character in
the range is mapped to the corresponding character.
If no -*outCharCode2* is given, any input characters in the range
is mapped to *outCharCode1*.

The *mapType* is one of followings:

`ascii` – ASCII to ASCII mapping

`ucs` – UCS to UCS mapping when the input is coded in UTF-8

`jis` – JIS to JIS mapping when the character set of input is JIS X 0208

`ucsjis` – UCS to JIS mapping in the conversion by CHARCODE=JIS or SJIS or EUC

`jisucs` – JIS to UCS mapping in the conversion by CHARCODE=UTF8

Example: reverse lowercase and upper case

`CHARMAP=ascii:a-z/A-Z,A-Z/a-z`

Example: “rot13” encoding

`CHARMAP=ascii:a-m/n-z,n-z/a-m,A-M/N-Z,N-Z/A-M`

Example: replace any Japanese character in JIS X 0208 with “GETA MARK”

`CHARMAP=jis:0100-7F7F/222E`

Example: replace any Japanese character in JIS X 0212 with “GETA MARK”

`CHARMAP=jis:10000-1FFFF/222E`

Example: represents unknown characters by “WHITE SQUARE” instead of “GETA MARK”

`CHARMAP=jis:0000/2222`

```bash
HTMLCONV parameter  ==  HTMLCONV=convList
          convList  ==  conv[,conv]*
              conv  ==  deent | enent | fullurl
                    --  default: HTMLCONV=deent
```

Specify a list of flags to control conversion for HTML text in
a HTTP response message.

|       | |                                                                        |
|-------|-|------------------------------------------------------------------------|
|deent  |–|decode entity symbol                                                    |
|enent  |–|encode entity symbol                                                    |
|fullurl|–|convert all of URLs to full URLs (equals to URICONV=“full:+,-HREF/BASE”)|

“deent” and “enent” control encoding and decoding of special
characters between HTML and plain text
(”<” to/from “<” for example)
when such characters appear in a text of
multi-byte charset (like ISO-2022-JP).
If “deent” is specified, encoded entity symbol appearing
in multi-byte charset text will be decoded.
This may be useful to recover a text
including characters indiscriminately encoded by
encoder which does not care multi-byte characters.

If “enent” is specified then entity symbols appearing
out of multi-byte charset text will be encoded.
This may be useful in case of NNTP-DeleGate to be accessed by
WWW client.
If empty list is specified, any conversion is disabled.

```bash
MIMECONV parameter  ==  MIMECONV=mimeConv[,mimeConv]
          mimeConv  ==  thru | charcode | nospenc
                                    | textonly | alt:first | alt:plain
                    --  default: none
                    --  MIMECONV="" if CHARCODE parameter is given
```

Control MIME encoding/decoding in NNTP/POP/SMTP DeleGate.
MIMECONV=thru disables any MIME encoding/decoding, and
MIMECONV=charcode enables only character code conversion.
MIMECONV=nospenc disables a special encoding of space character in
non-ASCII (ISO-2022-JP) text in MIME header.

Here is a group of options for filtering a “multipart/*” message
to convert it into a plain message by selecting or unfolding the
list of parts as follows:

:   `textonly` – only the first text/* part in multipart/*

```
`alt:first` -- only the first alternative in multipart/alternative

`alt:unfold` -- all of alternatives in multipart/alternative
```

```bash
FCL parameter       ==  FCL=filterCommand
FTOCL parameter     ==  FTOCL=filterCommand
FFROMCL parameter   ==  FFROMCL=filterCommand
FSV parameter       ==  FSV=filterCommand
FTOSV parameter     ==  FTOSV=filterCommand
FFROMSV parameter   ==  FFROMSV=filterCommand
FMD parameter       ==  FMD=filterCommand
FTOMD parameter     ==  FTOMD=filterCommand
FFROMMD parameter   ==  FFROMMD=filterCommand
filterCommand       ==  [-s,][-p,][-w,]command
                    --  default: none
```

Specify a[filter](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CFIscript) command
to be applied to data transmitted between DeleGate and clients,
or between DeleGate and servers.
When a *filterCommand* is specified in relative path name,
it is searched in [LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH).

Filters can be applied conditionally using
[CMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#cond-filter)
based on circuit level information, or
using [CFI script](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CFIscript)
based on application level information.

FILTER CONTROL OPTIONS: options to get status information from,
or control synchronization with filter program.

:   `-s` – get status information (ex. authentication) from filter  
`-w` – wait the filter process to exit before starting relay  
`-p` – detach the filter when it exits then continue relaying

BUILT-IN FILTERS: if a *filterCommand* is prefixed with “-”,
then it is a filter built-in to DeleGate.

credhyFilter == -credhy … encryption/decryption filter

teeFilter == -tee[*teeOpt*]*[SPACE *filePath*] … filter like tee(1) command

catFilter == -cat[*teeOpt*] … filter like cat(1) command

*teeOpt* == -h | -n | -t | -v | -l | -e
:   `-h` – output header part only  
`-n` – number the output lines  
`-t` – time stamp for each output line  
`-v` – visualize invisible characters  
`-l` – (with -tee) output to LOGFILE instead of stderr (default)  
`-e` – (with -tee) output to stderr

codeconvFilter == -*charCode* … char code conversion as[CHARCODE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARCODE)

*charCode* == jis | sjis | euc | utf8

Example:

`FTOCL=-tee-h-n FTOSV=-tee`

```bash
XCOM parameter      ==  XCOM=filterCommand
XFIL parameter      ==  XFIL=filterCommand
                    --  default: none
```

XCOM and XFIL is used together with SERVER=“exec” parameter.
A special protocol name “exec” means executing some local command
rather than connecting to a server. With “exec”, DeleGate will work
like simple *inetd* or *wrapper*.
What will be executed is specified with either XCOM or XFIL parameter.
Commands executed as XCOM will be given standard I/O
which are bound for a socket connected to the client.
Commands executed as XFIL will be given standard I/O
which are redirected to a pair of pipes bound for DeleGate,
which relays it to and from the client.

On WindowsNT and OS/2, commands executed as XCOM will be given a
environment variable “SOCKHANDLE_CLIENT”
which have the handle value of the inherited socket
connected to the client.

```bash
CHROOT parameter    ==  CHROOT=dirPath
                    --  default:  none
                    --  restriction: super-user only on most of Unix
```

Change the root of file system to *dirPath* at the start
using chroot(2) system call,
restricting accessible (visible) files to ones under *dirPath*.
This is effective to isolate the DeleGate from the whole file system
of the host machine preventing DeleGate from possible destruction of them
by its bug or by intrusion.[DGROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT) is interpreted after the root is changed.

A special case CHROOT=”/” means using the value of
(default or specified) DGROOT as CHROOT and set DGROOT=”/”.
That is, DGROOT=”/*path*” with CHROOT=”/” are equal to
DGROOT=”/” with CHROOT=”/*path*”.

```bash
DGROOT parameter    ==  DGROOT=dirPath
                    --  default: if ${STARTDIR}/DGROOT exists then use it, or
                                  on Unix: '/' if CHROOT is set or
                                           '${HOME}/delegate' or
                                           '/var/spool/delegate-${OWNER}' or
                                           '/tmp/delegate-${OWNER}'
                               on Windows: '/Program Files/DeleGate'
```

All of sub-directories (LOGDIR, ADMDIR, CACHEDIR, WORKDIR, ETCDIR,
ACTDIR and TMPDIR) will be located under the DGROOT by default.

At the start up time (on Unix), DeleGate searches an available DGROOT
which is both readable and writable by the OWNER.
When a candidate directory does not exist, DeleGate tries to make the
directory by itself.
If DGROOT is specified explicitly, it is tried first.
If it failed or no DGROOT is given,
default candidates will be tried in order until an available directory
is found.

```bash
SHARE parameter     ==  SHARE=dirPatternList
                    --  default: empty
```

If specified, created directories or files
which has name matches with given pattern
will be set with mode
0777(rwxrwxrwx) or 0666(rw-rw-rw-) respectively,
to be sharable among arbitrary users.
When a pattern is specified in non-absolute form, it is regarded as
relative to DGROOT.
By default, directories or files will be created with
mode 0755(rwxr-xr-x) or 0666(rw-rw-rw-),
as modified by UMASK which is 022 typically.

Example:

// make everything sharable  
`SHARE=""`  
// share cache and log under DGROOT  
`SHARE="cache/*,log/*"`  
// share directories with older versions  
`SHARE='${CACHEDIR}/*' CACHEDIR='/var/spool/delegate-anybody'`  
`SHARE='${VARDIR}/*' VARDIR='/var/spool/delegate'`

```bash
UMASK parameter     ==  UMASK=mask
                    --  default: the value of umask(2)
```

Set *mask* for file creation mode, using umask(2) system call.

```bash
VARDIR parameter    ==  VARDIR=dirPath
                    --  default: VARDIR='${DGROOT?&:/var/spool/delegate}'
```

This parameter seems be obsolete after DGROOT has become standard in
DeleGate/6.0.
It specifies the default base of sub directories like DGROOT
except for ACTDIR and TMPDIR.
The default value of VARDIR is the value of DGROOT.

```bash
CACHEDIR parameter  ==  CACHEDIR=dirPath
                    --  default: CACHEDIR='${VARDIR}/cache'
```

To enable cache, the directory CACHEDIR must exist and
is both readable and writable by the DeleGate.
It will be automatically created with CACHE=“do”
with necessary permissions.

```bash
ETCDIR parameter    ==  ETCDIR=dirPath
                    --  default: ETCDIR='${VARDIR}/etc'
```

The directory to hold persistent files for configuration and
administration of DeleGate.
Configuration files for origin SMTP-DeleGate([SMTPGATE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SMTPGATE))
and origin NNTP-DeleGate ([NNTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#origin_NNTP)) are placed hear.

```bash
ADMDIR parameter    ==  ADMDIR=dirPath
                    --  default: ADMDIR='${VARDIR}/adm'
```

The directory to hold genarated files for administration of DeleGate,
including files for[shutout](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#defense) defense,
password repository of [-Fauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#func_auth),
identification code of executalbe file of DeleGate,
server’s statistics file,
and COUNTER.

```bash
LOGDIR parameter    ==  LOGDIR=dirPath
                    --  default: LOGDIR='${VARDIR}/log'
                    --  v10-default: LOGDIR='log[date+/y%y/m%m/%d]'
```

The default directory where log files are placed.
From the version 10, by default, log files became devided
by year, month and day, as ‘DGROOT/log/y14/m08/20/80.http’ for example.

```bash
LOGFILE parameter   ==  LOGFILE=[LogFilename]
PROTOLOG parameter  ==  PROTOLOG=[LogFilename][:logFormat]
ERRORLOG parameter  ==  ERRORLOG=LogFilename
TRACELOG parameter  ==  TRACELOG=LogFilename
                    --  default: LOGFILE='${LOGDIR}/${PORT}'
                    --  default: PROTOLOG='${LOGDIR}/${PORT}.${PROTO}'
                    --  default: ERRORLOG='${LOGDIR}/errors.log'
                    --  default: TRACELOG='${LOGDIR}/ptrace.log'
```

If *LogFilename*s are specified in a relative path then they are placed
under ${LOGDIR}. If those names start with “./” then they are placed
under ${WORKDIR}.

The patterns ${PROTO} and ${PORT} will be substituted with the
protocol name and the port number of this DeleGate respectively.
These files and directories will be created automatically by
DeleGate if possible. You can stop logging by specifying null
file name like LOGFILE=”” or PROTOLOG=””.

The format of PROTOLOG for HTTP is compatible with
the[*common logfile format*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httplog) and is customizable.
The format of PROTOLOG for FTP is compatible with
[*xferlog*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#xferlog).

```bash
SYSLOG parameter*   ==  SYSLOG=[syslogOpts,][syslogServ]
        syslogOpts  ==  syslogOpt[,syslogOpts]
         syslogOpt  ==  -vt | -vs | -vS | -vH | -fname
                    --  default: none
```

This parameter specifies recording log data via the “syslog” service (RFC3164).
The “facility.priority” pair of logged data of[LOGFILE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGFILE)
is “daemon.debug” for usual data and “daemon.err” for errors.
(It will be divided into more detailed levels in the future.)
The log data of [PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROTOLOG) is sent with “daemon.notice”.
The facility name can be changed with a “-f*name*” option.

Multiple `SYSLOG` parameters can be specified to send a log data
to multiple different destinations each specified by a *syslogServ*.
A *syslogServ* is a URL of a syslog server or a local file.
The default *syslogServ* is the local logger to which log is sent
via the standard “syslog()” function.
For each destination, the log format or detailness can be specified by
prefixing a list of *syslogOpt* as follows:

|        |                                             |
|--------|---------------------------------------------|
|`-vt`   |– terse LOGFILE                              |
|`-vs`   |– without LOGFILE                            |
|`-vS`   |– without PROTOLOG                           |
|`-vH`   |– without the syslog header                  |
|`-fname`|– use the facility *name* instead of “daemon”|

Example:

|                           |                                    |
|---------------------------|------------------------------------|
|`SYSLOG=`                  |– to the local syslog               |
|`SYSLOG=syslog://host`     |– to a remote syslog server         |
|`SYSLOG=syslog://host:port`|– on a non-standard port            |
|`SYSLOG=/dev/tty`          |– to the console                    |
|`SYSLOG=file:path`         |– to a local file                   |
|`SYSLOG=-vH,file:path`     |– without the syslog header         |
|`SYSLOG=-fdaemon`          |– as the “daemon” facility (default)|
|`SYSLOG=-flocal1`          |– as the “local1” facility          |

The source port (and the address) of syslog UDP packets to a remote
syslog server can be specified as
`SRCIF=":8514:syslog"`
(or `SRCIF="xx.xx.xx.xx:8514:syslog"`)
for example.  
Switching syslog servers based on each client and server of the
application protocol is not (yet) supported.

LogFilename and dirPath Substitution for Aging

If the pattern “[date+*format*]” is included in the file name,
the *format* string is evaluated by strftime(3) compatible function
with the current time,
and will be substituted with the evaluated value.
This means that a log directory (or file) specified
will be divided into a granularity of specified time period,
thus it is *aged*.
Formats to represent typical time periods are as follows:

`%Y` – year (like 2000)  
`%y` – year without century [00-99]  
`%m` – month number [01-12]  
`%d` – day of month [01-31]  
`%W` – week number of year [00-53]  
`%w` – weekday number [0-6, Sunday=0]  
`%H` – hour [00-23]

Example: aging a log file day by day and rotate by a month

`LOGFILE='${PORT}[date+.%d]'`

Example: make log directory hierarchical by date

`LOGDIR='log[date+/aged/%y/%m/%d]'`

The latest LOGFILE will be pointed with another file name
(hard link to it) which name is made by omitting
“[date+*format*]” parts from LOGFILE specification.
For example, by the LOGFILE specification in the above example,
logfile will be named like “log/aged/00/12/31/80.http”
while the latest one is given another name “log/80.http”.

Another pattern for aging is “[start+*format*]”
which will be evaluated in the same way with
“date+” except that it will be substituted by
the time when the DeleGate started
(or restarted by SIGHUP or specified TIMEOUT=restart).

```bash
EXPIRELOG parameter ==  EXPIRELOG=LogFilename
                    --  default: EXPIRELOG='${LOGDIR}/expire.log'
```

The log-file for expiration by “-Fexpire” function or “-expire” action in CRON.

```bash
WORKDIR parameter   ==  WORKDIR=dirPath
                    --  default: WORKDIR='${VARDIR}/work/${PORT}'
```

If WORKDIR is not accessible, or if WORKDIR is not explicitly
specified when -vv option is given, then current directory (of
invoker of this DeleGate) will be used as WORKDIR.

```bash
ACTDIR parameter    ==  ACTDIR=dirPath
TMPDIR parameter    ==  TMPDIR=dirPath
PIDFILE parameter   ==  PIDFILE=fileName
                    --  default: ACTDIR='${DGROOT}/act'
                    --  default: TMPDIR=system dependent
                    --  default: PIDFILE='${ACTDIR}/pid/${PORT}'
```

Information about currently active servers are placed at ACTDIR.
Those are temporary files which are made on invocation of a
DeleGate server and are removed at its termination.

```bash
HOSTS parameter*    ==  HOSTS=nameList[/addrList]
          nameList  ==  name | {name[,name]*}
          addrList  ==  addr | {addr[,addr]*}
                    --  default: HOSTS=localhost/127.0.0.1
```

List of domain-names/IP-addresses pairs which will override DNS
(or NIS or /etc/hosts table) data.
This could be used for speed-up of resolution for
frequently referred hosts, aliasing,
or relief of unknown hosts by any resolvers.
Multiple names or addresses could be specified in the
form {name1,name2,…}/{addr1,addr2,…}.
If only {name1,name2,…} is given without *addr* part,
it makes name1,name2,… be regarded as a single host.

```bash
RESOLV parameter    ==  RESOLV=[resolver[,resolver]*]
          resolver  ==  resType[:[resParam][:[queryHostList][:clientHostList]]]
           resType  ==  cache | file | nis | dns | sys
                    --  default: RESOLV=cache,file,nis,dns,sys
```

Specify which name resolver should be used in what order.

|     |                                                                                                              |
|-----|--------------------------------------------------------------------------------------------------------------|
|cache|– means cached result from following resolvers                                                                |
|file |– means local hosts(5) file usually located at /etc/hosts,                                                    |
|nis  |– means hosts map on NIS or YP(4) service,                                                                    |
|dns  |– means DNS service, and                                                                                      |
|sys  |– means using gethostbyname(2) and gethostbyaddr(2) which usually call system’s standard resolver of the host.|

If RESOLV is not specified, “sys” is disabled if the IP-address of the
host of DeleGate is resolvable by “dns”.

If empty value is specified as RESOLV=”” then only hosts listed
in HOSTS parameter can be resolved (this could be useful
when you must hide hosts table for security consideration).
Each resolver can be specified with optional argument like follows:

|                                                                    |                                                |
|--------------------------------------------------------------------|------------------------------------------------|
|`cache:/path`                                                       |– path name of cache directory [$TMPDIR/resolvy]|
|`file:/path`                                                        |– path name of host-name file [/etc/hosts]      |
|`nis:nisDomain`                                                     |– NIS domain name [default domain]              |
|`dns:dnsHost`                                                       |– (a list of) DNS server                        |
|A resolver can be applied to specific queries from specific clients.|                                                |
|The optional *queryHostList* specifies for which hosts or           |                                                |
|addresses the resolver is applied.                                  |                                                |
|The optional *clientHostList* specifies for which client hosts      |                                                |
|the resolver is applied.                                            |                                                |

Example: selecting DNS servers depending on the inquired host/address

`RESOLV="cache,dns:{192.168.1.2:8053}:{192.168.*,*.localdomain},dns:192.168.1.1"`  
// resolve local hosts with DNS sever at 192.168.1.2:8053  
// and resolve others with 192.168.1.1:53  
// this can be decomposed into a set of parameters like follows:  
`RESOLV="cache,dns:local-dns:local-hosts,dns:192.168.1.1"   HOSTLIST=local-dns:192.168.1.2:8053   HOSTLIST=local-hosts:192.168.*,*.localdomain`

Example: selecting resolvers depending on the inquiring (client) DNS host

`RESOLV="file:/etc/hosts:localHosts:192.168.*,dns:xx.xx.xx.xx"   HOSTLIST="localHosts:192.168.*,*.localdomain,*.mydomain"`  
// queries from local hosts (192.168.*) for “localHosts” are resolved  
// with the file “/etc/hosts”, others are resolved with the DNS server
“xx.xx.xx.xx”.

By default, a connection to a host which has multiple IP addresses
is tried for each address in the order they are defined in each
resolver. A special parameter HOSTS=”*/*/RR” can be added to
specify “*Round Robin*” where those IP addresses are tried in
round robin order.

```bash
RES_WAIT parameter  ==  RES_WAIT=seconds:hostname
                    --  default: RES_WAIT="10:WWW.DeleGate.ORG"
```

Wait the resolver(s) to be ready before the DeleGate starts the
initialization procedure. In the initialization, the result value
of host-name resolution can be used as an important configuration
parameter like ones for access control.
The resolver of the host system may take time to be ready after
the system’s reboot, and could be unstable typically when the host
address is assigned by DHCP. Therefore it might be not yet ready
when the DeleGate started.

By default, DeleGate waits for 10 seconds until it can resolve
a host name “WWW.DeleGate.ORG” by the given set of resolvers which
is specified by the RESOLV parameter.
You can specify a more appropriate host name or IP address to be
used to detect the readiness of the resolvers.
This feature can be disabled with `RES_WAIT=0`.

```bash
RES_CONF parameter  ==  RES_CONF=URL
                    --  default: RES_CONF="file:/etc/resolv.conf"
                        or from registry (on Windows)
```

Specify where the “resolv.conf” file is. The file is interpreted
by the DeleGate original resolver named *Resolvy*.
Resolvy recognizes “nameserver”, “domain”, “ndots”, “search”, and
“sortlist” in it.

```bash
RES_NS parameter    ==  RES_NS=nsList
            nsList  ==  dnsServ[,nsList]
           dnsServ  ==  dnsServer[//socksV5Host] | END.
                    --  default: depend on RES_CONF
```

Specify a DNS server to be used: *dnsServer* is a host name or an
IP-address of the host name DNS server, which may optionally be
followed by port number, like “host:8053” when the port number
is not standard port(53).
With “*dnsServer*//*socksV5Host*”, a DNS server
beyond a firewall can be referred through the specified Socks V5 server.
The Socks server is specified by its IP address with an optional port
number like “192.168.1.1:2080”.

By default, name servers listed in “[resolv.conf](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RES_CONF)” are
added to the list of DNS servers to be used. A special *dnsServ*
name “.END” disables to adding such name servers. For example,
RES_NS=“192.168.1.1,END.” means using 192.168.1.1 only regardless of
“resolv.conf”.

```bash
RES_AF parameter    ==  RES_AF=afOrder
            afOrder ==  46 | 64 | 4 | 6
                    --  default: 46
```

Specify the ordered set of address families (IPv4 or IPv6) of the address
of the host to be retrieved. The default value “46” means
retrieving IPv4 address first, and if not found, then IPv6 address next.

```bash
RES_RR parameter    ==  RES_RR=HostList
                    --  default: RES_RR="*"
```

Round robin IP-address-list for the hosts included in the HostList.
Currently, only RES_RR=”*” and RES_RR=”” are supported.

```bash
RES_VRFY parameter  ==  RES_VRFY=""
                    --  default: none
```

With “RES_VRFY=”, results of reverse look-up of DNS server is verified.
When an *IPaddress1* is resolved to *Hostname*, and when the
*Hostname* is resolved to *IPaddress-list* which does not include
the *IPaddress1*, the verification fail and the result is ignored.

```bash
RES_DEBUG parameter ==  RES_DEBUG=number
                    --  default: none
```

The level of logging for debugging of the built-in resolver.
**PROTOLIST**

```bash
       ProtoList  ==  [!]protoSpec[,ProtoList]
       protoSpec  ==  protocolName[/[portNumList][/methodList]]
```

A ProtoList is a list of protocol names.
Reserved name “*” means all of protocols.
If “!” or “-” is prefixed,
the protocol is excluded from the protocol list.
**HOSTLIST**

```bash
        HostList  ==  [!][-iType]hostSpec[,HostList]
           iType  ==  {h|a|c|*}/[iType]
        hostSpec  ==  [{userList}@]hostSpec[/netMask]
        userList  ==  userNamePattern[,userNamePattern]*
        hostSpec  ==  hostNamePattern | hostAddrPattern
 userNamePattern  ==  [*]uname[*]
 hostNamePattern  ==  [*]hname[*]
 hostAddrPattern  ==  IPaddressPattern | IPrange
         netMask  ==  IPaddress | maskLength
```

A HostList is a list of hosts (by name or address)
to be used for matching to examine whether a certain host is included
in the list or not.
Each host (*hostSpec*)
is optionally prefixed with a list of users (*userList*),
and optionally followed by a *netMask*.

TYPE OF IDENTITY:   A *hostSpec* “*person*@*place*” represents following identities:

```
[`-h/`] [*Ident*@]*peerHost* -- peer host's identity (client, server or proxy):   The name or address of the host matches with *peerHost*,
    and if *Ident*@ part is specified,
    the name of the owner of the connection, detected automatically
    by the[Identification](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Ident) protocol, matches with *Ident*.
[`-a/`] *authUser*@*authHost* -- authenticated identity:   The user of the client is authenticated as *authUser*
    (showing the name with an appropriate password)
    by an authentication server *authHost*
    (specified as[AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER)=*authHost*)

[`-c/`] *person*@*domain* -- certificated identity
:   The E-mail address of the client's user is given as
    /Email=*person*@*domain*/
    in a client's certificate (which is passed over [SSL](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_SSL)).


Implicitly, A *hostSpec* like "*host*" without "*user*@"
part matches only with peer host's identity
while "*user*@*host*" matches with any kind of identities.
By prefixing -*iType* before *hostSpec*, identities to be
matched can be specified explicitly. for example:

`user@host`
-- matches if at least one of identities is "user@host"
  
`-h/user@host`
-- matches if peer host's identity is "user@host"
  
`host`
-- matches if peer host's identity is "host"
  
`-*/host`
-- matches if at least one of identities is "\*@host"
  
`-a/host`
-- matches if authenticated identity is "\*@host"
  
`-a/c/host`
-- matches if authenticated or certificated identity is "\*@host"
  
`-a/*`
-- matches if authenticated successfully
```

WILDCARD ( * )
:   A set of hosts belonging to a domain or a network can be represented
as a single *hostSpec* with wild-card notation.
You can prefix or postfix wild-card character “*” to a hostname
like “*.com” or “*.delegate.org” or “www.*”.
As a special case, *hostSpec* which begins with “*.” like
“*.*domain*” matches with “*domain*” as a hostname
as well as ordinary hostnames like “xx.*domain*” or “yy.xx.*domain*”
(since DeleGate/6.1.18).
IP-address range, which may represent a network,
can be specified like 192.168.[0-255], 192.168.1.[32-63].
These range can be written as 192.168.0.0/16 and 192.168.1.32/27.
In IP-address notation, wild-card character “*” means [0-255],
thus “192.168.*” is equals to 192.168.[0-255].
NEGATION ( ! )
:   If “!” is prefixed to a *host*,
it means that the host is excluded from the list.
All of elements in the list are scanned from the first one to the last one.
Thus once included (excluded) name may be excluded (included)
in succeeding list.
For example, for a HostList like follows:

```
"\*.dom,!\*.xx.dom,\*.yy.xx.dom"

a host named "host.yy.xx.dom" matches with the first *hostSpec*,
but excluded by the second one, but included again by the third one.
If the first *host* in a HostList is with "!", it means
exclusion from the universe ("\*", that is any host), that is,
`"!host, ..."` is regarded as `"*,!host, ..."`
```

NETMASK ( *host*/*mask* )
:   Specifying a *netMask*, you can check only a part of address,
the network address part typically.
The *netMask* can be specified in one of following formats;

```
`/24`, `/28`, ... length of mask bits

`/FFFFFF00`, `/FFFFFFF0`, ... hexadecimal notation

`/255.255.255.0`, `/255.255.240.0`, ... dot notation

`/@A`, `/@B` or `/@C` ... address class mask.
:   `@A`, `@B` and `@C` represent
    `/8`, `/16` and `/24` respectively.
    This notation can be followed by the number of bits for subnets;
    for example `/@B4` means class B network
    divided into sixteen subnets.

`@` ... the default network mask
:   represents one of `/@A`, `/@B` or `/@C`
    depending on the class of IP-address of the host to be masked

`.` ... narrower default network mask
:   similar to "@"
    but represents "/24" when it is applied to class-A IP-addresses.
    For an IPv6 address, the default mask is "ffff\_ffff\_ffff\_ffff\_\_"
    which represents a mask of 64bits "FFFF:FFFF:FFFF:FFFF::".
```

USER LIST ( {*userList*}@*host* )
:   For a srcHostList (i.e. HostList concerning client hosts),
list of user names (*userList*) can be prefixed to a host name
like {user1,user2,…}@host.
The negate symbol “!” have the same meaning with that in a HostList.
Note that !user@host is different from {!user}@host;
the former excludes user@host,
but the latter means {*,!user}@host thus includes *@host except user@host.
The special user name “?” matches with users whos names are not
IDENTified with identd.

```
Example: inhibit access from unknown hosts or from unknown users

`RELIABLE="{!?,!?@*}"`
```

PORT LIST ( *host*:{*portList*} ) For a dstHostList (i.e. HostList concerning server hosts), a list of port numbers (*postList*) can be postfixed to a host, to make matching by port number as well as host name/address. Example: conditional filtering using[CMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CMAP) `CMAP="sslway:FSV:*:{*:{563,636,990,992,995}}:*"`which is similar to `CMAP="sslway:FSV:nntps,ldaps,ftps,telnets,pop3s:*:*"`

SPECIAL HOST NAMES
:   There are special host names which are substituted with real host
names at runtime.

```
"."
:   the host where the DeleGate is running.

"-"
:   identical to "." if the host has unique IP address (network
    interface), but if it have multiple IP addresses, it will
    be the IP address from which the client connected to this DeleGate.

".o"
:   identical to "." if the host has unique IP address, but if
    it have multiple network interface, outgoing
    network interface
".localnet":   represents `"localhost,./.,-/.,.o/."` by default.
    It can be redefined by the[HOSTLIST](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#HOSTLIST) parameter
    as HOSTLIST=.localnet:*HostList*.

".C" or "-C"
:   the client host which may be useful to restrict access
    from a client only to the client (network).

"?"
:   matches any "*unknown hosts*" of which name or address is not
    known by resolvers (listed in [RESOLV](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESOLV)).
```

DISABLING NAME RESOLUTION ( -*host* )
:   If a hostname (or a IP-address) is prefixed with “-” like “-hostname”
(”-192.168.1.1”), then no name resolution (reverse resolution) will be
tried for the hostname (IP-address). This will avoid wasting time in
resolution trial for a never resolvable hostname (IP-address).

ADDRESS TYPE ( _4. | _6. )
:   `"_4.*"` matches any IPv4 addresses while
`"_6.*"` matches any IPv6 addresses.
These can be used for routing or access control based on address types.

AGENT CONDITION ( -A/*agentNamePattern* )
:   A pseudo host name pattern with prefix “-A/” at the top of it is used to
specify the User Agent of the client.
:   Example:

```
RELIABLE="-A/Mozilla/4,!-A/MSIE 5" ... which is similar to  
RELIABLE=.realmozi4 HOSTLIST=".realmozi4/A:Mozilla/4,!MSIE 5"
```

TIME CONDITION ( -T.*period* )
:   A pseudo host name pattern with prefix “-T.” at the top of it is used to
specify a time period in a day.
:   “-T.*period*”
matches if the current time is in the specified time *period*,
where *period* is represented as “*hour1*-*hour2*”
which means “from *hour1*:00:00 to *hour2*:59:59”.

```
Example:

`PERMIT="*:-T.9-16:hostList1" PERMIT="*:-T.17-8:hostList2"`
// *hostList1* is permitted during office hours whereas  
// *hostList2* is permitted non-office hours.

The complete format of *period* is like this:
[w*W*]*HH*[*MM*][-*HH*[*MM*]].
A time period in a week is represented with "w*W*" where *W*
expresses a day in a week ranging from "0" to "6" according to Sunday
through Saturday. Sunday can be expressed as "7" too for convenience.

Example:

`-T.w5-0` // Friday through Sunday  
`-T.w5-7` // Friday through Sunday  
`-T.w51730-10830` // from 5:30pm on Friday to 8:30am on Monday
```

COMPOSITE OPERATORS ( &, |, ! )
:   As explained above, the meaning of a comma (,)
in HostList like “A,B” is not AND nor OR.
Operators like AND, OR and NOT operators are provided as
a special member of a list.

```
"&"
:   AND operator used as "*hostList*=A,&,B" where when A turn to be
    false, the *hostList* as a whole turns to be false without
    evaluating B. Otherwise B must be true to be true as a whole.

"|"
:   OR operator used as "*hostList*=A,|,B" where when A turns to be
    true, the *hostList* as a whole turns to be true without
    evaluating B. Otherwise B must be true to be true as a whole.

"!"
:   NOT operator used as "A,!,B" where the result of A is
    negated, and succeed evaluation of B if it exists.

Example:

`PERMIT="*:*:-T.9-16,&,hostList1" PERMIT="*:*:-T.17-8,&,hostList2"`
// the same meaning with the above example.
```

**PARAMETER SUBSTITUTION**

There is no format of *configuration file* with some syntax sugar
for DeleGate (yet),
but there is a simple recursive substitution mechanism instead,
to assemble hierarchical and possibly distributed parts of parameters
into a single list of parameters (or options).

Options and parameters can be loaded from external
“*substitution resources*”.
An option like “+=*file*” is substituted by a list of options enumerated
in the resource named “*file*”.
An option like “*name*=+=*file*” is substituted
by a list of “*name*=*value*”
where the “*value*” is enumerated in the “*file*”.
Similarly an option like “*name*=*xxx*:+=*file*” is substituted
by a list of “*name*=*xxx*:*value*”.

A *substitution resource* can be given in an encrypted format.
Encrypted data can be directly represented in the string of format
as “+=enc:ext::XXXX:” in which the part of XXXX contains the encrypted data.
This format of data is created with “-Fenc” option of DeleGate.
When it is named with the suffix “`.cdh`” as “+=conf.cdh”,
it is decrypted by “Credhy” using the passphrase for decryption
which is specified as the password of
the[“config” user](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#EncryptedConf).

Substitution can be done recursively. In this case, a relative resource
name is searched in [DGPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGPATH)
or [LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH).
By default, `DGPATH='+:.:${HOME}/delegate'`
where “+” stands for the place where the “*caller*” resource is.
For example, if “+=file2” is referred from caller file “/local/etc/file1”,
the “file2” will be searched first as “/local/etc/file2”.
A resource name can be specified in full URL like
“+={file:/local/etc/file1}” or “+={<http://host/file}>”.

```bash
       paramRef ==  +=[URL][?label,[label]*]

      paramList ==  line
                    line
                    ...

  paramListPart ==  CASE label
                         paramList
                    ESAC
```

Substitution resources are the list of options (or parameters)
where each line stands for an option (or a parameter).
In each line, strings after sharp character(#) will be ignored
as a comment.
White space characters (SPACE, TAB, LF and CR) at the beginning
or the ending of each line are ignored.
Single quote(’) and double quote(”) are stripped.
Back slash character() let the succeeding character be as is.

Example:
The following five examples have the same meaning with each other.

`PERMIT=a:b:c PERMIT=a:b:d PERMIT=a:e:f PERMIT=x:y:z ...`

`+=parameters`

[content of parameters]
:   `PERMIT=a:b:c   PERMIT=a:b:d   PERMIT=a:e:f   PERMIT=x:y:z   ...`

`PERMIT=+=permits`

[content of permits]
:   `a:b:c   a:b:d   a:e:f   x:y:z`
…

`PERMIT=a:b:+=abclients PERMIT=+=others`

[content of abclients]
:   `c   d`

[content of others]
:   `a:e:f   x:y:z`
…

`PERMIT=+=permits`

[content of permits]
:   `PERMIT=a:b:+=?abclients

```
PERMIT=+=?others

CASE abclients
:   c  
    d

ESAC

CASE others
:   a:e:f  
    x:y:z  
    ...

ESAC`
```

Substitution resources will be reloaded when the DeleGate
[restart](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RESTART)
receiving a SIGHUP signal or by “-restart” action in CRON parameter.

Another substitution is in the form “*name*=-=*URL*” which loads the
content of URL into a temporary file on local file system (under ACTDIR),
then the parameter is rewritten to “name=/path/of/temporary-file”.
This will be useful when you wish to pass remote resources to CGI or
CFI programs,
like “[-e](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_-e)CONFIGDATA=-=<http://server/configData>”,
then those programs will be given an environment variable named CONFIGDATA
of which value is a temporary file name containing the content of
“<http://server/configData>”.

**CFI AND CFI SCRIPT**

Communication between client and DeleGate or between DeleGate and server
can be filtered or translated by user defined
filter programs attached to DeleGate using a simple scheme named
CFI (Common Filter Interface).
Existing filter programs, from standard input to standard output,
can be used as a CFI program without modification.
The usage of CFI is controlled by parameters like following:

```bash
filterName="filterSpec"
CMAP="filterSpec":filterName:connMap

  filterName  ==  FCL | FTOCL | FFROMCL |
                  FSV | FTOSV | FFROMSV |
                  FMD | FTOMD | FFROMMD 
  filterSpec  ==  filterCommand | CFIscriptName
                  | tcprelay://host:port
```

*filterName* is named as
`FXX`, `FTOXX` and `FFROMXX`
where `XX` is one of
`CL` (client), `SV` (server) and `MD` (MASTER-DeleGate).
Filter commands for `FXX` are bidirectional filter
given file descriptor 0 bound for the client,
and file descriptor 1 bound for the DeleGate.
Filters commands for `FTOXX` and `FFROMXX`
getting input from standard input and put output to standard output
which is bound for `XX`.
A unidirectional filter at a remote host can be used by connecting it on TCP
by “tcprelay://*host*:*port*”

A filter can be applied conditionally
based on circuit level information,
using[CMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CMAP) parameter like follows:

CMAP=*filterSpec*:*filterName*:*ProtoList*:*dstHostList*:*srcHostList*
For example, CMAP=“sslway:FSV:telnet:hostA:*”
means applying SSLway filter only
when connecting to the Telnet server at hostA.

For `FTOXX` and `FFROMXX` filters,
CFI script enables selecting an appropriate filter
to be applied to each data depending on the type of data.
Instead of direct usage of a filter program like
`FTOCL=filterCommand`, specify
`FTOCL=filter.cfi` where filter.cfi is a file
in the CFI script format.
Or a CFI script can be loaded from remote host like
`FTOCL=URL` via HTTP or FTP.
When the file name of CFI scripts or a filter command referred
in the script is specified in relative path name,
it is searched in [LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH).

**CFI script**

The CFI script is a simple script to select an appropriate filter
to be applied to a message data relayed on DeleGate, depending on
the type of data, the server name, the type of client, and so on.
A CFI script is text data which
starts with a magic string `"#!cfi"` and
contains more than one filter specifications
which are separated by `"--"` with each other.

```bash
  CFI script   == "!#cfi" NL filterUnit [ "--" NL filterUnit ]*
  filterUnit   == filterRule [ filterRule ]*
  filterRule   == matchingRule | rewriteRule | filterSpec
  matchingRule == matchingName ":" ruleBody
  matchingName == MIMEheader | X-header | CGIENV
  MIMEheader   == "Content-Type" | "User-Agent" | ...
  X-header     == "X-Status-Ver" | "X-Status-Code"
                | "X-Request-Method" | "X-Request-Ver"| "X-Request-URL" | ...
  CGIENV       == "REQUEST_METHOD" | "SERVER_PROTOCOL" | "SERVER_NAME"
                | "PATH_INFO" | "PATH_TRANSLATED" | "HTTP_USER_AGENT" | ...
  rewriteRule  == Action "/" MIMEheader : ruleBody
  Action       == "Output" | "Remove"
  filterSpec   == filterType ":" ruleBody
  filterType   == "Body-Filter" | "CGI" | "Header-Filter"
                | "MIME-Filter" | "Message-Filter"
  ruleBody     == string NL [ SP  string NL ]*
```

Input Format:

The input data to CFI script is a message of application protocol in
MIME format preceded with a request or a response status line of the
application protocol (HTTP, SMTP, POP, NNTP).
A MIME message is composed with a header and a body separated with
an empty line.

```bash
  CFIinputMessage == statusLine MIMEheader NL MIMEbody
```

Example: a simple HTTP response message

```bash
HTTP/1.0 200 OK           ... response status line
Content-Type: text/html   ... header
Content-Length: 20        ... header
                          ... header/body separator
body of the message       ... body
```

Matching Rule:

A *matchingRule* indicates matching the
`ruleName:ruleBody` to the input header.
It matches when the input message has a *ruleName* header with
a field body matches with *ruleBody*.
If at least one of matching rules turns to be true,
then the *filterUnit* is adopted.
If no matching rule is included in a *filterUnit* then
the *filterUnit* is adopted unconditionally.
Currently, only a limited set of MIME headers (in request or response
message) can be used for the matching.
Also, some extended headers can be used to match with information not
included in the original header (ex. “X-Status-Code” which means
status code in response message).
Matching with [CGI](http://hoohoo.ncsa.uiuc.edu/cgi/env.html)
environment variables.

Example: a matching rule

`#!cfi   HTTP_USER_AGENT: MSIE   SERVER_HOST: www1.dom1   SERVER_HOST: www2.dom2   X-Status-Code: 200   Content-Type: text/html   Content-Type: text/plain   Body-Filter: ...`

Rewriting Rule:

A *rewriteRule* with a prefix “*Action*/” to a
*ruleName*:*ruleBody* specifies some simple rewriting
using *ruleBody* data for relevant *ruleName* field.
“Output/*ruleName*:*ruleBody*” indicates appending (or replacing)
a *ruleName*:*ruleBody* field into the header.
“Remove/*ruleName*:*ruleBody*” indicates removing header fields
with name *ruleName* and body matches to *ruleBody*.

Filter Specification:

A *filterSpec* specifies a filter to be applied to the input data.
The whole or a part of input message will be passed to
the standard input of the filter program, then the output from the
standard output of it will be forwarded to the destination
(client or server) instead of the original input message.

```bash
  Body-Filter:    filter for MIMEbody
  CGI:            filter for MIMEbody
  Header-Filter:  filter for MIMEheader
  MIME-Filter:    filter for MIMEheader + MIMEbody
  Message-Filter: filter for statusLine + MIMEheader + MIMEbody
```

For filters of any type, the set of
[CGI](http://hoohoo.ncsa.uiuc.edu/cgi/env.html)
environment variables is passed.
In addition, CFI origin environments variables are passed including
“`SERVER_HOST`” (the name of the destination server),
“`REQUEST_URL`” (the URL of the request).

For filters of “Body-Filter” or “CGI”,
the “Content-Length” header in the forwarded message will be
adjusted to indicate the size of the body part after the filtering.
The output of “CGI” filter must preceded with the status header
of [CGI output](http://hoohoo.ncsa.uiuc.edu/cgi/out.html).

For filters of “Header-Filter”,
the header part of a message will be passed to and from the filter.
The *start-line* in the HTTP message (Request-Line or Status-Line)
will be passed as a header field prefixed with
“Request-Line:” or “Status-Line:”.

For filters of “MIME-Filter”,
the whole of the MIME message consists of a header and a body is passed
to and from the filter.

For filters of “Message-Filter”,
the whole message of the application protocol is passed to and from the filter
where each message consists of a MIME message prefixed with a line
representing request or response status in the application protocol.

Example: rewriting HTTP response messages

`SERVER=http FTOCL=test.cfi

## [content of test.cfi]  
#!cfi  
Content-Type: text/html  
Body-Filter: sed ‘s/string1/string2/’

Content-Type: image/gif  
Output/Content-Type: image/jpeg  
Body-Filter: gif2jpeg`

Example: dump available headers and environment variables

`#!cfi   Header-Filter: -tee-n-v /dev/tty   Body-Filter: env|sort > /dev/tty; cat`
**PROXYING BY URL REDIRECTION**

DeleGate with RELAY=“delegate” provides a special proxying without
changing “proxy configuration” in browsers.
When the URL of such DeleGate is http://*delegate*/,
a user can access target *URL* via the DeleGate
by giving a URL like http://*delegate*/-_-*URL* to the browser.
A request message for the URL from the client will be in form of
/-_-*URL* which is regarded as a request for *URL*
by DeleGate.
Then the DeleGate rewrites a URL included in a response messages to client
so that the access to the URL is directed to the DeleGate again.
This *redirection* is achieved by prefixing the URL of DeleGate
(http://*delegate*/) and “-_-” sign before original *URL* like
http://*delegate*/-_-*URL*.

U->C: *user opens* `http://delegate/-_-http://www/path1   C->D: GET /-_-http://www/path1   D->S: GET /path1   D<-S: HREF=/path2   C<-D: HREF=http://delegate/-_-http://www/path2   U->C:` *user clicks the anchor* `C->D: GET /-_-http://www/path2   D->S: GET /path2   S->D: HREF=ftp://ftp/path   D->C: HREF=http://delegate/-_-ftp://ftp/path`

Originally, this redirection mechanism was implemented for Gopher proxy,
and extended to HTTP protocol,
then extended to a generic MOUNT mechanism.
Now almost the same effect with “-_-” redirection can be emulated
with a MOUNT parameter like follows, allowing to replace “-_-” with
an arbitrary string.

`MOUNT="/-_-* *"`

You can write a DeleGate *switching table* in HTML.
Suppose that you have two DeleGate hosts connected to different network
provider each other, and you want to select one of them explicitly
but without changing configuration of your browser
and without typing a lengthy URL prefixed with “http://*delegate*/-_-”.
You can write a table in HTML to switch DeleGate like this:

<A HREF="http://proxy1:8080/-\_-http://www.w3.org/"> W3C via firewall1 </A>  
<A HREF="http://proxy2:8080/-\_-http://www.w3.org/"> W3C via firewall2 </A>

This table works independently of if the client is using DeleGate
or not,
because DeleGate does not do URL redirection in response message
described above if the URL is already redirected like above.

Right after the -_- mark, optional “/Modifier/” form can be inserted
as follows:

<http://delegate/-\_-/Modifier/URL>
Modifier can be a list of multiple Modifiers separated each other by
by comma (,) character.

cc.*outCode*[.*inCode*]
:   the character code of text data toward the client,
`"cc.JIS"` for example.

F*flags*
:   *flags* is a list of flag characters
“C” to disable cache,
“N” to force using not name but address overriding DELEGATE parameter,
“J” to make JIS (ISO-2022-JP) output overriding CHARCODE parameter,
and so on.
**PROTOCOL SPECIFIC ISSUE AND EXAMPLES**

Common Notation

# delegated …

:   implies invoking DeleGate by super-user to use a privileged port number

% delegated …
:   implies invoking DeleGate by non super-user

`firewall`% delegated …
:   implies running DeleGate on a host belongs to your site
and reachable to/from internet

`internal`% delegated …
:   implies running DeleGate on a internal host
in your site which is isolated from internet

`external`% …
:   implies doing something on a host external to your site**TCPrelay**

DeleGate with a SERVER=tcprelay parameter
relays communication between a client and a server
on a single TCP connection
without interpreting what is transmitted on it.
Thus an arbitrary application protocol on TCP,
even if it is not in supported protocol list of DeleGate,
can be relayed by SERVER=tcprelay.
But value added services, including caching, mounting and logging,
are not available in this case.
Connecting to arbitrary destination servers depending on a request from
a client is not possible.
Application protocols which dynamically create other connections besides
the main connection, like FTP, are not relayable.
Application protocols which exchange some kind of name depends on
an origin server on the protocol, like a full URL in HTTP,
are not relayable too.

Example: two proxies on TCP with similar function

# delegated -P25 SERVER=smtp://mailserver

# delegated -P25 SERVER=tcprelay://mailserver:25

**UDPrelay**

DeleGate with a SERVER=udprelay parameter
relays communication between a server and clients on UDP
without interpreting what is transmitted on it.
It has similar merits/demerits to tcprelay for TCP.
Also application protocols on which routing information are exchanged,
like CU-SeeMe, are not relayable with udprelay.

Example: two proxies on UDP with similar function

# delegated -P53 SERVER=dns://nameserver

# delegated -P53 SERVER=udprelay://nameserver:53

Example: a gateway between UDP and TCP

// UDP clients and a TCP server  
`# delegated -P53 SERVER=udprelay://nameserver:53 CONNECT=tcp`  
// TCP clients and a UDP server  
`# delegated -P53/tcp SERVER=udprelay://nameserver:53`

A pair of gateways like above can be used to convey UDP packets over TCP
connections, but such relaying (tunneling) is realized more efficiently
using[SockMux](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#UdpOverTcp) with a single TCP connection.

**DGAuth server**

“DGAuth” server by DeleGate provides Digest Authentication functionality
remotely, over an experimental “DGAuth” protocol.

Example: DGAuth-DeleGate server and its client

`hostS% delegated SERVER=dgauth -P8787   hostC% delegated SERVER=http -P8080 AUTHORIZER=`[-dgauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#dgauth)//hostS..8787

Example: DGAuth-DeleGate server and its client on the same host

`hostX% delegated SERVER=dgauth   hostX% delegated SERVER=http -P8080 AUTHORIZER=-dgauth`

A DGAuth server receives a set of components to be used to calculate
digest for each application protocol, then return the digest, as follows.

`Request:
:   HTTP user nonce realm method uri  
APOP user nonce [realm] (not used currently)

Response:
:   200 digest  
501 syntax error  
502 unknown user`
**PAM server**

PAM server by DeleGate provides PAM (Pluggable Authentication Modules)
functionality remotely,
over an experimental protocol compatible with HTTP (PAM/HTTP).

Example: PAM-DeleGate server and its client

`hostX% delegated -P8686 SERVER=httpam   hostY% delegated -P8023 SERVER=telnet AUTHORIZER=-pam//hostX/passwd`

Example: PAM-DeleGate server and its client communicating over SSL

`delegated hostX% -P8686 SERVER=httpam FCL=sslway   delegated hostY% -P8023 SERVER=telnet AUTHORIZER=-pam//hostX/passwd`[CMAP=sslway:FSV:pam](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#cond-filter)

Note that most of PAM authentications need to be executed under the
privilege of superuser on Unix (with OWNER=“root” option).
But you can avoid running your PAM-DeleGate server with superuser privilege by
installing external program “dgpam” under [DGROOT/subin/](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#subin).

The default port number of the experimental PAM/HTTP server is 8686.
Other ports can be specified as
[AUTHRIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER)=-pam//*host*..*port*,
for example as AUTHORIZER=”-pam//hostX..8765/passwd”.

PAM/HTTP protocol uses the format of HTTP compatible request/response
messages as follows.

`Request:
:   GET /-/pam/service/auth HTTP/1.0  
Authorization: Basic BASE64of(User:Pass)

Response (one of followings):
:   HTTP/1.0 200 OK, authorized  
HTTP/1.0 401 Not authorized  
HTTP/1.0 403 Forbidden to use the PAM server`
The base of request URL “/-/pam/” can be replaced with an arbitrary path
with PAMCONF=“baseurl:/*basePath*/”.
The whole request URL can be replaced by PAMCONF=“url:*/path*”.
The content of response message is not cared in the current specification
but it could convey some authentication related data or
capability information in future.

Following the format, you can easily develop your own PAM server,
instead of PAM-DeleGate, using your own HTTP server with CGI or so.

**FTPxHTTP server**

“FTPxHTTP” is a HTTP server which can be used for tunneling the FTP protocol
over HTTP by a (connectionless) sequence of usual HTTP requests
(not by CONNECT but by GET and POST).
It can be relayed by another HTTP proxy for forwarding, filtering or so.

Example:

`hostX% delegated -P8021 SERVER=ftp MOUNT="/* ftpxhttp://hostY:8080/*"   hostY% delegated -P8080 SERVER=ftpxhttp MOUNT="/* ftp://hostZ/*"`
client –FTP– <ftp://hostX:8021> –HTTP– <http://hostY:8080> –FTP– <ftp://hostZ>
**YYsh server**

The yysh server provides remote login and remote command execution
based on the YYSH and YYMUX protocol.

Example:

`hostX% delegated -P6023 SERVER=yysh   hostY% delegated -Fyysh hostX:6023`
**YYMUX server**

Example:

`hostX% delegated -P6010 SERVER=yymux   hostY% delegated -P8080 SERVER=http YYMUX=hostX:6010`

```bash
SOCKMUX parameter*  ==  SOCKMUX=host:port:option[,option]*
            option  ==  acc | con | ssl
                    --  default: none
                    --  status: tentative
```

If specified together with[SOCKS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SOCKS),
[PROXY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROXY), [MASTER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MASTER) (to chain two DeleGate),
then the communication between DeleGate is multiplexed on a single
persistent connection using [SockMux](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#proto_SockMux).
This is useful to reduce the delay to establish many connections repeatedly
between DeleGate which are running distant from each other with long RTT.

*host*:*port* specifies the port toward which a SockMux
persistent connection is established.
The connection is established from the DeleGate with “`con`”
option to the DeleGate with “`acc`” option.

Options:

`acc --` accept a SockMux connection at “*host*:*port*”.  
`con --` connect a SockMux connection to “*host*:*port*”.  
`ssl --` use SSL instead of the “Credhy” encryption.

Example: SOCKS proxies chained over SockMux

`hostA% delegated SOCKMUX=hostA:8000:acc SERVER=socks -P2080`  
`hostB% delegated SOCKMUX=hostA:8000:con SERVER=socks -P1080 SOCKS=hostA:8000`

Example: SOCKS proxies chained over SockMux connected from the server side

`hostA% delegated SOCKMUX=hostB:8000:con SERVER=socks -P2080`  
`hostB% delegated SOCKMUX=hostB:8000:acc SERVER=socks -P1080 SOCKS=hostA:8000`

Example: HTTP proxies chained over SockMux

`hostA% delegated SOCKMUX=hostA:8000:acc SERVER=http -P9080`  
`hostB% delegated SOCKMUX=hostA:8000:con SERVER=http -P8080 PROXY=hostA:8000`

Example: HTTP via SOCKS proxy chained over SockMux

`hostA% delegated SOCKMUX=hostA:8000:acc SERVER=socks -P2080`  
`hostB% delegated SOCKMUX=hostA:8000:con SERVER=http -P8080 SOCKS=hostA:8000`

```bash
SOXCONF parameter*  ==  SOXCONF=confSpec[,confSpec]*
                    --  default: none
```

crypt:no
:   disable the encryption of SockMux packets.

packsize:*SIZE* [16k]
:   specify the size of a SockMux packet,
128 in minimum and 16k at the maximum.
**SockMux server**

SockMux is an experimental protocol designed for inter-DeleGate communication.
It is a simple protocol for “port forwarding” to accept, relay and destroy
connections, multiplexed over a single persistent connection.
A pair of SockMux-DeleGate establish and retain a connection between them,
then forward port from local to remote each other over the connection.

The persistent connection is established with “-P*host:port*” parameter
at receptor side, and “SERVER=sockmux://*host:port*” at connector side.
The port to accept outgoing connections to be forwarded to remote is specified
with PORT=”*listOfPorts* parameter.
The server to be connected for incoming connections from remote is specified
with a postfix string “,-in” like SERVER=“telnet://host:23,-in”.

An incoming connection can be processed with DeleGate as a proxy of the
specified protocol.
If only protocol name is specified like SERVER=“telnet,-in”, or if “-in”
is postfixed like “-in(*option list*)”, then a DeleGate is
invoked to process the connection.
The *option list* is passed to the invoked DeleGate as the list of
command line options.
For example, SERVER=“telnet://host,-in(+=config.cnf)” will invoke a DeleGate
with command line options like ``delegated SERVER=telnet://host +=config.cnf’’.

Example: bi-directional SockMux-DeleGate

`hostX% delegated SERVER=sockmux -PhostX:9000 PORT=9023 SERVER="telnet://hostX,-in"   hostY% delegated SERVER=sockmux://hostX:9000 PORT=9023 SERVER="telnet://hostY,-in"`
// a pair of SockMux-DeleGate is connected at the port “hostX:9000”, then  
// the port “hostX:9023” is forwarded to “telnet://hostY”  
// the port “hostY:9023” is forwarded to “telnet://hostX”

Example: uni-directional SockMux-DeleGate

`hostX% delegated SERVER=sockmux -PhostX:9000 SERVER="telnet://hostX,-in"   hostY% delegated SERVER=sockmux://hostX:9000 PORT=hostY:9023`
// hostY:9023 is forwarded to “telnet://hostX”.

Example: uni-directional to proxy-Telent-DeleGate

`hostX% delegated SERVER=sockmux -PhostX:9000 PORT=hostX:9023   hostY% delegated SERVER=sockmux://hostX:9000 SERVER="telnet,-in"`
// hostX:9023 is forwarded to a Telnet proxy on hostY.

When SockMux is used just to relay data between sockets, without
interpreting the application protocol relayed over SockMux,
such relaying can be represented with simpler expression using
DEST parameter instead of SERVER as follows:

`DEST`=*host*:*port*[:*srcHostList*]
for
`SERVER`=tcprelay://*host*:*port*,-in[:-:*srcHostList*]

`DEST`=*host*:*port*/udp[:*srcHostList*]
for
`SERVER`=udprelay://*host*:*port*,-in[:-:*srcHostList*]

Example: tcprelay over SockMux

`hostX% delegated SERVER=sockmux://hostY:9000 PORT=hostX:111   hostY% delegated SERVER=sockmux -PhostY:9000 DEST=hostT:111`
// hostX:111/tcp is forwarded to the server at hostT:111/tcp via hostY.Example: relaying UDP over SockMux/TCP

`hostX% delegated SERVER=sockmux://hostY:9000 PORT=hostX:53/udp   hostY% delegated SERVER=sockmux -PhostY:9000 DEST=hostU:53/udp`
// hostX:53/udp is forwarded to the server at hostU:53/udp via hostY.

Another way to establish a persistent connection between
two SockMux-DeleGate is using a FIFO device like named pipe.
It is specified like SERVER=sockmux:*commtype*@*fifoName*
where *commtype* is one of “commin”, “commout”, and “comm”,
which represents uni-directional input, uni-directional output and
bi-directional input/output respectively.

Example: use fifo device on a host

% mkfifo /tmp/com0  
% mkfifo /tmp/com1  
serv1) SERVER=sockmux:commin@/tmp/com0 SERVER=sockmux:commout@/tmp/com1 …  
serv2) SERVER=sockmux:commin@/tmp/com1 SERVER=sockmux:commout@/tmp/com0 …

Example: use communication port between two hosts (not tested yet)

host1) SERVER=sockmux:comm@com1 …  
host2) SERVER=sockmux:comm@com2 …

The persistent connection can be established by a given external
program invoked by DeleGate.
The process of the program is passed a socket to/from DeleGate at
file descriptor number 0 and 1;

Example: establish connection by external command

% SERVER=“sockmux:proc@*connectCommand*” …

The destination SERVER for an incoming connection from remote can be
selected depending on which port it was accepted.
A SERVER parameter postfixed with
“[:-:](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SERVER_mount)-P*xxxx*”
will be applied only to connections which is accepted on remote host
with PORT=*xxxx*.

Example: forwarding multiple port

`hostX% ... PORT=8023,8080   hostY% ... SERVER=telnet,-in:-:-P8023 SERVER=http,-in:-:-P8080`
// hostX:8023 is forwarded to Telnet-proxy on hostY  
// hostX:8080 is forwarded to HTTP-proxy on hostY

NOTE: forwarding FTP data connection is not supported (yet).

```bash
HTMUX parameter     ==  HTMUX=sv[:[hostList][:portList]]
                     |  HTMUX=cl:host:port
                     |  HTMUX=px:host:port
                    --  restriction: requires CAPSKEY
                    --  default: none
```

HTMUX is used to accept requests at a port which is not directly accessible from
a DeleGate to serve the requests. Typically it is a port on a remote host.
HTTP DeleGate acts as a HTMUX server when given `HTMUX=sv` parameter.
A DeleGate for any application protocol can act as a HTMUX client specifying its
HTMUX server with `HTMUX=cl:host:port` parameter.
A HTMUX server accepts TCP connections at a port (specified by a HTMUX client)
on the host and relays the connections to HTMUX clients.

Not only incoming connections but also outgoing connections from a HTMUX client
is established via the HTMUX server by default.
This might not necessary for a DeleGate that relays incoming request to
internal server. In such case, use the CONNECT parameter to specify such
connections to be established directory, as `CONNECT="direct:*:192.168.1.*"`
for example.

Example:

`hostX% delegated -P192.168.1.1:9876 HTMUX=sv SERVER=http   hostI% delegated -Pxx.xx.xx.xx:8080 HTMUX=cl:192.168.1.1:9876 SERVER=http   hostJ% delegated -Pxx.xx.xx.xx:8021 HTMUX=cl:192.168.1.1:9876 SERVER=ftp`

This example implies that `hostX` is a multi-homed host with
a private addresses 192.168.1.1 and a global address xx.xx.xx.xx.
The DeleGate on `hostX` acts as a HTMUX server.
HTTP DeleGate on `hostI` and FTP DeleGate on `hostJ` act as
HTMUX client which remotely accepts requests (arrived at xx.xx.xx.xx) via
the HTMUX server on `HostX`.

A pair of HTMUX server and client uses a single persistent connection to relay
multiple parallel connections on it multiplexing them by the
[SockMux](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#proto_SockMux) protocol.  
This feature must not be exploited maliciously, for example to invite
incoming connections violating a restriction on a firewall.
Therefore you need to install [CAPSKEY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CAPSKEY) to enable this feature.
Other usages of HTMUX being disabled by default are
non-direct connection between client and server (connection via NAT or proxy),
too large clock skew between client and server (300 seconds by default),
or inserting SSL encryption between client and server.

There are two ways to enable non-direct connection for HTMUX.
One way is to install a CAPSKEY to enable indirect HTMUX connection.
Another way is inserting a HTMUX proxy as the following example.

Example: cascading HTMUX with a HTMUX proxy

`hostX% delegated -PhostX:9876 HTMUX=sv SERVER=http   hostI% delegated -PhostI:6789 HTMUX=px:hostX:9876 SERVER=http   hostJ% delegated -PhostX:8080 HTMUX=cl:hostI:6789 SERVER=http`

The persistent connection between HTMUX client and server is capable to
convey connections bi-directionally,
thus can be used to make a pair of proxies over it.
Each proxy accepts requests at the local port and forwards them to the
remote peer as the following example.

Example: using HTMUX to make symmetric proxies (the simplest generic configuration)

`hostX% delegated -P9876 HTMUX=sv SERVER=http   hostY% delegated -P8080 HTMUX=cl:hostX:9876 SERVER=http`

In this example, -P8080 is equivalent to a wild-card address expression
“-P*:8080” to accept from the port number 8080 on any network interfaces
on the host.
Therefore requests to the port 8080 on any interface on hostX is forwarded
to the servers via the DeleGate on hostY as a HTMUX client (and a HTTP proxy).
Symmetrically, requests to the port 8080 on any interface on hostY is
forwarded to the servers via the DeleGate on hostX as a HTTP proxy (and a
HTMUX server at hostX:9876).

(Again, note that this feature is disabled by default and needs
[CAPSKEY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CAPSKEY) to enable it)

The port to be used on the server side and on the client side can be specified
separately with the “/local” and “/remote” modifiers for
[-P](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P) or [-Q](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_Q) option.
“/local” marks a port to be used on the local host (on a HTMUX client),
and “/remote” marks the port to be used on the remote host (on a HTMUX server).
The specification “-P8080” in the above example is equivalent to
“-P*:8080/remote,*:8080/local”.

Example: using HTMUX bi-directionally

`hostX% delegated -PhostX:9876 HTMUX=sv SERVER=http   hostI% delegated -Plocalhost:8081 HTMUX=cl:hostX:9876 SERVER=http   hostJ% delegated -P8082/remote,8083/local HTMUX=cl:hostX:9876 SERVER=http`

In this example, between `hostX` and `hostI`,
requests to `localhost:8081` on each host are forwarded to the peer
(equivalent to “`-Plocalhost:8081/remote,localhost:8081/local`”)
Between `hostX` and `hostJ`,
`hostX:8082` and `hostJ:8083` are forwarded to the peer
(equivalent to “`-PhostX:8082/remote,hostJ:8083/local`”)

Example: using HTMUX only for outbound requests

`hostX% delegated -PhostX:9876 HTMUX=sv SERVER=http   hostI% delegated -Plocalhost:8084/local HTMUX=cl:hostX:9876 SERVER=http`

This is an example to use HTMUX only for outbound requests.
It works even without the HTMUX parameter, but with HTMUX, a single
persistent connection is used between the server and client.
This usage of HTMUX is enabled by default when DeleGate is executed
in foreground (with [-fv](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_f) option,
running not as a service or a daemon),
without restrictions described as above, and don’t require CAPSKEY.

```bash
CAPSKEY parameter*  ==  CAPSKEY=opaque
                    --  default: none
```

Some functionalities of DeleGate are disabled by default and need
CAPSKEY to be enabled.
You can get automatically issued CAPSKEY for evaluation use via mail.
Run DeleGate as “`delegated -Fcapsreq ADMIN=Email-address`”
and follow the instruction shown in the output.
**Socks server**

Socks-DeleGate with SERVER=socks accepts both SocksV4 and SocksV5,
whereas SERVER=socks4 and SERVER=socks5 accepts only SocksV4 and SocksV5
respectively.
Currently, only USER/PASS authentication scheme of SocksV5 is supported.

Example: Socks-DeleGate

`# delegated -P1080 SERVER=socks`
Example: forwarding to an upstream Socks server

`# delegated -P1080 SERVER=socks SOCKS=sockhost`

To accept an incoming TCP connection via a SOCKS-DeleGate server,
the network interface to be used for it is selected automatically
by DeleGate (based on the DST.ADDR or DSTIP which is sent from
a SOCKS client as the parameter of the BIND command).
With the[SRCIF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF) parameter, you can select a network
interface (and port number) manually, with the pseudo protocol name “tcpbind”.
The complete syntax of the parameter is
SRCIF=
“[*host*]:[*port*]:tcpbind[:*dstHostList*[:*srcHostList*]]”.
Typically, only the *host* filed is specified to select a network
interface, like SRCIF=“150.29.202.120::tcpbind” for example.

**NOTE**: When you chain DeleGate with another SOCKS server, it may
cause problems in UDP relaying due to the private and tentative
extensions to the SOCKS protocol by DeleGate.
The following SRCIF parameters can be useful to escape such problems.

- `SRCIF="host:port:socks-udp-tosv"`
  – network interface to servers  
  `SRCIF="0.0.0.0:0:socks-udp-tosv"`
  makes DeleGate as a SOCKS client behave compliantly to
  the SOCKSv5 specification on UDP ASSOCIATE.
- `SRCIF="host:port:socks-udp-tocl"`
  – network interface to clients  
  `SRCIF="0.0.0.0:0:socks-udp-tocl"`
  suppresses the failure in DeleGate as a SOCKS server
  trying to bind a UDP socket to a specific port number.

```bash
SOCKSTAP parameter*  ==  SOCKSTAP=ProtoList[:[dstHostList][:[srcHostList][:params]]]
                     --  default: none
```

If specified with a SOCKS server, the data stream relayed over the SOCKS is
interpreted in each application protocol.
For example, with `SOCKSTAP=http`, the delegated act as a server
of SERVER=http when the relayed protocol is detected to be the HTTP protocol.

Example: Socks-DeleGate which do caching for HTTP and FTP

`% delegated -P1080 SERVER=socks CACHE=do SOCKSTAP=http,ftp`

Example: Socks-DeleGate which do caching for HTTP with an upstream proxy

`% delegated -P1080 SERVER=socks SOCKSTAP="http:::CACHE=do PROXY=pxserv:8080"`

See[http://www.delegate.org/delegate/sockstap/>](http://www.delegate.org/delegate/sockstap/)
for more details.

**HTTP proxy/server**

Example: DeleGate as an HTTP proxy

`firewall% delegated -P8080 SERVER=http`

Then use this DeleGate from your client on the internal host,
specifying “*firewall*:8080” as the proxy for
HTTP, HTTPS (Security), FTP, Gopher, Wais, and so on.

Example: cascaded DeleGate as an HTTP proxy

`firewall% delegated -P8888 SERVER=delegate RELIABLE=internal   internal% delegated -P8080 SERVER=http MASTER=firewall:8888`

Run a generalist DeleGate on the *firewall* which only accepts
request from *internal* host,
then run a specialist on *internal* which use the generalist
on *firewall* host.
A generalist can be shared as an upstream DeleGate from multiple
DeleGates of arbitrary protocol.

Example: DeleGate as an origin HTTP server

`host# delegated -P80 SERVER=http \ :   MOUNT="/* /path/of/www/*" RELAY=no RELIABLE="*"`

A file with a name with “.cgi” extension is treated as a CGI script.
Also you can use arbitrary name of CGI scripts under a specified
directory with a MOUNT like:  
`MOUNT="/xxx/* cgi:/path/of/cgi-bin/*"`Example: DeleGate as a CGI program

You can use DeleGate as a CGI program from a HTTP server. For example,
specify in the “httpd.conf” file of your HTTP server(A) as follows.

Exec /other/* /path/of/cgi-delegate
Then write the content of the file /path/of/cgi-delegate as follows:

`#!/bin/sh

delegated -Fcgi
:   MOUNT=”/-* =” \  
MOUNT=”/www2/* <http://wwwserv2/>*” \  
MOUNT=”/news/* nntp://newsserv/*”`
This will add a pseudo sub tree “/other/” onto server(A)
including
/other/www2/ which is a content of a HTTP server “wwwserv2”, and
/other/news/ which is a content of a NNTP server “newsserv”.
HTTP Transfer Log Format

The format of PROTOLOG for HTTP protocol can be modified with a
optional format specification postfixed after the *LogFilename* as
PROTOLOG=”*LogFilename*:*format*”.
In this case, default file name can be omitted.
For example, `PROTOLOG=":%X"` specifies making a NCSA like
extended common logfile format.
The default format is
`PROTOLOG=":%X %D"` in version 10 while it was
`PROTOLOG=":%C %D"` in version 9.

|          |                                                                                                                    |
|----------|--------------------------------------------------------------------------------------------------------------------|
|`%C`      |– common logfile format of CERN-HTTPD                                                                               |
|`%c`      |– same as %C except the date is recorded in millisecond precision                                                   |
|`%D`      |– extension by DeleGate (`connTime+relayTime:status`)                                                               |
|`%X`      |== `'%C "%r" "%u"'` common logfile format with Referer and User-Agent                                               |
|`%r`      |– Referer field in the request message                                                                              |
|`%u`      |– User-Agent field in the request message                                                                           |
|`%S`      |– status of CONNECTion to the server (c,m,p,d,s,v)                                                                  |
|`%s`      |– session Id by HTTPCONF=[session](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#http_session)|
|`%As`     |– session Id in Digest Authorization                                                                                |
|`%{field}`|– arbitrary field in the request message                                                                            |

The client information part in %C, which records hostname, Ident,
and username by default, can be modified by AUTH=“log:” parameter.

The session identifier put by “%s” is generated by specifying
HTTPCONF=[session:cookie](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#http_session) option while
“%As” is generated by AUTHORIZER=[-dgauth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#dgauth) option.
The format of session identifier is as this:

*time*.*pid*.*proc#*+*conn#*[+*req#*].*reqnum*

For example, “031114-173045.1234.5+6+7.9” means that
it is the 9th request from the client
in the session started at 17:30:45 on November 14 by the process of PID=1234.
The start of the session is recorded in LOGFILE as this:

11/14 17:30:45 [1234] 5+6/7: NewSession 031114-173045.1234.5+6+7.0

Note that the *reqnum* part may not be unique because of parallel or
pipelined requests generated by a client as the owner of the session.
Note that the *reqnum* part for “%As” may not be incremented on each
request because the container of session identifier,
the opaque” parameter in Digest Authentication in this case,
may not be updated on each request.

```bash
HTTPCONF parameter  ==  HTTPCONF=what:conf
```

welcome:listOfWelcomeFiles:   – default: welcome.{[dgp](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#dgp),[shtml](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSI.shtml),html,cgi},index.{dgp,shtml,html,cgi},-dir.html

```
A list of index files or CGI scripts which should be used for URLs
of directories ending with "/" like "/path/". This is a list of
candidate file names. The list may be ended with "-dir.html" which
means a built-in index generator. If the list is empty, empty data
is substituted for index data.
```

search:pathOfSearchScript
:   – default: none  
The path of a CGI script to be applied for URLs with search part like
“/path?search”. This is a global specification applied for all URLs.
Also you can specify a local search script for each MOUNT point like

```
`MOUNT="/path2/* /root/of/path2/* search:script2".`
This local specification is prior to the global one. A special local
specification "search:-" can be used just to ignore the global
specification for the MOUNT point.
```

nvserv:noauto | auto | alias | gen | none
:   – default: HTTPCONF=nvserv:noauto  
Automatically detects virtual servers in MOUNT parameters and notate
each of them as a MOUNT rule to be applied only to a virtual server.
It can be done manually by specifying “[nvserv](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#nvserv)” MountOption
for each MOUNT parameter.
“nvserv:alias” means detecting target servers of host names with
common IP-addresses and notate them as virtual servers.
“nvserv:gen” means notating MOUNT parameters with “genvhost”
MountOption as virtual servers.
“nvserv:auto” is equivalent to “nvserv:alias,gen”.
The guessing can be overridden by explicitly specifying
the [avserv](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#nvserv) MountOption for each MOUNT parameter.
“nvserv:none” disables any treatment of virtual servers which are
detected automatically or specified explicitly by the “nvserv” MountOption.

methods:*listOfAcceptableMethods*
:   – default: methods:OPTIONS,GET,HEAD,POST,PUT,…  
– See the output to LOGFILE with HTTPCONF=methods:”+”  
Limit or add HTTP methods to be accepted.

```
Example:

`HTTPCONF=methods:GET,HEAD -- accept only GET and HEAD  
HTTPCONF=methods:-POST,-PUT -- don't accept POST and PUT  
HTTPCONF=methods:+,NEWMETHOD1 -- add NEWMETHOD1 to be accepted  
HTTPCONF=methods:* -- accept any methods`
```

rvers:*listOfAcceptableResponseVersions*
:   – default: rvers:HTTP  
Add versions in response message from HTTP servers.

```
Example:

`HTTPCONF=rvers:+,ICY  
HTTPCONF=rvers:* -- accept any response version`
```

post-ccx-type:*listOfTypes*:   – default: post-ccx-type:x-www-form-urlencoded  
Specify the list of names of Content-Type of request message to which
conversion by[CHARCODE](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHARCODE) is applied.

```
Example:

`HTTPCONF=post-ccx-type:+,multipart/form-data`
```

cryptCookie:*listOfCookies*:*cryptKey*:   *listOfCookies* == *attributes*[@*domains*]  
*attributes* == *attribute* | {*attribute*,*attribute*,…}  
*domains* == *domain* | {*domain*,*domain*,…}  
*domain* == [.]*domainName*  
*cryptKey* == *string* |[`%a` | `%P`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen)

```
encrypt specified attributes in a Set-Cookie response to be stored in a client,
then decrypt and forward the Cookie request only to the originator
of the Cookie.
An attribute in a Cookie is specified as "*attribute*@*host*"
or "*attribute*@.*domain*".
In the former case, a cookie generated by a *host* is encrypted
and echoed to *host* only.
In the latter case, a cookie generated by hosts in the *domain*
can be echoed to hosts in the *domain*.
The special string "`%a`" in *cryptKey* is substituted by
the IP-address of the client. This makes the crypted Cookie be usable
only by clients on the host of the IP-address.

Example:

`HTTPCONF="cryptCookie:SessionID@host1.dom1,UserID@.dom2:nanjamonja"  
HTTPCONF="cryptCookie:UserID@.dom:nanjamonja"  
HTTPCONF="cryptCookie:UserID@{host1.dom,host2.dom}:nanjamonja"`
```

kill-[i][qr]head: *listOfHeaders*
:   erase header fields listed in *listOfHeaders* before forwarding
a request/response message to server/client. “kill-qhead” is applied
only to request message to server and “kill-rhead” is applied only to
response message to client.
If “i” is prefixed as “kill-iqhead:Pragma,Cache-Control”, the specified
fields are erased before DeleGate interpret it as the HTTP headers.

```
Example:

`HTTPCONF=kill-qhead:Referer  
HTTPCONF=kill-qhead:If-*,Accept-*  
HTTPCONF=kill-rhead:Set-Cookie`
```

add-[i][qr]head:*name*:*body*
:   add a header *name*:*body* to forwarded request/response message.
Client’s identity information can be inserted into *body* string
with “%[format](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen)” notation.
If “i” is prefixed as “add-ihead:Pragma:no-cache”, then the specified field
with the body is added to the input to be interpreted by DeleGate
as a HTTP header from the client or the server.

```
Example:

`HTTPCONF="add-qhead:X-Forward-For:%a"`
```

replace-[i][qr]head:*name*:*body*
:   replace headers of “*name:*” with “*name*:*body*”
in forwarded request/response message.
This is equivalent to the combination of
`kill-head` and `add-head`.
Example:

`HTTPCONF=replace-qhead:Referer:http://x.y.z   HTTPCONF=kill-qhead:Referer HTTPCONF=add-qhead:Referer:http://x.y.z`

kill-tag: *listOfTags*
:   disable a tag listed in *listOfTags* when it it used in
a text/html response from a server.

```
Example:

`HTTPCONF=kill-tag:SCRIPT,APPLET`
```

ver:1.0
:   act as a HTTP/1.0 client/server

svver:1.0
:   act as a HTTP/1.0 client against servers (send request in HTTP/1.0)

clver:1.0
:   act as a HTTP/1.0 server against clients
(do not use chunked encoding in response)

acc-encoding:*encoding* [-thrugzip]
:   Accept-Encoding header to be sent to server.
This is applied to DeleGate which does some interpretation of content
with MOUNT, CHARCODE, CACHE, etc. To do such interpretation, the content
(response body) is not to be encoded in a format unknown to DeleGate.
“identity” specifies disabling any encoding of content in the server.
“-thrugzip” specifies forwarding Accept-Encoding:gzip from client to server.
If the program “gzip” is not available on the host of DeleGate
(i.e. not found in [LIBPATH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LIBPATH)),
“identity” is sent regardlessly.

gen-encoding:*encoding* [gzip]
:   The encoding applied to the content sent from DeleGate to client.
Only “gzip” is available in the current implementations.
“identity” and others disable any encoding.

tout-wait-reqbody:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [30]
:   max. period to wait the first data in request body.

tout-in-reqbody:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [15]
:   max. period to wait next data in request body.
(adjustable for a slow filter program at the client side)

tout-buff-reqbody:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [5]
:   max. period to do buffering request message to server

tout-buff-resbody:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [8]
:   max. period to do buffering response message to client

tout-cka:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [5]
:   max. period to keep a connection with the client alive.
(the timeout is ten times longer for the first connection from each client host)
max-cka:*number* [50]
:   max. number of requests to be relayed on a single connection
in keep-alive.
(ten times larger value is given to the first connection from each client host)

```
This is applied to the communication over a connection of SSLtunnel by the
CONNECT method too. A pair of upstream and downstream data is
regarded as a pair of request and response on HTTP, then the maximum
number of such pairs is restricted.
```

max-ckapch:*number* [8]
:   max. number of connections in keep-alive at a time for each client host.

max-reqline:*length* [8k]
:   max. length of request line to be accepted.

max-reqhead:*length* [12k]
:   max. length of request header to be accepted.

max-gw-reqline:*length* [512]
:   max. length of request line to be forwarded to another server
in another protocol.

max-hops:*number* [20]
:   max. number of hops in the chain of HTTP proxies.

tout-resp:[*period*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#period-value) [TIMEOUT=[io](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TIMEOUT-io)]
:   max. period to wait response from server.

tout-pack-intvl
[10.0]:   max. interval between packets relayed on [SSLtunnel](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SSLtunnel)
by the CONNECT method.

halfdup
:   Forbid full-duplex usage of SSLtunnel by the CONNECT method.

urlesc[:*escChars*] [*empty*]
:   the set of characters in request URL to be escaped by “%*XX*”
notation before any processing.
As a special case, HTTPCONF=“urlesc” means HTTPCONF=“urlesc:<>”.

mypro.xyz:{forw,thru,stop}
:   By default, an access to the virtual domain name
“http://[mypro.xyz](http://www.delegate.org/mypro.xyz/)”
is interpreted as an access to your proxy server.
HTTPCONF=“mypro.xyz:forw” enables forwarding the request to
upstream proxies by prefixing the hop count.
HTTPCONF=“mypro.xyz:thru” disables this interpretation and
forward the request to the upstream proxy if exists.
HTTPCONF=“mypro.xyz:stop” stops this interpretation and forwarding at all.
Another way for restriction of access to mypro.xyz is using AUTHORIZER
as AUTHORIZER=”-list{User:Pass}:*:*.mypro.xyz:*”.
proxycontrol[:{on|off}]
:   consume substring following “?_?” in request URL as control information for
the DeleGate; when DeleGate get request *URL*?_?*proxycontrol*,
only *URL* part is forwarded to the server
and *proxycontrol* part is (possibly) used by DeleGate.

cka-cfi
:   make connection with the client keep-alive even with external filter
(FCL, FTOCL).

nolog:*listOfCodeType*[:[connMap](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#connMap)]
:   *listOfCodeType* == [ *respCode* / ][ *Type* [ / *subType* ] ]

```
specify response code or Content-Type of response message
not to be logged in access log ([PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#PROTOLOG)).

Example:

`HTTPCONF="nolog:302,304,image"`
```

xferlog:ftp
:   record FTP/HTTP transactions in [xferlog](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#xferlog) format too.

bugs:*listOfBugs*
:   *listOfBugs* is a list of features to be disabled
to bypass possible bugs as follows:

```
no-gzip ... disable Content-Encoding:gzip

no-keepalive ... disable Connection:Keep-Alive

no-keepaliveproxy ... disable Connection:Keep-Alive with client side proxy

no-chunked ... disable Transfer-Encoding:chunked

no-flush-chunk ... disable flushing response after each chunk

kill-contleng ... erase original Content-Length in chunked encoding

add-contleng ... add or update Content-Length even in chunked encoding

do-authconv ... enable Authentication conversion from client's Basic to server's Digest
```

bugs:thru-304
:   disable the conversion from “304 Not Modified” to “200 Ok” in the message
as the response to a conditional request with the “If-Modified-Since” header.
DeleGate with external filters tries to return a HTTP response messages with
a body (with the code “200 Ok”) when it is filtered (and possibly rewritten)
by the filters even if the body should be returned as empty (304 Not Modified)
based on the modification date (Last-Modified) of the target data.
This is necessary to return data rewritten dynamically by filters, but it
disables the merit by the conditional request and the “304” response.
“thru-304” turns the above conversion off and let DeleGate pass through
“If-Modified-Since” request from clients and the “Last-Modified” and
“304 Not Modified” response from servers.

svauth:no-basic
:   Stop forwarding Basic Authorization (which contains cleartext password)
from client to server.
If the server supports Digest authentication, then the DeleGate do it
by proxy of the client.

svauth:less-basic
:   Postpone forwarding Basic Authorization from client to server until
the server requires the Basic Authentication.
session:cookie:   Enable session management based on Cookie.
The[session identifier](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#http_session_log)
is passed to CFI/CGI programs in
environment variable “X_COOKIE_SESSION”, and
can be logged into [PROTOLOG](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#http_session_log).

```
Example:

`HTTPCONF=session PROTOLOG=":%s %X"`
```

Example:
:   `HTTPCONF=search:/path/of/searchScript   MOUNT="/bin/* cgi:/path/of/cgi-bin/* search:-"   MOUNT="/* file:/path/of/data/*"`

```bash
FILETYPE parameter  ==  FILETYPE=suffix:gopherType:altText:iconName:contentType
                    --  default: FILETYPE=".txt:0:TXT:text:text/plain"
                                 FILETYPE=...
```

Define file name to content-type mapping.

*gopherType*:
:   0 - text,
1 - directory,
4 - BinHex,
6 - uuencode,
9 - binary,
g - gif,
I - image,
…

*altText*:
:   alternative text which should be displayed for the icon image
in text only displays
(embedded into IMG tag in HTML text like <IMG ALT=”*altText*” … >)

*iconName*:
:   one of binary, binhex, compressed, directory, document, ftp, gzip,
image, index, index2, movie, sound, tar, telnet, text, unknown, uu
(see http://*delegate*/-/builtin/icons/)

*contentType*::   text/plain,
image/gif,
…
(see[RFC2045](ftp://ftp.ietf.org/rfc/rfc2045.txt))

Example:

FILETYPE=”.txt:0:TXT:text:text/plain”  
FILETYPE=”.gif:g:GIF:image:image/gif”

```bash
CGIENV parameter    ==  CGIENV=name[,name]*
                    --  default: CGIENV="*"
```

A list of environment variables to be passed to CGI program.

```bash
MountOptions for HTTP-DeleGate
```

CONDITIONS:

vhost={*HostList*} – virtual host matching and rewriting.
:   true if the value of the “Host:” field in the request message is included
in the *HostList* for request rewriting, and true unconditionally
for response rewriting.
It supports *virtual hosting* by a special rewriting for response,
that is, any full-URL of a real host in a response message will be
rewritten to that of a virtual host.

avhost={*HostList*} – address based virtual hosting
:   equivalent to the “vhost” option.

nvhost={*HostList*} – name based virtual hosting:   similarly to “vhost” option, “nvhost” is used to configure virtual hosting
except that this option is restricted to create name based virtual hosts
which are distinguished each other only by their host names.
Each virtual host is identified textually by its name (thus no “-” prefix
for each host is necessary to force textual-only matching which is necessary
with the “vhost” option).
For example, the following two MOUNT parameters are equivalent to each other.

```
`MOUNT="/* http://server/* vhost=-www.domain"`  
`MOUNT="/* http://server/* nvhost=www.domain"`
  
A special option `"nvhost=-thru"` can be used
to ease forwarding a virtual domain name indicated by a client to a server.
The option means matching with virtual domain name to be sent to the target
server.
By default, the domain name can be specified explicitly with the[nvserv](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#nvserv) or the target server name in the *rURL*
of this MOUNT rule by default.
For example, the following three MOUNT parameters are equivalent mutually.
  
`MOUNT="/* http://domain/* nvhost=-thru,rserv=server"`
  
`MOUNT="/* http://server/* nvhost=-thru,nvserv=domain"`
  
`MOUNT="/* http://server/* nvhost=domain,nvserv=-thru"`
```

qmatch=*pattern* – pattern matching in the request header
:   true if the *pattern* matches with string in the request header.
(ex. qmatch=*User-Agent:*compatible;%20MS*)

dstproto={*ProtoList*} – to the server of specified protocol
:   true if the protocol of the destination server is in the *ProtoList*.

method={*methodList*} – request method
:   true if the access method of the current request is included in the
*methodList*.

asproxy
:   true if the DeleGate is called as a proxy server that is
the requested URL is in full URL format.

!asproxy
:   true if the DeleGate is not accessed as a proxy server in the request.

withquery
:   true if the requested URL has “?*query*” component

CONTROLS:

authorizer=*authServList*
:   the [AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER) which is to be applied to this MOUNT point.
If AUTHORIZER is specified in both MountOption and command line option,
the one in MountOption is used.

moved[={300|301|302|303}]
:   don’t relay to [*rURL*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MOUNT) but return response for redirection
as “302 Moved” with “Location:*rURL*”.
Redirection within the same server can be eased using the
[abbreviation](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountAbbrev) of host-name in the *rURL*
like MOUNT=”/path1 ///path2 moved”.

referer
:   Apply the rewriting only to the Referer: field to be forwarded.
This is an synonym of “where=ref”.

useproxy[=*proxyURI*]
:   generate “305 Use Proxy” response message.
If proxyURI is omitted or given as “direct”, the response
message is sent with Set-Proxy field as “Set-Proxy: DIRECT”.
Otherwise the URI is set in the field as
“Set-Proxy: SET; proxyURI=proxyURI”.

realm=*realmString*
:   specify the realm of authentication.

forbidden
:   reject the request as forbidden (synonym of “rcode=403”)

unknown
:   reject the request as unknown (synonym of “rcode=404”)

rcode={300|301|302|303|304|305|306|403|404}
:   return the response with the specified status code,
which can be useful for customizing error messages.
onerror[=*listOfCodes*]
:   this MOUNT entry is used to substitute a response message when an
error occurred.
It is applied If the response status code for the request shows an error (4xx
or 5xx), and the status code is in the *listOfCodes* if it is specified.
For example with MOUNT=”/path/* file:/tmp/autherr.cgi onerror={401,407}”,
the output from /tmp/autherr.cgi is sent when authentication error occurred
in access to URLs under “/path/”.

robots={no|ok}
:   allow or disallow retrievals from robots.
The default value for NNTP and FTP is “no”, while it is
“ok” for other protocols.
nvserv | nvserv=*host* – forwarding to a name based virtual server
:   specify MOUNTing the target server as a name based virtual hosting server.
The virtual host name to be sent to the server can be specified as
“nvserv=*host*” or it is the host name part in the *rURL* by default.
With this option, the target server is MOUNTed only as a virtual server of
the *host* name while other servers, of alias names of the *host*
or IP-addresses of the *host*, are not MOUNTed.
This means that the MOUNT rule will be applied for rewriting of URL in a
HTTP response message only if the hostname of a URL matches textually with
the virtual host name of the target server.
The virtual hostname from the client can be passed through to the server
with “nvserv=-thru”.

avserv | avserv=*host* – forwarding to an IP-address based virtual server:   notate that the target server is not a name based virtual hosting server.
With this option, all of servers of alias names or IP-addresses of the target
server are MOUNTed by this MOUNT rule.
It has been the default behavior of MOUNT but it can be changed with the
option HTTPCONF=”[nvserv:auto](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#nvserv_auto)” to automatically detect
virtual servers in a set of MOUNT parameters.
This “avserv” option could become necessary to notate a non-virtual
server which is automatically guessed as a virtual server.

rserv=*host*[:port] – real target server
:   specify the real host name or IP-address and port number of the target
server toward which the HTTP connection is established.
This option is used to do MOUNT a virtual hosting server of which virtual
host name is specified in the *rURL* rather than in the
“nvserv=*host*” option.
For example, the following two MOUNT rules are equivalent to each other.

```
`MOUNT="/v/* http://www.domain/* rserv=192.168.1.123"`  
`MOUNT="/v/* http://192.168.1.123/* nvserv=www.domain"`  
Specifying the "rserv" option implies that the target server is a virtual
server as if notated with the "nvserv" option.
```

genvhost=*host* (obsoleted by nvserv and rserv options)
:   Specify the hostname which will be received by the target server
as its virtual hostname.
It is set in the “Host: *host*” field in the request message to be
forwarded to the server.
When the request is to be forwarded via a HTTP proxy, it is set
in the request URL as http://*host*/…
The default Host field sent to the server is derived from the
[*rURL*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MOUNT)
part of the MOUNT parameter which specifies the target server.
For example for MOUNT=”/* <http://hosti:8080/\>*”, “Host: hosti:8080”
will be forwarded to the server (which is running at the port hosti:8080).
To through pass the Host field in the request from a client to the server,
specify as “genvhost=-thru”.

ftosv=-cc-*charCode*
:   convert charset in HTTP header forwarded to server into
*charCode* (jis|sjis|euc|utf8)
pathext=*string*
:   when DeleGate as an origin HTTP server searches a file for requested URL,
the path name extended with the specified *string* is retrieved first.
For example with “pathext=-ja”, “index-ja.html” is retrieved prior to
“index.html”. It can be useful in combination with other MOUNT conditions,
like MOUNT=”/* file:data/www/* nvhost=www.delegate.jp,pathext=-ja”

Example: virtual hosting, acting as multiple HTTP servers

The target server or local directory is switched by with which name
the DeleGate is referred (in the “Host:vhost” header field).
In this example, requests for “<http://dom1.com>” and “<http://dom2.org>”
are forwarded to each corresponding server, while requests for
“<http://dom3.net>” or any other name are retrieved in each corresponding
local directory.

`MOUNT="/* http://wwwA/* nvhost=dom1.com"   MOUNT="/* http://wwwB/* nvhost=dom2.org"   MOUNT="/* file:data/wwwC/* nvhost=dom3.net"   MOUNT="/* file:data/www/*"`

Example:

“useproxy”, “method”, “dst” and “withquery” options are introduced
originally to refuse potentially troublesome accesses which may invoke
CGI programs in target servers. For example, to refuse any request
with POST method, or with URL including “?”:

`MOUNT="http:* = method=POST,asproxy,useproxy"   MOUNT="http:* = withquery,asproxy,useproxy"`

AUTH parameters for HTTP-DeleGate

AUTH=origin:auth
:   – default: AUTH=origin:ident  
Like AUTH=proxy, specify using the value in “Authorization”
field in the HTTP header to authenticate the user, except
that accessibility to a DeleGate as a “HTTP origin server” is
checked in this case.

```
Example:

`AUTH=origin:auth RELIABLE="*@localhost"`  
Any user who can login to the localhost of this DeleGate,
giving a correct pair of user name and password in
Authorization, will be authorized to access.
```

AUTH=forward[:{by,for,ver,*}]
:   Put identification information of the source host in the Forwarded
field in a HTTP request header like:
`Forwarded: by Me (Version) for Client`
Currently, if this is specified, it is regarded as
AUTH=“forward:*:” regardless of the second field.
This is useful for a DeleGate on a firewall which relays
internal HTTP servers toward outside .

AUTH=viagen[:*hostIdentifier*]:   Specify the identifier of the host of this DeleGate, which is put into
the Via field in forwarded HTTP message headers as follows:

```
`Via: protocol-version hostIdentifier ( comment )`
If no AUTH=viagen is specified, a default pseudonym is used for
*hostIdentifier*.
If empty *hostIdentifier* is specified, as AUTH="viagen",
the hostname of this DeleGate is used.
A special specification AUTH="viagen:-" disables the insertion
of the Via field.  
If '%' character is used in a *hostIdentifier*, it is interpreted
as the format for[authString](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen) below.
```

AUTH=authgen:basic:*authString*
:   Generate `"Authorization: Basic authString"`
in a HTTP request header to be forwarded to a server,
if it does not have an original Authorization field from a client.
The *authString* should be “*userName*:*passWord*”.
The following special string stand for attributes of clients.

```
|  |  |
| --- | --- |
| `%u` | -- user name got using Ident protocol |
| `%h` | -- host name of the client got from the socket |
| `%i` | -- host name of the network interface to the client |
| `%I` | -- like %i but use the value of "Host:" if given in HTTP |
| `%a` | -- host address of the client |
| `%n` | -- network address of the client |
| `%H` | -- hostname of the DeleGate |
| `%M` | -- the ADMIN of the DeleGate |
| `%A` | -- generated string by "CMAP=string:authgen:mapSpec" |
| `%U` | -- username part of client's [Proxy-]Authorization: username:password |
| `%P` | -- password part of client's [Proxy-]Authorization: username:password |

Example:

When the firewall have two network interfaces and internal
and external hosts access from different interface, then
they can be distinguished by the name of interface.

`AUTH="authgen:basic:%i:%h"`
Otherwise, internal network should be explicitly defined
using CMAP as follows.

`AUTH="authgen:basic:%A"  
CMAP="{internal:passWord}:authgen:*:*:{InternalNetList}"  
CMAP="{external:passWord}:authgen:*:*:*"`

A generated password is formatted as "*passWord*/%i" and
a DeleGate rejects incoming requests with an Authorization
field of such pattern. Thus forged password cannot pass the
DeleGate on the host "%i".
```

AUTH=pauthgen:basic:*authString*
:   Generate `"Proxy-Authorization: Basic authString"`
like [AUTH=authgen](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#authgen).  
Note: obsoleted by [MYAUTH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MYAUTH)=”*user*:*pass*:http-proxy”.

```
Example:

Consume Proxy-Authorization in a request message from a client then
forward it to an upstream proxy as is (by *authString* == %U:%P)  
`AUTH=proxy:pauth AUTH="pauthgen:basic:%U:%P" PROXY=...`
```

AUTH=fromgen:*fromString*
:   If specified, “From: fromString” will be put in the HTTP
request if the original header does not have an original
From field. If fromString is omitted, the default value
is “%u@%h”.

AUTH=log:*remoteHost*:*identUser*:*authUser*
:   Specify contents of the client information part in common
logfile format of HTTP servers. The default value is
AUTH=“log:%h:%u:%U”.

```
|  |  |
| --- | --- |
| `%F` | -- E-mail address in From field |
| `%L` | -- local part of From: local@domain field |
| `%D` | -- domain part of From: local@domain field |
| `%U` | -- username part of Authorization: username:password |
| `%P` | -- password part of Authorization: username:password |
| `%Q` | -- "for *clientFQDN*" part of Forwarded: field |

Example:

To record information about an original client in an internal
DeleGate which is forwarded from a firewall DeleGate,
generate From field at the firewall DeleGate and record it
at the internal DeleGate.

`firewall% delegated AUTH="fromgen:%u@%h" ...  
internal% delegated AUTH="log:%D/%h:%L/%u:%U" ...`
```

Configuration of DeleGate by Users

To make configuration of DeleGate be flexible,
allowing it not only to the administrator of the DeleGate
but also to the users (providers of WWW resources on an origin HTTP-DeleGate),
DeleGate supports reading user defined configuration parameters
at each request processing time.
Such parameters should be given in a files with file name extension “.dgp”,
in the format of[”+=parameters”](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Substitution) file,
on MOUNTed local file systems.
It works like [-Fcgi](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Fcgi)
but more efficiently without creating a new process.

Example:
MOUNTing news server*N* at http://*delegate*/news/serv*N*/

(1) by a parameter at the start-up time MOUNT=”/news/serv*N*/* nntp://*nntpserver*N**/*”

(2) by a CGI-DeleGate MOUNT=”/news/* cgi:/*dirPath*/*”
:   [the contents of file:/*dirPath*/serv*N*/welcome.cgi]

```
delegated -Fcgi MOUNT="/\* nntp://*nntpserver*N**/\*"
```

(3) by a “.dgp” file MOUNT=”/news/* file:/*dirPath*/*”
:   [the contents of file:/*dirPath*/serv*N*/welcome.dgp]

```
MOUNT="/\* nntp://*nntpserver*N**/\*"
```

(This mechanism should be applied to other protocols like FTP…)

Server Side Include in SHTML files

On an origin HTTP-DeleGate, a local file with suffix “.shtml” is regarded,
like a file with “.html”,
as a HTML file except that it includes special tags for
*Server Side Include* (SSI) and META which are to be
interpreted and substituted by the HTTP-DeleGate
before it is sent to a client.

SSI tags

<!--#echo var="*varName*" -->

:   will be substituted with the value specified by *varName*.
*varName* can be arbitrary CGI compatible name like
“`REMOTE_HOST`” or “`HTTP_SERVER`”,
as well as followings.

```
`DATE_GMT` -- current time in GMT

`DATE_LOCAL` -- current time local to the server host

`LAST_MODIFIED` -- the last modified time of the .shtml file

`REFERER` -- equiv. to HTTP\_REFERER

`DOCUMENT_NAME` -- equiv. to SCRIPT\_NAME

`DOCUMENT_URI` -- equiv. to REQUEST\_URI

`*` -- all of variables as *name*=*value* pairs
```

<!--#include virtual="*URL*" -->:   will be substituted with the data specified by "virtual" attribute.

```
"virtual" can be full URL like "*proto*://*server*/*upath*"
or partial URL like "/*upath*" which will be interpreted
as http://*delegate*/*upath*.
Relative URLs like "*upath*" without leading "/"
are interpreted as relative to the base (current) shtml file.

Note that including a resource by SSI is under the access control of
DeleGate (as origin or proxy server) common to the access control
against client users. That is, if a client user is forbidden to
access the included resource, it is also forbidden even via SSI-include.
  
Especially allowing including a resource out of the DeleGate server,
with URL like `virtual=http://exserver/dir/fileX`
can make a security hole made by a user as a SHTML writer.
In an origin server, relaying as a proxy must be forbidden by[RELAY](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#RELAY)=no, but it also forbids SSI-include to do
from other servers.
  
A simple workaround in version 9 is adding a limited RELAY as
`RELAY="proxy:http:exserver:*"` that only allows
relaying to *exserver*.
Another safer workaround is using MOUNT like
`MOUNT="/ex/* http://exserver/dir/*"` then write SSI-include like
`virtual="/ex/fileX"`.
But both of these allows client users to access to resources
other than the intended virtual URL in the *exserver*.

To cope with the above problem in version 10, `RELAY=ssi` is
introduced to be used together with RELAY=no. `RELAY=ssi` allows
SHTML writers to do include from other servers, leaving the permission
for client users unchanged (as RELAY=no).
In other words without RELAY=ssi, you (as the administrator of DeleGate)
can forbid SHTML writers to include from other servers.
Also you can restrict the includable target server (and protocols or clients)
by the generic notation of DeleGate as
`RELAY=ssi:protocolList:serverList:clientList`.
  
Another (and maybe more important) extension in version 10 is relaying
request/response message header (as Cookie or User-Agent) back and forth
between client and server via SSI-include.

NOTE: Maybe it is impossible to forbid CGIs to access arbitrary servers
in a way independent of platforms and languages.
But at least we can forbid CGIs completely with
`REMITTABLE="+,-cgi"`.
```

<!--#fsize virtual="*URL*" -->

<!--#flastmod virtual="*URL*" -->

:   will be substituted with the size or the last modified time
of the specified data respectively.

<!--#config timefmt=*timeFormat* -->

:   will specify the format of generated time string by “#echo”,”#flastmod”
or so, in strftime(3) compatible format.
(default: timefmt=”%a, %d %b %Y %H:%M:%S %z”)

META tags

<META HTTP-EQUIV=*fieldName* content="*fieldBody*">
:   will generate "*fieldName*: *fieldBody*" header
    in the HTTP response message.
    The following patterns in *fileBody* will be substituted
    as described above.

```
${*varName*} or <!--#echo var=*varName* -->

${flastmod:*URL*} or <!--#flastmod virtual=*URL* -->

${fsize:*URL*} or <!--#fsize virtual=*URL* -->

${include:*URL*} or <!--#include virtual=*URL* -->
```

Example: `<META HTTP-EQUIV=Status content="200 OK"> <META HTTP-EQUIV=Content-Type content="text/html"> <META HTTP-EQUIV=Pragma content="no-cache"> <META HTTP-EQUIV=Date content="${DATE_GMT}"> <META HTTP-EQUIV=Last-Modified content="${flastmod:URL}">`

**ICP proxy/server**

ICP-DeleGate provides remote clients with ICP service
about local CACHEDIR,
independently of contents server like HTTP-DeleGate
but sharing the same CACHEDIR.
See<http://www.delegate.org/delegate/icp/>
for more details.

Example: a couple of ICP and HTTP DeleGates sharing a CACHEDIR

`% delegated -P3130 SERVER=icp   % delegated -P8180 SERVER=http`

Example: an ICP proxy merging multiple upstream ICP servers

`% delegated -P3130 SERVER=icp ICP=icpHost1,icpHost2,...`

```bash
ICPCONF parameter*  ==  ICPCONF={icpMaxima|icpConf}
         icpMaxima  ==  para:N|hitage:N|hitobjage:N|hitobjsize:N|timeout:N
           icpConf  ==  icpOptions:ProtoList:dstHostList:srcHostList
                    --  default: ICPCONF=para:2,hitage:1d,...
```

ICP configuration when the DeleGate server is running as an
ICP server (with SERVER=icp).

|                    |                                                     |
|--------------------|-----------------------------------------------------|
|para:*N*            |– the number of parallel ICP-DeleGate servers [2]    |
|hitage:*N*          |– valid age of cached data to be notified as HIT [1d]|
|hitobjage:*N*       |– valid age of cached data to be sent by HIT_OBJ [1h]|
|hitobjsize:*N*      |– max. size of cached data by HIT_OBJ [1024](bytes)  |
|timeout:*N*         |– default timeout of waiting response [2.0](seconds) |
|debug:*N*           |– the level of log for debug [0]                     |
|**FTP proxy/server**|                                                     |

Existing FTP clients without any proxying feature can use DeleGate
as a FTP proxy in two ways:

`USER user@host`
:   at login time,
enter the host name of a FTP server after user name.

`CWD //host[/path]`
:   at any time,
enter the host name of a FTP server after “//” as if it is a directory

A user name can be followed by an account name as follows.

`USER user~account@host`

Also the complete format
`user:pass@host[:port]`
as the generic server specification in URL
is usable both for USER and CWD like follows.

`USER ftp:foo%40bar@server`  
`CWD //ftp:foo%40bar@server/path`

On a multi-homed host, or on a host behind a firewall, the IP address
or port number used for data connections might have to be controlled by[SRCIF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF).

Example: proxy FTP-DeleGate

`firewall% delegated -P8021 SERVER=ftp`

Then you can connect to arbitrary FTP servers (which may be
outside of firewall) via this FTP-proxy.

```bash
internal% ftp
ftp> open firewall 8021
220- firewall PROXY-FTP server (DeleGate/6.1.0) ready.
220-   @ @
220-  ( - ) { DeleGate/6.1.0 (February 3, 2000) }
...
220- --
220- You can connect to a SERVER by `user' command:
220-    ftp> user username@SERVER
220- or by `cd' command (after logged in as an anonymous user):
220-    ftp> cd //SERVER
220- Cache is enabled by default and can be disabled by `cd .' (toggle)
220- This (proxy) service is maintained by 'admin@your.domain'
220  
Name (yourhost:yourname): ftp@ftp1
331-- USER for ftp@ftp1.
220- ftp1 FTP server ready.
331- Guest login ok, send your complete e-mail address as password.
331--  @ @  
331  \( - )/ -- { connected to `ftp' }
Password: me@my.domain
230 Guest login ok, access restrictions apply.
ftp> cd //ftp2
250-- CWD for ftp@ftp2
220- ftp2 FTP server ready.
230- Guest login ok, access restrictions apply.
250--  @ @  
250  \( - )/ -- { connected to `ftp2' }
ftp>
```

Note: The majority of ftp clients can allow to specify the port
number of FTP at command line like:  
`internal% ftp firewall 8021`

Example: cascaded FTP-Proxy

`firewall# delegated -P21 SERVER=ftp PERMIT="ftp:*:internal"   internal# delegated -P21 SERVER=ftp PROXY=firewall:21`

Example: FTP MOUNT with filtering, merging and aliasing

`firewall# delegated -P21 SERVER=ftp://serv1/ \ :   MOUNT="/pub2/* ftp://serv2/pub/*"`

This DeleGate relays the whole contents of serv1 except for “/pub2/*”
which is replaced by that of “<ftp://serv2/pub/\>*”

Example: MOUNT to non-anonymous FTP (and sftp) server

`MOUNT="/sv0/* ftp://serv0/*"   MOUNT="/sv1/* ftp://serv1/%2F*"   MOUNT="/sv2/* ftp://serv2/%2F* logindir"`

The url-path in the URL of FTP (as <ftp://server/url-path>) is interpreted
as the relative path from the login-directory of a user (RFC1738).
The absolute path from the root directory in the server is to be represented
as <ftp://server/%2Fabs-url-path> where “%2F” represents the url-encoded
string of “/” for the root directory.
In the case of MOUNT for non-anonymous FTP (and sftp) server, it is usual
that a login-directory is not the root directory in the server.
In the above examples of MOUNTs, the first one shows only the directory tree
under a login-directory while the second one shows the whole directory tree
under the root.
This becomes necessary to allow users to access to the whole directory
and/or to do cache data of non-anonymous users.
The third one with “logindir” option shows the whole tree but the current
directory right after login is set to the login-directory.
Example: FTP to LPR (Line Printer Daemon Protocol) gateway

`MOUNT="/* lpr://printer0/queue0/*"   MOUNT="/pr1/* lpr://printer1/queue1/*"   MOUNT="/pr2/* lpr://printer2/queue2/*"`

A LPR/FTP-DeleGate allows FTP clients to access to remote printers;
printing a file by FTP file uploading and
showing a printer status by FTP directory listing.
MountOption “readonly” will inhibits listing the status.

Example: origin FTP-DeleGate

`host# delegated -P21 SERVER=ftp MOUNT="/* /path/of/root/*" RELAY=no`

“RELAY=no” prohibits the DeleGate to work as a proxy FTP server.
Writing to the file is disabled by default in origin FTP-DeleGate.
You need to specify “rw” (read/write) as a mount option to
MOUNT points to be writable, like MOUNT=”/xxx/* /yyy/* rw”.

Retrieving the whole contents under a specified *directory* and
returning it as a single file in tar format
by “RETR *directory*.tar” command is supported to be
enabled by adding “tar” to the REMITTABLE list like REMITTABLE=”+,tar”.

```bash
FTPCONF parameter*  ==  FTPCONF=ftpControl[:{sv|cl}]
           ftpControl  ==  nopasv | noport | noxdc | rawxdc
                    --  default: none
```

nopasv
:   disables PASV command for data connection.

noport
:   disables PORT command for data connection.

noxdc
:   disables XDC mode for data transmission on control connection.

rawxdc
:   transmit data without encoding into BASE64 on XDC mode

If a *ftpControl* listed above is followed by “:sv” or “:cl” like “nopasv:sv”
for example, the *ftpControl* is applied only for server side
or client side respectively.

doepsv:sv
:   use EPSV (instead of PASV) with FTP servers

doeprt:sv
:   use EPRT (instead of PORT) with FTP servers

bounce:{no|do|th|cb|rl}
:   – default: FTPCONF=bounce:no  
controls how to manipulate[FTP Bounce](http://www.cert.org/advisories/CA-1997-27.html).

```
no -- reject any FTP Bounce

do -- permit any FTP Bounce

th -- don't care FTP Bounce (backward compatible)

cb -- convert FTP Bounce to "EPRT |||port|"

rl -- reject FTP Bounce from specific clients in combination with `REJECT="ftp-bounce`:\*:*clientHost*" parameter
```

forcexdc
:   enables XDC mode even if the destination server is on the same host

proxyauth
:   enables authentication and authorization as a proxy FTP server.
A username as *user*@*server* is decomposed into
*user* and *server* and used for matching in
[AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER) as
AUTHORIZER=-list{*user*:*pass*}(*reprUser*):ftp:*server*”.
Also it enables generation of authentication information to be forwarded
to the server by [MYAUTH](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MYAUTH) as
MYAUTH=”*genuser*:*genpass*:ftp:*server*:-a/*user*@*”.

servon=init|user|pass
:   select the timing of connection establishment to the MOUNTed server.
By default, the connection to a server is initiated on the command
from the client, of which argument selects the MOUNT point, after
the authentication finished (with USER and PASS).
servon=“init” forces immediate connection to a server on the client
connection and doing authentication by the server (as SERVER=<ftp://server>).
“user” or “pass” specifies connecting to a server on “USER” or “PASS”
command respectively.

usdelim:{setOfDelimiters}
:   – default: FTPCONF=“usdelim:*%#”  
a set of delimiters usable in place of “@” in “user@site”,
ex. “<ftp://user\*server@proxy>” or “<ftp://anonymous:name\*domain@server>”.

hideserv – hide server’s identification
:   Don’t relay the opening message from the server to client which may
include the identification information about the server.

nounesc – disables unescaping %*XX* notation in arguments to the server.
:   If this option is not specified, %*XX* notation included in arguments
representing path, like “%2Fhome/” for example, is unescaped by default.

`FTPCONF` can be applied on a specific condition by specifying it
as a [*MountOption*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountOptions) like
`MOUNT="`*vURL rURL* `FTPCONF=`*ftpConf*”
or with [`CMAP`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CMAP)
like `CMAP=`*ftpConf*`:FTPCONF:`*connMap*.

FTP Transfer Log Format

The format of PROTOLOG for FTP protocol is so called *xferlog*(5)
which is compatible with that of “wu-ftp”.
Each line of xferlog consists of following elements (in a single line).

*currentTime* *transferTime* *clientHost*
:   *fileSize* *fileName* *transferType*
*specialActionFlag* *direction* *accessMode*  
*userName* *serviceName* *authenticationMethod*
*authenticatedUserID*
*DeleGateStatus*

*transferTime* is the total time in seconds for the transfer.
*transferType* is either “a” (ascii) or “b” (binary).
*specialActionFlag* is always “_” (none) in the current implementation.
*direction* is either “o” (outgoing) or “i” (incoming).
*accessMode* is either “a” (anonymous) or “r” (real user).
*userName* is e-mail address with *accessMode* “a”,
or a real user name with *accessMode* “r”.
*serviceName* is always “ftp” in the current implementation.
*authenticationMethod* is either “0” (none) or “1” ([RFC1413](ftp://ftp.ietf.org/rfc/rfc1413.txt) Authentication).
*authenticatedUserID* is the user id got via the *authenticationMethod*
or “*” without authentication.
*DeleGateStatus* is one of “L” (local file), “H” (cache hit),
“N” (cache miss).

Example:

Mon Feb 28 15:32:15 2000 13 proxy.xyz.co.jp
:   182558 /ftp/pub/DeleGate/Manual.htm a _ o a  
[webmaster@xyz.co.jp](mailto:webmaster@xyz.co.jp) ftp 0 * L

**Telnet proxy/server**

Telnet-DeleGate can relay X Window protocol as well as Telnet protocol
in similar way to FWTK.

Example: proxy Telnet-DeleGate

`firewall% delegated -P8023 SERVER=telnet`[TIMEOUT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TIMEOUT-io)=io:1h

Then you can connect to arbitrary Telnet server via this Telnet-proxy.

```bash
internal% telnet firewall 8023
...
--  @ @  firewall PROXY-telnet server DeleGate/6.1.0
-- ( - ) { Hit '?' or enter `help' for help. }
...
-- -- -- This (proxy) service is maintained by 'admin@your.domain'
>> Host name: exthost
-- Connected to exthost.

SunOS UNIX (exthost)
login:
```

Example: origin Telnet-like server

`C:\> delegated -P23 SERVER=exec XFIL=command.com WORKDIR="/"`

// Use command.com of Windows95/98 as a simple telnet server.

**SSH/Telnet gateway**

In the Telnet-DeleGate (DeleGate server for Telnet clients), a host name
prefixed with “-ssh” and “.” (as “-ssh.*host*”) implies a SSH server
on the *host*.
In access to such a server, Telnet-DeleGate works as a gateway between
the SSH server and a Telnet client.
For example, using a Telnet-DeleGate configured like follows,
Telnet clients can login to a SSH server on *host* as *user*
as follows:

`% delegated -P8023 SERVER=telnet://-ssh   % telnet -l user@host localhost 8023`
The target SSH server can be limited as this:

`% delegated -P8023 SERVER=telnet://-ssh.host   % telnet -l user localhost 8023`
The user on the target SSH server can be limited as this:

`% delegated -P8023 SERVER=telnet://user@-ssh.host   % telnet localhost 8023`
The password of the user can be specified as this:

`% delegated -P8023 SERVER="telnet://user:pass@-ssh.host"   % telnet localhost 8023`
In this case, the Telnet client cannot specify anything about the target
SSH server and the login procedure is achieved fully automatically.
Reserved characters in the *pass* part should be escaped with
the “%XX” notation (at least “@” must be escaped with “%40”).

Telnet clients without the capability to send authentication information
with the “-l *user*” option or so, can specify it in the traditional way
of the Telnet-DeleGate as follows:

`% delegated -P8023 SERVER=telnet://-ssh  
% telnet localhost 8023

> > 
> > Host name: user@host`
> > **POP proxy**

Example: proxy POP-DeleGate

`firewall# delegated -P110 SERVER=pop

external% telnet firewall pop  
+OK Proxy-POP server (DeleGate6.1.0) at firewall starting.  
USER username@servername  
…  
Instead of “@”, “%” or “#” can be used as the delimiter between
username and servername, like
username%servername or
username#servername.`

Example: POP MOUNT

“pop://*user*@*server*” is represented
as “pop://*server*/*user*” internally thus
it can be controlled by MOUNT as follows:

`MOUNT="//* ="`
… don’t rewrite if a server is specified by the user  
`MOUNT="* pop://defaultHost/*"`
… specify default POP server  
`MOUNT="user1 pop://host1/*"`
… let the “host1” be the server of “user1”  
`MOUNT="//pop2/* pop://host2/*"`
… map *user*@pop2 to *user*@host2, hiding real hostname “host2”  
`MOUNT="`[`//*%S/%S`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#MountComplex) pop://server/*%(1)@%(0)”
… forward *user*@*host* as is to pop://server/*user*@*host*

When a target POP server indicates that it accepts APOP authentication
(by a greeting message with a time stamp), DeleGate tries login with
APOP first, then retries with USER+PASS when APOP failed.
But if a server never accepts APOP in spite of its greeting, the useless
trial with APOP can be suppressed by “noapop” MountOption like this:

`MOUNT="* pop://server/* noapop"`

Example: NNTP server to POP client gateway

`SERVER=pop   MOUNT="* nntp://nntpserver/*"   MOUNT="ns2-* nntp://nntpserver1/* apop=password"   MOUNT="ns3-* nntp://nntpserver2/* pass=password"`

Clients are expected to send a newsgroup name as a user name.

Example: POP server to HTTP client gateway

`firewall# delegated -P80 MOUNT="/mail/* pop://mailHost/*"`

This DeleGate provides mailboxes in POP server (at *mailHost* by
default) to HTTP clients. Clients accessing to
“`http://firewall/mail/`”
are required to enter Username and Password for POP server at *mailHost*
as authorization information on HTTP. If Username is in the form
“*user*@*mailHost2*”,
not *mailHost* but *mailHost2* is accessed as
a target POP server.
Each mailbox of User at Host server is named as
“`http://firewall/mail/+pop.User.Host`”,
thus you can directly specify User and Host in URL.

**IMAP proxy**

Example: proxy IMAP-DeleGate

`firewall# delegated -P143 SERVER=imap

external% telnet firewall imap

- OK external Proxy-IMAP server DeleGate/6.1.15  
  C001 LOGIN username@servername  
  …  
  LOGIN username%servername is also acceptable.`
  **SMTP proxy/server**

Example: proxy SMTP-DeleGate

// with aliasing and filtering  
`firewall# delegated -P25 SERVER=smtp://mail-server/   
:   MOUNT=“foo@bar smtp://foo2@bar2” \  
MOUNT=”* smtp://-”````bash
SMTPCONF parameter* ==  SMTPCONF=what:conf
–  default: SMTPCONF=bgdatasize:64K

```
myname:*name*
:   Specify the name of this host to be shown to client or server in
    its opening message, HELO command, and so on.

reject:{nohelo,nofrom,pipeline,nomx,notselfmx,notmxhelo}
:   Reject the DATA or the session if a specified condition is true.



    "nohelo" -- the client does not say "HELO"

    "nofrom" -- the client does not say "MAIL FROM"

    "pipeline" -- the client send command without waiting server's response

    "nomx" -- the client's host does not have a MX record

    "notselfmx" -- the client's host is not the MX of itself

    "notmxhelo" -- the domain in the HELO is not the MX of the client's host


    Multiple conditions can be specified concatenated with "+" as
    `SMTPCONF="reject:nomx+nohelo+nofrom+pipeline"`.

bgdatasize:*N*
:   If the data is larger than *N* bytes, relay it in background.
    This means relaying a "DATA" command to a server without having a client
    wait for the response for "QUIT" command from the server.
    Note that only one mail DATA can be relayed in background and the mail
    can be lost if the DeleGate crashes before finishing the forwarding
    because the current DeleGate have no mechanism for spooling and
    retransmission.

maxrcpt:*N*
:   Limit the acceptable maximum number of recipients (by RCPT commands)MX:*server*[:*domain*]
:   Specify the SMTP server toward which mails
    (bound for the *domain*) are forwarded.
    The server can be specified based on the destination address of the
    E-mail to be relayed (it is the address indicated in the RCPT command
    on the SMTP protocol).
    The character "\*" in *server* is replaced with the
    *domain* part of a E-mail address as "*foo*@*domain*".
    The prefix `"-MX."` to a domain name as `"-MX.domain"`
    represents the mail-exchange server of the domain
    (which is retrieved by DNS as the MX record of the domain or host).  
    The default specification is
    SMTPCONF="MX:{-MX.\*,\*}"
    which means trying the MX first, and if it failed, then try direct
    connection to the domain as a hostname.

    Examples:  
    SMTPCONF="MX:smtpserver"
    -- use the smtpserver as the upstream SMTP server  
    SMTPCONF="MX:{smtpserver1,smtpserver2}"
    -- try the SMTP servers in the order  
    SMTPCONF="MX:{-MX.\*,\*}"
    -- the default configuration  
    SMTPCONF="MX:{-MX.\*,\*,smtpserver}"
    -- adding a backup SMTP server  
    SMTPCONF="MX:{\*,-MX.\*}:\*.localdomain"
    -- forward directly to the host if it's in localdomain  
    SMTPCONF="MX:smtpserver:{\*.dom1,\*dom2}"
    -- a server for the specified domains

callback`[:[T][:srcHostList]]`
:   Callback to the SMTP server on the client host which is making
    current request (on HELO command).
    If there is not a SMTP server on the client host, then the
    processing of the request will be delayed up to *T* seconds.
    This could be effective to reduce DDoS type SPAM messages which
    are relayed exploiting non-SMTP servers.
    SMTPCONF="callback" is the abbreviation of `SMTPCONF="callback:20:*"`.

bcc:`emailAddr[:srcHostList]`
:   Append the *emailAddr* to the list of recipients.


```bash
SMTPGATE parameter  ==  SMTPGATE=dirPath
                    --  default: SMTPGATE='${ETCDIR}/smtpgate'
```

Specify the configuration directory for SMTPGATE,
a SMTP to {SMTP,NNTP} gateway.
To accept and relay SMTP messages bound to
“*recipient*@*the-host-of-DeleGate*”,
create a configuration directory at
“SMTPGATE/users/*recipient*”
for each *recipient*,
to hold files for configuration, log, counter, and spool.
Then create a configuration file named “SMTPGATE/users/*recipient*/conf”.

Example: SMTP to SMTP forwarding

// forward messages accepted at “[feedback@delegate.org](mailto:feedback@delegate.org)”  
// toward “[delegate-en@smtpgate.etl.go.jp](mailto:delegate-en@smtpgate.etl.go.jp)”

`delegate.org# delegated -P25 SERVER=smtp`

[the contents of SMTPGATE/users/feedback/conf]

`INHERIT: sendmail   SERVER-HOST: mail.etl.go.jp   RECIPIENT: delegate-en@smtpgate.etl.go.jp   ACCEPT/From: !%, !MAILER_DAEMON@, !hotmail.com, ...`

Example: SMTP to NNTP forwarding

[the contents of SMTPGATE/users/feedback/conf]

`INHERIT: postnews   SERVER-HOST: news.delegate.org   OUTPUT/Newsgroups: mail-lists.delegate-en   OUTPUT/Distribution: world   OUTPUT/Reply-To: feedback@delegate.org   OUTPUT/Subject: [DeleGate-En] ${subject:hc}   OUTPUT/Header: X-Seqno: ${seqno}   OUTPUT/Header: UNIX-From: ${unixfrom}   CONTROL/Errors-To: mladmin@delegate.org   ACCEPT/User-Text: delegate` ## reject if a word “delegate” is not in body `ACCEPT/Max-Bytes: 50000` ## reject larger 50KB header+body `ACCEPT/Min-Body-Bytes: 64` ## reject smaller 64B body `OPTION: isn,rni,res,reb`

A SMTPGATE configuration file consists of a series of lines
of directives,
each looks like a message header of the internet message.
Comment string after sharp (#) character in each line is ignored.
Directives are categorized into three groups;
CONTROL, ACCEPT and OUTPUT.

CONTROL
:   Specify the function of the gateway, the destination server,
and the destination address in the envelope.
Note that you can inherit a configuration from another *recipient*
as well as “sendmail” and “postnews” in the INHERIT directive.

```
`INHERIT`: {sendmail | postnews | *recipient*}

`SERVER-HOST`: *host*

`SERVER-PORT`: *portNumber*

`RECIPIENT`: *EmailAddressForm* (used with "sendmail")

`CONTROL/SENDER`: *EmailAddressForm* (envelope's From in SMTP)

`CONTROL/BCC`: *EmailAddressForm* (a copy is sent to the address on success)

`CONTROL/Errors-To`: *EmailAddress* (a copy is sent to the address on error or rejection)

`ARCHIVE`: *archiveFileNameForm*

`MYAUTH`: *username*:*password* (AUTHINFO for NNTP server)

`OPTION`: *OptionList* `isn` -- Increment Sequence Number (to be referred by ${seqno}) `rni` -- Reject No message-Id `res` -- Reject Empty Subject `reb` -- Reject Empty Body `axo` -- Append X-Original headers `rxo` -- Remove X-Original headers `gwt` -- GateWay Trace `ntr` -- Do NOT add trace field (Received:)
```

ACCEPT
:   If specified, only messages which have fields
matching with specified patterns are accepted.

```
`ACCEPT/Sender`: *ListOfEmailAddressPattern*

`ACCEPT/Recipient`: *ListOfEmailAddressPattern*

`ACCEPT/From`: *ListOfEmailAddressPattern*

`ACCEPT/To`: *ListOfEmailAddressPattern*

`ACCEPT/Max-Bytes`: *messageSize*

`ACCEPT/Min-Body-Bytes`: *bodySize*

`ACCEPT/Max-Exclams`: *theNumberOfExclamationMarks*

`ACCEPT/User-Text`: *listOfWords* (in Subject or body)

`REJECT/User-Text`: *listOfWords* (in Subject or body)

`ACCEPT/Content-Type`: *listOfTypesOrCharsets*

`ACCEPT/Client-Host`: *srcHostList*
```

OUTPUT
:   Header fields to be put into the output messages
replacing the original fields in the input message.

```
`Newsgroups`: *fieldBodyForm* (to be used with "postnews")

`Distribution`: *fieldBodyForm* (to be used with "postnews")

`Reply-To`: *fieldBodyForm*

`To`: *fieldBodyForm*

`Subject`: *fieldBodyForm*

`Header`: *fieldName*: *fieldBodyForm*

`FILTER`: *filterCommand*
```

Substitution
:   The following patterns appearing in …*Form* in field body part
of directives are substituted with the values in the header
or the envelope of the input message.

```
`${sender}` -- *sender* in the envelope (in RCPT To)

`${recipient}` -- *recipient* in the envelope (in MAIL From)

`${recipient.name}` -- local name part of the *recipient*

`${recipient.mx}` -- Mail eXchanger of the *recipient*

`${header.field}` -- body of header *field* in the input message

`${from}` -- From field in the input message

`${unixfrom}` -- Unix-From string for the *recipient*

`${subject}` -- Subject field in the input message

`${subject:hc}` -- *head-cleaned* Subject field

`${seqno}` -- sequence number

`${seqno/10}` -- sequence number / 10 (used with ARCHIVE)

`${seqno/100}` -- sequence number / 100 (used with ARCHIVE)

`${date+format}` -- formatted string of current time (used with ARCHIVE)
```

When a SMTP-DeleGate received a message bound for a recipient,
with an address formed as *recipient*@*mailhost*,
it retrieves the configuration file for the *recipient*
in the following two directories in the order.

SMTPGATE/users/*recipient*/

SMTPGATE/admin/*recipient*/

If no configuration for the *recipient* is found,
then the default configuration is used if it exists at the following directory.

SMTPGATE/admin/@default/

Otherwise the built-in default configuration is used.
The default is at “/-/builtin/config/smtpgate/@default/conf”
which can be[customized](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#customize) with MOUNT option.
The contents of the default is like follows which means
just delivering the input message
to the address of the recipient via the mail exchanger of the recipient.

`CONTROL/INHERIT: sendmail   CONTROL/RECIPIENT: ${recipient}   CONTROL/SERVER-HOST: ${recipient.mx}`

The directory for each *recipient* contains following files.

*recipient*/conf – configuration file

*recipient*/log – log file

*recipient*/count – counter file for ${seqno} (optional)

*recipient*/spool/ – archive directory of relayed messages (optional)

*recipient*/rejected/ – archive directory of rejected ones (optional)

Optional ones will be enabled by manually creating the file or the directory.
Instead of the default archive file,
user can define the file name and the unit of archive by ARCHIVE directive.

Example:

`ARCHIVE: spool/%05${seqno}-${date+%Y%m%d-%H%M%S}-%05${pid}
:   ## default archive enabled if spool/ exists

ARCHIVE: arc-${seqno} ## archive with sequence number

ARCHIVE: arc-%4${seqno/10} ## an archive file per every 10 messages

ARCHIVE: arc-${date+%Y-%m} ## an archive file per month`
**NNTP proxy/server**

MOUNT can be applied to NNTP-DeleGate, for filtering and aliasing of
newsgroups, and for merging multiple NNTP severs.
For example,
MOUNT=“alias-group. nntp://server/group.”
specifies to passing newsgroups “group.*” and aliases
them into “alias-group.*”.
A simple filtering specification is
SERVER=“nntp://server/group.”
which is equivalent to
MOUNT=”= nntp://server/group.”.
If multiple MOUNT for multiple NNTP servers, then the DeleGate
merges the newsgroups on the servers, and serves the newsgroups
to a client as if they are on a single server.

Example: Filtering

`# delegated -P119 SERVER=nntp://nntpServer/group.`

relays only newsgroups which have name pattern “*group*.*”.
A list of groups can be specified for a *nntpServer* like
“nntp://*nntpServer*/*group1*.,*group2*.,…”

Example: merge multiple NNTP servers

`# delegated -P119 SERVER=nntp \ :   MOUNT="= nntp://server1/"   MOUNT="= nntp://server2/"`

Example: merge multiple NNTP servers with authentication (by AUTHINFO)

`# delegated -P119 SERVER=nntp \ :   MOUNT="= nntp://user1:pass1@server1/"   MOUNT="= nntp://user2:pass2@server2/"`

Example: mount selected group(s)

// mounts groups of group.* with it original names.  
`MOUNT="= nntp://server1/group."`

// mounts groups of group.* with aliased names “alias-group.*”  
`MOUNT="alias-group. nntp://server1/group."`

Example: POP server to NNTP client

// mounts a mail spool as if it is a newsgroup named “+pop.user.host”.  
`# delegated -P119 SERVER=nntp MOUNT="= pop://user:pass@host/"`

Example: NNTP server to HTTP client

`# delegated -P80 MOUNT="/news/* nntp://nntpServer/*"`Example: origin NNTP-DeleGate

`# delegated -P119 SERVER=nntp://-.-/`

Specifying “-.-” as the destination server in SERVER parameter of
NNTP-DeleGate means using the DeleGate as an origin NNTP server
which has its own spools to be retrieved and posted.
To make a new newsgroup named *newsGroup*,
make an empty file

`'${ETCDIR}/news/groups/newsGroup'`
To relay an existing “/path/of/MH-folder” as *newsGroup*,
make a file like above and fill it with content like

`0 0 0 0 /path/of/MH-folder`  
(four zeros followed by a path name of a MH-folder)

When a posted article has Unix-From like “From *user* *date*”
as the first line or has a “Unix-From: *user* *date*” header,
the article number for the article is set to the one indicated in
“X-Seqno” (or “X-Sequence”) header if exists,
and the creation date of the spool file will be set to the *date*
in the Unix-From.
**Anonymizing NNTP articles**

To disable mail address mining for spamming, mail addresses transferred
over NNTP protocol can be anonymized with the “rewaddr” MountOption as this:

`MOUNT="* nntp://server/* rewaddr=*:%l@%r"`
This “rewaddr” MountOption can be used in MOUNT parameter both for NNTP
and HTTP DeleGate.
To suppress the rewriting of mail addresses for specific addresses or domains,
specify “nomapemail” option of NNTPCONF like this:

`NNTPCONF="nomapemail:{etl.go.jp,feedback@delegate.org,services@}"`

Anonymization can be controlled by the poster of each article via
a NNTP/HTTP gateway DeleGate. For example, a DeleGate server for NNTP/HTTP
gateway can be configured like this:

`SERVER=http -P8080 MOUNT="/ml/* nntp://server/mail-lists.*" ...`
The anonymization of each article, or articles posted by a poster, is
controlled in the page at:

`http://DeleGate:8080/ml/groupName/articleNumber?Admin`
An authentication key for each poster is required to control anonymization.
The key can be sent automatically via mail, or got with “-Fauthkey” command:

`delegated -Fauthkey foo@bar.dom`
Each key is encrypted with a passphrase, of which default value is an empty
string. It should be changed to a non-default value with the AUTH=pass
parameter for each DeleGate server or -Fauthkey command:

`delegated AUTH="pass:admin:creysalt:PassPhrase" SERVER=nntp ...   delegated AUTH="pass:admin:creysalt:PassPhrase" SERVER=http ...   delegated AUTH="pass:admin:creysalt:PassPhrase" -Fauthkey ...`
This anonymization can be applied as an off-line filter command too:

`delegated MIMECONV="rewaddr:*:%l@%r" -FdeMime < infile > outfile`
If necessary,
`MIMECONV="nomapemail:{listOfAddress}"` and
`AUTH=pass:admin:...` can be used with -FdeMime.

```bash
MountOptions for NNTP
```

hide={*GroupList*}
:   List of patterns of news group names to be
hidden to clients.  
Example: “hide={alt.*,!alt.comp*}”

cache=no
:   disable any caching.

cache=no-article
:   disable ARTICLE caching.

cache=no-list
:   disable LIST caching.

upact:*Invoke*/*Reload*/*Posted*
:   control updating of LIST (active list) cache.
The same meaning with
NNTPCONF=upact:*Invoke*/*Reload*/*Posted*
except this controls only the destination server of this MOUNT parameter.

rewaddr={*headerList*}:*addrFormat*
:   Rewrite E-mail address appeared in header fields or the body of a message.
For example, “rewaddr={From,Body}:%l@%r” will rewrite an address
“[foo@host.bar.org](mailto:foo@host.bar.org)” to “foo@bar” in the “From” header field and in the body.

```bash
NNTPCONF parameter* ==  NNTPCONF=what:conf
                    --  default: NNTPCONF=upact:600/300/120
```

pathhost:*Server*/*PathHost*
:   define a logical *PathHost* name
of the physical *Server*-host.  
Example: `NNTPCONF="wall.etl.go.jp/delegate.org"`

upact:*Invoke*/*Reload*/*Posted*
:   control updating of active list cache.
*Invoke* and *Reload* specifies expire time of the cache in seconds.
After an article is posted via the DeleGate, the cache will be
updated whenever the client checked it (by LIST command),
within the period specified by *Posted*.

overview.fmt:{*FieldList*}
:   default – overview.fmt:{Subject,From,Data,Message-ID,References,Bytes,Lines}  
The format of the XOVER response generated by the DeleGate.

xover:*Number*
:   default – xover:2000  
Limit the maximum number of articles in “XOVER *range*”

nice:*Number*
:   Set the nice value if defined.

ondemand
:   postpone the connection establishment to a server until
something from the server become necessary

dispensable
:   continue the client session even if a server is disconnected

auth:{*srcHostList*}
:   Force authentication (using AUTHINFO command) at the beginning of the NNTP
session, if the client hosts is included in the *srcHostList*.
This parameter should be set if the NNTP server does any
authentication for any subset of users, and this DeleGate does
caching for NNTP.

authcom:{*commandList*}
:   Define a set of NNTP commands which need authentication before used.

server:*host*[:*port*][/*grouplist*]
:   set NNTP server(s) for HTTP requests by URLs nntp://*/… or news:…

nntpcc:*Number*
:   default – nntpcc:1  
Specify “nntpcc:0” to disable “connection cache” for NNTP.
**LDAP proxy**

Example: proxy LDAP-DeleGate

`# delegated -P389 SERVER=ldap`

Specify this DeleGate server as your client’s LDAP server and
append “@host.of.ldap-server” after root directory name (i.e.
name of baseObject for search).

`% ldapsearch -x -h localhost -p 389 -b o=netcenter.com@memberdir.netscape.com`

Example: LDAP gateway

`# delegated -P389 SERVER=ldap   
:   MOUNT=“o=xxx* ldap://aaa.domain nocase”   
:   MOUNT=“o=yyy* ldap://bbb.domain nocase”

Search requests on base directory named “o=xxx…” sent to this LDAP-DeleGate
is forwarded to the LDAP-server “ldap://aaa.domain”.`

**Whois proxy**

Example: proxy Whois-DeleGate

`firewall# delegated -P43 SERVER=whois   internal% whois -h firewall "whois://whois.nic.ad.jp/help"`
**X proxy**

Example: relaying to a display on a single host

`x-server% xhost firewall   firewall% delegated -P6008 SERVER=X://x-server   internal% xterm -display firewall:8`

Example: relaying to two displays on a single server host

`firewall% delegated -P6002-6003 SERVER=X://x-server:-6002`

Example: relaying to two server hosts

`firewall% delegated -P6011-6012 \ :   SERVER=X://x-server1:-:{*:6011} \   SERVER=X://x-server2:-:{*:6012}`
**Gopher proxy**

Example: Gopher-DeleGate

`firewall% delegated -P8070 SERVER=gopher://gopher.ncc.go.jp

internal% gopher firewall 8070  
internal% gopher -p -_-gopher://gopher.tc.umn.edu firewall 8070`
**SSL proxy**

Using a filter program “*sslway*” in FCL, FSV, or[CMAP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#cond-filter) parameter,
client-side and/or server-side communication can be wrapped with
SSL protocol.
To use this filter, you need sslway and relevant PEM files placed
at some directories in LIBPATH, typically at DGROOT/lib.
See
<http://www.delegate.org/delegate/ssl/>
for more details.
( Sslway as an external command has become unnecessary.
Recent versions of DeleGate uses the built-in sslway when
it can utilize dynamic libraries of SSL. See
<http://www.delegate.org/delegate/tls/>
)

Example: relay between non-SSL client and SSL server

`# delegated -P80 SERVER=http FSV=sslway MOUNT="/* https://server/*"`
Example: relay between SSL client and non-SSL server

`# delegated -P443 SERVER=https FCL=sslway MOUNT="/* http://server/*"`
**DNS (Domain Name System) proxy/server**

A DNS-DeleGate server relays host name data gathered
from multiple sources including DNS, NIS and local file.
It can provide limited type of resource records only;
A, PTR, SOA and simplified MX.
SOA record is composed with information of[DNSCONF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DNSCONF) configuration.

Example: {NIS,FILE,DNS}/DNS gateway

`# delegated -P53 SERVER=dns \ :   RESOLV=cache,file,nis DNSCONF=domain:my.domain`

MX record for *hostname* is generated from
-MX.*hostname* if it is given (like the example below),
or the A record for *hostname* is used.
Priorities among multiple MX records can not be represented
in the current implementation.

Example: *hosts* table to use hostA as the MX of hostB

`10.1.2.3 hostA   10.4.5.6 hostB, -MX.hostA`

```bash
DNSCONF parameter*  ==  DNSCONF=what:value
```

Specify the configuration of the DNS-DeleGate server.

|                  |                                                                       |
|------------------|-----------------------------------------------------------------------|
|para:*N*          |– the number of parallel server process [2]                            |
|domain:*FQDN*     |– [domain name of the host of DeleGate]                                |
|origin:*FQDH*     |– [host name of the host of DeleGate]                                  |
|admin:*Email*     |– the mail address of the administrator [ADMIN]                        |
|mx:*FQDH*         |– [primary host name of -MX.*host* if exists or inquired *host* itself]|
|serial:*N*        |– serial number [%Y%m%d%h of the last configuration change]            |
|refresh:*period*  |– refresh interval [6h]                                                |
|retry:*period*    |– retry interval [10m]                                                 |
|expire:*period*   |– expire period [14d]                                                  |
|minttl:*period*   |– minimum ttl [6h]                                                     |
|**CU-SeeMe proxy**|                                                                       |

Example: proxy CU-SeeMe-DeleGate

`firewall% delegated -P7648 SERVER=cuseeme://Reflector/   INTERNAL# delegated -P7648 SERVER=cuseeme://firewall/   internal% {use firewall or INTERNAL as a proxy-reflector for Reflector}`

**RESERVED NAMES**

Special names “-“and “-.-”, when it is used in the “*host*:*port*” part
of URL, means the host and port of the DeleGate itself. And URL
“http://-.-/-/” is reserved for a entry point of a control page of
DeleGate.Another reserved name is “mypro.xyz”. An access to “<http://mypro.xyz>”
is interpreted to your proxy server like “http://-.-”.
If the proxy is chained, you can access to upstream proxies by
prefixing the hop count N from your client, as “<http://N.mypro.xyz>”,
as “<http://2.mypro.xyz>” for example.
This feature can be enabled or disabled by the[HTTPCONF=mypro.xyz](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httpconf_mypro.xyz) parameter.
**AF_LOCAL SOCKETS**

Sockets in AF_LOCAL (or AF_UNIX) address space can be referred like
host names in pseudo top-level domain “.af-local”.
For example, a socket with address “/tmp/sock” can be referred as
“sock.tmp.af-local”, then it is referred in command line options like
“-Psock.tmp.af-local”, SERVER=<http://sock.tmp.af-local:123>”, or so.
Port number of socket is ignored in this naming.

**CUSTOMIZATION**

The source of built-in data of DeleGate including icons and messages
are at the source code directory “src/builtin/*”.
They are compiled into the executable file of DeleGate and
are accessible as resources on a run-time DeleGate with
URL “http://*delegate*/-/builtin/*”.
Those data can be replaced without recompiling DeleGate but
by defining MOUNT for them.
For example, the error message returned on forbidden access is at
“http://*delegate*/-/builtin/mssgs/403-forbidden.dhtml”, and
it can be replaced by a MOUNT parameter like this:

MOUNT=”/-/builtin/mssgs/403-forbidden.dhtml /tmp/forbidden.dhtml”

In this example, the MOUNT replaces only the forbidden message
and the alternative data is a local file under “/tmp”.
But in general, a group of builtin-data can be replaced
using wild-card (*) notation and
alternative data can be placed at remote host which can be accessible
via HTTP or FTP. For example, copy the whole of “src/builtin/”
into “<http://yourwww/delegate/builtin/>” and MOUNT it like this:

MOUNT=”/-/builtin/* <http://yourwww/delegate/builtin/\>*”

Loading remote data will not suffer from overhead
as long as cache is enabled,
since MOUNTed built-in data are cached and reused like usual data.
**DEFENSE AGAINST ATTACKERS**

Immediately after an occurrence of fatal signal, like SIGSEGV or SIGBUS,
DeleGate stops serving to the client host which caused the fatal error,
since the error could be a sign of a failed trial of intrusion.
At the same time, to notify the incident, DeleGate will send a
report mail to the administrator named in the ADMIN parameter.

Since the most typical method of attackers is buffer overflow on stack,
expecting a target buffer resides at a certain address,
randomizing stack address will be effective to decrease the probability
of successful attack.
And a failure of attack will cause a fatal error
to be caught by DeleGate.

A suspicious client host will be shut out until a relevant file
(under ADMDIR/shutout/) is removed,
or the file is expired by TIMEOUT=shutout (30 minutes by default).
For safety, TIMEOUT=“shutout:0” (never timeout) is desirable
not to give a second chance to the attacker.
But as fatal errors are highly provably caused by usual bugs in DeleGate itself,
it may be troublesome to be the default value…

Anyway you should be aware of following options if you are aware of
preventing this kind of attacks,
as well as[access control](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#acl) configurations.

`TIMEOUT=shutout:N` [30m] … shortest attack retrial interval

`MAXIMA=randstack:N` [32] … randomize stack address

`MAXIMA=randenv:N` [1024] … randomize environment variable

`MAXIMA=randfd:N` [32] … randomize client’s socket descriptor

`CHROOT=dirPath` … restrict accessible file space

`OWNER=user` [nobody] … restrict the ability of the DeleGate process

`ADMIN=E-mail-address` … must be correct and SMTP-deliverable

`DGSIGN=mask` [V.R.P/Y.M.D] … hide DeleGate version to client and server

`-Phost:port` [0.0.0.0:] … restrict the interface of an entrance port

`-Tx` [off] … disable execve() system call

`-Fimp` [none] … restrict users and capability of DeleGate executable

At the start up time, the original environment variables and
command line arguments on stack area are moved to heap area and cleared
not to be utilized for intrusion code by attackers.
At the same time, a dummy environment variable named *RANDENV*
with a value of random length (with maximum MAXIMA=randenv)
is inserted to randomize addresses of environment variables
to be inherited to child processes like filter programs and CGI programs.

**ENCRYPTED CONFIGURATION**

Configuration data can be in encrypted format which requires a passphrase
to decrypt it. Such a passphrase is specified as the password
for a special user, “sslway” and “config”,
representing the kind of configuration.

The passphrase to decrypt the private-key for SSL is given as
the password of a special user named “sslway” in a special domain, as this:

`delegated -Fauth -a sslway:Passphrase -dgauth@admin`

The *Passphrase* will be used by SSL library for decryption of the
private-key, which might be bundled in a file together with a certificate,
like this for example:

`delegated -P443 SERVER=https STLS="fcl,sslway -cert cryptedKey.pem"`

Another passphrase is for getting
[encrypted
configuration](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CryptedParams) parameters specified as “+=conf.cdh”.
The passphrase to decrypt such data is given as the password of
a special user named “config” in a special domain, as this:

`delegated -Fauth -a config:Passphrase -dgauth@admin`

The suffix “.cdh” means that the data is encrypted with “Credhy” algorithm.
A file can be encrypted and decrypted with -Fcredhy as follows:

`delegated -Fcredhy Passphrase < conf > conf.cdh`  
`delegated -Fcredhy Passphrase -d < conf.cdh > conf`

An encrypted configuration file can be used as follows:

`delegated +=conf.cdh`  
`delegated +=http://server/path/conf.cdh`

When a configuration file is loaded from a remote server,
it is strongly recommended to use the encryption.

As shown in the examples, those special user names to hold passphrases
are in the special domain “-dgauth@admin” [[DGAuth](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#dgauth)].
The storage for passwords in DGAuth are encrypted with a passphrase,
or *MasterKey*.
It can be specified as this:

`CRYPT=pass:MasterKey`

If the *MasterKey* is not specified with a CRYPT parameter
for a DeleGate which requires it,
then it will be asked interactively.
When restarting DeleGate with “-r” or SIGHUP,
or restarting in short time after termination,
or possibly after rebooting the host machine,
the *MasterKey* is automatically saved and reused
without the interaction.

**PLATFORM SPECIFIC ISSUE**

Unix:   Invocation from Inetd
:   Both “nowait” and “wait” status can be specified in inetd.conf.
In “nowait” status, the DeleGate will processes just one request
(session) and exits, thus is ineffective.
In “wait” status, the DeleGate will process multiple requests;
maximum count of request may be limited to *N* by
“`MAXIMA=service:N`”.

```
Privileged operations without being superuser
:   Some operations of DeleGate needs the privilege of super-user, but
    running whole DeleGate process under super-user's ability is not
    desirable for security. To solve the problem, you can execute DeleGate
    by normal user while executing a privileged operation by a small external
    program with "set user ID on execution" flag.
    Those external subsidiary programs are placed at DGROOT/subin/ by
    optional installation.



    dgpam -- to do PAM authentication ([AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER))

    dgchroot -- to do chroot(2) ([CHROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#CHROOT))

    dgbind -- to do bind(2) to privileged ports ([-P](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_P), [SRCIF](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#SRCIF), [FTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_FTP) data, [SOCKS](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#serv_Socks) server)
```

Windows
:   Starting as a service
:   On WindowsNT/2000, DeleGate automatically starts to run as a service
(as a background process) by default,
when invoked from the command prompt without -v or -f option.
To stop and/or remove a DeleGate running as a service with
-P*xxxx* option, enter “delegated -P*xxxx*”
at the command prompt and answer to the simple query from the DeleGate.
On Windows95/98, DeleGate runs as a foreground process only.

CYGWIN
:   Seems to have to be invoked by the Administrator.

OS/2
:   The optional loopback device (localhost) is necessary
to be installed.

**GENTLE RESTART**

To make DeleGate restart gently
without aborting ongoing sessions in child processes,
and without changing the process ID of the DeleGate
and holding its resources like entrance ports,
send SIGHUP signal to the DeleGate process.
This can be done in a platform independent way
using[-Fkill](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#func_kill) function like this:

`delegated -Fkill-hup -Pport`

Also restarting with SIGHUP can be done by remote HTTP clients
at “http://*delegate*/-/admin/”
using [AUTH=admin](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTH_admin) parameter.

Restarting will be done after a configuration of DeleGate is changed.
Parameters to be reloaded on restart must be given with
[+=*parameters*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Substitution) notation
for parameter substitution.
Other options (parameters) given as command line arguments will be
inherited as is to the restarted DeleGate process.

Another purpose of restarting can be cleaning up
of possible garbage or leaked resources
like heap memory and file descriptors.
For this purpose,
DeleGate can be restarted periodically by
[`TIMEOUT=restart`](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#TIMEOUT) or
at each scheduled time by
[-restart](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#act_restart) action in CRON parameter.

**FUNCTIONS**

Given a[-F*function*](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#opt_Func) option,
DeleGate runs to do the specified function
which typically is a client-side action of a certain protocol.
You can omit entering lengthy “delegated -F” by
giving a file name “*function*” to an DeleGate executable file
and just call it as *function*.
The matching of *function* name is case-insensitive.

Command line options before -F*function* and after “–” option
is regarded as options for DeleGate rather than for the *function*,
as delegated *dgopt* … *dgopt*
-F*func* *fopt* … *fopt*
– *dgopt* … *dgopt*.
As an exception, parameter option, in *name*=*value* format,
is recognized as a parameter for DeleGate even if it appeared at
*fopt* position.

Example: using DeleGate as a resolver

`% delegated -Fresolvy www.delegate.org   % ln -s delegated Resolvy   % Resolvy www.delegate.org`

The following is a list of major functions.

`-Fhelp`
:   put a list of available functions

`-Fkill[-hup] -Pport`
:   terminate (or restart) the DeleGate sending SIGTERM (or SIGHUP)

`-Fimp`
:   implant configuration parameters into the executable file

`-Fcgi [DeleGateOptions]`
:   run as a CGI program of an arbitrary [HTTP](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#Fcgi) server

`-Fconnect host port[/udp] [XCOM=clientCommand]`
:   like a telnet client, connect to the specified *host*:*port*
and relay the standard I/O to/from it.

`-Fresolvy {[-MX.]hostname | IPaddress[-num]}`
:   like nslookup(8), resolve a given host name or IP address
(can be a range as 10.10.10.1-128)

`-Ffindu` [-atime *N*] [-ls] [-du] [-rm] … [*dir*]*
:   like find(1), find a file to apply a specified action.
Usage will be shown by “delegated -Ffindu”.  
Example: doing “find . -ls” together with “du(1)”

```
`delegated -Ffindu -ls -du`
```

`-Fdget [-h] [-o] [-eencoding] [PROXY=host:port] [MYAUTH=user:pass] URL`
:   download a resource specified by *URL*,
and put to standard output with “-o” option.
With “-h” option, the header part of a HTTP response message will be put
together.

`-Ficp` [-h *server*] *URL*
:   work as an ICP client.
Usage will be shown by “delegated -Ficp”.

`-Fsched {"crontabSpec" | crontabFile | schedSpec}*`
:   like cron(8), cause specified actions at specified timing.  
Example: cause an action every 15 minutes

```
`delegated -Fsched "0,15,30,45 * * * * /bin/date"`
*schedSpec* is the canonical format of scheduling specification.

*schedSpec* == *Wday*:*year*:*month*:*mday*:*Hour*:*Min*:*Sec*:*action*
Example: cause an action every 15 seconds

`delegated -Fsched "*:*:*:*:*:*:0,15,30,45:/bin/date"`
```

`-Fmd5 [infile]`
:   output the MD5 digest of input data

`-Fauth -{a|d|v} username[:password] hostname[:portnumber] [expire]`
:   Add, delete or view predefined (or cached) authorization information
for *hostname* as a server for[AUTHORIZER](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#AUTHORIZER).
If *hostname* is prefixed with “-”, it is regarded as a virtual name
without a real server.

```
Example:

`delegated -Fauth -a ken:blahblah -smtp.users.local`
// and refer this as AUTHORIZER=-smtp.users.local
```

**Version 10 Specific**

- Logfiles are split daily by default in version 10.
  See the[LOGDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#LOGDIR) parameter.
  It can be configured like the default of version 9 with `LOGDIR='log'`.
- The format of HTTP logfile is [extended](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#httplog) by default in version 10.
  It can be configured like the default of version 9 with `PROTOLOG=':%C %D'`.
- Counters are reset weekly by default in version 10.
  See the [COUNTERDIR](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#COUNTERDIR) parameter.
  It can be configured like version 9 with `COUNTERDIR='${ADMDIR}/counts'`.
- The format of “nonce” value is changed in version 10
  so that the digest authentication is not shared between version 9 and 10.
- Identification protocol is disabled by default in version 10.
  It can be enabled like in version 9 with `-EId` option.

**FILES**

|                 |                                                      |
|-----------------|------------------------------------------------------|
|`${DGROOT}/etc`  |– persistent files mainly for configuration           |
|`${DGROOT}/lib`  |– library files and scripts                           |
|`${DGROOT}/adm`  |– important log relevant to administration            |
|`${DGROOT}/log`  |– log files which will grow up                        |
|`${DGROOT}/work` |– for core dump                                       |
|`${DGROOT}/cache`|– for cached data                                     |
|`${DGROOT}/act`  |– control info. of currently active DeleGate processes|
|`${DGROOT}/tmp`  |– volatile files which should be erased on shutdown   |

See the description of[DGROOT](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#DGROOT) parameter
and [Local file usage](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#localfile)
for more information.

**Acronyms**

AIST – National Institute of Advanced Industrial Science and Technology

CERN – European Organization for Nuclear Research

ETL – ElectroTechnical Laboratory (was integrated to AIST)

MITI – Ministry of International Trade and Industry (antecedents of METI)

METI – Ministry of Economy, Trade and Industry

NCSA – National Center for Super-computing Applications

BSD – Berkeley Software Distribution (BSD UNIX)

CYGWIN – A system provides UNIX utilities on MS-Windows

OSX – Mac OSX (Apple version of UNIX)

UNIX – Uniplexed Information and Computing Service: Linux, BSD, Mac OSX, Solaris, and other

CFI – Common Filter Interface of DeleGate

CGI – Common Gateway Interface

CSS – Cascading Style Sheets

DHCP – Dynamic Host Configuration Protocol

DNS – Domain Name System/Service

FTP – File Transfer Protocol

FWTK – FireWall Tool Kit

HTML – Hyper Text Markup Language

HTTP – Hyper Text Transfer Protocol

HTTPS – HTTP protocol over SSL (or TLS)

IMAP – Internet Message Access Protocol

LDAP – Lightweight Directory Access Protocol

LPR – Line Printer Daemon Protocol

MIME – Multi purpose Internet Mail Extension (Internet mail format)

MITM – Man In the Middle (attack)

NAT – Network Address Translation

NFS – Network File System

NIS – Network Information Service

NTLM – Net Lan Manager (what?)

NNTP – Network News Transfer Protocol

PAM – Pluggable Authentication Modules

PEM – Privacy-enhanced Electronic Mail

POP – Post Office Protocol

SPAM – unsolicited or undesired electronic messages

SMTP – Simple Mail Transfer Protocol

SSL – Secure Socket Layer (original version of TLS)

SSH – Secure Shell

SSI – Server Side Inclusion

TCP – Transport Control Protocol

TLS – Transport Layer Security (successor version of SSL)

UDP – User Datagram Protocol

URI – Universal Resource Identifier

URL – Uniform Resource Locator (in URI format)

WWW – World Wide Web

XML – Extensible Markup Language

ASCII – American Standard Code for Information Interchange

EUC – Extended Unix Code (means EUC-JP in DeleGate)

JIS – In DeleGate, 7bits JIS code for Japanese text (ISO-2022-JP)

UCS – Universal multiple-octet coded Character Set

SJIS – Shift JIS, 8bits encoding of JIS characters (Shift_JIS)

APOP – Digest authentication protocol of POP protocol

CRL – Certificate Revocation List

FIFO – First In First Out (data stream)

FQDN – Fully Qualified Domain Name (ex. [www.deleate.org](http://www.deleate.org))

LD_LIBRARY_PATH – Path to find Dynamic Linking Library

PASV – abbreviation of Passive Mode in FTP protocol

PID – Process ID

SNI – Server Name Indication, (virtual) host name from SSL client

RTT – Round Trip Time

SHTML – HTML file to be interpreted and translated by SSI

STARTTLS – Starting TLS on the connection of non TLS

SIGBUS – Signal raised on bus error (fatal)

SIGCHLD – Signal to notify status changes in a child process

SIGHUP – Signal to restart a process

SIGINT – Signal to interrupt a process, usually generated by tty with Control-C

SIGSEGV – Signal raised on segment violation (fatal)

SIGTERM – Signal to terminate a process

**SEE ALSO**

du(1),
ps(1),
tee(1),
cat(1),
find(1),
chroot(2),
execve(2),
getpeername(2),
getsockname(2),
pstat(2),
ptrace(2),
setgid(2),
setuid(2),
umask(2),
scanf(3),
strftime(3),
system(3),
YP(4),
crontab(5),
hosts(5),
inetd.conf(5),
cron(8),
inetd(8),
nslookup(8),

DNS([RFC1034](ftp://ftp.ietf.org/rfc/rfc1034.txt)),
FTP([RFC959](ftp://ftp.ietf.org/rfc/rfc959.txt)),
Gopher([RFC1436](ftp://ftp.ietf.org/rfc/rfc1436.txt)),
HTML([RFC1866](ftp://ftp.ietf.org/rfc/rfc1866.txt)),
HTTP([RFC2068](ftp://ftp.ietf.org/rfc/rfc2068.txt)),
ICP([RFC2186](ftp://ftp.ietf.org/rfc/rfc2186.txt)),
Ident([RFC1413](ftp://ftp.ietf.org/rfc/rfc1413.txt)),
IMAP([RFC2060](ftp://ftp.ietf.org/rfc/rfc2060.txt)),
LDAP([RFC1777](ftp://ftp.ietf.org/rfc/rfc1777.txt)),
LPR([RFC1179](ftp://ftp.ietf.org/rfc/rfc1179.txt)),
MIME([RFC2045](ftp://ftp.ietf.org/rfc/rfc2045.txt)),
NNTP([RFC977](ftp://ftp.ietf.org/rfc/rfc977.txt)),
POP([RFC1460](ftp://ftp.ietf.org/rfc/rfc1460.txt)),
Socks([RFC1928](ftp://ftp.ietf.org/rfc/rfc1928.txt)),
SMTP([RFC821](ftp://ftp.ietf.org/rfc/rfc821.txt)),
Telnet([RFC854](ftp://ftp.ietf.org/rfc/rfc854.txt)),
URI([RFC2396](ftp://ftp.ietf.org/rfc/rfc2396.txt)),
URL([RFC1738](ftp://ftp.ietf.org/rfc/rfc1738.txt)),
Wais([RFC1625](ftp://ftp.ietf.org/rfc/rfc1625.txt)),
X([RFC1013](ftp://ftp.ietf.org/rfc/rfc1013.txt))
**AUTHOR**

````bash @ @ ( - ) _<   >_ ````
Yutaka Sato <y DOT sato AT delegate DOT org>  
National Institute of Advanced Industrial Science and Technology (AIST),
Tsukuba, Ibaraki 305-8568, Japan
**FEEDBACK**

Comments about DeleGate are expected to be directed to<mailto:feedback@delegate.org>
to be open and shared at
<http://www.delegate.org/feedback/>.
**DISTRIBUTION**

The latest version of DeleGate is available at the following location.
<URL:<ftp://ftp.delegate.org/pub/DeleGate/>>
in a tar+gzip format file named “delegate*.tar.gz”.
[**HELP**](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm#_menu)
[
[help](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?_help)
[search](http://www.delegate.org/fsx/search?index=man&sort=url)
[decomp](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.whole)
[parts](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.parts)
[skeleton](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/Manual.htm?.skeleton)
[frame](http://doc.imunixx.de/imunixx/SOFTWARE/DELEGATED/V9.9.12/$%7BSELF%7D?_frames)
]

```bash
help ... this information


search ... searching Manual in a search engine (FreyaSX)


decomp ... hyperlinks is rewritten to create decomposed view of each part


parts ... each part is annotated and hyperlinks is rewritten as in "decomp"


skeleton ... list of parts of Manual


frame ... Manual is shown in frame


[CTX] ... jump to the label of this part in the whole plain Manual


[ALL] ... jump to the label of this part in the "decomp" version of Manual
```

```bash
DeleGate Version 9.9.10 + 10.0.0     Last change: August 28, 2014
--------- --------- --------- --------- --------- --------- --------- ---------
```