#pragma once

namespace sip
{

   class CLASS_DECL_AURA transaction :
      virtual public ::object
   {
   public:


      property_set m_propertysetHeader;
      property_set m_propertysetAttribute;
      http::cookies m_cookies;
      string m_null;


      transaction(::object * pobject);
      transaction(const transaction & src);
      virtual ~transaction();

      property & header(const ::string & pszKey);

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

      void SetContentLength(long value);
      long ContentLength();

      void SetHost(const string & value);
      string Host();

      void SetPragma(const string & value);
      string Pragma();

      void SetReferer(const string & value);
      string Referer();

      void SetUserAgent(const string & value);
      string UserAgent();

      property_set & headers();

      property_set & attrs();

      property & attr(const ::string & psz);
      http::cookies & cookies();

      virtual void clear();


      transaction & operator = (const transaction & transaction);


   }; // end of class


} // namespace sip




