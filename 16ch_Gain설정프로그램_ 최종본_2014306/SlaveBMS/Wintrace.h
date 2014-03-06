//WinTrace.h
#ifndef _WINTRACE_H_
#define _WINTRACE_H_

#define WINTRACE_NAME	"WINTRACE"
#define COMPUTER_NAME	"."

BOOL WINTRACE(const char *format, ...);

#define WINTRACE_THIS_ERROR(lpmsg) \
		::WINTRACE("ERROR$¢º¢¹File:%s Line:%d -%s",__FILE__,__LINE__,lpmsg)
#define WINTRACE_THIS_WARNING(lpmsg) \
		::WINTRACE("WARNING$¢º¢¹File:%s Line:%d -%s",__FILE__,__LINE__,lpmsg)

#endif//_WINTRACE_H_