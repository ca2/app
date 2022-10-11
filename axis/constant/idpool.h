#pragma once


#include "aura/constant/idpool.h"


namespace axis
{


   class CLASS_DECL_AXIS idpool :
      virtual public ::aura::idpool
   {
   public:


      static idpool* g_pthis;


      idpool();


   };


} // namespace axis



