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
::i32 getche();
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


   void console::SetWindowSize(::i32 iHeight,::i32 iWidth)
   {

      throw ::interface_only();

   }


   void console::SetCursorVisibility(bool show)
   {

      throw ::interface_only();

   }


   void console::SetCursorPosition(::i32 y,::i32 x)
   {

      throw ::interface_only();

   }


   void console::SetTextColor(::i32 color)
   {

      throw ::interface_only();

   }


   void console::SetScreenColor(::enum_dos_color color,::i32 iLineStart,::i32 iLineCount)
   {

      throw ::interface_only();

   }


   void console::write(const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

   }





   ::i32_rectangle console::get_position_rectangle(::i32 y, ::i32 x)
   {
    
      throw ::interface_only();
      
      return {};
      
   }

   

   ::string console::prompt_line(const_char_pointer pszPrompt)
   {

      if (pszPrompt && *pszPrompt)
      {

         print_out(pszPrompt);
      }

      ::string strLine;

      ::i32 iRet;

      while (true)
      {

         ::string strChar;

         iRet = ::current_getch_utf8(strChar);

         if (iRet == EOF)
         {

            throw "cancel";
         }
         else if (strChar == "\n")
         {

            break;
         }
         else if (strChar == "\r")
         {

            // ignore carriage return (for safety)
            continue;
         }
         else if (strChar[0] == 127 || strChar == "\b")
         {

            // handle backspace
            if (strLine.has_character())
            {

               strLine.truncate(utf8_dec(strLine.begin(), strLine.end()));

               // erase character visually
               printf("\b \b");
            }
         }
         else
         {

            strLine += strChar;

            // echo character
            printf("%s", strChar.c_str());
         }
      }

      // move to next line after Enter
      putchar('\n');

      return strLine;
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

   ::i32 iGetChar = getchar();

   if(iGetChar == EOF)
   {

      printf("Error getting character.");

   }

}


::i32 safe_get_any_char(const class time & time)
{

   ::i32 iSafeChar = EOF;

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


::i32 safe_get_char(FILE * pfile, const class time & time)
{

   ::i32 iSafeChar = EOF;

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


::i32 getche()
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

   ::i8 ch = -1;

   auto iRead = read(0, &ch, 1);

   if (tcsetattr(0, TCSADRAIN, &termiosOld) < 0)
   {

      return -1;

   }

   return ch;

}




#endif // defined(HAVE_TERMIOS_H) && HAVE_TERMIOS_Hc


enum_dialog_result message_box_for_console(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrTitle,
   const ::user::enum_message_box& emessagebox)
{

   //return message_box_for_console(scopedstr, scopedstrTitle, emessagebox, nullptr);

   throw todo;

   return e_dialog_result_none;

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


CLASS_DECL_ACME ::i32 current_getch_utf8(::string & strChar)
{

   strChar.empty();

   ::i32 first = current_getch(); // your existing function

   if (first == EOF)
   {
      return EOF;
   }

   ::u8 c = (::u8) first;

   // 1-byte ASCII
   if ((c & 0x80) == 0)
   {
      strChar += (::i8)c;
      return 1;
   }

   // Determine UTF-8 sequence length
   ::i32 extra = 0;

   if ((c & 0xE0) == 0xC0) extra = 1;        // 2 bytes
   else if ((c & 0xF0) == 0xE0) extra = 2;   // 3 bytes
   else if ((c & 0xF8) == 0xF0) extra = 3;   // 4 bytes
   else
   {
      throw ::exception(error_failed, "Invalid UTF-8 start byte");
   }

   strChar += (::i8)c;

   for (::i32 i = 0; i < extra; i++)
   {
      ::i32 next = current_getch();

      if (next == EOF)
      {
         throw ::exception(error_failed, "Unexpected EOF in UTF-8 sequence");
      }

      strChar += (::i8)next;
   }

   return 1;

}



