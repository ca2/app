//
//  user.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-06-12.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//


#import <Foundation/Foundation.h>


class ns_alert_box
{
public:
   
   NSAlert * m_palert;
   int m_iButtonCount = 0;
   enum_dialog_result m_edialogresulta[4];

   ns_alert_box(const char * pszMessage, const char * pszTitle, enum_message_box emessagebox)
   {
      m_palert = [[NSAlert alloc] init];
      NSString * strMessage = [[NSString alloc]initWithUTF8String:pszMessage];
      [m_palert setMessageText:strMessage];
      //[m_palert runModal];
      //    alert.messageText = "Do you want to save the changes you made in the document?"
      //    alert.informativeText = "Your changes will be lost if you don't save them."
      //int iButtonCount = 0;
      
      switch(emessagebox & e_message_box_type_mask)
      {
         case e_message_box_ok:
            add_button(e_dialog_result_ok);
            break;
         case e_message_box_yes_no:
            add_button(e_dialog_result_yes);
            add_button(e_dialog_result_no);
            break;
         case e_message_box_yes_no_cancel:
            add_button(e_dialog_result_yes);
            add_button(e_dialog_result_no);
            add_button(e_dialog_result_cancel);
            break;
         case e_message_box_ok_cancel:
            add_button(e_dialog_result_ok);
            add_button(e_dialog_result_cancel);
            break;
         default:
            add_button(e_dialog_result_ok);
            break;
      }
      //[ alert addButtonWithTitle: @"OK" ];
      //edialogresulta[0] = e_dialog_result_ok;
      // [ alert addButtonWithTitle: @"Yes" ];
      // edialogresulta[1] = e_dialog_result_yes;
      // [ alert addButtonWithTitle: @"No" ];
      // edialogresulta[2] = e_dialog_result_no;
      
   }
   
   void add_button(enum_dialog_result edialogresult)
   {
      
      if(m_iButtonCount >= 3)
      {
       
         return;
         
      }
      
      switch(edialogresult)
      {
         case e_dialog_result_ok:
            [ m_palert addButtonWithTitle: @"OK" ];
            break;
         case e_dialog_result_yes:
            [ m_palert addButtonWithTitle: @"Yes" ];
            break;
         case e_dialog_result_no:
            [ m_palert addButtonWithTitle: @"No" ];
            break;
         case e_dialog_result_cancel:
            [ m_palert addButtonWithTitle: @"Cancel" ];
            break;
         default:
            [ m_palert addButtonWithTitle: @"Cancel" ];
            break;
      }
      
      m_edialogresulta[m_iButtonCount++] = edialogresult;

   }
   
   enum_dialog_result run_modal()
   {
      
      NSInteger result = [ m_palert runModal];
      switch(result)
      {
      case NSAlertFirstButtonReturn:
            return m_edialogresulta[0];
      case NSAlertSecondButtonReturn:
            return m_edialogresulta[1];
      case NSAlertThirdButtonReturn:
            return m_edialogresulta[2];
      default:
            return e_dialog_result_cancel;
       }
      
   }

};


enum_dialog_result ns_alert_box(const char * pszMessage, const char * pszTitle, enum_message_box emessagebox)
{
   
   class ns_alert_box nsalertbox(pszMessage, pszTitle, emessagebox);
   
   auto edialogresult = nsalertbox.run_modal();
   
   return edialogresult;
   
}




