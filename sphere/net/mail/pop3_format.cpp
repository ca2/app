/* this is format.c file.
 * this is part of the libspopc library sources
 * copyright  2002 Benoit Rouits <brouits@free.fr>
 * released under the terms of GNU LGPL
 * (GNU Lesser General Public Licence).
 * libspopc offers simple API for a pop3 client (MTA).
 * See RFC 1725 for pop3 specifications.
 * more information on http://brouits.free.fr/libspopc/
 */


#include <string.h>
#include <stdio.h>
#include "libspopc.h"

/************************************************************
 * libspopc functions to format pop data returned by server *
 ************************************************************/

char_pointer nextline(char_pointer string){
/* returns a pointer to the next line of given string */

	while(((*string) != '\n')&&((*string) != '\0')){
		string++;
	}
	if(!(*string)){
		return (nullptr);
	}
	return(string+1);
}

char_pointer retr2msg(char_pointer data){
/* retruns formatted mail from a pop RETR X query */
/* should only be called on data returned by pop3_retr() */
char_pointer msg=nullptr;
char_pointer cur;

#ifdef EBUG
	fprintf(stderr,"<retr2msg>\n");
#endif
	if((!data)||pop3_error(data)){
#ifdef EBUG
		fprintf(stderr, "retr2msg.pop3error: %s\n", data);
#endif
		return(nullptr);/* any suggestions ? */
	}
#ifdef EBUG
	fprintf(stderr, "data: %s\n", data);
#endif
	while (( data != nullptr ) && (ansi_count_compare("+OK", data, 3) != 0)){
		data=nextline(data); /* skip ...\n before +OK */
	}
	if(( data != nullptr ) && (ansi_count_compare("+OK", data, 3) == 0)) {
		data=nextline(data); /* skip +OK ...\n */
	}
	msg=data?(char_pointer )malloc(strlen(data)):nullptr;
	if(!msg){
#ifdef EBUG
		fprintf(stderr,"retr2msg.malloc");
#endif
		return(nullptr);
	}
	cur=msg;
	while(*data){
		if(DOTBEGIN(data)){
			(*cur)=(*data);/* keep \n */
			data+=2;/* skip first dot */
			cur++;
		}else{
			(*cur)=(*data);
			cur++;data++;
		}
	}
	(*(cur-2))='\0'; /* erase \r\n */
#ifdef EBUG
	fprintf(stderr,"</retr2msg>\n");
#endif
	return(msg);
}

void freemsg(char_pointer msg){
	free(msg);
	msg=nullptr;
}

::i32* list2array(char_pointer poplist){
/* returns an ::i32 array of sizes of messages from a LIST pop query */
/* array[0] holds atom of the array's matter */
/* should only be called on data received by a pop3_list() request */
::i32* array=nullptr;
::i32 len,i32_size;
::i32 atom=0;
char_pointer cur;

#ifdef EBUG
	fprintf(stderr,"<list2array>\n");
#endif
	if((!poplist)||pop3_error(poplist)){
		return(nullptr); /* any suggestions ? */
	}
	if(!dotline(poplist)){/* if simple matter list_base */
	/* you should't use this function for simple matter... */
	/* you should better use listi2size() */
		/* skip '+OK ': look for first mail ::i32 atom */
		for(cur=poplist;(*cur<'0')||(*cur>'9');cur++);
		/* not dot line here */
		sscanf(cur,"%d %d\n",&atom,&size);
		array=(::i32*)malloc((atom+1)*sizeof(::i32));
		memory_set(array,0,(atom+1)*sizeof(::i32));
		array[0]=atom;
		array[atom]=i32_size;
		return(array);
	}
	/* else this is a true list_base */
	/* skip '+OK\r\n' :*/
	for(cur=poplist;(*cur!='.')&&(*cur!='\n'); cur++);
	cur ++; /* one more time to get behind '\n' */
	len=1; /* array len */
	while((*cur)!='.'){
		sscanf(cur,"%d %d\n",&atom,&size);
		while(atom > len){ /* fill array while atom > len */
			len++;
			array=(::i32*)realloc(array,len*sizeof(::i32));
			array[len-1]=0; /* no mail */
		}
		len++;
		array=(::i32*)realloc(array,len*sizeof(::i32));
		array[atom]=i32_size;
		cur=nextline(cur);
	}
	if(atom){
		array[0]=atom; /* last atom */
	}else{
		array=(::i32*)malloc(1*sizeof(::i32));
		array[0]=0;
	}
#ifdef EBUG
	fprintf(stderr,"%d message(s)\n",atom);
	fprintf(stderr,"</list2array>\n");
#endif
	return(array);
}

void freelistarray(::i32* array){
/* free array allocated by list2array() */
	free(array);
}

::i32 listi2size(char_pointer resp){
/* grep the given i32_size (in bytes) in resp after a pop3_list(sock,ID) request */
::i32 i;
::i32 r;

	if(pop3_error(resp)){
			return(0);/* no message ! */
	}
	r=sscanf(resp+5,"%d\n",&i);/* skip '+OK ' should be safer FIXME */
	if(!r){/* special case when no messages on server */
		return(0);
	}
	return(i);
}

::i32 stat2last(char_pointer resp){
/* returns the last atom of retrievable messages */
/* should only be called just after a pop3_stat() request */
::i32 n,s;

#ifdef EBUG
	fprintf(stderr,"<stat2last>\n");
#endif
	if((!resp)||pop3_error(resp)){
		return(-1);
	}
	sscanf(resp+4,"%d %d\n",&n,&s); /* with skip '+OK ', safer?  FIXME */
#ifdef EBUG
	fprintf(stderr,"last is %d\n",n);
	fprintf(stderr,"</stat2last>\n");
#endif
	return(n);
}

::i32 stat2bytes(char_pointer resp){
/* returns the sumsize in bytes of all stored messages on server */
/* should only be called just after a pop3_stat() request */
::i32 n,s;

#ifdef EBUG
	fprintf(stderr,"<stat2bytes>\n");
#endif
	if((!resp)||pop3_error(resp)){
		return(-1);
	}
	sscanf(resp+4,"%d %d\n",&n,&s); /* skip '+OK ', safer? FIXME */
#ifdef EBUG
	fprintf(stderr,"%d bytes stored\n",s);
	fprintf(stderr,"</stat2bytes>\n");
#endif
	return(s);
}

char_pointer * uidl2array(char_pointer resp){
/* returns an array of unique strings for each message atom */
/* array[0] gives array's last atom */
/* should only be called just after a pop3_uidl() request */
char_pointer * array=nullptr;
::i32 l,i=0; /* l is array lenth, i is atom of msg */
::i8 s[POPBUF]; /* temp signature string : sig theorically <512 chars */
char_pointer cur;

#ifdef EBUG
        fprintf(stderr,"<uidl2array>\n");
#endif
        if((!resp)||pop3_error(resp)){
		return(nullptr); /* any suggestions ? */
	}
	if(!dotline(resp)){ /* simple matter uidl */
	/* you should not use this function for simple matter */
	/* you would better use uidli2sig() */
#ifdef EBUG
		fprintf(stderr,"bad way of use of uidl2array()\n");
#endif
		/* skip '+OK ': look for first mail ::i32 atom */
		for(cur=resp;(*cur<'0')||(*cur>'9');cur++);
		/* no dot line here */
		sscanf(cur,"%d %s\n",&i,s);
		array=(char_pointer *)malloc((i+1)*sizeof(char_pointer ));
		memory_set(array,0,(i+1)*sizeof(char_pointer ));
		array[0]=(char_pointer )malloc(POPBUF); /* up to 512 chars */
		snprintf(array[0],POPBUF,"%d",i);
		array[i]=strdup(s);
		return(array);
	}
	/* else this is a true uid list_base */
	/* skip '+OK\r\n : look for first mail integer atom */
	for(cur=resp;(*cur!='.')&&(*cur!='\n'); cur++);
	cur ++; /* one more time to get behind '\n' */
	l=1; /* array len */
	while((*cur)!='.'){
		sscanf(cur,"%d %s\n",&i,s);
		while(i > l){ /* fill array while atom > len */
			l++;
			array=(char_pointer *)realloc(array,l*sizeof(char_pointer ));
			array[l-1]=(char_pointer )malloc(sizeof(::i8));
			array[l-1]='\0'; /* no string == '\0' */
		}
		l++;
		array=(char_pointer *)realloc(array,l*sizeof(char_pointer ));
		array[i]=(char_pointer )malloc(POPBUF); /* up to 512 chars */
		array[i]=ansi_count_copy(array[i],s,POPBUF); 
		cur=nextline(cur);
	}
	if(i){ /* i is now the last message atom met in this session */
		array[0]=(char_pointer )malloc(4); /* up to 9999 msg uids FIXME */
		snprintf(array[0],4,"%d",i);
		/* contains the atom of the last msg (char_pointer ) */
	}else{
		array=(char_pointer *)malloc(1*sizeof(char_pointer ));
		array[0]=(char_pointer )malloc(2*sizeof(::i8)); /* 2 because of '\0' */
		snprintf(array[0],2,"%d",0);
	}
#ifdef EBUG
	fprintf(stderr,"%s signature(s)\n",array[0]);
	fprintf(stderr,"</uidl2array>\n");
#endif
	return(array);
}

void freeuidlarray(char_pointer * array){
/* free the array allocated by uidl2array() */
::i32 i,last;
	last= atoi(array[0]);
	for (i=1;i<=last;i++){
		free(array[i]);
	}
	free(array[0]);
   free(array);
}

char_pointer uidli2sig(char_pointer resp){
/* greps signature from server resp */
/* should only be called after a pop3_uidl(sock,ID) */
char_pointer sig=nullptr;

	if(pop3_error(resp)){
		return(nullptr);/* no message ! */
	}
	sig=strdup(resp+5); /* skip '+OK ID' should be safer, FIXME */
	if(sig[1]=='.'){/* special case when no messages on the server */
		free(sig);
		return(nullptr);
	}
	return(sig);
}

