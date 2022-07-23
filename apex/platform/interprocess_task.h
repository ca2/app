#pragma once


class CLASS_DECL_APEX interprocess_task :
   virtual public ::element
{
public:


   ::atom                                 m_atomPid;
   ::i64                                  m_iTask;
   __pointer(interprocess_call)           m_pcall;
   ::payload                              m_payload;
   __pointer(manual_reset_event)          m_pevReady;
   tristate                               m_tristateContinue;
   tristate                               m_tristateHandled;


   interprocess_task(interprocess_call* pcall, const ::atom& idPid, i64 iTask);
   ~interprocess_task() override;


   virtual void do_task(const string& strObject, const string& strMember, const property_set & propertyset);


};






