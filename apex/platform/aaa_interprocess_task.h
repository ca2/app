#pragma once


class CLASS_DECL_APEX ::interprocess::task :
   virtual public ::element
{
public:


   ::atom                                 m_atomPid;
   long long                                  m_iTask;
   ::pointer<::interprocess::call>          m_pcall;
   ::payload                              m_payload;
   ::pointer<manual_reset_happening>         m_pevReady;
   boolean                               m_tristateContinue;
   boolean                               m_tristateHandled;


   ::interprocess::task(::interprocess::call* pcall, const ::atom& idPid, long long iTask);
   ~::interprocess::task() override;


   virtual void do_task(const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, const property_set & propertyset);


};






