// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


//#ifdef ANDROID
//
//#include "acme/operating_system/android/_os_local.h"
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


void apex_main_data::system_construct(const ::main * pmain)
{

   //auto estatus = 
   
   ::main::system_construct(pmain);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //m_iPathInstallFolderExeArg = -1;

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

   //estatus = 
   on_system_construct();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


//void apex_main_data::system_construct(int argc, char** argv, char ** envp)
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
//void apex_main_data::system_construct(int argc, wchar_t** argv, wchar_t ** envp)
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


void apex_main_data::on_system_construct()
{

   //return success;

}


#ifdef WINDOWS_DESKTOP


//void apex_main_data::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow)
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
//   //zero(m_mainrunnera);
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


void apex_main_data::system_construct(const ::string_array & straParam)
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

   //zero(m_mainrunnera);

   //return ::success;

}


#else


void apex_main_data::system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display & edisplay)
{

   m_strCommandLine = pszCommandLine;

   //m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = nullptr;

   //zero(m_mainrunnera);

   //auto estatus =
   //
   on_system_construct();

//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;

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


string apex_main_data::get_env(const ::scoped_string & scopedstrVariableName) const
{

   if (m_wenvp)
   {

      wstring wstrPrefix(pszVariableName);

      wstrPrefix += "=";

      for(auto p = m_wenvp; p != nullptr; p++)
      {

         wstring wstr(*p);

         if(wstr.case_insensitive_begins_eat(wstrPrefix))
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

         if(str.case_insensitive_begins_eat(strPrefix))
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



