#include "framework.h"
#include <stdio.h>


CLASS_DECL_AURA ::i32 __cpp_assert_failed_line(const ::scoped_string & scopedstrFileName, ::i32 iLineNumber);




CLASS_DECL_AURA ::i32 __assert_failed_line(const ::scoped_string & scopedstrFileName, ::i32 iLineNumber)

{

   return __cpp_assert_failed_line(scopedstrFileName, iLineNumber);


}



//
//CLASS_DECL_AURA ::i32 __cpp_assert_failed_line(const ::scoped_string & scopedstrFileName, ::i32 iLineNumber)
//{
//
//   thread * pthread = get_task();
//
//   if(pthread != nullptr)
//   {
//
//      pthread->::auraacmesystem()->assert_failed_line(scopedstrFileName,iLineNumber);
//
//   }
//
//#ifdef _DEBUG
//
//   ::i8 szTitle[1024];
//   ::i8 szMessage[1024*4];
//
//   strcpy(szTitle, "Assert failed");
//
//   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",pszFileName,iLineNumber);
//
//   auto pmessageboxpayload = __initialize_new ::message_box_payload(szMessage,szTitle,MB_CANCELTRYCONTINUE | MB_ICONERROR, callback());

send(pmessageboxpayload);
//
//   //if(iResult == e_dialog_result_cancel)
//   //{
//
//   //   exit(0);
//
//   //   return false;
//
//   //}
//   //else if(iResult == IDTRYAGAIN)
//   //{
//
//   //   return false;
//
//   //}
//   //else
//   //{
//
//   //   return true;
//
//   //}
//
//#endif //__DEBUG
//
//   return false;
//
//}
//
//
