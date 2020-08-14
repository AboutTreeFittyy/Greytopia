/*File Name: mpgame.h
 *Author: Mathew Boland
 *Last Updated: August 14, 2020
 *Project: Greytopia
 *Version: 1.0
*/

#define GAMEMAP                          0        /* FMP  */
#define GAMEPAL                          1        /* PAL  */
#define PLAYER                           2        /* BMP  */
/***Don't touch above***/
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define JUMPIT 1600
#define PLAYERSPEED 4
#define NUMPROJ 6
#define FATS 4
#define COMMIES 5
#define TRADITION 0
#define EQUALITY 1
#define MUSIC 0

#define OH_YEAH 2
#define BLEEP 3
#define HISS 4
#define AM_ANTH 5

#define MURICA 7
#define SQUIRT 8
#define SLUSH 9
#define LASER 10
#define USSR_ANTH_R 11
#define BURP 12
#define PING 13
#define TEXTCOLOUR makecol(0,0,51)
//define the structure of the sprite
typedef struct SPRITE{
    int dir, cnt, alive, health;
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
//Sound
SAMPLE *sounds[14];
int volume = 128;
int pan = 128;
int pitch = 1000;
//Art/sprite variables
BITMAP *bar;
BITMAP *title;
BITMAP *lose;
BITMAP *victory_trad;
BITMAP *victory_equal;
BITMAP *pause_1;
BITMAP *pause_2;
BITMAP *splash;
BITMAP *player_image[40];
BITMAP *prime_image[12];
BITMAP *snek_image[12];
BITMAP *fat_image[24];
BITMAP *commie_image[14];
BITMAP *drag_image[12];
BITMAP *paint_image;
BITMAP *star_image;
BITMAP *temp;
BITMAP *buffer;	
SPRITE *tempSprite;
SPRITE *proj_paint[6];//player projectiles
SPRITE *player;
SPRITE *snek;//Tradition enemies
SPRITE *fat[FATS];
SPRITE *prime;
SPRITE *drag;//Equality Enemies
SPRITE *commie[COMMIES];
SPRITE *star[COMMIES*NUMPROJ];//Enemy projectiles

//Integer variables
int c, n, i, f, j, s, p; //index numbers
int oldpy, oldpx, mapxoff, mapyoff, pa_start, pa_end, gameOn, selected; //Misc
int quit, music, paused, facing, jump, resting, firetime, player_anim, cur_proj, fired, mapName; //Global flags/tracking numbers
















