#include "framework.h"


#include "acme/operating_system/_const_console.h"
#include "acme/operating_system/console.h"
#include "acme/primitive/collection/strdup_array.h"
#include <stdio.h>
#ifdef WINDOWS
#include <conio.h>
#endif
#if defined(HAVE_TERMIOS_H) && HAVE_TERMIOS_H
int getche();
#endif




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


   console_client::console_client()
   {

   }


   console_client::~console_client()
   {

   }


   void console_client::redirect_io()
   {

      get_console()->redirect_io();

   }


   console * console_client::get_console()
   {

      //get_console() = pconsole;

      //cout.m_p = pconsole->cout.m_p;

      return nullptr;

   }


   string_stream & console_client::cout()
   {

      return get_console()->cout();

   }


   void console_client::SetWindowSize(int iHeight, int iWidth)
   {

      get_console()->SetWindowSize(iHeight, iWidth);

   }


   void console_client::SetCursorVisibility(bool show)
   {

      get_console()->SetCursorVisibility(show);

   }


   void console_client::SetCursorPosition(int y, int x)
   {

      get_console()->SetCursorPosition(y, x);

   }


   void console_client::SetTextColor(int color)
   {
      m_iTextColor = color;

      get_console()->SetTextColor(color);

   }


   void console_client::SetScreenColor(enum_dos_color edoscolor, int iLineStart, int iLineCount)
   {

      get_console()->SetScreenColor(edoscolor, iLineStart, iLineCount);

   }


   void console_client::write(const ::string & str)
   {

      get_console()->write(str);

   }


} // namespace console

//#if !defined(_UWP) || defined(_UWP_CONSOLE)


void press_any_key_to_exit(const char * pszPrompt)
{

   string strPrompt;

   if (pszPrompt)
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


int safe_get_any_char(const ::duration & duration)
{

   int iSafeChar = EOF;

   ::duration millisStart;

   do
   {

      millisStart.Now();

#ifdef _UWP

      iSafeChar = getchar();

#else

      iSafeChar = getche();

#endif

   } while (millisStart.elapsed() < duration);

   return iSafeChar;

}


int safe_get_char(FILE * pfile, const ::duration & duration)
{

   int iSafeChar = EOF;

   ::duration millisStart;

   while (true)
   {

      millisStart.Now();

      iSafeChar = getc(pfile);

      if (!ansi_char_is_space(iSafeChar) && millisStart.elapsed() > duration)
      {

         break;

      }

      if (iSafeChar == -1)
      {

         clearerr(pfile);

      }

   }

   return iSafeChar;

}


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const char * psz, const char * pszTitle, const ::enum_message_box & emessagebox)
{

   string strLine;

   strLine = "\n";

   if (strlen(pszTitle) > 0)
   {

      strLine += pszTitle;

      strLine += "\n";

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

      strLine += "\n(" + str + ") ? ";

   }
   else
   {

      strLine += "\n(Press any key to continue) ";

   }

   enum_dialog_result edialogresult = edialogresultDefault;

   bool bAnswer = false;

repeat:

   if (emessagebox & e_message_box_icon_exclamation || emessagebox & e_message_box_icon_stop)
   {

      fputs(strLine, stderr);

      fflush(stderr);

   }
   else
   {

      fputs(strLine, stdout);

      fflush(stdout);

   }

   const char * pszAcceptedAnswer = "";

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


//#endif


#if defined(HAVE_TERMIOS_H) && HAVE_TERMIOS_H


#include <unistd.h>
#include <termios.h>


int getche()
{

   struct termios termiosOld = {0};

   if (tcgetattr(STDIN_FILENO, &termiosOld) < 0)
   {

      return -1;

   }

   auto termiosNew = termiosOld;

   termiosNew.c_lflag &= ~ICANON;
   termiosNew.c_lflag &= ~ECHO;

   if (tcsetattr(0, TCSANOW, &termiosNew) < 0)
   {

      return -1;

   }

   char ch = -1;

   auto iRead = read(0, &ch, 1);

   if (tcsetattr(0, TCSADRAIN, &termiosOld) < 0)
   {

      return -1;

   }

   return ch;

}


#endif // defined(HAVE_TERMIOS_H) && HAVE_TERMIOS_Hc



