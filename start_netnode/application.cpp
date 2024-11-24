#include "framework.h"
//#include "aura/update.h"
IMPLEMENT_APPLICATION(app_app);

namespace app_app
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application()
   {
      
      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bLicense = false;

      m_bImaging = false;

      m_bWriteText = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      ::aura::application::init_instance();

      auto poscontext = system()->os_context();

      //::file::path path = "C:\\basis\\operating_system\\tool-windows\\bin\\hstart.exe";

      //poscontext->hidden_run(1_minute, path, "/NOCONSOLE /NOUAC \"C:\\basis\\operating_system\\tool-windows\\headless_monitor\\deviceinstaller64.exe enableidd 1\"");

      poscontext->hidden_start("C:/Windows/system32/cmd.exe", "/c subst S: C:\\store");

      poscontext->hidden_start("C:/Windows/system32/cmd.exe", "/c subst T: C:\\Users\\camilo\\Desktop");

      poscontext->file_open("C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe", "\"C:\\netnode\\operating_system\\operating_system-windows\\_seed\\core_netnodelite.sln\" /run \"basis|x64\"");

      preempt(30_s);

      throw exit_exception();

   }


   void application::term_application()
   {

      ::aura::application::term_application();


   }


   void application::on_request(::request * prequest)
   {

      throw "not designed to show a graphical user interface";

      __construct_new(m_pmainwindow);

      m_pmainwindow->display(e_display_normal);

      m_pmainwindow->create_main_window();

      m_pmainwindow->set_need_layout();

      m_pmainwindow->set_need_redraw();

      m_pmainwindow->post_redraw();

   }


#ifdef _DEBUG


   huge_integer application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   huge_integer application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif

  
} // namespace app_app



