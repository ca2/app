#include "framework.h"


critical_section manager::s_criticalsection;
   

::set<manager_pointer > manager::s_managerset;


bool manager::s_bDestroyAll = false;


manager::manager()
{


}


manager::~manager()
{

}


#ifdef _DEBUG


i64 manager::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 manager::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 manager::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif


class ::signal * manager::get_signal(const ::atom & atom, const ::action_context& actioncontext)
{

   synchronous_lock synchronouslock(mutex());

   if (!m_psignalmap)
   {

      m_psignalmap = __new(signal_map);

   }

   auto & psignal = (*m_psignalmap)[atom];

   bool bNew = false;

   if (!psignal)
   {

      psignal = __new(class ::signal(atom, this));

      psignal->initialize(this);

      auto psystem = m_psystem;

      psignal->m_durationSleep = psystem->get_update_poll_time(atom);

      auto pnode = psystem->node();

      if (pnode && pnode->defer_launch_on_node(psignal))
      {

      }
      else if (psignal->should_poll(psignal->poll_time()))
      {

         m_pcontext->branch_element(psignal);

      }

      bNew = true;

   }

   psignal->m_actioncontext = actioncontext;

   synchronouslock.unlock();

   if(bNew)
   {

      psignal->notify();

   }


//      }
//      else if (ptopic->m_bNewSubject)
//      {
//
//         ptopic->m_bNewSubject = false;
//
//      }

   return psignal;

}


//   ::topic::subject_pointer manager::fork_subject(const ::atom & atom)
//   {
//
//      auto ptopic = this->topic(atom);
//
//      return ptopic;
//
//   }


void manager::__s_erase_signal_handler_from_any_source(::matter* pmatter)
{

   ::manager::__s_erase_signal_handler(pmatter);

}


//   void manager::deliver(const ::atom &atom)
//   {
//
//      auto ptopic = topic(atom);
//
//      if(ptopic)
//      {
//
//         ptopic->deliver();
//
//      }
//
//   }


//   void manager::deliver(const ::atom &atom, const ::action_context &actioncontext)
//   {
//
//      aut
//
//      topic(atom)->deliver();
//
//   }


//   void manager::process_subject(const ::atom &atom)
//   {
//
//      auto ptopic = topic(atom);
//
//      if (ptopic->m_bNewSubject)
//      {
//
//         return;
//
//      }
//
//      process(ptopic);
//
//   }


//   void manager::process_subject(const ::atom &atom, const ::action_context &actioncontext)
//   {
//
//      auto ptopic = topic(atom);
//
//      ptopic->m_pextendedtopic->m_actioncontext = actioncontext;
//
//      process(ptopic);
//
//   }

   
void manager::signal(const ::atom & atom, const ::action_context & actioncontext)
{

   auto psignal = get_signal(atom, actioncontext);

   psignal->notify();

   //handle(psignal, nullptr);

   //ptopic->m_id = id_handle;

   //signal(ptopic);

   //if(ptopic->m_id == id_not_modified)
   //{

   //   return;

   //}

   //ptopic->m_id = id_notify;

   //ptopic->notify();

   ////::context context;

   ////on_subject(ptopic, &context);

}


void manager::on_property_changed(property * pproperty, const ::action_context & actioncontext)
{

   signal(pproperty->m_id, actioncontext);

}

//void manager::signal(::signal * psignal)
//{
//
////      if (ptopic->m_id == id_prepare)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->m_id = id_process;
////
////      }
////
////      if (ptopic->m_id == id_process)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->m_id = id_deliver;
////
////      }
////
////      if (ptopic->m_id == id_deliver)
////      {
////
////         ptopic->deliver();
////
////      }
//
//}


//   void manager::process_subject(const ::atom &atom, const ::payload & payload)
//   {
//
//      auto ptopic = topic(atom);
//
//      ptopic->m_pextendedtopic->m_payload = payload;
//
//      process(ptopic);
//
//   }


//   void manager::set_modified(const ::atom &atom)
//   {
//
//      auto ptopic = topic(atom);
//
//      if (::is_set(ptopic))
//      {
//
//         ptopic->m_pextendedtopic->set_modified();
//
//      }
//
//   }


//   void manager::delivery_for(const ::atom &atom, ::matter *pmatter, bool bForkWhenNotify)
//   {
//
//      auto ptopic = topic(atom);
//
//      if (::is_set(ptopic))
//      {
//
//         ptopic->add(pmatter, bForkWhenNotify);
//
//      }
//
//   }


//   void manager::erase_subject(const ::atom &atom, ::matter *pmatter)
//   {
//
//      topic(atom)->erase(pmatter);
//
//   }


//subject_pointer manager::topic(const ::atom &atom, ::matter *pmatter)
//{


//   auto ptopic = __new(::topic(atom, pmatter));

//   return ptopic;

//}


//   action_pointer source::topic(const ::atom &atom, ::matter *pmatter)
//   {
//
//      auto pupdate = update(atom);
//
//      auto ptopic = ::new_action(pupdate, pmatter);
//
//      return ptopic;
//
//   }


void manager::destroy_signal_handling()
{

   m_psignalmap.release();

   

   //return ::success;

}


void manager::erase_signal_handler(::matter *pmatter)
{

   synchronous_lock synchronouslock(mutex());

   for (auto & psignal : m_psignalmap->values())
   {

      psignal->m_mattercontext.erase_key(pmatter);

   }

}


void manager::__s_erase_signal_handler(::matter *pmatter)
{

   critical_section_lock synchronouslock(&s_criticalsection);

   for (auto & passociation : s_managerset)
   {

      auto & pmanager = passociation.element();

      pmanager->erase_signal_handler(pmatter);

   }

}


void manager::__s_post_destroy_signal_handling()
{

   s_bDestroyAll = true;

}



bool manager::__s_may_run_signal_handling()
{

   if (s_bDestroyAll)
   {

      return false;

   }

   if (!::task_get_run())
   {

      return false;

   }

   return true;

}

//} // namespace promise





//
//#include "framework.h"
//#include "acme/platform/static_start.h"


//namespace topic
//{
//
//
//#undef new


 

   //manager::manager(::manager * pmanager, const ::atom & atom) :
   //   m_pbacking(pbacking)
   //{

   //   //m_id = atom;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}

