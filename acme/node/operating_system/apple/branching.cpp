//
//  branching.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"
#include "acme/operating_system.h"




CLASS_DECL_ACME void main_branch(::matter* pobjectTask, enum_priority epriority)
{

   ns_main_sync(^()
   {

      pobjectTask->operator()();

   });

}
