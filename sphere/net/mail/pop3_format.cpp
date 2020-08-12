/* this is format.c file.
 * this is part of the libspopc library sources
 * copyright � 2002 Benoit Rouits <brouits@free.fr>
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

char* nextline(char* string){
/* returns a pointer to the next line of given string */

	while(((*string) != '\n')&&((*string) != '\0')){
		string++;
	}
	if(!(*string)){
		return (nullptr);
	}
	return(string+1);
}

char* retr2msg(char* data){
/* retruns formatted mail from a pop RETR X query */
/* should only be called on data returned by pop3_retr() */
char* msg=nullptr;
char* cur;

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
	msg=data?(char*)malloc(strlen(data)):nullptr;
	if(!msg){
#ifdef EBUG
		perror("retr2msg.malloc");
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

void freemsg(char* msg){
	free(msg);
	msg=nullptr;
}

int* list2array(char* poplist){
/* returns an int array of sizes of messages from a LIST pop query */
/* array[0] holds id of the array's element */
/* should only be called on data received by a pop3_list() request */
int* array=nullptr;
int len,size;
int id=0;
char* cur;

#ifdef EBUG
	fprintf(stderr,"<list2array>\n");
#endif
	if((!poplist)||pop3_error(poplist)){
		return(nullptr); /* any suggestions ? */
	}
	if(!dotline(poplist)){/* if simple element list */
	/* you should't use this function for simple element... */
	/* you should better use listi2size() */
		/* skip '+OK ': look for first mail int id */
		for(cur=poplist;(*cur<'0')||(*cur>'9');cur++);
		/* not dot line here */
		sscanf(cur,"%d %d\n",&id,&size);
		array=(int*)malloc((id+1)*sizeof(int));
		__memset(array,0,(id+1)*sizeof(int));
		array[0]=id;
		array[id]=size;
		return(array);
	}
	/* else this is a true list */
	/* skip '+OK\r\n' :*/
	for(cur=poplist;(*cur!='.')&&(*cur!='\n'); cur++);
	cur ++; /* one more time to get behind '\n' */
	len=1; /* array len */
	while((*cur)!='.'){
		sscanf(cur,"%d %d\n",&id,&size);
		while(id > len){ /* fill array while id > len */
			len++;
			array=(int*)realloc(array,len*sizeof(int));
			array[len-1]=0; /* no mail */
		}
		len++;
		array=(int*)realloc(array,len*sizeof(int));
		array[id]=size;
		cur=nextline(cur);
	}
	if(id){
		array[0]=id; /* last id */
	}else{
		array=(int*)malloc(1*sizeof(int));
		array[0]=0;
	}
#ifdef EBUG
	fprintf(stderr,"%d message(s)\n",id);
	fprintf(stderr,"</list2array>\n");
#endif
	return(array);
}

void freelistarray(int* array){
/* free array allocated by list2array() */
	free(array);
}

int listi2size(char* resp){
/* grep the given size (in bytes) in resp after a pop3_list(sock,ID) request */
int i;
int r;

	if(pop3_error(resp)){
			return(0);/* no message ! */
	}
	r=sscanf(resp+5,"%d\n",&i);/* skip '+OK ' should be safer FIXME */
	if(!r){/* special case when no messages on server */
		return(0);
	}
	return(i);
}

int stat2last(char* resp){
/* returns the last id of retrievable messages */
/* should only be called just after a pop3_stat() request */
int n,s;

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

int stat2bytes(char* resp){
/* returns the sumsize in bytes of all stored messages on server */
/* should only be called just after a pop3_stat() request */
int n,s;

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

char** uidl2array(char* resp){
/* returns an array of unique strings for each message id */
/* array[0] gives array's last id */
/* should only be called just after a pop3_uidl() request */
char** array=nullptr;
int l,i=0; /* l is array lenth, i is id of msg */
char s[POPBUF]; /* temp signature string : sig theorically <512 chars */
char* cur;

#ifdef EBUG
        fprintf(stderr,"<uidl2array>\n");
#endif
        if((!resp)||pop3_error(resp)){
		return(nullptr); /* any suggestions ? */
	}
	if(!dotline(resp)){ /* simple element uidl */
	/* you should not use this function for simple element */
	/* you would better use uidli2sig() */
#ifdef EBUG
		fprintf(stderr,"bad way of use of uidl2array()\n");
#endif
		/* skip '+OK ': look for first mail int id */
		for(cur=resp;(*cur<'0')||(*cur>'9');cur++);
		/* no dot line here */
		sscanf(cur,"%d %s\n",&i,s);
		array=(char**)malloc((i+1)*sizeof(char*));
		__memset(array,0,(i+1)*sizeof(char*));
		array[0]=(char*)malloc(POPBUF); /* up to 512 chars */
		snprintf(array[0],POPBUF,"%d",i);
		array[i]=strdup(s);
		return(array);
	}
	/* else this is a true uid list */
	/* skip '+OK\r\n : look for first mail integer id */
	for(cur=resp;(*cur!='.')&&(*cur!='\n'); cur++);
	cur ++; /* one more time to get behind '\n' */
	l=1; /* array len */
	while((*cur)!='.'){
		sscanf(cur,"%d %s\n",&i,s);
		while(i > l){ /* fill array while id > len */
			l++;
			array=(char**)realloc(array,l*sizeof(char*));
			array[l-1]=(char*)malloc(sizeof(char));
			array[l-1]='\0'; /* no string == '\0' */
		}
		l++;
		array=(char**)realloc(array,l*sizeof(char*));
		array[i]=(char*)malloc(POPBUF); /* up to 512 chars */
		array[i]=ansi_count_copy(array[i],s,POPBUF); 
		cur=nextline(cur);
	}
	if(i){ /* i is now the last message id met in this session */
		array[0]=(char*)malloc(4); /* up to 9999 msg uids FIXME */
		snprintf(array[0],4,"%d",i);
		/* contains the id of the last msg (char*) */
	}else{
		array=(char**)malloc(1*sizeof(char*));
		array[0]=(char*)malloc(2*sizeof(char)); /* 2 because of '\0' */
		snprintf(array[0],2,"%d",0);
	}
#ifdef EBUG
	fprintf(stderr,"%s signature(s)\n",array[0]);
	fprintf(stderr,"</uidl2array>\n");
#endif
	return(array);
}

void freeuidlarray(char** array){
/* free the array allocated by uidl2array() */
int i,last;
	last= atoi(array[0]);
	for (i=1;i<=last;i++){
		free(array[i]);
	}
	free(array[0]);
   free(array);
}

char* uidli2sig(char* resp){
/* greps signature from server resp */
/* should only be called after a pop3_uidl(sock,ID) */
char* sig=nullptr;

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

