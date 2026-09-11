#include "platform.h"
#include "control_box_button.h"
#include "control_box.h"
#include "acme/handler/item.h"
#include "acme/constant/user_message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/stock_icon.h"
#include "aura/message/user.h"


namespace experience_anthill
{



   control_box_button::control_box_button()
   {

   }


   control_box_button::~control_box_button()
   {

   }


   void control_box_button::_001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::experience::button::_001OnClip(pdraw2dgraphics);

   }

   void control_box_button::_001OnNcDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

   }


   void control_box_button::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      if ((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      color32_t crText;

      pdraw2dgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      if (!is_window_enabled())
      {

         pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

         pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (hover_item().is_set())
      {

         pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackSel);

         pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackSel);

         crText = m_pcontrolbox->m_colorButtonForeSel;

      }
      else if (has_keyboard_focus())
      {

         pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBackFocus);

         pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBackFocus);

         crText = m_pcontrolbox->m_colorButtonForeFocus;

      }
      else
      {

         pdraw2dgraphics->set(m_pcontrolbox->m_pbrushButtonBack);

         pdraw2dgraphics->set(m_pcontrolbox->m_ppenButtonBack);

         crText = m_pcontrolbox->m_colorButtonFore;

      }

      ::i32_rectangle rectangleEllipse(rectangleX);

      ::i32_rectangle rW;

      window_rectangle(rW);

      rectangleEllipse.deflate(0, 0, 2, 2);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->fill_rectangle(rectangleX, pdraw2dgraphics->m_pdraw2dbrush->m_color);

      //pdraw2dgraphics->FillEllipse(rectangleEllipse);

      //pdraw2dgraphics->DrawEllipse(rectangleEllipse);

      if (m_estockicon == e_stock_icon_none)
      {

         string str;

         str = get_window_text();

         pdraw2dgraphics->set_font(this, ::e_element_none);

         pdraw2dgraphics->set_solid_color(crText);

         pdraw2dgraphics->draw_text(str, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         m_pbrush->create_solid(::is_set(pdraw2dgraphics->get_current_pen())
            ? pdraw2dgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pdraw2dgraphics->set(m_pbrush);

         m_ppen->create_solid(1.0, ::is_set(pdraw2dgraphics->get_current_pen())
            ? pdraw2dgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pdraw2dgraphics->set(m_ppen);

         ::i32_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);
         
         defer_construct_newø(m_pstockicon);
         
         m_pstockicon->m_estockiconNew = m_estockicon;

         pdraw2dgraphics->draw(rectangleIcon, m_pstockicon);

         //pdraw2dgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

      }

   }


   void control_box_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &button::on_message_show_window);

   }


   void control_box_button::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         if (m_estockicon == e_stock_icon_restore)
         {

            informationf("restore button is being shown");

         }

      }


   }


   void control_box_button::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {


      constructø(m_spregion);
      constructø(m_ppen);
      constructø(m_pbrush);


      auto rectangleX = this->rectangle();
      
      ::f64_ellipse ellipse;
      
      ellipse.set(rectangleX);

      m_spregion->create_ellipse(ellipse);

   }


   ::item_pointer control_box_button::on_hit_test(const ::i32_point & point, ::user::e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (m_spregion.is_null())
      {

         auto pitemNone = allocateø ::item(e_element_none);

         return pitemNone;

      }

      //if (m_spregion->get_os_data() == nullptr)
      //{

      //   item= e_element_none;
      //   return;

      //}

      if (!m_spregion->contains(point))
      {

         auto pitemNone = allocateø ::item(e_element_none);

         return pitemNone;

      }

      return allocateø ::item(::e_element_client);

   }


   bool control_box_button::keyboard_focus_is_focusable()
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }




} // namespace experience_anthill




