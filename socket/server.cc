#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>
#include <iostream>
#include <string>
int main()
{
int sfp,nfp;
//sockaddr_in REFER : http://blog.sina.com.cn/s/blog_6151984a0100etj1.html
struct sockaddr_in s_add,c_add;
unsigned int sin_size;
unsigned short portnum=0x8888;
printf("Hello,welcome to my server !\r\n");
//Socket()函数的接口和含义可以通过 &man socket 命令查询
sfp = socket(AF_INET, SOCK_STREAM, 0);
printf("fp=%d\n", sfp);
if(-1 == sfp)
{
    printf("socket fail ! \r\n");
    return -1;
}
printf("socket ok !\r\n");
//set zero;
bzero(&s_add,sizeof(struct sockaddr_in));
s_add.sin_family=AF_INET;
s_add.sin_addr.s_addr=inet_addr("192.168.139.129");//htonl(INADDR_ANY);
s_add.sin_port=htons(portnum);

printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
//man bind
if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
{
    printf("bind fail !\r\n");
    return -1;
}
printf("bind ok !\r\n");
//5  : 队列长度
if(-1 == listen(sfp,5))
{
    printf("listen fail !\r\n");
    return -1;
}
printf("listen ok\r\n");

sin_size = sizeof(struct sockaddr_in);
nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
if(-1 == nfp)
{
    printf("accept fail !\r\n");
    return -1;
}
printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));

while(1)
{
    std::string ss;
    std::cin>>ss;

    if(-1 == write(nfp,ss.c_str(),1024))
    {
        printf("write fail!\r\n");
        return -1;
    }
    printf("send: %s\r\n",ss.c_str());
    if(ss == "END") break;
    char buffer[1024]={0};
    int recbytes=0;
    if(-1 == (recbytes = read(nfp,buffer,1024)))
    {
        printf("read data fail !\r\n");
        return -1;
    }
    buffer[recbytes]='\0';
    printf("recv:%s\r\n",buffer);
}
close(nfp);
close(sfp);
return 0;
}