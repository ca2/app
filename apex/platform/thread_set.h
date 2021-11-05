#pragma once


//inline void thread_set(enum_thread_boolean ethreadboolean) { task_boolean(ethread) = true; }
//inline void thread_unset(enum_thread_boolean ethreadboolean) { task_boolean(ethread) = false; }
//inline bool task_flag().is_set(enum_thread_boolean ethreadboolean);


template  < >
inline ::task * default_keep_value < ::task * >()
{

   return ::get_task();

}


#define __keep_current_thread(...) auto TOKEN_AT_LINE(__keep_current_thread) = keep(__VA_ARGS__, ::get_task())




