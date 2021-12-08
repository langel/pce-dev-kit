#define BACKGROUND_FILE "special.pcx"

#include "../huc.h"

#define         RACKET_L        0x7000
#define         RACKET_R        0x7100
#define         BALL    0x7200
#define         DIGITS  0x7280

#define         DELTA     2
#define         INIT_X    118
#define         INIT_Y     86

#define         SCORE_Y   8
#define         SCORE_X1 48
#define         SCORE_X2 98

dispscore(score1, score2)
int score1, score2;
{
        int temp;

	temp = score1 / 10;
	spr_set(5);
	spr_pattern(DIGITS + 0x40 * (score1 - 10 * temp));	
	score1 = temp;

	temp = score1 / 10;
	spr_set(4);
	spr_pattern(DIGITS + 0x40 * (score1 - 10 * temp));	
	score1 = temp;

	temp = score1 / 10;
	spr_set(3);
	spr_pattern(DIGITS + 0x40 * (score1 - 10 * temp));	

	temp = score2 / 10;
	spr_set(8);
	spr_pattern(DIGITS + 0x40 * (score2 - 10 * temp));	
	score2 = temp;

	temp = score2 / 10;
	spr_set(7);
	spr_pattern(DIGITS + 0x40 * (score2 - 10 * temp));	
	score2 = temp;

	temp = score2 / 10;
	spr_set(6);
	spr_pattern(DIGITS + 0x40 * (score2 - 10 * temp));	

}


init_score(spr_low, spr_hi)
int spr_low, spr_hi;
{
        int i;
	for (i=spr_low; i< spr_low+3; i++)
	{
		spr_set(i);
		spr_x(SCORE_X1 + (i-spr_low) * 16);
         		spr_y(SCORE_Y);
		spr_pattern(DIGITS);
		spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		spr_pal(3);
		spr_pri(1);
		
	}

	for ( ;i<= spr_hi; i++)
	{
		spr_set(i);
		spr_x(SCORE_X2 + (i-spr_low) * 16);
         		spr_y(SCORE_Y);
		spr_pattern(DIGITS);
		spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
		spr_pal(3);
		spr_pri(1);
		
	}


}

main()
{

int y[2],ball_x,ball_y;
int i,sx,sy,score1, score2;

  sx = 2;
  sy = 2;

  score1 = 0;
  score2 = 0;

  y[0] = 135;
  y[1] = 135;

  ball_x = INIT_X;
  ball_y = INIT_Y;

        load_sprites(0x7000, racket_left, 1);
        load_sprites(0x7100, racket_right, 1);
        load_sprites(0x7200, ball, 1);
        load_sprites(0x7280, digits, 2);

         init_satb();

         spr_set(0);
         spr_x(1);
         spr_y(y[0]);
         spr_pattern(RACKET_L);
         spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x32|NO_FLIP);
         spr_pal(0);
         spr_pri(1);

         spr_set(1);
         spr_x(244);
         spr_y(y[1]);
         spr_pattern(RACKET_R);
         spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x32|NO_FLIP);
         spr_pal(1);
         spr_pri(1);

        spr_set(2);
        spr_x(118);
        spr_y(86);
        spr_pattern(BALL);
        spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
        spr_pal(2);
        spr_pri(1);

        init_score(3,8);

        load_background(special_bg, special_pal, special_bat, 32, 28);
        
        vsync(1);

        set_sprpal(0, racket_left_colors);
        set_sprpal(1, racket_right_colors);
        set_sprpal(2, ball_colors);
        set_sprpal(3, digits_colors);

	for (;;)
	{
	  vsync(1);


          for (i=0; i<2; i++)
          {
            if (joy(i) & JOY_UP)
             {
              if (y[i]>1)
                y[i]-=DELTA;
             }
            else if (joy(i) & JOY_DOWN)
             {
              if (y[i]<191)
                y[i]+=DELTA;
             }
          }

          if ((ball_x += sx) > 236)
           {
            sx = -sx;
            if ((ball_y<y[1]-4) || (ball_y>y[1]+28)) /* We missed the ball */
	{
		++score1;
              		ball_x = INIT_X;
	}
           }

          if (ball_x < 12)
           {
            sx = -sx;
            if ((ball_y<y[0]-4) || (ball_y>y[0]+28)) /* We missed the ball */
  	{
		++score2;
              		ball_x = INIT_X;
	}
           }

          if ((ball_y += sy) > 215)
            sy = -sy;

          if (ball_y < 1)
            sy = -sy;

          spr_set(0);
          spr_y(y[0]);

          spr_set(1);
          spr_y(y[1]);

          spr_set(2);
          spr_x(ball_x);
          spr_y(ball_y);

          dispscore(score1, score2);

          satb_update();

	}
  }

/* 
 * the sprite data
 */

#incspr(racket_left,"racketleft.pcx",0,0,2,2);        /* racket */

#incpal(racket_left_colors,"racketleft.pcx",0,1);

#incspr(racket_right,"racketright.pcx",0,0,2,2);      /* racket */

#incpal(racket_right_colors,"racketright.pcx",0,1);

#incspr(ball,"ball.pcx",0,0,1,1);      /* ball */

#incpal(ball_colors,"ball.pcx",0,1);

#define DIGITS_FONT_FILE "image2.pcx"

#incspr(digits,DIGITS_FONT_FILE,0,0,1,1);
#incspr(digits1,DIGITS_FONT_FILE,16,0,1,1);
#incspr(digits2,DIGITS_FONT_FILE,32,0,1,1);
#incspr(digits3,DIGITS_FONT_FILE,0,16,1,1);
#incspr(digits4,DIGITS_FONT_FILE,16,16,1,1);
#incspr(digits5,DIGITS_FONT_FILE,32,16,1,1);
#incspr(digits6,DIGITS_FONT_FILE,0,32,1,1);
#incspr(digits7,DIGITS_FONT_FILE,16,32,1,1);
#incspr(digits8,DIGITS_FONT_FILE,32,32,1,1);
#incspr(digits9,DIGITS_FONT_FILE,0,48,1,1);
#incspr(digits10,DIGITS_FONT_FILE,16,48,1,1);
#incspr(digits11,DIGITS_FONT_FILE,32,48,1,1);
#incpal(digits_colors,DIGITS_FONT_FILE,0,1);

#incchr(special_bg,BACKGROUND_FILE,32,28);
#incpal(special_pal,BACKGROUND_FILE);
#incbat(special_bat,BACKGROUND_FILE,0x1000,32,28);

