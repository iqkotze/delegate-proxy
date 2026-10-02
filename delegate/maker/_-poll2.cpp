#include <poll.h>
#include <vector>
#include "ystring.h"
#include "log.h"
#include <stdio.h>
#include "vsocket.h"

#define READY_EVENTS	(POLLIN|POLLPRI|POLLHUP|POLLERR)

/// TIMEOUT_IMM polls once, 0 waits forever, otherwise milliseconds.
static int pollWait(struct pollfd *pfd,int nfd,int timeout)
{
	if( timeout == TIMEOUT_IMM )
		return poll(pfd,nfd,0);
	return poll(pfd,nfd,timeout?timeout:-1);
}

int _PollIns(int timeout,int size,int *mask,int *rmask){
	std::vector<struct pollfd> pfd;
	int fi,rfd,nready,rready;

	pfd.reserve(size < 0 ? 0 : size);
	for(fi = 0; fi < size; fi++){
		if( 0 <= mask[fi] )
			pfd.push_back({mask[fi],(short)(POLLIN|POLLPRI),0});
		rmask[fi] = 0;
	}
	nready = pollWait(pfd.data(),pfd.size(),timeout);
	if( nready <= 0 )
		return nready;

	rready = 0;
	rfd = 0;
	for(fi = 0; fi < size; fi++){
		if( 0 <= mask[fi] ){
			if( pfd[rfd++].revents & READY_EVENTS ){
				rready++;
				rmask[fi] = 1;
			}
		}
	}
	return rready;
}
int _PollIn1(int fd,int timeout){
	struct pollfd pfd[1];
	int nready;

	if( fd < 0 )
		return -1;

	pfd[0].fd = fd;
	pfd[0].events = POLLIN;
	pfd[0].revents = 0;
	nready = pollWait(pfd,1,timeout);
	if( nready <= 0 )
		return nready;
	return (pfd[0].revents & (POLLIN|POLLHUP|POLLERR)) ? 1 : 0;
}
