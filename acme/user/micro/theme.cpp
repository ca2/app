// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "still.h"
#include "theme.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/nano.h"
#include "acme/windowing/window.h"
#include "acme/user/user/mouse.h"
#include "acme/user/micro/theme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"


namespace micro
{

   
      
      theme::theme()
      {

         m_iFontSize = 15;
         
         m_efont = e_font_sans;

      }


      theme::~theme()
      {


      }


      void theme::create_drawing_objects()
      {

         if (!m_pfont)
         {

            __øconstruct(m_pfont);

            m_pfont->m_iFontSize = m_iFontSize;

            m_pfont->m_strFontName = node()->font_name(m_efont);

         }

         bool bDarkMode = system()->dark_mode();

         if (bDarkMode)
         {

            m_colorWindow = argb(255, 0, 0, 0);
            m_colorText = argb(255, 255, 255, 255);
            m_colorHyperlink = argb(255, 40, 90, 245);
            m_colorHyperlinkHover = argb(255, 70, 180, 255);
            m_colorFocus = argb(255, 2, 128, 255);
            m_colorHover = argb(255, 2, 108, 235);
            m_colorHoverAndFocus = argb(255, 62, 188, 255);

         }
         else
         {

            m_colorWindow = argb(255, 255, 255, 255);
            m_colorText = argb(255, 0, 0, 0);
            m_colorHyperlink = argb(255, 50, 100, 185);
            m_colorHyperlinkHover = argb(255, 100, 180, 225);
            m_colorFocus = argb(255, 2, 58, 235);
            m_colorHover = argb(255, 2, 38, 235);
            m_colorHoverAndFocus = argb(255, 2, 108, 255);

         }

         m_pbrushWindow = ::nano::graphics::create_solid_brush(this, m_colorWindow);

         m_pbrushText = ::nano::graphics::create_solid_brush(this, m_colorText);

         m_pbrushHyperlink = ::nano::graphics::create_solid_brush(this, m_colorHyperlink);

         m_pbrushHyperlinkHover = ::nano::graphics::create_solid_brush(this, m_colorHyperlinkHover);

         m_ppenBorder = ::nano::graphics::create_pen(this, 2, m_colorText);

         m_ppenBorderFocus = ::nano::graphics::create_pen(this, 2, m_colorFocus);

         m_ppenBorderHover = ::nano::graphics::create_pen(this, 2, m_colorHover);

         m_ppenBorderHoverAndFocus = ::nano::graphics::create_pen(this, 2, m_colorHoverAndFocus);

      }


      void theme::update_drawing_objects()
      {

         delete_drawing_objects();

         nano()->graphics();

         create_drawing_objects();

      }


      void theme::delete_drawing_objects()
      {

         m_pbrushWindow.release();

         m_ppenBorder.release();

         m_ppenBorder.release();

      }


      void theme::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         if (ptopic->id() == id_operating_system_user_color_change)
         {

            update_drawing_objects();

         }
         else if (ptopic->id() == id_set_application_dark_mode)
         {

            update_drawing_objects();

         }
         else if (ptopic->id() == id_application_dark_mode_change)
         {

            update_drawing_objects();

         }

      }


} // namespace micro




