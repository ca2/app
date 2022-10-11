#pragma once


class CLASS_DECL_APEX ::interprocess::call :
   virtual public ::property_set
{
public:


   ::pointer<interprocess_intercommunication>  m_pinterprocesscommunication;
   string                                       m_strApp;
   id_array                                     m_iaExclude;
   bool                                         m_bAutoLaunch;

   // idPid - Task
   interprocess_task_map                        m_mapTask;


   string                                       m_strObject;
   string                                       m_strMember;


   ::interprocess::call(interprocess_intercommunication* pipi, const string& strApp, const string& strObject, const string& strMember);
   ~::interprocess::call() override;

   void set_auto_launch(bool bSet = true);

   bool is_auto_launch() const;

   void exclude_pid(::i32 iPid);

   //virtual void post(const ::atom& idPid);
   virtual void send(const ::atom& idPid);

   ::pointer<synchronization_array>synca();

   ::e_status wait();
   bool _wait(const class ::wait & wait);


   virtual id_array prepare_call();


   virtual void send_call();
   //virtual void post_call();


};



