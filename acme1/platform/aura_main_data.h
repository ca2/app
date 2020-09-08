#pragma once


class CLASS_DECL_ACME ace_main_data :
   public ace_main_struct,
   virtual public ::generic
{
public:


   int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
   os_local *                       m_poslocal;
   int                              m_argc;
   char **                          m_argv;
   wchar_t **                       m_wargv;
   int                              m_iExitCode;
   string                           m_strCommandLine;
   string                           m_strStandalone;
   LPFN_MAIN_RUNNER                 m_mainrunnera[64];
   ::edisplay                       m_edisplay;
   ::eactivation                    m_eactivation;
   string                           m_strAppId;
   ::file::path                     m_pathCacheDir;

#ifdef WINDOWS

   HINSTANCE                        m_hinstance;
   HINSTANCE                        m_hPrevInstance;

#endif


   ace_main_data();
   virtual ~ace_main_data();


   void set_main_struct(const ace_main_struct  & mainstruct);


   void system_construct(int argc, char** argv);
   void system_construct(int argc, wchar_t** argv);

   void system_construct(const char* pszCommandLine, const ::edisplay& edisplay = ::display_none);
   void system_construct(os_local* poslocal, const ::edisplay& edisplay = ::display_none);

#ifdef WINDOWS_DESKTOP

   void system_construct(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   void system_construct(Array < String^ >^ refstra);

#endif

   string get_arg(int i);

   bool is_console_app() const;


};
