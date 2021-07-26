#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#define MAX 100
int main()
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	//FILE *fptr;
	int sock,connected;
	//fchar send_data[1024],recv_data[1024];
	int sin_size;
	float basic,da,hra,pf,net_salary,gross_sal;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}


	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(6119);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(bind(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr))==-1)
	{
		perror("unable to bind");
		exit(1);
	}

	if(listen(sock,5)==-1)
	{
		perror("lsten");
		exit(1);
	}

	printf("tcp server is waiting for client on port XXXX\n");
	sin_size=sizeof(struct sockaddr_in);
	connected=accept(sock,(struct sockaddr *)&client_addr,&sin_size);

	read(connected,&basic,sizeof(basic));
	da=basic*0.25;
	hra=basic*0.15;
	gross_sal=basic+da+hra;
	pf=gross_sal*0.10;
	printf("da is:%.2f\nhra is:%.2f\ngross-salary is :%.2f\npf is :%.2f\n",da,hra,gross_sal,pf);
	net_salary=gross_sal-pf;
	printf("Net-salary of employee is :%.2f\n",net_salary);
	write(connected,&net_salary,sizeof(net_salary));
	close(sock);
}
