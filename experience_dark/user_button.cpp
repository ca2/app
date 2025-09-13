#include "framework.h"

namespace user
{

   button::button(::particle * pparticle) :
      object(pparticle),
      ::user::button(pparticle),
      ::experience::button(pparticle),
      m_spregion(e_create),
      m_ppen(e_create),
      m_pbrush(e_create)
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

      ::int_rectangle rectangleX;

      ::user::interaction::this->rectangle(rectangleX);

      if (rectangleX.area() <= 0)
         return;

      color32_t crText;

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackDisabled);

         pgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (m_pitemHover)
      {

         pgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackSel);

         pgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_keyboard_focus())
      {

         pgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackFocus);

         pgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBack);

         pgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::int_rectangle rectangleEllipse(rectangleX);

      ::int_rectangle rW;

      window_rectangle(rW);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(rectangleX, pgraphics->m_pbrush->m_cr);

      //pgraphics->FillEllipse(rectangleEllipse);

      //pgraphics->DrawEllipse(rectangleEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         select_font(pgraphics, font_button);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectangleX, e_align_center | DT_SINGLELINE);

      }
      else
      {

         m_pbrush->create_solid(pgraphics->get_current_pen().is_set()
                               ? pgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pgraphics->SelectObject(m_pbrush);

         m_ppen->create_solid(1.0, pgraphics->get_current_pen().is_set()
                             ? pgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pgraphics->SelectObject(m_ppen);

         ::int_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

      }

   }


   void button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &button::on_message_show_window);

   }

   void button::on_message_show_window(::message::message * pmessage)
   {


      ::pointer<::message::show_window>pshowwindow(pmessage);


      if (pshowwindow->m_bShow)
      {

         if (m_estockicon == stock_icon_restore)
         {

            informationf("restore button is being shown");

         }

      }


   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      m_spregion->create_oval(rectangleX);

   }


   ::item_pointer button::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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




