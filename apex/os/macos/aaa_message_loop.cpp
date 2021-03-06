//
//  message_loop.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "acme/parallelization/message_queue.h"


int_bool post_message(oswindow oswindow, const ::id & id, WPARAM wparam, LPARAM lparam)
{

   return message_queue_post(oswindow, message, wparam, lparam);

}

