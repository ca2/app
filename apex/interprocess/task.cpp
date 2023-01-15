// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "task.h"
#include "call.h"
#include "caller.h"
#include "communication.h"
#include "acme/parallelization/manual_reset_event.h"


namespace interprocess
{


   task::task(::interprocess::call * pcall, const ::atom & idPid, i64 iTask) :
      //::object(pcall),
      m_pcall(pcall),
      m_atomPid(idPid),
      m_pevReady(__new(manual_reset_event)),
      m_iTask(iTask)
   {

   }


   task::~task()
   {

   }


   void task::do_task(const string & strObject, const string & strMember, const ::property_set & propertyset)
   {

      try
      {

         auto & caller = m_pcall->m_pinterprocesscommunication->caller(m_pcall->m_strApp, m_atomPid);

         string strNetworkArguments = propertyset.get_network_arguments();

         m_iTask = m_pcall->m_pinterprocesscommunication->m_iTaskSeed++;

         string strSource;

         string strPid = m_pcall->m_pinterprocesscommunication->m_atomApp;

         strSource.format("protocol.origin=%s&protocol.origin_pid=%s", m_pcall->m_pinterprocesscommunication->m_strApp.c_str(), strPid.c_str());

         string strApp = m_pcall->m_strApp;

         strApp.find_replace("_", "-");
         strApp.find_replace(".", "-");
         strApp.find_replace("/", ".");

         string str = strApp + ":/" + strObject + "/" + strMember + "?" + strNetworkArguments + "&protocol.call_id=" + as_string(m_iTask) + "&" + strSource + "&protocol.target_pid=" + m_atomPid;

         //txc.send(str, m_pcall->m_time);
         caller.call(str, 1_min);

      }
      catch (...)
      {

         m_payload = false;

         m_pevReady->set_event();

         return;

      }

      if (strMember.case_insensitive_begins("reply."))
      {

         m_payload = true;

         m_pevReady->set_event();

      }

   }


} // namespace interprocess



