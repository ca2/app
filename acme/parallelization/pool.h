#pragma once


//#include "acme/prototype/prototype/object.h"


class CLASS_DECL_ACME task_pool :
   virtual public object
{
protected:


   ::pointer<::task>& task(const ::atom & atom) { return m_map[atom]; }


public:


   atom_map_base < ::pointer<::task >>  m_map;


   task_pool();
   ~task_pool() override;


   virtual ::pointer<::task>defer_branch(const ::atom& atom, const ::procedure & procedure);


   virtual void set_timer(enum_timer etimer, const class time & time);
   virtual void _timer_task(enum_timer etimer, const class time & time);
   virtual void operator()(enum_timer etimer);



};



