/*	File opt.c: 2.1 (83/03/20,16:02:09) */
/*% cc -O -c %
 *
 */

#include <stdio.h>
#include "defs.h"
#include "data.h"

/* defines */
#define Q_SIZE		16

/* optimized instructions */
#define X_MASK		0xFFFF0
#define X_LDB		0x10000
#define X_LDB_A		0x10000
#define X_LDB_S		0x10001
#define X_LDB_P		0x10002
#define X_LDW_S		0x10011
#define X_LEA_S		0x10021
#define X_PEA		0x10030
#define X_PEA_A		0x10030
#define X_PEA_S		0x10031
#define X_PUSHW_A	0x10040
#define X_STB_S		0x10051
#define X_STW_S		0x10061
#define X_STBI_S	0x10071
#define X_STWI_S	0x10081
#define X_ADDW_S	0x10091
#define X_INCW_S	0x100A1
#define X_DECW_S	0x100B1

/* locals */
static INS q_ins[Q_SIZE];
static int q_rd;
static int q_wr;
static int q_nb;


/* ----
 * push_ins()
 * ----
 *
 */

void push_ins(INS *ins)
{
	/* check queue size */
	if (q_nb == Q_SIZE)
	{
		/* queue is full - flush the last instruction */
		gen_code(&q_ins[q_rd]);

		/* advance queue read pointer */
		q_rd++;
		q_nb--;

		if (q_rd == Q_SIZE)
			q_rd = 0;
	}

	/* push new instruction */
	q_wr++;
	q_nb++;

	if (q_wr == Q_SIZE)
		q_wr = 0;

	q_ins[q_wr] = *ins;

	/* optimization level 1 - simple peephole optimizer,
	 * replace known instruction patterns by highly
	 * optimized asm code
	 */
	if (optimize >= 1)
	{
		INS *p[Q_SIZE];
		int  i, j;
		int  nb;

	lv1_loop:
		/* precalculate pointers to instructions */
		if (q_nb > 4)
			nb = 4;
		else
			nb = q_nb;
		for (i = 0, j = q_wr; i < nb; i++) {
			/* save pointer */
			p[i] = &q_ins[j];

			/* next */
			j -= 1;
			if (j < 0)
				j += Q_SIZE;
		}

		/* LEVEL 1 - FUN STUFF STARTS HERE */
		nb = 0;

		/* 2-instruction patterns */
		if (q_nb >= 2)
		{
			/*  __addmi i,__stack           --> __addmi i+j,__stack
			 *  __addmi j,__stack
			 *
			 *  ====
			 *  bytes  : 15+15 = 30         --> 15
			 *  cycles : 29+29 = 58         --> 29
			 *
			 */
			if ((p[0]->code == I_ADDMI) &&
				(p[1]->code == I_ADDMI) &&
	
				(p[0]->type == T_STACK) &&
				(p[1]->type == T_STACK))
			{
				/* replace code */
				p[1]->data += p[0]->data;
				nb = 1;
			}

			/*  __addwi i                   --> __addwi i+j
			 *  __addwi j
			 *
			 *  ====
			 *  bytes  :  7+ 7 = 14         -->  7
			 *  cycles : 10+10 = 20         --> 10
			 *
			 */
			else if
			   ((p[0]->code == I_ADDWI) &&
				(p[1]->code == I_ADDWI))
			{
				/* replace code */
				p[1]->data += p[0]->data;
				nb = 1;
			}

			/*  __ldwi  i                   --> __ldwi i+j
			 *  __addwi j
			 *
			 *  ====
			 *  bytes  : 4+ 7 = 11          --> 4
			 *  cycles : 4+10 = 14          --> 4
			 *
			 */
			else if
			   ((p[0]->code == I_ADDWI) &&
				(p[1]->code == I_LDWI) &&

				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[1]->data += p[0]->data;
				nb = 1;
			}

			/*  __ldwi i                    --> __ldwi i+i
			 *  __aslw
			 *
			 *  ====
			 *  bytes  : 4+4 = 8            --> 4
			 *  cycles : 4+8 = 12           --> 4
			 *
			 */
			else if
			   ((p[0]->code == I_ASLW) &&
				(p[1]->code == I_LDWI) &&

				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[1]->data += p[1]->data;
				nb = 1;
			}

			/*  __ldw   __stack             --> @_pea_s 0
			 *  __pushw
			 *
			 *  ====
			 *  bytes  : 4+23 = 27          --> 25
			 *  cycles : 8+49 = 57          --> 44
			 *
			 */
			else if
			   ((p[0]->code == I_PUSHW) &&
				(p[1]->code == I_LDW) &&
	
				(p[1]->type == T_STACK))
			{
				/* replace code */
				p[1]->code = X_PEA_S;
				p[1]->data = 0;
				nb = 1;
			}

			/*  __ldw   __stack             --> @_lea_s i
			 *  __addwi i
			 *
			 *  ====
			 *  bytes  : 4+ 7 = 11          --> 10
			 *  cycles : 8+10 = 18          --> 16
			 *
			 */
			if ((p[0]->code == I_ADDWI) &&
				(p[1]->code == I_LDW) &&
	
				(p[1]->type == T_STACK))
			{
				/* replace code */
				p[1]->code = X_LEA_S;
				p[1]->data = p[0]->data;
				nb = 1;
			}

			/*  ...                         --> ...
			 *  __addwi 0
			 *
			 *  ====
			 *  bytes  : x+ 7               --> x
			 *  cycles : y+10               --> y
			 *
			 */
			else if
			   ((p[0]->code == I_ADDWI) &&
				(p[0]->data == 0))
			{
				/* remove code */
				nb = 1;
			}

			/*  @_stw_s i                   --> @_stw_s i
			 *  @_ldw_s i
			 *
			 *  ====
			 *  bytes  :  9+ 8 = 17         -->  9
			 *  cycles : 22+20 = 42         --> 22
			 *
			 */
			else if
			   ((p[0]->code == X_LDW_S) &&
				(p[1]->code == X_STW_S) &&
				
				(p[0]->data == p[1]->data))
			{
				/* remove code */
				nb = 1;
			}

			/*  @_stb_s i                   --> @_stb_s i
			 *  @_ldb_s i
			 *
			 *  ====
			 *  bytes  :  6+ 9 = 15         -->  6
			 *  cycles : 13+17 = 30         --> 13
			 *
			 */
			else if
			   ((p[0]->code == X_LDB_S) &&
				(p[1]->code == X_STB_S) &&
				
				(p[0]->data == p[1]->data))
			{
				/* remove code */
				nb = 1;
			}

			/*  @_lea_s i                   --> @_pea_s i
			 *  __pushw
			 *
			 *  ====
			 *  bytes  : 10+23 = 33         --> 25
			 *  cycles : 16+49 = 65         --> 44
			 *
			 */
			else if
			   ((p[0]->code == I_PUSHW) &&
				(p[1]->code == X_LEA_S))
			{
				/* replace code */
				p[1]->code = X_PEA_S;
				nb = 1;
			}

			/*  __stw   __ptr               --> @_ldb_p
			 *  __ldbp  __ptr
			 *
			 *  ====
			 *  bytes  : 4+10 = 14          --> 11
			 *  cycles : 8+19 = 27          --> 23
			 *
			 */
			else if
			   ((p[0]->code == I_LDBP) &&
				(p[1]->code == I_STW) &&
	
				(p[1]->type == T_PTR))
			{
				/* replace code */
				p[1]->code = X_LDB_P;
				nb = 1;
			}

			/*  @_lea_s i                   --> @_ldb_s i
			 *  @_ldb_p
			 *
			 *  ====
			 *  bytes  : 10+11 = 21         -->  9
			 *  cycles : 16+23 = 39         --> 17
			 *
			 */
			else if
			   ((p[0]->code == X_LDB_P) &&
				(p[1]->code == X_LEA_S))
			{
				/* replace code */
				p[1]->code = X_LDB_S;
				nb = 1;
			}

			/*  @_pea_s i                   --> @_pea_s i
			 *  @_ldb_p                         @_ldb_s i+2
			 *
			 *  ====
			 *  bytes  : 25+11 = 36         --> 25+ 9 = 34
			 *  cycles : 44+23 = 67         --> 44+17 = 61
			 *
			 */
			else if
			   ((p[0]->code == X_LDB_P) &&
				(p[1]->code == X_PEA_S) &&
				
				(optimize >= 2))
			{
				/* replace code */
				p[0]->code = X_LDB_S;
				p[0]->data = p[1]->data + 2;

				/* loop */
				goto lv1_loop;
			}

			/* flush queue */
			if (nb)
			{
				q_wr -= nb;
				q_nb -= nb;
				nb    = 0;

				if (q_wr < 0)
					q_wr += Q_SIZE;

				/* loop */
				goto lv1_loop;
			}			
		}

		/* 3-instruction patterns */
		if (q_nb >= 3)
		{
			/*  __pushw                     --> __addwi i
			 *  __ldwi  i
			 *  __addws
			 *
			 *  ====
			 *  bytes  : 23+4+24 = 51      -->  7
			 *  cycles : 49+4+41 = 94      --> 10
			 *
			 */
			if ((p[0]->code == I_ADDWS) &&
				(p[1]->code == I_LDWI) &&
				(p[2]->code == I_PUSHW) &&
	
				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[2]->code = I_ADDWI;
				p[2]->data = p[1]->data;
				nb = 2;
			}

			/*  __pushw                   --> @_addw_s i-2
			 *  @_ldw_s i
			 *  __addws
			 *
			 *  ====
			 *  bytes  : 23+ 8+24 =  55   --> 10
			 *  cycles : 49+20+41 = 110   --> 24
			 *
			 */
			else if
			   ((p[0]->code == I_ADDWS) &&
				(p[1]->code == X_LDW_S) &&
				(p[2]->code == I_PUSHW))
			{
				/* replace code */
				p[2]->code = X_ADDW_S;
				p[2]->data = p[1]->data - 2;
				nb = 2;
			}

			/*  @_pea_s j                   --> @_stbi_s i,j
			 *  __ldwi  i
			 *  __stbps
			 *
			 *  ====
			 *  bytes  : 25+4+38 =  67      -->  9
			 *  cycles : 44+4+82 = 130      --> 15
			 *
			 */
			else if
			   ((p[0]->code == I_STBPS) &&
				(p[1]->code == I_LDWI) &&
				(p[2]->code == X_PEA_S) &&

				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[2]->code  = X_STBI_S;
				p[2]->imm   = p[1]->data;
				nb = 2;
			}

			/*  @_pea_s j                   --> @_stwi_s i,j
			 *  __ldwi  i
			 *  __stwps
			 *
			 *  ====
			 *  bytes  : 25+4+42 =  71      --> 12
			 *  cycles : 44+4+91 = 139      --> 24
			 *
			 */
			else if
			   ((p[0]->code == I_STWPS) &&
				(p[1]->code == I_LDWI) &&
				(p[2]->code == X_PEA_S) &&

				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[2]->code  = X_STWI_S;
				p[2]->imm   = p[1]->data;
				nb = 2;
			}

			/*  @_pea_s i                   --> @_lea_s i+j
			 *  __ldwi  j
			 *  __addws
			 *
			 *  ====
			 *  bytes  : 25+4+24 = 53       --> 10
			 *  cycles : 44+4+41 = 89       --> 16
			 *
			 */
			else if
			   ((p[0]->code == I_ADDWS) &&
				(p[1]->code == I_LDWI) &&
				(p[2]->code == X_PEA_S) &&

				(p[1]->type == T_VALUE))
			{
				/* replace code */
				p[2]->code  = X_LEA_S;
				p[2]->data += p[1]->data;
				nb = 2;
			}

			/*  @_lea_s i                   --> @_ldw_s i
			 *  __stw   __ptr
			 *  __ldwp  __ptr
			 *
			 *  ====
			 *  bytes  : 10+4+ 7 = 21       -->  8
			 *  cycles : 16+8+18 = 42       --> 20
			 *
			 */
			else if
			   ((p[0]->code == I_LDWP) &&
				(p[1]->code == I_STW) &&
				(p[2]->code == X_LEA_S) &&

				(p[0]->type == T_PTR) &&
				(p[1]->type == T_PTR))
			{
				/* replace code */
				p[2]->code = X_LDW_S;
				nb = 2;
			}

			/*  @_pea_s i                   --> @_pea_s i
			 *  __stw   __ptr                   @_ldw_s i+2
			 *  __ldwp  __ptr
			 *
			 *  ====
			 *  bytes  : 25+4+ 7 = 36       --> 25+ 8 = 33
			 *  cycles : 44+8+18 = 70       --> 44+20 = 64
			 *
			 */
			else if
			   ((p[0]->code == I_LDWP) &&
				(p[1]->code == I_STW) &&
				(p[2]->code == X_PEA_S) &&

				(p[0]->type == T_PTR) &&
				(p[1]->type == T_PTR) &&
				
				(optimize >= 2))
			{
				/* replace code */
				p[1]->code = X_LDW_S;
				p[1]->data = p[2]->data + 2;
				nb = 1;
			}

			/* flush queue */
			if (nb)
			{
				q_wr -= nb;
				q_nb -= nb;
				nb    = 0;

				if (q_wr < 0)
					q_wr += Q_SIZE;

				/* loop */
				goto lv1_loop;
			}			
		}

		/* 4-instruction patterns */
		if (q_nb >= 4)
		{
			/*  @_ldw_s i                  --> @_ldw_s  i
			 *  __addwi 1                      @_incw_s i
			 *  @_stw_s i
			 *  __subwi 1
			 *
			 *  ====
			 *  bytes  :  8+ 7+ 9+ 7 = 31  -->  8+16 = 24
			 *  cycles : 20+10+22+10 = 62  --> 20+24 = 44
			 *
			 */
			if ((p[0]->code == I_SUBWI) &&
				(p[1]->code == X_STW_S) &&
				(p[2]->code == I_ADDWI) &&
				(p[3]->code == X_LDW_S) &&
	
				(p[0]->data == 1) &&
				(p[2]->data == 1) &&
				(p[1]->data == p[3]->data) &&
				(p[1]->data <  255))
			{
				/* replace code */
				p[2]->code = X_INCW_S;
				p[2]->data = p[3]->data;
				nb = 2;
			}

			/* flush queue */
			if (nb)
			{
				q_wr -= nb;
				q_nb -= nb;
				nb    = 0;

				if (q_wr < 0)
					q_wr += Q_SIZE;

				/* loop */
				goto lv1_loop;
			}			
		}
	}

level_2:
	/* optimization level 2 - instruction re-scheduler,
	 * change instruction order to allow direct assignments
	 * rather than stack based assignments :
	 *
	 *  @_pea_s i                   -->   ...
	 *    ...                           @_stw_s i
	 *  __stwps
	 *
	 *  ====
	 *  bytes  : 25+??+42 = ??+ 67  --> ??+ 9 = ??+ 9
	 *  cycles : 44+??+91 = ??+135  --> ??+22 = ??+22
     *
	 */
	if (optimize >= 2)
	{
		int  offset;
		int  i, j;
		int  flag;
		int  t;

		/* check last instruction */
		if ((q_nb > 1) &&
		   ((q_ins[q_wr].code == I_STWPS) ||
			(q_ins[q_wr].code == I_STBPS) ||
			(q_ins[q_wr].code == I_CALLS)))
		{
			/* browse back the instruction list and
			 * etablish a stack history
			 */
			offset = 2;

			for (i = 1, j = q_wr; i < q_nb; i++) {
				j -= 1;

				if (j < 0)
					j += Q_SIZE;

				/* check instruction */
				switch (q_ins[j].code) {
				case I_JSR:
					flag |= 0x0001;

					if (q_ins[j].type == T_LIB)
						offset += 2;
					break;

				case I_ADDMI:
					if ((q_ins[j].type == T_STACK) ||
						(q_ins[j].type == T_NOP))
					{
						offset += q_ins[j].data;
					}
					break;

				case I_CALLS:
				case I_ADDWS:
				case I_SUBWS:
				case I_ORWS:
				case I_EORWS:
				case I_ANDWS:
				case I_POPW:
				case I_STWPS:
				case I_STBPS:
					offset += 2;
					break;

				case I_PUSHW:
				case X_PEA_S:
				case X_PUSHW_A:
					offset -= 2;
					break;
				}

				/* check offset */
				if (offset == 0) {
					/* good! */
					if (i == 1) {
						/* hmm, may be not...
						 * there should be at least one instruction
						 * between pea_s and stwps.
						 * this case should never happen, though,
						 * but better skipping it
						 */
						if (q_ins[q_wr].code != I_CALLS)
							break;
					}

					/* check the first instruction
					 */
					if (q_ins[q_wr].code == I_CALLS) {
						if (q_ins[j].code != X_PUSHW_A)
							break;
					}
					else {
						if (q_ins[j].code != X_PEA_S)
							break;

						/* change stwps into stw_s */
							q_ins[q_wr].data =  q_ins[j].data;
						if (q_ins[q_wr].code == I_STBPS)
							q_ins[q_wr].code =  X_STB_S;
						else
							q_ins[q_wr].code =  X_STW_S;
					}

					/* adjust stack references;
					 * because of the removal of pea_s
					 */
					for (t = i; t > 1; t--) {
						j += 1;
						if (j >= Q_SIZE)
							j -= Q_SIZE;

						/* check instruction */
						switch (q_ins[j].code) {
						case X_LEA_S:
						case X_PEA_S:
						case X_LDB_S:
						case X_LDW_S:
						case X_STB_S:
						case X_STW_S:
						case X_INCW_S:
						case X_ADDW_S:
						case X_STBI_S:
						case X_STWI_S:
							/* adjust stack offset */
							q_ins[j].data -= 2;
							break;
						}
					}

					/* remove all the instructions... */
					q_wr -= (i + 1);
					q_nb -= (i + 1);
					   j -= (i - 1);

					if (q_wr < 0)
						q_wr += Q_SIZE;
					if (j < 0)
						j += Q_SIZE;

					/* ... and re-insert them one by one
					 * in the queue (for further optimizations)
					 */
					for (; i > 0; i--) {
						j += 1;
						if (j >= Q_SIZE)
							j -= Q_SIZE;

						push_ins(&q_ins[j]);
					}
					break;
				}
			}
		}			
	}
}


/* ----
 * flush_ins()
 * ----
 * flush instruction queue
 *
 */

void flush_ins()
{
	while (q_nb)
	{
		/* gen code */
		gen_code(&q_ins[q_rd]);

		/* advance and wrap queue read pointer */
		q_rd++;
		q_nb--;

		if (q_rd == Q_SIZE)
			q_rd = 0;
	}

	/* reset queue */
	q_rd = 0;
	q_wr = Q_SIZE - 1;
	q_nb = 0;
}


/* ----
 * gen_asm()
 * ----
 * generate optimizer asm code
 * 
 */

gen_asm(INS *inst)
{
	switch (inst->code) {
	case X_LDB_P:
		ol("__ldb_p");
		break;

	case X_LDB_S:
		ot("__ldb_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_LDW_S:
		ot("__ldw_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_LEA_S:
		ot("__lea_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_PEA_S:
		ot("__pea_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_STBI_S:
		ot("__stbi_s\t");
		outdec(inst->imm);
		outstr(",");
		outdec(inst->data);
		nl();
		break;

	case X_STWI_S:
		ot("__stwi_s\t");
		outdec(inst->imm);
		outstr(",");
		outdec(inst->data);
		nl();
		break;

	case X_STW_S:
		ot("__stw_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_STB_S:
		ot("__stb_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_INCW_S:
		ot("__incw_s\t");
		outdec(inst->data);
		nl();
		break;

	case X_ADDW_S:
		ot("__addw_s\t");
		outdec(inst->data);
		nl();
		break;
	}
}

