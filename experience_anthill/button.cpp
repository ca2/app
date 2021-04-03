#include "framework.h"

namespace experience
{


   namespace anthill
   {




   button::button() :
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

      if ((get_top_level()->frame_is_transparent() && !get_top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      auto rectClient = get_client_rect();

      if (rectClient.is_empty())
      {

         return;

      }

      color32_t crText;

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->set(m_pcontrolbox->m_brushButtonBackDisabled);

         pgraphics->set(m_pcontrolbox->m_penButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (hover_item().is_set())
      {

         pgraphics->set(m_pcontrolbox->m_brushButtonBackSel);

         pgraphics->set(m_pcontrolbox->m_penButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_keyboard_focus())
      {

         pgraphics->set(m_pcontrolbox->m_brushButtonBackFocus);

         pgraphics->set(m_pcontrolbox->m_penButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pgraphics->set(m_pcontrolbox->m_brushButtonBack);

         pgraphics->set(m_pcontrolbox->m_penButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::rectangle_i32 rectEllipse(rectClient);

      ::rectangle_i32 rW;

      get_window_rect(rW);

      rectEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->fill_rectangle(rectClient, pgraphics->m_pbrush->m_color);

      //pgraphics->FillEllipse(rectEllipse);

      //pgraphics->DrawEllipse(rectEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         pgraphics->set_font(this, ::user::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectClient, e_align_center, e_draw_text_single_line);

      }
      else
      {

         m_brush->create_solid(::is_set(pgraphics->get_current_pen())
                               ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_brush);

         m_pen->create_solid(1.0, ::is_set(pgraphics->get_current_pen())
                             ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_pen);

         ::rectangle_i32 rectIcon(rectEllipse);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectEllipse, argb(255, 255, 255, 255));

      }

   }


   void button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &button::_001OnShowWindow);

   }

   void button::_001OnShowWindow(::message::message * pmessage)
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

      auto rectClient = get_client_rect();

      m_spregion->create_oval(rectClient);

   }


   void button::on_hit_test(::user::item & item)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_spregion.is_null())
      {

         item= ::user::e_element_none;
         return;

      }

      //if (m_spregion->get_os_data() == nullptr)
      //{

      //   item= e_element_none;
      //   return;

      //}

      if (!m_spregion->contains(item.m_pointHitTest))
      {

         item = ::user::e_element_none;
         return;

      }

      item= ::user::e_element_client;

   }


   bool button::keyboard_focus_is_focusable() const
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }




         } // namespace anthill


   } // namespace experience




