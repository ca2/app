#pragma once


#include "acme/primitive/primitive/particle.h"


class CLASS_DECL_APEX machine_event :
   virtual public ::particle
{
public:


   bool              m_bInitialized;


   machine_event();
   virtual ~machine_event();


   virtual void initialize(::particle * pparticle) override;

   bool read(machine_event_data * pdata);
   bool write(machine_event_data * pdata);

};



