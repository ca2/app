#include "framework.h"
#include <math.h>
#include "acme/const/id.h"
#include "aura/graphics/snippet/close_icon.h"


namespace app_shader
{


   main_window::main_window()
   {

      m_pdragmove.release();

      m_bTransparent = true;

      m_iShader = 0;

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
      MESSAGE_LINK(e_message_destroy, psender, this, &main_window::_001OnDestroy);
      MESSAGE_LINK(e_message_key_down, psender, this, &main_window::_001OnKeyDown);

   }




   void main_window::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      auto pitem = get_user_item(::user::e_element_close_button);

      *pitem = ::user::e_element_close_icon;

      get_top_level()->set_prodevian();

      update_shader(0);

   }


   void main_window::_001OnDestroy(::message::message * pmessage)
   {

   }


   void main_window::_001OnKeyDown(::message::message* pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

      if (pkey->m_ekey == ::user::e_key_s)
      {

         m_bSaveFrame = true;

      }


   }


   void main_window::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      if (psubject->id() == id_simple_checkbox || psubject->id() == id_no_client_frame)
      {

         set_need_redraw();

      }

      ::user::interaction::on_subject(psubject, pcontext);

   }


   bool main_window::keyboard_focus_is_focusable() const
   {

      return true;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = layout().get_client_rect();

      auto & prender = m_rendera.element_at_grow(m_iShader);

      if(::is_set(prender))
      {

         prender->_001OnDraw(pgraphics);

         if (m_bSaveFrame)
         {

            m_bSaveFrame = false;

            auto pimage = create_image(rectangleClient);

            ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

            prender->_001OnDraw(pgraphics);

            fork([this, pimage]()
                 {

                    auto psaveimage = __new(save_image());

                    psaveimage->m_eformat = ::draw2d::format_png;

                    auto psystem = m_psystem->m_paurasystem;

                    auto pdatetime = psystem->m_pdatetime;

                    string strDate = pdatetime->international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

                    auto papplication = get_application();

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

      auto & prender = m_rendera.element_at_grow(m_iShader);

      if(::is_set(prender))
      {

         prender->m_rectangle = rectangleClient;

         prender->on_layout(pgraphics);

      }

      ::user::main_window::on_layout(pgraphics);

   }


   bool main_window::on_click(const ::user::item& item)
   {

      if (::user::interaction::on_click(item))
      {

         return true;

      }

      int iNewShader = m_iShader + 1;

      if (iNewShader > 14)
      {

         iNewShader = 0;

      }

      update_shader(iNewShader);

      m_iShader = iNewShader;

      return true;

   }


   void main_window::update_shader(int iShader)
   {

      start_layout();

      auto prender = __create_new < render >();

      if (!prender)
      {

         return;

      }

      prender->m_pinteraction = this;

      string strText;

      if(iShader == 0)
      {

         prender->m_strShaderPrefix = "default";

      }
      else
      {

         prender->m_strShaderPrefix.Format("%d", iShader);

      }

      prender->update_shader();

      {

         synchronous_lock synchronouslock(mutex());

         m_rendera.set_at_grow(iShader, prender);

      }

      set_layout_ready();

      set_need_layout();

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item* pitem)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_eelement == ::user::e_element_close_icon)
      {

         ::user::draw_close_icon(pgraphics, this, pitem);

      }

   }



} // namespace app_shader



