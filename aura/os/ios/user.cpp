//
//  user.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//

#include <stdio.h>


CLASS_DECL_AURA void main_branch(::elemental* pobjectTask, e_priority epriority)
{

   ns_main_sync(^()
   {

      pobjectTask->call();

   });

}
