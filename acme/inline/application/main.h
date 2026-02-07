// Created by camilo on 2025-07-31 14:17 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/_operating_system.h"
#include "acme/platform/system_setup.h"




#define APPLICATION_NAMESPACE_MAIN(function) IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(IDENTIFIER_CONCATENATE(APPLICATION_NAMESPACE, _main), _), function)


#include "acme/inline/_include_user_and_system.h"


#if defined(WINDOWS)
#define APPLICATION_NAMESPACE_MAIN_EXPORT CLASS_DECL_APPLICATION_NAMESPACE
#else
#define APPLICATION_NAMESPACE_MAIN_EXPORT extern "C"
#endif


APPLICATION_NAMESPACE_MAIN_EXPORT void APPLICATION_NAMESPACE_MAIN(create_system)();


#if defined(WINDOWS)
APPLICATION_NAMESPACE_MAIN_EXPORT void APPLICATION_NAMESPACE_MAIN(initialize_system)(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow);
APPLICATION_NAMESPACE_MAIN_EXPORT void APPLICATION_NAMESPACE_MAIN(initialize_console_system)(int argc, char* argv[], char* envp[]);
#elif defined(__ANDROID__)
APPLICATION_NAMESPACE_MAIN_EXPORT void APPLICATION_NAMESPACE_MAIN(initialize_system)(int argc, char* argv[], char* envp[], const_char_pointer p1, const_char_pointer p2);
#else
APPLICATION_NAMESPACE_MAIN_EXPORT void APPLICATION_NAMESPACE_MAIN(initialize_system)(int argc, char* argv[], char* envp[]);
#endif


APPLICATION_NAMESPACE_MAIN_EXPORT int APPLICATION_NAMESPACE_MAIN(main)();




