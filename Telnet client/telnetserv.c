/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     char dirBuffer[1024];
     char totalDir[1024];
     struct dirent *directory;
     DIR *currentDir;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 1842;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
    char *tmp;
    while(1){ 
	         bzero(buffer,256);
	         n = read(newsockfd,buffer,255);
	         if (n < 0) error("ERROR reading from socket");
			if(strstr(buffer,"mkdir") != NULL){
			    tmp = strtok(buffer," ");
			    tmp = strtok(NULL," ");
			    mkdir(tmp,0777);
			}
			if(strstr(buffer,"rmdir") != NULL){
			    tmp = strtok(buffer," ");
			    tmp = strtok(NULL," ");
			    rmdir(tmp);
			}
			if(strstr(buffer,"cd") != NULL){
			    tmp = strtok(buffer," ");
			    tmp = strtok(NULL," ");
				if(strstr(tmp,"..") != NULL){
				  chdir("..");
				}
				else{
				  chdir(tmp);
				}
			}
			if(strstr(buffer,"pwd") != NULL){
			  bzero(dirBuffer,1024);
			  getcwd(dirBuffer,sizeof(dirBuffer));
			  n = write(newsockfd,dirBuffer,strlen(dirBuffer));
			}
			if(strstr(buffer,"ls") != NULL){
			  bzero(dirBuffer,1024);
			  bzero(totalDir,1024);
			  currentDir = opendir(".");
			  directory = readdir(currentDir);
			  directory = readdir(currentDir);
			  while((directory = readdir(currentDir))!=NULL){
			    snprintf(dirBuffer, sizeof(dirBuffer), "%s   ", directory->d_name);
			    strcat(totalDir,dirBuffer);
		       }
			n = write(newsockfd, totalDir, strlen(totalDir));
	        	if (n < 0) error("ERROR writing to socket");
	        } 
			if(strstr(buffer,"exit") != NULL){
			close(newsockfd);
	         	close(sockfd);
			  exit(1);
			}

        }
         close(newsockfd);
         close(sockfd);
     return 0; 
}
