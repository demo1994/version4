//
// Created by ddd on 18-5-25.
//

#include "packet.h"
#include <string.h>


MyPacket::MyPacket(int srcId, int destId, long long time, double latitude, double longitude, string message) {
    this->dstId = destId;
    this->srcId = srcId;
    this->latitude = latitude;
    this->longitude = longitude;
    this->time = time;
    this->message = message;
    this->lenMessage = message.size();
}
MyPacket::MyPacket(int srcId, int destId, long long time, double latitude, double longitude) {
    MyPacket(srcId, destId, time, latitude, longitude, "");
}
MyPacket::MyPacket()
{
    MyPacket(0, 0, 0, 0, 0);
}

MyPacket::~MyPacket()
{

};


bool MyPacket::operator ==(const MyPacket& s) {
    if (this == &s)
        return true;
    if (s.message.size() == 0 && this->message.size() == 0) {
        return this->srcId == s.srcId;
    }
    else
    {
        return this->srcId == s.srcId&&
               this->dstId == s.dstId&&
               this->time == s.time&&
               this->message == s.message;
    }
}

void MyPacket::setPriority(int priority) {
    this->priority = priority;
}
/**
* |+++++++|+++++++|++++++++|++++++++++|+++++++++++|++++++++++|++++++++++++++++++++++++++++++++++  |
* |     0 |     1 |2      9|10      17|18       25|   26     | 27		30 |31	                 |
* | srcId | dstId |  time  | latitude | longitude | priority | 	message长度|      message        |
* |+++++++|+++++++|++++++++|++++++++++|+++++++++++|++++++++++|+++++++++++++|+++++++++++++++++++ |
* @return
*/
unsigned char* getBytes(const MyPacket& src) {
    int size = 27 + src.message.size();
    unsigned char* data = new unsigned char[size];
    data[0] = src.srcId;
    data[1] = src.dstId;
    memcpy(data + 2, &src.time, 8);
    memcpy(data + 10, &src.latitude, 8);
    memcpy(data + 18, &src.longitude, 8);
    memcpy(data + 26, &src.priority, 1);
    memcpy(data + 27, &src.lenMessage, 4);
    memcpy(data + 31, src.message.c_str(), src.message.size());
    return data;
}
MyPacket fromBytes(const char* bytes) {
    int srcId = (bytes[0] + 256) % 256;
    int dstId = (bytes[1] + 256) % 256;
    long long time;
    memcpy(&time, bytes + 2, 8);
    double latitude;
    memcpy(&latitude, bytes + 10, 8);
    double longitude;
    memcpy(&longitude, bytes + 18, 8);
    int priority = bytes[26];
    int lenMessage = 0;
    memcpy(&lenMessage, bytes + 27, 4);
    char *data = new char[lenMessage + 1];
    memset(data, 0, lenMessage + 1);
    memcpy(data, bytes + 31, lenMessage);
    string message(data);
    MyPacket tmp(srcId, dstId, time, latitude, longitude, message);
    tmp.setPriority(priority);

    return tmp;
}
