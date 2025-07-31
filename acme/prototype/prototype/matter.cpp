#include "framework.h"
//#include "matter.h"
//#include "payload.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/system.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronizer.h"
#include "acme/parallelization/synchronous_lock.h"


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
//   if (m_eobject & e_object_any_hook && m_papplication)
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




void matter::operator()(::topic * ptopic, ::handler_context * phandlercontext)
{

   ::particle::operator ()(ptopic, phandlercontext);

}


void matter::operator()(::message::message * pmessage)
{


}


// void matter::operator()(const ::payload & payload)
// {
//
// }


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


void matter::destroy()
{

   ::particle::destroy();

}


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


//::platform::system * matteracmesystem()
//{
//
//   return ::is_set(m_papplication) ? m_papplication->m_psystem : nullptr;
//
//}


::platform::application* matter::_get_app()
{

   return m_papplication;

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





//void matter::on_sequence(const ::payload & payload)
//{
//
//}


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
//void matter::__tracef(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, ...) const
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


//void matter::__tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list valist) const
//{
//
//   string str;
//
//   va_list ptr1;
//
//   va_copy(ptr1, valist);
//
//   str.formatf_arguments(scopedstrFormat, valist);
//
//   va_end(ptr1);
//
//   __tracea(elevel, pszFunction, pszFile, iLine, str);
//
//}


//void matter::__simple_tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args) const
//{
//
//   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}
//
//
//void matter::__simple_tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, int iLine, const ::scoped_string & scopedstr) const
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
//      handle(ptopic, phandlercontext);
//
//      if(!ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, phandlercontext);
//
//      }
//
//      if(ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, phandlercontext);
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




//void matter::__task_main()
//{
//
//   //::e_status estatus = operator()();
//
//   call();
//
//   //return estatus;
//
//}




//void matter::__thread_procedure()
//{
//
//   unsigned int u = -1;
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


// void matter::task_osinit()
// {


// }


// void matter::__task_init()
// {

//    //return ::success;

// }


// void matter::__task_term()
// {

//    //return ::success;

// }


// void matter::task_osterm()
// {

//    //return ::success;

// }


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


//void matter::route(::topic * ptopic, ::handler_context * phandlercontext)
//{
//
//
//}


//void matter::post_process(::topic * ptopic, ::handler_context * phandlercontext)
//{
//
//
//}





CLASS_DECL_ACME void __call(const ::procedure & procedure)
{

   procedure();

}




//::pointer < ::subparticle > matter::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
//{
//
//   auto psequence = nano()->message_box(strMessage, strTitle, emessagebox, strDetails);
//
//   pmessagebox->sync();
//
//   return psequencer;
//
//}





bool matter::_handle_uri(const ::scoped_string & scopedstrUri)
{

   return handle_uri(strUri);

}


bool matter::_handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset)
{

   return handle_call(payload, strObject, strMember, propertyset);

}


//bool matter::_handle_call(::payload & payload, const ::scoped_string & scopedstrMember, ::property_set & propertyset)
//{
//
//   return handle_call(payload, blockMember, propertyset);
//
//}


bool matter::handle_uri(const ::scoped_string & scopedstringUri)
{

   return _handle_uri(stringUri);

}


bool matter::handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset)
{

   return false;

}

//
//bool matter::handle_call(::payload & payload, const ::scoped_string & scopedstrMember, ::property_set & propertyset)
//{
//
//   return false;
//
//}


//
//::topic_pointer matter::create_topic(const ::atom & atom)
//{
//
//   auto ptopic = __allocate ::topic(atom);
//
//   ptopic->m_papplication = system();
//
//   return ::transfer(ptopic);
//
//}


bool matter::__get_posted_payload_synchronously(const ::function < void(const ::procedure &) > & functionPost, const ::function < ::payload(void) > & functionReturn, ::payload & payload)
{

   auto psynchronizer = __allocate ::parallelization::synchronizer();

   psynchronizer->set_nok();

   auto function = [functionReturn, &payload, psynchronizer]()
   {

      auto payloadReturn = functionReturn();

      synchronous_lock synchronizationlock(psynchronizer->synchronization());

      psynchronizer->m_happeningGoingToWrite.set_happening();

      psynchronizer->m_happeningResponse.wait();

      if(!psynchronizer->has_flag(e_flag_timeout))
      {

         payload = payloadReturn;

         psynchronizer->set_ok_flag();

      }

      psynchronizer->m_happeningReady.set_happening();

      ::release((::particle * &)psynchronizer.m_p);

   };

   functionPost(function);

   auto estatusWait = psynchronizer->m_happeningGoingToWrite.wait(functionReturn.timeout());

   if (estatusWait.failed())
   {

      psynchronizer->set_flag(e_flag_timeout);

      psynchronizer->m_happeningResponse.set_happening();

      return false;

   }

   psynchronizer->m_happeningResponse.set_happening();

   psynchronizer->m_happeningReady.wait();

   return psynchronizer->is_ok();

}


void matter::__send_procedure(const ::function < void(const ::procedure &) > & functionPost, const ::procedure & procedureParam)
{

   auto psignalization = __allocate ::parallelization::signalization();

   auto procedure = procedureParam;

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

      psignalization->m_happeningReady.set_happening();

      psignalization->m_pparticleHold.release();

   };

   auto procedurePost = ::procedure(function);

   psignalization->m_pparticleHold = procedurePost.m_pbase;

   functionPost(procedurePost);

   //auto estatus = psignalization->m_happeningReady.wait(procedure.timeout());

   auto estatus = psignalization->m_happeningReady.wait(6.3_minutes);

   if(estatus == error_wait_timeout)
   {

      //procedurePost->set_timed_out_flag();
      throw ::exception(error_wait_timeout);

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
//::platform::system * matteracmesystem() const
//{
//
//   return ((matter*)this)->system();
//
//}


long long g_iFunctionDebuggingSerial = 0;


CLASS_DECL_ACME long long function_debugging_serial()
{

   g_iFunctionDebuggingSerial++;

   return g_iFunctionDebuggingSerial;

}