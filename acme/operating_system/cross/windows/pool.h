#pragma once


class CLASS_DECL_ACME task_pool :
   virtual public ::object
{
protected:


   task_pointer & task(const ::atom & atom) { return m_map[atom]; }


public:


   id_map < ::task_pointer >   m_map;


   task_pool();
   virtual ~task_pool();


   virtual ::task_pointer & defer_start(const ::atom& atom, const ::routine & routine);


   virtual void start_clock(enum_timer etimer, const duration & duration);
   virtual void _task_clock(enum_timer etimer, const duration & duration);
   virtual void on_clock(enum_timer etimer);



};



