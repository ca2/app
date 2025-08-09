#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/filesystem/filesystem/enumerator.h"
//#include "acme/filesystem/filesystem/path.h"


//namespace file
//{


   class CLASS_DECL_ACME directory_context :
      virtual public ::object,
      virtual public ::file::enumerator
   {
   public:


      ::file::path                  m_pathLocalFolder;


      directory_context();
      ~directory_context() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void init_system();
      virtual void init_context();

      virtual void term_system();
      virtual void term_context();

      void destroy() override;

      //::file::watcher & watcher();


      //bool _enumerates(::file::listing_base & listing) override;
      bool enumerate(::file::listing_base & listing) override;
      virtual bool _enumerate(::file::listing_base & listing);


      //virtual bool list_relative_name(::file::listing_base & listing);

      //virtual bool list_recursively(::file::listing_base& listing);
      //virtual bool list_recursively_relative_name(::file::listing_base& listing);

      //virtual bool list_pattern(::file::listing_base& listing, const ::file::path& path, const string_array& straPattern);
      //virtual bool list_file_pattern(::file::listing_base& listing, const ::file::path& path, const string_array& straPattern);
      //virtual bool list_recursively_pattern(::file::listing_base& listing, const ::file::path& path, const string_array & straPattern);
      //virtual bool list_recursively_file_pattern(::file::listing_base& listing, const ::file::path& path, const string_array & straPattern);

      //virtual bool list_file(::file::listing_base& listing);
      //virtual bool list_directory(::file::listing_base& listing);

      //virtual bool list_recursively_file(::file::listing_base& listing);
      //virtual bool list_recursively_directory(::file::listing_base& listing);

      //inline bool enumerate(::file::listing_base& listing, const ::file::path& path) { listing(path); return ls(listing); }

      //inline bool list_recursively(::file::listing_base& listing, const ::file::path& path) { listing(path); return list_recursively(listing); }

      //inline bool list_file(::file::listing_base& listing, const ::file::path & path) { listing(path); return ls_file(listing); }
      //inline bool list_directory(::file::listing_base& listing, const ::file::path& path) { listing(path); return ls_dir(listing); }

      //inline bool list_recursively_file(::file::listing_base& listing, const ::file::path& path) { listing(path); return list_recursively_file(listing); }
      //inline bool list_recursively_directory(::file::listing_base& listing, const ::file::path& path) { listing(path); return list_recursively_dir(listing); }


      inline bool is(const ::payload & payload) { return file_type(payload) & ::file::e_type_folder2; }

      //virtual bool  _is(const ::file::path& pcsz);

      //virtual bool  __is(const ::file::path & path, bool & bIsDir);

      virtual ::file::e_type file_type(const ::payload & payload);

      virtual ::file::e_type _file_type(const ::file::path& path);
      
      virtual ::file::e_type __file_type(const ::file::path& path);


      //virtual bool  is_cached(bool & bIs, const ::file::path & path);


      virtual ::file::e_type cached_file_type(const ::file::path& path);


      virtual bool name_is(const ::file::path & path);


      virtual bool is_inside(const ::file::path & pathFolder, const ::file::path & lpcszPath);

      virtual bool is_inside_time(const ::file::path & path);

      virtual ::file::listing_base & root_ones(::file::listing_base & listing);
      virtual void  create(const ::file::path & path);

      virtual void  erase(const ::file::path & path, bool bRecursive = true);

      virtual bool has_subdir(const ::file::path & path);

      virtual bool fast_has_subdir(const ::file::path & path);


      virtual ::file::path defer_get_file_system_file(const ::file::path & path, bool bExpandAll);

      
      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      virtual ::file::path install();
      virtual ::file::path config();

      virtual ::file::path home();

      virtual ::file::path module();
      //virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log(const ::scoped_string & scopedstrId);


      virtual void get_matter_locator(string_array & straMatterLocator, bool bIncludeMain = true);


      virtual ::file::path locale_schema_matter(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema, const ::file::path & pathRoot, const ::file::path & pathDomain);
      virtual ::file::path matter(const ::file::path & path, const ::file::path & pathRoot, const ::file::path & pathDomain);

      virtual ::file::path matter(const ::file::path_array & patha);
      virtual ::file::path matter(::file::path path);

      virtual ::file::path appmatter(::file::path path);

      virtual ::file::path matter_from_locator(const ::file::path_array & patha, const string_array & straMatterLocator);
      virtual ::file::path matter_from_locator(::file::path path, const string_array & straMatterLocator);

      virtual ::file::path appmatter(const ::scoped_string & scopedstrApp, ::file::path pathRel);

      virtual bool matter_enumerate(const ::file::path & str, ::file::listing_base & listing, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);
      //virtual bool matter_ls_file(const ::file::path & str, ::file::listing& stra);

      //virtual ::file::path commonappdata(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrBuild = nullptr, const ::scoped_string & scopedstrPlatform = nullptr, const ::scoped_string & scopedstrConfiguration = nullptr);
      //virtual ::file::path commonappdata_locale_schema(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrBuild = nullptr, const ::scoped_string & scopedstrPlatform = nullptr, const ::scoped_string & scopedstrConfiguration = nullptr, const ::scoped_string & scopedstrLocale = nullptr, const ::scoped_string & scopedstrSchema = nullptr);

      virtual ::file::path trash_that_is_not_trash(const ::file::path & path);

      virtual ::file::path cache();
      virtual ::file::path appdata(const ::scoped_string & scopedstrAppId = "");
      virtual ::file::path commonappdata_root();
      virtual ::file::path commonappdata();
      virtual ::file::path element_commonappdata(const ::scoped_string & scopedstrElement);

      virtual ::file::path localfolder();

      virtual ::file::path userquicklaunch();
      virtual ::file::path userprograms();

      virtual ::file::path commonprograms();

      virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode);

      //virtual void initialize(::particle * pparticle) override;

      //virtual ::file::path get_api_cc();

      virtual ::file::path bookmark();

      virtual ::file::path desktop();
      virtual ::file::path document();
      virtual ::file::path document2();
      virtual ::file::path download();

      virtual ::file::path music();
      virtual ::file::path video();
      virtual ::file::path image();

      //virtual ::file::path dropbox();
      virtual ::file::path onedrive();

      //virtual ::file::path dropbox_app();

      //virtual bool is_dropbox_installed();
      //virtual void calculate_dropbox_installed();
      //virtual bool is_onedrive_installed();
      //virtual void calculate_onedrive_installed();

      virtual ::file::path standalone();

      //virtual string_array locale_schema_matter(string & strLocale, const ::scoped_string & scopedstrStyle);
      //virtual string_array locale_schema_matter(string & strLocale, const ::scoped_string & scopedstrStyle, const string & pathRoot, const ::file::path & pathDomain);
      //virtual string matter(const ::file::path_array & patha, bool bDir);
      //virtual string matter(const ::file::path & path, bool bDir );

      //virtual void   matter_ls(const ::file::path & str, ::file::path_array & stra);
      //virtual ::file::path matter_file(const ::file::path & path, bool bDir = false);
      //virtual void   matter_ls_file(const ::file::path & str, ::file::path_array & stra);

      //virtual ::file::path usersystemappdata(const string & pcszPrefix);

      //virtual ::file::path userappdata();
      //virtual ::file::path userdata();
      //virtual ::file::path userfolder();
      //virtual ::file::path default_os_user_path_prefix();
      //virtual ::file::path default_userappdata(const string & pcszPrefix, const string & lpcszLogin );

      //virtual ::file::path default_userdata(const string & pcszPrefix, const string & lpcszLogin);

      //virtual ::file::path default_userfolder(const string & pcszPrefix, const string & lpcszLogin);



      //virtual ::file::path userquicklaunch();
      //virtual ::file::path userprograms();


      //virtual ::file::listing_base & ls(::file::listing_base & listing);
      //virtual ::file::listing_base & ls_relative_name(::file::listing_base & listing);


      //virtual bool  has_subdir(const ::file::path & path);

      //virtual bool  is(const ::file::path & path);

      //virtual bool  is(const ::scoped_string & scopedstr);
      //virtual bool  is(const ::payload & payload);
      //virtual bool  is_inside(const ::file::path & pathFolder, const ::file::path & lpcszPath);

      //virtual bool  is_inside_time(const ::file::path & path);

      //virtual ::file::listing_base & root_ones(::file::listing_base & listing);
      //virtual bool  mk(const ::file::path & path);

      //virtual bool  rm(const ::file::path & path, bool bRecursive = true);

      //virtual ::file::path pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode);

      //virtual ::file::path dropbox();


      //virtual ::file::path onedrive();

      //virtual ::file::path dropbox_client();
     


   };


   typedef ::pointer<directory_context>dir_context_pointer;


//} // namespace file



