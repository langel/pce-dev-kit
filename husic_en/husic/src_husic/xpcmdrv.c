/* Please see license in document of HuSIC to use this code */

#define XPCM_CH 5

int  xpcm_addr;
int  xpcm_len;
char xpcm_bank;
char xpcm_mode;
char xpcm_sw;
char xpcm_sp;

/* XPCM Interface ver 0.1 

  xpcm_ptr = address of PCM data
  xpcm_len = length of PCM data

  xpcm_mode = status
  0x00  ... stop
  0x01  ... play

*/

pcm_on(ch)
int ch;
{
	if (!xpcm_mode)
	{
		poke(SND_SEL, ch);
		poke(SND_MIX, 0xDF); /* on */
		ena_irq_tmr();
		xpcm_mode = 1;
	}
}

pcm_off()
{
	if (xpcm_mode)
	{
		dis_irq_tmr();
		xpcm_mode = 0;
	}
	
}

pcm_set(ch)
int ch;
{
	poke(SND_SEL, ch);
	poke(SND_MIX, 0x00); /* on */
}


pcm_intr()
{
	char out;
	if (xpcm_mode) {

		if (xpcm_sp & 1) {
			out = (peek(xpcm_addr)>>3) & 0x1e;
		} else {
			out = (peek(xpcm_addr++)<<1) & 0x1e;
			if (xpcm_len) xpcm_len--; else pcm_off();
		}
		xpcm_sp ^= 0x01;
		poke(SND_SEL, XPCM_CH);
		poke(SND_WAV,out);
		poke(SND_SEL,reg_ch);
	} 
}

#asm
    .proc _ena_irq_tmr
	smb   #2,<irq_m
	rts
	.endp

    .proc _dis_irq_tmr
	rmb   #2,<irq_m
	rts
	.endp

	.proc _set_pcmintr

	stz   irq_status
	stw   #_timer_pcm,timer_jmp
	rmb   #2,<irq_m

	lda   #0
	sta   timer_cnt

	lda   #$1
	sta   timer_ctrl

	cli

	rts
	.endp

	.proc _chg_pcmbank
	txa
	tam #3
	rts
	.endp

#endasm


init_pcmdrv()
{
	xpcm_sp=0x00;
	xpcm_sw=0x00;
	xpcm_mode=0x00;
	set_pcmintr();
}

