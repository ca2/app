// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "call.h"
#include "communication.h"
#include "task.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronous_lock.h"


namespace interprocess
{


   call::call(communication * pcommunication, const string & strApp, const string & strObject, const string & strMember) :
      //::object(pipi),
      m_pinterprocesscommunication(pcommunication),
      m_strApp(strApp),
      m_strObject(strObject),
      m_strMember(strMember),
      m_bAutoLaunch(false)
   {

      initialize(pcommunication);

      //m_time = minute();

   }


   call::~call()
   {

   }


   //void call::add_property(const ::property & property)
   //{
   //
   //   m_propertyset.merge(property);
   //
   //}
   //
   //
   //void call::add_property_set(const ::property_set & propertyset)
   //{
   //
   //   m_propertyset.merge(propertyset);
   //
   //}


   //void call::set_timeout(const time& time)
   //{
   //
   //   m_time = time;
   //
   //}


   void call::set_auto_launch(bool bSet)
   {

      m_bAutoLaunch = bSet;

   }


   bool call::is_auto_launch() const
   {

      return m_bAutoLaunch;

   }

   //m_pcontext->m_papexcontext->os_context()->get_pid()

   void call::exclude_pid(::i32 iPid)
   {

      m_processidentifieraExclude.add(iPid);

   }


   void call::send(const ::atom & idPid)
   {

      ::pointer<call>pcall = this;

      auto & pobjectTask = pcall->m_mapTask[idPid];

      if (!pobjectTask)
      {

         pobjectTask = pcall->m_pinterprocesscommunication->create_task(pcall, idPid);

      }

      pobjectTask->do_task(pcall->m_strObject, pcall->m_strMember, *pcall);

   }


   //void call::post(const ::atom& idPid)
   //{
   //
   //   ::pointer<call>pcall = this;
   //
   //   fork([pcall, idPid]()
   //      {
   //
   //         pcall->send(idPid);
   //
   //      });
   //
   //}


   ::pointer<synchronization_array>call::synca()
   {

      auto psynca = __new(synchronization_array);

      for (auto & ptask : this->m_mapTask.payloads())
      {

         psynca->add(ptask->m_pevReady);

      }

      return psynca;

   }


   ::e_status call::wait()
   {

      if (!this->m_mapTask.is_empty())
      {

         if (!_wait(::time::infinity()))
         {

            return error_wait_timeout;

         }

      }

      return ::success;

   }


   bool call::_wait(const class time & timeWait)
   {

      auto psynca = synca();

      synchronous_lock synchronouslock(psynca);

      return synchronouslock.wait(timeWait);

   }


   ::process_identifier_array call::prepare_call()
   {

      ///exclude_this_app();

      auto iaPid = m_pinterprocesscommunication->processes_identifiers(m_strApp);

      if (iaPid.is_empty())
      {

         if (!is_auto_launch())
         {

            return {};

         }

         m_pinterprocesscommunication->start(m_strApp);

         iaPid = m_pinterprocesscommunication->processes_identifiers(m_strApp);

      }

      iaPid -= m_processidentifieraExclude;

      return iaPid;

   }


   void call::send_call()
   {

#ifdef SANDBOXED_PLATFORM

      send(0);

#else

      auto iaPid = prepare_call();

      for (auto & idPid : iaPid)
      {

         send(idPid);

      }

#endif

   }


   //void call::post_call()
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
} // namespace interprocess


