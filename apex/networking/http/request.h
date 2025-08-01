#pragma once


#include "form.h"
#include "transaction.h"
#include "acme/filesystem/file/binary_stream.h"


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
      atom                             m_atomHttpMethod;
      memory_file_pointer              m_pmemfileBody;
      ::binary_stream                  m_binarystreamOutput;
      string                           m_null;
      http::form                       m_form;
      ::url::url                       m_url;
      ::url::url                       m_urlHandRoot;


      request();
      request(const request& src);
      ~request();


      /** Cookies */
      void add_cookie(const ::scoped_string & scopedstrSetCookie);

      /** open file for body data */
      void InitBody( memsize sz );

      /** write body data */
      void write( const_char_pointer buf, memsize sz );

      /** No more writing */
      void CloseBody();

      void ParseBody(::platform::context * pcontextUploadFile);

      http::form & form();

      ::binary_stream & ostream()  { return m_binarystreamOutput; }
      ::memory_file * file()      { return m_pmemfileBody; }

      virtual void clear();

      virtual string a_url();

   }; // end of class



   // --------------------------------------------------------------------------------------
   inline http::form & request::form()
   {
      return m_form;
   }


} // namespace http




