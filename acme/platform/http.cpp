//
// Created by camilo on 2024-10-24 21:31 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/http/get.h"
#include "acme/nano/http/http.h"


namespace platform
{


   http::http()
   {

      
   }


   http::~http()
   {


   }


   bool http::exists(const ::url::url & url, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }


   ::file::enum_type http::get_type(const ::url::url & url, ::property_set & set)
   {

      throw ::interface_only();

      return ::file::e_type_unknown;

   }


   ::file::enum_type http::get_type(const ::url::url & url, ::payload * pvarQuery, ::property_set & set)
   {

      throw ::interface_only();

      return ::file::e_type_unknown;

   }



   ::string http::get(const ::url::url & url, const class ::time & timeTimeout)
   {

      auto defer_get = create_newø < ::nano::http::get >();

      defer_get->m_url = url;

      defer_get->m_timeSyncTimeout = timeTimeout;

      defer_get->call();

      ::string str = defer_get->get_memory_response()->as_utf8();

      return str;

   }


   ::string http::get(const ::url::url & url, ::property_set & set, const class ::time & timeTimeout)
   {

      auto pnanohttpget = createø < ::nano::http::get >();

      pnanohttpget->m_url = url;

      pnanohttpget->m_ppropertyset = &set;

      pnanohttpget->m_timeSyncTimeout = timeTimeout;

      pnanohttpget->want_memory_response();

      pnanohttpget->call();

      ::string str;
      
      auto pmemory = pnanohttpget->get_memory_response();

      str = pmemory->as_utf8();

      return str;

   }


   ::url::url http::get_effective_url(const ::url::url& url, ::property_set & set)
   {

      return nano()->http()->get_effective_url(url, set);

   }


   void http::download(const ::payload & payloadFile, const ::url::url & url, const class ::time & timeTimeout)
   {

      auto pfile = file_system()->get_writer(payloadFile);

      auto pnanohttpget = create_newø < ::nano::http::get >();

      pnanohttpget->m_url = url;

      pnanohttpget->m_timeSyncTimeout =  timeTimeout;

      pnanohttpget->call();

      pfile->write(*pnanohttpget->get_memory_response());

      pfile->seek_to_begin();

   }


   void http::download(const ::payload & payloadFile, const ::url::url & url, ::property_set & set, const class ::time & timeTimeout)
   {

      auto pfile = file_system()->get_writer(payloadFile,
         ::file::e_open_create
         | ::file::e_open_defer_create_directory);

      auto phttpget = createø < ::nano::http::get >();

      phttpget->m_url = url;

      phttpget->m_ppropertyset = &set;

      phttpget->want_memory_response();

      phttpget->m_timeSyncTimeout =  timeTimeout;

      phttpget->call();

      auto pmemory = phttpget->get_memory_response();

      pfile->write(*pmemory);

      pfile->seek_to_begin();

   }


   bool http::put(const ::url::url & url, memory_base & memory, ::property_set & set)
   {

      throw ::interface_only();

      return false;


   }


   bool http::put(const ::url::url & url, file_pointer  pfile, ::property_set & set)
   {

      throw ::interface_only();

      return false;


   }


   bool http::put(const ::url::url & url, memory_base * pmemory, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }
   //virtual bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set);


} // namespace platform


