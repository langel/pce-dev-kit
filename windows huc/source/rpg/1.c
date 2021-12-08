#include "huc.h"

#define LIFEMAX 500
#define TITLEPCX "titletest.pcx"
#define SPRITE "sprite1.pcx"
#define TILES "tiles.pcx"
#define SCREEN "screen.pcx"
#define DEX 30
#define ATK 50
#define DEF 50

char Entry[6];
char NamP1[6];
char DexP1,DexN,AtkP1,AtkN,DefP1,DefN;
int spriteX,spriteY;

strcpy(lhs,rhs)
char* lhs;
char* rhs;
{
  while (*rhs)
    *lhs++=*rhs++;
  *lhs=0;
    
}

/***************************************/
/*        MAIN         PROG            */
/***************************************/

main()
{
char select;

DexP1=50;
AtkP1=70;
DefP1=60;
strcpy(NamP1,"Willy");

while (1)
{
 cls();
 set_font_color(1,2);
 load_default_font();

select=0;

 load_background(titlegfx,titlepal,titlebat,32,28);

 put_string("Start a battle",11,18);
 put_string("Change name",11,20);
 put_string("Begin game",11,22);
 put_char('-',9,18);

 while (!(joytrg(0) & JOY_STRT))
 {
  if ((joytrg(0) & JOY_UP) && (select>0))
    {
     select--;
     put_char(' ',9,20+2*select);
     put_char('-',9,18+2*select);
    }
  if ((joytrg(0) & JOY_DOWN) && (select<2))
    {
     select++;
     put_char(' ',9,16+2*select);
     put_char('-',9,18+2*select);
    }
   vsync(1);
 }

switch (select)
{
  case 0:
    battle(LIFEMAX,ATK,DEF,DEX);
    break;

  case 1:
    strcpy(Entry,"Willy");
    enter();
    strcpy(NamP1,Entry);
    break;

  case 2:
    sprite();
    break;
}

}
}
/****************************************/
battle(Life,AtkN,DefN,DexN)
int Life;
char DexN,DefN,AtkN;
{

int life_player,life_enemi,rnd,rnd2,i,wound,hit;
char turn,continu;

set_font_color(1,2);
load_default_font();

while(1)
 {

  satb_update();
  cls();
  battlescreen();
  life_player=LIFEMAX;
  life_enemi=Life;
  turn=1;
  continu=1;

 
  while ((life_player>0) & (life_enemi>0))
   {
   put_string(NamP1,17,23);
   put_string("ennemi",17,24); 

  /* wait + random */

   put_string("PUSH START",8,16);

   while(!(joytrg(0) & JOY_STRT))
       rand();

   
   vsync(rand() % 3);
   cls();
   battlescreen(); 

   /* results */

   if (turn)
    {
     hit=2*(rand() % DexP1) - (rand() % DexN);
     if (hit<0)
          put_string("You missed",5,1);
     else
        {
         wound=(2*(rand() % AtkP1) - (rand() % DefN));
         put_string("You hit for",5,1);
         if (wound<0)
          {
           life_enemi-=1;
           put_number(1,4,16,1);
          }
         else
          {
           life_enemi-=wound;
           put_number(wound,4,16,1);
          }
         put_string("points",21,1);
        }
     turn=0;
    }
   else
    {
     hit=2*(rand() % DexN) - (rand() % DexP1);
     if (hit<0)
        put_string("He missed",5,1);
       else
        {
         wound=2*(rand() % AtkN)-(rand() % DefP1);
         put_string("He hit for",5,1);
         if (wound<0)
           {
            life_player-=1;
	    put_number(1,4,15,1);
           }
          else
           {
            life_player-=wound;
            put_number(wound,4,15,1);
           }
         put_string("points",20,1);
        }
     turn=1;
    }

   put_number(life_player,5,25,23);
   put_number(life_enemi,5,25,24);
   vsync(2);

  }

  if (life_player>0)
     {
     put_string("You won",8,8);
     return;
     }
   else
     {
     put_string("You lost",8,8);
  put_string("Play again?",7,10);
  put_char('Y',8,13);

  vsync(60);

  while (!(joytrg(0) & JOY_STRT))
    {
	if (joytrg(0) & 0xf7)
	  {
	    if (continu)
		{
		 continu--;
		 put_char('N',8,13);
		}
	      else
		{
		 continu++;
		 put_char('Y',8,13);
		}
	  }
       vsync();
     }

 if (!(continu))
	return;
 }
     }

}
/************************************/
battlescreen()
{
char i,j;

cls();
load_sprites(0X1000,screengfx,1);
set_bgpal(0,screenpal);

i=0;
while (i<32)
{
 j=3;
 while (j<22)
  {
   put_raw(0X104,i,j);
   j++;
  }
put_raw(0X101,i,0);
put_raw(0X107,i,2);
put_raw(0X101,i,22);
put_raw(0X107,i,27);
i++;
}

put_raw(0x100,0,0);
put_raw(0X102,31,0);
put_raw(0X106,0,2);
put_raw(0X108,31,2);
put_raw(0X103,0,1);
put_raw(0X105,31,1);
put_raw(0X100,0,22);
put_raw(0X102,31,22);
put_raw(0X106,0,27);
put_raw(0X108,31,27);
put_raw(0X103,0,23);
put_raw(0X105,31,23);
put_raw(0X103,0,24);
put_raw(0X105,31,24);
put_raw(0X103,0,25);
put_raw(0X105,31,25);
put_raw(0X103,0,26);
put_raw(0X105,31,26);

}
/************************************/
enter()
{
 char i;
 i=0;
 cls();
 load_default_font();
 set_font_color(1,2);
 while (!(joytrg(0) & JOY_STRT))
  {
   if ((joytrg(0) & JOY_LEFT) && (i>0)) i--;
   if ((joytrg(0) & JOY_RGHT) && (i<4)) i++;
   if (joytrg(0) & JOY_UP) Entry[i]++;
   if (joytrg(0) & JOY_DOWN) Entry[i]--;
   put_string(Entry,15,15);
   put_string("     ",15,17);
   put_char('I',15+i,17);
   vsync(1);
  }
 return;
}
/************************************************/
sprite()
{
int pos,oldpos;

pos=1;

spriteX=16;
spriteY=16;

init_satb();
load_sprites(0X4000,sprgfx,1);
spr_set(0);
spr_pri(1);
set_sprpal(0,sprpal);
spr_pattern(0X4000);
spr_ctrl(FLIP_MAS | SIZE_MAS,NO_FLIP | SZ_16x16);
spr_pal(0);
spr_x(spriteX);
spr_y(spriteY);

while (1)
{
 switch (pos)
 {
 case -1:
    spr_hide();
    menu();
    spr_show();
    pos=oldpos;
    load_sprites(0X4000,sprgfx,1);
    break;
 case 1:
    oldpos=1; 
    pos=move1();
    break;
 case 2:
    oldpos=2; 
    pos=move2();
    break;
 case 3:
    oldpos=3;
    pos=move3();
    break;
 }
}


}
/***********************************************/
menu()
{
char i;

  satb_update();
  cls();
  set_bgpal(0,screenpal);
  set_font_color(1,2);
  load_default_font();
  load_sprites(0X1000,screengfx,1);

  put_raw(0X100,0,0);
  put_raw(0X102,31,0);
  put_raw(0X106,0,27);
  put_raw(0X108,31,27);

  i=1;
  while (i<31)
   {
    put_raw(0X101,i,0);
    put_raw(0X107,i,27);
    i++;
   }
  i=1;
  while (i<27)
   {
    put_raw(0X103,0,i);
    put_raw(0X105,31,i);
    put_raw(0X103,23,i);
    i++;
   }
  put_raw(0X100,23,0);
  put_raw(0X106,23,27);

  put_string("Item",24,2);
  put_string("Magic",24,4);
  put_string("Equip",24,6);
  put_string("Status",24,8);

  vsync();
  while(!(joytrg(0)));

}
/***********************************************/
move1()
{

map1();


while(!(JOY_STRT & joytrg(0)))
 {
  satb_update();
  if ((joy(0) & JOY_LEFT) && (spriteX>16)) {spriteX--; spr_x(spriteX);}
  if ((joy(0) & JOY_RGHT) && (spriteX<224)) {spriteX++; spr_x(spriteX);}
  if ((joy(0) & JOY_UP) && (spriteY>16) && (spriteX<225)) {spriteY--; spr_y(spriteY);}
  if ((joy(0) & JOY_DOWN) && (spriteY<192) && (spriteX<225)) {spriteY++; spr_y(spriteY);}
  if ((joy(0) & JOY_RGHT) && (spriteX>223) && (spriteX<242) && (spriteY>62) && (spriteY<66)) {spriteX++; spr_x(spriteX);}
  if ((spriteX<96) && (spriteX>64) && (spriteY<144) && (spriteY>112))
    {
     spr_hide();
     battle(LIFEMAX*2/3+rand()%(LIFEMAX/3),ATK,DEF,DEX);
     spriteX=16;
     spriteY=16;
     spr_x(spriteX);
     spr_y(spriteY);
     map1();
     spr_show();
     satb_update();
    }
  if (spriteX>240) {spriteX=2; spr_x(spriteX); return 2;}
  vsync();
 }
return -1;
}
/***********************************************/
move2()
{
int monster;
map2();
monster=0;
while(!(JOY_STRT & joytrg(0)))
 {
  satb_update();
  if ((joy(0) & JOY_LEFT) && (spriteX>16))
         {spriteX--; monster++; spr_x(spriteX);}
  if ((joy(0) & JOY_RGHT) && (spriteX<224))
         {spriteX++; monster++; spr_x(spriteX);}
  if ((joy(0) & JOY_UP) && (spriteY>16) && (spriteX>15) &&(spriteX<225))
         {spriteY--; monster++; spr_y(spriteY);}
  if ((joy(0) & JOY_DOWN) && (spriteX<225) && (spriteX>15))
         {spriteY++; monster++; spr_y(spriteY);}
  if (spriteY>210)
         {spriteY=3; spr_y(spriteY); return 3;}
  if ((joy(0) & JOY_LEFT) && (spriteX<17) && (spriteY>62) && (spriteY<66))
         {spriteX--; monster++; spr_x(spriteX);}
  if (spriteX<1)
         {spriteX=240; spr_x(spriteX); return 1;}
  if (!(monster % 10))
      { if ((rand() % 100) < (monster / 10))
        {spr_hide(); battle(LIFEMAX / 2,ATK / 2,DEF / 3,DEX); monster=0; spr_show;}
      }

  vsync();
 }
return -1;
}
/***********************************************/
move3()
{
map3();
while(!(JOY_STRT & joytrg(0)))
 {
  satb_update();
  if ((joy(0) & JOY_LEFT) && (spriteX>16)) {spriteX--; spr_x(spriteX);}
  if ((joy(0) & JOY_RGHT) && (spriteX<224)) {spriteX++; spr_x(spriteX);}
  if (joy(0) & JOY_UP) {spriteY--; spr_y(spriteY);}
  if ((joy(0) & JOY_DOWN) && (spriteY<192)) {spriteY++; spr_y(spriteY);}
  if (spriteY<1) {spriteY=207; spr_y(spriteY); return 2;}
  vsync();
 }
return -1;
}
/***********************************************/
map1()
{

char i,j;

vsync();
cls();

i=0;
load_sprites(0X1000,tilesgfx,1);
while (i<32)
{
put_raw(0x102,i,0);
put_raw(0x103,i+1,0);
put_raw(0x10a,i,1);
put_raw(0x10b,i+1,1);
put_raw(0x102,i,26);
put_raw(0x103,i+1,26);
put_raw(0x10a,i,27);
put_raw(0x10b,i+1,27);
i+=2;
}
i=2;
while (i<27)
{
put_raw(0x102,0,i);
put_raw(0x103,1,i);
put_raw(0x10a,0,i+1);
put_raw(0x10b,1,i+1);
put_raw(0x102,30,i);
put_raw(0x103,31,i);
put_raw(0x10a,30,i+1);
put_raw(0x10b,31,i+1);
i+=2;
}
i=2;
while(i<29)
{
 j=2;
 while(j<26)
  {
   put_raw(0x100,i,j);
   put_raw(0x101,i+1,j);
   put_raw(0x108,i,j+1);
   put_raw(0x109,i+1,j+1);
   j+=2;
  }
 i+=2;
}

put_raw(0x104,10,16);
put_raw(0x105,11,16);
put_raw(0x10c,10,17);
put_raw(0x10d,11,17);

put_raw(0x104,30,8);
put_raw(0x105,31,8);
put_raw(0x10c,30,9);
put_raw(0x10d,31,9);


set_bgpal(0,tilespal);

}
/***********************************************/
map2()
{

char i,j;

vsync();
cls();

i=0;
load_sprites(0X1000,tilesgfx,1);
while (i<32)
{
put_raw(0x102,i,0);
put_raw(0x103,i+1,0);
put_raw(0x10a,i,1);
put_raw(0x10b,i+1,1);
put_raw(0x102,i,26);
put_raw(0x103,i+1,26);
put_raw(0x10a,i,27);
put_raw(0x10b,i+1,27);
i+=2;
}
i=2;
while (i<27)
{
put_raw(0x102,0,i);
put_raw(0x103,1,i);
put_raw(0x10a,0,i+1);
put_raw(0x10b,1,i+1);
put_raw(0x102,30,i);
put_raw(0x103,31,i);
put_raw(0x10a,30,i+1);
put_raw(0x10b,31,i+1);
i+=2;
}
i=2;
while(i<29)
{
 j=2;
 while(j<27)
  {
   put_raw(0x100,i,j);
   put_raw(0x101,i+1,j);
   put_raw(0x108,i,j+1);
   put_raw(0x109,i+1,j+1);
   j+=2;
  }
 i+=2;
}


put_raw(0x104,0,8);
put_raw(0x105,1,8);
put_raw(0x10c,0,9);
put_raw(0x10d,1,9);


set_bgpal(0,tilespal);

}
/***********************************************/
map3()
{

char i,j;

vsync();
cls();

i=0;
load_sprites(0X1000,tilesgfx,1);
while (i<32)
{
put_raw(0x102,i,26);
put_raw(0x103,i+1,26);
put_raw(0x10a,i,27);
put_raw(0x10b,i+1,27);
i+=2;
}
i=0;
while (i<27)
{
put_raw(0x102,0,i);
put_raw(0x103,1,i);
put_raw(0x10a,0,i+1);
put_raw(0x10b,1,i+1);
put_raw(0x102,30,i);
put_raw(0x103,31,i);
put_raw(0x10a,30,i+1);
put_raw(0x10b,31,i+1);
i+=2;
}
i=2;
while(i<29)
{
 j=0;
 while(j<26)
  {
   put_raw(0x100,i,j);
   put_raw(0x101,i+1,j);
   put_raw(0x108,i,j+1);
   put_raw(0x109,i+1,j+1);
   j+=2;
  }
 i+=2;
}

set_bgpal(0,tilespal);

}
/***********************************************/
#incchr(titlegfx,TITLEPCX,32,28);
#incpal(titlepal,TITLEPCX);
#incbat(titlebat,TITLEPCX,0x1000,32,28);

#incchr(screengfx,SCREEN,3,3);
#incpal(screenpal,SCREEN);

#incchr(tilesgfx,TILES,8,8);
#incpal(tilespal,TILES);

#incspr(sprgfx,SPRITE,1,1);
#incpal(sprpal,SPRITE);
