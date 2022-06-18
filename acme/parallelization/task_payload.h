// Created by camilo on 2022-06-09 11:10 BRT <3ThomasBorregaardSorensen!! and Mummi and bilbo!!
#pragma once



inline ::payload& task_property(const ::atom& atom);




class CLASS_DECL_ACME ___keep_task_payload
{
public:


   ::atom         m_atom;
   ::payload      m_payload;


   ___keep_task_payload(const ::atom& atom) :
      m_atom(atom),
      m_payload(task_property(atom))
   {


   }


   ~___keep_task_payload()
   {

      task_property(m_atom) = m_payload;

   }


};


inline ___keep_task_payload keep_task_payload(const ::atom& atom)
{

   return atom;

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
