// From main.inl to main_executable.inl by
// camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#define CLASS_DECL_APPLICATION_NAMESPACE CLASS_DECL_IMPORT
#include "acme/inline/application/main.h"




#ifdef CUBE
#include  "acme/platform/factory_function.h"
#include "operating_system/appconfig.h"
#include "_static_factory_.inl"
DO_FACTORY(REFERENCE_FACTORY)
#endif


#ifdef WINDOWS

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif


#if defined(WINDOWS)
int WINAPI wWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow)
#elif defined(__ANDROID__)
extern "C" int android_main(int argc, char* argv[], char* envp[], const char* p1, const char* p2)
#else
extern "C" int main(int argc, char* argv[], char* envp[])
#endif
{

   ::platform::system* psystem;

#if defined(WINDOWS)
   psystem = APPLICATION_NAMESPACE_MAIN(create_system)(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);
#elif defined(__ANDROID__)
   psystem = APPLICATION_NAMESPACE_MAIN(create_system)(argc, argv, envp, p1, p2);
#else
   psystem = APPLICATION_NAMESPACE_MAIN(create_system)(int argc, char* argv[], char* envp[]);
#endif

   auto iExitCode = APPLICATION_NAMESPACE_MAIN(main)(psystem);

   return iExitCode;

}



