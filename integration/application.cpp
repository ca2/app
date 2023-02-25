#include "framework.h"
#include "application.h"
#include "frame.h"
#include "main_frame.h"
#include "document.h"
#include "menu.h"
//#include "openssl.h"
//#include "ffmpeg.h"
#include "impact.h"
#include "tab_impact.h"
#include "acme/handler/request.h"
#include "aura/user/user/button.h"
#include "base/user/user/show.h"
#include "base/user/user/single_document_template.h"


namespace app_integration
{


   application::application()
   {

      m_ptemplateSimpleDrawingMain = nullptr;

      m_ptabimpact = nullptr;

      m_strAppId = "app/integration";

      m_strDatabaseAppId = "app/integration";

      m_strBaseSupportId = "ca2_flag";

      m_strAppName = "Integration";

      m_bLicense = false;

      m_bNetworking = false;

      m_bMultiverseChat = true;

   }


   application::~application()
   {

   }


   ::type application::get_pane_impact_type() const
   {

      return __type(tab_impact);

   }


   void application::init_instance()
   {

      create_application_properties();

      m_textAppTitle = __text("text://app/integration/app_integration/Integration");

      auto pproperty1 = application_properties().find("simple_checkbox");

      bool bCheckOk = false;

      if (pproperty1->m_etype == e_type_enum_check)
      {

         auto pproperty = pproperty1;

         if (pproperty->m_etype == e_type_enum_check)
         {

            auto & echeck = pproperty->m_echeck;

            if (echeck == e_check_undefined)
            {

               bCheckOk = true;

            }

         }

      }

      if (!bCheckOk)
      {

         output_debug_string("ERROR: simple_check_box is not ok");

      }

      application_properties().m_strMainTitle = "Integration";

      //set_local_data();

      factory()->add_factory_item <::user::button_impact >();
      factory()->add_factory_item <::app_integration::document >();
      factory()->add_factory_item <::app_integration::frame >();
      factory()->add_factory_item <::app_integration::main_frame >();
      factory()->add_factory_item <::app_integration::impact >();
      factory()->add_factory_item <::app_integration::tab_impact >();
      factory()->add_factory_item <::app_integration::menu >();
      //factory()->add_factory_item <::app_integration::openssl >();
      //factory()->add_factory_item <::app_integration::ffmpeg >();

      default_toggle_check_handling("simple_checkbox");

      default_toggle_check_handling("no_client_frame");

      ::base::application::init_instance();

      auto pdoctemplate = __new(::user::single_document_template(
                               "main",
                               __type(document),
                               __type(main_frame),
                               get_pane_impact_type()));

      m_ptemplateSimpleDrawingMain = pdoctemplate;

      add_document_template(pdoctemplate);


      pdoctemplate = __new(::user::single_document_template(
         "openssl",
         __type(document),
         __type(main_frame),
         __type(impact)));

      m_ptemplateOpenSSL = pdoctemplate;

      add_document_template(pdoctemplate);

      pdoctemplate = __new(::user::single_document_template(
         "ffmpeg",
         __type(document),
         __type(main_frame),
         __type(impact)));

      m_ptemplateFFMPEG = pdoctemplate;

      add_document_template(pdoctemplate);

      default_data_save_handling("simple_checkbox");

      default_data_save_handling("no_client_frame");

      default_data_save_handling("simple_text");

      //return true;

   }


   void application::term_application()
   {

      ::base::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateSimpleDrawingMain->get_document_count() == 0)
      {

         if(prequest->m_bMakeVisible)
         {

            INFORMATION("pcreate->m_bMakeVisible");

         }
         else
         {

            INFORMATION("NOT pcreate->m_bMakeVisible");

         }

         m_ptemplateSimpleDrawingMain->request(prequest);

      }

      if (is_true("wfi_maximize"))
      {

         prequest->payload("document").cast < document >()->get_typed_impact < ::user::tab_impact >()->top_level_frame()->design_window_maximize();

      }

      output_debug_string("\nfinished simple_drawing::on_request");

   }


   string application::preferred_experience()
   {

      return ::aura::application::preferred_experience();

   }


#ifdef _DEBUG


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   //::pointer<impact> application::create_simple_drawing_impact(::user::impact* pimpactParent, ::user::impact_data * pimpactdata)
   //{

   //   return pimpactParent->create_impact < impact >(pimpactdata);

   //}


   ::atom application::translate_property_id(const ::atom & atom)
   {
      
      return atom;

//      if(atom == "simple_checkbox")
//      {
//
//         return id_simple_checkbox;
//
//      }
//      else if(atom == "simple_text")
//      {
//
//         return id_simple_text;
//
//      }
//      else if (atom == "no_client_frame")
//      {
//
//         return id_no_client_frame;
//
//      }
//
//      return atom;

   }



} // namespace simple_drawing



