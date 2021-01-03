#pragma once


//namespace file
//{


   class CLASS_DECL_APEX dir_context :
      virtual public ::object
   {
   public:


      dir_context();
      virtual ~dir_context();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      virtual ::e_status init_system();
      virtual ::e_status init_context();



      ::file::watcher & watcher();


      virtual ::file::listing & ls(::file::listing & listing);
      virtual ::file::listing & ls_relative_name(::file::listing & listing);

      virtual ::file::listing& rls(::file::listing& listing);
      virtual ::file::listing& rls_relative_name(::file::listing& listing);

      virtual ::file::listing& ls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern);
      virtual ::file::listing& ls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern);
      virtual ::file::listing& rls_pattern(::file::listing& listing, const ::file::path& path, const string_array & straPattern);
      virtual ::file::listing& rls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array & straPattern);

      virtual ::file::listing& ls_file(::file::listing& listing);
      virtual ::file::listing& ls_dir(::file::listing& listing);

      virtual ::file::listing& rls_file(::file::listing& listing);
      virtual ::file::listing& rls_dir(::file::listing& listing);

      inline ::file::listing& ls(::file::listing& listing, const ::file::path& path) { listing(path); return ls(listing); }

      inline ::file::listing& rls(::file::listing& listing, const ::file::path& path) { listing(path); return rls(listing); }

      inline ::file::listing& ls_file(::file::listing& listing, const ::file::path & path) { listing(path); return ls_file(listing); }
      inline ::file::listing& ls_dir(::file::listing& listing, const ::file::path& path) { listing(path); return ls_dir(listing); }

      inline ::file::listing& rls_file(::file::listing& listing, const ::file::path& path) { listing(path); return rls_file(listing); }
      inline ::file::listing& rls_dir(::file::listing& listing, const ::file::path& path) { listing(path); return rls_dir(listing); }


      virtual bool  is(const ::file::path & pcsz);


      virtual bool  is_impl(const ::file::path & pcsz);


      virtual bool  is_cached(bool & bIs, const ::file::path & pcsz);


      virtual bool  name_is(const ::file::path & pcsz);


      virtual bool  is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath);

      virtual bool  is_inside_time(const ::file::path & pcsz);

      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual bool  mk(const ::file::path & pcsz);

      virtual bool  rm(const ::file::path & psz, bool bRecursive = true);

      virtual bool has_subdir(const ::file::path & psz);

      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      virtual ::file::path install();
      virtual ::file::path config();

      virtual ::file::path home();

      virtual ::file::path module();
      virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log(const string & strId);


      virtual ::file::path locale_schema_matter(const string & strLocale, const string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain);
      virtual ::file::path matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain);

      virtual ::file::path matter(const ::file::patha & patha, bool bDir = false);
      virtual ::file::path matter(::file::path path, bool bDir = false);

      virtual ::file::path matter_from_locator(const ::file::patha & patha, const string_array & straMatterLocator, bool bDir = false);
      virtual ::file::path matter_from_locator(::file::path path, const string_array & straMatterLocator, bool bDir = false);

      virtual ::file::path appmatter(string strApp, ::file::path pathRel);

      virtual void matter_ls(const ::file::path & str, ::file::listing & stra);
      virtual void matter_ls_file(const ::file::path & str, ::file::listing& stra);

      virtual ::file::path commonappdata(const char * pszAppId, const char * pszBuild = nullptr, const char * pszPlatform = nullptr, const char * pszConfiguration = nullptr);
      virtual ::file::path commonappdata_locale_schema(const char * pszAppId, const char * pszBuild = nullptr, const char * pszPlatform = nullptr, const char * pszConfiguration = nullptr, const char * pszLocale = nullptr, const char * pszSchema = nullptr);

      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz);

      virtual ::file::path cache();
      virtual ::file::path appdata();
      virtual ::file::path commonappdata_root();
      virtual ::file::path commonappdata();
      virtual ::file::path element_commonappdata(const string & strElement);

      virtual ::file::path userquicklaunch();
      virtual ::file::path userprograms();

      virtual ::file::path commonprograms();

      virtual ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);

      //virtual ::e_status initialize(::layered * pobjectContext) override;

      //virtual ::file::path get_api_cc();

      virtual ::file::path bookmark();

      virtual ::file::path desktop();
      virtual ::file::path document();
      virtual ::file::path download();

      virtual ::file::path music();
      virtual ::file::path video();
      virtual ::file::path image();

      virtual ::file::path dropbox();
      virtual ::file::path onedrive();

      virtual ::file::path standalone();


      //virtual string_array locale_schema_matter(string & strLocale, const string & strStyle);
      //virtual string_array locale_schema_matter(string & strLocale, const string & strStyle, const string & pathRoot, const ::file::path & pathDomain);
      //virtual string matter(const ::file::patha & patha, bool bDir);
      //virtual string matter(const ::file::path & path, bool bDir );

      //virtual void   matter_ls(const ::file::path & str, ::file::patha & stra);
      //virtual ::file::path matter_file(const ::file::path & path, bool bDir = false);
      //virtual void   matter_ls_file(const ::file::path & str, ::file::patha & stra);

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


      //virtual ::file::listing & ls(::file::listing & listing);
      //virtual ::file::listing & ls_relative_name(::file::listing & listing);


      //virtual bool  has_subdir(const ::file::path & pcsz);

      //virtual bool  is(const ::file::path & pcsz);

      //virtual bool  is(const string & str);
      //virtual bool  is(const payload & payload);
      //virtual bool  is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath);

      //virtual bool  is_inside_time(const ::file::path & pcsz);

      //virtual ::file::listing & root_ones(::file::listing & listing);
      //virtual bool  mk(const ::file::path & pcsz);

      //virtual bool  rm(const ::file::path & psz, bool bRecursive = true);

      //virtual ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);

      //virtual ::file::path dropbox();


      //virtual ::file::path onedrive();


   };


   typedef ___pointer < dir_context > dir_context_pointer;


//} // namespace file



