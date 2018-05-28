//
// Created by ddd on 18-5-25.
//

#ifndef UDPVERSION2_ROUTER_H
#define UDPVERSION2_ROUTER_H


#include "packet.h"
//#include "udprelay.h"
#include <ctime>
#include <list>
#include <vector>
#include <algorithm>
#include <exception>

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

class TestRouter{
public:
    TestRouter(char *senderIp,int port,int id,int maxId)
    {
        this->senderIp=senderIp;
        this->senderPort=port;
        this->selfId=id;
        this->maxId=maxId;
        std::list<MyPacket> temp;
        sendQueues.push_back(temp);
        sendQueues.push_back(temp);
        sendQueues.push_back(temp);

    }


    void enqueuePacket(MyPacket packet);

    bool handleReceivedPacket(MyPacket packet);

    void schedule(long delay,long period);

    bool sendPacket(MyPacket packet);

    void starTimeSync(MyPacket packet);

    void starTimeSync();

    int getSize() {return sendQueues.size();}
    int getsize() {return sendQueues[1].size();}

private:
    static const int WAIT_PERIOD=1;
    static const int WORKING_PERIOD=5;
    int selfId;
    int maxId;
    //DatagramSocket sendSocket;
    clock_t timer;
    char *senderIp;
    int senderPort;
    std::vector<std::list<MyPacket>> sendQueues;
    std::list<MyPacket> broadCastPackets;



};


#endif //UDPVERSION2_ROUTER_H
