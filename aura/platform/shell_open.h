#pragma once


////#include "acme/prototype/prototype/object.h"


class CLASS_DECL_AURA shell_open :
   virtual public ::object
{
public:


   shell_open();
   virtual ~shell_open();

   virtual void initialize(::particle * pparticle) override;


   virtual void initialize_shell_open();


};



