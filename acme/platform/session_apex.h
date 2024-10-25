//
// Created by camilo on 2024-10-24 22:12 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME apex_session_layer_t
   {

      ///__creatable(session);




//#if defined UNIVERSAL_WINDOWS
//
//      ::universal_windows::directx_framework_impact ^                          m_frameworkview;
//
//#endif




      //::aqua::session* m_paquasession;
      //::aura::session* m_paurasession;
      //::axis::session* m_paxissession;
      //::base::session* m_pbasesession;
      //::bred::session* m_pbredsession;
      //::core::session* m_pcoresession;

      // For Mobile systems it is particularly meaningful...
      // ... is is the "Main Window" (sometimes just a concept) holding the App.
      // For Desktop Applications a meaning should be given or this member could be ignored?
      // The Main papp window?
      ::pointer<::user::interaction_base>                        m_puserprimitiveHost;
      //::pointer<::layered>    m_pimplLastSeed;
      //::pointer<::layered>                       m_puiMain2;

      // apex commented
      //::pointer<::user::keyboard>                        m_pkeyboard;

      ::pointer < ::map < ::user::enum_key, bool > >        m_pmapKeyPressed;

      bool                                                  m_bProgrammerMode;

      //bool                                                  m_bOnInitializeWindowObject;

      bool                                                  m_bSystemSynchronizedCursor;
      point_i32                                                 m_pointCursor;

      //comparable_array < ::pointer<::layered >>m_uiptraToolWindow;

      // apex commented
      //::windowing::window *                            m_pimplPendingFocus2;
      //::layered *                                 m_puiLastUserInputPopup;
      //::image::cursor *                                    m_pcursor;
      //::image::cursor *                                    m_pcursorCursor;
      //enum_cursor                                              m_ecursorDefault;
      //enum_cursor                                              m_ecursor;

      // apex commented
      //::layered *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;

      //::pointer<::object>                                  m_pobjectCoreUser;

      // apex commented
      //::pointer<::user::copydesk>                        m_pcopydesk;

      // apex commented
      //::layered *                                 m_puiMouseMoveCapture;
      //::layered *                                 m_puiLastLButtonDown;


      // apex commented
      //::write_text::font_enumeration_item_array                        m_fontenumitema;

      //index                                               m_iEdge;

      //::pointer<::account::department>                   m_paccount;
      //::pointer<::account::licensing>                    m_plicensing;
      //::pointer<::layered>                     m_puserinteractionSystem;

      ::payload                                                   m_varTopicFile;
      bool                                                  m_bShowPlatform;


      //index                                                 m_iMainMonitor;
      //index                                                 m_iMainWorkspace;


      // apex commented
      //atom_map < ::layered * >                      m_mapboundui;



      //::pointer<::userpresence::department>              m_puserpresence;


      ::pointer<::ftpfs>                                 m_pftpfs;
      ::pointer<::fs::remote_native>                     m_premotefs;
      ::pointer<::fs::fs>                                m_pfs;
      ::pointer<::fs::data>                              m_pfsdata;
      ::pointer<::ifs>                                   m_pifs;
      //ke
      bool                                                  m_bIfs;

      bool                                                  m_bMatterFromHttpCache;

      ::u32                                                 m_dwLongPhRESSingTime;


   };


   class CLASS_DECL_ACME apex_session_layer
   {
   public:

   };


} // namespace platform





