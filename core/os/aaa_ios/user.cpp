//
//  user.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//

#include <stdio.h>


CLASS_DECL_CORE void main_branch(::element* pobjectTask, e_priority epriority)
{

   ns_main_sync(^()
   {

      pobjectTask->call();

   });

}
