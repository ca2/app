#pragma once


class CLASS_DECL_APEX inteprocess_channel :
   virtual public object,
   virtual public ::interprocess_channel::listener
{
public:


   using interprocess_map = atom_map < ::pointer< ::interprocess::task > >;


   interlocked_count                                                 m_iTaskSeed;
   string                                                            m_strApp;
   ::atom                                                            m_atomApp;
   string_map < ::pointer<::interprocess::caller > >   m_callermap;
   string_map < ::pointer< ::mutex > >                                m_mapAppMutex;
   ::pointer<::interprocess::handler>                  m_phandler;
   string_array_base                                                      m_straModule;

   // strTask - Task
   interprocess_map                                                  m_mapTask;

protected:

   using object::initialize;

public:


   interprocess_intercommunication();
   ~interprocess_intercommunication() override;


   virtual void initialize_interprocess_communication(::object* pparticle, const ::scoped_string & scopedstrApp);


   void destroy() override;


   virtual void defer_add_module(const ::scoped_string & scopedstrModule, const ::atom& idPid);

   virtual ::pointer<::interprocess::task>create_task(::interprocess::call* pcall, const ::atom& idPid);

   virtual ::pointer<::interprocess::task>get_task(long long iTask);

   virtual ::pointer<::interprocess::call>create_call(const ::scoped_string & scopedstrApp, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember);

   virtual ::pointer<::interprocess::call>create_call(const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember);

   virtual ::interprocess::caller & call(const ::scoped_string & scopedstrApp, const ::atom& idPid);

   virtual atom_array get_pid(const ::scoped_string & scopedstrApp);

   virtual string key(const ::scoped_string & scopedstrApp, const ::atom& idPid);

   virtual string str_from_va(const payload_array& va);

   virtual void on_interprocess_handle(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset);

   //using ::interprocess::handler::receiver::on_interprocess_receive;

   bool on_interprocess_handle(::interprocess::handler* phandler, const ::scoped_string & scopedstrUri) override;

   virtual void start(const ::scoped_string & scopedstrApp);

   virtual void connect(const ::scoped_string & scopedstrApp, const ::atom& idPid);

   virtual void on_new_instance(const ::scoped_string & scopedstrModule, const ::atom& idPid);

   void interprocess_communication_open(const ::file::path & path);

};


//} // namespace apex




