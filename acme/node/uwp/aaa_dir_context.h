#pragma once


namespace universal_windows
{


   class CLASS_DECL_ACME dir_context:
      virtual public ::dir_context
   {
   public:


      __reference(dir_system)       m_pdirsystem;
      __reference(file_system)      m_pfilesystem;



      dir_context();
      virtual ~dir_context();


      virtual ::e_status initialize(::matter * pobject) override;

      virtual ::e_status init_system() override;

      //virtual bool update_module_path();




      //using ::file::system_dir::path;
      //virtual class ::file::path & path();
      //virtual string path(const char * pszFolder,strsize iLenFolder,const char * pszRelative,strsize iLenRelative,const char * psz2,strsize iLen2,bool bUrl);

      //virtual string relpath(const char * lpcszSource,const char * lpcszRelative,const char * lpcsz2 = nullptr);
      //virtual bool  ls_pattern(const char * pcsz,const char * lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,bool_array * pbaIsDir = nullptr,i64_array * piaSize = nullptr);
      virtual ::file::listing & ls(::file::listing & listing) override;
      //virtual bool  rls_pattern(const char * pcsz,const char * lpcszPattern,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,bool_array * pbaIsDir = nullptr,i64_array * piaSize = nullptr,e_extract eextract = extract_first);
      //virtual bool  rls(const char * pcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr,e_extract eextract = extract_first);
      //virtual bool  rls_dir(const char * pcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr,string_array * pstraRelative = nullptr);
      //virtual bool  ls_dir(const char * pcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
      //virtual bool  ls_file(const char * pcsz,string_array * pstraPath = nullptr,string_array * pstraTitle = nullptr);
      virtual bool  is_impl(const ::file::path & path) override;
      //virtual bool  is(const ::string & str);
      virtual bool  name_is(const ::file::path & str);
      virtual bool  has_subdir( const ::file::path & path);
      virtual bool  is_inside(const ::file::path & pathDir, const ::file::path & path);
      virtual bool  is_inside_time(const ::file::path & path);
      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual bool mk(const ::file::path & path);
      virtual bool rm( const ::file::path & path, bool bRecursive = true);


      //virtual string name(const char * pcsz);
      //virtual string name(const ::string & str);

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

      ::file::path time_square( const ::string & strPrefix, const ::string & strSuffix);

      virtual ::file::path trash_that_is_not_trash(const ::file::path & path);

      virtual ::file::path appdata();

      //virtual ::file::path usersystemappdata(const ::string & strPrefix);
      //virtual ::file::path userappdata();
      //virtual ::file::path userdata();
      ////virtual ::file::path userfolder();
      //virtual ::file::path default_os_user_path_prefix();
      //virtual ::file::path default_userappdata(const ::string & strPrefix,const ::string & strLogin);
      //virtual ::file::path default_userdata(const ::string & strPrefix,const ::string & strLogin);
      //virtual ::file::path default_userfolder(const ::string & strPrefix,const ::string & strLogin);
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





