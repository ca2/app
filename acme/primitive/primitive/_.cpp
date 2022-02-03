#include "framework.h"


extern ::mutex * g_pmutexChildren;

void _debug_debug_string_string()
{

   ::id id("a-ha");

   auto bEndsInHa1 = ::str::ends(id, "ha");
   auto bEndsInHa2 = ::str::ends_ci(id, "Ha");


}


void __assert_valid_object(const ::matter * pOb, const char * pszFileName, i32 nLine)
{

   if (pOb == nullptr)
   {

      auto edialogresult = __assert_failed_line(pszFileName, nLine);

      if(edialogresult == e_dialog_result_cancel)
      {

         exit(0);

      }
      else if(edialogresult == e_dialog_result_try_again)
      {

         DEBUG_BREAK;

      }

      return;     // quick escape

   }

   if (!__is_valid_address(pOb, sizeof(matter)))
   {

      ///TRACE(trace_category_appmsg, 0, "ASSERT_VALID fails with illegal pointer.\n");

      if (__assert_failed_line(pszFileName, nLine))
      {

         DEBUG_BREAK;

      }

      return;     // quick escape

   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::matter) == sizeof(void *));
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



//CLASS_DECL_ACME void call(::matter * pobjectTask)
//{
//
//   pobjectTask->call();
//
//}
//



//CLASS_DECL_ACME void call(const ::method & method)
//{
//
//   method();
//
//}
//

//
//CLASS_DECL_ACME string __string(const ::e_status & estatus)
//{
//
//   return __string((::i64)estatus.m_estatus);
//
//}



CLASS_DECL_ACME void __call(::matter * pmatter)
{
   
   /*auto estatus =*/ pmatter->run();
   
   //if(!estatus)
   //{
   //   
   //   return estatus;
   //   
   //}
   //
   //return estatus;
   
}
