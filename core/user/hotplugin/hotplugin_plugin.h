#pragma once


#include "base/user/simple_ui/simple_ui_style.h"
#include "base/user/simple_ui/simple_ui_interaction.h"
#include "base/base/base/session.h"


namespace hotplugin
{


   class host;


   class CLASS_DECL_BASE plugin :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style,
      virtual public ::base::session,
      virtual public ::aura::ipc::ipc
   {
   public:


      bool                          m_bOnPaint;
      bool                          m_bInitialized;
      FILE *                        m_pfile;
      bool                          m_bPreCheck;
      int                       m_iHealingSurface;
      unsigned int                      m_last_redraw;
      int                       m_iEdge;
      bool                          m_bAppStarted;
      manual_reset_happening            m_happeningReady;
      bool                          m_bApp;
      host *                        m_phost;
      bool                          m_bOk;
      bool                          m_bStream;

      ::image::image_pointer              m_pimage;
      ::draw2d::graphics_pointer         m_pgraphics;
      file::memory_map              m_memorymapBitmap;
      ::int_size                        m_sizeBitmap;

      string                        m_strStatus;
      string                        m_strStatus2;

      itask                      m_nCa2StarterStartThreadID;
      bool                          m_bReload;
      bool                          m_bInstalling;
      const char *                  m_pszReloadCommandLine;

      ::pointer< ::mutex >                       m_pmutexBitmap;
      ::int_size                          m_sizeBitmapData;
      string                        m_strBitmapChannel;
      ::int_point                         m_pointCursorPhase;

      class ::time m_timeSync;
      int                       m_iDelta;


      plugin();
      virtual ~plugin();


      void install_message_routing(::channel * pchannel) override;

      // host should implement
      virtual bool         open_link(const ::string & strLink,const string & pszTarget);
      virtual bool         reload_plugin();

      virtual void delete_this() override;
      void handle(::topic * ptopic, ::handler_context * pcontext) override;
      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string     get_host_location_url();

      //virtual void set_finish() override;


      //virtual property fetch_property(const ::atom & atom) override;


      virtual void         redraw();
      virtual void         post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam);

      virtual oswindow         get_host_user_interaction();

      /*
      using ::user::interaction::client_to_screen;
      virtual bool client_to_screen(::int_point * ppt) override;

      using ::user::interaction::screen_to_client;
      virtual bool screen_to_client(::int_point * ppt) override;

      using ::user::interaction::window_rectangle;
      virtual bool window_rectangle(::long_long_rectangle * prectangle) override;

      using ::user::interaction::this->rectangle;
      virtual bool this->rectangle(::long_long_rectangle * prectangle) override;
      */



      virtual void translate_mouse_message(int * px, int * py);

      //virtual bool display(int nCmdShow);
      //virtual bool destroy_window();
      //
      // call host memory
      virtual void   set_memory(void * puchMemory, ::collection::count c);
      virtual void   append_memory(void * puchMemory, ::collection::count c);
      virtual ::collection::count get_memory_length();
      virtual ::collection::count read_memory(void * puchMemory, ::collection::count c);
      virtual void   free_memory();
      //static  void   free_memory(unsigned char ** ppuchMemory);


      virtual bool is_ok();
      virtual void set_ready();
      virtual void on_ready();

      virtual bool plugin_initialize();
      virtual bool plugin_finalize();

      virtual void start_plugin();

      virtual int  start_ca2_system();

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual void deferred_prodevian_redraw();

      virtual void plugin_system_redraw();


#if !defined(WINDOWS) && !defined(APPLEOS) && !defined(ANDROID)
      using ::user::interaction::message_handler;
      virtual int x11_message_handler(void * pevent);
#endif
      virtual void message_handler(::user::message * pusermessage) override;
      virtual void plugin_message_handler(::enum_message emessage, ::wparam wparam, ::lparam lparam, bool bEnsureTx);

      virtual void plugin_message_handler(MESSAGE * pmsg,bool bEnsureTx);


      virtual void on_bare_paint(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual void on_bare_paint_full_screen(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual void on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual void on_bare_paint_veri_discreet(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual void start_ca2();

      virtual void set_progress_rate(double dRate);

      virtual double get_progress_rate();

      virtual void on_update_progress();

      virtual void on_paint_progress(::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & prectangle);


      virtual double extract_spa_progress_rate();

      virtual void set_ca2_installation_ready(bool bReady = true);

      virtual void set_status(const ::string & pszStatus);

      virtual void restart_aura_ipc() override;

      virtual void ensure_bitmap_data(const ::int_size & size, bool bCreateFile);

      virtual bool set_host(::hotplugin::host * phost);

      virtual void get_progress_color(unsigned char & uchR, unsigned char & uchG, unsigned char & uchB, double dRate, int iProfile);

      virtual void on_host_timer();

      //virtual ::form_property_set * get_form_property_set() override;

      virtual void destroy() override;
      //void install_message_routing(::channel * pchannel) override;
      //void handle(::topic * ptopic, ::handler_context * pcontext) override;


   };


} // namespace hotplugin




