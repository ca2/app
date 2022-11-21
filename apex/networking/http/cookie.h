﻿#pragma once


////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/primitive/payload.h"


class http_socket;


namespace http
{


   class CLASS_DECL_APEX cookie :
      virtual public ::object
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


      string as_string() const override;


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


      index find_cookie(const char * name);
      index lowfind_cookie(const char * name);
      ::http::cookie & cookie(const char * name);
      ::http::cookie & lowcookie(const char * name);
      using  pointer_array < http::cookie >::add;
      void add(const char * psz);
      void parse_header(const char * psz);
      string get_cookie_header();
      strsize get_length(const char * name);
      bool set_cookie(
         const char * pszKey,
         const ::payload & payload,
         const ::duration & duration = 0_s,
         const char * pszDomain = nullptr,
         const char * pszPath = nullptr,
         bool bSecure = false);
      static string expire(const class ::duration & duration = 5_minute);


      using ARRAY_BASE::operator [];
      http::cookie & operator [](const char * name);


      cookies & operator = (const cookies & cookies);

   };


} // namespace http


