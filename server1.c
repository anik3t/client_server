#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#define LIMIT 8 
#define PORT 5000
#define SIZE 80

int main()
{
	int sockfd,len,n;
	char *buffer;//*c
	buffer=(char *)malloc(SIZE);

	int ifd, ofd;
	char list[LIMIT],filename[SIZE];
	ssize_t cin, cout;
	
	struct sockaddr_in servaddr,cliaddr;
	sockfd=socket(AF_INET, SOCK_DGRAM,0);
 
	if(sockfd<0)
	{
		perror("socket");
		exit(0);
	}
	printf("socket success server\n");
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(PORT);
	if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))<0)
	{
		perror("bind");
		exit(0);
	}
	printf("bind success\n");
	fputs("***server started***\n",stdout);
	len=sizeof(cliaddr);
	recvfrom(sockfd,filename,SIZE,0,(struct sockaddr *) &cliaddr,&len);
	
	ifd = open (filename, O_RDONLY);
	
	if (ifd == -1)
	{
	   printf ("\nerror open for reading");
		return -1;
	 }
	 
	
	while(1){	
	 cin = read (ifd, &list, LIMIT);
	if(cin==0)
		break;
	 sendto(sockfd,&list,sizeof(list),0,(struct sockaddr*)&cliaddr,len);
	 printf(">");
	 }
	 
	 strcpy(list,"stop");
	 	 sendto(sockfd,&list,sizeof(list),0,(struct sockaddr*)&cliaddr,len);
	
	

return 0;
}



