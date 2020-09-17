#include "framework.h"
#include <stdio.h>


CLASS_DECL_ACME int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber);


CLASS_DECL_ACME string message_box_result_to_string(int iResult);


namespace acme
{
 
   class os_message_box :
      virtual public ::generic
   {
   public:

      string            m_strText;
      string            m_strTitle;
      ::emessagebox     m_emessagebox;
      ::callback        m_callback;

      os_message_box(const string & strText, const string & strTitle, ::emessagebox emessagebox, ::callback callback) :
         m_strText(strText), m_strTitle(strTitle), m_emessagebox(emessagebox), m_callback(callback)
      {


      }
       
     virtual ~os_message_box()
      {

      }

      virtual ::estatus run() override
      {

         int iMessageBox = m_emessagebox.m_eenum & 0x7f;

         wstring wstrText(m_strText);

         wstring wstrTitle(m_strTitle);

         int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);

         string strResult = message_box_result_to_string(iResult);

         m_callback.receive_response(strResult);

         return ::success;

      }


   };

}

::estatus os_message_box(const char* pszText, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   auto posmessagebox = __new(::acme::os_message_box(pszText, pszTitle, emessagebox, callback));

   posmessagebox->os_fork();

   return ::success;

}

CLASS_DECL_ACME int __assert_failed_line(const char * pszFileName, int iLineNumber)

{

   return __cpp_assert_failed_line(pszFileName, iLineNumber);


}




CLASS_DECL_ACME int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber)
{

   //__throw(todo("thread"));
   //thread * pthread = get_thread();

   //if(pthread != nullptr)
   //{

   //   pthread->get_context_system()->assert_failed_line(pszFileName,iLineNumber);

   //}

#ifdef __DEBUG

   char szTitle[1024];
   char szMessage[1024*4];

   strcpy(szTitle, "Assert failed");

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",pszFileName,iLineNumber);

   os_message_box(szMessage,szTitle,MB_CANCELTRYCONTINUE | MB_ICONERROR, callback());


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


