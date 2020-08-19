#pragma once


namespace file
{


   class CLASS_DECL_AURA system_dir :
      virtual public ::object
   {
   public:


      ::file::path m_pathLocalAppMatterFolder;
      ::zip::util *                       m_pziputil;


      __pointer(::file::watcher)                 m_pfilewatcher;

      ::file::path            m_pathAppData;
      ::file::path            m_pathDefaultAppData;

      //class CLASS_DECL_AURA is_dir :
      //   virtual public sspa(is_dir)
      //{
      //public:

      //   int            m_iIsDir;
      //   tick m_tickLastCheck;
      //   u32       m_dwError;
      //   string         m_str;
      //   inline const char * c_str()
      //   {
      //      return m_str.c_str();
      //   }

      //};

      //class CLASS_DECL_AURA is_dir_work
      //{
      //public:

      //   char *   m_psz;

      //   inline const char * c_str()
      //   {
      //      return m_psz;
      //   }

      //};


      //class CLASS_DECL_AURA is_dir_map :
      //   virtual public is_dir
      //{
      //public:

      //   critical_section     m_cs;
      //   u32             m_tickTimeout;

      //   is_dir_map();

      //   bool lookup(const ::file::path & path, bool &bIsDir, u32 & dwLastError);
      //   bool lookup(const ::file::path & path, bool &bIsDir, u32 & dwLastError, i32 iLastChar);
      //   bool lookup_dynamic(const ::file::path & path, bool &bIsDir, u32 & dwLastError, i32 iLastChar);
      //   bool lookup_small(const ::file::path & path, bool &bIsDir,u32 & dwLastError,i32 iLastChar);
      //   void set(const ::file::path & path,bool bIsDir,u32 dwLastError);


      //};


      static system_dir *        g_pthis;
      //is_dir_map               m_isdirmap;
      ::mutex                    m_mutex;
      string                     m_strApiCc;

      ::file::path               m_pathCa2Config;
      ::file::path               m_pathCa2Module;
      ::file::path               m_pathModule;
      ::file::path               m_pathHome;
      ::file::path               m_pathInstall;

      bool                       m_bMatterFromHttpCache;


      system_dir();
      virtual ~system_dir();


      ::file::watcher & watcher();

      virtual ::file::listing & ls(::object * pobject,listing & listing);
      virtual ::file::listing & ls_relative_name(::object * pobject, listing & listing);


      virtual bool  is(const ::file::path & pcsz,::object * pobject);


      virtual bool  is_impl(const ::file::path & pcsz, ::object * pobject);


      virtual bool  is_cached(bool & bIs, const ::file::path & pcsz,::object * pobject);


      virtual bool  name_is(const ::file::path & pcsz,::object * pobject);


      virtual bool  is_inside(const ::file::path & pcszDir,const ::file::path & lpcszPath,::object * pobject);

      virtual bool  is_inside_time(const ::file::path & pcsz,::object * pobject);

      virtual ::file::listing & root_ones(::file::listing & listing,::object * pobject);
      virtual bool  mk(const ::file::path & pcsz,::object * pobject);

      virtual bool  rm(::object * pobject,const ::file::path & psz,bool bRecursive = true);

      virtual bool has_subdir(::object * pobject,const ::file::path & psz);

      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      virtual ::file::path install();
      virtual ::file::path config();

      virtual ::file::path home();

      virtual ::file::path module();
      virtual ::file::path ca2module();
      virtual ::file::path time_square(::object * pobject);
      virtual ::file::path time_log(const string & strId);


      virtual string locale_schema_matter(::object * pobject, const string & strLocale, const string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain);
      virtual string matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain);

      virtual string matter(::object * pobject, const ::file::patha & patha, bool bDir = false);
      virtual string matter(::object * pobject, ::file::path path, bool bDir = false);

      virtual string matter_from_locator(::object * pobject, const ::file::patha & patha, const string_array & straMatterLocator, bool bDir = false);
      virtual string matter_from_locator(::object * pobject, ::file::path path, const string_array & straMatterLocator, bool bDir = false);

      virtual ::file::path appmatter(string strApp, ::file::path pathRel);

      virtual void   matter_ls(::object * pobject, const ::file::path & str, ::file::patha & stra);
      virtual void   matter_ls_file(::object * pobject,const ::file::path & str,::file::patha & stra);

      virtual ::file::path commonappdata(const char * pszAppId, const char * pszBuild = nullptr, const char * pszPlatform = nullptr, const char * pszConfiguration = nullptr);
      virtual ::file::path commonappdata_locale_schema(const char * pszAppId, const char * pszBuild = nullptr, const char * pszPlatform = nullptr, const char * pszConfiguration = nullptr, const char * pszLocale = nullptr, const char * pszSchema = nullptr);

      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz);

      virtual ::file::path cache();
      virtual ::file::path appdata();
      virtual ::file::path commonappdata_root();
      virtual ::file::path commonappdata();
      virtual ::file::path element_commonappdata(const string & strElement);

      virtual ::file::path userquicklaunch(::object * pobjectContext);
      virtual ::file::path userprograms(::object * pobjectContext);

      virtual ::file::path commonprograms();

      virtual ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode,::object * pobject);

      virtual ::estatus initialize(::object * pobjectContext) override;

      //virtual ::file::path get_api_cc();

      virtual bool update_module_path();

      virtual ::file::path bookmark();

      virtual ::file::path desktop();
      virtual ::file::path document();
      virtual ::file::path download();

      virtual ::file::path music();
      virtual ::file::path video();
      virtual ::file::path image();

      virtual ::file::path dropbox(::object * pobject);
      virtual ::file::path onedrive(::object * pobject);

      virtual ::file::path standalone();


   };


   typedef pointer < system_dir > system_dir_pointer;


} // namespace file



