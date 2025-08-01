// Created by camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/_operating_system.h"
#include "acme/platform/system_setup.h"


#define APPLICATION_NAMESPACE_MAIN(function) IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(APPLICATION_NAMESPACE, _main), _), function)


#if defined(WINDOWS)
CLASS_DECL_APPLICATION_NAMESPACE void APPLICATION_NAMESPACE_MAIN(create_system)();
#elif defined(__ANDROID__)
extern "C" void APPLICATION_NAMESPACE_MAIN(create_system)();
#else
extern "C" void APPLICATION_NAMESPACE_MAIN(create_system)();
#endif


#if defined(WINDOWS)
CLASS_DECL_APPLICATION_NAMESPACE void APPLICATION_NAMESPACE_MAIN(initialize_system)(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow);
#elif defined(__ANDROID__)
CLASS_DECL_APPLICATION_NAMESPACE void APPLICATION_NAMESPACE_MAIN(initialize_system)(int argc, char* argv[], char* envp[], const_char_pointer p1, const_char_pointer p2);
#else
CLASS_DECL_APPLICATION_NAMESPACE void APPLICATION_NAMESPACE_MAIN(initialize_system)(int argc, char* argv[], char* envp[]);
#endif


CLASS_DECL_APPLICATION_NAMESPACE int APPLICATION_NAMESPACE_MAIN(main)();



