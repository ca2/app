//
//  user.cpp
//  ios_apex
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//

#include <stdio.h>


CLASS_DECL_APEX void main_branch(::matter* pobjectTask, enum_priority epriority)
{

   ns_main_sync(^()
   {

      pobjectTask->call();

   });

}
