#include "framework.h"
#include "application.h"
#include "main_window.h"
#include "render.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/filesystem/filesystem/directory_context.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_shader);
IMPLEMENT_APPLICATION_FACTORY(app_shader);


namespace app_shader
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_shader));


   application::application() 
   {

      m_strAppId = "app/shader";

      m_strAppName = "Shader";

      m_strBaseSupportId = "app/shader";

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use innate_ui icon?

      m_bWriteText = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      //set_local_data();

      //factory()->add_factory_item <::app_shader::main_window >();

      ::aura::application::init_instance();

      //if (!)
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

      m_pmainwindow = __create_new < ::app_shader::main_window > ();

      m_pmainwindow->display(e_display_normal);

      m_pmainwindow->create_main_window(prequest);

//      m_pmainwindow->set_need_layout();
//
//      m_pmainwindow->set_need_redraw();
//
//      m_pmainwindow->post_redraw();

   }



#ifdef _DEBUG


   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif


   string application::get_next_shader_path(const string& strPath)
   {

      ::file::listing listing;

      get_shader_listing(listing);

      auto next = listing.get_next(strPath);

      return ::transfer(next);

   }


   void application::get_shader_listing(::file::listing & listing)
   {

      auto pcontext = m_papplication;

      bool bUseOwnResources = is_sandboxed();

      for (;;)
      {

         if (bUseOwnResources)
         {

            listing.set_pattern_file_listing("matter://shader/simple shader/", { "*.frag" });

         }
         else
         {

            listing.set_pattern_file_listing("dropbox://shader/simple shader/", { "*.frag" });

         }

         pcontext->directory()->enumerate(listing);

         if (listing.has_elements() || bUseOwnResources)
         {

            break;

         }

         bUseOwnResources = true;

      }

      listing.order();

   }


} // namespace app_shader



