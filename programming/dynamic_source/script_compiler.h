#pragma once


namespace dynamic_source
{


   class script;
   class script_instance;

   class library  :
      virtual public ::object
   {
   public:

      ::mutex                                     m_mutex;
      string                                    m_strError;
      ::string_stream                               m_memfileError;
      ::string_stream                               m_memfileLibError;
      ::file::listing                           m_straLibSourcePath;
      ::file::patha                             m_straLibSourceRelPath;
      ::file::patha                             m_straLibCppPath;
      ::file::listing                           m_straLibIncludePath;
      ::file::patha                             m_straLibIncludeRelPath;
      ::file::patha                             m_straLibHppPath;
      ::file::path                              m_strLibraryPath;

      millis m_millisLastLibraryVersionCheck;
      bool                                      m_bLastLibraryVersionCheck;
      __pointer(::apex::library)                       m_plibraryLib;


      raw_array < __time_t >                    m_ftaLibCreation;
      raw_array < __time_t >                    m_ftaLibAccess;
      raw_array < __time_t >                    m_ftaLibModified;

      library(::context_object * pcontextobject);
      virtual ~library();

      void load_library();
      void unload_library();
   };


   class CLASS_DECL_APP_PROGRAMMING script_compiler :
      virtual public ::object,
      virtual public ::file::listener
   {
   public:


      enum ecpptype
      {
         cpptype_ds,
         cpptype_source,
         cpptype_include,
      };


      string_map < __pointer(library) > m_mapLib;

#ifdef WINDOWS
      string                                    m_strVs;
      string                                    m_strVsTools;
      string                                    m_strVCVersion;
#endif
      ::file::path                              m_pathProjectDir;
      string                                    m_strDynamicSourceConfiguration;
      ::file::path                              m_strDynamicSourceStage;
      ::file::path                              m_strDynamicSourceStageFolder;


      string      m_strLibPlatform;


      string_array                                   m_straSync;
//      map_string_to_ptr                         m_mapLib;
      string                                    m_strLibsLibs;
      string                                    m_strEnv;
      __pointer(script_manager)                        m_pmanager;
      string                                    m_strSdk1;
      string                                    m_strPlatform;
      string                                    m_strStagePlatform;
      ::file::watch_id                        m_filewatcherid;

      string                                    m_strPlat1;
      string                                    m_strPlat2;
      ::file::path                              m_strTime;


      ::mutex                                     m_mutex;

      ::mutex                                     m_mutexLibrary;


      script_compiler();
      virtual ~script_compiler();


      virtual ::e_status initialize_dynamic_source_script_compiler(script_manager * pscriptmanager);
      void prepare_compile_and_link_environment();

      void run_persistent();

      virtual ::e_status init1();

      bool defer_run_persistent(const char *psz);

      bool is_id(const char * psz, strsize iLen, const char * pszId, strsize iLenId, strsize & iIdLen);
      const char * next_nonspace(const char * psz);

      void compile(ds_script * pscript);

      void cppize(ds_script * pscript);
      void cppize(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype enum_type);

      void cppize1(ds_script * pscript);
      void cppize1(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype enum_type);

      string cppize2(const string & pszSource,bool bScript,string_array & straId);

      string get_ds_print(const char *psz)   ;

      void folder_watch();

      library & lib(const char * pszLibrary);
      void process_include(const char * pszInclude);

      //    bool library_DoesMatchVersion();


      virtual void handle_file_action(::file::action * paction) override;


      void prepare1(const char * pszSource, const char * pszDest);


      virtual void parse_pstr_set();

      virtual void pstr_set(id pszTopic,id idLocale,id idSchema,const char * psz);

   };



} // namespace dynamic_source


