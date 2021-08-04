#include "framework.h"



namespace hotplugin
{


   container_launcher::container_launcher(string strPlatform, const ::string & pszChannel)
   {

      m_strChannel   = pszChannel;

      m_strPlatform  = strPlatform;

   }


   string container_launcher::get_executable_path()
   {

      return ::path::app_app_nest(m_strPlatform, process_configuration_dir_name());

   }


   string container_launcher::get_params()
   {

      return string(": channel=") + m_strChannel;

   }


} // namespace hotplugin


