//
// Created by camilo on 2024-10-29 00:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_acme.h"


namespace platform
{


   bool acme_http_layer::exists(const ::url::url& url, ::property_set & set)
   {
      return false;
   }


   ::file::enum_type acme_http_layer::get_type(const ::url::url& url, ::property_set & set)
   {
      return ::file::e_type_unknown;
   }


   ::file::enum_type acme_http_layer::get_type(const ::url::url& url, ::payload* pvarQuery, ::property_set & set)
   {
      return ::file::e_type_unknown;
   }


   ::string acme_http_layer::get(const ::url::url& url, const class ::time& timeTimeout)
   {
      return {};
   }


   ::string acme_http_layer::get(const ::url::url& url, ::property_set & set, const class ::time& timeTimeout)
   {
      return {};
   }


   ::url::url acme_http_layer::get_effective_url(const ::url::url& url)
   {
      return url;
   }


   //void http_sync(::nano::http::get * defer_get){}
   //void http_async(::nano::http::get * defer_get, const ::function < void(::nano::http::get *) > & callback){}


   void acme_http_layer::download(const ::payload& payloadFile, const ::url::url& url,
                                  const class ::time& timeTimeout)
   {
   }


   void acme_http_layer::download(const ::payload& payloadFile, const ::url::url& url, ::property_set & set,
                                  const class ::time& timeTimeout)
   {
   }


   bool acme_http_layer::put(const ::url::url& url, memory_base& memory, ::property_set & set)
   {
      return false;
   }


   bool acme_http_layer::put(const ::url::url& url, file_pointer pfile, ::property_set & set)
   {

      return false;

   }


   bool acme_http_layer::put(const ::url::url& url, memory_base* pmemory, ::property_set & set)
   {

return false;

   }


   //bool put(const ::url::url & url, file_pointer  pfile, ::property_set & set){}

   //::url::url get_effective_url(const ::url::url & url){}


}
