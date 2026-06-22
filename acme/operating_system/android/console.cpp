// From acme/operating_system/freebsd/console.cpp by
// camilo on 2026-06-21 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system/console.h"

#include <stdio.h>


namespace console
{


   void console::defer_non_root()
   {

      // Android app processes do not run as root in the usual NDK app case.

   }


   void console::start_input()
   {

      setbuf(stdout, nullptr);

   }


   ::i32 console::getch()
   {

      return EOF;

   }


   ::i32 console::get_thoughtful_character()
   {

      return EOF;

   }


   enum_response console::yes_no(const_char_pointer pszPrompt)
   {

      if (pszPrompt && *pszPrompt)
      {

         print_line(pszPrompt);

      }

      return e_response_cancel;

   }


   enum_response console::yes_no_default_yes(const_char_pointer pszPrompt)
   {

      if (pszPrompt && *pszPrompt)
      {

         print_line(pszPrompt);

      }

      return e_response_cancel;

   }


} // namespace console


