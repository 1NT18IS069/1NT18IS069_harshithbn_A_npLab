#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#define MAX 100
int main()
{
	int sock;
	struct sockaddr_in server_addr;
	//char recv_data[1024],send_data[1024];
	int buff[MAX],n=0;
	float basic,net_salary;
	struct hostent *host;
	host=gethostbyname("127.0.0.1");
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(6119);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}
	printf("Enter basic salary of employee : \n");
	scanf("%f",&basic);
	
	write(sock,&basic,sizeof(basic));
	
	read(sock,&net_salary,sizeof(net_salary));
	printf("Net-salary of employee from server :%.2f\n",net_salary);
	close(sock);	
	return 0;
}
