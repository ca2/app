//
//  _api.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 20:10.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"



namespace posix
{
   

   CLASS_DECL_ACME string get_errno_string(::i32 iErrNo)
   {
      
      if(iErrNo == 0)
      {
         
         return "(No Error)";
         
      }
      else
      {
         
         auto psz = strerror(iErrNo);
         
         if(!psz)
         {
          
            return "(Unknown error)";
            
         }
         
         return psz;
         
      }
   
   }


} // namespace posix



