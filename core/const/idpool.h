#pragma once


#include "base/id.h"


namespace core
{


   class CLASS_DECL_CORE idpool :
      public ::base::idpool
   {
   public:


      static idpool* g_pthis;
      

      idpool();



   };


} // namespace core





