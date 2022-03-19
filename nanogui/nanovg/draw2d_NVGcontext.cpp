// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSørensen!! (Thomas Like number 5)
#include "framework.h"
#include "NVGcontext.h"
#include "draw2d_NVGcontext.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace draw2d
{


   NVGcontext::NVGcontext(::draw2d::graphics_pointer & pgraphics) :
      m_pgraphics(pgraphics)
   {

      m_pgraphics->__construct(m_pbrush);
      m_pgraphics->__construct(m_pfont);


   }


   NVGcontext::~NVGcontext()
   {


   }


   void NVGcontext::font_face(const char * font)
   {

      string strFont(font);

      if (strFont.compare_ci("sans-bold") == 0)
      {

         m_pfont->m_strFontFamilyName = m_pgraphics->m_psystem->node()->font_name(e_font_sans_ui);

         m_pfont->m_iFontWeight = 800;

      }



   }



   void NVGcontext::font_size(float size)
   {

      m_pfont->m_dFontSize = size;
      m_pfont->m_eunitFontSize = ::draw2d::unit_pixel;

   }


   void NVGcontext::fill_color(NVGcolor color)
   {

      m_pbrush->m_color.set(
         color.r,
         color.g,
         color.b,
         color.a);

   }


   void NVGcontext::text_align(int align)
   {

      m_ealignText = e_align_none;

      if (align & NVG_ALIGN_CENTER)
      {

         m_ealignText |= e_align_horizontal_center;


      }
      else if (align & NVG_ALIGN_RIGHT)
      {

         m_ealignText |= e_align_right;

      }
      else
      {

         m_ealignText |= e_align_left;

      }

      if (align & NVG_ALIGN_MIDDLE)
      {

         m_ealignText |= e_align_vertical_center;


      }
      else if (align & NVG_ALIGN_TOP)
      {

         m_ealignText |= e_align_top;

      }
      else
      {

         m_ealignText |= e_align_bottom;

      }

   }


   float NVGcontext::text(float x, float y, const char * string, const char * end)
   {

      ::string strText(string, end ? end - string : str::length(string));

      m_pgraphics->set(m_pfont);

      m_pgraphics->set(m_pbrush);

      m_pgraphics->text_out({ (double)x, (double)y }, strText);

      auto size = m_pgraphics->get_text_extent(strText);

      return x + size.cx;

   }




   float NVGcontext::text_bounds(float x, float y, const char * string, const char * end, float * bounds)
   {

      ::string strText(string, end ? end - string : str::length(string));

      m_pgraphics->set(m_pfont);

      auto size = m_pgraphics->get_text_extent(strText);

      if (bounds)
      {

         bounds[0] = x;
         bounds[1] = y;
         bounds[2] = x + size.cx;
         bounds[3] = y + size.cy;

      }

      return size.cx;

   }


} // namespace draw2d



