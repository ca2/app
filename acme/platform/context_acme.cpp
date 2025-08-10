//
// Created by camilo on 2024-10-24 04:33 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "context_acme.h"


namespace platform
{


   void acme_context_layer::set_platform()
   {
   }


   //void initialize(::particle * pparticle) override{}

   void acme_context_layer::initialize_context()
   {
   }


   void acme_context_layer::initialize_context_1()
   {


   }


   void acme_context_layer::finalize_context()
   {


   }


   void acme_context_layer::initialize_http()
   {


   }


   //::pointer < ::reified < ::message_box > > realize(::realizable < ::message_box > * p) override{}

   ::image::image_context* acme_context_layer::image()
   {
      return nullptr;
   }


   // bool acme_context_layer::is_system() const{}
   // bool acme_context_layer::is_session() const{}

   void acme_context_layer::translate_text_data(::text::data* ptextdata)
   {
   }


   //virtual ::text::text __text(const ::atom& atom) override{}


   //inline ::platform::system * system(){}
   //::platform::node * node(){}


   //inline ::os_context * os_context() { return m_poscontext{} }


   //::file_system * file_system(){}
   //::directory_system * directory_system(){}


   ::directory_context* acme_context_layer::directory()
   {

      return nullptr;
   }


   ::file_context* acme_context_layer::file()
   {
      return nullptr;
   }


   ::directory_system* acme_context_layer::directory_system()
   {
      return nullptr;
   }


   ::file_system* acme_context_layer::file_system()
   {
      return nullptr;
   }


   ::path_system* acme_context_layer::path_system()
   {
      return nullptr;
   }


   //::file::watcher* acme_context_layer::file_watcher()
   //{
   //   return nullptr;
   //}


   // ::platform::http* acme_context_layer::http()
   // {
   //    return nullptr;
   // }


   ::payload acme_context_layer::file_payload(const ::payload& payloadFile)
   {
      return {};
   }


   //::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen) override{}


   ::file::path acme_context_layer::defer_process_path(::file::path path)
   {
      return {};
   }


   ::file::path acme_context_layer::_defer_process_path(::file::path path)
   {
      return {};
   }


   ::file::path acme_context_layer::__defer_process_path(::file::path path)
   {
      return {};
   }


   void acme_context_layer::fork_count(::collection::count iCount,
                                       const ::function<void(::collection::index, ::collection::index,
                                                             ::collection::index, ::collection::index)>& function,
                                       const ::procedure& procedureCompletion, ::collection::index iStart )
   {
   }


   ::string acme_context_layer::get_locale()
   {
      return {};
   }


   ::string acme_context_layer::get_schema()
   {
      return {};
   }


   void acme_context_layer::locale_schema_matter(string_array_base& stra, const string_array_base& straMatterLocator,
                                                 const ::scoped_string& scopedstrLocale,
                                                 const ::scoped_string& scopedstrSchema)
   {
   }


   string acme_context_layer::get_locale_schema_dir()
   {
      return {};
   }


   string acme_context_layer::matter_locator(const ::scoped_string & scopedstrApp)
   {
      return {};
   }


   string acme_context_layer::matter_locator(::platform::application* papp)
   {
      return {};
   }


   void acme_context_layer::add_matter_locator(const ::scoped_string & scopedstrApp)
   {
   }


   void acme_context_layer::add_matter_locator(::platform::application* papp)
   {
   }


   ::file::path acme_context_layer::defer_process_matter_path(::file::path path)
   {

      return {};
   }


   //::file::path acme_context_layer::defer_process_relative_path(const ::file::path & path){}

   ::file::path acme_context_layer::get_matter_path(const ::scoped_string & scopedstrMatter)
   {
      return {};
   }


   ::file::path acme_context_layer::get_matter_cache_path(::file::path path)
   {
      return {};
   }


   ::file::path acme_context_layer::side_get_matter_path(const ::scoped_string & scopedstrMatter)
   {
      return {};
   }


   bool acme_context_layer::os_is_alias(const ::file::path& path)
   {
      return false;
   }


    ::pointer<::file::link> acme_context_layer::os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount)
   {
      return {};
   }


   bool acme_context_layer::_os_has_alias_in_path(const ::file::path& path, bool bNoUI, bool bNoMount)
   {
      return false;
   }


   ::pointer<::file::link> acme_context_layer::_os_resolve_alias(const ::file::path& path, bool bNoUI, bool bNoMount)
   {
      return {};
   }


   //bool acme_context_layer::os_is_alias(const ::file::path & path) override{}

   bool acme_context_layer::defer_process_media_library_path(::file::path& path)
   {
      return false;
   }


   bool acme_context_layer::defer_process_known_folder_path(::file::path& path)
   {
      return false;
   }


   bool acme_context_layer::defer_process_protocol_path(::file::path& path)
   {
      
      return false;

   }



   ::platform::http * acme_context_layer::http()
   {

      return nullptr;

   }


} // namespace platform
