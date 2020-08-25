#pragma once


namespace http
{


   class CLASS_DECL_BASE transaction :
      virtual public ::context_object
   {
   public:


      property_set         m_propertysetHeader;
      property_set         m_propertysetAttribute;
      http::cookies        m_cookies;
      string               m_null;


      transaction();
      transaction(const transaction & src);
      virtual ~transaction();

      

      void SetAccept(const string & value);
      string Accept();

      void SetAcceptCharset(const string & value);
      string AcceptCharset();

      void SetAcceptEncoding(const string & value);
      string AcceptEncoding();

      void SetAcceptLanguage(const string & value);
      string AcceptLanguage();

      void SetConnection(const string & value);
      string Connection();

      void SetContentType(const string & value);
      string ContentType();

      void SetContentLength(memsize value);
      memsize ContentLength();

      void SetHost(const string & value);
      string Host();

      void SetPragma(const string & value);
      string Pragma();

      void SetReferer(const string & value);
      string Referer();

      void SetUserAgent(const string & value);
      string UserAgent();

      property_set & headers();
      property & header(id idKey);
      
      property_set & attrs();
      property & attr(id idKey);


      http::cookies & cookies();

      virtual void clear();


   }; // end of class

   inline property_set & transaction::attrs()
   {
      return m_propertysetAttribute;
   }

   inline property & transaction::attr(id idKey)
   {
      return m_propertysetAttribute[idKey];
   }

   inline property_set & transaction::headers()
   {
      return m_propertysetHeader;
   }

   inline property & transaction::header(id idKey)
   {
      return m_propertysetHeader[idKey];
   }

   inline http::cookies & transaction::cookies()
   {
      return m_cookies;
   }


} // namespace http



