#pragma once


class CLASS_DECL_APEX ::interprocess::task :
   virtual public ::element
{
public:


   ::atom                                 m_atomPid;
   ::i64                                  m_iTask;
   ::pointer<::interprocess::call>          m_pcall;
   ::payload                              m_payload;
   ::pointer<manual_reset_event>         m_pevReady;
   boolean                               m_tristateContinue;
   boolean                               m_tristateHandled;


   ::interprocess::task(::interprocess::call* pcall, const ::atom& idPid, i64 iTask);
   ~::interprocess::task() override;


   virtual void do_task(const string& strObject, const string& strMember, const property_set & propertyset);


};






