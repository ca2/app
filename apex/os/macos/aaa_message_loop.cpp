//
//  message_loop.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "acme/multithreading/mq.h"


int_bool post_message(oswindow oswindow, const ::id & id, WPARAM wparam, LPARAM lparam)
{

   return mq_post_message(oswindow, message, wparam, lparam);

}

