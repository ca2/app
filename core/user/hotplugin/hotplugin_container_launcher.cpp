#include "framework.h"



namespace hotplugin
{


   container_launcher::container_launcher(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrChannel)
   {

      m_strChannel   = pszChannel;

      m_strPlatform  = strPlatform;

   }


   string container_launcher::get_executable_path()
   {

      return ::path::app_app_nest(m_strPlatform, process_configuration_name());

   }


   string container_launcher::get_params()
   {

      return string(": channel=") + m_strChannel;

   }


} // namespace hotplugin


