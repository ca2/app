#pragma once
#include "aura/platform/profiler2.h"


extern ::task_pointer g_pthreadXlib;
extern itask_t g_itaskXlib;


void x11_kick_idle();
void x11_async_runnable(::matter * prunnable);
void x11_sync_runnable(::matter * prunnable);




template < typename PRED >
void x11_fork(PRED pred)
{

   if(::get_current_itask() == g_itaskXlib)
   {

      pred();

      return;

   }

   auto prunnable = __task_procedure(pred, g_pthreadXlib);

   x11_async_runnable(prunnable);

}


mutex * user_synchronization();


template < typename PRED >
void x11_sync(PRED pred)
{

   synchronous_lock synchronouslock(x11_mutex());

   pred();

}



