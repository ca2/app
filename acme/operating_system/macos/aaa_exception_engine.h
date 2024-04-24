#pragma once


#include "acme/exception/engine.h"


namespace macos
{


   namespace exception
   {

   
      class CLASS_DECL_ACME engine :
         virtual public ::exception_engine
      {
      public:


         engine();
         virtual ~engine();


      };
   
   
   } // namespace exception


} // namespace macos



