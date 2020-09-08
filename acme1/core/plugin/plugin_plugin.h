#pragma once


i32 spaboot_start(const char * pszVersion, const char * pszId);


namespace acme
{
   class file;
}


namespace plugin
{

   enum enum_check
   {
      check_before_auth,
      check_before_start,
   };


   class host_interaction;
   class system;

   class CLASS_DECL_ACME plugin :
      virtual public hotplugin::plugin
   {
   public:


      host_interaction *            m_puiHost;
      memory           m_memory;
      //::plugin::system *            m_psystem;
      index                           m_iEdge;
      bool                          m_bMainReady;
      string                        m_strCa2LoginRuri;
      string                        m_strCa2LogoutRuri;
      //::image_pointer              m_pimage;


      plugin();


      virtual host_interaction * create_host_interaction() = 0;

      virtual void set_window_rect(const ::rect & rect);

      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszRun);


      virtual void finalize();

      virtual ::estatus os_native_bergedge_start();

      virtual void on_paint(::draw2d::graphics_pointer & pgraphics,const ::rect & rect);


      virtual i32  start_ca2_system();

      virtual void on_ready();

      virtual void ready_on_main_thread();

      virtual void open_ca2_string(const char * psz);

      virtual void message_handler(::message::acme * pbase);


      void start_ca2_login();
      void start_ca2_logout();
      void ca2_login();
      void ca2_logout();
      //static ::estatus     thread_proc_ca2_login(thread_parameter parameter);
      //static ::estatus     thread_proc_ca2_logout(thread_parameter parameter);


      virtual bool plugin_initialize();


   };


} // namespace npca2


