#include "framework.h"
#include "manager.h"
#include "signal.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/action_context.h"


//::critical_section manager::s_criticalsection;
   

//::set<manager_pointer > manager::s_managerset;


//bool manager::s_bDestroyAll = false;


manager::manager()
{


}


manager::~manager()
{

}


#ifdef _DEBUG


//#error "manager::increment_reference_count is being compiled??"


long long manager::increment_reference_count()
{

   return ::property_object::increment_reference_count();

}


long long manager::decrement_reference_count()
{

   return ::property_object::decrement_reference_count();

}


long long manager::release()
{

   return ::property_object::release();

}


#endif

#if REFERENCING_DEBUGGING

CLASS_DECL_ACME void set_ThisDebug12321575();

#endif

void manager::destroy()
{

#if REFERENCING_DEBUGGING

   ::string strType = ::type(this).name();

   if (strType.contains("main_frame"))
   {

      set_ThisDebug12321575();

      output_debug_string("");

   }

#endif

   m_psignalmap.release();

   ::property_object::destroy();

}


class ::handler::signal * manager::signal(const ::atom & atom)
{

   return signal(atom, ::action_context());

}


class ::handler::signal * manager::signal(const ::atom & atom, const ::action_context& actioncontext)
{

   _synchronous_lock synchronouslock(this->synchronization());

   if (!m_psignalmap)
   {

      m_psignalmap = __allocate ::handler::signal_map();

   }

   auto & psignal = (*m_psignalmap)[atom];

   bool bNew = false;

   if (!psignal)
   {

      psignal = __allocate class ::handler::signal (atom, this);

      psignal->initialize(this);

      psignal->m_pparticle = this;

      auto psystem = system();

      psignal->m_timeSleep = psystem->get_update_poll_time(atom);

      auto pnode = psystem->node();

      if (pnode && pnode->defer_launch_on_node(psignal))
      {

      }
      else if (psignal->should_poll(psignal->poll_time()))
      {

         m_papplication->branch_procedure(psignal);

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


// void manager::add_handler(::matter * pmatter, const ::atom& atomSignal)
// {
//
//    auto psignal = signal(atomSignal);
//
//    if (::is_null(psignal))
//    {
//
//       throw ::exception(error_resource);
//
//    }
//
//    psignal->add_handler(pmatter);
//
// }
//
//
// void manager::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
// {
//
//    auto psignal = get_signal(atomSignal);
//
//    if (::is_null(psignal))
//    {
//
//       throw ::exception(error_resource);
//
//    }
//
//    psignal->add_signal_handler(signalhandler);
//
// }


//void manager::erase_signal_handler(const ::signal_handler& signalhandler)
//{
//   
//   synchronous_lock synchronouslock(this->synchronization());
//
//   if (!m_psignalmap)
//   {
//      
//      return;
//      
//   }
//   
//   for(auto & pair : *m_psignalmap)
//   {
//   
//      pair.m_element2->erase_signal_handler(signalhandler);
//   
//   }
//   
//}


//void manager::erase_signal_handlers(::particle * pparticle)
//{
//   
//   synchronous_lock synchronouslock(this->synchronization());
//
//   if (!m_psignalmap)
//   {
//      
//      return;
//      
//   }
//   
//   for(auto & pair : *m_psignalmap)
//   {
//   
//      pair.m_element2->erase_signal_handlers(pparticle);
//   
//   }
//   
//}



//   ::topic::subject_pointer manager::fork_subject(const ::atom & atom)
//   {
//
//      auto ptopic = this->topic(atom);
//
//      return ptopic;
//
//   }



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


void manager::send_signal(const ::atom & atom)
{

   send_signal(atom, {});

}

   
void manager::send_signal(const ::atom & atom, const ::action_context & actioncontext)
{

   auto psignal = signal(atom, actioncontext);

   psignal->notify();

   //handle(psignal, nullptr);

   //ptopic->id() = id_handle;

   //signal(ptopic);

   //if(ptopic->id() == id_not_modified)
   //{

   //   return;

   //}

   //ptopic->id() = id_notify;

   //ptopic->notify();

   ////::context context;

   ////on_subject(ptopic, &context);

}


void manager::on_property_changed(property * pproperty, const ::action_context & actioncontext)
{

   send_signal(pproperty->name(), actioncontext);

}

//void manager::signal(::signal * psignal)
//{
//
////      if (ptopic->id() == id_prepare)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->id() = id_process;
////
////      }
////
////      if (ptopic->id() == id_process)
////      {
////
////         //on_subject(ptopic);
////
////         ptopic->id() = id_deliver;
////
////      }
////
////      if (ptopic->id() == id_deliver)
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


void manager::erase_signal_handler(const ::signal_handler::base * pbase)
{

   _synchronous_lock synchronouslock(this->synchronization());

   //auto values = m_psignalmap->values();

   //auto & begin = values.begin();

   if (!m_psignalmap)
   {
      
      return;
      
   }

   for (auto & psignal : m_psignalmap->payloads())
   {

      while(true)
      {
      
         auto p = psignal->m_signalhandlercontext2.predicate_find([pbase](auto & iterator)
                                                                 {
            return iterator->m_element1.m_pbase == pbase;
            
         });
         
         if(!p)
         {
            
            break;
            
         }
         
         psignal->m_signalhandlercontext2.erase(p);
         
      }

   }

}


void manager::erase_handler(::object * pobject)
{

   _synchronous_lock synchronouslock(this->synchronization());

   //auto values = m_psignalmap->values();

   //auto & begin = values.begin();

   if (!m_psignalmap)
   {

      return;

   }

   for (auto psignal : m_psignalmap->payloads())
   {

      psignal->erase_handler(pobject);

   }

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

   //   //id() = atom;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}

