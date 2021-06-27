#include "framework.h"
#include "core/user/userex/_userex.h"
#include "aura/update.h"


//#if defined(APPLEOS)
//#define ARGB_COLORREF(A, R, G, B) argb(A, R, G, B)
//#define COLORREF_get_a_value(color32) colorref_get_a_value(color32)
//#define COLORREF_get_r_value(color32) colorref_get_r_value(color32)
//#define COLORREF_get_g_value(color32) colorref_get_g_value(color32)
//#define COLORREF_get_b_value(color32) colorref_get_b_value(color32)
//#else
//#define ARGB_COLORREF(A, R, G, B) argb(A, B, G, R)
//#define COLORREF_get_a_value(color32) colorref_get_a_value(color32)
//#define COLORREF_get_r_value(color32) colorref_get_b_value(color32)
//#define COLORREF_get_g_value(color32) colorref_get_g_value(color32)
//#define COLORREF_get_b_value(color32) colorref_get_r_value(color32)
//#endif


namespace userex
{


   home_view::home_view()
   {

      m_idView = COLORSEL_IMPACT;

   }


   home_view::~home_view()
   {


   }


   void home_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void home_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void home_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &home_view::on_message_create);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &home_view::on_message_mouse_move);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &home_view::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &home_view::on_message_left_button_up);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &home_view::_001OnShowWindow);

   }


   void home_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   void home_view::on_control_event(::user::control_event * pevent)
   {

      ::user::impact::on_control_event(pevent);

   }


   void home_view::on_message_create(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //::draw2d::pen_pointer pen(e_create);

      //pen->create_solid(1.0, argb(255, 255, 255, 255));

      //m_pimageBeam->g()->set(pen);

      //m_pimageBeam->g()->DrawEllipse(rectangle_i32_dimension(0, 0, 32, 32));



      //get_parent_frame()->m_id += ".color_sel";

      pmessage->previous();

      if (get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = this;

      }

      set_impact_title("__CoLoR_");

      get_parent_frame()->set_frame_title("__CoLoR_");

   }


   void home_view::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
      //__pointer(::message::show_window) pshowwindow(pmessage);

   }


   //color home_view::get_color()
   //{

   //   //::color::color color;

   //   //color.set_hls(m_hls);

   //   //color.m_iA = 255;

   //   //return color.get_rgba();

   //   return 

   //}


   //void home_view::set_color(::color::color color)
   //{

   //   color.get_hls(m_hls);

   //}


   void home_view::on_mouse(const ::point_i32 & point)
   {


   }


   void home_view::rebuild_luminance()
   {

   }





   void home_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void home_view::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      set_mouse_capture();

   }


   void home_view::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      ::user::control_event ev;

      ev.m_eevent = ::user::e_event_after_change_cur_sel;

      ev.m_id = m_idView;

      ev.m_puie = this;

      ev.m_actioncontext = ::e_source_user;

      on_control_event(&ev);

   }


   void home_view::on_message_mouse_move(::message::message * pmessage)
   {

      //__pointer(::message::mouse) pmouse(pmessage);

   }


   void home_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::on_layout(pgraphics);

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.area() <= 0)
      {

         return;

      }

      ::rectangle_i32 rectColors;

      get_client_rect(rectColors);

      //if (!m_bCompact)
      //{

      //   rectColors.left = rectangleClient.center().x;
      //   rectColors.bottom = rectangleClient.center().y;

      //   rectColors.deflate(rectangleClient.width() / 16, rectangleClient.height() / 16);

      //}

      //m_rectColors = rectColors;

      //m_pimage = create_image({m_rectColors->width() / 2,  m_rectColors->height()});

      //m_pimage->g()->draw(m_pimage->rectangle(), m_pimageTemplate->get_graphics(), m_pimageTemplate->rectangle());

      //m_pimageLuminance = create_image({m_rectColors->width() / 8,  m_rectColors->height()});

      //rebuild_luminance();

   }


} // namespace userex



