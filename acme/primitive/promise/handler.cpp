#include "framework.h"


namespace promise
{


   ::critical_section handler::g_cs;
   ::set<handler_pointer > handler::g_handlerset;
   bool handler::g_bDestroyAll = false;


   //handler::handler()
   //{

   //}


   //handler::~handler()
   //{


   //}


   ::promise::subject * handler::subject(const ::id & id)
   {

      sync_lock sl(mutex());

      if (!m_pmapSubject)
      {

         m_pmapSubject = __new(::id_map<__pointer(::promise::subject)>);

      }

      auto & psubject = m_pmapSubject->operator[](id);

      if(::is_null(psubject))
      {

         psubject = __new(::promise::subject(this, id));

         start_subject_handling(id);

      }

      return psubject;

   }


   ::promise::subject_pointer handler::fork_subject(const ::id & id)
   {

      auto psubject = this->subject(id);

      return psubject;

   }


   ::promise::subject * handler::start_subject_handling(const ::id &id)
   {

      auto psubject = this->subject(id);

      psubject->defer_create_mutex();

      psubject->m_iMillisSleep = os_get_system_update_poll_time(id);

      process(psubject);

      if (psubject->should_poll(psubject->poll_millis()))
      {

         ::task::launch(psubject);

      }

      return psubject;

   }


   void handler::deliver(const ::id &id)
   {

      subject(id)->deliver();

   }


   void handler::deliver(const ::id &id, const ::action_context &actioncontext)
   {

      subject(id)->deliver(actioncontext);

   }


   void handler::process_subject(const ::id &id)
   {

      auto psubject = subject(id);

      process(psubject);

   }


   void handler::process_subject(const ::id &id, const ::action_context &actioncontext)
   {

      auto psubject = subject(id);

      psubject->m_actioncontext = actioncontext;

      process(psubject);

   }

   
   void handler::process(::promise::subject * psubject)
   {

      psubject->m_esubject = e_subject_prepare;

      on_subject(psubject);

   }


   void handler::on_subject(::promise::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         //on_subject(psubject);

      }

      if (psubject->m_esubject == e_subject_process)
      {

         //on_subject(psubject);

      }

      if (psubject->m_esubject == e_subject_deliver)
      {

         psubject->deliver();

      }

   }


   void handler::process_subject(const ::id &id, const ::payload &payload)
   {

      auto psubject = subject(id);

      psubject->m_payload = payload;

      process(psubject);

   }


   void handler::set_modified(const ::id &id)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->set_modified();

      }

   }


   void handler::delivery_for(const ::id &id, ::matter *pmatter, bool bForkWhenNotify)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->add(pmatter, bForkWhenNotify);

      }

   }


   void handler::remove_subject(const ::id &id, ::matter *pmatter)
   {

      subject(id)->remove(pmatter);

   }


   //subject_pointer handler::subject(const ::id &id, ::matter *pmatter)
   //{


   //   auto psubject = __new(::promise::subject(id, pmatter));

   //   return psubject;

   //}


//   action_pointer source::promise::subject(const ::id &id, ::matter *pmatter)
//   {
//
//      auto pupdate = update(id);
//
//      auto psubject = ::new_action(pupdate, pmatter);
//
//      return psubject;
//
//   }


   void handler::finalize()
   {

      context_object::finalize();

      m_pmapSubject.release();

   }


   void handler::remove(::matter *pmatter)
   {

      sync_lock sl(mutex());

      for (auto &pupdate : m_pmapSubject->values())
      {

         pupdate->m_mattercontext.remove_key(pmatter);

      }

   }


   void handler::__remove(::matter *pmatter)
   {

      cslock sl(&g_cs);

      for (auto &phandler : g_handlerset)
      {

         phandler->remove(pmatter);

      }

   }


   void handler::post_destroy_all()
   {

      g_bDestroyAll = true;

   }


} // namespace promise






#include "framework.h"
#include "acme/platform/static_start.h"


namespace promise
{


#undef new


 

   //handler::handler(::promise::handler * phandler, const ::id & id) :
   //   m_pbacking(pbacking)
   //{

   //   //m_id = id;

   //   m_iUpdateSerial = -1;

   //}


   //handler::~handler()
   //{

   //}


#ifdef DEBUG


   i64 handler::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 handler::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 handler::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::release(OBJ_REF_DBG_ARGS);

   }


#endif







   //void handler::process(const ::action_context & actioncontext)
   //{

   //   ::promise::subject subject(m_id, actioncontext);

   //   m_pbacking->process(&subject);

   //}


   //void handler::process()
   //{

   //   ::promise::subject subject(this);

   //   m_pbacking->process(&subject);

   //}


   //void handler::process(const ::payload & payload)
   //{

   //   ::promise::subject subject(this);

   //   subject.m_var = payload;

   //   m_pbacking->process(&subject);


   //   //for (auto& matterchange : m_matterchange)
   //   //{

   //   //   auto& pmatter = matterchange.m_element1;
   //   //
   //   //   auto& pchange = matterchange.m_element2;

   //   //   ::promise::subject action(this, pchange, pmatter);

   //   //   pchange->apply(&action);

   //   //}

   //}




} // namespace promise



