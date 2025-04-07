#include "framework.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/constant/timer.h"
#include "acme/graphics/image/image32.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/timer.h"
#include "acme/platform/keep.h"
#include "aura/platform/draw_context2.h"
#include "acme/prototype/mathematics/mathematics.h"
//#include "acme/prototype/time/integral/generic.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "check_box.h"
#include "style.h"
#include "aura/message/user.h"


void scroll_x(::int_rectangle & rectangleTarget, double dRateX, const ::int_rectangle & rectangle)
{

   int w = ::width(rectangle);

   rectangleTarget.left() = (int) (rectangle.left() + (rectangle.width() - w) * dRateX);

   rectangleTarget.right() = rectangleTarget.left() + w;

}


namespace user
{


   check_box::check_box(e_style estyle)
   {

      m_bDefaultClickHandling = true;

      m_timeAnimationPeriod = 300_ms;

      m_estyle = estyle;

      m_econtroltype = e_control_type_check_box;

   }


   check_box::~check_box()
   {

   }


   ::subparticle_pointer check_box::clone()
   {

      auto pcheckbox = m_papplication->__create_new <::user::check_box>();

      return pcheckbox;

   }


   //void check_box::set_check(const ::e_check & echeckInput, const ::action_context & context)
   //void check_box::on_check_changed(const ::e_check & echeckInput, const ::action_context & context)
   void check_box::on_check_changed(::data::check_change & change)
   {

      //::e_check echeckInput = checkproperty;

      //::e_check echeckEffective = echeckInput;

      //if(echeckInput != ::e_check_unchecked && echeckInput != ::e_check_checked && echeckInput != ::e_check_tristate)
      //{

      //   // default value when setting a value that does not match the ones above

      //   echeckEffective = ::e_check_checked;

      //}

      //if(this->echeck() != echeckEffective)
      //{

      //   check::set_check(echeckEffective, context);

         if(has_handler())
         {

            auto ptopic = create_topic(::id_set_check);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = change.action_context();

            route(ptopic);
            
         }

         set_need_redraw();

         post_redraw();

      //}

   }


   void check_box::_001OnNcDraw(::draw2d::graphics_pointer& pgraphics)
   {


   }


   void check_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_estyle == style_toggle_switch)
      {

         _001OnDrawToggleSwitch(pgraphics);

      }
      else if (m_estyle == style_red_green_circle)
      {

         _001OnDrawRedGreenCircle(pgraphics);

      }
      else
      {

         _001OnDrawNormal(pgraphics);

      }

   }


   enum_element check_box::get_default_element()
   {

      return e_element_check;

   }


   void check_box::_001OnDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      ::pointer<::user::style>pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001DrawCheckBox(pgraphics, this))
         {

            return;

         }

      }

      ::aura::draw_context drawcontext;

      drawcontext.m_pdrawcontextNext = m_pdrawcontext;

      drawcontext.m_bListItemHover = hover_item().is_set();

      KEEP(pgraphics->m_pdrawcontext, &drawcontext);

      //::int_rectangle rectangleX;

      auto rectangleX = this->rectangle();

      int w = rectangleX.width();

      int h = rectangleX.height();

      if (w <= 0 || h <= 0)
      {

         return;

      }

      auto echeck = this->echeck();

      ::draw2d::save_context savecontext(pgraphics);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->offset_origin(rectangleX.left(), rectangleX.top());

      ::int_rectangle rectangleCheckBox;

      ::int_rectangle rectangleText;

      {

         int iSize = minimum(15 * w / 15, 15 * h / 15);

         rectangleCheckBox.left() = 0;
         rectangleCheckBox.top() = 0;
         rectangleCheckBox.right() = iSize;
         rectangleCheckBox.bottom() = iSize;

         rectangleText = rectangleX;

         rectangleText.left() = rectangleCheckBox.right() + 4;

         auto estate = get_user_state();

         auto colorBackground = get_color(pstyle, e_element_background, estate);

         pgraphics->fill_rectangle(rectangleCheckBox, colorBackground);

         if (echeck == ::e_check_tristate)
         {

            pgraphics->fill_rectangle(rectangleCheckBox, argb(120, 120, 120, 120));

         }

         auto rectangleBorder = rectangleCheckBox;

         rectangleBorder.inflate(1);

         auto colorText = get_color(pstyle, e_element_text, estate);

         pgraphics->set_text_color(colorText);

         pgraphics->draw_inset_rectangle(rectangleBorder, colorText, 1.0);

         //if (drawcontext.m_bListItemHover)
         //{

         //   pgraphics->draw_inset_rectangle(rectangleBorder, argb(255, 60, 120, 200), 1.0);

         //}
         //else
         //{

         //   pgraphics->draw_inset_rectangle(rectangleBorder, argb(255, 128, 128, 128), 1.0);

         //}

         if (echeck == ::e_check_tristate || echeck == ::e_check_checked)
         {

            if (pstyle)
            {

               pstyle->draw_check(this, echeck, rectangleCheckBox, pgraphics);

            }

         }

      }

      {

         string strWindowText;

         strWindowText = get_window_text();

         if(strWindowText.has_character())
         {

            ::e_align ealign = e_align_left_center;

            ::e_draw_text edrawtext = e_draw_text_single_line;

            pgraphics->set_font(this, ::e_element_none);

   /*         ::color::color crText;

            if (drawcontext.m_bListItemHover)
            {

               crText = argb(255, 0, 0, 0);

            }
            else
            {

               crText = argb(255, 0, 0, 0);

            }*/


            ::color::color color;

            auto estate = get_user_state();

            color = get_color(pstyle, e_element_text, estate);

            pgraphics->set_text_color(color);

            pgraphics->draw_text(strWindowText, rectangleText, ealign, edrawtext);

         }

      }

   }


   void check_box::_001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics)
   {

      ::pointer<::user::style>pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001DrawCheckBox(pgraphics, this))
         {

            return;

         }

      }

      ::aura::draw_context drawcontext;

      drawcontext.m_bListItemHover = hover_item().is_set();

      KEEP(pgraphics->m_pdrawcontext, &drawcontext);

      auto rectangleX = this->rectangle();

      int w = rectangleX.width();

      int h = rectangleX.height();

      w--;

      h--;

      if (w % 2 == 0)
      {

         w--;

      }

      if (h % 2 == 0)
      {

         h--;

      }

      if (w <= 0 || h <= 0)
      {

         return;

      }

      //::enum_check echeck = get_check();

      ::draw2d::save_context savecontext(pgraphics);

      if (w > h * 2)
      {

         w = h * 2;

      }
      else
      {

         h = w / 2;

      }

      ::int_rectangle rectangle(1, 1, w-2, h-2);

      ::int_rectangle rectangleEllipse(1, 1, h-2, h-2);

      //double dNow = ::get_millis();

      ::draw2d::path_pointer ppath(e_create, this);

      ::int_rectangle rectangleL(1, 1, h-2, h-2);

      auto rectangleR = int_rectangle_dimension(h-2, 1, h-2, h-2);

      ppath->add_arc(rectangleL, -90_degree, -180_degree);

      ppath->add_line((rectangleL.left() + rectangleL.right()) / 2, rectangleL.bottom());

      ppath->add_line((rectangleR.left() + rectangleR.right()) / 2, rectangleR.bottom());

      ppath->add_arc(rectangleR, 90_degree, -180_degree);

      ppath->add_line((rectangleR.left() + rectangleR.right()) / 2, rectangleR.top());

      ppath->add_line((rectangleL.left() + rectangleL.right()) / 2, rectangleL.top());

      ppath->close_figure();

      auto ppen = __øcreate < ::draw2d::pen > ();

      ::draw2d::pen_pointer p0(e_create, this);

      ::draw2d::brush_pointer pbrush1(e_create, this);

      ppen->create_solid(2.0, argb(255, 0, 0, 0));

      p0->create_solid(2.0, argb(255, 90, 150, 255));

      ppen->m_epenalign = ::draw2d::e_pen_align_center;

      pbrush1->create_solid(argb(255, 90, 150, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto dRate = m_timeAnimationStart.period_rate(m_timeAnimationPeriod);

      if (dRate < 1.0)
      {

         bool bComplement;

         if (echeck() == ::e_check_unchecked)
         {

            bComplement = true;

         }
         else
         {

            bComplement = false;

         }

         auto color = argb(255, 255, 255, 255);

         auto pbrush = __øcreate < ::draw2d::brush > ();

         auto pmathematics = mathematics();

         m_dPosition = ::sin((π / 2.0) * dRate);

         double dRate = m_dPosition;

         if (bComplement)
         {

            dRate = 1.0 - dRate;

         }

         pbrush1->m_color.set_opacity(dRate);

         pbrush1->set_modified();

         p0->m_color = pbrush1->m_color;

         p0->set_modified();

         pgraphics->set(pbrush1);
         pgraphics->set(p0);

         pgraphics->path(ppath);

         pbrush->create_solid(color.rate_rgb_set_opacity(255, dRate));

         ::scroll_x(rectangleEllipse, dRate, rectangle);

         rectangleEllipse.rate(0.6);

         pgraphics->set(pbrush);

         pgraphics->fill_ellipse(rectangleEllipse);

         unsigned char bAlphaP1 = (unsigned char) (255.0 * (1.0 - dRate));

         ::color::color crP1 = argb(bAlphaP1, 0, 0, 0);

         ppen->create_solid(2.0, crP1);

         ppen->set_modified();

         pgraphics->set(ppen);

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         pgraphics->draw(ppath);

      }
      else
      {

         if (echeck() == ::e_check_unchecked)
         {

            rectangleEllipse.Align({ e_align_left, e_align_vertical_center}, rectangle);

            rectangleEllipse.rate(0.6);

            auto pbrush = __øcreate < ::draw2d::brush > ();

            pbrush->create_solid(argb(255, 0, 0, 0));

            pgraphics->set(pbrush);

            pgraphics->fill_ellipse(rectangleEllipse);

            ppen->create_solid(2.0, argb(255, 0, 0, 0));

            pgraphics->set(ppen);

            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

            pgraphics->draw(ppath);

         }
         else
         {

            pgraphics->set(pbrush1);

            pgraphics->set(p0);

            pgraphics->path(ppath);

            rectangleEllipse.Align(e_align_right | e_align_vertical_center, rectangle);

            rectangleEllipse.rate(0.6);

            auto pbrush = __øcreate < ::draw2d::brush > ();

            pbrush->create_solid(argb(255, 255, 255, 255));

            pgraphics->set(pbrush);

            pgraphics->fill_ellipse(rectangleEllipse);

         }

      }

   }


   void check_box::_001OnDrawRedGreenCircle(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      int iMinimumDimension = maximum(rectangleX.minimum_dimension() -1, 1);

      ::int_rectangle rectangleCheckBox;
      rectangleCheckBox.left() = 1;
      rectangleCheckBox.top() = 1;
      rectangleCheckBox.right() = iMinimumDimension + 1;
      rectangleCheckBox.bottom() = iMinimumDimension + 1;

      ::color::color crPen = argb(255, 0, 0, 0);
      ::color::color crBrush;

      if (echeck() == ::e_check_checked)
      {

         crBrush = argb(255, 100, 220, 120);

      }
      else if (echeck() == ::e_check_unchecked)
      {

         crBrush = argb(255, 220, 220, 100);

      }
      else
      {

         crBrush = argb(255, 128, 128, 128);

      }

      auto ppen = __øcreate < ::draw2d::pen > ();

      ppen->create_solid(1.0, crPen);

      pgraphics->set(ppen);

      auto pbrush = __øcreate < ::draw2d::brush >();

      pbrush->create_solid(crBrush);

      pgraphics->set(pbrush);

      pgraphics->ellipse(rectangleCheckBox);
      //   pgraphics->draw_inset_3d_rectangle(rectangleCheckBox, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
      //   if (m_echeck == e_check_tristate
      //      || m_echeck == e_check_checked)
      //   {
      //      auto ppen = __øcreate < ::draw2d::pen > ();
      //      ppen->create_solid(1, m_echeck == e_check_checked ? argb(255, 0, 0, 0) : argb(255, 96, 96, 96));
      //      pgraphics->set(ppen);
      //      pgraphics->set_current_point(2, 8);
      //      pgraphics->line_to(6, 12);
      //      pgraphics->line_to(13, 5);
      //      pgraphics->set_current_point(2, 9);
      //      pgraphics->line_to(6, 13);
      //      pgraphics->line_to(13, 6);
      //   }
      //}
      //pgraphics->offset_origin(-rectangleX.left(), -rectangleX.top());

   }


   void check_box::on_timer(::timer * ptimer)
   {

      if (ptimer->m_uTimer == e_timer_check_toggle_animation)
      {

         set_need_redraw();

         post_redraw();

         if (m_timeAnimationStart.elapsed() > m_timeAnimationPeriod)
         {

            kill_timer(ptimer->m_uTimer);

         }

      }
//      else if (ptimer->m_uTimer == e_timer_command_probe)
//      {
//
//         ::user::menu_command command(this);
//
//         command.id() = id();
//
//         command.m_puiOther = this;
//
//         try
//         {
//
//            _001SendCommandProbe(&command);
//
//         }
//         catch(...)
//         {
//         }
//
//      }

      ::user::interaction::on_timer(ptimer);

   }


   void check_box::on_message_key_down(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void check_box::on_message_key_up(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_space)
      {

         m_checkproperty.toggle(::e_source_user);

      }

   }


   void check_box::on_message_left_button_double_click(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

   }


   bool check_box::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      m_dPosition = 0.0;

      m_timeAnimationStart.Now();

      set_timer(e_timer_check_toggle_animation, 12_ms);

      m_checkproperty.toggle(::e_source_user);

      return true;

   }


   void check_box::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      interaction::handle(ptopic, phandlercontext);

   }


   void check_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);
      
      MESSAGE_LINK(e_message_create, pchannel, this, &check_box::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &check_box::on_message_left_button_double_click);

   }


   void check_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      if (size(e_layout_sketch).is_empty())
      {

         set_size({ 24, 24 });

      }

      ::string strId(id().as_string());

      if (strId.case_insensitive_begins_eat("application://"))
      {

         ::data::check_property checkproperty((::data::property_container *) this->application(), strId);

         set_check_property(checkproperty);

      }

      //m_linkedpropertyCheck = fetch_property(id(), true);

   }


} // namespace user
