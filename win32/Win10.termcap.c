/*-
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/*
 * Win10.termcap.c
 * termcap emulation for Windows 10 now that it finally supports xterm-256color
 *
 */
#ifdef WINNT_NATIVE_UTF8_SUPPORT
#include "sh.h"


#define CAPABLEN	2

#define ISSPACE(c)  ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n')
#define ISDIGIT(x)  ((x) >= '0' && (x) <= '9')

#define FAKE_VISIBLE_BELL_ENTRY ":vb=ntvisb:"
#define FAKE_VISIBLE_BELL_SEQ  "ntvisb"

char		*capab;		/* the capability itself */
int
tgetent(char *bp, const char *name)
{
	int lins, cols,ignore;
	char linstr[256];

	USE(name);

	nt_getsize(&lins,&ignore,&cols);

	sprintf(linstr,":co#%d:li#%d",cols,lins);

	capab = bp;
	strcpy(bp,
	"x3|xterm-256-color:"
		":Co#256:"
		":pa#65536:"
		":AB=\\E[48;5;%dm:"
		":AF=\\E[38;5;%dm:"
		":XT:"
		":*6=\\EOF:"
		":@7=\\EOF:"
		":F1=\\E[23~:"
		":F2=\\E[24~:"
		":K2=\\EOE:"
		":Km=\\E[M:"
		":k1=\\EOP:"
		":k2=\\EOQ:"
		":k3=\\EOR:"
		":k4=\\EOS:"
		":k5=\\E[15~:"
		":k6=\\E[17~:"
		":k7=\\E[18~:"
		":k8=\\E[19~:"
		":k9=\\E[20~:"
		":k;=\\E[21~:"
		":kB=\\E[Z:"
		":kH=\\EOF:"
		":kI=\\E[2~:"
		":kN=\\E[6~:"
		":kP=\\E[5~:"
		":kd=\\EOB:"
		":kh=\\EOH:"
		":kl=\\EOD:"
		":kr=\\EOC:"
		":ku=\\EOA:"
		":am:bs:km:mi:ms:ut:xn:AX:kn#12");
		strcat(bp,linstr);
		//:co#80:li#24
	strcat(bp,":pa#64:"
		":AL=\\E[%dL:"
		":DC=\\E[%dP:"
		":DL=\\E[%dM:"
		":DO=\\E[%dB:"
		":LE=\\E[%dD:"
		":RI=\\E[%dC:"
		":UP=\\E[%dA:"
		":ac=``aaffggiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~:"
		":ae=\\E(B:"
		":al=\\E[L:"
		":as=\\E(0:"
		":bl=^G:"
		":cd=\\E[J:"
		":ce=\\E[K:"
		":cl=\\E[H\\E[2J:"
		":cm=\\E[%i%d;%dH:"
		":cr=\r:"
		":cs=\\E[%i%d;%dr:"
		":ct=\\E[3g:"
		":dc=\\E[P:"
		":dl=\\E[M:"
		":do=\n:"
		//":ei=\\E[4l:"
		":ho=\\E[H:"
		":ic=\\E[1@:"
		":IC=\\E[%d@:"
		//":im=\\E[4h:"
		":is=\\E[!p\\E[?3;4l\\E[4l\\E>\\E]104\007:"
		":kD=\\E[3~:"
		":kb=^H:"
		":kd=\n:"
		":ke=\\E[?1l\\E>:"
		":kl=^H:"
		":ks=\\E[?1h\\E=:"
		":le=^H:"
		":md=\\E[1m:"
		":me=\\E[m:"
		":ml=\\El:"
		":mr=\\E[7m:"
		":mu=\\Em:"
		":nd=\\E[C:"
		":nw=\r\n:"
		":op=\\E[39;49m:"
		":rc=\\E8:"
		":rs=\\E[!p\\E[?3;4l\\E[4l\\E>\\E]104\007:"
		":sc=\\E7:"
		":se=\\E[27m:"
		":sf=\n:"
		":so=\\E[7m:"
		":sr=\\EM:"
		":st=\\EH:"
		":ta=^I:"
		":te=\\E[?1049l:"
		":ti=\\E[?1049h:"
		":ue=\\E[24m:"
		":up=\\E[A:"
		":us=\\E[4m:"
		FAKE_VISIBLE_BELL_ENTRY //\\E7\\E[?5h\\E[?5l\\E8:"
		":ve=\\E[?12l\\E[?25h:"
		":vi=\\E[?25l:"
		":vs=\\E[?12;25h:"
		":kb=^H:"
	);
	return(1);
}
/*
 *	tgetnum - get the numeric terminal capability corresponding
 *	to id. Returns the value, -1 if invalid.
 */
int
tgetnum(const char *id)
{
	char	*cp;
	int	ret;

	if ((cp = capab) == NULL || id == NULL)
		return(-1);
	while (*++cp != ':')
		;
	for (++cp ; *cp ; cp++) {
		while (ISSPACE(*cp))
			cp++;
		if (strncmp(cp, id, CAPABLEN) == 0) {
			while (*cp && *cp != ':' && *cp != '#')
				cp++;
			if (*cp != '#')
				return(-1);
			for (ret = 0, cp++ ; *cp && ISDIGIT(*cp) ; cp++)
				ret = ret * 10 + *cp - '0';
			return(ret);
		}
		while (*cp && *cp != ':')
			cp++;
	}
	return(-1);
}

/*
 *	tgetflag - get the boolean flag corresponding to id. Returns -1
 *	if invalid, 0 if the flag is not in termcap entry, or 1 if it is
 *	present.
 */
int
tgetflag(const char *id)
{
	char	*cp;

	if ((cp = capab) == NULL || id == NULL)
		return(-1);
	while (*++cp != ':')
		;
	for (++cp ; *cp ; cp++) {
		while (ISSPACE(*cp))
			cp++;
		if (strncmp(cp, id, CAPABLEN) == 0)
			return(1);
		while (*cp && *cp != ':')
			cp++;
	}
	return(0);
}

/*
 *	tgetstr - get the string capability corresponding to id and place
 *	it in area (advancing area at same time). Expand escape sequences
 *	etc. Returns the string, or NULL if it can't do it.
 */
char *
tgetstr(const char *id, char **area)
{
	char	*cp;
	char	*ret;
	int	i;

	if ((cp = capab) == NULL || id == NULL)
		return(NULL);
	while (*++cp != ':')
		;
	for (++cp ; *cp ; cp++) {
		while (ISSPACE(*cp))
			cp++;
		if (strncmp(cp, id, CAPABLEN) == 0) {
			while (*cp && *cp != ':' && *cp != '=')
				cp++;
			if (*cp != '=')
				return(NULL);
			for (ret = *area, cp++; *cp && *cp != ':' ; 
				(*area)++, cp++)
				switch(*cp) {
				case '^' :
					**area = *++cp - '@'; /* fix (efth)*/
					break;
				case '\\' :
					switch(*++cp) {
					case 'E' :
						**area = CTL_ESC('\033');
						break;
					case 'n' :
						**area = '\n';
						break;
					case 'r' :
						**area = '\r';
						break;
					case 't' :
						**area = '\t';
						break;
					case 'b' :
						**area = '\b';
						break;
					case 'f' :
						**area = '\f';
						break;
					case '0' :
					case '1' :
					case '2' :
					case '3' :
						for (i=0 ; *cp && ISDIGIT(*cp) ;
							 cp++)
							i = i * 8 + *cp - '0';
						**area = (char)i;
						cp--;
						break;
					case '^' :
					case '\\' :
						**area = *cp;
						break;
					}
					break;
				default :
					**area = *cp;
				}
			*(*area)++ = '\0';
			return(ret);
		}
		while (*cp && *cp != ':')
			cp++;
	}
	return(NULL);
}

/*
 *	tgoto - given the cursor motion string cm, make up the string
 *	for the cursor to go to (destcol, destline), and return the string.
 *	Returns "OOPS" if something's gone wrong, or the string otherwise.
 */
char *
tgoto(const char *cm, int destcol, int destline)
{
	char	*rp;
	static char	ret[24];
	int		incr = 0;
	int 		argno = 0, numval;

	for (rp = ret ; *cm ; cm++) {
		switch(*cm) {
		case '%' :
			switch(*++cm) {
			case '+' :
				numval = (argno == 0 ? destline : destcol);
				argno = 1 - argno;
				*rp++ = (char)(numval + incr + *++cm);
				break;

			case '%' :
				*rp++ = '%';
				break;

			case 'i' :
				incr = 1;
				break;

			case 'd' :
				numval = (argno == 0 ? destline : destcol);
				numval += incr;
				argno = 1 - argno;
				if(numval >= 100) {
					*rp++ = (char)('0' + (numval/100));
					numval %= 100;
				}
				*rp++ = (char)('0' + (numval/10));
				*rp++ = '0' + (numval%10);
				break;

			case 'r' :
				argno = 1;
				break;
			}

			break;
		default :
			*rp++ = *cm;
		}
	}
	*rp = '\0';
	return(ret);
}

/*
 *	tputs - put the string cp out onto the terminal, using the function
 *	outc. This should do padding for the terminal, but I can't find a
 *	terminal that needs padding at the moment...
 */
void
tputs(const char *cp, int affcnt, void (*outc)(int))
{
	unsigned long delay = 0;
	USE(affcnt);

	if (cp == NULL)
		return;
	if(!stricmp(cp,FAKE_VISIBLE_BELL_SEQ))
	{
		NT_VisibleBell();
		return;
	}
	/* do any padding interpretation - left null for MINIX just now */
	for (delay = 0; *cp && ISDIGIT(*cp) ; cp++)
		delay = delay * 10 + *cp - '0';
	while (*cp)
		(*outc)(*cp++);
	return;
}
#else
#pragma warning(disable : 4206) //nonstandard extension used: translation unit is empty
#endif
