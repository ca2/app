#include "framework.h"
#include "acme/parallelization/task.h"
#include "acme/platform/message_box.h"
#include "acme/platform/system.h"
#include <stdio.h>


//#if defined(__APPLE__)

//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::future future);

//#elif defined(UNIVERSAL_WINDOWS)

//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::future future);

//#else

//#ifdef UNIVERSAL_WINDOWS
//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::future & future);
//#else
//int _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox);
//#endif


//#endif


CLASS_DECL_ACME ::payload __cpp_assert_failed_line(const_char_pointer pszFileName, int iLineNumber);


CLASS_DECL_ACME string message_box_result_to_string(int iResult);


#ifndef UNIVERSAL_WINDOWS


namespace acme
{

//
//   class message_box_synchronous :
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
//      message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox) :
//         m_strText(strText),
//         m_strTitle(strTitle),
//         m_emessagebox(emessagebox)
//      {
//
//      }
//
//
//      virtual ~message_box_synchronous()
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
//   ::payload message_box_synchronous::realize()
//   {
//
//      int iResult = ::_os_message_box(m_strText, m_strTitle, m_emessagebox);
//
//      return iResult;
//
//   }


} // namespace acme


#endif

//#ifdef UNIVERSAL_WINDOWS
//
//
//void message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::future & future)
//{
//
//   return _os_message_box(scopedstrText, pszTitle, emessagebox, process);
//
//}
//
//
//#else
//
//
////void message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::future & future)
////{
////
////   auto posmessagebox = __allocate ::acme::auto pmessagebox = __initialize_new ::message_box(scopedstrText, pszTitle, emessagebox);

//pmessagebox->sync();
////
////   return __realize(posmessagebox, process);
////
////}
////
//
//#endif


//::platform::system * system();


CLASS_DECL_ACME bool __assert_failed_line(const_char_pointer pszFileName, int iLineNumber)
{

#ifdef LINUX

   if(is_main_thread())
   {

      // Cannot display synchronously in user/main thread.

      // Cannot show user interface on break of user/main thread.

      return false;

   }

#endif

   auto edialogresult = __cpp_assert_failed_line(pszFileName, iLineNumber);

   if(edialogresult == e_dialog_result_cancel)
   {

      exit(0);

   }
   else if(edialogresult == e_dialog_result_retry)
   {

      return false;

   }

   return true;

}


CLASS_DECL_ACME ::payload __cpp_assert_failed_line(const_char_pointer pszFileName, int iLineNumber)
{

   char szMessage[1024*4];

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running", pszFileName,iLineNumber);

   auto pmessagebox = 
      __initialize_new_with(system())
      ::message_box(
         szMessage,
         "ASSERT",
         e_message_box_cancel_try_continue | e_message_box_icon_error);

   pmessagebox->sync();

   return pmessagebox->m_payloadResult;

}



