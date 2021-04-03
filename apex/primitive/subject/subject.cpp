#include "framework.h"
#include "acme/platform/obj_ref_dbg.h"


namespace subject
{


   //subject::subject()
   //{

   //   subject_common_construct();

   //}


   /*subject::subject(const ::id &id, const ::action_context &actioncontext)
   {

      subject_common_construct();

      m_id = id;

      m_actioncontext = actioncontext;

   }


   subject::subject(const ::id &id, ::matter *pmatter) :
           m_pmatter(pmatter)
   {

      subject_common_construct();

      m_id = id;

   }*/


   subject::subject(::subject::manager * pmanager, const ::id & id)
   {

      subject_common_construct();

      m_pmanager = pmanager;

      m_id = id;

   }



   //subject::subject(::subject::subject * phandler, ::matter *pmatter) :
   //        m_phandler(phandler),
   //        m_pcontext(pmatter ? phandler->context(pmatter) : nullptr)
   //{

   //   m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   //   subject_common_construct();

   //   if (m_phandler)
   //   {

   //      m_id = m_phandler->m_id;

   //   }

   //}


   //subject::subject(::subject::subject * phandler, ::subject::context * pcontext, ::matter * pmatter) :
   //   m_phandler(phandler),
   //   m_pcontext(pcontext)
   //{

   //   m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   //   subject_common_construct();

   //   if (m_phandler)
   //   {

   //      m_id = m_phandler->m_id;

   //   }

   //}


   subject::~subject()
   {

      m_pmatter.release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

   }


#ifdef DEBUG


   i64 subject::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 subject::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 subject::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::property_object::release(OBJ_REF_DBG_ARGS);

   }


#endif


   ::e_status subject::step()
   {

      auto ptask = ::get_task();

      if(::subject::manager::s_bDestroyAll || !ptask->task_get_run())
      {

         return ::error_failed;

      }

      m_pmanager->process(this);

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

         m_pmanager->process(this);

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

         ::sleep(iPollMillis);

      }

      return ::success;

   }


   void subject::deliver()
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

            ::task::launch(pmatter);

         }
         else
         {

            pmatter->on_subject(this, pcontext);

         }

      }

   }


   ::subject::context * subject::context(::matter * pmatter)
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

      m_esubject = e_subject_prepare;
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


   void subject::deliver(const ::action_context & actioncontext)
   {

      for (auto & mattercontext : m_mattercontext)
      {

         auto & pmatter = mattercontext.m_element1;

         auto & pcontext = mattercontext.m_element2;

         pmatter->on_subject(this, pcontext);

      }

   }


   void subject::add(::matter * pmatter, bool bForkWhenNotify)
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

      pmatter->on_subject(this, pcontext);

   }


   void subject::remove(::matter * pmatter)
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.remove_key(pmatter);

   }


   void subject::set_modified()
   {

      synchronous_lock synchronouslock(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_time()))
      {

         ::task::launch(this);

      }

   }


   void subject::post_destroy_all()
   {

      synchronous_lock synchronouslock(mutex());

      m_mattercontext.remove_all();

   }


} // namespace subject



