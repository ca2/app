#pragma once

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



