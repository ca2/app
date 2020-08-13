#include "framework.h"
#include "aura/application.h"
#include "aura/update.h"


namespace simple_shader
{


   application::application() :
      m_echeckSimple(topic(id_simple_checkbox)),
      m_echeckNoClientFrame(topic(id_no_client_frame)),
      m_strSimple(topic(id_simple_text))
   {
      
      auto pproperty1 = find_property(id_simple_checkbox);
      
      bool bCheckOk = false;
      
      if(pproperty1->m_etype == type_enum_check)
      {
         
         auto pproperty = pproperty1;
         
         if(pproperty->m_etype == type_enum_check)
         {
            
            auto & echeck = pproperty->m_echeck;
            
            if(echeck == check_undefined)
            {
               
               bCheckOk = true;
               
            }
            
         }
         
      }
      
      if(!bCheckOk)
      {
       
         message_box("simple_check_box is not ok");
         
      }
      
      m_strAppId = "app-simple/shader";

      m_strAppName = "app-simple/shader";

      m_strBaseSupportId = "ca2_flag";

      m_bLicense = false;

      m_bMultiverseChat = true;

      m_strMainTitle = "Simple Drawing";

   }


   application::~application()
   {

   }




   string application::get_hover_font() const
   {

      return "Helvetica";

   }


   ::estatus application::init_instance()
   {

      set_local_data();

      create_factory <::simple_shader::window >();

      default_toggle_check_handling(id_simple_checkbox);

      default_toggle_check_handling(id_no_client_frame);

      if (!::aura::application::init_instance())
      {

         return false;

      }

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      __compose(m_pwindow, __create_new < window >());

      ::rect rectWindow;

      m_pwindow->_001InitialFramePosition(rectWindow, { 0.05, 0.05, 0.4, 0.4 });

      ::user::create_struct cs(0, nullptr, "app_app", WS_VISIBLE, rectWindow);

      m_pwindow->create_window_ex(cs);

      m_pwindow->display(display_normal);

      m_pwindow->place(rectWindow);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->post_redraw();

   }


   string application::preferred_experience()
   {

      return ::aura::application::preferred_experience();

   }


#ifdef _DEBUG


   int64_t application::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t application::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


#endif


   ::id application::translate_property_id(const ::id & id)
   {

      if(id == "simple_checkbox")
      {

         return id_simple_checkbox;

      }
      else if(id == "simple_text")
      {

         return id_simple_text;

      }

      return id;

   }


   __namespace_application_factory("app/shader");


} // namespace simple_shader



