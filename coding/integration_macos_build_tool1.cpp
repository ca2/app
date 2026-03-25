//
// From integration_windows_build_tool.com by camilo on 2023-05-05 22:07 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application.h"
#include "impact.h"
#include "integration.h"
#include "item.h"
#include "task.h"
#include "task_group.h"
#include "acme/constant/integration.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/file/buffered_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/from_integer.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme_macos/_.h"


CLASS_DECL_ACME bool sort_of_ok_earth_time_from_international_string(const ::scoped_string& scopedstrTime);

namespace coding
{


//   void integration::integrate_macos_port(::coding::item* pitem)
//   {
//
//      integrate_windows_parallels(e_task_port, pitem);
//      //::file::path pathBuildFolder = m_pathBuildFolder;
//
//      //::file::path pathOperatingSystemFolder;
//
//      //pathOperatingSystemFolder = pathBuildFolder / "operating_system/operating_system-windows";
//
//      //auto pacmedirectory = directory_system();
//
//      //auto pacmefile = file_system();
//
//      //pacmedirectory->change_current(pathBuildFolder);
//
//      //::file::path pathDeploymentTemplate;
//
//      //pathDeploymentTemplate = pathOperatingSystemFolder / "deployment/deployment.txt";
//
//      //string strFileName;
//
//      ////string strProjectName;
//
//      //string strReleaseDot;
//
//      //string strReleaseComma;
//
//      //string strReleaseDateTime;
//
//      //string strFileNameTimeBuild;
//
//      //strFileName = "ca2";
//
//      ////strProjectName = "ca2";
//
//      //auto pdatetime = datetime();
//
//      //strReleaseDot = pdatetime->format("%Y.%m%d.%H%M.%S",m_timeBuild);
//
//      //strReleaseComma = pdatetime->format("%Y,%m%d,%H%M,%S", m_timeBuild);
//
//      //strReleaseDateTime = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);
//
//      //strFileNameTimeBuild = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);
//
//      //::file::path pathDeployment;
//
//      //pathDeployment = pathOperatingSystemFolder / ("deployment/deployment" + strFileNameTimeBuild + ".txt");
//
//      //::file::path pathDeploymentRcTemplate;
//
//      //pathDeploymentRcTemplate = pathOperatingSystemFolder / "deployment/deployment_rc.txt";
//
//      //auto strDeploymentRcTemplate = pacmefile->as_string(pathDeploymentTemplate);
//
//      //strDeploymentRcTemplate.find_replace("%FILENAME%", strFileName);
//      ////strDeploymentRcTemplate.find_replace("%PROJECTNAME%", strProjectName);
//      //strDeploymentRcTemplate.find_replace("%RELEASEDOT%", strReleaseDot);
//      //strDeploymentRcTemplate.find_replace("%RELEASECOMMA%", strReleaseComma);
//      //strDeploymentRcTemplate.find_replace("%RELEASEDATETIME%", strReleaseDateTime);
//
//      //pacmefile->put_contents(pathDeployment, strDeploymentRcTemplate);
//
//      //pacmefile->copy(pathDeploymentRcTemplate, pathDeployment, true);
//
//      //string strBuildSln;
//
//      //strBuildSln = m_pathBuildFolder / "solution-windows/third-all.sln";
//
//      //strBuildSln.find_replace("/", "\\");
//
//      //pathDeployment = pathBuildFolder / "operating_system/operating_system-windows/deployment/deployment.txt";
//
//      //directory_system()->change_current(pathBuildFolder);
//
//      ////string strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";
//
//      ////file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);
//
//      ////file_system()->put_contents(m_straLine2, )
//
//      ////acmenode()->command_system(pacmedirectory->system() / "build.bat"
//
//      //::array < task > taska;
//
//      //::string strProgramFiles = node()->get_environment_variable("ProgramFiles");
//      //
//      //taska.add(
//      //   {
//      //      "Clean Debug|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"Debug|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean Release|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"Release|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean StaticDebug|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"StaticDebug|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean StaticRelease|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"StaticRelease|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean Debug|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"Debug|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean Release|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"Release|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean StaticDebug|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"StaticDebug|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Clean StaticRelease|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Clean \"StaticRelease|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build Debug|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"Debug|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build Release|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"Release|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build StaticDebug|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"StaticDebug|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build StaticRelease|x64",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"StaticRelease|x64\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build Debug|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"Debug|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build Release|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"Release|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build StaticDebug|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"StaticDebug|Win32\""
//      //   });
//
//      //taska.add(
//      //   {
//      //      "Build StaticRelease|Win32",
//      //      "cmd /c devenv \"" + strBuildSln + "\" /Build \"StaticRelease|Win32\""
//      //   });
//
//      //taska.add(
//      //     {
//      //      "Compress",
//      //      "Compress"
//      //   });
//
//      ////straCommand.add("\"" +strProgramFiles+ "\\Git\\bin\\bash.exe\" -c package");
//      ////straLabel.add("007_package");
//
//      ////auto plabel = straLabel.begin();
//
//      //::file_pointer pfileLog;
//
//      //trace_function functionTrace = [&](auto etracelevel, auto& str)
//      //{
//
//      //   {
//
//      //      _synchronous_lock synchronouslock(m_pmutexLines);
//
//      //      m_straLine2.append_formatf("%c: %s\n", trace_level_letter(etracelevel), str.c_str());
//
//      //   }
//
//      //   std_inline_log()(etracelevel, str);
//
//      //   pfileLog->write(str + "\r\n");
//
//      //};
//
//      //functionTrace.m_timeTimeout = 1_hour;
//
//      //::string strSerial;
//
//      //int iSerial = 1;
//
//      //for (auto & command : commanda)
//      //{
//
//      //   strSerial.formatf("%02d", iSerial);
//
//      //   auto strLabel = command.m_strLabel;
//
//      //   ::string strTitle;
//      //   
//      //   strTitle = strSerial + "_third_" + strLabel;
//
//      //   m_pimpactinterface->set_topic_text(strTitle);
//
//      //   auto strLogName = strTitle;
//      //     
//      //   strLogName.find_replace(" ", "_");
//
//      //   strLogName.find_replace("|", "_");
//
//      //   auto strCommand = command.m_strCommand;
//
//      //   int iExitCode = 0;
//
//      //   pfileLog = file()->get_writer(m_pathBuildFolder / "time-windows" / (strFileNameTimeBuild + "_log") / (strLogName + ".txt"), ::file::e_open_share_deny_none);
//
//      //   m_timeTopicStart.Now();
//
//      //   if (strCommand == "Compress")
//      //   {
//
//      //      directory_system()->change_current("C:\\operating_system\\");
//
//      //      iExitCode = node()->command_system("\"C:\\operating_system\\tool-windows\\bin\\zip\" -r \"C:\\store\\windows\\storage-windows.zip\" storage-windows", functionTrace);
//
//      //   }
//      //   else
//      //   {
//
//      //      iExitCode = node()->command_system(command.m_strCommand, functionTrace);
//
//      //   }
//
//      //   auto elapsed = m_timeTopicStart.elapsed();
//
//      //   if (iExitCode == 0)
//      //   {
//
//      //      m_itemtimeaSummary.insert_at(0, { "✓ " + strLabel, elapsed } );
//
//      //   }
//      //   else
//      //   {
//
//      //      m_itemtimeaSummary.insert_at(0, { "✗ " + strLabel, elapsed } );
//
//      //   }
//
//      //   iSerial++;
//
//      //}
//
//      ////file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);
//
//      ////string strCmd = "cmd /c \"" + (pacmedirectory->system() / "build.bat") + "\"";
//
//      ////string strOutput;
//
//      ////string strError;
//
//      ////int iExitCode = 0;
//
//      //
//
//   }


//   void integration::integrate_macos_openssl(::coding::item* pitem)
//   {
//
//      integrate_macos_parallels(e_task_openssl, pitem);
//
//   //   m_pathBuildFolder = "C:\\port\\openssl\\" + datetime()->date_time_text_for_file_with_no_spaces();
//
//   //   ::file::path pathBuildFolder = m_pathBuildFolder;
//
//   //   ::file::path pathOperatingSystemFolder;
//
//   //   pathOperatingSystemFolder = pathBuildFolder / "operating_system/operating_system-windows";
//
//   //   auto pacmedirectory = directory_system();
//
//   //   auto pacmefile = file_system();
//
//   //   pacmedirectory->create(pathBuildFolder);
//
//   //   pacmedirectory->change_current(pathBuildFolder);
//
//   //   ::file::path pathDeploymentTemplate;
//
//   //   pathDeploymentTemplate = pathOperatingSystemFolder / "deployment/deployment.txt";
//
//   //   string strFileName;
//
//   //   //string strProjectName;
//
//   //   string strReleaseDot;
//
//   //   string strReleaseComma;
//
//   //   string strReleaseDateTime;
//
//   //   string strFileNameTimeBuild;
//
//   //   strFileName = "ca2";
//
//   //   //strProjectName = "ca2";
//
//   //   auto pdatetime = datetime();
//
//   //   strReleaseDot = pdatetime->format("%Y.%m%d.%H%M.%S", m_timeBuild);
//
//   //   strReleaseComma = pdatetime->format("%Y,%m%d,%H%M,%S", m_timeBuild);
//
//   //   strReleaseDateTime = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);
//
//   //   strFileNameTimeBuild = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);
//
//   //   ::file::path pathDeployment;
//
//   //   pathDeployment = pathOperatingSystemFolder / ("deployment/deployment" + strFileNameTimeBuild + ".txt");
//
//   //   ::file::path pathDeploymentRcTemplate;
//
//   //   pathDeploymentRcTemplate = pathOperatingSystemFolder / "deployment/deployment_rc.txt";
//
//   //   auto strDeploymentRcTemplate = pacmefile->as_string(pathDeploymentTemplate);
//
//   //   strDeploymentRcTemplate.find_replace("%FILENAME%", strFileName);
//   //   //strDeploymentRcTemplate.find_replace("%PROJECTNAME%", strProjectName);
//   //   strDeploymentRcTemplate.find_replace("%RELEASEDOT%", strReleaseDot);
//   //   strDeploymentRcTemplate.find_replace("%RELEASECOMMA%", strReleaseComma);
//   //   strDeploymentRcTemplate.find_replace("%RELEASEDATETIME%", strReleaseDateTime);
//
//   //   pacmefile->put_contents(pathDeployment, strDeploymentRcTemplate);
//
//   //   pacmefile->copy(pathDeploymentRcTemplate, pathDeployment, true);
//
//   //   string strBuildSln;
//
//   //   strBuildSln = m_pathBuildFolder / "solution-windows/third-all.sln";
//
//   //   strBuildSln.find_replace("/", "\\");
//
//   //   pathDeployment = pathBuildFolder / "operating_system/operating_system-windows/deployment/deployment.txt";
//
//   //   directory_system()->change_current(pathBuildFolder);
//
//   //   //string strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";
//
//   //   //file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);
//
//   //   //file_system()->put_contents(m_straLine2, )
//
//   //   //acmenode()->command_system(pacmedirectory->system() / "build.bat"
//
//   //   ::array < label_command_task > commanda;
//
//   //   ::string strProgramFiles = node()->get_environment_variable("ProgramFiles");
//
//   //   enum_task etaskGroup = ::coding::e_task_openssl;
//
//   //   m_pimpactinterface->on_start_task_group(etaskGroup);
//
//   //   commanda.add(
//   //      {
//   //         "OpenSSL",
//   //         "application_build_helper openssl Win32 Debug",
//   //         e_task_openssl_win32_debug,
//   //      });
//
//   //   commanda.add(
//   //      {
//   //         "OpenSSL",
//   //         "application_build_helper openssl Win32 Release",
//   //         e_task_openssl_win32_release,
//   //      });
//
//   //   commanda.add(
//   //      {
//   //         "OpenSSL",
//   //         "application_build_helper openssl Win32 Static Debug",
//   //         e_task_openssl_win32_static_debug,
//   //      });
//
//   //   commanda.add(
//   //      {
//   //         "OpenSSL",
//   //         "application_build_helper openssl Win32 Static Debug",
//   //         e_task_openssl_win32_debug,
//   //      });
//
//   //   commanda.add(
//   //      {
//   //         "OpenSSL",
//   //         "application_build_helper openssl Win32 Debug",
//   //         e_task_openssl_win32_debug,
//   //      });
//
//   //   //straCommand.add("\"" +strProgramFiles+ "\\Git\\bin\\bash.exe\" -c package");
//   //   //straLabel.add("007_package");
//
//   //   //auto plabel = straLabel.begin();
//
//   //   ::file_pointer pfileLog;
//
//   //   //trace_function functionTrace = [&](auto etracelevel, auto& str)
//   //   //   {
//
//   //   //      {
//
//   //   //         _synchronous_lock synchronouslock(m_pmutexLines);
//
//   //   //         m_straLine2.append_formatf("%c: %s\n", trace_level_letter(etracelevel), str.c_str());
//
//   //   //      }
//
//   //   //      std_inline_log()(etracelevel, str);
//
//   //   //      pfileLog->write(str + "\r\n");
//
//   //   //   };
//   //   trace_function functionTrace = [ploginterface, pfileLog](auto etracelevel, auto& str)
//   //      {
//
//   //         /*if (defer_status(0, "Preparing to build", s))
//   //         {
//
//   //            ploginterface->m_strTopic2 = "Preparing to build " + ploginterface->m_strStage + "...";
//
//   //         }
//   //         else if (defer_status(1, "Downloading", s))
//   //         {
//
//   //            ploginterface->m_strTopic2 = "Downloading " + ploginterface->m_strStage + "...";
//
//   //         }
//   //         else if (defer_status(2, "Configuring"))
//   //         {
//
//   //            ploginterface->m_strTopic2 = "Configuring " + ploginterface->m_strStage + "...";
//
//   //         }
//   //         else if (defer_status(3, "Building"))
//   //         {
//
//   //            ploginterface->m_strTopic2 = "Building " + ploginterface->m_strStage + "...";
//
//   //         }
//   //         else if (defer_status(3, "Finishing"))
//   //         {
//
//   //            ploginterface->m_strTopic2 = "Finishing " + ploginterface->m_strStage + "...";
//
//   //         }*/
//
//   //         ploginterface->on_trace(etracelevel, str);
//
//
//   //         //std_inline_log()(etracelevel, str);
//
//   //         pfileLog->write(str + "\r\n");
//
//   //      };
//
//   //   {
//
//   //      _synchronous_lock synchronouslock(ploginterface->synchronization());
//
//   //      ploginterface->m_strTopic = task.m_strLabel;
//
//   //      ploginterface->m_strTopic2 = "Starting...";
//
//   //   }
//
//   //   functionTrace.m_timeTimeout = 2_hour;
//
//   //   try
//   //   {
//
//   //      iExitCode = node()->command_system(task.m_strCommand + strParallelization, functionTrace);
//
//   //   }
//   //   catch (...)
//   //   {
//
//   //   }
//
//   //   auto elapsed = m_timeTopicStart.elapsed();
//
//   //   {
//
//   //      _synchronous_lock synchronouslock(ploginterface->synchronization());
//
//   //      if (iExitCode == 0)
//   //      {
//
//   //         m_itemtimeaSummary.insert_at(0, { "✓ " + strLabel, elapsed });
//
//   //         ploginterface->m_strTopic2 = "Completed Successfully!!";
//
//   //         m_iFFMPEGOk++;
//
//   //      }
//   //      else
//   //      {
//
//   //         m_itemtimeaSummary.insert_at(0, { "✗ " + strLabel, elapsed });
//
//   //         ploginterface->m_strTopic2 = "Failed with exit code " + ::string_from(iExitCode);
//
//   //         m_iFFMPEGOk = 0;
//
//   //      }
//
//   //      ploginterface->m_straLog.add(ploginterface->m_strTopic2);
//
//   //   }
//
//   //   {
//
//   //      _synchronous_lock synchronouslock(m_pimpactinterface->synchronization());
//
//   //      if (iExitCode == 0)
//   //      {
//
//   //         m_iFFMPEGOk++;
//
//   //      }
//   //      else
//   //      {
//
//   //         m_iFFMPEGNok++;
//
//   //      }
//
//   //      m_iTaskCount--;
//
//   //      if (m_iTaskCount == 0)
//   //      {
//
//   //         if (m_iFFMPEGOk == 8)
//   //         {
//
//   //            m_straLine2.add("All FFMPEG Platforms and Configuration Built Successfully!!");
//
//   //         }
//   //         else if (m_iFFMPEGNok == 8)
//   //         {
//
//   //            m_straLine2.add("All FFMPEG Platforms and Configuration Failed to Build!");
//
//   //         }
//   //         else
//   //         {
//
//   //            m_pimpactinterface->on_lines_change();
//
//   //         }
//
//   //      }
//
//
//   //   }
//
//   //});
//
//   }


//   void integration::integrate_macos_ffmpeg(::coding::item* pitem)
//   {
//
//      integrate_macos_parallels(e_task_ffmpeg, pitem);
//
//      //m_pathBuildFolder = "C:\\port\\ffmpeg\\" + datetime()->date_time_text_for_file_with_no_spaces();
//
//      //::file::path pathBuildFolder = m_pathBuildFolder;
//
//      //auto pacmedirectory = directory_system();
//
//      //auto pacmefile = file_system();
//
//      //pacmedirectory->create(pathBuildFolder);
//
//      //pacmedirectory->change_current(pathBuildFolder);
//
//      //string strFileName;
//
//      //string strReleaseDot;
//
//      //string strReleaseComma;
//
//      //string strReleaseDateTime;
//
//      //string strFileNameTimeBuild;
//
//      //strFileName = "ca2";
//
//      //::array < label_command_task> commandaTaska;
//      //m_iTaskCount = 8;
//      //m_iFFMPEGOk = 0;
//      //m_iFFMPEGNok = 0;
//
//      //::string strParallelization;
//
//      //auto iProcessorCount = node()->get_processor_count();
//
//      //int iParallelization = -1;
//
//      //if (iProcessorCount >= m_iTaskCount)
//      //{
//
//      //   iParallelization = iProcessorCount / m_iTaskCount;
//
//      //}
//      //
//      //if (iParallelization >= 2)
//      //{
//
//      //   strParallelization.formatf(" --parallelization=%d", iParallelization);
//
//      //}
//
//      //enum_task etaskGroup = ::coding::e_task_ffmpeg;
//
//      //m_pimpactinterface->on_start_task_group(etaskGroup);
//
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" Win32 Debug",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " Win32 Debug",
//      //      e_task_ffmpeg_win32_debug
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" Win32 Release",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " Win32 Release",
//      //      e_task_ffmpeg_win32_release
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" Win32 StaticDebug",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " Win32 StaticDebug",
//      //      e_task_ffmpeg_win32_static_debug
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" Win32 StaticRelease",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " Win32 StaticRelease",
//      //      e_task_ffmpeg_win32_static_release
//      //   });
//
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" x64 Debug",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " x64 Debug",
//      //      e_task_ffmpeg_x64_debug
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" x64 Release",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " x64 Release",
//      //      e_task_ffmpeg_x64_release
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" x64 StaticDebug",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " x64 StaticDebug",
//      //      e_task_ffmpeg_x64_static_debug
//      //   });
//      //commandaTaska.add(
//      //   {
//      //      ptaskgroup->m_strName+" x64 StaticRelease",
//      //      strApplicationBuildHelper + ptaskgroup->m_strId + " x64 StaticRelease",
//      //      e_task_ffmpeg_x64_static_release
//      //   });
//
//      //m_timeTopicStart.Now();
//
//      //for (enum_task etaskOrdinal = e_task_ordinal_0; etaskOrdinal <= e_task_ordinal_7; etaskOrdinal = (enum_task)(etaskOrdinal + 1))
//      //{
//
//      //   auto task = commandaTaska[etaskOrdinal];
//
//      //   fork([this, task, strParallelization, etaskOrdinal]()
//      //      {
//
//      //         ::file_pointer pfileLog;
//
//      //         auto ploginterface = task_log(task.m_etask);
//
//      //         ::string strTitle;
//
//      //         ::string strTask;
//
//      //         strTask.formatf("%02d", etaskOrdinal);
//
//      //         auto strLabel = task.m_strLabel;
//
//      //         strTitle = strTask + "_ffmpeg_" + strLabel;
//
//      //         ploginterface->m_strTopic = strTitle;
//
//      //         auto strLogName = strTitle;
//
//      //         strLogName.find_replace(" ", "_");
//
//      //         strLogName.find_replace("|", "_");
//
//      //         auto strCommand = task.m_strCommand;
//
//      //         int iExitCode = 0;
//
//      //         ploginterface->m_eindexa.clear();
//      //         ploginterface->m_eindexa.add(::coding::e_index_preparing);
//      //         ploginterface->m_eindexa.add(::coding::e_index_downloading);
//      //         ploginterface->m_eindexa.add(::coding::e_index_configuring);
//      //         ploginterface->m_eindexa.add(::coding::e_index_building);
//      //         ploginterface->m_eindexa.add(::coding::e_index_finishing);
//
//      //         ploginterface->m_iIndex = -1;
//
//      //         ploginterface->m_straStage.clear();
//      //         ploginterface->m_straStage.add("x264");
//      //         ploginterface->m_straStage.add("x265");
//      //         ploginterface->m_straStage.add("FFMPEG");
//
//      //         ploginterface->m_iStage = 0;
//
//      //         /*auto defer_status = [ploginterface](auto iStatus, auto str, auto line)
//      //            {
//
//      //            };*/
//
//      //         pfileLog = file()->get_writer(m_pathBuildFolder / "time-windows" / (strLabel + "_log") / (strLogName + ".txt"), ::file::e_open_share_deny_none);
//
//      //         trace_function functionTrace = [ploginterface, pfileLog](auto etracelevel, auto& str)
//      //            {
//
//      //               /*if (defer_status(0, "Preparing to build", s))
//      //               {
//
//      //                  ploginterface->m_strTopic2 = "Preparing to build " + ploginterface->m_strStage + "...";
//
//      //               }
//      //               else if (defer_status(1, "Downloading", s))
//      //               {
//
//      //                  ploginterface->m_strTopic2 = "Downloading " + ploginterface->m_strStage + "...";
//
//      //               }
//      //               else if (defer_status(2, "Configuring"))
//      //               {
//
//      //                  ploginterface->m_strTopic2 = "Configuring " + ploginterface->m_strStage + "...";
//
//      //               }
//      //               else if (defer_status(3, "Building"))
//      //               {
//
//      //                  ploginterface->m_strTopic2 = "Building " + ploginterface->m_strStage + "...";
//
//      //               }
//      //               else if (defer_status(3, "Finishing"))
//      //               {
//
//      //                  ploginterface->m_strTopic2 = "Finishing " + ploginterface->m_strStage + "...";
//
//      //               }*/
//
//      //               ploginterface->on_trace(etracelevel, str);
//
//
//      //               //std_inline_log()(etracelevel, str);
//
//      //               pfileLog->write(str + "\r\n");
//
//      //            };
//
//      //         {
//
//      //            _synchronous_lock synchronouslock(ploginterface->synchronization());
//
//      //            ploginterface->m_strTopic = task.m_strLabel;
//
//      //            ploginterface->m_strTopic2 = "Starting...";
//
//      //         }
//
//      //         functionTrace.m_timeTimeout = 2_hour;
//
//      //         try
//      //         {
//
//      //            iExitCode = node()->command_system(task.m_strCommand + strParallelization, functionTrace);
//
//      //         }
//      //         catch (...)
//      //         {
//
//      //         }
//
//      //         auto elapsed = m_timeTopicStart.elapsed();
//
//      //         {
//
//      //            _synchronous_lock synchronouslock(ploginterface->synchronization());
//
//      //            if (iExitCode == 0)
//      //            {
//
//      //               m_itemtimeaSummary.insert_at(0, { "✓ " + strLabel, elapsed });
//
//      //               ploginterface->m_strTopic2 = "Completed Successfully!!";
//
//      //               m_iFFMPEGOk++;
//
//      //            }
//      //            else
//      //            {
//
//      //               m_itemtimeaSummary.insert_at(0, { "✗ " + strLabel, elapsed });
//
//      //               ploginterface->m_strTopic2 = "Failed with exit code " + ::string_from(iExitCode);
//
//      //               m_iFFMPEGOk = 0;
//
//      //            }
//
//      //            ploginterface->m_straLog.add(ploginterface->m_strTopic2);
//
//      //         }
//
//      //         {
//
//      //            _synchronous_lock synchronouslock(m_pimpactinterface->synchronization());
//
//      //            if (iExitCode == 0)
//      //            {
//
//      //               m_iFFMPEGOk++;
//
//      //            }
//      //            else
//      //            {
//
//      //               m_iFFMPEGNok++;
//
//      //            }
//
//      //            m_iTaskCount--;
//
//      //            if (m_iTaskCount == 0)
//      //            {
//
//      //               if (m_iFFMPEGOk == 8)
//      //               {
//
//      //                  m_straLine2.add("All FFMPEG Platforms and Configuration Built Successfully!!");
//
//      //               }
//      //               else if (m_iFFMPEGNok == 8)
//      //               {
//
//      //                  m_straLine2.add("All FFMPEG Platforms and Configuration Failed to Build!");
//
//      //               }
//      //               else
//      //               {
//
//      //                  m_pimpactinterface->on_lines_change();
//
//      //               }
//
//      //            }
//
//
//      //         }
//
//
//      //      });
//
//
//
//      //}
//
//      //while (m_iTaskCount > 0)
//      //{
//
//      //   preempt(1_s);
//
//      //}
//
//      ////file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);
//
//      ////string strCmd = "cmd /c \"" + (pacmedirectory->system() / "build.bat") + "\"";
//
//      ////string strOutput;
//
//      ////string strError;
//
//      ////int iExitCode = 0;
//
//
//
//   }


   void integration::on_start_task_group(enum_task etaskGroup)
   {

      m_etaskGroupRunning = etaskGroup;

      m_pimpactinterface->on_start_task_group(etaskGroup);

      if (etaskGroup == e_task_openssl)
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


//   void integration::integrate_macos_parallels(enum_task etaskGroup, ::coding::item* pitem)
//   {
//
//      auto strReleaseTimeNoSpaces = m_strIntegration;
//
//      strReleaseTimeNoSpaces.find_replace(" ", "_");
//
//      auto& ptaskgroup = pitem->m_ptaskgroup;
//         
//      ptaskgroup = m_taskgroup[etaskGroup];
//
//      ::string strParallelization;
//
//
//
//      ::string strNonInteractive;
//
//      strNonInteractive = " --non-interactive";
//
//      ptaskgroup->m_pathBuildFolder = "C:/port";
//      ptaskgroup->m_pathBuildFolder /= ptaskgroup->m_strId;
//      ptaskgroup->m_pathBuildFolder /= strReleaseTimeNoSpaces;
//
//      ::file::path pathBuildFolder = ptaskgroup->m_pathBuildFolder;
//
//      auto pacmedirectory = directory_system();
//
//      auto pacmefile = file_system();
//
//      pacmedirectory->create(pathBuildFolder);
//
//      pacmedirectory->change_current(pathBuildFolder);
//
//      string strFileName;
//
//      string strReleaseDot;
//
//      string strReleaseComma;
//
//      string strReleaseDateTime;
//
//      string strFileNameTimeBuild;
//
//      strFileName = "ca2";
//
//
//      on_start_task_group(etaskGroup);
//
//
//      m_timeTopicStart.Now();
//
//      ptaskgroup->on_start();
//
//      ptaskgroup->m_taskaOk.clear();
//      ptaskgroup->m_taskaNok.clear();
//      ptaskgroup->m_taskaInitialQueue;
//
//      auto iProcessorCount = node()->performance_core_count();
//
//      int iParallelization = -1;
//
//      if (iProcessorCount >= ptaskgroup->task_count())
//      {
//
//         iParallelization = iProcessorCount / ptaskgroup->task_count();
//
//      }
//
//      if (iParallelization >= 2)
//      {
//
//         strParallelization.formatf(" --parallelization=%d", iParallelization);
//
//      }
//      auto& taska = ptaskgroup->m_taska;
//
//      for(auto ptask : taska)
//      {
//
//         if (!m_baTaskOrdinalEnable[ptask->m_etaskOrdinal])
//         {
//
//            ptaskgroup->m_countQueued--;
//
//            continue;
//
//         }
//
//         fork([this, ptask, strParallelization, strNonInteractive]()
//            {
//
//               ::file_pointer pfileLog;
//
//               auto ploginterface = task_log(ptask->etask());
//
//               ::string strTitle;
//
//               ::string strTask;
//
//               strTask.formatf("%02d", ptask->m_etaskOrdinal);
//
//               auto strLabel = ptask->m_strLabel;
//
//               strTitle = strTask + "_ffmpeg_" + strLabel;
//
//               ptask->m_strTopic1 = strTitle;
//
//               auto strLogName = strTitle;
//
//               strLogName.find_replace(" ", "_");
//
//               strLogName.find_replace("|", "_");
//
//               auto strCommand = ptask->m_strCommand;
//
//               int iExitCode = 0;
//
//               //ploginterface->m_eindexa.clear();
//
//               //task_group_indexes(ptask->m_etaskGroup, ploginterface->m_eindexa);
//
//               ploginterface->m_iIndex = -1;
//
//               //ploginterface->m_straStage.clear();
//
//               //task_group_stages(ptask->m_etaskGroup, ploginterface->m_straStage);
//
//               ploginterface->m_iStage = 0;
//
//               /*auto defer_status = [ploginterface](auto iStatus, auto str, auto line)
//                  {
//
//                  };*/
//
//               pfileLog = file()->get_writer(ptask->m_ptaskgroup->m_pathBuildFolder / "time-windows" / (strLabel + "_log") / (strLogName + ".txt"), ::file::e_open_share_deny_none);
//
//               trace_function functionTrace = [ploginterface, pfileLog](auto etracelevel, auto& str, bool bCarriage)
//                  {
//
//                     /*if (defer_status(0, "Preparing to build", s))
//                     {
//
//                        ploginterface->m_strTopic2 = "Preparing to build " + ploginterface->m_strStage + "...";
//
//                     }
//                     else if (defer_status(1, "Downloading", s))
//                     {
//
//                        ploginterface->m_strTopic2 = "Downloading " + ploginterface->m_strStage + "...";
//
//                     }
//                     else if (defer_status(2, "Configuring"))
//                     {
//
//                        ploginterface->m_strTopic2 = "Configuring " + ploginterface->m_strStage + "...";
//
//                     }
//                     else if (defer_status(3, "Building"))
//                     {
//
//                        ploginterface->m_strTopic2 = "Building " + ploginterface->m_strStage + "...";
//
//                     }
//                     else if (defer_status(3, "Finishing"))
//                     {
//
//                        ploginterface->m_strTopic2 = "Finishing " + ploginterface->m_strStage + "...";
//
//                     }*/
//
//                     ploginterface->on_trace(etracelevel, str, bCarriage);
//
//
//                     //std_inline_log()(etracelevel, str);
//
//                     pfileLog->write(str + "\r\n");
//
//                  };
//
//               {
//
//                  _synchronous_lock synchronouslock(ptask->synchronization());
//
//                  ptask->m_strTopic1 = ptask->m_strLabel;
//
//                  ptask->m_strTopic12 = "Starting...";
//
//               }
//
//               functionTrace.m_timeTimeout = 2_hour;
//
//               ptask->on_start();
//
//               try
//               {
//
//                  iExitCode = node()->command_system(
//                     ptask->m_strCommand 
//                        + strParallelization
//                        + strNonInteractive, 
//                     functionTrace,
//                     ptask->m_ptaskgroup->m_pathBuildFolder);
//
//                  // iExitCode = 0;
//
//               }
//               catch (...)
//               {
//
//               }
//
//               ptask->on_finished(iExitCode);
//
//               m_pimpactinterface->on_lines_change();
//
//            });
//
//      }
//
//
//      ptaskgroup->wait_to_complete();
//
//      m_pimpactinterface->on_lines_change();
//
//
//
//
//      //file_system()->put_contents(pacmedirectory->system() / "build.bat", "@call " + strBuildCmd + "\n" + strSh1 + "\n" + strSh2 + "\n" + strSh3 + "\n" + strSh4 + "\n" + strCmd1 + "\n" + strCmd2 + "\n" + strSh10);
//
//      //string strCmd = "cmd /c \"" + (pacmedirectory->system() / "build.bat") + "\"";
//
//      //string strOutput;
//
//      //string strError;
//
//      //int iExitCode = 0;
//
//
//
//   }


//   void integration::_defer_macos_task_group(enum_task etaskGroup, ::pointer < task_group >* pptaskgroup)
//   {
//
//
//      if (pptaskgroup)
//      {
//
//         if (*pptaskgroup)
//         {
//
//            if ((*pptaskgroup)->m_etaskGroup == etaskGroup)
//            {
//
//               return;
//
//            }
//
//         }
//
//      }
//
//      auto ptaskgroup = __allocate_and_initialize<::coding::task_group>(
//         this,
//         etaskGroup,
//         task_group_id(etaskGroup),
//         task_group_name(etaskGroup));
//
//      task_group_indexes(ptaskgroup->m_etaskGroup, ptaskgroup->m_eindexa);
//      task_group_stages(ptaskgroup->m_etaskGroup, ptaskgroup->m_straStage);
//
//      ptaskgroup->m_strTopic1 = ptaskgroup->m_strName;
//
//      if (!sort_of_ok_earth_time_from_international_string(m_strIntegration))
//      {
//
//         throw ::exception(error_wrong_state, "bad integration (bad release date time, please set integration time with integration/handler)");
//
//      }
//
//      ptaskgroup->m_strTopic12 = m_strIntegration;
//      //::string ptaskgroup->m_strId(task_group_id(etaskGroup));
//        // ::string ptaskgroup->m_strName(task_group_name(etaskGroup));
//
//      // scopedstr1 all lower case // ffmpeg openssl
//      // scopedstr2 brandy // FFMPEG OpenSSL
//
//
//      //::pointer_array < ::coding::task> taska;
//      //ptaskgroup->m_iTaskTotalCount = 8;
//      //ptaskgroup->m_iTaskCompletedCount = 0;
//      //ptaskgroup->m_iOk = 0;
//      //ptaskgroup->m_iNok = 0;
//
//
//      //enum_task etaskGroup = ::coding::e_task_ffmpeg;
//
//      auto& taska = ptaskgroup->m_taska;
//
//      //::string_array straOrdinalTask;
//
//      task_group_tasks_ordinals(ptaskgroup->m_etaskGroup, ptaskgroup->m_etaskaOrdinal);
//
//
//      for (auto& etask : ptaskgroup->m_etaskaOrdinal)
//      {
//         //::string str2(scopedstr2);
//         ::string strOrdinalTask = m_straTaskOrdinal[etask];
//         ::string strApplicationBuildHelper("C:\\operating_system\\bin\\application_build_helper");
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " " + strOrdinalTask,
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " " + strOrdinalTask,
//               etask
//            ));
//       /*  taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " Win32 Release",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " Win32 Release",
//               e_task_win32_release
//            ));
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " Win32 StaticDebug",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " Win32 StaticDebug",
//               e_task_win32_static_debug
//            ));
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " Win32 StaticRelease",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " Win32 StaticRelease",
//               e_task_win32_static_release
//            ));
//
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " x64 Debug",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " x64 Debug",
//               e_task_x64_debug
//            ));
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " x64 Release",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " x64 Release",
//               e_task_x64_release
//            ));
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " x64 StaticDebug",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " x64 StaticDebug",
//               e_task_x64_static_debug
//            ));
//         taska.add(
//            __allocate_and_initialize < task>(
//               ptaskgroup,
//               ptaskgroup->m_strName + " x64 StaticRelease",
//               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " x64 StaticRelease",
//               e_task_x64_static_release
//            ));*/
//
//      }
//
//      m_taskgroup[etaskGroup] = ptaskgroup;
//      m_etaskaGroup.add(etaskGroup);
//
//      if (pptaskgroup)
//      {
//
//         *pptaskgroup = ptaskgroup;
//
//      }
//
//   }

void application::defer_task_groups(::coding::integration * pintegration)
{
   
}



   
} // namespace coding




