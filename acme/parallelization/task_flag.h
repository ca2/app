// Created by camilo on 2022-06-09 11:32 BRT <3ThomasBorregaardSorensen!! Mummi and bilbo!!
#pragma once


using task_bitset = enum_bitset < enum_task_flag, e_task_flag_count >;


CLASS_DECL_ACME task_bitset& task_flag();


class CLASS_DECL_ACME ___keep_task_flag
{
public:


   enum_task_flag       m_eflag;
   bool                 m_bSet;


   ___keep_task_flag(enum_task_flag eflag) :
      m_eflag(eflag),
      m_bSet(task_flag().is_set(eflag))
   {


   }


   ~___keep_task_flag()
   {

      task_flag().set(m_eflag, m_bSet);

   }


};


inline ___keep_task_flag keep_task_flag(enum_task_flag eflag)
{

   return eflag;

}



#define __keep_task_flag(...) auto TOKEN_AT_LINE(__keep_task_flag) = keep_task_flag(__VA_ARGS__)





#define __task_guard_ret(flag, ret) \
 \
synchronous_lock synchronouslock(this->synchronization()); \
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


#define __prevent_bad_status_exception __keep_task_flag(e_task_flag_prevent_bad_status_exception)



