#include "platform.h"

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

   void button::_001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::experience::button::_001OnClip(pdraw2dgraphics);

   }

   void button::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      if (get_top_level()->frame_is_transparent() && !get_top_level()->is_active())
      {

         return;

      }

      ::i32_rectangle rectangleX;

      ::user::interaction::this->rectangle(rectangleX);

      if (rectangleX.area() <= 0)
         return;

      color32_t crText;

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      if (!is_window_enabled())
      {

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackDisabled);

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (m_pitemHover)
      {

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackSel);

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_keyboard_focus())
      {

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBackFocus);

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_pbrushButtonBack);

         pdraw2dgraphics->SelectObject(m_pcontrolbox->m_ppenButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::i32_rectangle rectangleEllipse(rectangleX);

      ::i32_rectangle rW;

      window_rectangle(rW);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->fill_rectangle(rectangleX, pdraw2dgraphics->m_pbrush->m_cr);

      //pdraw2dgraphics->FillEllipse(rectangleEllipse);

      //pdraw2dgraphics->DrawEllipse(rectangleEllipse);

      if (m_estockicon == stock_icon_none)
      {

         string str;

         get_window_text(str);

         select_font(pdraw2dgraphics, font_button);

         pdraw2dgraphics->set_solid_color(crText);

         pdraw2dgraphics->draw_text(str, rectangleX, e_align_center | DT_SINGLELINE);

      }
      else
      {

         m_pbrush->create_solid(pdraw2dgraphics->get_current_pen().is_set()
                               ? pdraw2dgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pdraw2dgraphics->SelectObject(m_pbrush);

         m_ppen->create_solid(1.0, pdraw2dgraphics->get_current_pen().is_set()
                             ? pdraw2dgraphics->get_current_pen()->m_cr : argb(255, 255, 255, 255));

         pdraw2dgraphics->SelectObject(m_ppen);

         ::i32_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pdraw2dgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         //pdraw2dgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

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


   void button::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      m_spregion->create_oval(rectangleX);

   }


   ::item_pointer button::on_hit_test(const ::i32_point &point, ::user::e_zorder ezorder)
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




