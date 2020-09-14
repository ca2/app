#pragma once


namespace apex
{


   class CLASS_DECL_APEX ipi :
      virtual public object,
      virtual public ::apex::ipc::rx::receiver
   {
   public:


      class call;


      class CLASS_DECL_APEX task :
         virtual public ::object
      {
      public:


         ::id                                m_idPid;
         ::i64                               m_iTask;
         __pointer(class call)               m_pcall;
         var                                 m_var;
         __pointer(manual_reset_event)       m_pevReady;


         task(class call * pcall, const ::id & idPid, i64 iTask);
         virtual ~task();


         virtual void do_task(const string & strObject, const string & strMember, const var_array & vara);


      };


      using pid_task = id_map < __pointer(task) >;


      class CLASS_DECL_APEX call :
         virtual public ::object
      {
      public:


         __pointer(ipi)                m_pipi;
         string                        m_strApp;
         ::duration                    m_duration;
         id_array                      m_iaExclude;
         bool                          m_bAutoLaunch;

         // idPid - Task
         pid_task                      m_mapTask;


         string                        m_strObject;
         string                        m_strMember;
         var_array                     m_varaArgs;


         call(ipi * pipi, const string & strApp, const string & strObject, const string & strMember);
         virtual ~call();

         auto tasks() { return typename pid_task::dereferenced_value_iterator(nullptr, &m_mapTask); }

         void add_arg(const var & var);
         void add_args(const var_array & vara);
         void set_timeout(const duration & duration);
         void set_auto_launch(bool bSet = true);

         bool is_auto_launch() const;

         void exclude_this_app();

         virtual void post(const ::id & idPid);

         __pointer(sync_array) synca();

         ::sync_result wait();

         void announce();


      };


      ::i64                                        m_iTaskSeed;
      string                                       m_strApp;
      ::id                                         m_idApp;
      string_map < __pointer(::apex::ipc::tx) >    m_txmap;
      string_map < __pointer(::mutex) >            m_mapAppMutex;
      __pointer(::apex::ipc::rx)                   m_prx;
      string_array                                 m_straModule;

      // strTask - Task
      pid_task                                     m_mapTask;


      ipi(const string & strApp);
      virtual ~ipi();


      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual void finalize() override;

      virtual void defer_add_module(const string & strModule, const ::id & idPid);

      virtual __pointer(class task) create_task(call * pcall, const ::id & idPid);

      virtual __pointer(class task) get_task(i64 iTask);

      virtual __pointer(class call) create_call(const string & strApp, const string & strObject, const string & strMember);

      virtual __pointer(class call) create_call(const string & strObject, const string & strMember);

      virtual ::apex::ipc::tx & tx(const string & strApp, const ::id & idPid);

      virtual id_array get_pid(const string & strApp);

      virtual string key(const string &strApp, const ::id & idPid);

      virtual string str_from_va(const var_array & va);

      virtual void on_ipi_call(var & var, const string & strObject, const string & strMember, var_array & vara);

      using ::apex::ipc::rx::receiver::on_ipc_receive;

      virtual void on_ipc_receive(::apex::ipc::rx * prx, const char * pszMessage) override;

      virtual bool start(const string & strApp);

      virtual bool connect(const string & strApp, const ::id & idPid);

      virtual void on_new_instance(const string & strModule, const ::id & idPid);


   };


} // namespace apex




