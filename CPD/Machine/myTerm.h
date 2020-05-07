#ifndef myTerm
#define myTerm

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
// Перечисления цветов консоли
enum colors
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE,
	CONSOLE = 9
};

char temp[20];

int mt_getscreensize(int *, int *);
int mt_clrscr();
int mt_gotoXY(int, int);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

#endif
