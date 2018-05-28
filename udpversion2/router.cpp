//
// Created by ddd on 18-5-26.
//

#include "router.h"


void TestRouter::enqueuePacket(MyPacket packet)
{
    int priority=packet.priority;
    if(priority!=0&&priority!=1&&priority!=2)
    {
        cout<<"invaild priority"<<endl;
        exit(1);
    }
    else {
        std::list<MyPacket> &queue = sendQueues[priority];
        auto it = std::find(queue.begin(), queue.end(), packet);
        if (it == queue.end()) {
            if (packet.srcId != this->selfId) {
                queue.push_back(packet);
            }
        } else {
            it = queue.erase(it);
            queue.insert(it, packet);
        }
    }

}

bool TestRouter::handleReceivedPacket(MyPacket packet)
{
    if(packet.priority==-1)
    {
        this->starTimeSync();
        return false;
    }
    if(packet.dstId!=0)
    {
        if(packet.dstId==this->selfId)
            return true;
        else
        {
            this->enqueuePacket(packet);
            return false;
        }

    }
    else
    {
        if(broadCastPackets.end()!=std::find(broadCastPackets.begin(),broadCastPackets.end(),packet))
            return false;
        else
        {
            broadCastPackets.push_back(packet);
            enqueuePacket(packet);//?
            if(broadCastPackets.size()>16)
                broadCastPackets.pop_front();//?
        }
        return true;
    }



}
bool TestRouter::sendPacket(MyPacket packet)
{
    try{
        struct sockaddr_in addr;
        addr.sin_family =AF_INET;
        addr.sin_port =htons(this->senderPort);
        addr.sin_addr.s_addr = inet_addr(this->senderIp);

        unsigned char* c=getBytes(packet);
        int len=packet.lenMessage+31;
        char *bytes=new char[256];
        memcpy(bytes,c,len);
        //test.setWritetxt(bytes,len);
        //cout<<"msglen:"<<len<<endl;


        printf("\n");
        sendto(socket(AF_INET,SOCK_DGRAM,0),&bytes[0], len,0,(struct sockaddr*)&addr,sizeof(addr));
        cout<<"send sucessful"<<endl;
        return true;

    }catch(std::exception e){
        std::cout<<"send failed"<<std::endl;
        return false;

    }
}

void TestRouter::starTimeSync(MyPacket packet)
{
    if(this->sendPacket(packet))
    {
        starTimeSync();
    }
}

void TestRouter::starTimeSync()
{
    this->timer=clock();
    long delay= (WAIT_PERIOD + (this->selfId - 1) * WORKING_PERIOD);
    long period = WORKING_PERIOD * maxId ;
    schedule(delay,period);

}

void TestRouter::schedule(long delay,long period)
{
    if(sendQueues.size()!=3)
        cout<<"init error: sendQueue's size !=3"<<endl;
    sleep(delay);
    while(1)
    {
        if(sendQueues[2].size()!=0)
        {
            sendPacket(*(sendQueues[2].begin()));
            sendQueues[2].pop_front();
        }
        else if(sendQueues[1].size()!=0)
        {
            sendPacket(*(sendQueues[1].begin()));
            sendQueues[1].pop_front();
        }
        else if(sendQueues[0].size()!=0)
        {
            sendPacket(*(sendQueues[0].begin()));
            sendQueues[0].pop_front();
        }
        else
            cout<<"Send queue of ID "<<this->selfId<<" is empty"<<endl;
        sleep(period);
    }

}

