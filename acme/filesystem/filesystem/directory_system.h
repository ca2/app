// Create on 2021-03-20 23:59 <3ThomasBS_
#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


#include "acme/prototype/media_library/item.h"
#include "enumerator.h"
#include "acme/platform/department.h"
#include "acme/prototype/collection/map.h"
#include "acme/prototype/collection/string_map.h"
#include "acme/parallelization/mutex.h"



class CLASS_DECL_ACME directory_system :
   virtual public ::acme::department,
   virtual public ::file::enumerator
{
public:





   ::file::path                  m_pathLocalAppMatterFolder;
   ::file::path                  m_pathLocalAppMatterCacheFolder;

   //::pointer<::file::watcher>   m_pfilewatcher;

   ::file::path                  m_pathAppData;
   ::file::path                  m_pathDefaultAppData;

   string                        m_strApiCc;

   ::file::path                  m_pathCa2Config;
   //::file::path                  m_pathModule;
   ::file::path                  m_pathHome;
   ::file::path                  m_pathInstall;

   bool                          m_bMatterFromHttpCache;
   bool                          m_bMatterFromResource;


   ::file::path                  m_pathUpload;




   //class music_item :
   //   virtual public library_item
   //{
   //public:


   //   ::string       m_strTitle;
   //   ::string       m_strArtist;


   //};


   //class image_item :
   //   virtual public library_item
   //{
   //public:


   //   ::string       m_strTitle;


   //};


   //class video_item :
   //   virtual public library_item
   //{
   //public:


   //   ::string       m_strTitle;
   //   ::string       m_strArtist;


   //};



   ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::directory_system *     m_pplatformdir;
   ::file_system *                                                     m_pfilesystem;
   ::path_system *                                                     m_ppathsystem;

   ::file::path                                    m_pathInstallFolder;
   //::file::path                                    m_pathModuleFolder;


   ::media_library::item_map                       m_medialibraryitemmap;
   
   ::pointer < ::mutex >                           m_pmutexMediaLibrary;
    ::file::path                                                      m_pathFolder;


   directory_system();
   ~directory_system() override;


   void initialize(::particle * pparticle) override;

   
   //virtual ::file::path module_folder();


   virtual ::file::path app(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path app_app_nest(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path app_app(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path vcredist(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path install_log(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);


   virtual ::file::path install();
   virtual ::file::path default_install();
   virtual ::file::path beforeca2();
   virtual ::file::path module();
   virtual ::file::path relative(::file::path path);
   virtual ::string appid();
   virtual ::file::path appdata(); // appdata
   virtual ::file::path archive();
   virtual ::file::path tool();
   //virtual ::file::path public_system();
   //virtual ::file::path system();
   virtual ::file::path userconfig();
   virtual ::file::path config();
   virtual ::file::path local();
   virtual ::file::path sensitive();
   virtual ::file::path localconfig(); // #vcs C:\\Users\\user\\AppData\\Roaming\\ca2\\localconfig
   virtual ::file::path ca2roaming(); // writable root (non-bin, non-exe)
   virtual ::file::path ca2appdata(); // writable root (non-bin, non-exe)
   virtual ::file::path roaming();
   virtual ::file::path program_data();
   virtual ::file::path application_data_base();
   virtual ::file::path application_data();
   virtual ::file::path application_data(const ::scoped_string & scopedstrAppId);
   virtual ::file::path application_home();
   virtual ::file::path application_home(const ::scoped_string & scopedstrAppId);
   virtual ::file::path public_root(); // writable common root (non-bin, non-exe)
   virtual ::file::path bookmark();
   virtual ::file::path home();
   virtual ::file::path icloud_container2(const_char_pointer pszContentIdentifier = nullptr);
   virtual ::file::path icloud_container_documents(const_char_pointer pszContentIdentifier = nullptr);
   virtual ::file::path icloud_container2_final(const_char_pointer pszContentIdentifier = nullptr);
   virtual bool is_icloud_container(const ::file::path & path, const_char_pointer pszContentIdentifier = nullptr);
   virtual bool has_icloud_container(const_char_pointer pszContentIdentifier = nullptr);
   virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode);
   virtual ::file::path program_files_x86();
   virtual ::file::path program_files();
   //virtual ::file::path program_data();
   virtual ::file::path stage(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path sys_temp();
   virtual ::file::path temp();
   virtual ::string dir_root();
   //virtual ::file::path home();
   //virtual ::file::path program_data();
   //virtual ::file::path roaming();
   virtual ::file::path get_memory_map_base_folder_path();
   //virtual ::file::path ca2appdata();
   //virtual ::file::path ca2roaming();
   //virtual ::file::path localconfig();
   virtual string system_short_name();


   //::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   //virtual ::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
   virtual ::file::path inplace_matter_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);


   virtual void set_path_install_folder(const ::scoped_string & scopedstrPath);

   //virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode);

   virtual ::file::path machine_event_file_path();

   virtual ::file::path user_appdata_local();
   //virtual ::file::path tool();

   inline bool is(const ::file::path& path) { return file_type(path) & ::file::e_type_folder2; }
   inline bool __is(const ::file::path& path) { return __file_type(path) & ::file::e_type_folder2; }

   virtual ::file::e_type file_type(const ::file::path& path);
   virtual ::file::e_type _file_type(const ::file::path& path);
   virtual ::file::e_type __file_type(const ::file::path& path);
   // From acme/filesystem/file/dir.cpp by camilo 
   // From acme_posix/directory_system.h
// on 2021-08-09 03:20 BRT
// <3ThomasBorregaardSorensen!!


   //namespace posix
   //{


   //   class CLASS_DECL_ACME_POSIX directory_system :
   //      virtual public ::directory_system
   //   {

   //   public:

   //      directory_system();
   //      ~directory_system();

         //virtual string name(const ::file::path & path1);


         //virtual ::file::path base_module();

         virtual void create(const ::file::path & path);
         //virtual void _create(const ::file::path & path);
         virtual void _create2(const ::file::path & path);
         virtual void _create4(const ::file::path & path);
         virtual void erase(const ::file::path & path);
         virtual void erase_recursively(const ::file::path & path);


         //virtual void enumerate_recursively(::file::path_array_base & stra, const ::scoped_string & scopedstr);
         //virtual void enumerate_recursively_directory(::file::path_array_base & stra, const ::scoped_string & scopedstr);

         //bool _enumerates(::file::listing_base & listing) override;
         
         bool enumerate(::file::listing_base & listing) override;

         virtual bool defer_enumerate_protocol(::file::listing_base& listing);

         virtual bool defer_enumerate_media_library(::file::listing_base& listing);
         virtual ::media_library::item* media_library_item(const ::file::path& path);
         virtual bool defer_process_media_library_path(::file::path& path);
         virtual bool defer_media_library_representative_file_name(::file::path & path);

         bool list_base(::string_array_base & stra, const ::scoped_string & path, ::file::e_flag eflag = ::file::e_flag_file_or_folder) override;

         virtual ::file::listing_base folders(const ::file::path & path) override;
         virtual ::file::listing_base files(const ::file::path& path) override;
         virtual ::file::listing_base folders_and_files(const ::file::path& path) override;


         //virtual void enumerate(::file::listing_base & listing, const ::file::path & path, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);
         //virtual void enumerate_pattern(::file::listing_base & listing, const ::file::path & path, const ::string_array_base & straNamePattern, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);
         //virtual void enumerate_directory(::file::path_array_base & stra, const ::scoped_string & scopedstr, enum_depth edepth = e_depth_none);
         //virtual void enumerate_file(::file::path_array_base & stra, const ::scoped_string & scopedstr, enum_depth edepth = e_depth_none);

         virtual int make_path(const ::scoped_string & scopedstr);


         /*namespace dir
         {*/


            //virtual string name(const ::file::path & path);
            //virtual bool mk(const ::scoped_string & scopedstrPath);
            //virtual bool _mk(const  char * path); // makes a directory path (all intermediates too)
            //virtual bool is(const ::file::path & path);
            //virtual bool _is(const ::file::path & path);
            //virtual bool mk(const  char * path); // makes a directory path (all intermediates too)
            //virtual bool mkdir(const  char * path); // only creates if parent dir already exists
            //virtual void ls(::file::path_array_base & patha, const ::file::path & path);
            //virtual void ls_dir(::file::path_array_base & patha, const ::file::path & path);
            //virtual void ls_file(::file::path_array_base & patha, const ::file::path & path);
            //virtual void rls(::file::path_array_base & patha, const ::file::path & path);
            //virtual void rls_dir(::file::path_array_base & patha, const ::file::path & path);


            //virtual::file::path ca2_module();
            //virtual::file::path base_module();


         //} // namespace dir

   virtual string_to_string_base map_content(const ::file::path & path);
   virtual ::string_array_base enumerate_content(const ::file::path & path);




   virtual ::file::path current();
   virtual void change_current(const ::file::path & path);
   virtual void set_current(const ::file::path& path);
   virtual void change_to_home();


   virtual void add_media_library_item(::media_library::item* pmedialibraryitem);


   virtual ::file::path windows();
   virtual ::file::path system_drive();

   virtual ::file::path fonts();
   virtual ::file::path ___fonts();


   virtual bool is_accessible(const ::file::path & path);

   virtual bool contains_files(const ::file::path& path, const ::string_array_base& straName, int iMinimumSize);


   //virtual void initialize(::particle * pparticle) override;

   virtual void init_system();

   virtual void term_system();

   void destroy() override;

   virtual ::file::path compute_default_app_data_path();

};



