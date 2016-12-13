//Brad Jones and Jeremy Benedek
//main.c for Final Project
//Dec 02 2016
#include <stdlib.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stm32f30x.h>
#include <f3d_lcd_sd.h>
#include <f3d_delay.h>
#include <glcdfont.h>
#include <stdio.h>
#include <f3d_mag.h>
#include <stdlib.h>
#include <string.h>
#include <f3d_timer2.h>
#include <f3d_dac.h>
#include <f3d_user_btn.h>
#define TIMER 20000
#define AUDIOBUFSIZE 128
#include <string.h>

  const char *b[1];
  int mode=0;
  nunchuk_t nun;
  nunchuk_t chuk;
  int values[]={50,-50,0,100,50,-50,0,100};//values of lights

extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

char key[]={'C','A','B','D','A','D','C','B','B','C','B','A','D','C','C'}; //answer key
char *intros[]={"logo.bmp","rules1.bmp","rules2.bmp","scoring.bmp","ready.bmp"};
char *ending[]={"winner.bmp","c1.bmp","c2.bmp","trophy2.bmp"};
char *question[]={"q1.bmp", "q2.bmp", "q3.bmp", "q4.bmp", "q5.bmp", "q6.bmp", "q7.bmp", "q8.bmp", "q9.bmp", "q10.bmp", "q11.bmp", "q12.bmp", "q13.bmp", "q14.bmp", "q15.bmp"};


FATFS Fatfs;		/* File system object */
FIL fid;		/* File object */
BYTE Buff[512];		/* File read buffer */
int ret;
int scorex=0;
int scorey=0;

uint8_t side[]={0x02,0x03,0x05,0x06};  //determines which way picture is drawn
char *pics[]={"1.bmp","2.bmp","3.bmp"};  //pictures to be drawn

typedef struct {    //holds bmp info
  unsigned char magic [2];
} bmpfile_magic;

typedef struct {  //holds bmp header info
  uint32_t filesz ;
  uint16_t creator1 ;
  uint16_t creator2 ;
  uint32_t bmp_offset ;
} bmpfile_header;

typedef struct {  //holds bmp file info
  uint32_t header_sz ;
  int32_t width ;
  int32_t height ;
  uint16_t nplanes ;
  uint16_t bitspp ;
  uint32_t compress_type ;
  uint32_t bmp_bytesz ;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors ;
  uint32_t nimpcolors ;
} BITMAPINFOHEADER ;

typedef struct { // little endian byte order
  uint8_t b;
  uint8_t g;
  uint8_t r;
} bmppixel;

bmpfile_magic magic;
bmpfile_header header;
BITMAPINFOHEADER info;


uint16_t convertColor(bmppixel* color);
void truncateImageBottom();
void readHeaders();

static const uint16_t height_width_difference = ST7735_height - ST7735_width;

void die (FRESULT rc) {
        printf("Failed with rc=%u.n", rc);
        while (1) ;
}

uint16_t convertColor(bmppixel *color) {  //converts pixel into color  
  uint16_t r = color->r >> 3;
  uint16_t g = color->g >> 2;
  uint16_t b = color->b >> 3;

  uint16_t pixel = r;
  pixel |= (g << 5);
  pixel |= (b << 11);
  return pixel;
}

void truncateImageBottom() {
  UINT br;
  bmppixel trashPixelBuffer[ST7735_width];
  int i;
  for (i = 0; i < height_width_difference; i++) {
    f_read(&fid, (void *) trashPixelBuffer, sizeof(bmppixel) * ST7735_width, &br);
  }
}

void readHeaders() {
  UINT br;
  // read bmp headers
  f_read(&fid, (void *) &magic, 2, &br);
  f_read(&fid, (void *) &header, sizeof(header), &br);
  f_read(&fid, (void *) &info, sizeof(info), &br);

  // @hack - we have to throw away a bunch of bytes here
  //         for the image to line up correctly
  const int TRASH_BYTES = sizeof(bmppixel) * 28;
  bmppixel bmpTrash[TRASH_BYTES];
  //f_read(&Fil, (void *) bmpTrash, TRASH_BYTES, &br);
}

int gyro(){  //reads info from gyro and calculates roll and pitch
float a[3];
float temp,pitch,roll;
f3d_accel_read(a);
temp=(a[1]*a[1])+(a[2]*a[2]);
pitch=atan(a[0]/sqrt(temp));
pitch=pitch*(180/M_PI);
temp=(a[2]*a[2])+(a[0]*a[0]);
roll=atan(a[1]/sqrt(temp));
roll=roll*(180/M_PI);
if(roll>1){
return 1;
}
else if(roll<-1){
return 2;
}
else if(pitch>1){
return 3;
}
else{
return 0;
}
}

void drawpicture(char* x,uint8_t way){//draws picture on screen
    char footer[20];
    int count=0;
    int i;
    FRESULT rc;         /* Result code */
    DIR dir;            /* Directory object */
    FILINFO fno;            /* File information object */
    UINT bw, br;
    unsigned int retval;
    f_mount(0, &Fatfs); /* Register volume work area (never fails) */
    char fname[10];
    strcpy(fname, x);
    rc = f_open(&fid, fname, FA_READ);
        if (rc) die(rc);
    readHeaders(); 

    int row, col;
    bmppixel bmpBuffer[sizeof(bmppixel) * ST7735_width];
    uint16_t rowBuffer[ST7735_width];

    int border = 0;
        for (row = border; row <= ST7735_height - 1 - border; row++) {
            // read in one row of the image
            f_read(&fid, (void *) bmpBuffer, sizeof(bmppixel) * ST7735_width, &br);
        for (col = ST7735_width - 1; col >= 0; col--) {
        // convert bmp pixels to ST7735 pixels
        rowBuffer[col] = convertColor(&bmpBuffer[col]);
        }
        // write to screen
        f3d_lcd_setAddrWindow(-20, row, ST7735_width - 1, row + 1,way);
        f3d_lcd_pushColor(rowBuffer, ST7735_width);
    }

rc=f_close(&fid);
}

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;      
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd))
    exit(-1);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
}

void sound(int one){  // plays an audio file
  FRESULT rc;                   /* Result code */
  DIR dir;                      /* Directory object */
  FILINFO fno;                  /* File information object */
  UINT bw, br;
  unsigned int retval;
 
  char *sounds[]={"coin.wav","gameover.wav"};  //files available to select

  	rc = f_open(&fid,sounds[one], FA_READ); //file is opened
	
	if (!rc) {
		struct ckhd hd;
		uint32_t waveid;
		struct fmtck fck;
		readckhd(&fid, &hd, 'FFIR');
		
		f_read(&fid, &waveid, sizeof(waveid), &ret);
		
		readckhd(&fid, &hd, ' tmf');		
		f_read(&fid, &fck, sizeof(fck), &ret);
		
		if (hd.cksize != 16) {
			//printf("extra header info %d\n", hd.cksize - 16);
			f_lseek(&fid, hd.cksize - 16);
		}
				
		while(1){
			readckhd(&fid, &hd, 0);
			if (hd.ckID == 'atad')
				break;
			f_lseek(&fid, hd.cksize);
		}
		
		f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
		hd.cksize -= ret;
		audioplayerStart();
		while (hd.cksize) {
			int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
			if (audioplayerHalf) {
				if (next < AUDIOBUFSIZE/2)
					bzero(Audiobuf, AUDIOBUFSIZE/2);
				f_read(&fid, Audiobuf, next, &ret);
				hd.cksize -= ret;
				audioplayerHalf = 0;
			}
			if (audioplayerWhole) {
				if (next < AUDIOBUFSIZE/2)
					bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
				f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
				hd.cksize -= ret;
				audioplayerWhole = 0;
			}
		}
		audioplayerStop();
	}
	
	rc = f_close(&fid); //file is closed
	
	if (rc) die(rc);
}

int ledspinner(int x){//cycles through lights on board
 int count = 0;
  while (1){
    while(user_btn_read()==0){    //runs while button is not held down
    int k;
	for(k=0;k<8;k++){
	f3d_led_all_off();
	f3d_led_on(k);
	delay(x);
	
	  while(user_btn_read()==1){
        
	return values[k];
	break;
	}
   }
  }
 }
f3d_led_all_off();
}
char *intro[]={"BLUE","GREEN","RED","BLACK","WHITE"};
void instructions(){//opening pictures of game
int d=0;
int e;
int f=0;
char p[16];
drawpicture(intros[0],side[0]);
while(d<5){
if(d==0){
e=gyro();   
  if(e!=f){   //runs if orientation of board has changed

   f3d_lcd_fillScreen(WHITE);   
     drawpicture(intros[d],side[e]);
      f=e;     
    delay(1000);
}
}
    f3d_nunchuk_read(&nun,1);
    f3d_nunchuk_read(&chuk,2);
if(nun.jx>210||chuk.jx>210){
d++;
if(d==5){
break;
}
f3d_lcd_fillScreen(WHITE);
drawpicture(intros[d],side[0]);
delay(1000);
}
else if((nun.jx<30||chuk.jx<30)&&d>0){
d--;
f3d_lcd_fillScreen(WHITE);
drawpicture(intros[d],side[0]);
delay(1000);
}
}
f3d_lcd_fillScreen(GREEN);
}

char answer[]={'A','B','C','D'};//answers to select from

int correct(int x,int y){//function where user chooses answer
int choose=0;
 f3d_lcd_drawChar(60, 60,answer[0],BLACK,GREEN);

if(x==0){//runs if player one buzzed first 
f3d_nunchuk_read(&nun,1);
while(nun.c!=1){
delay(100);
f3d_nunchuk_read(&nun,1);

if(nun.jy>210&&choose>0){//runs if joystick is pointed up
 f3d_lcd_drawChar(60,60, answer[choose], GREEN,GREEN);
choose--;
// f3d_lcd_fillScreen(BLUE);
 f3d_lcd_drawChar(60,60,answer[choose], BLACK,GREEN);
delay(500);
}
else if(nun.jy<30&&choose<3){//runs if joystick points down
 f3d_lcd_drawChar(60, 60,answer[choose], GREEN,GREEN);
choose++;
// f3d_lcd_fillScreen(BLUE);
 f3d_lcd_drawChar(60, 60,answer[choose], BLACK,GREEN);
 delay(500);
nun.z=0;
}
}

}


else{//runs if player two buzzed first

f3d_nunchuk_read(&chuk,2);

while(chuk.c!=1){
    f3d_nunchuk_read(&chuk,2);  
if(chuk.jy>210&&choose>0){//runs if joystick is pointed up
 f3d_lcd_drawChar(60, 60, answer[choose], GREEN,GREEN);
choose--;
 f3d_lcd_drawChar(60, 60,answer[choose],BLACK,GREEN);
delay(500);
}
else if(chuk.jy<30&&choose<3){//runs if joystick is pointed down
 f3d_lcd_drawChar(60, 60,answer[choose], GREEN,GREEN);
choose++;
// f3d_lcd_fillScreen(BLUE);
 f3d_lcd_drawChar(60, 60,answer[choose], BLACK,GREEN);
delay(500);
}
}
}
if(answer[choose]==key[y]){//runs if user selected correctly
//sound(correct);
return 0;
}
else{ //runs if user selected incorrectly
//sound(wrong);
return 1;
}
}

int questions(int x){//used to show pictures of questions
char p[16];
char r[16];
int number=0;
int a=0;
int b=0;
int which;
while(number<5){

   sprintf(p, "Player1:%d", scorex);
     sprintf(r, "Player2:%d", scorey);
	f3d_lcd_fillScreen(WHITE);
	
 f3d_lcd_drawString(30,60,p,BLACK,WHITE);
 f3d_lcd_drawString(30,80,r,BLACK,WHITE);
delay(5000);
drawpicture(question[x*5+number],side[0]);
f3d_led_all_off();
while(a==0&&b==0){
  f3d_nunchuk_read(&nun,1);
    f3d_nunchuk_read(&chuk,2);
   if(nun.z==1){
   a=1;
   f3d_lcd_fillScreen(GREEN);
   delay(500);
}
else if(chuk.z==1){
  b=1;
  f3d_lcd_fillScreen(GREEN);
  chuk.z=0;
  delay(1000);
}
}
if(a==1){
which=correct(0,number);
if(which==0){ 
 f3d_lcd_fillScreen(BLACK);
 f3d_lcd_drawString(50,50,"CORRECT!",WHITE,BLACK);
 scorex+=ledspinner(45-(9*number));
  }
else{
  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_drawString(50,50,"WRONG!",WHITE,BLACK);
  scorey+=ledspinner(45-(9*number));

}
}
else{
which=correct(1,number);
if(which==0){
f3d_lcd_fillScreen(BLACK);
 f3d_lcd_drawString(50,50,"CORRECT!",WHITE,BLACK);
 scorey+=ledspinner(45-(9*number));
}
else{
f3d_lcd_fillScreen(BLACK);
 f3d_lcd_drawString(50,50,"WRONG!",WHITE,BLACK);

  scorex+=ledspinner(45-(9*number));
}
}
number++;
a=0;
b=0;
}
if(scorex>scorey){
sound(1);
return 1;
}
else{
sound(1);
return 2;
}

}

int end(int x){
int c;
f3d_lcd_fillScreen(WHITE);
drawpicture(ending[0],side[0]);
if(x==1){
f3d_lcd_fillScreen(WHITE);
drawpicture(ending[1],side[0]);
delay(2000);
}
else{
f3d_lcd_fillScreen(WHITE);
drawpicture(ending[2],side[0]);
delay(2000);
}
f3d_lcd_fillScreen(WHITE);
drawpicture(ending[3],side[0]);
if(x==1){
for(c=0;c<1000;c++){
 f3d_nunchuk_read(&nun,1);
 delay(100);
if(nun.z==1){
f3d_lcd_fillScreen(BLUE);
scorex=0;
scorey=0;
return 0;
break;
}
}
}
else{
for(c=0;c<1000;c++){
 f3d_nunchuk_read(&chuk,2);
 delay(100);
if(chuk.z==1){
f3d_lcd_fillScreen(GREEN);
return 0;
break;
}
}
}

return 1;
}

int main(void) { 
  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;
  int bytesread,e;
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
	      f3d_lcd_init();
	delay(100);
	f3d_user_btn_init();
	delay(100);
  f3d_lcd_fillScreen(WHITE);

        f3d_led_init();
	delay(100);
	f3d_gyro_init();
        delay(100);   
	f3d_timer2_init();
	delay(100);
//	f3d_accel_init();
	delay(100);
	f3d_dac_init();
	delay(100);
	f3d_delay_init();
	delay(100);
	f3d_rtc_init();
	delay(100);
	f3d_i2c1_init();
	delay(100);
          //file is called
        f3d_nunchuk_init(1);
	f3d_nunchuk_init(2);	
  f_mount(0, &Fatfs);/* Register volume work area */
instructions();
int role=0;
int escape=0;
int win;
  //initial screen is drawn
  while(role<3&&escape==0){
  f3d_lcd_fillScreen(WHITE);

// f3d_lcd_fillScreen(GREEN);
win=questions(role);
  role++;
escape=end(win);
}

  }

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
