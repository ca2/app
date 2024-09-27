#pragma once


////#include "acme/prototype/prototype/object.h"


class CLASS_DECL_AURA wait_cursor :
   virtual public ::object
{
public:


   wait_cursor(::particle * pparticle);
   ~wait_cursor() override;


   void restore();


};



