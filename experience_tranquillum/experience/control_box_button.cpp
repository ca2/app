#include "framework.h"
#include "control_box_button.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/message/user.h"
#include "base/user/experience/control_box.h"


namespace experience_tranquillum
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

      ::int_rectangle rectangleX;

      rectangleX = ::user::interaction::rectangle();

      if (rectangleX.area() <= 0)
         return;

      color32_t crText;

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      if (!is_window_enabled())
      {

         pgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

         pgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

         crText = m_pcontrolbox->m_colorButtonForeDisabled;

      }
      else if (::is_set(m_pitemHover))
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

      ::int_rectangle rectangleEllipse(rectangleX);

      //auto rW = window_rectangle();

      rectangleEllipse.deflate(0, 0, 2, 2);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(rectangleX, pgraphics->m_pbrush->m_color);

      //pgraphics->FillEllipse(rectangleEllipse);

      //pgraphics->DrawEllipse(rectangleEllipse);

      if (m_estockicon == e_stock_icon_none)
      {

         auto strWindowText = get_window_text();

         //get_window_text(str);

         pgraphics->set_font(this, ::e_element_none);

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strWindowText, rectangleX, e_align_center, e_draw_text_single_line);

      }
      else
      {

         m_pbrush->create_solid(::is_set(pgraphics->get_current_pen())
                                 ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_pbrush);

         m_ppen->create_solid(1.0, ::is_set(pgraphics->get_current_pen())
                              ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

         pgraphics->set(m_ppen);

         ::int_rectangle rectangleIcon(rectangleEllipse);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         //pgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

      }

   }


   void control_box_button::install_message_routing(::channel * pchannel)
   {

      ::experience::button::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &control_box_button::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &control_box_button::on_message_show_window);

   }


   void control_box_button::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      __øconstruct(m_ppen);
      
      __øconstruct(m_pbrush);

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


   void control_box_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::experience::button::on_layout(pgraphics);

      //__øconstruct(m_spregion);
      //__øconstruct(m_ppen);
      //__øconstruct(m_pbrush);
      //   
      //auto rectangleX = this->rectangle();
      //
      //::double_ellipse ellipse;
      //
      //ellipse.set(rectangleX);

      //m_spregion->create_ellipse(ellipse);

   }


   ::item_pointer control_box_button::on_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {

      return ::experience::button::on_hit_test(point, ezorder);

      //synchronous_lock synchronouslock(this->synchronization());

      //if (m_spregion.is_null())
      //{

      //   auto pitemNone = __allocate ::item(e_element_none);

      //   return pitemNone;

      //}

      //if (!m_spregion->contains(point))
      //{

      //   auto pitemNone = __allocate ::item(e_element_none);

      //   return pitemNone;

      //}

      //return __allocate ::item(::e_element_client);

   }


   bool control_box_button::keyboard_focus_is_focusable()
   {

      //return false && ::user::button::keyboard_focus_is_focusable();

      return false;


   }


} // namespace experience_tranquillum



