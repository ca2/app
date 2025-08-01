#include "framework.h"
#include "object_meta.h"
#include "acme/constant/message.h"
#include "acme/handler/extended_topic.h"
//#include "acme/update.h"
//#if REFERENCING_DEBUGGING
//#include "acme/platform/obj_ref_debug_impl.h"
//#endif
//#include "acme/constant/idpool.h"
//#include "acme/prototype/text/_.h"
#include "acme/prototype/prototype/set_bit.h"
//#include "acme/prototype/string/hex.h"
#include "acme/prototype/text/text.h"
#include "acme/prototype/collection/atom_map.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/queue.h"
#include "acme/parallelization/synchronously_keep_bit.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"
#include "acme/platform/referencing_debugging.h"
#include "acme/platform/system.h"


object::~object()
{

   ::acme::del(m_pmeta);

   auto particleaNotify = ::transfer(m_particleaNotify);

   for (auto pparticle : particleaNotify)
   {

      pparticle->on_notify(this, id_destroy);

   }

}


long long object::increment_reference_count()
{

   return ::subparticle::increment_reference_count();
//   auto c = m_countReference++;
//
//#if REFERENCING_DEBUGGING
//
//   add_reference_item(m_bIncludeCallStackTrace);
//
//#endif
//
//   return c;

}


long long object::decrement_reference_count()
{

   return ::subparticle::decrement_reference_count();
//   auto c = --m_countReference;
//
//#if REFERENCING_DEBUGGING
//
//   if (c >= 0)
//   {
//
//      erase_reference_item();
//
//   }
//
//#endif
//
//   return c;

}


long long object::release()
{

   long long i = decrement_reference_count();

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

   m_pmeta = __raw_new object_meta();

}


string object::as_string() const
{

   return ::type(this).name() + " (0x" + ::hex::lower_case_from((uptr)this) + ")";

}


//void object::add_composite(::particle * pparticle)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   __defer_construct_new(m_pcompositea);
//
//   if (!m_pcompositea->add_unique(pelement))
//   {
//
//      throw ::exception(success_none);
//
////#ifdef _DEBUG
////
////      object_on_add_composite(pelement);
////
////#endif
//
//   }
//
//   //return ::success;
//
//}
//
//
//void object::add_reference(::particle * pparticle)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   __defer_construct_new(m_preferencea);
//
//   m_preferencea->add_unique(pelement);
//
//   if (m_preferencea->get_upper_bound() == 8)
//   {
//
//      if (::type(this).name().contains("application"))
//      {
//
//         string strMessage = "what is this? : " + __type_name(m_preferencea->last());
//
//         information(strMessage);
//
//      }
//
//   }
//
//   //return ::success;
//
//}


//void object::release_composite2(::particle * pparticle)
//{
//
//   if (::is_null(pelement))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_pcompositea)
//   {
//
//      if (m_pcompositea->erase(pelement))
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
//void object::finalize_composite(::particle * pparticle)
//{
//
//   if (::is_null(pelement))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_pcompositea)
//   {
//
//      if (m_pcompositea->contains(pelement))
//      {
//
//         synchronouslock.unlock();
//
//         pelement->destroy();
//
//         synchronouslock.lock();
//
//         if (m_pcompositea)
//         {
//
//            m_pcompositea->erase(pelement);
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
//void object::release_reference(::particle * pparticle )
//{
//
//   if (::is_null(pelement))
//   {
//
//      return ::success_none;
//
//   }
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_preferencea)
//   {
//
//      if (m_preferencea->erase(pelement) > 0)
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


//::user::interaction_base* object::get_user_interaction_host()
//{
//
//   if (m_psession.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return __user_prototype(m_psession->m_puserinteractionHost);
//
//}


//::user::interaction * object::get_host_user_interaction()
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


::extended_topic_pointer object::create_extended_topic(const ::atom & atom)
{

   auto pextendedtopic = __allocate ::extended_topic(atom);

   pextendedtopic->initialize(this);

   return ::transfer(pextendedtopic);

}


void object::dev_log(const ::scoped_string & scopedstrMessage)
{

   information() << scopedstrMessage.c_str();

//#ifdef _DEBUG
//
//   if (get_app())
//   {
//
//      get_app()->post_critical_error_message(strMessage);
//
//   }
//
//#endif //__DEBUG

}


//array < ::procedure >* object::routinea(const ::atom& atom)
//{
//
//   //if (m_pmeta)
//   //{
//
//   //   auto p = m_pmeta->m_mapRoutine.plookup(atom);
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


//array < ::future >* object::processa(const ::atom & idProcess)
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


//void object::add_object(::object* pparticle)
//{
//
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      __defer_construct_new(m_pobjecta);
//
//      m_pobjecta->add_unique(pparticle);
//
//   }
//
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      __defer_construct_new(pparticle->m_pobjecta);
//
//      pparticle->m_pobjecta->add_unique(this);
//
//   }
//
//}
//
//
//void object::on_delete_object(::object* pparticle)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_pobjecta)
//   {
//
//      m_pobjecta->erase(pparticle);
//
//   }
//
//}

//
//void object::enumerate_composite(element_array& a)
//{
//
//
//}


//void object::enumerate_reference(element_array& a)
//{
//
//
//}
//
//
//
void object::call_routine2(const ::procedure & procedure)
{

   procedure();

}


void object::call_procedures(const ::atom& atom)
{

   auto procedurea = this->procedure_array(atom);

   for (auto& procedure : procedurea)
   {

      try
      {

         procedure();

      }
      catch (...)
      {

      }

   }

}


void object::post_procedures(const ::atom& atom)
{

   auto procedurea = this->procedure_array(atom);

   for (auto& procedure : procedurea)
   {

      post(procedure);

   }

   //return for_routines_with_id(atom, this, &::object::post);

}



void object::send_procedures(const ::atom& atom)
{

   auto procedurea = this->procedure_array(atom);

   for (auto& procedure : procedurea)
   {

      send(procedure);

   }

}


//void object::post_procedure(const ::procedure& procedure)
//{
//
//   m_papplication->fork(procedure);
//
//}
//
//
//void object::send_procedure(const ::procedure& procedure)
//{
//
//   m_papplication->send_procedure(procedure);
//
//}
//
//void object::post(::particle * pparticle)
//{
//   post_procedure([pparticle]()
//      {
//
//        pparticle->call_run();
//
//});
//}
//
//void object::send(::particle * pparticle)
//{
//
//   ::procedure procedure;
//
//   procedure = [pparticle]()
//      {
//
//         pparticle->call_run();
//
//      };
//
//   procedure.m_timeTimeout = pparticle->get_run_timeout();
//
//   send_procedure(procedure);
//}



::text::text object::__text(const ::atom& atom)
{

   return m_papplication->__text(atom);

}


//void object::send_payload(const ::atom & idProcess, const ::payload & payload)
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


void object::add_procedure(const ::atom& atom, const ::procedure & procedure)
{

   get_meta()->m_mapRoutine[atom].add(procedure);

}


//void object::add_process(const ::atom & atom, const ::future & future)
//{
//
//   get_meta()->m_mapProcess[atom].add(process);
//
//}


void object::add_each_routine_from(const ::atom& atom, ::object* pobjectSource)
{

   if (::is_set(pobjectSource))
   {

      auto procedurea = pobjectSource->procedure_array(atom);

      get_meta()->m_mapRoutine[atom].append(procedurea);

   }

}


//void object::add_each_process_from(const ::atom & atom, ::object * pobjectSource)
//{
//
//   if (pobjectSource)
//   {
//
//      auto pprocessa = pobjectSource->processa(atom);
//
//      if (pprocessa)
//      {
//
//         get_meta()->m_mapProcess[atom].add(*pprocessa);
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


//void object::set_topic_text(const ::scoped_string & scopedstrTopicText)
//{
//
//   get_meta()->m_strTopicText = strTopicText;
//
//}
//
//
//void object::initialize(::particle * pparticle)
//{
//
//   auto estatus = ::property_object::initialize(pparticle);
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


bool object::is_task_set() const
{

   return true;

}


//bool object::is_running() const
//{
//
//   return false;
//
//}
//

void object::branch_send(const ::procedure & procedure, manual_reset_happening * phappening)
{

   fork([procedure]()
      {

         procedure();

      });

   phappening->wait(procedure.timeout());

}


//void object::runchild_post_quit(const ::scoped_string & scopedstrTag)
//{
//
//   try
//   {
//
//      auto pelement = running(scopedstrTag);
//
//      if (pelement.is_null())
//      {
//
//         return;
//
//      }
//
//      pelement->destroy();
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
//void object::child_post_quit_and_wait(const ::scoped_string & scopedstrTag, const time& time)
//{
//
//   try
//   {
//
//      auto pelement = running(scopedstrTag);
//
//      if (pelement.is_null())
//      {
//
//         return;
//
//      }
//
//      pelement->destroy();
//
//      string strTag(scopedstrTag);
//
//      predicate_Sleep(time,
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


void object::defer_update_object_id()
{

   if (id().is_empty())
   {

      id() = calc_default_object_id();

   }

}





::atom object::calc_default_object_id() const
{

   string strType = ::type(this).name();

   strType.case_insensitive_begins_eat("class ");

   return strType;

}


//void object::do_request(::request * prequest)
//{
//
//   main();
//
//}


//void object::call_request(::request * prequest)
//{
//
//   on_request(prequest);
//
//}




void object::destruct()
{

}


//void object::system(const ::scoped_string & scopedstrProjectName)
//{
//
//   __UNREFERENCED_PARAMETER(strProjectName);
//
//}


// void object::run()
// {

// }




//void object::on_finish()
//{
//
//   m_bDestroying = true;
//
//   auto estatus = destroy_composites();
//
//   if (estatus == error_pending)
//   {
//
//      //system()->add_pending_finish(this);
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


//void object::set_finish()
//{
//
//// if "this" gets invalid while a member functions of "this" object
//// is running, something is wrong ? or !!!!
//// Yes, someone destroyed it while someone was running a "this" member function.
//// And the caller that called "this" object's member function,
//// wasn't holding proper reference to "this" member.
//// So actually, I cannot make assumption that something is alive
//// running a member of such an object, that doesn't hold proper
//// reference for the time of execution of a function.
//// ::pointer<::object>pobjectHold = this;
//
//   set_finish_bit();
//
//   set_finish_composites();
//
//   return ::success;
//
//}



//
//void object::destroy()
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
//   //m_papplication.release();
//
//   //m_pthread.release();
//
//   //m_papp.release();
//
//   //m_psession.release();
//
//   //m_psystemContext.release();
//
//   //on_finalize();
//
//   if (string(id()).contains("::rx"))
//   {
//
//      informationf("::rx destroy");
//
//   }
//
//   if (string(id()).contains("::interprocess::communication"))
//   {
//
//      informationf("::interprocess::communication destroy");
//
//   }
//
//   //release_references();
//
//   //{
//
//   //   _synchronous_lock synchronouslock(this->synchronization());
//
//   //   if (m_pobjecta)
//   //   {
//
//   //      for (auto& pparticle : *m_pobjecta)
//   //      {
//
//   //         pparticle->on_delete_object(this);
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

      throw ::exception(error_bad_argument);

      return;

   }

   if(pobjectTask == this)
   {

      throw ::exception(error_bad_argument);

      return;

   }

   defer_create_synchronization();

   _synchronous_lock synchronouslockParent1(synchronization());

   if(is_ascendant_task(pobjectTask))
   {

      throw ::exception(error_bad_argument);

      return;

   }

   auto ptaskOldParent = pobjectTask->m_pobjectParentTask;

   _synchronous_lock synchronouslockParent2(ptaskOldParent ? ptaskOldParent->synchronization() : nullptr);

   _synchronous_lock synchronouslock(pobjectTask->synchronization());

   if(ptaskOldParent == this
   && m_pparticleaChildrenTask
   && m_pparticleaChildrenTask->contains(pobjectTask))
   {

      return;

   }

   __defer_construct_new(m_pparticleaChildrenTask);

   string strType = ::type(this).name();

   if (strType.contains("prodevian"))
   {

      informationf("task added to prodevian\n");

   }
   else if (strType.contains("user::thread"))
   {

      informationf("task added to user::thread\n");

   }

   __refdbg_add_referer_for(pobjectTask);

   m_pparticleaChildrenTask->add(pobjectTask);

   pobjectTask->m_pobjectParentTask = this;

   if(::is_set(ptaskOldParent) && ptaskOldParent != this)
   {

      if(::is_set(ptaskOldParent->m_pparticleaChildrenTask))
      {

         ptaskOldParent->m_pparticleaChildrenTask->erase(pobjectTask);

      }

   }

}


void object::erase_task_and_set_task_new_parent(::object* pobjectTask, ::object * pobjectTaskNewParent)
{

   _synchronous_lock synchronouslock(this->synchronization());

   _synchronous_lock synchronouslockObject(pobjectTask->synchronization());

//#if REFERENCING_DEBUGGING
//
//   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);
//
//#endif


   if (!m_pparticleaChildrenTask)
   {

      return;

   }

   if (pobjectTask->m_pobjectParentTask != this)
   {

      throw ::exception(error_bad_argument);

      return;

   }

   string strType = ::type(this).name();

   if (strType.contains("user::thread"))
   {

      informationf("task added to user::thread\n");

   }

   pobjectTask->m_pobjectParentTask = pobjectTaskNewParent;

   if (m_pparticleaChildrenTask->erase(pobjectTask) <= 0)
   {

      informationf("not a child");
      
   }

   kick_idle();

}


void object::transfer_tasks_from(::object* ptask)
{

   if(::is_null(ptask))
   {

      throw ::exception(error_bad_argument);

      return;

   }

   if(ptask == this)
   {

      throw ::exception(error_bad_argument);

      return;

   }

   defer_create_synchronization();

   if(is_ascendant_task(ptask))
   {

      throw ::exception(error_bad_argument);

      return;

   }

   ::cast < ::task > ptaskTask = ptask;

   if(ptaskTask)
   {

      if(ptaskTask->m_procedurea2.has_element())
      {

         ::cast < ::task > ptaskTaskTarget = this;

         if (ptaskTaskTarget)
         {

            _synchronous_lock synchronouslockTask(ptaskTask->synchronization());

            auto procedurea = ::transfer(ptaskTask->m_procedurea2);

            synchronouslockTask.unlock();

            _synchronous_lock synchronouslock(this->synchronization());

            ptaskTaskTarget->m_procedurea2.append(procedurea);

         }

      }

   }

   _synchronous_lock synchronouslockParent2(ptask->synchronization());

   if(!ptask->m_pparticleaChildrenTask || ptask->m_pparticleaChildrenTask->is_empty())
   {

      return;

   }

   __defer_construct_new(m_pparticleaChildrenTask);

   pointer_array < ::object > objectaChildrenTask;

   objectaChildrenTask = *ptask->m_pparticleaChildrenTask;

   *m_pparticleaChildrenTask = objectaChildrenTask;

   ptask->m_pparticleaChildrenTask.release();

   for (auto pobjectTask : objectaChildrenTask)
   {

      _synchronous_lock synchronouslock(pobjectTask->synchronization());

      try
      {

         pobjectTask->m_pobjectParentTask = this;

      }
      catch (...)
      {

      }

   }

}


bool object::is_ascendant_task(::object * ptaskCandidateAscendant) const
{

   try
   {

      auto p = m_pobjectParentTask.m_p;

      while(::is_set(p))
      {

         if(p == ptaskCandidateAscendant)
         {

            return true;

         }
         
         if(p == p->m_pobjectParentTask)
         {
            
            return false;
            
         }

         p = p->m_pobjectParentTask;

      }
      
   }
   catch(...)
   {
      
   }

   return false;

}


bool object::set_children_to_finish_and_check_them_finished()
{

   if (::is_null(m_pparticleaChildrenTask))
   {

      return true;

   }

   if (has_flag(e_flag_checking_children_task))
   {

      if(m_pparticleaChildrenTask->is_empty())
      {

         return true;

      }

      return false;

   }

   _synchronous_lock lock(synchronization());

   if (has_flag(e_flag_checking_children_task))
   {

      if(m_pparticleaChildrenTask->is_empty())
      {

         return true;

      }

      return false;

   }

   auto synchronouslykeepbitCheckingChildrenTask = synchronously_keep_bit(this, m_eflagElement, e_flag_checking_children_task, true, false);

   try
   {

      for (int iChildTask = 0; iChildTask < m_pparticleaChildrenTask->get_size(); iChildTask++)
      {

         auto & ptaskChild = m_pparticleaChildrenTask->element_at(iChildTask);

         if (ptaskChild)
         {

            string strType;

            try
            {

               try
               {

                  strType = ::type(ptaskChild).name();

               }
               catch (...)
               {

               }

               ptaskChild->set_finish();

            }
            catch (...)
            {

            }

         }

      }

      for (int iChildTask = 0; iChildTask < m_pparticleaChildrenTask->get_size(); )
      {

          auto ptaskChild = m_pparticleaChildrenTask->element_at(iChildTask);

          if (!ptaskChild)
          {

             m_pparticleaChildrenTask->erase_at(iChildTask);

          }
          else
          {

             iChildTask++;

          }

      }

   }
   catch (...)
   {

   }

   if (m_pparticleaChildrenTask->is_empty())
   {

      return true;

   }

   return false;

}



//void object::finish()
//{
//
//
//   ::object::finish();
//
//   return ::success;
//
//}
//


void object::destroy_tasks()
{

   while (!set_children_to_finish_and_check_them_finished())
   {

      task_run(100_ms);

   }

}


void object::destroy()
{

   /*auto estatus = */ destroy_tasks();

   /*estatus = */ on_destroy();

   ///*estatus = */ destroy_composites();

   ///*estatus = */ release_references();
   ///

   auto procedureaDestroy = ::transfer(m_procedureaDestroying);

   for (auto& procedure: procedureaDestroy)
   {

      if (procedure)
      {

         procedure();

      }

   }

   auto particleaNotify = ::transfer(m_particleaNotify);

   for (auto pparticle: particleaNotify)
   {

      pparticle->on_notify(this, id_destroy);

   }

   //m_destroyinga.erase_all();


   /*estatus = */
   property_object::destroy();

   //return ::success;

}


void object::on_notify(::particle * pparticle, enum_id eid)
{

   if (eid == id_destroy)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_particleaNotify.erase(pparticle);

   }

}


void object::on_destroy()
{

   //return ::success;

}


void object::set_finish()
{

   property_object::set_finish();

   kick_idle();

   //return ::success;

}


// please refer to object::finish verses/documentation
void object::delete_this()
{

   property_object::delete_this();

}


//void object::destroy_composites()
//{
//
//   ::e_status estatus = ::success;
//
//   string strTypeName = ::type(this).name();
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_pcompositea)
//   {
//
//      for (auto& pelement : *m_pcompositea)
//      {
//
//         synchronouslock.unlock();
//
//         pelement->destroy();
//
//         synchronouslock.lock();
//
//      }
//
//      m_pcompositea.release();
//
//   }
//
//   //return estatus;
//
//}
//
//
//void object::release_references()
//{
//
//   ::e_status estatus = ::success;
//
//   string strTypeName = ::type(this).name();
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   if (m_preferencea)
//   {
//
//      m_preferencea.release();
//
//   }
//
//   //return estatus;
//
//}
//

CLASS_DECL_ACME::pointer < ::mutex >* get_children_mutex();


///// tells if pparticle is dependant of this object or of any dependant objects
//bool object::___is_reference(::particle * pparticle) const
//{
//
//   if (::is_null(pelement))
//   {
//
//      return false;
//
//   }
//
//   _synchronous_lock synchronouslock(get_children_mutex());
//
//   if (!m_preferencea)
//   {
//
//      return false;
//
//   }
//
//   if (m_preferencea->contains(pelement))
//   {
//
//      return true;
//
//   }
//
//   return true;
//
//}
//
//
//bool object::__is_composite(::particle * pparticle) const
//{
//
//   if (::is_null(pelement))
//   {
//
//      return false;
//
//   }
//
//   if (!m_pcompositea)
//   {
//
//      return false;
//
//   }
//
//   if (!m_pcompositea->contains(pelement))
//   {
//
//      return true;
//
//   }
//
//   return false;
//
//}


bool object::__is_child_task(::particle * pparticleTask) const
{

   if (::is_null(pparticleTask))
   {

      return false;

   }

   _synchronous_lock lock(synchronization());

   if (!m_pparticleaChildrenTask)
   {

      return false;

   }

   if (!m_pparticleaChildrenTask->contains(pparticleTask))
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
// ->at simple objects (from finish int_point of impact)...
// ->for objects that doesn't have custom finalization
// finish calls set_finish and destroy.
//
// ->for complex objects (from finish int_point of impact)...
// ->for objects that have custom finalization
// finish wouldn't call *destroy*,
// but only set_finish or custom set_finish.
// "Otherwise, *destroy* could release references (that could be deleted)
// and would be still used during the ideal destroy(-action)."
// So a flag/timer/message that indicates that things should be destroyed/closed/finalized
// should be enough (which triggers the full finalization that would end up calling
// the "final" destroy).
//void object::finish(::property_object* pcontextobjectFinish)
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


//string object::__get_text(const ::scoped_string & scopedstr)
//{
//
//   if (get_app() == nullptr)
//   {
//
//      return ::__get_text(str);
//
//   }
//
//   return get_app()->__get_text(str);
//
//}




//#ifdef __APPLE__
//
//void object::ns_main_post(dispatch_block_t block)
//{
//
//   atomic_increment(&m_countTasksPending);
//
//   ::ns_main_post(^
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


void object::branch(const ::procedure_array& routinea)
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


void object::branch_each(const ::procedure_array& routinea)
{

   for (auto& routine : routinea)
   {

      fork([routine]()
      {

         routine();

      });

   }

}


::task_pointer object::defer_branch(const ::atom& atom, const ::procedure & procedure, enum_priority epriority)
{

   auto ptask = property_set()["thread"][atom].cast < ::task>();

   if(ptask && ptask->is_task_set())
   {

      return ptask;

   }

   ptask = __create_new < task >();

   ptask->m_procedure = procedure;

   property_set()["thread"][atom] = ptask;

   auto ptask2 = property_set()["thread"][atom].cast < ::task>();

   ptask->branch();

   return ptask;

}


::pointer < ::parallelization::queue>object::queue(const ::atom& atomQueue)
{

   defer_create_synchronization();

   _synchronous_lock synchronouslock(this->synchronization());

   if (!m_pqueuemap)
   {

      __construct_new(m_pqueuemap);

   }

   auto& pqueue = (*m_pqueuemap)[atomQueue];

   if (!pqueue)
   {

      __construct_new(pqueue);

      pqueue->m_pobjectFork = this;

   }

   return pqueue;

}


::pointer<task>object::branch_procedure(const ::procedure & procedure, bool bAutoRelease, enum_parallelization eparallelization, const create_task_attributes_t & createtaskattributes)
{

   if (::is_reference_null(procedure))
   {

      throw ::exception(error_failed);

   }

   auto ptask = __create_new < ::task >();

   if (!ptask)
   {

      throw ::exception(error_failed);

   }

   //ptask->m_bAutoRelease = bAutoRelease;

   ptask->m_procedure = procedure;
   
   auto pbase = procedure.m_pbase.m_p;

   ptask->id() = typeid(*pbase).name();

   ptask->branch(eparallelization, createtaskattributes);

   return ptask;

}


::pointer<::task>object::branch_procedure_synchronously(const ::procedure & procedure, bool bAutoRelease, const create_task_attributes_t & createtaskattributes)
{

   if (::is_reference_null(procedure))
   {

      throw ::exception(error_failed);

   }

   auto ptask = __create_new < ::task >();

   if (!ptask)
   {

      throw ::exception(error_failed);

   }

   //ptask->m_bAutoRelease = bAutoRelease;

   ptask->m_procedure = procedure;
   
   auto pbase = procedure.m_pbase.m_p;

   ptask->id() = typeid(*pbase).name();

   ptask->branch_synchronously(createtaskattributes);

   return ptask;

}

//
//::pointer<task>object::branch(enum_parallelization eparallelization, const create_task_attributes & createthreadattributes)
//{
//
//   auto ptask = branch_procedure(this, eparallelization, createthreadattributes);
//
//   return ptask;
//
//}

//
//::pointer<task>object::branch_synchronously(const create_task_attributes & createthreadattributes)
//{
//
//   auto ptask = branch_procedure_synchronously(this, createthreadattributes);
//
//   return ptask;
//
//}


::task_pointer object::run_procedure(enum_synchronicity esynchronicity, const ::procedure & procedure)
{

   if (esynchronicity == e_synchronicity_synchronous)
   {

      procedure();

      return nullptr;

   }
   else
   {

      return branch_procedure(procedure);

   }

}


void object::handle_exception(const ::exception& e)
{

   if (e.estatus().is_exit_status())
   {

      throw e;

   }
   else if (e.estatus() == error_library_not_found)
   {

      auto pmessagebox = __initialize_new ::message_box(e.m_strMessage);

      pmessagebox->sync();

   }

}


void object::top_handle_exception(const ::exception& e)
{

   if (e.estatus().is_exit_status())
   {

      system()->process_exit_status(this, e.estatus());

   }

}


//void object::process_exit_status(const ::e_status & estatus)
//{
//
//   if (estatus == error_exit_system)
//   {
//
//      system()->finish();
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


void object::process_exception(const ::exception& e)
{

   if (e.m_bHandled)
   {

      if (!e.m_bContinue)
      {

         throw e;

         //return false;

      }

   }

   //return true;

}


//::collection::index object::task_add(::task * ptask)
//{
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   return get_meta()->task_add(this, ptask);
//
//}


void object::task_erase(::task* ptask)
{

   //_synchronous_lock synchronouslock(this->synchronization());

   //if (m_pmeta)
   //{

   //   m_pmeta->task_erase(this, ptask);

   //}


   //void object::task_erase(::task * ptask)
   //{

   try
   {

      string strThreadThis = ::type(this).name();

      string strThreadChild = ::type(ptask).name();

      _synchronous_lock synchronouslock(this->synchronization());

      if (::is_null(ptask))
      {

         throw ::exception(error_bad_argument);

      }

      //_synchronous_lock slChild(ptask->synchronization());

      //if (!m_pcompositea->contains(ptask) && ptask->thread_parent() != this)
      //{

      //   throw ::exception(error_bad_argument, "thread is no parent-child releationship between the threads");

      //}

      //ptask->m_pobjectParent.release();

      //auto ptaska = _task_array();

      //if (ptaska)
      //{

      //m_pcompositea->erase(ptask);

      //}

      //if (finish_bit() && (!m_ptaska || ptaska->is_empty()))
      if (has_finishing_flag())
      {

         if (strThreadThis == "app_veriwell_keyboard::application")
         {

            informationf("app_veriwell_keyboard::application");

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
void object::sleep(const class time & time)
{

   auto ptask = ::get_task();

   if (::is_set(ptask))
   {


      ::pointer<manual_reset_happening>phappening;

      {

         _synchronous_lock synchronouslock(ptask->synchronization());

         if (ptask->m_pevSleep.is_null())
         {

            ptask->m_pevSleep = __allocate manual_reset_happening();

            ptask->m_pevSleep->reset_happening();

         }

         phappening = ptask->m_pevSleep;

      }

      if (system() && system()->has_finishing_flag())
      {

         throw ::exception(error_exit_system);

      }

      //if (m_psession && m_psession->finish_bit())
      //{

      //   return error_exit_session;

      //}

      //if (m_papp && m_papp->finish_bit())
      //{

      //   return error_exit_application;

      //}

      if (::is_set(phappening))
      {

         phappening->wait(time);

         phappening.release();

         return;
         //return ::task_get_run();

      }

   }

   auto start = ::time::now();

   while (true)
   {

      auto waitStep = minimum(time - start.elapsed(), 100_ms);

      if (waitStep <= 0_s)
      {

         break;

      }

      if (system() && system()->has_finishing_flag())
      {

         throw ::exception(error_exit_system);

      }

      //if (m_psession && m_psession->finish_bit())
      //{

      //   return error_exit_session;

      //}

      //if (m_papp && m_papp->finish_bit())
      //{

      //   return error_exit_application;

      //}


      sleep(waitStep);

   }

   // return ::success;

}



//void object::task_erase_all()
//{
//
//   /*_synchronous_lock synchronouslock(this->synchronization());
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
//   _synchronous_lock synchronouslock(this->synchronization());
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
//   _synchronous_lock synchronouslock(this->synchronization());
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
//   _synchronous_lock synchronouslock(this->synchronization());
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


//::pointer<thread>object::start(
//   ::particle * pparticle,
//   ::enum_priority epriority = e_priority_normal,
//   unsigned int nStackSize = 0,
//   unsigned int dwCreateFlags = 0)
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

   //::topic topic(this, (::iptr)pmessage->m_wparam);

   //topic.m_payload = (::particle*)(::iptr)pmessage->m_lparam;

   //process(&topic);

}



// //void receiver::install_message_routing(::channel * pchannel)
// void object::install_message_routing(::channel* pchannel)
// {
//
//    //pchannel->add_handler(e_message_system_update, this, &::object::_001OnUpdate);
//
// }


//::particle_pointerobject::running(const ::scoped_string & scopedstrTag) const
//{
//
//   //if (m_pcompositea)
//   //{
//
//   //   auto pparticle = ::parallelization::array::is_running(*m_pcompositea, pszTag);
//
//   //   if (pparticle)
//   //   {
//
//   //      return pparticle;
//
//
//   //   }
//
//   //}
//
//   //if (m_preferencea)
//   //{
//
//   //   auto pparticle = ::parallelization::array::is_running(*m_preferencea, pszTag);
//
//   //   if (pparticle)
//   //   {
//
//   //      return pparticle;
//
//   //   }
//
//   //}
//
//   return nullptr;
//
//}


//void object::add_update_notification(const ::atom & atom, bool bCreate)
//{
//
//   auto pproperty = fetch_property(atom, bCreate);
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


//void object::add_update_notification(const ::atom & atom, ::particle * pparticle)
//{
//
//   if (::is_null(pparticle))
//   {
//
//      return ::error_failed;
//
//   }
//
//   if (!pparticle->m_ppropertyset)
//   {
//
//      return ::error_failed;
//
//   }
//
//   auto pproperty = pparticle->m_ppropertyset->find(atom);
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
   
   if(m_papplication == this)
   {
      
      return nullptr;
      
   }

   return m_papplication;

}

//::pointer<::handle::ini>object::appini()
//{
//
//   return __allocate ::handle::ini (         auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->localconfig()));
//
//}



//
//
//
//
//





struct context_object_test_struct :
   virtual public object
{

   context_object_test_struct(::particle* p)
   {


   }

   virtual ~context_object_test_struct()
   {

   }

   unsigned char m_ucha[1024];

};

//void debug_context_object(::object* pparticle)
//{
//
//   auto p1 = __allocate struct context_object_test_struct (pparticle);
//
//   auto p2 = __allocate struct context_object_test_struct (pparticle);
//
//   p2 = p1;
//
//}
//
//
//CLASS_DECL_ACME void object_on_add_composite(const element* pusermessage)
//{
//
//   string strType = ::type(pusermessage).name();
//
//   if (strType.case_insensitive_contains("user::thread"))
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


void call_sync(const ::procedure_array& methoda)
{

   try
   {

      for (auto& method : methoda)
      {

         //try
         //{

            /*auto estatus =*/ method();

            //if (__no_continue(estatus))
            //{

            //   return estatus;

            //}

         //}
         //catch (const ::exception& e)
         //{

         //   if (__no_continue(e.m_estatus))
         //   {

         //      return e.m_estatus;

         //   }

         //}
         //catch (...)
         //{

         //   //break;

         //}

      }
   }
   catch (...)
   {

   }

   //return ::success;

}








//string object::get_text(const ::payload& payload, const ::atom& atom)
//{
//
//   if (payload.has_property(atom) && payload[atom].has_character())
//   {
//
//      return payload[atom];
//
//   }
//
//   return "";
//
//   //string str = file()->as_string(payload);
//
//   //if (str.has_character())
//   //{
//
//   //   return str;
//
//   //}
//
//   //auto strExtension = payload.get_file_path().extension();
//
//   //if (strExtension == as_string(atom))
//   //{
//
//   //   return "";
//
//   //}
//
//   //return payload.get_string();
//
//}


//pointer< ::extended::sequence < ::conversation > > object::message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox)
//{
//
//   auto psystem = system();
//
//   auto psequence = psystem->message_box(puserinteraction, strMessage, strTitle, emessagebox);
//
//   return psequence;
//
//}


//void object::message_box_timeout(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const class time & timeTimeout, const ::e_message_box & emessagebox, const ::future & future)
//{
//
//   ::e_status estatus = error_failed;
//
//   //if (::is_null(get_session()) || ::is_null(get_session()->userex()))
//   //{
//
//   //   estatus = get_session()->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, timeTimeout, emessagebox, callback);
//
//   //}
//
//   if (!estatus)
//   {
//
////      estatus = ::auto pmessagebox = __initialize_new ::message_box(scopedstrMessage, pszTitle, emessagebox, process);

//pmessagebox->sync();
//
//   }
//
//   return estatus;
//
//}


#ifdef _DEBUG


//void object::set_context(::handler_context* pcontext)
//{
//
//   m_papplication.reset(pcontext);
//
//}
//
//
//void object::set_context_thread(::thread* pthread)
//{
//
//   m_pthread.reset(pthread);
//
//}
//
//
//void object::set_context_app(::apex::application* pappContext)
//{
//
//   m_papp.reset(pappContext);
//
//}
//
//
//void object::set_context_session(::apex::session* psessionContext)
//{
//
//   m_psession.reset(psessionContext);
//
//}
//
//
////void object::set_context_system(::apex::system* psystemContext)
////{
////
////   m_psystemContext.reset(psystemContext);
////
////}
//

#endif


::particle * object::get_taskpool_container()
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
//long long object::increment_reference_count()
//{
//
//   return property_object::increment_reference_count();
//
//}
//
//
//long long object::decrement_reference_count()
//{
//
//   return property_object::decrement_reference_count();
//
//}
//
//
//long long object::release()
//{
//
//   return property_object::release();
//
//}
//
//
//#else
//
//
//long long object::increment_reference_count()
//{
//
//   return property_object::increment_reference_count();
//
//}
//
//
//long long object::decrement_reference_count()
//{
//
//   return property_object::decrement_reference_count();
//
//}
//
//
//long long object::release()
//{
//
//   return property_object::release();
//
//}
//
//
//#endif


//::apex::system* objectacmesystem() const
//{
//
//
//}
//
//
//void object::process_exit_status(const ::e_status & estatus)
//{
//
//
//}
//
//
//::application* object::_get_application()
//{
//
//   return m_papp;
//
//}


//inline ::application* object::application() { return m_papp; }


//template < typename BASE_TYPE >
//::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);

//
//void object::add_procedure(const ::atom& idRoutine, const ::procedure & procedure)
//{
//
//
//}

//
//void object::add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource)
//{
//
//
//}

//
procedure_array object::procedure_array(const ::atom& atomProcedure)
{

   return get_meta()->m_mapRoutine[atomProcedure];

}

//
//void object::call_routine(const ::atom& idRoutine)
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
//void object::sleep(const class time & time)
//{
//
//   return ::success;
//
//}


//template < typename BASE_TYPE >
//void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);


void object::initialize(::particle * pparticle)
{
   
   auto estatus = ::success;

#if OBJECT_TYPE_COUNTER

   if (!m_eobject.is(e_object_object_type_counter))
   {

      m_eobject += e_object_object_type_counter;

      OBJECT_TYPE_COUNTER_INCREMENT;

   }

#endif

   //#if REFERENCING_DEBUGGING
   //
   //   string strType = ::type(this).name();
   //
   //   if (strType.case_insensitive_contains("session"))
   //   {
   //
   //      if (m_pobjrefdbg->m_iStep == 39)
   //      {
   //
   //         informationf("session");
   //
   //      }
   //
   //   }
   //
   //#endif


   ::property_object::initialize(pparticle);

//   if (!system())
//   {
//
//      system() = pparticle->system();
//
//   }
//
//   if (!m_papplication)
//   {
//
//      m_papplication = pparticle->m_papplication;
//
//   }
//
//   /*estatus =*/ on_initialize_particle();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //if (!m_papp)
   //{

   //   m_papp = pparticle->m_papp;

   //}

   //if (!m_psession)
   //{

   //   m_psession = pparticle->m_psession;

   //}

   //if (!psystem)
   //{

   //   set_context_system(::apex::get_system(pparticle) REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

   //}

   //if (!get_context())
   //{

   //   if (m_papp)
   //   {

   //      m_papplication = m_papp;

   //   }
   //   else if (m_psession)
   //   {

   //      m_papplication = m_psession;

   //   }
   //   else if (system())
   //   {

   //      m_papplication = system();

   //   }

   //}

   //return estatus;


   if(::is_null(m_pparticleContext))
   {

      m_pparticleContext = this->application();

   }

}


//void object::on_initialize_particle()
//{
//
//   return ::success;
//
//}


//void object::destroy()
//{
//
//
//}


//::thread_pointer object::launch(const ::procedure & procedure)
//{
//
//   auto pthread = __create_new < ::thread >();
//
//   pthread->m_pelement = routine;
//
//   pthread->id() = ::type(pthread->m_pelement).name();
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

//void object::set_topic_text(const ::scoped_string & scopedstr)
//{
//
//
//}

//void create_object_meta();

//inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

//inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

//inline ::handler_context* object::get_context() const { return m_papplication; }

//inline ::thread* object::get_thread() const { return m_pthread; }

//inline ::application* object::get_app() const { return m_papp; }

//inline ::apex::session* object::get_session() const { return m_psession; }

//::apex::system * psystem const { return m_psystemContext; }

//::object * get_context_user() const { return m_puserContext; }

//inline ::application * application() const { return m_papp; }

//string object::get_text(const ::payload& payload, const ::atom& atom)
//{
//
//   return "";
//
//}
////
//#ifdef _DEBUG
//    void set_context(::handler_context* pcontext);
//    void set_context_thread(::thread* pthread);
//    void set_context_app(::apex::application* pappContext);
//    void set_context_session(::apex::session* psessionContext);
//   // void set_context_system(::apex::system* psystemContext);
//   // void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::handler_context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::apex::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   // void set_object(::particle * pparticle) 


   //inline void defer_set_object(::particle * pparticle);

//void object::call()
//{
//
//   run();
//
//}


//inline long long get_ref_count()
//{

//   return m_countReference;

//}


// ::user::interaction_base* get_user_interaction_host();
// ::user::interaction * get_host_user_interaction();


//void object::dev_log(const ::scoped_string & scopedstr) const
//{
//
//
//}


::object& object::operator = (const ::payload& payload)
{

   return *this;

}




//static unsigned int s_thread_proc(void* p);


// void to_string(const string_exchange & str) const 

//::image::image_pointer create_image();
//::image::image_pointer create_image(const ::int_size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

//::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
//::image::image_pointer matter_image(const ::scoped_string & scopedstrMatter, bool bCache = true, bool bSync = true);

//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__øcreate();

//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__id_create(const ::atom& atom);

//template < typename TYPE >
//inline ::pointer<TYPE>__create_new();

//inline void __øconstruct(::pointer<::image::image>& pimage);

//inline void __øconstruct(::pointer<::image::image>& pimage, ::image::image *pimageSource);

//inline void __defer_construct(::pointer<::image::image>& pimage) { return !pimage ? __øconstruct(pimage) : void(::success); }

// for composition (ownership)

//template < typename BASE_TYPE >
//inline void __øconstruct(::pointer<BASE_TYPE> pusermessage);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __øconstruct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __øconstruct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource);

//template < typename BASE_TYPE >
//inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

//template < typename BASE_TYPE >
//inline void __raw_construct(::pointer<BASE_TYPE> pusermessage);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource);

//template < typename TYPE >
//inline void __raw_construct_new(::pointer<TYPE> ptype);

//template < typename TYPE >
//inline void __construct_new(::pointer<TYPE> ptype);




//template < typename BASE_TYPE >
//inline void __defer_construct(::pointer<BASE_TYPE> pusermessage) { return !pusermessage ? __øconstruct(pusermessage) : void(::success); }

//template < typename BASE_TYPE >
//inline void __defer_id_compose(::pointer<BASE_TYPE> pusermessage, const ::atom& atom) { return !pusermessage ? __id_construct(pusermessage) : void(::success); }

//template < typename TYPE >
//inline void __defer_raw_compose_new(::pointer<TYPE> ptype) { return !ptype ? __raw_construct_new(ptype) : void(::success); }

//template < typename TYPE >
//inline void __defer_construct_new(::pointer<TYPE> ptype) { return !ptype ? __construct_new(ptype) : void(::success); }




//template < typename BASE_TYPE >
//inline void __øconstruct(::pointer<BASE_TYPE> pusermessage);

//template < typename BASE_TYPE >
//inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

//template < typename TYPE >
//inline void __construct_new(::pointer<TYPE> pusermessage);

//template < typename BASE_TYPE >
//inline void __release(::pointer<BASE_TYPE> pcomposite);

//template < typename BASE_TYPE >
//inline void __release(::pointer<BASE_TYPE> preference);

//template < typename SOURCE >
//inline void release_reference(::pointer<SOURCE> psource);


// void add_composite(::particle * pparticle)
// void add_reference(::particle * pparticle)


// void release_composite2(::particle * pparticle)
// void finalize_composite(::particle * pparticle)
// void release_reference(::particle * pparticle)


//template < typename BASE_TYPE >
//inline void add_composite(::pointer<BASE_TYPE> pcomposite);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __refer(::pointer<BASE_TYPE> preference, const SOURCE* psource);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource);

//template < typename BASE_TYPE, typename SOURCE >
//inline void __refer(::pointer<BASE_TYPE> preference, const ::primitive::member < SOURCE >& psource);

//template < typename SOURCE >
//inline void add_reference(SOURCE* psource);

//template < typename SOURCE >
//inline void add_reference(::pointer<SOURCE> psource);

//template < typename SOURCE >
//inline void add_reference(::pointer<SOURCE> psource);



//void object::destruct()
//{
//
//
//}

//void object::system(const ::scoped_string & scopedstrProjectName)
//{
//
//}
//
//void object::enable_application_events(bool bEnable)
//{
//
//   return ::success;
//
//}

//void object::handle_exception(const ::exception& e)
//{
//
//   return ::success;
//
//}
//
//void object::top_handle_exception(const ::exception& e)
//{
//
//   return ::success;
//
//}


//void object::process_exception(const ::exception& e)
//{
//
//   return ::success;
//
//}


//::property_object* object::parent_property_set_holder() const
//{
//
//   if (m_papp && m_papp.m_p != this)
//   {
//
//      return m_papp.m_p;
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
//   if (system() && (::property_object*)system() != (::property_object*)this)
//   {
//
//      return system();
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


//void object::child_post_quit(const ::scoped_string & scopedstrTag)
//{
//
//
//}


//void object::child_post_quit_and_wait(const ::scoped_string & scopedstrTag, const time& time)
//{
//
//
//}


//void object::finish(::property_object* pcontextobjectFinish)
//{
//
//   return ::success;
//
//}

//void object::set_finish(::property_object* pcontextobjectFinish)
//{
//
//   return ::success;
//
//}

//void object::set_finish_composites(::property_object* pcontextobjectFinish)
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


//::atom object::calc_default_object_id() const
//{
//
//   return ::atom();
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


//void object::request_file(const ::payload& payloadFile)
//{
//
//   return ::success;
//
//}


//void object::request_file(const ::payload& payloadFile, ::payload varQuery)
//{
//
//   return ::success;
//
//}


//void object::request(arguments arguments)
//{
//
//   return ::success;
//
//}


//void object::do_request(::create* pcreate)
//{
//
//   return ::success;
//
//}


//pointer< ::extended::future < ::conversation > >  object::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox)
//{
//
//   return nullptr;
//
//}
//{
//
//   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

//}


// void message_box_timeout(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
//{

//   return message_box_timeout(nullptr, pszMessage, pszTitle, timeTimeout, emessagebox, process);

//}

// void message_box(::user::interaction_base* puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
// void message_box_timeout(::user::interaction_base* puserinteractionOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());

//void object::release_references()
//{
//
//}

//::pointer<::element>object::running(const ::scoped_string & scopedstrTag) const
//{
//
//   return nullptr;
//
//}

//bool object::___is_reference(::particle * pparticle) const
//{
//
//   return false;
//
//}

//bool object::__is_composite(::particle * pparticle) const
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
//void object::call_request(::create* pcreate)
//{
//
//   return ::success;
//
//}

//// former user::server
// ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
//void object::on_request(::create* pcreate)
//{
//
//
//}

// ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
// ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
// ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile);
// ::user::document* create_subdocument(::user::impact_data* pimpactdata);

//
//void object::run()
//{
//
//   return ::success;
//
//}


//string object::lstr(const ::atom& atom, const ::scoped_string & scopedstrDefault)
//{
//
//   return "";
//
//}
//
//
//string object::__get_text(const ::scoped_string & scopedstr)
//{
//
//   return "";
//
//}



//template < typename PRED >
//::image::image_pointer get_image(const ::payload & payloadFile, unsigned long long uTrait, PRED pred);

// ::image::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
// ::image::image_pointer load_matter_image(const ::scoped_string & scopedstrMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
// ::image::image_pointer load_matter_icon(string_array & straMatter, const ::scoped_string & scopedstrIcon);
// ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
// ::image::image_pointer load_thumbnail(const ::file::path & path);
// ::image::image_pointer load_dib(const ::file::path & pathDib);



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
//void object::single_fork(const ::procedure_array& routinea)
//{
//
//
//}
//

//void object::multiple_fork(const ::procedure_array& routinea)
//{
//
//
//}

//   using property_object::defer_fork;

  /* template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread, const ::procedure & procedure)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }*/


   //inline void object::defer_fork(::thread_pointer& pthread, const ::procedure & procedure);


   //template < typename THREAD >
   //inline ::pointer<THREAD> start(::pointer<THREAD> pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer lcontext_object::aunch(const ::procedure & procedure);


   //template < typename METHOD >
   //inline ::task_pointer object::opt_fork(const ::procedure & procedure)
   //{

   //   auto ptask = ::get_task();

   //   _synchronous_lock synchronouslock(ptask->synchronization());

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

   //::thread_pointer object::begin(::enum_priority epriority, unsigned int nStackSize, unsigned int dwCreateFlags)
   //{

   //   return nullptr;

   //}
   //::thread_pointer defer_fork(const ::scoped_string & scopedstrThread = "");

//#ifdef __APPLE__
//    void ns_main_post(dispatch_block_t block);
//#endif

   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());


   // void to_string(string & str) const 


//::file_pointer object::get_file(const ::payload& payloadFile, ::file::e_open eopen)
//{
//
//   return nullptr;
//
//}

//inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary);
//inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



//void add_update_notification(property * pproperty);
//void add_update_notification(const ::atom & atom, bool bCreate = true);
//void property_notify(const ::atom & atom, ::matter * pmatter);


//   inline void format_topic_text(const ::scoped_string & scopedstr, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(scopedstr, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const ::scoped_string & scopedstr, va_list valist)
//   {
//
//      string str;
//      str.formatf_arguments(scopedstr, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(void (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
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
   //void __øconstruct(::thread_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //void __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::thread_pointer __start_thread(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


//matter* object::get_taskpool_container()
//{
//
//   return nullptr;
//
//}



//::task_pointer object::run_procedure(bool bSync, const ::procedure & procedure)
//{
//
//   if (bSync)
//   {
//
//
//
//
//   }
//
//
//    //ptask = __allocate predicate_task < PRED > (pparticle, pred);
////
////   ptask->branch();
////
////   return ptask;
//   return ::predicate_run(this, bSync, procedure);
//
//}



//::platform::application * object::get_app() const
//{
//
//   //return m_papplication && m_papplication->m_papplication ? m_papplication->m_papplication : nullptr;
//   
//   return ((::object *)this)->::matter::application();
//
//}
//
//
//
//::platform::session * object::get_session() const
//{
//
//   return m_papplication ? m_papplication->m_psession : nullptr;
//
//}


void object::defer_branch(::task_pointer & ptask, const ::procedure & procedure)
{

   if (::is_null(ptask))
   {

      __øconstruct(ptask);

      //ptask->m_bAutoRelease = true;

      ::pointer < ::object > pobjectHoldThis = this;

      ptask->m_procedure = [procedure, &ptask, pobjectHoldThis]()
      {

         try
         {

            procedure();

         }
         catch (...)
         {

         }

         ptask = nullptr;

      };

      ptask->branch();

   }

}


::pointer<task>object::fork(const ::procedure& procedure)
{

   return fork(procedure, {});

}


::pointer<task>object::fork(const ::procedure & procedure, const create_task_attributes & createthreadattributes)
{

   auto ptask = this->branch_procedure(procedure, true, e_parallelization_asynchronous, createthreadattributes);

   if (!ptask)
   {

      return ptask;

   }

   return ptask;

}


