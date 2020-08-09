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
		pa_start = start;
		pa_end = endFrame;
		player_anim = 1;	
	}	
}
/*Loads in the tradition level assets*/
void loadTradition(){
	//load prime robot character sprite
    temp = load_bitmap("images/chad_prime.bmp", NULL);
    for (n=0; n<12; n++){
		prime_image[n] = grabFrame(temp,256,256,0,0,4,n);
    }
    destroy_bitmap(temp);		
    prime = malloc(sizeof(SPRITE));
    prime->x = 1650;
    prime->y = 100;
    prime->width = prime_image[0]->w;
    prime->height = prime_image[0]->h;
    prime->xdelay = 1;
    prime->ydelay = 0;
    prime->xcount = 0;
    prime->ycount = 0;
    prime->xspeed = 2;
    prime->yspeed = 0;
    prime->curframe = 0;
    prime->maxframe = 3;
    prime->framecount = 0;
    prime->framedelay = 12;
    prime->animdir = 1;
    prime->startFrame = 0;
    prime->health = 500;
    prime->alive = 1;
    //load prime robot character sprite
    temp = load_bitmap("images/snek_larger.bmp", NULL);
    for (n=0; n<12; n++){
		snek_image[n] = grabFrame(temp,256,256,0,0,4,n);
    }
    destroy_bitmap(temp);		
    snek = malloc(sizeof(SPRITE));
    snek->x = 650;
    snek->y = 125;
    snek->width = snek_image[0]->w;
    snek->height = snek_image[0]->h;
    snek->xdelay = 1;
    snek->ydelay = 0;
    snek->xcount = 0;
    snek->ycount = 0;
    snek->xspeed = 2;
    snek->yspeed = 0;
    snek->curframe = 0;
    snek->maxframe = 3;
    snek->framecount = 0;
    snek->framedelay = 12;
    snek->animdir = 1;
    snek->startFrame = 0;
    snek->health = 500;
    snek->alive = 1;
}
/*Loads the sprites into their struct from their bitmap files*/
void loadLevel(char * map){   
	//load the map
	if(MapLoad(map)){
		printf("Error Loading Map Code: %d", n);
		exit(1);
	}
	//Eventually if more levels are built, add a parameter to pass the value for this
	mapName = TRADITION;
	switch(mapName){
		case TRADITION: loadTradition();
		break;
	}
	//load vlad playable character sprite
    temp = load_bitmap("images/vlad_all.bmp", NULL);
    for (n=0; n<32; n++){
		player_image[n] = grabFrame(temp,64,96,0,0,4,n);
    }
    destroy_bitmap(temp);		
    player = malloc(sizeof(SPRITE));
    player->x = 36;
    player->y = 360;
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
    player->health = 200;
    player->alive = 1;
    //Load in paint projectiles
    temp = load_bitmap("images/grey_paint.bmp", NULL);
    paint_image = grabFrame(temp,24,16,0,0,1,0);
    destroy_bitmap(temp);		
    for(n=0;n<NUMPROJ;n++){
		proj_paint[n] = malloc(sizeof(SPRITE));
	    proj_paint[n]->x = -50;
	    proj_paint[n]->y = -50;
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
//checks if coordinates are inside a given hitbox, return 1 if inside
int inside(int x,int y,int left,int top,int right,int bottom) {
	if (x > left && x < right && y > top && y < bottom){
		return 1;
	}
	else{
		return 0;
	}
}
//checks two sprites for collisions
int collide(SPRITE *first, SPRITE *second, int border) {
	//get width/height of both sprites 
	int width1 = first->x + first->width; 
	int height1 = first->y + first->height;
	int width2 = second->x + second->width; 
	int height2 = second->y + second->height;
	//see if corners of first are inside second boundary 
	if (inside(first->x, first->y, second->x + border, second->y + border, width2 - border, height2 - border)){
		return 1;
	}
	if (inside(first->x, height1, second->x + border, second->y + border, width2 - border, height2 - border)){
		return 1;
	}
	if (inside(width1, first->y, second->x + border, second->y + border, width2 - border, height2 - border)){ 
		return 1;
	}
	if (inside(width1, height1, second->x + border, second->y + border, width2 - border, height2 - border)){
		return 1;
	}
	return 0;//no collision return 0
}
/*Check collisions for enemy with attack (Snek can't be meleed)*/
void checkMelee(int x1, int x2, int y1, int y2){
	j=0;
	SPRITE *t = malloc(sizeof(SPRITE));
	tempSprite->x = x1;
    tempSprite->y = y1;
    tempSprite->width = x2 - x1;
    tempSprite->height = y1 - y2;
	switch(mapName){
		case TRADITION:			
		    //See if hit box is for front or back
			if(player->x < prime->x && prime->xspeed >0){//player on left side and prime walking to right
				j = collide(tempSprite, prime, 10);
			}else if(player->x < prime->x && prime->xspeed <0){//Player on left side and prime walking left
				t->x = prime->x+(prime->width/2);
			    t->y = prime->y;
			    t->width = prime->width/2;
			    t->height = prime->height;
				j = collide(tempSprite, t, 10);
			}else if(player->x > prime->x && prime->xspeed >0){//Player on right side and prime walking right
				t->x = prime->x;
			    t->y = prime->y;
			    t->width = prime->width/2;
			    t->height = prime->height;
				j = collide(tempSprite, t, 10);
			}else if(player->x > prime->x && prime->xspeed <0){//Player on right side and prime walkiing left
				j = collide(tempSprite, prime, 10);
			}
		    if(j){
		    	prime->health -= 25;
		    	if(prime->health <= 0){
		    		prime->alive = 0;
				}else{
					prime->y-=15;//Bounce when hit to let player know damage is dealt
				}
			}
			break;
	}
	free(t);
}
/*Check for any collision with the maps given enemies and the projectiles*/
void checkFire(SPRITE *spr){
	j=0;
	switch(mapName){
		case TRADITION:
			/*Prime*/
			//See if hit box is for front or back
			if(player->x < prime->x && prime->xspeed >0){//player on left side and prime walking to right
				j = collide(spr, prime, 10);
			}else if(player->x < prime->x && prime->xspeed <0){//Player on left side and prime walking left
				tempSprite->x = prime->x+(prime->width/2);
			    tempSprite->y = prime->y;
			    tempSprite->width = prime->width/2;
			    tempSprite->height = prime->height;
				j = collide(spr, tempSprite, 10);
			}else if(player->x > prime->x && prime->xspeed >0){//Player on right side and prime walking right
				tempSprite->x = prime->x;
			    tempSprite->y = prime->y;
			    tempSprite->width = prime->width/2;
			    tempSprite->height = prime->height;
				j = collide(spr, tempSprite, 10);
			}else if(player->x > prime->x && prime->xspeed <0){//Player on right side and prime walkiing left
				j = collide(spr, prime, 10);
			}
		    if(j){//Check if collided
		    	prime->health -= 25;
		    	if(prime->health <= 0){
		    		prime->alive = 0;
				}else{
					prime->y-=15;//Bounce when hit to let player know damage is dealt
				}
				spr->y=-50;//Get rid of shot so it doesnt hit more than once
			}
			j=0;
			/*Snek*/
			j = collide(spr, snek, 10);
		    if(j && snek->alive){//Check if collided
		    	snek->health -= 25;
		    	if(snek->health <= 0){
		    		snek->alive = 0;
				}else{
					snek->y-=15;//Bounce when hit to let player know damage is dealt
				}
				spr->y=-50;//Get rid of shot so it doesnt hit more than once
			}
			j=0;
			break;
	}
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
		}else if(key[KEY_SPACE] && key[KEY_S]){//Jump while using paint brush   
			playAnim(player, 28, 31);
		}else if (key[KEY_D]){ //Move right
	        facing = 1; 
	        player->xspeed=PLAYERSPEED;
	        playAnim(player, 4, 7);
	    }else if (key[KEY_A]){ //Move left
	        facing = 0; 
	        player->xspeed=-PLAYERSPEED;
	        playAnim(player, 4, 7);
	    }else if(key[KEY_SPACE]){//Just jump
			playAnim(player, 4, 7);
		}
	}else if (key[KEY_W]){//Shoot paint gun		
		if(jump == JUMPIT && key[KEY_D]){
	    	player->xspeed = PLAYERSPEED;
			playAnim(player, 12, 15);			
			n=14;
		}else if(jump == JUMPIT && key[KEY_A]){
	    	player->xspeed = -PLAYERSPEED;
			playAnim(player, 12, 15);			
			n=14;
		}else if(jump == JUMPIT){
	    	player->xspeed = 0;
			playAnim(player, 8, 11);			
			n=10;
		}else{
			playAnim(player, 16, 19);
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
    }else if (key[KEY_S]){//Use paint brush		
		if(jump == JUMPIT && key[KEY_D]){
	    	player->xspeed = PLAYERSPEED;
			playAnim(player, 24, 27);			
			n=26;
		}else if(jump == JUMPIT && key[KEY_A]){
	    	player->xspeed = -PLAYERSPEED;
			playAnim(player, 24, 27);			
			n=26;
		}else if(jump == JUMPIT){
	    	player->xspeed = 0;
			playAnim(player, 20, 23);			
			n=22;
		}else{
			playAnim(player, 28, 31);
			n=30;
		}
		if(player->curframe == n && fired == 0){				
			printf(".BEFORE");
			if(facing == 0){//melee left
			printf(".LEFT");
				checkMelee(player->x-40, player->x, player->y - 10, player->y - 60);
			}else{//melee right
			printf(".RIGHT");
				checkMelee(player->x+player->width, player->x+player->width+40, player->y - 10, player->y - 60);
			}
			printf(".AFTER");
			fired = 1;
		}else if(player->curframe == n){//keep fired flag on while on this frame
			fired = 1;
		}else{//turn fired flag off since animation restarted
			fired=0;
		}
    }else if (key[KEY_D]){ //Move right
        facing = 1; 
        player->xspeed=PLAYERSPEED;
        if(jump == JUMPIT){//Not jumping so normal animation
			playAnim(player, 0, 3);
		}else{//continues playing jump animation after jumping
			playAnim(player, 4, 7);
		}
    }else if (key[KEY_A]){ //Move left
        facing = 0; 
        player->xspeed=-PLAYERSPEED;
        if(jump == JUMPIT){//Not jumping so normal animation
			playAnim(player, 0, 3);
		}else{//continues playing jump animation after jumping
			playAnim(player, 4, 7);
		}
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
//Moves map around
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
			draw_sprite(buffer, paint_image, (proj_paint[j]->x-mapxoff+50), (proj_paint[j]->y-mapyoff+35));
		}
	}else{
		draw_sprite_h_flip(buffer, player_image[player->curframe], (player->x-mapxoff), (player->y-mapyoff));
		for(j=0;j<NUMPROJ;j++){
			draw_sprite_h_flip(buffer, paint_image, (proj_paint[j]->x-mapxoff-10), (proj_paint[j]->y-mapyoff+35));
		}
	}
	switch(mapName){//Switch on different maps to know what enemies to draw
		case TRADITION:
			if(prime->xspeed>0){//Prime
				draw_sprite(buffer, prime_image[prime->curframe], (prime->x-mapxoff), (prime->y-mapyoff+1));
			}else{
				draw_sprite_h_flip(buffer, prime_image[prime->curframe], (prime->x-mapxoff), (prime->y-mapyoff+1));
			}
			if(snek->xspeed<0){//Snek
				draw_sprite(buffer, snek_image[snek->curframe], (snek->x-mapxoff), (snek->y-mapyoff+1));
			}else{
				draw_sprite_h_flip(buffer, snek_image[snek->curframe], (snek->x-mapxoff), (snek->y-mapyoff+1));
			}
			break;
	}
}
/*Handles enemy updates and events*/
void handleEnemies(){
	switch(mapName){//Switch on different maps to know what enemies to draw
		case TRADITION:
			/*Handle Prime enemy*/
			if(prime->curframe != 11){//Last frame after dead, stay on it when dead
				if(!prime->alive){//He's dead so play the death animation
					playAnim(prime, 8, 11);
				}else if(collide(player, prime, 10)){
					player->health-=10;//player lose health
					if(prime->xspeed > 0 && player->x > prime->x){//bounce player back to right
						player->x += 10;
					}else if(prime->xspeed > 0 && player->x < prime->x){//bounce player back to left
						player->x -= 10;
					}else if(prime->xspeed < 0 && player->x < prime->x){//bounce player back to left
						player->x -= 10;
					}else{//bounce player back to left
						player->x += 10;
					}
				}
				if(prime->x>2000){
					prime->xspeed=-2;
				}else if(prime->x<1000){
					prime->xspeed=2;
				}
				if(!collided(prime->x + prime->width/2, prime->y + prime->height)){
		        	prime->yspeed=1; 
				}else{
					prime->yspeed=0;
				}
				updateSprite(prime);
			}else{//must be on last frame so just stay on it
				prime->xspeed=0;
			}	
			/*Handle Snek enemy*/
			if(snek->curframe != 11){//Last frame after dead, stay on it when dead
				if(!snek->alive){//He's dead so play the death animation
					playAnim(snek, 8, 11);
				}else if(collide(player, snek, 10)){
					player->health-=10;//player lose health
					if(snek->xspeed > 0 && player->x > snek->x){//bounce player back to right
						player->x += 10;
					}else if(snek->xspeed > 0 && player->x < snek->x){//bounce player back to left
						player->x -= 10;
					}else if(snek->xspeed < 0 && player->x < snek->x){//bounce player back to left
						player->x -= 10;
					}else{//bounce player back to left
						player->x += 10;
					}
				}
				if(snek->x>1000){
					snek->xspeed=-2;
				}else if(snek->x<600){
					snek->xspeed=2;
				}
				if(!collided(snek->x + snek->width/2, snek->y + snek->height)){
		        	snek->yspeed=1; 
				}else{
					snek->yspeed=0;
				}
				if(player->x < snek->x && player->x > snek->x-20){//stop player from passing through snake from left side
					player->x-=10;
					player->health-=20;
					printf(".HIT");
				}else if(player->x > snek->x && player->x > snek->x-snek->width+20){
					player->x-=10;
					player->health-=20;
					printf(".HIT");
				}
				updateSprite(snek);
			}else{//must be on last frame so just stay on it
				snek->xspeed=0;
			}				
			break;
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
	//printf(".1");  
	oldpy = player->y; 
    oldpx = player->x;
	updateSprite(player);//Update player sprite
	for(n=0;n<NUMPROJ;n++){//Update the player projectiles
		updateSprite(proj_paint[n]);
		checkFire(proj_paint[n]);//Check for collisions with enemies
	}	
	//printf(".2");
	handleEnemies();//Update enemies
	if(player->curframe == pa_end){//Turn off animation that finished
		player_anim = 0;
		player->animdir=0;
	}	
	//printf(".3");	
    updateMap();
    drawSprites();
    //printf(".4");
    //blit the double buffer 
	vsync();
	//printf(".5");
    acquire_screen();
    //printf(".6");
	blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
	//printf(".7");
    release_screen();
    //printf(".8");
}
/*Main function, handles initial loading. Passes on taks to be handled in title/game loop functions. When quit, destroys allocated memory.*/
int main(void){
    facing = 0, jump = JUMPIT, quit = 0, firetime = -1, player_anim = 0, pa_start = 0, pa_end = 0;
	fired = 0, cur_proj = 0;
	tempSprite = malloc(sizeof(SPRITE));
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
    free(prime);
    free(snek);
	destroy_bitmap(buffer);
	MapFreeMem ();
	printf(".CLEANED");
	allegro_exit();
	return 0;
}
END_OF_MAIN()
