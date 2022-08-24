#include "framework.h"
//#include "aura/update.h"


namespace app_app
{


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

      auto poscontext = m_psystem->m_papexsystem->os_context();

      //::file::path path = "C:\\basis\\operating-system\\tool-windows\\bin\\hstart.exe";

      //poscontext->hidden_run(1_minute, path, "/NOCONSOLE /NOUAC \"C:\\basis\\operating-system\\tool-windows\\headless_monitor\\deviceinstaller64.exe enableidd 1\"");

      poscontext->hidden_start("C:/Windows/system32/cmd.exe", "/c subst S: C:\\store");

      poscontext->hidden_start("C:/Windows/system32/cmd.exe", "/c subst T: C:\\Users\\camilo\\Desktop");

      poscontext->file_open("C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv.exe", "\"C:\\netnode\\operating-system\\operating-system-windows\\_seed\\core_netnodelite.sln\" /run \"basis|x64\"");

      preempt(30_s);

      throw exit_exception();

   }


   void application::term_application()
   {

      ::aura::application::term_application();


   }


   void application::on_request(::create * pcreate)
   {

      throw "not designed to show a graphical user interface";

      __compose_new(m_pmainwindow);

      m_pmainwindow->display(e_display_restored);

      m_pmainwindow->create_main_window();

      m_pmainwindow->set_need_layout();

      m_pmainwindow->set_need_redraw();

      m_pmainwindow->post_redraw();

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

  
} // namespace app_app



