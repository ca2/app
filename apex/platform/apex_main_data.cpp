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


void apex_main_data::system_construct(int argc, char** argv)
{

   m_argc = argc;

   m_argv = argv;

   m_iPathInstallFolderExeArg = -1;


//#
//
//   g_poslocal = nullptr;
//
   m_wargv = nullptr;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   //windows_register_class((HINSTANCE) m_hinstance);

   m_hPrevInstance = nullptr;

   m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

}


void apex_main_data::system_construct(int argc, wchar_t** argv)
{

   m_argc = argc;

   m_argv = nullptr;

   m_iPathInstallFolderExeArg = -1;

   //m_poslocal = nullptr;

   m_wargv = argv;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   //windows_register_class((HINSTANCE) m_hinstance);

   m_hPrevInstance = nullptr;

   m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

}


void apex_main_data::system_construct(const char* pszCommandLine, const ::e_display& edisplay)
{

   m_strCommandLine = pszCommandLine;

   m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = nullptr;

   //__zero(m_mainrunnera);

}


void apex_main_data::system_construct(os_local* poslocal, const ::e_display& edisplay)
{

#ifdef ANDROID

   m_strCommandLine = "app.exe : app=" + poslocal->m_strApplicationIdentifier + " " + poslocal->m_strCommandLineParameters;

#endif

   m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = poslocal;

   //__zero(m_mainrunnera);

}


#ifdef WINDOWS_DESKTOP


void apex_main_data::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow)
{

   m_hinstance = hinstanceThis;

   //windows_register_class((HINSTANCE) m_hinstance);

   //MyRegisterClass((HINSTANCE) m_hinstance);

   m_hPrevInstance = hPrevInstance;

   m_strCommandLine = pCmdLine;

   m_edisplay = windows_show_window_to_edisplay(nCmdShow, m_eactivation);

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   //__zero(m_mainrunnera);

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


#endif


void apex_main_data::set_main_struct(const apex_main_struct & mainstruct)
{

   *((::apex_main_struct*)(this)) = mainstruct;

}


string apex_main_data::get_arg(int i)
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


bool apex_main_data::is_console_app() const
{

   return m_bConsole;

}



