//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
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
integration::integration()
{
   
}


integration::~integration()
{
   
}


void integration::prepare_build()
{
   
   directory_system()->create(m_strRepositoryPath / "time-macos/archive");
   
   directory_system()->create(m_strRepositoryPath / "time-macos/release");
   
   directory_system()->create(m_strRepositoryPath / "time-macos/store");
   
   //m_iCurrentStoreCopyStruct = 0;
   
}


void integration::integrate_main2(::coding::item* pitem)
{
   
   auto&  ptaskgroup = pitem->m_ptaskgroup;
   
   _defer_task_group(::coding::e_task_macos, &ptaskgroup);
   
   //string& strBuildResult = m_strBuildResult;
   
   ptaskgroup->m_pathBuildFolder = m_strRepositoryPath;
   
   ::file::path pathOperatingSystemFolder;
   
   pathOperatingSystemFolder = ptaskgroup->m_pathBuildFolder / "operating_system/operating_system-macos";
   
   //auto pacmedirectory = directory_system();
   
   auto pathApplicationList = m_strRepositoryPath / "application_release.txt";
   
    ::string strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientRelease;
   
   m_pathStoreFolder1 = directory_system()->home() / "store" / strSystemAmbientRelease;
   
   m_pathStorageFolder = directory_system()->home() / "storage" / strSystemAmbientRelease;
   
   add_store_copy("application_build_helper", "application_build_helper", m_pathStorageFolder / "application_build_helper");
   
   auto straLines = file_system()->lines(pathApplicationList);
   
   straLines.insert_unique_at(0, "app-core/store");
   
   //straLines.insert_unique_at(0, "integration/code");
   
   for(auto & strLine : straLines)
   {
      auto range = strLine();
      
      
      if(range.contains('/'))
      {
         
         range.trim();
         
         ::string strAppId;
         
         strAppId = range;
         
         auto strRoot = range.consume_token_until_any_character_in("\\/");
         
         strRoot.find_replace("-", "_");
         
         auto strName = range.consume_token_until_any_character_in("\\/");
         
         strName.find_replace("-", "_");
         
         ::string strScheme;
         
         strScheme = "_" + strRoot + "_" + strName;
         
         ::string strOk;
         
         try
         {
            
            strOk = macos_archive(strAppId, strScheme);
            
         }
         catch (...)
         {
            
         }
         
         //auto timeElapsed = m_timeTopicStart.elapsed();
         
         if(strOk.has_character())
         {
            
            //integration_summary(strAppId, "✓");
            integration_summary(strAppId, strOk, true);
            
         }
         //            else
         //            {
         //
         //               m_itemtimeaSummary.insert_at(0, { "✗ " + strScheme, timeElapsed });
         //
         //            }
         
      }
      
   }
   
}


//void integration::task_group_tasks_ordinals(::coding::enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal)
//{
//   
//   
//   switch (etaskGroup)
//   {
//      case ::coding::e_task_port:
//      case ::coding::e_task_openssl:
//      case ::coding::e_task_ffmpeg:
//   {
//      etaskaOrdinal.add(::coding::e_task_multi_arch_debug);
//      etaskaOrdinal.add(::coding::e_task_multi_arch_release);
//   }
//   break;
//   default:
//      break;
//
//   }
//
//}
//



::string integration::macos_archive(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme)
{
   
   ::string strScheme = scopedstrScheme;
   
   main_status(strScheme);
   
   ::file::path pathXcworkspace;
   
   if(scopedstrAppId == "integration/code")
   {
      
      ::file::path pathBuildFolder = m_strRepositoryPath;
      
      pathXcworkspace = (pathBuildFolder - 1) / "integration/workspace-macos/mac-integration.xcworkspace";
      
   }
   else
   {
      
      ::file::path pathBuildFolder = m_strRepositoryPath;
      
      pathXcworkspace = pathBuildFolder / "workspace-macos/mac-all.xcworkspace";
      
   }
   
   auto pathXcarchive = m_strRepositoryPath / "time-macos/archive" / (scopedstrAppId + ".xcarchive");
   
   auto pathReleaseFolder = m_strRepositoryPath / "time-macos/release" / scopedstrAppId;
   
   pathReleaseFolder -= 1;
   
   auto pathReleaseApp = pathReleaseFolder /(strScheme + ".app");
   
   ::string strZipFilename;
   
   //      if(scopedstrAppId == "app-core/store")
   //      {
   //
   //         strZipFilename = "store.zip";
   //
   //      }
   //      else
   {
      
      strZipFilename = scopedstrAppId + ".zip";
      
   }
   
   //auto pathZip = m_pathStoreFolder / "store-zip" / strZipFilename;
   
   auto pathStorage = m_pathStorageFolder / strZipFilename;
   
   auto pathExportOptionsPlist = m_strRepositoryPath /"operating_system/operating_system-macos/exportOptions.plist";
   
   synchronous_lock sl(m_pmutexLines);
   
   directory_system()->change_current(m_strRepositoryPath);
   
   ::file_pointer pfileLog;
   
   int iExitCode = 0;
   
   ::string strCommand;
   
   trace_function functionTrace = [&](auto etracelevel, auto & str, bool bCarriage)
   {
      
      if(etracelevel <= e_trace_level_information)
      {
         
         m_straLine3.feed_line("I: " + str, bCarriage);
         
      }
      else
      {
         
         m_straLine3.feed_line("E: " + str, bCarriage);
         
      }
      
      pfileLog->write(str + "\n");
      
      m_pimpactinterface->on_lines_change();
      
   };
   
   //bool bStorageDone = false;
   
   if(!file_system()->exists(pathStorage))
   {
      
      if(!directory_system()->is(pathReleaseApp))
      {
         
         if(!directory_system()->is(pathXcarchive))
         {
            
            directory_system()->create(pathXcarchive.folder());
            
            append_message("xcarchive folder \"%s\" doesn't exist...", pathXcarchive.c_str());
            
            append_message("Creating xcarchive folder \"%s\"...", pathXcarchive.c_str());
            
            strCommand.formatf("xcodebuild -workspace \"%s\" -scheme \"%s\" archive -archivePath \"%s\"", pathXcworkspace.c_str(), strScheme.c_str(), pathXcarchive.c_str());
            
            auto pathLogFolder = directory_system()->home() / "integration";
            
            pathLogFolder /= m_strReleaseFilename;
            
            auto strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientRelease;
            
            pathLogFolder /= strSystemAmbientRelease;
            
            auto pathLog = pathLogFolder / (scopedstrAppId + "_build.txt");
            
            pfileLog = file()->get_writer(pathLog);
            
            sl.unlock();
            
            functionTrace.set_timeout(2_hour);
            
            node()->command_system(strCommand, functionTrace);
            
            sl.lock();
            
         }
         
         if(!directory_system()->is(pathXcarchive))
         {
            
            return "✗";
            
         }
         
         directory_system()->create(pathReleaseFolder);
         
         append_message( "application folder \"%s\" doesn't exist...", pathReleaseApp.c_str());
         
         append_message( "Creating application folder \"%s\"...", pathReleaseApp.c_str());
         
         strCommand.formatf("xcodebuild -exportArchive -archivePath \"%s\" -exportPath \"%s\" -exportOptionsPlist \"%s\"",
                            pathXcarchive.c_str(), pathReleaseFolder.c_str(),
                            pathExportOptionsPlist.c_str());
         
         auto pathLogFolder = directory_system()->home() / "integration";
         
         pathLogFolder /= m_strReleaseFilename;
         
         auto strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientRelease;
         
         pathLogFolder /= strSystemAmbientRelease;
         
         auto pathLog = pathLogFolder / (scopedstrAppId + "_packaging.txt");
         
         pfileLog = file()->get_writer(pathLog);
         
         sl.unlock();
         
         functionTrace.set_timeout(15_minute);
         
         iExitCode = node()->command_system(strCommand, functionTrace);
         
         sl.lock();
         
      }
      
      if(!directory_system()->is(pathReleaseApp))
      {
         
         return "📦";
         
      }
      
      directory_system()->create(pathStorage.folder());
      
      append_message( "\"%s\" doesn't exist...", pathStorage.c_str());
      
      append_message( "Creating \"%s\"...", pathStorage.c_str());
      
      auto pathFolderReleaseApp = pathReleaseApp.folder();
      
      auto strNameReleaseApp = pathReleaseApp.name();
      
      strCommand.formatf("zip -r \"%s\" \"%s\"", pathStorage.c_str(), ::string(strNameReleaseApp).c_str());
      
      auto pathLogFolder = directory_system()->home() / "integration";
      
      pathLogFolder /= m_strReleaseFilename;
      
      auto strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientRelease;
      
      pathLogFolder /= strSystemAmbientRelease;
      
      auto pathLog = pathLogFolder / (scopedstrAppId + "_store.txt");
      
      pfileLog = file()->get_writer(pathLog);
      
      sl.unlock();
      
      directory_system()->change_current(pathFolderReleaseApp);
      
      functionTrace.set_timeout(5_min);
      
      node()->command_system(strCommand, functionTrace);
      
      sl.lock();
      
      //bStorageDone = true;
      
   }
   
   if(!file_system()->exists(pathStorage))
   {
      
      return "🏪";
      
   }
   
   auto pitem = summary_item(scopedstrAppId);
   
   pitem->m_timeBuild = m_timeTopicBuildStart.elapsed();
   
   //if(bStorageDone)
   {
      
      add_store_copy(scopedstrAppId);
      
   }
   
   append_message(strScheme);
   
   return "";
   
}


bool integration::on_packaging(::string &strAppId, ::string &strTarget, ::string &strSource)
{
   
   if(strAppId == "app-core/store")
   {
      //
      //      ::string strCommand = "application_build_helper --release-store-installer";
      //
      //      acmenode()->command_system(strCommand, tracefunction);
      //
      ::string strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientRelease;
      //
      //      ::string strPlatform = m_poperatingsystemsummary->m_strPackagePlatform;
      //
      //      ::string strExtension = m_poperatingsystemsummary->m_strStandardPackageFileExtension;
      //
      //strTarget = strSlashedIntegration / "store.zip";
      strTarget = "store.zip";
      //
      //      strSource = m_pathStoreFolder / ("store_" + strPlatform + "." + strExtension);
      //
   }
   
   return true;
   
}


//b
//   ::file::path integration::port_base_folder()
//   {
//
//      return directory_system()->home() / "port";
//
//   }



void integration::on_start_task_group(::coding::enum_task etaskGroup)
{
   
   m_etaskGroupRunning = etaskGroup;
   
   m_pimpactinterface->on_start_task_group(etaskGroup);
   
   if (etaskGroup == ::coding::e_task_openssl)
   {
      
#ifdef WINDOWS_DESKTOP
      
      auto ptaskgroup = m_taskgroup[etaskGroup];
      
      m_papp->defer_install(e_install_msys2, ptaskgroup);
      
      if (!m_papp->is_installed(e_install_msys2, false))
      {
         
         throw ::exception(error_wrong_state, "msys2 isn't installed or not installed at C:\\msys64");
         
      }
      
      m_papp->defer_install(e_install_strawberry_perl, ptaskgroup);
      
      if (!m_papp->is_installed(e_install_strawberry_perl, false))
      {
         
         throw ::exception(error_wrong_state, "StrawberryPerl isn't installed or not installed at C:\\Strawberry");
         
      }
      
#endif
      
   }
   
}


void integration::defer_task_groups()
{
   
}

} // namespace coding

} // namespace macos



void coding_factory(::factory::factory * pfactory)
{
   
   pfactory->add_factory_item<::macos::coding::integration, ::coding::integration>();
   
}


