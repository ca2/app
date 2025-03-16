//
// Created by camilo on 2024-10-24 04:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "context_apex.h"
#include "acme/platform/ini.h"


namespace platform
{


   ::string apex_context_layer::get_store_server_base_url()
   {

      return {};
   }


   //bool contains(::request * prequest) const{}

   //string command_line_text() const{}

   //void apex_context_layer::destroy() override{}

   //virtual ::task_pool* taskpool() override{}


   //      void initialize_context() override{}
   //
   //
   //      void initialize_context_1() override{}
   //
   //
   //      void finalize_context() override{}


   void apex_context_layer::clear_cache()
   {
   }


   //      bool is_system() const override{}
   //      bool is_session() const override{}
   bool apex_context_layer::is_local_data() const
   {
      return false;
   }


   //inline ::http::context& http() { return *m_phttp{} }
   //inline ::os_context * os_context() { return m_poscontext{} }{}


   //::directory_context * dir() override{}
   //::directory_system * directory_system() override{}
   //::file_context * file() override{}
   //::file_system * file_system() override{}


   ::handle::ini apex_context_layer::ini_from_path(::file::path& path)
   {
      return {};
   }


   ::handle::ini apex_context_layer::local_ini()
   {
      return {};
   }


   //bool apex_context_layer::http_download(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile){}
   //::string apex_context_layer::http_get(const string& strUrl, ::property_set& set){}
   //::string apex_context_layer::http_get(const ::scoped_string & scopedstrUrl){}

   ::string apex_context_layer::get_latest_build_number(const ::scoped_string& scopedstrConfiguration,
                                                        const ::scoped_string& scopedstrAppId)
   {
      return {};
   }


   ::file::path apex_context_layer::defer_make_file_system_url(string str)
   {

      return {};
   }


   ::string apex_context_layer::defer_get_file_title(string str)
   {
      return {};
   }


   //      bool defer_process_media_library_path(::file::path& path) override{}
   //
   //
   //      ::file::path defer_process_path(::file::path path) override{}
   //      ::file::path _defer_process_path(::file::path path) override{}
   //      ::file::path __defer_process_path(::file::path path) override{}

   bool apex_context_layer::_001IsProtocol(::file::path& path, const ::string& strProtocol)
   {
      return false;
   }


   //bool defer_process_known_folder_path(::file::path & path) override{}
   ::file::path apex_context_layer::full_process_path(::file::path path)
   {
      return {};
   }


   //bool apex_context_layer::defer_process_protocol_path(::file::path & path) override{}

   //sclass ::hyperlink hyperlink() { return this{} }


   // get a file and if there are exceptions, should show end user friendly messages
   file_pointer apex_context_layer::friendly_get_file(::payload payloadFile, ::file::e_open eopen)
   {
      return {};
   }


   //::pointer < ::file::link > os_resolve_alias(const ::file::path& path, bool bNoUI = false, bool bNoMount = false) override{}

   //bool _os_has_alias_in_path(const ::file::path & path, bool bNoUI = false, bool bNoMount = false) override{}

   //::pointer < ::file::link > _os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount) override{}

   //bool apex_context_layer::os_is_alias(const ::file::path & path) override{}

   ::file::path apex_context_layer::sys_path(const ::scoped_string& scopedstrPath)
   {
      return {};
   }


   void apex_context_layer::sys_set(const ::scoped_string& scopedstrPath, const ::scoped_string& scopedstrValue)
   {
   }


   ::string apex_context_layer::sys_get(const ::scoped_string& scopedstrPath,
                                        const ::scoped_string& scopedstrDefault )
   {
      return {};
   }


   ::string apex_context_layer::load_string(const ::scoped_string& scopedstr)
   {
      return {};
   }


   //bool _enumerates(::file::listing & listing) override{}
   //bool enumerate(::file::listing& listing) override{}
   //bool apex_context_layer::perform_file_relative_name_listing(::file::listing& listing) override{}


   //virtual ::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true){}
   //virtual ::image::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true){}

   //virtual ::image::image_pointer load_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false) override{}
   //virtual ::image::image_pointer load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false){}
   //virtual ::image::image_pointer load_matter_icon(string_array & straMatter, string strIcon) override{}
   //virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h) override{}
   //virtual ::image::image_pointer load_thumbnail(const ::string & strPath){}
   //virtual ::image::image_pointer load_dib(const ::file::path & pathDib) override{}
   //virtual ::icon_pointer load_icon(const ::payload & payloadFile){}


   //void apex_context_layer::_get_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true){}
   //void apex_context_layer::_matter_image(::image::image *pimage, const ::string & strMatter, bool bSync = true){}


   //void apex_context_layer::_load_image(::image::image *pimage, const ::payload & payloadFile, bool bSync = true, bool bCreateHelperMaps = false){}
   //void apex_context_layer::_load_matter_image(::image::image *pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false){}
   //void apex_context_layer::_load_matter_icon(::image::image *pimage, string_array & straMatter, string strIcon){}
   //void apex_context_layer::_load_thumbnail(::image::image *pimage, const ::payload & payloadFile, int w, int h){}
   //void apex_context_layer::_load_thumbnail(::image::image *pimage, const ::payload & payloadFile){}
   //void apex_context_layer::_load_dib(::image::image *pimage, const ::file::path & pathDib){}


   //void apex_context_layer::save_image(const ::payload & payloadFile, const ::image::image *pimage, ::save_image * psaveimage = nullptr){}
   //void apex_context_layer::save_dib(const ::file::path & path, const ::image::image *pimage){}


   //virtual ::image::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions){}
   //void apex_context_layer::_save_to_file(const ::payload & payloadFile, const ::image::image *pimage, const ::payload & varOptions){}


   /*::string apex_context_layer::matter_locator(string strApp){}
   ::string apex_context_layer::matter_locator(::apex::application* papp){}


   void apex_context_layer::add_matter_locator(string strApp){}
   void apex_context_layer::add_matter_locator(::apex::application* papp){}*/


   void apex_context_layer::_load_from_file(::particle* pparticle, const ::payload& payloadFile, const ::payload& varOptions)
   {
   }


   void apex_context_layer::_save_to_file(const ::payload& payloadFile, const ::payload& varOptions, const ::particle* pparticle)
   {
   }


   void apex_context_layer::load_from_file(::particle* pparticle, const ::payload& payloadFile, const ::payload* pvarOptions)
   {
   }


   void apex_context_layer::load_from_file(::particle* pparticle, const ::payload& payloadFile)
   {
   }


   void apex_context_layer::save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle* pparticle)
   {
   }


   void apex_context_layer::save_to_file(const ::payload& payloadFile, const ::particle* pparticle)
   {
   }


   //void apex_context_layer::destroy() override{}

   //file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override{}


   //      using acme::context::http_text{}
   //      ::string http_text(const ::scoped_string & scopedstrUrl, ::property_set & set) override{}
   //
   //      using acme::context::http_download{}
   //      void http_download(const ::payload & payloadFile, const ::scoped_string & scopedstrUrl, ::property_set & set) override{}

   //      using acme::context::http_get{}
   //::pointer < ::nano::http::response > http_get(const ::scoped_string& scopedstrUrl, const ::property_set& set) override{}

   //void apex_context_layer::perform(::nano::http::get * pget){}


   bool apex_context_layer::defer_process_fs_raw_folder_protocol_path(::file::path & path)
   {

      return false;

   }



   bool apex_context_layer::is_fs_raw_folder_protocol_installed(const ::scoped_string & scopedstrProtocol)
   {

      return false;

   }



} // namespace platform
