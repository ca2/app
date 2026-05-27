// from console.cpp by camilo on 2022-09-04 09:07 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "console_client.h"
#include "acme/prototype/geometry2d/rectangle.h"


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


   void console_client::SetWindowSize(::i32 iHeight, ::i32 iWidth)
   {

      get_console()->SetWindowSize(iHeight, iWidth);

   }


   void console_client::SetCursorVisibility(bool show)
   {

      get_console()->SetCursorVisibility(show);

   }


   void console_client::SetCursorPosition(::i32 y, ::i32 x)
   {

      get_console()->SetCursorPosition(y, x);

   }


   void console_client::SetTextColor(::i32 color)
   {
      m_iTextColor = color;

      get_console()->SetTextColor(color);

   }


   void console_client::SetScreenColor(enum_dos_color edoscolor, ::i32 iLineStart, ::i32 iLineCount)
   {

      get_console()->SetScreenColor(edoscolor, iLineStart, iLineCount);

   }


   void console_client::write(const ::scoped_string & scopedstr)
   {

      get_console()->write(scopedstr);

   }


   ::i32_rectangle console_client::get_position_rectangle(::i32 y, ::i32 x)
   {
    
      return get_console()->get_position_rectangle(y, x);
      
   }


} // namespace console



