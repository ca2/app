#include "platform.h"
#include "main_window.h"
#include "application.h"
#include <math.h>
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/encoding_options.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/user/control_box_icon.h"
#include "aura/message/user.h"
#include "aura/platform/system.h"
#include "bred/user/user/gpu_shader_host.h"
#include "bred/user/user/gpu_shader_render.h"


namespace app_shader
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_enonclient.erase(::user::e_non_client_background);

      m_enonclient.erase(::user::e_non_client_focus_rect);

      //m_colorBackground = {};

      m_bDefaultClickHandling = true;

   }


   main_window::~main_window()
   {

   }


   ::user::enum_translucency main_window::get_translucency(::user::style* pstyle)
   {

      return ::user::e_translucency_present;

   }


   void main_window::install_message_routing(::channel * psender)
   {

      app_consumer < ::app_shader::application, ::user::main_window >::install_message_routing(psender);
      USER_MESSAGE_LINK(::user::e_message_create,psender,this,&::app_shader::main_window::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &::app_shader::main_window::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_key_down, psender, this, &::app_shader::main_window::on_message_key_down);
      //USER_MESSAGE_LINK(::user::e_message_switch, psender, this, &main_window::on_message_switch);

   }




   void main_window::on_message_create(::message::message* pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      construct_newø(m_pappshaderhost);


      m_pappshaderhost->create_child(this);

      m_pappshaderhost->display();



//      {
//
//         tool().add_item(allocateø ::item(e_element_close_button, id_close_app));
//
////         auto pitem = user_item(::e_element_close_button);
////
////         if (pitem)
////         {
////
////            *pitem = ::e_element_close_icon;
////
////         }
//
//      }

      {

         auto pitemSwitch = allocateø ::item(::e_element_switch_button, ::id_switch);

         tool().add_item(pitemSwitch);

         user_item(pitemSwitch)->m_ezorder = ::user::e_zorder_front;

      }

//      {
//
//         tool().add_item(allocateø ::item(::e_element_maximize_button, ::id_maximize));
//
//         //auto pitem = user_item(::e_element_maximize_button);
//
////         if (pitem)
////         {
////
////            *pitem = ::e_element_maximize_icon;
////
////         }
//
//      }


//      {
//
//
//         tool().add_item(allocateø ::item(e_element_minimize_button, id_minimize));
//
////         auto pitem = user_item(::e_element_minimize_button);
////
////         if (pitem)
////         {
////
////            *pitem = ::e_element_minimize_icon;
////
////         }
//
//      }

//      top_level()->set_fps_interest();
      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);


      m_pappshaderhost->switch_shader();

   }


   void main_window::on_message_destroy(::message::message * pmessage)
   {


   }


   void main_window::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_pappshaderhost->m_bSaveFrame = true;

      }


   }



   //void main_window::on_message_switch(::message::message* pmessage)
   //{

   //   switch_shader();

   //   pmessage->m_bRet = true;

   //}


   void main_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == "simple_checkbox"
         || ptopic->id() == "no_client_frame")
      {

         set_need_redraw();

      }

      ::user::interaction::handle(ptopic, phandlercontext);

   }


   bool main_window::keyboard_focus_is_focusable() 
   {

      return true;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {




      //auto rectangleX = this->rectangle();

      //auto & prender = m_pappshaderhost->m_maprender[m_pappshaderhost->m_strCurrentShaderPath];

      //if(::is_set(prender))
      //{

      //   prender->_001OnDraw(pdraw2dgraphics);

      //   if (m_pappshaderhost->m_bSaveFrame)
      //   {

      //      m_pappshaderhost->m_bSaveFrame = false;

      //      auto pimage = image()->create_image(rectangleX.size(), draw2d_domain());

      //      auto pdraw2dgraphics = pimage->acquire_graphics();

      //      prender->_001OnDraw(pdraw2dgraphics);

      //      fork([this, pimage]()
      //           {

      //              ::image::encoding_options encodingoptions;

      //              encodingoptions.m_eformat = ::image::e_format_png;

      //              string strDate = datetime()->date_time_text_for_file();

      //              image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

      //           });

      //   }
      //}

      // Draw the window tools after the child shader host.

   }


   void main_window::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::main_window::_001OnNcPostDraw(pdraw2dgraphics);

      //for (auto pitem : {m_pitemSwitch, m_pitemClose, m_pitemMaximize, m_pitemMinimize})
      //{
      //   if (pitem) _001DrawItem(pdraw2dgraphics, *user_item(pitem), ::user::e_state_none);
      //}

      // Draw after child windows so the shader host cannot cover this probe.
      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      pdraw2dgraphics->fill_solid_rectangle({ 16, 16, 80, 80 }, argb(128, 100, 180, 240));

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      //if (!m_pitemSwitch)
      //{
      //   m_pitemSwitch = allocateø ::item(::e_element_switch_button, ::id_switch);
      //   m_pitemClose = allocateø ::item(::e_element_close_button, ::id_close_app);
      //   m_pitemMaximize = allocateø ::item(::e_element_maximize_button, ::id_maximize);
      //   m_pitemMinimize = allocateø ::item(::e_element_minimize_button, ::id_minimize);
      //}
      //for (auto pitem : {m_pitemSwitch, m_pitemClose, m_pitemMaximize, m_pitemMinimize})
      //{
      //   ::i32_rectangle r;
      //   get_element_rectangle(r, pitem->m_item.m_eelement);
      //   auto pu = user_item(pitem);
      //   pu->m_rectangle2 = r;
      //   pu->m_ezorder = ::user::e_zorder_front;
      //}
      //auto rectangleShader = rectangleX;
      //rectangleShader.top += 32;
      //rectangleShader.bottom -= 48;
      m_pappshaderhost->place(rectangleX);

      auto & prender = m_pappshaderhost->m_mapusergpushaderrender[m_pappshaderhost->m_strCurrentShaderPath];

      if(::is_set(prender))
      {

         prender->m_rectangle = rectangleX;

         prender->on_layout(pdraw2dgraphics);

      }

      ::user::main_window::on_layout(pdraw2dgraphics);

   }


   //::item_pointer main_window::hit_test(const ::i32_point & point, ::user::e_zorder ezorder)
   //{
   //   for (auto pitem : {m_pitemSwitch, m_pitemClose, m_pitemMaximize, m_pitemMinimize})
   //   {
   //      if (pitem && user_item_rectangle(user_item(pitem), ::user::e_layout_design).contains(point))
   //         return pitem;
   //   }
   //   return ::user::main_window::hit_test(point, ezorder);
   //}


   bool main_window::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (pitem && (pitem->m_item.m_eelement == ::e_element_switch_button
         || pitem->m_item.m_eelement == ::e_element_switch_icon))
      {
         m_pappshaderhost->switch_shader();
         return true;
      }


      if (::user::interaction::on_click(pitem, pmouse))
      {

         return true;

      }

      return true;

   }


   //void main_window::update_shader(const ::scoped_string & scopedstrShaderPath)
   //{

   //   {

   //      //::user::lock_sketch_to_design lockSketchToDesign(this);

   //      auto prender = create_newø < render >();

   //      if (!prender)
   //      {

   //         return;

   //      }

   //      prender->m_puserinteraction = this;

   //      string strText;

   //      prender->m_strShaderPath = scopedstrShaderPath;

   //      prender->update_shader();

   //      {

   //         synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //         m_maprender[scopedstrShaderPath] = prender;

   //      }

   //      set_need_layout();

   //   }

   //   post_redraw();

   //}


   //void main_window::_001DrawItem(::draw2d::graphics_pointer& pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate)
   //{

   //   ::user::interaction::_001DrawItem(pdraw2dgraphics, useritem, estate);

   //}


   //void main_window::switch_shader()
   //{

   //   auto papp = get_app();

   //   auto strNextShaderPath = papp->get_next_shader_path(m_strCurrentShaderPath);

   //   if (strNextShaderPath == m_strCurrentShaderPath)
   //   {

   //      return;

   //   }

   //   m_strCurrentShaderPath = strNextShaderPath;

   //   update_shader(strNextShaderPath);

   //}


} // namespace app_shader



