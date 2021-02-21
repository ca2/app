#pragma once


class CLASS_DECL_APEX apex_main_data :
   public apex_main_struct,
   virtual public ::object
{
public:


   int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
   int                              m_argc;
   char **                          m_argv;
   wchar_t **                       m_wargv;
   int                              m_iExitCode;
   string                           m_strCommandLine;
   string                           m_strStandalone;
   //LPFN_MAIN_RUNNER                 m_mainrunnera[64];
   ::e_display                      m_edisplay;
   ::e_activation                   m_eactivation;
   string                           m_strAppId;
   ::file::path                     m_pathCacheDirectory;

#ifdef WINDOWS

   hinstance                        m_hinstance;
   hinstance                        m_hPrevInstance;
   int                              m_nCmdShow;

#endif


   apex_main_data();
   virtual ~apex_main_data();


   void set_main_struct(const apex_main_struct  & mainstruct);


   ::e_status system_construct(int argc, char** argv);
   ::e_status system_construct(int argc, wchar_t** argv);

   virtual ::e_status on_system_construct();


#ifdef WINDOWS_DESKTOP

   ::e_status system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   ::e_status system_construct(Array < String^ >^ refstra);

#else

   ::e_status system_construct(const char * pszCommandLine, const ::e_display & edisplay = ::e_display_none);
   ::e_status system_construct(os_local * poslocal, const ::e_display & edisplay = ::e_display_none);

#endif

   string get_arg(int i);

   bool is_console_app() const;


};
