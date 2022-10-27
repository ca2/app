#include "framework.h"

#include "acme/operating_system/_const_console.h"
#include "acme/operating_system/console.h"
#include "console.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/context.h"


namespace graphics
{


   int next_char(char & ch, const char *& psz, int & x, int & y, int cx, int cy)
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

      return 0;

   }


   console::console(::user::interaction * puserinteraction, ::size_i32 sizeTile) :
      m_puserinteraction(puserinteraction),
      m_sizeTile(sizeTile)
   {

      m_cout.m_p = this;

      m_x = 0;
      m_y = 0;
      m_iBorder = 23;

   }

   
   console::~console()
   {


   }


   string_stream & console::cout()
   {

      return m_cout;

   }


   void console::assert_ok() const
   {


   }



   void console::dump(dump_context& dump) const
   {


   }



   void console::SetWindowSize(int iHeight, int iWidth)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_sizeWindow.cx = iWidth;

      m_sizeWindow.cy = iHeight;

      ::size_i32 sizeImage(m_sizeTile.cx * m_sizeWindow.cx + m_iBorder * 2, m_sizeTile.cy * m_sizeWindow.cy + m_iBorder * 2);

      m_pimage = m_pcontext->m_pauracontext->create_image(sizeImage);

      m_pimage->g()->m_pdraw2dhost = m_puserinteraction;

      __construct(m_pimage->g()->m_pfont);

#ifdef LINUX

      m_pimage->g()->m_pfont->create_pixel_font("Ubuntu Mono", m_sizeTile.cy * 0.92);

#else

      m_pimage->g()->m_pfont->create_pixel_font("Lucida Console", m_sizeTile.cy * 0.92);

#endif

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

      //m_pimage->g()->FillSolidRect(0,iLineStart * m_sizeTile.cy,m_pimage->width(),m_pimage->height() - iLineStart * m_sizeTile.cy,console_dos_color(color));

      //update_image();

   }


   void console::write(const ::string & strParam)
   {
      synchronous_lock synchronouslock(this->synchronization());

      auto psz = strParam.c_str();
      string str;
      //int i2 = 2;
      while (*psz)
      {
         char ch = *psz;
         while (m_stra.element_at_grow(m_y).get_length() < m_x + 1)
         {
            m_stra.element_at_grow(m_y) += ' ';
         }
         m_stra.element_at_grow(m_y).set_at(m_x, ch);
         m_i2aColor.element_at_grow(m_y).element_at_grow(m_x) = m_iColor;

         m_x++;

         if (m_x >= (m_pimage->width() / m_sizeTile.cx))
         {
            m_x = 0;
            m_y++;
         }

         psz++;
      }

   }


   void console::write(const void * pdata, memsize nCount)
   {

#ifdef WINDOWS

      string str((const ::string &)pdata, minimum(strnlen_s((const ::string &)pdata, (size_t)nCount), nCount));

#else
      string str((const ::string &)pdata, minimum(strnlen((const ::string &)pdata, (size_t)nCount), nCount));

#endif
      write(str);
   }


   void console::update_image()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage.nok())
      {

         return;

      }

      ::color::color crScreen = console_dos_color(m_edoscolor);

      m_pimage->fill(crScreen);

      for (int y = 0; y < m_stra.get_count(); y++)
      {

         string & str = m_stra[y];

         for (int x = 0; x < str.get_length(); x++)
         {

            draw_write(str[x], x, y, (enum_dos_color) m_i2aColor[y][x]);

         }

      }

   }


   bool console::defer_write(char ch, int x, int y, int cx, int cy, int edoscolor)
   {

      return false;

   }

   ::draw2d::pen_pointer & console::get_pen2(enum_dos_color edoscolor)
   {

      ::draw2d::pen_pointer & ppen2 = m_mappen2[edoscolor];

      if (ppen2.is_null())
      {

         ppen2.create(this);

         ppen2->create_solid(2.0, console_dos_color(edoscolor));

      }

      return ppen2;

   }


   ::draw2d::pen_pointer & console::get_pen1(enum_dos_color edoscolor)
   {

      ::draw2d::pen_pointer & ppen1 = m_mappen1[edoscolor];

      if (ppen1.is_null())
      {

         ppen1.create(this);

         ppen1->create_solid(1.0, console_dos_color(edoscolor));

      }

      return ppen1;

   }


   void console::draw_write(char ch, int x, int y, enum_dos_color edoscolor)
   {

      if (ch == ' ')
      {
         
         return;

      }

      string str;

      int i2 = 2;

      if (!defer_write(ch, m_iBorder + x * m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy, m_sizeTile.cx, m_sizeTile.cy, edoscolor))
      {

         m_pimage->g()->set_smooth_mode(::draw2d::e_smooth_mode_none);

         if (ch == (char)209)// horizontal double / down simple
         {

            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);

            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);

            m_pimage->g()->set(ppen2);

            m_pimage->g()->draw_line(
               ::point_i32(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );

            m_pimage->g()->set(ppen1);

            m_pimage->g()->draw_line(
               ::point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
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

            m_pimage->g()->draw_line(
               point_i32(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
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

            m_pimage->g()->draw_line(
               point_i32(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
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

            m_pimage->g()->draw_line(
               point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy),
               point_i32(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 2;

         }
         else if (ch == (char)199) // vertical double / right simple
         {
            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);
            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);
            m_pimage->g()->set(ppen2);

           m_pimage->g()->draw_line(
              ::point_f64( m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy ),
              ::point_f64( m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
              m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1 )
            );
            m_pimage->g()->set(ppen1);

            m_pimage->g()->draw_line(
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );

            m_iLastPenColor = edoscolor;
            m_iLastPen = 1;

         }
         else if (ch == (char)182) // vertical double / left simple
         {
            ::draw2d::pen_pointer & ppen2 = get_pen2(edoscolor);
            ::draw2d::pen_pointer & ppen1 = get_pen1(edoscolor);
            m_pimage->g()->set(ppen2);

            m_pimage->g()->draw_line(
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy),
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, 
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
            );
            m_pimage->g()->set(ppen1);

            m_pimage->g()->draw_line(
               ::point_f64(m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
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

            m_pimage->g()->draw_line(
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy),
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, 
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
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

            m_pimage->g()->draw_line(
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point_f64(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, 
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
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

           m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
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

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
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

           m_pimage->g()->draw_text(str, rectangle_i32(m_iBorder + x * m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy), e_align_center);

         }

      }

   }


   string console::as_string() const
   {

      throw ::not_implemented();

      return {};

   }


} // namespace graphics



