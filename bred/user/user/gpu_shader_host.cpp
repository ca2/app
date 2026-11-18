// Created by camilo on 2026-11-01 11:45 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "gpu_shader_host.h"
#include "gpu_shader_list.h"
#include "gpu_shader_render.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/image32_t.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/session.h"
#include "acme/prototype/datetime/datetime.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/block.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/debug_scope.h"
#include "bred/gpu/window_attachment.h"
#include "bred/gpu/layer.h"
#include "bred/graphics3d/asset_manager.h"
#include "bred/graphics3d/engine_instance.h"
#include "bred/graphics3d/input.h"
#include "bred/graphics3d/scene_base.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/graphics_context.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/aaa_target.h"
#include "aura/message/user.h"
#include "aura/windowing/window.h"
#include "bred/graphics3d/types.h"
#include "aura/platform/application.h"
#include "bred/gpu/graphics.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/texture_site.h"
#include "bred/prodevian/immersion.h"
#include <atomic>
#include <cstdlib>


namespace user
{



   gpu_shader_host::gpu_shader_host()
   {

      m_bTransparent = true;

      m_enonclient.erase(::user::e_non_client_background);

      m_enonclient.erase(::user::e_non_client_focus_rect);

      //m_colorBackground = {};

      m_bDefaultClickHandling = true;

      //m_emouse = ::gpu_shader_host::e_mouse_updateLook;
//m_ekeyboard = ::gpu_shader_host::e_keyboard_updateMovement;
////m_bAbsoluteMousePosition = false;
//m_bShouldClose = false;
      m_bFramebufferResized = false;
      m_psession = nullptr;


   }


   gpu_shader_host::~gpu_shader_host()
   {

   }





#ifdef _DEBUG


   ::i64 gpu_shader_host::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   ::i64 gpu_shader_host::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif
   //::user::enum_translucency gpu_shader_host::get_translucency(::user::style * pstyle)
   //{

   //   return ::user::e_translucency_present;

   //}


   void gpu_shader_host::install_message_routing(::channel * psender)
   {

      ::user::gpu_interaction::install_message_routing(psender);
      USER_MESSAGE_LINK(::user::e_message_create, psender, this, &gpu_shader_host::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &gpu_shader_host::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_key_down, psender, this, &gpu_shader_host::on_message_key_down);
      USER_MESSAGE_LINK(::user::e_message_key_up, psender, this, &gpu_shader_host::on_message_key_up);

      //USER_MESSAGE_LINK(::user::e_message_switch, psender, this, &gpu_shader_host::on_message_switch);

   }




   void gpu_shader_host::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

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

         //         auto pitem = user_item(::e_element_switch_button);
         //
         //         *pitem = ::e_element_switch_button;

      }

      //      {
      //
      //
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
      //tool().add_item(allocateø::item(::e_element_maximize_button, ::id_maximize));

      //      top_level()->set_fps_interest();
      //add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);


      //switch_shader();

   }


   void gpu_shader_host::on_message_destroy(::message::message * pmessage)
   {


   }


   //void gpu_shader_host::on_message_key_down(::message::message * pmessage)
   //{

   //   auto pkey = pmessage->m_union.m_pkey;

   //   if (pkey->m_ekey == ::user::e_key_s)
   //   {

   //      m_bSaveFrame = true;

   //   }


   //}





   void gpu_shader_host::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == "simple_checkbox"
         || ptopic->id() == "no_client_frame")
      {

         set_need_redraw();

      }

      ::user::interaction::handle(ptopic, phandlercontext);

   }


   bool gpu_shader_host::keyboard_focus_is_focusable()
   {

      return true;

   }


   ::image::image * gpu_shader_host::drawn_frame_image()
   {

      auto rectangleX = this->rectangle();

      auto pusergpushaderrender = get_current_render();

      if (::is_null(pusergpushaderrender))
      {

         return nullptr;

      }

      pusergpushaderrender->initialize_user_gpu_shader_render(this);

      auto pimageTarget = pusergpushaderrender->drawn_frame_image();

      if (m_bSaveFrame)
      {

         m_bSaveFrame = false;

         ::image::image_pointer pimage = pimageTarget->clone();

         //auto pimage = image()->create_image(rectangleX.size(), draw2d_domain());

         //auto pdraw2dgraphics = pimage->acquire_graphics();

         //prender->_001OnDraw(pdraw2dgraphics);

         fork([this, pimage]()
               {

               ::image::encoding_options encodingoptions;

               encodingoptions.m_eformat = ::image::e_format_png;

               string strDate = datetime()->date_time_text_for_file();

               image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

               });

      }
      //      }

            // The shader has finished; draw controls on the same active UI target.

      return pimageTarget;

   }


   void gpu_shader_host::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::gpu_interaction::_001OnDraw(pdraw2dgraphics);

   }


   void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::gpu_interaction::_001OnNcPostDraw(pdraw2dgraphics);

   }


   void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      auto & pusergpushaderrender = m_mapusergpushaderrender[m_strCurrentShaderPath];

      if (::is_set(pusergpushaderrender))
      {

         pusergpushaderrender->m_rectangle = rectangleX;

         pusergpushaderrender->on_layout(pdraw2dgraphics);

      }

      ::user::gpu_interaction::on_layout(pdraw2dgraphics);

   }


   bool gpu_shader_host::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (::user::interaction::on_click(pitem, pmouse))
      {

         return true;

      }

      return true;

   }


   ::user::gpu_shader_render * gpu_shader_host::get_current_render()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & pusergpushaderrender = m_mapusergpushaderrender[m_strCurrentShaderPath];

      if (!pusergpushaderrender)
      {

         synchronouslock.unlock();

         //::user::lock_sketch_to_design lockSketchToDesign(this);

         auto pusergpushaderrenderNew = create_newø < ::user::gpu_shader_render >();

         if (!pusergpushaderrenderNew)
         {

            throw ::exception(error_failed);

            return nullptr;

         }

         pusergpushaderrenderNew->initialize_user_gpu_shader_render(this);

         string strText;

         pusergpushaderrenderNew->m_strShaderPath = m_strCurrentShaderPath;

         pusergpushaderrenderNew->update_shader();

         {

            synchronouslock.lock();

            pusergpushaderrender = pusergpushaderrenderNew;

            synchronouslock.unlock();

         }

         //set_need_layout();

      }

      //post_redraw();

      return pusergpushaderrender;

   }


   //void gpu_shader_host::_001DrawItem(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate)
   //{

   //   ::user::interaction::_001DrawItem(pdraw2dgraphics, useritem, estate);

   //}



   void gpu_shader_host::on_user_interface_switch()
   {

      switch_shader();

   }


   void gpu_shader_host::switch_shader()
   {

      auto pusergpushaderlist = user_gpu_shader_list();

      auto strNextShaderPath = pusergpushaderlist->get_next_shader_path(m_strCurrentShaderPath);

      if (strNextShaderPath == m_strCurrentShaderPath)
      {

         return;

      }

      information() << "app_shader switch: " << m_strCurrentShaderPath << " -> " << strNextShaderPath;

      m_strCurrentShaderPath = strNextShaderPath;

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   ::user::gpu_shader_list * gpu_shader_host::user_gpu_shader_list()
   {

      if (!m_pusergpushaderlist)
      {

         construct_newø(m_pusergpushaderlist);

         m_pusergpushaderlist->initialize_user_gpu_shader_list(this);

      }

      return m_pusergpushaderlist;

   }


   ////void gpu_shader_host::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   ////   //void gpu_shader_host::_000OnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)

   //   }

   //   return m_pgpushaderlist;

   //}


   //void gpu_shader_host::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   //   //void gpu_shader_host::_000OnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   //{

   //   ::user::gpu_interaction::_001OnDraw(pdraw2dgraphics);

   //}


   //void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{


   //}


   //   ::key::enum_state gpu_shader_host::get_key_state(const ::user::e_key & ekey)
     // {

       //  if (session()->is_key_pressed(ekey))
         //{

           // return ::key::e_state_pressed;

    //     }

      //   return ::key::e_state_none;

      //}




   //::image::image * gpu_shader_host::drawn_frame_image()
   //{

   //   auto rectangleX = this->rectangle();

   //   auto prender = get_current_render();

   //   if (::is_null(prender))
   //   {

   //      return nullptr;

   //   }

   //   prender->initialize_app_shader_render(this);

   //   auto pimageTarget = prender->drawn_frame_image();

   //   if (m_bSaveFrame)
   //   {

   //      m_bSaveFrame = false;

   //      ::image::image_pointer pimage = pimageTarget->clone();

   //      //auto pimage = image()->create_image(rectangleX.size(), draw2d_domain());

   //      //auto pdraw2dgraphics = pimage->acquire_graphics();

   //      //prender->_001OnDraw(pdraw2dgraphics);

   //      fork([this, pimage]()
   //            {

   //               ::image::encoding_options encodingoptions;

   //               encodingoptions.m_eformat = ::image::e_format_png;

   //               string strDate = datetime()->date_time_text_for_file();

   //               image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

   //            });

   //   }
   //   //      }

   //         // The shader has finished; draw controls on the same active UI target.

   //   return pimageTarget;

   //}


   //void gpu_shader_host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   ::user::gpu_interaction::_001OnNcPostDraw(pdraw2dgraphics);

   //}


   //void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   auto rectangleX = this->rectangle();

   //   if (rectangleX.is_empty())
   //   {

   //      return;

   //   }

   //   auto & prender = m_mapusergpurender[m_strCurrentShaderPath];

   //   if (::is_set(prender))
   //   {

   //      prender->m_rectangle = rectangleX;

   //      prender->on_layout(pdraw2dgraphics);

   //   }

   //   ::user::gpu_shader_host::on_layout(pdraw2dgraphics);




   //}



   //void gpu_shader_host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   //{

   //   ::user::gpu_interaction::on_layout(pdraw2dgraphics);

   //   //auto rectangleX = this->rectangle();

   //   //if (rectangleX.area() <= 0)
   //   //{

   //   //   return;

   //   //}

   //   //auto size = rectangleX.size();

   //   //m_iWidth = size.width();

   //   //m_iHeight = size.height();

   //   //if (!m_pgraphics3dengineinstance)
   //   //{

   //   //   defer_initialize_graphics3d_engine_instance(this->host_rectangle());

   //   //}
   //   //else if (m_pgraphics3dengineinstance->has_ok_flag())
   //   //{

   //   //   auto rectanglePlacement = this->host_rectangle();

   //   //   if (m_papplication->use_gpu_swap_chain())
   //   //   {

   //   //      // The interaction's cached screen origin can lag an X11 window
   //   //      // move. Compose in the current native window's coordinates.
   //   //      auto pwindow = this->window();
   //   //      rectanglePlacement.offset(pwindow->get_window_rectangle().origin());

   //   //   }
   //   //   else
   //   //   {

   //   //      rectanglePlacement.offset(-rectanglePlacement.top_left());

   //   //   }

   //   //   m_pgraphics3dengineinstance->on_layout(rectanglePlacement);

   //   //}

   //   ////reset_mouse_last_position();

   //}


   bool gpu_shader_host::wasWindowResized()
   {

      return m_bFramebufferResized;


   }


   void gpu_shader_host::resetWindowResizedFlag()
   {

      m_bFramebufferResized = false;

   }


   //::pointer < ::gpu_shader_host::key_map > gpu_shader_host::get_default_key_map()
   //{

   //   auto pmap = create_newø < ::gpu_shader_host::key_map>();
   //   using namespace ::gpu_shader_host;

   //   pmap->map(e_key_moveLeft, ::user::e_key_a);
   //   pmap->map(e_key_moveRight, ::user::e_key_d);
   //   pmap->map(e_key_moveForward, ::user::e_key_w);
   //   pmap->map(e_key_moveBackward, ::user::e_key_s);
   //   pmap->map(e_key_moveUp, ::user::e_key_e);
   //   pmap->map(e_key_moveDown, ::user::e_key_q);
   //   pmap->map(e_key_lookLeft, ::user::e_key_left);
   //   pmap->map(e_key_lookRight, ::user::e_key_right);
   //   pmap->map(e_key_lookUp, ::user::e_key_up);
   //   pmap->map(e_key_lookDown, ::user::e_key_down);
   //   pmap->map(e_key_Exit, ::user::e_key_escape);

   //   return pmap;

   //}


   ::f32 gpu_shader_host::getAspectRatio()
   {

      auto fH = fabs(static_cast<::f32>(this->height()));

      if (fH <= 0.00001)
      {

         return 1.0f;

      }

      return static_cast<::f32>(this->width()) / fH;

   }


   //void gpu_shader_host::prepare_mouse_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->prepare_mouse_input();

   //}


   //void gpu_shader_host::process_mouse_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->process_mouse_input();

   //}



   //void gpu_shader_host::process_keyboard_input()
   //{

   //   m_pgraphics3dengineinstance->m_pinput->process_keyboard_input();

   //}

} // namespace user



