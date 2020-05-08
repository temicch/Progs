const int XL1 = 10, XL2 = 20, XL3 = 780, XL4 = 790; // locators positions
const int BulletDelay = 10000000; // one point time for bullet, in ns
const int BulletY0 = 570; // initial y-coordinate of a bullet
const int GunDelay = 25; // one point time for gun move, in ms
const int GunY = 570; // gun's y-coordinate
const int RCMDelay = 4000000; // one point time for RCM, in ns

// registers
const int LOC_INTR = 10; // interrupt number for locators
const int RG_LOCN = 0; // (r) locator num (1..4)
const int RG_LOCY = 4; // (r) y-coordinate of target
const int RG_LOCW = 8; // (r) width of target
const int RG_GUNS = 12; // (w) gun shoot command
  const int GUNS_SHOOT = 111;
const int RG_GUNM = 16; // (w) gun move command
  const int GUNM_LEFT = -1;
  const int GUNM_RIGHT = 1;
  const int GUNM_STOP = 0;
const int RG_GUNX = 16; // (r) gun x-coordinate
const int RG_RCMN = 20; // (w) RCM (radio-controlled missile) num (0..10)
const int RG_RCMC = 24; // (w) RCM command: |cmd| - |dy |dx |
  const int RCMC_START = 0x0100FF00;
  const int RCMC_LEFT  = 0x020000FF;
  const int RCMC_UP    = 0x0200FF00;
  const int RCMC_RIGHT = 0x02000001;
  const int RCMC_DOWN  = 0x02000100;

extern int getreg (int reg);
extern void putreg (int reg, int value);
//extern int InterruptAttach (int intno, const struct sigevent* (*handler)(void*, int),
//                     const void * area, int size, unsigned flags );
//extern int InterruptAttachEvent (int intno, const struct sigevent * event, unsigned flags );
//extern int InterruptDetach (int id);
extern void InterruptDisable_ ();
extern void InterruptEnable_ ();
extern void StartGame (int level);
extern void EndGame ();

