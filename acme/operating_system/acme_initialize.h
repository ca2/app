// Created by camilo on 2023-11-10 23:28 <3ThomasBorregaardSorensen!!
#pragma once


namespace acme
{


#if defined(WINDOWS) && defined(UNICODE)
   CLASS_DECL_ACME void initialize(::i32 argc, wchar_t * wargv[], wchar_t * wenvp[]);
   CLASS_DECL_ACME void initialize(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR * pCmdLine, ::i32 nCmdShow);
#else
   CLASS_DECL_ACME void initialize(::i32 argc, platform_char ** argv, platform_char ** envp);
#endif


} // namespace acme