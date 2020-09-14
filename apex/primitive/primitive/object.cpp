#include "framework.h"
#include "apex/message.h"
#include "apex/update.h"



//extern ::mutex * g_pmutexChildren;

#ifdef DEBUG

CLASS_DECL_APEX void object_on_add_composite(const generic* pbase);

#endif


object::object(::layered * pobjectContext)
{

   m_pmeta = nullptr;

   set_layer(0, this);

   //m_pObjectThis = nullptr;

   set_context_object(__object(pobjectContext));

   //__refer(m_pobjectContext, pobject);

   //__refer(m_pappContext, ::get_context_application(m_pobjectContext));

   //__refer(m_psessionContext, ::get_context_session(m_pobjectContext));

   //__refer(m_psystemContext, ::get_context_system(m_pobjectContext));

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

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 object::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
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


i64 object::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


//sync * object::get_mutex()
//{
//
//   return mutex();
//
//}


void object::create_object_meta()
{

   if (m_pmeta)
   {

      return;

   }

   m_pmeta = new object_meta();

}


void object::to_string(string & str) const
{

   str = string(type_name()) + " (0x" + ::hex::lower_from((uptr)this) + ")";

}


::estatus object::add_composite(::generic* pobject)
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


::estatus object::add_reference(::generic* pobject)
{

   sync_lock sl(mutex());

   m_preferencea.defer_create_new();

   if (m_preferencea->add_unique(pobject))
   {

      pobject->add_ref(OBJ_REF_DBG_P_NOTE(this, debug_note()));

   }

   return ::success;

}


::estatus object::release_composite(::generic* pobject)
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


::estatus object::release_reference(::generic* pobject)
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







array < ::procedure >* object::procedures(const ::id & idProcedure)
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


array < ::callback >* object::callbacks(const ::id & idCallback)
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


void object::runall(const ::id & idProcedure)
{

   auto pprocedures = procedures(idProcedure);

   if(pprocedures)
   {

      pprocedures->pred_each([](auto& f) {f.call(); });

   }

}

void object::receive(const ::id & idCallback, const ::var& var)
{

   auto pcallbacks = callbacks(idCallback);

   if(pcallbacks)
   {

      pcallbacks->pred_each([&var](auto& f) {f.receive_response(var); });

   }

}


void object::add(const ::procedure & procedure)
{

   meta()->m_proceduremap[procedure.m_id].add(procedure);

}


void object::add(const ::callback & callback)
{

   meta()->m_callbackmap[callback.m_id].add(callback);

}


void object::add_procedures_from(const ::id &idProcedure, ::object* pobjectSource)
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


void object::add_callbacks_from(const ::id & idCallback, ::object * pobjectSource)
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


void object::set_context_object(::layered * pobjectContext)
{

   ::context_object::set_context_object(pobjectContext);

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

   set_context_object(pobjectContext);

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


void object::child_post_quit_and_wait(const char * pszTag, const duration & duration)
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



bool object::enable_application_events(bool bEnable)
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

   auto pcommandline = __new(command_line(this));

   pcommandline->m_varFile = varFile;

   pcommandline->m_varQuery = varQuery;

   return request({pcommandline});

}


::estatus     object::request(arguments arguments)
{

   auto pcreate = __new(::create(this, arguments));

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


void object::on_request(::create* pcreate)
{

   __pointer(::create) cc(__new(::create(this, Application.m_strAppId, ::type_empty, true)));

   if (pcreate == nullptr)
   {

      pcreate = cc;

   }

   do_request(pcreate);

   //      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();

}


//::user::document* object::open_document_file(::apex::application* pappOnBehalfOf)
//{
//
//   return open_document_file(pappOnBehalfOf, ::type_empty_argument);
//
//}


//::user::document* object::open_document_file(::apex::application* pappOnBehalfOf, const var& varFile, const ::var & varOptions, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
//{
//
//   auto pcreate = __new(::create(pappOnBehalfOf, pappOnBehalfOf->m_strAppId, varFile, varOptions, puiParent, eflag, id));
//
//   do_request(pcreate);
//
//   return ::user::__document(pcreate);
//
//}


//::user::document* object::open_document_file(::apex::application* pappOnBehalfOf, const var& varFile)
//{
//
//   return open_document_file(pappOnBehalfOf, varFile, ::type_empty_argument);
//
//}


//::user::document* object::create_subdocument(::user::impact_data* pimpactdata)
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


::estatus object::call()
{

   return ::context_object::call();

}


void object::on_finalize()
{

}


void object::finalize()
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

// please refer to object::set_finish verses/documentation
void object::delete_this()
{

   set_finish();

   context_object::delete_this();

}


//sync * object::get_mutex() const
//{
//
//   return mutex();
//
//}


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


void object::set_finish_composites()
{

   if (m_pcompositea)
   {

      for (auto & pcomposite : *m_pcompositea)
      {

         pcomposite->set_finish();

      }

   }

}


void object::release_references()
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

CLASS_DECL_ACME mutex* get_children_mutex();


/// tells if pobject is dependant of this object or of any dependant objects
bool object::___is_reference(::generic * pobject) const
{

   if (::is_null(pobject))
   {

      return false;

   }

   sync_lock sl(get_children_mutex());

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


bool object::__is_composite(::generic * pobject) const
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

// set_finish (machines...)
// "ask" to close object, not cancellable

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
void object::set_finish()
{

   string strTypeName = type_name();

#ifdef ANDROID

   demangle(strTypeName);

#endif

   if (strTypeName == "user::shell")
   {

      output_debug_string("user::shell::set_finish");

   }
   else if (strTypeName == "apex::system")
   {

      output_debug_string("apex::system::set_finish");

   }

   set_finish_composites();

   finalize();

}


string object::__get_text(string str)
{

   if(get_context_application() == nullptr)
   {

      return ::__get_text(str);

   }

   return Application.__get_text(str);

}


void object::start_clock(e_clock eclock, duration duration)
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

void object::_task_clock(e_clock eclock, duration duration)
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


void object::on_clock(e_clock eclock)
{



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

      call();

   }
   else
   {

      member_fork(&::object::call);

   }

}


void object::single_fork(const runnable_array & runnablea)
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


void object::multiple_fork(const runnable_array & runnablea)
{

   for (auto & pobjectTask : runnablea)
   {

      fork([pobjectTask]()
         {

            pobjectTask->call();

         });

   }

}

thread_pointer object::defer_fork(string strThread)
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


bool object::handle_exception(::exception_pointer pe)
{

   if(pe.is < exit_exception > ())
   {

      __rethrow(pe);

   }

   return true;

}


bool object::top_handle_exception(::exception_pointer pe)
{

   __pointer(exit_exception) pexitexception = pe;

   if(pexitexception)
   {

      pexitexception->set_finish();

      return false;

   }

   return true;

}


bool object::process_exception(::exception_pointer pe)
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


//__pointer(thread) object::fork(::e_priority epriority, UINT nStackSize, u32 dwCreateFlags, LPSECURITY_ATTRIBUTES pSecurityAttrs)
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


void object::message_receiver_destruct()
{

}


void object::_001OnUpdate(::message::message * pmessage)
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
void object::install_message_routing(::channel * pchannel)
{

   IGUI_MSG_LINK(message_update, pchannel, this, &::object::_001OnUpdate);

}


__pointer(::object) object::running(const char * pszTag) const
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


CLASS_DECL_APEX void object_on_add_composite(const generic * pbase)
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


::estatus object::message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
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

      estatus = ::os_message_box(strMessage, strTitle, emessagebox, callback);

   }

   return estatus;

}


::estatus object::message_box_timeout(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::duration& durationTimeout, ::emessagebox emessagebox, ::callback callback)
{

   ::estatus estatus = error_failed;

   //if (::is_null(get_context_session()) || ::is_null(get_context_session()->userex()))
   //{

   //   estatus = get_context_session()->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);

   //}

   if (!estatus)
   {

      estatus = ::os_message_box(pszMessage, pszTitle, emessagebox, callback);

   }

   return estatus;

}


#ifdef DEBUG


void object::set_context(::context* pcontext)
{

   m_pcontextContext = pcontext;

}


void object::set_context_thread(::thread* pthread)
{

   m_pthreadContext = pthread;

}


void object::set_context_app(::apex::application* pappContext)
{

   m_pappContext = pappContext;

}


void object::set_context_session(::apex::session* psessionContext)
{

   m_psessionContext = psessionContext;

}


void object::set_context_system(::apex::system* psystemContext)
{

   m_psystemContext = psystemContext;

}


//void object::set_context_user(::object * puserContext)
//{
//
//   m_puserContext = puserContext;
//
//}


#endif


// CLASS_DECL_APEX const char* topic_text(::generic* pgeneric)
// {

//    if (::is_null(pgeneric))
//    {

//       return nullptr;

//    }

//    auto playered = pgeneric->m_pobjectContext;

//    if (!playered)
//    {

//       return nullptr;

//    }

//    auto pobject = __object(playered);

//    if (::is_null(pobject))
//    {

//       return nullptr;

//    }

//    return pobject->topic_text();

// }

