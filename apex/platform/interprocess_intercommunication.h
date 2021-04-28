#pragma once



   //class CLASS_DECL_APEX ipi_call :
   //   virtual public ::object
   //{
   //public:


   //   __pointer(interprocess_intercommunication)                m_pinterprocessintercommunication;
   //   string                        m_strApp;
   //   ::duration                    m_duration;
   //   id_array                      m_iaExclude;
   //   bool                          m_bAutoLaunch;

   //   // idPid - Task
   //   pid_task                      m_mapTask;


   //   string                        m_strObject;
   //   string                        m_strMember;
   //   var_array                     m_varaArgs;


   //   interprocess_call(interprocess_intercommunication* pipi, const string& strApp, const string& strObject, const string& strMember);
   //   virtual ~interprocess_call();

   //   auto tasks() { return typename pid_task::dereferenced_value_iterator(nullptr, &m_mapTask); }

   //   void add_arg(const ::payload & payload);
   //   void add_args(const var_array& vara);
   //   void set_timeout(const duration& duration);
   //   void set_auto_launch(bool bSet = true);

   //   bool is_auto_launch() const;

   //   void exclude_this_app();

   //   virtual void post(const ::id& idPid);

   //   __pointer(synchronization_array) synca();

   //   ::synchronization_result wait();

   //   void announce();


   //};


   //class CLASS_DECL_APEX task :
   //   virtual public ::object
   //{
   //public:


   //   ::id                                m_idPid;
   //   ::i64                               m_iTask;
   //   __pointer(interprocess_call)               m_pcall;
   //   ::payload                                 m_var;
   //   __pointer(manual_reset_event)       m_pevReady;


   //   task(interprocess_call* pcall, const ::id& idPid, i64 iTask);
   //   virtual ~task();


   //   virtual void do_task(const string& strObject, const string& strMember, const var_array& vara);


   //};



   class CLASS_DECL_APEX interprocess_intercommunication :
      virtual public object,
      virtual public ::interprocess_communication::rx::receiver
   {
   public:



      using interprocess_map = id_map < __pointer(interprocess_task) >;




      ::i64                                                       m_iTaskSeed;
      string                                                      m_strApp;
      ::id                                                        m_idApp;
      string_map < __pointer(::interprocess_communication::tx) >  m_txmap;
      string_map < __pointer(::mutex) >                           m_mapAppMutex;
      __pointer(::interprocess_communication::rx)                 m_prx;
      string_array                                                m_straModule;

      // strTask - Task
      interprocess_map                                            m_mapTask;

   protected:

      using object::initialize;

   public:

      interprocess_intercommunication();
      virtual ~interprocess_intercommunication();


      virtual ::e_status initialize_interprocess_communication(::object * pobject, const string & strApp);

      virtual ::e_status finalize() override;

      virtual void defer_add_module(const string & strModule, const ::id & idPid);

      virtual __pointer(interprocess_task) create_task(interprocess_call * pcall, const ::id & idPid);

      virtual __pointer(interprocess_task) get_task(i64 iTask);

      virtual __pointer(interprocess_call) create_call(const string & strApp, const string & strObject, const string & strMember);

      virtual __pointer(interprocess_call) create_call(const string & strObject, const string & strMember);

      virtual ::interprocess_communication::tx & tx(const string & strApp, const ::id & idPid);

      virtual id_array get_pid(const string & strApp);

      virtual string key(const string &strApp, const ::id & idPid);

      virtual string str_from_va(const var_array & va);

      virtual void on_interprocess_call(::payload & payload, const string & strObject, const string & strMember, var_array & vara);

      using ::interprocess_communication::rx::receiver::on_interprocess_receive;

      virtual void on_interprocess_receive(::interprocess_communication::rx * prx, const char * pszMessage) override;

      virtual bool start(const string & strApp);

      virtual bool connect(const string & strApp, const ::id & idPid);

      virtual void on_new_instance(const string & strModule, const ::id & idPid);


   };


//} // namespace apex




