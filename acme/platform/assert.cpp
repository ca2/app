#include "framework.h"
#include <stdio.h>


//#if defined(__APPLE__)

//void _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::future future);

//#elif defined(_UWP)

//::e_status _os_message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox, ::future future);

//#else

//#ifdef _UWP
//::e_status _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process);
//#else
//int _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox);
//#endif


//#endif


CLASS_DECL_ACME int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber);


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
//      os_message_box(const string & strText, const string & strTitle, const ::e_message_box & emessagebox) :
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

#ifdef _UWP


::e_status os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
{

   return _os_message_box(pszText, pszTitle, emessagebox, process);

}


#else


//::e_status os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::future & process)
//{
//
//   auto posmessagebox = __new(::acme::os_message_box(pszText, pszTitle, emessagebox));
//
//   return __realize(posmessagebox, process);
//
//}
//

#endif

CLASS_DECL_ACME int __assert_failed_line(const char * pszFileName, int iLineNumber)
{

   return __cpp_assert_failed_line(pszFileName, iLineNumber);

}


CLASS_DECL_ACME int __cpp_assert_failed_line(const char * pszFileName, int iLineNumber)
{


   //char szTitle[1024];

   char szMessage[1024*4];

   //strcpy(szTitle, "Assert failed");

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",pszFileName,iLineNumber);

   __throw(error_assert, szMessage);

   return 0;

}



