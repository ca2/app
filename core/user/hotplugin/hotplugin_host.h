#pragma once


namespace hotplugin
{


   class CLASS_DECL_BASE host :
      virtual public plugin
   {
   public:


      ::hotplugin::composer *       m_pbasecomposer;
      plugin *                      m_pplugin;
      memory                        m_memory;
      double                        m_dProgressRate;
      bool                          m_bShowProgress;


      bool                          m_bCa2InstallationReady;
      // this flag is only set if spaadmin is installing ca files while npca2 is *started*
      // it isn't set when npca2 is already running and spaadmin starts, may be only in the case above, when npca2 *restarts*.
      // this enables spaadmin to install ca files to ca folder, because npca2 would not use any ca shared libraries.
      bool                          m_bRunningSpaAdmin;


      ::mutex                       m_mutexSystem;

      ::image_pointer               m_pimage;

      ::rectangle_i32                        m_rectangle;
      ::rectangle_i32                        m_rectangleClient;
      ::rectangle_i32                        m_rectangleWindow;

      bool                          m_bHostStarterStart;



      host();
      virtual ~host();


      virtual void * get_context_system();

      virtual void redraw() override;

      virtual bool open_link(const ::string & strLink,const string & pszTarget) override;
      virtual bool reload_plugin() override;

      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string get_host_location_url() override;

      virtual void post_message(const ::atom & atom, wparam wparam, lparam lparam) override;

      virtual oswindow get_host_window() override;

      //using ::hotplugin::plugin::get_window_rect;
      //virtual bool get_window_rect(RECTANGLE_I64 * prectangle) override;

      //using ::hotplugin::plugin::get_client_rect;
      //virtual bool get_client_rect(RECTANGLE_I64 * prectangle) override;

      virtual bool hotplugin_host_begin();
      virtual bool hotplugin_host_is_initialized();
      virtual bool hotplugin_host_initialize();

      virtual void hotplugin_host_on_write();


      virtual void   set_memory(void * puchMemory, ::count c) override;
      virtual void   append_memory(void * puchMemory, ::count c) override;
      virtual ::count get_memory_length() override;
      virtual ::count read_memory(void * puchMemory, ::count c) override;
      virtual void   free_memory() override;


      virtual void set_ready() override;
      virtual void on_ready() override;


      virtual bool plugin_initialize() override;
      virtual bool plugin_finalize() override;


      virtual void start_plugin() override;

      virtual i32  start_ca2_system() override;

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle) override;


      virtual i32 start_app_install(const ::string & pszCommandLine);

      static i32 s_start_app_install(const ::string & pszCommandLine,::aura::application * papp,host * phost, plugin * pplugin = nullptr);

      i32 start_app_install(const ::string & pszCommandLine, ::aura::application * papp, plugin * pplugin = nullptr);

      static i32 s_host_starter_start_sync(const ::string & pszCommandLine,::aura::application * papp,host * phost,plugin * pplugin = nullptr);

      i32 host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, plugin * pplugin = nullptr);

      virtual void deferred_prodevian_redraw() override;

      virtual void start_ca2() override;

      virtual void set_progress_rate(double dRate) override;

      virtual double get_progress_rate() override;

      virtual void set_ca2_installation_ready(bool bReady = true) override;

      virtual bool is_ca2_installation_ready();

      virtual void set_status(const ::string & pszStatus) override;

      virtual void set_bitmap(::draw2d::graphics * pimage, const ::rectangle_i32 & rectangle);


      virtual void paint_bitmap(::draw2d::graphics * pimage,const ::rectangle_i32 & rectangle);


      virtual void blend_bitmap(::draw2d::graphics * pimage,const ::rectangle_i32 & rectangle);


      virtual void translate_mouse_message(int * px, int * py) override;

      virtual void message_handler(::user::message * pusermessage) override;
      virtual void plugin_message_handler(const ::atom & atom,wparam wparam,lparam lparam, bool bEnsureTx) override;

      virtual void plugin_message_handler(MESSAGE * pmsg, bool bEnsureTx) override;


   };


} // namespace hotplugin


