#include "framework.h"
#include <math.h>
#include "aura/const/id.h"


namespace simple_shader
{


   window::window()
   {

      m_iView = -1;

      value(FONTSEL_IMPACT) = true;

      m_flagNonClient.remove(non_client_background);

      m_flagNonClient.remove(non_client_focus_rect);

   }


   window::~window()
   {

   }


   void window::assert_valid() const
   {

      user::interaction::assert_valid();

   }


   void window::dump(dump_context & dumpcontext) const
   {

      user::interaction::dump(dumpcontext);

   }


#ifdef _DEBUG


   int64_t window::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::interaction::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t window::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return  ::user::interaction::dec_ref(OBJ_REF_DBG_ARGS);

   }


#endif


   void window::install_message_routing(::channel * psender)
   {

      ::user::interaction::install_simple_ui_default_mouse_handling(psender);
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

      GetTopLevelFrame()->set_prodevian();

      auto predraw = [this]()
         {

            set_need_redraw();

            post_redraw();

         };

      Application.m_mapRunnable[id_simple_checkbox] += predraw;

      Application.m_mapRunnable[id_no_client_frame] += predraw;

      auto estatus = __construct_new(m_prender);

      if(!estatus)
      {

         pcreate->set_fail();

         return;

      }

      m_prender->initialize_application_consumer();

      m_prender->m_pinteraction = this;

      string strText;


      m_prender->update_shader();


      {

         ::id id = id_simple_text;

         auto pproperty = Application.fetch_property(id);

         var var;

         if (Application.data_get(id, var))
         {

            pproperty->convert(var);

         }

         auto idRunnable = Application.translate_property_id(id);

         Application.m_mapRunnable[idRunnable] += [this, id]()
         {

            auto pproperty = fetch_property(id);

            m_prender->defer_load_fragment(pproperty->get_string());

         };

      }


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

      if (m_bSaveFrame)
      {

         m_bSaveFrame = false;

         auto rectClient = get_client_rect();

         auto pimage = create_image(rectClient);

         ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

         m_prender->_001OnDraw(pgraphics);

         fork([this, pimage]()
            {

               save_image saveimage;

               saveimage.m_eformat = ::draw2d::format_png;

               string strDate = System.datetime().international().get_gmt_date_time(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

               Context.save_image("image://app_simple_shader-" + strDate + ".png", pimage, &saveimage);

            });


      }

      m_prender->_001OnDraw(pgraphics);

   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      m_prender->m_rect = rectClient;

      m_prender->on_layout(pgraphics);

   }


} // namespace simple_shader



