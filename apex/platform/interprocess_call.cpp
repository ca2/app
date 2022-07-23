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


//void interprocess_call::add_property(const ::property & property)
//{
//
//   m_propertyset.merge(property);
//
//}
//
//
//void interprocess_call::add_property_set(const ::property_set & propertyset)
//{
//
//   m_propertyset.merge(propertyset);
//
//}


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

//m_pcontext->m_papexcontext->os_context()->get_pid()

void interprocess_call::exclude_pid(::i32 iPid)
{

   m_iaExclude.add(iPid);

}


void interprocess_call::send(const ::atom& idPid)
{

   __pointer(interprocess_call) pcall = this;

   auto& pobjectTask = pcall->m_mapTask[idPid];

   if (!pobjectTask)
   {

      pobjectTask = pcall->m_pinterprocessintercommunication->create_task(pcall, idPid);

   }

   pobjectTask->do_task(pcall->m_strObject, pcall->m_strMember, *pcall);

}


//void interprocess_call::post(const ::atom& idPid)
//{
//
//   __pointer(interprocess_call) pcall = this;
//
//   fork([pcall, idPid]()
//      {
//
//         pcall->send(idPid);
//
//      });
//
//}


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

   if (!this->m_mapTask.is_empty())
   {

      if (!_wait(::duration::infinite()))
      {

         return error_wait_timeout;

      }

   }

   return ::success;

}


bool interprocess_call::_wait(const class ::wait & wait)
{

   auto psynca = synca();

   synchronous_lock synchronouslock(psynca);

   return synchronouslock.wait(wait);

}


id_array interprocess_call::prepare_call()
{

   ///exclude_this_app();

   auto iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

   if (iaPid.is_empty())
   {

      if (!is_auto_launch())
      {

         return {};

      }

      m_pinterprocessintercommunication->start(m_strApp);

      iaPid = m_pinterprocessintercommunication->get_pid(m_strApp);

   }

   iaPid -= m_iaExclude;

   return iaPid;

}


void interprocess_call::send_call()
{

#ifdef SANDBOXED_PLATFORM

   send(0);

#else

   auto iaPid = prepare_call();

   for (auto& idPid : iaPid)
   {

      send(idPid);

   }

#endif

}


//void interprocess_call::post_call()
//{
//
//#ifdef SANDBOXED_PLATFORM
//   
//   send(0);
//   
//#else
//   
//   auto iaPid = prepare_call();
//
//   for (auto& idPid : iaPid)
//   {
//
//      send(idPid);
//
//   }
//   
//#endif
//
//}



