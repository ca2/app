/*
 *  Http put/get mini lib
 *  written by L. Demailly
 *  (c) 1998 Laurent Demailly - http://www.demailly.com/~dl/
 *  (c) 1996 Observatoire de Paris - Meudon - France
 *  see LICENSE for terms, conditions and DISCLAIMER OF ALL WARRANTIES
 *
 * $Id: http_lib.c,v 3.5 1998/09/23 06:19:15 dl Exp $
 *
 * Description : Use http protocol, connects to server to echange data
 *
 * $Log: http_lib.c,v $
 * Revision 3.5  1998/09/23 06:19:15  dl
 * portability and http 1.x (1.1 and later) compatibility
 *
 * Revision 3.4  1998/09/23 05:44:27  dl
 * added support for HTTP/1.x answers
 *
 * Revision 3.3  1996/04/25 19:07:22  dl
 * using intermediate variable for htons (port) so it does not yell
 * on freebsd  (thx pp for report)
 *
 * Revision 3.2  1996/04/24  13:56:08  dl
 * added proxy support through m_strProxyServer & m_iHttpProxyPort
 * some httpd *needs* cr+lf so provide them
 * simplification + cleanup
 *
 * Revision 3.1  1996/04/18  13:53:13  dl
 * http-tiny release 1.0
 *
 *
 */

#include "framework.h"
#include <unistd.h>

static const char *rcsid="$Id: http_lib.c,v 3.5 1998/09/23 06:19:15 dl Exp $";

#define VERBOSE

/* http_lib - Http data exchanges mini library.
 */


#ifndef OSK
/* unix */
#include <ctype.h>

#else
/* OS/9 includes */
#include <modes.h>
#include <types.h>
#include <machine/reg.h>
#include <INET/socket.h>
#include <INET/in.h>
#include <INET/netdb.h>
#include <INET/pwd.h>
extern char *malloc();
#endif /* OS9/Unix */


#define SERVER_DEFAULT "adonis"

tiny_http::tiny_http()
{
      m_iHttpPort = 80;
      m_iHttpProxyPort = 0;
      m_strUserAgent ="adlib/3 ($Date: 1998/09/23 06:19:15 $)";
}

tiny_http::~tiny_http()
{
}



/*
 * read a line from file descriptor
 * returns the number of bytes read. negative if a read error occured
 * before the end of line or the MAX.
 * cariage returns (CR) are ignored.
 */
i32 tiny_http::t_read_line (i32 fd, char * buffer, i32 MAX)
{ /* not efficient on long lines (multiple unbuffered 1 char reads) */
  i32 n=0;
  while (n<MAX) {
    if (read(fd,buffer,1)!=1) {
      n= -n;
      break;
    }
    n++;
    if (*buffer=='\015') continue; /* ignore CR */
    if (*buffer=='\012') break;    /* LF is the separator */
    buffer++;
  }
  *buffer=0;
  return n;
}


/*
 * read data from file descriptor
 * retries reading until the number of bytes requested is read.
 * returns the number of bytes read. negative if a read error (EOF) occured
 * before the requested length.
 */
i32 tiny_http::t_read_buffer (i32 fd, char * buffer, i32 length, void (*callback)(void *, i32, dword_ptr), void * callback_param)
{
  i32 n,r;
  for (n=0; n<length; n+=r) {
    r=read(fd,buffer,length-n);
    if(callback)
    callback(callback_param, 1, n);
    if (r<=0) return -n;
    buffer+=r;
  }
  return n;
}




/* beware that filename+type+rest of header must not exceed MAXBUF */
/* so we limit filename to 256 and type to 64 chars in put & get */
#define MAXBUF 512

/*
 * Pseudo general http query
 *
 * send a command and additional headers to the http server.
 * optionally through the proxy (if m_strProxyServer and m_iHttpProxyPort are
 * set).
 *
 * Limitations: the url is truncated to first 256 chars and
 * the server name to 128 in case of proxy request.
 */
//      char *command;	/* command to send  */
  //   char *url;		/* url / filename queried  */
     //char *additional_header;	/* additional header */
     //querymode mode; 		/* type of query */
     //char *data;  /* Data to send after header. If nullptr, not data is sent */
     //i32 length;  /* size of data */
     //i32 *pfd;    /* pointer to variable where to set file descriptor value */

tiny_http::http_retcode tiny_http::t_query(const char * command,  const char * url,  const char * additional_header, querymode mode, char * data, i32 length, i32 * pfd)
{
   i32                  s;
   struct hostent *     hp;
   struct sockaddr_in   server;
   char                 header[MAXBUF];
   i32                  hlg;
   http_retcode         ret;
   i32 proxy = (m_strProxyServer != nullptr && m_iHttpProxyPort != 0);
   i32 port = proxy ? m_iHttpProxyPort : m_iHttpPort;
   if (pfd) * pfd = -1;

   /* get host info by name :*/
   if(hp = gethostbyname(proxy ? m_strProxyServer : (m_strHttpServer != nullptr ? m_strHttpServer : SERVER_DEFAULT )))
   {
      __memset((char *) &server,0, sizeof(server));
      __memmov((char *) &server.sin_addr, hp->h_addr, hp->h_length);
      server.sin_family = hp->h_addrtype;
      server.sin_port = (unsigned short) htons( port );
   }
   else
      return ERRHOST;

  /* create socket */
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return ERRSOCK;
  setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, 0, 0);

  /* connect to server */
  if (connect(s, (const sockaddr *) &server, sizeof(server)) < 0)
    ret=ERRCONN;
  else {
    if (pfd) *pfd=s;

    /* create header */
    if (proxy) {
      sprintf(header,
"%s http://%.128s:%d/%.256s HTTP/1.0\015\012User-Agent: %s\015\012%s\015\012",
	      command,
	      (const char *) m_strHttpServer,
	      m_iHttpPort,
	      url,
	      (const char *) m_strUserAgent,
	      additional_header
	      );
    } else {
      sprintf(header,
"%s /%.256s HTTP/1.0\015\012User-Agent: %s\015\012%s\015\012",
	      command,
	      url,
	      (const char *) m_strUserAgent,
	      additional_header
	      );
    }

    hlg=strlen(header);

    /* send header */
    if (write(s,header,hlg)!=hlg)
      ret= ERRWRHD;

    /* send data */
    else if (length && data && (write(s,data,length)!=length) )
      ret= ERRWRDT;

    else {
      /* read result & check */
      i32 iRet=t_read_line(s,header,MAXBUF-1);
#ifdef VERBOSE
      fputs(header,stderr);
      putc('\n',stderr);
#endif
      if (iRet<=0)
	ret=ERRRDHD;
      else if (sscanf(header,"HTTP/1.%*d %03d",(i32*)&ret)!=1)
	  ret=ERRPAHD;
      else if (mode==KEEP_OPEN)
	return ret;
    }
  }
  /* close socket */
  close(s);
  return ret;
}


/*
 * Put data on the server
 *
 * This function sends data to the http data server.
 * The data will be stored under the ressource name filename.
 * returns a negative error code or a positive code from the server
 *
 * limitations: filename is truncated to first 256 characters
 *              and type to 64.
 */
//     char *filename;  /* name of the ressource to create */
  //   char *data;      /* pointer to the data to send   */
     //i32 length;      /* length of the data to send  */
    // i32 overwrite;   /* flag to request to overwrite the ressource if it
			 // was already existing */
     //char *type;      /* type of the data, if nullptr default type is used */
tiny_http::http_retcode tiny_http::t_put(const char * data, i32 length, i32 overwrite, void (*callback)(void *, i32, dword_ptr), void * callback_param)
{
  char header[MAXBUF];
  if (m_strContentType.get_length() > 0)
    sprintf(header,"Content-length: %d\015\012Content-type: %.64s\015\012%s",
	    length,
	    (const char *) m_strContentType,
	    overwrite ? "Control: overwrite=1\015\012" : ""
	    );
  else
    sprintf(header,"Content-length: %d\015\012%s",length,
	    overwrite ? "Control: overwrite=1\015\012" : ""
	    );
  return t_query("PUT",m_strFileName,header,CLOSE, (char *) data, length, nullptr);
}


/*
 * Get data from the server
 *
 * This function gets data from the http data server.
 * The data is read from the ressource named filename.
 * Address of new allocated memory block is filled in pdata
 * whose length is returned via plength.
 *
 * returns a negative error code or a positive code from the server
 *
 *
 * limitations: filename is truncated to first 256 characters
 */
//     char *filename; /* name of the ressource to read */
  //   char **pdata; /* address of a pointer variable which will be set
	//	      to point toward allocated memory containing read data.*/
     //i32  *plength;/* address of integer variable which will be set to
//		      length of the read data */
  //   char *typebuf; /* allocated buffer where the read data type is returned.
	//	    If nullptr, the type is not returned */
tiny_http::http_retcode tiny_http::t_get(char ** pdata, i32 * plength, void (*callback)(void *, i32, dword_ptr), void * callback_param)
{
  http_retcode ret;

  char header[MAXBUF];
  char *pc;
  i32  fd;
  i32  n,length=-1;

  if (!pdata) return ERRNULL; else *pdata=nullptr;
  if (plength) *plength=0;
  m_strContentType = "";

  ret=t_query("GET",m_strFileName,"",KEEP_OPEN, nullptr, 0, &fd);
  if (ret==200) {
    while (1) {
      n=t_read_line(fd,header,MAXBUF-1);
#ifdef VERBOSE
      fputs(header,stderr);
      putc('\n',stderr);
#endif
      if (n<=0) {
	close(fd);
	return ERRRDHD;
      }
      /* empty line ? (=> end of header) */
      if ( n>0 && (*header)=='\0') break;
      /* try to parse some keywords : */
      /* convert to lower case 'till a : is found or end of string */
      for (pc=header; (*pc!=':' && *pc) ; pc++) *pc=tolower(*pc);
      sscanf(header,"content-length: %d",&length);
      m_strContentType.alloc(1024);
      sscanf(header,"content-type: %s", (char *) m_strContentType);
    }
    if (length<=0) {
      close(fd);
      return ERRNOLG;
    }
    if (plength) *plength=length;
    if (!(*pdata=(char *) ca2_alloc(length))) {
      close(fd);
      return ERRMEM;
    }
    n=t_read_buffer(fd,*pdata,length);
    close(fd);
    if (n!=length) ret=ERRRDDT;
  } else if (ret>=0) close(fd);
  return ret;
}


/*
 * Request the header
 *
 * This function outputs the header of thehttp data server.
 * The header is from the ressource named filename.
 * The length and type of data is eventually returned (like for http_get(3))
 *
 * returns a negative error code or a positive code from the server
 *
 * limitations: filename is truncated to first 256 characters
 */
//     char *filename; /* name of the ressource to read */
  //   i32  *plength;/* address of integer variable which will be set to
	//	      length of the data */
     //char *typebuf; /* allocated buffer where the data type is returned.
		 //   If nullptr, the type is not returned */
tiny_http::http_retcode tiny_http::t_head(i32 * plength)
{
/* mostly copied from http_get : */
  http_retcode ret;

  char header[MAXBUF];
  char *pc;
  i32  fd;
  i32  n,length=-1;

  if (plength) *plength=0;
  m_strContentType = "";

  ret=t_query("HEAD",m_strFileName,"",KEEP_OPEN, nullptr, 0, &fd);
  if (ret==200) {
    while (1) {
      n=t_read_line(fd,header,MAXBUF-1);
#ifdef VERBOSE
      fputs(header,stderr);
      putc('\n',stderr);
#endif
      if (n<=0) {
	close(fd);
	return ERRRDHD;
      }
      /* empty line ? (=> end of header) */
      if ( n>0 && (*header)=='\0') break;
      /* try to parse some keywords : */
      /* convert to lower case 'till a : is found or end of string */
      for (pc=header; (*pc!=':' && *pc) ; pc++) *pc=tolower(*pc);
      sscanf(header,"content-length: %d",&length);
      m_strContentType.alloc(1024);
      sscanf(header,"content-type: %s", (char *) m_strContentType);
    }
    if (plength) *plength=length;
    close(fd);
  } else if (ret>=0) close(fd);
  return ret;
}



/*
 * Delete data on the server
 *
 * This function request a DELETE on the http data server.
 *
 * returns a negative error code or a positive code from the server
 *
 * limitations: filename is truncated to first 256 characters
 */

tiny_http::http_retcode tiny_http::t_delete()
//     char *filename;  /* name of the ressource to create */
{
  return t_query("DELETE",m_strFileName,"",CLOSE, nullptr, 0, nullptr);
}



/* parses an url : setting the m_strHttpServer and m_iHttpPort global variables
 * and returning the filename to pass to http_get/put/...
 * returns a negative error code or 0 if sucessfully parsed.
 */
tiny_http::http_retcode tiny_http::t_parse_url(const char * url)
{
   vsstring strUrl(url);
   if(!strUrl.begins_eat_ci("http://"))
   {
#ifdef VERBOSE
    fprintf(stderr,"invalid url (must start with 'http://')\n");
#endif
    return ERRURLH;
  }
  i32 iFind1 = strUrl.find(":");
  i32 iFind2 = strUrl.find("/");
  if(iFind1 > 0)
  {
     if((iFind2 > 0 && iFind1 < iFind2) || iFind2 < 0)
     {
         m_iHttpPort = atoi(&((const char *)strUrl)[iFind1 + 1]);
     }
     else
     {
         m_iHttpPort = 80;
     }
  }
  else
  {
      m_iHttpPort = 80;
  }
  if(iFind2 >= 0)
  {
      m_strFileName   = strUrl.substr(iFind2 + 1);
  }
  else
  {
     m_strFileName = "";
  }


#ifdef VERBOSE
  fprintf(stderr,"host=(%s), port=%d, filename=(%s)\n",
	    (const char *) m_strHttpServer,m_iHttpPort, (const char *) m_strFileName);
#endif
  return OK0;
}

