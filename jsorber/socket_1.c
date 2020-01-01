#include <sys/socket.h>	/* basic socket definitions */
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h> /* for variadic function */
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_PORT 80	/* standard HTTP port*/
#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...){
	int errno_save;
	va_list ap;

	// any system or library call can set errno, so we need to save it now
	errno_save = errno;

	// print out the fmt+args to stadard out
	va_start(ap, fmt);
	vfprintf(stdout, fmt,ap);
	fprintf(stdout,"\n");
	fflush(stdout);

	//print out error message is errno was set
	if (errno_save !=0){
		fprintf(stdout, "(errno=%d) : %s\n", errno_save, strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);

	// this is the .. and_die part. Terminate with an error.
	exit(0);
}


int main(int argc, char **argv){
	int sockfd, n;
	int sendbytes;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE];
	char recvline[MAXLINE];

	if (argc !=2) // check input correct
		err_n_die("usage: %s <server address>", argv[0]);

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // create socket n check if error
		err_n_die("Error while creating the socket!");

	bzero(&servaddr, sizeof(servaddr));	// zero out the address
	servaddr.sin_family = AF_INET;		// specify address family again tcp/ip
	servaddr.sin_port = htons(SERVER_PORT); // chat server address, htons=host to network, short.

	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) // translate string repr of address into binary repr. eg "1.2.3.4" => [1,2,3,4]
		err_n_die("inet_pton error for %s", argv[1]);

	// connect to server
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) <0)
		err_n_die("connect failed");

	// We're connected. prepare the message
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n"); // GET command, / is root, HTTP 1.1 standar, \r\n\r\n is end of request
	sendbytes = strlen(sendline);
	
	// Send the request -- making sure you send it all
	// This code is a bit fragile, since it bails if only some of the bytes are sent.
	// Normally, you would want to retry, unless the return values was -1.
	if (write(sockfd, sendline, sendbytes) != sendbytes) 
		err_n_die("write error");

	memset(recvline, 0, MAXLINE);
	
	// Now read the servers response
	while ( (n=read(sockfd, recvline, MAXLINE-1)) > 0){
		printf("%s",recvline);
		memset(recvline, 0, MAXLINE);
	}

	if (n<0)
		err_n_die("read error");

	exit(0); // end successfully
}
