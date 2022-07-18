#pragma once



class CLASS_DECL_APEX interprocess_intercommunication :
   virtual public object,
   virtual public ::interprocess_communication::rx::receiver
{
public:



   using interprocess_map = id_map < __pointer(interprocess_task) >;




   interlocked_count                                           m_iTaskSeed;
   string                                                      m_strApp;
   ::atom                                                      m_atomApp;
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
   ~interprocess_intercommunication() override;


   virtual void initialize_interprocess_communication(::object* pobject, const ::string& strApp);

   void destroy() override;

   virtual void defer_add_module(const ::string& strModule, const ::atom& idPid);

   virtual __pointer(interprocess_task) create_task(interprocess_call* pcall, const ::atom& idPid);

   virtual __pointer(interprocess_task) get_task(i64 iTask);

   virtual __pointer(interprocess_call) create_call(const ::string& strApp, const ::string& strObject, const ::string& strMember);

   virtual __pointer(interprocess_call) create_call(const ::string& strObject, const ::string& strMember);

   virtual ::interprocess_communication::tx& tx(const ::string& strApp, const ::atom& idPid);

   virtual id_array get_pid(const ::string& strApp);

   virtual string key(const string& strApp, const ::atom& idPid);

   virtual string str_from_va(const payload_array& va);

   virtual void on_interprocess_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset);

   using ::interprocess_communication::rx::receiver::on_interprocess_receive;

   void on_interprocess_receive(::interprocess_communication::rx* prx, ::string&& strMessage) override;

   virtual void start(const ::string& strApp);

   virtual void connect(const ::string& strApp, const ::atom& idPid);

   virtual void on_new_instance(const ::string& strModule, const ::atom& idPid);

   void interprocess_communication_open(const char* pszPath);

};


//} // namespace apex




