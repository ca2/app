//
//  message_loop.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "acme/parallelization/mq.h"


int_bool post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam)
{

   return mq_post_message(oswindow, message, wparam, lparam);

}

