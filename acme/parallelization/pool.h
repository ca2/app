#pragma once


class CLASS_DECL_ACME task_pool :
   virtual public object
{
protected:


   __composite(::task) & task(const ::atom & atom) { return m_map[atom]; }


public:


   id_map < __composite(::task) >   m_map;


   task_pool();
   virtual ~task_pool();


   virtual __composite(::task) defer_branch(const ::atom& atom, const ::routine & routine);


   virtual void set_timer(enum_timer etimer, const duration & duration);
   virtual void _timer_task(enum_timer etimer, const duration & duration);
   virtual void on_timer(enum_timer etimer);



};



