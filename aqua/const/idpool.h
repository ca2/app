#pragma once


#include "apex/id.h"


namespace aqua
{


   class CLASS_DECL_AQUA idpool :
      virtual public ::apex::idpool
   {
   public:


      static idpool* g_pthis;


      idpool();


   };


} // namespace aqua



