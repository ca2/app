#include "framework.h"
#include "acme/message.h"
#include "acme/update.h"



extern ::mutex * g_pmutexChildren;


generic::generic(::generic * pobject)
{

   m_pmeta = nullptr;

   //m_pObjectThis = nullptr;

   set_context_object(pobject);

   //__refer(m_pobjectContext, pobject);

   //__refer(m_pappContext, ::get_context_application(m_pobjectContext));

   //__refer(m_psessionContext, ::get_context_session(m_pobjectContext));

   //__refer(m_psystemContext, ::get_context_system(m_pobjectContext));

}


generic::~generic()
{

   if (m_pmeta)
   {

      ::acme::del(m_pmeta);

   }

}


i64 generic::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 generic::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_decrement(&m_countReference);

#if OBJ_REF_DBG

   if (c > 0)
   {

      dec_ref_history(p, pszObjRefDbg);

   }

#endif

   return c;

}


i64 generic::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


void generic::create_object_meta()
{

   if (m_pmeta)
   {

      return;

   }

   m_pmeta = new object_meta();

}


void generic::to_string(string & str) const
{

   str = string(type_name()) + " (0x" + ::hex::lower_from((uptr)this) + ")";

}


::estatus generic::add_composite(::generic* pobject)
{

   sync_lock sl(mutex());

   m_pcompositea.defer_create_new();

   if (m_pcompositea->add_unique(pobject))
   {

      pobject->add_ref(OBJ_REF_DBG_P_NOTE(this, debug_note()));

#ifdef DEBUG

      object_on_add_composite(pobject);

#endif

   }

   return ::success;

}


::estatus generic::add_reference(::generic* pobject)
{

   sync_lock sl(mutex());

   m_preferencea.defer_create_new();

   if (m_preferencea->add_unique(pobject))
   {

      pobject->add_ref(OBJ_REF_DBG_P_NOTE(this, debug_note()));

   }

   return ::success;

}


::estatus generic::release_composite(::generic* pobject)
{

   if (::is_null(pobject))
   {

      return ::success_none;

   }

   sync_lock sl(mutex());

   if (m_pcompositea)
   {

      if (m_pcompositea->remove(pobject) > 0)
      {

         pobject->release(OBJ_REF_DBG_THIS);

         return ::success;

      }

   }

   return ::error_failed;

}


::estatus generic::release_reference(::generic* pobject)
{

   if (::is_null(pobject))
   {

      return ::success_none;

   }

   sync_lock sl(mutex());

   if (m_preferencea)
   {

      if (m_preferencea->remove(pobject) > 0)
      {

         pobject->release(OBJ_REF_DBG_THIS);

         return ::success;

      }

   }

   return ::error_failed;

}


::user::interaction* generic::get_user_interaction_host()
{

   if (m_psessionContext.is_null())
   {

      return nullptr;

   }

   return m_psessionContext->m_puiHost;

}


void generic::dev_log(string strMessage) const
{

   TRACE("%s", strMessage.c_str());

#ifdef __DEBUG

   if (get_context_application())
   {

      get_context_application()->post_critical_error_message(strMessage);

   }

#endif //__DEBUG

}







array < ::procedure >* generic::procedures(const ::id & idProcedure)
{

   if (m_pmeta)
   {

      auto p = m_pmeta->m_proceduremap.plookup(idProcedure);

      if (p)
      {

         return &p->element2();

      }

   }

   return nullptr;

}


array < ::callback >* generic::callbacks(const ::id & idCallback)
{

   if (m_pmeta)
   {

      auto p = m_pmeta->m_callbackmap.plookup(idCallback);

      if (p)
      {

         return &p->element2();

      }

   }

   return nullptr;

}


void generic::runall(const ::id & idProcedure)
{

   auto pprocedures = procedures(idProcedure);

   if(pprocedures)
   {

      pprocedures->pred_each([](auto& f) {f.call(); });

   }

}

void generic::receive(const ::id & idCallback, const ::var& var)
{

   auto pcallbacks = callbacks(idCallback);

   if(pcallbacks)
   {

      pcallbacks->pred_each([&var](auto& f) {f.receive_response(var); });

   }

}


void generic::add(const ::procedure & procedure)
{

   meta()->m_proceduremap[procedure.m_id].add(procedure);

}


void generic::add(const ::callback & callback)
{

   meta()->m_callbackmap[callback.m_id].add(callback);

}


void generic::add_procedures_from(const ::id &idProcedure, ::generic* pobjectSource)
{

   if (pobjectSource)
   {

      auto pprocedures = pobjectSource->procedures(idProcedure);

      if (pprocedures)
      {

         meta()->m_proceduremap[idProcedure].add(*pprocedures);

      }

   }

}


void generic::add_callbacks_from(const ::id & idCallback, ::generic * pobjectSource)
{

   if (pobjectSource)
   {

      auto pcallbacks = pobjectSource->callbacks(idCallback);

      if (pcallbacks)
      {

         meta()->m_callbackmap[idCallback].add(*pcallbacks);

      }

   }

}

context& generic::__context(const var& var)
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


var generic::__context_value(const var& var)
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


void generic::set_topic_text(const ::string & strTopicText)
{

   meta()->m_strTopicText = strTopicText;

}


void generic::set_context_object(::generic* pobjectContext)
{

   ::generic::set_context_object(pobjectContext);

   set_context_app(::get_context_application(pobjectContext));

   set_context_session(::get_context_session(pobjectContext));

   set_context_system(::get_context_system(pobjectContext));

   if (m_pappContext)
   {

      set_context(m_pappContext.get());

   }
   else if (m_psessionContext)
   {

      set_context(m_psessionContext.get());

   }
   else if (m_psystemContext)
   {

      set_context(m_psystemContext.get());

   }

}




::estatus generic::initialize(::generic * pobjectContext)
{

   auto estatus = ::success;

#if OBJ_TYP_CTR

   if (!m_eobject.is(e_object_obj_typ_ctr))
   {

      m_eobject += e_object_obj_typ_ctr;

      OBJ_TYP_CTR_INC;

   }

#endif

   set_context_object(pobjectContext);

   return estatus;

}


string generic::get_tag() const
{

   return "";

}


bool generic::is_thread() const
{

   return false;

}


bool generic::thread_get_run() const
{

   return ::thread_get_run();

}


bool generic::is_running() const
{

   return false;

}


void generic::child_post_quit(const char * pszTag)
{

   try
   {

      auto pobject = running(pszTag);

      if (pobject.is_null())
      {

         return;

      }

      pobject->finalize();

   }
   catch (...)
   {

   }

}


void generic::child_post_quit_and_wait(const char * pszTag, const duration & duration)
{

   try
   {

      auto pobject = running(pszTag);

      if (pobject.is_null())
      {

         return;

      }

      pobject->finalize();

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

void generic::defer_update_object_id()
{

   if(m_id.is_empty())
   {

      m_id = calc_default_object_id();

   }

}





::id generic::calc_default_object_id() const
{

   string strType = type_name();

   ::str::begins_eat_ci(strType, "class ");

   return strType;

}



bool generic::enable_application_events(bool bEnable)
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


::estatus     generic::request_file(const ::var & varFile)
{

   return request_file(varFile, type_new);

}


::estatus     generic::request_file(const ::var& varFile,var varQuery)
{

   auto pcommandline = __new(command_line(this));

   pcommandline->m_varFile = varFile;

   pcommandline->m_varQuery = varQuery;

   return request({pcommandline});

}


::estatus     generic::request(arguments arguments)
{

   auto pcreate = __new(::create(this, arguments));

   return do_request(pcreate);

}


::estatus     generic::do_request(::create * pcreate)
{

   on_request(pcreate);

   return pcreate->m_estatus;

}


//::estatus generic::message_box(const ::var& var)
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


::estatus     generic::call_request(::create * pcreate)
{

   on_request(pcreate);

   return ::success;

}


//::user::document* generic::open_new_document(::acme::application* pappOnBehalfOf)
//{
//
//   return open_document_file(pappOnBehalfOf, __visible(true));
//
//}


void generic::on_request(::create* pcreate)
{

   __pointer(::create) cc(__new(::create(this, Application.m_strAppId, ::type_empty, true)));

   if (pcreate == nullptr)
   {

      pcreate = cc;

   }

   do_request(pcreate);

   //      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();

}


//::user::document* generic::open_document_file(::acme::application* pappOnBehalfOf)
//{
//
//   return open_document_file(pappOnBehalfOf, ::type_empty_argument);
//
//}


//::user::document* generic::open_document_file(::acme::application* pappOnBehalfOf, const var& varFile, const ::var & varOptions, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
//{
//
//   auto pcreate = __new(::create(pappOnBehalfOf, pappOnBehalfOf->m_strAppId, varFile, varOptions, puiParent, eflag, id));
//
//   do_request(pcreate);
//
//   return ::user::__document(pcreate);
//
//}


//::user::document* generic::open_document_file(::acme::application* pappOnBehalfOf, const var& varFile)
//{
//
//   return open_document_file(pappOnBehalfOf, varFile, ::type_empty_argument);
//
//}


//::user::document* generic::create_subdocument(::user::impact_data* pimpactdata)
//{
//
//   auto pdocument = open_document_file(
//      pimpactdata->m_pplaceholder->get_context_application(),
//      ::type_null,
//      __visible(true),
//      pimpactdata->m_pplaceholder);
//
//   pimpactdata->m_pdocument = pdocument;
//
//   return pdocument;
//
//}








void generic::destruct()
{



}


void generic::system(const char * pszProjectName)
{

   UNREFERENCED_PARAMETER(pszProjectName);

}


::estatus     generic::run()
{

   return ::success;

}


::estatus generic::call()
{

   return ::generic::call();

}


void generic::on_finalize()
{

}


void generic::finalize()
{

#if OBJ_TYP_CTR

   if (m_eobject.is(e_object_obj_typ_ctr))
   {

      m_eobject -= e_object_obj_typ_ctr;

      OBJ_TYP_CTR_DEC;

   }

#endif

   m_pcontextContext.release();

   m_pthreadContext.release();

   m_pappContext.release();

   set_context_session(nullptr);

   m_psystemContext.release();

   on_finalize();

   if(string(m_id).contains("::rx"))
   {

      output_debug_string("::rx finalize");

   }

   if(string(m_id).contains("::ipi"))
   {

      output_debug_string("::ipi finalize");

   }

   release_references();

}

// please refer to generic::set_finish verses/documentation
void generic::delete_this()
{

   set_finish();

   generic::delete_this();

}


sync * generic::get_mutex() const
{

   return mutex();

}


string generic::lstr(const ::id & id, string strDefault)
{

   return get_context_application()->lstr(id,strDefault);

}


void generic::copy_from(const generic & o)
{

   m_pobjectContext = o.m_pobjectContext;

   m_pthreadContext = o.m_pthreadContext;

   m_pappContext = o.m_pappContext;

   set_context_session(o.m_psessionContext);

   m_psystemContext = o.m_psystemContext;

   if (!o.m_pset)
   {

      m_pset.release();

   }
   else
   {

      m_pset = __new(property_set(*o.m_pset));

   }

}


void generic::set_finish_composites()
{

   if (m_pcompositea)
   {

      for (auto & pcomposite : *m_pcompositea)
      {

         pcomposite->set_finish();

      }

   }

}


void generic::release_references()
{

   sync_lock sl(mutex());

   if (m_pcompositea)
   {

      for (auto& p : *m_pcompositea)
      {

         try
         {

            release_composite(p);
            
         }
         catch (...)
         {

         }

      }

      m_pcompositea.release();

   }

   if (m_preferencea)
   {

      for (auto& p : *m_preferencea)
      {

         try
         {

            release_reference(p);

         }
         catch (...)
         {

         }

      }

      m_preferencea.release();

   }

}


/// tells if pobject is dependant of this generic or of any dependant objects
bool generic::___is_reference(::generic * pobject) const
{

   if (::is_null(pobject))
   {

      return false;

   }

   sync_lock sl(g_pmutexChildren);

   if (!m_preferencea)
   {

      return false;

   }

   if (m_preferencea->contains(pobject))
   {

      return true;

   }

   return true;

}


bool generic::__is_composite(::generic * pobject) const
{

   if (::is_null(pobject))
   {

      return false;

   }

   if (!m_pcompositea)
   {

      return false;

   }

   if (!m_pcompositea->contains(pobject))
   {

      return true;

   }

   return false;

}


// message to stop generic operations and unbind relations with other objects
// generic have time to do it (as any atomic operation, yes, it is "atomic" or "cpu-4-hours")
// though it is good that the generic does it the most fast possible
// (as in cancellation)
// Alive Machine without feelings...
// Poetry.
// We shouldn't need to say a human to stop (reflection, empathy).
// Sometimes we cannot wait for (expectation).
// We are unpatient, yes, but if want to be saved/healed we should be good patients...
// (as in Eternal)
// Human (as once we imagined it...)

// set_finish (machines...)
// "ask" to close generic, not cancellable

//
// ->at simple objects (from set_finish point of view)...
// ->for objects that doesn't have custom finalization
// set_finish calls set_finish_composites and finalize.
// 
// ->for complex objects (from set_finish point of view)...
// ->for objects that have custom finalization
// set_finish wouldn't call *finalize*,
// but only set_finish_composites or custom set_finish_composites.
// "Otherwise, *finalize* could release references (that could be deleted)
// and would be still used during the ideal finalize(-action)."
// So a flag/timer/message that indicates that things should be destroyed/closed/finalized
// should be enough (which triggers the full finalization that would end up calling
// the "final" finalize).
void generic::set_finish()
{

   string strTypeName = type_name();

#ifdef ANDROID

   demangle(strTypeName);

#endif

   if (strTypeName == "user::shell")
   {

      output_debug_string("user::shell::set_finish");

   }
   else if (strTypeName == "acme::system")
   {

      output_debug_string("acme::system::set_finish");

   }

   set_finish_composites();

   finalize();

}


string generic::__get_text(string str)
{

   if(get_context_application() == nullptr)
   {

      return ::__get_text(str);

   }

   return Application.__get_text(str);

}


void generic::start_clock(e_clock eclock, duration duration)
{

   string strName;

   switch(eclock)
   {
   case clock_none:
      throw invalid_argument_exception();
      return;
   case clock_slow:
      strName="clock_slow";
      break;
   case clock_fast:
      strName="clock_fast";
      break;
   default:
      throw invalid_argument_exception();
      return;

   }

   defer_fork(strName, [&, eclock, duration]()
   {

      _task_clock(eclock, duration);

   });

}

void generic::_task_clock(e_clock eclock, duration duration)
{

   auto timeout = duration.get_total_milliseconds();

   while(true)
   {

      if(!thread_sleep((u32) timeout))
      {

         break;

      }

      try
      {

         on_clock(eclock);

      }
      catch (...)
      {

      }

   }

}


void generic::on_clock(e_clock eclock)
{



}


//#ifdef __APPLE__
//
//void generic::ns_main_async(dispatch_block_t block)
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


void generic::start()
{

   if (has(e_object_synchro))
   {

      call();

   }
   else
   {

      member_fork(&::generic::call);

   }

}


void generic::single_fork(const runnable_array & runnablea)
{

   fork([runnablea]()
   {

      for(auto & pobjectTask : runnablea)
      {

         try
         {

            pobjectTask->call();

         }
         catch (...)
         {

         }

      }

   });

}


void generic::multiple_fork(const runnable_array & runnablea)
{

   for (auto & pobjectTask : runnablea)
   {

      fork([pobjectTask]()
         {

            pobjectTask->call();

         });

   }

}

thread_pointer generic::defer_fork(string strThread)
{

   if (strThread.is_empty())
   {

      strThread = string(type_name()) + "::run";

   }

   return defer_fork(strThread, [this]()
   {

      call();

   });

}


bool generic::handle_exception(::exception_pointer pe)
{

   if(pe.is < exit_exception > ())
   {

      __rethrow(pe);

   }

   return true;

}


bool generic::top_handle_exception(::exception_pointer pe)
{

   __pointer(exit_exception) pexitexception = pe;

   if(pexitexception)
   {

      pexitexception->set_finish();

      return false;

   }

   return true;

}


bool generic::process_exception(::exception_pointer pe)
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


//__pointer(thread) generic::fork(::e_priority epriority, UINT nStackSize, u32 dwCreateFlags, LPSECURITY_ATTRIBUTES pSecurityAttrs)
//{
//
//   return fork([this]()
//   {
//
//      call();
//
//   });
//
//}


void generic::message_receiver_destruct()
{

}


void generic::_001OnUpdate(::message::message * pmessage)
{

   if (pmessage->m_lparam)
   {

      __pointer(::update) pupdate(pmessage->m_lparam);

      call_update(pupdate);

   }
   else
   {

      call_update((::id) (::iptr) pmessage->m_wparam);

   }

}



//void receiver::install_message_routing(::channel * pchannel)
void generic::install_message_routing(::channel * pchannel)
{

   IGUI_MSG_LINK(message_update, pchannel, this, &::generic::_001OnUpdate);

}


__pointer(::generic) generic::running(const char * pszTag) const
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



::estatus generic::bind_update(const ::id & id, bool bCreate)
{

   auto pproperty = fetch_property(id, bCreate);

   if (!pproperty)
   {

      return ::error_failed;

   }

   return bind_update(pproperty);

}


::estatus generic::bind_update(const ::id & id, ::generic * pobject)
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


::estatus generic::bind_update(property * pproperty)
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

::generic * generic::parent_property_set_holder() const
{

   return get_context_application();

}

//__pointer(::handle::ini) generic::appini()
//{
//
//   return __new(::handle::ini(::dir::localconfig()));
//
//}


::file_result generic::get_file(const var & varFile, efileopen eopen)
{

   return Context.file().get_file(varFile, eopen);

}








CLASS_DECL_ACME ::estatus __call(::generic * pobjectTask)
{

   return pobjectTask->call();

}



struct context_object_test_struct :
   virtual public generic
{

   context_object_test_struct(::generic * p) :
      ::generic(p)
   {


   }

   virtual ~context_object_test_struct()
   {

   }

   byte m_ucha[1024];

};

void debug_context_object(::generic * pobject)
{

   auto p1 = __new(struct context_object_test_struct(pobject));

   auto p2 = __new(struct context_object_test_struct(pobject));

   p2 = p1;

}


CLASS_DECL_ACME void object_on_add_composite(const generic * pbase)
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


::estatus call_sync(const runnable_array & runnablea)
{

   try
   {

      for (auto & pobjectTask : runnablea)
      {

         try
         {

            auto estatus = pobjectTask->call();

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








string generic::get_text(const var& var, const ::id& id)
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


::estatus generic::message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   ::estatus estatus = error_failed;

   auto psession = get_context_session();

   callback.m_id = DIALOG_RESULT_CALLBACK;

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
         
         strTitle = Application.get_app_user_friendly_task_bar_name();
         
      }

      estatus = ::os_message_box(puiOwner->get_safe_handle(), strMessage, strTitle, emessagebox, callback);

   }

   return estatus;

}


::estatus generic::message_box_timeout(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::duration& durationTimeout, ::emessagebox emessagebox, ::callback callback)
{

   ::estatus estatus = error_failed;

   //if (::is_null(get_context_session()) || ::is_null(get_context_session()->userex()))
   //{

   //   estatus = get_context_session()->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);

   //}

   if (!estatus)
   {

      estatus = ::os_message_box(puiOwner->get_safe_handle(), pszMessage, pszTitle, emessagebox, callback);

   }

   return estatus;

}


#ifdef DEBUG


void generic::set_context(::context* pcontext)
{

   m_pcontextContext = pcontext;

}


void generic::set_context_thread(::thread* pthread)
{

   m_pthreadContext = pthread;

}


void generic::set_context_app(::acme::application* pappContext)
{

   m_pappContext = pappContext;

}


void generic::set_context_session(::acme::session* psessionContext)
{

   m_psessionContext = psessionContext;

}


void generic::set_context_system(::acme::system* psystemContext)
{

   m_psystemContext = psystemContext;

}


//void generic::set_context_user(::generic * puserContext)
//{
//
//   m_puserContext = puserContext;
//
//}


#endif



