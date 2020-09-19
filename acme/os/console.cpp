#include "framework.h"
#include "acme/os/console.h"
#include <stdio.h>
#include <conio.h>


void std_out_buffer::write(const void * pdata,memsize nCount)
{

   DWORD dw;

#ifdef WINDOWS

   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (DWORD) nCount, &dw, nullptr);


#else

   fwrite(pdata, nCount, 1, stdout);


#endif

}



namespace console
{


   void console::redirect_io()
   {

   }


   console_composite::console_composite()
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


   void console_composite::SetScreenColor(int color, int iLineStart, int iLineCount)
   {

      m_pconsole->SetScreenColor(color, iLineStart, iLineCount);

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
