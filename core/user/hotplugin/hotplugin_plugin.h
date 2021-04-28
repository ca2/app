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
      i32                       m_iHealingSurface;
      u32                      m_last_redraw;
      i32                       m_iEdge;
      bool                          m_bAppStarted;
      manual_reset_event            m_evReady;
      bool                          m_bApp;
      host *                        m_phost;
      bool                          m_bOk;
      bool                          m_bStream;

      ::image_pointer              m_pimage;
      ::draw2d::graphics_pointer         m_pgraphics;
      file::memory_map              m_memorymapBitmap;
      ::size_i32                        m_sizeBitmap;

      string                        m_strStatus;
      string                        m_strStatus2;

      itask_t                      m_nCa2StarterStartThreadID;
      bool                          m_bReload;
      bool                          m_bInstalling;
      const char *                  m_pszReloadCommandLine;

      ::mutex *                       m_pmutexBitmap;
      ::size_i32                          m_sizeBitmapData;
      string                        m_strBitmapChannel;
      ::point_i32                         m_pointCursorPhase;

      millis m_millisSync;
      i32                       m_iDelta;


      plugin();
      virtual ~plugin();


      virtual void install_message_routing(::channel * pchannel) override;

      // host should implement
      virtual bool         open_link(const string & strLink,const string & pszTarget);
      virtual bool         reload_plugin();

      virtual void delete_this() override;
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string     get_host_location_url();

      //virtual void set_finish() override;


      //virtual property fetch_property(const ::id & id) override;


      virtual void         redraw();
      virtual void         post_message(const ::id & id, wparam wparam, lparam lparam);

      virtual oswindow         get_host_window();

      /*
      using ::user::interaction::_001ClientToScreen;
      virtual bool _001ClientToScreen(POINT_I32 * ppt) override;

      using ::user::interaction::_001ScreenToClient;
      virtual bool _001ScreenToClient(POINT_I32 * ppt) override;

      using ::user::interaction::get_window_rect;
      virtual bool get_window_rect(RECTANGLE_I64 * prectangle) override;

      using ::user::interaction::get_client_rect;
      virtual bool get_client_rect(RECTANGLE_I64 * prectangle) override;
      */



      virtual void translate_mouse_message(int * px, int * py);

      //virtual bool display(int nCmdShow);
      //virtual bool destroy_window();
      //
      // call host memory
      virtual void   set_memory(void * puchMemory, ::count c);
      virtual void   append_memory(void * puchMemory, ::count c);
      virtual ::count get_memory_length();
      virtual ::count read_memory(void * puchMemory, ::count c);
      virtual void   free_memory();
      //static  void   free_memory(u8 ** ppuchMemory);


      virtual bool is_ok();
      virtual void set_ready();
      virtual void on_ready();

      virtual bool plugin_initialize();
      virtual bool plugin_finalize();

      virtual void start_plugin();

      virtual i32  start_ca2_system();

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual void deferred_prodevian_redraw();

      virtual void plugin_system_redraw();


#if !defined(WINDOWS) && !defined(APPLEOS) && !defined(ANDROID)
      using ::user::interaction::message_handler;
      virtual i32 x11_message_handler(void * pevent);
#endif
      virtual void message_handler(::user::message * pusermessage) override;
      virtual void plugin_message_handler(const ::id & id, wparam wparam, lparam lparam, bool bEnsureTx);

      virtual void plugin_message_handler(MESSAGE * pmsg,bool bEnsureTx);


      virtual void on_bare_paint(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual void on_bare_paint_full_screen(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual void on_bare_paint_discreet(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual void on_bare_paint_veri_discreet(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual void start_ca2();

      virtual void set_progress_rate(double dRate);

      virtual double get_progress_rate();

      virtual void on_update_progress();

      virtual void on_paint_progress(::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & prectangle);


      virtual double extract_spa_progress_rate();

      virtual void set_ca2_installation_ready(bool bReady = true);

      virtual void set_status(const char * pszStatus);

      virtual void restart_aura_ipc() override;

      virtual void ensure_bitmap_data(const ::size_i32 & size, bool bCreateFile);

      virtual bool set_host(::hotplugin::host * phost);

      virtual void get_progress_color(byte & uchR, byte & uchG, byte & uchB, double dRate, i32 iProfile);

      virtual void on_host_timer();

      //virtual ::form_property_set * get_form_property_set() override;

      virtual ::e_status finalize() override;
      //virtual void install_message_routing(::channel * pchannel) override;
      //virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


   };


} // namespace hotplugin




