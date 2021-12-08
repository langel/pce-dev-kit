/*****************************************
 *****************************************
 ***                                   ***
 ***       TRANSLATION DE PALETTE      ***
 ***            ( Chenille )           ***
 ***                                   ***
 *****************************************
 *****************************************
 ***                                   ***
 ***             version 1             ***
 ***                                   ***
 *****************************************
 *****************************************
 ***                                   ***
 ***         jycet@caramail.com        ***
 ***                                   ***
 *****************************************
 *****************************************/

#include "huc.h"

#incchr(image_chr, "image.pcx");			/* chargement image */
#incbat(image_bat, "image.pcx", 0x1000);	/* chargement image */
#incpal(image_pal, "image.pcx", 0);			/* chargement image */

int i,j;									/* définition des variables */
char palette[48];							/* définition du nombre de couleur */

main()										/* debut programme principal */
{
j=0;										/* initialisation du point de depart de la palette */
disp_off();									/* désactivation ecran */
load_background(image_chr, image_pal, image_bat, 32, 28);	/* affichage image */
disp_on();									/* actvation ecran */
	for (i=0; i<16; i+=1)					/* initialisation d'une palette nuancée de 48 couleurs */
		{
		palette[i]=get_color(i);			/* initialisation d'une palette nuancée de 16 couleurs (de 0 à 15) */
		palette[i+16]=get_color(15-i);		/* initialisation d'une palette nuancée de 16 couleurs (de 16 à 31) */
		palette[i+32]=get_color(i);			/* initialisation d'une palette nuancée de 16 couleurs (de 32 à 47) */
		}

for (;;)									/* debut de la boucle du prog principal */
	{
	for (i=0; i<16; i+=1)					/* initialisation de la palette */
		{
			set_color(i,palette[i+j]);		/* initialisation de la palette */
		}
	j+=1;									/* deplace le point de depart de la palette */
	if (j==32){j=0;}						/* remise a 0 du point de depart de la palette */
		vsync(1);							/* affichage à 30 FPS */
	}

}
