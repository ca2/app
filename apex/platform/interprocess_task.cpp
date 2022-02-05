#include "framework.h"


interprocess_task::interprocess_task(interprocess_call* pcall, const ::atom& idPid, i64 iTask) :
   //::object(pcall),
   m_pcall(pcall),
   m_idPid(idPid),
   m_pevReady(__new(manual_reset_event)),
   m_iTask(iTask)
{
   
   initialize(pcall);

}


interprocess_task::~interprocess_task()
{

}


void interprocess_task::do_task(const string& strObject, const string& strMember, const payload_array& payloada)
{

   ::interprocess_communication::tx& txc = m_pcall->m_pinterprocessintercommunication->tx(m_pcall->m_strApp, m_idPid);

   string strVara = m_pcall->m_pinterprocessintercommunication->str_from_va(payloada);

   m_iTask = m_pcall->m_pinterprocessintercommunication->m_iTaskSeed++;

   string strSource;

   string strPid = __string(m_pcall->m_pinterprocessintercommunication->m_idApp);

   strSource.format(" from %s:%s ", m_pcall->m_pinterprocessintercommunication->m_strApp.c_str(), strPid.c_str());

   string str = "call " + __string(m_iTask) + strSource + strObject + "." + strMember + ": " + strVara;

   try
   {

      //txc.send(str, m_pcall->m_duration);
      txc.send(str, 1_min);

   }
   catch (...)
   {

      m_var = false;

      m_pevReady->set_event();

      return;

   }

   if (strMember.begins_ci("reply."))
   {

      m_var = true;

      m_pevReady->set_event();

   }

}



