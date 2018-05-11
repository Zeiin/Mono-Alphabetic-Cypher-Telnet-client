#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];
    portno = 1842;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    while(1){
	printf(">telnet ");
        bzero(buffer,1024);
        fgets(buffer,1024,stdin);
        n = write(sockfd,buffer,strlen(buffer));
	if(strstr(buffer,"exit") != NULL){
		close(sockfd);
		exit(1);
	}
        if (n < 0) 
             error("ERROR writing to socket");
	if((strstr(buffer,"ls") != NULL) || (strstr(buffer,"pwd") != NULL)){
        	bzero(buffer,1024);
        	n = read(sockfd,buffer,1023);
        	if (n < 0) 
           	  error("ERROR reading from socket");
        	printf("%s\n",buffer); 
   	}
      }
    
    close(sockfd);
    return 0;
}
