#include "framework.h"


interprocess_call::interprocess_call(interprocess_intercommunication* pipi, const string& strApp, const string& strObject, const string& strMember) :
   //::object(pipi),
   m_pinterprocessintercommunication(pipi),
   m_strApp(strApp),
   m_strObject(strObject),
   m_strMember(strMember),
   m_bAutoLaunch(false)
{

   initialize(pipi);

   //m_duration = minute();

}


interprocess_call::~interprocess_call()
{

}


void interprocess_call::add_arg(const ::payload & payload)
{

   m_payloadaArgs.add(payload);

}


void interprocess_call::add_args(const payload_array& payloada)
{

   ::papaya::array::add(m_payloadaArgs, payloada);

}


//void interprocess_call::set_timeout(const duration& duration)
//{
//
//   m_duration = duration;
//
//}


void interprocess_call::set_auto_launch(bool bSet)
{

   m_bAutoLaunch = bSet;

}


bool interprocess_call::is_auto_launch() const
{

   return m_bAutoLaunch;

}


void interprocess_call::exclude_this_app()
{

   m_iaExclude.add(m_pcontext->m_papexcontext->os_context()->get_pid());

}


void interprocess_call::post(const ::atom& idPid)
{

   __pointer(interprocess_call) pcall = this;

   fork([pcall, idPid]()
      {

         auto& pobjectTask = pcall->m_mapTask[idPid];

         if (!pobjectTask)
         {

            pobjectTask = pcall->m_pinterprocessintercommunication->create_task(pcall, idPid);

         }

         pobjectTask->do_task(pcall->m_strObject, pcall->m_strMember, pcall->m_payloadaArgs);

      });

}


__pointer(synchronization_array) interprocess_call::synca()
{

   auto psynca = __new(synchronization_array);

   for (auto& ptask : this->m_mapTask.values())
   {

      psynca->add(ptask->m_pevReady);

   }

   return psynca;

}


::e_status interprocess_call::wait()
{

   if(!_wait(::duration::infinite()))
   {

      return error_wait_timeout;

   }

   return ::success;

}


bool interprocess_call::_wait(const class ::wait & wait)
{

   auto psynca = synca();

   synchronous_lock synchronouslock(psynca);

   return synchronouslock.wait(wait);

}


void interprocess_call::announce()
{

   exclude_this_app();

   auto iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

   if (iaPid.is_empty())
   {

      if (!is_auto_launch())
      {

         return;

      }

      m_pinterprocessintercommunication->start(m_strApp);

      iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

   }

   iaPid -= m_iaExclude;

   for (auto& idPid : iaPid)
   {

      post(idPid);

   }

}



