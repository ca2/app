#include "framework.h"
#include "aura/user/_user.h"
#include "acme/constant/timer.h"
#include "acme/platform/timer.h"
#include "aura/platform/draw_context2.h"
//#include "interaction_draw2d.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "aura/graphics/draw2d/_draw2d.h"


void scroll_x(RECTANGLE_I32 * prectangle, double dRateX, const ::rectangle_i32 & rectangle)
{

   ::i32 w = ::width(prectangle);

   prectangle->left = (::i32) (rectangle.left + (rectangle.width() - w) * dRateX);

   prectangle->right = prectangle->left + w;

}


namespace user
{


   check_box::check_box(e_style estyle)
   {

      m_bClickDefaultMouseHandling = true;

      m_durationAnimationPeriod = 300_ms;

      m_estyle = estyle;

      m_econtroltype = e_control_type_check_box;

   }


   check_box::~check_box()
   {

   }


   ::element * check_box::clone() const
   {

      auto pcheckbox = new ::user::check_box;

      return pcheckbox;

   }


   void check_box::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if(echeck != ::check_unchecked && echeck != ::check_checked && echeck != ::check_tristate)
      {

         // default value when setting a value that does not match the ones above

         echeck = ::check_checked;

      }

      if(this->echeck() != echeck)
      {

         check::_001SetCheck(echeck, context);
         
         if(has_handler())
         {

            ::extended_topic extendedtopic(::id_set_check);

            extendedtopic.m_puserelement = this;

            extendedtopic.m_actioncontext = context;

            route(&extendedtopic);
            
         }

         set_need_redraw();

         post_redraw();

      }

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


   enum_element check_box::get_default_element() const
   {

      return e_element_check;

   }


   void check_box::_001OnDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::user::style) pstyle = get_style(pgraphics);

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

      __keep(pgraphics->m_pdrawcontext, &drawcontext);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width();

      int h = rectangleClient.height();

      if (w <= 0 || h <= 0)
      {

         return;

      }

      auto echeck = this->echeck();

      ::draw2d::savedc savedc(pgraphics);

      pgraphics->OffsetViewportOrg(rectangleClient.left, rectangleClient.top);

      ::rectangle_i32 rectangleCheckBox;

      ::rectangle_i32 rectangleText;

      {

         int iSize = minimum(15 * w / 15, 15 * h / 15);

         rectangleCheckBox.left = 0;
         rectangleCheckBox.top = 0;
         rectangleCheckBox.right = iSize;
         rectangleCheckBox.bottom = iSize;

         rectangleText = rectangleClient;

         rectangleText.left = rectangleCheckBox.right + 4;

         if (echeck == ::check_tristate)
         {

            pgraphics->fill_rectangle(rectangleCheckBox, argb(255, 220, 220, 220));

         }

         if (drawcontext.m_bListItemHover)
         {

            pgraphics->draw_inset_rectangle(rectangleCheckBox, argb(255, 60, 120, 200));

         }
         else
         {

            pgraphics->draw_inset_rectangle(rectangleCheckBox, argb(255, 128, 128, 128));

         }

         if (echeck == ::check_tristate || echeck == ::check_checked)
         {

            if (pstyle)
            {

               pstyle->draw_check(this, echeck, rectangleCheckBox, pgraphics);

            }

         }

      }

      {

         string strText;

         get_window_text(strText);

         ::e_align ealign = e_align_left_center;
         
         ::e_draw_text edrawtext = e_draw_text_single_line;

         pgraphics->set_font(this, ::e_element_none);

         ::color::color crText;

         if (drawcontext.m_bListItemHover)
         {

            crText = argb(255, 0, 0, 0);

         }
         else
         {

            crText = argb(255, 0, 0, 0);

         }

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strText, rectangleText, ealign, edrawtext);

      }

   }


   void check_box::_001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::user::style) pstyle = get_style(pgraphics);

      if(pstyle)
      {

         if (pstyle->_001DrawCheckBox(pgraphics, this))
         {

            return;

         }

      }

      ::aura::draw_context drawcontext;

      drawcontext.m_bListItemHover = hover_item().is_set();

      __keep(pgraphics->m_pdrawcontext, &drawcontext);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width();

      int h = rectangleClient.height();

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

      //::enum_check echeck = _001GetCheck();

      ::draw2d::savedc savedc(pgraphics);

      if (w > h * 2)
      {

         w = h * 2;

      }
      else
      {

         h = w / 2;

      }

      ::rectangle_i32 rectangle(1, 1, w-2, h-2);

      ::rectangle_i32 rectangleEllipse(1, 1, h-2, h-2);

      //double dNow = ::get_millis();

      ::draw2d::path_pointer ppath(e_create, this);

      ::rectangle_i32 rectangleL(1, 1, h-2, h-2);

      auto rectangleR = rectangle_i32_dimension(h-2, 1, h-2, h-2);

      ppath->add_arc(rectangleL, -90_degree, -180_degree);

      ppath->add_line((rectangleL.left + rectangleL.right) / 2, rectangleL.bottom);

      ppath->add_line((rectangleR.left + rectangleR.right) / 2, rectangleR.bottom);

      ppath->add_arc(rectangleR, 90.0, -180.0);

      ppath->add_line((rectangleR.left + rectangleR.right) / 2, rectangleR.top);

      ppath->add_line((rectangleL.left + rectangleL.right) / 2, rectangleL.top);

      ppath->close_figure();

      auto ppen = __create < ::draw2d::pen > ();

      ::draw2d::pen_pointer p0(e_create, this);

      ::draw2d::brush_pointer pbrush1(e_create, this);

      ppen->create_solid(2.0, argb(255, 0, 0, 0));

      p0->create_solid(2.0, argb(255, 90, 150, 255));

      ppen->m_epenalign = ::draw2d::e_pen_align_center;

      pbrush1->create_solid(argb(255, 90, 150, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto dRate = m_durationAnimationStart.integral_millisecond().period_rate(m_durationAnimationPeriod.integral_millisecond());

      if (dRate < 1.0)
      {

         bool bComplement;

         if (echeck() == ::check_unchecked)
         {

            bComplement = true;

         }
         else
         {

            bComplement = false;

         }

         ::color32_t color32 = argb(255, 255, 255, 255);

         auto pbrush = __create < ::draw2d::brush > ();

         auto pmathematics = ::mathematics::mathematics();

         m_dPosition = ::sin((pmathematics->get_pi() / 2.0) * dRate);

         double dRate = m_dPosition;

         if (bComplement)
         {

            dRate = 1.0 - dRate;

         }

         pbrush1->m_color = (pbrush1->m_color.u32 & 0xffffff) | ((byte(255.0 * dRate)) << 24);

         pbrush1->set_modified();

         p0->m_color = pbrush1->m_color;

         p0->set_modified();

         pgraphics->set(pbrush1);
         pgraphics->set(p0);

         pgraphics->path(ppath);

         pbrush->create_solid(argb(255,
                               (byte)((double) colorref_get_r_value(color32) * dRate),
                               (byte)((double) colorref_get_g_value(color32) * dRate),
                               (byte)((double) colorref_get_b_value(color32) * dRate)));

         ::scroll_x(rectangleEllipse, dRate, rectangle);

         rectangleEllipse.rate(0.6);

         pgraphics->set(pbrush);

         pgraphics->fill_ellipse(rectangleEllipse);

         byte bAlphaP1 = (byte) (255.0 * (1.0 - dRate));

         ::color::color crP1 = argb(bAlphaP1, 0, 0, 0);

         ppen->create_solid(2.0, crP1);

         ppen->set_modified();

         pgraphics->set(ppen);

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

         pgraphics->draw_path(ppath);

      }
      else
      {

         if (echeck() == ::check_unchecked)
         {

            rectangleEllipse.Align({ e_align_left, e_align_vertical_center}, rectangle);

            rectangleEllipse.rate(0.6);

            auto pbrush = __create < ::draw2d::brush > ();

            pbrush->create_solid(argb(255, 0, 0, 0));

            pgraphics->set(pbrush);

            pgraphics->fill_ellipse(rectangleEllipse);

            ppen->create_solid(2.0, argb(255, 0, 0, 0));

            pgraphics->set(ppen);

            pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

            pgraphics->draw_path(ppath);

         }
         else
         {

            pgraphics->set(pbrush1);

            pgraphics->set(p0);

            pgraphics->path(ppath);

            rectangleEllipse.Align(e_align_right | e_align_vertical_center, rectangle);

            rectangleEllipse.rate(0.6);

            auto pbrush = __create < ::draw2d::brush > ();

            pbrush->create_solid(argb(255, 255, 255, 255));

            pgraphics->set(pbrush);

            pgraphics->fill_ellipse(rectangleEllipse);

         }

      }

   }


   void check_box::_001OnDrawRedGreenCircle(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      int iMin = maximum(rectangleClient.min_dim() -1, 1);

      ::rectangle_i32 rectangleCheckBox;
      rectangleCheckBox.left = 1;
      rectangleCheckBox.top = 1;
      rectangleCheckBox.right = iMin + 1;
      rectangleCheckBox.bottom = iMin + 1;

      ::color::color crPen = argb(255, 0, 0, 0);
      ::color::color crBrush;

      if (echeck() == ::check_checked)
      {

         crBrush = argb(255, 100, 220, 120);

      }
      else if (echeck() == ::check_unchecked)
      {

         crBrush = argb(255, 220, 220, 100);

      }
      else
      {

         crBrush = argb(255, 128, 128, 128);

      }

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, crPen);

      pgraphics->set(ppen);

      auto pbrush = __create < ::draw2d::brush >();

      pbrush->create_solid(crBrush);

      pgraphics->set(pbrush);

      pgraphics->ellipse(rectangleCheckBox);
      //   pgraphics->draw_inset_3d_rectangle(rectangleCheckBox, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
      //   if (m_echeck == check_tristate
      //      || m_echeck == check_checked)
      //   {
      //      auto ppen = __create < ::draw2d::pen > ();
      //      ppen->create_solid(1, m_echeck == check_checked ? argb(255, 0, 0, 0) : argb(255, 96, 96, 96));
      //      pgraphics->set(ppen);
      //      pgraphics->move_to(2, 8);
      //      pgraphics->line_to(6, 12);
      //      pgraphics->line_to(13, 5);
      //      pgraphics->move_to(2, 9);
      //      pgraphics->line_to(6, 13);
      //      pgraphics->line_to(13, 6);
      //   }
      //}
      //pgraphics->OffsetViewportOrg(-rectangleClient.left, -rectangleClient.top);

   }


   void check_box::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == e_timer_check_toggle_animation)
      {

         set_need_redraw();

         post_redraw();

         if (m_durationAnimationStart.elapsed() > m_durationAnimationPeriod)
         {

            KillTimer(ptimer->m_uEvent);

         }

      }
//      else if (ptimer->m_uEvent == e_timer_command_probe)
//      {
//
//         ::user::menu_command command(this);
//
//         command.m_atom = m_atom;
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

      ::user::interaction::_001OnTimer(ptimer);

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

         _001ToggleCheck(::e_source_user);

      }

   }


   bool check_box::on_click(const ::item & item)
   {

      m_dPosition = 0.0;

      m_durationAnimationStart.Now();

      SetTimer(e_timer_check_toggle_animation, 12_ms);

      _001ToggleCheck(::e_source_user);

      return true;


   }


   void check_box::handle(::topic * ptopic, ::context * pcontext)
   {

      interaction::handle(ptopic, pcontext);

   }


   void check_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);
      
      MESSAGE_LINK(e_message_create, pchannel, this, &check_box::on_message_create);

   }


   void check_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      m_propertyCheck = fetch_property(m_atom, true);

   }


} // namespace user
