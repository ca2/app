#pragma once


class CLASS_DECL_AURA machine_event
{
public:


   ::pointer < ::mutex >      m_pmutex;
   bool              m_bInitialized;


   machine_event();
   virtual ~machine_event();


   bool initialize();

   bool read(machine_event_data * pdata);
   bool write(machine_event_data * pdata);

};



