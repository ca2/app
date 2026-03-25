#include "framework.h"
#include "code.h"
#include "code_impact.h"
#include "code_application.h"
#include "install.h"
#include "install_impact_interface.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/handler/topic.h"
#include "acme/user/micro/user.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/frame_interaction.h"
#include "apex/platform/node.h"
#include "axis/user/user/line_layout.h"


#include <math.h>


namespace coding
{


   impact::impact() :
   m_propertyMainRemark((::user::text *) this, "main_remark")
   {

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);


   }


   impact::~impact()
   {

   }


   //void impact::assert_ok() const
   //{

   //   user::box::assert_ok();

   //}


   //void impact::dump(dump_context & dumpcontext) const
   //{

   //   user::box::dump(dumpcontext);

   //}


   void impact::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      USER_MESSAGE_LINK(::user::e_message_create,psender,this,&impact::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, psender, this, &impact::on_message_destroy);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      constructø(m_pfont);

      m_pfont->create_font(e_font_sans_ui, 18.0_pt);

      m_pcode = m_papp->code(this->id());

      m_pcode->m_pimpact = this;

      m_iButtonHeight = 30;
      m_iButtonPadding = 10;
      m_iButtonCount = 3;

      m_iAllButtonsHeight = m_iButtonCount * (m_iButtonHeight + m_iButtonPadding) + m_iButtonPadding;

      m_plinelayoutMainColumn = create_line_layout(this, e_orientation_vertical);

      m_pstillCodeTitle = create_title1(m_plinelayoutMainColumn, "Code with:");

      update_main_remark(e_source_initialize);

      m_pstillMainRemark = create_label(m_plinelayoutMainColumn, m_propertyMainRemark);

      m_papp->m_propertyCloudDataProvider.property_changed() += [this](auto & propertychanged)
      {

         update_main_remark(propertychanged.m_actioncontext);

      };

      if(is_initial_setup())
      {

         m_pstillMainStatus1 = create_label(m_plinelayoutMainColumn, "Choose Git Credential Manager, SSH or Standard.");
         m_pstillMainStatus2 = create_label(m_plinelayoutMainColumn, "This is initial page...");

         create_release_install_buttons(m_plinelayoutMainColumn);

      }
      else
      {

         m_pstillMainStatus1 = create_label(m_plinelayoutMainColumn, "");
         m_pstillMainStatus2 = create_label(m_plinelayoutMainColumn, "");

         if (m_papp->m_strMayNeedRestartStatus.has_character())
         {

            auto pimpact = this;

            auto pstill = pimpact->m_pstillMainStatus2;

            pstill->set_window_text(m_papp->m_strMayNeedRestartStatus);

            //pimpact->m_bNeedPerformLayout = true;

            //pimpact->set_need_layout();

            //pimpact->set_need_redraw();

            //pimpact->post_redraw();

         }

         create_main_screen(m_plinelayoutMainColumn);

      }

      set_need_redraw();

      post_redraw();

   }


   bool impact::is_initial_setup() const
   {

      return this->id() == as_domainid(e_mode_initial_setup);

   }


   bool impact::is_gcm() const
   {

      return this->id() == as_domainid(e_mode_gcm);

   }


   bool impact::is_ssh() const
   {

      return this->id() == as_domainid(e_mode_ssh);

   }


   bool impact::is_std() const
   {

      return this->id() == as_domainid(e_mode_standard);

   }


   void impact::update_main_remark(const ::action_context & actioncontext)
   {

      if(is_std())
      {

         ::file::path pathSourceFolder = m_papp->cloud_folder() / ".ssh";

         ::string strMessage;

         strMessage = "Do you get id_auth, id_auth.pub, id_sign and id_sign.pub at " + pathSourceFolder;

         m_propertyMainRemark.set_property(strMessage, actioncontext);

         m_bNeedPerformLayout = true;

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

   }



   void impact::on_message_destroy(::message::message * pmessage)
   {

   }


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == "simple_checkbox")
      {

         set_need_redraw();

      }

      ::user::impact::handle(ptopic, phandlercontext);

   }


   void impact::create_main_screen(::user::interaction* puserinteractionParent)
   {

      // auto pcolumn = puserinteractionParent;

      _synchronous_lock synchronouslock(this->synchronization());

#ifdef WINDOWS

      if (is_std())
      {

         auto poptionCloud = m_pcode->create_option(
            m_papp->m_propertyCloudDataProvider,
            puserinteractionParent,
            m_papp->m_atomaCloudDataProviderOptions,
            m_papp->m_straCloudDataProviderOptionsNames);

         poptionCloud->set_size({ 200 * m_papp->m_atomaCloudDataProviderOptions.size(), 50 });

         auto poptionBrowser = m_pcode->create_option(
            m_papp->m_propertyBrowser,
            puserinteractionParent,
            m_papp->m_atomaBrowser,
            m_papp->m_straBrowserNames);

         poptionBrowser->set_size({ 200 * m_papp->m_atomaBrowser.size(), 50});

         auto poptionRepository = m_pcode->create_option(
            m_papp->m_propertyRepository,
            puserinteractionParent,
            m_papp->m_atomaRepository,
            m_papp->m_straRepositoryNames);

         poptionRepository->set_size({ 200 * m_papp->m_atomaRepository.size(), 50 });

         m_pcode->create_install(::coding::e_install_storage_windows, puserinteractionParent, {});
         //m_pcode->create_install(::coding::e_install_storage_universal_windows, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, { ::coding::e_install_browser });
         m_pcode->create_install(::coding::e_install_setup_folders, puserinteractionParent, {}, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_visual_studio, puserinteractionParent, {},  { ::coding::e_install_browser,::coding::e_install_visual_studio_code, ::coding::e_install_git_scm , ::coding::e_install_setup_folders, ::coding::e_install_tortoise_git, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, { ::coding::e_install_setup_folders }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, { ::coding::e_install_git_scm, ::coding::e_install_setup_folders });
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, { ::coding::e_install_tool_os }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_tortoise_git, puserinteractionParent, { ::coding::e_install_git_scm,::coding::e_install_patch_shell }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, { ::coding::e_install_git_scm,::coding::e_install_patch_shell }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm });
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, { ::coding::e_install_git_scm, ::coding::e_install_tool_os, ::coding::e_install_patch_shell });

      }
      else if (is_ssh())
      {

         // m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, { ::coding::e_install_browser });
         // m_pcode->create_install(::coding::e_install_visual_studio, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_tortoise_git, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {});

         auto poptionCloud = m_pcode->create_option(
            m_papp->m_propertyCloudDataProvider,
            puserinteractionParent,
            m_papp->m_atomaCloudDataProviderOptions,
            m_papp->m_straCloudDataProviderOptionsNames);

         poptionCloud->set_size({ 200 * m_papp->m_atomaCloudDataProviderOptions.size(), 50 });

         auto poptionBrowser = m_pcode->create_option(
            m_papp->m_propertyBrowser,
            puserinteractionParent,
            m_papp->m_atomaBrowser,
            m_papp->m_straBrowserNames);

         poptionBrowser->set_size({ 200 * m_papp->m_atomaBrowser.size(), 50});

         auto poptionRepository = m_pcode->create_option(
            m_papp->m_propertyRepository,
            puserinteractionParent,
            m_papp->m_atomaRepository,
            m_papp->m_straRepositoryNames);

         poptionRepository->set_size({ 200 * m_papp->m_atomaRepository.size(), 50 });

         m_pcode->create_install(::coding::e_install_storage_windows, puserinteractionParent, {});
         //m_pcode->create_install(::coding::e_install_storage_universal_windows, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, { ::coding::e_install_browser });
         m_pcode->create_install(::coding::e_install_setup_folders, puserinteractionParent, {}, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_visual_studio, puserinteractionParent, {},  { ::coding::e_install_browser,::coding::e_install_visual_studio_code, ::coding::e_install_git_scm , ::coding::e_install_setup_folders, ::coding::e_install_tortoise_git, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, { ::coding::e_install_setup_folders }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, { ::coding::e_install_git_scm, ::coding::e_install_setup_folders });
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, { ::coding::e_install_tool_os }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_tortoise_git, puserinteractionParent, { ::coding::e_install_git_scm,::coding::e_install_patch_shell }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, { ::coding::e_install_git_scm,::coding::e_install_patch_shell }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm });
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, { ::coding::e_install_git_scm, ::coding::e_install_tool_os, ::coding::e_install_patch_shell });

      }
      else if (is_gcm())
      {

         auto poptionBrowser = m_pcode->create_option(
            m_papp->m_propertyBrowser,
            puserinteractionParent,
            m_papp->m_atomaBrowser,
            m_papp->m_straBrowserNames);

         poptionBrowser->set_size({ 200 * m_papp->m_atomaBrowser.size(), 50 });

         m_pcode->create_install(::coding::e_install_storage_windows, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, { ::coding::e_install_browser });
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, { }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code });
         m_pcode->create_install(::coding::e_install_tortoise_git, puserinteractionParent, { ::coding::e_install_git_scm }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, { ::coding::e_install_git_scm }, { ::coding::e_install_browser, ::coding::e_install_visual_studio_code, ::coding::e_install_git_scm });
         m_pcode->create_install(::coding::e_install_visual_studio, puserinteractionParent, { ::coding::e_install_browser,::coding::e_install_visual_studio_code, ::coding::e_install_git_scm , ::coding::e_install_tortoise_git, ::coding::e_install_smart_git });
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, { ::coding::e_install_git_scm });
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, { ::coding::e_install_git_scm, ::coding::e_install_tool_os });

      }

#elif defined(MACOS)
      
      
      if(is_std())
      {

         auto poptionCloud = m_pcode->create_option(
   m_papp->m_propertyCloudDataProvider,
   puserinteractionParent,
   m_papp->m_atomaCloudDataProviderOptions,
   m_papp->m_straCloudDataProviderOptionsNames);

         poptionCloud->set_size({ 200 * m_papp->m_atomaCloudDataProviderOptions.size(), 50 });

         auto poptionBrowser = m_pcode->create_option(
   m_papp->m_propertyBrowser,
   puserinteractionParent,
   m_papp->m_atomaBrowser,
   m_papp->m_straBrowserNames);

         poptionBrowser->set_size({ 200 * m_papp->m_atomaBrowser.size(), 50});

         auto poptionRepository = m_pcode->create_option(
            m_papp->m_propertyRepository,
            puserinteractionParent,
            m_papp->m_atomaRepository,
            m_papp->m_straRepositoryNames);

         poptionRepository->set_size({ 200 * m_papp->m_atomaRepository.size(), 50 });

         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, {::coding::e_install_browser});
         m_pcode->create_install(::coding::e_install_cloud_data_provider, puserinteractionParent, {},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_setup_folders, puserinteractionParent, {::coding::e_install_cloud_data_provider},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_xcode, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {::coding::e_install_setup_folders});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {::coding::e_install_smart_git});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_patch_shell});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_scm, ::coding::e_install_setup_folders});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell,::coding::e_install_git_scm, ::coding::e_install_setup_folders});

      }
      else if(is_ssh())
      {

         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_xcode, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_credential_manager});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell});

      }
      else if(is_gcm())
      {
         //m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_xcode, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_git_credential_manager, puserinteractionParent, {::coding::e_install_git_scm});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_credential_manager});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell});
      }


      
#else

      if(is_std())
      {

         auto poptionCloud = m_pcode->create_option(
   m_papp->m_propertyCloudDataProvider,
   puserinteractionParent,
   m_papp->m_atomaCloudDataProviderOptions,
   m_papp->m_straCloudDataProviderOptionsNames);

         poptionCloud->set_size({ 200 * m_papp->m_atomaCloudDataProviderOptions.size(), 50 });

         auto poptionBrowser = m_pcode->create_option(
   m_papp->m_propertyBrowser,
   puserinteractionParent,
   m_papp->m_atomaBrowser,
   m_papp->m_straBrowserNames);

         poptionBrowser->set_size({ 200 * m_papp->m_atomaBrowser.size(), 50});

         auto poptionRepository = m_pcode->create_option(
            m_papp->m_propertyRepository,
            puserinteractionParent,
            m_papp->m_atomaRepository,
            m_papp->m_straRepositoryNames);

         poptionRepository->set_size({ 200 * m_papp->m_atomaRepository.size(), 50 });

         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, {::coding::e_install_browser});
         m_pcode->create_install(::coding::e_install_cloud_data_provider, puserinteractionParent, {},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_setup_folders, puserinteractionParent, {::coding::e_install_cloud_data_provider},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {::coding::e_install_setup_folders});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {::coding::e_install_smart_git});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_patch_shell});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_scm, ::coding::e_install_setup_folders});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell,::coding::e_install_git_scm, ::coding::e_install_setup_folders});

      }
      else if(is_ssh())
      {

         // m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_deps});
         // m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {});
         // m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         // m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_tool_os});
         // m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_credential_manager});
         // m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell});

         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {}, {::coding::e_install_browser});
         //m_pcode->create_install(::coding::e_install_cloud_data_provider, puserinteractionParent, {},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         //m_pcode->create_install(::coding::e_install_setup_folders, puserinteractionParent, {::coding::e_install_cloud_data_provider},{::coding::e_install_browser, ::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {::coding::e_install_browser,::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {::coding::e_install_smart_git,::coding::e_install_browser,::coding::e_install_visual_studio_code});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_scm});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_patch_shell});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell});
         m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_repositories});

      }
      else if(is_gcm())
      {
         //m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_browser, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_visual_studio_code, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_jetbrains_clion, puserinteractionParent, {::coding::e_install_deps});
         m_pcode->create_install(::coding::e_install_git_scm, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_git_credential_manager, puserinteractionParent, {::coding::e_install_git_scm});
         m_pcode->create_install(::coding::e_install_smart_git, puserinteractionParent, {});
         m_pcode->create_install(::coding::e_install_patch_shell, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_deps, puserinteractionParent, {::coding::e_install_tool_os});
         m_pcode->create_install(::coding::e_install_tool_os, puserinteractionParent, {::coding::e_install_git_credential_manager});
         m_pcode->create_install(::coding::e_install_repositories, puserinteractionParent, {::coding::e_install_patch_shell});
      }


#endif


      //if (node()->_is_visual_studio_installed())
      //{

      //   //m_pcheckboxVisualStudio->enable_window(false);

      //   //m_pcheckboxVisualStudio->set_check(true, e_source_initialize);

      //}
      //else
      //{


      //}


      //::string strGscmCheck;

      //if (m_papp->is_git_scm_installed())
      //{

      //   strGscmCheck = "☑";

      //}

      //auto plineGscm = create_line_layout(pcolumn, e_orientation_horizontal);

      //plineGscm->m_ealignrelativeOrthogonal = ::user::line_layout::e_align_relative_base_bottom_line;

      //m_pstillGitScmTitle = create_title2(plineGscm, strGscmCheck + "git");

      //m_pstillGitScmRemark = create_label<::user::still>(plineGscm, "Required for downloading and managing source.");

      //::string strAddGscm;

      ////if (m_papp->is_git_installed())
      ////{

      ////   strAddGscm = " (already installed)";

      ////}


      //if (!m_papp->is_git_scm_installed())
      //{

      //   m_pstillGitScmStatus = create_label(plineGscm, "Not installed.");

      //   m_pcheckboxGitScm = create_check_box_with_label(plineGscm, "Install");

      //   m_pcheckboxGitScm->set_check(e_check_checked, e_source_initialize);

      //   m_pcheckboxGitScm->m_callbackOnCheck = [this](auto pcheckbox)
      //      {

      //         update_start_button();

      //      };

      //}


      //::string strTortoiseGitCheck;

      //if (m_papp->is_tortoise_git_installed())
      //{

      //   strTortoiseGitCheck = "☑";

      //}

      //auto plineTgit = create_line_layout(pcolumn, e_orientation_horizontal);

      //plineTgit->m_ealignrelativeOrthogonal = ::user::line_layout::e_align_relative_base_bottom_line;

      //m_pstillTortoiseGitTitle = create_title2(plineTgit, strTortoiseGitCheck + "TortoiseGit");

      //m_pstillTortoiseGitRemark = create_label(plineTgit, "Recommended for File Explorer Right Click[Context] Menu and Icon Overlay.");

      //if (!m_papp->is_tortoise_git_installed())
      //{

      //   m_pstillTortoiseGitStatus = create_label(plineTgit, "Not installed.");

      //   m_pcheckboxTortoiseGit = create_check_box_with_label(plineTgit, "Install");
      //   m_pcheckboxTortoiseGit->set_check(e_check_checked, e_source_initialize);

      //   m_pcheckboxTortoiseGit->m_callbackOnCheck = [this](auto pcheckbox)
      //      {

      //         update_start_button();

      //      };

      //   //m_pcheckboxTortoiseGit->enable_window(false);

      //   //m_pcheckboxTortoiseGit->set_check(true, e_source_initialize);

      ////}
      ////else
      ////{



      //}

      //::string strSmartGitCheck;

      //if (m_papp->is_smart_git_installed())
      //{

      //   strSmartGitCheck = "☑";

      //}

      //auto plineSgit = create_line_layout(pcolumn, e_orientation_horizontal);

      //plineSgit->m_ealignrelativeOrthogonal = ::user::line_layout::e_align_relative_base_bottom_line;

      //m_pstillSmartGitTitle = create_title2(plineSgit, strSmartGitCheck + "SmartGit");

      //m_pstillSmartGitRemark = create_label(plineSgit, "Recommended IDE for Git Source Control.");


      //if (!m_papp->is_smart_git_installed())
      //{

      //   m_pstillSmartGitStatus = create_label(plineSgit, "Not installed.");

      //   m_pcheckboxSmartGit = create_check_box_with_label(plineSgit, "Install");

      //   m_pcheckboxSmartGit->set_check(e_check_checked, e_source_initialize);

      //   m_pcheckboxSmartGit->m_callbackOnCheck = [this](auto pcheckbox)
      //      {

      //         update_start_button();

      //      };
      //   //m_pcheckboxTortoiseGit->enable_window(false);

      //   //m_pcheckboxTortoiseGit->set_check(true, e_source_initialize);

      ////}
      ////else
      ////{



      //}
      ////m_pcheckboxTortoiseGit = create_check_box_with_label<::user::check_box>(pcolumn, "TortoiseGit (recommended for File Explorer Right Click[Context] Menu and Icon Overlay)" + strTortoiseGit);

      ////if (node()->_is_tortoise_git_installed())
      ////{

      ////   m_pcheckboxTortoiseGit->enable_window(false);

      ////   m_pcheckboxTortoiseGit->set_check(true, e_source_initialize);

      ////}
      ////else
      ////{



      ////}
      ///

      create_release_install_buttons(m_plinelayoutMainColumn);

      m_papp->defer_release_install();

      //auto papp = get_app();

      //papp->m_pimpact = this;

      //constructø(m_pfontTitle);

      //m_pfontTitle->create_font("Helvetica", 36.0_pt, e_font_weight_bold);

      //papp->m_strMainStatus = "Setting up coding...";

      //papp->fork([this, papp]()
      //   {

      //      papp->setup_coding();

      //   });

      ////parent_frame()->display(e_display_zoomed);

      ////parent_frame()->order_top();

      ////parent_frame()->set_need_redraw();

      ////parent_frame()->post_redraw();

      m_papp->on_change_current_cloud_data_provider(e_source_initialize);

      m_papp->on_change_current_browser(e_source_initialize);

      m_papp->on_change_current_repository(e_source_initialize);

   }


   void impact::update_start_button()
   {

      if(!m_pbuttonStart)
      {

         return;

      }

      print_line("code impact update_start_button");

      bool bCanStartInstalling = m_papp->can_start_installing();

      printf_line("bCanStartInstalling %d", (int) bCanStartInstalling);

      bool bInstalling = m_papp->is_installing();

      printf_line("bInstalling %d", (int) bInstalling);

      m_pbuttonStart->enable_window(bCanStartInstalling && !bInstalling);

   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //auto papp = get_app();

      //if (papp->m_bFirstStageOk)
      //{

      //   return;

      //}

      //double dStdH = 1080.0;

      //double dH = this->height();

      //double rate = dH / dStdH;

      //::rectangle_i32 rectangle;

      //::draw2d::save_context savecontext(pgraphics);

      //::geometry2d::matrix matrix;

      //matrix.scale(rate, rate);

      //pgraphics->set(matrix);

      //rectangle = this->rectangle();

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //auto pstyle = get_style(pgraphics);

      //auto color = get_color(pstyle, ::e_element_background);

      //pgraphics->fill_rectangle(rectangle, color);

      //color = get_color(pstyle, ::e_element_text);

      //pgraphics->set_text_color(color);

      ////pgraphics->set(m_pfontTitle);

      ////pgraphics->text_out({ 20, 20 }, "Code!!");

      //pgraphics->set(m_pfont);

      //int iGroupCount = 6;

      //double x = 20.0;

      //double y = m_pstillCodeTitle->bottom();

      //double Δ = (dStdH - 80.0 - (double)m_iAllButtonsHeight / rate) / (double) iGroupCount;

      //pgraphics->text_out({ x, y }, papp->m_strMainStatus + papp->m_strMainStatus2
      //+ papp->m_strMayNeedRestartStatus);

      //y += Δ;

      //
      //   pgraphics->text_out({ x, y }, papp->m_strFirstStageStatus);
      //
      //   //return;
      //
      ////}

      ////pgraphics->text_out({ x, y }, papp->m_strSourceStatus + papp->m_strSourceStatus2);

      ////y += Δ;

      ////pgraphics->text_out({ x, y }, papp->m_strGraphicalIdeStatus + papp->m_strGraphicalIdeStatus2);

      ////y += Δ;

      ////pgraphics->text_out({ x, y }, papp->m_strGitScmStatus + papp->m_strGitScmStatus2);

      ////y += Δ;

      ////pgraphics->text_out({ x, y }, papp->m_strTortoiseGitStatus + papp->m_strTortoiseGitStatus2);

      ////y += Δ;

      ////pgraphics->text_out({ x, y }, papp->m_strBinariesStatus + papp->m_strBinariesStatus2);

   }


   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = this->rectangle();

      if(rectangleClient.is_empty())
      {

         return;

      }

      //m_psimpledrawing->m_rectangle = rectangleClient;

      //m_psimpledrawing->on_layout(pgraphics);

      //auto r = rectangleClient;

      //r.deflate(m_iButtonPadding, m_iButtonPadding);

      //if (m_pbuttonOpenBaseFolder)
      //{

      //   r.top() = r.bottom() - m_iButtonHeight;

      //   m_pbuttonOpenBaseFolder->place(r);

      //   r.bottom() -= (m_iButtonPadding + m_iButtonHeight);

      //}

      //if (m_pbuttonOpenSolutionFolder)
      //{

      //   r.top() = r.bottom() - m_iButtonHeight;

      //   m_pbuttonOpenSolutionFolder->place(r);

      //   r.bottom() -= (m_iButtonPadding + m_iButtonHeight);

      //}

      //if (m_pbuttonLaunchSolution)
      //{

      //   r.top() = r.bottom() - m_iButtonHeight;

      //   m_pbuttonLaunchSolution->place(r);

      //   r.bottom() -= (m_iButtonPadding + m_iButtonHeight);

      //}


      ////if (m_pbuttonDebugProject)
      ////{

      ////   r.top = r.bottom - m_iButtonHeight;

      ////   m_pbuttonDebugProject->place(r);

      ////   r.bottom -= (m_iButtonPadding + m_iButtonHeight);

      ////}

   }


   void impact::create_release_install_buttons(::user::interaction* puserinteractionParent)
   {

      if (m_pbuttonLaunchSolution)
      {

         return;

      }

      int iButtonCount;

      ::file::path path;

#if defined(WINDOWS)

      iButtonCount = 3;

      path = "C:/simple/solution-windows/simple.sln";

#else

      iButtonCount = 2;

      auto pathSimpleFolder = m_papp->get_repository_path(::coding::e_repository_simple);

      path = pathSimpleFolder / "CMakeLists.txt";

#endif

      //defer_constructø(m_pbuttonDebugProject);

      //m_pbuttonDebugProject->create_control(this, "button_launch_solution");

      //m_pbuttonDebugProject->display();

      //m_pbuttonDebugProject->set_window_text("Debug \"_app_simple_drawing\"");

      //m_pbuttonDebugProject->add_message_handler("on_click",
      //   [this, path](::message::message* pmessage)
      //   {

      //      m_papplicationForConsumer->start_debugging_project();


      //   }, false);

      if(!is_initial_setup())
      {

         m_pbuttonStart = create_button<::user::button>(puserinteractionParent, "Start");

         update_start_button();

         m_pbuttonStart->m_callbackOnClick = [this](auto, auto, auto)
         {

            m_pcode->m_strMainStatus = "Setting up coding...";

            m_papp->fork([this]()
               {

                  m_pcode->setup_coding();

               });

            return true;

         };

      }

      m_pbuttonLaunchSolution = create_button<::user::button>(puserinteractionParent, "Open \"" + path + "\"");

      m_pbuttonLaunchSolution->add_message_handler(::user::e_message_click,
         [this,path](::message::message * pmessage)
      {

         node()->file_open(path);


      });

      m_pbuttonOpenSolutionFolder = create_button<::user::button>(puserinteractionParent, "Open \"" + path.folder() + "\"");

      m_pbuttonOpenSolutionFolder->add_message_handler(::user::e_message_click,
         [this, path](::message::message* pmessage)
         {

            node()->file_open(path.folder());


         });

      if(iButtonCount >= 3)
      {
         m_pbuttonOpenBaseFolder = create_button<::user::button>(puserinteractionParent, "Open \"" + path.folder().folder() + "\"");

         m_pbuttonOpenBaseFolder->add_message_handler(::user::e_message_click,
            [this, path](::message::message* pmessage)
            {

               node()->file_open(path.folder().folder());


            });
      }

      m_pathReleaseInstall = path;

      //m_pbuttonDebugProject->enable_window(false);

      m_pbuttonLaunchSolution->enable_window(false);

      m_pbuttonOpenSolutionFolder->enable_window(false);

      if(iButtonCount >= 3)
      {
         m_pbuttonOpenBaseFolder->enable_window(false);
      }

      //set_need_layout();

      //set_need_redraw();

      //post_redraw();

      //fork([this]()
      //   {

      //      while (::task_get_run())
      //      {

      //         update_debug_project_enable();

      //         preempt(300_ms);

      //      }

      //   });


   }


   void impact::defer_enable_release_install()
   {

      bool bVisualStudioOk = m_papp->is_installed(::coding::e_install_visual_studio, true);

      bool bAppSimpleSourceOk = m_papp->is_installed(::coding::e_install_repositories, true);

      if (m_pbuttonLaunchSolution)
      {

         m_pbuttonLaunchSolution->enable_window(bVisualStudioOk && bAppSimpleSourceOk);

      }

      if (m_pbuttonOpenSolutionFolder)
      {

         m_pbuttonOpenSolutionFolder->enable_window(bAppSimpleSourceOk);

      }

      if (m_pbuttonOpenBaseFolder)
      {

         m_pbuttonOpenBaseFolder->enable_window(bAppSimpleSourceOk);

      }

      set_need_redraw();

      post_redraw();

   }





} // namespace coding



