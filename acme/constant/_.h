//
// Created by camilo on 04/12/2020. <3Tbs, Mummi and bilbo!!
//
#pragma once


enum enum_no_initialize
{

   e_no_initialize,

};






#include "code_page.h"






enum enum_normalize
{

   e_normalize

};


enum enum_null
{

   e_null

};


//// very short name ([{c}])ontext (switchers, as it as action_context) enums
//enum nullptr_t
//{
//   nullptr
//};


// very short name ([{c}])ontext (switchers, as it as action_context) enums
enum e_context_switcher_empty
{
   
   cempty

};


enum enum_create_new
{

   e_create_new

};


enum enum_create
{

   e_create

};


enum enum_defer_new // new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
{

   e_defer_new

};


enum enum_move_transfer
{

   e_move_transfer

};


enum enum_copy_clone
{

   e_copy_clone

};


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



