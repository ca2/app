#pragma once


#include "bred/id.h"


namespace core
{


   class CLASS_DECL_CORE idpool :
      public ::bred::idpool
   {
   public:


      static idpool* g_pthis;
      

      idpool();



   };


} // namespace core





