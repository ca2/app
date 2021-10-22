//
// Created by camilo on 04/12/2020. <3Tbs, Mummi and bilbo!!
//
#pragma once


#include "_mathematics.h"


#include "code_page.h"


#include "cursor.h"


enum enum_flag
{


   e_flag_none,
   e_flag_heap_allocated = 1 << 0,
   e_flag_finishing = 1 << 1,
   e_flag_destroying = 1 << 2,
   e_flag_processed = 1 << 3,
   e_flag_task_started = 1 << 4,
   e_flag_task_terminated = 1 << 5,
   e_flag_checking_children_task = 1 << 6,
   e_flag_check_children_task_post_quit = 1 << 7,
   e_flag_task_ready = 1 << 8,
   e_flag_data_struct = 1 << 9,
   e_flag_exited = 1 << 10,


};


#include "user_text.h"
#include "user.h"
#include "flag.h"


