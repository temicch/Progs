#include <vingraph.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <pthread.h>
#include "warehouse.h"
#include "transport.h"
 
int WidgetText;
 
char text[100];
 
#define ATTACH_POINT "boilerOrder"
#define ATTACH_POINT_TTB "TransportToBroiler"		// Здесь перед TransportToBroiler надо добавить HOSTNAME клиента
 
int Channel_TTB = -1;
 
bool isFilling = false;
 
warehouse *oWarehouse;
 
void *mainWarehouseWork(void *args)
{
    oWarehouse = new warehouse(35, 90, 0, cGreen);
    while(1)
    {
        if(!oWarehouse->isFull() && !isFilling)
            oWarehouse->Add();
        delay(100);
    }
}
    name_attach_t *attach;
 
void* server(void *args)
{
    int msg;
    int rcvid;
    transport object(60, 50);
    while (1)
    {
       rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), 0);
 
       if (rcvid == -1) {/* Error condition, exit */
           //break;
       }
 
       //if (rcvid == 0) {/* Pulse received */
       //}
       //else
       {
            while(oWarehouse->getValue() < 5 || isFilling);
            int size = oWarehouse->getValue();
            isFilling = true;
            for(int i = 0; i < size; i++)
            {
                oWarehouse->Remove();
                delay(150);
            }
            isFilling = false;
            object.value = size;
            object.show();   
           
            while(object.X < 150 + 30)
            {
                object.move(object.X + 1, object.Y);
                delay(1);
            }
            msg = object.value | (object.myNum << 5);
            //MsgReply(rcvid, 0, &msg, sizeof(msg));
            if(Channel_TTB == -1)
                while((Channel_TTB = name_open(ATTACH_POINT_TTB, 0)) == -1);
            MsgSend(Channel_TTB, &msg, sizeof(msg), NULL, 0);
            object.hide();
            object.value = 0;
            while(object.X > object.startX)
            {
                object.move(object.X - 1, object.Y);
                delay(1);
            }
       }
   }
    SetText(WidgetText, "closed");
   name_detach(attach, 0);
}
 
int main()
{
    ConnectGraph("server");
    EnlargeTo(0, 0, 150, 400);
    Fill(RGB(0, 0, 0));
    WidgetText = Text(200, 320, "Empty", RGB(255, 0, 0));
   
    attach = name_attach(NULL, ATTACH_POINT, 0);
    pthread_t tMainWarehouseWork, tServer, tServer2;
    pthread_create(&tMainWarehouseWork,NULL,mainWarehouseWork,NULL);
    pthread_create(&tServer,NULL,server,NULL);
 
    while(1)
    {
        int c = InputChar();
        //81 - left
        //82 - up
        //83 - right
        //84 - down
        if((int)c == 82)
            pthread_create(&tServer,NULL,server,NULL);
        if((int)c == 27)
            break;
        if((int)c == 84)
        {
            pthread_cancel(tServer--);
            isFilling = false;
        }
    }
    pthread_cancel(tMainWarehouseWork);
    pthread_cancel(tServer);
    CloseGraph();
    _exit(0);
    return 0;
}