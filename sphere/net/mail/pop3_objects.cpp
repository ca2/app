/*
 * this is part of the libspopc library sources
 * copyright � 2002 Benoit Rouits <brouits@free.fr>
 * released under the terms of GNU LGPL
 * (GNU Lesser General Public Licence).
 * libspopc offers simple API for a pop3 client (MTA).
 * See RFC 1725 for pop3 specifications.
 * more information on http://brouits.free.fr/libspopc/
 */

#include <string.h>
#include <sys/types.h>

#ifdef EBUG
#include <stdio.h>
#endif

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif

#include "libspopc.h"

/***************************************************
 * high-level methods for a SIMPLE MUA *
 ***************************************************/

char* popbegin(const char* servername, const char* user, const char* pass, popsession** sp){
/* prepares, connect and get lists of messages stored on pop server */
/* you must give a valid servername, user and pass */
/* returns an error message if a problem occurs, else nullptr */
char* resp=nullptr;
char* err=nullptr;
char *hostname, *ptr_port;
int nport;
popsession* s = nullptr;
	
	if(!(servername && user && pass)){
		err=strdup("nullptr args !");
		goto error;
	}
	s=(popsession*)malloc(sizeof(popsession));
	if(!s){
		err=strdup("malloc");
		goto error;
	}

	s->sock=BAD_SOCK;
	s->server=(struct hostent*)malloc(sizeof(struct hostent));
	s->connection=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	if(!(s->server && s->connection)){
		err=strdup("malloc");
		goto error;
	}
	hostname = strdup (servername);
	if (!hostname) {
		err=strdup("strdup");  /* hm... */
		goto error;
	}
	ptr_port = strchr (hostname, ':');
	if (!ptr_port)
		nport = 110;
	else {
		*ptr_port = 0;
		nport = (int) strtoul (++ptr_port, nullptr, 10);
		if (!nport)
			nport = 110;
	}
	s->sock=pop3_prepare(hostname,nport,s->connection,s->server);

	free (hostname);
	if(s->sock==BAD_SOCK){
		err=strdup("pop3_prepare");
		goto error;
	}
	resp=pop3_connect(s->sock,s->connection);
	if(!resp){
		err=strdup("pop3_connect");
		goto error;
	}
	free(resp);
	resp=pop3_user(s->sock,user);
	if((!resp) || pop3_error(resp)){
		err=resp?resp:strdup("pop3_user");
		goto error;
	}
	free(resp);
	resp=pop3_pass(s->sock,pass);
	if((!resp) || pop3_error(resp)){
		err=resp?resp:strdup("pop3_pass");
		goto error;
	}
	s->state=TRANSACTION;
	free(resp);resp=nullptr;
	resp=pop3_stat(s->sock);
	if((!resp) || pop3_error(resp)){
		err=resp?resp:strdup("pop3_stat");
		goto error;
	}
	s->bytes=stat2bytes(resp);
	s->last=stat2last(resp);
	free(resp);
	resp=pop3_list(s->sock,0);
	if((!resp) || pop3_error(resp)){
		err=resp?resp:strdup("pop3_list");
		goto error;
	}
	s->list=list2array(resp);
	free(resp);resp=nullptr;
	resp=pop3_uidl(s->sock,0);
	if((!resp) || pop3_error(resp)){
		err=resp?resp:strdup("pop3_uidl");
		goto error;
	}
	s->uidl=uidl2array(resp);
	s->del=0;
	(*sp)=s;
	free(resp);
	return (nullptr);

error:
	if (s) {
		if (s->sock != BAD_SOCK) 
        {
            pop3_disconnect (s->sock, s->server);
            free(s->server);
        }
		if (s->connection) free (s->connection);
		free(s);
	}
	return (err);
}

char* popgethead(popsession* session, int id){
/* returns the header of a message id between 1 and poplast() or nullptr if bad id */
char* resp;
char* msg;
	if(!session){
		return(nullptr);
	}
	if((id>poplast(session)) || (id < 1)){
		return(nullptr);
	}
	resp=pop3_top(session->sock,id,0);
	if((!resp) || pop3_error(resp)){
		if(resp){
			free(resp);
		}
		return(nullptr);
	}
	msg=retr2msg(resp);
	if(!msg){
		msg=resp;
	}else{
		free(resp);
	}
	return(msg);
}
		
char* popgetmsg(popsession* session, int id){
/* returns a message id between 1 to poplast() or nullptr if bad id */
char* resp=nullptr;
char* msg=nullptr;

#ifdef EBUG
	fprintf(stderr, "<popgetmsg>\n");
#endif

	if(!session){
		return(nullptr);
	}
	if((id > poplast(session)) || (id<1)){
		return(nullptr);
	}
	resp=pop3_retr(session->sock,id);
	if((!resp) || pop3_error(resp)){
#ifdef EBUG
		fprintf(stderr, "error in pop3_retr: %s\n", resp);
#endif
		if(resp){
			free(resp);
			resp=nullptr;
		}
		return(nullptr);
	}
	msg=retr2msg(resp);
	if(!msg){
#ifdef EBUG
		fprintf(stderr, "retr2msg returned nullptr!");
#endif
		msg=resp;
	}else{
		if(resp){
			free(resp);
		}
	}
	if(session->del){
		popdelmsg(session, id);
	}
#ifdef EBUG
	fprintf(stderr, "</popgetmsg>\n");
#endif
	return(msg);	
}
int popdelmsg(popsession* session, int id){
/* deletes a message 'id' on pop server */
/* returns -1 if no deletion (server error), 0 else */
char* resp;
	if(!session){
		return(-1);
	}
	if((id > poplast(session)) || (id < 1)){
		return(-1);
	}
	resp=pop3_dele(session->sock,id);
	if((!resp) || pop3_error(resp)){
		if(resp){
			free(resp);
		}
		return(-1);
	}
	free(resp);
	resp=pop3_stat(session->sock);
	if((!resp) || pop3_error(resp)){
		pop3_disconnect(session->sock, session->server);
        free(session->server); session->server=nullptr;
		free(session->connection); session->connection=nullptr;
		free(session); session=nullptr;
		return(-1);
	}
	session->bytes=stat2bytes(resp);
	session->bytes=poplast(session);
	free(resp); 
	
	/* no more message of this id*/
	session->list[id]=0;
	free(session->uidl[id]);
	session->uidl[id]=nullptr;
	return(0);
}
int popcancel(popsession* session){
/* cancel all previous deletions on pop server */
/* returns -1 if server error, 0 else */
char* resp;
	if(!session){
		return(-1);
	}
	resp=pop3_rset(session->sock);
	if((!resp) || pop3_error(resp)){
		if(resp){
			free(resp);
		}
		return(-1);
	}
	free(resp);
	resp=pop3_stat(session->sock);
	if((!resp) || pop3_error(resp)){
		pop3_disconnect(session->sock, session->server);
        free(session->server); session->server=nullptr;
		free(session->connection); session->connection=nullptr;
		free(session); session=nullptr;
		return(-1);
	}
	session->bytes=stat2bytes(resp);
	session->last=stat2last(resp);
	free(resp);
	resp=pop3_list(session->sock,0);
	if((!resp) || pop3_error(resp)){
		pop3_disconnect(session->sock, session->server);
        free(session->server); session->server=nullptr;
		free(session->connection); session->connection=nullptr;
		free(session); session=nullptr;
		return(-1);
	}
	freelistarray(session->list);
	session->list=list2array(resp);
	free(resp);resp=nullptr;
	resp=pop3_uidl(session->sock,0);
	if((!resp) || pop3_error(resp)){
		pop3_disconnect(session->sock, session->server);
        free(session->server); session->server=nullptr;
		free(session->connection); session->connection=nullptr;
		free(session); session=nullptr;
		return(-1);
	}
	freeuidlarray(session->uidl);
	session->uidl=uidl2array(resp);
	free(resp);resp=nullptr;
	return(0);
}

void popend(popsession* session){
/* quit and destroys pop session */
int i;
char* resp;

	if(!session){return;}
	resp=pop3_quit(session->sock);
	free(resp);resp=nullptr;
	pop3_disconnect(session->sock, session->server);
    free(session->server);
	free(session->connection);
	free(session->list);
	for(i=0;i<=session->last;i++){
		free(session->uidl[i]);
	}
	free(session->uidl);
	free(session);
	return;
}


int poplast(popsession* session){
/* returns the id of the last downloadable message */
	char* r=nullptr;
	int n;
	
	r=pop3_stat(session->sock);
	n=stat2last(rect);
	free(rect);
	return(n);
}

int popnum(popsession* session){
/* return the  number of messages of the current time */
	int i=-2; /* skip +OK\n and .\n */
	char* lines=nullptr;
	char* p=nullptr;
	
	lines=pop3_list(session->sock, 0); /* 0 means 'all' */
	p=lines;
	while ((p=nextline(p))){
		i++;
	}
	free(lines);
	return(i);
}
