#include "platform.h"
#include "text_box.h"
#include "font_list.h"
#include "text_box.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/draw2d/graphics_layer_scope.h"
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


   void text_box::update(font_list * plist, ::i32 iBox, const ::scoped_string & scopedstrText)
   {

      if (!m_pimage)
      {

         plist->constructø(m_pimage);

         if (!m_pimage)
         {

            return;

         }

         m_pimage->m_bHintCpuBackingEnabled = false;

      }

      m_pimage->create_as_descriptor(m_size);

      m_bOk = false;

      auto pacmeuserinteractionAffinity = plist->m_puserinteractionGraphicsContext
         ? (::acme::user::interaction *)plist->m_puserinteractionGraphicsContext.m_p
         : (::acme::user::interaction *)plist->m_puserinteraction.m_p;

      auto bDarkMode = plist->m_bDarkMode;

      ::i32 iColorIndex = 0;

      if (bDarkMode)
      {

         iColorIndex = 1;

      }

      {

         auto pgraphics = m_pimage->acquire_graphics(::draw2d::e_acquire_dont_load, pacmeuserinteractionAffinity);

         //auto layerscope = pgraphics.begin_layer_scope();

         auto uBackgroundColor = plist->m_uaBackgroundColor[iColorIndex][iBox];

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         auto rectangleItem = ::i32_rectangle(m_size);

         pgraphics->fill_rectangle(rectangleItem, uBackgroundColor);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->set(m_pfont);

         auto uForegroundColor = plist->m_uaForegroundColor[iColorIndex][iBox];

         if (uForegroundColor.is_transparent())
         {

            plist->information() << "Color is transparent";

         }

         pgraphics->set_text_color(uForegroundColor);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         pgraphics->text_out(plist->m_rectangleMargin.left, plist->m_rectangleMargin.top, scopedstrText);

#if 0

         pgraphics->fill_solid_rectangle(rectangleItem, ::argb(128, 100, 160, 200));
         pgraphics->fill_solid_rectangle({ rectangleItem.origin(), rectangleItem.size() / 2 }, color::blue);

#endif

   #if 0

         string str;

         str.formatf("item:ARGB(%d,%d,%d,%d):%d, %d, %s",
            uForegroundColor.m_u8Opacity,
            uForegroundColor.m_u8Red,
            uForegroundColor.m_u8Green,
            uForegroundColor.m_u8Blue,
            plist->m_rectangleMargin.left,
            plist->m_rectangleMargin.top, strText.c_str());

         plist->information() << str;

   #endif

      }

      //layerscope.close();

      //graphicslease.close();

      m_bOk = true;

      m_bDarkMode = bDarkMode;

   }


} // namespace write_text



