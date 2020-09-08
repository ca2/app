#include "framework.h"


namespace sip
{


   transaction::transaction(::object * pobject) :
      ::object(pobject)
   {

   }

   transaction::transaction(const transaction & src) :
      ::object(src.get_context_application()),
      m_propertysetAttribute(src.m_propertysetAttribute),
      m_propertysetHeader(src.m_propertysetHeader)
   {

   }


   // --------------------------------------------------------------------------------------
   transaction::~transaction()
   {
   }



   property & transaction::header(const char * pszKey)
   {
      return m_propertysetHeader[pszKey];
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetAccept(const string & value)
   {
      header("Accept") = value;
   }


   string transaction::Accept()
   {
      return header("Accept");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetAcceptCharset(const string & value)
   {
      header("Accept-Charset") = value;
   }


   string transaction::AcceptCharset()
   {
      return header("Accept-Charset");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetAcceptEncoding(const string & value)
   {
      header("Accept-Encoding") = value;
   }


   string transaction::AcceptEncoding()
   {
      return header("Accept-Encoding");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetAcceptLanguage(const string & value)
   {
      header("Accept-Language") = value;
   }


   string transaction::AcceptLanguage()
   {
      return header("Accept-Language");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetConnection(const string & value)
   {
      header("Connection") = value;
   }


   string transaction::Connection()
   {
      return header("Connection");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetContentType(const string & value)
   {
      header("Content-Type") = value;
   }


   string transaction::ContentType()
   {
      return header("Content-Type");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetContentLength(long value)
   {
      header("Content-Length") = (i64) value;
   }


   long transaction::ContentLength()
   {
      return atol(header("Content-Length"));
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetHost(const string & value)
   {
      header("Host") = value;
   }


   string transaction::Host()
   {
      return header("Host");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetPragma(const string & value)
   {
      header("Pragma") = value;
   }


   string transaction::Pragma()
   {
      return header("Pragma");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetReferer(const string & value)
   {
      header("Referer") = value;
   }


   string transaction::Referer()
   {
      return header("Referer");
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetUserAgent(const string & value)
   {
      header("User-Agent") = value;
   }


   string transaction::UserAgent()
   {
      return header("User-Agent");
   }


   // --------------------------------------------------------------------------------------
   property_set & transaction::headers()
   {
      return m_propertysetHeader;
   }


   // --------------------------------------------------------------------------------------
   void transaction::clear()
   {
      m_propertysetAttribute.clear();
      m_propertysetHeader.clear();
      m_cookies.remove_all();
   }

   property & transaction::attr(const char * psz)
   {
      return m_propertysetAttribute[psz];
   }

   property_set & transaction::attrs()
   {
      return m_propertysetAttribute;
   }

   http::cookies & transaction::cookies()
   {
      return m_cookies;
   }


} // namespace sip




