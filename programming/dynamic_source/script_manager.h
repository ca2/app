#pragma once


#include "acme/parallelization/semaphore.h"
#include "acme/prototype/collection/string_map.h"
#include "acme/prototype/geometry2d/size.h"
#include "apex/message/channel.h"
#include "acme/filesystem/watcher/listener.h"


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


         script_manager * m_pmanager;

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


      pointer_array < plugin_map_item >                     m_pluginmapitema;

      ::semaphore                                           m_semCompiler;
      ::pointer < ::mutex >                                 m_pmutexIncludeMatches;
      string_map < ::logic::boolean >                       m_mapIncludeMatchesFileExists2;
      string_map < ::logic::boolean >                       m_mapIncludeMatchesIsDir2;
      ::pointer < ::mutex >                                 m_pmutexIncludeHasScript;
      string_map < ::logic::boolean >                       m_mapIncludeHasScript2;
      ::pointer < ::mutex >                                 m_pmutexShouldBuild;
      string_map < ::logic::boolean >                       m_mapShouldBuild2;
      ::pointer < ::mutex >                                 m_pmutexIncludeExpandMd5;
      string_to_string                                      m_mapIncludeExpandMd5;
      //::pointer<::user::message_window>                  m_pmessagequeue;

      int                                                   m_iTunnelPluginCount;
      ::pointer < ::mutex >                                 m_pmutexOutLink;
      string_map < ::pointer<::sockets::link_out_socket > > m_mapOutLink;
      ::pointer < ::mutex >                                 m_pmutexInLink;
      ::pointer<::sockets::in_link_map>                     m_pmapInLink;
      ::pointer < ::mutex >                                 m_pmutexTunnel;
      strmap(tunnel_map_item)                               m_mapTunnel;


      ::pointer < ::mutex >                                 m_pmutexImageSize;
      string_map < ::int_size >                             m_mapImageSize;



      string                                                m_strRepos;
      string                                                m_strNamespace;
      ::file::path                                          m_pathBase;
      ::file::path                                          m_pathNetnodePath;
      ::file::path                                          m_pathNetseedPath;
      ::file::path                                          m_pathNetseedDsCa2Path;

      ::pointer < ::mutex >                                 m_pmutexSimage;
      ::pointer < ::mutex >                                 m_pmutexSpider;

      ::pointer < ::mutex >                                 m_pmutexRsa;
      
      ::crypto::rsaptra                                     m_rsaptra;

      class ::time                                          m_timeLastRsa;



      class ::time                                          m_timeDatabaseWaitTimeOut;

      ::pointer < ::mutex >                                 m_pmutexSession;
      string_map < ::pointer<::dynamic_source::session > >  m_mapSession;
      ::pointer < ::mutex >                                 m_pmutexMusicDbPool;
      ::pointer < ::mutex >                                 m_pmutexWayDbPool;
      ::pointer<script_cache>                               m_pcache;
      ::pointer<script_compiler>                            m_pcompiler;
      class ::time                                          m_timeBuildInterval;
      class ::time                                          m_timeTimeRandomInterval;

      string_to_string                                      m_strmapFunUserKey;

      string                                                m_strPersistentError;

      ::pointer < ::mutex >                                 m_pmutexPersistentStr;
      ::pointer < ::mutex >                                 m_pmutexUiRedir;
      ::pointer < ::mutex >                                 m_pmutexTagId;
      string_to_string                                      m_tagid;
      string_to_string                                      m_usersecuretagid;
      ::pointer < ::mutex >                                 m_pmutexTagName;
      string_to_string                                      m_tagname;


      string                                                m_strSeed;


      bool                                                  m_bCompiler;
      class ::time                                          m_timeSessionExpiration;


      script_manager();
      ~script_manager() override;

      
      void initialize(::particle * pparticle) override;


      void destroy() override;


      virtual void init1();


      virtual bool include_matches_file_exists(const ::scoped_string & scopedstrPath);
      void set_include_matches_file_exists(const ::scoped_string & scopedstrPath, bool bFileExists);
      bool include_matches_is_dir(const ::scoped_string & scopedstrPath);
      bool include_has_script(const ::scoped_string & scopedstrPath);
      string include_expand_md5(const ::scoped_string & scopedstrPath);
      void set_include_expand_md5(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMd5);

      ::pointer<::dynamic_source::session>get_session(const ::scoped_string & scopedstrId);

      ::pointer<script_instance>get(const ::scoped_string & scopedstrName);
      ::pointer<script_instance>get(const ::scoped_string & scopedstrName, ::pointer<script> & pscript);
      virtual void handle(::dynamic_source::httpd_socket * psocket);
      ::payload get_output_internal(::dynamic_source::script_interface * pinstanceParent, const ::scoped_string & scopedstrName);
      void run(const ::scoped_string & scopedstrName);

      void LoadEnv();

      string get_library_build_log();


      virtual void clear_include_matches(::file::path path);
      virtual void clear_include_matches();
      //static unsigned int c_cdecl clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

      virtual ::file::path real_path(const ::file::path & str);
      virtual ::file::path real_path(const ::file::path & strBase,const ::file::path & str);


      ::pointer<::crypto::rsa>get_rsa_key();

      string get_rsa_key(script_interface * pscriptinterface);

      void calc_rsa_key();


      virtual void on_load_env();

      virtual void register_plugin(const ::scoped_string & scopedstrHost, const ::scoped_string & scopedstrScript, const ::scoped_string & scopedstrName, script * pscript);


      virtual string get_root_plugin();


      void wait_link_out(const ::scoped_string & scopedstrServer, ::sockets::link_in_socket * pinsocket);
      bool has_link_out_link(const ::scoped_string & scopedstrServer, ::sockets::link_in_socket * pinsocket, ::httpd::socket * phttpdsocket);
      ::sockets::link_in_socket * get_link_in(const ::scoped_string & scopedstrServer, ::sockets::link_out_socket * poutsocket);
      bool is_online(const ::scoped_string & scopedstrServer);
      ::sockets::link_out_socket * create_link_out(const ::scoped_string & scopedstrServer, ::httpd::socket * phttpdsocket);
      ::int_size get_image_size(const ::file::path & strFile);
      bool extract_image_size(const ::file::path & strFile,::int_size * psize);


      virtual void defer_clean_session();

      virtual ::file::path get_full_stage_path(const ::file::path & strScript);

      virtual ::file::path get_stage_path(const ::file::path & strScript);

      virtual bool should_build(const ::file::path & strScript);

      virtual ::file::path get_script_path(const ::file::path & strName, const ::scoped_string & scopedstrModifier);

   };


} // namespace dynamic_source



