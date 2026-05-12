//
// Created by camilo on 2023-12-19 04:57 <3ThomasBorregaardSorensen!!
// From https://github.com/ca2/motif_labs
//
#include <AppKit/AppKit.h>

//#include "acme/constant/"
//#include "message_box.h"
//
//enum_dialog_result ns_alert_box(const_char_pointer pszMessage, const_char_pointer pszTitle, enum_message_box emessagebox);
//
//namespace macos
//{
//
//
//   ///::atom message_box::do_modal(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
//   ::payload message_box::do_synchronously(const class time & timeWait)
//   {
//
//      ::string strMessage(m_strMessage);
//      ::string strTitle(m_strTitle);
//
//      auto edialogresult = ns_alert_box(strMessage, strTitle, m_emessagebox);
//
//      return edialogresult;
//
//   }
//
////#else
////   real_message_box_fallback();
////#endif
//
//
//} // macos
//
//
//void macos_message_box_factory(::factory::factory * pfactory)
//{
//
//   pfactory->add_factory_item < ::macos::message_box, ::operating_system::message_box >();
//
//}
//
//
//




//// Return values to mimic Win32 IDYES/IDNO
//enum {
//    MAC_IDOK = 1,
//    MAC_IDCANCEL = 2,
//    MAC_IDYES = 3,
//    MAC_IDNO = 4
//};

int ns_message_box(const char* title, const char* message, int yesNoStyle)
{
    NSAlert *alert = [[NSAlert alloc] init];
    
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:message]];
    [alert setAlertStyle:NSAlertStyleInformational];

    if (yesNoStyle) {
        [alert addButtonWithTitle:@"Yes"];   // Index 1000
        [alert addButtonWithTitle:@"No"];    // Index 1001
    } else {
        [alert addButtonWithTitle:@"OK"];     // Index 1000
        [alert addButtonWithTitle:@"Cancel"]; // Index 1001
    }

    NSInteger result = [alert runModal];

    // Map NSAlert returns back to our custom enum
    if (yesNoStyle) {
        return (result == NSAlertFirstButtonReturn) ? e_dialog_result_yes : e_dialog_result_no;
    } else {
        return (result == NSAlertFirstButtonReturn) ? e_dialog_result_ok :e_dialog_result_cancel;
    }
}
