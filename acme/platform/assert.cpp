#include "framework.h"
#include "acme/user/interface/message_box.h"
#include "acme/parallelization/task.h"
#include "acme/platform/system.h"
#include <stdio.h>



//#if defined(__APPLE__)

//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, ::future future);

//#elif defined(UNIVERSAL_WINDOWS)

//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, ::future future);

//#else

//#ifdef UNIVERSAL_WINDOWS
//void _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::future & future);
//#else
//::i32 _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox);
//#endif


//#endif


CLASS_DECL_ACME ::payload __cpp_assert_failed_line(const_char_pointer pszFileName, ::i32 iLineNumber);


CLASS_DECL_ACME string message_box_result_to_string(::i32 iResult);


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
//      const ::user::e_message_box &     m_emessagebox;
//
//
//      message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox) :
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
//      ::i32 iResult = ::_os_message_box(m_strText, m_strTitle, m_emessagebox);
//
//      return iResult;
//
//   }


} // namespace acme


#endif

//#ifdef UNIVERSAL_WINDOWS
//
//
//void message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::future & future)
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
////void message_box_synchronous(const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::future & future)
////{
////
////   auto posmessagebox = allocateø ::acme::auto pmessageboxpayload = __initialize_new ::message_box_payload(scopedstrText, pszTitle, emessagebox);

//send(pmessageboxpayload);
////
////   return __realize(posmessagebox, process);
////
////}
////
//
//#endif


//::platform::system * system();


CLASS_DECL_ACME bool __assert_failed_line(const_char_pointer pszFileName, ::i32 iLineNumber)
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


CLASS_DECL_ACME ::payload __cpp_assert_failed_line(const_char_pointer pszFileName, ::i32 iLineNumber)
{

   ::i8 szMessage[1024*4];

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running", pszFileName,iLineNumber);

   auto pmessagebox = ::system()->createø<::user_interface::message_box>();

   pmessagebox->initialize_message_box(
         szMessage,
         "ASSERT",
         ::user::e_message_box_cancel_try_continue | ::user::e_message_box_icon_error);

   pmessagebox->display(e_display_normal, {});

   pmessagebox->wait_dialog_response();

   return pmessagebox->get_dialog_response();

}

