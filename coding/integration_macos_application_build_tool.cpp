//
// Created by camilo on 2025-01-06 08:28 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application.h"
#include "item.h"
#include "task_group.h"
#include "impact_interface.h"
#include "integration_macos.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/prototype/url.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/system.h"


#include "acme/_operating_system.h"


namespace macos
{


namespace coding
{

void integration::task_group_tasks_ordinals(::coding::enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal)
{
   
   
   switch (etaskGroup)
   {
      case ::coding::e_task_port:
      case ::coding::e_task_openssl:
      case ::coding::e_task_ffmpeg:
   {
      etaskaOrdinal.add(::coding::e_task_multi_arch_debug);
      etaskaOrdinal.add(::coding::e_task_multi_arch_release);
   }
   break;
   default:
      break;

   }

}



void integration::on_initialize_application_build_tool_operating_system_integrate_list()
{
   
   m_eintegrateaOperatingSystem.copy_initializer_list(
                                                      {
                                                         ::coding::e_integrate_macos_openssl,
                                                         ::coding::e_integrate_macos_ffmpeg,
                                                         ::coding::e_integrate_ios_openssl,
                                                         ::coding::e_integrate_ios_ffmpeg,
                                                      });
   
}




void integration::on_initialize_application_build_tool_task_groups()
{
   
   _defer_task_group(::coding::e_task_openssl);
   _defer_task_group(::coding::e_task_ffmpeg);
   _defer_task_group(::coding::e_task_ios_openssl);
   _defer_task_group(::coding::e_task_ios_ffmpeg);

}



} // namespace coding



} // namespace macos





namespace coding{


::string integration::task_group_id(enum_task etaskGroup)
{

   ::string strTaskGroupId;
#ifdef WINDOWS_DESKTOP

   if (m_papp->m_bWinRT)
   {
      strTaskGroupId = "winrt_";
   }

#endif

   switch (etaskGroup)
   {
   case e_task_port:
      strTaskGroupId+= "port";
      break;
   case e_task_openssl:
      strTaskGroupId += "openssl";
      break;
   case e_task_ffmpeg:
      strTaskGroupId += "ffmpeg";
      break;
   case e_task_ios_openssl:
      strTaskGroupId += "ios_openssl";
      break;
   case e_task_ios_ffmpeg:
      strTaskGroupId += "ios_ffmpeg";
      break;
   case e_task_windows:
      strTaskGroupId += "windows";
      break;
   case e_task_macos:
      strTaskGroupId += "macos";
      break;
   default:
      throw ::exception(error_not_implemented);
   }
   
   return strTaskGroupId;

}


::string integration::task_group_name(enum_task etaskGroup)
{

   ::string strTaskGroupName;

#ifdef WINDOWS_DESKTOP

   if (m_papp->m_bWinRT)
   {
      strTaskGroupName = "Universal ";
   }
   else
   {
      strTaskGroupName = "Destkop ";
   }

#endif

   switch (etaskGroup)
   {
   case e_task_port:
      strTaskGroupName+= "port";
      break;
   case e_task_openssl:
      strTaskGroupName+= "OpenSSL";
      break;
   case e_task_ffmpeg:
      strTaskGroupName += "FFMPEG";
      break;
   case e_task_ios_openssl:
      strTaskGroupName+= "ios OpenSSL";
      break;
   case e_task_ios_ffmpeg:
      strTaskGroupName += "ios FFMPEG";
      break;
   case e_task_windows:
      strTaskGroupName += "Windows";
      break;
   case e_task_macos:
      strTaskGroupName += "macOS";
      break;
   default:
      throw ::exception(error_not_implemented);
   }

   return strTaskGroupName;
}


::string integration::task_group_speech_name(enum_task etaskGroup)
{

   switch (etaskGroup)
   {
   case e_task_port:
      return "Windows Port";
   case e_task_openssl:
      return "Open S S L";
   case e_task_ffmpeg:
      return "F F Em PEG";
   case e_task_windows:
      return "Windows";
   case e_task_macos:
      return "macOS";
   case e_task_ios_openssl:
      return "i o s Open S S L";
   case e_task_ios_ffmpeg:
      return "i o s F F Em PEG";
   default:
      throw ::exception(error_not_implemented);
   }

}


}
