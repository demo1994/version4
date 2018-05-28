//
// Created by ddd on 18-5-25.
//

#ifndef UDPVERSION2_PACKET_H
#define UDPVERSION2_PACKET_H

#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

class MyPacket
{
public:
    MyPacket();
    MyPacket(int srcId, int destId, long long time, double latitude, double longitude);
    MyPacket(int srcId, int destId, long long time, double latitude, double longitude, string message);
    bool operator ==(const MyPacket& s);
    void setPriority(int priority);
    ~MyPacket();
    unsigned char srcId;
    unsigned char dstId;
    long long time;
    double latitude;
    double longitude;
    unsigned char priority;
    int lenMessage;
    string message;
};


unsigned char* getBytes(const MyPacket& src);
MyPacket fromBytes(const char* bytes);

#endif //UDPVERSION2_PACKET_H
