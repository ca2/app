// Created by camilo on 2024-08-29 12:15 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace url
{


   class CLASS_DECL_ACME url_context :
      virtual public ::acme::department
   {
   public:

      
      url_context();
      ~url_context() override;


   };


   inline bool is(const ::scoped_string& scopedstr)
   {

      return ::url::url(scopedstr).is();

   }


   CLASS_DECL_ACME ::string request_set_href(const ::scoped_string& scopedstrRequest, const ::scoped_string& scopedstrHref);
   CLASS_DECL_ACME ::string parameter_erased(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrKey);
   CLASS_DECL_ACME ::string parameter_set(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string query_parameter_set(const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);
   CLASS_DECL_ACME void erase_parameter(::string & str, const ::scoped_string& scopedstrKey);
   CLASS_DECL_ACME void set_parameter(::string & str, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);
   CLASS_DECL_ACME void query_set_parameter(::string& strQuery, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string path_join_query(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrQuery);
   CLASS_DECL_ACME string __parameter_erased(const ::scoped_string& scopedstr, character_count iStartParam, const ::scoped_string& scopedstrKey);
   CLASS_DECL_ACME bool __has_parameter_replace(::string& str, const ::scoped_string& scopedstr, character_count iStart, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter);
   CLASS_DECL_ACME bool __get_parameter(::string& strParameter, const ::scoped_string& scopedstr, character_count iStart, const ::scoped_string& scopedstrParam);
   //CLASS_DECL_ACME bool query_has_parameter_replace(const ::scoped_string & scopedstrQuery, const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter);
   //CLASS_DECL_ACME ::string query_has_parameter_replace(const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter);
   //CLASS_DECL_ACME bool query_get_parameter(::string & strParameter, const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrParam);
   //CLASS_DECL_ACME ::string query_get_parameter(const ::scoped_string& scopedstrQuery, const ::scoped_string& scopedstrParam);
   CLASS_DECL_ACME ::string set_request_path(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrScript);
   CLASS_DECL_ACME bool has_parameter_replace(::string& str, const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter);
   CLASS_DECL_ACME ::string has_parameter_replace(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrKey, const ::scoped_string& scopedstrParameter);
   CLASS_DECL_ACME bool get_parameter(::string& strParameter, const ::scoped_string& scopedstr, const ::scoped_string& scopedstrParam);
   CLASS_DECL_ACME ::string get_parameter(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrParam);
   CLASS_DECL_ACME ::string get_raw_request_path(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string get_request_path(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string get_protocol(const ::scoped_string & scopedstr);
   CLASS_DECL_ACME ::string get_host(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string get_root(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string get_query(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string get_object(const ::scoped_string & scopedstr);

   /// <summary>
   /// version of ::url::get_query with purifiers/stabilizers
   /// it currently remove unencoded : and / from the query part
   /// </summary>
   /// <param name="scopedstr"></param>
   /// <returns></returns>
   CLASS_DECL_ACME ::string _001GetQuery(const ::scoped_string& scopedstr);
   CLASS_DECL_ACME ::string object_set_query(const ::scoped_string& scopedstrObject, const ::scoped_string& scopedstrQuery);

} // namespace url



