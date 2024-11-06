// From userex/color_impact 2023-10-09 01:56 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "color_selector_control.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/image32.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/drawing.h"
#include "acme/handler/topic.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/message/user.h"
//#include "aura/operating_system/windows_common/graphics.h"
#include "aura/platform/system.h"
#include "base/user/user/document.h"


namespace user
{


   color_selector_control::color_selector_control()
   {

      m_bMouseColorBeam = false;

      m_bCompact = false;

      m_atomImpact = COLORSEL_IMPACT;

      m_bLButtonPressed = false;

      m_atom = COLORSEL_IMPACT;

   }


   color_selector_control::~color_selector_control()
   {


   }


   void color_selector_control::on_initialize_particle()
   {

      ::user::interaction::on_initialize_particle();
      
      ::graphics::color_selector::on_initialize_particle();

   }


   //void color_selector_control::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void color_selector_control::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   void color_selector_control::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &color_selector_control::on_message_create);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &color_selector_control::on_message_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &color_selector_control::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &color_selector_control::on_message_left_button_up);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &color_selector_control::on_message_show_window);

   }


   void color_selector_control::set_sel_color(const ::color::hls & hls)
   {

      set_color(hls);

   }


   ::color::hls color_selector_control::get_sel_color()
   {

      return color_selector_get_color().get_hls();

   }


   void color_selector_control::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::interaction::handle(ptopic, pcontext);

   }


   //void color_selector_control::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   ::user::impact::handle(ptopic, pcontext);

   //}


   void color_selector_control::on_message_create(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //auto ppen = __create < ::draw2d::pen > ();

      //ppen->create_solid(1.0, argb(255, 255, 255, 255));

      //m_pimageBeam->g()->set(ppen);

      //m_pimageBeam->g()->DrawEllipse(rectangle_i32_dimension(0, 0, 32, 32));



      //get_parent_frame()->m_atom += ".color_sel";

      pmessage->previous();

      //if (get_document()->m_pviewTopic == nullptr)
      //{

      //   get_document()->m_pviewTopic = this;

      //}

      //set_impact_title("__CoLoR_");

      //set_frame_title("__CoLoR_");

   }


   void color_selector_control::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //::pointer<::message::show_window>pshowwindow(pmessage);

   }


   ::color::color color_selector_control::get_color()
   {

      auto color = color_selector_get_color();

      return color;

   }


   void color_selector_control::set_color(const ::color::color & color)
   {

      m_bMouseColorBeam = false;

      color_selector_set_color(color);

      set_need_layout();

      set_need_redraw();

   }


   //void color_selector_control::on_mouse_motion(const ::point_i32 & point)
   //{

   //   if (point.y() >= m_rectangleColors.bottom())
   //   {

   //      return;

   //   }

   //   if (point.x() < m_rectangleColors.left())
   //   {

   //      return;

   //   }

   //   if (point.y() < m_rectangleColors.top())
   //   {

   //      return;

   //   }

   //   int iColorsLeft = m_rectangleColors.left();

   //   int iColorsWidth = m_pimage->width();

   //   int iColorsRight = iColorsLeft + iColorsWidth;

   //   if (point.x() < iColorsRight)
   //   {

   //      int x = point.x() - iColorsLeft;

   //      int y = point.y() - m_rectangleColors.top();

   //      m_pointMouseColorBeam = point;

   //      m_bMouseColorBeam = true;

   //      ::color::color color;

   //      visual::color_with_shade_of_grey(color,
   //         x, y,
   //         iColorsWidth, m_rectangleColors.height());

   //      ::color::hls hls;

   //      color.get_hls(hls);

   //      m_hls.m_dH = hls.m_dH;

   //      m_hls.m_dS = hls.m_dS;

   //      rebuild_luminance();

   //      if (has_handler())
   //      {

   //         auto ptopic = create_topic(::id_after_change_cur_hover);

   //         ptopic->m_puserelement = this;

   //         ptopic->m_actioncontext = ::e_source_user;

   //         route(ptopic);

   //      }

   //      set_need_redraw();

   //      post_redraw();

   //   }
   //   else if (point.x() < m_rectangleColors.center().x() + m_rectangleColors.width() / 8)
   //   {

   //      auto pointLuminance = point - ::size_i32(m_rectangleColors.center().x(), m_rectangleColors.top());

   //      m_hls.m_dL = 1.0 - ((double)pointLuminance.y() / (double)m_pimage->height());

   //      if (has_handler())
   //      {

   //         auto ptopic = create_topic(::id_after_change_cur_hover);

   //         ptopic->m_puserelement = this;

   //         ptopic->m_actioncontext = ::e_source_user;

   //         route(ptopic);

   //      }

   //      set_need_redraw();

   //      post_redraw();

   //   }

   //}


   //void color_selector_control::rebuild_luminance()
   //{

   //   ::visual::shades_of_luminance(m_pimageLuminance, m_hls.m_dH, m_hls.m_dS);

   //}


   //void color_selector_control::draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & pointParam)
   //{

   //   point_f64 point(pointParam);

   //   double dSize = 17.0;

   //   size_f64 sizeBeam(dSize, dSize);

   //   rectangle_f64 rectangleOuter(point.x() - sizeBeam.cx() / 2.0, point.y() - sizeBeam.cy() / 2.0, point.x() + sizeBeam.cx() / 2.0, point.y() + sizeBeam.cy() / 2.0);

   //   rectangle_f64 rectangleInner(rectangleOuter);

   //   rectangleInner.deflate(sizeBeam.cx() / 4.0, sizeBeam.cy() / 4.0);

   //   auto pbrush = __create < ::draw2d::brush >();

   //   pbrush->create_solid(argb(255, 0, 0, 0));

   //   pgraphics->set(pbrush);

   //   double dHalfTriBase = dSize / 8.0;

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(rectangleOuter.left(), point.y() - dHalfTriBase));
   //      pointa.add(point_f64(rectangleInner.left(), point.y()));
   //      pointa.add(point_f64(rectangleOuter.left(), point.y() + dHalfTriBase));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(point.x() - dHalfTriBase, rectangleOuter.top()));
   //      pointa.add(point_f64(point.x(), rectangleInner.top()));
   //      pointa.add(point_f64(point.x() + dHalfTriBase, rectangleOuter.top()));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(rectangleOuter.right(), point.y() - dHalfTriBase));
   //      pointa.add(point_f64(rectangleInner.right(), point.y()));
   //      pointa.add(point_f64(rectangleOuter.right(), point.y() + dHalfTriBase));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(point.x() - dHalfTriBase, rectangleOuter.bottom()));
   //      pointa.add(point_f64(point.x(), rectangleInner.bottom()));
   //      pointa.add(point_f64(point.x() + dHalfTriBase, rectangleOuter.bottom()));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //}


   //void color_selector_control::draw_level(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleW, int yParam)
   //{

   //   double y = yParam;

   //   double dSize = 17.0;

   //   rectangle_f64 rectangleInner(rectangleW);

   //   rectangle_f64 rectangleOuter(rectangleInner);

   //   rectangleOuter.inflate(dSize / 2.0, dSize / 2.0);

   //   auto pbrush = __create < ::draw2d::brush >();

   //   pbrush->create_solid(argb(255, 0, 0, 0));

   //   pgraphics->set(pbrush);

   //   double dHalfTriBase = dSize / 8.0;

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(rectangleOuter.left(), y - dHalfTriBase));
   //      pointa.add(point_f64(rectangleInner.left(), y));
   //      pointa.add(point_f64(rectangleOuter.left(), y + dHalfTriBase));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //   {

   //      point_double_array pointa;

   //      pointa.add(point_f64(rectangleOuter.right(), y - dHalfTriBase));
   //      pointa.add(point_f64(rectangleInner.right(), y));
   //      pointa.add(point_f64(rectangleOuter.right(), y + dHalfTriBase));

   //      pgraphics->fill_polygon(pointa);

   //   }

   //}


   void color_selector_control::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      color_selector::_001OnDraw(pgraphics);

   }

   //   ::rectangle_i32 rC;

   //   rC = this->rectangle();

   //   pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

   //   ::rectangle_i32 rTarget;

   //   rTarget.top_left() = m_rectangleColors.top_left();

   //   if (!m_pimage)
   //   {

   //      return;

   //   }

   //   rTarget.set_size(m_pimage->get_size());

   //   ::rectangle_i32 rSource = m_pimage->rectangle();

   //   ::rectangle_i32 rCursor;

   //   {

   //      ::image::image_source imagesource(m_pimage, rSource);

   //      ::image::image_drawing_options imagedrawingoptions(rTarget);

   //      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   //      pgraphics->draw(imagedrawing);

   //   }

   //   ::point_i32 point;

   //   if (m_bMouseColorBeam)
   //   {

   //      point = m_pointMouseColorBeam;

   //   }
   //   else
   //   {

   //      point.x() = (int)(rTarget.left() + rTarget.width() * m_hls.m_dH);

   //      point.y() = (int)(rTarget.top() + rTarget.height() * (1.0 - m_hls.m_dS));

   //   }

   //   draw_beam(pgraphics, point);

   //   ::rectangle_i32 rectangleLum1;

   //   rectangleLum1.top_left() = m_rectangleColors.top_left() + ::size_i32(m_pimage->width() - 1, 0);

   //   rectangleLum1.set_size(m_pimageLuminance->get_size());

   //   rSource = m_pimageLuminance->rectangle();

   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   {

   //      ::image::image_source imagesource(m_pimageLuminance);

   //      ::image::image_drawing_options imagedrawingoptions(rectangleLum1);

   //      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   //      pgraphics->draw(imagedrawing);

   //   }

   //   rTarget.top_left() = m_rectangleColors.top_left() + ::size_i32(m_pimage->width() - 1 + m_pimageLuminance->get_size().cx() - 1, 0);

   //   rTarget.set_size(m_rectangleColors.right() - rTarget.left(), m_pimage->height());

   //   pgraphics->fill_rectangle(rTarget, get_color());

   //   int y = (int)(rectangleLum1.top() + (1.0 - m_hls.m_dL) * rectangleLum1.height());

   //   draw_level(pgraphics, rectangleLum1, y);

   //}


   void color_selector_control::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_pointHost;

      host_to_client()(point);

      on_mouse_motion(point);

      pmouse->m_bRet = true;

      set_mouse_capture();

      m_bLButtonPressed = true;

   }


   void color_selector_control::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_pointHost;

      host_to_client()(point);

      on_mouse_motion(point);

      pmouse->m_bRet = true;

      defer_release_mouse_capture();

      m_bLButtonPressed = false;

      if (is_ok_target(point))
      {

         if (has_handler())
         {

            auto ptopic = create_topic(::id_after_change_cur_sel);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            route(ptopic);

         }
         
         if(m_callbackHls)
         {
            
            m_callbackHls(m_hls, true);
            
         }

      }

   }


   void color_selector_control::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_bLButtonPressed)
      {

         ::point_i32 point = pmouse->m_pointHost;

         host_to_client()(point);

         on_mouse_motion(point);

         pmouse->m_bRet = true;

      }

   }


   void color_selector_control::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(this->rectangle().area() < (48 * 48))
      {

         return;

      }

         ::user::interaction::on_layout(pgraphics);

      layout_color_selector(this->rectangle());

   }


   void color_selector_control::on_after_hover_color_change()
   {

      color_selector::on_after_hover_color_change();

      if (has_handler())
      {

         auto ptopic = create_topic(::id_after_change_cur_hover);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext = ::e_source_user;

         route(ptopic);

      }

      set_need_redraw();

      post_redraw();

   }


} // namespace user



