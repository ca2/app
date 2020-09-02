#include "framework.h"
#include <math.h>
#include "aura/const/id.h"


namespace app_shader
{


   window::window()
   {

      m_iShader = 0;

      value(FONTSEL_IMPACT) = true;

      m_flagNonClient.remove(non_client_background);

      m_flagNonClient.remove(non_client_focus_rect);

      m_colorBackground = 0;

   }


   window::~window()
   {

   }


   ::user::e_translucency window::get_translucency(::user::style* pstyle) const
   {

      return ::user::translucency_present;

   }


   void window::install_message_routing(::channel * psender)
   {

      ::user::main_window::install_message_routing(psender);
      IGUI_MSG_LINK(WM_CREATE,psender,this,&window::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &window::_001OnDestroy);
      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &window::_001OnKeyDown);

   }




   void window::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      auto pitem = get_user_item(::user::element_close_button);

      *pitem = ::user::element_close_icon;

      ModifyStyleEx(0, WS_EX_LAYERED);

      GetTopLevel()->set_prodevian();

      update_shader();

   }


   void window::_001OnDestroy(::message::message * pmessage)
   {

   }


   void window::_001OnKeyDown(::message::message* pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if (pkey->m_ekey == ::user::key_s)
      {

         m_bSaveFrame = true;

      }


   }


   void window::update(::update * pupdate)
   {

      if (pupdate->m_id == id_simple_checkbox || pupdate->m_id == id_no_client_frame)
      {

         set_need_redraw();

      }

      ::user::interaction::update(pupdate);

   }


   bool window::keyboard_focus_is_focusable()
   {

      return true;

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
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

               save_image saveimage;

               saveimage.m_eformat = ::draw2d::format_png;

               string strDate = System.datetime().international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

               Context.save_image("image://app_simple_shader-" + strDate + ".png", pimage, &saveimage);

            });


      }

      m_rendera[m_iShader]->_001OnDraw(pgraphics);

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      m_rendera[m_iShader]->m_rect = rectClient;

      m_rendera[m_iShader]->on_layout(pgraphics);

      ::user::main_window::on_layout(pgraphics);

   }


   bool window::on_click(const ::user::item& item)
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


   void window::update_shader()
   {

      sync_lock sl(mutex());

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


} // namespace app_shader



