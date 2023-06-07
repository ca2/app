#include "framework.h"
#include "manager.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "acme/primitive/collection/set.h"


::critical_section manager::s_criticalsection;
   

::set<manager_pointer > manager::s_managerset;


bool manager::s_bDestroyAll = false;


manager::manager()
{


}


manager::~manager()
{

}


#ifdef _DEBUG


//#error "manager::increment_reference_count is being compiled??"


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

   synchronous_lock synchronouslock(this->synchronization());

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

      psignal->m_pparticle = this;

      auto psystem = acmesystem();

      psignal->m_timeSleep = psystem->get_update_poll_time(atom);

      auto pnode = psystem->node();

      if (pnode && pnode->defer_launch_on_node(psignal))
      {

      }
      else if (psignal->should_poll(psignal->poll_time()))
      {

         m_pcontext->branch_procedure(psignal);

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


void manager::__s_erase_signal_handler_from_any_source(const ::signal_handler& signalhandler)
{

   ::manager::__s_erase_signal_handler(signalhandler);

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
//      ptopic->m_actioncontext = actioncontext;
//
//      process(ptopic);
//
//   }

   
void manager::signal(const ::atom & atom, const ::action_context & actioncontext)
{

   auto psignal = get_signal(atom, actioncontext);

   psignal->notify();

   //handle(psignal, nullptr);

   //ptopic->m_atom = id_handle;

   //signal(ptopic);

   //if(ptopic->m_atom == id_not_modified)
   //{

   //   return;

   //}

   //ptopic->m_atom = id_notify;

   //ptopic->notify();

   ////::context context;

   ////on_subject(ptopic, &context);

}


void manager::on_property_changed(property * pproperty, const ::action_context & actioncontext)
{

   signal(pproperty->m_atom, actioncontext);

}

//void manager::signal(::signal * psignal)
//{
//
////      if (ptopic->m_atom == id_prepare)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->m_atom = id_process;
////
////      }
////
////      if (ptopic->m_atom == id_process)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->m_atom = id_deliver;
////
////      }
////
////      if (ptopic->m_atom == id_deliver)
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
//      ptopic->_extended_topic()->m_payload = payload;
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
//         ptopic->set_modified();
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


//   auto ptopic = create_topic(atom, pmatter);;

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


void manager::erase_signal_handler(const ::signal_handler& signalhandler)
{

   synchronous_lock synchronouslock(this->synchronization());

   //auto values = m_psignalmap->values();

   //auto & begin = values.begin();

   for (auto & psignal : m_psignalmap->payloads())
   {

      psignal->m_signalhandlercontext.erase_item(signalhandler);

   }

}


void manager::__s_erase_signal_handler(const ::signal_handler& signalhandler)
{

   critical_section_lock synchronouslock(&s_criticalsection);

   for (auto & passociation : s_managerset)
   {

      auto & pmanager = passociation.element();

      pmanager->erase_signal_handler(signalhandler);

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
//


 

   //manager::manager(::manager * pmanager, const ::atom & atom) :
   //   m_pbacking(pbacking)
   //{

   //   //m_atom = atom;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}

