// From integration code on 2024-05-04 15:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "install.h"
#include "acme/constant/id.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/queue.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "aura/platform/node.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/windowing/windowing.h"

#include "acme_windows_common/_.h"
#include "acme_windows_common/bstring.h"
#include "acme_windows_common/comptr.h"


#include "acme/_operating_system.h"


//#include "acme_windows_common/_.h"


#define boolean win_boolean


//#import <C:\Program Files (x86)\Common Files\microsoft shared\MSEnv\vcproject.dll> raw_interfaces_only named_guids
#import <C:\Program Files (x86)\Common Files\microsoft shared\MSEnv\dte80a.olb> raw_interfaces_only named_guids \
rename("GetObject", "GetObjectA") \
rename("SearchPath", "SearchPathA")
//using namespace EnvDTE;
#import <C:\Program Files (x86)\Common Files\microsoft shared\MSEnv\dte80.olb> raw_interfaces_only named_guids
//using namespace EnvDTE80;

#undef boolean


namespace coding
{

   void visual_studio_select_project(::platform::system* psystem, string str)
   {

      auto purl = psystem->url();

      string strProtocol = ::url::get_protocol(str);

      if (strProtocol == "ca2project")
      {

         string strBase = ::url::get_host(str);

         string strAppId = ::url::get_request_path(str);

         strAppId.begins_eat("/");

         string strQuery = ::url::get_query(str);

         string strMessage;

         strMessage.formatf("protocol: ca2project\nbase: %s\nAppId: %s\nquery: %s\n", strBase, strAppId, strQuery);

         //message_box(strMessage, e_message_box_ok);

         string strParams;

         //strParams.format("\"ca2project\" \"%s\" \"%s\" \"%s\"\n", strBase, strAppId, strQuery);

         string strProj;

         strProj = strAppId;

         string_array stra;

         stra.explode("/", strAppId);

         strProj.case_insensitive_find_replace("-", "_");
         strProj.case_insensitive_find_replace("/", "_");

         //strProj = "..\\..\\..\\" + stra[0] + "\\" + stra[1] + "\\" + stra[1] + ".vcxproj";

         strParams.formatf("\"openvsproject://%s\"", strProj);


         //int iRet = call_sync("C:\\bergedge\\time\\stage\\visual_studio_automation_2017.exe",strParams, "C:\\bergedge\\time\\stage\\", SW_HIDE, 30, 1000, nullptr, 0);


         psystem->fork([=]()
            {
               EnvDTE::_DTE* xxx = nullptr;

               comptr<EnvDTE::_DTE> pDTE;
               CLSID clsid;
               //            CLSID clsid2;
               CLSIDFromProgID(L"VisualStudio.DTE.16.0", &clsid);
               comptr<IUnknown> punk;
               // Get a running instance of Visual Studio.
               HRESULT hr = GetActiveObject(clsid, nullptr, &punk);

               if (FAILED(hr))
               {
                  string str = "error1: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  return;

               }

               punk.as(pDTE);
               comptr<EnvDTE::_Solution> pSolution;
               hr = pDTE->get_Solution(&pSolution);
               if (FAILED(hr))
               {
                  string str = "error2: result = " + as_string(hr);
                  //               MessageBox(nullptr, str, str, e_message_box_icon_information);

                  return;

               }
               comptr<EnvDTE::SolutionBuild> pSolutionBuild;
               hr = pSolution->get_SolutionBuild(&pSolutionBuild);
               if (FAILED(hr))
               {
                  string str = "error3: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  return;

               }
               comptr<EnvDTE::Properties> pProperties;
               hr = pSolution->get_Properties(&pProperties);
               if (FAILED(hr))
               {
                  string str = "error4: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  return;

               }

               VARIANT payload;
               //VariantClear(&payload);
               //payload.vt = VT_BSTR;
               //payload.bstrVal = strProj.AllocSysString();
               //hr = pSolutionBuild->get_StartupProjects(&payload);

               // TODO: Add your dispatch handler integration_code here
               //USES_CONVERSION;
               //Initialize the VARIANT (Type is SAFEARRAY of byte)
               VariantInit(&payload);
               payload.vt = VT_ARRAY | VT_BSTR;
               int nBufferSize = 1;
               // Define a safe array of nCnt Item and Starting index as 0
               SAFEARRAYBOUND safeBounds = { (ULONG)nBufferSize, 0 };

               //Create the Safe Array passing it the bounds
               SAFEARRAY* pSafeArray = SafeArrayCreate(VT_BSTR, 1, &safeBounds);
               //Get a pointer to the array data, This actually increments the arrays lock count)
               BSTR* p = nullptr;
               SafeArrayAccessData(pSafeArray, (void**)&p);

               p[0] = ::bstring::allocate_string(strProj);
               // We are done wth populating the array Decrement the lock
               SafeArrayUnaccessData(pSafeArray);
               payload.parray = pSafeArray;
               /// hr = pSolutionBuild->put_StartupProjects(payload);
               //VARIANT var2;
               //VariantClear(&var2);
               //hr = pSolutionBuild->get_StartupProjects(&var2);

               VARIANT varIndex;
               VariantInit(&varIndex);
               varIndex.vt = VT_BSTR;
               string strStartupProject("StartupProject");
               varIndex.bstrVal = bstring::allocate_string(strStartupProject);
               comptr<EnvDTE::Property> prop;
               pProperties->Item(varIndex, &prop);
               VARIANT varValue;
               //prop->get_Value(&varValue);
               VariantInit(&varValue);
               varValue.vt = VT_BSTR;
               varValue.bstrVal = bstring::allocate_string(strProj);
               prop->put_Value(varValue);


               //          string str = "result = " + as_string(hr) + "::" + strProj;
               //MessageBox(nullptr, str, str, e_message_box_icon_information);
   //            open_string(str);
               //output_debug_string(str);

            });



      }
   }



   void visual_studio_select_configuration_platform(::platform::system* psystem, string strConfigurationParam, string strPlatformParam)
   {

      psystem->fork([=]()
         {
            EnvDTE::_DTE* xxx = nullptr;

            comptr<EnvDTE::_DTE> pDTE;
            CLSID clsid;
            //            CLSID clsid2;
            CLSIDFromProgID(L"VisualStudio.DTE.16.0", &clsid);
            comptr<IUnknown> punk;
            // Get a running instance of Visual Studio.
            HRESULT hr = GetActiveObject(clsid, nullptr, &punk);

            if (FAILED(hr))
            {
               string str = "error1: result = " + as_string(hr);
               //MessageBox(nullptr, str, str, e_message_box_icon_information);

               return;

            }

            punk.as(pDTE);
            comptr<EnvDTE::_Solution> pSolution;
            hr = pDTE->get_Solution(&pSolution);
            if (FAILED(hr))
            {
               string str = "error2: result = " + as_string(hr);
               //               MessageBox(nullptr, str, str, e_message_box_icon_information);

               return;

            }

            comptr<EnvDTE::SolutionBuild> pSolutionBuild;
            hr = pSolution->get_SolutionBuild(&pSolutionBuild);
            if (FAILED(hr))
            {
               string str = "error3: result = " + as_string(hr);
               //MessageBox(nullptr, str, str, e_message_box_icon_information);

               return;

            }

            comptr<EnvDTE::SolutionConfigurations> pSolutionsConfigurations;
            hr = pSolutionBuild->get_SolutionConfigurations(&pSolutionsConfigurations);
            if (FAILED(hr))
            {
               string str = "error4: result = " + as_string(hr);
               //MessageBox(nullptr, str, str, e_message_box_icon_information);

               return;

            }

            long lCount = 0;

            hr = pSolutionsConfigurations->get_Count(&lCount);
            if (FAILED(hr) || lCount <= 0)
            {
               string str = "error4: result = " + as_string(hr);
               //MessageBox(nullptr, str, str, e_message_box_icon_information);

               return;

            }

            VARIANT varItem;

            varItem.vt = VT_I4;

            for (varItem.intVal = 0; varItem.intVal < lCount; varItem.intVal++)
            {
               comptr<EnvDTE::SolutionConfiguration> pConfiguration;
               hr = pSolutionsConfigurations->Item(varItem, &pConfiguration);
               if (FAILED(hr))
               {
                  string str = "error4: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  continue;

               }

               comptr<::EnvDTE80::SolutionConfiguration2> pConfiguration2;
               hr = pConfiguration.as(pConfiguration2);
               if (FAILED(hr))
               {
                  string str = "error4: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  continue;

               }

               bstring bstrConfiguration;
               hr = pConfiguration2->get_Name(&bstrConfiguration.m_bstr);
               if (FAILED(hr))
               {
                  string str = "error4: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  continue;

               }
               string strConfiguration(bstrConfiguration.m_bstr);
               if (strConfiguration.case_insensitive_order(strConfigurationParam) != 0)
               {

                  continue;

               }
               bstring bstrPlatform;
               hr = pConfiguration2->get_PlatformName(&bstrPlatform.m_bstr);
               if (FAILED(hr))
               {
                  string str = "error4: result = " + as_string(hr);
                  //MessageBox(nullptr, str, str, e_message_box_icon_information);

                  continue;

               }
               string strPlatform(bstrPlatform.m_bstr);
               if (strPlatform.case_insensitive_order(strPlatformParam) != 0)
               {

                  continue;

               }
               pConfiguration->Activate();
               break;


            }


         });

   }



   //int application::unix_shell_command(const ::scoped_string& scopedstrCommand)
   //{

   //   try
   //   {

   //      ::string strGitBash;

   //      strGitBash = "C:\\Program Files\\Git\\bin\\bash.exe";

   //      ::string strCommandInner;

   //      strCommandInner = scopedstrCommand.c_str();

   //      strCommandInner.find_replace("\"", "\\\"");

   //      ::string strCommand;

   //      strCommand.format("\"%s\" -c \"%s\"", strGitBash.c_str(), strCommandInner.c_str());

   //      auto iExitCode = acmenode()->command_system(strCommand);

   //      return iExitCode;

   //   }
   //   catch (...)
   //   {

   //   }

   //   return -1;

   //}


   void install::install_visual_studio()
   {

      //set_status("Installing...");

      //auto transferprogressfunction = [this](double rate, filesize done, filesize total)
      //   {

      //      if (total == 0 || total == (filesize)-1)
      //      {

      //         ::string str2;

      //         str2.formatf("Downloading Visual Studio Installer (%lld).", done);

      //         set_visual_studio_status2(str2);

      //      }
      //      else
      //      {

      //         ::string str2;

      //         str2.formatf("Downloading Visual Studio Installer %0.1f%% (%lld of %lld).", rate * 100.0, done, total);

      //         set_visual_studio_status2(str2);

      //      }

      //      //m_pimpact->set_need_redraw();

      //      //m_pimpact->post_redraw();

      //   };

      //auto path = download("vs_community", transferprogressfunction);

      //download();

      //for (::collection::index i = 0; i < 300; i++)
      //{

      //   if (is_git_installed())
      //   {

      //      break;

      //   }

      //   task_sleep(1_s);

      //   m_strVisualStudioInstallationStatus2 = "Waiting for git-scm to install...";

      //}

      //if (!is_git_installed())
      //{

      //   return;

      //}

      m_papp->queue(id_system_install)->sync([this]()
         {

            try
            {


               set_status2("Starting Installer");

               //m_pimpact->set_need_redraw();

               //m_pimpact->post_redraw();

               //task_sleep(1_s);

            //      m_bWasInstallingVisualStudio = true;

               string strCommand = "-p --add Microsoft.VisualStudio.Workload.NativeDesktop;includeRecommended";

               property_set set;

               auto pprocess = createø < ::operating_system::process >();

               pprocess->create_child_process("\"" + m_path + "\" " + strCommand);

               class time tickStart;

               tickStart.Now();

               bool bLaunched = false;

               while (!pprocess->has_exited())
               {

                  task_sleep(1_s);

                  if (!bLaunched)
                  {

                     if (has_visible_top_level_window_named_visual_studio_installer())
                     {

                        bLaunched = true;

                        tickStart.Now();

                     }

                  }

                  if (bLaunched)
                  {

                     if (tickStart.elapsed() > 2_min)
                     {

                        set_status2("Visual Studio Installer Bootstrap Process is taking long to complete.\nYou can try to cancel it and stop installation. Code!! will restart it some more times.");

                        //m_pimpact->set_need_redraw();

                        //m_pimpact->post_redraw();

                     }
                     else
                     {

                        set_status2("Setting up Visual Studio Installer");

                        //m_pimpact->set_need_redraw();

                        //m_pimpact->post_redraw();

                     }

                  }
                  else
                  {

                     if (tickStart.elapsed() > 1_min)
                     {

                        set_status2("Visual Studio Installer Bootstrap Process is taking long to start.\nYou can try to terminate it at Task Manager. Code!! will restart it some more times.");

                        //m_pimpact->set_need_redraw();

                        //m_pimpact->post_redraw();

                     }
                     else
                     {

                        set_status2("Starting Visual Studio Installer Bootstrap");

                        //m_pimpact->set_need_redraw();

                        //m_pimpact->post_redraw();

                     }

                  }

               }

               if (pprocess->m_exitstatus.m_iExitCode != 0)
               {

                  return;

               }

               bool bTimeout = set.is_true("timed_out");

               set_status("Installing Visual Studio");

               class time tickStartWaiting;

               tickStartWaiting.Now();
               bool bVsInstallerEverRun = false;

               ::collection::count cFailureGetInstallerName = 0;

               ::collection::count cTopCount = 0;

               while (!is_installed(false) && cTopCount < 2)
               {

                  while (true)
                  {

                     task_sleep(1_s);

                     if (tickStartWaiting.elapsed() > 1_hour)
                     {

                        break;

                     }

                     if (has_visible_top_level_window_named_visual_studio_installer())
                     {

                        bVsInstallerEverRun = true;

                        cFailureGetInstallerName = 0;

                        cTopCount = 0;

                     }
                     else
                     {

                        cFailureGetInstallerName++;

                        if (cFailureGetInstallerName > 10)
                        {

                           break;

                        }

                     }

                  }

                  cTopCount++;

               }

            }
            catch (...)
            {


            }

            {

               auto pathSourceFolder = m_papp->cloud_folder() / "box/.vsix";

               auto pathSourceIndex = pathSourceFolder / "index.txt";

               auto pathSourceIndexProcessed = application()->defer_process_path(pathSourceIndex);

               node()->root_execute_sync("C:\\operating_system\\bin\\application_build_helper.exe", "--install-vsix-from-folder-listing=" + pathSourceIndexProcessed);

            }

            on_finished();

         }, 4_hour);

   }



   bool install::has_visible_top_level_window_named_visual_studio_installer()
   {

      auto pwindowing = system()->windowing();

      return pwindowing->_visible_top_level_contains_name("Visual Studio Installer");

   }


   bool install::has_visible_top_level_window_named_simple__microsoft_visual_studio()
   {

      string_array stra;

      stra.add("simple");

      stra.add("Visual Studio");

      auto pwindowing = system()->windowing();

      return pwindowing->_visible_top_level_contains_all_names(stra);

   }


   bool install::get_debug_project_enabled()
   {

      if (!has_visible_top_level_window_named_simple__microsoft_visual_studio())
      {

         return false;

      }

      return true;

   }


} // namespace coding



void edge_installed()
{

   MessageBoxW(NULL, L"Edge selected", L"Edge selected", MB_OK);

}