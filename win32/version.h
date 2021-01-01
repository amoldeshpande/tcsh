#ifndef VERSION_H
#define VERSION_H

/* remember to change both instance of the version -amol */

#define NTBASEVERSTR ",nt-rev-9.00" 

#ifdef WINNT_NATIVE_UTF8_SUPPORT
#define NTUTF8STR ",utf8"
#else
#define NTUTF8STR 
#endif // WINNT_NATIVE_UTF8_SUPPORT

#ifdef NTDBG
#define LOCAL_DEBUG_STR "-debug"
#else
#define LOCAL_DEBUG_STR 
#endif //NTDBG

#define LOCALSTR  NTUTF8STR NTBASEVERSTR LOCAL_DEBUG_STR

#endif VERSION_H
