#include "framework.h"
//#include "matter.h"
//#include "payload.h"
#include "acid/constant/id.h"
#include "acid/handler/topic.h"
#include "acid/platform/system.h"
#include "acid/exception/interface_only.h"
#include "acid/parallelization/synchronizer.h"
#include "acid/parallelization/synchronous_lock.h"


#if REFERENCING_DEBUGGING


void defer_delete(reference_count_debug* p);


#endif


matter::~matter()
{

//#if REFERENCING_DEBUGGING
//
//   ::defer_delete(m_pobjrefdbg);
//
//#endif
//
//   if (m_eobject & e_object_any_hook && m_pcontext)
//   {
//
//      system()->erase_from_any_hook(this);
//
//   }

}


//void matter::assert_ok() const
//{
//
//}
//
//
//void matter::dump(dump_context & dumpcontext) const
//{
//
//}


//void matter::initialize_matter(::matter* pmatter)
//{
//
//   system() = pmatter->system();
//
//   //return ::success;
//
//}




//void matter::on_initialize_particle()
//{
//
//   //return ::success;
//
//}


::topic_pointer create_topic(::particle * pparticleCall, const ::atom & atom);


::topic_pointer matter::create_topic(const ::atom & atom)
{

   return ::transfer(::create_topic(this, atom));

}


::extended_topic_pointer create_extended_topic(::particle * pparticleCall, const ::atom & atom);


::extended_topic_pointer matter::create_extended_topic(const ::atom & atom)
{

   return ::transfer(::create_extended_topic(this, atom));

}


void matter::operator()(::topic* ptopic, ::context* pcontext)
{

   handle(ptopic, pcontext);

}


void matter::operator()(::message::message * pmessage)
{


}


void matter::operator()(const ::payload & payload)
{

}


//// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
void matter::handle_command(const ::atom & atom)
{
//
//   //return ::success_none;
//
}

//void matter::set_object(::object* pparticle)
//{
//
//   return ::success;
//
//}


//void matter::on_finish()
//{
//
//   auto estatus = destroy();
//
//   return estatus;
//
//}


//void matter::set_finish_composites(::property_object * pcontextobjectFinish)
//void matter::destroy_composites()
//{
//
//   //return ::success;
//
//}





//void matter::set_finish(::property_object * pcontextobjectFinish)
//{
//
//   set_finish_bit();
//
//   return ::success;
//
//}




void matter::post_quit()
{

   set_finishing_flag();

}


void matter::set_finish()
{

   set_finishing_flag();

   //destroy();

   try
   {

      on_set_finish();

   }
   catch (...)
   {

   }

   //return ::success;

}


//void matter::destroy()
//{
//
//   return ::success;
//
//}


void matter::on_set_finish()
{


}


//
//::particle * matter::clone() const
//{
//
//   throw ::interface_only();
//
//   return nullptr;
//
//}


bool matter::is_ready_to_quit() const
{

   return true;

}





//void matter::erase_from_any_source()
//{
//
//}


//void matter::branch()
//{
//
////   if (has(e_object_synchronous))
////   {
////
////      return operator()();
////
////   }
////   else
////   {
//
//     auto ptask = system()->branch(__routine([this](){this->operator()();}));
//
//     if(!ptask)
//     {
//
//        return error_failed;
//
//     }
//
//     return ::success_started;
//
//   //}
//
//}





//void matter::run()
//{
//
//   return ::success;
//
//}


//void matter::on_task()
//{
//
//   return run();
//   
//}


bool matter::is_thread() const
{

   return false;

}


::thread * matter::get_thread()
{

   return nullptr;

}


bool matter::thread_is_running() const
{

   return true;

}


//::property_object * matter::_get_context_object()
//{
//
//   return nullptr;
//
//}


::task * matter::get_task()
{

   return ::get_task();

}


//::acid::system * matteracesystem()
//{
//
//   return ::is_set(m_pcontext) ? m_pcontext->m_pacesystem : nullptr;
//
//}


::acid::application* matter::_get_app()
{

   return m_pcontext ? m_pcontext->m_paceapplication : nullptr;

}


const char * matter::get_task_tag()
{

   return nullptr;

}

//::collection::index matter::task_add(::task* ptask)
//{
//
//   return -1;
//
//}


void matter::task_erase(::task* ptask)
{


}


void matter::notify_on_destroy(::property_object * pparticle)
{

}





void matter::on_sequence(const ::payload & payload)
{

}


//::task* matter::defer_branch(const ::atom& atom, const ::procedure & procedure)
//{
//
//   auto ptasktool = taskpool();
//
//   if (!ptasktool)
//   {
//
//      return nullptr;
//
//   }
//
//   return ptasktool->defer_branch(atom, routine);
//
//}



//void matter::delete_this()
//{
//
//   try
//   {
//
//      delete this;
//
//   }
//   catch (...)
//   {
//
//   }
//
//}


//void matter::__tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const
//{
//
//   system()->__tracea(elevel, pszFunction, pszFile, iLine, psz);
//
//}
//
//
//void matter::__tracef(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, i32 iLine, const ::scoped_string & scopedstrFormat, ...) const
//{
//
//   va_list valist;
//
//   va_start(valist, pszFormat);
//
//   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, valist);
//
//   va_end(valist);
//
//}


//void matter::__tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, i32 iLine, const ::scoped_string & scopedstrFormat, va_list valist) const
//{
//
//   string str;
//
//   va_list ptr1;
//
//   va_copy(ptr1, valist);
//
//   str.formatf_arguments(pszFormat, valist);
//
//   va_end(ptr1);
//
//   __tracea(elevel, pszFunction, pszFile, iLine, str);
//
//}


//void matter::__simple_tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, i32 iLine, const ::scoped_string & scopedstrFormat, va_list args) const
//{
//
//   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}
//
//
//void matter::__simple_tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, i32 iLine, const ::scoped_string & scopedstr) const
//{
//
//   __tracea(elevel, pszFunction, pszFileName, iLine, psz);
//
//}








//void matter::future(const ::atom & atom, const ::payload & payload)
//{
//
//
//}


//void matter::future(::promise::update * ptopic)
//{
//
//   if (!ptopic->is_up_to_date())
//   {
//
//      handle(ptopic, pcontext);
//
//      if(!ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, pcontext);
//
//      }
//
//      if(ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, pcontext);
//
//      }
//
//   }
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}




void matter::__task_main()
{

   //::e_status estatus = operator()();

   call_run();

   //return estatus;

}




//void matter::__thread_procedure()
//{
//
//   ::u32 u = -1;
//
//   ::e_status estatus = error_failed;
//
//   ::e_status estatusOs = error_failed;
//
//   ::e_status estatusStart = error_failed;
//
//   {
//
//      estatusOs = osthread_init();
//
//      if (::succeeded(estatusOs))
//      {
//
//         estatusStart = __thread_init();
//
//      }
//
//   }
//
//   if (::succeeded(estatusStart))
//   {
//
//      estatus = __thread_main();
//
//   }
//
//   if (::succeeded(estatusOs))
//   {
//
//      __thread_term();
//
//      osthread_term();
//
//   }
//
//#if REFERENCING_DEBUGGING
//
//   //release(REFERENCING_DEBUGGING_P_NOTE(this, nullptr));
//
//   try
//   {
//
//      if (m_countReference > 1)
//      {
//
//         __check_pending_releases(this);
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//#endif
//
//   return estatus;
//
//}


void matter::task_osinit()
{

   //return ::success;

}


void matter::__task_init()
{

   //return ::success;

}


void matter::__task_term()
{

   //return ::success;

}


void matter::task_osterm()
{

   //return ::success;

}


//void matter::to_string(const class string_exchange & str) const
//{
//
//   str = ::type(this).name();
//
//}
//


//void matter::route(::signal * psignal)
//{
//
//
//}

//
//void matter::signal(::signal * psignal)
//{
//
//
//}

//
//void matter::signal(::signal * psignal)
//{
//
//
//}


//void matter::route(::topic * ptopic, ::context * pcontext)
//{
//
//
//}


//void matter::post_process(::topic * ptopic, ::context * pcontext)
//{
//
//
//}





CLASS_DECL_ACID void __call(const ::procedure & procedure)
{

   procedure();

}




//pointer< ::sequencer < ::conversation > > matter::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
//{
//
//   auto psequence = nano()->message_box(strMessage, strTitle, emessagebox, strDetails);
//
//   psequencer->do_synchronously();
//
//   return psequencer;
//
//}





bool matter::_handle_uri(const ::string & strUri)
{

   return handle_uri(strUri);

}


bool matter::_handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
{

   return handle_call(payload, strObject, strMember, propertyset);

}


//bool matter::_handle_call(::payload & payload, const ::string & strMember, ::property_set & propertyset)
//{
//
//   return handle_call(payload, blockMember, propertyset);
//
//}


bool matter::handle_uri(const ::string & stringUri)
{

   return _handle_uri(stringUri);

}


bool matter::handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
{

   return false;

}

//
//bool matter::handle_call(::payload & payload, const ::string & strMember, ::property_set & propertyset)
//{
//
//   return false;
//
//}


//
//::topic_pointer matter::create_topic(const ::atom & atom)
//{
//
//   auto ptopic = __allocate< ::topic >(atom);
//
//   ptopic->m_pcontext = system();
//
//   return ::transfer(ptopic);
//
//}


bool matter::__get_posted_payload_synchronously(const ::function < void(const ::procedure &) > & functionPost, const ::function < ::payload(void) > & functionReturn, ::payload & payload)
{

   auto psynchronizer = __allocate< ::parallelization::synchronizer >();

   psynchronizer->set_nok();

   auto function = [functionReturn, &payload, psynchronizer]()
   {

      auto payloadReturn = functionReturn();

      synchronous_lock synchronizationlock(psynchronizer->synchronization());

      psynchronizer->m_evGoingToWrite.SetEvent();

      psynchronizer->m_evResponse.wait();

      if(!psynchronizer->has_flag(e_flag_timeout))
      {

         payload = payloadReturn;

         psynchronizer->set_ok_flag();

      }

      psynchronizer->m_evReady.SetEvent();

      ::release((::particle * &)psynchronizer.m_p);

   };

   functionPost(function);

   auto estatusWait = psynchronizer->m_evGoingToWrite.wait(functionReturn.m_timeTimeout);

   if (estatusWait.failed())
   {

      psynchronizer->set_flag(e_flag_timeout);

      psynchronizer->m_evResponse.SetEvent();

      return false;

   }

   psynchronizer->m_evResponse.SetEvent();

   psynchronizer->m_evReady.wait();

   return psynchronizer->is_ok();

}


void matter::__send_procedure(const ::function < void(const ::procedure &) > & functionPost, const ::procedure & procedure)
{

   auto psignalization = __allocate< ::parallelization::signalization >();

   auto function = [procedure, psignalization]()
   {

      try
      {

         procedure();

         psignalization->m_estatus = ::success;

      }
      catch (const ::exception& exception)
      {

         psignalization->m_estatus = exception.m_estatus;

      }
      catch(...)
      {

         psignalization->m_estatus = ::error_exception;

      }

      psignalization->m_evReady.SetEvent();

      psignalization->m_pparticleHold.release();

   };

   auto procedurePost = ::procedure(function);

   psignalization->m_pparticleHold = procedurePost.m_pbase;

   functionPost(procedurePost);

   auto estatus = psignalization->m_evReady.wait(procedure.timeout());

   if(estatus == error_wait_timeout)
   {

      procedurePost->set_timed_out_flag();

   }

}


::string matter::class_title()
{

   auto strName = demangle(typeid(*this).name());

   auto pszLastColon = strName.rear_find(':');

   if(!pszLastColon)
   {

      return strName;

   }

   return pszLastColon + 1;


}

//
//::acid::system * matteracesystem() const
//{
//
//   return ((matter*)this)->system();
//
//}



