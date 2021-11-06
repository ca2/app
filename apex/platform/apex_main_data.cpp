#include "framework.h"
#include "apex/operating_system.h"


//#ifdef ANDROID
//
//#include "acme/node/operating_system/android/_os_local.h"
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


::e_status apex_main_data::system_construct(const ::main & main)
{

   auto estatus = ::main::system_construct(main);

   if (!estatus)
   {

      return estatus;

   }

   m_iPathInstallFolderExeArg = -1;

#ifdef WINDOWS_DESKTOP

   if (!m_hinstanceThis)
   {

      m_hinstanceThis = ::GetModuleHandle(nullptr);

   }

   //m_hPrevInstance = nullptr;

   if (m_nCmdShow == -1000)
   {

      m_nCmdShow = SW_SHOWDEFAULT;

   }

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

   estatus = on_system_construct();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


//::e_status apex_main_data::system_construct(int argc, char** argv, char ** envp)
//{
//
//   auto estatus = acme_main_data::system_construct(argc, argv, envp);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_iPathInstallFolderExeArg = -1;
//
//#ifdef WINDOWS_DESKTOP
//
//   m_hinstance = ::GetModuleHandle(nullptr);
//
//   m_hPrevInstance = nullptr;
//
//   m_nCmdShow = SW_SHOWDEFAULT;
//
//#elif defined(LINUX)
//
//   m_bGtkApp = false;
//
//#endif
//
//   estatus = on_system_construct();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}
//
//
//::e_status apex_main_data::system_construct(int argc, wchar_t** argv, wchar_t ** envp)
//{
//
//   auto estatus = acme_main_data::system_construct(argc, argv, envp);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_iPathInstallFolderExeArg = -1;
//
//#ifdef WINDOWS_DESKTOP
//
//   m_hinstance = ::GetModuleHandle(nullptr);
//
//   m_hPrevInstance = nullptr;
//
//   m_nCmdShow = SW_SHOWDEFAULT;
//
//#elif defined(LINUX)
//
//   m_bGtkApp = false;
//
//#endif
//
//   estatus = on_system_construct();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


e_status apex_main_data::on_system_construct()
{

   return success;

}


#ifdef WINDOWS_DESKTOP


//::e_status apex_main_data::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow)
//{
//
//   auto estatus = acme_main_data::system_construct(pCmdLine);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_hinstance = hinstanceThis;
//
//   m_hPrevInstance = hPrevInstance;
//
//   m_nCmdShow = nCmdShow;
//
//   //__zero(m_mainrunnera);
//
//   estatus = on_system_construct();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//
//}


#elif defined(_UWP)


::e_status apex_main_data::system_construct(const ::string_array & straParam)
{

   //m_poslocal = nullptr;

   auto stra = straParam;

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   //m_pfnNewAuraApplication = nullptr;

   //m_pfnNewAuraLibrary = nullptr;

   //m_poslocal = nullptr;

   m_edisplay = e_display_default;

   //__zero(m_mainrunnera);

   return ::success;

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



