#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
//#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <arpa/inet.h>


int main()
{
int cfd;
int recbytes;
int sin_size;
char buffer[1024]={0};   
struct sockaddr_in s_add,c_add;
unsigned short portnum=0x8888; 
printf("Hello,welcome to client !\r\n");

cfd = socket(AF_INET, SOCK_STREAM, 0);

printf("fp=%d\n", cfd);

if(-1 == cfd)
{
    printf("socket fail ! \r\n");
    return -1;
}
printf("socket ok !\r\n");

bzero(&s_add,sizeof(struct sockaddr_in));
s_add.sin_family=AF_INET;
s_add.sin_addr.s_addr= inet_addr("127.0.0.1");
s_add.sin_port=htons(portnum);
printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
//????为什么没有调用bind（）????
if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
{
    printf("connect fail !\r\n");
    return -1;
}
printf("connect ok !\r\n");
while(1)
{
	if(-1 == (recbytes = read(cfd,buffer,1024)))
	{
	    printf("read data fail !\r\n");
	    return -1;
	}
	buffer[recbytes]='\0';
    printf("recv:%s\r\n",buffer);
    std::string ss;
    std::cin>>ss;
    if(-1 == write(cfd,ss.c_str(),32))
    {
        printf("write fail!\r\n");
        return -1;
    }
    printf("send: %s\r\n",ss.c_str());
    if(ss == "END") break;

}

// printf("read ok\r\nREC:\r\n");

getchar();
close(cfd);
return 0;
}