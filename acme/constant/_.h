//
// Created by camilo on 04/12/2020. <3Tbs, Mummi and bilbo!!
//
#pragma once


#include "_mathematics.h"


#include "geometry2d.h"


#include "code_page.h"


#include "cursor.h"


enum enum_flag : u64
{


   e_flag_none,
   e_flag_success = 1 << 0,
   e_flag_timeout = 1 << 1,
   e_flag_failure = 1 << 2,
   e_flag_persist = 1 << 3,
   e_flag_factory = 1 << 4,
   e_flag_acquire = 1 << 6,
   e_flag_default = 1 << 7,
   e_flag_changed = 1 << 9,
   e_flag_heap_allocated = 1 << 10,
   e_flag_finishing = 1 << 11,
   e_flag_destroying = 1 << 12,
   e_flag_processed = 1 << 13,
   e_flag_task_started = 1 << 14,
   e_flag_task_terminated = 1 << 15,
   e_flag_checking_children_task = 1 << 16,
   e_flag_check_children_task_post_quit = 1 << 17,
   e_flag_task_ready = 1 << 18,
   e_flag_data_struct = 1 << 19,
   e_flag_exited = 1 << 20,
   e_flag_storing = 1 << 21,
   e_flag_alertable_wait = 1 << 22,


};


#include "user_text.h"
#include "user.h"
#include "flag.h"


#include "earth.h"


#include "data.h"


#include "error_code_type.h"



