#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sip
{


   transaction::transaction(::object * pobject) :
      ::object(pobject)
   {

   }


   transaction::transaction(const transaction & src) :
      ::object(src.get_application()),
      m_propertysetAttribute(src.m_propertysetAttribute),
      m_propertysetHeader(src.m_propertysetHeader)
   {

   }


   transaction::~transaction()
   {

   }


   property & transaction::header(const ::string & pszKey)
   {

      return m_propertysetHeader[pszKey];

   }


   void transaction::SetAccept(const string & value)
   {

      header(__id(accept)) = value;

   }


   string transaction::Accept()
   {

      return header(__id(accept));

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
      header(__id(connection)) = value;
   }


   string transaction::Connection()
   {
      return header(__id(connection));
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetContentType(const string & value)
   {
      header(__id(content_type)) = value;
   }


   string transaction::ContentType()
   {
      return header(__id(content_type));
   }



   // --------------------------------------------------------------------------------------
   void transaction::SetContentLength(long value)
   {
      header(__id(content_length)) = (i64) value;
   }


   long transaction::ContentLength()
   {
      return atol(header(__id(content_length)));
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
      m_cookies.erase_all();
   }

   property & transaction::attr(const ::string & psz)
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

   transaction & transaction::operator = (const transaction & transaction)
   {

      if(this != &transaction)
      {

         m_propertysetHeader     = transaction.m_propertysetHeader;
         m_propertysetAttribute  = transaction.m_propertysetAttribute;
         m_cookies               = transaction.m_cookies;
         m_null                  = transaction.m_null;

      }

      return *this;

   }


} // namespace sip




