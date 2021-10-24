#pragma once


namespace hotplugin
{


   class CLASS_DECL_BASE composer
   {
   public:


      enum enum_state    
      {

         state_start_axis_system,
         state_start_composer_system,
         state_start_host,
         state_init_host,
         state_start_window,
         state_ok,

      };


      bool                          m_bFocus;
      bool                          m_bActive;
      bool                          m_bSendActivationState;
      bool                          m_bActivationStateSent;
      bool                          m_bRectSent;


      enum_state                                m_estate;
      bool                                   m_bBaseSystemOk;
      bool                                   m_bComposerSystemOk;
      bool                                   m_bInit;
      bool                                   m_bHostOk;
      bool                                   m_bTryInitHost;
      bool                                   m_bHostInit;
      bool                                   m_bTryInitWindow;
      bool                                   m_bWindowOk;
      bool                                   m_bOk;
      ::rectangle_i32                                 m_rectangle;
      bool                                   m_bResponsive;
      string                                 m_strEntryHallText;
      ::duration m_durationEntryHallTextStart;
      bool                                   m_bEntryHallTextStarted;


      ::hotplugin::host *                    m_paxishost;


      bool                                   m_bOpenUrl;
      string                                 m_strOpenUrl;
      string                                 m_strOpenTarget;

      string                                 m_strPluginUrl;
      string                                 m_strPluginHeaders;
      string                                 m_strPluginData;


      string                                 m_strHostPluginLocation;

      bool                                   m_bWrite;

      ::aura::system *                       m_pcomposersystem;


      composer();
      virtual ~composer();


      virtual ::hotplugin::host * create_host(__pointer(::aura::system) psystem) ;

      virtual void hotplugin_composer_on_timer();

      virtual bool on_composer_init_window();

      virtual void deferred_prodevian_redraw();

      // if composer on paint returns (returns true), it has painted something meaningful : no other painting is needed or even desired (finally when system, and host are ok,
      // if host returns in a fashion-timed way the response for bitmap, it draw this bitmap, and not the default waiting [hall] screen painted by this composer).

      virtual bool windows_on_paint(::draw2d::graphics_pointer & pgraphics);


      virtual bool      open_link(const ::string & strLink,const string & pszTarget);

      virtual bool      _open_link(const ::string & strLink,const string & pszTarget);

      virtual bool is_active();

      virtual ::aura::system * get_composer_system();
      virtual bool defer_start_composer_system();
      static u32 c_cdecl composer_system_main(LPVOID pVoid);

      virtual void defer_stop_composer_system();

   };


} // namespace hotplugin


