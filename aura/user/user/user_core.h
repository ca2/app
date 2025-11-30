//
// Created by camilo on 2024-10-29 08:23 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace user
{


   struct CLASS_DECL_AURA core_user_layer_t
   {



      //::user::impact_system *                      m_ptemplatePlaceHolder;



      //::user::multiple_document_template *         m_ptemplateProgress2;


      //map_base < ::platform::type, ::user::impact_system * >      m_mapTemplate;

      //atom_map_base < ::user::impact_system * >           m_mapimpactsystem;


      //::pointer<::userex::userex>             m_puserex;
      bool                                         m_bFontSelInitialized;





      string_array_base                                 m_straEscape;

      ::platform::type                             m_typeDefaultMeshData;
      ::platform::type                             m_typeDefaultListHeader;
      ::platform::type                             m_typeDefaultListData;

      ::pointer<::userfs::userfs>               m_puserfs;

      ::e_status                                   m_estatus;

      //::pointer<::user::keyboard>             m_pkeyboard;

      //index                                      m_iEdge;
      //::map_base < ::user::enum_key, ::user::enum_key, bool, bool > *  m_pmapKeyPressed;

      //bool                                       m_bProgrammerMode;

      //bool                                       m_bSystemSynchronizedCursor;
      //int_point                                      m_pointCursor;

      //pointer_array < ::user::interaction >         m_uiptraToolWindow;

      //::windowing::window *                            m_pimplPendingFocus2;
      //::user::interaction *                                 m_puiLastUserInputPopup;
      //::image::cursor *                                    m_pcursor;
      //::image::cursor *                                    m_pcursorCursor;
      //e_cursor                                              m_ecursorDefault;
      //e_cursor                                              m_ecursor;

      //::pointer<::user::theme>                           m_ptheme;
      //string_map_base < ::pointer<::user::theme >>            m_mapTheme;

      //::user::interaction *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;


      //::pointer<::user::copydesk>                        m_pcopydesk;

      //::user::interaction *                                 m_puiMouseMoveCapture;
      //::user::interaction *                                 m_puiLastLButtonDown;


      //::write_text::font_enumeration_item_array                        m_fontenumitema;

      ////index                                               m_iEdge;

      //::pointer<::account::department>                   m_paccount;
      ////::pointer<::account::licensing>                    m_plicensing;
      ////::pointer<::user::interaction>                     m_puserinteractionSystem;

      //::payload                                                   m_varTopicFile;
      //::payload                                                   m_varCurrentImpactFile;
      //bool                                                  m_bShowPlatform;

      //::pointer<::text::context>                     m_ptextcontext;


      //bool                                                  m_bSystemSynchronizedScreen;
      //int_rectangle_array_base                                            m_rectangleaMonitor;
      //int_rectangle_array_base                                            m_rectangleaWorkspace;
      //index                                                 m_iMainMonitor;
      //index                                                 m_iMainWorkspace;



      //atom_map_base < ::user::interaction * >                      m_mapboundui;



      //::pointer<::userpresence::department>              m_puserpresence;


      ////::pointer<::ftpfs>                                 m_pftpfs;
      ////::pointer<::fs::remote_native>                     m_premotefs;
      ////::pointer<::fs::fs>                                m_pfs;
      ////::pointer<::fs::data>                              m_pfsdata;
      ////::pointer<::ifs>                                   m_pifs;
      //////ke
      ////bool                                                  m_bIfs;

      //bool                                                  m_bMatterFromHttpCache;

      //unsigned int                                                 m_dwLongPhRESSingTime;


      //::pointer<::userex::userex>                        m_puserex;
      //bool                                                  m_bFontSelInitialized;
      //::pointer<::write_text::font_list>                     m_pfontlistSingleColumn;
      //::pointer<::user::user>                            m_puser;


   };


   class CLASS_DECL_AURA core_user_layer
   {
   public:


      virtual void on_file_manager_open(::filemanager::data* pdata, ::file::item_array& itema);

      virtual bool get_fs_size(string & strSize, const ::scoped_string & scopedstrPath, bool & bPending);
      virtual bool get_fs_size(long long & i64Size, const ::scoped_string & scopedstrPath, bool & bPending);

      virtual void data_on_after_change(::message::message * pmessage);

      virtual class ::user::keyboard * keyboard();

      virtual bool modal_get_color(::user::interaction * puiOwner, ::color::hls & hls);

      virtual void AddToRecentFileList(const ::scoped_string & scopedstrPathName);


      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);


      virtual void _001OnFileNew();


      virtual ::pointer<::user::list_header>default_create_list_header(::particle * pparticle);
      virtual ::pointer<::user::mesh_data>default_create_mesh_data(::particle * pparticle);
      virtual ::pointer<::user::list_data>default_create_list_data(::particle * pparticle);


      virtual ::platform::type default_type_mesh_data();
      virtual ::platform::type default_type_list_header();
      virtual ::platform::type default_type_list_data();


      virtual void will_use_impact_hint(::atom idImpact);


      //virtual void term_instance() override;


      virtual void LoadStdProfileSettings(unsigned int nMaxMRU = 10);

      virtual ::collection::count get_template_count() const;
      virtual ::pointer<::user::impact_system>get_template(::collection::index index) const;




      ::user::document * hold(::pointer<::user::interaction>pinteraction);


      //virtual void initialize(::particle * pparticle) override;


      //virtual bool do_prompt_file_name(::payload& payloadFile, const ::scoped_string & scopedstrTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument, const atom & atomFileManager = "file_manager_save");


      virtual void initialize_userex();

      virtual void userfs_init1();
      virtual void userfs_process_init();


      //virtual void create_html();

      //virtual ::pointer<::userex::userex>create_userex();
      //virtual ::pointer<::userfs::userfs>create_userfs();


      virtual ::platform::type get_pane_tab_impact_type_info();
      //virtual ::platform::type get_simple_frame_window_type_info() override;
      //virtual ::platform::type get_simple_child_frame_type_info();


      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array_base& patha) override;





   };


} // namespace user



