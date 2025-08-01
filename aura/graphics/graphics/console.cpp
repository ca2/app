#include "framework.h"
#include "console.h"
#include "acme/exception/not_implemented.h"
#include "acme/operating_system/_const_console.h"
#include "acme/operating_system/console.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/string/international.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/write_text/font_family.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/context.h"


namespace graphics
{


   int next_char(char & ch, const_char_pointer &psz, int & x, int & y, int cx, int cy)
   {

      if (!*psz)
      {

         return 0;

      }

      int iAdvance = 0;

      if (*psz == '\n')
      {

         psz++;

         iAdvance++;

         if (*psz == '\r')
         {

            psz++;

            iAdvance++;

         }

         y++;

         x = 0;

      }
      else if (*psz == '\r')
      {

         psz++;

         iAdvance++;

         if (*psz == '\n')
         {

            psz++;

            iAdvance++;

         }

         y++;

         x = 0;

      }
      else
      {

         x++;

      }

      if (y >= cy)
      {

         return false;

      }

      ch = *psz;

      psz++;

      iAdvance++;

      return iAdvance;

   }


   ::color::color console::console_dos_color(enum_dos_color edoscolor)
   {

      switch (edoscolor)
      {
      case e_dos_color_background_white:
      case e_dos_color_foreground_white:
         return argb(255, 255, 255, 255);
      case e_dos_color_background_blue:
      case e_dos_color_foreground_blue:
         return argb(255, 127, 127, 255);
      case e_dos_color_background_dark_blue:
      case e_dos_color_foreground_dark_blue:
         return argb(255, 0, 0, 255);
      case e_dos_color_background_red:
      case e_dos_color_foreground_red:
         return argb(255, 255, 0, 0);
      case e_dos_color_background_cyan:
      case e_dos_color_foreground_cyan:
         return argb(255, 0, 255, 255);
      case e_dos_color_background_magenta:
      case e_dos_color_foreground_magenta:
         return argb(255, 255, 0, 255);
      case e_dos_color_background_yellow:
      case e_dos_color_foreground_yellow:
         return argb(255, 255, 255, 0);
      case e_dos_color_background_black:
         return argb(255, 0, 0, 0);
      default:
         break;
      }

      return {};

   }


   console::console(::user::interaction * puserinteraction, ::int_size sizeTile) :
      m_puserinteraction(puserinteraction),
      m_sizeTile(sizeTile),
      ::console::console(this)
   {

      m_x = 0;
      m_y = 0;
      m_iBorder = 23;

   }

   
   console::~console()
   {


   }


//   write_text_stream <::file::file> & console::cout()
//   {
//
//      return m_cout;
//
//   }


//   void console::assert_ok() const
//   {
//
//
//   }
//
//
//
//   void console::dump(dump_context& dump) const
//   {
//
//
//   }



   void console::SetWindowSize(int iHeight, int iWidth)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_sizeWindow.cx() = iWidth;

      m_sizeWindow.cy() = iHeight;

      ::int_size sizeImage(m_sizeTile.cx() * m_sizeWindow.cx() + m_iBorder * 2, m_sizeTile.cy() * m_sizeWindow.cy() + m_iBorder * 2);

      m_pimage = image()->create_image(sizeImage);

      m_pimage->g()->m_pdraw2dhost = m_puserinteraction;

      m_papplication->__øconstruct(m_pimage->g()->m_pfont);

      m_pimage->g()->m_pfont->create_font(e_font_monospace, ::write_text::font_size(m_sizeTile.cy() * 0.92, e_unit_pixel));

      SetScreenColor(e_dos_color_background_black);

   }


   void console::SetCursorVisibility(bool show)
   {
   }

   void console::SetCursorPosition(int y, int x)
   {

      m_x = x;
      m_y = y;

   }

   void console::SetTextColor(int color)
   {
      m_iColor = color;
      m_iTextColor = color;

   }


   void console::SetScreenColor(::enum_dos_color color, int iLineStart, int iLineCount)
   {

      m_edoscolor = color;
      //synchronous_lock synchronouslock(m_pmutex);

      //m_pimage->g()->FillSolidRect(0,iLineStart * m_sizeTile.cy(),m_pimage->width(),m_pimage->height() - iLineStart * m_sizeTile.cy(),console_dos_color(color));

      //update_image();

   }


   void console::write(const ::scoped_string & scopedstrParam)
   {
      synchronous_lock synchronouslock(this->synchronization());

      ::string strParam(scopedstrParam);
      auto psz = strParam.c_str();
      string str;
      //int i2 = 2;
      while (*psz)
      {
         char ch = *psz;
         while (m_stra.element_at_grow(m_y).length() < m_x + 1)
         {
            m_stra.element_at_grow(m_y) += ' ';
         }
         m_stra.element_at_grow(m_y).set_at(m_x, ch);
         m_i2aColor.element_at_grow(m_y).element_at_grow(m_x) = m_iColor;

         m_x++;

         if (m_x >= (m_pimage->width() / m_sizeTile.cx()))
         {
            m_x = 0;
            m_y++;
         }

         psz++;
      }

   }


   void console::write(const void * p, ::memsize s)
   {

      auto data = (unsigned char *)p;

      string str((const_char_pointer )data, minimum(ansi_nlen((const_char_pointer )data, (size_t)s), s));

      write(str);

   }


   void console::update_image()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage.nok())
      {

         return;

      }

      ::color::color crScreen = console_dos_color(m_edoscolor);

      m_pimage->clear(crScreen);

      for (int y = 0; y < m_stra.get_count(); y++)
      {

         string & str = m_stra[y];

         for (int x = 0; x < str.length(); x++)
         {

            draw_write(str[x], x, y, (enum_dos_color) m_i2aColor[y][x]);

         }

      }

   }


   bool console::defer_write(char ch, const ::int_rectangle & r, int edoscolor)
   {

      return false;

   }

   ::draw2d::pen_pointer & console::get_pen2(enum_dos_color edoscolor)
   {

      ::draw2d::pen_pointer & ppen2 = m_mappen2[edoscolor];

      if (ppen2.is_null())
      {

         __øconstruct(ppen2);

         ppen2->create_solid(2.0, console_dos_color(edoscolor));

      }

      return ppen2;

   }


   ::draw2d::pen_pointer & console::get_pen1(enum_dos_color edoscolor)
   {

      ::draw2d::pen_pointer & ppen1 = m_mappen1[edoscolor];

      if (ppen1.is_null())
      {

         __øconstruct(ppen1);

         ppen1->create_solid(1.0, console_dos_color(edoscolor));

      }

      return ppen1;

   }


   ::int_rectangle console::_get_position_rectangle(int y, int x)
   {
   
      ::int_rectangle r;
      
      
      r.left() = x * m_sizeTile.cx();
      
      r.top() = y * m_sizeTile.cy();
      
      r.right() = r.left() + m_sizeTile.cx();
      
      r.bottom() = r.top() + m_sizeTile.cy();
      
      return r;
      
   }


   ::int_rectangle console::get_position_rectangle(int y, int x)
   {

      ::int_rectangle r;
      
      r = _get_position_rectangle(y, x);
      
      r.offset(m_iBorder, m_iBorder);
      
      return r;
      
   }


   void console::draw_write(char ch, int x, int y, enum_dos_color edoscolor)
   {

      if (ch == ' ')
      {
         
         return;

      }

      string str;

      int i2 = 2;
      
      auto r = get_position_rectangle(y, x);

      if (!defer_write(ch, r, edoscolor))
      {

         m_pimage->g()->set_smooth_mode(::draw2d::e_smooth_mode_none);

         if (ch == (char)209)// horizontal double / down simple
         {

            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

            m_pimage->g()->set(ppen2);

            m_pimage->g()->line(
               ::int_point(m_iBorder + x * m_sizeTile.cx(),
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               ::int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );

            m_pimage->g()->set(ppen1);

            m_pimage->g()->line(
               ::int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               ::int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)205)// horizontal double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

            m_pimage->g()->line(
               int_point(m_iBorder + x * m_sizeTile.cx(),
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)196) // horizontal simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

               m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               int_point(m_iBorder + x * m_sizeTile.cx(),
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)186) // vertical double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

            m_pimage->g()->line(
               int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
                  m_iBorder + y * m_sizeTile.cy()),
               int_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)199) // vertical double / right simple
         {
            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);
            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);
            m_pimage->g()->set(ppen2);

           m_pimage->g()->line(
              ::double_point( m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() ),
              ::double_point( m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
              m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1 )
            );
            m_pimage->g()->set(ppen1);

            m_pimage->g()->line(
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)182) // vertical double / left simple
         {
            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);
            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);
            m_pimage->g()->set(ppen2);

            m_pimage->g()->line(
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy()),
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, 
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1)
            );
            m_pimage->g()->set(ppen1);

            m_pimage->g()->line(
               ::double_point(m_iBorder + x * m_sizeTile.cx(),
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)179) // vertical simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

               m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy()),
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, 
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)218) // top-left simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

               m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2),
               ::double_point(m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1, 
                  m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2)
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy()
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)201) // top-left double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2 - i2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)200) // bottom-left double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2 - i2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy()
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)192) // bottom-left simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

               m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() + 1, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy()
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)188) // bottom-right double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

           m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx(),
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2 + i2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy()
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)217) // bottom-right simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

               m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx(),
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy()
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)187) // top-right double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

               m_pimage->g()->set(ppen2);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx(),
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2 + i2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)191) // top-right simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != edoscolor)
            {

               ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

              m_pimage->g()->set(ppen1);

            }

            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx(),
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2
            );
            m_pimage->g()->line(
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2,
               m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() / 2,
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx() / 2, m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy() + 1
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else
         {

            string str;

            multibyte_to_utf8(437, str, string(ch));

            //str = ch;

            m_pimage->g()->set_text_color(console_dos_color(edoscolor));

           m_pimage->g()->draw_text(str, int_rectangle(m_iBorder + x * m_sizeTile.cx(), m_iBorder + y * m_sizeTile.cy(),
               m_iBorder + x * m_sizeTile.cx() + m_sizeTile.cx(), m_iBorder + y * m_sizeTile.cy() + m_sizeTile.cy()), e_align_center);

         }

      }

   }


   string console::right_string(::memsize iReadAtMostByteCount)
   {

      throw ::not_implemented();

      return {};

   }


} // namespace graphics



