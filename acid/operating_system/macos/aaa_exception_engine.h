#pragma once


#include "acid/exception/engine.h"


namespace macos
{


   namespace exception
   {

   
      class CLASS_DECL_ACID engine :
         virtual public ::exception_engine
      {
      public:


         engine();
         virtual ~engine();


      };
   
   
   } // namespace exception


} // namespace macos



