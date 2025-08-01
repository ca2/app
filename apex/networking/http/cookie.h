#pragma once


////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/prototype/payload.h"


class http_socket;


namespace http
{


   class CLASS_DECL_APEX cookie :
      virtual public ::subparticle
   {
   public:


      string         m_strName;
      string         m_strNameLow;
      ::payload      m_payload;
      string         m_strExpire;
      string         m_strPath;
      string         m_strDomain;
      bool           m_bSecure;
      string         m_strSameSite;


      cookie();
      cookie(const cookie & cookie);
      ~cookie() override;


      string get_cookie_string();

      cookie & operator = (::payload payload)
      {
         m_payload = payload;
         return *this;
      }


      cookie & operator = (const cookie & cookie);

      bool is_set()
      {
         return m_payload.is_set();
      }

      bool is_new()
      {
         return m_payload.is_new();
      }


      ::string as_string() const;


      //inline string to_string() const
      //{

      //   return m_payload.to_string();

      //}


      operator ::property() const
      {

         return ::property(m_strName,m_payload);

      }

   };



   class CLASS_DECL_APEX cookies :
      public pointer_array < cookie >
   {
   public:

      using ARRAY_BASE = pointer_array < ::http::cookie >;

      cookies();
      virtual ~cookies();


      ::collection::index find_cookie(const_char_pointer name);
      ::collection::index lowfind_cookie(const_char_pointer name);
      ::http::cookie & cookie(const_char_pointer name);
      ::http::cookie & lowcookie(const_char_pointer name);
      using  pointer_array < http::cookie >::add;
      void add(const ::scoped_string & scopedstr);
      void parse_header(const ::scoped_string & scopedstr);
      string get_cookie_header();
      character_count get_length(const_char_pointer name);
      bool set_cookie(
         const ::scoped_string & scopedstrKey,
         const ::payload & payload,
         const class time & time = 0_s,
         const ::scoped_string& strPath = nullptr,
         const ::scoped_string & scopedstrDomain = nullptr,
         const ::scoped_string & scopedstrSameSite = "Strict",
         bool bSecure = false);
      static string expire(const class time & time = 5_minute);


      http::cookie & operator [](const_char_pointer name);


      cookies & operator = (const cookies & cookies);


   };


} // namespace http


