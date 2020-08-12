#include "framework.h"


namespace user
{

   meta_button::meta_button(::object * pobject) :
      object(pobject),
      ::user::button(pobject),
      ::experience::button(pobject),
      m_spregion(this_create)
   {

   }


   meta_button::~meta_button()
   {

   }


   void meta_button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void meta_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (GetTopLevel()->frame_is_transparent() && GetTopLevel() != GetActiveWindow())
      {

         return;

      }

      ::rect rectClient;

      ::user::interaction::GetClientRect(rectClient);

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
      else if (Session.get_keyboard_focus() == this)
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

      rectEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->FillEllipse(rectEllipse);

      pgraphics->DrawEllipse(rectEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         GetWindowText(str);

         select_font(pgraphics, font_button, this);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

      }
      else
      {

         ::draw2d::brush_pointer brush(this_create);

         brush->create_solid(pgraphics->get_current_pen()->m_cr);

         pgraphics->SelectObject(brush);

         ::draw2d::pen_pointer pen(this_create);

         *pen = *pgraphics->get_current_pen();

         pen->m_dWidth = 1.0;

         pgraphics->SelectObject(pen);

         ::rect rectIcon(rectEllipse);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);


      }

   }


   void meta_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

   }


   void meta_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      GetClientRect(rectClient);

      m_spregion->create_oval(rectClient);

   }


   void meta_button::on_hit_test(::user::item & item)
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

      ScreenToClient(&point);

      if (!m_spregion->contains(point))
      {

         eelement = element_none;

         return -1;

      }

      eelement = element_client;

      return 0;

   }


   bool meta_button::keyboard_focus_is_focusable()
   {

      return false && ::user::button::keyboard_focus_is_focusable();

   }







} // namespace user


