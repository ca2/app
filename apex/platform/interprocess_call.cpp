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

   m_duration = one_minute();

}


interprocess_call::~interprocess_call()
{

}


void interprocess_call::add_arg(const ::payload & payload)
{

   m_varaArgs.add(payload);

}


void interprocess_call::add_args(const var_array& vara)
{

   ::papaya::array::add(m_varaArgs, vara);

}


void interprocess_call::set_timeout(const duration& duration)
{

   m_duration = duration;

}


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

   m_iaExclude.add(m_pcontext->m_papexcontext->os().get_pid());

}


void interprocess_call::post(const ::id& idPid)
{

   fork([this, idPid]()
      {

         auto& pobjectTask = m_mapTask[idPid];

         if (pobjectTask)
         {

            return;

         }

         pobjectTask = m_pinterprocessintercommunication->create_task(this, idPid);

         pobjectTask->do_task(m_strObject, m_strMember, m_varaArgs);

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


::synchronization_result interprocess_call::wait()
{

   auto psynca = synca();

   synchronous_lock synchronouslock(psynca);

   return synchronouslock.wait(m_duration);

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



