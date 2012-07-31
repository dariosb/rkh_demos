/*
 * debug.h
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#if ACTIVE_DEBUG

#define DBG_MODULE_NAME(name)	static const char *m_name = #name;

void _dprintf( const char* fmt, ... );
void _mdebug( int i, const char *mn, const char *fn );

#define mdebug(s)				_mdebug(s, m_name, __FUNCTION__ )

#define dprintf					_dprintf

#else

#define DBG_MODULE_NAME(name)

#define mdebug(s)				(void)(0)

#define dprintf( x, ... )		(void)(0)

#endif

#define PR_OFFSET	"#"
#define DBG_OFFSET	"\t\t\t\t\t\t   "

enum
{
	TMP_DBG,
	TCTRL_DBG,
	GPS_DBG,
	TRK_DBG,
	EMGR_DBG,
	GPRS_DBG
};

#endif
