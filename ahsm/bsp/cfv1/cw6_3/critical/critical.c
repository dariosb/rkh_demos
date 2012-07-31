/*
 * critical.c
 * ColdFire V1 critical section 
 */

#include "critical.h"
#include "derivative.h"

#define INT_MASK	0x2700

#if (CRITICAL_METHOD == 1)

static unsigned short crit_cnt;
static unsigned short sr_mem;

void
init_critical( void )
{
	asm
	{
		move.w	#0,d0
		move.w	d0,crit_cnt
	}
}

void 
enter_critical( void )
{
	asm
	{
		move.w	crit_cnt,d0
		addq.l	#1,d0
		move.w	d0,crit_cnt
		cmpi.w	#1,d0
		bhi.s	end

		save:
		move.w	sr,d0
		move.w	d0,sr_mem
		move.w	#INT_MASK,d0
		move.w	d0,sr
		end:
	}
}

void 
exit_critical( void )
{
	asm
	{
		tst.w	crit_cnt
		beq.s	restore
		move.w	crit_cnt,d0
		subq.l	#1,d0
		move.w	d0,crit_cnt
		bne.s	end

		restore: 
		move.w	sr_mem,d0
		move.w	d0,sr
		end:
	}
}

#endif

#if CRITICAL_METHOD == 2

static ushort *ccr_sp;
static ushort ccr_sp_mem[ MAX_NESTING_CSECT ];

void
init_critical( void )
{
	asm
	{
		lea		ccr_sp_mem,a0
		move.l	a0,ccr_sp
	}
}

void 
enter_critical( void )
{
	asm
	{
		move.w	sr,d0
		movea.l	ccr_sp,a0
		move.w	d0,(a0)
		move.w	#INT_MASK,d0
		move.w	d0,sr
		addq.l	#2,ccr_sp
	}
}

void 
exit_critical( void )
{
	asm
	{
		subq.l	#2,ccr_sp
		movea.l	ccr_sp,a0
		move.w	(a0),d0
		move.w	d0,sr
	}
}

#endif


