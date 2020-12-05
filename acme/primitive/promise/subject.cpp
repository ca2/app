#include "framework.h"
#include "acme/platform/obj_ref_dbg.h"


namespace promise
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


   subject::subject(::promise::handler * phandler, const ::id & id)
   {

      subject_common_construct();

      m_phandler = phandler;

      m_id = id;

   }



   //subject::subject(::promise::subject * phandler, ::matter *pmatter) :
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


   //subject::subject(::promise::subject * phandler, ::promise::context * pcontext, ::matter * pmatter) :
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

      return ::context_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 subject::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 subject::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::release(OBJ_REF_DBG_ARGS);

   }


#endif


   ::estatus subject::run()
   {

      auto ptask = ::get_task();

//      int iUpdateSerial;

      while (!::promise::handler::g_bDestroyAll && ptask->thread_get_run())
      {

         //iUpdateSerial = m_iUpdateSerial;

         m_phandler->process(this);

//         if (iUpdateSerial != m_iUpdateSerial)
//         {
//
//            deliver();
//
//         }

         //if (m_iUpdateSerial < 0)
//         {
//
//            m_pbacking->process_subject(m_id);
//
//         }

//         if (m_bModified)
//         {
//
//            m_bModified = false;
//
//            try
//            {
//
//               notify();
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }

         // fetch updated polling time
         int iPollMillis = poll_millis();

         if (!should_poll(iPollMillis))
         {

            break;

         }

         if (is_ending())
         {

            break;

         }

         //m_psource->apply_update(m_id);

         //if (m_bModified)
         //{

//            continue;

  //       }

         ::sleep(iPollMillis);

      }

      return ::success;

   }


   //void subject::process(const ::payload & payload)
   //{


   //   process();

   //}

   //void subject::process(const ::action_context & actioncontext)
   //{

   //   m_actioncontext = actioncontext;

   //   process();

   //}

   //void subject::process()
   //{


   //}


   void subject::deliver()
   {

      sync_lock sl(mutex());

      for (auto & pair : m_mattercontext)
      {

         auto & pmatter = pair.m_element1;

         auto & pcontext = pair.m_element2;

         if (!pcontext)
         {

            pcontext = __new(::promise::context);

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


   ::promise::context * subject::context(::matter * pmatter)
   {

      sync_lock sl(mutex());

      auto & pcontext = m_mattercontext[pmatter];

      if (!pcontext)
      {

         pcontext = __new(::promise::context);

      }

      return pcontext;

   }



   void subject::subject_common_construct()
   {

      m_esubject = e_subject_prepare;
      m_bRet = false;
      m_psender = nullptr;
      m_puserinteraction = nullptr;
      m_pcontrolevent = nullptr;
      //m_iUpdateSerial = 0;
      //m_bFork = false;

   }


   ::estatus subject::start_task()
   {

      return ::success_none;

   }


   void subject::reset_update(const ::id &id)
   {

      //m_phandler = ::promise::handler::fork_handler(id);

   }


   ::estatus subject::on_task()
   {

      return run();

   }


   bool subject::is_up_to_date(const ::promise::context * pcontext) const
   {

      if (::is_null(m_phandler))
      {

         return false;

      }

      if (m_iUpdateSerial < 0)
      {

         return false;

      }

      return pcontext->is_up_to_date(this);

   }


   void subject::set_up_to_date(::promise::context * pcontext)
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

      sync_lock sl(mutex());

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

         pcontext = __new(::promise::context);

      }

      pcontext->m_bFork = bForkWhenNotify;

      pmatter->on_subject(this, pcontext);



   }


   void subject::remove(::matter * pmatter)
   {

      sync_lock sl(mutex());

      m_mattercontext.remove_key(pmatter);

   }


   void subject::set_modified()
   {

      sync_lock sl(mutex());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_millis()))
      {

         ::task::launch(this);

      }

   }


   void subject::post_destroy_all()
   {

      sync_lock sl(mutex());

      m_mattercontext.remove_all();

   }


} // namespace promise



