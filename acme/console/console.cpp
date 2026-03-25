// Created by camilo on 2026-03-25 18:25 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"



void application::start_input()
{


   setbuf(stdout, 0);

}


int application::getch(void) {
   struct termios oldt, newt;
   int ch;

   tcgetattr(STDIN_FILENO, &oldt);   // save terminal settings
   newt = oldt;
   newt.c_lflag &= ~(ICANON | ECHO); // disable buffered input + echo
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);

   ch = getchar();

   tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore settings
   return ch;
}

int application::get_thoughtful_character()
{

   int iCharacter;

   while (true)
   {

      class ::time timeStart;

      timeStart.Now();

      iCharacter = getch();

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


bool application::yes_no_default_yes(const char * pszPrompt)
{

   while (true)
   {

      print_line(pszPrompt);

      auto iCharacter = get_thoughtful_character();

      if (tolower(iCharacter) == 'y')
      {

         return true;

      }
      else if (tolower(iCharacter) == 'n')
      {

         return false;

      }
      else if (iCharacter == '\n')
      {

         return true;

      }

   }

}


void application::install_chrome()
{

   print_line("");
   print_line("");
   bool bInstallChrome = yes_no_default_yes("Install Chrome? (Y/n)");
   print_line("");
   print_line("");

   if (bInstallChrome)
   {


      print_line("Chrome installed");
      print_line("");
      print_line("");


   }




}
