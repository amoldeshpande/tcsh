#ifndef VERSION_H
#define VERSION_H

/* remember to change both instance of the version -amol */

#define NTBASEVERSTR ",nt-rev-8.10" 

#ifdef WINNT_NATIVE_UTF8_SUPPORT
#define NTUTF8STR ",utf8,"
#else
#define NTUTF8STR ""
#endif // WINNT_NATIVE_UTF8_SUPPORT

#ifdef NTDBG
#define LOCALSTR  NTUTF8STR NTBASEVERSTR "-debug"
#endif //NTDBG

#endif VERSION_H
