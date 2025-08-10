// From main.inl to main_executable.inl by
// camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#define CLASS_DECL_APPLICATION_NAMESPACE CLASS_DECL_IMPORT
#include "acme/inline/application/main.h"




#ifdef WINDOWS

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif


#if defined(WINDOWS)
int WINAPI wWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow)
#else
extern "C" int main(int argc, char* argv[], char* envp[])
#endif
{

   APPLICATION_NAMESPACE_MAIN(create_system)();

#if defined(WINDOWS)
   APPLICATION_NAMESPACE_MAIN(initialize_system)(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);
#elif defined(__ANDROID__)
   const char * p1 = nullptr; //_todo_begin;
   const char * p2 = nullptr; //_todo_end;
   APPLICATION_NAMESPACE_MAIN(initialize_system)(argc, argv, envp, p1, p2);
#else
   APPLICATION_NAMESPACE_MAIN(initialize_system)(argc, argv, envp);
#endif

   auto iExitCode = APPLICATION_NAMESPACE_MAIN(main)();

   return iExitCode;

}



