// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex_main_struct.h"


class CLASS_DECL_ACME apex_main_data :
   virtual public apex_main_struct,
   virtual public ::object
{
public:


   ///int                              m_iPathInstallFolderExeArg;
   bool                             m_bFork;
   string                           m_strStandalone;
   //LPFN_MAIN_RUNNER                 m_mainrunnera[64];
   ::e_display                      m_edisplay;
   ::e_activation                   m_eactivation;
   ::file::path                     m_pathCacheDirectory;

//#ifdef WINDOWS
//
//   hinstance                        m_hinstance;
//   hinstance                        m_hPrevInstance;
//   int                              m_nCmdShow;
//
//#endif


   apex_main_data();
   ~apex_main_data() override;


   void set_main_struct(const apex_main_struct  & mainstruct);


   void system_construct(const class ::main * pmain) override;


   //void system_construct(int argc, char** argv, char ** envp);
   //void system_construct(int argc, wchar_t** argv, wchar_t ** envp);

   virtual void on_system_construct();


#ifdef WINDOWS_DESKTOP

   void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(UNIVERSAL_WINDOWS)

   void system_construct(const string_array & stra);

#else

   void system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display & edisplay = ::e_display_none);

#endif

   string get_arg(int i) const;
   string get_env(const char *pszVariableName) const;


   bool is_console_app() const;


};
