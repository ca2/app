#pragma once


class CLASS_DECL_APEX interprocess_task :
   virtual public ::object
{
public:


   ::atom                                m_idPid;
   ::i64                               m_iTask;
   __pointer(interprocess_call)               m_pcall;
   ::payload                                 m_var;
   __pointer(manual_reset_event)       m_pevReady;


   interprocess_task(interprocess_call* pcall, const ::atom& idPid, i64 iTask);
   virtual ~interprocess_task();


   virtual void do_task(const string& strObject, const string& strMember, const payload_array& payloada);


};






