#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif
#include "aura/update.h"


//#if defined(APPLEOS)
//#define ARGB_COLORREF(A, R, G, B) ARGB(A, R, G, B)
//#define COLORREF_get_a_value(cr) colorref_get_a_value(cr)
//#define COLORREF_get_r_value(cr) colorref_get_r_value(cr)
//#define COLORREF_get_g_value(cr) colorref_get_g_value(cr)
//#define COLORREF_get_b_value(cr) colorref_get_b_value(cr)
//#else
//#define ARGB_COLORREF(A, R, G, B) ARGB(A, B, G, R)
//#define COLORREF_get_a_value(cr) colorref_get_a_value(cr)
//#define COLORREF_get_r_value(cr) colorref_get_b_value(cr)
//#define COLORREF_get_g_value(cr) colorref_get_g_value(cr)
//#define COLORREF_get_b_value(cr) colorref_get_r_value(cr)
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

      MESSAGE_LINK(e_message_create, pchannel, this, &home_view::_001OnCreate);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &home_view::_001OnMouseMove);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &home_view::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &home_view::_001OnLButtonUp);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &home_view::_001OnShowWindow);

   }


   void home_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   void home_view::on_control_event(::user::control_event * pevent)
   {

      ::user::impact::on_control_event(pevent);

   }


   void home_view::_001OnCreate(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //::draw2d::pen_pointer pen(e_create);

      //pen->create_solid(1.0, ARGB(255, 255, 255, 255));

      //m_pimageBeam->g()->set(pen);

      //m_pimageBeam->g()->DrawEllipse(rect_dim(0, 0, 32, 32));



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

   //   //color color;

   //   //color.set_hls(m_hls);

   //   //color.m_iA = 255;

   //   //return color.get_rgba();

   //   return 

   //}


   //void home_view::set_color(color color)
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


   void home_view::_001OnLButtonDown(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      _001ScreenToClient(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      SetCapture();

   }


   void home_view::_001OnLButtonUp(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      _001ScreenToClient(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      ReleaseCapture();

      ::user::control_event ev;

      ev.m_eevent = ::user::e_event_after_change_cur_sel;

      ev.m_id = m_idView;

      ev.m_puie = this;

      ev.m_actioncontext = ::e_source_user;

      on_control_event(&ev);

   }


   void home_view::_001OnMouseMove(::message::message * pmessage)
   {

      //__pointer(::message::mouse) pmouse(pmessage);

   }


   void home_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::on_layout(pgraphics);

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      ::rectangle_i32 rectColors;

      get_client_rect(rectColors);

      //if (!m_bCompact)
      //{

      //   rectColors.left = rectClient.center().x;
      //   rectColors.bottom = rectClient.center().y;

      //   rectColors.deflate(rectClient.width() / 16, rectClient.height() / 16);

      //}

      //m_rectColors = rectColors;

      //m_pimage = create_image({m_rectColors->width() / 2,  m_rectColors->height()});

      //m_pimage->g()->draw(m_pimage->rectangle_i32(), m_pimageTemplate->get_graphics(), m_pimageTemplate->rectangle_i32());

      //m_pimageLuminance = create_image({m_rectColors->width() / 8,  m_rectColors->height()});

      //rebuild_luminance();

   }


} // namespace userex



