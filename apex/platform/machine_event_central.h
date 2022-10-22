#pragma once


#include "apex/parallelization/thread.h"


class CLASS_DECL_APEX machine_event_central :
   virtual public thread
{
public:


   ::pointer<machine_event>      m_pmachineevent;
   bool                          m_bInitialized;


   machine_event_central();
   ~machine_event_central() override;


   void read(machine_event_data * pdata);
   void write(machine_event_data * pdata);

   virtual void initialize(::object * pobject) override;
   virtual void run() override;

   bool is_close_application();

   //void command(::pointer<::xml::node>pnodeCommand);

};


