//*****************************************************************************
//
//      Class:          thread_pool
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides the ability to queue simple member functions
//                      to the Windows thread pool.
//
//*****************************************************************************

#pragma once

#ifdef WINDOWS_DESKTOP
#define THREAD_START_ROUTINE_API WINAPI
#else
#define THREAD_START_ROUTINE_API
#endif

template < typename T >
class simple_signal :
   virtual public ::generic
{
public:

   typedef void (T::*method)();


   T *         m_p;
   method      m_pmethod;


   simple_signal(T * pobject, method pmethod);

   void emit();

};


template < typename T >
simple_signal < T > ::simple_signal(T * pobject, method pmethod) :
   m_p(pobject),
   m_pmethod(pmethod)
{

}


template < typename T >
void simple_signal < T > ::emit()
{
   (m_p->*m_pmethod)();
}

class thread_pool
{
public:

   template <typename T>
   static void QueueUserWorkItem(T * pobject, void (T::*pmethod)(), WINULONG flags =
#ifdef WINDOWS_DESKTOP
                                 WT_EXECUTELONGFUNCTION
#else
                                 0
#endif
                                )
   {

      simple_signal < T > * psignal = new simple_signal < T >(pobject, pmethod);

#ifdef WINDOWS_DESKTOP

      if(!::QueueUserWorkItem((LPTHREAD_START_ROUTINE) thread_proc < T >, psignal, flags))
      {

         delete psignal;

         __throw(last_error_exception());

      }

#else

      pobject->fork([psignal]()
      {

         psignal->emit();

         delete psignal;

      });

//      if(!create_thread(thread_proc < T >, psignal))
//      {
//
//         delete psignal;
//
//         __throw(::exception::exception("failed to start QueueUserWorkItem"));
//
//      }

#endif

   }

private:

   template <typename T>
   static u32 THREAD_START_ROUTINE_API thread_proc(void * pcontext)
   {
      simple_signal < T > * psignal =  static_cast < simple_signal < T > * >(pcontext);

      psignal->emit();

      delete psignal;
      return 0;
   }

   thread_pool();
};
