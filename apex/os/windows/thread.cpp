#include "framework.h"
#include "apex/operating_system.h"


bool on_init_thread()
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


bool on_term_thread()
{

   // acme commented for apex
   //bool bOk1 = __os_term_thread();
   bool bOk1 = false;

   return bOk1;

}





void __node_init_multithreading()
{

}



void __node_term_multithreading()
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





//void _on_os_hthread_end(int iRet)
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

// CLASS_DECL_ACME u32 thread_alloc()
// {

//    return (u32) TlsAlloc();

// }


// CLASS_DECL_ACME void * thread_get_data(u32 uiIndex)
// {

//    return (void *) TlsGetValue((::u32) uiIndex);

// }


// CLASS_DECL_ACME i32 thread_set_data(u32 uiIndex, void * pvalue)
// {

//    return TlsSetValue((::u32)uiIndex, (LPVOID) pvalue);

// }


// CLASS_DECL_ACME int_bool thread_free(u32 uiIndex)
// {

//    return TlsFree((::u32) uiIndex);

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


CLASS_DECL_APEX void main_branch(matter * pmatter, e_priority epriority)
{

   ::apex::get_system()->sync_procedure(pmatter);

}



