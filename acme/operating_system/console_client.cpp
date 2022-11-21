// from console.cpp by camilo on 2022-09-04 09:07 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "console_client.h"


namespace console
{


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


//   write_text_stream < ::file::file > & console_client::cout()
//   {
//
//      return get_console()->cout();
//
//   }


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



