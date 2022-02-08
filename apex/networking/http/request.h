#pragma once


#include "form.h"
#include "transaction.h"


namespace http
{

   class form;


   class CLASS_DECL_APEX request : 
      public transaction
   {
   public:


      string                           m_strRequestUri;
      string                           m_strQueryString;
      string                           m_strHttpHost;
      atom                               m_atomHttpMethod;
      memory_file                      m_memfileBody;
      ::text_stream                    m_ostream;
      string                           m_null;
      http::form                       m_form;


      request();
      request(const request& src);
      ~request();


      /** Cookies */
      void add_cookie(const char * pszSetCookie);

      /** open file for body data */
      void InitBody( memsize sz );

      /** write body data */
      void write( const char *buf, memsize sz );

      /** No more writing */
      void CloseBody();

      void ParseBody();

      http::form & form();

      ::text_stream & ostream()  { return m_ostream; }
      ::file::file & file()      { return m_memfileBody; }

      virtual void clear();

      virtual string a_url();

   }; // end of class



   // --------------------------------------------------------------------------------------
   inline http::form & request::form()
   {
      return m_form;
   }


} // namespace http




