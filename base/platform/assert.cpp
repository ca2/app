#include "framework.h"
#include <stdio.h>


CLASS_DECL_AURA int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber);




CLASS_DECL_AURA int __assert_failed_line(const char * pszFileName, int iLineNumber)

{

   return __cpp_assert_failed_line(pszFileName, iLineNumber);


}




CLASS_DECL_AURA int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber)
{

   thread * pthread = get_thread();

   if(pthread != nullptr)
   {

      pthread->get_context_system()->assert_failed_line(pszFileName,iLineNumber);

   }

#ifdef __DEBUG

   char szTitle[1024];
   char szMessage[1024*4];

   strcpy(szTitle, "Assert failed");

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",pszFileName,iLineNumber);

#ifdef WINDOWS_DESKTOP

   os_message_box(nullptr,szMessage,szTitle,MB_CANCELTRYCONTINUE | MB_ICONERROR, callback());

#else

   message_box(nullptr, szMessage, szTitle, MB_CANCELTRYCONTINUE | MB_ICONERROR, callback());

#endif

   //if(iResult == IDCANCEL)
   //{

   //   exit(0);

   //   return false;

   //}
   //else if(iResult == IDTRYAGAIN)
   //{

   //   return false;

   //}
   //else
   //{

   //   return true;

   //}

#endif //__DEBUG

   return false;

}


