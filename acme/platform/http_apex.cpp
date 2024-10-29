//
// Created by camilo on 2024-10-28 23:55 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_apex.h"


namespace platform
{


   void apex_http_layer::http_system_destruct()
   {


   }


   void apex_http_layer::get(::http::message* phttpmessage)
   {


   }


   bool apex_http_layer::http_get(::pointer<::sockets::http_client_socket>& m_psocket, const ::url::url& url,
                                  property_set& set)
   {

      return false;

   }


   bool apex_http_layer::get(::http::session& session, const ::url::url& url, string& str, property_set& set)
   {

      return false;

   }


   string apex_http_layer::get(::http::session& session, const ::url::url& url, property_set& set)
   {

      return {};

   }


   //virtual void set_proxy_auth(::account::user * puser, ::sockets::http_client_socket * pfile){}
   //virtual void clean_proxy_auth(::account::user * puser){}


   bool apex_http_layer::open(::pointer<::sockets::http_session>& psession, const ::url::connect& connect,
                              property_set& set, const ::string& strVersion)
   {

      return false;

   }


   bool apex_http_layer::request(::pointer<::sockets::http_session>& spsession, const ::url::request& request,
                                         property_set& set)
   {

      return false;

   }


   ::payload apex_http_layer::get(const ::url::url& url, property_set& set)
   {

      return {};

   }


   bool apex_http_layer::request(const ::scoped_string& scopedstrMethod, const ::url::url& url, property_set& set)
   {

      return false;

   }


   bool apex_http_layer::download(::pointer<::sockets::http_session>& psession, const ::scoped_string& scopedstrRequest,
                         ::payload payloadFile, property_set& set)
   {

      return false;

   }


   bool apex_http_layer::download(const ::url::url& url, ::payload payloadFile, property_set& set)
   {

      return false;

   }


   bool apex_http_layer::put(const ::url::url& url, memory_base& memory, property_set& set)
   {

      return false;

   }


   bool apex_http_layer::put(const ::url::url& url, file_pointer pfile, property_set& set)
   {

      return false;

   }


   bool apex_http_layer::put(const ::url::url& url, memory_base* pmemory, property_set& set)
   {

      return false;

   }


   //virtual bool put(const ::url::url & url, file_pointer  pfile, property_set & set){}


   ::url::url apex_http_layer::get_effective_url(const ::url::url& url)
   {

      return url;

   }


   void apex_http_layer::defer_auto_initialize_proxy_configuration()
   {


   }


   void apex_http_layer::auto_config_proxy(i32 i)
   {


   }


   i32 apex_http_layer::auto_config_proxy_count()
   {

      return 0;

   }


   void apex_http_layer::config_proxy(const ::url::url& url, ::sockets::http_tunnel* psocket)
   {


   }


   // void apex_http_layer::config_proxy(const ::url::url& url, proxy* pproxy)
   // {
   //
   //
   // }


   // bool apex_http_layer::try_pac_script(const ::scoped_string& scopedstrScriptUrl, const ::url::url& url, proxy* pproxy)
   // {
   //
   //    return false;
   //
   // }


   string apex_http_layer::gmdate(posix_time t)
   {

      return {};

   }


   // pac* apex_http_layer::get_pac(const ::url::url& url)
   // {
   //
   //    return nullptr;
   //
   // }


   // proxy* apex_http_layer::get_proxy(const ::url::url& url)
   // {
   //
   //    return nullptr;
   //
   // }


   //virtual void on_auth(property_set & set, ::apex::application * papp, string & strUrl, string & strSessId, ::pointer<::account::user>& puser){}

   void apex_http_layer::http_application_destruct()
   {


   }


   property_set& apex_http_layer::process_set(property_set& set, const ::url::url& url)
   {

      return set;

   }


   //DECLARE_MESSAGE_HANDLER(get){}

   bool apex_http_layer::get(::pointer<::sockets::http_client_socket>& psocket, const ::url::url& url, property_set& set)
   {

      return false;

   }


   //virtual string api_get(const ::url::url & url, property_set & set){}
   //virtual string api_get(const ::url::url & url){}

   //virtual bool exists(const ::url::url & url, property_set & set){}
   bool apex_http_layer::exists(const ::url::url& url, property_set& set)
   {

      return false;

   }


   ::file::enum_type apex_http_layer::get_type(const ::url::url& url, property_set& set)
   {

      return ::file::e_type_unknown;

   }


   ::file::enum_type apex_http_layer::get_type(const ::url::url& url, ::payload* pvarQuery, property_set& set)
   {

      return ::file::e_type_unknown;

   }


   ::payload apex_http_layer::length(const ::url::url& url, property_set& set)
   {

      return {};

   }


   //virtual ::payload length(const ::url::url & url, property_set & set){}
   ::payload apex_http_layer::length(const ::url::url& url, ::payload* pvarQuery, property_set& set)
   {

      return {};

   }


   //virtual string get(const ::url::url & url, property_set & set){}
   void apex_http_layer::_get(const ::url::url& url, property_set& set)
   {


   }


   void apex_http_layer::get(string& str, const ::url::url& url, property_set& set)
   {


   }


   void apex_http_layer::get(memory_base* pmemory, const ::url::url& url, property_set& set)
   {


   }


   void apex_http_layer::perform(::nano::http::get* pget)
   {


   }


   //virtual bool request(const ::scoped_string & scopedstrRequest, const ::url::url & url, property_set & set){}

   //virtual bool download(::pointer<::sockets::http_session>& psession, const ::url::url & url, ::payload payloadFile, property_set & set){}
   //virtual bool download(const ::url::url & url, ::payload payloadFile, property_set & set){}

   string apex_http_layer::locale_schema_url(const ::url::url& url, const ::scoped_string& scopedstrLocale,
                                    const ::scoped_string& scopedstrSchema)
   {

      return {};

   }


   string apex_http_layer::get_locale_schema(const ::url::url& url, const ::scoped_string& scopedstrLocale,
                                    const ::scoped_string& scopedstrSchema)
   {

      return {};

   }


} // namespace platform
