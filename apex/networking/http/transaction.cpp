#include "framework.h"
#include "transaction.h"
#include "apex/id.h"


namespace http
{


   transaction::transaction()
   {

   }


   transaction::transaction(const transaction & src) :
      m_propertysetAttribute(src.m_propertysetAttribute),
      m_propertysetHeader(src.m_propertysetHeader)
   {

   }


   transaction::~transaction()
   {

   }


   transaction & transaction::operator = (const transaction & transaction)
   {

      if(this != &transaction)
      {

         m_propertysetHeader = transaction.m_propertysetHeader;
         m_propertysetAttribute = transaction.m_propertysetAttribute;
         m_cookies = transaction.m_cookies;
         m_null = transaction.m_null;

      }

      return *this;

   }


   void transaction::SetAccept(const string & value)
   {

      header("accept") = value;

   }


   string transaction::Accept()
   {

      string str;

      str = header("accept");

      return str;

   }


   void transaction::SetAcceptCharset(const string & value)
   {
      
      header("Accept-Charset") = value;

   }


   string transaction::AcceptCharset()
   {
      
      string str;
      
      str = header("Accept-Charset");

      return str;

   }


   void transaction::SetAcceptEncoding(const string & value)
   {

      header("Accept-Encoding") = value;

   }


   string transaction::AcceptEncoding()
   {
   
      string str;
      
      str = header("Accept-Encoding");

      return str;

   }


   void transaction::SetAcceptLanguage(const string & value)
   {
      
      header("Accept-Language") = value;

   }


   string transaction::AcceptLanguage()
   {
      
      string str;
      
      str = header("Accept-Language");

      return str;

   }


   void transaction::SetConnection(const string & value)
   {
   
      header("connection") = value;

   }


   string transaction::Connection()
   {
   
      string str;
      
      str = header("connection");

      return str;

   }


   void transaction::SetContentType(const string & value)
   {
   
      header("content_type") = value;

   }


   string transaction::ContentType()
   {
      
      string str;
      
      str = header("content_type");

      return str;

   }


   void transaction::SetContentLength(memsize value)
   {
   
      header("content_length") = value;

   }


   memsize transaction::ContentLength()
   {
   
      return header("content_length").iptr();

   }


   void transaction::SetHost(const string & value)
   {
   
      header("Host") = value;

   }


   string transaction::Host()
   {

      string str;
      
      str = header("Host");

      return str;

   }


   void transaction::SetPragma(const string & value)
   {

      header("Pragma") = value;

   }


   string transaction::Pragma()
   {
      
      string str;
      
      str = header("Pragma");

      return str;

   }


   void transaction::SetReferer(const string & value)
   {
   
      header("Referer") = value;

   }


   string transaction::Referer()
   {
      
      string str;
      
      str = header("Referer");

      return str;

   }


   void transaction::SetUserAgent(const string & value)
   {
      
      header("User-Agent") = value;

   }


   string transaction::UserAgent()
   {
      
      string str;
      
      str = header("User-Agent");

      return str;

   }


   void transaction::clear()
   {
      
      m_propertysetAttribute.clear();

      m_propertysetHeader.clear();

      m_cookies.erase_all();

   }


} // namespace http



