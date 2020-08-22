#include "framework.h" 
#include "aura/id.h"
#include "aura/net/sockets/_.h"


namespace http
{


   request::request() :
      m_ostream(&m_memfileBody)
   {

   }


   request::request(const request& src) :
      transaction(src),
      m_null(src.m_null),
      m_ostream(&m_memfileBody)
   {

      m_memfileBody = src.m_memfileBody;

   }


   request::~request()
   {

   }






   // --------------------------------------------------------------------------------------
   void request::add_cookie(const char * pszSetCookie)
   {
      m_cookies.add(pszSetCookie);
   }


   // --------------------------------------------------------------------------------------
   void request::InitBody( memsize sz )
   {
      UNREFERENCED_PARAMETER(sz);
      m_memfileBody.set_size(0);
      /*if (!m_file.get())
         m_file = pointer<IFile>(new MemFile);
      DEBUG_ONLY(   else
         TRACE("Body data file already opened\n");*/
   }


   // --------------------------------------------------------------------------------------
   void request::write( const char *buf, memsize sz )
   {
      m_memfileBody.write(buf, sz);
   }


   // --------------------------------------------------------------------------------------
   void request::CloseBody()
   {
      //m_file.close();
   }


   // --------------------------------------------------------------------------------------
   void request::ParseBody()
   {

      m_form.clear();

      m_strQueryString = System.url().object_get_query(m_strRequestUri);
      attr(__id(query_string)) = m_strQueryString;
      m_form.parse_query_string(m_strQueryString, m_strQueryString.get_length());
      m_form.request()         = m_form.get();
      attr(__id(http_referer)) = header(__id(referer));
      if(m_idHttpMethod == __id(put))
      {
         // skip following POST processing below
         return;
      }
      if(m_memfileBody.get_size() > 0)
      {
         m_form.parse_body(&m_memfileBody, ContentType(), ContentLength());
      }
      m_form.request().merge(m_form.post());
   }





   // --------------------------------------------------------------------------------------
   void request::clear()
   {
      transaction::clear();
      /*   attr("http_method") = "";
         attr("http_protocol") = "";
         attr("request_uri") = "";
         attr("remote_host") = "";
         attr("server_name") = "";
         attr("server_port") = 0;
         attr("https") = false;*/

      //   m_file = pointer<IFile>(nullptr);
      m_form.clear();
      m_cookies.remove_all();
      file().set_size(0);
   }

} // namespace http

