#pragma once


class CLASS_DECL_APEX inteprocess_channel :
   virtual public object,
   virtual public ::interprocess_channel::listener
{
public:


   using interprocess_map = atom_map < ::pointer< ::interprocess::task > >;


   interlocked_count                                           m_iTaskSeed;
   string                                                      m_strApp;
   ::atom                                                      m_atomApp;
   string_map < ::pointer<::interprocess_channel::caller > >   m_callermap;
   string_map < ::pointer< ::mutex > >                          m_mapAppMutex;
   ::pointer<::interprocess_channel::handler>                  m_phandler;
   string_array                                                m_straModule;

   // strTask - Task
   interprocess_map                                                  m_mapTask;

protected:

   using object::initialize;

public:


   interprocess_intercommunication();
   ~interprocess_intercommunication() override;


   virtual void initialize_interprocess_communication(::object* pparticle, const ::string& strApp);


   void destroy() override;


   virtual void defer_add_module(const ::string& strModule, const ::atom& idPid);

   virtual ::pointer<::interprocess::task>create_task(::interprocess::call* pcall, const ::atom& idPid);

   virtual ::pointer<::interprocess::task>get_task(i64 iTask);

   virtual ::pointer<::interprocess::call>create_call(const ::string& strApp, const ::string& strObject, const ::string& strMember);

   virtual ::pointer<::interprocess::call>create_call(const ::string& strObject, const ::string& strMember);

   virtual ::interprocess::caller & call(const ::string& strApp, const ::atom& idPid);

   virtual atom_array get_pid(const ::string& strApp);

   virtual string key(const string& strApp, const ::atom& idPid);

   virtual string str_from_va(const payload_array& va);

   virtual void on_interprocess_handle(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset);

   //using ::interprocess::handler::receiver::on_interprocess_receive;

   bool on_interprocess_handle(::interprocess::handler* phandler, const ::string & strUri) override;

   virtual void start(const ::string& strApp);

   virtual void connect(const ::string& strApp, const ::atom& idPid);

   virtual void on_new_instance(const ::string& strModule, const ::atom& idPid);

   void interprocess_communication_open(const ::file::path & path);

};


//} // namespace apex




