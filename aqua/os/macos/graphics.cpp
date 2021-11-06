//
//  graphics.cpp
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


namespace aura
{


   HCURSOR application::load_default_cursor(e_cursor ecursor)
   {
      
      return nscursor_system(ecursor);
      
   }


} // namespace aura



