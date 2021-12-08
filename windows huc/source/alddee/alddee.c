/*
 * Alddee
 *
 * I hacked this together this in about a day. What's so cool about it is that
 * its design, visuals, and name, all come from a dream. I had spent the previous
 * evening thinking about what game to make next, but I couldn't come up with anything
 * 
 * Then I went to bed and in my dream, I was approaching something resembling an
 * arcade machine. The name "Alddee" was written somewhere, and I started playing it.
 * After I woke up, I tried remembering exactly what it looked like, and I transcribed
 * it on a sheet of paper as soon as I could.
 *
 * It's not really a complete game, but that's the point. It didn't make sense in my
 * dream, so that's how I'm making it here.
 *
 *  If you have any questions regarding the code, contact me
 *  via the method specified at  http://www.sebastianmihai.com
 *  (operational in 2012), and I will try my best to help.
 *
 *                             Sebastian Mihai, 2012
 *
*/
#define BACKGROUND_FILE "graphics\\background.pcx"
#define GAMEOVER_FILE "graphics\\gameover.pcx"

#include "huc.h"

/*Screen resolution is 256x224*/
#define         TILE_PLAYERFRAME0        0x7000
#define         TILE_PLAYERFRAME1        0x7100
#define         PEG    0x7200
#define			SPIKY 0x7300
#define			TILE_PLAYERATTACKINGFRAME 0x7400
#define			TILE_WEAPON 0x7500

#define         INIT_X    20
#define         INIT_Y    90
#define			LEVEL_2_ENEMY_X 200
#define			LEVEL_2_ENEMY_Y 25
#define			SPIKY_RADIUS 20

#define SPR_PEG1 2
#define SPR_PEG2 3
#define SPR_PEG3 4

#define SPR_SPIKY1 5
#define SPR_SPIKY2 6
#define SPR_SPIKY3 7

#define SPR_WEAPON 8

int level1BarrierDestroyed;

int spikyX[8], spikyY[8];

initialize()
{
	/* load files into memory */
	load_sprites(TILE_PLAYERFRAME0, playerframe0, 1);
	load_sprites(TILE_PLAYERFRAME1, playerframe1, 1);
	load_sprites(PEG, peg, 1);
	load_sprites(SPIKY, spiky, 1);
	load_sprites(TILE_PLAYERATTACKINGFRAME, playerattackingframe, 1);
	load_sprites(TILE_WEAPON, weapon, 1);

	init_satb();

	load_background(special_bg, special_pal, special_bat, 32, 28);
	
	vsync(1);
	
	/* LOAD PALETTES - they are later accessed by their index (0, 1, 2 ... ) */
	set_sprpal(0, playerframe0_pal);
	set_sprpal(1, playerframe1_pal);
	set_sprpal(2, peg_colors);
	set_sprpal(3, special_pal);
	set_sprpal(4, spiky_pal);
	set_sprpal(5, weapon_pal);

	/* set up spiky peg rotation coordinate arrays */
	spikyX[0] = -SPIKY_RADIUS;
	spikyX[1] = -SPIKY_RADIUS*2/3;
	spikyX[2] = 0;
	spikyX[3] = SPIKY_RADIUS*2/3;
	spikyX[4] = SPIKY_RADIUS;
	spikyX[5] = SPIKY_RADIUS*2/3;
	spikyX[6] = 0;
	spikyX[7] = -SPIKY_RADIUS*2/3;
	
	spikyY[0] = 0;
	spikyY[1] = -SPIKY_RADIUS*2/3;
	spikyY[2] = -SPIKY_RADIUS;
	spikyY[3] = -SPIKY_RADIUS*2/3;
	spikyY[4] = 0;
	spikyY[5] = SPIKY_RADIUS*2/3;
	spikyY[6] = SPIKY_RADIUS;
	spikyY[7] = SPIKY_RADIUS*2/3;
	
	/* 3 pegs - they use hardware sprites SPR_PEG1, SPR_PEG2, and SPR_PEG3 */
	spr_set(SPR_PEG1);
	spr_x(135);
	spr_y(65);
	spr_pattern(PEG);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pal(2);
	spr_pri(1);
	
	spr_set(SPR_PEG2);
	spr_x(135);
	spr_y(105);
	spr_pattern(PEG);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pal(2);
	spr_pri(1);
	
	spr_set(SPR_PEG3);
	spr_x(135);
	spr_y(145);
	spr_pattern(PEG);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
	spr_pal(2);
	spr_pri(1);
	
	/* 3 spiky balls */
	spr_set(SPR_SPIKY1);
	spr_x(140);
	spr_y(145);
	spr_pattern(SPIKY);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
	spr_pal(4);
	spr_pri(1);
	
	spr_set(SPR_SPIKY2);
	spr_x(140);
	spr_y(105);
	spr_pattern(SPIKY);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
	spr_pal(4);
	spr_pri(1);
	
	spr_set(SPR_SPIKY3);
	spr_x(140);
	spr_y(65);
	spr_pattern(SPIKY);
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
	spr_pal(4);
	spr_pri(1);
}

/* Move sprite offscreen */
hide_sprite( sprite)
int sprite;
{
	spr_set( sprite );
	spr_x( 260 );
	spr_y( 230 );
}

/* Rotate the three spiky balls */
animate_spiky( currentFrame )
int currentFrame;
{
	int index;
	
	index = (currentFrame%32)/4;
	spr_set(SPR_SPIKY1);
	spr_x( 135 - 12 + spikyX[index] );
	spr_y( 65 - 12 + spikyY[index] );
	spr_set(SPR_SPIKY2);
	spr_x( 135 - 12 + spikyX[index] );
	spr_y( 105 - 12 + spikyY[index] );
	spr_set(SPR_SPIKY3);
	spr_x( 135 - 12 + spikyX[index] );
	spr_y( 145 - 12 + spikyY[index] );
}

/* modify player sprite (0) to animate and move player around */
animate_player( currentFrame, playerX, playerY, attacking ) 
int currentFrame, playerX, playerY, attacking;
{
	spr_set(0);
	spr_x( playerX );
	spr_y( playerY );
	if( attacking == 0 ) {
		if( currentFrame % 30 < 15 )
			spr_pattern(TILE_PLAYERFRAME0);
		else
			spr_pattern(TILE_PLAYERFRAME1);
	} else {
		spr_pattern( TILE_PLAYERATTACKINGFRAME );
	}
	
	spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
	spr_pal(0);
	spr_pri(1);
}

/* Animate the ghostly enemy who looks like the player */
animate_enemy( currentFrame, enemyX, enemyY )
int currentFrame,enemyX,enemyY;
{
	 spr_set(1);
	 spr_x(enemyX);
	 spr_y( enemyY );
	 if( currentFrame % 30 < 15 )
		spr_pattern(TILE_PLAYERFRAME0);
	 else
		spr_pattern(TILE_PLAYERFRAME1);
	 spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|FLIP_X);
	 spr_pal(3);
	 spr_pri(1);
}

/*
 * 
 * Level 1 - face off against a ghostly enemy 
 * 
 * 
 */
level1()
{
int playerX,playerY,playerAttacking;
int enemyX,enemyY,enemyAlive;
int i;
int currentFrame;

	level1BarrierDestroyed = 0;
	playerX = INIT_X;
	playerY = INIT_Y;
	enemyX = playerX + 200;
	enemyY = playerY;
	
	initialize();
	enemyAlive = 1;
	currentFrame = 0;
	
	for (;;)
	{
		currentFrame++;
		vsync(1);

		/* Check for fire button */
		if (joy(i) & JOY_A) {
			playerAttacking = 1;
			/* has player destroyed the spikys ? */
			if( playerX > 80 && playerX <= 85 ) {
				level1BarrierDestroyed = 1;
			}
			
			/* has player hit the enemy? */
			if( enemyX - playerX < 17 && ( enemyY-playerY < 10 && playerY-enemyY < 10 ) ) {
				hide_sprite( 1 );
				enemyAlive = 0;
			}
		} else {
			playerAttacking = 0;
			
			/* can only move if not attacking */
			if (joy(i) & JOY_UP) {
			if( playerY > 20 )
				playerY--;
			} else if (joy(i) & JOY_DOWN) {
				if( playerY < 153 )
					playerY++;
			}
			
			if (joy(i) & JOY_LEFT && playerX > 0) {
				playerX--;
			} else if (joy(i) & JOY_RGHT && playerX < 225) {
				if( level1BarrierDestroyed == 1 || playerX < 85 )
					/* restrict player once the enemy is active */
					if( playerX < enemyX - 16 || enemyAlive == 0 )
						playerX++;
			}
		}	
	  
		if ( level1BarrierDestroyed == 1 && enemyAlive == 1 ) {
			
			/* Move enemy towards player every other frame */
			if( currentFrame % 2 == 0 ) {
			
				if( enemyY > playerY )
					enemyY--;
				if( enemyY < playerY )
					enemyY++;
				
				if( enemyX - playerX > 16 )					
						enemyX--;
			}
			
		}
	  
		animate_player( currentFrame, playerX, playerY, playerAttacking );
		
		if( enemyAlive == 1 )
			animate_enemy( currentFrame, enemyX, enemyY );
		if( level1BarrierDestroyed == 0 ) {
			animate_spiky( currentFrame );
		} else {
			hide_sprite( SPR_SPIKY1 );
			hide_sprite( SPR_SPIKY2 );
			hide_sprite( SPR_SPIKY3 );
		}

		/* show weapon upgrade */
		if( enemyAlive == 0 ) {
			spr_set(SPR_SPIKY1);
			spr_x( 130 );
			spr_y( 45 );
			spr_pattern( TILE_WEAPON );	
			spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
			spr_pal(5);
			spr_pri(1);
			
			/* end level once player is on top of weapon */
			if( playerX > 110  && playerX < 130 &&
				playerY > 30 && playerY < 50 ) {
					return 0;
				}
		}

        satb_update();

	}
}

/* animate rotating spiky ball at the top right of the screen */
animate_level2_spiky( currentFrame )
int currentFrame;
{
	int index;
	
	index = (currentFrame%32)/4;
	spr_set(SPR_SPIKY1);
	spr_x( LEVEL_2_ENEMY_X + spikyX[index] );
	spr_y( LEVEL_2_ENEMY_Y + spikyY[index] );
}

move_bullet( sprite, x, y )
int sprite,x,y;
{
	spr_set(sprite);
	spr_x( x );
	spr_y( y );
}

/*
 *
 *  Level two 
 *
 *
 */ 
level2()
{

int playerX,playerY,playerAttacking,enemyLife;
int i;
int currentFrame;
int bulletX[2],bulletY[2];
int firstBulletFired;

	firstBulletFired = 0;
	playerX = INIT_X;
	playerY = INIT_Y;
	bulletX[0] = 270;
	bulletY[0] = 0;
	bulletX[1] = LEVEL_2_ENEMY_X+12;
	bulletY[1] = LEVEL_2_ENEMY_Y+12;
	
	initialize();
	currentFrame = 0;
	enemyLife = 30;
	
	load_background(special_bg, special_pal, special_bat, 32, 28);
	vsync(1);
	
	hide_sprite( SPR_SPIKY3 );
	hide_sprite( SPR_PEG1 );
	hide_sprite( SPR_PEG2 );
	hide_sprite( SPR_PEG3 );
	
	spr_set(SPR_SPIKY2);
	spr_x( LEVEL_2_ENEMY_X );
	spr_y( LEVEL_2_ENEMY_Y );
	i=0;
	for (;;)
	{
		currentFrame++;
		vsync(1);

		if (joy(i) & JOY_A && playerX >= LEVEL_2_ENEMY_X - 40 && playerY < 45 ) {
			playerAttacking = 1;
			enemyLife--;
		} else {
			playerAttacking = 0;
			
			/* can only move if not attacking */
			if (joy(i) & JOY_UP) {
			if( playerY > 20 )
				playerY--;
			} else if (joy(i) & JOY_DOWN) {
				if( playerY < 153 )
					playerY++;
			}
			
			if (joy(i) & JOY_LEFT && playerX > 0) {
				playerX--;
			} else if (joy(i) & JOY_RGHT && playerX < LEVEL_2_ENEMY_X - 38) {
						playerX++;
			}
		}
	  
		animate_player( currentFrame, playerX, playerY, playerAttacking );
		
		animate_level2_spiky( currentFrame );
		
		/* Shoot bullets, alternating between bullet 0 and 1 (one is diagonal, one is straight down) */
		if( currentFrame % 140 == 0 ) {
			bulletX[0] = LEVEL_2_ENEMY_X+12;
			bulletY[0] = LEVEL_2_ENEMY_Y+12;
			firstBulletFired = 1;
		}
		
		if( currentFrame % 140 == 70 ) {
			bulletX[1] = LEVEL_2_ENEMY_X + 12;
			bulletY[1] = LEVEL_2_ENEMY_Y + 12;
			firstBulletFired = 1;
		}
		
		if( firstBulletFired == 1) {
			bulletY[0]++;
			bulletX[1]--;
			bulletY[1]++;
			
			move_bullet( SPR_PEG1, bulletX[0], bulletY[0] );
			move_bullet( SPR_PEG2, bulletX[1], bulletY[1] );
		}
		
        satb_update();
		
		if( enemyLife == 0 ) 
			return;
	}
}

gameover()
{
	int i;
	initialize();
	for(i=0;i<9;i++)
		hide_sprite(i);
	satb_update();
	load_background(gameover_bg, gameover_pal, special_bat, 32, 28);
}

main()
{
	char stringspace[256];
	char *author;
	
	author = &stringspace[0];
	author = "Alddee by Sebastian Mihai, 2012. I dreamed the design and name, after an evening of trying to figure out a new game idea to code.";
	
	level1();
	level2();
	gameover();
}
  
/* 
 * the sprite data
 */

#incspr(playerframe0,"graphics\\p0.pcx",0,0,2,2);        /* player frame 0 */
#incpal(playerframe0_pal,"graphics\\p0.pcx",0,1);

#incspr(playerframe1,"graphics\\p1.pcx",0,0,2,2);      /* player frame 1 */
#incpal(playerframe1_pal,"graphics\\p1.pcx",0,1);

#incspr(playerattackingframe,"graphics\\pattacking.pcx",0,0,2,2);      /* player attacking frame */
#incpal(playerattackingframe_pal,"graphics\\pattacking.pcx",0,1);

#incspr(peg,"graphics\\peg.pcx",0,0,1,1);      /* peg */
#incpal(peg_colors,"graphics\\peg.pcx",0,1);

#incspr(weapon,"graphics\\weapon.pcx",0,0,1,1);      /* weapon upgrade */
#incpal(weapon_pal,"graphics\\weapon.pcx",0,1);

#incspr(spiky,"graphics\\spiky.pcx",0,0,2,2); /* rotating spiky ball */
#incpal(spiky_pal,"graphics\\spiky.pcx",0,1);

#incchr(special_bg,BACKGROUND_FILE,32,28); /* background */
#incpal(special_pal,BACKGROUND_FILE);
#incbat(special_bat,BACKGROUND_FILE,0x1000,32,28);

#incchr(gameover_bg,GAMEOVER_FILE,32,28); /* gameover */
#incpal(gameover_pal,GAMEOVER_FILE);
