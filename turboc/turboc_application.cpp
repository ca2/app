#include "framework.h"


namespace turboc
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject) :
      m_mutexAiFont(this)
   {

      m_strAppName            = "turboc";
      m_strBaseSupportId      = "ca2_flag";
      m_bLicense              = false;

      m_etype                 = type_normal;

      m_strTurboC             = "Turbo C!!";
      m_strAlternateTurboC    = "TC!!";

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_bMultiverseChat = true;

      m_pfnmainMain = NULL;

      m_pmain = NULL;

   }

   application::~application()
   {

   }


   bool application::initialize_application()
   {

      m_pcontext = new context(this);


      add_factory_item <::turboc::document >();
      add_factory_item <::turboc::frame >();
      add_factory_item <::turboc::edit_impact >();
      add_factory_item <::turboc::toggle_impact >();
      add_factory_item <::turboc::top_impact >();
      add_factory_item <::turboc::lite_impact >();
      add_factory_item <::turboc::full_impact >();
      add_factory_item <::turboc::impact >();
      add_factory_item <::turboc::main_impact >();
      add_factory_item <::turboc::switcher_impact >();
      add_factory_item <::turboc::pane_impact >();

      if(!::console::application::initialize_application())
         return false;

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::pane_impact));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::main_impact));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseImpact = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::switcher_impact));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseSwitcher = pDocTemplate;

      return true;

   }

   bool application::start_main()
   {

      if(m_pfnmainMain == NULL)
      {

         message_box(NULL,"There is no turboc main function setup");

         return false;

      }

      if(!start_main(m_pfnmainMain))
      {

         return false;

      }

      return true;

   }


   bool application::start_main(PFN_MAIN pfnMain)
   {

      if(m_pmain != NULL)
      {

         return false;

      }

      m_pmain = new ::turboc::main(this);

      m_pmain->m_pfnMain = pfnMain;

      m_pmain->begin();


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

      if(pcreate->m_payloadFile.has_char())
      {

         m_ptemplateHelloMultiverseImpact->do_request(pcreate);

      }

      //pcreate->payload("document").cast < document >()->get_type_impact < pane_impact >()->get_parent_frame()->display(e_display_restore);

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

      application * pimpact = (application *)pparam;

      pimpact->m_iErrorAiFont = -1;

      //pimpact->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pimpact->get_app()).ftlibrary(),Sess(pimpact->get_app()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pimpact->m_faceAi);

      return pimpact->m_iErrorAiFont;

   }


} // namespace turboc
















