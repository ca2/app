#pragma once


class CLASS_DECL_APEX machine_event_central :
   virtual public thread
{
public:


   __pointer(machine_event)      m_pmachineevent;
   bool                          m_bInitialized;


   machine_event_central();
   virtual ~machine_event_central();


   void read(machine_event_data * pdata);
   void write(machine_event_data * pdata);

   virtual ::e_status initialize(::object * pobject) override;
   virtual ::e_status     run() override;

   bool is_close_application();

   //void command(__pointer(::xml::node) pnodeCommand);

};


