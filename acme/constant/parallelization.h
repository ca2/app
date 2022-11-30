// Created by camilo on 2021-08-09 02:26 BRT <3ThomasBorregaardS�rensen!!
#pragma once


//
//enum enum_synchronization_result
//{
//
//   e_synchronization_result_abandoned_base = -1024,
//   e_synchronization_result_error = -16,
//   e_synchronization_result_thread_set_finish = -6,
//   e_synchronization_result_io_completion = -3,
//   e_synchronization_result_bad_thread = -2,
//   e_synchronization_result_timed_out = -1,
//   e_synchronization_result_signaled_base = 0,
//
//};




//
//enum e_task_flag :
//   i64
//{
//
//   task_flag_fast_path = 1 << 0,
//   task_flag_zip_is_dir = 1 << 1,
//   task_flag_is_timer = 1 << 2,
//   task_flag_resolve_alias = 1 << 3,
//   //task_flag_prevent_create_task = 1 << 4,
//   task_flag_prevent_bad_status_exception = 1 << 5,
//
//};



enum enum_task_op :i64
{

   e_task_op_none,
   e_task_op_tool,
   e_task_op_predicate,
   e_task_op_fork_count,

};


enum enum_task_tool : ::iptr
{

   e_task_tool_draw2d,

};



