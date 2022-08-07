#include "framework.h"
#include "axis/user/_user.h"
#include "acme/constant/timer.h"


void scroll_x(RECT32 * prect, double dRateX, const ::rectangle & rectangle)
{

   ::i32 w = ::width(prect);

   prect->left = (::i32) (rectangle.left + (rectangle.width() - w) * dRateX);

   prect->right = prect->left + w;

}


namespace user
{


   check_box::check_box(e_style estyle)
   {

      m_durationAnimationPeriod = 300_ms;

      m_estyle = estyle;

   }


   check_box::~check_box()
   {

   }


   void check_box::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if(echeck != ::e_check_unchecked && echeck != ::e_check_checked && echeck != ::e_check_tristate)
      {

         // default value when setting a value that does not match the ones above

         echeck = ::e_check_checked;

      }

      if(this->echeck() != echeck)
      {

         check::_001SetCheck(echeck, context);

         ::topic topic;

         topic.m_puserinteraction = this;

         //topic.m_atom = m_atom;

         topic.m_atom = ::id_set_check;

         topic.m_actioncontext = context;

         route(&topic);

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


   void check_box::_001OnDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::axis::style) pstyle = get_style(pgraphics);

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

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      int w = rectangleClient.width();

      int h = rectangleClient.height();

      if (w <= 0 || h <= 0)
      {

         return;

      }

      auto echeck = this->echeck();

      ::draw2d::savedc savedc(pgraphics);

      pgraphics->offset_origin(rectangleClient.left, rectangleClient.top);

      ::rectangle rectangleCheckBox;

      ::rectangle rectangleText;

      {

         int iSize = minimum(15 * w / 15, 15 * h / 15);

         rectangleCheckBox.left = 0;
         rectangleCheckBox.top = 0;
         rectangleCheckBox.right = iSize;
         rectangleCheckBox.bottom = iSize;

         rectangleText = rectangleClient;

         rectangleText.left = rectangleCheckBox.right + 4;

         if (echeck == ::e_check_tristate)
         {

            pgraphics->fill_rectangle(rectangleCheckBox, argb(255, 220, 220, 220));

         }

         if (drawcontext.m_bListItemHover)
         {

            pgraphics->draw_rectangle(rectangleCheckBox, argb(255, 60, 120, 200));

         }
         else
         {

            pgraphics->draw_rectangle(rectangleCheckBox, argb(255, 128, 128, 128));

         }

         if (echeck == ::e_check_tristate || echeck == ::e_check_checked)
         {

            if (pstyle)
            {

               pstyle->draw_check(echeck, rectangleCheckBox, pgraphics);

            }

         }

      }

      {

         string strText;

         get_window_text(strText);

         int iDrawParams = e_align_left_center | DT_SINGLELINE;

         pgraphics->set_font(this, ::e_element_none);

         color32_t crText;

         if (drawcontext.m_bListItemHover)
         {

            crText = argb(255, 0, 0, 0);

         }
         else
         {

            crText = argb(255, 0, 0, 0);

         }

         pgraphics->set_text_color(crText);

         pgraphics->draw_text(strText, rectangleText, iDrawParams);

      }

   }


   void check_box::_001OnDrawToggleSwitch(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::axis::style) pstyle = get_style(pgraphics);

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

      ::rectangle rectangleClient;

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

      ::rectangle rectangle(1, 1, w-2, h-2);

      ::rectangle rectangleEllipse(1, 1, h-2, h-2);

      //double dNow = ::get_millis();

      ::draw2d::path_pointer point(e_create);

      ::rectangle rectangleL(1, 1, h-2, h-2);

      auto rectangleR = rectangle_i32_dimension(h-2, 1, h-2, h-2);

      point->add_arc(rectangleL, -90_degree, -180_degree);

      point->add_line((rectangleL.left + rectangleL.right) / 2, rectangleL.bottom);

      point->add_line((rectangleR.left + rectangleR.right) / 2, rectangleR.bottom);

      point->add_arc(rectangleR, 90.0, -180.0);

      point->add_line((rectangleR.left + rectangleR.right) / 2, rectangleR.top);

      point->add_line((rectangleL.left + rectangleL.right) / 2, rectangleL.top);

      point->close_figure();

      ::draw2d::pen_pointer point1(e_create);

      ::draw2d::pen_pointer p0(e_create);

      ::draw2d::brush_pointer pbrush1(e_create);

      point1->create_solid(2.0, argb(255, 0, 0, 0));

      p0->create_solid(2.0, argb(255, 90, 150, 255));

      point1->m_ealign = draw2d::pen::e_align_center;

      pbrush1->create_solid(argb(255, 90, 150, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      double dRate = m_durationAnimationStart.period_rate(m_durationAnimationPeriod);

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

         color32_t color32 = argb(255, 255, 255, 255);

         auto pbrush = __create < ::draw2d::brush > ();

         m_dPosition = ::sin((::aura::get_system()->math().get_pi() / 2.0) * dRate);

         double dRate = m_dPosition;

         if (bComplement)
         {

            dRate = 1.0 - dRate;

         }

         pbrush1->m_color = (pbrush1->m_color.operator color32_t() & 0xffffff) | ((byte(255.0 * dRate)) << 24);

         pbrush1->set_modified();

         p0->m_color = pbrush1->m_color;

         p0->set_modified();

         pgraphics->set(pbrush1);
         pgraphics->set(p0);

         pgraphics->path(point);

         pbrush->create_solid(argb(255,
                               (byte)((double) colorref_get_r_value(color32) * dRate),
                               (byte)((double) colorref_get_g_value(color32) * dRate),
                               (byte)((double) colorref_get_b_value(color32) * dRate)));

         ::scroll_x(rectangleEllipse, dRate, rectangle);

         rectangleEllipse.rate(0.6);

         pgraphics->set(pbrush);

         pgraphics->fill_ellipse(rectangleEllipse);

         byte bAlphaP1 = (byte) (255.0 * (1.0 - dRate));

         color32_t crP1 = argb(bAlphaP1, 0, 0, 0);

         point1->create_solid(2.0, crP1);

         point1->set_modified();

         pgraphics->set(point1);

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         pgraphics->draw_path(point);


      }
      else
      {

         if (echeck() == ::e_check_unchecked)
         {

            rectangleEllipse.Align({e_align_left, e_align_vertical_center}, rectangle);

            rectangleEllipse.rate(0.6);

            auto pbrush = __create < ::draw2d::brush > ();

            pbrush->create_solid(argb(255, 0, 0, 0));

            pgraphics->set(pbrush);

            pgraphics->fill_ellipse(rectangleEllipse);

            point1->create_solid(2.0, argb(255, 0, 0, 0));

            pgraphics->set(point1);

            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

            pgraphics->draw_path(point);


         }
         else
         {

            pgraphics->set(pbrush1);

            pgraphics->set(p0);

            pgraphics->path(point);

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

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      int iMin = maximum(rectangleClient.min_dim() -1, 1);

      ::rectangle rectangleCheckBox;
      rectangleCheckBox.left = 1;
      rectangleCheckBox.top = 1;
      rectangleCheckBox.right = iMin + 1;
      rectangleCheckBox.bottom = iMin + 1;

      color32_t crPen = argb(255, 0, 0, 0);
      color32_t crBrush;

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

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, crPen);

      pgraphics->set(ppen);

      auto pbrush = __create < ::draw2d::brush >();

      pbrush->create_solid(crBrush);

      pgraphics->set(pbrush);

      pgraphics->ellipse(rectangleCheckBox);
      //   pgraphics->draw_inset_3d_rectangle(rectangleCheckBox, argb(255, 128, 128, 128), argb(255, 128, 128, 128));
      //   if (m_echeck == e_check_tristate
      //      || m_echeck == e_check_checked)
      //   {
      //      auto ppen = __create < ::draw2d::pen > ();
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
      //pgraphics->offset_origin(-rectangleClient.left, -rectangleClient.top);

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


   bool check_box::on_click(::item * pitem)
   {

      m_dPosition = 0.0;

      m_durationAnimationStart.Now();

      SetTimer(e_timer_check_toggle_animation, 12);

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

      install_simple_ui_default_mouse_handling(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &check_box::on_message_create);

   }


   void check_box::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      m_ppropertyCheck = fetch_property(m_atom, true);

      add_update_notification(m_ppropertyCheck);

   }


} // namespace user
