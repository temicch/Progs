#include <vingraph.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <pthread.h>
#include "warehouse.h"
#include "transport.h"
 
#define ATTACH_POINT "boilerOrder"					
#define ATTACH_POINT_TTB "TransportToBroiler"

struct arg_struct
{
    int arg1, arg2;
};

struct msg_transport
{
    transport *oTransport;
    int rcvid;
};

int WidgetText;
char text[100];
int Channel;
name_attach_t *Channel_TTB;
 
void *transportLeft(void *args)
{
        ((msg_transport*)args)->oTransport->hide();
        while(((msg_transport*)args)->oTransport->X > -30)
        {
            ((msg_transport*)args)->oTransport->move(((msg_transport*)args)->oTransport->X - 1, ((msg_transport*)args)->oTransport->Y);
            delay(1);
        }          
        delete ((msg_transport*)args)->oTransport;
        MsgReply(((msg_transport*)args)->rcvid, 0, NULL, 0);
}
 
void *boilerWork(void *args)
{  
    warehouse object(((arg_struct *)args)->arg1, ((arg_struct *)args)->arg2, 5, cLightGreen);
    pthread_t tTransportLeft;
    msg_transport msg_t;
    while(1)
    {
        object.Remove();
        if(object.getValue() == 2)
        {
            if(MsgSendPulse(Channel, 1, 0,  (object.getX() + 40 - 15)) == -1)          
            {
                SetText(WidgetText, "Can't send pulse!");
            }
        }
        if(object.isEmpty())
        {
            int receive;
            int rcvid = MsgReceive(Channel_TTB->chid, &receive, 1, 0);
            transport *oTransport = new transport(-35, 50, (receive >> 5));
            oTransport->show();
            while(oTransport->X < object.getX() + 40 - 15)
            {
                oTransport->move(oTransport->X + 1, oTransport->Y);
                delay(1);
            }
            for(int i = 0; i < (receive & 0x1F); i++)
            {
                object.Add();
                delay(100);
            }
            msg_t.rcvid = rcvid;
            msg_t.oTransport = oTransport;
            pthread_create(&tTransportLeft,NULL, transportLeft,(void *)&msg_t);
        }
        delay(500 + (rand() % 5) * 200);
    }
}
 
int main()
{
    arg_struct msg;
    ConnectGraph("client");
    Fill(RGB(0, 0, 0));
    EnlargeTo(0, 300, 1520, 400);
    WidgetText = Text(0, 350, "Empty", RGB(255, 0, 0));
   
    while((Channel = name_open(ATTACH_POINT, 0)) == -1)
    {
        SetText(WidgetText, "Try to connect...");
        delay(1000);
    }
    Channel_TTB = name_attach(NULL, ATTACH_POINT_TTB, 0);
    SetText(WidgetText, "Connected");
    pthread_t tboilerWork[4];
    for(int i = 0; i < 8; i++)
    {
        msg.arg1 = 170 + i * 102;
        msg.arg2 = 90;
        pthread_create(&tboilerWork[i],NULL, boilerWork,(void *)&msg);
    }  
    while(1)
    {
        int c = InputChar();
        //81 - left
        //82 - up
        //83 - right
        //84 - down
        if((int)c == 27)
            break;
    }
    for(int i = 0; i < 8; i++)
    {
        pthread_cancel(tboilerWork[i]);
    }
    name_close(Channel);
    CloseGraph();
    _exit(0);
    return 0;
}