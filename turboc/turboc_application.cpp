#include "framework.h"


namespace turboc
{


   application::application(::layered * pobjectContext) :
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


      create_factory <::turboc::document >();
      create_factory <::turboc::frame >();
      create_factory <::turboc::edit_view >();
      create_factory <::turboc::toggle_view >();
      create_factory <::turboc::top_view >();
      create_factory <::turboc::lite_view >();
      create_factory <::turboc::full_view >();
      create_factory <::turboc::view >();
      create_factory <::turboc::main_view >();
      create_factory <::turboc::switcher_view >();
      create_factory <::turboc::pane_view >();

      if(!::console::application::initialize_application())
         return false;

      ::user::single_document_template* pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::pane_view));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseMain = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::main_view));
      add_document_template(pDocTemplate);
      m_ptemplateHelloMultiverseView = pDocTemplate;
      pDocTemplate = new ::user::single_document_template(
      this,
      "main",
      __type(::turboc::document),
      __type(::turboc::frame),       // top level SDI frame::user::interaction_impl
      __type(::turboc::switcher_view));
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
      id lowvalue;
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

      ::MessageBox(NULL,"stop oh yes!!","stop oh yes!!",MB_ICONINFORMATION);

      */

      //pcreate->m_bMakeVisible = false;

      if(m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         m_ptemplateHelloMultiverseMain->do_request(pcreate);

      }

      if(pcreate->m_pcommandline->m_varFile.has_char())
      {

         m_ptemplateHelloMultiverseView->do_request(pcreate);

      }

      //pcreate->m_pcommandline->m_varQuery["document"].cast < document >()->get_typed_view < pane_view >()->GetParentFrame()->display(display_restore);

   }



   void application::load_ai_font()
   {

      if(m_bLoadAiFont)
         return ;

      m_bLoadAiFont = true;

      m_iErrorAiFont = -1;

      __begin_thread(get_context_application(),&thread_proc_load_ai_font,this,::priority_normal,0,0,NULL);

   }


   ::u32 application::thread_proc_load_ai_font(void * pparam)
   {

      application * pview = (application *)pparam;

      pview->m_iErrorAiFont = -1;

      //pview->m_iErrorAiFont = FT_New_Face((FT_Library)Sys(pview->get_context_application()).ftlibrary(),Sess(pview->get_context_application()).dir().matter_file("font/truetype/arialuni.ttf"),0,(FT_Face *)&pview->m_faceAi);

      return pview->m_iErrorAiFont;

   }


} // namespace turboc
















