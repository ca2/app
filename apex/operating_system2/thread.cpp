#include "framework.h"
#include "acme/parallelization/task.h"

#include "apex/operating_system.h"


#ifndef WINDOWS
extern thread_data_index g_tlsindexLastError;
#endif

// namespace parallelization
// {


//    thread_data_index g_dwTls = 0;


//    CLASS_DECL_APEX void os_tls_init()
//    {

//       g_dwTls = thread_data_allocate();

// #ifndef WINDOWS

//       g_tlsindexLastError = thread_data_allocate();

// #endif

//    }


//    CLASS_DECL_APEX void os_tls_term()
//    {

// #ifndef WINDOWS

//       thread_data_free(g_tlsindexLastError);

// #endif

//       thread_data_free(g_dwTls);

//    }


//    CLASS_DECL_APEX void os_tls_set(void * p)
//    {

//       thread_data_set(g_dwTls, p);

//    }


//    CLASS_DECL_APEX void * os_tls_get()
//    {

//       return thread_data_get(g_dwTls);

//    }


// } // namespace parallelization


//thread_local ::pointer<::property_set>t_ppropertyset;
//
//
//::property_set& _thread_property_set()
//{
//
//   auto& ppropertyset = t_ppropertyset;
//
//   ppropertyset.defer_create_new();
//
//   return *ppropertyset;
//
//}
//
//::property_set& thread_property_set()
//{
//
//   auto & ppropertyset = t_ppropertyset;
//
//   return ppropertyset ? *ppropertyset : _thread_property_set();
//
//}



string apex_get_task_name(::task* ptask)
{

   if (ptask->m_strTaskName.has_character())
   {

      return ptask->m_strTaskName;

   }

   if (ptask->m_strTaskTag.has_character())
   {

      return ptask->m_strTaskTag;

   }

   return ::type(ptask).name();

}
