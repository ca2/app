#include "framework.h"
#include "apex/message.h"
#include "apex/update.h"
#if OBJ_REF_DBG
#include "acme/platform/obj_ref_dbg_impl.h"
#endif


#ifdef DEBUG


CLASS_DECL_APEX void object_on_add_composite(const matter* pbase);


#endif


object::object(::layered * pobjectContext) :
   m_pmeta(nullptr)
{

   set_layer(0, this);

   initialize(pobjectContext);

}


object::~object()
{

   if (m_pmeta)
   {

      ::acme::del(m_pmeta);

   }

}


i64 object::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 object::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_decrement(&m_countReference);

#if OBJ_REF_DBG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 object::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

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

   str = string(type_name()) + " (0x" + ::hex::lower_from((uptr)this) + ")";

}


::estatus object::add_composite(::matter* pmatter OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   sync_lock sl(mutex());

   m_pcompositea.defer_create_new();

   if (m_pcompositea->add_unique(pmatter))
   {

#ifdef DEBUG

      object_on_add_composite(pmatter);

#endif

   }

   return ::success;

}


::estatus object::add_reference(::matter* pmatter OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   sync_lock sl(mutex());

   m_preferencea.defer_create_new();

   m_preferencea->add_unique(pmatter);

   if (m_preferencea->get_upper_bound() == 8)
   {

      if (string(type_name()).contains("application"))
      {

         string strMessage = "what is this? : " +string( m_preferencea->last()->type_name());
         output_debug_string(strMessage);
      }

   }

   return ::success;

}


::estatus object::release_composite2(::matter * pmatter OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   sync_lock sl(mutex());

   if (m_pcompositea)
   {

      if (m_pcompositea->remove(pmatter))
      {

         return ::success;

      }

   }

   return ::error_failed;

}


::estatus object::finalize_composite(::matter* pmatter OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   sync_lock sl(mutex());

   if (m_pcompositea)
   {

      if(m_pcompositea->contains(pmatter))
      {

         sl.unlock();

         pmatter->finalize();

         sl.lock();

         if (m_pcompositea)
         {

            m_pcompositea->remove(pmatter);

         }

         return ::success;

      }

   }

   return ::error_failed;

}


::estatus object::release_reference(::matter* pmatter  OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   if (::is_null(pmatter))
   {

      return ::success_none;

   }

   sync_lock sl(mutex());

   if (m_preferencea)
   {

      if (m_preferencea->remove(pmatter) > 0)
      {

         return ::success;

      }

   }

   return ::error_failed;

}


::user::primitive* object::get_user_interaction_host()
{

   if (m_psessionContext.is_null())
   {

      return nullptr;

   }

   return __user_primitive(m_psessionContext->m_puiHost);

}


void object::dev_log(string strMessage) const
{

   TRACE("%s", strMessage.c_str());

#ifdef __DEBUG

   if (get_context_application())
   {

      get_context_application()->post_critical_error_message(strMessage);

   }

#endif //__DEBUG

}


array < ::procedure >* object::procedures(const ::id & id)
{

   if (m_pmeta)
   {

      auto p = m_pmeta->m_mapProcedure.plookup(id);

      if (p)
      {

         return &p->element2();

      }

   }

   return nullptr;

}


array < ::futurevar >* object::futurevars(const ::id & idFuture)
{

   if (m_pmeta)
   {

      auto p = m_pmeta->m_mapFuturevar.plookup(idFuture);

      if (p)
      {

         return &p->element2();

      }

   }

   return nullptr;

}


void object::call_procedure(const ::id & id)
{

   auto pprocedurea = procedures(id);

   if(pprocedurea)
   {

      pprocedurea->pred_each([](auto& procedure) { procedure(); });

   }

}


void object::send_futurevar(const ::id & idFuture, const ::var& var)
{

   auto pfuturevars = futurevars(idFuture);

   if(pfuturevars)
   {

      pfuturevars->pred_each([&var](auto & futurevar) { futurevar(var); });

   }

}


void object::add_procedure(const ::id & id, const ::procedure & procedure)
{

   meta()->m_mapProcedure[id].add(procedure);

}


void object::add_futurevar(const ::id & id, const ::futurevar & futurevar)
{

   meta()->m_mapFuturevar[id].add(futurevar);

}


void object::add_procedures_from(const ::id &id, ::object* pobjectSource)
{

   if (pobjectSource)
   {

      auto pprocedures = pobjectSource->procedures(id);

      if (pprocedures)
      {

         meta()->m_mapProcedure[id].add(*pprocedures);

      }

   }

}


void object::add_futurevars_from(const ::id & id, ::object * pobjectSource)
{

   if (pobjectSource)
   {

      auto pcallbacks = pobjectSource->futurevars(id);

      if (pcallbacks)
      {

         meta()->m_mapFuturevar[id].add(*pcallbacks);

      }

   }

}

context& object::__context(const var& var)
{

   if (var.has_property("value"))
   {

      auto pcontext = var["context"].cast < context >();

      if (pcontext)
      {

         return *pcontext;

      }

   }

   return *get_context();

}


var object::__context_value(const var& var)
{

   if (var.has_property("context") && var.has_property("value"))
   {

      return var["value"];

   }
   else
   {

      return var;

   }

}


void object::set_topic_text(const ::string & strTopicText)
{

   meta()->m_strTopicText = strTopicText;

}


::estatus object::initialize(::layered * pobjectContext)
{

   auto estatus = ::success;

#if OBJ_TYP_CTR

   if (!m_eobject.is(e_object_obj_typ_ctr))
   {

      m_eobject += e_object_obj_typ_ctr;

      OBJ_TYP_CTR_INC;

   }

#endif

//#if OBJ_REF_DBG
//
//   string strType = type_name();
//
//   if (strType.contains_ci("session"))
//   {
//
//      if (m_pobjrefdbg->m_iStep == 39)
//      {
//
//         output_debug_string("session");
//
//      }
//
//   }
//
//#endif

   if (!get_context_object())
   {
    
      set_context_object(pobjectContext OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   }

   if (!get_context_application())
   {

      set_context_app(::get_context_application(pobjectContext) OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   }

   if (!get_context_session())
   {

      set_context_session(::get_context_session(pobjectContext) OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   }

   //if (!get_context_system())
   //{

   //   set_context_system(::get_context_system(pobjectContext) OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   //}

   if (!get_context())
   {

      if (m_pappContext)
      {

         set_context(m_pappContext.get() OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      }
      else if (m_psessionContext)
      {

         set_context(m_psessionContext.get() OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      }
      else if (&System)
      {

         set_context(&System OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      }

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


bool object::thread_get_run() const
{

   return ::thread_get_run();

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

      pmatter->finalize();

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

      pmatter->finalize();

      pred_Sleep((int) duration.get_total_milliseconds(),
                 [=]()
      {

         return running(pszTag).is_set();

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

   string strType = type_name();

   ::str::begins_eat_ci(strType, "class ");

   return strType;

}



::estatus object::enable_application_events(bool bEnable)
{

   if(::is_null(get_context_application()))
   {

      return false;

   }

   if(!get_context_application()->enable_application_events(this, bEnable))
   {

      return false;

   }

   return true;

}


::estatus     object::request_file(const ::var & varFile)
{

   return request_file(varFile, type_new);

}


::estatus     object::request_file(const ::var& varFile,var varQuery)
{

   auto pcommandline = __create_new< command_line >();

   pcommandline->m_varFile = varFile;

   pcommandline->m_varQuery = varQuery;

   return request({pcommandline});

}


::estatus     object::request(arguments arguments)
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


::estatus     object::do_request(::create * pcreate)
{

   on_request(pcreate);

   return pcreate->m_estatus;

}


//::estatus object::message_box(const ::var& var)
//{
//
//   __pointer(::user::primitive) pinteraction = get_context_object();
//
//   if (pinteraction)
//   {
//
//      return pinteraction->message_box(var);
//
//   }
//
//   if (get_context_application())
//   {
//
//      return get_context_application()->message_box(var);
//
//   }
//
//   return ::os_message_box(var);
//
//}


::estatus     object::call_request(::create * pcreate)
{

   on_request(pcreate);

   return ::success;

}


//::user::document* object::open_new_document(::apex::application* pappOnBehalfOf)
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

         __throw(::exception::exception(estatus));

      }

      estatus = pcreate->initialize_create(Application.m_strAppId, ::type_empty, true);

      if (!estatus)
      {

         __throw(::exception::exception(estatus));

      }

   }

   do_request(pcreate);

}


void object::destruct()
{



}


void object::system(const char * pszProjectName)
{

   UNREFERENCED_PARAMETER(pszProjectName);

}


::estatus     object::run()
{

   return ::success;

}


::estatus object::operator()()
{

   return ::context_object::operator()();

}


void object::on_finalize()
{

}


void object::finalize()
{

   //if (m_pmeta)
   //{

   //   m_pmeta->finalize(this);

   //}

   source::finalize();

#if OBJ_TYP_CTR

   if (m_eobject.is(e_object_obj_typ_ctr))
   {

      m_eobject -= e_object_obj_typ_ctr;

      OBJ_TYP_CTR_DEC;

   }

#endif

   m_pcontextContext.release(OBJ_REF_DBG_THIS);

   m_pthreadContext.release(OBJ_REF_DBG_THIS);

   m_pappContext.release(OBJ_REF_DBG_THIS);

   m_psessionContext.release(OBJ_REF_DBG_THIS);

   //m_psystemContext.release(OBJ_REF_DBG_THIS);

   on_finalize();

   if(string(m_id).contains("::rx"))
   {

      output_debug_string("::rx finalize");

   }

   if(string(m_id).contains("::interprocess_intercommunication"))
   {

      output_debug_string("::interprocess_intercommunication finalize");

   }

   release_references();

}


void object::on_finish()
{

   source::on_finish();

   finalize();

//   sync_lock sl(mutex());

   //if (m_pcompositea)
   //{

   //   for (auto & pcomposite : *m_pcompositea)
   //   {

   //      if (pcomposite)
   //      {

   //         auto pcontextobject = pcomposite->_get_context_object();

   //         if (pcontextobject && pcontextobject->m_pnotifya)
   //         {

   //            sl.unlock();

   //            pcontextobject->m_pnotifya->remove(this);

   //            sl.lock();

   //         }

   //      }

   //   }

   //   //m_ptaska.release(OBJ_REF_DBG_THIS);

   //}

}


// please refer to object::finish verses/documentation
void object::delete_this()
{

   finalize();

   context_object::delete_this();

}


string object::lstr(const ::id & id, string strDefault)
{

   return get_context_application()->lstr(id,strDefault);

}


void object::copy_from(const object & o)
{

   m_pobjectContext = o.m_pobjectContext;

   m_pthreadContext = o.m_pthreadContext;

   m_pappContext = o.m_pappContext;

   set_context_session(o.m_psessionContext);

   //m_psystemContext = o.m_psystemContext;

   if (!o.m_pset)
   {

      m_pset.release(OBJ_REF_DBG_THIS);

   }
   else
   {

      m_pset = __new(property_set(*o.m_pset));

   }

}


::estatus object::set_finish_composites(::context_object * pcontextobjectFinish)
{

   ::estatus estatus = ::success;

   sync_lock sl(mutex());

   string strTypeName = type_name();

   if (m_pcompositea)
   {

   composite_set_finish:

      ::count countComposite = m_pcompositea->get_count();

      for (::index iComposite = 0; iComposite < countComposite; iComposite++)
      {

         auto pcomposite = m_pcompositea->element_at(iComposite);

         if (!pcomposite || pcomposite->m_bitSetFinish)
         {

            continue;

         }

         string strCompositeType = pcomposite->type_name();

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

         sl.unlock();

         auto estatusComposite = pcomposite->finish(pcontextobjectFinish);

         sl.lock();

         if (estatusComposite == ::error_pending)
         {

            if (strTypeName.contains_ci("application"))
            {

               output_debug_string("pending at application");

            }

            else if (strTypeName.contains_ci("app_app::window"))
            {

               output_debug_string("pending at app_window");

            }

            //auto pcontextobject = pcomposite->_get_context_object();

            //if (pcontextobject)
            //{

            //   pcontextobject->notify_array().add_unique(this);

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


::estatus object::set_finish(::context_object * pcontextobjectFinish)
{

   __pointer(::object) pobjectHold = this;

   m_bitFinishing = true;

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
//      string strTypeName = type_name();
//
//#ifdef ANDROID
//
//      demangle(strTypeName);
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

      //      sl.unlock();

      //      auto estatus = ptask->finish();

      //      if (estatus == ::error_pending)
      //      {

      //         bStillFinishingTasks = true;

      //      }

      //      sl.lock();

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

   //               strThreadType = pcomposite->type_name();

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

   //            TRACE("The thread %s is waiting for the following threads to finish:\r\n%s", type_name(), strWaiting.c_str());

   //         }

   //      }

   //      kick_idle();

   //   }
   //   else
   //   {


   //      string strType = type_name();

   //      if (strType.contains_ci("session"))
   //      {

   //         auto bShouldRun = thread_get_run();

   //         if (!bShouldRun)
   //         {

   //            output_debug_string("session_shouldn't_run?");

   //         }

   //      }
   //      else if (strType.contains_ci("application"))
   //      {

   //         auto bShouldRun = thread_get_run();

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

   sync_lock sl(mutex());

   while(m_pcompositea && m_pcompositea->has_element())
   {

      auto composite = m_pcompositea->pop();

      sl.unlock();

      try
      {

         finalize_composite(composite);

      }
      catch (...)
      {

      }

      sl.lock();

   }

   if (m_pcompositea)
   {

      m_pcompositea.release(OBJ_REF_DBG_THIS);

   }

   if (m_preferencea)
   {

      m_preferencea.release(OBJ_REF_DBG_THIS);

   }

}

CLASS_DECL_ACME mutex* get_children_mutex();


/// tells if pobject is dependant of this object or of any dependant objects
bool object::___is_reference(::matter * pmatter) const
{

   if (::is_null(pmatter))
   {

      return false;

   }

   sync_lock sl(get_children_mutex());

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
// ->at simple objects (from finish point of view)...
// ->for objects that doesn't have custom finalization
// finish calls set_finish and finalize.
//
// ->for complex objects (from finish point of view)...
// ->for objects that have custom finalization
// finish wouldn't call *finalize*,
// but only set_finish or custom set_finish.
// "Otherwise, *finalize* could release references (that could be deleted)
// and would be still used during the ideal finalize(-action)."
// So a flag/timer/message that indicates that things should be destroyed/closed/finalized
// should be enough (which triggers the full finalization that would end up calling
// the "final" finalize).
::estatus object::finish(::context_object * pcontextobjectFinish)
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

   if(get_context_application() == nullptr)
   {

      return ::__get_text(str);

   }

   return Application.__get_text(str);

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


void object::single_fork(const procedure_array & procedurea)
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


void object::multiple_fork(const procedure_array & procedurea)
{

   for (auto & procedure : procedurea)
   {

      fork([procedure]()
         {

            procedure();

         });

   }

}


::estatus object::handle_exception(::exception_pointer pe)
{

   if(pe.is < exit_exception > ())
   {

      __rethrow(pe);

   }

   return true;

}


::estatus object::top_handle_exception(::exception_pointer pe)
{

   __pointer(exit_exception) pexitexception = pe;

   if(pexitexception)
   {

      pexitexception->finish(this);

      return false;

   }

   return true;

}


::estatus object::process_exception(::exception_pointer pe)
{

   if (pe->m_bHandled)
   {

      if (!pe->m_bContinue)
      {

         return false;

      }

   }

   return true;

}


//::index object::task_add(::task * ptask)
//{
//
//   sync_lock sl(mutex());
//
//   return meta()->task_add(this, ptask);
//
//}


void object::task_remove(::task* ptask)
{

   //sync_lock sl(mutex());

   //if (m_pmeta)
   //{

   //   m_pmeta->task_remove(this, ptask);

   //}


   //void object::task_remove(::task * ptask)
   //{

      try
      {

         string strThreadThis = type_name();

         string strThreadChild = ptask->type_name();

         sync_lock sl(mutex());

         if (::is_null(ptask))
         {

            __throw(invalid_argument_exception());

         }

         sync_lock slChild(ptask->mutex());

         if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
         {

            __throw(invalid_argument_exception("thread is no parent-child releationship between the threads"));

         }

         ptask->m_pobjectParent.release();

         //auto ptaska = _task_array();

         //if (ptaska)
         //{

            m_pcompositea->remove(ptask);

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


//void object::task_remove_all()
//{
//
//   /*sync_lock sl(mutex());
//
//   if (m_pmeta)
//   {
//
//      m_pmeta->task_remove_all(this);
//
//   }*/
//
//}

//::task_array * object::task_array_get()
//{
//
//   sync_lock sl(mutex());
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
//   sync_lock sl(mutex());
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
//   sync_lock sl(mutex());
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
//   ::e_priority epriority = priority_normal,
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

  ::action action((::iptr)pmessage->m_wparam);

  action.m_var = (::matter*) (::iptr) pmessage->m_lparam;

  apply(action);

}



//void receiver::install_message_routing(::channel * pchannel)
void object::install_message_routing(::channel * pchannel)
{

   MESSAGE_LINK(e_message_system_update, pchannel, this, &::object::_001OnUpdate);

}


__pointer(::matter) object::running(const char * pszTag) const
{

   if (m_pcompositea)
   {

      auto pobject = ::multithreading::array::is_running(*m_pcompositea, pszTag);

      if (pobject)
      {

         return pobject;


      }

   }

   if (m_preferencea)
   {

      auto pobject = ::multithreading::array::is_running(*m_preferencea, pszTag);

      if (pobject)
      {

         return pobject;

      }

   }

   return nullptr;

}



::estatus object::bind_update(const ::id & id, bool bCreate)
{

   auto pproperty = fetch_property(id, bCreate);

   if (!pproperty)
   {

      return ::error_failed;

   }

   return bind_update(pproperty);

}


::estatus object::bind_update(const ::id & id, ::object * pobject)
{

   if (::is_null(pobject))
   {

      return ::error_failed;

   }

   if (!pobject->m_pset)
   {

      return ::error_failed;

   }

   auto pproperty = pobject->m_pset->find(id);

   if (!pproperty)
   {

      return ::error_failed;

   }

   return bind_update(pproperty);

}


::estatus object::bind_update(property * pproperty)
{

   ASSERT(::is_set(pproperty));

   auto pchannel = Application.m_mapNotify[pproperty->m_id];

   if (!pchannel)
   {

      pchannel = get_context_application();

   }

   if (!pchannel)
   {

      return ::error_failed;

   }

   pchannel->add_update_route(this, pproperty->m_id);

   string strTypeSource = ::str::demangle(pchannel->type_name());

   string strTypeTarget = type_name();

   INFO("property from '%s' update handling installed to '%s'", strTypeSource.c_str(), strTypeTarget.c_str());

   return ::success;

}


::object * object::parent_property_set_holder() const
{

   return get_context_application();

}

//__pointer(::handle::ini) object::appini()
//{
//
//   return __new(::handle::ini(::dir::localconfig()));
//
//}


::file_result object::get_file(const var & varFile, efileopen eopen)
{

   return Context.file().get_file(varFile, eopen);

}










struct context_object_test_struct :
   virtual public object
{

   context_object_test_struct(::layered * p) :
      ::object(p)
   {


   }

   virtual ~context_object_test_struct()
   {

   }

   byte m_ucha[1024];

};

void debug_context_object(::layered * pobjectContext)
{

   auto p1 = __new(struct context_object_test_struct(pobjectContext));

   auto p2 = __new(struct context_object_test_struct(pobjectContext));

   p2 = p1;

}


CLASS_DECL_APEX void object_on_add_composite(const matter * pbase)
{

   string strType = ::str::demangle(pbase->type_name());

   if (strType.contains_ci("user::thread"))
   {

      //debug_break();

   }

}


bool __no_continue(::estatus estatus)
{

   return false;

}


::estatus call_sync(const procedure_array & methoda)
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
         catch(::exception_pointer pe)
         {

            if(__no_continue(pe->m_estatus))
            {

               return pe->m_estatus;

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








string object::get_text(const var& var, const ::id& id)
{

   if (var.has_property(id) && var[id].has_char())
   {

      return var[id];

   }

   string str = Context.file().as_string(var);

   if (str.has_char())
   {

      return str;

   }

   auto strExtension = var.get_file_path().extension();

   if (strExtension == __str(id))
   {

      return "";

   }

   return var.get_string();

}


::estatus object::message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, const ::futurevar & futurevar)
{

   ::estatus estatus = error_failed;

   auto psession = get_context_session();

   //future.m_id = DIALOG_RESULT_FUTURE;

   if (::is_set(psession))
   {

      //auto puserex = psession->userex();

      //if (::is_set(puserex))
      //{

      //   estatus = puserex->ui_message_box(this, puiOwner, pszMessage, pszTitle, emessagebox, callback);

      //}

   }

   if (!estatus)
   {

      string strMessage(pszMessage);

      string strTitle(pszTitle);

      if(strTitle.is_empty())
      {

         auto papp = get_context_application();

         if(papp)
         {

            strTitle = papp->get_app_user_friendly_task_bar_name();

         }

      }

      estatus = ::os_message_box(strMessage, strTitle, emessagebox, futurevar);

   }

   return estatus;

}


::estatus object::message_box_timeout(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::duration& durationTimeout, ::emessagebox emessagebox, const ::futurevar & futurevar)
{

   ::estatus estatus = error_failed;

   //if (::is_null(get_context_session()) || ::is_null(get_context_session()->userex()))
   //{

   //   estatus = get_context_session()->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);

   //}

   if (!estatus)
   {

      estatus = ::os_message_box(pszMessage, pszTitle, emessagebox, futurevar);

   }

   return estatus;

}


#ifdef DEBUG


void object::set_context(::context* pcontext OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   m_pcontextContext.reset(pcontext OBJ_REF_DBG_COMMA_ARGS);

}


void object::set_context_thread(::thread* pthread OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   m_pthreadContext.reset(pthread OBJ_REF_DBG_COMMA_ARGS);

}


void object::set_context_app(::apex::application* pappContext OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   m_pappContext.reset(pappContext OBJ_REF_DBG_COMMA_ARGS);

}


void object::set_context_session(::apex::session* psessionContext OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

   m_psessionContext.reset(psessionContext OBJ_REF_DBG_COMMA_ARGS);

}


//void object::set_context_system(::apex::system* psystemContext OBJ_REF_DBG_COMMA_PARAMS_DEF)
//{
//
//   m_psystemContext.reset(psystemContext OBJ_REF_DBG_COMMA_ARGS);
//
//}


#endif


matter* object::get_taskpool_container()
{

   return get_context_thread();

}




