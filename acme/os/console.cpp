#include "framework.h"
#include "acme/os/console.h"
#include <stdio.h>





namespace console
{


   console::console()
   {


   }


   console::~console()
   {


   }


   void console::redirect_io()
   {

   }


   console_composite::console_composite()
   {

   }


   console_composite::~console_composite()
   {

   }


   void console_composite::redirect_io()
   {

      m_pconsole->redirect_io();

   }


   void console_composite::set_console(console* pconsole)
   {

      m_pconsole = pconsole;

      cout.m_p = pconsole->cout.m_p;

   }


   void console_composite::SetWindowSize(int iHeight, int iWidth)
   {

      m_pconsole->SetWindowSize(iHeight, iWidth);

   }


   void console_composite::SetCursorVisibility(bool show)
   {

      m_pconsole->SetCursorVisibility(show);

   }


   void console_composite::SetCursorPosition(int y, int x)
   {

      m_pconsole->SetCursorPosition(y, x);

   }


   void console_composite::SetTextColor(int color)
   {
      m_iTextColor = color;

      m_pconsole->SetTextColor(color);

   }


   void console_composite::SetScreenColor(enum_dos_color edoscolor, int iLineStart, int iLineCount)
   {

      m_pconsole->SetScreenColor(edoscolor, iLineStart, iLineCount);

   }


   void console_composite::write(const char * psz)
   {

      m_pconsole->write(psz);

   }


} // namespace console


void press_any_key_to_exit(const char * pszPrompt)
{

   string strPrompt;

   if(pszPrompt)
   {

      strPrompt = pszPrompt;

   }
   else
   {

      strPrompt = "Press any key to exit.";

   }

   printf("%s\n", strPrompt.c_str());

   getchar();

}

int safe_get_char(FILE * pfile, const ::duration & duration)
{

   int iSafeChar = EOF;

   ::millis millisStart;

   do
   {

      millisStart.Now();

      iSafeChar = getc(pfile);

   }
   while(ansi_char_is_space(iSafeChar) || millisStart.elapsed() < duration);

   return iSafeChar;

}

enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::e_message_box & emessagebox)
{

   string strLine;

   strLine = "\n";

   if (strlen(pszTitle) > 0)
   {

      strLine += pszTitle;

      strLine += " : ";

   }

   strLine += psz;

   enum_dialog_result edialogresultDefault = e_dialog_result_ok;

   string str;

   auto etype = (emessagebox & e_message_box_type_mask);

   if (etype == e_message_box_yes_no_cancel)
   {
      str += "y/n/c";
   }
   else if (etype == e_message_box_yes_no)
   {
      str += "y/n";
   }

   bool bDefault = false;

   auto edefaultbutton = (emessagebox & e_message_box_default_button_mask);

   if (edefaultbutton == e_message_box_default_button_1 && str.get_length() >= 1)
   {
      str.set_at(0, ansi_char_uppered(str[0]));
      edialogresultDefault = e_dialog_result_yes;
      bDefault = true;
   }
   else if (edefaultbutton == e_message_box_default_button_2 && str.get_length() >= 3)
   {
      str.set_at(2, ansi_char_uppered(str[2]));
      edialogresultDefault = e_dialog_result_no;
      bDefault = true;
   }
   else if (edefaultbutton == e_message_box_default_button_3 && str.get_length() >= 5)
   {
      str.set_at(4, ansi_char_uppered(str[4]));
      edialogresultDefault = e_dialog_result_cancel;
      bDefault = true;
   }

   if (str.has_char())
   {

      strLine += " : (" + str + ") ? ";

   }
   else
   {

      strLine += " : (OK) ";

   }

   enum_dialog_result edialogresult = edialogresultDefault;

   bool bAnswer = false;

repeat:

   if (emessagebox & e_message_box_icon_exclamation || emessagebox & e_message_box_icon_stop)
   {

      fputs(strLine, stderr);

   }
   else
   {

      fputs(strLine, stdout);

   }

   int c = safe_get_char(stdin, 100_ms);

   c = ::ansi_tolower(c);

   if (etype == e_message_box_yes_no_cancel)
   {

      bAnswer = ::ansi_chr("ync", c) != nullptr;

   }
   else if (etype == e_message_box_yes_no)
   {

      bAnswer = ::ansi_chr("yn", c) != nullptr;

   }
   else
   {

      bAnswer = true;

   }

   if (!bAnswer)
   {

      goto repeat;

   }

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

   return edialogresult;

}
