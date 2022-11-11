#pragma once


#include "history.h"


class CLASS_DECL_APEX os_history :
   virtual public ::apex::history
{
public:

   os_history(::particle * pparticle);
         
   
   virtual bool hist(const char *psz);

};



