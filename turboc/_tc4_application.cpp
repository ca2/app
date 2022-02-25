#include "framework.h"


namespace tc4
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject):
      m_mutexAiFont(this)
   {

      m_strAppName            = "tc4";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strHelloMultiverse             = "Hello Multiverse!!";
      m_strAlternateHelloMultiverse    = "Hello!!";

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_bMultiverseChat = true;



   }


   application::~application()
   {
   }


   bool application::initialize_application()
   {

      add_factory_item <::tc4::document >();
      add_factory_item <::tc4::frame >();
      add_factory_item <::tc4::edit_view >();
      add_factory_item <::tc4::toggle_view >();
      add_factory_item <::tc4::top_view >();
      add_factory_item <::tc4::lite_view >();
      add_factory_item <::tc4::full_view >();
      add_factory_item <::tc4::impact >();
      add_factory_item <::tc4::main_impact >();
      add_factory_item <::tc4::switcher_view >();
      add_factory_item <::tc4::pane_view >();

      if(!::turboc::application::initialize_application())
         return false;

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::tc4::document),
      __type(::tc4::frame),       // top level SDI frame::user::interaction_impl
      __type(::tc4::pane_view));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::tc4::document),
      __type(::tc4::frame),       // top level SDI frame::user::interaction_impl
      __type(::tc4::main_impact));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::tc4::document),
      __type(::tc4::frame),       // top level SDI frame::user::interaction_impl
      __type(::tc4::switcher_view));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;

      return true;
   }

   i32 application::exit_application()
   {

      return ::aura::application::exit_application();
   }

   void application::on_request(::create * pcreate)
   {

      /*

      {
         atom lowvalue;
         {
            string str = "ABC";
            lowvalue = str.lower();
         }
      }

      property_set set;

      set["c"] = 0;
      set["ABC"] = 0;
      set["abc"] = 0;
      set["ebc"] = 0;

      ::MessageBox(NULL,"stop oh yes!!","stop oh yes!!",e_message_box_icon_information);

      */

      //pcreate->m_bMakeVisible = false;

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->do_request(pcreate);

      }

      if(pcreate->m_pcommandline->m_payloadFile.has_char())
      {

         m_ptemplateHelloMultiverseView->do_request(pcreate);

      }

      //pcreate->m_pcommandline->payload("document").cast < document >()->get_type_impact < pane_view >()->get_parent_frame()->display(e_display_restore);

   }



   void application::load_ai_font()
   {

      if(m_bLoadAiFont)
         return ;

      m_bLoadAiFont = true;

      m_iErrorAiFont = -1;

      __begin_thread(get_app(),&thread_proc_load_ai_font,this,::e_priority_normal,0,0,NULL);

   }


   ::u32 application::thread_proc_load_ai_font(void * pparam)
   {

      application * pview = (application *)pparam;

      pview->m_iErrorAiFont = -1;

      //pview->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pview->get_app()).ftlibrary(),Sess(pview->get_app()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pview->m_faceAi);

      return pview->m_iErrorAiFont;

   }


} // namespace tc4




extern "C"
::acme::library * get_new_library(::object * pobject)
{

   return new ::apex::single_application_library < ::tc4::application > (pobject, "app-core");

}



