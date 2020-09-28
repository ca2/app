#pragma once
#include "acme/platform/profiler.h"


extern __pointer(::thread) g_pthreadXlib;
extern ITHREAD g_ithreadXlib;


void x11_kick_idle();
void x11_async_runnable(::elemental * prunnable);
void x11_sync_runnable(::elemental * prunnable);




template < typename PRED >
void x11_fork(PRED pred)
{

   if(::get_current_ithread() == g_ithreadXlib)
   {

      pred();

      return;

   }

   auto prunnable = __task_procedure(pred, g_pthreadXlib);

   x11_async_runnable(prunnable);

}


mutex * x11_mutex();


template < typename PRED >
void x11_sync(PRED pred)
{

   sync_lock sl(x11_mutex());

   pred();

}



