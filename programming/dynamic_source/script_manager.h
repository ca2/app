#pragma once


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING script_manager :
      virtual public ::channel
   {
   public:


      class CLASS_DECL_APP_PROGRAMMING clear_include_matches_file_watcher :
         virtual public ::file::listener::base
      {
      public:


         __pointer(script_manager)   m_pmanager;

         clear_include_matches_file_watcher(::object * pobject);

         virtual void operator()(::file::action * paction) override;


      };



      class CLASS_DECL_APP_PROGRAMMING plugin_map_item :
         virtual public ::object
      {
      public:


         string         m_strHost;
         string         m_strScript;
         string         m_strPlugin;

         plugin_map_item();
         plugin_map_item(const plugin_map_item & item);


         plugin_map_item & operator = (const plugin_map_item & item);

      };

      class CLASS_DECL_APP_PROGRAMMING tunnel_map_item
      {
      public:


         string         m_strServer;
         ::duration           m_tick;


      };


      ::netnode::script_manager *                           m_pnetnodescriptmanager;


      __pointer_array(plugin_map_item)                      m_pluginmapitema;


      ::mutex                                               m_mutexIncludeMatches;
      string_map < bool >                                   m_mapIncludeMatchesFileExists;
      string_map < bool >                                   m_mapIncludeMatchesIsDir;
      ::mutex                                               m_mutexIncludeHasScript;
      string_map < bool >                                   m_mapIncludeHasScript;
      ::mutex                                               m_mutexShouldBuild;
      string_map < bool >                                   m_mapShouldBuild;
      ::mutex                                               m_mutexIncludeExpandMd5;
      string_to_string                                      m_mapIncludeExpandMd5;
      //__composite(::user::message_window)                   m_pmessagequeue;

      i32                                                   m_iTunnelPluginCount;
      ::mutex                                               m_mutexOutLink;
      string_map < __pointer(::sockets::link_out_socket) >  m_mapOutLink;
      ::mutex                                               m_mutexInLink;
      ::sockets::in_link_map                                m_mapInLink;
      ::mutex                                               m_mutexTunnel;
      strmap(tunnel_map_item)                               m_mapTunnel;


      ::mutex                                               m_mutexImageSize;
      string_map < ::size_i32 >                                 m_mapImageSize;



      string                                                m_strRepos;
      string                                                m_strNamespace;
      ::file::path                                          m_strNetnodePath;
      ::file::path                                          m_strNetseedPath;
      ::file::path                                          m_strNetseedDsCa2Path;

      ::mutex                                               m_mutexSimage;
      ::mutex                                               m_mutexSpider;

      ::mutex                                               m_mutexRsa;

      ::crypto::rsaptra                                     m_rsaptra;

      ::duration                                                  m_durationLastRsa;



      i64                                                   m_iDatabaseWaitTimeOut;

      ::mutex                                               m_mutexSession;
      string_map < __pointer(::dynamic_source::session) >   m_mapSession;
      ::mutex                                               m_mutexMusicDbPool;
      ::mutex                                               m_mutexWayDbPool;
      __pointer(script_cache)                               m_pcache;
      __pointer(script_compiler)                            m_pcompiler;
      i32                                                   m_iBuildTimeWindow;
      i32                                                   m_iBuildTimeRandomWindow;

      string_to_string                                      m_strmapFunUserKey;

      string                                                m_strPersistentError;

      ::mutex                                               m_mutexPersistentStr;
      ::mutex                                               m_mutexUiRedir;
      ::mutex                                               m_mutexTagId;
      string_to_string                                      m_tagid;
      string_to_string                                      m_usersecuretagid;
      ::mutex                                               m_mutexTagName;
      string_to_string                                      m_tagname;


      string                                                m_strSeed;


      bool                                                  m_bCompiler;
      ::integral_second                                     m_secsSessionExpiration;


      script_manager();
      ~script_manager() override;

      
      virtual void initialize(::object * pobject) override;


      virtual void init1();


      virtual bool include_matches_file_exists(const ::string & strPath);
      void set_include_matches_file_exists(const ::string & strPath, bool bFileExists);
      bool include_matches_is_dir(const ::string & strPath);
      bool include_has_script(const ::string & strPath);
      string include_expand_md5(const ::string & strPath);
      void set_include_expand_md5(const ::string & strPath, const ::string & strMd5);

      __pointer(::dynamic_source::session) get_session(const ::string & pszId);

      __pointer(script_instance) get(const ::string & strNafme);
      __pointer(script_instance) get(const ::string & strName, __pointer(script) & pscript);
      virtual void handle(::dynamic_source::httpd_socket * psocket);
      ::payload get_output_internal(::dynamic_source::script_interface * pinstanceParent, const ::string & strName);
      void run(const ::string & lpcszName);

      void LoadEnv();

      string get_library_build_log();


      virtual void clear_include_matches(::file::path path);
      virtual void clear_include_matches();
      //static ::u32 c_cdecl clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

      virtual ::file::path real_path(const ::file::path & str);
      virtual ::file::path real_path(const ::file::path & strBase,const ::file::path & str);


      __pointer(::crypto::rsa) get_rsa_key();

      string get_rsa_key(script_interface * pscriptinterface);

      void calc_rsa_key();


      virtual void on_load_env();

      virtual void register_plugin(const ::string & strHost, const ::string & strScript, const ::string & strName, script * pscript);


      virtual string get_root_plugin();


      void wait_link_out(const ::string & pszServer, ::sockets::link_in_socket * pinsocket);
      bool has_link_out_link(const ::string & pszServer, ::sockets::link_in_socket * pinsocket, ::sockets::httpd_socket * phttpdsocket);
      ::sockets::link_in_socket * get_link_in(const ::string & pszServer, ::sockets::link_out_socket * poutsocket);
      bool is_online(const ::string & pszServer);
      ::sockets::link_out_socket * create_link_out(const ::string & pszServer, ::sockets::httpd_socket * phttpdsocket);
      ::size_i32 get_image_size(const ::file::path & strFile);
      bool extract_image_size(const ::file::path & strFile,::size_i32 * psize);


      virtual void defer_clean_session();

      virtual ::file::path get_full_stage_path(const ::file::path & strScript);

      virtual ::file::path get_stage_path(const ::file::path & strScript);

      virtual bool should_build(const ::file::path & strScript);

      virtual ::file::path get_script_path(const ::file::path & strName, const ::string & strModifier);

   };


} // namespace dynamic_source



