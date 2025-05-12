#include "framework.h"
#include "acme/operating_system/_const_console.h"
#include "acme/operating_system/console.h"
#include "acme/prototype/collection/strdup_array.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/rectangle.h"
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


   ::int_rectangle console::get_position_rectangle(int y, int x)
   {
    
      throw ::interface_only();
      
      return {};
      
   }


} // namespace console


//#if !defined(UNIVERSAL_WINDOWS) || defined(_UWP_CONSOLE)


void press_any_key_to_exit(const ::scoped_string & scopedstrPrompt)
{

   string strPrompt;

   if (scopedstrPrompt.has_character())
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

#if defined(UNIVERSAL_WINDOWS) || defined(__ANDROID__) || defined(APPLE_IOS)

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


//CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
//{
//
//   return message_box_for_console(scopedstr, scopedstrTitle, emessagebox, nullptr);
//
//}


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
//   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (unsigned int)nCount, &dw, nullptr);
//
//#else
//
//   fwrite(pdata, nCount, 1, stdout);
//
//
//#endif
//
//}
