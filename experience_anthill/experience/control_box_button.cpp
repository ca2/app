#include "framework.h"
#include "control_box_button.h"
#include "control_box.h"
#include "acme/handler/item.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/frame.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/message/user.h"


namespace experience_anthill
{



   control_box_button::control_box_button()
   {

   }


   control_box_button::~control_box_button()
   {

   }


   void control_box_button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::_001OnClip(pgraphics);

   }

   void control_box_button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void control_box_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if ((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      auto rectangleClient = client_rectangle();

      if (rectangleClient.is_empty())
      {

         return;

      }

      color32_t crText;

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

         pgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (hover_item().is_set())
      {

         pgraphics->set(m_pcontrolbox->m_pbrushButtonBackSel);

         pgraphics->set(m_pcontrolbox->m_ppenButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_keyboard_focus())
      {

         pgraphics->set(m_pcontrolbox->m_pbrushButtonBackFocus);

         pgraphics->set(m_pcontrolbox->m_ppenButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pgraphics->set(m_pcontrolbox->m_pbrushButtonBack);

         pgraphics->set(m_pcontrolbox->m_ppenButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::rectangle_i32 rectangleEllipse(rectangleClient);

      ::rectangle_i32 rW;

      window_rectangle(rW);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(rectangleClient, pgraphics->m_pbrush->m_color);

      //pgraphics->FillEllipse(rectangleEllipse);

      //pgraphics->DrawEllipse(rectangleEllipse);

      if (m_estockicon == e_stock_icon_none)
      {

         string str;

         str = get_window_text();

         pgraphics->set_font(this, ::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(str, rectangleClient, e_align_center, e_draw_text_single_line);

      }
      else
      {

         m_pbrush->create_solid(::is_set(pgraphics->get_current_pen())
            ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_pbrush);

         m_ppen->create_solid(1.0, ::is_set(pgraphics->get_current_pen())
            ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_ppen);

         ::rectangle_i32 rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

      }

   }


   void control_box_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &button::on_message_show_window);

   }


   void control_box_button::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         if (m_estockicon == e_stock_icon_restore)
         {

            output_debug_string("restore button is being shown");

         }

      }


   }


   void control_box_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


      __construct(m_spregion);
      __construct(m_ppen);
      __construct(m_pbrush);


      auto rectangleClient = client_rectangle();
      
      ::ellipse_f64 ellipse;
      
      ellipse.set(rectangleClient);

      m_spregion->create_ellipse(ellipse);

   }


   ::item_pointer control_box_button::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_spregion.is_null())
      {

         auto pitemNone = __new(::item(e_element_none));

         return pitemNone;

      }

      //if (m_spregion->get_os_data() == nullptr)
      //{

      //   item= e_element_none;
      //   return;

      //}

      if (!m_spregion->contains(point))
      {

         auto pitemNone = __new(::item(e_element_none));

         return pitemNone;

      }

      return __new(::item(::e_element_client));

   }


   bool control_box_button::keyboard_focus_is_focusable()
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }




} // namespace experience_anthill




