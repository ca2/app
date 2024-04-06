#pragma once


#include "usera.h"


namespace account
{


   class CLASS_DECL_AXIS user_set :
      virtual public usera
   {
   public:


      user_set(::particle * pparticle);
      virtual ~user_set();



   };


} // namespace account



