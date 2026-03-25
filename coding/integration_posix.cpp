//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "integration.h"
#include "item.h"
#include "application.h"
#include "impact_interface.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/handler/sequence.h"
#include "acme/prototype/comparison/array.h"
#include "aura/user/user/still.h"


#include "acme/_operating_system.h"


namespace coding
{


   void integration::prepare_build()
   {

//      m_straunion.add_array(m_pintegrationcontext->m_straOutput);
//
//      m_straunion.add_array(m_straLine2);

   }


   void integration::integrate_posix(const ::scoped_string & scopedstrRelease)
   {

      auto strSystemSlashedIntegration = m_poperatingsystemsummary->m_strSlashedIntegration;

      if(m_strRepositoryPath.trimmed().is_empty())
      {

         ::string strError;

         strError = "Integration Folder cannot be empty for building \"" + strSystemSlashedIntegration + "\".";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         psequencer->do_asynchronously();

         return;

      }
      else if(!directory_system()->is(m_strRepositoryPath))
      {

         ::string strError;

         strError = "Specified path (\"" + m_strRepositoryPath + "\") for Integration Folder doesn't exist or isn't folder";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         psequencer->do_asynchronously();

         return ;

      }
      else if(!node()->has_posix_shell_command("cmake"))
      {

         ::string strError;

         strError = "cmake is not installed";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         psequencer->do_asynchronously();

         return ;

      }
      else if(!node()->has_posix_shell_command("ninja"))
      {

         ::string strError;

         strError = "ninja is not installed";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         psequencer->do_asynchronously();

         return ;

      }

      information() << "integration_posix slashed : " << strSystemSlashedIntegration;

      information() << "integration_posix release : " << scopedstrRelease;

      //m_strDistroRelease = scopedstrDistroRelease;

      //m_poperatingsysttem->initialize(this);//

      //auto strSystemSlashedOperatingSystem = acmenode()->get_environment_variable("__SYSTEM_SLASHED_OPERATING_SYSTEM");

      ::file::path pathIntegrationFolder;

      pathIntegrationFolder = directory_system()->home() / "integration" / strSystemSlashedIntegration;

      m_pathStoreFolder1 = directory_system()->home() / "store" / strSystemSlashedIntegration;

      m_pathStorageFolder = directory_system()->home() / "storage" / strSystemSlashedIntegration;

      directory_system()->create(pathIntegrationFolder);

      file_system()->erase(pathIntegrationFolder / "build succeeded.txt");

      file_system()->erase(pathIntegrationFolder / "build failed.txt");

      auto bBuildOk = integrate_posix_with_result(scopedstrRelease);

      string strBuildResult = m_strBuildResult;

      ::file::path pathBuildResult;

      pathBuildResult = pathIntegrationFolder / ("build-" + m_strReleaseFilename + ".txt");

      file_system()->put_contents(pathBuildResult, strBuildResult);

      if(bBuildOk)
      {

         file_system()->put_contents(pathIntegrationFolder / "build succeeded.txt", strBuildResult);

      }
      else
      {

         file_system()->put_contents(pathIntegrationFolder / "build failed.txt", strBuildResult);

      }

   }


   bool integration::integrate_posix_with_result(const ::scoped_string &scopedstrRelease)
   {

      ::file::path pathBuildFolder = m_strRepositoryPath;

      directory_system()->change_current(pathBuildFolder);

      string strFileName;

      strFileName = "ca2";

      if(m_baPhaseEnable[e_phase_checkout])
      {

         add_command(
            "checkout",
            "posix://checkout",
            10_minute);

      }

      if(m_baPhaseEnable[e_phase_application_list])
      {

         add_command(
         "application_list",
         "application_build_helper --application-list",
         3_minute);

      }

      if(m_baPhaseEnable[e_phase_prepare_applications])
      {

         add_command("prepare_applications",
         "application_build_helper --prepare-applications",
         10_minute);

      }

      if(m_baPhaseEnable[e_phase_project_list])
      {

         add_command("project_list",
         "application_build_helper --project-list",
         10_minute);

      }

      if(m_baPhaseEnable[e_phase_prepare_projects])
      {

         add_command("prepare_projects",
         "application_build_helper --prepare-projects",
         10_minute);

      }

      if(m_baPhaseEnable[e_phase_cmake])
      {

         ::string strCommand;

         strCommand = "cmake";
         strCommand += " -DCMAKE_BUILD_TYPE=Release";
         strCommand += " -DCMAKE_MAKE_PROGRAM=ninja";
         strCommand += " -G Ninja";
         strCommand += " -S " + pathBuildFolder;
         strCommand += " -B " + pathBuildFolder + "/cmake-build-release";

         add_command(
                 "cmake",
               strCommand,
               5_minute);

      }

      if(m_baPhaseEnable[e_phase_clean])
      {


         ::string strCommand;

         strCommand = "cmake";
         strCommand += " --build " + pathBuildFolder + "/cmake-build-release";
         strCommand += " --target clean -- -j 6";

         add_command("cmake_clean",
               strCommand,
               10_minute);

      }

      auto bOk = integrate_command_list();

      if(!bOk)
      {

         return false;

      }

      m_integrationcommanda.clear();

      information() << "reading list of applications";

      auto strApps = file_system()->lines(m_strRepositoryPath / "application_store.txt");

      if(strApps.is_empty())
      {

         strApps = file_system()->lines(m_strRepositoryPath / "application_release.txt");

         if(strApps.is_empty())
         {

            strApps = file_system()->lines(m_strRepositoryPath / "application_list.txt");

         }

      }

      ::comparison::array::defer_transfer_to(strApps, 0, "app-core/store");

      for(auto & strApp : strApps)
      {

         ::string strAppId = strApp().trim();

         information() << strAppId;

         ::string strLabel = "build_project " + strAppId;

         ::string strTarget;

         strTarget = "_" + strAppId;

         strTarget.find_replace("/", "_");

         strTarget.find_replace("-", "_");

         ::string strCommand;

         strCommand = "cmake";
         strCommand += " --build " + pathBuildFolder + "/cmake-build-release";
         strCommand += " --target " + strTarget + " -- -j 6";

         auto timeTimeout = 1_hour;

         add_command(strLabel, strCommand, timeTimeout);

      }

      bOk = integrate_command_list();

      return bOk;

   }


   bool integration::on_packaging(::string &strAppId, ::string &strTarget, ::string &strSource)
   {

      if(!on_more_packaging(strAppId, strTarget, strSource))
      {

//         {
//
//            synchronous_lock synchronouslock(this->synchronization());
//
//            m_itemtimeaSummary.insert_at(0, {"✗ " + strAppId, m_timeTopicStart.elapsed()});
//
//         }

         integration_summary(strAppId, "📦");

         return false;

      }

//      if(strAppId == "app-core/store")
//      {
//
//         ::file::path pathSource = strSource;
//
//         ::string strName;
//
//         strName = pathSource.name() + "_(2)_" + m_strReleaseFilename + ".txt";
//
//         auto pathLog = pathSource.folder() / strName;
//
//         auto pfileLog = file()->get_writer(pathLog, ::file::e_open_write | ::file::e_open_create |
//                                                     ::file::e_open_defer_create_directory |
//                                                     ::file::e_open_share_deny_write);
//
//         trace_function tracefunction = [&](auto etracelevel, auto &str)
//         {
//
//            ::string strTrace;
//
//            strTrace = str + "\n";
//
//            pfileLog->write(strTrace);
//
//            m_pimpactinterface->on_lines_change();
//
//         };
//
//         ::string strCommand = "application_build_helper --release-store-installer";
//
//         int iExitCode = acmenode()->command_system(strCommand, tracefunction);
//
//         if(iExitCode != 0)
//         {
//
//            integration_summary(strAppId, "🏪");
//
//
////            { x
////
////               synchronous_lock synchronouslock(this->synchronization());
////
////               m_itemtimeaSummary.insert_at(0, {"✗ " + strAppId, m_timeTopicStart.elapsed()});
////
////            }
//
//            return false;
//
//         }
//
//         ::string strSystemSlashedIntegration = m_poperatingsystemsummary->m_strSlashedIntegration;
//
//         ::string strPlatform = m_poperatingsystemsummary->m_strPackagePlatform;
//
//         ::string strExtension = m_poperatingsystemsummary->m_strStandardPackageFileExtension;
//
//         //strTarget = strSystemSlashedIntegration / ("store_" + strPlatform + "." + strExtension);
//
//         strTarget = ("store_" + strPlatform + "." + strExtension);
//
//         strSource = m_pathStoreFolder / ("store_" + strPlatform + "." + strExtension);
//
//      }

      return true;

   }


   void integration::on_start_task_group(enum_task etaskGroup)
   {

      m_etaskGroupRunning = etaskGroup;

      m_pimpactinterface->on_start_task_group(etaskGroup);

//      if (etaskGroup == e_task_openssl)
//      {
//
//         auto ptaskgroup = m_taskgroup[etaskGroup];
//
//         m_papp->_defer_install_msys2(ptaskgroup);
//
//         m_papp->defer_install(e_install_strawberry_perl, ptaskgroup);
//
//         if (!m_papp->is_installed(e_install_strawberry_perl, false))
//         {
//
//            throw ::exception(error_wrong_state, "StrawberryPerl isn't installed or not installed at C:\\Strawberry");
//
//         }
//
//      }
//      else if (etaskGroup == e_task_ffmpeg)
//      {
//
//         auto ptaskgroup = m_taskgroup[etaskGroup];
//
//         m_papp->_defer_install_msys2(ptaskgroup);
//
//      }

   }


} // namespace coding



