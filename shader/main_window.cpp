#include "framework.h"
#include "main_window.h"
#include "application.h"
#include "render.h"
#include <math.h>
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/user/control_box_icon.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/encoding_options.h"
#include "aura/graphics/image/context.h"
#include "aura/message/user.h"
#include "aura/platform/system.h"


namespace app_shader
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

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

      ::user::main_window::install_message_routing(psender);
      MESSAGE_LINK(e_message_create,psender,this,&main_window::on_message_create);
      MESSAGE_LINK(e_message_destroy, psender, this, &main_window::on_message_destroy);
      MESSAGE_LINK(e_message_key_down, psender, this, &main_window::on_message_key_down);
      MESSAGE_LINK(e_message_switch, psender, this, &main_window::on_message_switch);

   }




   void main_window::on_message_create(::message::message* pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

//      {
//
//         tool().add_item(__allocate ::item(e_element_close_button, id_close_app));
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

         tool().add_item(__allocate ::item(::e_element_switch_button, ::id_switch));

//         auto pitem = user_item(::e_element_switch_button);
//
//         *pitem = ::e_element_switch_button;

      }

//      {
//
//         tool().add_item(__allocate ::item(::e_element_maximize_button, ::id_maximize));
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
//         tool().add_item(__allocate ::item(e_element_minimize_button, id_minimize));
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


      switch_shader();

   }


   void main_window::on_message_destroy(::message::message * pmessage)
   {


   }


   void main_window::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_bSaveFrame = true;

      }


   }



   void main_window::on_message_switch(::message::message* pmessage)
   {

      switch_shader();

      pmessage->m_bRet = true;

   }


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


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if(::is_set(prender))
      {

         prender->_001OnDraw(pgraphics);

         if (m_bSaveFrame)
         {

            m_bSaveFrame = false;

            auto pimage = image()->create_image(rectangleX.size());

            ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

            prender->_001OnDraw(pgraphics);

            fork([this, pimage]()
                 {

                    ::image::encoding_options encodingoptions;

                    encodingoptions.m_eformat = ::image::e_format_png;

                    string strDate = datetime()->date_time_text_for_file();

                    image()->save_image("image://app_simple_shader-" + strDate + ".png", pimage, encodingoptions);

                 });

         }
      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if(::is_set(prender))
      {

         prender->m_rectangle = rectangleX;

         prender->on_layout(pgraphics);

      }

      ::user::main_window::on_layout(pgraphics);

   }


   bool main_window::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      if (::user::interaction::on_click(pitem, pmouse))
      {

         return true;

      }

      return true;

   }


   void main_window::update_shader(const ::string & strShaderPath)
   {

      {

         //::user::lock_sketch_to_design lockSketchToDesign(this);

         auto prender = __create_new < render >();

         if (!prender)
         {

            return;

         }

         prender->m_puserinteraction = this;

         string strText;

         prender->m_strShaderPath = strShaderPath;

         prender->update_shader();

         {

            synchronous_lock synchronouslock(this->synchronization());

            m_maprender[strShaderPath] = prender;

         }

         set_need_layout();

      }

      post_redraw();

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item & useritem, const ::user::e_state & estate)
   {

      ::user::interaction::_001DrawItem(pgraphics, useritem, estate);

   }


   void main_window::switch_shader()
   {

      auto papp = get_app();

      auto strNextShaderPath = papp->get_next_shader_path(m_strCurrentShaderPath);

      if (strNextShaderPath == m_strCurrentShaderPath)
      {

         return;

      }

      m_strCurrentShaderPath = strNextShaderPath;

      update_shader(strNextShaderPath);

   }


} // namespace app_shader



