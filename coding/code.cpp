//
// Created by camilo on 2024-06-05 16:32 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "code.h"
//#include "code_impact.h"
#include "install.h"
#include "option.h"
//#include "code_option_form_handler.h"
//#include "code_install_form_handler.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace coding
{


    code::code()
    {


    }


    code::~code()
    {


    }


    void code::set_main_status1(const ::scoped_string& scopedstr)
    {

        m_strMainStatus= scopedstr;

        // if (m_pimpact && m_pimpact->m_pstillMainStatus1)
        // {
        //
        //     m_pimpact->user_post([this]()
        //     {
        //
        //         m_pimpact->m_pstillMainStatus1->set_window_text(m_strMainStatus);
        //
        //         m_pimpact->m_bNeedLayout = true;
        //
        //         m_pimpact->set_need_layout();
        //
        //         m_pimpact->set_need_redraw();
        //
        //         m_pimpact->post_redraw();
        //
        //     });
        //
        // }

    }


    ::coding::enum_install code::get_next(::coding::enum_install einstall)
    {

        if(m_einstalla.is_empty())
        {

            return ::coding::e_install_none;

        }

        auto iFind = m_einstalla.find_first(einstall);

        if(iFind < 0 || iFind >= m_einstalla.get_upper_bound())
        {

            return m_einstalla[0];

        }

        return m_einstalla[iFind+1];

    }


    void code::defer_sources()
    {

        m_papp->defer_start_installation(::coding::e_install_tool_os);
        m_papp->defer_start_installation(::coding::e_install_repositories);

    }


   void code::setup_coding()
   {

      m_papp->m_bStartingInstallation2 = true;

      //m_papp->defer_release_install();

        for(auto einstall : m_einstalla)
        {


            m_papp->defer_start_installation(einstall);
        }

      //if (m_bInstalling)
      //{

      //   //return ::success_none;

      //   //throw ::exception(::success_started);

      //   return;

      //}

      //scoped_restore(m_bInstalling);

      //m_bInstalling = true;

      //if (!defer_first_stage())
      //{

      //   m_bFirstStageOk = false;

      //   return;

      //}


      //if (!defer_relocate_code_exe())
      //{

      //   throw ::exception(error_failed);

      //}

      //if (!defer_application_build_helper())
      //{

      //   throw ::exception(error_failed);

      //}

      //defer_initial_ambient_setup();

      //acmenode()->unzip_to_folder("C:/op_system", "C:/op_system/storage-windows.zip");
      //return;

      //release_install();

      //return;

// #if defined(WINDOWS)
//
//       ::file::path pathCanonical;
//
//       pathCanonical = "C:/operating_system/bin/code.exe";
//
//       if (!file_system()->module().case_insensitive_equals(pathCanonical))
//       {
//
//          throw ::exception(error_unexpected, "this situation/condition/scenario/case should be handled on application startup");
//
//          return;
//
//       }
//
// #endif
//
//       if (!m_bFirstStageOk)
//       {
//
//          //throw ::exit_exception(this);
//
//          return;
//
//       }
//
//       /* ::acme_windows::registry::key key;
//
//        auto estatus = key._open(HKEY_CURRENT_USER, "Environment");
//
//        if (::failed(estatus))
//        {
//
//           set_finish();
//
//           return estatus;
//
//        }*/
//
//       //string str;
//
//       //if (::failed(key._get("__archive", str)))
//       //{
//
//       //   set_status1("Setting \"archive\" User Environment Variable");
//
//       //   auto psystem = acmesystem();
//
//       //   auto pacmedirectory = psystem->m_pacmedirectory;
//
//       //   ::file::path path;
//       //
//       //   path = pacmedirectory->home() / "archive";
//
//       //   key._set("__archive", path);
//
//       //   acmesystem()->m_papexsystem->os(L"__archive", wstring(path));
//
//       //   acmesystem()->m_papexsystem->node()->broadcast_environment_variable_change();
//
//       //}
//
//
//       //m_cPendingInstall = 1; // visual studio
//
//       //m_bSvnInstalled = false;
//
//       //#if INSTALL_GIT_ServiceControlManager
//       //
//       //      m_cPendingInstall += 2; // git scm and download source with git scm
//       //
//       //#endif
//
//       {
//
//          _synchronous_lock synchronouslock(this->synchronization());
//
//          auto & installmap = this->install_map();
//
//          for (auto& pinstall : installmap.payloads())
//          {
//
//             //if (pinstall->m_pcheckbox && pinstall->m_pcheckbox->bcheck())
//             if (pinstall->m_pinstallimpactinterface->is_selected())
//             {
//
//                pinstall->m_pinstallimpactinterface->hide_selection();
//
//                //pinstall->m_pcheckbox->hide();
//                //pinstall->m_pstillCheckBox->hide();
//
//             }
//
//          }
//
//       }
//
// #if defined(WINDOWS)
//
//       fork([this]()
//          {
//
//             {
//
//                ::file::path pathStorageWindowsFolder;
//
//                pathStorageWindowsFolder = "C:/operating_system/storage-windows";
//
//                if (!directory_system()->is(pathStorageWindowsFolder))
//                {
//
//                   m_strBinariesStatus = "Storage-windows binaries are missing...";
//
//                   ::file::path pathStorageWindowsZip = "C:/operating_system/storage-windows.zip";
//
//                   ::file::path pathStorageWindowsUrl = "https://ca2.software/download/storage-windows.zip";
//
//                   ::property_set set;
//
//                   set["raw_http"] = true;
//
//                   set["disable_common_name_cert_check"] = true;
//
//                   transfer_progress_function transferprogressfunction;
//
//                   transferprogressfunction = [this](double rate, filesize done, filesize total)
//                      {
//
//                         if (total == 0 || total == (filesize)-1)
//                         {
//
//                            m_strBinariesStatus2.formatf("Downloading storage-windows binaries compressed folder (%lld).",
//                               done);
//
//                         }
//                         else
//                         {
//
//                            m_strBinariesStatus2.formatf(
//                               "Downloading storage-windows binaries compressed folder  %0.1f%% (%lld of %lld).",
//                               rate * 100.0, done, total);
//
//                         }
//
//                         m_pimpact->set_need_redraw();
//
//                         m_pimpact->post_redraw();
//
//                      };
//
//                   set["transfer_progress_function"] = transferprogressfunction.m_pbase;
//
//                   http().download(pathStorageWindowsUrl, pathStorageWindowsZip, set);
//
//                   directory_system()->change_current(pathStorageWindowsZip.folder());
//
//                   file()->unzip_to_folder(pathStorageWindowsFolder.folder(), pathStorageWindowsZip);
//
//                }
//
//             }
//
//             if (directory_system()->is("C:/operating_system/storage-windows"))
//             {
//
//                m_strBinariesStatus = "Storage-windows binaries seem ok.";
//
//             }
//
//          });
//
//
// #endif
//
//       defer_start_installation(::coding::e_install_google_chrome);
//
//       defer_start_installation(::coding::e_install_visual_studio_code);
//       //#if TORTOISE_SVN
//       //
//       //      if (value("tortoise_svn"))
//       //      {
//       //
//       //         m_cPendingInstall += 2; // tortoisesvn and download source with tortoisesvn
//       //
//       //      }
//       //
//       //#endif
//       //
//       //#if SMART_SVN
//       //
//       //      if (set("smart_svn"))
//       //      {
//       //
//       //         m_cPendingInstall += 1;
//       //
//       //      }
//       //
//       //#endif
//       //
// #if INSTALL_GIT_ServiceControlManager
//
//       defer_start_installation(::coding::e_install_git_scm);
//
// #endif
//
// #if TORTOISE_SVN
//
//       if (value("tortoise_svn"))
//       {
//
//          fork([this]()
//             {
//
//                try
//                {
//
//                   int iTry = 0;
//
//                   while (!is_installed_svn_command() && iTry < 3)
//                   {
//
//                      install_tortoise_svn();
//
//                      task_sleep(500_ms);
//
//                      iTry++;
//
//                   }
//
//                   if (is_installed_svn_command())
//                   {
//
//                      ensure_minimal_source();
//
//                      if (m_bSourceOk)
//                      {
//
//                         set_status1("All Required Sources Donwloaded");
//
//                         release_install();
//
//                      }
//                      else
//                      {
//
//                         set_finish();
//
//                      }
//
//                   }
//                   else
//                   {
//
//                      set_finish();
//
//                      return;
//
//                   }
//
//                }
//                catch (...)
//                {
//
//                   set_finish();
//
//                }
//
//             });
//
//       }
//
// #endif
//
//
// #if TORTOISE_GIT
//
//       defer_start_installation(::coding::e_install_tortoise_git);
//       ////if (value("tortoise_svn"))
//       ////{
//       //if (m_pimpact->m_pcheckboxTortoiseGit
//       //   && m_pimpact->m_pcheckboxTortoiseGit->bcheck())
//       //{
//
//       //   fork([this]()
//       //      {
//
//       //         try
//       //         {
//
//       //            defer_install_tortoise_git(3);
//
//       //         }
//       //         catch (...)
//       //         {
//
//       //         }
//
//       //      });
//
//       //}
//
// #endif
//
// #if SMART_SVN
//
//       if (set("smart_svn"))
//       {
//
//          fork([this]()
//             {
//
//                if (!is_installed_smart_svn())
//                {
//
//                   install_smart_svn();
//
//                }
//
//                release_install();
//
//             });
//
//       }
//
// #endif
//
//
//       defer_start_installation(::coding::e_install_git_credential_manager);
//
//
// #if SMART_GIT
//
//       defer_start_installation(::coding::e_install_smart_git);
//       //if (value("tortoise_svn"))
//       //{
//       //if (m_pimpact->m_pcheckboxSmartGit
//       //   && m_pimpact->m_pcheckboxSmartGit->bcheck())
//       //{
//
//       //   fork([this]()
//       //      {
//
//       //         try
//       //         {
//
//       //            defer_install_smart_git(3);
//
//       //         }
//       //         catch (...)
//       //         {
//
//       //         }
//
//       //      });
//
//       //}
//
// #endif
//
//
//       //start_install_graphical_ide();
//       defer_start_installation(::coding::e_install_tool_os);
//
//       defer_start_installation(::coding::e_install_patch_shell);
//
//       defer_start_installation(::coding::e_install_deps);
//
//       defer_start_installation(::coding::e_install_visual_studio);
//
//       defer_start_installation(::coding::e_install_jetbrains_clion);
//
//       defer_start_installation(::coding::e_install_jetbrains_toolbox);
//
//       defer_start_installation(::coding::e_install_app_simple);
//
//
//
//       //while (true)
//       //{
//
//       //   if (is_installed(e_install_git_scm()))
//       //   {
//
//       //      if (is_graphical_ide_installed())
//       //      {
//
//       //         if (is_source_installed())
//       //         {
//
//       //            break;
//
//       //         }
//
//       //      }
//
      //    }
      //
      //    preempt(5_s);
      //
      // }


   }


   // ::pointer<::user::multiple_option > code::create_option(
   //    const ::data::property & property,
   //    ::user::interaction* puserinteractionParent,
   //    const ::atom_array& atomaOptions,
   //    const ::string_array & straName)
   // {
   //
   //    auto& poption = m_optionmap[property.atom()];
   //
   //    if (!poption)
   //    {
   //
   //       construct_newø(poption);
   //
   //       poption->create_option(property, atomaOptions, straName, straName);
   //
   //    }
   //
   //    auto poptionformhandler = create_newø<::coding::option_form_handler>();
   //
   //    auto pmultipleoption = poptionformhandler->create_option_form_handler(this, poption, puserinteractionParent);
   //
   //    // poption->m_poptionimpactinterface = poptionformhandler;
   //
   //    // pinstall->m_poptionloginterface = poptionformhandler;
   //
   //    // m_einstallaDependency[einstall] = einstallaDependency;
   //
   //    // m_einstallaSoftDependency[einstall] = einstallaSoftDependency;
   //
   //    m_atomaOptions.add(property.atom());
   //
   //    return pmultipleoption;
   //
   // }


    void code::create_install(::coding::enum_install einstall, ::user::interaction* puserinteractionParent, const ::numeric_array_base< ::coding::enum_install> & einstallaDependency, const ::numeric_array_base< ::coding::enum_install>& einstallaSoftDependency)
    {

#ifdef DEBUG

        ::string strName = m_papp->install_name(einstall);

        auto lines = file()->lines(directory_system()->home() / "assume_not_installed.txt");

        lines.trim();

        lines.erase_empty();

        for (auto& line : lines)
        {

            line.erase_character(' ');
            line.erase_character('\t');

        }

        if (!lines.case_insensitive_contains(strName) && !lines.case_insensitive_contains("#" + strName))
        {

            lines.add("#" + strName);

            file()->put_lines(directory_system()->home() / "assume_not_installed.txt", lines);

        }

#endif

        auto & pinstall = m_installmap[einstall];

        if(!pinstall)
        {
            construct_newø(pinstall);

            pinstall->create_install(einstall);

            pinstall->m_strName = m_papp->install_name(einstall);

            //_synchronous_lock synchronouslock(this->synchronization());

            //auto & installmap = m_papp->install_map();

        }

        // auto pinstallformhandler = create_newø<::coding::install_form_handler>();
        //
        // pinstallformhandler->create_install_form_handler(this, pinstall, puserinteractionParent);
        //
        // pinstall->m_pinstallimpactinterface = pinstallformhandler;
        //
        // pinstall->m_pinstallloginterface = pinstallformhandler;

        m_einstallaDependency[einstall] = einstallaDependency;

        m_einstallaSoftDependency[einstall] = einstallaSoftDependency;

        m_einstalla.add(einstall);

    }


    map < ::coding::enum_install, ::pointer < ::coding::install > >& code::install_map()
    {

       return m_installmap;

    }

} // namespace coding



