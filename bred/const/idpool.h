#pragma once


#include "base/atom.h"


namespace bred
{


   class CLASS_DECL_BRED idpool :
      virtual public ::base::idpool
   {
   public:


      static idpool* g_pthis;


      idpool();


   };


} // namespace bred



