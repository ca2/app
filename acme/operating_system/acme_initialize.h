// Created by camilo on 2023-11-10 23:28 <3ThomasBorregaardSorensen!!
#pragma once


namespace acme
{


#if defined(WINDOWS) && defined(UNICODE)
   CLASS_DECL_ACME void initialize(int argc, wchar_t * wargv[], wchar_t * wenvp[]);
   CLASS_DECL_ACME void initialize(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR * pCmdLine, int nCmdShow);
#else
   CLASS_DECL_ACME void initialize(int argc, platform_char ** argv, platform_char ** envp);
#endif


} // namespace acme