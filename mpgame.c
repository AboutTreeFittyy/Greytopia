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
//Turns on an animation specified for the given sprite
void playAnim(SPRITE *spr, int start, int endFrame){
    //make sure animation not already in progress
    if(spr->startFrame != start ||  spr->animdir ==  0){
		spr->startFrame = start;
		spr->curframe = start;
	    spr->maxframe = endFrame;
	    spr->animdir = 1;	
	}	
}
/*Loads the sprites into their struct from their bitmap files*/
void loadLevel(char * map){   
	//load the map
	if(MapLoad(map)){
		printf("Error Loading Map Code: %d", n);
		exit(1);
	}
	//load vlad playable character sprite
    temp = load_bitmap("images/vlad_all.bmp", NULL);
    for (n=0; n<32; n++){
		player_image[n] = grabFrame(temp,64,96,0,0,4,n);
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
    player->animdir = 0;
    player->startFrame = 0;
    player->alive = 1;
    //Load in paint projectiles
    temp = load_bitmap("images/grey_paint.bmp", NULL);
    paint_image = grabFrame(temp,24,16,0,0,1,1);
    destroy_bitmap(temp);		
    for(n=0;n<NUMPROJ;n++){
		proj_paint[n] = malloc(sizeof(SPRITE));
	    proj_paint[n]->x = 30;
	    proj_paint[n]->y = 30;
	    proj_paint[n]->width = paint_image->w;
	    proj_paint[n]->height = paint_image->h;
	    proj_paint[n]->xdelay = 1;
	    proj_paint[n]->ydelay = 0;
	    proj_paint[n]->xcount = 0;
	    proj_paint[n]->ycount = 0;
	    proj_paint[n]->xspeed = 0;
	    proj_paint[n]->yspeed = 0;
	    proj_paint[n]->curframe = 0;
	    proj_paint[n]->maxframe = 0;
	    proj_paint[n]->framecount = 0;
	    proj_paint[n]->framedelay = 12;
	    proj_paint[n]->animdir = 0;
	    proj_paint[n]->startFrame = 0;
	    proj_paint[n]->alive = 1;
	}
}
/*Collision function*/
int collided(int x, int y){
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);	
	return blockdata->tl;
}
void tryAnim(){
	
}
/*Input handling function, checks pressed key to see what action to take depending on set flags at time*/
void getInput(){
	//Check for quit game
	if(key[KEY_ESC]){
		quit = 1;
	}
	if(player_anim == 1 && player->curframe >= pa_start && player->curframe < pa_end){		
		playAnim(player, pa_start, pa_end);
	}
	
	
	if(key[KEY_SPACE] && jump == JUMPIT){//Handle jumping
    	jump = 30;
	    if(key[KEY_SPACE] && key[KEY_W]){//Jump while shooting	    	
	    	playAnim(player, 16, 19);
	    	player_anim = 1;
	    	pa_start = 16;
	    	pa_end = 19;
	    	printf("1");
	    	/*if(player->curframe == 18 && fired == 0){
				printf("2");
				if(cur_proj == NUMPROJ){//Max reached
					cur_proj = 0;
				}				
				if(facing == 0){//shoot left
					proj_paint[cur_proj]->x=player->x;
					proj_paint[cur_proj]->y=player->y;
					proj_paint[cur_proj]->xspeed=-6;
				}else{//shoot right
					proj_paint[cur_proj]->x=player->x;
					proj_paint[cur_proj]->y=player->y;
					proj_paint[cur_proj]->xspeed=6;
				}
				fired = 1;
				cur_proj++;
			}else if(player->curframe == 18){//keep fired flag on while on this frame
				printf("3");
				fired = 1;
			}else{//turn fired flag off since animation restarted
				printf("4");
				fired=0;
			}*/
		}else if(key[KEY_SPACE] && key[KEY_S]){//Jump while using paint brush   
			playAnim(player, 28, 31);
	    	player_anim = 1;
	    	pa_start = 28;
	    	pa_end = 31;
		}else if (key[KEY_D]){ //Move right
	        facing = 1; 
	        player->xspeed=PLAYERSPEED;
	        playAnim(player, 4, 7);
	        player_anim = 1;
		   	pa_start = 4;
		    pa_end = 7;
	    }else if (key[KEY_A]){ //Move left
	        facing = 0; 
	        player->xspeed=-PLAYERSPEED;
	        playAnim(player, 4, 7);
	        player_anim = 1;
		    pa_start = 0;
		    pa_end = 3;
	    }else if(key[KEY_SPACE]){//Just jump
			playAnim(player, 4, 7);
	    	player_anim = 1;
	    	pa_start = 4;
	    	pa_end = 7;
		}
	}else if (key[KEY_D]){ //Move right
        facing = 1; 
        player->xspeed=PLAYERSPEED;
        if(jump == JUMPIT){//Not jumping so normal animation
			playAnim(player, 0, 3);
	        player_anim = 1;
		   	pa_start = 0;
		    pa_end = 3;
		}else{//continues playing jump animation after jumping
			playAnim(player, 4, 7);
	        player_anim = 1;
		   	pa_start = 4;
		    pa_end = 7;
		}
    }else if (key[KEY_A]){ //Move left
        facing = 0; 
        player->xspeed=-PLAYERSPEED;
        if(jump == JUMPIT){//Not jumping so normal animation
			playAnim(player, 0, 3);
	        player_anim = 1;
		   	pa_start = 0;
		    pa_end = 3;
		}else{//continues playing jump animation after jumping
			playAnim(player, 4, 7);
	        player_anim = 1;
		   	pa_start = 4;
		    pa_end = 7;
		}
    }else if (key[KEY_W]){			
	    player_anim = 1;
		if(jump == JUMPIT){
	    	player->xspeed = 0;
			playAnim(player, 8, 11);			
		    pa_start = 8;
		    pa_end = 11;
			n=10;
		}else{
			playAnim(player, 16, 19);
	    	player_anim = 1;
			pa_start = 16;
	    	pa_end = 19;
			n=18;
		}
		if(player->curframe == n && fired == 0){
			if(cur_proj == NUMPROJ){//Max reached
				cur_proj = 0;
			}				
			if(facing == 0){//shoot left
				proj_paint[cur_proj]->x=player->x;
				proj_paint[cur_proj]->y=player->y;
				proj_paint[cur_proj]->xspeed=-6;
			}else{//shoot right
				proj_paint[cur_proj]->x=player->x;
				proj_paint[cur_proj]->y=player->y;
				proj_paint[cur_proj]->xspeed=6;
			}
			fired = 1;
			cur_proj++;
		}else if(player->curframe == n){//keep fired flag on while on this frame
			fired = 1;
		}else{//turn fired flag off since animation restarted
			fired=0;
		}
    }else if (key[KEY_S] && jump == JUMPIT){//Use paint brush
		player->xspeed = 0;
		playAnim(player, 20, 23);
		player_anim = 1;
	    pa_start = 20;
	    pa_end = 23;
    }else {
		player->xspeed=0;
	}	
	//More stuff for handling Jumping
    if(jump==JUMPIT){ 
        if(!collided(player->x + player->width/2, player->y + player->height + 5)){
        	jump = 0; 
		}		              
    }else{
        player->y -= jump/3; 
        jump--; 
    }
	if(jump<0){ 
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

//updates the properties of the specified sprite
void updateSprite(SPRITE *spr){
    //update x position
    if (++spr->xcount > spr->xdelay){
        spr->xcount = 0;
        spr->x += spr->xspeed;
    }
    //update y position
    if (++spr->ycount > spr->ydelay){
        spr->ycount = 0;
        spr->y += spr->yspeed;
    }
    //update frame based on animdir
    if (++spr->framecount > spr->framedelay){
        spr->framecount = 0;
        if (spr->animdir == -1){
            if (--spr->curframe < spr->startFrame){
                spr->curframe = spr->maxframe;
            }
        }
        else if (spr->animdir == 1){
            if (++spr->curframe > spr->maxframe){
                spr->curframe = spr->startFrame;
            }
        }
    }
}
/*Draws all of the sprites in the game to the buffer*/
void drawSprites(){
	//draw the player's sprite
	if(facing){
		draw_sprite(buffer, player_image[player->curframe], (player->x-mapxoff), (player->y-mapyoff+1));		
		for(j=0;j<NUMPROJ;j++){
			draw_sprite(buffer, paint_image, (proj_paint[j]->x-mapxoff+50), (proj_paint[j]->y-mapyoff+40));
		}
	}else{
		draw_sprite_h_flip(buffer, player_image[player->curframe], (player->x-mapxoff), (player->y-mapyoff));
		for(j=0;j<NUMPROJ;j++){
			draw_sprite_h_flip(buffer, paint_image, (proj_paint[j]->x-mapxoff-10), (proj_paint[j]->y-mapyoff+40));
		}
	}
}
/*Loop used during title screen, handles selection/progression to gameloop or exiting application*/
void titleLoop(){
	
}
/*The main loop run when game in progress, handles flow of calls and checks as well as updating screen*/
void gameLoop(){	
    if(keypressed()){ //Get keyboard input when key(s) pressed
    	getInput();
	}    
	oldpy = player->y; 
    oldpx = player->x;
    //check for collided with foreground tiles
	if(!facing){	 
        if(collided(player->x, player->y + player->height)){	
			player->x = oldpx; 
		}                
    }else{ 
        if(collided(player->x + player->width, player->y + player->height)){
        	player->x = oldpx; 
		}               
    }	
	updateSprite(player);//Update player sprite
	for(n=0;n<NUMPROJ;n++){//Update the player projectiles
		updateSprite(proj_paint[n]);
	}	
	if(player->curframe == pa_end){//Turn off animation that finished
		player_anim = 0;
		player->animdir=0;
	}	
    updateMap();
    drawSprites();
    //blit the double buffer 
	vsync();
    acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
    release_screen();
}
/*Main function, handles initial loading. Passes on taks to be handled in title/game loop functions. When quit, destroys allocated memory.*/
int main(void){
    facing = 0, jump = JUMPIT, quit = 0, firetime = -1, player_anim = 0, pa_start = 0, pa_end = 0;
	fired = 0, cur_proj = 0;
	allegro_init();	
	install_timer();
	install_keyboard();
	set_color_depth(16);
    if(set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0)) {
        printf(".GFX_ERROR: ");
		allegro_message(allegro_error);
        return;
    }
    //install sound
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "")){
        allegro_message("Error initializing sound system");
        return 1;
    }
	printf(".LOADING");
	
//	printf("SCREEN_CODE: %d", screen);//NO idea why but the screen doesn't work sometimes causing the map to fail loading. Using this line helps for some reason
	
	/***This is set up this way so that multiple levels can be implemented mroe easily
		Try having level select from title screen or next map loaded when previous finished***/	
	loadLevel("images/tradition_bg/map.FMP");//loads the specified level and the sprites with it  
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
