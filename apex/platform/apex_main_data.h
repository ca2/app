#pragma once


class CLASS_DECL_APEX apex_main_data :
   virtual public acme_main_data,
   virtual public apex_main_struct,
   virtual public ::object
{
public:


   int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
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


   ::e_status system_construct(int argc, char** argv, char ** envp);
   ::e_status system_construct(int argc, wchar_t** argv, wchar_t ** envp);

   virtual ::e_status on_system_construct();


#ifdef WINDOWS_DESKTOP

   ::e_status system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   ::e_status system_construct(Array < String^ >^ refstra);

#else

   ::e_status system_construct(const char * pszCommandLine, const ::e_display & edisplay = ::e_display_none);
   ::e_status system_construct(os_local * poslocal, const ::e_display & edisplay = ::e_display_none);

#endif

   string get_arg(int i) const;
   string get_env(const char *pszVariableName) const;


   bool is_console_app() const;


};
