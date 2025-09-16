#include "framework.h"
#include "text_box.h"
#include "font_list.h"
#include "text_box.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/graphics.h"
//#include "acme/_finish.h"


namespace write_text
{


   text_box::text_box()
   {

      m_bInit = false;
      m_bOk = false;

   }


   text_box::~text_box()
   {

   }


   bool text_box::is_layout_ok(font_list* plist)
   {

      return m_bInit;

   }


   bool text_box::is_drawing_ok(font_list* plist)
   {

      return m_bOk && (is_equivalent(m_bDarkMode, plist->m_bDarkMode));

   }


   void text_box::set_text_box_init(bool bSet)
   {

      m_bInit = bSet;

   }


   void text_box::set_text_box_ok(bool bSet)
   {

      m_bOk = bSet;

   }


   void text_box::update(font_list* plist, int iBox, const ::scoped_string & scopedstrText)
   {

      if (!m_pimage)
      {

         plist->øconstruct(m_pimage);

         if (!m_pimage)
         {

            return;

         }

      }

      m_pimage->create(m_size);

      auto bDarkMode = plist->m_bDarkMode;

      int iColorIndex = 0;

      if (bDarkMode)
      {

         iColorIndex = 1;

      }

      auto uBackgroundColor = plist->m_uaBackgroundColor[iColorIndex][iBox];

      m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      m_pimage->g()->fill_rectangle(::int_rectangle(m_size), uBackgroundColor);

      m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      m_pimage->g()->set(m_pfont);

      auto uForegroundColor = plist->m_uaForegroundColor[iColorIndex][iBox];

      if (uForegroundColor.is_transparent())
      {
      
         plist->information() << "Color is transparent";

      }

      m_pimage->g()->set_text_color(uForegroundColor);

      m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      m_pimage->g()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      m_pimage->g()->text_out(plist->m_rectangleMargin.left(), plist->m_rectangleMargin.top(), scopedstrText);

#if 0

         string str;

         str.formatf("item:ARGB(%d,%d,%d,%d):%d, %d, %s",
            uForegroundColor.m_uchOpacity,
            uForegroundColor.m_uchRed,
            uForegroundColor.m_uchGreen,
            uForegroundColor.m_uchBlue,
            plist->m_rectangleMargin.left(), 
            plist->m_rectangleMargin.top(), strText.c_str());
         
         plist->information() << str;

#endif

      m_bOk = true;

      m_bDarkMode = bDarkMode;

   }


} // namespace write_text



