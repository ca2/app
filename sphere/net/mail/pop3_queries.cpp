#include "framework.h"


#ifdef USE_SSL

::i32 pop3_recv (pop3sock_t sock, char_pointer buf, ::i32 len){
	return sock->ssl?SSL_read(sock->ssl,buf,len):recv(sock->sock,buf,len,0);
}


::i32 pop3_send (pop3sock_t sock, char_pointer buf, ::i32 len){
	return sock->ssl?SSL_write(sock->ssl,buf,len):send(sock->sock,buf,len,0);
}

#else

::i32 pop3_recv (pop3sock_t sock, char_pointer buf, ::i32 len){
	return recv(sock,buf,len,0);
}

::i32 pop3_send (pop3sock_t sock, char_pointer buf, ::i32 len){
	return send(sock,buf,len,0);
}

#endif

/* enable timeout sockets with 'select' */
::i32 timedrselect(fd_set *rfds, ::i32 maximum, ::i32 time){
struct timeval timeout;
timeout.tv_sec = time;
timeout.tv_usec = 0;

   if(select(maximum, rfds, nullptr, nullptr, &timeout) <= 0){
      fprintf(stderr,"timeout reached\n");
      return(1);
   }
   return(0);
}

/* prepare the socket to be read */
::i32 timedrread(pop3sock_t sock, ::i32 time) {
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
char_pointer recv_rest(pop3sock_t sock, char_pointer buf, ::i32 cs, ::i32 bs);
/* recv end of data through sock, buffer is of bs bytes, already filled by cs */
/* end of data is assumed when data has a "\r\n.\r\n" string */

char_pointer pop3_query(pop3sock_t sock, const ::string & query){
/* performs a simple pop query and returns server's <512 bytes response */
::i32 r;
::i32 bytes=0;
char_pointer buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_query>\n");
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,(char_pointer )query,strlen(query));
	if(r==-1){
		fprintf(stderr,"pop3_query.send");
		return(nullptr);
	}
	buf=(char_pointer )malloc(POPBUF +1); /* 512 chars + '\0' */ /* FIXME: free when ? */
	if(!buf){
		fprintf(stderr,"pop3_query.malloc");
		return(nullptr);
	}
	/* memory_set(buf,0,POPBUF); SUGGEST: should not be an obligation */
	bytes=pop3_recv(sock,buf,POPBUF);
	while((buf[bytes-2]!='\r') && (buf[bytes-1]!='\n')){
		r=pop3_recv(sock,buf+bytes,POPBUF-bytes);
		if(r<=0){
			fprintf(stderr,"pop3_query.recv");
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

char_pointer pop3_user(pop3sock_t sock, const ::scoped_string & scopedstrName){
/* performs "USER" pop query and returns server's <512 bytes response */
::i8 query[POPBUF]; /* total "USER ****your_name****\n" is < 512  */

	snprintf(query,POPBUF,"USER %s\r\n",name);
	return(pop3_query(sock,query));
}

char_pointer pop3_pass(pop3sock_t sock, const ::scoped_string & scopedstrw){
/* performs "PASS" pop query and return server's <512 bytes response */
::i8 query[POPBUF]; /* total "PASS ****your_pass****\n" is <512 */

	snprintf(query,POPBUF,"PASS %s\r\n",pw);
	return(pop3_query(sock,query));
}

char_pointer pop3_quit(pop3sock_t sock){
/* performs "QUIT" pop query and returns server's <512 bytes response */
::i8 query[]="QUIT\r\n";

	return(pop3_query(sock,query));
}

char_pointer pop3_stat(pop3sock_t sock){
/* performs "STAT" pop query and returns server's <512 bytes response */
::i8 query[]="STAT\r\n";

	return(pop3_query(sock,query));
}

char_pointer recv_rest(pop3sock_t sock, char_pointer buf, ::i32 cs, ::i32 bs){
/* recv rest of data through sock, given a cs  pre-filled buffer ::f64_size of bs.
* end of data is assumed when data has a "\r\n.\r\n" string
* recv() is TCPBUFLEN  bytes stepped, SUGGEST any good value...
* Warning: after calling this function, buf must never be used again
* -not even for a free(buf)- since it may be reallocated. use the return
* value instead (usage example: buf=recv_rest(sock,buf,cs,bs); free(buf); */
char_pointer ret = nullptr;
char_pointer cur = nullptr; /* current position ready to receive */
::i32 tr;    /* total received */
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
		ret=(char_pointer )realloc(buf,bs+1);
		if(!ret){
			fprintf(stderr,"recv_rest.realloc");
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
			ret = (char_pointer )realloc(buf, (bs *=2) +1);
		}
		if(!ret){
			fprintf(stderr,"recv_rest.realloc");
			return(buf);
		}
		buf = ret;
		cur = buf + tr;
		if(timedrread(sock, SOCKET_TIMEOUT)){
			cs=pop3_recv(sock, cur, TCPBUFLEN);
			if (cs < 0){ /* socket error */
				fprintf(stderr,"Socket Error");
				free(buf);
				return(nullptr);
			} else if (cs == 0){ /* connection closed */
				fprintf(stderr,"Connection closed by peer");
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
      
char_pointer pop3_list(pop3sock_t sock, ::i32 atom){
/* performs a "LIST" pop query and returns server's (long) response */
::i32 r;
::i8 query[POPBUF]; /* total query "LIST ID\n" string is < 512 */
char_pointer buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_list>\n");
#endif
	if(atom>0){
		snprintf(query,POPBUF,"LIST %d\r\n",atom);
	}else{
		snprintf(query,POPBUF,"LIST\r\n");
	}
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		fprintf(stderr,"pop3_list.send");
		return(nullptr);
	}
	/* now prepare a first ::i16 512 bytes recv() */
	/* it might be now enough for recv() from "LIST X" */
	buf=(char_pointer )malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		fprintf(stderr,"pop3_list.malloc");
		return(nullptr);
	}
	r=pop3_recv(sock,buf,POPBUF);
   if(r < 0){ /* socket error */
      fprintf(stderr,"Socket Error");
      free(buf);
      return(nullptr);
   }
   buf[r]='\0';
	if(atom>0){/* +OK atom i32_size */
		return(buf); /* 512 bytes are enough as say RFC 1939 */
	}
	/* else : +OK X messages (YYY octets)\n atom i32_size\n... */
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


char_pointer pop3_retr(pop3sock_t sock, ::i32 atom){
::i32 r;
::i8 query[POPBUF];
char_pointer buf;

#ifdef EBUG
   fprintf(stderr, "<pop3_retr>\n");
#endif
   snprintf(query, POPBUF, "RETR %d\r\n", atom);
   r=pop3_send(sock, query, strlen(query));
   if(r == -1){
      fprintf(stderr,"pop3_retr.send");
      return(nullptr);
   }
   buf=(char_pointer )malloc(POPBUF +1);/* 512 chars + '\0' */
   if(!buf) {
      fprintf(stderr,"pop3_retr.malloc");
      return(nullptr);
   }
   if(timedrread(sock, SOCKET_TIMEOUT)){
      r=pop3_recv(sock, buf, POPBUF); 
      if(r < 0){ /* socket error */
         fprintf(stderr,"Socket Error");
         free(buf);
         return(nullptr);
      }
   }else{
      fprintf(stderr,"timeout reached\n");
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
      fprintf(stderr,"nothing returned\n");
      free(buf);
      return(nullptr);
   }
}

char_pointer pop3_dele(pop3sock_t sock, ::i32 atom){
/* performs a "DELE" pop query and returns server's <512 bytes response */
::i8 query[POPBUF]; /* total "DELE X\n" string < 512 */

	if(atom<=0){
#ifdef EBUG
		fprintf(stderr,"pop3_dele : won't delete %d\n",atom);
#endif
		return(nullptr);
	}
	snprintf(query,POPBUF,"DELE %d\r\n",atom);
	return(pop3_query(sock,query));
}

char_pointer pop3_noop(pop3sock_t sock){
/* performs a "NOOP" pop query and returns server's <512 bytes response */
::i8 query[]="NOOP\r\n";
	
	return(pop3_query(sock,query));
}

char_pointer pop3_rset(pop3sock_t sock){
/* performs a "RSET" pop query and returns server's <512 bytes response */
::i8 query[]="RSET\r\n";

	return(pop3_query(sock,query));
}

char_pointer pop3_top(pop3sock_t sock, ::i32 atom, ::i32 lines){
/* performs a "TOP" pop query and returns server's (long) response */
::i32 r;
::i8 query[POPBUF]; /* total "TOP X Y\n" is < 512 */
char_pointer buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_top>\n");
#endif
	snprintf(query,POPBUF,"TOP %d %d\r\n",atom,lines);
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		fprintf(stderr,"pop3_top.send");
		return(nullptr);
	}
	/* prepare first recv() of 512 bytes */
	buf=(char_pointer )malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		fprintf(stderr,"pop3_top.malloc");
		return(nullptr);
	}
/*	memory_set(buf,0,POPBUG); SUGGEST: no obligation */
	r=pop3_recv(sock,buf,POPBUF);
   if(r < 0){ /* socket error */
      fprintf(stderr,"Socket Error");
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

char_pointer pop3_uidl(pop3sock_t sock, ::i32 atom){
/* performs a "UIDL" pop query and returns server's (long) response */
::i32 r;
::i8 query[POPBUF]; /* total "UIDL X\n" is < 512 */
char_pointer buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_uidl>\n");
#endif
	if(atom>0){
		snprintf(query,POPBUF,"UIDL %d\r\n",atom);
	}else{
		snprintf(query,POPBUF,"UIDL\r\n");
	}
#ifdef EBUG
	fprintf(stderr,"send %s",query);
#endif
	r=pop3_send(sock,query,strlen(query));
	if(r==-1){
		fprintf(stderr,"pop3_uidl.send");
		return(nullptr);
	}
	/* prepare first 512 bytes for recv() */
	/* i hope this is also enough for the 'one line' ::i16 response */
	buf=(char_pointer )malloc(POPBUF +1); /* 512 chars + '\0' */
	if(!buf){
		fprintf(stderr,"pop3_uidl.malloc");
		return(nullptr);
	}
	memory_set(buf,0,POPBUF);
	r=pop3_recv(sock,buf,POPBUF);
   if (r < 0){ /* socket errorr */
      fprintf(stderr,"Socket Error");
      free(buf);
      return(nullptr);
   }
   buf[r]='\0';
   
	if(atom>0){/* +OK atom sig */
#ifdef EBUG
		if(pop3_error(buf)){
			fprintf(stderr,"%s",buf);
		}
#endif
		/* anyway, we return the ::i16 buf, error or not */
		return(buf); /* 512 are enough as say RFC 1939 */
	}
	/* else : +OK\n atom sig\nid sig\nid sig\n... */
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

char_pointer pop3_apop(pop3sock_t sock, const ::scoped_string & scopedstrName, const ::string & digest){
/* performs a "APOP" secure query and returns server's <512 bytes response */
::i8 query[POPBUF]; /* total "APOP name digest\n" is < 512 */

	snprintf(query,POPBUF,"APOP %s %s\r\n",name,digest);
	return(pop3_query(sock,query));
}
