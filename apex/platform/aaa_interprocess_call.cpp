#include "framework.h"


::interprocess::call::interprocess::call(interprocess_intercommunication* pipi, const string& strApp, const string& strObject, const string& strMember) :
   //::object(pipi),
   m_pinterprocesscommunication(pipi),
   m_strApp(strApp),
   m_strObject(strObject),
   m_strMember(strMember),
   m_bAutoLaunch(false)
{

   initialize(pipi);

   //m_duration = minute();

}


::interprocess::call::~::interprocess::call()
{

}


//void ::interprocess::call::add_property(const ::property & property)
//{
//
//   m_propertyset.merge(property);
//
//}
//
//
//void ::interprocess::call::add_property_set(const ::property_set & propertyset)
//{
//
//   m_propertyset.merge(propertyset);
//
//}


//void ::interprocess::call::set_timeout(const duration& duration)
//{
//
//   m_duration = duration;
//
//}


void ::interprocess::call::set_auto_launch(bool bSet)
{

   m_bAutoLaunch = bSet;

}


bool ::interprocess::call::is_auto_launch() const
{

   return m_bAutoLaunch;

}

//m_pcontext->m_papexcontext->os_context()->get_pid()

void ::interprocess::call::exclude_pid(::i32 iPid)
{

   m_iaExclude.add(iPid);

}


void ::interprocess::call::send(const ::atom& idPid)
{

   ::pointer<::interprocess::call>pcall = this;

   auto& pobjectTask = pcall->m_mapTask[idPid];

   if (!pobjectTask)
   {

      pobjectTask = pcall->m_pinterprocesscommunication->create_task(pcall, idPid);

   }

   pobjectTask->do_task(pcall->m_strObject, pcall->m_strMember, *pcall);

}


//void ::interprocess::call::post(const ::atom& idPid)
//{
//
//   ::pointer<::interprocess::call>pcall = this;
//
//   fork([pcall, idPid]()
//      {
//
//         pcall->send(idPid);
//
//      });
//
//}


::pointer<synchronization_array>::interprocess::call::synca()
{

   auto psynca = __new(synchronization_array);

   for (auto& ptask : this->m_mapTask.values())
   {

      psynca->add(ptask->m_pevReady);

   }

   return psynca;

}


::e_status ::interprocess::call::wait()
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


bool ::interprocess::call::_wait(const class ::wait & wait)
{

   auto psynca = synca();

   synchronous_lock synchronouslock(psynca);

   return synchronouslock.wait(wait);

}


atom_array ::interprocess::call::prepare_call()
{

   ///exclude_this_app();

   auto iaPid = m_pinterprocesscommunication->get_pid(m_strApp);

   if (iaPid.is_empty())
   {

      if (!is_auto_launch())
      {

         return {};

      }

      m_pinterprocesscommunication->start(m_strApp);

      iaPid = m_pinterprocesscommunication->get_pid(m_strApp);

   }

   iaPid -= m_iaExclude;

   return iaPid;

}


void ::interprocess::call::send_call()
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


//void ::interprocess::call::post_call()
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



