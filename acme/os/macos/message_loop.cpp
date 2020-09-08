//
//  message_loop.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "acme/platform/mq.h"


int_bool post_message(oswindow oswindow, UINT message, WPARAM wparam, LPARAM lparam)
{

   return mq_post_message(oswindow, message, wparam, lparam);

}

