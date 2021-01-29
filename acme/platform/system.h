#pragma once


namespace acme
{


   class CLASS_DECL_ACME system :
      virtual public ::promise::handler,
      virtual public ::task
   {
   public:


#ifdef LINUX
      enum_linux_distribution                            m_elinuxdistribution;
#endif
      ::user::enum_desktop                               m_edesktop;

      ::mutex                                            m_mutexTask;
      task_map                                           m_taskmap;
      task_id_map                                        m_taskidmap;
      ::mutex                                            m_mutexTaskOn;
      map < ithread_t, ithread_t >                       m_mapTaskOn;


      ::apex::system *                                   m_papexsystem;
      ::aqua::system *                                   m_paquasystem;
      ::aura::system *                                   m_paurasystem;
      ::axis::system *                                   m_paxissystem;
      ::base::system *                                   m_pbasesystem;
      ::bred::system *                                   m_pbredsystem;
      ::core::system *                                   m_pcoresystem;

      string                                             m_strOsUserTheme;
      __pointer(::acme::node)                      m_pnode;

      
      ::millis                                           m_millisFileListingCache;


      system();
      virtual ~system();


      void os_construct();


      ::acme::node * node();


      virtual ::e_status create_os_node();

      virtual string os_get_user_theme();


      virtual void defer_calc_os_dark_mode();


      virtual ::user::enum_desktop get_edesktop();

      virtual ::user::enum_desktop calc_edesktop();


      //virtual void defer_calc_os_user_theme();


      virtual ::e_status os_application_system_run();
      virtual ::e_status run_system();

      enum_operating_system get_operating_system() const;

#ifdef LINUX

      inline enum_linux_distribution get_linux_distribution() const {return m_elinuxdistribution;}

#endif

      using ::promise::handler::on_subject;
      virtual void on_subject(::promise::subject * psubject) override;


      virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
      virtual void open_link(string strUrl, string strProfile, string strTarget);
      virtual void open_url(string strUrl, string strProfile, string strTarget);


      virtual ::e_status main_user_async(const ::promise::routine & routine, ::e_priority epriority = priority_normal);

      virtual ::e_status main_user_sync(const ::promise::routine & routine, const ::duration & duration = one_minute(), e_priority epriority = priority_normal);


      ::task * get_task(ithread_t ithread);
      ithread_t get_task_id(::task * ptask);
      void set_task(ithread_t ithread, ::task * ptask);
      void unset_task(ithread_t ithread, ::task * ptask);


      virtual string __get_text(const string & str);

#ifdef LINUX

//!!!      virtual ::e_status defer_initialize_x11();

#endif

      virtual ::e_status message_box(const char* pszText, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::promise::process & process = ::promise::process());


   };


} // namespace acme
