#pragma once


//#include "acid/primitive/primitive/object.h"


class CLASS_DECL_ACID task_pool :
   virtual public object
{
protected:


   ::pointer<::task>& task(const ::atom & atom) { return m_map[atom]; }


public:


   atom_map < ::pointer<::task >>  m_map;


   task_pool();
   virtual ~task_pool();


   virtual ::pointer<::task>defer_branch(const ::atom& atom, const ::procedure & procedure);


   virtual void set_timer(enum_timer etimer, const class time & time);
   virtual void _timer_task(enum_timer etimer, const class time & time);
   virtual void on_timer(enum_timer etimer);



};



