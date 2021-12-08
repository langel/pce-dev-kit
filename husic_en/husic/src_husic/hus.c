/* -----------------------------------------------------------
 HuSIC body ver 0.26 by BouKiCHi
   Multi purpose sound driver

   The driver is started at 2004/02/29
   The code which the driver uses is based on mck's code.
   Please see license in the package to use this code.
 ----------------------------------------------------------- */

/********************************************

  The details of the PCE tone generator
  0-1ch waveform
  the channels can also be used as a Frequency Modulation(FM).
  if the channels were FM, the channels cannot use as a waveform.

Å@2-3ch waveform

  4-5ch waveform
  the channels can also be used as a noise geenerator.

  The details of waveform data

	the data of waveform is signed 5bit 32bytes.
    the resulution of the data is 12bit.


*********************************************/

#define SND_SEL 0x0800 /* Channel Selector */
#define SND_VOL 0x0801 /* Global Volume */
#define SND_FIN 0x0802 /* Fine Freq */
#define SND_ROU 0x0803 /* Rough Freq */
#define SND_MIX 0x0804 /* Mixer */
#define SND_PAN 0x0805 /* Pan Volume */
#define SND_WAV 0x0806 /* Wave Buffer */
#define SND_NOI 0x0807 /* Noise Mode */
#define SND_LFO 0x0808 /* LFO */
#define SND_LTR 0x0809 /* LFO trig */


/* mixer register
bit7 voice on/off(guessed)
bit6 Direct D/A(dda)
*/


extern int sound_dat[];
extern int xpcmdata;

extern int pcewav[];

/* noise = 3.58MHz / 64 * ( 5bit XOR 31) */


/* o4 = 2 ,o3 = 1 ,o2 = 0 */

/********************
 Lower 4bit of note
 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
 C  C#  D D#  E  F F#  G G#  A A#  B     A A#  B

 range 0D-0F is lower 1 octave than range 00-0B

********************/


#include "ftable.h"

char	reg_ch;

char	ch_cnt[8];
char	ch_vol[8];
char	ch_bank[8];

char	ch_nowbank;
char	ch_topbank;

char	note_data[8];

char	pitch_sw[8];
char	note_sw[8];

char	detune[8];
char	panpod[8];
char	loop_cnt[8];

char	*seq_ptr;
int		seq_pos[8];
int		seq_freq[8];

int		pitch_envadr[8];
int		volume_envadr[8];
int		note_envadr[8];

int		i,j;
char	noise_freq[2];
char	noise_sw[2];

char	lfo_num[8]; /* 0xff = no_effect*/
char	lfo_cnt[8]; /* speed cnt */
char	lfo_ct2[8]; /* step cnt */
char	lfo_stp[8]; /* step of 1level */
char	lfo_lev[8]; /* up/down level of 1step */
char	lfo_sw[8];


#include "xpcmdrv.c"

#asm
	.proc _chg_cbank
	txa
	tam #2
	rts
	.endp

	.proc _now_cbank
	tma #2
	tax
	cla
	rts
	.endp

	.proc _def_cbank
	lda #CONST_BANK+_bank_base
	tam #2
	rts
	.endp

#endasm



mixvol(val)
char val;
{
 if (reg_ch == XPCM_CH && xpcm_sw)
 {
	poke(SND_MIX,0xC0|val);
	return;
 }

    if (!val)
		poke(SND_MIX,0);
    else 
		poke(SND_MIX,0x80|val);
}

snd_saw(ch)
int ch;
{
	char inf;

	reg_ch = ch;
	poke(SND_SEL, ch);
	poke(SND_MIX, 0x00);

	for(inf=0; inf < 32; inf++)
	{
		poke(SND_WAV,inf);
	}
	poke(SND_PAN, panpod[ch]);
	poke(SND_MIX, 0x80); /* on */
}

snd_chg(ch,num)
int ch,num;
{
	char	inf;
	char	*pcmpos;

	pcmpos = *(pcewav[0]+(num<<1));

	reg_ch = ch;
	poke(SND_SEL,ch);

	poke(SND_MIX, 0x00);

	for(inf=0; inf < 32; inf++)
	{
		poke(SND_WAV,*pcmpos);
		pcmpos++;
	}
	poke(SND_MIX, 0x80); /* on */
}


#asm

	.proc _set_drvintr

	stw   #_vsync_drv,vsync_hook
	smb   #4,<irq_m		; enable new code
	smb   #5,<irq_m		; disable system card code

	rts

	.endp

#endasm

/* freq = 3.58MHz / 32 x (12bit value) */

/* Initializes HuSIC driver */

drv_init()
{
	char *seq_data;

	ch_topbank = now_cbank();

	for (i = 0; i < 6; i++) {
		lfo_num[i]  = note_sw[i] = panpod[i] = pitch_sw[i] = 0xff;
		seq_pos[i]  = *(sound_dat[0]+(i<<1));
		loop_cnt[i] = detune[i] =
		note_envadr[i] = pitch_envadr[i] = volume_envadr[i] = 0x00;

		ch_bank[i]  = *(sound_dat[7]+i);
	}
	for(i=0; i < 2; i++)  noise_sw[i] = noise_freq[i] = 0x00;

	poke(SND_VOL, 0xFF); /* maxvol */

	for(i=0; i<6; i++) {
		snd_saw(i);
		ch_cnt[i]=0;
	}

	init_pcmdrv();
	set_drvintr();
}

set_vol(ch,buf)
int ch,buf;
{
	/*
		poke(SND_PAN,0);
		return;
	 */
	if (buf & 0x80)
	{
		volume_envadr[ch] = 0;
		mixvol(buf & 0x1f);
		/* pan volume */
	}
	else
	{
		buf &= 0x7f;
		chg_cbank(ch_topbank);
		volume_envadr[ch]= *(sound_dat[2] + (buf<<1));
		chg_cbank(ch_nowbank);
	}
}

set_note(chan,data)
char chan,data;
{
	char i;

	i = (data + 3) & 0x0f;
	put_hex(i,2, 5 + (chan<<2),13);
	seq_freq[chan] = freq[i & 0x0f] >> (data>>4);
}



extern int seqproc[];

seq(ch,sd)
int ch,sd;
{
    int seq_adrs,tmp;
	

    while(sd >= 0x90)
    {

	if (sd >= 0xec) 
	{
		tmp = seqproc[sd-0xec];
#asm
;  make jump
;  sax

  pha
  sax
  pha
  rts
#endasm

#asm
SEQ_FF:
  nop
#endasm

		chg_cbank(ch_topbank);
		seq_ptr = *(sound_dat[1]+(ch<<1));
		ch_nowbank = *(sound_dat[8]+ch);
		chg_cbank(ch_nowbank);

#asm
		jmp endpoint
#endasm

#asm
SEQ_FE:
  nop
#endasm
		seq_ptr+=2;
		
#asm
	jmp endpoint
#endasm



#asm
SEQ_F9:
  nop
#endasm
		seq_ptr+=2;
#asm
	jmp endpoint
#endasm

#asm
SEQ_FD:
  nop
#endasm

/* Volume Set */
		j = *(++seq_ptr); seq_ptr++;
		/* j=0x8F; */
		ch_vol[ch]=j;
		set_vol(ch,j);
		
#asm
	jmp endpoint
#endasm

#asm
SEQ_FC:
  nop
#endasm

/* Rest */
		j = *(++seq_ptr); seq_ptr++;

		mixvol(0);

		if (ch == XPCM_CH && xpcm_sw) 
			pcm_off();
		
		volume_envadr[ch] = 0x00; /* envelope off */
		ch_cnt[ch] = j;
		return;
#asm
	jmp endpoint
#endasm

#asm
SEQ_FB:
  nop
#endasm
		j = *(++seq_ptr); seq_ptr++;

		lfo_num[ch] = j;
		lfo_sw[ch]  = 0;
		chg_cbank(ch_topbank);
		lfo_cnt[ch] = *(sound_dat[6]+(j<<2));
		chg_cbank(ch_nowbank);

#asm
	jmp endpoint
#endasm

#asm
SEQ_FA:
  nop
#endasm

 /* detune */
		j = *(++seq_ptr); seq_ptr++;

		if (j == 0xff)
			detune[ch] = 0x00;
		else
			detune[ch] = j;

#asm
	jmp endpoint
#endasm

#asm
SEQ_F8:
  nop
#endasm
		j = *(++seq_ptr); seq_ptr++;
		pitch_sw[ch] = j;

#asm
	jmp endpoint
#endasm

#asm
SEQ_F7:
  nop
#endasm
		j = *(++seq_ptr); seq_ptr++;
		note_sw[ch] = j;

#asm
	jmp endpoint
#endasm

#asm
SEQ_F4:
  nop
#endasm
 /* wait */
		j = *(++seq_ptr); seq_ptr++;
		ch_cnt[ch] = j;

#asm
	jmp endpoint
#endasm

#asm
SEQ_F2:
  nop
#endasm
/* PCE noise command */
		j = *(++seq_ptr); seq_ptr++;

		if (ch > 3) {
			if (j) 
				noise_sw[ch - 4] = 0x01;
			else {
				noise_sw[ch - 4]  =0x00;
				poke(SND_NOI,0);
			}
		}
		

#asm
	jmp endpoint
#endasm

#asm
SEQ_F1:
  nop
#endasm

 /* PCE wave change command */
		j = *(++seq_ptr); seq_ptr++;
		chg_cbank(ch_topbank);
		snd_chg(ch,j);
		chg_cbank(ch_nowbank);
		

#asm
	jmp endpoint
#endasm

#asm
SEQ_F0:
  nop
#endasm


/* PCE pan command */
		j = *(++seq_ptr); seq_ptr++;
		panpod[ch] = j;
		poke(SND_PAN, j);

#asm
	jmp endpoint
#endasm

#asm
SEQ_EF:
  nop
#endasm

 /* XPCM switch */
		j = *(++seq_ptr); seq_ptr++;

		if (ch == XPCM_CH) {
			xpcm_sw = j;
			if (xpcm_sw) 
				pcm_on(XPCM_CH);

		}
		
#asm
	jmp endpoint
#endasm

#asm
SEQ_EE:
  nop
#endasm

 /* Bank Change Command */
		j = *(++seq_ptr); seq_ptr++;
		seq_adrs = *(seq_ptr) | *(seq_ptr+1)<<8;
		seq_ptr = seq_adrs;

		/* put_hex(seq_ptr,4,5,16); */

		chg_cbank(j);
		ch_nowbank = j;

#asm
	jmp endpoint
#endasm

#asm
SEQ_ED:
  nop
#endasm

 /* LFO mode */
		j = *(++seq_ptr); seq_ptr++;
		if (j == 0xff) {
			poke(SND_LTR,0x00); 
			/* off */
		} else {
			poke(SND_LTR,j|0x80); 
			/* bit7 as high is turned on the hardware LFO */
		}

#asm
	jmp endpoint
#endasm

#asm
SEQ_EC:
  nop
#endasm

 /* LFO freq */
		j = *(++seq_ptr); seq_ptr++;
		poke(SND_LFO,j);
		
#asm
endpoint:
#endasm
     }
		else {
			if (sd == 0xa1) {
				
				/* repeat2 command */
				seq_ptr++;
				if (loop_cnt[ch] == 1)
				{
					loop_cnt[ch] = 0;
					
					seq_adrs = *(seq_ptr) | *(seq_ptr+1)<<8;
					seq_ptr  = seq_adrs;
				} else	seq_ptr+=2;
			}
			if (sd == 0xa0) {
				/* repeat command */
				j = *(++seq_ptr); seq_ptr++;
				
				tmp = *(seq_ptr++); /* bank */
				seq_adrs =  *(seq_ptr) | *(seq_ptr + 1) << 8;
				seq_ptr  += 2;
				
				if (loop_cnt[ch] == 1)
				{
					loop_cnt[ch] = 0;
				} 
				else
				{
					if (loop_cnt[ch] > 1)
						loop_cnt[ch]--;
					else
						loop_cnt[ch] = j-1;

					seq_ptr = seq_adrs;
					chg_cbank(tmp);
					ch_nowbank = tmp;
				} 
			}
		}
		
	sd = *seq_ptr;
    }

    if (sd < 0x90) 
	{

		note_data[ch] = sd;

		if (ch == XPCM_CH && xpcm_sw) 
		{

			chg_cbank(ch_topbank);
			pcm_off();
			tmp = xpcmdata + (sd<<3);

			xpcm_addr = *(tmp);
			xpcm_len  = *(tmp+2);
			xpcm_bank = *(tmp+4);

			/* put_hex(xpcm_len,4,5,16); */
			chg_pcmbank(xpcm_bank);
			
			pcm_on(ch);
			chg_cbank(ch_nowbank);

			j = *(++seq_ptr); seq_ptr++;
			ch_cnt[ch] = j;
			set_vol(ch,ch_vol[ch]);

			return;
		}

		/* reload ptr of pitch env */
		chg_cbank(ch_topbank);

		/* set note stuff */
		if (note_sw[ch] == 0xff)
			note_envadr[ch] = 0;
		else
			note_envadr[ch] = *(sound_dat[9]+(note_sw[ch]<<1));

		/* set pitch stuff */
		if (pitch_sw[ch] == 0xff) 
			pitch_envadr[ch] = 0;
		else 
			pitch_envadr[ch] = *(sound_dat[4]+(pitch_sw[ch]<<1));

		chg_cbank(ch_nowbank);

        if (ch > 3 && noise_sw[ch-4])
		{
			noise_freq[ch-4] = sd & 0x1f;
			poke(SND_NOI, 0x80 | sd & 0x1f );

			j = *(++seq_ptr); seq_ptr++;
			ch_cnt[ch]=j;
			set_vol(ch,ch_vol[ch]);

			return;
		}

		put_hex(sd,2, 5 + (ch<<2),11);


		/* 0x20 = o4c , 0x30 = o5c */

		/* j =  0x0c * (sd>>4); 
		   j += (sd+3) & 0x0f; */

	
		chg_cbank(ch_topbank);

		lfo_sw[ch]  = 0;
		lfo_cnt[ch] = *(sound_dat[6]+(lfo_num[ch]<<2));

		set_note(ch,sd);

		chg_cbank(ch_nowbank);


		if ( detune[ch] )
		{
			if ( detune[ch] & 0x80 )
				seq_freq[ch] -= detune[ch] & 0x7f;
			else
				seq_freq[ch] += detune[ch] & 0x7f;
		}

		poke(SND_ROU, (seq_freq[ch]>>8) & 0x0f );
    	poke(SND_FIN,  seq_freq[ch]     & 0xff );

		j = *(++seq_ptr); seq_ptr++;
		ch_cnt[ch] = j;

		set_vol(ch,ch_vol[ch]);

    }
}

#asm
_seqproc:
	dw   SEQ_EC
	dw   SEQ_ED
	dw   SEQ_EE
	dw   SEQ_EF
	dw   SEQ_F0
	dw   SEQ_F1
	dw   SEQ_F2
	dw   endpoint ; f3
	dw   SEQ_F4
	dw   endpoint ; f5
	dw   endpoint ; f6
	dw   SEQ_F7   ; f7
	dw   SEQ_F8
	dw   SEQ_F9
	dw   SEQ_FA
	dw   SEQ_FB
	dw   SEQ_FC
	dw   SEQ_FD
	dw   SEQ_FE
	dw   SEQ_FF

#endasm


divxt(x,y)
char x,y;
{
	int i,j;

	j=0;
	for(i=0; j < x; i++) j+=y;
	return i;
}

drv_pitchenv(sch)
int sch;
{
	char buf; 
	/* type 'char' is important!! */

	if (pitch_envadr[sch])
	{

			buf = *pitch_envadr[sch];
			pitch_envadr[sch]++;

			if (buf == 0xff)
			{
				pitch_envadr[sch] = *(sound_dat[5]+(pitch_sw[sch]<<1));
				buf = *pitch_envadr[sch];
				pitch_envadr[sch]++;
			}


			if (sch > 3 && noise_sw[sch-4])
			{
				if (buf & 0x80)
					noise_freq[sch-4] -= buf&0x7f;
				else
					noise_freq[sch-4] += buf;

				poke(SND_NOI,0x80 | noise_freq[sch-4] & 0x1f);
			}

			if (buf & 0x80)
				seq_freq[sch] -= buf & 0x7f;
			else
				seq_freq[sch] += buf;

  			poke(SND_ROU, (seq_freq[sch]>>8) & 0x0f );
	    	poke(SND_FIN,  seq_freq[sch]     & 0xff );

	}

}

drv_lfoseq(sch)
int sch;
{
	int tmp;
	if (lfo_num[sch] != 0xff)
	{
		tmp = sound_dat[6]+(lfo_num[sch]<<2);
		put_hex(lfo_lev[sch], 2, 5+(sch<<2),15);
		put_hex(lfo_cnt[sch], 2, 5+(sch<<2),16);
		put_hex(lfo_ct2[sch], 2, 5+(sch<<2),17);

		/* tmp+1 = speed
		   tmp+2 = depth */

		switch(lfo_sw[sch])
		{
		case 0x00:
			if (lfo_cnt[sch]) 
				lfo_cnt[sch]--; 
			else
			{
				lfo_sw[sch]  = 1;
				lfo_cnt[sch] = *(tmp+1);

				lfo_ct2[sch] = divxt(*(tmp+1),*(tmp+2));
				lfo_stp[sch] = lfo_ct2[sch];

				lfo_lev[sch] = divxt(*(tmp+2),*(tmp+1));

				if (!lfo_lev[sch])
					lfo_lev[sch]=1;

					/* 1step = lfo_speed/lfo_depth
					   1level = lfo_depth/lfo_speed */

			}
		break;
		case 0x01:
			if (lfo_cnt[sch])
				lfo_cnt[sch]--;

			if (lfo_ct2[sch])
				lfo_ct2[sch]--; 
			else
			{
			    seq_freq[sch] -= lfo_lev[sch];
			    lfo_ct2[sch]   = lfo_stp[sch];
			    if (!lfo_cnt[sch])
				{
					lfo_cnt[sch]=*(tmp+1);
					lfo_sw[sch]=0x02;
			    }
			}
		break;
		case 0x02:
			if (lfo_cnt[sch])
				lfo_cnt[sch]--;

			if (lfo_ct2[sch]) 
				lfo_ct2[sch]--; 
			else
			{

				seq_freq[sch] += lfo_lev[sch];
				lfo_ct2[sch]   = lfo_stp[sch];

				if (!lfo_cnt[sch])
				{
					lfo_cnt[sch] = *(tmp+1);
					lfo_sw[sch]  = 0x03;
			    }
			}
		break;
		case 0x03:
			if (lfo_cnt[sch])
				lfo_cnt[sch]--;

			if (lfo_ct2[sch]) 
				lfo_ct2[sch]--; 
			else
			{
				seq_freq[sch] += lfo_lev[sch];
				lfo_ct2[sch]  =  lfo_stp[sch];

			    if (!lfo_cnt[sch])
				{
					lfo_cnt[sch] = *(tmp+1);
					lfo_sw[sch]  = 0x04;
			    }
			}
		break;
		case 0x04:
			if (lfo_cnt[sch])
				lfo_cnt[sch]--;

			if (lfo_ct2[sch]) 
				lfo_ct2[sch]--; 
			else
			{
			    seq_freq[sch] -= lfo_lev[sch];
			    lfo_ct2[sch]   = lfo_stp[sch];

				if (!lfo_cnt[sch])
				{
					lfo_cnt[sch] = *(tmp+1);
					lfo_sw[sch]  = 0x01;
			    }
			}
		break;
		} /* switch */
	
		poke(SND_ROU, (seq_freq[sch]>>8) & 0x0f );
		poke(SND_FIN,  seq_freq[sch]     & 0xff );
	} /* end of LFO_SW */
}


drv_intr()
{
    int   sch,tmp;
    char  buf,num,mod;

    for(sch=0; sch < 6; sch++)
	{

		reg_ch = sch;
		poke(SND_SEL, sch);

		put_hex(ch_cnt[sch],2,5+(sch<<2),12);

		if (!ch_cnt[sch])
		{
			seq_ptr = seq_pos[sch];

			ch_nowbank = ch_bank[sch];
			chg_cbank(ch_nowbank);

			seq(sch, *seq_ptr );
			seq_pos[sch] = seq_ptr;

			ch_bank[sch] = ch_nowbank;
			chg_cbank(ch_topbank);

		}

		ch_cnt[sch]--;

		if (volume_envadr[sch])
		{

			buf = *volume_envadr[sch];
			volume_envadr[sch]++;

			if (buf == 0xff)
			{
				buf = ch_vol[sch] & 0x7f;
				volume_envadr[sch] = *(sound_dat[3]+(buf<<1));
				buf = *volume_envadr[sch];
				volume_envadr[sch]++;
			}

			mixvol(buf & 0x1f);
		}

		if (note_envadr[sch])
		{

			buf = *note_envadr[sch];
			note_envadr[sch]++;

			if (buf == 0xff)
			{
				note_envadr[sch] = *(sound_dat[10] + (note_sw[sch]<<1));
				buf = *note_envadr[sch];
				note_envadr[sch]++;
			}

			if (buf & 0x80)
			{
				mod = note_data[sch];
				num = buf&0x7f;
				tmp = (num/12)<<4;
				mod -= tmp;
				tmp = num%12;
				if ((mod & 0x0f) >= tmp)
				{
					mod -= tmp;
				} else
				{
					mod -= 0x04;
					mod	-= tmp;
				}
				note_data[sch] = mod;
			} else
			{
				mod = note_data[sch];
				num = buf;
				tmp = (num/12)<<4;
				mod += tmp;
				tmp = num%12;
				mod += tmp;
				if ((mod & 0x0f) >= 0x0c)
				{
					mod += 0x04;
				}
				note_data[sch] = mod;
			}
			put_hex(note_data[sch],2, 5 + (sch<<2),11);
			set_note(sch,note_data[sch]);

			poke(SND_ROU, (seq_freq[sch]>>8) & 0x0f );
			poke(SND_FIN,  seq_freq[sch]     & 0xff );
		}

		drv_pitchenv(sch);
		drv_lfoseq(sch);

    } /* end of for(..) */
}

