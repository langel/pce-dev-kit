#include "huc.h"

/*------------------------------------------------------------------------------------*/
/* include the huc interface to the psg bios functions. Note that both of these are   */
/* NOT needed (only psglib, I think). However, including them both allows us to do    */
/* 'on-the-fly' changes, though that can (and will) mess up the player. If you don't  */
/* like using sngInit(), wavelib has some of the functions needed to set things up by */
/* hand, assuming you know what you're doing :-)                                      */
/*------------------------------------------------------------------------------------*/

#include "sound/psglib.c"
#include "snginit.c"

int VSyncCnt;
int TimerCnt;
int MainCnt;
int SubCnt;

main()
{
	int  song;
	int  jsv;

	int  psgMainStatus;
	int  psgSubStatus;

	init_satb();

	/*-----------------------------------------------------------------------*/
	/* set up psg / mml player.                                              */
	/*-----------------------------------------------------------------------*/

	psgInit(5);
	psgOn(0); 			/* use timer for now : vsync works okay, but limits speed */
	psgPlay(0);			/* play Track 0.  If you only have one song in your .mml file, 
						it had better be .TRACK 0 */
						
	/*-----------------------------------------------------------------------*/
	/* initialize the song. sngInit() is a squirrel-generated function, that */
	/* handles all of the setup for a song, including registering everything.*/
	/* It is worth looking at to see how things are done to actually get a   */
	/* song ready for playing.                                               */
	/*-----------------------------------------------------------------------*/
	sngInit();
	psgDelay( 0 );


	while( 1 )
	{
		vsync(0);
		jsv = joy(0);
		
		/* Use these to check the status of channels
		/* They return the bitfield of playing channels,
		/*                                            65 4321
		/* Each channel represents 1 bit in a byte (00xx xxxx)
		/* If you have any problems, ask me (Arkhan)
		*************************************************************/
		psgMainStatus = psgMStat();
		psgSubStatus  = psgSStat();


		put_string("          Squirrel 3.0             ", 0, 9);
		put_string(" Please direct all questions to    ", 0, 11);
		put_string("      aetherbyte@gmail.com         ", 0, 13);
		put_string(" or post at aetherbyte.com/forum   ", 0, 15);
		put_string("     Thank you and Enjoy!!!!!!     ", 0, 17);

		/* these will only work if you made subtrack 1 and subtrack 2 as sound effects	  
			see gnop.mml, and the manual, for details */		
		if( jsv & JOY_A )                       
		{
			psgPlay( 1 );	 		
		}

		if( jsv & JOY_B )                        
		{
			psgPlay( 2 );
		}
	
	}
	
}

