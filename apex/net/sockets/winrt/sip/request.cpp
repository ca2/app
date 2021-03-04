#include "framework.h"


namespace sip
{


   request::request(::layered * pobjectContext) :
      ::object(pobject),
      transaction(pobject),
      m_file(pobject),
      m_form(pobject)
   {
   }


   request::request(const request& src) :
   ::object(((request&) src).get_context_application()),
   transaction(src),
   m_null(src.m_null),
   m_file(((request&) src).get_context_application()),
   m_form(((request&) src).get_context_application())
   {
      m_file = src.m_file;
   }



   request::~request()
   {
   }






   void request::add_cookie(const char * pszSetCookie)
   {
      m_cookies.add(pszSetCookie);
   }


   void request::InitBody( memsize sz )
   {
      UNREFERENCED_PARAMETER(sz);
      m_file.Truncate(0);
      /*if (!m_file.get())
         m_file = std::auto_ptr<IFile>(new MemFile);
   DEBUG_ONLY(   else
         TRACE("Body data file already opened\n");*/
   }


   void request::write( const char *buf, memsize sz )
   {
         m_file.write(buf, sz);
   }


   void request::CloseBody()
   {
      //m_file.close();
   }


   void request::ParseBody()
   {
      //Utility::ncmap<string>::const_iterator it;
      m_form.clear();
      if(attrs().has_property("request_uri"))
      {
         attr("query_string") = System->url().object_get_query(attr("request_uri"));
         string str = attrs()["query_string"];
         m_form.parse_query_string(str);
      }
      attr("http_host") = header("host");
      attr("http_referer") = header("referer");
      if(m_file.get_size() > 0)
      {
         m_form.parse_body(&m_file, ContentType(), ContentLength());
      }
      m_form.request().merge(m_form.get());
      m_form.request().merge(m_form.post());
   }


   // --------------------------------------------------------------------------------------
   http::form & request::form()
   {
      return m_form;
   }



   // --------------------------------------------------------------------------------------
   void request::clear()
   {
      transaction::clear();
   /*   attr("http_method") = "";
      attr("http_protocol") = "";
      attr("request_uri") = "";
      attr("remote_address") = "";
      attr("remote_host") = "";
      attr("server_name") = "";
      attr("server_port") = 0;
      attr("https") = false;*/

   //   m_file = std::auto_ptr<IFile>(nullptr);
      m_form.clear();
      m_cookies.remove_all();
      file().Truncate(0);
   }


} // namespace sip




