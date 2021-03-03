#include "framework.h"


//::mutex * g_pmutexChildren = nullptr;
//
//void _debug_debug_string_string()
//{
//
//   ::id id("a-ha");
//
//   auto bEndsInHa1 = ::str::ends(id, "ha");
//   auto bEndsInHa2 = ::str::ends_ci(id, "Ha");
//
//
//}

void __assert_valid_object(const ::context_object * pOb, const char * pszFileName, i32 nLine)

{

   if (pOb == nullptr)
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         DEBUG_BREAK;

      }

      return;     // quick escape

   }

   if (!__is_valid_address(pOb, sizeof(object)))
   {

      ///TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal pointer.\n");

      if (__assert_failed_line(pszFileName, nLine))
      {

         DEBUG_BREAK;

      }

      return;     // quick escape

   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), false))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), false))
   {

      //      TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");

      if (__assert_failed_line(pszFileName, nLine))
      {

         DEBUG_BREAK;

      }

      return;     // quick escape

   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, false))
   {
   TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(pszFileName, nLine))

   debug_break();
   return;     // quick escape
   }*/

   pOb->assert_valid();

}



//CLASS_DECL_APEX void call(::object * pobjectTask)
//{
//
//   pobjectTask->call();
//
//}
//



//CLASS_DECL_APEX void call(const ::method & method)
//{
//
//   method();
//
//}
//

