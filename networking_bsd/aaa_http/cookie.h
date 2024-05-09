#pragma once


class http_socket;


namespace http
{


   class CLASS_DECL_APEX cookie :
      virtual public object
   {
   public:


      string         m_strName;
      string         m_strNameLow;
      ::payload      m_varValue;
      string         m_strExpire;
      string         m_strPath;
      string         m_strDomain;
      bool           m_bSecure;


      cookie();
      cookie(const cookie & cookie);
      ~cookie() override;


      string get_cookie_string();

      cookie & operator = (::payload payload)
      {
         m_varValue = payload;
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


      string get_string() const override;


      //inline string to_string() const
      //{

      //   return m_varValue.to_string();

      //}


      operator property() const
      {

         return property(m_strName,m_varValue);

      }

   };



   class CLASS_DECL_APEX cookies :
      public pointer_array < cookie >
   {
   public:

      using ARRAY_BASE = pointer_array < ::http::cookie >;

      cookies();
      virtual ~cookies();


      ::collection::index find_cookie(const char * name);
      ::collection::index lowfind_cookie(const char * name);
      ::http::cookie & cookie(const char * name);
      ::http::cookie & lowcookie(const char * name);
      using  pointer_array < http::cookie >::add;
      void add(const ::scoped_string & scopedstr);
      void parse_header(const ::scoped_string & scopedstr);
      string get_cookie_header();
      strsize get_length(const char * name);
      bool set_cookie(
         const ::scoped_string & scopedstrKey,
         const ::payload & payload,
         const ::duration & duration = 0_s,
         const ::scoped_string & scopedstrDomain = nullptr,
         const ::file::path & path = nullptr,
         bool bSecure = false);
      static string expire(const class ::duration & duration = 5_minute);


      using ARRAY_BASE::operator [];
      http::cookie & operator [](const char * name);


      cookies & operator = (const cookies & cookies);

   };


} // namespace http


