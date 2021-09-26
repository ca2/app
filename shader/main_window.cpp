#include "framework.h"
#include <math.h>
#include "acme/constant/id.h"
#include "aura/graphics/user/close_icon.h"


namespace app_shader
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_flagNonClient.erase(non_client_background);

      m_flagNonClient.erase(non_client_focus_rect);

      m_colorBackground = 0;

      m_bClickDefaultMouseHandling = true;

   }


   main_window::~main_window()
   {

   }


   ::user::enum_translucency main_window::get_translucency(::user::style* pstyle) const
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

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      {

         auto pitem = get_user_item(::e_element_close_button);

         *pitem = ::e_element_close_icon;

      }

      {

         add_user_item({ ::e_element_switch_button, ::e_subject_close_app });

         auto pitem = get_user_item(::e_element_switch_button);

         *pitem = ::e_element_switch_button;

      }

      get_top_level()->set_prodevian();

      update_shader("");

   }




   void main_window::on_message_destroy(::message::message * pmessage)
   {

   }


   void main_window::on_message_key_down(::message::message* pmessage)
   {

      auto pkey = pmessage->m_pkey;

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


   void main_window::handle(::subject * psubject, ::context * pcontext)
   {

      if (psubject->id() == id_simple_checkbox || psubject->id() == id_no_client_frame)
      {

         set_need_redraw();

      }

      ::user::interaction::handle(psubject, pcontext);

   }


   bool main_window::keyboard_focus_is_focusable() const
   {

      return true;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = layout().get_client_rect();

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if(::is_set(prender))
      {

         prender->_001OnDraw(pgraphics);

         if (m_bSaveFrame)
         {

            m_bSaveFrame = false;

            auto pimage = m_pcontext->context_image()->create_image(rectangleClient);

            ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

            prender->_001OnDraw(pgraphics);

            fork([this, pimage]()
                 {

                    auto psaveimage = __new(save_image());

                    psaveimage->m_eformat = ::draw2d::format_png;

                    auto psystem = m_psystem->m_paurasystem;

                    auto pdatetime = psystem->m_pdatetime;

                    string strDate = pdatetime->international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

                    //auto papplication = get_application();

                    auto pcontext = m_pcontext;

                    auto pcontextimage = pcontext->context_image();

                    pcontextimage->save_image("image://app_simple_shader-" + strDate + ".png", pimage, psaveimage);

                 });

         }
      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      auto & prender = m_maprender[m_strCurrentShaderPath];

      if(::is_set(prender))
      {

         prender->m_rectangle = rectangleClient;

         prender->on_layout(pgraphics);

      }

      ::user::main_window::on_layout(pgraphics);

   }


   bool main_window::on_click(const ::item& item)
   {

      if (::user::interaction::on_click(item))
      {

         return true;

      }

      return true;

   }


   void main_window::update_shader(const ::string & strShaderPath)
   {

      {

         ::user::lock_sketch_to_design lockSketchToDesign(this);

         auto prender = __create_new < render >();

         if (!prender)
         {

            return;

         }

         prender->m_pinteraction = this;

         string strText;

         prender->m_strShaderPath = strShaderPath;

         prender->update_shader();

         {

            synchronous_lock synchronouslock(mutex());

            m_maprender[strShaderPath] = prender;

         }

         set_need_layout();

      }

      post_redraw();

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem)
   {

      ::user::interaction::_001DrawItem(pgraphics, pitem);

   }


   void main_window::switch_shader()
   {

      auto papplication = get_application();

      auto strNextShaderPath = papplication->get_next_shader_path(m_strCurrentShaderPath);

      if (strNextShaderPath == m_strCurrentShaderPath)
      {

         return;

      }

      m_strCurrentShaderPath = strNextShaderPath;

      update_shader(strNextShaderPath);

   }


} // namespace app_shader



