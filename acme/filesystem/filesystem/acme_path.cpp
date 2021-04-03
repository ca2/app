// Create on 2021-03-21 00:11 <3ThomasBS_
#include "framework.h"
#include "acme_path.h"
#include "acme_dir.h"


::file::path acme_path::app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

}


::file::path acme_path::app_app_admin(string strPlatform, string strConfiguration)
{

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

}


::file::path acme_path::app_app_nest(string strPlatform, string strConfiguration)
{

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

}


::file::path acme_path::app_app(string strPlatform, string strConfiguration)
{

#ifdef WINDOWS

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

}


::file::path acme_path::vcredist(string strPlatform, string strConfiguration)
{

   return m_psystem->m_pacmedir->stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

}


::file::path acme_path::install_log(string strPlatform, string strConfiguration)
{

   return m_psystem->m_pacmedir->install() / ("install-" + strPlatform + ".log");

}


string acme_path::from(string str)
{

   string strFsSafe;

   for (index i = 0; i < str.length(); i++)
   {

      if (ansi_char_is_alphanumeric(str[i]))
      {

         strFsSafe += str[i];

      }
      else
      {

         strFsSafe += "-" + ::hex::lower_from(str[i]);

      }

   }

   return strFsSafe;

}


::file::path acme_path::app_module()
{

   return "";

}



