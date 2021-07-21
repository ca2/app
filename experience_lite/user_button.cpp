#include "framework.h"

namespace user
{

   button::button(::object * pobject) :
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

      if (get_top_level()->frame_is_transparent() && !get_top_level()->is_active())
      {

         return;

      }

      ::rectangle_i32 rectangleClient;

      ::user::interaction::get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
         return;

      color32_t crText;

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackDisabled);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (m_itemHover)
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackSel);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_focus())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBackFocus);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pgraphics->SelectObject(m_pcontrolbox->m_brushButtonBack);

         pgraphics->SelectObject(m_pcontrolbox->m_penButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::rectangle_i32 rectEllipse(rectangleClient);

      ::rectangle_i32 rW;

      get_window_rect(rW);

      rectEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(rectangleClient, pgraphics->m_pbrush->m_cr);

      //pgraphics->FillEllipse(rectEllipse);

      //pgraphics->DrawEllipse(rectEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         select_font(pgraphics, font_button);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectangleClient, e_align_center | DT_SINGLELINE);

      }
      else
      {

         m_brush->create_solid(pgraphics->get_current_pen().is_set()
                               ? pgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pgraphics->SelectObject(m_brush);

         m_pen->create_solid(1.0, pgraphics->get_current_pen().is_set()
                             ? pgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pgraphics->SelectObject(m_pen);

         ::rectangle_i32 rectIcon(rectEllipse);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectEllipse, argb(255, 255, 255, 255));

      }

   }


   void button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &button::on_message_show_window);

   }

   void button::on_message_show_window(::message::message * pmessage)
   {


      __pointer(::message::show_window) pshowwindow(pmessage);


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

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      m_spregion->create_oval(rectangleClient);

   }


   void button::on_hit_test(::user::item & item)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_spregion.is_null())
      {

         eelement = e_element_none;

         return -1;

      }

      if (m_spregion->get_os_data() == nullptr)
      {

         eelement = e_element_none;

         return -1;

      }

      screen_to_client(&point);

      if (!m_spregion->contains(point))
      {

         eelement = e_element_none;

         return -1;

      }

      eelement = e_element_client;

      return 0;

   }


   bool button::keyboard_focus_is_focusable()
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }



} // namespace user




