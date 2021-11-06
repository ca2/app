#pragma once


#include "axis/id.h"


namespace base
{


   class CLASS_DECL_BASE idpool :
      public ::axis::idpool
   {
   public:


      static idpool* g_pthis;


      idpool();

   };


} // namespace base



