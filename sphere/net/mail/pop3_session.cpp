#include "framework.h"
#include <winsock.h>
#include <io.h>


#define socklen_t int /* actually true on most systems */

extern int pop3_recv (pop3sock_t sock, char* buf, int len);

#ifdef USE_SSL

static int SSL_UP = 0;

static char* SSL_CERT = nullptr;


void pop3_cert_setup(const ::string &certfile)
{
	if (SSL_CERT) free(SSL_CERT);
	SSL_CERT=nullptr;
	if (certfile) SSL_CERT=strdup(certfile);
}


int ssl_verify_callback(int ok, X509_STORE_CTX *ctx) {
    if (!ok) {
        int err;
        err = X509_STORE_CTX_get_error(ctx);
#ifdef EBUG
        fprintf(stderr, "SSL error #%d: %s.\n", err,
                X509_verify_cert_error_string(err));
#endif
        return 0;
    }
    return 1;
}



pop3sock_t ssl_prepare(const int port)
{
   pop3sock_t sock;
	sock =(pop3sock_t)malloc(sizeof(pop3sock));
	sock->m_psock = memory_new TcpSocket();
	if(nullptr==sock->m_psock)
   {
	   perror("ssl_prepare.socket");
      free(sock);
		return nullptr;
	}
	if(port == 995)
   {
      sock->m_psock->InitSSLClient();
	}
	return sock;
}

#endif

pop3sock_t pop3_prepare(const ::string & servername, const int port, struct sockaddr_in* connection, struct hostent* server){
/* prepares the pop session and returns a socket descriptor */
pop3sock_t sock;
struct hostent* hostent_buf;
int i;
#ifdef WIN32

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
#ifdef EBUG
	fprintf(stderr,"WSAStartup() failed");
#endif
	exit(1);
	}

#endif

	memory_set((char*)connection,0,sizeof(struct sockaddr_in));

	hostent_buf=gethostbyname(servername);
	if(!hostent_buf){
		perror("pop3_prepare.gethostbyname");
		return BAD_SOCK;
	}
    /* begin hostent deep copy */
    __memmov(server,hostent_buf,sizeof(struct hostent));
#if 1
    server->h_name=strdup(hostent_buf->h_name);
    server->h_aliases=nullptr;
    i=0;
    while (hostent_buf->h_aliases[i])
    {
        server->h_aliases=realloc(server->h_aliases,(i+1)*sizeof(char*));
        if(hostent_buf->h_aliases[i])
            server->h_aliases[i]=strdup(hostent_buf->h_aliases[i]);
        else server->h_aliases[i]=nullptr;
        i++;
    }
    server->h_addr_list=nullptr;
    i=0;
    while (hostent_buf->h_addr_list[i])
    { /* has at least one adress */
        server->h_addr_list=realloc(server->h_addr_list,(i+1)*sizeof(char*));
        server->h_addr_list[i]=malloc(server->h_length);
        __memmov(server->h_addr_list[i],hostent_buf->h_addr_list[i],server->h_length);
        i++;
    } 
    server->h_addr_list=realloc(server->h_addr_list, (i+1)*sizeof(char*));
    server->h_addr_list[i]=malloc(1);
    server->h_addr_list[i]='\0'; 
    /* end hostent deep copy */
#endif
	__memmov((char*)&(connection->sin_addr.s_addr),server->h_addr,server->h_length);
	connection->sin_family=AF_INET;
	connection->sin_port=htons(port?(unsigned short int)port:(unsigned short int)110);	/* integral size_i32 mismatch in argument - htons(port)*/

#ifdef USE_SSL
	sock = ssl_prepare(port);
#else
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(BAD_SOCK==sock){
		perror("pop3_prepare.socket");
	}
#endif
	return(sock);
}

char* pop3_connect(pop3sock_t sock, struct sockaddr_in* connection){
/* connects to the server through the sock and returns server's welcome */
int r;
char* buf;

#ifdef EBUG
	fprintf(stderr,"<pop3_connect>\n");
#endif

#ifdef USE_SSL
	r=connect(sock->sock,(struct sockaddr*)connection,(socklen_t)sizeof(*connection));
	if ( r!=-1  && sock->ssl ) {
		if (SSL_connect(sock->ssl) == -1) {
#ifdef EBUG
			fprintf(stderr, "SSL_connect failed\n");
#endif
			close(sock->sock);
			return(nullptr);
		}
		if ( SSL_CERT ) {
			if ( !SSL_get_peer_certificate(sock->ssl) ) {
#ifdef EBUG
	 			fprintf(stderr, "SSL: failed to get peer certificate\n");
#endif
				close(sock->sock);               
				return(nullptr);
	                }
		}
	}   
#else
	r=connect(sock,(struct sockaddr*)connection,(socklen_t)sizeof(*connection));
#endif

	if(r==-1){
		perror("pop3_connect.connect");
		return(nullptr);
	}


	buf=(char*)malloc(POPBUF);
	if(!buf){
		perror("pop3_connect.malloc");
		return(nullptr);
	}
	r=pop3_recv(sock,buf,POPBUF); /* 512 is enough, as say RFC 1939 */
	buf[r]='\0';

#ifdef EBUG
	fprintf(stderr,"recv %s",buf);
	fprintf(stderr,"</pop3_connect>\n");
#endif
	return(buf);
}

void pop3_disconnect(pop3sock_t sock, struct hostent* server){
    int i;
/* close socket  */
#ifdef USE_SSL
	if (sock->sock>0) 
    {
        shutdown(sock->sock,SHUT_RDWR);
        close(sock->sock);
    }
        if (nullptr != sock->ssl) {
		SSL_shutdown(sock->ssl);
		free(sock->ssl);
	}
	if ( nullptr != sock->ctx ) SSL_CTX_free(sock->ctx);
	free(sock);
#else
	if (sock>0) {
        shutdown(sock,SHUT_RDWR);
        close(sock);
    }
#endif
    /* free deep copy of struct hostent */
    i=0;
    while(server->h_addr_list[i]) {
    /* has at least one adress */
        free(server->h_addr_list[i]);
        i++;
    }
    free(server->h_addr_list[i]); /* thanks to i++ */
    free(server->h_addr_list);
    free(server->h_name);
#ifdef WIN32
	WSACleanup();
#endif
}
