//
//  message_loop.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "aura/platform/message_queue.h"


int_bool post_message(oswindow oswindow, const ::atom & atom, WPARAM wparam, LPARAM lparam)
{

   return message_queue_post(oswindow, message, wparam, lparam);

}

