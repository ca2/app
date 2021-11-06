#include "framework.h"
#include "apex/message.h"
#include "acme/update.h"
#if OBJECT_REFERENCE_COUNT_DEBUG
#include "acme/platform/obj_ref_debug_impl.h"
#endif


namespace exception
{

   
   void finish(::e_status estatusExit, const ::object* pobject)
   {


   }


}


#ifdef _DEBUG


CLASS_DECL_APEX void object_on_add_composite(const matter* pusermessage);


#endif


//object::object(::object * pobject) :
//   m_pmeta(nullptr)
//{
//
//   set_layer(0, this);
//
//   initialize(pobject);
//
//}
//

object::~object()
{

   if (m_pmeta)
   {

      ::acme::del(m_pmeta);

   }

}


i64 object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = m_countReference++;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = m_countReference--;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 object::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


void object::create_object_meta()
{

   if (m_pmeta)
   {

      return;

   }

   m_pmeta = new object_meta();

}


void object::to_string(const class string_exchange & str) const
{

   str = __type_name(this) + " (0x" + ::hex::lower_from((uptr)this) + ")";

}


::e_status object::add_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   synchronous_lock synchronouslock(mutex());

   m_pcompositea.defer_create_new();

   if (m_pcompositea->add_unique(pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS))
   {

#ifdef _DEBUG

      object_on_add_composite(pmatter);

#endif

   }

   return ::success;

}


::e_status object::add_reference(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   synchronous_lock synchronouslock(mutex());

   m_preferencea.defer_create_new();

   m_preferencea->add_unique(pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   if (m_preferencea->get_upper_bound() == 8)
   {

      if (__type_name(this).contains("application"))
      {

         string strMessage = "what is this? : " +string( m_preferencea->last()__type_name());
         output_debug_string(strMessage);
      }

   }

   return ::success;

}


::e_status object::release_composite2(::matter * pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   synchronous_lock synchronouslock(mutex());

   if (m_pcompositea)
   {

      if (m_pcompositea->erase(pmatter))
      {

         return ::success;

      }

   }

   return ::error_failed;

}


::e_status object::finalize_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   synchronous_lock synchronouslock(mutex());

   if (m_pcompositea)
   {

      if(m_pcompositea->contains(pmatter))
      {

         synchronouslock.unlock();

         pmatter->destroy();

         synchronouslock.lock();

         if (m_pcompositea)
         {

            m_pcompositea->erase(pmatter);

         }

         return ::success;

      }

   }

   return ::error_failed;

}


::e_status object::release_reference(::matter* pmatter  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   synchronous_lock synchronouslock(mutex());

   if (m_preferencea)
   {

      if (m_preferencea->erase(pmatter) > 0)
      {

         return ::success;

      }

   }

   return ::error_failed;

}


//::user::primitive* object::get_user_interaction_host()
//{
//
//   if (m_psession.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return __user_primitive(m_psession->m_puserinteractionHost);
//
//}


//::user::interaction * object::get_host_window()
//{
//
//   if (m_psession.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return __user_interaction(m_psession->m_puserinteractionHost);
//
//}


void object::dev_log(string strMessage) const
{

   FORMATTED_TRACE("%s", strMessage.c_str());

#ifdef __DEBUG

   if (get_application())
   {

      get_application()->post_critical_error_message(strMessage);

   }

#endif //__DEBUG

}


array < ::routine >* object::routinea(const ::id & id)
{

   if (m_pmeta)
   {

      auto p = m_pmeta->m_mapRoutine.plookup(id);

      if (p)
      {

         return &p->element2();

      }

   }

   return nullptr;

}


//array < ::future >* object::processa(const ::id & idProcess)
//{
//
//   if (m_pmeta)
//   {
//
//      auto p = m_pmeta->m_mapProcess.plookup(idProcess);
//
//      if (p)
//      {
//
//         return &p->element2();
//
//      }
//
//   }
//
//   return nullptr;
//
//}


void object::call_routine(const ::id & id)
{

   auto proutinea = routinea(id);

   if(proutinea)
   {

      proutinea->predicate_each([](auto& procedure) { procedure(); });

   }

}


//void object::send_payload(const ::id & idProcess, const ::payload & payload)
//{
//
//   auto pprocessa = processa(idProcess);
//
//   if(pprocessa)
//   {
//
//      pprocessa->predicate_each([&payload](auto & process) { process(payload); });
//
//   }
//
//}
//

void object::add_routine(const ::id & id, const ::routine & routine)
{

   get_meta()->m_mapRoutine[id].add(routine);

}


//void object::add_process(const ::id & id, const ::future & process)
//{
//
//   get_meta()->m_mapProcess[id].add(process);
//
//}


void object::add_each_routine_from(const ::id &id, ::object* pobjectSource)
{

   if (pobjectSource)
   {

      auto proutinea = pobjectSource->routinea(id);

      if (proutinea)
      {

         get_meta()->m_mapRoutine[id].add(*proutinea);

      }

   }

}


//void object::add_each_process_from(const ::id & id, ::object * pobjectSource)
//{
//
//   if (pobjectSource)
//   {
//
//      auto pprocessa = pobjectSource->processa(id);
//
//      if (pprocessa)
//      {
//
//         get_meta()->m_mapProcess[id].add(*pprocessa);
//
//      }
//
//   }
//
//}

context& object::__context(const ::payload & payload)
{

   if (payload.has_property("value"))
   {

      auto pcontext = payload["context"].cast < context >();

      if (pcontext)
      {

         return *pcontext;

      }

   }

   return *get_context();

}


::payload object::__context_value(const ::payload & payload)
{

   if (payload.has_property("context") && payload.has_property("value"))
   {

      return payload["value"];

   }
   else
   {

      return payload;

   }

}


void object::set_topic_text(const ::string & strTopicText)
{

   get_meta()->m_strTopicText = strTopicText;

}


::e_status object::initialize(::object * pobject)
{

   auto estatus = ::manager::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


string object::get_tag() const
{

   return "";

}


bool object::is_thread() const
{

   return false;

}


bool object::task_get_run() const
{

   return ::task_get_run();

}


bool object::is_running() const
{

   return false;

}


void object::child_post_quit(const char * pszTag)
{

   try
   {

      auto pmatter = running(pszTag);

      if (pmatter.is_null())
      {

         return;

      }

      pmatter->destroy();

   }
   catch (...)
   {

   }

}


void object::child_post_quit_and_wait(const char * pszTag, const duration & duration)
{

   try
   {

      auto pmatter = running(pszTag);

      if (pmatter.is_null())
      {

         return;

      }

      pmatter->destroy();

      string strTag(pszTag);

      predicate_Sleep(duration,
                 [this, strTag]()
      {

         return running(strTag).is_set();

      });

   }
   catch (...)
   {

   }

}

void object::defer_update_object_id()
{

   if(m_id.is_empty())
   {

      m_id = calc_default_object_id();

   }

}





::id object::calc_default_object_id() const
{

   string strType = __type_name(this);

   ::str::begins_eat_ci(strType, "class ");

   return strType;

}



::e_status object::enable_application_events(bool bEnable)
{

   if(::is_null(get_application()))
   {

      return false;

   }

   if(!get_application()->enable_application_events(this, bEnable))
   {

      return false;

   }

   return true;

}


::e_status     object::request_file(const ::payload & payloadFile)
{

   return request_file(payloadFile, e_type_new);

}


::e_status     object::request_file(const ::payload& payloadFile,::payload varQuery)
{

   auto pcommandline = __create_new< command_line >();

   pcommandline->m_varFile = payloadFile;

   pcommandline->m_varQuery = varQuery;

   return request({pcommandline});

}


::e_status     object::request(arguments arguments)
{

   __pointer(::create) pcreate;

   auto estatus = __construct_new(pcreate);

   if (!estatus)
   {

      return estatus;

   }

   estatus = pcreate->initialize_create(arguments);

   if (!estatus)
   {

      return estatus;

   }

   return do_request(pcreate);

}


::e_status     object::do_request(::create * pcreate)
{

   on_request(pcreate);

   return pcreate->m_estatus;

}


//::e_status object::message_box(const ::payload & payload)
//{
//
//   __pointer(::user::primitive) pinteraction = this;
//
//   if (pinteraction)
//   {
//
//      return pinteraction->message_box(payload);
//
//   }
//
//   if (get_application())
//   {
//
//      return get_application()->message_box(payload);
//
//   }
//
//   return ::os_message_box(payload);
//
//}


::e_status     object::call_request(::create * pcreate)
{

   on_request(pcreate);

   return ::success;

}


//::user::document* object::open_new_document(::application* pappOnBehalfOf)
//{
//
//   return open_document_file(pappOnBehalfOf, __visible(true));
//
//}


void object::on_request(::create* pcreateParam)
{

   __pointer(::create) pcreate(pcreateParam);
   
   if (!pcreate)
   {

      auto estatus = __construct(pcreate);

      if (!estatus)
      {

         __throw(estatus);

      }

      estatus = pcreate->initialize_create(get_application()->m_strAppId, ::e_type_empty, true);

      if (!estatus)
      {

         __throw(estatus);

      }

   }

   do_request(pcreate);

}


void object::destruct()
{



}


void object::system(const char * pszProjectName)
{

   __UNREFERENCED_PARAMETER(pszProjectName);

}


::e_status     object::run()
{

   return ::success;

}


::e_status object::operator()()
{

   return ::object::operator()();

}


void object::on_finalize()
{

}


::e_status object::destroy()
{

   //if (m_pmeta)
   //{

   //   m_pmeta->destroy(this);

   //}

   manager::destroy();

#if OBJECT_TYPE_COUNTER

   if (m_eobject.is(e_object_object_type_counter))
   {

      m_eobject -= e_object_object_type_counter;

      OBJECT_TYPE_COUNTER_DECREMENT;

   }

#endif

   m_pcontext.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_pthread.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_papplication.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   m_psession.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   //m_psystemContext.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   on_finalize();

   if(string(m_id).contains("::rx"))
   {

      output_debug_string("::rx destroy");

   }

   if(string(m_id).contains("::interprocess_intercommunication"))
   {

      output_debug_string("::interprocess_intercommunication destroy");

   }

   release_references();

}


void object::on_finish()
{

   manager::on_finish();

   destroy();

//   synchronous_lock synchronouslock(mutex());

   //if (m_pcompositea)
   //{

   //   for (auto & pcomposite : *m_pcompositea)
   //   {

   //      if (pcomposite)
   //      {

   //         auto pobject = pcomposite->_get_context_object();

   //         if (pobject && pobject->m_pnotifya)
   //         {

   //            synchronouslock.unlock();

   //            pobject->m_pnotifya->erase(this);

   //            synchronouslock.lock();

   //         }

   //      }

   //   }

   //   //m_ptaska.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   //}

}


// please refer to object::finish verses/documentation
void object::delete_this()
{

   destroy();

   object::delete_this();

}


string object::lstr(const ::id & id, string strDefault)
{

   return get_application()->lstr(id,strDefault);

}


void object::copy_from(const object & o)
{

   m_pthread = o.m_pthread;

   m_papplication = o.m_papplication;

   m_psession = o.m_psession;

   m_psystem = o.m_psystem;

   if (!o.m_ppropertyset)
   {

      m_ppropertyset.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   }
   else
   {

      m_ppropertyset = __new(property_set(*o.m_ppropertyset));

   }

}


::e_status object::set_finish_composites(::property_object * pcontextobjectFinish)
{

   ::e_status estatus = ::success;

   synchronous_lock synchronouslock(mutex());

   string strTypeName = __type_name(this);

   if (m_pcompositea)
   {

   composite_set_finish:

      ::count countComposite = m_pcompositea->get_count();

      for (::index iComposite = 0; iComposite < countComposite; iComposite++)
      {

         auto pcomposite = m_pcompositea->element_at(iComposite);

         if (!pcomposite || pcomposite->m_bSetFinish)
         {

            continue;

         }

         string strCompositeType = __type_name(pcomposite);

         if (strTypeName.contains("session"))
         {

            if (strCompositeType.contains("application"))
            {

               output_debug_string("application composite finish");

            }

         }
         else if (strTypeName.contains("application"))
         {

            if (strCompositeType.contains("user::thread"))
            {

               output_debug_string("user::thread composite finish");

            }
            else if (strCompositeType.contains("main_frame"))
            {

               output_debug_string("main_frame thread composite finish");

            }
         }

         synchronouslock.unlock();

         auto estatusComposite = pcomposite->finish(pcontextobjectFinish);

         synchronouslock.lock();

         if(estatusComposite == ::error_pending.succeeded())
         {

            if (strTypeName.contains_ci("application"))
            {

               output_debug_string("pending at application");

            }

            else if (strTypeName.contains_ci("app_app::window"))
            {

               output_debug_string("pending at app_window");

            }

            //auto pobject = pcomposite->_get_context_object();

            //if (pobject)
            //{

            //   pobject->notify_array().add_unique(this);

            //}

            estatus = error_pending;

         }

         if (!m_pcompositea)
         {

            break;

         }

         if (countComposite != m_pcompositea->get_count())
         {

            goto composite_set_finish;

         }

      }

   }

   return estatus;

}


::e_status object::set_finish(::property_object * pcontextobjectFinish)
{

   __pointer(::object) pobjectHold = this;

   m_bFinishing = true;

   auto estatus = set_finish_composites(pcontextobjectFinish);

   if (estatus == error_pending)
   {

      if (::is_set(pcontextobjectFinish))
      {

         notify_array().add_unique(pcontextobjectFinish);

      }

      return estatus;

   }

   if (!finish_bit())
   {

      //

      set_finish_bit();

   }

//   if (m_bitFinishing)
//   {
//
//      string strTypeName = __type_name(this);
//
//#ifdef ANDROID
//
//      strTypeName;
//
//#endif
//
//      if (strTypeName == "user::shell")
//      {
//
//         output_debug_string("user::shell::finish");
//
//      }
//      else if (strTypeName == "apex::system")
//      {
//
//         output_debug_string("apex::system::finish");
//
//      }
//
//      if (strTypeName.contains_ci("app_app::window"))
//      {
//
//         output_debug_string("set_finish at app_window");
//
//      }
//
      //if (m_ptaska)
      //{

      //task_set_finish:

      //   ::count countTask = m_ptaska->get_count();

      //   for (::index iTask = 0; m_ptaska && iTask < countTask; iTask++)
      //   {

      //      auto & ptask = m_ptaska->element_at(iTask);

      //      synchronouslock.unlock();

      //      auto estatus = ptask->finish();

      //      if (estatus == ::error_pending)
      //      {

      //         bStillFinishingTasks = true;

      //      }

      //      synchronouslock.lock();

      //      if (countTask != m_ptaska->get_count())
      //      {

      //         goto task_set_finish;

      //      }

      //   }

      //}

      //if (bStillFinishingComposites || bStillFinishingTasks)

   //   if (estatus == ::error_pending)
   //   {

   //      if (m_pcompositea)
   //      {

   //         auto compositea = *m_pcompositea;

   //         string strWaiting;

   //         for (auto & pcomposite : compositea)
   //         {

   //            try
   //            {

   //               string strThreadType;

   //               strThreadType = __type_name(pcomposite);

   //               strWaiting += strThreadType;

   //               strWaiting += "\r\n";

   //               pcomposite->finish();

   //            }
   //            catch (...)
   //            {

   //            }

   //         }

   //         if (strWaiting.has_char())
   //         {

   //            FORMATTED_TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", __type_name(this), strWaiting.c_str());

   //         }

   //      }

   //      kick_idle();

   //   }
   //   else
   //   {


   //      string strType = __type_name(this);

   //      if (strType.contains_ci("session"))
   //      {

   //         auto bShouldRun = task_get_run();

   //         if (!bShouldRun)
   //         {

   //            output_debug_string("session_shouldn't_run?");

   //         }

   //      }
   //      else if (strType.contains_ci("application"))
   //      {

   //         auto bShouldRun = task_get_run();

   //         if (!bShouldRun)
   //         {

   //            output_debug_string("application_shouldn't_run?");

   //         }


   //      }

   //      m_bitFinishing = false;

   //   }

   //}

   return estatus;

}


void object::release_references()
{

   synchronous_lock synchronouslock(mutex());

   while(m_pcompositea && m_pcompositea->has_element())
   {

      auto & composite = m_pcompositea->last();

      m_pcompositea->erase_last();

      synchronouslock.unlock();

      try
      {

         finalize_composite(composite);

      }
      catch (...)
      {

      }

      synchronouslock.lock();

   }

   if (m_pcompositea)
   {

      m_pcompositea.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   }

   if (m_preferencea)
   {

      m_preferencea.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   }

}

CLASS_DECL_ACME ::mutex* get_children_mutex();


/// tells if pobject is dependant of this object or of any dependant objects
bool object::___is_reference(::matter * pmatter) const
{

   if (::is_null(pmatter))
   {

      return false;

   }

   synchronous_lock synchronouslock(get_children_mutex());

   if (!m_preferencea)
   {

      return false;

   }

   if (m_preferencea->contains(pmatter))
   {

      return true;

   }

   return true;

}


bool object::__is_composite(::matter * pmatter) const
{

   if (::is_null(pmatter))
   {

      return false;

   }

   if (!m_pcompositea)
   {

      return false;

   }

   if (!m_pcompositea->contains(pmatter))
   {

      return true;

   }

   return false;

}



bool object::__is_child_task(::task * ptask) const
{

   if (::is_null(ptask))
   {

      return false;

   }

   //if (!m_ptaska)
   //{

   //   return false;

   //}

   //if (!m_ptaska->contains(ptask))
   //{

   //   return true;

   //}

   return false;

}



// message to stop object operations and unbind relations with other objects
// object have time to do it (as any atomic operation, yes, it is "atomic" or "cpu-4-hours")
// though it is good that the object does it the most fast possible
// (as in cancellation)
// Alive Machine without feelings...
// Poetry.
// We shouldn't need to say a human to stop (reflection, empathy).
// Sometimes we cannot wait for (expectation).
// We are unpatient, yes, but if want to be saved/healed we should be good patients...
// (as in Eternal)
// Human (as once we imagined it...)

// finish (machines...)
// "ask" to close object, not cancellable

//
// ->at simple objects (from finish point_i32 of impact)...
// ->for objects that doesn't have custom finalization
// finish calls set_finish and destroy.
//
// ->for complex objects (from finish point_i32 of impact)...
// ->for objects that have custom finalization
// finish wouldn't call *destroy*,
// but only set_finish or custom set_finish.
// "Otherwise, *destroy* could release references (that could be deleted)
// and would be still used during the ideal destroy(-action)."
// So a flag/timer/message that indicates that things should be destroyed/closed/finalized
// should be enough (which triggers the full finalization that would end up calling
// the "final" destroy).
::e_status object::finish(::property_object * pcontextobjectFinish)
{

   if (!pcontextobjectFinish)
   {

      pcontextobjectFinish = this;

   }
   
   auto estatus = set_finish(pcontextobjectFinish);

   if (estatus == success)
   {

      on_finish();

   }

   return estatus;

}


string object::__get_text(string str)
{

   if(get_application() == nullptr)
   {

      return ::__get_text(str);

   }

   return get_application()->__get_text(str);

}




//#ifdef __APPLE__
//
//void object::ns_main_async(dispatch_block_t block)
//{
//
//   atomic_increment(&m_countTasksPending);
//
//   ::ns_main_async(^
//   {
//
//      block();
//
//      atomic_decrement(&m_countTasksPending);
//
//
//   });
//
//}
//
//#endif


void object::start()
{

   if (has(e_object_synchro))
   {

      operator()();

   }
   else
   {

      ::task::launch(this);

   }

}


void object::single_fork(const ::routine_array & procedurea)
{

   fork([procedurea]()
   {

      for(auto & procedure : procedurea)
      {

         try
         {

            procedure();

         }
         catch (...)
         {

         }

      }

   });

}


void object::multiple_fork(const ::routine_array & procedurea)
{

   for (auto & procedure : procedurea)
   {

      fork([procedure]()
         {

            procedure();

         });

   }

}


::e_status object::handle_exception(const ::exception & e)
{

   if(::is_exit_exception_status(e.estatus()))
   {

      __rethrow(e);

   }

   return true;

}


::e_status object::top_handle_exception(const ::exception & e)
{

   if(::is_exit_exception_status(e.estatus()))
   {

      process_exit_status(e.estatus());

      return false;

   }

   return true;

}


void object::process_exit_status(const ::e_status& estatus)
{

   if (estatus == error_exit_system)
   {

      m_psystem->finish();

   }
   else if (estatus == error_exit_session)
   {

      get_session()->finish();

   }
   else if (estatus == error_exit_application)
   {

      get_session()->finish();

   }
   else if (estatus == error_exit_application)
   {

      ::get_task()->finish();

   }

}


::e_status object::process_exception(const ::exception & e)
{

   if (e.m_bHandled)
   {

      if (!e.m_bContinue)
      {

         return false;

      }

   }

   return true;

}


//::index object::task_add(::task * ptask)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   return get_meta()->task_add(this, ptask);
//
//}


void object::task_erase(::task* ptask)
{

   //synchronous_lock synchronouslock(mutex());

   //if (m_pmeta)
   //{

   //   m_pmeta->task_erase(this, ptask);

   //}


   //void object::task_erase(::task * ptask)
   //{

      try
      {

         string strThreadThis = __type_name(this);

         string strThreadChild = __type_name(ptask);

         synchronous_lock synchronouslock(mutex());

         if (::is_null(ptask))
         {

            __throw(error_invalid_argument);

         }

         synchronous_lock slChild(ptask->mutex());

         if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
         {

            __throw(error_invalid_argument, "thread is no parent-child releationship between the threads");

         }

         ptask->m_pobjectParent.release();

         //auto ptaska = _task_array();

         //if (ptaska)
         //{

            m_pcompositea->erase(ptask);

         //}

         //if (finish_bit() && (!m_ptaska || ptaska->is_empty()))
         if(finish_bit())
         {

            if (strThreadThis == "veriwell_keyboard::application")
            {

               output_debug_string("veriwell_keyboard::application");

            }

            finish(this);

         }
         //else
         //{

         //   kick_idle();

         //}

      }
      catch (...)
      {


      }

   //}

}

// returns false if something like "should exit thread/application/session/system"
// returns true normally.
::e_status object::sleep(const ::duration& duration)
{

   auto ptask = ::get_task();

   try
   {

      if (::is_set(ptask))
      {


         __pointer(manual_reset_event) spev;

         {

            synchronous_lock synchronouslock(ptask->mutex());

            if (ptask->m_pevSleep.is_null())
            {

               ptask->m_pevSleep = __new(manual_reset_event());

               ptask->m_pevSleep->ResetEvent();

            }

            spev = ptask->m_pevSleep;

         }

         if (m_psystem && m_psystem->finish_bit())
         {

            return error_exit_system;

         }

         if (m_psession && m_psession->finish_bit())
         {

            return error_exit_session;

         }

         if (m_papplication && m_papplication->finish_bit())
         {

            return error_exit_application;

         }

         if (spev.is_set())
         {

            ptask->m_pevSleep->wait(duration);

            return ::task_get_run();

         }

      }

   }
   catch (...)
   {

   }

   auto iTenths = duration / ::duration(100_ms);

   auto millisRemaining = duration % ::duration(100_ms);

   while (iTenths > 0)
   {

      if (m_psystem && m_psystem->finish_bit())
      {

         return error_exit_system;

      }

      if (m_psession && m_psession->finish_bit())
      {

         return error_exit_session;

      }

      if (m_papplication && m_papplication->finish_bit())
      {

         return error_exit_application;

      }


      iTenths--;

      sleep(100_ms);

   }

   sleep(millisRemaining);

   return ::success;

}



//void object::task_erase_all()
//{
//
//   /*synchronous_lock synchronouslock(mutex());
//
//   if (m_pmeta)
//   {
//
//      m_pmeta->task_erase_all(this);
//
//   }*/
//
//}

//::task_array * object::task_array_get()
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (!m_pmeta)
//   {
//
//      return nullptr;
//
//   }
//
//   return &m_pmeta->m_taska;
//
//}


//const ::task_array* object::task_array_get() const
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (!m_pmeta)
//   {
//
//      return nullptr;
//
//   }
//
//   return &m_pmeta->m_taska;
//
//}


//bool object::task_is_empty() const
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   auto pthreada = task_array_get();
//
//   if (!pthreada)
//   {
//
//      return true;
//
//   }
//
//   return pthreada->isEmpty();
//
//}


//void object::task_on_term(::task * ptask)
//{
//
//   if (finish_bit())
//   {
//
//      finish();
//
//   }
//
//}


//__pointer(thread) object::start(
//   ::matter* pmatter,
//   ::enum_priority epriority = e_priority_normal,
//   u32 nStackSize = 0,
//   u32 dwCreateFlags = 0)
//{
//
//   auto pthread = __create_new< ::thread >();
//
//   ::task::start(pthread);
//
//   return pthread;
//
//}



void object::message_receiver_destruct()
{

}


void object::_001OnUpdate(::message::message * pmessage)
{

   ::subject subject(this, (::iptr)pmessage->m_wparam);

   subject.m_payload = (::matter*) (::iptr) pmessage->m_lparam;

   process(&subject);

}



//void receiver::install_message_routing(::channel * pchannel)
void object::install_message_routing(::channel * pchannel)
{

   pchannel->add_handler(e_message_system_update, this, &::object::_001OnUpdate);

}


__pointer(::matter) object::running(const char * pszTag) const
{

   if (m_pcompositea)
   {

      auto pobject = ::parallelization::array::is_running(*m_pcompositea, pszTag);

      if (pobject)
      {

         return pobject;


      }

   }

   if (m_preferencea)
   {

      auto pobject = ::parallelization::array::is_running(*m_preferencea, pszTag);

      if (pobject)
      {

         return pobject;

      }

   }

   return nullptr;

}


//::e_status object::add_update_notification(const ::id & id, bool bCreate)
//{
//
//   auto pproperty = fetch_property(id, bCreate);
//
//   if (!pproperty)
//   {
//
//      return ::error_failed;
//
//   }
//
//   return add_update_notification(pproperty);
//
//}


//::e_status object::add_update_notification(const ::id & id, ::object * pobject)
//{
//
//   if (::is_null(pobject))
//   {
//
//      return ::error_failed;
//
//   }
//
//   if (!pobject->m_ppropertyset)
//   {
//
//      return ::error_failed;
//
//   }
//
//   auto pproperty = pobject->m_ppropertyset->find(id);
//
//   if (!pproperty)
//   {
//
//      return ::error_failed;
//
//   }
//
//   return add_update_notification(pproperty);
//
//}




::object * object::parent_property_set_holder() const
{

   return get_application();

}

//__pointer(::handle::ini) object::appini()
//{
//
//   return __new(::handle::ini(         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->localconfig()));
//
//}


::file_transport object::get_file(const ::payload & payloadFile, const ::file::e_open & eopen)
{

   return pcontext->m_papexcontext->file().get_file(payloadFile, eopen);

}










struct context_object_test_struct :
   virtual public object
{

   context_object_test_struct(::matter * p) 
   {


   }

   virtual ~context_object_test_struct()
   {

   }

   byte m_ucha[1024];

};

void debug_context_object(::object * pobject)
{

   auto p1 = __new(struct context_object_test_struct(pobject));

   auto p2 = __new(struct context_object_test_struct(pobject));

   p2 = p1;

}


CLASS_DECL_APEX void object_on_add_composite(const matter * pusermessage)
{

   string strType = __type_name(pusermessage);

   if (strType.contains_ci("user::thread"))
   {

      //debug_break();

   }

}


bool __no_continue(::e_status estatus)
{

   return false;

}


::e_status call_sync(const ::routine_array & methoda)
{

   try
   {

      for (auto & method : methoda)
      {

         try
         {

            auto estatus = method();

            if (__no_continue(estatus))
            {

               return estatus;

            }

         }
         catch(const ::exception & e)
         {

            if(__no_continue(e.m_estatus))
            {

               return e.m_estatus;

            }

         }
         catch (...)
         {

            //break;

         }

      }
   }
   catch (...)
   {

   }

   return ::success;

}








string object::get_text(const ::payload & payload, const ::id& id)
{

   if (payload.has_property(id) && payload[id].has_char())
   {

      return payload[id];

   }

   string str = pcontext->m_papexcontext->file().as_string(payload);

   if (str.has_char())
   {

      return str;

   }

   auto strExtension = payload.get_file_path().extension();

   if (strExtension == __string(id))
   {

      return "";

   }

   return payload.get_string();

}


__pointer(::extended::future < ::conversation >) object::message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox)
{

   //auto edialogresult =

   auto psystem = get_system()->m_papexsystem;
 
   auto presult = psystem->_message_box(this, pszMessage, pszTitle, emessagebox);

   //auto psession = get_session();

   ////future.m_id = DIALOG_RESULT_PROCESS;

   //if (::is_set(psession))
   //{

   //   //auto puserex = psession->userex();

   //   //if (::is_set(puserex))
   //   //{

   //   //   estatus = puserex->ui_message_box(this, puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //   //}

   //}

   //if (!estatus)
   //{

   //   string strMessage(pszMessage);

   //   string strTitle(pszTitle);

   //   if(strTitle.is_empty())
   //   {

   //      auto papp = get_application();

   //      if(papp)
   //      {

   //         strTitle = papp->get_app_user_friendly_task_bar_name();

   //      }

   //   }

   //   estatus = ::os_message_box(strMessage, strTitle, emessagebox, process);

   //}

   //return estatus;

   //return edialogresult;

   return presult;

}


//::e_status object::message_box_timeout(const char* pszMessage, const char* pszTitle, const ::duration& durationTimeout, const ::e_message_box & emessagebox, const ::future & process)
//{
//
//   ::e_status estatus = error_failed;
//
//   //if (::is_null(get_session()) || ::is_null(get_session()->userex()))
//   //{
//
//   //   estatus = get_session()->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);
//
//   //}
//
//   if (!estatus)
//   {
//
////      estatus = ::os_message_box(pszMessage, pszTitle, emessagebox, process);
//
//   }
//
//   return estatus;
//
//}


#ifdef _DEBUG


void object::set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   m_pcontext.reset(pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


void object::set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   m_pthread.reset(pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


void object::set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   m_papplication.reset(pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


void object::set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   m_psession.reset(psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


//void object::set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   m_psystemContext.reset(psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


#endif


matter* object::get_taskpool_container()
{

   return m_pthread;

}




