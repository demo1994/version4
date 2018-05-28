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
#include "udprelay.h"
#include "router.h"




int main()
{
    MyPacket p1(55,12,12345678,1.1,1.2,"zhkzhaisg54565");
    p1.setPriority(1);
    //printf("%d",p1.priority);
    //unsigned char* c=getBytes(p1);
    //char *bytes=new char[256];
    //memcpy(bytes,c,37);
    //test.setWritetxt(bytes,37);

    test.init();

    pthread_t write_id,read_id;
    /*if(pthread_create(&write_id,NULL,write_func,NULL))
    {
        printf("pthread_create write_func err\n");
    }
*/

    if(pthread_create(&read_id,NULL,read_func,NULL))
    {
        printf("pthread_create read_func err\n");
    }
    TestRouter router(const_cast<char *>("127.0.0.1"),8888,1,4);
    //router.sendPacket(p1);
    router.enqueuePacket(p1);
    router.enqueuePacket(p1);
    //router.enqueuePacket(p1);
    cout<<router.getsize()<<endl;
    router.starTimeSync();



    return 0;

   /*  char *bytes;
    memcpy(bytes,c,38);
    MyPacket p2=fromBytes(bytes);
    std::cout<<p2.longitude;
    return 0;





    //MyPacket p2=fromBytes((const char *)c);
    //cout<<p2.message<<std::endl;*/
}

/*int main()
{









    test.init();

    pthread_t write_id,read_id;
    if(pthread_create(&write_id,NULL,write_func,NULL))
    {
        printf("pthread_create write_func err\n");
    }


    if(pthread_create(&read_id,NULL,read_func,NULL))
    {
        printf("pthread_create read_func err\n");
    }
    while(1)
    {}

    return 0;

}
/*int main()
{
    MyPacket p2(4,4,123456789,1.1,0.0,"str");
    p2.setPriority(3);
    std::cout<<sizeof(p2)/sizeof(char)<<std::endl;

    MyPacket *p=&p2;
    /*char *P=(char *)p;
    for(int i=0;i<=43;++i)
        printf("%x",*(P+i));
    std::cout<<std::endl;
    char *temp=P+8;
     long long *temp2=(long long *)temp;
    std::cout<<*temp2<<std::endl;
    temp2++;
    double *temp3=(double *)temp2;
    std::cout<<*temp3<<std::endl;
    temp3++;
    std::cout<<*temp3<<std::endl;
    temp3++;
    int *temp4=(int *)temp3;
    std::cout<<*temp4<<std::endl;
    temp4++;
    char *temp5=(char *)temp4;
    printf("%s",temp5);*/

// p2.toBuffer();





//return 0;
//}*/
