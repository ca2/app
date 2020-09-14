//
//  user.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//

#include <stdio.h>


CLASS_DECL_AXIS void main_branch(::generic* pobjectTask, e_priority epriority)
{

   ns_main_sync(^()
   {

      pobjectTask->call();

   });

}
