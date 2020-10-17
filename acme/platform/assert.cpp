#include "framework.h"
#include <stdio.h>
#ifdef LINUX
#include "acme/os/x11/_x11.h"
#endif


//#if defined(__APPLE__)

//void _os_message_box(const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::future future);

//#elif defined(_UWP)

//::estatus _os_message_box(const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::future future);

//#else


int _os_message_box(const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox);


//#endif


CLASS_DECL_ACME int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber);


CLASS_DECL_ACME string message_box_result_to_string(int iResult);


namespace acme
{


   class os_message_box :
      virtual public ::matter
   {
   public:


      string            m_strText;
      string            m_strTitle;
      ::emessagebox     m_emessagebox;


      os_message_box(const string & strText, const string & strTitle, ::emessagebox emessagebox) :
         m_strText(strText),
         m_strTitle(strTitle),
         m_emessagebox(emessagebox)
      {

      }


      virtual ~os_message_box()
      {

      }


      virtual var realize() override;


   };


   var os_message_box::realize()
   {

      int iResult = ::_os_message_box(m_strText, m_strTitle, m_emessagebox);

      return iResult;

   }


} // namespace acme


::estatus os_message_box(const char * pszText, const char * pszTitle, ::emessagebox emessagebox, ::future future)
{

   auto posmessagebox = __new(::acme::os_message_box(pszText, pszTitle, emessagebox));

   return __launch(posmessagebox, future);

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

   os_message_box(szMessage, szTitle, MB_CANCELTRYCONTINUE | MB_ICONERROR);

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



