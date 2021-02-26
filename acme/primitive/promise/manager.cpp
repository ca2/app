#include "framework.h"


namespace promise
{


   critical_section manager::s_criticalsection;
   ::set<manager_pointer > manager::s_managerset;
   bool manager::s_bDestroyAll = false;


   //manager::manager()
   //{

   //}


   //manager::~manager()
   //{


   //}


   ::promise::subject * manager::subject(const ::id & id)
   {

      synchronization_lock synchronizationlock(mutex());

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


   ::promise::subject_pointer manager::fork_subject(const ::id & id)
   {

      auto psubject = this->subject(id);

      return psubject;

   }


   ::promise::subject * manager::start_subject_handling(const ::id &id)
   {

      auto psubject = this->subject(id);

      psubject->defer_create_mutex();

      psubject->m_millisSleep = os_get_system_update_poll_time(id);

      process(psubject);

      auto pnode = Node;

      if(pnode && pnode->defer_launch_on_node(psubject))
      {

      }
      else if (psubject->should_poll(psubject->poll_time()))
      {

         ::task::launch(psubject);

      }

      return psubject;

   }


   void manager::deliver(const ::id &id)
   {

      auto psubject = subject(id);

      if(psubject)
      {

         psubject->deliver();

      }

   }


   void manager::deliver(const ::id &id, const ::action_context &actioncontext)
   {

      subject(id)->deliver(actioncontext);

   }


   void manager::process_subject(const ::id &id)
   {

      auto psubject = subject(id);

      process(psubject);

   }


   void manager::process_subject(const ::id &id, const ::action_context &actioncontext)
   {

      auto psubject = subject(id);

      psubject->m_actioncontext = actioncontext;

      process(psubject);

   }

   
   void manager::process(::promise::subject * psubject)
   {

      psubject->m_esubject = e_subject_prepare;

      on_subject(psubject);

   }


   void manager::on_subject(::promise::subject * psubject)
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


   void manager::process_subject(const ::id &id, const ::payload & payload)
   {

      auto psubject = subject(id);

      psubject->m_payload = payload;

      process(psubject);

   }


   void manager::set_modified(const ::id &id)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->set_modified();

      }

   }


   void manager::delivery_for(const ::id &id, ::matter *pmatter, bool bForkWhenNotify)
   {

      auto psubject = subject(id);

      if (::is_set(psubject))
      {

         psubject->add(pmatter, bForkWhenNotify);

      }

   }


   void manager::remove_subject(const ::id &id, ::matter *pmatter)
   {

      subject(id)->remove(pmatter);

   }


   //subject_pointer manager::subject(const ::id &id, ::matter *pmatter)
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


   void manager::finalize()
   {

      context_object::finalize();

      m_pmapSubject.release();

   }


   void manager::remove(::matter *pmatter)
   {

      synchronization_lock synchronizationlock(mutex());

      for (auto &pupdate : m_pmapSubject->values())
      {

         pupdate->m_mattercontext.remove_key(pmatter);

      }

   }


   void manager::__remove(::matter *pmatter)
   {

      critical_section_lock synchronizationlock(&s_criticalsection);

      for (auto & manager : s_managerset)
      {

         manager.element()->remove(pmatter);

      }

   }


   void manager::post_destroy_all()
   {

      s_bDestroyAll = true;

   }


} // namespace promise






#include "framework.h"
#include "acme/platform/static_start.h"


namespace promise
{


#undef new


 

   //manager::manager(::promise::manager * pmanager, const ::id & id) :
   //   m_pbacking(pbacking)
   //{

   //   //m_id = id;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}


#ifdef DEBUG


   i64 manager::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 manager::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 manager::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::context_object::release(OBJ_REF_DBG_ARGS);

   }


#endif







   //void manager::process(const ::action_context & actioncontext)
   //{

   //   ::promise::subject subject(m_id, actioncontext);

   //   m_pbacking->process(&subject);

   //}


   //void manager::process()
   //{

   //   ::promise::subject subject(this);

   //   m_pbacking->process(&subject);

   //}


   //void manager::process(const ::payload & payload)
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



