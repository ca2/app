#pragma once
#include "acme/platform/profiler.h"


extern __pointer(::thread) g_pthreadXlib;
extern ITHREAD g_ithreadXlib;


void x11_kick_idle();
void x11_async_runnable(::generic * prunnable);
void x11_sync_runnable(::generic * prunnable);




template < typename PRED >
void x11_fork(PRED pred)
{

   if(::get_current_ithread() == g_ithreadXlib)
   {

      pred();

      return;

   }

   auto prunnable = __pred_method(pred);

   x11_async_runnable(prunnable);

}


mutex * x11_mutex();


template < typename PRED >
void x11_sync(PRED pred)
{

   sync_lock sl(x11_mutex());

   pred();

}



