// Created by camilo on 2022-06-09 14:31 BRT <3ThomasBorregaardSorensen!! and Mummi and bilbo!!
#pragma once


#define __keep_current_thread(...) auto TOKEN_AT_LINE(__keep_current_thread) = keep(__VA_ARGS__, ::get_task())


template < >
inline ::task* default_keep_value < ::task* >()
{

   return ::get_task();

}

#define __task_guard_ret(flag, ret) \
 \
synchronous_lock synchronouslock(mutex()); \
 \
if (flag) \
{ \
\
   ret; \
\
} \
\
auto TOKEN_AT_LINE(__task_guard_task_ret) = keep(flag); \
\
synchronouslock.unlock()

#define __task_guard(flag) __task_guard_ret(flag, return)


#define __guard_wait_ret(flag, ret) \
 \
synchronous_lock synchronouslock(mutex()); \
 \
while (flag) \
{ \
\
   \
   synchronouslock.unlock(); \
   \
   if (!task_sleep(100_ms)) \
   {\
   \
      ret; \
   \
   } \
   \
   synchronouslock.lock(); \
   \
   \
} \
\
auto TOKEN_AT_LINE(__guard_wait_ret) = keep(&flag); \
\
synchronouslock.unlock()

#define __guard_wait(flag) __task_guard_ret(flag, return)


