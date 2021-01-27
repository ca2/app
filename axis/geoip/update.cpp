#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/geoip/_.h"
#endif
#include "apex/net/sockets/_sockets.h"
#include <stdio.h>


#ifdef BSD_STYLE_SOCKETS
//#include<openssl/ssl.h>
//#include<openssl/md5.h>
#endif



i16 parse_http_proxy(char **proxy_host, i32 *port);
//#ifdef BSD_STYLE_SOCKETS
//struct hostent *GeoIP_get_host_or_proxy ();
//#else
string GeoIP_get_host_or_proxy ();
//#endif


#define BLOCK_SIZE 1024

/* Update DB Host & HTTP GET Request formats:
 * ------------------------------------------
 * GET must support an optional HTTP Proxy.
 */
const char *GeoIPUpdateHost = "updates.maxmind.com";
/* This is the direct, or proxy port number. */
//static i32 GeoIPHTTPPort = 80;
/* License-only format (OLD) */
const char *GeoIPHTTPRequest = "GET %s%s/app/update?license_key=%s&md5=%s HTTP/1.0\nHost: updates.maxmind.com\n\n";
/* General DB Types formats */
const char *GeoIPHTTPRequestFilename = "GET %s%s/app/update_getfilename?product_id=%s HTTP/1.0\nHost: %s\n\n";
const char *GeoIPHTTPRequestClientIP = "GET %s%s/app/update_getipaddr HTTP/1.0\nHost: %s\n\n";
const char *GeoIPHTTPRequestMD5 = "GET %s%s/app/update_secure?db_md5=%s&challenge_md5=%s&user_id=%s&edition_id=%s HTTP/1.0\nHost: updates.maxmind.com\n\n";

/* messages */
const char *NoCurrentDB = "%s can't be opened, proceeding to download database\n";
const char *MD5Info = "MD5 Digest of installed database is %s\n";
const char *SavingGzip = "Saving gzip file to %s ... ";
const char *WritingFile = "Writing uncompressed data to %s ...";

const char * GeoIP_get_error_message(i32 i) {
  switch (i) {
  case GEOIP_NO_NEW_UPDATES:
    return "no new updates";
  case GEOIP_SUCCESS:
    return "Success";
  case GEOIP_LICENSE_KEY_INVALID_ERR:
    return "License Key Invalid";
  case GEOIP_DNS_ERR:
    return "Unable to resolve hostname";
  case GEOIP_NON_IPV4_ERR:
    return "Non - IPv4 address";
  case GEOIP_SOCKET_OPEN_ERR:
    return "Error opening socket";
  case GEOIP_CONNECTION_ERR:
    return "Unable to connect";
  case GEOIP_GZIP_IO_ERR:
    return "Unable to write GeoIP.dat.gz file";
  case GEOIP_TEST_IO_ERR:
    return "Unable to write GeoIP.dat.test file";
  case GEOIP_GZIP_READ_ERR:
    return "Unable to read gzip data";
  case GEOIP_OUT_OF_MEMORY_ERR:
    return "Out of memory error";
  case GEOIP_SOCKET_READ_ERR:
    return "Error reading from socket, see errno";
  case GEOIP_SANITY_OPEN_ERR:
    return "Sanity check GeoIP_open error";
  case GEOIP_SANITY_INFO_FAIL:
    return "Sanity check database_info string failed";
  case GEOIP_SANITY_LOOKUP_FAIL:
    return "Sanity check ip address lookup failed";
  case GEOIP_RENAME_ERR:
    return "Rename error while installing db, check errno";
  case GEOIP_USER_ID_INVALID_ERR:
    return "Invalid userID";
  case GEOIP_PRODUCT_ID_INVALID_ERR:
    return "Invalid product ID or subscription expired";
  case GEOIP_INVALID_SERVER_RESPONSE:
    return "Server returned something unexpected";
  default:
    return "no error";
  }
}
i32 GeoIP_fprintf(i32 (*f)(FILE *, char *),FILE *fp, const char *str, ...) {
  va_list ap;
  i32 rc;
  char * f_str;
  i32 silence;

  if ( f == nullptr )
    return 0;
  va_start(ap, str);
#if defined(HAVE_VASPRINTF)
  silence = vasprintf(&f_str, str, ap);
#elif defined (HAVE_VSNPRINTF)
  f_str = malloc(4096);
  if ( f_str )
    silence = vsnprintf(f_str, 4096, str, ap);
#else
  f_str = (char *) malloc(4096);
  if ( f_str )
    silence = vsprintf(f_str, str, ap);
#endif
  va_end(ap);
  if (  f_str == nullptr )
    return -1;
  rc = (*f)(fp, f_str);
  free(f_str);
  return(rc);
}

void GeoIP_printf(void (*f)(char *), const char *str,...) {
  va_list params;
  char * f_str;
  i32 silence;
  if (f == nullptr)
    return;
  va_start(params, str);
#if defined(HAVE_VASPRINTF)
  silence = vasprintf(&f_str, str, params);
#elif defined (HAVE_VSNPRINTF)
  f_str = malloc(4096);
  if ( f_str )
    silence = vsnprintf(f_str, 4096, str, params);
#else
  f_str =(char *)  malloc(4096);
  if ( f_str )
    silence = vsprintf(f_str, str, params);
#endif
  va_end(params);
  if ( f_str == nullptr )
    return;
  (*f)(f_str);
  free(f_str);
}

/* Support HTTP Proxy Host
 * --------------------------------------------------
 * Use typical App support for the optional HTTP Proxy.
 *
 * Proxy adds http://{real-hostname} to URI format strings:
 * sprintf("GET %s%s/ HTTP/1.0\r\n",GeoIPProxyHTTP,GeoIPProxiedHost, ...);
 */

/* The Protocol is usually "" OR "http://" with a proxy. */
//static const char * GeoIPProxyHTTP = "";
/* GeoIP Hostname where proxy forwards requests. */
//static const char * GeoIPProxiedHost = "";

/* read http_proxy env. ::payload & parse it.
 * -----------------------------------------
 * Allow only these formats:
 * "http://server.com", "http://server.com:8080"
 * OR
 * "server.com", "server.com:8080"
 *
 * A "::account::user:password@" part will break this.
 */
i16 parse_http_proxy(char **proxy_host, i32 *port) {

#ifdef _UWP

   return 0;

#else

   char * http_proxy;

   char * port_value;

   if ((http_proxy = getenv("http_proxy"))) {

      if (! ansi_count_compare("http://", http_proxy, 7)) http_proxy += 7;
      *proxy_host = ansi_dup(http_proxy);
      if ( *proxy_host == nullptr )
         return 0; /* let the other functions deal with the memory error */

      if ((port_value = strchr(*proxy_host, ':'))) {
         *port_value++ = '\0';
         *port = atoi(port_value);
      }
      else {
         *port = 80;
      }
      return(1);
   }
   else {
      return(0);
   }

#endif

}


#ifdef BSD_STYLE_SOCKETS


string GeoIP_get_host_or_proxy()
{

   return ip_reverse(GeoIPUpdateHost);

}


#endif


//thread_pointer < hostent > t_phostentGeoip;

/* get the GeoIP host or the current HTTP Proxy host. */
//#ifdef BSD_STYLE_SOCKETS
//struct hostent *GeoIP_get_host_or_proxy ()
//#else
//string GeoIP_get_host_or_proxy ()
//#endif
//{
//   char * hostname = (char *) GeoIPUpdateHost;
//   char * proxy_host;
//   i32 proxy_port;
//
//   /* Set Proxy from App: Unix/Linux */
//   if (parse_http_proxy(&proxy_host,&proxy_port)) {
//      hostname = proxy_host;
//      GeoIPProxyHTTP = "http://";
//      GeoIPProxiedHost = (char *) GeoIPUpdateHost;
//      GeoIPHTTPPort = proxy_port;
//   }
//
//   if(t_phostentGeoip == nullptr)
//   {
//
//      t_phostentGeoip = new hostent;
//
//   }
//
//   /* Resolve DNS host entry. */
//   return getaddrinfo(;
//
//}


i16 GeoIP_update_database (char * license_key, i32 verbose, void (*f)( char * ));


//i16 GeoIP_update_database (char * license_key, i32 verbose, void (*f)( char * ))
//{
//
//#ifdef BSD_STYLE_SOCKETS
//   struct hostent *hostlist;
//   SOCKET sock;
//
//   char * buf;
//   struct sockaddr_in sa;
//   i32 offset = 0, err;
//   char * request_uri;
//   char * compr;
//   u32 comprLen;
//   FILE *comp_fh, *cur_db_fh, *gi_fh;
//   gzFile gz_fh;
//   char * file_path_gz, * file_path_test;
//   MD5_CTX context;
//   uchar buffer[1024], digest[16];
////   uchar buffer[1024];
//   char hex_digest[34] = "00000000000000000000000000000000\0";
//   u32 i;
//   GeoIP * gi;
//   char * db_info;
//   char block[BLOCK_SIZE];
//   i32 block_size = BLOCK_SIZE;
//   size_t len;
//   size_t written;
//   _GeoIP_setup_dbfilename();
//
//   /* get MD5 of current GeoIP database file */
//   if ((cur_db_fh = fopen (GeoIPDBFileName[GEOIP_COUNTRY_EDITION], "rb")) == nullptr) {
//    GeoIP_printf(f,"%s%s",  NoCurrentDB, GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   } else {
//
////      MD5_CTX context;
//
//      //MD5_Init(&ctx);
//
//      //::crypto::md5::context ctx(get_object());
//
//
//      MD5_Init(&context);
//      while ((len = fread (buffer, 1, 1024, cur_db_fh)) > 0)
//         MD5_Update (&context, buffer, (u32) len);
//        // MD5_Update(&ctx, buffer, len);
//      MD5_Final (buffer, &context);
//      ::memcpy_dup(digest,buffer,16);
//      fclose (cur_db_fh);
//      for (i = 0; i < 16; i++) {
//       //  "%02x" will write 3 chars
//         snprintf (&hex_digest[2*i], 3, "%02x", digest[i]);
//      }
//      GeoIP_printf(f,MD5Info, hex_digest);
//      //string strHex = ctx.to_hex();
//      //strHex.make_lower();
////    GeoIP_printf(f, MD5Info, strHex.c_str());
//   }
//
//   hostlist = GeoIP_get_host_or_proxy();
//
//
//   if (hostlist == nullptr)
//      return GEOIP_DNS_ERR;
//
//   if (hostlist->h_addrtype != AF_INET)
//      return GEOIP_NON_IPV4_ERR;
//
//   if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//      return GEOIP_SOCKET_OPEN_ERR;
//   }
//
//   __memset(&sa, 0, sizeof(struct sockaddr_in));
//   sa.sin_port = htons((u_short)GeoIPHTTPPort);
//   ::memcpy_dup(&sa.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
//   sa.sin_family = AF_INET;
//
//   if (verbose == 1){
//      GeoIP_printf(f,"Connecting to MaxMind GeoIP Update server\n");
//      GeoIP_printf(f, "via Host or Proxy Server: %s:%d\n", hostlist->h_name, GeoIPHTTPPort);
//   }
//
//   /* Download gzip file */
//   if (connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr))< 0)
//      return GEOIP_CONNECTION_ERR;
//
//   request_uri = (char *) malloc(sizeof(char) * (strlen(license_key) + strlen(GeoIPHTTPRequest)+36));
//   if (request_uri == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   sprintf(request_uri,GeoIPHTTPRequest,GeoIPProxyHTTP,GeoIPProxiedHost,license_key, hex_digest);
//   send(sock, request_uri, (i32) strlen(request_uri),0);
//   free(request_uri);
//
//   buf = (char *) malloc(sizeof(char) * block_size);
//   if (buf == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Downloading gzipped GeoIP Dataaxis...\n");
//
//   for (;;) {
//      i32 amt;
//      amt = (i32) recv(sock, &buf[offset], block_size,0);
//      if (amt == 0) {
//         break;
//      } else if (amt == -1) {
//         free(buf);
//         return GEOIP_SOCKET_READ_ERR;
//      }
//      offset += amt;
//      buf = (char *) realloc(buf, offset+block_size);
//      if (buf == nullptr)
//         return GEOIP_OUT_OF_MEMORY_ERR;
//   }
//
//   compr = strstr(buf, "\r\n\r\n") + 4;
//   comprLen = (u32) (offset + buf - compr);
//
//   if (strstr(compr, "License Key Invalid") != nullptr) {
//      if (verbose == 1)
//         GeoIP_printf(f,"Failed\n");
//      free(buf);
//      return GEOIP_LICENSE_KEY_INVALID_ERR;
//   } else if (strstr(compr, "Invalid product ID or subscription expired") != nullptr){
//      free(buf);
//      return GEOIP_PRODUCT_ID_INVALID_ERR;
//   } else if (strstr(compr, "No new updates available") != nullptr) {
//      free(buf);
//      return GEOIP_NO_NEW_UPDATES;
//   }
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   /* save gzip file */
//   file_path_gz = (char *) malloc(sizeof(char) * (strlen(GeoIPDBFileName[GEOIP_COUNTRY_EDITION]) + 4));
//   if (file_path_gz == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   strcpy(file_path_gz,GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   ansi_concatenate(file_path_gz,".gz");
//   if (verbose == 1) {
//    GeoIP_printf(f, SavingGzip, file_path_gz);
//   }
//   comp_fh = fopen(file_path_gz, "wb");
//
//   if(comp_fh == nullptr) {
//      free(file_path_gz);
//      free(buf);
//      return GEOIP_GZIP_IO_ERR;
//   }
//
//   written = fwrite(compr, 1, comprLen, comp_fh);
//   fclose(comp_fh);
//   free(buf);
//
//        if ( written != comprLen )
//      return GEOIP_GZIP_IO_ERR;
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Uncompressing gzip file ... ");
//
//   /* uncompress gzip file */
//   gz_fh = gzopen(file_path_gz, "rb");
//   file_path_test = (char *) malloc(sizeof(char) * (strlen(GeoIPDBFileName[GEOIP_COUNTRY_EDITION]) + 6));
//   if (file_path_test == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   strcpy(file_path_test,GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   ansi_concatenate(file_path_test,".test");
//   gi_fh = fopen(file_path_test, "wb");
//
//   if(gi_fh == nullptr) {
//      free(file_path_test);
//      return GEOIP_TEST_IO_ERR;
//   }
//   for (;;) {
//      iptr amt;
//      amt = gzread(gz_fh, block, block_size);
//      if (amt == -1) {
//         free(file_path_test);
//         fclose(gi_fh);
//         gzclose(gz_fh);
//         return GEOIP_GZIP_READ_ERR;
//      }
//      if (amt == 0) {
//         break;
//      }
//      if ( fwrite(block,1,amt,gi_fh) != natural(amt) )
//      {
//         free(file_path_test);
//         fclose(gi_fh);
//         gzclose(gz_fh);
//         return GEOIP_GZIP_READ_ERR;
//      }
//   }
//   gzclose(gz_fh);
//   ansi_unlink(file_path_gz);
//   free(file_path_gz);
//   fclose(gi_fh);
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   if (verbose == 1) {
//    GeoIP_printf(f, WritingFile, GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   }
//
//   /* sanity check */
//   gi = GeoIP_open(file_path_test, GEOIP_STANDARD);
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Performing santity checks ... ");
//
//   if (gi == nullptr) {
//      GeoIP_printf(f,"Error opening sanity check database\n");
//      return GEOIP_SANITY_OPEN_ERR;
//   }
//
//   /* this checks to make sure the files is complete, since info is at the end */
//   /* dependent on future databases having MaxMind in info */
//   if (verbose == 1)
//      GeoIP_printf(f,"database_info  ");
//   db_info = GeoIP_database_info(gi);
//   if (db_info == nullptr) {
//      GeoIP_delete(gi);
//      if (verbose == 1)
//         GeoIP_printf(f,"FAIL\n");
//      return GEOIP_SANITY_INFO_FAIL;
//   }
//   if (strstr(db_info, "MaxMind") == nullptr) {
//      free(db_info);
//      GeoIP_delete(gi);
//      if (verbose == 1)
//         GeoIP_printf(f,"FAIL\n");
//      return GEOIP_SANITY_INFO_FAIL;
//   }
//   free(db_info);
//   if (verbose == 1)
//      GeoIP_printf(f,"PASS  ");
//
//   /* this performs an IP lookup test of a US IP address */
//   if (verbose == 1)
//      GeoIP_printf(f,"lookup  ");
//   if (strcmp(GeoIP_country_code_by_addr(gi,"24.24.24.24"), "US") != 0) {
//      GeoIP_delete(gi);
//      if (verbose == 1)
//         GeoIP_printf(f,"FAIL\n");
//      return GEOIP_SANITY_LOOKUP_FAIL;
//   }
//   GeoIP_delete(gi);
//   if (verbose == 1)
//      GeoIP_printf(f,"PASS\n");
//
//   /* install GeoIP.dat.test -> GeoIP.dat */
//   err = rename(file_path_test, GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   if (err != 0) {
//      GeoIP_printf(f,"GeoIP Install error while renaming file\n");
//      return GEOIP_RENAME_ERR;
//   }
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   return 0;
//
//#else
//
//   __throw(todo());
//
//#endif
//
//}

i16 GeoIP_update_database_general (::object * pobject, char * user_id,char * license_key,char *data_axis_type, i32 verbose,char ** client_ipaddr, void (*f)( char *));


//i16 GeoIP_update_database_general (::object * pobject, char * user_id,char * license_key,char *data_axis_type, i32 verbose,char ** client_ipaddr, void (*f)( char *)) {
//
//#ifdef BSD_STYLE_SOCKETS
//   struct hostent *hostlist;
//   SOCKET sock;
//   char * buf;
//   struct sockaddr_in sa;
//   i32 offset = 0, err;
//   char * request_uri;
//   char * compr;
//   u32 comprLen;
//   FILE *comp_fh, *cur_db_fh, *gi_fh;
//   gzFile gz_fh;
//   char * file_path_gz, * file_path_test;
//   MD5_CTX context;
//   MD5_CTX context2;
//   uchar buffer[1024];
//   uchar digest[16] ,digest2[16];
//   char hex_digest[33] = "0000000000000000000000000000000\0";
//   char hex_digest2[33] = "0000000000000000000000000000000\0";
//   u32 i;
//   char *f_str;
//   GeoIP * gi;
//   char * db_info;
//   char *ipaddress;
//   char *geoipfilename;
//   char *tmpstr;
//   i32 dbtype;
//   i32 lookupresult = 1;
//   char block[BLOCK_SIZE];
//   i32 block_size = BLOCK_SIZE;
//   size_t len;
//   size_t request_uri_len;
//   size_t size;
//
//
//   hostlist = GeoIP_get_host_or_proxy();
//
//   if (hostlist == nullptr)
//      return GEOIP_DNS_ERR;
//
//   if (hostlist->h_addrtype != AF_INET)
//      return GEOIP_NON_IPV4_ERR;
//   if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//      return GEOIP_SOCKET_OPEN_ERR;
//   }
//
//   __memset(&sa, 0, sizeof(struct sockaddr_in));
//   sa.sin_port = htons((u_short) GeoIPHTTPPort);
//   ::memcpy_dup(&sa.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
//   sa.sin_family = AF_INET;
//
//   if (verbose == 1) {
//      GeoIP_printf(f,"Connecting to MaxMind GeoIP server\n");
//      GeoIP_printf(f, "via Host or Proxy Server: %s:%d\n", hostlist->h_name, GeoIPHTTPPort);
//   }
//
//   if (connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr))< 0)
//      return GEOIP_CONNECTION_ERR;
//   request_uri = (char *) malloc(sizeof(char) * (strlen(license_key) + strlen(GeoIPHTTPRequestMD5)+1036));
//   if (request_uri == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//
//   /* get the file name from a web page using the product id */
//   sprintf(request_uri,GeoIPHTTPRequestFilename,GeoIPProxyHTTP,GeoIPProxiedHost,data_axis_type,GeoIPUpdateHost);
//   if (verbose == 1) {
//      GeoIP_printf(f, "sending request %s \n",request_uri);
//   }
//   send(sock, request_uri, (i32) strlen(request_uri),0); /* send the request */
//   free(request_uri);
//   buf = (char *) malloc(sizeof(char) * (block_size+4));
//   if (buf == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   offset = 0;
//   for (;;){
//      i32 amt;
//      amt = (i32) recv(sock, &buf[offset], block_size,0);
//      if (amt == 0){
//         break;
//      } else if (amt == -1) {
//         free(buf);
//         return GEOIP_SOCKET_READ_ERR;
//      }
//      offset += amt;
//      buf = (char *) realloc(buf, offset + block_size + 4);
//   }
//   buf[offset] = 0;
//   offset = 0;
//   tmpstr = strstr(buf, "\r\n\r\n") + 4;
//   if (tmpstr[0] == '.' || strchr(tmpstr, '/') != nullptr) {
//      free(buf);
//      return GEOIP_INVALID_SERVER_RESPONSE;
//   }
//   geoipfilename = _GeoIP_full_path_to(tmpstr);
//   free(buf);
//
//   /* print the database product id and the database filename */
//   if (verbose == 1){
//      GeoIP_printf(f, "database product id %s database file name %s \n",data_axis_type,geoipfilename);
//   }
//   _GeoIP_setup_dbfilename();
//
//   /* get MD5 of current GeoIP database file */
//   if ((cur_db_fh = fopen (geoipfilename, "rb")) == nullptr) {
//    GeoIP_printf(f, NoCurrentDB, geoipfilename);
//   } else {
////      ::crypto::md5::context ctx(get_object());
//      MD5_Init(&context);
//      while ((len = fread (buffer, 1, 1024, cur_db_fh)) > 0)
//        // ctx.update(buffer, len);
//         MD5_Update (&context, buffer, (u32) len);
//      MD5_Final (buffer, &context);
//    ::memcpy_dup(digest,buffer,16);
//      fclose (cur_db_fh);
//      for (i = 0; i < 16; i++)
//         sprintf (&hex_digest[2*i], "%02x", digest[i]);
//      //strcpy(hex_digest, ctx.to_hex());
//      ansi_lower(hex_digest);
//    GeoIP_printf(f, MD5Info, hex_digest );
//   }
//   if (verbose == 1) {
//      GeoIP_printf(f,"MD5 sum of database %s is %s \n",geoipfilename,hex_digest);
//   }
//   if (client_ipaddr[0] == nullptr) {
//      /* We haven't gotten our IP address yet, so let's request it */
//      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         free(geoipfilename);
//         return GEOIP_SOCKET_OPEN_ERR;
//      }
//
//      __memset(&sa, 0, sizeof(struct sockaddr_in));
//      sa.sin_port = htons((u_short) GeoIPHTTPPort);
//      ::memcpy_dup(&sa.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
//      sa.sin_family = AF_INET;
//
//      if (verbose == 1)
//         GeoIP_printf(f,"Connecting to MaxMind GeoIP Update server\n");
//
//      /* Download gzip file */
//      if (connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr))< 0) {
//         free(geoipfilename);
//         return GEOIP_CONNECTION_ERR;
//      }
//      request_uri = (char *) malloc(sizeof(char) * (strlen(license_key) + strlen(GeoIPHTTPRequestMD5)+1036));
//      if (request_uri == nullptr) {
//         free(geoipfilename);
//         return GEOIP_OUT_OF_MEMORY_ERR;
//      }
//
//      /* get client ip address from MaxMind web page */
//      sprintf(request_uri,GeoIPHTTPRequestClientIP,GeoIPProxyHTTP,GeoIPProxiedHost,GeoIPUpdateHost);
//      send(sock, request_uri, (i32) strlen(request_uri),0); /* send the request */
//      if (verbose == 1) {
//         GeoIP_printf(f, "sending request %s", request_uri);
//      }
//      free(request_uri);
//      buf = (char *) malloc(sizeof(char) * (block_size+1));
//      if (buf == nullptr) {
//         free(geoipfilename);
//         return GEOIP_OUT_OF_MEMORY_ERR;
//      }
//      offset = 0;
//
//      for (;;){
//         i32 amt;
//         amt = (i32) recv(sock, &buf[offset], block_size,0);
//         if (amt == 0) {
//            break;
//         } else if (amt == -1) {
//            free(buf);
//            return GEOIP_SOCKET_READ_ERR;
//         }
//         offset += amt;
//         buf = (char *) realloc(buf, offset+block_size+1);
//      }
//
//      buf[offset] = 0;
//      offset = 0;
//      ipaddress = strstr(buf, "\r\n\r\n") + 4; /* get the ip address */
//      ipaddress = (char *) malloc(strlen(strstr(buf, "\r\n\r\n") + 4)+5);
//      strcpy(ipaddress,strstr(buf, "\r\n\r\n") + 4);
//      client_ipaddr[0] = ipaddress;
//      if (verbose == 1) {
//         GeoIP_printf(f, "client ip address: %s\n",ipaddress);
//      }
//      free(buf);
//#if defined(LINUX)
//      close(sock);
//#endif
//   }
//
//   ipaddress = client_ipaddr[0];
//
//   /* make a md5 sum of ip address and license_key and store it in hex_digest2 */
//   request_uri_len = sizeof(char) * 2036;
//   request_uri = (char *) malloc(request_uri_len);
//   //::crypto::md5::context ctx2(get_object());
//   MD5_Init(&context2);
//   uchar bufMd5[16];
////   ctx2.update(license_key,12);
//   //ctx2.update(ipaddress, strlen(ipaddress));
//   MD5_Update (&context2, (u8 *)license_key, 12);//add license key to the md5 sum
//   MD5_Update (&context2, (u8 *)ipaddress, (u32) strlen(ipaddress));//add ip address to the md5 sum
//   MD5_Final (bufMd5, &context2);
//   ::memcpy_dup(digest2, bufMd5,16);
//   for (i = 0; i < 16; i++)
//      snprintf (&hex_digest2[2*i], 3, "%02x", digest2[i]);// machine the digest to a hex digest
//   //strcpy(hex_digest2, ctx2.to_hex());
//   ansi_lower(hex_digest2);
//   if (verbose == 1) {
//      GeoIP_printf(f, "md5sum of ip address and license key is %s \n",hex_digest2);
//   }
//
//   /* send the request using the ::account::user id,product id,
//    * md5 sum of the prev database and
//    * the md5 sum of the license_key and ip address */
//   if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//   {
//      return GEOIP_SOCKET_OPEN_ERR;
//   }
//   __memset(&sa, 0, sizeof(struct sockaddr_in));
//   sa.sin_port = htons((u_short) GeoIPHTTPPort);
//   ::memcpy_dup(&sa.sin_addr, hostlist->h_addr_list[0], hostlist->h_length);
//   sa.sin_family = AF_INET;
//   if (connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr))< 0)
//      return GEOIP_CONNECTION_ERR;
//   snprintf(request_uri, request_uri_len, GeoIPHTTPRequestMD5,GeoIPProxyHTTP,GeoIPProxiedHost,hex_digest,hex_digest2,user_id,data_axis_type);
//   send(sock, request_uri, (i32) strlen(request_uri),0);
//   if (verbose == 1) {
//      GeoIP_printf(f, "sending request %s\n",request_uri);
//   }
//
//   free(request_uri);
//
//   offset = 0;
//   buf = (char *) malloc(sizeof(char) * block_size);
//   if (buf == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Downloading gzipped GeoIP Dataaxis...\n");
//
//   for (;;) {
//      i32 amt;
//      amt = (i32) recv(sock, &buf[offset], block_size,0);
//
//      if (amt == 0) {
//         break;
//      } else if (amt == -1) {
//         free(buf);
//         return GEOIP_SOCKET_READ_ERR;
//      }
//      offset += amt;
//      buf = (char *) realloc(buf, offset+block_size);
//      if (buf == nullptr)
//         return GEOIP_OUT_OF_MEMORY_ERR;
//   }
//
//   compr = strstr(buf, "\r\n\r\n") + 4;
//   comprLen = (u32) (offset + buf - compr);
//
//   if (strstr(compr, "License Key Invalid") != nullptr) {
//      if (verbose == 1)
//         GeoIP_printf(f,"Failed\n");
//      free(buf);
//      return GEOIP_LICENSE_KEY_INVALID_ERR;
//   } else if (strstr(compr, "No new updates available") != nullptr) {
//      free(buf);
//      GeoIP_printf(f, "%s is up to date, no updates required\n", geoipfilename);
//      return GEOIP_NO_NEW_UPDATES;
//   } else if (strstr(compr, "Invalid UserId") != nullptr){
//      free(buf);
//      return GEOIP_USER_ID_INVALID_ERR;
//   } else if (strstr(compr, "Invalid product ID or subscription expired") != nullptr){
//      free(buf);
//      return GEOIP_PRODUCT_ID_INVALID_ERR;
//   }
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   GeoIP_printf(f, "Updating %s\n", geoipfilename);
//
//   /* save gzip file */
//   file_path_gz =(char *) malloc(sizeof(char) * (strlen(geoipfilename) + 4));
//
//   if (file_path_gz == nullptr)
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   strcpy(file_path_gz,geoipfilename);
//   ansi_concatenate(file_path_gz,".gz");
//   if (verbose == 1) {
//    GeoIP_printf(f, "%s%s", SavingGzip, file_path_gz );
//   }
//   comp_fh = fopen(file_path_gz, "wb");
//
//   if(comp_fh == nullptr) {
//      free(file_path_gz);
//      free(buf);
//      return GEOIP_GZIP_IO_ERR;
//   }
//
//   size = fwrite(compr, 1, comprLen, comp_fh);
//   fclose(comp_fh);
//   free(buf);
//        if ( size != comprLen ) {
//      return GEOIP_GZIP_IO_ERR;
//   }
//
//   if (verbose == 1) {
//      GeoIP_printf(f, "download data to a gz file named %s \n",file_path_gz);
//      GeoIP_printf(f,"Done\n");
//      GeoIP_printf(f,"Uncompressing gzip file ... ");
//   }
//
//   file_path_test = (char *) malloc(sizeof(char) * (strlen(GeoIPDBFileName[GEOIP_COUNTRY_EDITION]) + 6));
//   if (file_path_test == nullptr) {
//      free(file_path_gz);
//      return GEOIP_OUT_OF_MEMORY_ERR;
//   }
//   strcpy(file_path_test,GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
//   ansi_concatenate(file_path_test,".test");
//   gi_fh = fopen(file_path_test, "wb");
//   if(gi_fh == nullptr) {
//      free(file_path_test);
//      free(file_path_gz);
//      return GEOIP_TEST_IO_ERR;
//   }
//   /* uncompress gzip file */
//   offset = 0;
//   gz_fh = gzopen(file_path_gz, "rb");
//   for (;;) {
//      iptr amt;
//      amt = gzread(gz_fh, block, block_size);
//      if (amt == -1) {
//         free(file_path_gz);
//         free(file_path_test);
//         gzclose(gz_fh);
//         fclose(gi_fh);
//         return GEOIP_GZIP_READ_ERR;
//      }
//      if (amt == 0) {
//         break;
//      }
//      if (natural(amt) != fwrite(block,1,amt,gi_fh) ){
//         return GEOIP_GZIP_IO_ERR;
//      }
//   }
//   gzclose(gz_fh);
//   ansi_unlink(file_path_gz);
//   free(file_path_gz);
//   fclose(gi_fh);
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//
//   if (verbose == 1) {
//      len = strlen(WritingFile) + strlen(geoipfilename) - 1;
//      f_str = (char *) malloc(len);
//      snprintf(f_str,len,WritingFile,geoipfilename);
//      free(f_str);
//   }
//
//   /* sanity check */
//   gi = GeoIP_open(file_path_test, GEOIP_STANDARD);
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Performing santity checks ... ");
//
//   if (gi == nullptr) {
//      GeoIP_printf(f,"Error opening sanity check database\n");
//      return GEOIP_SANITY_OPEN_ERR;
//   }
//
//
//   /* get the database type */
//   dbtype = GeoIP_database_edition(gi);
//   if (verbose == 1) {
//      GeoIP_printf(f, "Dataaxis type is %d\n",dbtype);
//   }
//
//   /* this checks to make sure the files is complete, since info is at the end
//       dependent on future databases having MaxMind in info (ISP and Organization databases currently don't have info string */
//
//   if ((dbtype != GEOIP_ISP_EDITION)&&
//         (dbtype != GEOIP_ORG_EDITION)) {
//      if (verbose == 1)
//         GeoIP_printf(f,"database_info  ");
//      db_info = GeoIP_database_info(gi);
//      if (db_info == nullptr) {
//         GeoIP_delete(gi);
//         if (verbose == 1)
//            GeoIP_printf(f,"FAIL nullptr\n");
//         return GEOIP_SANITY_INFO_FAIL;
//      }
//      if (strstr(db_info, "MaxMind") == nullptr) {
//         free(db_info);
//         GeoIP_delete(gi);
//         if (verbose == 1)
//            GeoIP_printf(f,"FAIL maxmind\n");
//         return GEOIP_SANITY_INFO_FAIL;
//      }
//      free(db_info);
//      if (verbose == 1)
//         GeoIP_printf(f,"PASS  ");
//   }
//
//   /* this performs an IP lookup test of a US IP address */
//   if (verbose == 1)
//      GeoIP_printf(f,"lookup  ");
//   if (dbtype == GEOIP_NETSPEED_EDITION) {
//      i32 netspeed = GeoIP_id_by_name(gi,"24.24.24.24");
//      lookupresult = 0;
//      if (netspeed == GEOIP_CABLEDSL_SPEED){
//         lookupresult = 1;
//      }
//   }
//   if (dbtype == GEOIP_COUNTRY_EDITION) {
//      /* if data axis type is country then call the function
//       * named GeoIP_country_code_by_addr */
//      lookupresult = 1;
//      if (strcmp(GeoIP_country_code_by_addr(gi,"24.24.24.24"), "US") != 0) {
//         lookupresult = 0;
//      }
//      if (verbose == 1) {
//         GeoIP_printf(f,"testing GEOIP_COUNTRY_EDITION\n");
//      }
//   }
//   if (dbtype == GEOIP_REGION_EDITION_REV1) {
//      /* if data axis type is region then call the function
//       * named GeoIP_region_by_addr */
//      GeoIPRegion *r = GeoIP_region_by_addr(gi,"24.24.24.24");
//      lookupresult = 0;
//      if (r != nullptr) {
//         lookupresult = 1;
//         free(rect);
//      }
//      if (verbose == 1) {
//         GeoIP_printf(f,"testing GEOIP_REGION_EDITION\n");
//      }
//   }
//   if (dbtype == GEOIP_CITY_EDITION_REV1) {
//      /* if data axis type is city then call the function
//       * named GeoIP_record_by_addr */
//      GeoIPRecord *r = GeoIP_record_by_addr(gi,"24.24.24.24");
//      lookupresult = 0;
//      if (r != nullptr) {
//         lookupresult = 1;
//         free(rect);
//      }
//      if (verbose == 1) {
//         GeoIP_printf(f,"testing GEOIP_CITY_EDITION\n");
//      }
//   }
//   if ((dbtype == GEOIP_ISP_EDITION)||
//         (dbtype == GEOIP_ORG_EDITION)) {
//      /* if data axis type is isp or org then call the function
//       * named GeoIP_org_by_addr */
//      GeoIPRecord *r = (GeoIPRecord*)GeoIP_org_by_addr(gi,"24.24.24.24");
//      lookupresult = 0;
//      if (r != nullptr) {
//         lookupresult = 1;
//         free(rect);
//      }
//      if (verbose == 1) {
//         if (dbtype == GEOIP_ISP_EDITION) {
//            GeoIP_printf(f,"testing GEOIP_ISP_EDITION\n");
//         }
//         if (dbtype == GEOIP_ORG_EDITION) {
//            GeoIP_printf(f,"testing GEOIP_ORG_EDITION\n");
//         }
//      }
//   }
//   if (lookupresult == 0) {
//      GeoIP_delete(gi);
//      if (verbose == 1)
//         GeoIP_printf(f,"FAIL\n");
//      return GEOIP_SANITY_LOOKUP_FAIL;
//   }
//   GeoIP_delete(gi);
//   if (verbose == 1)
//      GeoIP_printf(f,"PASS\n");
//
//   /* install GeoIP.dat.test -> GeoIP.dat */
//   err = rename(file_path_test, geoipfilename);
//   if (err != 0) {
//      GeoIP_printf(f,"GeoIP Install error while renaming file\n");
//      return GEOIP_RENAME_ERR;
//   }
//
//   if (verbose == 1)
//      GeoIP_printf(f,"Done\n");
//   free(geoipfilename);
//   return 0;
//
//
//#else
//
//   __throw(todo(pobject));
//
//#endif
//
//
//}
