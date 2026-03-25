//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application.h"
#include "group_checkout_for_another_system.h"
#include "group_machine_box.h"
#include "group_netnode.h"
#include "group_new_release_prefix.h"
#include "group_operating_system.h"
#include "impact.h"
#include "integration.h"
#include "integration_command.h"
#include "item.h"
#include "task.h"
#include "task_group.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/speech/speech.h"
#include "acme/user/micro/user.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/scoped_restore.h"
#include "acme/handler/sequence.h"
#include "acme/prototype/collection/_string.h"
#include "acme/prototype/datetime/_text_stream.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/from_integer.h"
#include "acme/filesystem/file/buffered_file.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "apex/networking/http/context.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"


#include "acme/_operating_system.h"


CLASS_DECL_ACME::earth::time earth_time_from_international_string(const ::scoped_string& scopedstrTime);
CLASS_DECL_ACME bool sort_of_ok_earth_time_from_international_string(const ::scoped_string& scopedstrTime);


namespace coding
{


   integration::integration()
   {

      m_timeStart2.Now();

      m_timeEnd2 = m_timeStart2;

      m_eintegrateMask = e_integrate_none;

      m_bBuildFinished = false;

      m_bSummaryError = false;

      m_iCommandStep = 0;



#ifdef MACOS

      m_baTaskOrdinalEnable.set_size(2);

      m_baTaskOrdinalEnable[0] = true;
      m_baTaskOrdinalEnable[1] = true;

#else

      m_baTaskOrdinalEnable.set_size(8);

      m_baTaskOrdinalEnable[0] = true;
      m_baTaskOrdinalEnable[1] = true;
      m_baTaskOrdinalEnable[2] = true;
      m_baTaskOrdinalEnable[3] = true;
      m_baTaskOrdinalEnable[4] = true;
      m_baTaskOrdinalEnable[5] = true;
      m_baTaskOrdinalEnable[6] = true;
      m_baTaskOrdinalEnable[7] = true;

#endif

      m_baPhaseEnable.set_size(e_phase_count);

      m_baPhaseEnable[e_phase_new_release_prefix] = false;
      m_baPhaseEnable[e_phase_checkout] = true;
      m_baPhaseEnable[e_phase_application_list] = true;
      m_baPhaseEnable[e_phase_prepare_applications] = true;
      m_baPhaseEnable[e_phase_project_list] = true;
      m_baPhaseEnable[e_phase_prepare_projects] = true;
      m_baPhaseEnable[e_phase_cmake] = true;
      m_baPhaseEnable[e_phase_clean] = true;


   }


   integration::~integration()
   {

   }


   ::file::path integration::base_integration_folder()
   {

      return m_pintegrationcontext->base_integration_folder();

      //#ifdef WINDOWS_DESKTOP
      //
      //      return "C:/integration";
      //
      //#else
      //
      //      return directory_system() / "integration";
      //
      //#endif

   }


   ::file::path integration::host_integration_folder()
   {

      return m_pintegrationcontext->host_integration_folder();

   }


   ::file::path integration::integration_folder()
   {

      return host_integration_folder() / m_strIntegration;

   }


   void integration::initialize(::particle* pparticle)
   {

      ::app_consumer<::coding::application, ::object>::initialize(pparticle);

#ifdef WINDOWS_DESKTOP

      m_straTaskOrdinal.add("Win32 Debug");
      m_straTaskOrdinal.add("Win32 Release");
      m_straTaskOrdinal.add("Win32 StaticDebug");
      m_straTaskOrdinal.add("Win32 StaticRelease");
      m_straTaskOrdinal.add("x64 Debug");
      m_straTaskOrdinal.add("x64 Release");
      m_straTaskOrdinal.add("x64 StaticDebug");
      m_straTaskOrdinal.add("x64 StaticRelease");

#else

      m_straTaskOrdinal.add("Debug");
      m_straTaskOrdinal.add("Release");

#endif

   }


   void integration::initialize_integration()
   {

      node()->integration_factory();

      m_pparticleHttpSynchronization = node()->create_mutex();

      constructø(m_pintegrationcontext);

      defer_create_synchronization();

      m_poperatingsystemsummary = node()->operating_system_summary();

      m_pmutexLines = m_pintegrationcontext->m_pmutexLines;

      m_bSummaryError = true;


#if defined(WINDOWS)

      m_strVs = "2022";

      if (m_papp->m_bWinRT)
      {

         m_eintegrateMask |= e_integrate_branch_microsoft | e_integrate_system_type_universal;

      }
      else
      {

         m_eintegrateMask |= e_integrate_branch_microsoft | e_integrate_system_type_desktop;

      }

#endif

#if defined(LINUX)

      m_eintegrateMask |= e_integrate_branch_linux;

#endif

#if defined(__APPLE__)

      m_eintegrateMask |= e_integrate_branch_apple;

#endif
#if defined(FREEBSD)

      m_eintegrateMask |= e_integrate_branch_bsd | e_integrate_bsd_freebsd;

#endif


      if (m_papp->m_eapplication == e_application_build_tool)
      {

         on_initialize_application_build_tool();

      }
      else if (m_papp->m_eapplication == e_application_integration)
      {

         on_initialize_application_integration();

      }

   }


   ::string_array integration::save_nodes()
   {

      ::string_array straLines;

      for (::collection::index i = 0; i < m_straNode.get_size(); i++)
      {

         auto strLine = m_straNode[i];

         strLine.trim();

         if (strLine.has_character())
         {

            bool bEnabled = i >= m_baNodeEnabled.get_size() || m_baNodeEnabled[i];

            if (!bEnabled)
            {

               strLine = "# " + strLine;

            }

            straLines.add(strLine);

         }

      }

      return straLines;

   }


   void integration::load_nodes(const ::string_array& straLines)
   {

      m_straNode.clear();

      m_baNodeEnabled.clear();

      for (auto strLine : straLines)
      {

         strLine.trim();

         bool bEnabled = !strLine.begins_eat("#");

         strLine.trim();

         if (strLine.has_character())
         {

            m_straNode.add(strLine);

            m_baNodeEnabled.add(bEnabled);

         }

      }

      m_straNetnode.clear();

      for (::collection::index i = 0; i < m_straNode.get_size(); i++)
      {

         bool bEnabled = i >= m_baNodeEnabled.get_size() || m_baNodeEnabled[i];

         auto strLine = m_straNode[i];

         if (bEnabled)
         {

            m_straNetnode.add(strLine);

         }

      }


      if (m_papp->m_strAppId.case_insensitive_ends("/handler"))
      {

         if (m_straNetnode.has_element())
         {

            m_pgroupnetnode = create_newø < group_netnode >();

            m_pgroupnetnode->m_pintegration = this;

            m_pgroupnetnode->initialize_group_netnode(m_straNetnode);

            //m_groupa.add(m_pgroupnetnode);

         }
         else
         {

            m_pgroupnetnode.release();

         }

      }


   }


   void integration::read_nodes()
   {

      ::file::path pathNetnode;

      pathNetnode = host_integration_folder() / "netnode.txt";

      auto straLines = file_system()->lines(pathNetnode);

      straLines.trim();

      straLines.erase_empty();

      load_nodes(straLines);

   }


   void integration::write_nodes()
   {

      ::file::path pathNetnode;

      pathNetnode = host_integration_folder() / "netnode.txt";

      auto straLines = save_nodes();

      file_system()->put_lines(pathNetnode, straLines);

      read_nodes();

   }



   void integration::on_start_task_group(enum_task etaskGroup)
   {

   }

   void integration::on_initialize_application_integration()
   {

      m_pintegrationcontext->m_pathBaseIntegrationFolder = node()->get_default_base_integration_folder();

      auto pathHostIntegrationFolder = host_integration_folder();

      information() << "open_integration (host integration folder) : " << pathHostIntegrationFolder;

      m_pathCheckoutThenPowerOff = pathHostIntegrationFolder / "checkout_then_power_off.txt";

      information() << "open_integration (m_pathCheckoutThenPowerOff) : " << m_pathCheckoutThenPowerOff;

      auto strSlashedSystem = file_system()->as_string(m_pathCheckoutThenPowerOff);

      if (strSlashedSystem.has_character())
      {

         auto pgroupcheckout = create_newø<group_checkout_for_another_system>();

         pgroupcheckout->m_pintegration = this;

         pgroupcheckout->initialize_group_checkout_for_another_system(strSlashedSystem);

         m_groupa.add(pgroupcheckout);

         /* }
          else
          {*/

          //if (m_papp->m_eapplication == e_application_build_tool)
          //{

          //   m_eintegrateaOperatingSystem.copy_initializer_list(
          //      {
          //         e_integrate_none,
          //         e_integrate_windows_port,
          //         e_integrate_windows_openssl,
          //         e_integrate_windows_ffmpeg,
          //      });

          //}
          //else if (m_papp->m_eapplication == e_application_integration)
          //{

          //   ::file::path pathOperatingSystem;

          //   pathOperatingSystem = host_integration_folder() / "operating_system.txt";

          //   if (file_system()->exists(pathOperatingSystem))
          //   {

          //      m_straOperatingSystem = file_system()->lines(pathOperatingSystem);

          //      m_straOperatingSystem.trim();

          //      m_straOperatingSystem.erase_empty();

          //      if (m_straOperatingSystem.contains("windows"))
          //      {

          //         m_eintegrateaOperatingSystem.add(e_integrate_windows);

          //      }

          //   }
          //   else
          //   {

          //      if (m_eintegrateaOperatingSystem.is_empty())
          //      {

          //         m_eintegrateaOperatingSystem.copy_initializer_list(
          //            {
          //                    e_integrate_none,
          //                    e_integrate_windows,
          //                    e_integrate_windows_port,
          //                    e_integrate_ubuntu,
          //                    e_integrate_fedora,
          //                    e_integrate_kubuntu,
          //                    e_integrate_kfedora,
          //                    e_integrate_xubuntu,
          //                    e_integrate_opensuse_tumbleweed,
          //                    e_integrate_opensuseg_tumbleweed,
          //                    e_integrate_manjarog,
          //                    e_integrate_kmanjaro,
          //                    e_integrate_debiang,
          //                    e_integrate_kdebian,
          //                    e_integrate_freebsdg,
          //                    e_integrate_kfreebsd,
          //                    e_integrate_openbsdg,
          //                    e_integrate_kopenbsd,
          //                    e_integrate_netbsdg,
          //                    e_integrate_knetbsd,
          //                    e_integrate_macos,
          //            });

          //      }

          //   }

          //}

          ///*m_eintegrategroupa.copy_initializer_list(
          //{

          //   e_integrate_group_operating_system,
          //   e_integrate_group_third,
          //   e_integrate_group_machine_box,

          //});*/

          //initialize_integrate_operating_system();

          ////::file::path pathParentIntegrationPath;

          ////pathParentIntegrationPath = host_integration_folder() / "parent_integration.txt";

          ////::string strParentIntegration = file_system()->as_string(pathParentIntegrationPath);

          ////if (strParentIntegration.has_character())
          ////{

          ////   m_pathParentIntegration = base_integration_folder() / strParentIntegration;

          ////}

         return;

      }

      //if (m_papp->m_eapplication == e_application_build_tool)
      //{

      //   m_eintegrateaOperatingSystem.copy_initializer_list(
      //      {
      //         e_integrate_none,
      //         e_integrate_windows_port,
      //         e_integrate_windows_openssl,
      //         e_integrate_windows_ffmpeg,
      //      });

      //}
      //else if (m_papp->m_eapplication == e_application_integration)
      //{

      ::file::path pathOperatingSystem;

      pathOperatingSystem = host_integration_folder() / "operating_system.txt";

      if (file_system()->exists(pathOperatingSystem))
      {

         m_straOperatingSystem = file_system()->lines(pathOperatingSystem);

         m_straOperatingSystem.trim();

         m_straOperatingSystem.erase_empty();

         if (m_straOperatingSystem.contains("windows"))
         {

            m_eintegrateaOperatingSystem.add(e_integrate_windows);

         }

      }
      else
      {

         if (m_eintegrateaOperatingSystem.is_empty())
         {

            m_eintegrateaOperatingSystem.copy_initializer_list(
               {
                       e_integrate_none,
                       e_integrate_windows,
                       //e_integrate_windows_port,
                       e_integrate_ubuntu,
                       e_integrate_fedora,
                       e_integrate_kubuntu,
                       e_integrate_kfedora,
                       e_integrate_xubuntu,
                       e_integrate_opensuse_tumbleweed,
                       e_integrate_opensuseg_tumbleweed,
                       e_integrate_manjarog,
                       e_integrate_kmanjaro,
                       e_integrate_debiang,
                       e_integrate_kdebian,
                       e_integrate_freebsdg,
                       e_integrate_kfreebsd,
                       e_integrate_openbsdg,
                       e_integrate_kopenbsd,
                       e_integrate_netbsdg,
                       e_integrate_knetbsd,
                       e_integrate_macos,
               });

         }

      }

      //}

      /*m_eintegrategroupa.copy_initializer_list(
      {

         e_integrate_group_operating_system,
         e_integrate_group_third,
         e_integrate_group_machine_box,

      });*/

      initialize_integrate_operating_system();

      //if (m_papp->m_eapplication == e_application_integration)
      //{

      ::file::path pathMachineBox;

      pathMachineBox = host_integration_folder() / "machine_box.txt";

      m_straMachineBox = file_system()->lines(pathMachineBox);

      erase_sharp_comment(m_straMachineBox);

      m_straMachineBox.trim();

      m_straMachineBox.erase_empty();

      if (m_straMachineBox.has_element())
      {

         auto pgroupmachinebox = create_newø<group_machine_box>();

         pgroupmachinebox->m_pintegration = this;

         pgroupmachinebox->initialize_group_machine_box(m_straMachineBox);

         m_groupa.add(pgroupmachinebox);

      }

      //}

      m_straPhaseId.add("new_release_prefix");
      m_straPhaseId.add("checkout");
      m_straPhaseId.add("application_list");
      m_straPhaseId.add("prepare_applications");
      m_straPhaseId.add("project_list");
      m_straPhaseId.add("prepare_projects");
      m_straPhaseId.add("cmake");
      m_straPhaseId.add("clean");

      for (::collection::index i = 0; i < m_straPhaseId.size(); i++)
      {

         m_papp->datastream()->get(m_straPhaseId[i], m_baPhaseEnable[i]);
         //m_papp->datastream()->get("application_list", m_bApplicationList);
         //m_papp->datastream()->get("prepare_applications", m_bPrepareApplications);
         //m_papp->datastream()->get("project_list", m_bProjectList);
         //m_papp->datastream()->get("prepare_projects", m_bPrepareProjects);
         //m_papp->datastream()->get("cmake", m_bCmake);
         //m_papp->datastream()->get("clean", m_bClean);

      }

      m_straPhaseText.add("New Release Prefix");
      m_straPhaseText.add("Checkout");
      m_straPhaseText.add("Application List");
      m_straPhaseText.add("Prepare Applications");
      m_straPhaseText.add("Project List");
      m_straPhaseText.add("Prepare Projects");
      m_straPhaseText.add("Cmake");
      m_straPhaseText.add("Clean");

      ///}

      on_load();


   }


   void integration::on_initialize_application_handler()
   {

      m_papp->datastream()->get("new_release_prefix", m_baPhaseEnable[e_phase_new_release_prefix]);

      if (m_baPhaseEnable[e_phase_new_release_prefix])
      {

         auto pgroupnewreleaseprefix = create_newø<group_new_release_prefix>();

         pgroupnewreleaseprefix->m_pintegration = this;

         pgroupnewreleaseprefix->initialize_group_new_release_prefix();

         m_pgroupnewreleaseprefix = pgroupnewreleaseprefix;

         m_groupa.add(m_pgroupnewreleaseprefix);

      }

      read_nodes();

   }


   void integration::open(const ::file::path& pathIntegrationFolder)
   {

      m_pintegrationcontext->m_pathBaseIntegrationFolder = pathIntegrationFolder;

      information() << "open_integration (integration folder) : " << m_pintegrationcontext->m_pathBaseIntegrationFolder;

      ::file::path pathHost;

      pathHost = host_integration_folder();

      auto pathParentIntegration = pathHost / "parent_integration.txt";

      auto strParentIntegration = file_system()->as_string(pathParentIntegration);

      strParentIntegration.trim();

      ::file::path pathCurrentIntegration;

      auto pathBaseIntegrationFolder = m_pintegrationcontext->base_integration_folder();

      information() << "pathHost : " << pathHost;

      information() << "pathParentIntegration : " << pathParentIntegration;

      information() << "strParentIntegration : " << strParentIntegration;

      information() << "pathBaseIntegrationFolder : " << pathBaseIntegrationFolder;

      if (strParentIntegration.has_character())
      {

         pathCurrentIntegration = pathBaseIntegrationFolder / strParentIntegration / "current_integration.txt";

      }
      else
      {

         pathCurrentIntegration = pathHost / "current_integration.txt";

      }

      information() << "pathCurrentIntegration : " << pathCurrentIntegration;

      auto strIntegration = file_system()->as_string(pathCurrentIntegration);

      information() << "strIntegration : " << strIntegration;

      m_strIntegration = strIntegration;

      if (m_papp->m_eapplication == e_application_build_tool)
      {

         on_open_build_tool();

      }
      else if (m_papp->m_eapplication == e_application_integration
         || m_papp->m_eapplication == e_application_handler)
      {

         on_open_integration();

      }

   }


   void integration::on_open_integration()
   {

      //m_pintegrationcontext->m_pathBaseIntegrationFolder = pathIntegrationFolder;

      //node()->integration_factory();

      //m_pparticleHttpSynchronization = node()->create_mutex();

      //constructø(m_pintegrationcontext);

      //m_pintegrationcontext->m_pathBaseIntegrationFolder = pathIntegrationFolder;

      //defer_create_synchronization();

      //m_poperatingsystemsummary = node()->operating_system_summary();

      //m_pmutexLines = m_pintegrationcontext->m_pmutexLines;

      //m_bSummaryError = true;


   }


   void integration::on_load()
   {

      ::string strSystem = node()->operating_system_summary()->m_strSystem;

      ::string strSystemRelease = node()->operating_system_summary()->m_strSystemRelease;

      ::string strBranch = node()->operating_system_summary()->m_strSystemBranch;

      information() << "__SYSTEM : " << strSystem;

      information() << "__SYSTEM_RELEASE : " << strSystemRelease;

      information() << "__SYSTEM_BRANCH : " << strBranch;

      bool bCheck;

      for (auto& pgroup : m_groupa)
      {

         for (::collection::index iIntegrate = 0; iIntegrate < pgroup->get_size(); iIntegrate++)
         {

            bCheck = false;

            auto eintegrate = pgroup->get_eintegrate(iIntegrate);

            if (eintegrate == e_integrate_checkout_for_another_system)
            {

               bCheck = true;

               goto create_integration_option;

            }
            else if (eintegrate == e_integrate_new_release_prefix)
            {

               bCheck = true;

               goto create_integration_option;

            }
            else if (eintegrate == e_integrate_netnode)
            {

               bCheck = true;

               goto create_integration_option;

            }
            else if (eintegrate == e_integrate_machine_box)
            {

               bCheck = true;

               goto create_integration_option;

            }
            else if ((m_eintegrateMask & eintegrate) != m_eintegrateMask)
            {

               continue;

            }

#ifdef INTEGRATE_WINDOWS

            if (eintegrate == e_integrate_windows)
            {

               //auto iFind = straIntegration.case_insensitive_find_first("windows");

               //if (iFind >= 0)
               //{

               //   straIntegration.erase_at(iFind);

               //   goto create_integration_option;

               //}
               //else
               {

                  bCheck = true;

                  goto create_integration_option;

               }

            }
            else if (eintegrate == e_integrate_windows_port)
            {

               goto create_integration_option;

            }

#endif

#ifdef INTEGRATE_LINUX

            if (strSystem == "fedora")
            {


               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kfedora)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_fedora)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
            else if (strSystem == "ubuntu")
            {


               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kubuntu)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else if (strBranch == "xfce")
               {

                  if (eintegrate != e_integrate_xubuntu)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_ubuntu)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
            else if (strSystem == "debian")
            {

               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kdebian)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_debiang)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
            else if (strSystem == "manjaro")
            {

               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kmanjaro)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_manjarog)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
            else if (strSystem == "opensuse-tumbleweed")
            {

               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_opensuse_tumbleweed)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_opensuseg_tumbleweed)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
            else if (strSystem == "manjaro")
            {

               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kmanjaro)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_manjarog)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
#endif
#ifdef FREEBSD
            if (strDistro == "freebsd")
            {

               if (strBranch == "kde")
               {

                  if (eintegrate != e_integrate_kfreebsd)
                  {

                     continue;

                  }

                  bCheck = true;

               }
               else
               {

                  if (eintegrate != e_integrate_freebsdg)
                  {

                     continue;

                  }

                  bCheck = true;

               }

            }
#endif
         create_integration_option:

            auto& pitem = m_itema.add_new();

            construct_newø(pitem);

            pitem->m_eintegrate = eintegrate;

            pitem->m_bInitialCheck = bCheck;

            ::string strName;

            strName = pgroup->get_name(iIntegrate);

            pitem->m_strName1 = strName;

            pitem->m_iIntegrate = iIntegrate;

            pitem->m_pgroup = pgroup;

            ::string strShortName;

            strShortName = pgroup->get_short_name(iIntegrate);

            pitem->m_strShortName = strShortName;

            pitem->m_strRelease = strSystemRelease;

         }

      }


   }


   void integration::initialize_integrate_operating_system()
   {

      if (m_eintegrateaOperatingSystem.has_element())
      {

         auto pgroupoperatingsystem = create_newø<group_operating_system>();

         pgroupoperatingsystem->m_pintegration = this;

         pgroupoperatingsystem->initialize_group_operating_system(
            m_eintegrateaOperatingSystem.data(),
            m_eintegrateaOperatingSystem.size());

         m_groupa.add(pgroupoperatingsystem);

      }



   }

   void integration::set_impact_interface(impact_interface* pimpactinterface)
   {

      m_pimpactinterface = pimpactinterface;

   }


   void integration::set_integrate(enum_integrate eintegrate)
   {

      m_eintegrate = eintegrate;

      m_pimpactinterface->on_integrate_change();

   }


   void integration::run()
   {

      m_timeSpeechSpamControl.Now();

      m_iFailedTasks = 0;
      //auto pathBuildThenPowerOff = pathHost / "build_then_power_off.txt";

      //auto pathStartBuild = pathHost / "start_build.txt";

      //m_strIntegration = file_system()->as_string(pathStartBuild);

      m_timeStart = earth_time_from_international_string(m_strIntegration);

      auto pathIntegration = integration_folder();

      ::string strTimeStart = datetime()->date_time_text_for_file_with_no_spaces(m_timeStart);

      auto pathStartedBuilding = pathIntegration / "started_building.txt";

      m_timeStarted.Now();

      information() << "pathStartedBuilding : " << pathStartedBuilding;

      file_system()->put_time(pathStartedBuilding, m_timeStarted);

      main_status("Starting Integration...");

      m_straunion.add_array(m_pintegrationcontext->m_straOutput);

      m_straunion.add_array(m_straLine3);

      m_straunion.add_array(m_straPinnedLast2);

#if 1

      m_timeStart2.Now();

      if (m_pgroupnewreleaseprefix)
      {

         set_integrate(m_pgroupnewreleaseprefix->get_eintegrate(0));

#if defined(INTEGRATE_WINDOWS)

         integrate_new_release_prefix_windows();

#else

         throw "todo";

#endif

      }

      {

         //::property_set set;

         //set["raw_http"] = true;
         //set["disable_common_name_cert_check"] = true;

         //::string strUrl;

         //strUrl = "https://master-integrator.ca2.software/release_time";

         //::string strTime = system()->m_papexsystem->http().get(strUrl, set);
         //
         //strTime.trim();
         //
         //strTime.make_lower();
         //
         //if(strTime == "auto")
         //{
         //
         //   information() << "Auto Build release time string";

         //   m_timeBuild.Now();

         //}
         //else if (strTime.length() < 19
         //|| !character_isdigit(strTime[0])
         //|| !character_isdigit(strTime[1])
         //|| !character_isdigit(strTime[2])
         //|| !character_isdigit(strTime[3])
         //)
         //{
         //
         //   m_straLine2.add("E: Release time is incorrect.");

         //   m_straLine2.add("E: Requested URL : " + strUrl);
         //
         //   m_straLine2.add("E: Returned Text : \"" + strTime + "\"");
         //
         //   //m_straError.add(strError);
         //
         //
         //   m_pimpactinterface->on_lines_change();

         //   m_bBuildFinished = true;

         //   on_finished();

         //   return;

         //}
         //else
         //{
         //
         //   m_timeBuild = earth_time_from_international_string(strTime);
         //
         //}
         m_timeBuild = earth_time_from_international_string(m_strIntegration);

         information() << "Build release time string \"" << m_timeBuild << "\"";

      }

      m_bEnableUpdateElapsed = true;

      m_bBuildFinished = false;

      try
      {

         prepare_build();

         auto pdatetime = datetime();

         m_strReleaseDot = pdatetime->format("%Y.%m%d.%H%M.%S", m_timeBuild);

         m_strReleaseDash = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);

         m_strReleaseComma = pdatetime->format("%Y,%m%d,%H%M,%S", m_timeBuild);

         m_strReleaseDatetime = pdatetime->format("%Y-%m-%d-%H-%M-%S", m_timeBuild);

         m_strReleaseFilename = pdatetime->format("%Y-%m-%d %H-%M-%S", m_timeBuild);

         if (m_pgroupnetnode)
         {

            m_pgroupnetnode->start_integration(this);

         }

         for (auto& pitem : m_itema)
         {

            if (::is_null(pitem))
            {

               warningf("null item inserted in item list?!?!");

               continue;

            }

            auto eintegrate = pitem->m_eintegrate;

            if (eintegrate == e_integrate_none)
            {

               warningf("item with no integration inserted in item list?!?!");

               continue;

            }

            auto eintegrateId = eintegrate & e_integrate_id_mask;

            m_pitem = pitem;

            if (pitem->m_pcheckbox->is_checked())
            {

               set_integrate(eintegrate);

               try
               {

                  if (eintegrateId == e_integrate_main)
                  {

                     call_integrate_main(pitem);

                  }
                  else if (!on_integrate(pitem))
                  {

                     pitem->integrate();

                  }

               }
               catch (const ::exception& e)
               {

                  throw e;

               }
               catch (...)
               {

                  string strLine = "build of " + pitem->m_strShortName + " has failed!!";

                  m_straLine3.add(strLine);

                  m_straError.add(strLine);

               }

            }

         }

      }
      catch (const ::exception& e)
      {

         throw e;

      }
      catch (...)
      {

      }

      m_bEnableUpdateElapsed = false;

      m_bBuildFinished = true;

      while (!is_upload_finished())
      {

         set_integrate(e_integrate_uploading);

         preempt(1_s);

      }

      if (m_pgroupnetnode)
      {

         main_status("netnode running");

         m_pgroupnetnode->wait_to_finish();

      }

#endif

      on_finished();

   }


   void integration::on_finished()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_timeEnd2.Now();

         set_integrate(e_integrate_finished);

         if (m_straError.has_elements())
         {

            m_straLine3.add("Integration finished with errors!!");

            m_straLine3.append(m_straError);

            m_strFinishedStatus = "Finished with errors...";

         }
         else
         {

            m_strFinishedStatus = "Finished!!";

         }
         
         ::string strDateTime;
         
         strDateTime = datetime()->date_time_text();
         
         m_strFinishedStatus.append_formatf(" (at %s)", strDateTime.c_str());

         m_straLine3.add(m_strFinishedStatus);

      }

      main_status(m_strFinishedStatus);

   }


   //   ::file::path integration::log_base_folder()
   //   {
   //
   //#ifdef WINDOWS
   //
   //      return "C:/integration";
   //
   //#else
   //
   //      return directory_system()->home() / "integration";
   //
   //#endif
   //
   //   }


   void integration::prepare1(const ::string& lpcszSource, const ::string& lpcszDest)
   {

      string_array stra;


      string strLog;


#ifdef WINDOWS
      //sleep(15000_ms);

      auto papp = m_papp;

      string strBuildCmd = m_strEnv;

      if (m_strVs == "2015")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

      }
      else if (m_strVs == "2017")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

      }
      else if (m_strVs == "2019")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

      }
      else if (m_strVs == "2022")
      {

         //strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

         strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Integration/vcvars64.bat\"";

      }

      ::operating_system::process_pointer process(e_create, this);

      ::file::path pathEnvTxt;

      auto pacmedirectory = directory_system();

      pathEnvTxt = pacmedirectory->userconfig() / "env.txt";

      file_system()->put_contents(pacmedirectory->userconfig() / "env1.bat", pacmedirectory->userconfig() / "env.bat > \"" + pathEnvTxt + "\"");

      file_system()->put_contents(pacmedirectory->userconfig() / "env.bat", "@call " + strBuildCmd + "\r\n@set");

      node()->run_silent(pacmedirectory->userconfig() / "env1.bat", "");

      strLog = file_system()->as_string(pacmedirectory->userconfig() / "env.txt");

      stra.add_lines(strLog);

      //sleep(10000_ms);

#ifdef WINDOWS_DESKTOP

      property_set setEnvironment;

      setEnvironment.parse_environment_variable(stra);

      for (auto& property : setEnvironment)
      {

         string strVar = property.m_atom;

         string strValue = property.as_string();

         if (strVar == "PATH")
         {

            output_debug_string("");

         }

         SetEnvironmentVariableW(wstring(strVar), wstring(strValue));

      }



#endif
#endif

      stra.add_lines(strLog);

   }


   string integration::get_integration_name()
   {

      if (!m_pitem)
      {

         return "";

      }

      return m_pitem->m_strShortName;

   }


   task_group* integration::running_task_group()
   {

      if (m_etaskGroupRunning == e_task_none)
      {

         return nullptr;

      }

      return m_taskgroup[m_etaskGroupRunning];

   }


   class ::time integration::get_build_elapsed_time()
   {

      class ::time timeElapsed;

      if (!m_bEnableUpdateElapsed)
      {

         timeElapsed = m_timeEnd2 - m_timeStart2;

      }
      else
      {

         timeElapsed = m_timeStart2.elapsed();

      }

      if (timeElapsed <= 0_s)
      {

         return 0_s;

      }

      return timeElapsed;

   }


   //void integration::set_topic_text(const ::scoped_string& scopedstr)
   //{


   //   m_pimpactinterface->set_topic_text(s)
   //   //m_pimpact->m_ptopicText->set_window_text(scopedstr);

   //}


   //void integration::set_topic_text2(const ::scoped_string& scopedstr)
   //{

   //   m_pimpact->m_ptopicText2->set_window_text(scopedstr);

   //}

//   string integration::get_name(enum_integrate eintegrate)
//   {
//
//      switch (eintegrate)
//      {
//#ifdef WINDOWS
//      case e_integrate_windows:
//         return "Windows 10";
//      case e_integrate_windows_third:
//         return "Windows 10 third";
//#endif
//#ifdef LINUX
//      case e_integrate_ubuntu:
//         return "Ubuntu";
//      case e_integrate_fedora:
//         return "Fedora";
//      case e_integrate_kubuntu:
//         return "Kubuntu";
//      case e_integrate_kfedora:
//         return "Kfedora";
//#endif
//#ifdef MACOS
//      case e_integrate_macos:
//         return "macOS";
//#endif
//      default:
//         return "";
//      }
//
//   }


   void integration::append_message(const ::ansi_character* pszFormat, ...)
   {

      ::string strMessage;

      ASSERT(is_string_ok(pszFormat));

      va_list argList;

      va_start(argList, pszFormat);

      strMessage.formatf_arguments(pszFormat, argList);

      va_end(argList);

      m_straLine3.add_item(strMessage);

   }

   //
   //   void integration::add_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme)
   //   {
   //
   //
   //   }

   //
   //   //void integration::start_store_copy(const ::file::path & pathZip, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme)
   //   void integration::add_store_copy(const ::scoped_string & scopedstrAppId)
   //   {
   //
   //      ::file::path pathTarget;
   //
   //      if(scopedstrAppId == "app-core/store")
   //      {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //         pathTarget = m_pathStoreFolder / "store.exe";
   //
   //#elif defined(MACOS)
   //
   //         pathTarget = m_pathStoreFolder / "store.zip";
   //
   //#else
   //
   //         ::string strPlatform = m_distroreleaseanddesktopenvironment.m_strPackagePlatform;
   //
   //         ::string strExtension = m_distroreleaseanddesktopenvironment.m_strStandardPackageFileExtension;
   //
   //         pathTarget = m_pathStoreFolder / ("store_" + strPlatform + "." + strExtension);
   //
   //#endif
   //
   //      }
   //      else
   //      {
   //
   //         pathTarget = m_pathStoreFolder / (scopedstrAppId + ".zip");
   //
   //      }
   //
   //      synchronous_lock synchronouslock(this->synchronization());
   //
   //      m_storecopystructa.add({scopedstrAppId, pathTarget, pathSource, scopedstrScheme});
   //
   //   }


   void integration::add_store_copy(const ::scoped_string& scopedstrAppId)
   {
      
      ::file::path pathTarget;

      ::file::path pathSource;

      ::string strName = scopedstrAppId + ".zip";

      //::string strSystemAmbientReleaseArchitecture = m_poperatingsystemsummary->m_strSystemAmbientReleaseArchitecture;

      pathTarget = strName;

      pathSource = m_pathStorageFolder / strName;

      add_store_copy(scopedstrAppId, pathTarget, pathSource);

   }


   bool integration::is_upload_finished()
   {

      if (m_iCurrentStoreCopyItem >= m_copyitemaStore.get_size())
      {

         if (m_bBuildFinished)
         {

            return true;

         }

      }

      return false;

   }


   void integration::add_store_copy(const ::scoped_string& scopedstrAppId, const ::file::path& pathTarget,
      const ::file::path& pathSource)
   {

      if (!m_ptaskCopy)
      {

         m_ptaskCopy = fork([this]()
            {

               preempt(1_s);

               while (::task_get_run() && !is_upload_finished())
               {

                  preempt(100_ms);

                  ::pointer<copy_item> pcopyitem;

                  {

                     _synchronous_lock synchronouslock(this->synchronization());

                     if (m_iCurrentStoreCopyItem >= m_copyitemaStore.get_size())
                     {

                        continue;

                     }

                     pcopyitem = m_copyitemaStore[m_iCurrentStoreCopyItem];

                     m_iCurrentStoreCopyItem++;

                  }

                  if (pcopyitem)
                  {

                     informationf("copy item release package \"%s\"", pcopyitem->m_strAppId.c_str());

                     release_package(pcopyitem->m_strAppId,
                        pcopyitem->m_pathTarget,
                        pcopyitem->m_pathSource);

                     informationf("Ended Copy Item release package \"%s\"",
                        pcopyitem->m_strAppId.c_str());

                  }

               }

               information() << "add_store_copy Upload Task Stopped";

               if (is_upload_finished())
               {

                  on_finished();

               }

            });

      }

      auto pcopyitem = create_newø<copy_item>();

      pcopyitem->m_strAppId = scopedstrAppId;

      pcopyitem->m_pathTarget = pathTarget;

      pcopyitem->m_pathSource = pathSource;

      informationf("new copy item \"%s\"", pcopyitem->m_strAppId.c_str());
      informationf("source path \"%s\"", pcopyitem->m_pathSource.c_str());
      informationf("target path \"%s\"", pcopyitem->m_pathTarget.c_str());

      _synchronous_lock synchronouslock(this->synchronization());

      m_copyitemaStore.add(pcopyitem);

   }


   void integration::release_package(const char* pszAppId, const char* pszTarget, const char* pszSource)
   {
      
      m_timeTopicStoreStart.Now();

      ::string strAppId(pszAppId);

      ::string strTarget(pszTarget);

      ::string strSource(pszSource);

      if (!on_packaging(strAppId, strTarget, strSource))
      {

         return;

      }

      store_copy(strAppId, strTarget, strSource);

   }


   void integration::store_copy(const ::scoped_string& scopedstrAppId, const ::file::path& pathTarget,
      const ::file::path& pathSource)
   {

      ::memory memory;

      memory = file_system()->safe_get_memory(pathSource);

      information() << "source : " << pathSource;

      if (memory.is_empty())
      {

         information() << "🔼 Does file exist? : " + pathSource;

         integration_summary(scopedstrAppId, "🔼 Does file exist? : " + pathSource, false);

         return;

      }

      auto pmemoryfile = create_memory_file(memory);

      ::file::path pathFolder;

#ifdef WINDOWS

      pathFolder = "C:/store";

#else

      pathFolder = directory_system()->home() / "store";

#endif

      if (directory_system()->is(pathFolder))
      {

         store_copy_to_local_file_system_store(pathFolder, scopedstrAppId, pathTarget, pmemoryfile);

      }
      else
      {

         store_copy_to_http_server(scopedstrAppId, pathTarget, pmemoryfile);

      }

   }


   void integration::store_copy_to_local_file_system_store(const ::file::path& pathFolder,
      const ::scoped_string& scopedstrAppId,
      const ::file::path& pathTarget, ::file::file* pfileSource)
   {

      ::string strSystemAmbientReleaseArchitecture = m_poperatingsystemsummary->m_strSystemAmbientReleaseArchitecture;

      ::file::path pathDestination = pathFolder / strSystemAmbientReleaseArchitecture / pathTarget;

      information("Store Copy Copying \"" + scopedstrAppId + "\"");

      information() << "destination : " << pathDestination;

      information() << "pfileSource : " << (::iptr)pfileSource;

      try
      {

         file()->copy(pathDestination, pfileSource);

      }
      catch (...)
      {

         integration_summary(scopedstrAppId, "🔼", false);

         return;

      }

      integration_summary(scopedstrAppId, "✓", false);

      {

         //synchronous_lock synchronouslock(this->synchronization());

         //m_strTopic2.clear();

         m_pimpactinterface->set_topic_text2("");

      }

   }


   void integration::store_copy_to_http_server(const ::scoped_string& scopedstrAppId, const ::file::path& pathTarget,
      ::file::file* pfileSource)
   {

      ::property_set set;

      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

      auto timeUpload = ::earth::time::now();

      ::string strSystemAmbientReleaseArchitecture = m_poperatingsystemsummary->m_strSystemAmbientReleaseArchitecture;

      ::string strUploadTime = datetime()->date_time_text_for_file_with_no_spaces(timeUpload, ::posix_time(zero_t{}));

      ::string strUrl = "https://upstream.ca2.software/store_upload?";

      strUrl += "slashed_operating_system=" + ::url::encode(strSystemAmbientReleaseArchitecture);
      strUrl += "&release_time=" + ::url::encode(m_strReleaseFilename);
      strUrl += "&upload_time=" + ::url::encode(strUploadTime);
      strUrl += "&path=" + ::url::encode(pathTarget);

      information("Store Copy Uploading \"" + scopedstrAppId + "\"");

      if (m_bBuildFinished)
      {

         main_status("Uploading " + scopedstrAppId);

      }

      set["transfer_progress_function"] = ::transfer_progress_function(
         [this, scopedstrAppId](double dRate, filesize done, filesize total)
         {

            if (total > 0)
            {

               ::string strTopic2;

               if (done == total)
               {

                  strTopic2.formatf("Uploading %s complete", scopedstrAppId.c_str());

               }
               else
               {

                  strTopic2.formatf("Uploading %s - %0.2f%% %d of %d...", scopedstrAppId.c_str(), dRate * 100.0,
                     done, total);

               }

               m_pimpactinterface->set_topic_text2(strTopic2);

               //m_pimpactinterface->on_state_change();

            }

         });

      ::memory memoryResponse;

      set["get_memory"] = &memoryResponse;

      http()->put(strUrl, pfileSource, set);

      set["get_memory"].unset();

      ::string strResponse = memoryResponse.get_string();

      information() << "http_put url : " << strUrl << " response : " << strResponse;

      if (strResponse != "OK")
      {

         integration_summary(scopedstrAppId, "🔼", false);

         return;

      }

      integration_summary(scopedstrAppId, "✓", false);

      {

         //synchronous_lock synchronouslock(this->synchronization());

         //m_strTopic2.clear();

         m_pimpactinterface->set_topic_text2("");

      }
      //      auto pathLog = m_pathBuildFolder / "time-macos/store_release" / (scopedstrScheme + "_" + m_strReleaseFilename + ".txt");
      //
      //      auto pfileLogCopyFunction = file()->get_writer(pathLog);
      //
      //      if(!file_system()->exists(pathSource))
      //      {
      //
      //         pfileLogCopyFunction->println("Fatal: Source file doesn't exist:\n" + pathSource);
      //
      //         return;
      //
      //      }
      //
      //      ::filesize sizeTarget = -1;
      //
      //      ::filesize sizeSource = -1;
      //
      //      class ::time timeModificationTarget;
      //
      //      class ::time timeModificationSource;
      //
      //      bool bCopy = !file_system()->exists(pathTarget);
      //
      //      if(bCopy)
      //      {
      //
      //         ::string strMessage;
      //
      //         strMessage.format("File:\n\"%s\"\ndoesn't exist!!\n\n", pathTarget.c_str());
      //
      //         pfileLogCopyFunction->println(strMessage);
      //
      //         pfileLogCopyFunction->flush();
      //
      //      }
      //
      //      if(!bCopy)
      //      {
      //
      //         sizeTarget = file_system()->get_size(pathTarget);
      //
      //         sizeSource = file_system()->get_size(pathSource);
      //
      //         bCopy = sizeTarget != sizeSource;
      //
      //         if(bCopy)
      //         {
      //
      //            ::string strMessage;
      //
      //            strMessage.format("Files:\n\"%s\"\nand\n\"%s\"\nhave different sizes:\n%d and %d\n\n", pathTarget.c_str(), pathSource.c_str(),sizeTarget, sizeSource);
      //
      //            pfileLogCopyFunction->println(strMessage);
      //
      //            pfileLogCopyFunction->flush();
      //
      //         }
      //
      //      }
      //
      //      if(!bCopy)
      //      {
      //
      //         timeModificationTarget = file_system()->modification_time(pathTarget);
      //
      //         timeModificationSource = file_system()->modification_time(pathSource);
      //
      //         bCopy = timeModificationTarget != timeModificationSource;
      //
      //         if(bCopy)
      //         {
      //
      //            ::string strMessage;
      //
      //            strMessage.format("Files:\n\"%s\"\nand\n\"%s\"\nhave different modification times:\n%s\nand\n%s\n\n", pathTarget.c_str(), pathSource.c_str(), acmesystem()->datetime()->international().format((time_t)timeModificationTarget.m_iSecond).c_str(),
      //                              timeModificationTarget.m_iNanosecond / 1'000'000, acmesystem()->datetime()->international().format((time_t)timeModificationSource.m_iSecond).c_str(),timeModificationSource.m_iNanosecond / 1'000'000);
      //
      //            pfileLogCopyFunction->println(strMessage);
      //
      //            pfileLogCopyFunction->flush();
      //
      //         }
      //
      //      }
      //
      //      if (bCopy)
      //      {
      //
      //         ::string strMessage;
      //
      //         strMessage = "Going to copy from:\n\"" + pathSource + "\"\nto:\n\"" + pathTarget+ "\"\n\n";
      //
      //         pfileLogCopyFunction->println(strMessage);
      //
      //         pfileLogCopyFunction->flush();
      //
      //         file()->copy(pathTarget, pathSource, false);
      //
      //         strMessage = "Copied from:\n\"" + pathSource + "\"\nto:\n\"" + pathTarget + "\"\n\n";
      //
      //         pfileLogCopyFunction->println(strMessage);
      //
      //         pfileLogCopyFunction->flush();
      //
      //      }
      //      else
      //      {
      //
      //         ::string strMessage;
      //
      //         strMessage = pathTarget + " exists and has same size and modification time as source...\n\n";
      //
      //         pfileLogCopyFunction->println(strMessage);
      //
      //         pfileLogCopyFunction->flush();
      //
      //      }

   }


class ::time integration::get_topic_elapsed_time()
{
   
   if(m_timeTopicBuildStart.is_null())
   {
    
      return {};
      
   }
 
   return m_timeTopicBuildStart.elapsed();
   
}


   void integration::main_status(const ::scoped_string& scopedstrMainStatus)
   {

      ::string strLabel(scopedstrMainStatus);

      ::string strStatusDateTime;

      {

         //synchronous_lock synchronouslock(this->synchronization());

         m_pimpactinterface->set_topic_text(strLabel);

         m_timeTopicBuildStart.Now();

         strStatusDateTime = datetime()->date_time_text_for_file_with_no_spaces(m_timeTopicBuildStart, ::posix_time(zero_t{}));

         if (m_pitem && m_pitem->m_pstillStatus)
         {

            m_pitem->m_pstillStatus->set_window_text(strLabel);

         }

      }

      ::file::path pathMainStatus;

      if (m_papp->m_strAppId.case_insensitive_ends("/handler"))
      {

         pathMainStatus = host_integration_folder() / "main_status.txt";

      }
      else
      {

         pathMainStatus = integration_folder() / "main_status.txt";

      }

      file_system()->put_block(pathMainStatus, scopedstrMainStatus);

      //m_pimpactinterface->set_topic_text(scopedstrMainStatus);

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_straLine3.add_item(scopedstrMainStatus);

      }

      m_pimpactinterface->on_lines_change();

      //      fork([this, strLabel, strStatusDateTime]()
      //         {
      //
      //            ::string strHostname = node()->m_papexnode->get_host_name();
      //
      //            ::string strSlashedOperatingSystem = m_poperatingsystemsummary->m_strSlashedIntegration;
      //
      //            ::string strUrl = "https://upstream.ca2.software/integration_status?";
      //
      //            strUrl += "slashed_operating_system=" + ::url::encode(strSlashedOperatingSystem);
      //            strUrl += "&release_time=" + ::url::encode(m_strReleaseFilename);
      //            strUrl += "&status_time=" + ::url::encode(strStatusDateTime);
      //            strUrl += "&status=" + ::url::encode(strLabel);
      //
      //            ::property_set set;
      //
      //            set["raw_http"] = true;
      //            set["disable_common_name_cert_check"] = true;
      //
      //            auto strLastUpstreamServerStatus = system()->m_papexsystem->http().get(strUrl, set);
      //
      //            {
      //
      //               _synchronous_lock synchronouslock(this->synchronization());
      //
      //               m_strLastUpstreamServerStatus = strLastUpstreamServerStatus;
      //
      //               if (m_strLastUpstreamServerStatus.has_character())
      //               {
      //
      //                  m_timeLastUpstreamServerStatus.Now();
      //
      //               }
      //
      //            }
      //
      //         });

   }


   bool integration::on_more_packaging(::string& strAppId, ::string& strTarget, ::string& strSource)
   {

      ::string strCommand;

      strCommand = "application_build_helper --package-application " + strAppId;

      ::file::path pathSource = strSource;

      ::string strName;

      strName = pathSource.name() + "_" + m_strReleaseFilename + ".txt";

      auto pathLog = directory_system()->home() / "integration/_____";

      auto strSystemAmbientReleaseArchitecture = node()->operating_system_summary()->m_strSystemAmbientReleaseArchitecture;

      pathLog /= strSystemAmbientReleaseArchitecture;

      pathLog /= m_strReleaseFilename / (strAppId + ".txt");

      information() << "release pathLog : " << pathLog;

      auto pfileLog = file()->get_writer(pathLog, ::file::e_open_write | ::file::e_open_create |
         ::file::e_open_defer_create_directory |
         ::file::e_open_share_deny_write);

      pfileLog->write(strCommand + "\n");

      pfileLog->write("Current Directory: " + directory_system()->current() + "\n");

      trace_function tracefunction = [&](auto etracelevel, auto& str, bool bCarriage)
         {

            ::string strTrace;

            strTrace = str + (bCarriage ? "\r" : "\n");

            pfileLog->write(strTrace);

            m_pimpactinterface->on_lines_change();

         };

      information(strCommand);

      int iExitCode = node()->command_system(strCommand, tracefunction);

      if (iExitCode != 0)
      {

         ::string strTrace;

         strTrace = "Failed to package application : " + strAppId;

         ::string strError;

         strError = "Exit code : " + ::string_from(iExitCode);

         pfileLog->write(strTrace + "\n");

         pfileLog->write(strError + "\n");

         information() << strTrace;

         information() << strError;

         return false;

      }

      return true;

   }

::coding::summary_item * integration::summary_item(const ::scoped_string & scopedstrItem)
{
   _synchronous_lock synchronouslock(this->synchronization());
   
   auto &pitem = m_mapSummaryItem[scopedstrItem];
   if(defer_construct_newø(pitem))
   {
      pitem->m_strItem = scopedstrItem;
   }
   
   return pitem;

}

   void integration::integration_summary(const ::scoped_string& scopedstrAppId, const ::scoped_string& scopedstrOk, bool bBuild)
   {
      
      class ::time timeBuild;
      class ::time timeStore;
      
      if(bBuild)
      {
       
         timeBuild = m_timeTopicBuildStart.elapsed();
         
      }
      else
      {
         
         timeStore = m_timeTopicStoreStart.elapsed();
         
      }

      //auto timeNow = ::time::now();

      //auto timeElapsed = timeNow - m_timeTopicStart;

      {
         
         _synchronous_lock synchronouslock(this->synchronization());
         
         m_straSummary.insert_at(0, scopedstrAppId);
         
         auto pitem = summary_item(scopedstrAppId);
         
         if(scopedstrOk.has_character())
         {
            
            if(scopedstrOk.size() > 10)
            {
               
               pitem->m_strStatus = scopedstrAppId + ": " + scopedstrOk;
               
            }
            else
            {
               
               pitem->m_strStatus = scopedstrOk + " " + scopedstrAppId;
               
            }
            
         }
         if(timeBuild.is_set())
         {
            pitem->m_timeBuild = timeBuild;
         }
         if(timeStore.is_set())
         {
            pitem->m_timeStore = timeStore;
         }

      }

      if (m_pimpactinterface)
      {

         m_pimpactinterface->on_lines_change();

      }

      if (scopedstrOk.has_character() && !scopedstrOk.contains("✓"))
      {

         if (!m_bSummaryError)
         {

            m_bSummaryError = true;

            m_baPhaseEnable[e_phase_checkout] = false;
            m_papp->datastream()->set("checkout", m_baPhaseEnable[e_phase_checkout]);

            m_baPhaseEnable[e_phase_application_list] = false;
            m_papp->datastream()->set("application_list", m_baPhaseEnable[e_phase_application_list]);

            m_baPhaseEnable[e_phase_prepare_applications] = false;
            m_papp->datastream()->set("prepare_applications", m_baPhaseEnable[e_phase_prepare_applications]);

            m_baPhaseEnable[e_phase_project_list] = false;
            m_papp->datastream()->set("project_list", m_baPhaseEnable[e_phase_project_list]);

            m_baPhaseEnable[e_phase_prepare_projects] = false;
            m_papp->datastream()->set("prepare_projects", m_baPhaseEnable[e_phase_prepare_projects]);

            m_baPhaseEnable[e_phase_cmake] = false;
            m_papp->datastream()->set("cmake", m_baPhaseEnable[e_phase_cmake]);

            m_baPhaseEnable[e_phase_clean] = false;
            m_papp->datastream()->set("clean", m_baPhaseEnable[e_phase_clean]);

         }

      }

      ::string strSummaryTime = system()->datetime()->date_time_text_for_file_with_no_spaces(m_timeTopicBuildStart, posix_time(zero_t{}));

      //      ::string strUrl = "https://upstream.ca2.software/integration_summary?";
      //
      //      ::string strSlashedOperatingSystem = m_poperatingsystemsummary->m_strSlashedIntegration;
      //
      //      strUrl += "slashed_operating_system=" + ::url::encode(strSlashedOperatingSystem);
      //      strUrl += "&release_time=" + ::url::encode(m_strReleaseFilename);
      //      strUrl += "&summary_time=" + ::url::encode(strSummaryTime);
      //      strUrl += "&appid=" + ::url::encode(scopedstrAppId);
      //      strUrl += "&ok=" + scopedstrOk;
      //
      //      ::property_set set;
      //
      //      set["raw_http"] = true;
      //      set["disable_common_name_cert_check"] = true;
      //
      //      auto strLastUpstreamServerSummary = system()->m_papexsystem->http().get(strUrl, set);
      //
      //      {
      //
      //         _synchronous_lock synchronouslock(this->synchronization());
      //
      //         m_strLastUpstreamServerSummary = strLastUpstreamServerSummary;
      //
      //         if (m_strLastUpstreamServerSummary == "OK")
      //         {
      //
      //            m_timeLastUpstreamServerSummary = timeNow;
      //
      //         }
      //
      //      }

      _synchronous_lock synchronouslock(this->synchronization());

      ::string strSummaryText;

      strSummaryText += scopedstrOk + " ";
      strSummaryText += strSummaryTime + " ";
      strSummaryText += scopedstrAppId + "\n";

      auto pathSummaryFolder = directory_system()->home() / "integration";

      pathSummaryFolder /= m_strReleaseFilename;

      auto strSystemAmbientRelease = m_poperatingsystemsummary->m_strSystemAmbientReleaseArchitecture;

      pathSummaryFolder /= strSystemAmbientRelease;

      {

         ::file::path pathSummary = pathSummaryFolder / ("summary.txt");

         ::string strSummary = file()->safe_get_string(pathSummary);

         strSummary += strSummaryText;

         file()->put_text_utf8(pathSummary, strSummary);

      }

      if (scopedstrOk != "✓")
      {

         ::file::path pathSummary = pathSummaryFolder / ("failed.txt");

         ::string strSummary = file()->safe_get_string(pathSummary);

         strSummary += strSummaryText;

         file()->put_text_utf8(pathSummary, strSummary);

      }

   }


   bool integration::has_selected_build() const
   {

      for (auto pitem : m_itema)
      {

         if (!pitem)
         {

            continue;

         }

         auto pcheckbox = pitem->m_pcheckbox;

         if (!pcheckbox)
         {

            continue;

         }

         if (pcheckbox->is_checked())
         {

            return true;

         }

      }

      return false;

   }


   void integration::add_command(
      const ::scoped_string& scopedstrLabel,
      const ::scoped_string& scopedstrCommand,
      const class ::time& timeTimeout
   )
   {


      auto pcommand = create_newø < integration_command >();

      pcommand->m_pintegration = this;

      pcommand->m_strLabel = scopedstrLabel;
      pcommand->m_strCommand = scopedstrCommand;
      pcommand->m_timeTimeout = timeTimeout;

      m_integrationcommanda.add(pcommand);

      pcommand->m_iStep =(int) m_iCommandStep++;

   }



   void integration::do_command(integration_command* pintegrationcommand)
   {

      auto strStep = pintegrationcommand->get_step_text();

      auto strPlainLabel = pintegrationcommand->get_plain_label();

      auto pathLog = m_pathLogFolder / (strStep + " " + strPlainLabel + ".txt");

      pintegrationcommand->m_pfileLog = file()->get_writer(pathLog, ::file::e_open_write | ::file::e_open_create |
         ::file::e_open_defer_create_directory |
         ::file::e_open_share_deny_write);

      trace_function tracefunction = [this, pintegrationcommand](auto etracelevel, auto& str, bool bCarriage)
         {

            _synchronous_lock singlelock(m_pmutexLines);

            ::string s;

            s.formatf("%c: %s", trace_level_letter(etracelevel), ::string(str).c_str());

            m_straLine3.feed_line(s, bCarriage);

            ::string strTrace;

            strTrace = str + (bCarriage ? "\r" : "\n");

            pintegrationcommand->m_pfileLog->write(strTrace);

            m_pimpactinterface->on_lines_change();

         };

      pintegrationcommand->m_tracefunction = tracefunction;

      try
      {

         pintegrationcommand->run();

      }
      catch (...)
      {

      }

      if (pintegrationcommand->m_pfileLog)
      {

         pintegrationcommand->m_pfileLog->close();

      }

   }


   //   void integration_command::run()
   //   {
   //
   //      m_tracefunction.m_timeTimeout = m_timeTimeout;
   //
   //      auto strStep = get_step_text();
   //
   //      class ::time timeItem;
   //
   //      timeItem.Now();
   //
   //      auto strLabel = m_strLabel;
   //
   //      m_pintegration->main_status(node()->operating_system_summary()->m_strSlashedIntegration + ":" + strLabel);
   //
   //      auto strCommand = m_strCommand;
   //
   //      ::string strPlainLabel = strLabel;
   //
   //      strPlainLabel.find_replace("/", "_");
   //
   //      {
   //
   //         informationf("command_system: %s\n", strCommand.c_str());
   //
   //         if (m_strCommand.begins_eat("unix:"))
   //         {
   //
   //            m_iExitCode = node()->unix_shell_command(strCommand, m_tracefunction);
   //
   //         }
   //         else
   //         {
   //
   //            m_iExitCode = node()->command_system(strCommand, m_tracefunction);
   //
   //         }
   //
   //         informationf("exit_code: %d\n", m_iExitCode);
   //
   //         string strItemResult;
   //
   //         strItemResult += "\n";
   //
   //         strItemResult += "-----         " + strLabel + "\n";
   //         strItemResult += "command     : " + strCommand + "\n";
   //         strItemResult += "exit code   : " + ::as_string(m_iExitCode) + "\n";
   //         strItemResult += "time    : " + ::as_string(timeItem.elapsed().floating_minute()) + " minute(s)\n";
   //
   //         strItemResult += "\n";
   //
   //         m_pfileLog->write(strItemResult);
   //
   //         m_pintegration->m_pimpactinterface->on_lines_change();
   //
   //         m_pintegration->m_strBuildResult += strItemResult;
   //
   //      }
   //
   //      ::string strAppIdStore;
   //
   //      strAppIdStore = strLabel;
   //
   //      if (strAppIdStore.case_insensitive_begins_eat("cmake_project "))
   //      {
   //
   //         if (m_iExitCode == 0)
   //         {
   //
   //            information() << "add_store_copy : " << strAppIdStore;
   //
   //            m_pintegration->add_store_copy(strAppIdStore);
   //
   //         }
   //         else
   //         {
   //
   //            //synchronous_lock synchronouslock(this->synchronization());
   //
   //            //m_itemtimeaSummary.insert_at(0, {"✗ " + strAppIdStore, m_timeTopicStart.elapsed()});
   //
   //            m_pintegration->integration_summary(strAppIdStore, "✗");
   //
   //         }
   //
   //      }
   //
   //   }


   bool integration::integrate_command_list()
   {

      string& strBuildResult = m_strBuildResult;

      auto pathLogFolder = this->integration_folder();

      pathLogFolder /= "_____build";

      m_pathLogFolder = pathLogFolder;

     // int iExitCode = 0;

      string strStep;

      string strLabel;

      string strCommand;

      ::collection::index i = 0;

      bool bOk = true;

      //auto pacmedirectory = directory_system();

      //auto pacmefile = file_system();

      for (; bOk && i < m_integrationcommanda.get_size() && ::task_get_run(); i++)
      {

         auto pcommand = m_integrationcommanda.element_at(i);

         do_command(pcommand);

         auto iExitCode = pcommand->m_iExitCode;

         if (iExitCode != 0)
         {

            bOk = false;

         }

      }

      string strTime = m_pitem->m_pstillElapsed->get_window_text();

      strBuildResult += "Total build time: " + strTime + "\n";

      m_bBuildFinished = true;

      if (bOk)
      {

         strBuildResult += "Build succeeded!!";

         m_pitem->m_pstillStatus->set_window_text("OK");

         auto pathBuildSucceeded = pathLogFolder / (strStep + " _____ Build Succeeded!!.txt");

         file_system()->put_contents(pathBuildSucceeded, strBuildResult);

      }
      else
      {

         strBuildResult += "Build stopped at step \"" + strLabel + "\"";

         m_pitem->m_pstillStatus->set_window_text("Failed at " + strLabel + "!");

         auto pathFailedStep = pathLogFolder / (strStep + " _____ Step Failed!!.txt");

         file_system()->put_contents(pathFailedStep, strBuildResult);

      }

      return bOk;

   }


   void integration::on_finished_finish_animations()
   {

      auto pathHost = host_integration_folder();

      if (m_itema.get_size() == 1
         && m_itema.first()->m_eintegrate == e_integrate_checkout_for_another_system)
      {

         main_status("In 16 seconds, going to power off machine...");

         preempt(11_s);

         auto pathCheckoutThenPoweredOff = pathHost / "checkout_then_powered_off.txt";

         file_system()->transfer(pathCheckoutThenPoweredOff, m_pathCheckoutThenPowerOff);

         preempt(5_s);

         node()->shutdown(true);

         application()->set_finish();

      }
      else
      {

         auto pathBuildThenPowerOff = pathHost / "build_then_power_off.txt";

         if (file_system()->exists(pathBuildThenPowerOff))
         {

            main_status("In 20 seconds, going to power off machine...");

            preempt(15_s);

            auto pathBuiltThenPoweredOff = pathHost / "built_then_powered_off.txt";

            file_system()->transfer(pathBuiltThenPoweredOff, pathBuildThenPowerOff);

            preempt(5_s);

            node()->shutdown(true);

            application()->set_finish();

         }
         else
         {

            information() << "integration : " << m_strIntegration;

            if (file_system()->exists(m_pathStartBuild))
            {

               auto pathBuilt = integration_folder() / "build_completion_status.txt";

               file_system()->erase(m_pathStartBuild);

               file_system()->put_block(pathBuilt, m_strBuildResult);

            }

         }

      }

   }


   log_interface* integration::task_log(enum_task etask)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto p = m_taskgroup.find((enum_task)(etask & e_task_group_mask));

      if (!p || !p->element2())
      {

         return nullptr;

      }

      auto ptaskgroup = p->element2();

      auto etaskOrdinal = (enum_task)(etask & e_task_ordinal_mask);

      auto& ptask = ptaskgroup->m_taskmapTemplate[etaskOrdinal];

      if (!ptask)
      {

         return nullptr;

      }

      auto& plog = ptask->m_plog;

      //defer_task_group(etask & e_task_group_mask, ptaskgroup);

      //defer_task(etask & e_task_ordinal_mask, ptaskgroup);

      if (!plog)
      {

         construct_newø(plog);

         plog->m_ptask = ptask;

         ptask->m_plog = plog;

         plog->defer_create_synchronization();

      }

      return plog;

   }


   bool integration::should_task_group_tasks_be_sequential(enum_task etaskGroup)
   {

      switch (etaskGroup)
      {
      case e_task_port:
         return true;
      default:
         return false;
      }

   }



   void integration::task_group_indexes(enum_task etaskGroup, ::numeric_array_base<::coding::enum_index>& eindexa)
   {

      switch (etaskGroup)
      {
      case e_task_port:
      {
         //eindexa.add(::coding::e_index_preparing);
         //eindexa.add(::coding::e_index_downloading);
         //eindexa.add(::coding::e_index_configuring);
         eindexa.add(::coding::e_index_building);
         //eindexa.add(::coding::e_index_finishing);
      }
      break;
      case e_task_openssl:
      {
         eindexa.add(::coding::e_index_preparing);
         eindexa.add(::coding::e_index_downloading);
         eindexa.add(::coding::e_index_configuring);
         eindexa.add(::coding::e_index_building);
         eindexa.add(::coding::e_index_finishing);
      }
      break;
      case e_task_ffmpeg:
      {
         eindexa.add(::coding::e_index_preparing);
         eindexa.add(::coding::e_index_downloading);
         eindexa.add(::coding::e_index_configuring);
         eindexa.add(::coding::e_index_building);
         eindexa.add(::coding::e_index_finishing);
      }
         case e_task_ios_openssl:
         {
            eindexa.add(::coding::e_index_preparing);
            eindexa.add(::coding::e_index_downloading);
            eindexa.add(::coding::e_index_configuring);
            eindexa.add(::coding::e_index_building);
            eindexa.add(::coding::e_index_finishing);
         }
         break;
         case e_task_ios_ffmpeg:
         {
            eindexa.add(::coding::e_index_preparing);
            eindexa.add(::coding::e_index_downloading);
            eindexa.add(::coding::e_index_configuring);
            eindexa.add(::coding::e_index_building);
            eindexa.add(::coding::e_index_finishing);
         }
      break;
         default:
            break;
      }

   }


   void integration::task_group_stages(enum_task etaskGroup, ::string_array& straStage)
   {

      switch (etaskGroup)
      {
      case e_task_port:
      {
         straStage.add("port");
      }
      break;
      case e_task_openssl:
      {
         straStage.add("OpenSSL");
      }
      break;
      case e_task_ffmpeg:
      {
         straStage.add("x264");

         straStage.add("x265");

         straStage.add("FFMPEG");
      }
      break;
      default:
         break;

      }

   }


   void integration::task_group_tasks_ordinals(enum_task etaskGroup, ::numeric_array_base < ::coding::enum_task >& etaskaOrdinal)
   {
     
//      switch (etaskGroup)
//      {
//      case e_task_port:
//      case e_task_openssl:
//      case e_task_ffmpeg:
//      {
//#ifdef WINDOWS_DESKTOP
//         etaskaOrdinal.add(e_task_win32_debug);
//         etaskaOrdinal.add(e_task_win32_release);
//         etaskaOrdinal.add(e_task_win32_static_debug);
//         etaskaOrdinal.add(e_task_win32_static_release);
//         etaskaOrdinal.add(e_task_x64_debug);
//         etaskaOrdinal.add(e_task_x64_release);
//         etaskaOrdinal.add(e_task_x64_static_debug);
//         etaskaOrdinal.add(e_task_x64_static_release);
//#else
//         etaskaOrdinal.add(e_task_multi_arch_release);
//#endif
//      }
//      break;
//      case e_task_windows:
//      {
//
//         etaskaOrdinal.add(e_task_x64_release);
//
//      }
//      break;
//      default:
//         break;
//
//      }


   //}


   }


   bool integration::integrate_posix_with_result(const ::scoped_string & scopedstrDistroRelease)
   {

      throw ::interface_only();

      return false;

   }


   void integration::speak(::collection::index iIndex, ::collection::index iCount, const ::scoped_string& scopedstrText, int iExitCode)
   {

      ::string strMessage;

      if (!m_timeSpeechSpamControl.m_iSecond || m_timeSpeechSpamControl.elapsed() > 20_s)
      {

         strMessage = "Attention Release Builder! ";

      }

      if (iExitCode == 0)
      {

         strMessage.append_formatf("Step %d of %d succedeed... %s!!", iIndex, iCount, ::string(scopedstrText).c_str());

      }
      else
      {

         strMessage.append_formatf("Step %d of %d failed... %s!!", iIndex, iCount, ::string(scopedstrText).c_str());

      }

      _speak(strMessage);

   }


   void integration::_speak(const ::scoped_string& scopedstrText)
   {

      at_end_of_scope
      {

              m_bSpeaking = false;

      m_timeSpeechSpamControl.Now();

      };

      m_bSpeaking = true;

      system()->speak(scopedstrText, "en-us", e_gender_male);

   }


   void integration::integrate_task_group(enum_task etaskGroup, ::coding::item* pitem)
   {

      if (etaskGroup == e_task_none)
      {

         throw ::exception(error_wrong_state);

      }

      if (!sort_of_ok_earth_time_from_international_string(m_strIntegration))
      {

         throw ::exception(error_wrong_state, "bad integration (bad release date time, please set integration time with integration/handler)");

      }

      auto strReleaseTimeNoSpaces = m_strIntegration;

      strReleaseTimeNoSpaces.find_replace(" ", "_");

      auto& ptaskgroup = pitem->m_ptaskgroup;

      ptaskgroup = m_taskgroup[etaskGroup];

      ::file::path pathBuildFolder;

      pathBuildFolder = port_base_folder();
      pathBuildFolder /= ptaskgroup->m_strId;
      pathBuildFolder /= strReleaseTimeNoSpaces;

      on_start_task_group(ptaskgroup->m_etaskGroup);

      m_timeTopicBuildStart.Now();

      strReleaseTimeNoSpaces.find_replace(" ", "_");

      ptaskgroup->do_tasks(
         pathBuildFolder,
         [this](auto ptask)
         {

            return _do_task(ptask);

         });

      ptaskgroup->wait_to_complete();

      m_pimpactinterface->on_lines_change();

   }



   void integration::_defer_task_group(enum_task etaskGroup, ::pointer < task_group >* pptaskgroup)
   {

      if (etaskGroup == e_task_none)
      {

         throw ::exception(error_wrong_state);

      }

      if (pptaskgroup)
      {

         if (*pptaskgroup)
         {

            if ((*pptaskgroup)->m_etaskGroup == etaskGroup)
            {

               return;

            }

         }

      }

      auto ptaskgroup = allocateø::coding::task_group(
         this,
         etaskGroup,
         task_group_id(etaskGroup),
         task_group_name(etaskGroup));

      ptaskgroup->initialize(this);

      ptaskgroup->m_strSpeechName = task_group_speech_name(etaskGroup);

      task_group_indexes(ptaskgroup->m_etaskGroup, ptaskgroup->m_eindexa);
      task_group_stages(ptaskgroup->m_etaskGroup, ptaskgroup->m_straStage);

      ptaskgroup->m_strTopic1 = ptaskgroup->m_strName;

      auto& taskmap = ptaskgroup->m_taskmapTemplate;

      task_group_tasks_ordinals(ptaskgroup->m_etaskGroup, ptaskgroup->m_etaskaOrdinal);

      for (auto& etask : ptaskgroup->m_etaskaOrdinal)
      {
         ::string strOrdinalTask = m_straTaskOrdinal[etask];
#ifdef WINDOWS_DESKTOP
         ::string strApplicationBuildHelper("C:\\operating_system\\bin\\application_build_helper");
#elif defined(MACOS)
         ::string strApplicationBuildHelper(directory_system()->home() / "workspace/operating_system/tool-macos/bin/application_build_helper");
#else
         ::string strApplicationBuildHelper(directory_system()->home() / "bin/application_build_helper");
#endif
         auto ptask=
            allocateø task(
               ptaskgroup,
               ptaskgroup->m_strName + " " + strOrdinalTask,
               ptaskgroup->m_strSpeechName + " " + strOrdinalTask,
               strApplicationBuildHelper + " " + ptaskgroup->m_strId + " " + strOrdinalTask,
               etask
            );
         ptask->initialize(this);
         taskmap[etask] = ptask;
      }


      m_taskgroup[etaskGroup] = ptaskgroup;
      m_etaskaGroup.add(etaskGroup);

      if (pptaskgroup)
      {

         *pptaskgroup = ptaskgroup;

      }

   }


   // void integration::integrate_openssl(::coding::item* pitem)
   // {

   //    integrate_task_group(e_task_openssl, pitem);

   // }


   // void integration::integrate_ffmpeg(::coding::item* pitem)
   // {

   //    integrate_task_group(e_task_ffmpeg, pitem);

   // }


   int integration::_do_task(::coding::task* ptask)
   {

      ::file_pointer pfileLog;

      auto ploginterface = task_log(ptask->etask());

      ::string strTitle;

      ::string strTask;

      strTask.formatf("%02d", ptask->m_etaskOrdinal);

      auto strLabel = ptask->m_strLabel2;

      strTitle = strTask + "_" + strLabel;

      ptask->m_strTopic1 = strTitle;

      auto strLogName = strTitle;

      strLogName.find_replace(" ", "_");

      strLogName.find_replace("|", "_");

      auto strCommand = ptask->m_strCommand;

      int iExitCode = 0;

      ploginterface->m_iIndex = -1;

      ploginterface->m_iStage = 0;

      pfileLog = file()->get_writer(ptask->m_ptaskgroup->m_pathBuildFolder / "time-windows" / (strLabel + "_log") / (strLogName + ".txt"), ::file::e_open_share_deny_none);

      trace_function functionTrace = [ploginterface, pfileLog](auto etracelevel, auto& str, bool bCarriage)
         {

            ploginterface->on_trace(etracelevel, str, bCarriage);

            pfileLog->write(str + "\r\n");

         };

      {

         _synchronous_lock synchronouslock(ptask->synchronization());

         ptask->m_strTopic1 = ptask->m_strLabel2;

         ptask->m_strTopic12 = "Starting...";

      }

      functionTrace.set_timeout(8_hour);

      ptask->on_start();

      try
      {

         ::string strCommand;
         
         ::string strParallelization = ptask->m_ptaskgroup->m_strTaskParallelizationArguments;
         
         ::string strInteractiveness = ptask->m_ptaskgroup->m_strTaskInteractivenessArguments;
         
         strCommand = ptask->m_strCommand + strParallelization + strInteractiveness;
         
         iExitCode = node()->command_system(
            strCommand,
            functionTrace,
            ptask->m_ptaskgroup->m_pathBuildFolder);
            

         //preempt(1_s * mathematics()->random(1.0, 60.0));
//preempt(1_s * mathematics()->random(1.0, 5.0));

         //iExitCode = 1;

      }
      catch (...)
      {

      }

      return iExitCode;

   }

   enum_task integration::as_task_group(enum_integrate eintegrate)
   {

      auto eintegrateId = eintegrate & e_integrate_id_mask;

      switch (eintegrateId)
      {
      case e_integrate_openssl:
         return e_task_openssl;
      case e_integrate_ffmpeg:
         return e_task_ffmpeg;
      case e_integrate_port:
         return e_task_port;
      default:
         return e_task_none;
      }

   }


   bool integration::on_integrate(::coding::item* pitem)
   {

      auto etaskGroup = as_task_group(pitem->m_eintegrate);

      if (etaskGroup != e_task_none)
      {

         integrate_task_group(etaskGroup, pitem);

         return true;

      }

      return false;

   }

   ::file::path integration::port_base_folder()
   {

      return directory_system()->home() / "port";

   }
   bool integration::on_packaging(::string& strAppId, ::string& strTarget, ::string& strSource)
   {

      return false;
   }
   //::string integration::macos_archive(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme)
   //{
   // 
   //   return {};
   //   
   //}

   void integration::prepare_build()
   {

   }

   void integration::call_integrate_main(::coding::item* pitem)
   {

      auto strSystemAmbientReleaseArchitecture = m_poperatingsystemsummary->m_strSystemAmbientReleaseArchitecture;

      if (m_strRepositoryPath.trimmed().is_empty())
      {

         ::string strError;

         strError = "Integration Folder cannot be empty for building \"" + strSystemAmbientReleaseArchitecture + "\".";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         post(pmessageboxpayload);

         return;

      }
      else if (!directory_system()->is(m_strRepositoryPath))
      {

         ::string strError;

         strError = "Specified path (\"" + m_strRepositoryPath + "\") for Integration Folder doesn't exist or isn't folder";

         m_straError.add(strError);

         auto pmessageboxpayload = message_box(strError, "Integration Failed");

         post(pmessageboxpayload);

         return;

      }

      integrate_main2(pitem);

   }


   void integration::integrate_main2(::coding::item* pitem)
   {

   }


   void integration::on_initialize_application_build_tool_operating_system_integrate_list()
   {


   }


   void integration::on_initialize_application_build_tool_task_groups()
   {


   }


   void integration::integrate_new_release_prefix_windows()
   {


   }


   void integration::integrate_port(::coding::item* pitem)
   {

      integrate_task_group(::coding::e_task_port, pitem);

   }


#ifdef MACOS


   ::string integration::macos_archive(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrScheme)
   {
      
      return {};
      
   }


#endif


} // namespace coding



