//
// Created by camilo on 2024-10-24 19:05 <3ThomasBorregaardSorensen
//
#pragma once


#include "http_acme.h"
#include "http_apex.h"
#include "acme/platform/department.h"


namespace platform
{


   class CLASS_DECL_ACME http :
      virtual public ::acme::department,
      virtual public ::platform::acme_http_layer_t,
      virtual public ::platform::apex_http_layer_t,
      virtual public ::platform::acme_http_layer,
      virtual public ::platform::apex_http_layer
   {
   public:


      // ::property_set    m_setHttp;


      http();
      ~http() override;


      virtual bool exists(const ::url::url& url, ::property_set& set) override;


      virtual ::file::enum_type get_type(const ::url::url& url, property_set& set) override;


      virtual ::file::enum_type get_type(const ::url::url& url, ::payload* pvarQuery, property_set& set) override;


      using ::platform::apex_http_layer::get;
      virtual ::string get(const ::url::url& url, const class ::time& timeTimeout = 5_min) override;


      virtual ::string get(const ::url::url& url, ::property_set& set, const class ::time& timeTimeout = 5_min) override;


      virtual ::url::url get_effective_url(const ::url::url& url) override;


      //virtual void http_sync(::nano::http::get * pget);
      //virtual void http_async(::nano::http::get * pget, const ::function < void(::nano::http::get *) > & callback);


      virtual void download(const ::payload& payloadFile, const ::url::url& url, const class ::time& timeTimeout = 5_h) override;


      virtual void download(const ::payload& payloadFile, const ::url::url& url, ::property_set& set,
                            const class ::time& timeTimeout = 5_h) override;

      virtual bool put(const ::url::url & url, memory_base & memory, property_set & set) override;
      virtual bool put(const ::url::url & url, file_pointer  pfile, property_set & set) override;
      virtual bool put(const ::url::url & url, memory_base * pmemory, property_set & set) override;
      //virtual bool put(const ::url::url & url, file_pointer  pfile, property_set & set);

      //virtual ::url::url get_effective_url(const ::url::url & url);


   };


} // namespace platform



