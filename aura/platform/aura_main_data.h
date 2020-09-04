#pragma once


class CLASS_DECL_AURA aura_main_data :
   public aura_main_struct,
   virtual public ::object
{
public:


   int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
   os_local *                       m_poslocal;
   bool                             m_bVerbose;
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
   bool                             m_bAvoidFirstResponder;


#ifdef WINDOWS

   HINSTANCE                        m_hinstance;
   HINSTANCE                        m_hPrevInstance;

#endif


   aura_main_data();
   virtual ~aura_main_data();


   void set_main_struct(const aura_main_struct  & mainstruct);


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
