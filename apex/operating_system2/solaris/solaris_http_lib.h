/*
 *  Http put/get mini lib
 *  written by L. Demailly
 *  (c) 1998 Laurent Demailly - http://www.demailly.com/~dl/
 *  (c) 1996 Observatoire de Paris - Meudon - France
 *  see LICENSE for terms, conditions and DISCLAIMER OF ALL WARRANTIES
 *
 * $Id: http_lib.h,v 1.4 1998/09/23 06:14:15 dl Exp $
 *
 */

#pragma once

/* declarations */



class CLASS_DECL_APEX tiny_http
{
public:

   typedef enum
   {
      /* Client side errors */
      ERRHOST=-1, /* No such host */
      ERRSOCK=-2, /* Can't create socket */
      ERRCONN=-3, /* Can't connect to host */
      ERRWRHD=-4, /* Write error on socket while writing header */
      ERRWRDT=-5, /* Write error on socket while writing data */
      ERRRDHD=-6, /* Read error on socket while reading result */
      ERRPAHD=-7, /* Invalid answer from data server */
      ERRNULL=-8, /* Null data pointer */
      ERRNOLG=-9, /* No/Bad length in header */
      ERRMEM=-10, /* Can't allocate memory */
      ERRRDDT=-11,/* Read error while reading data */
      ERRURLH=-12,/* Invalid url - must start with 'http://' */
      ERRURLP=-13,/* Invalid port in url */


      /* Return code by the server */
      ERR400=400, /* Invalid query */
      ERR403=403, /* Forbidden */
      ERR408=408, /* Request timeout */
      ERR500=500, /* Server error */
      ERR501=501, /* Not implemented */
      ERR503=503, /* Service overloaded */

      /* Succesful results */
      OK0 = 0,   /* successfull parse */
      OK201=201, /* Ressource succesfully created */
      OK200=200  /* Ressource succesfully read */
   } http_retcode;

   typedef enum
   {
      CLOSE,  /* Close the socket after the query (for put) */
      KEEP_OPEN /* Keep it open */
   } querymode;



   string    m_strHttpServer;
   int         m_iHttpPort;
   string    m_strProxyServer;
   int           m_iHttpProxyPort;
   string            m_strUserAgent;
   ::file::path      m_strFileName;

   string    m_strContentType;

   tiny_http();
   ~tiny_http();

   http_retcode t_put(const_char_pointer data, int length, int overwrite, void (*callback)(void *, int, dword_ptr) = nullptr, void * callback_param = nullptr);
   http_retcode t_get(char ** pdata, int * plength, void (*callback)(void *, int, dword_ptr) = nullptr, void * callback_param = nullptr);
   http_retcode t_delete() ;
   http_retcode t_head(int *plength);
   http_retcode t_parse_url(const_char_pointer url);

   int t_read_line (int fd,char *buffer, int maximum) ;
   int t_read_buffer (int fd,char *buffer, int maximum, void (*callback)(void *, int, dword_ptr) = nullptr, void * callback_param = nullptr) ;

   http_retcode t_query(const_char_pointer command, const_char_pointer url, const_char_pointer additional_header, querymode mode, char* data, int length, int *pfd);
};


