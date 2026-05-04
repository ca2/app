// Created by camilo on 2026-03-25 18:33 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/console.h"
#include <termios.h>
#include <unistd.h>

int current_getch();

int current_getch_utf8(::string & strChar);

namespace console
{


   void console::defer_non_root()
   {

      // getuid() returns 0 for the root user
      if (getuid() == 0) {
         error() << "WARNING: This program should not be run as root.";
         // Optionally exit, or just warn
         // exit(EXIT_FAILURE);
         throw ::exception(error_failed);
      }

      information() << "Running with user ID: " << getuid();

   }


   void console::start_input()
   {


      setbuf(stdout, 0);

   }


   int console::getch(void) {
      return ::current_getch();

   }

   int console::get_thoughtful_character()
   {

      int iCharacter;

      while (true)
      {

         class ::time timeStart;

         timeStart.Now();

         iCharacter = current_getch();

         if (iCharacter == EOF)
         {

            break;

         }
         else if (timeStart.elapsed() > 75_ms)
         {

            break;

         }

      }

      return iCharacter;

   }



   enum_response console::yes_no(const char * pszPrompt)
   {

      while (true)
      {

         print_line(pszPrompt);

         auto iCharacter = get_thoughtful_character();

         if (tolower(iCharacter) == 'y')
         {

            return e_response_yes;

         }
         else if (tolower(iCharacter) == 'n')
         {

            return e_response_no;

         }
         else if (iCharacter == EOF)
         {

            throw "cancel";

         }

      }

   }

   enum_response console::yes_no_default_yes(const char * pszPrompt)
   {

      while (true)
      {

         print_line(pszPrompt);

         auto iCharacter = get_thoughtful_character();

         if (tolower(iCharacter) == 'y')
         {

            return e_response_yes;

         }
         else if (tolower(iCharacter) == 'n')
         {

            return e_response_no;

         }
         else if (iCharacter == '\n')
         {

            return e_response_yes;

         }
         else if (iCharacter == EOF)
         {

            throw "cancel";

         }

      }

   }

   //
   // void application::install_chrome()
   // {
   //
   //    print_line("");
   //    print_line("");
   //    bool bInstallChrome = yes_no_default_yes("Install Chrome? (Y/n)");
   //    print_line("");
   //    print_line("");
   //
   //    if (bInstallChrome)
   //    {
   //
   //
   //       print_line("Chrome installed");
   //       print_line("");
   //       print_line("");
   //
   //
   //    }
   //
   //
   //
   //
   // }

   ::string console::prompt_line(const char * pszPrompt)
   {

      if (pszPrompt && *pszPrompt)
      {

         print_out(pszPrompt);

      }

      ::string strLine;

      int iRet;

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



