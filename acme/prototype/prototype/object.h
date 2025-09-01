// Some cleanup by camilo on 2024-11-08 10:21 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/property_object.h"
#include "acme/handler/handler_context.h"
#include "acme/parallelization/create_task_attributes.h"


class CLASS_DECL_ACME object :
   virtual public property_object,
   virtual public handler_context
{
   
protected:


   ::pointer < ::object >                                               m_pobjectParentTask;
   ::pointer < ::pointer_array < ::particle > >                         m_pparticleaChildrenTask;
   ::pointer < ::map_particle < atom_map_base < ::pointer < ::parallelization::queue > > > >    m_pqueuemap;


   ::procedure_array                                                    m_procedureaDestroying;
   ::comparable_array< ::particle * >                                   m_particleaNotify;


public:


   ::particle *                  m_pparticleContext;

   ::object_meta *               m_pmeta;


   object(const ::e_flag & eflag = e_flag_none, const ::e_status & estatus = undefined) :
      property_object(eflag, estatus),
      m_pmeta(nullptr) 
   {
      
      m_pobjectParentTask = nullptr;
      m_pparticleContext = nullptr;

   }
   ~object() override;



#ifdef _DEBUG


   virtual long long increment_reference_count() override;
   virtual long long decrement_reference_count() override;
   virtual long long release() override;


#else


   virtual long long increment_reference_count();
   virtual long long decrement_reference_count();
   virtual long long release();


#endif


   ::procedure_array & destroyinga() { return m_procedureaDestroying; }
   ::comparable_array< ::particle * > & notifya() { return m_particleaNotify; }
   void on_notify(::particle * pparticle, enum_id eid) override;



   template < typename BASE_TYPE >
   ::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);


   virtual void add_procedure(const ::atom& idRoutine, const ::procedure & procedure);


   virtual void add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource);


   virtual ::procedure_array procedure_array(const ::atom& idRoutine);

   
   virtual void call_routine2(const ::procedure & procedure);


   virtual void call_procedures(const ::atom& atom);


   virtual void post_procedures(const ::atom& atom);


   virtual void send_procedures(const ::atom& atom);
  

   //inline ::payload context_value(const ::payload& payload);


   virtual ::text::text __text(const ::atom& atom);


   virtual void task_erase(::task* ptask) override;


   virtual void sleep(const class ::time& time);


   template < typename BASE_TYPE >
   void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);

   
   virtual void initialize(::particle * pparticle) override;
   virtual void set_finish() override;
   //virtual void destroy() override;

   virtual void add_task(::object* pobjectTask);
   virtual void erase_task_and_set_task_new_parent(::object* pobjectTask, ::object * pobjectTaskNewParent);
   virtual void transfer_tasks_from(::object * ptask);
   virtual bool is_ascendant_task(::object * ptaskCandidateAscendant) const;

//   void destroy() override;

   //virtual void set_finish();


   virtual bool is_thread_class() const override;
   virtual bool task_get_run() const;
   virtual bool is_task_set2() const;
   //virtual void child_post_quit(const ::scoped_string & scopedstrTag);
   //virtual void child_post_quit_and_wait(const ::scoped_string & scopedstrTag, const time& time);

   virtual void branch_send(const ::procedure & procedure, manual_reset_happening * phappening);

   //void destroy() override;

   //virtual void finish(::property_object* pcontextobjectRootFinishingInitiator = nullptr) override;
   //virtual void set_finish(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual void set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual void on_finish() override;

   virtual bool set_children_to_finish_and_check_them_finished();

   void destroy() override;

   virtual void on_destroy();

   virtual void destroy_tasks();


   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }


   ::extended_topic_pointer create_extended_topic(const ::atom & atom) override;

   virtual void dev_log(const ::scoped_string & scopedstr);


   virtual void delete_this() override;

   virtual void destruct();

   virtual void handle_exception(const ::exception& e) override;

   virtual void top_handle_exception(const ::exception& e);

   virtual void process_exception(const ::exception& e);


   ::property_object* parent_property_set_holder() const override;

   //void copy_from(const object& o);


   virtual string get_tag() const;


   virtual void defer_update_object_id();
   virtual ::atom calc_default_object_id() const;


   //void install_message_routing(::channel* pchannel) override;

   void message_receiver_destruct();

   void _001OnUpdate(::message::message* pmessage);

   //virtual void request_file(const ::payload& payloadFile);

   //virtual void request_file(const ::payload& payloadFile, ::payload varQuery);

   //virtual void request(arguments arguments);

   //virtual void do_request(::create* pcreate);

   //virtual void do_request(::request * prequest);

   //virtual pointer< ::extended::sequence < ::conversation > >  message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual void message_box_timeout(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::future & future = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, timeTimeout, emessagebox, process);

   //}

   //virtual void message_box(::user::interaction_base* puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::future & future = ::future());
   //virtual void message_box_timeout(::user::interaction_base* puserinteractionOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class ::time& timeTimeout = ::time::infinite(), const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::future & future = ::future());

   //virtual void release_references();

   //virtual ::pointer<::element>running(const ::scoped_string & scopedstrTag) const;

   //virtual bool ___is_reference(::particle * pparticle) const;

   //virtual bool __is_composite(::particle * pparticle) const;

   virtual bool __is_child_task(::particle * pparticle) const;



   bool IsSerializable() const;

   void branch(const ::procedure_array& routinea);
   void branch_each(const ::procedure_array& routinea);

   template < typename TASK >
   inline ::pointer<TASK>& defer_branch(::pointer<TASK> ptask, const ::procedure & procedure)
   {

      if (ptask && ptask->is_running())
      {

         return ptask;

      }

      ødefer_construct_new(ptask);

      ptask->m_procedure = procedure;

      ptask->branch();

      return ptask;

   }


   template < typename THREAD >
   inline ::pointer<THREAD> defer_branch(::pointer<THREAD>pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }


   void defer_branch(::task_pointer& ptask, const ::procedure & procedure);

   ::pointer<task> fork(const ::procedure & procedure);

   ::pointer<task> fork(const ::procedure & procedure, const create_task_attributes& createtaskattributes);

   virtual ::pointer < ::parallelization::queue> queue(const ::atom & atomQueue);

   virtual ::pointer<::task> branch_procedure(const ::procedure& procedure, bool bAutoDelete = true, enum_parallelization eparallelization = e_parallelization_asynchronous, const create_task_attributes_t & createtaskattributes = {});

   virtual ::pointer<::task> branch_procedure_synchronously(const ::procedure& procedure, bool bAutoDelete = true, const create_task_attributes_t& createtaskattributes = {});

   virtual ::task_pointer run_procedure(enum_synchronicity esynchronicity, const ::procedure & procedure);

   template < typename TYPE >
   ::task_pointer branch_below_normal(void (TYPE::* pfn)())
   {

      return branch(pfn, ::e_priority_below_normal);

   }


   ::task_pointer defer_branch(const ::atom& atom, const ::procedure & procedure, enum_priority epriority = e_priority_normal);

   virtual ::particle * get_taskpool_container() override;

   ::object& operator = (const ::payload& payload);



   string as_string() const override;

   void single_fork(const ::procedure_array& routinea);
   void multiple_fork(const ::procedure_array& routinea);


   template < primitive_function FUNCTION >
      void hold_signal_function(::data::signal<FUNCTION> * psignal, FUNCTION f);


};




#define __make_identifier(PART1, PART2) PART1 ## PART2


#define __defer_branch(procedure) defer_branch(m_p ## procedure, [this](){procedure();})






#define __PROPERTIES(xxx) \
class __ ## xxx ## _properties : \
   public ::property_set \
{ \
public: \


#define __PROPERTY(type, name, ID) type & name = reference(ID)



