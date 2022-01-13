// Extrapolation from merge with control_"subject" by camilo on day after ThomasBirthday2021 10:30!!
#include "framework.h"


signal::signal(const ::id & id, ::manager * pmanager) :
   ::material_object(id),
   ::property_object(id),
   ::object(id),
   ::subject(id),
   m_pmanager(pmanager)
{


}


signal::~signal()
{


}


#ifdef _DEBUG


i64 signal::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::subject::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 signal::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::subject::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 signal::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::subject::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif




//void signal::step()
//{
//
//   auto ptask = ::get_task();
//
//   if (::manager::s_bDestroyAll || !ptask->task_get_run())
//   {
//
//      return ::error_failed;
//
//   }
//
//   m_pmanager->signal(this);
//
//   return ::success;
//
//}


//bool signal::is_modified()
//{
//
//   return false;
//
//}


void signal::run()
{

   while (true)
   {

      bool bModified = is_modified();

      if (!bModified)
      {

         // fetch updated polling time
         auto iPollMillis = poll_time();

         if (!should_poll(iPollMillis))
         {

            break;

         }

         if (::manager::__s_may_run_signal_handling())
         {

            break;

         }

         ::preempt(iPollMillis);

         continue;

      }

      clear_modified();

      notify();

   }

   //return ::success;

}


void signal::notify()
{

   synchronous_lock synchronouslock(mutex());

   for (auto & pair : m_mattercontext)
   {

      auto & pmatter = pair.m_element1;

      auto & pcontext = pair.m_element2;

      if (!pcontext)
      {

         pcontext = __new(::context);

      }

      if (pcontext->m_bFork)
      {

         branch_task(pmatter);

      }
      else
      {

         pmatter->handle(this, pcontext);

      }

   }

}


::context * signal::listener_context(::matter * pmatter)
{

   synchronous_lock synchronouslock(mutex());

   auto & pcontext = m_mattercontext[pmatter];

   if (!pcontext)
   {

      pcontext = __new(::context);

   }

   return pcontext;

}


void signal::start_task()
{

   //return ::success_none;

}


//void subject::reset_update(const ::id & id)
//{
//
//
//}
//

bool signal::is_up_to_date(const ::context * pcontext) const
{

   if (::is_null(m_pmanager))
   {

      return false;

   }

   if (m_iUpdateSerial < 0)
   {

      return false;

   }

   return pcontext->is_up_to_date(this);

}


void signal::set_up_to_date(::context * pcontext)
{

   pcontext->set_up_to_date(this);

}



void signal::add_handler(::matter * pmatter, bool bForkWhenNotify)
{

   synchronous_lock synchronouslock(mutex());

   //bool bShouldFork = false;

   //if (m_matterchange.is_empty())
   //{

   //   if (should_poll(poll_millis()))
   //   {

   //      bShouldFork = true;

   //   }

   //}

   //if(m_iUpdateSerial < || >>= 0)
   //{

   //   bShouldFork = true;

   //}

   auto & pcontext = m_mattercontext[pmatter];

   if (!pcontext)
   {

      pcontext = __new(::context);

   }

   pcontext->m_bFork = bForkWhenNotify;

   //pmatter->on_subject(this, pcontext);

}


void signal::erase_handler(::matter * pmatter)
{

   synchronous_lock synchronouslock(mutex());

   m_mattercontext.erase_key(pmatter);

}


void signal::set_modified()
{

   synchronous_lock synchronouslock(mutex());

   m_bModified = true;

   m_iUpdateSerial++;

   if (!should_poll(poll_time()))
   {

      branch_task(this);

   }

}

void signal::clear_modified()
{

   m_bModified = false;

}


bool signal::is_modified() const
{

   return m_bModified;

}


void signal::post_destroy_all()
{

   synchronous_lock synchronouslock(mutex());

   m_mattercontext.erase_all();

}





