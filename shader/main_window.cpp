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

      payload(FONTSEL_IMPACT) = true;

      m_flagNonClient.remove(non_client_background);

      m_flagNonClient.remove(non_client_focus_rect);

      m_colorBackground = 0;

      //m_bSimpleUIDefaultMouseHandling = true;

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

      update_shader();

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

      auto rectClient = layout().get_client_rect();

      if (m_bSaveFrame)
      {

         auto pimage = create_image(rectClient);

         m_bSaveFrame = false;

         ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

         m_rendera[m_iShader]->_001OnDraw(pgraphics);

         fork([this, pimage]()
            {

               auto psaveimage = __new(save_image(this));

               psaveimage->m_eformat = ::draw2d::format_png;

               auto psystem = get_system();

               string strDate = psystem->datetime().international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

               auto papplication = get_application();

               papplication->image().save_image("image://app_simple_shader-" + strDate + ".png", pimage, psaveimage);

            });


      }

      m_rendera[m_iShader]->_001OnDraw(pgraphics);

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      m_rendera[m_iShader]->m_rectangle = rectClient;

      m_rendera[m_iShader]->on_layout(pgraphics);

      ::user::main_window::on_layout(pgraphics);

   }


   bool main_window::on_click(const ::user::item& item)
   {

      if (::user::interaction::on_click(item))
      {

         return true;

      }

      m_iShader++;

      if (m_iShader > 14)
      {

         m_iShader = 1;

      }

      update_shader();

      return true;

   }


   void main_window::update_shader()
   {

      synchronization_lock synchronizationlock(mutex());

      start_layout();

      if (m_rendera.get_count() <= m_iShader)
      {

         m_rendera.set_size(m_iShader + 1);

      }

      auto estatus = __construct_new(m_rendera[m_iShader]);

      if (!estatus)
      {

         return;

      }

      m_rendera[m_iShader]->initialize_application_consumer();

      m_rendera[m_iShader]->m_pinteraction = this;

      string strText;

      m_rendera[m_iShader]->m_strShaderPrefix.Format("%d", m_iShader + 1);

      m_rendera[m_iShader]->update_shader();

      //string str;

      //str.Format("%d", m_iShader + 1);

      //m_rendera[m_iShader]->defer_load_fragment(str);

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



