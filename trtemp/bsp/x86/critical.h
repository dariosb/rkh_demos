/*
 * critical.h
 * Critical Section 
 */

#ifndef __CRITICAL_H__
#define __CRITICAL_H__

#include <windows.h>

extern CRITICAL_SECTION trt_crt_sec;

#define init_critical()		InitializeCriticalSection( &trt_crt_sec )
#define enter_critical()	EnterCriticalSection( &trt_crt_sec )
#define exit_critical()		LeaveCriticalSection( &trt_crt_sec )


#endif
