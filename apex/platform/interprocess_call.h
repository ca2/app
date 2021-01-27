#pragma once


class CLASS_DECL_APEX interprocess_call :
   virtual public ::object
{
public:


   __pointer(interprocess_intercommunication)                m_pinterprocessintercommunication;
   string                        m_strApp;
   ::duration                    m_duration;
   id_array                      m_iaExclude;
   bool                          m_bAutoLaunch;

   // idPid - Task
   interprocess_task_map         m_mapTask;


   string                        m_strObject;
   string                        m_strMember;
   var_array                     m_varaArgs;


   interprocess_call(interprocess_intercommunication* pipi, const string& strApp, const string& strObject, const string& strMember);
   virtual ~interprocess_call();

   //inline auto tasks() const { return m_mapTask.values(); }

   void add_arg(const ::payload & payload);
   void add_args(const var_array& vara);
   void set_timeout(const duration& duration);
   void set_auto_launch(bool bSet = true);

   bool is_auto_launch() const;

   void exclude_this_app();

   virtual void post(const ::id& idPid);

   __pointer(sync_array) synca();

   ::sync_result wait();

   void announce();


};



