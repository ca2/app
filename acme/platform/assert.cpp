#include "framework.h"
#include <stdio.h>


//#if defined(__APPLE__)

//void _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::future future);

//#elif defined(_UWP)

//void _os_message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, ::future future);

//#else

//#ifdef _UWP
//void _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process);
//#else
//int _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox);
//#endif


//#endif


CLASS_DECL_ACME ::id __cpp_assert_failed_line(const char * pszFileName, int iLineNumber);


CLASS_DECL_ACME string message_box_result_to_string(int iResult);


#ifndef _UWP


namespace acme
{

//
//   class os_message_box :
//      virtual public ::matter
//   {
//   public:
//
//
//      string            m_strText;
//      string            m_strTitle;
//      const ::e_message_box &     m_emessagebox;
//
//
//      os_message_box(const ::string & strText, const ::string & strTitle, const ::e_message_box & emessagebox) :
//         m_strText(strText),
//         m_strTitle(strTitle),
//         m_emessagebox(emessagebox)
//      {
//
//      }
//
//
//      virtual ~os_message_box()
//      {
//
//      }
//
//
//      virtual ::payload realize() override;
//
//
//   };
//
//
//   ::payload os_message_box::realize()
//   {
//
//      int iResult = ::_os_message_box(m_strText, m_strTitle, m_emessagebox);
//
//      return iResult;
//
//   }


} // namespace acme


#endif

//#ifdef _UWP
//
//
//void os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
//{
//
//   return _os_message_box(pszText, pszTitle, emessagebox, process);
//
//}
//
//
//#else
//
//
////void os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
////{
////
////   auto posmessagebox = __new(::acme::os_message_box(pszText, pszTitle, emessagebox));
////
////   return __realize(posmessagebox, process);
////
////}
////
//
//#endif


class ::system * get_system();


CLASS_DECL_ACME bool __assert_failed_line(const char * pszFileName, int iLineNumber)
{

   auto edialogresult = __cpp_assert_failed_line(pszFileName, iLineNumber);

   if(edialogresult == e_dialog_result_cancel)
   {

      exit(0);

   }
   else if(edialogresult == e_dialog_result_try_again)
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME ::id __cpp_assert_failed_line(const char * pszFileName, int iLineNumber)
{

   char szMessage[1024*4];

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",pszFileName,iLineNumber);

   return os_message_box(::get_system(), szMessage, "ASSERT", e_message_box_cancel_try_continue);

}



