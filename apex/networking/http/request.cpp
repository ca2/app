#include "framework.h"
#include "request.h"
//#include "apex/id.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/system.h"
////#include "apex/networking/sockets/_.h"


namespace http
{


   request::request() :
      m_ostream(m_pmemfileBody=__new(memory_file))
   {

   }


   request::request(const request& src) :
      transaction(src),
      m_null(src.m_null),
      m_ostream(m_pmemfileBody=src.m_pmemfileBody)
   {

   }


   request::~request()
   {

   }






   // --------------------------------------------------------------------------------------
   void request::add_cookie(const ::scoped_string & scopedstrSetCookie)
   {
      m_cookies.add(scopedstrSetCookie);
   }


   // --------------------------------------------------------------------------------------
   void request::InitBody( memsize sz )
   {
      __UNREFERENCED_PARAMETER(sz);
      m_pmemfileBody->set_size(0);
      /*if (!m_file.get())
         m_file = ::pointer<IFile>e>(memory_new MemFile);
      DEBUG_ONLY(   else
         TRACE("Body data file already opened\n");*/
   }


   // --------------------------------------------------------------------------------------
   void request::write( const char *buf, memsize sz )
   {
      m_pmemfileBody->write({ buf, sz });
   }


   // --------------------------------------------------------------------------------------
   void request::CloseBody()
   {
      //m_file.close();
   }


   // --------------------------------------------------------------------------------------
   void request::ParseBody(::apex::context * pcontextUploadFile)
   {

      m_form.clear();

      auto psystem = acmesystem();

      auto purl = psystem->url();

      m_strQueryString = purl->object_get_query(m_strRequestUri);

      attr("query_string") = m_strQueryString;
      m_form.parse_query_string(m_strQueryString, m_strQueryString.length());
      m_form.request()         = m_form.get();
      attr("http_referer") = header("referer");
      if(m_atomHttpMethod == "put")
      {
         // skip following POST processing below
         return;
      }
      if(m_pmemfileBody->size() > 0)
      {
         m_form.parse_body(pcontextUploadFile, m_pmemfileBody, ContentType(), ContentLength());
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

      //   m_file = ::pointer<IFile>e>(nullptr);
      m_form.clear();
      m_cookies.erase_all();
      file()->set_size(0);
   }


   string request::a_url()
   {

      string strUrl = attr("http_protocol") + "://" + header("host") + attr("request_uri");

      return strUrl;

   }


} // namespace http

