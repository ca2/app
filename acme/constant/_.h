//
// Created by camilo on 04/12/2020. <3Tbs, Mummi and bilbo!!
//
#pragma once


#include "_mathematics.h"


#include "code_page.h"


#include "cursor.h"


enum enum_matter
{

   e_matter_none,
   e_matter_heap_allocated = 1 << 0,
   e_matter_finishing = 1 << 1,
   e_matter_destroying = 1 << 2,
   e_matter_processed = 1 << 3,
   e_matter_task_started = 1 << 4,
   e_matter_task_terminated = 1 << 5,
   e_matter_checking_children_task = 1 << 6,
   e_matter_check_children_task_post_quit = 1 << 7,
   e_matter_task_ready = 1 << 8,
   e_matter_data_struct = 1 << 9,
   e_matter_exited = 1 << 10,

};



#include "user_text.h"
#include "user.h"
#include "flag.h"


