#pragma once
#include "acme/platform/profiler.h"


//extern __pointer(::thread) g_pthreadXlib;
//extern ithread_t g_ithreadXlib;


void x11_kick_idle();
void x11_async_runnable(::matter * prunnable);
void x11_sync_runnable(::matter * prunnable);


CLASS_DECL_ACME ithread_t x11_get_ithread();
CLASS_DECL_ACME ::thread * x11_get_thread();


template < typename PRED >
void x11_fork(PRED pred)
{

   if(::get_current_ithread() == ::x11_get_ithread())
   {

      pred();

      return;

   }

   auto prunnable = __routine(pred);

   x11_async_runnable(prunnable);

}


::mutex * x11_mutex();


template < typename PRED >
void x11_sync(PRED pred)
{

   sync_lock sl(x11_mutex());

   pred();

}



