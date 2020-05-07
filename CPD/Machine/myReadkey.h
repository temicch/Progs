#ifndef myReadkey
#define myReadkey

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
// Коды клавиш
enum keys
{
	KEY_TAB = 9,
	KEY_ENTER,
	KEY_I = 105,
	KEY_L = 108,
	KEY_R = 114,
	KEY_S,
	KEY_T,
	KEY_F5= 53,
	KEY_F6 = 55,
	KEY_F7,
	KEY_UP = 65,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT
};

int rk_mytermregime(int, int, int, int, int);
int rk_mytermsave(void);
int rk_readkey(enum keys *);
int rk_mytermrestore(void);

#endif