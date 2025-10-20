#pragma once


#include "acme/parallelization/semaphore.h"
#include "acme/prototype/collection/string_map.h"
#include "acme/prototype/geometry2d/size.h"
#include "apex/message/channel.h"
#include "acme/filesystem/watcher/listener.h"
#include "acme/filesystem/filesystem/file_system_cache_item.h"
#include "acme/filesystem/filesystem/file_system_cache.h"
#include "acme/filesystem/filesystem/file_system_real_path_interface.h"


namespace dynamic_source
{




   class CLASS_DECL_APP_PROGRAMMING script_manager :
      virtual public ::channel,
      virtual public ::file_system_cache,
      virtual public ::file_system_real_path_interface
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
      //::pointer<::user::message_window>                  m_pmessagequeue;

      int                                                   m_iTunnelPluginCount;
      ::pointer < ::mutex >                                 m_pmutexOutLink;
      string_map_base < ::pointer<::sockets::link_out_socket > > m_mapOutLink;
      ::pointer < ::mutex >                                 m_pmutexInLink;
      ::pointer<::sockets::in_link_map>                     m_pmapInLink;
      ::pointer < ::mutex >                                 m_pmutexTunnel;
      ::string_map < tunnel_map_item >                      m_mapTunnel;


      ::pointer < ::mutex >                                 m_pmutexImageSize;
      string_map_base < ::int_size >                             m_mapImageSize;



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

      ::pointer < ::mutex >                                 m_pmutexShouldBuild;
      string_map_base < ::logic::boolean >                       m_mapShouldBuild2;


      class ::time                                          m_timeDatabaseWaitTimeOut;

      ::pointer < ::mutex >                                 m_pmutexSession;
      string_map_base < ::pointer<::dynamic_source::session > >  m_mapSession;
      ::pointer < ::mutex >                                 m_pmutexMusicDbPool;
      ::pointer < ::mutex >                                 m_pmutexWayDbPool;
      ::pointer<script_cache>                               m_pcache;
      ::pointer<script_compiler>                            m_pcompiler;
      class ::time                                          m_timeBuildInterval;
      class ::time                                          m_timeTimeRandomInterval;

      string_to_string_base                                      m_strmapFunUserKey;

      string                                                m_strPersistentError;

      ::pointer < ::mutex >                                 m_pmutexPersistentStr;
      ::pointer < ::mutex >                                 m_pmutexUiRedir;
      ::pointer < ::mutex >                                 m_pmutexTagId;
      string_to_string_base                                      m_tagid;
      string_to_string_base                                      m_usersecuretagid;
      ::pointer < ::mutex >                                 m_pmutexTagName;
      string_to_string_base                                      m_tagname;


      string                                                m_strSeed1;
      ::file_system_cache_item                              m_filesystemcacheitemSeed;


      bool                                                  m_bCompiler;
      class ::time                                          m_timeSessionExpiration;
      ///::pointer < ::programming::file_system_cache >        m_pfilesystemcache;

      script_manager();
      ~script_manager() override;

      
      void initialize(::particle * pparticle) override;


      void on_initialize_particle() override;


      void destroy() override;


      virtual void init1();


      ::file_system_real_path_interface* get_file_system_real_path_interface() override;
      //virtual ::programming::file_system_cache* fs_cache();

      ::pointer<::dynamic_source::session>get_session(const ::scoped_string & scopedstrId);

      virtual ::file_system_cache_item netnode_file_path(const ::scoped_string& scopedstrName);

      //::pointer<script_instance>get(const ::scoped_string & scopedstrName);
      //::pointer<script_instance>get(const ::scoped_string & scopedstrName, ::pointer<script> & pscript);
      ::pointer<script_instance>get(::file_system_item * pfilesystemitem);
      ::pointer<script_instance>get(::file_system_item* pfilesystemitem, ::pointer<script>& pscript);
      virtual void handle(::dynamic_source::httpd_socket * psocket);
      //::payload get_output_internal(::dynamic_source::script_interface * pinstanceParent, const ::scoped_string & scopedstrName);
      ::payload get_output_internal(::dynamic_source::script_interface* pinstanceParent, ::file_system_item * pfilesystemitem);
      void run(const ::file_system_cache_item& filesystemcacheitem);

      void LoadEnv();

      string get_library_build_log();


      //static unsigned int c_cdecl clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

      ::file::path _real_path1(const ::scoped_string& scopedstrName) override;
      //virtual ::file_system_cache_item _real_path(const ::file::path & str);
      virtual ::file::path _real_path2(const ::file::path & strBase,const ::file::path & str);


      ::pointer<::crypto::rsa>get_rsa_key();

      string get_rsa_key(script_interface * pscriptinterface);

      void calc_rsa_key();


      virtual void on_load_env();

      virtual void register_plugin(const ::scoped_string & scopedstrHost, const ::file_system_cache_item& filesystemcacheitem, script * pscript);


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

      virtual ::file::path netnode_file_path(const ::file::path & strName, const ::scoped_string & scopedstrModifier);

   };


} // namespace dynamic_source



