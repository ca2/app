#pragma once


#include "acme/primitive/collection/string_map.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "apex/message/channel.h"
#include "apex/filesystem/file/listener.h"


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


         ::pointer<script_manager>  m_pmanager;

         clear_include_matches_file_watcher(::particle * pparticle);

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


         string                  m_strServer;
         class ::time            m_time;


      };


      ::netnode::script_manager *                           m_pnetnodescriptmanager;


      pointer_array < plugin_map_item >                      m_pluginmapitema;


      ::pointer < ::mutex >                                               m_pmutexIncludeMatches;
      string_map < bool >                                   m_mapIncludeMatchesFileExists;
      string_map < bool >                                   m_mapIncludeMatchesIsDir;
      ::pointer < ::mutex >                                               m_pmutexIncludeHasScript;
      string_map < bool >                                   m_mapIncludeHasScript;
      ::pointer < ::mutex >                                               m_pmutexShouldBuild;
      string_map < bool >                                   m_mapShouldBuild;
      ::pointer < ::mutex >                                               m_pmutexIncludeExpandMd5;
      string_to_string                                      m_mapIncludeExpandMd5;
      //::pointer<::user::message_window>                  m_pmessagequeue;

      i32                                                   m_iTunnelPluginCount;
      ::pointer < ::mutex >                                               m_pmutexOutLink;
      string_map < ::pointer<::sockets::link_out_socket >> m_mapOutLink;
      ::pointer < ::mutex >                                               m_pmutexInLink;
      ::pointer<::sockets::in_link_map>                    m_pmapInLink;
      ::pointer < ::mutex >                                               m_pmutexTunnel;
      strmap(tunnel_map_item)                               m_mapTunnel;


      ::pointer < ::mutex >                                               m_pmutexImageSize;
      string_map < ::size_i32 >                                 m_mapImageSize;



      string                                                m_strRepos;
      string                                                m_strNamespace;
      ::file::path                                          m_strNetnodePath;
      ::file::path                                          m_strNetseedPath;
      ::file::path                                          m_strNetseedDsCa2Path;

      ::pointer < ::mutex >                                               m_pmutexSimage;
      ::pointer < ::mutex >                                               m_pmutexSpider;

      ::pointer < ::mutex >                                               m_pmutexRsa;

      ::crypto::rsaptra                                     m_rsaptra;

      class ::time                                                  m_timeLastRsa;



      class ::time                                                   m_timeDatabaseWaitTimeOut;

      ::pointer < ::mutex >                                               m_pmutexSession;
      string_map < ::pointer<::dynamic_source::session >>  m_mapSession;
      ::pointer < ::mutex >                                               m_pmutexMusicDbPool;
      ::pointer < ::mutex >                                               m_pmutexWayDbPool;
      ::pointer<script_cache>                              m_pcache;
      ::pointer<script_compiler>                           m_pcompiler;
      class ::time                                       m_timeBuildInterval;
      class ::time                                       m_timeTimeRandomInterval;

      string_to_string                                      m_strmapFunUserKey;

      string                                                m_strPersistentError;

      ::pointer < ::mutex >                                               m_pmutexPersistentStr;
      ::pointer < ::mutex >                                               m_pmutexUiRedir;
      ::pointer < ::mutex >                                               m_pmutexTagId;
      string_to_string                                      m_tagid;
      string_to_string                                      m_usersecuretagid;
      ::pointer < ::mutex >                                               m_pmutexTagName;
      string_to_string                                      m_tagname;


      string                                                m_strSeed;


      bool                                                  m_bCompiler;
      class ::time                                          m_timeSessionExpiration;


      script_manager();
      ~script_manager() override;

      
      virtual void initialize(::particle * pparticle) override;


      virtual void init1();


      virtual bool include_matches_file_exists(const ::string & strPath);
      void set_include_matches_file_exists(const ::string & strPath, bool bFileExists);
      bool include_matches_is_dir(const ::string & strPath);
      bool include_has_script(const ::string & strPath);
      string include_expand_md5(const ::string & strPath);
      void set_include_expand_md5(const ::string & strPath, const ::string & strMd5);

      ::pointer<::dynamic_source::session>get_session(const ::string & pszId);

      ::pointer<script_instance>get(const ::string & strNafme);
      ::pointer<script_instance>get(const ::string & strName, ::pointer<script> & pscript);
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


      ::pointer<::crypto::rsa>get_rsa_key();

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



