//
//  strdup.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/01/24.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include <string.h>


namespace c
{


   char * strdup(const char * psz)
   {
      
      return ::strdup(psz);
      
   }
   

} // namespace c



