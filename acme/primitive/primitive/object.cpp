#include "framework.h"
#include "acme/constant/message.h"
#include "acme/update.h"
#if OBJECT_REFERENCE_COUNT_DEBUG
#include "acme/platform/obj_ref_debug_impl.h"
#endif
#include "acme/primitive/text/_.h"
#include "acme/primitive/primitive/set_bit.h"
#include "acme/parallelization/synchronously_keep_bit.h"


object::~object() = default;


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

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c >= 0)
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


//void object::create_object_meta()
//{
//
//   if (m_pmeta)
//   {
//
//      return;
//
//   }
//
//   m_pmeta = new object_meta();
//
//}


string object::to_string() const
{

   return string(type_name()) + " (0x" + ::hex::lower_from((uptr)this) + ")";

}


::e_status object::add_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   _synchronous_lock synchronouslock(mutex());

   m_pcompositea.defer_create_new();

   if (!m_pcompositea->add_unique(pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS))
   {

      return success_none;

//#ifdef _DEBUG
//
//      object_on_add_composite(pmatter);
//
//#endif

   }

   return ::success;

}


::e_status object::add_reference(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   _synchronous_lock synchronouslock(mutex());

   m_preferencea.defer_create_new();

   m_preferencea->add_unique(pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   if (m_preferencea->get_upper_bound() == 8)
   {

      if (string(type_name()).contains("application"))
      {

         string strMessage = "what is this? : " + string(m_preferencea->last()->type_name());
         output_debug_string(strMessage);
      }

   }

   return ::success;

}


//::e_status object::release_composite2(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pmatter))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(mutex());
//
//   if (m_pcompositea)
//   {
//
//      if (m_pcompositea->erase(pmatter))
//      {
//
//         return ::success;
//
//      }
//
//   }
//
//   return ::error_failed;
//
//}
//
//
//::e_status object::finalize_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pmatter))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(mutex());
//
//   if (m_pcompositea)
//   {
//
//      if (m_pcompositea->contains(pmatter))
//      {
//
//         synchronouslock.unlock();
//
//         pmatter->destroy();
//
//         synchronouslock.lock();
//
//         if (m_pcompositea)
//         {
//
//            m_pcompositea->erase(pmatter);
//
//         }
//
//         return ::success;
//
//      }
//
//   }
//
//   return ::error_failed;
//
//}
//
//
//::e_status object::release_reference(::matter* pmatter  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   if (::is_null(pmatter))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(mutex());
//
//   if (m_preferencea)
//   {
//
//      if (m_preferencea->erase(pmatter) > 0)
//      {
//
//         return ::success;
//
//      }
//
//   }
//
//   return ::error_failed;
//
//}


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

   TRACE("%s", strMessage.c_str());

//#ifdef __DEBUG
//
//   if (get_application())
//   {
//
//      get_application()->post_critical_error_message(strMessage);
//
//   }
//
//#endif //__DEBUG

}


//array < ::routine >* object::routinea(const ::id& id)
//{
//
//   //if (m_pmeta)
//   //{
//
//   //   auto p = m_pmeta->m_mapRoutine.plookup(id);
//
//   //   if (p)
//   //   {
//
//   //      return &p->element2();
//
//   //   }
//
//   //}
//
//   return nullptr;
//
//}


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


//void object::add_object(::object* pobject)
//{
//
//   {
//
//      _synchronous_lock synchronouslock(mutex());
//
//      __defer_construct_new(m_pobjecta);
//
//      m_pobjecta->add_unique(pobject);
//
//   }
//
//   {
//
//      _synchronous_lock synchronouslock(mutex());
//
//      __defer_construct_new(pobject->m_pobjecta);
//
//      pobject->m_pobjecta->add_unique(this);
//
//   }
//
//}
//
//
//void object::on_delete_object(::object* pobject)
//{
//
//   _synchronous_lock synchronouslock(mutex());
//
//   if (m_pobjecta)
//   {
//
//      m_pobjecta->erase(pobject);
//
//   }
//
//}

//
//void object::enumerate_composite(matter_array& a)
//{
//
//
//}


//void object::enumerate_reference(matter_array& a)
//{
//
//
//}
//


void object::call_routine(const ::id& id)
{

   if (::is_null(m_pmapPropertyRoutine))
   {

      return;

   }
   
   auto & routinea = this->routine_array(id);

   for(auto & routine : routinea)
   {
      
      try
      {
      
         routine();
      
      }
      catch(...)
      {
         
      }
      
   }
   
   //auto payload = this->payload(id);

   //payload.predicate_each([](auto payload) { payload(); });

}



::text::text object::__text(const ::id& id)
{

   return m_pcontext->__text(id);

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

//void object::add_routine(const ::id& id, const ::routine& routine)
//{
//
//   get_meta()->m_mapRoutine[id].add(routine);
//
//}


//void object::add_process(const ::id & id, const ::future & process)
//{
//
//   get_meta()->m_mapProcess[id].add(process);
//
//}


//void object::add_each_routine_from(const ::id& id, ::object* pobjectSource)
//{
//
//   if (pobjectSource)
//   {
//
//      auto proutinea = pobjectSource->routinea(id);
//
//      if (proutinea)
//      {
//
//         get_meta()->m_mapRoutine[id].add(*proutinea);
//
//      }
//
//   }
//
//}


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

//context& object::__context(const ::payload& payload)
//{
//
//   if (payload.has_property("value"))
//   {
//
//      auto pcontext = payload["context"].cast < context >();
//
//      if (pcontext)
//      {
//
//         return *pcontext;
//
//      }
//
//   }
//
//   return *get_context();
//
//}


//::payload object::__context_value(const ::payload& payload)
//{
//
//   if (payload.has_property("context") && payload.has_property("value"))
//   {
//
//      return payload["value"];
//
//   }
//   else
//   {
//
//      return payload;
//
//   }
//
//}


//void object::set_topic_text(const ::string& strTopicText)
//{
//
//   get_meta()->m_strTopicText = strTopicText;
//
//}
//
//
//::e_status object::initialize(::object* pobject)
//{
//
//   auto estatus = ::property_object::initialize(pobject);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


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


//void object::runchild_post_quit(const char * pszTag)
//{
//
//   try
//   {
//
//      auto pmatter = running(pszTag);
//
//      if (pmatter.is_null())
//      {
//
//         return;
//
//      }
//
//      pmatter->destroy();
//
//   }
//   catch (...)
//   {
//
//   }
//
//}
//
//
//void object::child_post_quit_and_wait(const ::string & pszTag, const duration& duration)
//{
//
//   try
//   {
//
//      auto pmatter = running(pszTag);
//
//      if (pmatter.is_null())
//      {
//
//         return;
//
//      }
//
//      pmatter->destroy();
//
//      string strTag(pszTag);
//
//      predicate_Sleep(duration,
//         [this, strTag]()
//      {
//
//         return running(strTag).is_set();
//
//      });
//
//   }
//   catch (...)
//   {
//
//   }
//
//}


::e_status object::post(const ::routine& routine)
{

   __throw(error_interface_only);

   return error_interface_only;

}


void object::defer_update_object_id()
{

   if (m_id.is_empty())
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



//::e_status object::enable_application_events(bool bEnable)
//{
//
//   if (::is_null(get_application()))
//   {
//
//      return false;
//
//   }
//
//   if (!get_application()->enable_application_events(this, bEnable))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}


//::e_status     object::request_file(const ::payload& varFile)
//{
//
//   return request_file(varFile, e_type_new);
//
//}


//::e_status object::request_file(const ::payload& varFile, ::payload varQuery)
//{
//
//   auto pcommandline = __create_new< command_line >();
//
//   pcommandline->m_varFile = varFile;
//
//   pcommandline->m_varQuery = varQuery;
//
//   return request({ pcommandline });
//
//}


//::e_status object::request(arguments arguments)
//{
//
//   __pointer(::create) pcreate;
//
//   auto estatus = __construct_new(pcreate);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = pcreate->initialize_create(arguments);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return do_request(pcreate);
//
//}


void object::do_request(::create* pcreate)
{

   on_request(pcreate);

//   return pcreate->m_estatus;

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


void object::call_request(::create* pcreate)
{

   on_request(pcreate);

//   return ::success;

}


//::user::document* object::open_new_document(::application* pappOnBehalfOf)
//{
//
//   return open_document_file(pappOnBehalfOf, __visible(true));
//
//}


void object::request(::create* pcreate)
{

   on_request(pcreate);

}


//void object::on_request(::create* pcreateParam)
void object::on_request(::create * pcreate)
{

   //__pointer(::create) pcreate(pcreateParam);

   //if (!pcreate)
   //{

   //   auto estatus = __construct(pcreate);

   //   if (!estatus)
   //   {

   //      __throw(estatus);

   //   }

   //   estatus = pcreate->initialize_create(get_application()->m_XstrAppId, ::e_type_empty, true);

   //   if (!estatus)
   //   {

   //      __throw(estatus);

   //   }

   //}

   //do_request(pcreate);

}


void object::destruct()
{



}


void object::system(const ::string & strProjectName)
{

   UNREFERENCED_PARAMETER(strProjectName);

}


::e_status     object::run()
{

   return ::success;

}


//::e_status object::operator()()
//{
//
//   return ::object::operator()();
//
//}


//::e_status object::on_finish()
//{
//
//   m_bDestroying = true;
//
//   auto estatus = destroy_composites();
//
//   if (estatus == error_pending)
//   {
//
//      //m_psystem->add_pending_finish(this);
//
//      return estatus;
//
//   }
//
//   estatus = destroy();
//
//   if (estatus == error_pending)
//   {
//
//      estatus = error_failed;
//
//   }
//
//   return estatus;
//
//}


//::e_status object::set_finish()
//{
//
//// if "this" gets invalid while a member functions of "this" object
//// is running, something is wrong ? or !!!!
//// Yes, someone destroyed it while someone was running a "this" member function.
//// And the caller that called "this" object's member function,
//// wasn't holding proper reference to "this" member.
//// So actually, I cannot make assumption that something is alive
//// running a member of such an object, that doesn't hold proper
//// reference for the duration of execution of a function.
//// __pointer(::object) pobjectHold = this;
//
//   set_finish_bit();
//
//   set_finish_composites();
//
//   return ::success;
//
//}



//
//::e_status object::destroy()
//{
//
//   //if (m_pmeta)
//   //{
//
//   //   m_pmeta->destroy(this);
//
//   //}
//
//   //manager::destroy();
//
//#if OBJECT_TYPE_COUNTER
//
//   if (m_eobject.is(e_object_object_type_counter))
//   {
//
//      m_eobject -= e_object_object_type_counter;
//
//      OBJECT_TYPE_COUNTER_DECREMENT;
//
//   }
//
//#endif
//
//   //m_pcontext.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   //m_pthread.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   //m_papplication.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   //m_psession.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   //m_psystemContext.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//   //on_finalize();
//
//   if (string(m_id).contains("::rx"))
//   {
//
//      output_debug_string("::rx destroy");
//
//   }
//
//   if (string(m_id).contains("::interprocess_intercommunication"))
//   {
//
//      output_debug_string("::interprocess_intercommunication destroy");
//
//   }
//
//   //release_references();
//
//   //{
//
//   //   _synchronous_lock synchronouslock(mutex());
//
//   //   if (m_pobjecta)
//   //   {
//
//   //      for (auto& pobject : *m_pobjecta)
//   //      {
//
//   //         pobject->on_delete_object(this);
//
//   //      }
//
//   //      m_pobjecta->erase_all();
//
//   //   }
//
//   //}
//
//   return ::success;
//
//}
//

void object::add_task(::object* pobjectTask)
{

   if(::is_null(pobjectTask))
   {

      __throw(error_invalid_argument);

      return;

   }

   if(pobjectTask == this)
   {

      __throw(error_invalid_argument);

      return;

   }

   _synchronous_lock synchronouslockParent1(mutex());

   if(is_ascendant_task(pobjectTask))
   {

      __throw(error_invalid_argument);

      return;

   }

   auto ptaskOldParent = pobjectTask->m_pobjectParentTask;

   _synchronous_lock synchronouslockParent2(ptaskOldParent ? ptaskOldParent->mutex() : nullptr);

   _synchronous_lock synchronouslock(pobjectTask->mutex());

   if(ptaskOldParent == this
   && m_pobjectaChildrenTask 
   && m_pobjectaChildrenTask->contains(pobjectTask))
   {

      return;

   }

   if (!m_pobjectaChildrenTask)
   {

      m_pobjectaChildrenTask.create_new();

   }

   string strType = type_c_str();

   if (strType.contains("prodevian"))
   {

      ::output_debug_string("task added to prodevian\n");

   }
   else if (strType.contains("user::thread"))
   {

      ::output_debug_string("task added to user::thread\n");

   }

   m_pobjectaChildrenTask->add(pobjectTask);

   pobjectTask->m_pobjectParentTask = this;

   if(::is_set(ptaskOldParent))
   {

      if(::is_set(ptaskOldParent->m_pobjectaChildrenTask))
      {

         ptaskOldParent->m_pobjectaChildrenTask->erase(pobjectTask);

      }

   }

}


void object::erase_task(::object* pobjectTask)
{

   _synchronous_lock synchronouslock(mutex());

   _synchronous_lock synchronouslockObject(pobjectTask->mutex());

   if (!m_pobjectaChildrenTask)
   {

      return;

   }

   if (pobjectTask->m_pobjectParentTask != this)
   {

      __throw(error_invalid_argument);

      return;

   }

   string strType = type_c_str();

   if (strType.contains("user::thread"))
   {

      ::output_debug_string("task added to user::thread\n");

   }

   pobjectTask->m_pobjectParentTask = nullptr;

   if (m_pobjectaChildrenTask->erase(pobjectTask) <= 0)
   {

      ::output_debug_string("not a child");

   }

}


void object::transfer_tasks_from(::object* ptask)
{

   if(::is_null(ptask))
   {

      __throw(error_invalid_argument);

      return;

   }

   if(ptask == this)
   {

      __throw(error_invalid_argument);

      return;

   }

   _synchronous_lock synchronouslock(mutex());

   if(is_ascendant_task(ptask))
   {

      __throw(error_invalid_argument);

      return;

   }

   _synchronous_lock synchronouslockParent2(ptask->mutex());

   if(!ptask->m_pobjectaChildrenTask
   || ptask->m_pobjectaChildrenTask->is_empty())
   {

      return;

   }

   if (!m_pobjectaChildrenTask)
   {

      m_pobjectaChildrenTask.create_new();

   }

   __pointer_array(::object) objectaChildrenTask;

   objectaChildrenTask = *ptask->m_pobjectaChildrenTask;

   for (auto pobjectTask : objectaChildrenTask)
   {

      _synchronous_lock synchronouslock(pobjectTask->mutex());

      try
      {

         pobjectTask->m_pobjectParentTask = this;

         m_pobjectaChildrenTask->add(pobjectTask);

      }
      catch (...)
      {

      }

   }

   ptask->m_pobjectaChildrenTask.release();

}


bool object::is_ascendant_task(::object * ptaskCandidateAscendant) const
{

   try
   {

      auto p = m_pobjectParentTask;

      while(::is_set(p))
      {

         if(p == ptaskCandidateAscendant)
         {

            return true;

         }

         p = p->m_pobjectParentTask;

      }
      
   }
   catch(...)
   {
      
   }

   return false;

}


bool object::check_tasks_finished()
{

   if (::is_null(m_pobjectaChildrenTask))
   {

      return false;

   }

   if (m_bCheckingChildrenTask)
   {

      return m_pobjectaChildrenTask->has_element();

   }

   if (!is_finishing())
   {

      return m_pobjectaChildrenTask->has_element();

   }

   _synchronous_lock lock(mutex());

   if (m_bCheckingChildrenTask)
   {

      return m_pobjectaChildrenTask->has_element();

   }

   auto synchronouslykeepbitCheckingChildrenTask = synchronously_keep_bit(this, m_ematter, e_matter_checking_children_task, true, false);

   try
   {

      for (int iChildTask = 0; iChildTask < m_pobjectaChildrenTask->get_size(); iChildTask++)
      {

         auto & ptaskChild = m_pobjectaChildrenTask->element_at(iChildTask);

         if (ptaskChild)
         {

            string strType = ptaskChild->type_c_str();

            ptaskChild->set_finish();

         }

      }

      for (int iChildTask = 0; iChildTask < m_pobjectaChildrenTask->get_size(); )
      {

          auto ptaskChild = m_pobjectaChildrenTask->element_at(iChildTask);

          if (!ptaskChild)
          {

             m_pobjectaChildrenTask->erase_at(iChildTask);

          }
          else
          {

             iChildTask++;

          }
      //    else
      //    {

      //       _synchronous_lock synchronouslockChild(ptaskChild->mutex());

      //       string strType = ptaskChild->type_c_str();

      //       if (ptaskChild->m_bTaskTerminated || !ptaskChild->m_bTaskStarted)
      //       {

      //          if (ptaskChild->m_pobjectParentTask == this)
      //          {

      //             ptaskChild->m_pobjectParentTask = nullptr;

      //          }

      //          m_pobjectaChildrenTask->erase_at(iChildTask);

      //       }
      //       else
      //       {

      //          iChildTask++;

      //       }

      //    }

      }

   }
   catch (...)
   {

   }

   if (m_pobjectaChildrenTask->has_element())
   {

      return true;

   }

   if(!is(e_matter_checking_children_task))
   {

      try
      {

         post_quit();

      }
      catch (...)
      {

      }

   }

   return false;

}



//::e_status object::finish()
//{
//
//
//   ::object::finish();
//
//   return ::success;
//
//}
//


::e_status object::destroy_tasks()
{

   set_finish();

//   while (check_tasks_finished())
//   {
//
//      ::sleep(100_ms);
//
//   }

   return ::success;

}


::e_status object::destroy()
{

   auto estatus = destroy_tasks();

   estatus = destroy_composites();

   estatus = release_references();

   estatus = property_object::destroy();

   return ::success;

}


::e_status object::set_finish()
{

   property_object::set_finish();

   kick_idle();

   return ::success;

}


// please refer to object::finish verses/documentation
void object::delete_this()
{

   destroy();

   property_object::delete_this();

}


::e_status object::destroy_composites()
{

   ::e_status estatus = ::success;

   string strTypeName = type_name();

   _synchronous_lock synchronouslock(mutex());

   if (m_pcompositea)
   {

      for (auto& pmatter : *m_pcompositea)
      {

         synchronouslock.unlock();

         auto estatusItem = pmatter->destroy();

         synchronouslock.lock();

      }

      m_pcompositea.release();

   }

   return estatus;

}


::e_status object::release_references()
{

   ::e_status estatus = ::success;

   string strTypeName = type_name();

   _synchronous_lock synchronouslock(mutex());

   if (m_preferencea)
   {

      m_preferencea.release();

   }

   return estatus;

}


CLASS_DECL_ACME::mutex* get_children_mutex();


/// tells if pobject is dependant of this object or of any dependant objects
bool object::___is_reference(::matter* pmatter) const
{

   if (::is_null(pmatter))
   {

      return false;

   }

   _synchronous_lock synchronouslock(get_children_mutex());

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


bool object::__is_composite(::matter* pmatter) const
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


bool object::__is_child_task(::object * pobjectTask) const
{

   if (::is_null(pobjectTask))
   {

      return false;

   }

   _synchronous_lock lock(mutex());

   if (!m_pobjectaChildrenTask)
   {

      return false;

   }

   if (!m_pobjectaChildrenTask->contains(pobjectTask))
   {

      return false;

   }

   return true;

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
//::e_status object::finish(::property_object* pcontextobjectFinish)
//{
//
//   if (!pcontextobjectFinish)
//   {
//
//      pcontextobjectFinish = this;
//
//   }
//
//   auto estatus = set_finish(pcontextobjectFinish);
//
//   if (estatus == success)
//   {
//
//      on_finish();
//
//   }
//
//   return estatus;
//
//}


//string object::__get_text(string str)
//{
//
//   if (get_application() == nullptr)
//   {
//
//      return ::__get_text(str);
//
//   }
//
//   return get_application()->__get_text(str);
//
//}




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


void object::branch(const ::routine_array& routinea)
{

   fork([routinea]()
   {

      for (auto& routine : routinea)
      {

         try
         {

            routine();

         }
         catch (...)
         {

         }

      }

   });

}


void object::branch_each(const ::routine_array& routinea)
{

   for (auto& routine : routinea)
   {

      fork([routine]()
      {

         routine();

      });

   }

}


::task_pointer object::defer_branch(const ::id& id, const ::routine & routine, enum_priority epriority)
{

   auto ptask = get_property_set()[__id(thread)][id].cast < ::task>();

   if(ptask && ptask->is_running())
   {

      return ptask;

   }

   ptask = __create_new < task >();

   ptask->m_pmatter = routine;

   get_property_set()[__id(thread)][id] = ptask;

   ptask->branch();

   return ptask;

}


__transport(task) object::branch_task(matter * pmatter, ::enum_priority epriority, ::u32 nStackSize, ::u32 dwCreateFlags ARG_SEC_ATTRS)
{

   if (::is_null(pmatter))
   {

      return error_failed;

   }

   auto ptask = __create_new < ::task >();

   if (!ptask)
   {

      return error_failed;

   }

   ptask->m_pmatter = pmatter;

   ptask->m_id = typeid(*pmatter).name();

   auto estatus = ptask->branch(epriority, nStackSize, dwCreateFlags ADD_PASS_SEC_ATTRS);

   if (!estatus)
   {

      return estatus;

   }

   return ptask;

}


__transport(task) object::branch(::enum_priority epriority, ::u32 nStackSize, ::u32 dwCreateFlags ARG_SEC_ATTRS)
{

   auto ptask = branch_task(this, epriority, nStackSize, dwCreateFlags ADD_PASS_SEC_ATTRS);

   return ptask;

}


::e_status object::handle_exception(const ::exception::exception& e)
{

   if (::is_exit_exception_status(e.estatus()))
   {

      __rethrow(e);

   }

   return true;

}


::e_status object::top_handle_exception(const ::exception::exception& e)
{

   if (::is_exit_exception_status(e.estatus()))
   {

      m_psystem->process_exit_status(this, e.estatus());

      return false;

   }

   return true;

}


//void object::process_exit_status(const ::e_status& estatus)
//{
//
//   if (estatus == error_exit_system)
//   {
//
//      m_psystem->finish();
//
//   }
//   else if (estatus == error_exit_session)
//   {
//
//      get_session()->finish();
//
//   }
//   else if (estatus == error_exit_application)
//   {
//
//      get_session()->finish();
//
//   }
//   else if (estatus == error_exit_application)
//   {
//
//      ::get_task()->finish();
//
//   }
//
//}


::e_status object::process_exception(const ::exception::exception& e)
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
//   _synchronous_lock synchronouslock(mutex());
//
//   return get_meta()->task_add(this, ptask);
//
//}


void object::task_erase(::task* ptask)
{

   //_synchronous_lock synchronouslock(mutex());

   //if (m_pmeta)
   //{

   //   m_pmeta->task_erase(this, ptask);

   //}


   //void object::task_erase(::task * ptask)
   //{

   try
   {

      string strThreadThis = type_name();

      string strThreadChild = ptask->type_name();

      _synchronous_lock synchronouslock(mutex());

      if (::is_null(ptask))
      {

         __throw(error_invalid_argument);

      }

      //_synchronous_lock slChild(ptask->mutex());

      //if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
      //{

      //   __throw(error_invalid_argument, "thread is no parent-child releationship between the threads");

      //}

      //ptask->m_pobjectParent.release();

      //auto ptaska = _task_array();

      //if (ptaska)
      //{

      //m_pcompositea->erase(ptask);

      //}

      //if (finish_bit() && (!m_ptaska || ptaska->is_empty()))
      if (is_finishing())
      {

         if (strThreadThis == "veriwell_keyboard::application")
         {

            output_debug_string("veriwell_keyboard::application");

         }

         destroy();

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


         __pointer(manual_reset_event) pevent;

         {

            _synchronous_lock synchronouslock(ptask->mutex());

            if (ptask->m_pevSleep.is_null())
            {

               ptask->m_pevSleep = __new(manual_reset_event());

               ptask->m_pevSleep->ResetEvent();

            }

            pevent = ptask->m_pevSleep;

         }

         if (m_psystem && m_psystem->set_finish())
         {

            return error_exit_system;

         }

         //if (m_psession && m_psession->finish_bit())
         //{

         //   return error_exit_session;

         //}

         //if (m_papplication && m_papplication->finish_bit())
         //{

         //   return error_exit_application;

         //}

         if (::is_set(pevent))
         {

            pevent->wait(duration);

            pevent.release();

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

      if (m_psystem && m_psystem->is_finishing())
      {

         return error_exit_system;

      }

      //if (m_psession && m_psession->finish_bit())
      //{

      //   return error_exit_session;

      //}

      //if (m_papplication && m_papplication->finish_bit())
      //{

      //   return error_exit_application;

      //}


      iTenths--;

      sleep(100_ms);

   }

   sleep(millisRemaining);

   return ::success;

}



//void object::task_erase_all()
//{
//
//   /*_synchronous_lock synchronouslock(mutex());
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
//   _synchronous_lock synchronouslock(mutex());
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
//   _synchronous_lock synchronouslock(mutex());
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
//   _synchronous_lock synchronouslock(mutex());
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


void object::_001OnUpdate(::message::message* pmessage)
{

   //::subject::subject subject(this, (::iptr)pmessage->m_wparam);

   //subject.m_payload = (::matter*)(::iptr)pmessage->m_lparam;

   //process(&subject);

}



//void receiver::install_message_routing(::channel * pchannel)
void object::install_message_routing(::channel* pchannel)
{

   //pchannel->add_handler(e_message_system_update, this, &::object::_001OnUpdate);

}


//__pointer(::matter) object::running(const ::string & pszTag) const
//{
//
//   //if (m_pcompositea)
//   //{
//
//   //   auto pobject = ::parallelization::array::is_running(*m_pcompositea, pszTag);
//
//   //   if (pobject)
//   //   {
//
//   //      return pobject;
//
//
//   //   }
//
//   //}
//
//   //if (m_preferencea)
//   //{
//
//   //   auto pobject = ::parallelization::array::is_running(*m_preferencea, pszTag);
//
//   //   if (pobject)
//   //   {
//
//   //      return pobject;
//
//   //   }
//
//   //}
//
//   return nullptr;
//
//}


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




::property_object* object::parent_property_set_holder() const
{

   return m_pcontext;

}

//__pointer(::handle::ini) object::appini()
//{
//
//   return __new(::handle::ini(         auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->localconfig()));
//
//}


::file_transport object::get_file(const ::payload& varFile, const ::file::e_open& eopen)
{

   return m_pcontext->get_file(varFile, eopen);

}

//
//
//
//
//





struct context_object_test_struct :
   virtual public object
{

   context_object_test_struct(::matter* p)
   {


   }

   virtual ~context_object_test_struct()
   {

   }

   byte m_ucha[1024];

};

//void debug_context_object(::object* pobject)
//{
//
//   auto p1 = __new(struct context_object_test_struct(pobject));
//
//   auto p2 = __new(struct context_object_test_struct(pobject));
//
//   p2 = p1;
//
//}
//
//
//CLASS_DECL_ACME void object_on_add_composite(const matter* pusermessage)
//{
//
//   string strType = ::str::demangle(pusermessage->type_name());
//
//   if (strType.contains_ci("user::thread"))
//   {
//
//      //debug_break();
//
//   }
//
//}


bool __no_continue(::e_status estatus)
{

   return false;

}


::e_status call_sync(const ::routine_array& methoda)
{

   try
   {

      for (auto& method : methoda)
      {

         try
         {

            auto estatus = method();

            if (__no_continue(estatus))
            {

               return estatus;

            }

         }
         catch (const ::exception::exception& e)
         {

            if (__no_continue(e.m_estatus))
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








string object::get_text(const ::payload& payload, const ::id& id)
{

   if (payload.has_property(id) && payload[id].has_char())
   {

      return payload[id];

   }

   return "";

   //string str = m_pcontext->m_papexcontext->file().as_string(payload);

   //if (str.has_char())
   //{

   //   return str;

   //}

   //auto strExtension = payload.get_file_path().extension();

   //if (strExtension == __str(id))
   //{

   //   return "";

   //}

   //return payload.get_string();

}


__pointer(::extended::future < ::conversation >) object::message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box& emessagebox)
{

   auto psystem = m_psystem;

   auto presult = psystem->message_box(puserinteraction, strMessage, strTitle, emessagebox);

   return presult;

}


//::e_status object::message_box_timeout(const ::string & pszMessage, const ::string & pszTitle, const ::duration& durationTimeout, const ::e_message_box & emessagebox, const ::future & process)
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


//void object::set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   m_pcontext.reset(pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//void object::set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   m_pthread.reset(pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//void object::set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   m_papplication.reset(pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//void object::set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   m_psession.reset(psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
////void object::set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   m_psystemContext.reset(psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
////
////}
//

#endif


matter* object::get_taskpool_container()
{

   //return m_pthread;

   return nullptr;

}







//
//
//object::~object()
//{
//
//}

//
//#ifdef _DEBUG
//
//
//i64 object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//i64 object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//i64 object::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//#else
//
//
//i64 object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//i64 object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//i64 object::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//{
//
//   return property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//}
//
//
//#endif


//::apex::system* object::get_system() const
//{
//
//
//}
//
//
//void object::process_exit_status(const ::e_status& estatus)
//{
//
//
//}
//
//
//::application* object::_get_application()
//{
//
//   return m_papplication;
//
//}


//inline ::application* object::application() { return m_papplication; }


//template < typename BASE_TYPE >
//__pointer(BASE_TYPE) file_as(const ::payload& varFile);

//
//void object::add_routine(const ::id& idRoutine, const ::routine& routine)
//{
//
//
//}

//
//void object::add_each_routine_from(const ::id& idRoutine, ::object* pobjectSource)
//{
//
//
//}

//
//array < ::routine >* object::routinea(const ::id& idRoutine)
//{
//
//   return nullptr;
//
//}

//
//void object::call_routine(const ::id& idRoutine)
//{
//
//
//
//}
//

//inline ::payload object::context_value(const ::payload& payload)

//
//
//void object::task_erase(::task* ptask)
//{
//
//
//}

//
//::e_status object::sleep(const ::duration& duration)
//{
//
//   return ::success;
//
//}


//template < typename BASE_TYPE >
//void save_to(const ::payload& varFile, BASE_TYPE* pobject);


::e_status object::initialize(::object* pobject)
{
   
   auto estatus = ::success;

#if OBJECT_TYPE_COUNTER

   if (!m_eobject.is(e_object_object_type_counter))
   {

      m_eobject += e_object_object_type_counter;

      OBJECT_TYPE_COUNTER_INCREMENT;

   }

#endif

   //#if OBJECT_REFERENCE_COUNT_DEBUG
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

   if (!get_system())
   {

      m_psystem = pobject->get_system();

   }

   if (!m_pcontext)
   {

      m_pcontext = pobject->m_pcontext;

   }

   estatus = on_initialize_object();

   if (!estatus)
   {

      return estatus;

   }

   //if (!m_papplication)
   //{

   //   m_papplication = pobject->m_papplication;

   //}

   //if (!m_psession)
   //{

   //   m_psession = pobject->m_psession;

   //}

   //if (!psystem)
   //{

   //   set_context_system(::::apex::get_system(pobject) OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

   //}

   //if (!get_context())
   //{

   //   if (m_papplication)
   //   {

   //      m_pcontext = m_papplication;

   //   }
   //   else if (m_psession)
   //   {

   //      m_pcontext = m_psession;

   //   }
   //   else if (m_psystem)
   //   {

   //      m_pcontext = m_psystem;

   //   }

   //}

   return estatus;

}


//::e_status object::on_initialize_object()
//{
//
//   return ::success;
//
//}


//::e_status object::destroy()
//{
//
//
//}


//::thread_pointer object::launch(const ::routine& routine)
//{
//
//   auto pthread = __create_new < ::thread >();
//
//   pthread->m_pmatter = routine;
//
//   pthread->m_id = pthread->m_pmatter->type_name();
//
//   pthread->begin_thread();
//
//   return pthread;
//
//}
//


//inline const ::string & object::topic_text();

 //context& object::__context(const ::payload& payload)
 //{


 //}

 //{

 //   return 

 //}

//::payload object::__context_value(const ::payload& payload)
//{
//
//   return ::payload();
//
//}

//void object::set_topic_text(const string& str)
//{
//
//
//}

//void create_object_meta();

//inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

//inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

//inline ::context* object::get_context() const { return m_pcontext; }

//inline ::thread* object::get_thread() const { return m_pthread; }

//inline ::application* object::get_application() const { return m_papplication; }

//inline ::apex::session* object::get_session() const { return m_psession; }

//::apex::system * psystem const { return m_psystemContext; }

//::object * get_context_user() const { return m_puserContext; }

//inline ::application * application() const { return m_papplication; }

//string object::get_text(const ::payload& payload, const ::id& id)
//{
//
//   return "";
//
//}
////
//#ifdef _DEBUG
//    void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   // void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   // void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   // void set_object(::object * pobject) 


   //inline void defer_set_object(::object * pobject);

::e_status object::operator()()
{

   return run();

}


//inline i64 get_ref_count()
//{

//   return m_countReference;

//}


// ::user::primitive* get_user_interaction_host();
// ::user::interaction * get_host_window();


//void object::dev_log(string str) const
//{
//
//
//}


::object& object::operator = (const ::payload& payload)
{

   return *this;

}




//static u32 s_thread_proc(void* p);


// void to_string(const string_exchange & str) const 

//::image_transport create_image();
//::image_transport create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

//::image_transport get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
//::image_transport matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

//template < typename BASE_TYPE >
//inline __transport(BASE_TYPE) __create();

//template < typename BASE_TYPE >
//inline __transport(BASE_TYPE) __id_create(const ::id& id);

//template < typename TYPE >
//inline __transport(TYPE) __create_new();

//inline ::e_status __compose(__composite(::image) & pimage);

//inline ::e_status __compose(__composite(::image) & pimage, ::image * pimageSource);

//inline ::e_status __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : ::e_status(::success); }

// for composition (ownership)

//template < typename BASE_TYPE >
//inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE >
//inline ::e_status __id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id);

//template < typename BASE_TYPE >
//inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource);

//template < typename TYPE >
//inline ::e_status __raw_compose_new(__composite(TYPE)& ptype);

//template < typename TYPE >
//inline ::e_status __compose_new(__composite(TYPE)& ptype);




//template < typename BASE_TYPE >
//inline ::e_status __defer_compose(__composite(BASE_TYPE)& pusermessage) { return !pusermessage ? __compose(pusermessage) : ::e_status(::success); }

//template < typename BASE_TYPE >
//inline ::e_status __defer_id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id) { return !pusermessage ? __id_compose(pusermessage) : ::e_status(::success); }

//template < typename TYPE >
//inline ::e_status __defer_raw_compose_new(__composite(TYPE)& ptype) { return !ptype ? __raw_compose_new(ptype) : ::e_status(::success); }

//template < typename TYPE >
//inline ::e_status __defer_compose_new(__composite(TYPE)& ptype) { return !ptype ? __compose_new(ptype) : ::e_status(::success); }




//template < typename BASE_TYPE >
//inline ::e_status __construct(__pointer(BASE_TYPE)& pusermessage);

//template < typename BASE_TYPE >
//inline ::e_status __id_construct(__pointer(BASE_TYPE)& pusermessage, const ::id& id);

//template < typename TYPE >
//inline ::e_status __construct_new(__pointer(TYPE)& pusermessage);

//template < typename BASE_TYPE >
//inline ::e_status __release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE >
//inline ::e_status __release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename SOURCE >
//inline ::e_status release_reference(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


// ::e_status add_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
// ::e_status add_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 


// ::e_status release_composite2(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
// ::e_status finalize_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
// ::e_status release_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 


//template < typename BASE_TYPE >
//inline ::e_status add_composite(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status __refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename SOURCE >
//inline ::e_status add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename SOURCE >
//inline ::e_status add_reference(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//template < typename SOURCE >
//inline ::e_status add_reference(__reference(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

//void object::delete_this()
//{
//
//
//}

//void object::destruct()
//{
//
//
//}

//void object::system(const ::string & pszProjectName)
//{
//
//}
//
//::e_status object::enable_application_events(bool bEnable)
//{
//
//   return ::success;
//
//}

//::e_status object::handle_exception(const ::exception::exception& e)
//{
//
//   return ::success;
//
//}
//
//::e_status object::top_handle_exception(const ::exception::exception& e)
//{
//
//   return ::success;
//
//}


//::e_status object::process_exception(const ::exception::exception& e)
//{
//
//   return ::success;
//
//}


//::property_object* object::parent_property_set_holder() const
//{
//
//   if (m_papplication && m_papplication.m_p != this)
//   {
//
//      return m_papplication.m_p;
//
//   }
//
//   if (m_psession && m_psession.m_p != this)
//   {
//
//      return m_psession.m_p;
//
//   }
//
//   if (m_psystem && (::property_object*)m_psystem != (::property_object*)this)
//   {
//
//      return m_psystem;
//
//   }
//
//   return nullptr;
//
//}
//
//
//void object::copy_from(const object& o)
//{
//
//
//}
//

//string object::get_tag() const
//{
//
//   return "";
//
//}


//bool object::is_thread() const
//{
//   return false;
//
//}


//bool object::task_get_run() const
//{
//
//   return true;
//}


//bool object::is_running() const
//{
//
//   return true;
//
//}


//void object::child_post_quit(const ::string & pszTag)
//{
//
//
//}


//void object::child_post_quit_and_wait(const ::string & pszTag, const duration& duration)
//{
//
//
//}


//::e_status object::finish(::property_object* pcontextobjectFinish)
//{
//
//   return ::success;
//
//}

//::e_status object::set_finish(::property_object* pcontextobjectFinish)
//{
//
//   return ::success;
//
//}

//::e_status object::set_finish_composites(::property_object* pcontextobjectFinish)
//{
//
//   return ::success;
//
//}


//void object::on_finish()
//{
//
//
//}


//void object::defer_update_object_id()
//{
//
//
//}


//::id object::calc_default_object_id() const
//{
//
//   return ::id();
//
//}


//void object::install_message_routing(::channel* pchannel)
//{
//
//
//}

//void object::message_receiver_destruct()
//{
//
//
//
//}

//void object::_001OnUpdate(::message::message* pmessage)
//{
//
//
//}


//::e_status object::request_file(const ::payload& varFile)
//{
//
//   return ::success;
//
//}


//::e_status object::request_file(const ::payload& varFile, ::payload varQuery)
//{
//
//   return ::success;
//
//}


//::e_status object::request(arguments arguments)
//{
//
//   return ::success;
//
//}


//::e_status object::do_request(::create* pcreate)
//{
//
//   return ::success;
//
//}


//__pointer(::extended::future < ::conversation >)  object::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box& emessagebox)
//{
//
//   return nullptr;
//
//}
//{
//
//   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

//}


// ::e_status message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
//{

//   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

//}

// ::e_status message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
// ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

//void object::release_references()
//{
//
//}

//__pointer(::matter) object::running(const ::string & pszTag) const
//{
//
//   return nullptr;
//
//}

//bool object::___is_reference(::matter* pobject) const
//{
//
//   return false;
//
//}

//bool object::__is_composite(::matter* pobject) const
//{
//
//   return false;
//
//}

//bool object::__is_child_task(::task* ptask) const
//{
//
//   return false;
//
//}

//void object::on_finalize()
//{
//
//
//}
//
//::e_status object::call_request(::create* pcreate)
//{
//
//   return ::success;
//
//}

//// former user::server
// ::user::document* open_new_document(::application* pappOnBehalfOf);
//void object::on_request(::create* pcreate)
//{
//
//
//}

// ::user::document* open_document_file(::application* pappOnBehalfOf);
// ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
// ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile);
// ::user::document* create_subdocument(::user::impact_data* pimpactdata);

//
//::e_status object::run()
//{
//
//   return ::success;
//
//}


//string object::lstr(const ::id& id, string strDefault)
//{
//
//   return "";
//
//}
//
//
//string object::__get_text(string str)
//{
//
//   return "";
//
//}



//template < typename PRED >
//::image_transport get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

// ::image_transport load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
// ::image_transport load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
// ::image_transport load_matter_icon(string_array & straMatter, string strIcon);
// ::image_transport load_thumbnail(const ::payload & varFile, int w, int h);
// ::image_transport load_thumbnail(const char * pszPath);
// ::image_transport load_dib(const ::file::path & pathDib);



bool object::IsSerializable() const
{

   return false;

}


//void object::start()
//{
//
//
//}
//
//
//void object::single_fork(const ::routine_array& routinea)
//{
//
//
//}
//

//void object::multiple_fork(const ::routine_array& routinea)
//{
//
//
//}

//   using property_object::defer_fork;

  /* template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::routine& routine)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }*/


   //inline ::e_status object::defer_fork(::thread_pointer& pthread, const ::routine& routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer lcontext_object::aunch(const ::routine& routine);


   //template < typename METHOD >
   //inline ::task_pointer object::opt_fork(const ::routine& routine)
   //{

   //   auto ptask = ::get_task();

   //   _synchronous_lock synchronouslock(ptask->mutex());

   //   if (ptask && ptask->m_bIsPredicate)
   //   {

   //      routine();

   //      return ptask;

   //   }

   //   return launch(routine);

   //}


   //template < typename METHOD >
   //inline ::thread_pointer fork(METHOD method);


   //template < typename PRED >
   //inline auto new_predicateicate_thread(PRED pred);

   //template < typename TYPE >
   //inline auto async(void (TYPE::* pfnMemberProcedure)())
   //{

   //   return fork([this, pfnMemberProcedure]()
   //      {

   //         TYPE* ptype = dynamic_cast <TYPE*> (this);

   //         (ptype->*pfnMemberProcedure)();

   //      });

   //}

   //template < typename PRED >
   //inline ::thread_pointer predicate_run(bool bSync, PRED pred);

   //::thread_pointer object::begin(::enum_priority epriority, ::u32 nStackSize, u32 dwCreateFlags)
   //{

   //   return nullptr;

   //}
   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//    void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());


   // void to_string(string & str) const 


//::file_transport object::get_file(const ::payload& varFile, const ::file::e_open& eopen)
//{
//
//   return nullptr;
//
//}

//inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary);
//inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



//::e_status add_update_notification(property * pproperty);
//::e_status add_update_notification(const ::id & id, bool bCreate = true);
//::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const char * psz, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(psz, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const char * psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   //template < typename TYPE >
   //::thread_pointer start_below_normal(void (TYPE::* pfn)())
   //{

   //   return fork(pfn, ::e_priority_below_normal);

   //}


   //template < typename TYPE >
   //::e_status __construct(::thread_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //::e_status __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::thread_pointer __start_thread(const ::id& id, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


//matter* object::get_taskpool_container()
//{
//
//   return nullptr;
//
//}

