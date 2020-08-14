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
    temp = load_bitmap("images/tradition_bg/chad_prime.bmp", NULL);
    for (n=0; n<12; n++){
		prime_image[n] = grabFrame(temp,256,256,0,0,4,n);
    }
    destroy_bitmap(temp);		
    prime = malloc(sizeof(SPRITE));
    prime->x = 3500;
    prime->y = 0;
    prime->width = prime_image[0]->w;
    prime->height = prime_image[0]->h;
    prime->xdelay = 1;
    prime->ydelay = 0;
    prime->xcount = 0;
    prime->ycount = 0;
    prime->xspeed = 0;
    prime->yspeed = 0;
    prime->curframe = 0;
    prime->maxframe = 3;
    prime->framecount = 0;
    prime->framedelay = 12;
    prime->animdir = 1;
    prime->startFrame = 0;
    prime->health = 300;
    prime->alive = 1;
    //load prime robot character sprite
    temp = load_bitmap("images/tradition_bg/snek_larger.bmp", NULL);
    for (n=0; n<12; n++){
		snek_image[n] = grabFrame(temp,256,256,0,0,4,n);
    }
    destroy_bitmap(temp);		
    snek = malloc(sizeof(SPRITE));
    snek->x = 1200;
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
    snek->health = 200;
    snek->alive = 1;
    //Load fat enemies
    temp = load_bitmap("images/tradition_bg/fat.bmp", NULL);
    for (n=0; n<24; n++){
		fat_image[n] = grabFrame(temp,88,85,0,0,4,n);
    }
    destroy_bitmap(temp);
	for(n=0;n<FATS;n++){
		fat[n] = malloc(sizeof(SPRITE));
	    fat[n]->x = 1250 + (500*n);
	    fat[n]->y = 125;
	    fat[n]->width = fat_image[0]->w;
	    fat[n]->height = fat_image[0]->h;
	    fat[n]->xdelay = 1;
	    fat[n]->ydelay = 0;
	    fat[n]->xcount = 0;
	    fat[n]->ycount = 0;
	    fat[n]->xspeed = -2;
	    fat[n]->yspeed = 0;
	    fat[n]->curframe = 0;
	    fat[n]->maxframe = 19;
	    fat[n]->framecount = 0;
	    fat[n]->framedelay = 4;
	    fat[n]->animdir = 1;
	    fat[n]->startFrame = 0;
	    fat[n]->health = 100;
	    fat[n]->alive = 1;
	}
	//Load music
	sounds[HISS] = load_sample("sounds/hiss.wav");
    sounds[AM_ANTH] = load_sample("sounds/amer_anth.wav");
    sounds[MURICA] = load_sample("sounds/prime.wav");
    sounds[BURP] = load_sample("sounds/burp.wav");
	//play music
	play_sample(sounds[AM_ANTH], volume-50, pan, pitch, TRUE);
}
/*Loads the equality map*/
void loadEquality(){
	//load dragon character sprite
    temp = load_bitmap("images/equality_bg/dragon.bmp", NULL);
    for (n=0; n<12; n++){
		drag_image[n] = grabFrame(temp,575,264,0,0,6,n);
    }
    destroy_bitmap(temp);		
    drag = malloc(sizeof(SPRITE));
    drag->x = 3500;
    drag->y = 0;
    drag->width = drag_image[0]->w;
    drag->height = drag_image[0]->h;
    drag->xdelay = 1;
    drag->ydelay = 0;
    drag->xcount = 0;
    drag->ycount = 0;
    drag->xspeed = 0;
    drag->yspeed = 0;
    drag->curframe = 0;
    drag->maxframe = 5;
    drag->framecount = 0;
    drag->framedelay = 12;
    drag->animdir = 1;
    drag->startFrame = 0;
    drag->health = 300;
    drag->alive = 1;
	//Load commie enemies
    temp = load_bitmap("images/equality_bg/commie.bmp", NULL);
    for (n=0; n<14; n++){
		commie_image[n] = grabFrame(temp,45,59,0,0,9,n);
    }
    destroy_bitmap(temp);
	for(n=0;n<COMMIES;n++){
		commie[n] = malloc(sizeof(SPRITE));
	    commie[n]->x = 550 + (500*n);
	    commie[n]->y = 350;
	    commie[n]->width = commie_image[0]->w;
	    commie[n]->height = commie_image[0]->h;
	    commie[n]->xdelay = 1;
	    commie[n]->ydelay = 0;
	    commie[n]->xcount = 0;
	    commie[n]->ycount = 0;
	    commie[n]->xspeed = -2;
	    commie[n]->yspeed = 0;
	    commie[n]->curframe = 0;
	    commie[n]->maxframe = 8;
	    commie[n]->framecount = 0;
	    commie[n]->framedelay = 4;
	    commie[n]->animdir = 1;
	    commie[n]->dir = n*NUMPROJ;//Keep track of projectiles
	    commie[n]->cnt = 0;
	    commie[n]->startFrame = 0;
	    commie[n]->health = 100;
	    commie[n]->alive = 1;
	    //create their bullets
	    temp = load_bitmap("images/equality_bg/star.bmp", NULL);
	    star_image = grabFrame(temp,8,8,0,0,1,0);
	    destroy_bitmap(temp);		
	    for(j=n*NUMPROJ;j<(n+1)*NUMPROJ;j++){
			star[j] = malloc(sizeof(SPRITE));
		    star[j]->x = 3900;
		    star[j]->y = 600;
		    star[j]->width = star_image->w;
		    star[j]->height = star_image->h;
		    star[j]->xdelay = 1;
		    star[j]->ydelay = 0;
		    star[j]->xcount = 0;
		    star[j]->ycount = 0;
		    star[j]->xspeed = 0;
		    star[j]->yspeed = 0;
		    star[j]->curframe = 0;
		    star[j]->maxframe = 0;
		    star[j]->framecount = 0;
		    star[j]->framedelay = 12;
		    star[j]->animdir = 0;
		    star[j]->startFrame = 0;
		    star[j]->alive = 1;
		}
	}
	//Load sounds
	sounds[USSR_ANTH_R] = load_sample("sounds/ussr_anth_r.wav");
	//sounds[USSR_ANTH] = load_sample("sounds/ussr_anth.wav");//Removed due to corrupt wav file, above one works well anyhow as replacement
	sounds[PING] = load_sample("sounds/ping.wav");
	//play music
	play_sample(sounds[USSR_ANTH_R], volume-50, pan, pitch, TRUE);
}
/*Loads the sprites into their struct from their bitmap files*/
void loadLevel(char * map){
	//Reset in case not first level loaded
	facing = 0, music=0, jump = JUMPIT, s = 0, f = 0, p = 0, firetime = -1, player_anim = 0, pa_start = 0, pa_end = 0;
	fired = 0, cur_proj = 0;
	//load the map
	if(MapLoad(map)){
		printf("Error Loading Map Code: %d", n);
		exit(1);
	}
	//Load in sounds for all levels
    sounds[OH_YEAH] = load_sample("sounds/male_oh_yeah.wav");
    sounds[BLEEP] = load_sample("sounds/beep.wav");
    sounds[SQUIRT] = load_sample("sounds/squirt.wav");
    sounds[SLUSH] = load_sample("sounds/slush.wav");
    sounds[LASER] = load_sample("sounds/laser.wav");
    
	//Eventually if more levels are built, add a parameter to pass the value for this
	switch(mapName){
		case TRADITION: loadTradition();
		break;
		case EQUALITY: loadEquality();
		break;
	}
	//load vlad playable character sprite
    temp = load_bitmap("images/leo.bmp", NULL);
    for (n=0; n<40; n++){
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
	    proj_paint[n]->x = 3900;
	    proj_paint[n]->y = 600;
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
/*Collision function for with blocks*/
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
/*Check collisions for enemy with attack (Prime is enabled but melee is really only for fats)*/
void checkMelee(int x1, int x2, int y1, int y2){
	j=0;
	SPRITE *t = malloc(sizeof(SPRITE));
	tempSprite->x = x1;
    tempSprite->y = y1;
    tempSprite->width = x2 - x1;
    tempSprite->height = y1 - y2;
	switch(mapName){
		case TRADITION:			
		    /*Prime*/
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
		    	play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
				prime->health -= 25;
		    	if(prime->health <= 0){
		    		prime->alive = 0;
				}else{
					prime->y-=15;//Bounce when hit to let player know damage is dealt
				}
			}
			/*Fat*/
			for(j=0;j<FATS;j++){
			    if(collide(tempSprite, fat[j], 15)){
			    	play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
					fat[j]->health -= 25;
			    	if(fat[j]->health <= 0){
			    		fat[j]->alive = 0;
					}else{
						fat[j]->y-=15;//Bounce when hit to let player know damage is dealt
					}
				}
			}
			break;
	}
	free(t);
}
/*Check for any collision with the maps given enemies and the projectiles*/
void checkFire(SPRITE *spr){
	j=0;
	/*Stop projectile when collides with wall/platform*/
	if(collided(spr->x,spr->y+spr->height/2) && spr->xspeed < 0){//moving left
		spr->y = 600;
		spr->x = 3900;
		spr->xspeed=0;
		play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
	}else if(collided(spr->x+60,spr->y+spr->height/2) && spr->xspeed > 0){//moving right
		spr->y = 600;
		spr->x = 3900;
		spr->xspeed=0;
		play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
	}else if(collided(spr->x + spr->width/2, spr->y + spr->height) && spr->xspeed!=0){
    	spr->y = 600;
		spr->x = 3900;
		spr->xspeed=0;
		play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
	}else{
		/*Switch on what map playing to see what enemies there are for updating*/
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
			    	play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
					prime->health -= 25;
			    	if(prime->health <= 0){
			    		prime->alive = 0;
					}else{
						prime->y-=15;//Bounce when hit to let player know damage is dealt
					}
					spr->y = 600;
					spr->x = 3900;//Get rid of shot so it doesnt hit more than once
				}
				j=0;
				/*Snek*/
				j = collide(spr, snek, 10);
			    if(j && snek->alive){//Check if collided
			    	snek->health -= 25;
			    	if(snek->health <= 0){
			    		snek->alive = 0;
					}else{
						snek->y-=25;//Bounce when hit to let player know damage is dealt
					}
					spr->y = 600;
					spr->x = 3900;//Get rid of shot so it doesnt hit more than once
				}
				j=0;
				break;
			case EQUALITY:
				/*DRAGON*/
				j=0;
				//See if hit box is for front or back
				if(player->x < drag->x && drag->xspeed >0){//player on left side and drag walking to right
					j = collide(spr, drag, 10);
				}else if(player->x < drag->x && drag->xspeed <0){//Player on left side and drag walking left
					tempSprite->x = drag->x+(drag->width/2);
				    tempSprite->y = drag->y;
				    tempSprite->width = drag->width/2;
				    tempSprite->height = drag->height;
					j = collide(spr, tempSprite, 10);
				}else if(player->x > drag->x && drag->xspeed >0){//Player on right side and drag walking right
					tempSprite->x = drag->x;
				    tempSprite->y = drag->y;
				    tempSprite->width = drag->width/2;
				    tempSprite->height = drag->height;
					j = collide(spr, tempSprite, 10);
				}else if(player->x > drag->x && drag->xspeed <0){//Player on right side and drag walkiing left
					j = collide(spr, drag, 10);
				}
			    if(j){//Check if collided
			    	play_sample(sounds[SLUSH], volume, pan, pitch, FALSE);
					drag->health -= 25;
			    	if(drag->health <= 0){
			    		drag->alive = 0;
					}else{
						drag->y-=15;//Bounce when hit to let player know damage is dealt
					}
					spr->y = 600;
					spr->x = 3900;//Get rid of shot so it doesnt hit more than once
				}
				j=0;
				/*Commies*/
				for(i=0;i<COMMIES;i++){
					j = collide(spr, commie[i], 5);
				    if(j && commie[i]->alive){//Check if collided
				    	commie[i]->health -= 10;
				    	if(commie[i]->health <= 0){
				    		commie[i]->alive = 0;
						}else{
							commie[i]->y-=25;//Bounce when hit to let player know damage is dealt
						}
						spr->y = 600;
						spr->x = 3900;//Get rid of shot so it doesnt hit more than once
					}
					j=0;
				}			
			break;
		}
	}
}
/*Pauses the current game session with options to return to menu*/
void pauseGame(){
	//Blit the info screen
	if(mapName == TRADITION){
		blit(pause_1,screen,0,0,WIDTH/2-200,HEIGHT/2-200,400,400);//add image to screen
	}else if(mapName == EQUALITY){
		blit(pause_2,screen,0,0,WIDTH/2-200,HEIGHT/2-200,400,400);//add image to screen
	}else{
		return;//Level not found
	}	
	release_screen();
	paused=0;
	while(!paused){
		rest(250);//add delay so that it doesn't pause and unpause from keyboard input stream (I wish the API had a KEY_UP setting)
		if (key[KEY_P] || key[KEY_H]){//checks for P/H press
	        if(key_shifts & KB_CTRL_FLAG){//checks if ctrl is held too
				paused=1;
			}
		}
	}
}
/*Input handling function, checks pressed key to see what action to take depending on set flags at time*/
void getInput(){
	//Check for quit game
	if(key[KEY_ESC]){
		gameOn = 1;
		switch(mapName){
			case TRADITION:
				stop_sample(sounds[AM_ANTH]);
				stop_sample(sounds[MURICA]);//Could be playing so better safe than sorry
				break;
			case EQUALITY:
				stop_sample(sounds[USSR_ANTH_R]);//Could be playing so better safe than sorry
				break;
		}
	}else if (key[KEY_M]){//checks for M press
        if(key_shifts & KB_CTRL_FLAG){//checks if ctrl is held too
			if(!music){//music is on so turn off
	        	music = 1; //mute
	        	if(mapName == TRADITION){
	        		stop_sample(sounds[AM_ANTH]);
				}else if(mapName == EQUALITY){
					stop_sample(sounds[USSR_ANTH_R]);
				}
			}else{//music off so turn on
				music = 0; //unmute
		    	if(mapName == TRADITION){
	        		play_sample(sounds[AM_ANTH], volume-50, pan, pitch, TRUE);
				}else if(mapName == EQUALITY){
					play_sample(sounds[USSR_ANTH_R], volume-50, pan, pitch, TRUE);
				}
			}
			rest(250);//add delay so that it doesn't turn music on and off
		}
	}
	if(player->health<=0){//don't allow for control when player dead
		return;
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
			play_sample(sounds[SQUIRT], volume, pan, pitch, FALSE);
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
			if(facing == 0){//melee left
				checkMelee(player->x-60, player->x, player->y - 10, player->y - 60);
			}else{//melee right
				checkMelee(player->x+player->width, player->x+player->width+60, player->y - 10, player->y - 60);
			}
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
    }else if (key[KEY_P] || key[KEY_H]){//checks for P/H press
        if(key_shifts & KB_CTRL_FLAG){//checks if ctrl is held too
			pauseGame();
			rest(250);//add delay so that it doesn't pause and unpause from keyboard input stream (I wish the API had a KEY_UP setting)
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
/*Checks which way a sprite shouldbe displayed and then displays it*/
void testDrawSide(SPRITE *spr, BITMAP *bm[]){
	if(spr->xspeed<0){//See what direction moving
		draw_sprite_h_flip(buffer, bm[spr->curframe], (spr->x-mapxoff), (spr->y-mapyoff+1));
	}else{
		
		draw_sprite(buffer, bm[spr->curframe], (spr->x-mapxoff), (spr->y-mapyoff+1));
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
			testDrawSide(prime, prime_image);
			if(player->x<snek->x+snek->width/2){//See what direction player is relative to us so we always face them
				draw_sprite_h_flip(buffer, snek_image[snek->curframe], (snek->x-mapxoff), (snek->y-mapyoff+1));
			}else{
				
				draw_sprite(buffer, snek_image[snek->curframe], (snek->x-mapxoff), (snek->y-mapyoff+1));
			}		
			for(j=0;j<FATS;j++){
				testDrawSide(fat[j], fat_image);
			}		
			break;
		case EQUALITY:
			if(drag->xspeed>0){//See what direction moving
				draw_sprite_h_flip(buffer, drag_image[drag->curframe], (drag->x-mapxoff), (drag->y-mapyoff+1));
			}else{				
				draw_sprite(buffer, drag_image[drag->curframe], (drag->x-mapxoff), (drag->y-mapyoff+1));
			}
			for(j=0;j<COMMIES;j++){
				testDrawSide(commie[j], commie_image);
			}
			for(j=0;j<COMMIES*NUMPROJ;j++){
				draw_sprite(buffer, star_image, (star[j]->x-mapxoff), (star[j]->y-mapyoff+1));
			}
			break;			
	}
}
/*Adds gravity to sprite, stopping when colliding with blocks*/
void gravity(SPRITE *spr){
	if(!collided(spr->x + spr->width/2, spr->y + spr->height)){
    	spr->yspeed=1; 
	}else{
		spr->yspeed=0;					
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
					play_sample(sounds[LASER], volume, pan, pitch, FALSE);
					if(prime->xspeed > 0 && player->x > prime->x){//bounce player back to right
						player->x += 30;
					}else if(prime->xspeed > 0 && player->x < prime->x){//bounce player back to left
						player->x -= 30;
					}else if(prime->xspeed < 0 && player->x < prime->x){//bounce player back to left
						player->x -= 30;
					}else{//bounce player back to left
						player->x += 30;
					}
				}
				if(player->x>3150 && p!=1){
					prime->xspeed = -(PLAYERSPEED);
					p=1;					
					play_sample(sounds[MURICA], volume+164, pan, pitch, FALSE);
				}
				if(prime->x<10){//prevents game crash from prime running off screen
					prime->xspeed=2;
				}else if(prime->x> 3700){
					prime->xspeed=-2;
				}
				gravity(prime);
				updateSprite(prime);
			}else if(prime->xspeed!=0){
				prime->xspeed=0;
				stop_sample(sounds[AM_ANTH]);
				play_sample(sounds[AM_ANTH], volume+50, pan, pitch-500, FALSE);
			}else{//must be on last frame so just stay on it
				stop_sample(sounds[MURICA]);				
			}	
			/*Handle Snek enemy*/
			if(snek->curframe != 11){//Last frame after dead, stay on it when dead
				if(!snek->alive){//He's dead so play the death animation
					playAnim(snek, 8, 11);
				}else if(collide(player, snek, 10)){
					player->health-=10;//player lose health
					if(snek->xspeed > 0 && player->x > snek->x){//bounce player back to right
						player->x += 20;
					}else if(snek->xspeed > 0 && player->x < snek->x){//bounce player back to left
						player->x -= 20;
					}else if(snek->xspeed < 0 && player->x < snek->x){//bounce player back to left
						player->x -= 20;
					}else{//bounce player back to left
						player->x += 20;
					}
					playAnim(snek, 4, 7);
					stop_sample(sounds[HISS]);
					play_sample(sounds[HISS], volume, pan, pitch, FALSE);
				}else if(player->x+player->width > snek->x-20 && player->x+player->width< snek->x+2){//stop player from passing through snake from left side
					playAnim(snek, 4, 7);
					s=4;
				}else if(player->x > snek->x+snek->width && player->x< snek->x+snek->width+20){//stop player from passing through snake from left side
					playAnim(snek, 4, 7);
					s=4;
				}else if(s != 0){
					s--;
					playAnim(snek, 4, 7);
				}else{
					playAnim(snek, 0, 3);
				}
				if(snek->x>1450){
					snek->xspeed=-2;
				}else if(snek->x<850){
					snek->xspeed=2;
				}
				gravity(snek);			
				updateSprite(snek);
			}else{//must be on last frame so just stay on it
				snek->xspeed=0;
			}	
			/*Fats*/
			for(j=0;j<FATS;j++){
				if(fat[j]->curframe != 23){//Last frame after dead, stay on it when dead					
					if(!fat[j]->alive){//He's dead so play the death animation
						playAnim(fat[j], 20, 23);
					}else if(collide(fat[j], player,  10) && f <=0){
						f=10;
						fat[j]->xspeed=-fat[j]->xspeed;
						stop_sample(sounds[BURP]);
						play_sample(sounds[BURP], volume, pan, pitch, FALSE);
						player->health-=10;//player lose health
						if(fat[j]->xspeed > 0 && player->x > fat[j]->x){//bounce player back to right
							player->x += 20;
						}else if(fat[j]->xspeed > 0 && player->x < fat[j]->x){//bounce player back to left
							player->x -= 20;
						}else if(fat[j]->xspeed < 0 && player->x < fat[j]->x){//bounce player back to left
							player->x -= 20;
						}else{//bounce player back to left
							player->x += 20;
						}
					}else{
						playAnim(fat[j], 0, 19);
						f--;
					}
					if(fat[j]->x>1350 + (500*j)){
						fat[j]->xspeed=-2;
					}else if(fat[j]->x<1150 + (500*j)){
						fat[j]->xspeed=2;
					}
					gravity(fat[j]);			
					updateSprite(fat[j]);
				}else{//must be on last frame so just stay on it
					fat[j]->xspeed=0;
				}
			}			
			break;
		case EQUALITY:
			/*Commies*/
			for(j=0;j<COMMIES;j++){
				if(commie[j]->curframe != 13){//Last frame after dead, stay on it when dead					
					if(!commie[j]->alive){//He's dead so play the death animation
						playAnim(commie[j], 9, 13);
					}else if(collide(commie[j], player,  10) && f <=0){
						f=10;
						commie[j]->xspeed=-commie[j]->xspeed;
						play_sample(sounds[BLEEP], volume, pan, pitch, FALSE);
						player->health-=10;//player lose health
						if(commie[j]->xspeed > 0 && player->x > commie[j]->x){//bounce player back to right
							player->x += 20;
						}else if(commie[j]->xspeed > 0 && player->x < commie[j]->x){//bounce player back to left
							player->x -= 20;
						}else if(commie[j]->xspeed < 0 && player->x < commie[j]->x){//bounce player back to left
							player->x -= 20;
						}else{//bounce player back to left
							player->x += 20;
						}
					}else{//no collision just keep animating and try to fire
						if(commie[j]->cnt >60){//Check if enough frames gone by to fire
							commie[j]->cnt=0;
							if(commie[j]->dir>=(j*NUMPROJ+NUMPROJ)){//Reset projectile list to restart using projectiles from bottom
								commie[j]->dir=j*NUMPROJ;
							}
							//Fire current dir
							if(commie[j]->xspeed > 0){//moving right so fire right
								star[commie[j]->dir]->x=commie[j]->x+commie[j]->width;
								star[commie[j]->dir]->xspeed=3;
							}else{//moving left fire left
								star[commie[j]->dir]->x=commie[j]->x;
								star[commie[j]->dir]->xspeed=-3;
							}
							star[commie[j]->dir]->y=commie[j]->y;
							commie[j]->dir++;
						}else{
							commie[j]->cnt++;
						}
						playAnim(commie[j], 0, 8);
						f--;
					}
					if(commie[j]->x>700 + (500*j)){
						commie[j]->xspeed=-2;
					}else if(commie[j]->x<500 + (500*j)){
						commie[j]->xspeed=2;
					}
					gravity(commie[j]);			
					updateSprite(commie[j]);
				}else{//must be on last frame so just stay on it
					commie[j]->xspeed=0;
				}
			}	
			/*Now just to Update the bullets*/
			for(n=0;n<NUMPROJ*COMMIES;n++){//Update the enemy projectiles
				updateSprite(star[n]);
				/*Stop projectile when collides with wall/platform*/
				if(collided(star[n]->x,star[n]->y+star[n]->height/2) && star[n]->xspeed < 0){//moving left
					star[n]->y = 600;
					star[n]->x = 3900;
					star[n]->xspeed=0;
				}else if(collided(star[n]->x+60,star[n]->y+star[n]->height/2) && star[n]->xspeed > 0){//moving right
					star[n]->y = 600;
					star[n]->x = 3900;
					star[n]->xspeed=0;
				}else if(collide(star[n], player, 25)){
					star[n]->y = 600;
					star[n]->x = 3900;
					star[n]->xspeed=0;
					player->health-=10;
					play_sample(sounds[PING], volume, pan, pitch, FALSE);
				}
			}
			/*Dragon*/
			if(drag->curframe != 11){//Last frame after dead, stay on it when dead
				if(!drag->alive){//He's dead so play the death animation
					playAnim(drag, 6, 11);
				}else if(collide(player, drag, 10)){
					player->health-=10;//player lose health
					//play_sample(sounds[LASER], volume, pan, pitch, FALSE);
					if(drag->xspeed > 0 && player->x > drag->x){//bounce player back to right
						player->x += 30;
					}else if(drag->xspeed > 0 && player->x < drag->x){//bounce player back to left
						player->x -= 30;
					}else if(drag->xspeed < 0 && player->x < drag->x){//bounce player back to left
						player->x -= 30;
					}else{//bounce player back to left
						player->x += 30;
					}
				}
				if(player->x>3150 && p!=1){
					drag->xspeed = -(PLAYERSPEED);
					p=1;					
					stop_sample(sounds[USSR_ANTH_R]);
					play_sample(sounds[USSR_ANTH_R], volume+64, pan, pitch, FALSE);
				}
				if(drag->x<10){//prevents game crash from drag running off screen
					drag->xspeed=2;
				}else if(drag->x> 3700){
					drag->xspeed=-2;
				}
				gravity(drag);
				updateSprite(drag);
			}else if(drag->xspeed!=0){
				drag->xspeed=0;
				stop_sample(sounds[USSR_ANTH_R]);
				play_sample(sounds[USSR_ANTH_R], volume+50, pan, pitch-500, FALSE);
			}	
			break;
	}
}
/*Ends the current game seesion with options to return to menu*/
void endGame(){
	//Play death animation
	if(mapName == TRADITION && player->curframe != 35){//check hasn't finished animation
		playAnim(player,32,35);
	}else if(mapName == EQUALITY && player->curframe != 39){
		playAnim(player,36,39);
	}else{//Dead now, prompt for decision
		//Blit the info screen
		blit(lose,screen,0,0,WIDTH/2-128,HEIGHT/2-128,256,256);//add image to screen
		release_screen();
		while(!quit){			
			//Check for quit game
			if(key[KEY_ESC]){
				quit = 1;
			}
		}
	}
}
/*Ends game but for a winning scenario*/
void winGame(){
	play_sample(sounds[OH_YEAH], volume, pan, pitch+100, FALSE);//play game win sound effect
	if(mapName == TRADITION){
		blit(victory_trad,screen,0,0,0,0,640,480);//add image to screen
	}else if(mapName == EQUALITY){
		blit(victory_equal,screen,0,0,0,0,640,480);//add image to screen
	}else{
		return;
	}	
	release_screen();
	while(!gameOn){			
		//Check for quit game
		if(key[KEY_ESC]){
			gameOn = 1;
			switch(mapName){
				case TRADITION:
					stop_sample(sounds[AM_ANTH]);
					stop_sample(sounds[MURICA]);//Could be playing so better safe than sorry
					break;
				case EQUALITY:
					stop_sample(sounds[USSR_ANTH_R]);//Could be playing so better safe than sorry
					break;
			}
		}
	}
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
	//printf(".1-2");
	for(n=0;n<NUMPROJ;n++){//Update the player projectiles
		gravity(proj_paint[n]);
		updateSprite(proj_paint[n]);
		//printf(".1-3");
		checkFire(proj_paint[n]);//Check for collisions with enemies
	}	
	//printf(".2");
	handleEnemies();//Update enemies
	//printf(".2-1");
	if(player->curframe == pa_end){//Turn off animation that finished
		player_anim = 0;
		player->animdir=0;
	}	
	//printf(".3");	
    updateMap();
    drawSprites();
    //printf(".4");
    /*Prevent player from walking through walls, need to hit top and bottom of player so can still walk through platforms*/
    if(collided(player->x + player->width/2, player->y + player->height) && collided(player->x + player->width/2, player->y + player->height/2)){//right side hit wall and trying to move through it
    	if(player->xspeed > 0){//right side hit wall and trying to move through it
    	player->x -= PLAYERSPEED;
    	player->xspeed = 0;
		}else if(player->xspeed < 0){//left side hit wall and trying to move through it
	    	player->x += PLAYERSPEED;
	    	player->xspeed = 0;
		}
	}
	//Check player is alive
	if(player->health <= 0){
		endGame();
	}
	if(player->x>3800){
		winGame();
	}
    //blit the double buffer 
	vsync();
	//printf(".5");
    acquire_screen();
    //printf(".6");
	blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
	blit(bar,screen,0,0,0,HEIGHT-48,640,48);//add bottom bar to screen
	textprintf_centre_ex(screen,font,320,HEIGHT-24,TEXTCOLOUR,-1,"HEALTH: %d", player->health);
	//write info to bar
	//printf(".7");
    release_screen();
}
/*Loop used during title screen, handles selection/progression to gameloop or exiting application*/
void titleLoop(){
	while(!quit){
		//Bring up title screen
		blit(title,screen,0,0,0,0,640,480);		
		play_sample(sounds[MUSIC], volume, pan, pitch, FALSE);
		//Wait for input
		while(!gameOn){//Run game loop
			while(!selected){//Run title loop
				if(key[KEY_ESC]){
					quit = 1;//this will exit all loops
					selected=1;
					gameOn=1;
				}else if(key[KEY_1]){
					mapName=TRADITION;
					loadLevel("images/tradition_bg/map.FMP");
					printf(".LOADED_TRADITION");					
					stop_sample(sounds[MUSIC]);//stop title music so it doesnt interfere with level theme
					selected=1;//just break this loop to start gameloop
				}else if(key[KEY_2]){
					mapName=EQUALITY;
					loadLevel("images/equality_bg/equality.FMP");
					printf(".LOADED_EQUALITY");					
					stop_sample(sounds[MUSIC]);//stop title music so it doesnt interfere with level theme
					selected=1;//just break this loop to start gameloop
				}
			}
			gameLoop();//Plays the game
		}//Reset
		selected=0;
		gameOn=0;
		rest(100);//wait a bit so escape isn't auto exiting entire game	
	}
}
/*Main function, handles initial loading. Passes on taks to be handled in title/game loop functions. When quit, destroys allocated memory.*/
int main(void){
    facing = 0, jump = JUMPIT, music = 0, s = 0, f = 0, p = 0, quit = 0, firetime = -1, player_anim = 0, pa_start = 0, pa_end = 0;
	fired = 0, cur_proj = 0, gameOn = 0, selected = 0;
	tempSprite = malloc(sizeof(SPRITE));
	allegro_init();	
	install_timer();
	install_keyboard();
	set_color_depth(16);
	lose = load_bitmap("images/gameover.bmp", NULL);//Load gameover screen
	pause_1 = load_bitmap("images/tradition_bg/pause_trad.bmp", NULL);//Load game paused screen
	pause_2 = load_bitmap("images/equality_bg/pause_equal.bmp", NULL);//Load game paused screen
	bar = load_bitmap("images/bottom_bar.bmp", NULL);//Load bottom screen bar
	victory_trad = load_bitmap("images/tradition_bg/tradition_win.bmp", NULL);//Load victory screen
	victory_equal = load_bitmap("images/equality_bg/equality_win.bmp", NULL);//Load victory screen
	title = load_bitmap("images/title_screen.bmp", NULL);//Load title screen
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
    //load sound
    sounds[MUSIC] = load_sample("sounds/title_music.wav");
	printf(".LOADING");
    //create the double buffer
	buffer = create_bitmap(WIDTH, HEIGHT);
	clear(buffer);
    //master loop
	while(!quit){		
		titleLoop();//Plays the game
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
