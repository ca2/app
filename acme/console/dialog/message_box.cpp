// Created by camilo on 2024-08-09 14:34 <3ThomasBorregaardSorensen!!
// From operating_system/console_message_box
// to console dialog by camilo on 2024-10-08 04:04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/console/dialog.h"
#include <stdio.h>


int safe_get_char(FILE * pfile, const class time & time);
int safe_get_any_char(const class time & time);


namespace console
{


   enum_dialog_result dialog::run_message_box(::message_box * pmessagebox)
   {

      string strLine;

      strLine = "\n";

      if (pmessagebox->m_strTitle.has_character())
      {

         strLine += pmessagebox->m_strTitle;

         strLine += "\n";

      }

      strLine += pmessagebox->m_strMessage;

      enum_dialog_result edialogresultDefault = e_dialog_result_ok;

      string str;

      auto etype = (pmessagebox->m_emessagebox & e_message_box_type_mask);

      if (etype == e_message_box_yes_no_cancel)
      {
         str += "y/n/c";
      }
      else if (etype == e_message_box_yes_no)
      {
         str += "y/n";
      }

      if (pmessagebox->m_strDetails.is_empty())
      {

         str += "/d";

      }

      //bool bDefault = false;

      auto edefaultbutton = (pmessagebox->m_emessagebox & e_message_box_default_button_mask);

      if (edefaultbutton == e_message_box_default_button_1 && str.size() >= 1)
      {
         str.set_at(0, ansi_char_toupper(str[0]));
         edialogresultDefault = e_dialog_result_yes;
         //bDefault = true;
      }
      else if (edefaultbutton == e_message_box_default_button_2 && str.size() >= 3)
      {
         str.set_at(2, ansi_char_toupper(str[2]));
         edialogresultDefault = e_dialog_result_no;
         //bDefault = true;
      }
      else if (edefaultbutton == e_message_box_default_button_3 && str.size() >= 5)
      {
         str.set_at(4, ansi_char_toupper(str[4]));
         edialogresultDefault = e_dialog_result_cancel;
         //bDefault = true;
      }

      if (str.has_character())
      {

         strLine += "\n(" + str + ") ? ";

      }
      else
      {

         strLine += "\n(Press any key to continue) ";

      }

      enum_dialog_result edialogresult = edialogresultDefault;

      bool bAnswer = false;

   repeat:

      if ((pmessagebox->m_emessagebox & e_message_box_icon_exclamation)
         || (pmessagebox->m_emessagebox & e_message_box_icon_stop))
      {

         fputs(strLine.c_str(), stderr);

         fflush(stderr);

      }
      else
      {

         fputs(strLine.c_str(), stdout);

         fflush(stdout);

      }

      const_char_pointer pszAcceptedAnswer = "";

      if (etype == e_message_box_yes_no_cancel)
      {

         pszAcceptedAnswer = "ync";

      }
      else if (etype == e_message_box_yes_no)
      {

         pszAcceptedAnswer = "yn";

      }

      if (ansi_len(pszAcceptedAnswer) > 0)
      {

         int c = safe_get_char(stdin, 100_ms);

         c = ::ansi_tolower(c);

         if (pmessagebox->m_strDetails.has_character())
         {

            if (c == 'd')
            {

               printf("%s", pmessagebox->m_strDetails.c_str());

               goto repeat;

            }

         }

         bAnswer = ::ansi_chr(pszAcceptedAnswer, c) != nullptr;

         switch (c)
         {
         case 'y':
            edialogresult = e_dialog_result_yes;
            break;
         case 'n':
            edialogresult = e_dialog_result_no;
            break;
         case 'c':
            edialogresult = e_dialog_result_cancel;
            break;
         default:
            break;

         }
      }
      else
      {

         int iSafeChar = safe_get_any_char(100_ms);

         bAnswer = true;

         edialogresult = e_dialog_result_ok;

      }

      if (!bAnswer)
      {

         goto repeat;

      }

      return edialogresult;

   }


} // namespace console



