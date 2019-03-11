#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#define LIMIT 2048
#define PORT 5000
#define SIZE 80
int main(int argc, char **argv)
{
	int sockfd,len,n;
	char *buffer,*sendBuffer,*filename;
	char fname[80];
	filename=(char *)malloc(SIZE);
	buffer=(char *)malloc(SIZE);
	sendBuffer=(char *)malloc(SIZE);
	int ifd, ofd;
	char list[LIMIT];
	ssize_t cin, cout;
	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	if(sockfd<0)
	{
		perror("socket");
		exit(0);
	}
	printf("Socket success\n");
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	len=sizeof(servaddr);
	printf("Enter file name\n");
	scanf("%s",fname);
	sendto(sockfd,fname,sizeof(fname),0,(const struct sockaddr *)&servaddr,len);

	ofd = open(fname, O_WRONLY | O_CREAT, 0644);
	if(ofd == -1){
				printf ("---error open for writing---");
				exit(0);
				return -1;
	}
	recvfrom(sockfd,&list,sizeof(list),0,(struct sockaddr *)&servaddr,&len);
	while(1){
		if(strcmp(list,"stop")==0)
			break;	
	cout = write (ofd, &list, strlen(list)); 
	recvfrom(sockfd,&list,sizeof(list),0,(struct sockaddr *)&servaddr,&len);
	printf("<");
	}
	close(ofd);
	printf("Success");	
		close(ofd);      
	
	return 0;
}



