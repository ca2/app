#include "framework.h"
#include "apex/operating_system.h"


//#ifdef ANDROID
//
//#include "acme/os/android/_os_local.h"
//
//#endif


#ifdef ANDROID


#endif


//#if defined(WINDOWS_DESKTOP)

//CLASS_DECL_ACME bool windows_register_class(HINSTANCE hinstance);

//CLASS_DECL_ACME ATOM MyRegisterClass(HINSTANCE hInstance);

//#endif


apex_main_data::apex_main_data()
{


}


apex_main_data::~apex_main_data()
{

}


::e_status apex_main_data::system_construct(int argc, char** argv, char ** envp)
{

   m_argc = argc;

   m_argv = argv;

   m_envp = envp;

   m_iPathInstallFolderExeArg = -1;


//#
//
//   g_poslocal = nullptr;
//
   m_wargv = nullptr;

   m_wenvp = nullptr;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   //windows_register_class((HINSTANCE) m_hinstance);

   m_hPrevInstance = nullptr;

   m_nCmdShow = SW_SHOWDEFAULT;

   //m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

   auto estatus = on_system_construct();

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status apex_main_data::system_construct(int argc, wchar_t** argv, wchar_t ** envp)
{

   m_argc = argc;

   m_argv = nullptr;

   m_envp = nullptr;

   m_iPathInstallFolderExeArg = -1;

   //m_poslocal = nullptr;

   m_wargv = argv;

   m_wenvp = envp;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   //windows_register_class((HINSTANCE) m_hinstance);

   m_hPrevInstance = nullptr;

   //m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

   m_nCmdShow = SW_SHOWDEFAULT;

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

   auto estatus = on_system_construct();

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


e_status apex_main_data::on_system_construct()
{

   return success;

}


#ifdef WINDOWS_DESKTOP


::e_status apex_main_data::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow)
{

   m_hinstance = hinstanceThis;

   //windows_register_class((HINSTANCE) m_hinstance);

   //MyRegisterClass((HINSTANCE) m_hinstance);

   m_hPrevInstance = hPrevInstance;

   m_strCommandLine = pCmdLine;

   //m_edisplay = windows_show_window_to_edisplay(nCmdShow, m_eactivation);

   m_nCmdShow = nCmdShow;

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   m_envp = *__p__environ();

   m_wenvp = *__p__wenviron();

   //__zero(m_mainrunnera);

   auto estatus = on_system_construct();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;


}


#elif defined(_UWP)


void apex_main_data::system_construct(Array < String^ >^ refstra)
{

   //m_poslocal = nullptr;

   string_array stra(refstra);

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   //m_pfnNewAuraApplication = nullptr;

   //m_pfnNewAuraLibrary = nullptr;

   //m_poslocal = nullptr;

   m_edisplay = e_display_default;

   __zero(m_mainrunnera);

}


#else


::e_status apex_main_data::system_construct(const char * pszCommandLine, const ::e_display & edisplay)
{

   m_strCommandLine = pszCommandLine;

   //m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = nullptr;

   //__zero(m_mainrunnera);

   auto estatus = on_system_construct();

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status apex_main_data::system_construct(os_local * poslocal, const ::e_display & edisplay)
{

#ifdef ANDROID

   m_strCommandLine = "app.exe : app=" + poslocal->m_strApplicationIdentifier + " " + poslocal->m_strCommandLineParameters;

#endif

   m_edisplay = edisplay;

   //m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = poslocal;

   //__zero(m_mainrunnera);

   auto estatus = on_system_construct();

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


#endif


void apex_main_data::set_main_struct(const apex_main_struct & mainstruct)
{

   *((::apex_main_struct*)(this)) = mainstruct;

}


string apex_main_data::get_arg(int i) const
{

   if (m_wargv)
   {

      return string(m_wargv[i]);

   }
   else if (m_argv)
   {

      return string(m_argv[i]);

   }

   return "";


}


string apex_main_data::get_env(const char * pszVariableName) const
{

   if (m_wenvp)
   {

      wstring wstrPrefix(pszVariableName);

      wstrPrefix += "=";

      for(auto p = m_wenvp; p != nullptr; p++)
      {

         wstring wstr(*p);

         if(wstr.begins_eat_ci(wstrPrefix))
         {

            return wstr;

         }

      }

      return "";

   }
   else if (m_envp)
   {

      string strPrefix(pszVariableName);

      strPrefix += "=";

      for(auto p = m_envp; p != nullptr; p++)
      {

         string str(*p);

         if(str.begins_eat_ci(strPrefix))
         {

            return str;

         }

      }

      return "";

   }

   return "";

}


bool apex_main_data::is_console_app() const
{

   return m_bConsole;

}



