// From acme::context by camilo on 2024-05-24 16:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "ace/primitive/primitive/quantum.h"


namespace ace
{


   class context :
      virtual public ::quantum
   {
   public:


      ::pointer < ::ace::shell > m_pshell;

      context();
      ~context() override;


      //virtual void on_set_platform();

      //virtual void set_platform(::platform::platform * pplatform);


      void initialize(::particle * pparticle) override;

      virtual void initialize_context();

      virtual void initialize_context_1();

      virtual void finalize_context();


      virtual void information_log(const char * psz);
      virtual void informationf_log(const char * psz,...);
      virtual void error_log(const char * psz);
      virtual void errorf_log(const char * psz,...);



virtual ::ace::shell * shell()


      virtual bool http_exists(const ::scoped_string & scopedstrUrl, ::property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, property_set & set);
      virtual ::file::enum_type http_get_type(const ::scoped_string & scopedstrUrl, ::payload * pvarQuery, property_set & set);


      virtual ::string http_text(const ::scoped_string & scopedstrUrl, const class ::time & timeTimeout = 5_min);
      virtual ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set, const class ::time & timeTimeout = 5_min);


      virtual void sync(::nano::http::get * pget);
      virtual void async(::nano::http::get * pget, const ::function < void(::nano::http::get *) > & callback);


      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, const class ::time & timeTimeout = 5_h);
      virtual void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set, const class ::time & timeTimeout = 5_h);


   };


} // namespace acme



