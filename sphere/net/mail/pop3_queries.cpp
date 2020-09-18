#include "StdAfx.h"


#ifdef USE_SSL

int pop3_recv (pop3sock_t sock, char* buf, int len){
	return sock->ssl?SSL_read(sock->ssl,buf,len):recv(sock->sock,buf,len,0);
}


int pop3_send (pop3sock_t sock, char* buf, int len){
	return sock->ssl?SSL_write(sock->ssl,buf,len):send(sock->sock,buf,len,0);
}

#else

int pop3_recv (pop3sock_t sock, char* buf, int len){
	return recv(sock,buf,len,0);
}

int pop3_send (pop3sock_t sock, char* buf, int len){
	return send(sock,buf,len,0);
}

#endif

/* enable timeout sockets with 'select' */
int timedrselect(fd_set *rfds, int max, int time){
struct timeval timeout;
timeout.tv_sec = time;
timeout.tv_usec = 0;

   if(select(max, rfds, nullptr, nullptr, &timeout) <= 0){
      perror("timeout reached\n");
      return(1);
   }
   return(0);
}

/* prepare the socket to be read */
int timedrread(pop3sock_t sock, int time) {
#if 0
fd_set rfds;
#ifdef USE_SSL
#define SOCK (sock->sock)
   if (sock->ssl) return 1;
#else
#define SOCK (sock)
#endif
   FD_ZERO(&rfds);
   FD_SET(SOCK, &rfds);
   timedrselect(&rfds, SOCK + 1, time);
   return FD_ISSET(SOCK, &rfds);
#else
   sock = 0; time=0;
   return 1;
#endif
}

/* this function is not in the API, just for libspopc internal use: */
char* recv_rest(pop3sock_t sock, char* buf, int cs, int bs);
/* recv end of data through sock, buffer is of bs bytes, already filled by cs */
/* end of data is assumed when data has a "\r\n.\r\n" string */

char* pop3_query(pop3sock_t sock, const char* query){
/* performs a simple pop query and returns server's <512 bytes response */
int r;
int bytes=0;
char* buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_query>\n");
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,(char *)query,strlen(query));
	if(r==-1){
		perror("pop3_query.send");
		return(nullptr);
	}
	buf=(char*)malloc(POPBUF +1); /* 512 chars + '\0' */ /* FIXME: free when ? */
	if(!buf){
		perror("pop3_query.malloc");
		return(nullptr);
	}
	/* __memset(buf,0,POPBUF); SUGGEST: should not be an obligation */
	bytes=pop3_recv(sock,buf,POPBUF);
	while((buf[bytes-2]!='\r') && (buf[bytes-1]!='\n')){
		r=pop3_recv(sock,buf+bytes,POPBUF-bytes);
		if(r<=0){
			perror("pop3_query.recv");
			free(buf);
			return(nullptr);
		}
		bytes+=r;
	}
	buf[bytes]='\0';
#ifdef EBUG
	fprintf(stderr,"recv %s",buf);
	fprintf(stderr,"</pop3_query>\n");
#endif
	return(buf);
}

char* pop3_user(pop3sock_t sock, const char* name){
/* performs "USER" pop query and returns server's <512 bytes response */
char query[POPBUF]; /* total "USER ****your_name****\n" is < 512  */

	snprintf(query,POPBUF,"USER %s\r\n",name);
	return(pop3_query(sock,query));
}

char* pop3_pass(pop3sock_t sock, const char* pw){
/* performs "PASS" pop query and return server's <512 bytes response */
char query[POPBUF]; /* total "PASS ****your_pass****\n" is <512 */

	snprintf(query,POPBUF,"PASS %s\r\n",pw);
	return(pop3_query(sock,query));
}

char* pop3_quit(pop3sock_t sock){
/* performs "QUIT" pop query and returns server's <512 bytes response */
char query[]="QUIT\r\n";

	return(pop3_query(sock,query));
}

char* pop3_stat(pop3sock_t sock){
/* performs "STAT" pop query and returns server's <512 bytes response */
char query[]="STAT\r\n";

	return(pop3_query(sock,query));
}

char* recv_rest(pop3sock_t sock, char* buf, int cs, int bs){
/* recv rest of data through sock, given a cs  pre-filled buffer sized of bs.
* end of data is assumed when data has a "\r\n.\r\n" string
* recv() is TCPBUFLEN  bytes stepped, SUGGEST any good value...
* Warning: after calling this function, buf must never be used again
* -not even for a free(buf)- since it may be reallocated. use the return
* value instead (usage example: buf=recv_rest(sock,buf,cs,bs); free(buf); */
char* ret = nullptr;
char* cur = nullptr; /* current position ready to receive */
int tr;    /* total received */
#ifdef EBUG
	fprintf(stderr,"<recv_rest>\n");
#endif
	if(!buf){
#ifdef EBUG
		fprintf(stderr,"was given nullptr buf !\n");
#endif
		free(buf);
		return(nullptr);
	}
	tr = cs;
	cur = buf;
	if(cs == bs){
		ret=(char*)realloc(buf,bs+1);
		if(!ret){
			perror("recv_rest.realloc");
			return buf;
		}
        	cur = buf = ret;
	}
	cur[tr]='\0';
	while(!dotline(cur)){
#ifdef EBUG
		fprintf(stderr, "no dotline in: %s\n", cur);
#endif
		if (tr >= (bs - TCPBUFLEN)){
#ifdef EBUG
			fprintf(stderr,"realloc bs*2 + 1 == %d\n", bs*2 +1);
#endif
			ret = (char*)realloc(buf, (bs *=2) +1);
		}
		if(!ret){
			perror("recv_rest.realloc");
			return(buf);
		}
		buf = ret;
		cur = buf + tr;
		if(timedrread(sock, SOCKET_TIMEOUT)){
			cs=pop3_recv(sock, cur, TCPBUFLEN);
			if (cs < 0){ /* socket error */
				perror("Socket Error");
				free(buf);
				return(nullptr);
			} else if (cs == 0){ /* connection closed */
				perror("Connection closed by peer");
				free(buf);
				return(nullptr);
			}
		}else{
			printf("timeout reached\n");
			return(buf);
		}
		if (cs > 0){
			tr+=cs;
			cur[cs] = '\0';
		}else{
			cs = 0;
		}
	}
	cur[cs] = '\0';
#ifdef EBUG
	fprintf(stderr, "total recv %d bytes\n", tr);
	fprintf(stderr, "</recv_rest>\n");
#endif
	return(buf);
}
      
char* pop3_list(pop3sock_t sock, int id){
/* performs a "LIST" pop query and returns server's (long) response */
int r;
char query[POPBUF]; /* total query "LIST ID\n" string is < 512 */
char* buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_list>\n");
#endif
	if(id>0){
		snprintf(query,POPBUF,"LIST %d\r\n",id);
	}else{
		snprintf(query,POPBUF,"LIST\r\n");
	}
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		perror("pop3_list.send");
		return(nullptr);
	}
	/* now prepare a first short 512 bytes recv() */
	/* it might be now enough for recv() from "LIST X" */
	buf=(char*)malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		perror("pop3_list.malloc");
		return(nullptr);
	}
	r=pop3_recv(sock,buf,POPBUF);
   if(r < 0){ /* socket error */
      perror("Socket Error");
      free(buf);
      return(nullptr);
   }
   buf[r]='\0';
	if(id>0){/* +OK id size */
		return(buf); /* 512 bytes are enough as say RFC 1939 */
	}
	/* else : +OK X messages (YYY octets)\n id size\n... */
	if(pop3_error(buf)){
#ifdef EBUG
		fprintf(stderr,"%s",buf);
#endif
		return(buf);
	}
#ifdef EBUG
	fprintf(stderr,"</>\n");
#endif
	return(recv_rest(sock,buf,r,POPBUF));
}


char* pop3_retr(pop3sock_t sock, int id){
int r;
char query[POPBUF];
char *buf;

#ifdef EBUG
   fprintf(stderr, "<pop3_retr>\n");
#endif
   snprintf(query, POPBUF, "RETR %d\r\n", id);
   r=pop3_send(sock, query, strlen(query));
   if(r == -1){
      perror("pop3_retr.send");
      return(nullptr);
   }
   buf=(char*)malloc(POPBUF +1);/* 512 chars + '\0' */
   if(!buf) {
      perror("pop3_retr.malloc");
      return(nullptr);
   }
   if(timedrread(sock, SOCKET_TIMEOUT)){
      r=pop3_recv(sock, buf, POPBUF); 
      if(r < 0){ /* socket error */
         perror("Socket Error");
         free(buf);
         return(nullptr);
      }
   }else{
      perror("timeout reached\n");
      free(buf);
      return(nullptr);
   }
   if(pop3_error(buf)){
      buf[r+1] = '\0';
      return(buf); /* 512 are enough as say RFC 1939 */
   }
#ifdef EBUG
   fprintf(stderr,"</>\n");
#endif
   if (r > 0) {
      return(recv_rest(sock, buf, r, POPBUF));
   }else{
      perror("nothing returned\n");
      free(buf);
      return(nullptr);
   }
}

char* pop3_dele(pop3sock_t sock, int id){
/* performs a "DELE" pop query and returns server's <512 bytes response */
char query[POPBUF]; /* total "DELE X\n" string < 512 */

	if(id<=0){
#ifdef EBUG
		fprintf(stderr,"pop3_dele : won't delete %d\n",id);
#endif
		return(nullptr);
	}
	snprintf(query,POPBUF,"DELE %d\r\n",id);
	return(pop3_query(sock,query));
}

char* pop3_noop(pop3sock_t sock){
/* performs a "NOOP" pop query and returns server's <512 bytes response */
char query[]="NOOP\r\n";
	
	return(pop3_query(sock,query));
}

char* pop3_rset(pop3sock_t sock){
/* performs a "RSET" pop query and returns server's <512 bytes response */
char query[]="RSET\r\n";

	return(pop3_query(sock,query));
}

char* pop3_top(pop3sock_t sock, int id, int lines){
/* performs a "TOP" pop query and returns server's (long) response */
int r;
char query[POPBUF]; /* total "TOP X Y\n" is < 512 */
char* buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_top>\n");
#endif
	snprintf(query,POPBUF,"TOP %d %d\r\n",id,lines);
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		perror("pop3_top.send");
		return(nullptr);
	}
	/* prepare first recv() of 512 bytes */
	buf=(char*)malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		perror("pop3_top.malloc");
		return(nullptr);
	}
/*	__memset(buf,0,POPBUG); SUGGEST: no obligation */
	r=pop3_recv(sock,buf,POPBUF);
   if(r < 0){ /* socket error */
      perror("Socket Error");
      free(buf);
      return(nullptr);
   }
   buf[r]='\0';
   
	if(pop3_error(buf)){
#ifdef EBUG
		fprintf(stderr,"%s",buf);
#endif
		return(buf); /* 512 bytes are enough as say RFC 1939 */
	}
#ifdef EBUG
	fprintf(stderr,"</>\n");
#endif
	return(recv_rest(sock,buf,r,POPBUF));
}

char* pop3_uidl(pop3sock_t sock, int id){
/* performs a "UIDL" pop query and returns server's (long) response */
int r;
char query[POPBUF]; /* total "UIDL X\n" is < 512 */
char* buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_uidl>\n");
#endif
	if(id>0){
		snprintf(query,POPBUF,"UIDL %d\r\n",id);
	}else{
		snprintf(query,POPBUF,"UIDL\r\n");
	}
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		perror("pop3_uidl.send");
		return(nullptr);
	}
	/* prepare first 512 bytes for recv() */
	/* i hope this is also enough for the 'one line' short response */
	buf=(char*)malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		perror("pop3_uidl.malloc");
		return(nullptr);
	}
	__memset(buf,0,POPBUF);
	r=pop3_recv(sock,buf,POPBUF);
   if (r < 0){ /* socket errorr */
      perror("Socket Error");
      free(buf);
      return(nullptr);
   }
   buf[r]='\0';
   
	if(id>0){/* +OK id sig */
#ifdef EBUG
		if(pop3_error(buf)){
			fprintf(stderr,"%s",buf);
		}
#endif
		/* anyway, we return the short buf, error or not */
		return(buf); /* 512 are enough as say RFC 1939 */
	}
	/* else : +OK\n id sig\nid sig\nid sig\n... */
	if(pop3_error(buf)){
#ifdef EBUG
		fprintf(stderr,"%s",buf);
#endif
		return(buf); /* hope error msg were < 512 bytes */
	}
#ifdef EBUG
	fprintf(stderr,"buf=%s</>\n",buf);
#endif
	return(recv_rest(sock,buf,r,POPBUF));
}

char* pop3_apop(pop3sock_t sock, const char* name, const char* digest){
/* performs a "APOP" secure query and returns server's <512 bytes response */
char query[POPBUF]; /* total "APOP name digest\n" is < 512 */

	snprintf(query,POPBUF,"APOP %s %s\r\n",name,digest);
	return(pop3_query(sock,query));
}
