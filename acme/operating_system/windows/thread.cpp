#include "framework.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME bool os_on_init_thread()
{

   SetThreadLocale(65001);


   //attach_thread_input_to_main_thread();

   // acme commented for apex
   //if(!__os_init_thread())
   //{

   //   return false;

   //}

   return true;

}


CLASS_DECL_ACME void os_on_term_thread()
{

   // acme commented for apex
   //bool bOk1 = __os_term_thread();
   //bool bOk1 = false;

   //return bOk1;

}





void __node_init_multitasking()
{

}



void __node_term_multitasking()
{

}



//extern CLASS_DECL_ACME thread_int_ptr < HRESULT > thread_set("hresult_co_initialize");



bool __os_init_thread()
{


   //thread_set("hresult_co_initialize") = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);

   //if(FAILED(thread_set("hresult_co_initialize")))
   ////{

   ////   if(thread_set("hresult_co_initialize").operator HRESULT() == RPC_E_CHANGED_MODE)
   ////   {

   ////      thread_set("hresult_co_initialize") = ::CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED);

   ////      if(FAILED(thread_set("hresult_co_initialize")))
   ////      {

   ////         ::message_box(nullptr,"Failed to ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED) at __node_pre_init","__node_pre_init failure",e_message_box_icon_exclamation);

   ////         return false;

   ////      }

   ////   }
   ////   else
   ////   {

   ////      ::message_box(nullptr,"Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init","__node_pre_init failure",e_message_box_icon_exclamation);

   ////      return false;

   ////   }

   ////}

   return true;

}





//void _on_os_htask_end(int iRet)
//{
//
//   // allow C-runtime to cleanup, and exit the thread
//   try
//   {
//
//      _endthreadex(iRet);
//
//   }
//   catch(...)
//   {
//
//   }
//
//}

// CLASS_DECL_ACME unsigned int thread_alloc()
// {

//    return (unsigned int) TlsAlloc();

// }


// CLASS_DECL_ACME void * thread_get_data(unsigned int uiIndex)
// {

//    return (void *) TlsGetValue((unsigned int) uiIndex);

// }


// CLASS_DECL_ACME int thread_set_data(unsigned int uiIndex, void * pvalue)
// {

//    return TlsSetValue((unsigned int)uiIndex, (LPVOID) pvalue);

// }


// CLASS_DECL_ACME int_bool thread_free(unsigned int uiIndex)
// {

//    return TlsFree((unsigned int) uiIndex);

// }


// CLASS_DECL_ACME void thread_shutdown()
// {

// }


// LPVOID thread_data_get(thread_data_index dwIndex)
// {

//    return TlsGetValue(dwIndex);

// }


// int_bool thread_data_set(thread_data_index dwIndex, void* pvalue)
// {

//    return TlsSetValue(dwIndex, pvalue);


// }


// thread_data_index thread_data_allocate()
// {

//    return TlsAlloc();

// }


// int_bool thread_data_free(thread_data_index dwIndex)
// {

//    return TlsFree(dwIndex);

// }






//bool __os_init_thread()
//{
//
//   return true;
//
//}



bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


namespace platform
{


   void node::_user_post(const ::procedure & procedure)
   {

      //if (is_main_thread())
      //{

      //   procedure();

      //   return;

      //}

      system()->acme_windowing()->_main_post(procedure);

      //auto ptask = ::get_task();

      //if (::is_set(ptask))
      //{

      //   ptask->post(procedure);

      //}
      //else
      //{

      //   system()->post(procedure);

      //}

   }


   //void node::_user_post(::subparticle * p)
   //{

   //   if (is_main_thread())
   //   {

   //      p->call_run();

   //      return;

   //   }

   //   auto ptask = ::get_task();

   //   if (::is_set(ptask))
   //   {

   //      ptask->post(p);

   //   }
   //   else
   //   {

   //      system()->post(p);

   //   }

   //}

}  // namespace platform




