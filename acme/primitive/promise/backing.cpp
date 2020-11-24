#include "framework.h"


namespace promise
{


   ::critical_section backing::g_cs;
   ::isomap<backing_pointer, backing_pointer> backing::g_sourcekeyset;
   bool backing::g_bDestroyAll = false;


   backing::backing()
   {

   }


   backing::~backing()
   {


   }


   ::promise::handler * backing::handler(const ::id & id)
   {

      sync_lock sl(mutex());

      if (!m_pmap)
      {

         m_pmap = __new(::id_map<__pointer(::promise::handler)>);

      }

      auto & phandler = m_pmap->operator[](id);

      if(::is_null(phandler))
      {

         phandler = __new(::promise::handler(id));

      }

      return phandler;

   }


   ::promise::handler_pointer backing::fork_handler(const ::id & id)
   {

      auto pupdate = this->handler(id);

      return pupdate;

   }


   ::promise::handler * backing::start_subject_handling(const ::id &id)
   {

      auto phandler = this->handler(id);

      if (!phandler)
      {

         phandler = __new(::promise::handler(this, id));

         phandler->defer_create_mutex();

         phandler->m_iMillisSleep = os_get_system_update_poll_time(id);

      }

      if (is_null(&phandler))
      {

         output_debug_string("teste");

      }

      return phandler;

   }


   void backing::deliver(const ::id &id)
   {

      handler(id)->deliver();

   }


   void backing::deliver(const ::id &id, const ::action_context &actioncontext)
   {

      handler(id)->deliver(actioncontext);

   }


   void backing::process_subject(const ::id &id)
   {

      handler(id)->process();

   }


   void backing::process_subject(const ::id &id, const ::action_context &actioncontext)
   {

      handler(id)->process(actioncontext);

   }


   void backing::process_subject(const ::id &id, const ::payload &payload)
   {

      handler(id)->process(payload);

   }


   void backing::set_modified(const ::id &id)
   {

      auto phandler = handler(id);

      if (::is_set(phandler))
      {

         phandler->set_modified();

      }

   }


   void backing::add_subject(const ::id &id, ::matter *pmatter, bool bForkWhenNotify)
   {

      auto pupdate = handler(id);

      if (::is_set(pupdate))
      {

         pupdate->add(pmatter, bForkWhenNotify);

      }

   }


   void backing::remove_subject(const ::id &id, ::matter *pmatter)
   {

      handler(id)->remove(pmatter);

   }


   subject_pointer backing::subject(const ::id &id, ::matter *pmatter)
   {

      auto paction = __new(::promise::subject(id, pmatter));

      return paction;

   }


//   action_pointer source::action(const ::id &id, ::matter *pmatter)
//   {
//
//      auto pupdate = update(id);
//
//      auto paction = ::new_action(pupdate, pmatter);
//
//      return paction;
//
//   }


   void backing::finalize()
   {

      context_object::finalize();

      m_pmap.release();

   }


   void backing::remove(::matter *pmatter)
   {

      sync_lock sl(mutex());

      for (auto &pupdate : m_pmap->values())
      {

         pupdate->remove(pmatter);

      }

   }


   void backing::__remove(::matter *pmatter)
   {

      cslock sl(&g_cs);

      for (auto &psource : g_sourcekeyset.values())
      {

         psource->remove(pmatter);

      }

   }


   void backing::post_destroy_all()
   {

      g_bDestroyAll = true;

   }


} // namespace promise



