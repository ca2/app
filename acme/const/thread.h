#pragma once

//
//enum e_thread_flag :
//   i64
//{
//
//   thread_flag_fast_path = 1 << 0,
//   thread_flag_zip_is_dir = 1 << 1,
//   thread_flag_is_timer = 1 << 2,
//   thread_flag_resolve_alias = 1 << 3,
//   //thread_flag_prevent_create_thread = 1 << 4,
//   thread_flag_prevent_bad_status_exception = 1 << 5,
//
//};



enum enum_thread_op :i64
{

   e_thread_op_none,
   e_thread_op_tool,
   e_thread_op_pred,
   e_thread_op_fork_count,

};


enum enum_thread_tool : ::i64
{

   e_thread_tool_draw2d,

};



