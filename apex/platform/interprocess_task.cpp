#include "framework.h"


interprocess_task::interprocess_task(interprocess_call* pcall, const ::atom& idPid, i64 iTask) :
   //::object(pcall),
   m_pcall(pcall),
   m_atomPid(idPid),
   m_pevReady(__new(manual_reset_event)),
   m_iTask(iTask)
{
   
}


interprocess_task::~interprocess_task()
{

}


void interprocess_task::do_task(const string& strObject, const string& strMember, const ::property_set & propertyset)
{

   try
   {

      ::interprocess_communication::tx& txc = m_pcall->m_pinterprocessintercommunication->tx(m_pcall->m_strApp, m_atomPid);

      string strNetworkArguments = propertyset.get_network_arguments();

      m_iTask = m_pcall->m_pinterprocessintercommunication->m_iTaskSeed++;

      string strSource;

      string strPid = __string(m_pcall->m_pinterprocessintercommunication->m_atomApp);

      strSource.format("protocol.origin=%s&protocol.origin_pid=%s", m_pcall->m_pinterprocessintercommunication->m_strApp.c_str(), strPid.c_str());
      
      string strApp = m_pcall->m_strApp;
      
      strApp.find_replace("_", "-");
      strApp.find_replace("/", "-");
      strApp.find_replace(".", "-");

      string str = strApp + "://" + strObject + "/" + strMember + "?" + strNetworkArguments + "&protocol.call_id=" + __string(m_iTask) + "&" + strSource + "&protocol.target_pid=" + m_atomPid.to_string();

      //txc.send(str, m_pcall->m_duration);
      txc.send(str, 1_min);

   }
   catch (...)
   {

      m_payload = false;

      m_pevReady->set_event();

      return;

   }

   if (strMember.begins_ci("reply."))
   {

      m_payload = true;

      m_pevReady->set_event();

   }

}



