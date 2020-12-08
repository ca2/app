#include "framework.h"


namespace install
{


   starter_start::starter_start(::layered * pobjectContext) :
      ::object(pobject)
   {

   }


   ::u32 starter_start::start()
   {

      bool bHostStarterStartFoo = false;

      bool * pbHostStarterStartFoo = nullptr;

      if(m_phost == nullptr)
      {

         pbHostStarterStartFoo = &bHostStarterStartFoo;

      }
      else
      {

         pbHostStarterStartFoo = &m_phost->m_bHostStarterStart;

      }

      keep < bool > keepStarterStart(pbHostStarterStartFoo,true,false,true);

      
      if (m_bStarting)
         return -1;

#if CA2_PLATFORM_VERSION == CA2_BASIS

      string strVersion = "basis";

#else

      string strVersion = "stage";

#endif

      if(file_exists(::dir::system() / "config\\plugin\\version.txt"))
         strVersion = file_as_string(::dir::system() / "config\\plugin\\version.txt");

      ::set_thread(m_pplugin);

      string strId = get_command_line_param(m_strCommandLine, "app", "session", "session_start").trimmed();

      string strType;

      string strLocale;

      string strSchema;

      get_command_line_param(strType, m_strCommandLine, "app_type");

      get_command_line_param(strLocale, m_strCommandLine, "locale");

      get_command_line_param(strSchema, m_strCommandLine, "schema");

      get_command_line_param(strVersion,m_strCommandLine,"version");

      if (strId.is_empty())
         return -1;

      if (strType.is_empty())
         strType = "application";

      keep_true keepStarting(m_bStarting);

      i32 i = 0;

      string strBuild;

      System.install().set_admin(false);

      while (true)
      {

         if ((i % 5) == 0 || strBuild.is_empty())
         {

            strBuild = "latest";

         }

         if (System.install().is_installing_ca2())
         {
            
            sleep((5000) * 2);

            continue;

         }

         System.install().update_ca2_installed(true);

         if (System.install().is_ca2_installed() && System.install().is_installed(strVersion, strBuild, strType, strId, strLocale, strSchema))
         {

            break;

         }

         System.install().synch_install(m_strCommandLine, strBuild);

         prepare_small_bell(true);

      }

      if (System.install().is_ca2_installed() && System.install().is_installed(strVersion, strBuild, strType, strId, strLocale, strSchema) && m_pplugin != nullptr)
      {

         defer_play_small_bell();

         m_pplugin->set_ca2_installation_ready();

      }

      // sentinel is not ready neither spa entire concept of passive installation is ready yet.
      // recap:  wait for a required installation. But upgrades are passive installation,  done when it all can be done hot or when there is no use, except when it is requested explicitly.

      /*string strPlatform = spa_get_platform();

      string strSentinelPath = dir::path(dir::beforeca2(), ("aura\\stage\\" + strPlatform + "\\app.sentinel.exe"));

      call_sync(strSentinelPath, "");*/

      return 0;

   }


   u32 _ca2_starter_start(void * p)
   {


      starter_start * pstart = (starter_start *)pvoid;


      ::u32 uRet = pstart->start();


      if (uiRet != 0)
         return uiRet;


      delete pstart;


      return uiRet;


   }


} // namespace install




