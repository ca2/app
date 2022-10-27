#pragma once


#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_APEX machine_event :
   virtual public ::matter
{
public:


   bool              m_bInitialized;


   machine_event();
   virtual ~machine_event();


   virtual void initialize(::particle * pparticle) override;

   bool read(machine_event_data * pdata);
   bool write(machine_event_data * pdata);

};



