#pragma once


class CLASS_DECL_APEX machine_event :
   virtual public ::matter
{
public:


   bool              m_bInitialized;


   machine_event();
   virtual ~machine_event();


   virtual ::e_status initialize(::object * pobject) override;

   bool read(machine_event_data * pdata);
   bool write(machine_event_data * pdata);

};



