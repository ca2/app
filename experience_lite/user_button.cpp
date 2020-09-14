#include "framework.h"

namespace user
{

   button::button(::layered * pobjectContext) :
      object(pobject),
      ::user::button(pobject),
      ::experience::button(pobject),
      m_spregion(e_create),
      m_pen(e_create),
      m_brush(e_create)
   {

   }


   button::~button()
   {

   }

   void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::_001OnClip(pgraphics);

   }

   void button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (GetTopLevel()->frame_is_transparent() && !GetTopLevel()->is_active())
      {

         return;

      }

      ::rect rectClient;

      ::user::interaction::get_client_rect(rectClient);

      if (rectClient.area() <= 0)
         return;

      COLORREF crText;

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackDisabled);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackDisabled);

         crText = m_pcontrolbox->m_crButtonForeDisabled;

      }
      else if (m_itemHover)
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackSel);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackSel);

         crText = m_pcontrolbox->m_crButtonForeSel;

      }
      else if (has_focus())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackFocus);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackFocus);

         crText = m_pcontrolbox->m_crButtonForeFocus;

      }
      else
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBack);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBack);

         crText = m_pcontrolbox->m_crButtonFore;

      }

      ::rect rectEllipse(rectClient);

      ::rect rW;

      get_window_rect(rW);

      rectEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->fill_rect(rectClient, pgraphics->m_pbrush->m_cr);

      //pgraphics->FillEllipse(rectEllipse);

      //pgraphics->DrawEllipse(rectEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         select_font(pgraphics, font_button);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

      }
      else
      {

         m_brush->create_solid(pgraphics->get_current_pen().is_set()
                               ? pgraphics->get_current_pen()->m_cr : ARGB(255, 255, 255, 255));

         pgraphics->SelectObject(m_brush);

         m_pen->create_solid(1.0, pgraphics->get_current_pen().is_set()
                             ? pgraphics->get_current_pen()->m_cr : ARGB(255, 255, 255, 255));

         pgraphics->SelectObject(m_pen);

         ::rect rectIcon(rectEllipse);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectEllipse, ARGB(255, 255, 255, 255));

      }

   }


   void button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &button::_001OnShowWindow);

   }

   void button::_001OnShowWindow(::message::message * pmessage)
   {


      SCAST_PTR(::message::show_window, pshowwindow, pmessage);


      if (pshowwindow->m_bShow)
      {

         if (m_estockicon == stock_icon_restore)
         {

            output_debug_string("restore button is being shown");

         }

      }


   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      m_spregion->create_oval(rectClient);

   }


   void button::on_hit_test(::user::item & item)
   {

      sync_lock sl(mutex());

      if (m_spregion.is_null())
      {

         eelement = element_none;

         return -1;

      }

      if (m_spregion->get_os_data() == nullptr)
      {

         eelement = element_none;

         return -1;

      }

      _001ScreenToClient(&point);

      if (!m_spregion->contains(point))
      {

         eelement = element_none;

         return -1;

      }

      eelement = element_client;

      return 0;

   }


   bool button::keyboard_focus_is_focusable()
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }



} // namespace user




