#include <stdio.h>
#include <allegro.h>
#include "mappyal.h"
#include "mpgame.h"
/*tile grabber*/
BITMAP *grabFrame(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame){
    BITMAP *temp = create_bitmap(width,height);
    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;
    blit(source,temp,x,y,0,0,width,height);
    return temp;
}
/*Loads the sprites into their struct from their bitmap files*/
void loadLevel(char * map){   
	//load the map
	n = MapLoad("images/tradition_bg/map.FMP");
	if(n){
		printf("Error Loading Map Code: %d", n);
		exit(1);
	}
	//load vlad playable character sprite
    temp = load_bitmap("images/vlad.bmp", NULL);
    for (n=0; n<16; n++){
		player_image[n] = grabFrame(temp,64,96,0,0,9,n);
    }
    destroy_bitmap(temp);		
    player = malloc(sizeof(SPRITE));
    player->x = 80;
    player->y = 100;
    player->width = player_image[0]->w;
    player->height = player_image[0]->h;
    player->xdelay = 1;
    player->ydelay = 0;
    player->xcount = 0;
    player->ycount = 0;
    player->xspeed = 0;
    player->yspeed = 0;
    player->curframe = 0;
    player->maxframe = 3;
    player->framecount = 0;
    player->framedelay = 12;
    player->animdir = 1;
    player->startFrame = 0;
    player->alive = 1;
}
/*Collision function*/
int collided(int x, int y){
    printf(".COLLIDE");	
	BLKSTR *blockdata;
	printf("3");	
	printf(".INTS: %d, %d", x, y);
	printf(".HEIGHTS: %d, %d", mapblockwidth, mapblockheight);
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	printf("4");	
	return blockdata->tl;
}
/*Input handling function, checks pressed key to see what action to take depending on set flags at time*/
void getInput(){
	//Check for quit game
	if(key[KEY_ESC]){
		quit = 1;
	}
	if (key[KEY_RIGHT]){ 
        facing = 1; 
        player->x+=2; 
        if (++player->framecount > player->framedelay){
            player->framecount=0;
            if (++player->curframe > player->maxframe)
                player->curframe=1;
        }
    }else if (key[KEY_LEFT]){ 
        facing = 0; 
        player->x-=2; 
        if (++player->framecount > player->framedelay){
            player->framecount=0;
            if (++player->curframe > player->maxframe){
            	 player->curframe=1;
			}                   
        }
    }else {
		player->curframe=0;
	}
	//handle jumping
    if (jump==JUMPIT){ 
        if (!collided(player->x + player->width/2, player->y + player->height + 5)){
        	jump = 0; 
		}
	    if (key[KEY_SPACE]) {
	    	jump = 30;
		}                
    }
    else{
        player->y -= jump/3; 
        jump--; 
    }
	if (jump<0) { 
        if (collided(player->x + player->width/2, player->y + player->height)){ 
            jump = JUMPIT; 
            while (collided(player->x + player->width/2, player->y + player->height)){
            	player->y -= 2; 
			}                    
        } 
    }
}

void updateMap(){
	//update the map scroll position
	mapxoff = player->x + player->width/2 - WIDTH/2 + 10;
	mapyoff = player->y + player->height/2 - HEIGHT/2 + 10;
    //avoid moving beyond the map edge
	if(mapxoff < 0){
		mapxoff = 0;
	}
	if(mapxoff > (mapwidth * mapblockwidth - WIDTH)){
		mapxoff = mapwidth * mapblockwidth - WIDTH;
	}            
	if(mapyoff < 0){
		mapyoff = 0;
	}            
	if(mapyoff > (mapheight * mapblockheight - HEIGHT)){
		mapyoff = mapheight * mapblockheight - HEIGHT;
	}
	//draw the background tiles
	MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1);
    //draw foreground tiles
	MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1, 0);
}

void updateSprites(){
	//draw the player's sprite
	if(facing){
		draw_sprite(buffer, player_image[player->curframe], (player->x-mapxoff), (player->y-mapyoff+1));
	}else{
		draw_sprite_h_flip(buffer, player_image[player->curframe], (player->x-mapxoff), (player->y-mapyoff));
	}
}
/*Loop used during title screen, handles selection/progression to gameloop or exiting application*/
void titleLoop(){
	
}
/*The main loop run when game in progress, handles flow of calls and checks as well as updating screen*/
void gameLoop(){
	oldpy = player->y; 
    oldpx = player->x;
    if(keypressed()){ //Get keyboard input when key(s) pressed
    	getInput();
	}    
	printf(".FACING");	
    //check for collided with foreground tiles
	if(!facing){
		printf("1");	 
        if(collided(player->x, player->y + player->height)){
        	printf("2");	
			player->x = oldpx; 
		}                
    }else{ 
        if(collided(player->x + player->width, player->y + player->height)){
        	player->x = oldpx; 
		}               
    }		
    updateMap();
    updateSprites();
    //blit the double buffer 
	vsync();
    acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();
}
/*Main function, handles initial loading. Passes on taks to be handled in title/game loop functions. When quit, destroys allocated memory.*/
int main(void){
    facing = 0, jump = JUMPIT, quit = 0;
	allegro_init();	
	install_timer();
	install_keyboard();
	set_color_depth(16);
	set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
	printf(".LOADING");
	/***This is set up this way so that multiple levels can be implemented mroe easily
		Try having level select from title screen or next map loaded when previous finished***/	
	loadLevel("images/test.FMP");//loads the specified level and the sprites with it  
	printf(".LOADED");  
    //create the double buffer
	buffer = create_bitmap(WIDTH, HEIGHT);
	clear(buffer);
    //master loop
	while(!quit){		
		//Sudo code for when implementing title screen		
		//Have gameLoop run while a new flag "playing" is = 1
		//Have if else in getInput for ESC so if "playing" then only that is turned off to return to title, otherwise "quit" exiting application		
		gameLoop();//Plays the game
	} //while
	//Cleanup
	printf(".CLEANING");
    for (n=0; n<8; n++){
    	destroy_bitmap(player_image[n]);
	}        
    free(player);
	destroy_bitmap(buffer);
	MapFreeMem ();
	printf(".CLEANED");
	allegro_exit();
	return 0;
}
END_OF_MAIN()