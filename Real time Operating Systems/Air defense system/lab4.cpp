#include <vingraph.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include "plates.h"
 
using namespace std;
 
struct sigevent ev;
 
const int windowY = 600;
 
struct sPlates
{
    int t1, t1_sec, t2, t2_sec, y, dir;
} oPlates[windowY];
 
timespec calculateNS(double ns)
{
    double fullNS = (double)ns;
    int sec = (int)(fullNS / (double)1000000000);
    fullNS -= (double)sec * (double)1000000000;
    printf("SEC: %d NSEC: %f\n", sec, fullNS);
    timespec result;
    result.tv_sec = sec;
    result.tv_nsec = (int)fullNS;
    return result;
}
 
int bRocket = 0;
 
int setSendData(int N, int Y, int Fast)
{
    int result = Y | (N << 10) | (Fast << 13);
    return result;
}
 
void getSendData(int data, int *N, int *Y, bool *Fast)
{
    *N = (data >> 10)&0x7;
    *Y = (data) & 0x3ff;
    *Fast = (data >> 13);
}
 
int PYC_shoot()
{
    int currentRocket = bRocket++;
    putreg(RG_RCMN, currentRocket);
    putreg(RG_RCMC, RCMC_START);
    return currentRocket;
}
 
void PYC_setDir(int rocket, int dir)
{
        putreg(RG_RCMN, rocket);
        putreg(RG_RCMC, dir);                          
}
 
void *markWork(void *args)
{
    int N, Y, x, Fast;
    getSendData(*((int*)args), &N, &Y, (bool*)(&Fast));
 
    if(N == 1)
        x = 10;
    else if(N == 2)
        x = 20;
    else if(N == 3)
        x = 780;
    else if(N == 4)
        x = 790;
    int color, line1, line2, circle1, circle2;
    if(Fast)
        color = RGB(8, 252, 248);
    else
        color = RGB(128, 128, 128);
   
    line1 = Line(x - 5, Y - 5, x + 5, Y + 5, color);
    line2 = Line(x - 5, Y + 5, x + 5, Y - 5, color);
    circle1 = Ellipse(x - 3-1-1, Y - 3-1-1, 12, 12, color);
    circle2 = Ellipse(x - 3, Y - 3, 8, 8, color);
   
    for(int i = 0; i < 5; i++)
    {
        Show(line1);
        Show(line2);
        Show(circle1);
        Show(circle2);
        delay(1200);
        Hide(line1);
        Hide(line2);
        Hide(circle1);
        Hide(circle2);
        delay(500);
    }
}
 
int getDir(int x)
{
    if(x == -1)
        return RCMC_LEFT;
    return RCMC_RIGHT;
}
 
void *plateWork(void *args)
{
    sPlates *pla = (sPlates*)args;
    timespec t;
   
    double t1, t2;
    t1 = modf((570 - (double)pla->y) / 100, &t2);
   
    double t4 = (t1 * 1000000000 + t2 * 1000000000);
    double t3 = ((pla->t2 + 1000000000 * (pla->t2_sec - pla->t1_sec)) - pla->t1) * (double)38;
    //printf("Raketa letit za: %f\n", t4);
    //printf("Tarelka letit za: %f\n", t3);
    if(t3 < t4)
    {
        t1 = modf((570 - (double)pla->y) / 250, &t2);
        t4 = (t1 * 1000000000 + t2 * 1000000000);
        t = calculateNS(t4);
        int currentRocket = PYC_shoot();
        int sendData = setSendData(pla->dir == -1 ? 2 : 3, pla->y, 1);
        pthread_create(NULL, NULL, markWork,(void *)&sendData);
        clock_nanosleep(CLOCK_REALTIME, 0, &t, NULL);
        if(t4 > t3)
        {
            PYC_setDir(currentRocket, getDir(-1 * pla->dir));                          
        }
        else
        {
            PYC_setDir(currentRocket, getDir(pla->dir));                       
        }
    }
    else
    {
        t = calculateNS(t3 - t4);
        int sendData = setSendData(pla->dir == -1 ? 2 : 3, pla->y, 0);
        pthread_create(NULL, NULL, markWork,(void *)&sendData);
   
        clock_nanosleep(CLOCK_REALTIME, 0, &t, NULL);
        putreg(RG_GUNS, GUNS_SHOOT);
    }
    oPlates[pla->y].t1 = 0;
}
 
const struct sigevent *intr(void *area, int id)
{
    int n, y, w;
    n = getreg(RG_LOCN);
    y = getreg(RG_LOCY);
    w = getreg(RG_LOCW);
    ev.sigev_value.sival_int = n + (y << 16) + (w << 3);
    return &ev;
}
 
int main()
{
    int buf[4];
    for(int i = 0; i < windowY; i++)
    {
        oPlates[i].t1 = 0;
        oPlates[i].t2 = 0;
        oPlates[i].t1_sec = 0;
        oPlates[i].t2_sec = 0;
    }
    StartGame(3);
    int chan = ChannelCreate(0);
    int coid = ConnectAttach(0, 0, chan, 0, 0);
    SIGEV_PULSE_INIT(&ev, coid, 10, 0, 0);
    while(1)
    {
        int rsid = InterruptAttach(LOC_INTR, intr, 0, 0, _NTO_INTR_FLAGS_TRK_MSK);
        if(rsid >= -1)
            break;
    }
    char c;
    while(1)
    {
        MsgReceive(chan, buf, 16, 0);
        timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        int y = buf[2] >> 16, n = buf[2] & 7, w = (buf[2] >> 3) & 7;
        if(w == 3)
        {
            if(n > 1 && n < 4)
            {
                oPlates[y].t2 = t.tv_nsec;
                oPlates[y].t2_sec = t.tv_sec;
                if(oPlates[y].t1 != 0)
                {
                    oPlates[y].dir = (n == 2) ? -1: 1;
                    oPlates[y].y = y;
                    pthread_create(NULL, NULL, plateWork,(void *)&oPlates[y]);
                }
            }
            else
            {
                oPlates[y].t1 = t.tv_nsec;
                oPlates[y].t1_sec = t.tv_sec;
            }
        }
    }
    EndGame();
    return 0;
}
