// Created by camilo on 2026-11-01 11:53 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#include "platform.h"
#include "host.h"
#include "main_window.h"
#include "application.h"
#include "render.h"
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


namespace app_shader
{


   host::host()
   {

      m_bTransparent = true;

      m_enonclient.erase(::user::e_non_client_background);

      m_enonclient.erase(::user::e_non_client_focus_rect);

      //m_colorBackground = {};

      m_bDefaultClickHandling = true;

   }


   host::~host()
   {

   }


   ::user::enum_translucency host::get_translucency(::user::style * pstyle)
   {

      return ::user::e_translucency_present;

   }


   void host::install_message_routing(::channel * psender)
   {

      ::user::gpu_shader_host::install_message_routing(psender);
      USER_MESSAGE_LINK(::user::e_message_create, psender, this, &host::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &host::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_key_down, psender, this, &host::on_message_key_down);
      //USER_MESSAGE_LINK(::user::e_message_switch, psender, this, &host::on_message_switch);

   }




   void host::on_message_create(::message::message * pmessage)
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
      tool().add_item(allocateø ::item(::e_element_maximize_button, ::id_maximize));

      //      top_level()->set_fps_interest();
      add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);


      switch_shader();

   }


   void host::on_message_destroy(::message::message * pmessage)
   {


   }


   void host::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_bSaveFrame = true;

      }


   }





   void host::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == "simple_checkbox"
         || ptopic->id() == "no_client_frame")
      {

         set_need_redraw();

      }

      ::user::interaction::handle(ptopic, phandlercontext);

   }


   bool host::keyboard_focus_is_focusable()
   {

      return true;

   }


   ::image::image * host::drawn_frame_image()
   {

      auto rectangleX = this->rectangle();

      auto prender = get_current_render();

      if (::is_null(prender))
      {

         return nullptr;

      }

      prender->initialize_app_shader_render(this);

      auto pimageTarget = prender->drawn_frame_image();

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


   void host::_001OnNcPostDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::user::gpu_shader_host::_001OnNcPostDraw(pdraw2dgraphics);

   }


   void host::on_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if (::is_set(prender))
      {

         prender->m_rectangle = rectangleX;

         prender->on_layout(pdraw2dgraphics);

      }

      ::user::gpu_shader_host::on_layout(pdraw2dgraphics);




   }


   bool host::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (::user::interaction::on_click(pitem, pmouse))
      {

         return true;

      }

      return true;

   }


   ::app_shader::render * host::get_current_render()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if(!prender)
      {

         synchronouslock.unlock();

         //::user::lock_sketch_to_design lockSketchToDesign(this);

         auto prenderNew = create_newø < render >();

         if (!prenderNew)
         {

            throw ::exception(error_failed);

            return nullptr;

         }

         prenderNew->initialize_app_shader_render(this);

         string strText;

         prenderNew->m_strShaderPath = m_strCurrentShaderPath;

         prenderNew->update_shader();

         {

            synchronouslock.lock();

            prender = prenderNew;

            synchronouslock.unlock();

         }

         //set_need_layout();

      }

      //post_redraw();

      return prender;

   }


   void host::_001DrawItem(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::item & useritem, const ::user::e_state & estate)
   {

      ::user::interaction::_001DrawItem(pdraw2dgraphics, useritem, estate);

   }



   void host::on_user_interface_switch()
   {

      switch_shader();

   }


   void host::switch_shader()
   {

      auto papp = get_app();

      auto strNextShaderPath = papp->get_next_shader_path(m_strCurrentShaderPath);

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


} // namespace app_shader



