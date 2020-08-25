#pragma once


class http_socket;


namespace http
{


   class CLASS_DECL_BASE cookie :
      virtual public object
   {
   public:


      string         m_strName;
      string         m_strNameLow;
      var            m_varValue;
      string         m_strExpire;
      string         m_strPath;
      string         m_strDomain;
      bool           m_bSecure;


      cookie();
      cookie(const cookie & cookie);
      virtual ~cookie();


      string get_cookie_string();

      cookie & operator = (var var)
      {
         m_varValue = var;
         return *this;
      }


      cookie & operator = (const cookie & cookie);

      bool is_set()
      {
         return m_varValue.is_set();
      }

      bool is_new()
      {
         return m_varValue.is_new();
      }


      inline void to_string(string & str) const override
      {

         m_varValue.to_string(str);

      }


      inline string to_string() const
      {

         return m_varValue.to_string();

      }


      operator property() const
      {

         return property(m_strName,m_varValue);

      }

   };



   class CLASS_DECL_BASE cookies :
      public __pointer_array(cookie)
   {
   public:

      using ARRAY_BASE = __pointer_array(::http::cookie);

      cookies();
      virtual ~cookies();


      index find_cookie(const char * name);
      index lowfind_cookie(const char * name);
      ::http::cookie & cookie(const char * name);
      ::http::cookie & lowcookie(const char * name);
      using  __pointer_array(http::cookie)::add;
      void add(const char * psz);
      void parse_header(const char * psz);
      string get_cookie_header();
      strsize get_length(const char * name);
      bool set_cookie(
         const char * pszKey,
         const ::var & var,
         const ::duration & duration = 0,
         const char * pszDomain = nullptr,
         const char * pszPath = nullptr,
         bool bSecure = false);
      static string expire(const ::duration & duration = 5_min);


      using ARRAY_BASE::operator [];
      http::cookie & operator [](const char * name);


      cookies & operator = (const cookies & cookies);

   };


} // namespace http


