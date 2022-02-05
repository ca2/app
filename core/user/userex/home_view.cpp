#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/update.h"


//#if defined(__APPLE__)
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

      m_idImpact = COLORSEL_IMPACT;

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
      MESSAGE_LINK(e_message_show_window, pchannel, this, &home_view::on_message_show_window);

   }


   void home_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   //void home_view::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   ::user::impact::handle(ptopic, pcontext);

   //}


   void home_view::on_message_create(::message::message * pmessage)
   {

      //m_pimageBeam->create_image(this, ::size_i32(32, 32));

      //m_pimageBeam->fill(0);

      //auto ppen = __create < ::draw2d::pen > ();

      //ppen->create_solid(1.0, argb(255, 255, 255, 255));

      //m_pimageBeam->g()->set(ppen);

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


   void home_view::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
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

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      set_mouse_capture();

   }


   void home_view::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      screen_to_client(point);

      on_mouse(point);

      pmouse->m_bRet = true;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      ::topic topic;

      topic.m_id = ::id_after_change_cur_sel;

      topic.m_id = m_idImpact;

      topic.m_puserelement = this;

      topic.m_actioncontext = ::e_source_user;

      route(&topic);

   }


   void home_view::on_message_mouse_move(::message::message * pmessage)
   {

      //auto pmouse = pmessage->m_union.m_pmouse;

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

      ::rectangle_i32 rectangleColors;

      get_client_rect(rectangleColors);

      //if (!m_bCompact)
      //{

      //   rectangleColors.left = rectangleClient.center().x;
      //   rectangleColors.bottom = rectangleClient.center().y;

      //   rectangleColors.deflate(rectangleClient.width() / 16, rectangleClient.height() / 16);

      //}

      //m_rectangleColors = rectangleColors;

      //m_pimage = create_image({m_rectangleColors->width() / 2,  m_rectangleColors->height()});

      //m_pimage->g()->draw(m_pimage->rectangle(), m_pimageTemplate->get_graphics(), m_pimageTemplate->rectangle());

      //m_pimageLuminance = create_image({m_rectangleColors->width() / 8,  m_rectangleColors->height()});

      //rebuild_luminance();

   }


} // namespace userex



