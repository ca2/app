// Created by camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/_operating_system.h"
#include "acme/platform/system_setup.h"


#define APPLICATION_NAMESPACE_MAIN(function) IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(APPLICATION_NAMESPACE, _main), _), function)


#if defined(WINDOWS)
CLASS_DECL_APPLICATION_NAMESPACE int APPLICATION_NAMESPACE_MAIN(wWinMain)(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow);
#elif defined(__ANDROID__)
extern "C" int APPLICATION_NAMESPACE_MAIN(android_main)(int argc, char* argv[], char* envp[], const char* p1, const char* p2)
#else
extern "C" int APPLICATION_NAMESPACE_MAIN(main)(int argc, char* argv[], char* envp[]);
#endif
