//
// Created by ddd on 18-5-25.
//

#ifndef UDPVERSION2_UDPRELAY_H
#define UDPVERSION2_UDPRELAY_H
#include <iostream>

#include<cstdio>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <pthread.h>
#include<string.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "packet.h"



class udpRelay
{
private:
    const char *DEFAULT_IP="127.0.0.1";
    const int DEFAULT_BUFFER_LENGTH=1024;
    const int DEFAULT_PORT=8888;

    char *sendIp;
    char *recvIp;
    int sendPort;
    int recvPort;
    char writetxt[256];
    int txtSize;
    int sockfd;

public:
    udpRelay()
    {
        sendIp=const_cast<char*>(DEFAULT_IP);
        recvIp=const_cast<char*>(DEFAULT_IP);
        sendPort=DEFAULT_PORT;
        recvPort=DEFAULT_PORT;
        //writetxt= const_cast<char *>("this is default msg");
        txtSize=sizeof(writetxt);
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
    }
    void init();
    void setRecvIp(std::string s);
    void setRecvPort(int port);
    void setWritetxt(char *bytes,int len);
    void setWritetxt(char *);
    void setMsgLen(int len);
    void setTxtSize(int size) { this->txtSize=size; }

    int getRecvPort()
    {
        return recvPort;
    }
    int getSocketfd()
    {
        return sockfd;
    }
    char *getRecvIp()
    {
        return recvIp;
    }
    char *getWritetxt()
    {
        return writetxt;
    }
    int getTxtSize()
    {
        return txtSize;
    }
}test;



void udpRelay::setRecvPort(int port)
{
    this->recvPort=port;
}
void udpRelay::setRecvIp(std::string s)
{
    const char *temp=nullptr;
    temp=s.c_str();
    this->recvIp= const_cast<char *>(temp);
}
void udpRelay::setWritetxt(char *bytes,int len)
{
    memcpy(writetxt,bytes,len);
    setTxtSize(len);
}
void udpRelay::setWritetxt( char *c)
{
    //this->writetxt=c;

}

void udpRelay::init()
{
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(this->recvPort);

    //char ip1[]="127.0.0.1";
    addr.sin_addr.s_addr= inet_addr(this->recvIp);



    //绑定socket对象与通信链接
    int ret =bind(this->sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind error\n");

        exit(1);

    }
    else
        std::cout<<"init sucessful"<<std::endl;
}


void *write_func(void *args)
{

    //const char *write = "ddddddd";
    //int fd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(test.getRecvPort());
    addr.sin_addr.s_addr = inet_addr(const_cast<char*>(test.getRecvIp()));
    std::cout<<"size:"<<test.getTxtSize()<<std::endl;

    while(1)
    {
        sleep(1);
        sendto(test.getSocketfd(),test.getWritetxt(), test.getTxtSize(),0,(struct sockaddr*)&addr,sizeof(addr));/*向客户端发送数据*/
        std::cout<<"server send message"<<std::endl;

    }
}

void *read_func(void *args)
{
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);
    char buf[256];
    while(1)
    {

        memset(&buf, 0, sizeof(buf));
        recvfrom(test.getSocketfd(), buf, 256, 0, (struct sockaddr *) &cli, &len);
        //printf("server recv data: %s \n", buf);
        //std::cout<<"size:"<<sizeof(buf)<<std::endl;
        //for(int i=0;i!=37;++i)
            //printf("%c\n",buf[i]);
        //char *temp=new char[256];
        //memcpy(temp,&buf[0],37);
        MyPacket p2=fromBytes(buf);
        std::cout<<p2.time<<endl;//阻塞

    }
}
#endif //UDPVERSION2_UDPRELAY_H
