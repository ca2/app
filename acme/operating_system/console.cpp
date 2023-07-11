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


   console::console(const ::pointer < ::string_buffer_base > & pstringbuffer) :
      m_cout(pstringbuffer)
   {


   }


   console::~console()
   {


   }


   void console::redirect_io()
   {

   }


} // namespace console


//#if !defined(UNIVERSAL_WINDOWS) || defined(_UWP_CONSOLE)


void press_any_key_to_exit(const ::scoped_string & scopedstrPrompt)
{

   string strPrompt;

   if (scopedstrPrompt.has_char())
   {

      strPrompt = scopedstrPrompt;

   }
   else
   {

      strPrompt = "Press any key to exit.";

   }

   printf("%s\n", strPrompt.c_str());

   getchar();

}


int safe_get_any_char(const class time & time)
{

   int iSafeChar = EOF;

   class ::time timeStart;

   do
   {

      timeStart.Now();

#if defined(UNIVERSAL_WINDOWS) || defined(ANDROID) || defined(APPLE_IOS)

      iSafeChar = getchar();

#else

      iSafeChar = getche();

#endif

   } while (timeStart.elapsed() < time);

   return iSafeChar;

}


int safe_get_char(FILE * pfile, const class time & time)
{

   int iSafeChar = EOF;

   class ::time timeStart;

   while (true)
   {

      timeStart.Now();

      iSafeChar = getc(pfile);

      if (!ansi_char_isspace(iSafeChar) && timeStart.elapsed() > time)
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


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
{

   string strLine;

   strLine = "\n";

   if (scopedstrTitle.size() > 0)
   {

      strLine += scopedstrTitle;

      strLine += "\n";

   }

   strLine += scopedstr;

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

   if (scopedstrDetails.is_empty())
   {

      str += "/d";

   }

   //bool bDefault = false;

   auto edefaultbutton = (emessagebox & e_message_box_default_button_mask);

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

      fputs(strLine.c_str(), stderr);

      fflush(stderr);

   }
   else
   {

      fputs(strLine.c_str(), stdout);

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

      if (scopedstrDetails.has_char())
      {

         if (c == 'd')
         {

            printf("%s", scopedstrDetails.c_str());

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


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
{

   return message_box_for_console(scopedstr, scopedstrTitle, emessagebox, nullptr);

}


std_out_buffer::std_out_buffer()
{

}


std_out_buffer::~std_out_buffer()
{

}






//
//
//void std_out_buffer::write(const void * pdata, memsize nCount)
//{
//
//#ifdef WINDOWS
//
//   DWORD dw;
//
//   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (::u32)nCount, &dw, nullptr);
//
//#else
//
//   fwrite(pdata, nCount, 1, stdout);
//
//
//#endif
//
//}
