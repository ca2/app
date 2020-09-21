#include "framework.h"


interprocess_task::interprocess_task(interprocess_call* pcall, const ::id& idPid, i64 iTask) :
   ::object(pcall),
   m_pcall(pcall),
   m_idPid(idPid),
   m_pevReady(__new(manual_reset_event)),
   m_iTask(iTask)
{

}


interprocess_task::~interprocess_task()
{

}


void interprocess_task::do_task(const string& strObject, const string& strMember, const var_array& vara)
{

   ::interprocess_communication::tx& txc = m_pcall->m_pinterprocessintercommunication->tx(m_pcall->m_strApp, m_idPid);

   string strVara = m_pcall->m_pinterprocessintercommunication->str_from_va(vara);

   m_iTask = atomic_increment(&m_pcall->m_pinterprocessintercommunication->m_iTaskSeed);

   string strSource;

   string strPid = __str(m_pcall->m_pinterprocessintercommunication->m_idApp);

   strSource.Format(" from %s:%s ", m_pcall->m_pinterprocessintercommunication->m_strApp.c_str(), strPid.c_str());

   string str = "call " + __str(m_iTask) + strSource + strObject + "." + strMember + ": " + strVara;

   bool bSendOk = txc.send(str, m_pcall->m_duration);

   if (!bSendOk)
   {

      m_var = false;

      m_pevReady->set_event();

   }
   else if (strMember.begins_ci("reply."))
   {

      m_var = true;

      m_pevReady->set_event();

   }

}



