#include "framework.h"
#include "acme/platform/object_reference_count_debug.h"


namespace subject
{


   subject::subject(::subject::manager * pmanager, const ::id & id)
   {

      subject_common_construct();

      m_pmanager = pmanager;

      m_id = id;

   }


   subject::~subject()
   {

      m_pmatter.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);

   }


#ifdef _DEBUG


   i64 subject::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 subject::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 subject::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::e_status subject::step()
   {

      auto ptask = ::get_task();

      if(::subject::manager::s_bDestroyAll || !ptask->task_get_run())
      {

         return ::error_failed;

      }

      m_pmanager->handle_subject(this);

      return ::success;

   }


   ::e_status subject::run()
   {

      while (true)
      {

         auto estatus = step();

         if(!estatus)
         {

            return estatus;

         }

         m_pmanager->handle_subject(this);

         // fetch updated polling time
         auto iPollMillis = poll_time();

         if (!should_poll(iPollMillis))
         {

            break;

         }

         if (is_ending())
         {

            break;

         }

         ::preempt(iPollMillis);

      }

      return ::success;

   }


   void subject::notify()
   {

      synchronous_lock synchronouslock(mutex());

      for (auto & pair : m_mattercontext)
      {

         auto & pmatter = pair.m_element1;

         auto & pcontext = pair.m_element2;

         if (!pcontext)
         {

            pcontext = __new(::subject::context);

         }

         if (pcontext->m_bFork)
         {

            branch_task(pmatter);

         }
         else
         {

            pmatter->on_subject(this, pcontext);

         }

      }

   }


   ::subject::context * subject::listener_context(::matter * pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      auto & pcontext = m_mattercontext[pmatter];

      if (!pcontext)
      {

         pcontext = __new(::subject::context);

      }

      return pcontext;

   }



   void subject::subject_common_construct()
   {

      m_esubject = e_subject_handle;
      m_bRet = false;

   }


   ::e_status subject::start_task()
   {

      return ::success_none;

   }


   void subject::reset_update(const ::id &id)
   {

      //m_phandler = ::subject::manager::fork_handler(id);

   }


   //::e_status subject::on_task()
   //{

   //   return run();

   //}


   bool subject::is_up_to_date(const ::subject::context * pcontext) const
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


   void subject::set_up_to_date(::subject::context * pcontext)
   {

      pcontext->set_up_to_date(this);

   }


//   void subject::notify()
//   {
//
//      m_esubject = e_subject_deliver;
//
//      //m_actioncontext = actioncontext;
//
//      for (auto & mattercontext : m_mattercontext)
//      {
//
//         auto & pmatter = mattercontext.m_element1;
//
//         auto & pcontext = mattercontext.m_element2;
//
//         pmatter->on_subject(this, pcontext);
//
//      }
//
//   }


   void subject::add_listener(::matter * pmatter, bool bForkWhenNotify)
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

         pcontext = __new(::subject::context);

      }

      pcontext->m_bFork = bForkWhenNotify;

      //pmatter->on_subject(this, pcontext);

   }


   void subject::erase_listener(::matter * pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.erase_key(pmatter);

   }


   void subject::set_modified()
   {

      synchronous_lock synchronouslock(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_time()))
      {

         branch_task(this);

      }

   }


   void subject::post_destroy_all()
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.erase_all();

   }


} // namespace subject



