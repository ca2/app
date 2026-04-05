#pragma once


#include "acme/_.h"


#if defined(_coding_project)
#define CLASS_DECL_CODING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CODING  CLASS_DECL_IMPORT
#endif

#ifdef OPENBSD
#define INTEGRATION_HAS_AUDIO 0
#else
#define INTEGRATION_HAS_AUDIO 1
#endif


//#define ASSUME_NOTHING_INSTALLED false
//#define TORTOISE_SVN true
//#define SMART_SVN false
#ifdef WINDOWS
#define TORTOISE_GIT 1
#endif

#define SMART_GIT 1
#define INSTALL_GIT_ServiceControlManager 1

#ifdef LINUX
#define JETBRAINS_CLION 1
#else
#define JETBRAINS_CLION 0
#endif



namespace coding
{


   enum enum_application
   {

      e_application_none,
      e_application_build_tool,
      e_application_integration,
      e_application_handler,
      e_application_code,

   };




   class application;
   class document;
   class impact;
   class tab_impact;
   class integration;
   class impact_interface;
   class log_interface;


   class item;


   class group;
   class group_netnode;
   class group_new_release_prefix;

   class task;
   class task_group;


   class install;
   class option;


   class install_impact_interface;
   class install_log_interface;


#ifdef WINDOWS_DESKTOP


   CLASS_DECL_CODING void visual_studio_select_project(::platform::system* psystem, string str);
   CLASS_DECL_CODING void visual_studio_select_configuration_platform(::platform::system* psystem, string strConfiguration, string strPlatform);


#endif



} // namespace coding


namespace coding
{


   class application;


}


namespace coding
{


   class code;
   class impact;
   class tab_impact;




}// namespace coding


#ifdef WINDOWS

#define OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME "solution"

#elif defined(__APPLE__)

#define OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME "workspace"

#else

#define OPERATING_SYSTEM_WORKSPACE_DEFAULT_NAME "cmake"

#endif


