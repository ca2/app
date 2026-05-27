/* this is parsing.c file.
 * this is part of the libspopc library sources
 * copyright  2002 Benoit Rouits <brouits@free.fr>
 * released under the terms of GNU LGPL
 * (GNU Lesser General Public Licence).
 * libspopc offers simple API for a pop3 client (MTA).
 * See RFC 1725 for pop3 specifications.
 * more information on http://brouits.free.fr/libspopc/
 */

#include <string.h>
#ifdef EBUG
#include <stdio.h>
#endif
#include "libspopc.h"

::i32 dotline(char_pointer buf){
/* returns 1 if buf contains a "\n.\n" or "\n.\r" substring */
char_pointer ptr;

#ifdef EBUG
	fprintf(stderr, "<dotline>\n");
#endif
	if(!buf){
#ifdef EBUG
		fprintf(stderr,"empty buf ?\n");
#endif
		return(0);
	}
	ptr=buf;
	while((ptr=strchr(ptr,'.'))){
		char_pointer dl=ptr-2;/* 2 characters before the dot */
		/* RFC1939 specifies that the termination line is "CRLF.CRLF" */
		if((dl[0] == '\r') && (dl[1] == '\n') && (dl[3] == '\r') && (dl[4] == '\n')){
#ifdef EBUG
			fprintf(stderr, "found dotline: %s\n", ptr);
#endif
			return(1);
		}
		ptr++;
	}
#ifdef EBUG
	fprintf(stderr,"</dotline>\n");
#endif
	return(0);
}
            
::i32 pop3_error(char_pointer string){
/* returns 1 if pop server error reply (i.e : -ERR ...) */
	return(string?(!ansi_count_compare(string,"-ERR",(size_t)4)):1);
}
