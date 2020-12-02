#include "framework.h"
#include "aura/os/android/_os_local.h"


#if defined(WINDOWS_DESKTOP)

bool windows_register_class(HINSTANCE hinstance);

ATOM MyRegisterClass(HINSTANCE hInstance);

#endif


aura_main_data::aura_main_data()
{

   m_bVerbose = false;
   m_etracelevel = trace_level_error;

}


aura_main_data::~aura_main_data()
{

}


void aura_main_data::system_construct(int argc, char** argv)
{

   m_argc = argc;

   m_argv = argv;

   m_iPathInstallFolderExeArg = -1;

   m_poslocal = nullptr;

   m_wargv = nullptr;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   windows_register_class(m_hinstance);

   m_hPrevInstance = nullptr;

   m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

}


void aura_main_data::system_construct(int argc, wchar_t** argv)
{

   m_argc = argc;

   m_argv = nullptr;

   m_iPathInstallFolderExeArg = -1;

   m_poslocal = nullptr;

   m_wargv = argv;

#ifdef WINDOWS_DESKTOP

   m_hinstance = ::GetModuleHandle(nullptr);

   windows_register_class(m_hinstance);

   m_hPrevInstance = nullptr;

   m_edisplay = windows_show_window_to_edisplay(SW_SHOWDEFAULT, m_eactivation);

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

}


void aura_main_data::system_construct(const char* pszCommandLine, const ::edisplay& edisplay)
{

   m_strCommandLine = pszCommandLine;

   m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   m_poslocal = nullptr;

   xxf_zero(m_mainrunnera);

}

void aura_main_data::system_construct(os_local* poslocal, const ::edisplay& edisplay)
{

   m_strCommandLine = poslocal->m_strCommandLine;

   m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   m_poslocal = poslocal;

   xxf_zero(m_mainrunnera);

}


#ifdef WINDOWS_DESKTOP


void aura_main_data::system_construct(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, i32 nCmdShow)
{

   m_hinstance = hinstance;

   windows_register_class(m_hinstance);

   MyRegisterClass(m_hinstance);

   m_hPrevInstance = hPrevInstance;

   m_strCommandLine = pCmdLine;

   m_edisplay = windows_show_window_to_edisplay(nCmdShow, m_eactivation);

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   m_poslocal = nullptr;

   xxf_zero(m_mainrunnera);

}


#elif defined(_UWP)


void aura_main_data::system_construct(Array < String^ >^ refstra)
{

   m_poslocal = nullptr;

   string_array stra(refstra);

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   //m_pfnNewAuraApplication = nullptr;

   //m_pfnNewAuraLibrary = nullptr;

   m_poslocal = nullptr;

   m_edisplay = e_display_default;

   xxf_zero(m_mainrunnera);

}


#endif

CLASS_DECL_AURA void set_global_trace_level(e_trace_level etracelevel);


void aura_main_data::set_main_struct(const aura_main_struct & mainstruct)
{

   *((::aura_main_struct*)(this)) = mainstruct;

   set_global_trace_level(m_etracelevel);

}


string aura_main_data::get_arg(int i)
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


bool aura_main_data::is_console_app() const
{

   return m_bConsole;

}



