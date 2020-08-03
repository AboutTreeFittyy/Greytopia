/* Allegro datafile object indexes, produced by grabber v3.11 (beta) */
/* Datafile: c:\cprog\mappy\mpgame.dat */
/* Date: Sat Mar  6 19:03:06 1999 */
/* Do not hand edit! */

#define GAMEMAP                          0        /* FMP  */
#define GAMEPAL                          1        /* PAL  */
#define PLAYER                           2        /* BMP  */
/***Don't touch above***/
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 4000
#define HEIGHT 640
#define JUMPIT 1600

//define the structure of the sprite
typedef struct SPRITE{
    int dir, alive;
    int x,y;
    int width,height;
    int xspeed,yspeed;
    int xdelay,ydelay;
    int xcount,ycount;
    int curframe,maxframe,animdir;
    int framecount,framedelay;
    int startFrame; //Used to manipulate where the animation will start (Allows for multiple animations in one sheet)
}SPRITE;

/***Global variables***/

//Art/sprite variables
BITMAP *player_image[16];//This limits max frames
BITMAP *temp;
SPRITE *player;
BITMAP *buffer;	


//Integer variables
int c, n, i, f, j; //index numbers
int oldpy, oldpx, mapxoff, mapyoff; //Misc
int quit, facing, jump; //Global flags/tracking numbers