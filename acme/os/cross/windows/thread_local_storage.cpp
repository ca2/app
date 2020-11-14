#include "framework.h"


static ::u32 nextTlsIndex = ::multithreading::slot_user_begin;




//CLASS_DECL_THREAD thread_local_data* t_pthreadlocaldata;

u32_array* g_puaThreadLocalDataFreeIndexes = nullptr;

//::mutex* g_pmutexThreadLocalData = nullptr;

//map < ithread_t, ithread_t, thread_local_data >* g_pmapThreadLocalData = nullptr;

//thread_local thread_local_data t_threadlocaldata;


CLASS_DECL_ACME void __node_init_cross_windows_threading()
{

   //g_pmutexThreadLocalData = new mutex();

   //g_pmapThreadLocalData = new map < ithread_t, ithread_t, thread_local_data >();

   //g_puaThreadLocalDataFreeIndexes = new u32_array();

}


CLASS_DECL_ACME void __node_term_cross_windows_threading()
{

   //::acme::del(g_puaThreadLocalDataFreeIndexes);

   //::acme::del(g_pmapThreadLocalData);

   //::acme::del(g_pmutexThreadLocalData);

}

//thread_local thread_local_data t_threadlocaldata;
//// *___ :  lock g_pmutexThreadLocalData to use it
//inline thread_local_data* ___get_thread_local_data(ithread_t idthread)
//{
//
//   return &t_threadlocaldata;
//
//   //try
//   //{
//
//   //   return &g_pmapThreadLocalData->operator[](idthread);
//
//   //}
//   //catch (...)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//}


// *___ :  lock g_pmutexThreadLocalData to use it
//inline thread_local_data* ___get_current_thread_local_data()
//{
//
////   auto pthreadlocaldata = t_pthreadlocaldata;
////
////   if (pthreadlocaldata)
////   {
////
////      return pthreadlocaldata;
////
////   }
//
//   auto pthreadlocaldata = ___get_thread_local_data(get_current_ithread());
//
////   t_pthreadlocaldata = pthreadlocaldata;
//
//   return pthreadlocaldata;
//
//}


//thread_data_index thread_data_allocate()
//{
//
//   sync_lock lock(g_pmutexThreadLocalData);
//
//   if (g_puaThreadLocalDataFreeIndexes->get_count() > 0)
//   {
//
//      return g_puaThreadLocalDataFreeIndexes->pop();
//
//   }
//
//   return nextTlsIndex++;
//
//}


//int_bool thread_data_free(thread_data_index dwIndex)
//{
//
//   if (dwIndex < ::multithreading::slot_user_begin || dwIndex >= nextTlsIndex)
//   {
//
//      return false;
//
//   }
//
//   sync_lock lock(g_pmutexThreadLocalData);
//
//   try
//   {
//
//      if (g_puaThreadLocalDataFreeIndexes->contains(dwIndex))
//      {
//
//         return false;
//
//      }
//
//      g_puaThreadLocalDataFreeIndexes->add(dwIndex);
//
//   }
//   catch (...)
//   {
//
//      return false;
//
//   }
//
//   // Zero the value for all threads that might be using this now freed slot.
//
//   for (auto& pair : *g_pmapThreadLocalData)
//   {
//
//      auto& threadlocaldata = pair.element2();
//
//      if ((::count) dwIndex < threadlocaldata.get_count())
//      {
//
//         threadlocaldata[dwIndex] = nullptr;
//
//      }
//
//      // Hellish Detail & Fun to Implement:
//      // Shrink threadata (even to 0 size), while last values are nullptr
//      // (as it is the default value for not allocated slots).
//
//      index iFindLastNonNull = threadlocaldata.find_last_not(nullptr);
//
//      threadlocaldata.set_size(iFindLastNonNull + 1);
//
//   }
//
//   return true;
//
//}


//LPVOID thread_data_get(thread_data_index dwIndex)
//{
//
//   return __thread_get_data(get_current_ithread(), dwIndex);
//
//}
//
//
//void* __thread_get_data(ithread_t idthread, thread_data_index dwIndex)
//{
//
//   if (dwIndex >= nextTlsIndex)
//   {
//
//      return nullptr;
//
//   }
//
//   try
//   {
//
//      sync_lock lock(g_pmutexThreadLocalData);
//
//      auto pthreadlocaldata = ___get_thread_local_data(idthread);
//
//      if ((::count) dwIndex < pthreadlocaldata->get_count())
//      {
//
//         return pthreadlocaldata->element_at(dwIndex);
//
//      }
//      else
//      {
//
//         return nullptr;
//
//      }
//
//   }
//   catch (...)
//   {
//
//      return nullptr;
//
//   }
//
//}

//
//int_bool thread_set_data(thread_data_index dwIndex, void* pvalue)
//{
//
//   return __thread_set_data(get_current_ithread(), dwIndex, pvalue);
//
//}
//
//
//int_bool thread_data_set(thread_data_index dwIndex, void* pvalue)
//{
//
//   return thread_set_data(dwIndex, pvalue);
//
//}
//
//
//
//int_bool __thread_set_data(ithread_t idthread, thread_data_index dwIndex, void* pvalue)
//{
//
//   if (dwIndex >= nextTlsIndex)
//   {
//
//      return false;
//
//   }
//
//   sync_lock lock(g_pmutexThreadLocalData);
//
//   auto pthreadlocaldata = ___get_thread_local_data(idthread);
//
//   pthreadlocaldata->set_at_grow(dwIndex, pvalue);
//
//   // Hellish Detail & Fun to Implement:
//   // Shrink threadata (even to 0 size), while last values are nullptr
//   // (as it is the default value for not allocated slots).
//
//   index iFindLastNonNull = pthreadlocaldata->find_last_not(nullptr);
//
//   pthreadlocaldata->set_size(iFindLastNonNull + 1);
//
//   return true;
//
//}
//
//
//// Called at thread exit to clean up TLS allocations.
//void thread_shutdown()
//{
//
////   thread_local_data* pthreadlocaldata = t_pthreadlocaldata;
////
////   if (pthreadlocaldata)
//   {
//
//      sync_lock ml(g_pmutexThreadLocalData);
//
//      g_pmapThreadLocalData->remove_key(get_current_ithread());
//
//   }
//
//}


// void* thread_get_data(thread_data_index dwIndex)
// {

//    sync_lock ml(g_pmutexThreadLocalData);

//    thread_local_data* pthreadlocaldata = ___get_current_thread_local_data();

//    if (!pthreadlocaldata)
//    {

//       return nullptr;

//    }

//    if ((::count) dwIndex >= pthreadlocaldata->get_count())
//    {

//       return nullptr;

//    }

//    return pthreadlocaldata->element_at(dwIndex);

// }



