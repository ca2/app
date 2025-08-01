#pragma once


namespace universal_windows
{


   class CLASS_DECL_APEX directory_context:
      virtual public ::directory_context
   {
   public:


      ::pointer<directory_system>      m_pdirectorysystem;
      ::pointer<file_system>     m_pfilesystem;



      directory_context();
      virtual ~directory_context();


      virtual void initialize(::particle * pparticle) override;

      virtual void init_system() override;

      //virtual bool update_module_path();




      //using ::file::system_dir::path;
      //virtual class ::file::path & path();
      //virtual string path(const ::scoped_string & scopedstrFolder,character_count iLenFolder,const ::scoped_string & scopedstrRelative,character_count iLenRelative,const ::scoped_string & scopedstr2,character_count iLen2,bool bUrl);

      //virtual string relpath(const_char_pointer lpcszSource,const_char_pointer lpcszRelative,const_char_pointer lpcsz2 = nullptr);
      //virtual bool  ls_pattern(const ::scoped_string & scopedstr,const_char_pointer lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,bool_array * pbaIsDir = nullptr,long_long_array * piaSize = nullptr);
      using ::directory_context::ls;
      virtual ::file::listing & ls(::file::listing & listing) override;
      //virtual bool  rls_pattern(const ::scoped_string & scopedstr,const_char_pointer lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,bool_array * pbaIsDir = nullptr,long_long_array * piaSize = nullptr,enum_extract eextract = e_extract_first);
      //virtual bool  rls(const ::scoped_string & scopedstr,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,enum_extract eextract = e_extract_first);
      //virtual bool  rls_dir(const ::scoped_string & scopedstr,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr);
      //virtual bool  ls_dir(const ::scoped_string & scopedstr,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
      //virtual bool  ls_file(const ::scoped_string & scopedstr,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
      virtual bool  is_impl(const ::file::path & path) override;
      //virtual bool  is(const ::scoped_string & scopedstr);
      virtual bool  name_is(const ::file::path & str);
      virtual bool  has_subdir( const ::file::path & path);
      virtual bool  is_inside(const ::file::path & pathFolder, const ::file::path & path);
      virtual bool  is_inside_time(const ::file::path & path);
      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual bool mk(const ::file::path & path);
      virtual bool rm( const ::file::path & path, bool bRecursive = true);


      //virtual string name(const ::scoped_string & scopedstr);
      //virtual string name(const ::scoped_string & scopedstr);

      ::file::path userfolder();

      virtual ::file::path warehouse();
      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      // stage in ccwarehouse spalib
      virtual ::file::path install();

      //virtual ::file::path module();
      //virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log();

      ::file::path time_square( const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix);

      virtual ::file::path trash_that_is_not_trash(const ::file::path & path);

      virtual ::file::path appdata();

      //virtual ::file::path usersystemappdata(const ::scoped_string & scopedstrPrefix);
      //virtual ::file::path userappdata();
      //virtual ::file::path userdata();
      ////virtual ::file::path userfolder();
      //virtual ::file::path default_os_user_path_prefix();
      //virtual ::file::path default_userappdata(const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin);
      //virtual ::file::path default_userdata(const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin);
      //virtual ::file::path default_userfolder(const ::scoped_string & scopedstrPrefix,const ::scoped_string & scopedstrLogin);
      virtual ::file::path userquicklaunch();
      virtual ::file::path userprograms();

      virtual ::file::path commonprograms();

      virtual ::file::path commonappdata();


      virtual ::file::path document() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;


   };


} // namespace universal_windows





