#include "framework.h"
#include "manager.h"
#include "signal.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/action_context.h"


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


i64 manager::increment_reference_count()
{

   return ::property_object::increment_reference_count();

}


i64 manager::decrement_reference_count()
{

   return ::property_object::decrement_reference_count();

}


i64 manager::release()
{

   return ::property_object::release();

}


#endif

CLASS_DECL_ACME void set_ThisDebug12321575();


void manager::destroy()
{

   ::string strType = ::type(this).name();

   if (strType.contains("main_frame"))
   {

      set_ThisDebug12321575();

      output_debug_string("");

   }

   m_psignalmap.release();

   ::object::destroy();


}


class ::signal * manager::get_signal(const ::atom & atom)
{

   return get_signal(atom, ::action_context());

}


class ::signal * manager::get_signal(const ::atom & atom, const ::action_context& actioncontext)
{

   synchronous_lock synchronouslock(this->synchronization());

   if (!m_psignalmap)
   {

      m_psignalmap = __allocate< signal_map >();

   }

   auto & psignal = (*m_psignalmap)[atom];

   bool bNew = false;

   if (!psignal)
   {

      psignal = __allocate< class ::signal >(atom, this);

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


void manager::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
{

   auto psignal = get_signal(atomSignal);

   if (::is_null(psignal))
   {

      throw ::exception(error_resource);

   }

   psignal->add_signal_handler(signalhandler);

}


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


void manager::signal(const ::atom & atom)
{

   signal(atom, {});

}

   
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


void manager::erase_signal_handler(const ::signal_handler::base * pbase)
{

   synchronous_lock synchronouslock(this->synchronization());

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
      
         auto p = psignal->m_signalhandlercontext.predicate_find([pbase](auto & iterator)
                                                                 {
            return iterator->m_element1.m_pbase == pbase;
            
         });
         
         if(!p)
         {
            
            break;
            
         }
         
         psignal->m_signalhandlercontext.erase(p);
         
      }

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

   //   //m_atom = atom;

   //   m_iUpdateSerial = -1;

   //}


   //manager::~manager()
   //{

   //}

