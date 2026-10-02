#ifndef _YSOCKET_H
#define _YSOCKET_H


typedef struct sockaddr *_SAP;
int _SOCKET(int,int,int);
int _BIND(int,_SAP,int);
int _LISTEN(int,int);
int _ACCEPT(int,_SAP,int*);
int _CONNECT(int,const _SAP,int);
int _SENDTO(int,const void*,unsigned int,int,_SAP,unsigned int);
int _RECVFROM(int,void*,unsigned int,int,_SAP,int*);
int _SEND(int,const void*,unsigned int,int);
int _RECV(int,void*,unsigned int,int);
int _GETSOCKOPT(int,int,int,void *,int*);
int _SETSOCKOPT(int,int,int,const void *,int);
int _SELECT(int,fd_set*,fd_set*,fd_set*,struct timeval*);
int _GETHOSTNAME(char*,unsigned int);
int _SHUTDOWN(int,int);


#define STD_HOSTENT
#define gethostbyname	_GETHOSTBYNAME
#define gethostbyaddr	_GETHOSTBYADDR



#define bind(s,a,l)	_BIND(s,a,l)
#define accept(s,a,l)	_ACCEPT(s,a,l)
#define connect(s,a,l)	_CONNECT(s,a,l)


#define PS_IN     001
#define PS_PRI    002
#define PS_OUT    004
#define PS_ERR    010
#define PS_HUP    020
#define PS_NVAL   040
#define PS_ERRORS 070

#endif /* _YSOCKET_H */
