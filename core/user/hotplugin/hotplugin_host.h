#pragma once


namespace hotplugin
{


   class CLASS_DECL_BERG host :
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


      ::pointer < ::mutex >                       m_pmutexSystem;

      ::image::image_pointer               m_pimage;

      ::int_rectangle                        m_rectangle;
      ::int_rectangle                        m_rectangleX;
      ::int_rectangle                        m_rectangleWindow;

      bool                          m_bHostStarterStart;



      host();
      virtual ~host();


      virtual void * get_context_system();

      virtual void redraw() override;

      virtual bool open_link(const ::scoped_string & scopedstrLink,const ::scoped_string & scopedstrTarget) override;
      virtual bool reload_plugin() override;

      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string get_host_location_url() override;

      virtual void post_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam) override;

      virtual oswindow get_host_user_interaction() override;

      //using ::hotplugin::plugin::window_rectangle;
      //virtual bool window_rectangle(::long_long_rectangle * prectangle) override;

      //using ::hotplugin::plugin::this->rectangle;
      //virtual bool this->rectangle(::long_long_rectangle * prectangle) override;

      virtual bool hotplugin_host_begin();
      virtual bool hotplugin_host_is_initialized();
      virtual bool hotplugin_host_initialize();

      virtual void hotplugin_host_on_write();


      virtual void   set_memory(void * puchMemory, ::collection::count c) override;
      virtual void   append_memory(void * puchMemory, ::collection::count c) override;
      virtual ::collection::count get_memory_length() override;
      virtual ::collection::count read_memory(void * puchMemory, ::collection::count c) override;
      virtual void   free_memory() override;


      virtual void set_ready() override;
      virtual void on_ready() override;


      virtual bool plugin_initialize() override;
      virtual bool plugin_finalize() override;


      virtual void start_plugin() override;

      virtual int  start_ca2_system() override;

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle) override;


      virtual int start_app_install(const ::scoped_string & scopedstrCommandLine);

      static int s_start_app_install(const ::scoped_string & scopedstrCommandLine,::aura::application * papp,host * phost, plugin * pplugin = nullptr);

      int start_app_install(const ::scoped_string & scopedstrCommandLine, ::aura::application * papp, plugin * pplugin = nullptr);

      static int s_host_starter_start_sync(const ::scoped_string & scopedstrCommandLine,::aura::application * papp,host * phost,plugin * pplugin = nullptr);

      int host_starter_start_sync(const ::scoped_string & scopedstrCommandLine, ::aura::application * papp, plugin * pplugin = nullptr);

      virtual void deferred_prodevian_redraw() override;

      virtual void start_ca2() override;

      virtual void set_progress_rate(double dRate) override;

      virtual double get_progress_rate() override;

      virtual void set_ca2_installation_ready(bool bReady = true) override;

      virtual bool is_ca2_installation_ready();

      virtual void set_status(const ::scoped_string & scopedstrStatus) override;

      virtual void set_bitmap(::draw2d::graphics * pimage, const ::int_rectangle & rectangle);


      virtual void paint_bitmap(::draw2d::graphics * pimage,const ::int_rectangle & rectangle);


      virtual void blend_bitmap(::draw2d::graphics * pimage,const ::int_rectangle & rectangle);


      virtual void translate_mouse_message(int * px, int * py) override;

      virtual void message_handler(::user::message * pusermessage) override;
      virtual void plugin_message_handler(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, bool bEnsureTx) override;

      virtual void plugin_message_handler(MESSAGE * pmsg, bool bEnsureTx) override;


   };


} // namespace hotplugin


