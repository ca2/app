#pragma once


//template < typename TASK_POINTER >
class CLASS_DECL_ACME task_pool :
   virtual public ::context_object
{
protected:


   task_pointer& task(const ::id& id) { return m_map[id]; }


public:


   id_map < ::task_pointer >   m_map;


   task_pool();
   virtual ~task_pool();


   virtual ::task_pointer & defer_start(const ::id& id, const ::procedure & procedure);


   virtual void start_clock(enum_clock eclock, const duration & duration);
   virtual void _task_clock(enum_clock eclock, const duration & duration);
   virtual void on_clock(enum_clock eclock);



};



