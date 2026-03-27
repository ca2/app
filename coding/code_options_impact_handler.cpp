#include "framework.h"
#include "document.h"
#include "code_options_impact_handler.h"
#include "item.h"
#include "integration.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aqua/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"
#include "aura/message/user.h"
#include "aura/user/user/plain_edit.h"
#include "axis/user/user/line_layout.h"
#include "berg/user/user/impact_system.h"


namespace coding
{



   options_impact_handler::options_impact_handler()
   {


   }


   options_impact_handler::~options_impact_handler()
   {

   }


   void options_impact_handler::create_options_impact(::user::interaction *pinteraction)
   {


//      auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//      m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization = create_check_box(pline, "checkbox_exclude_all_folders_except_box_folder_from_dropbox_synchronization");
//
//      m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->set_check_property(m_papp->m_checkExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization);
//
//      m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->set_size({24, 24});
//
//      m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization= create_label(pline, "Exclude all folders except \"box\" folder from dropbox synchronization");
//
//      m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization->m_bAutoResize = true;


//      constructø(m_pbuttonNewReleasePrefix);
//      constructø(m_pbuttonCheckout);
//      constructø(m_pbuttonApplicationList);
//      constructø(m_pbuttonPrepareApplications);
//      constructø(m_pbuttonProjectList);
//      constructø(m_pbuttonPrepareProjects);
//      constructø(m_pbuttonCmake);
//      constructø(m_pbuttonClean);
//
//      constructø(m_pstillNewReleasePrefix);
//      constructø(m_pstillCheckout);
//      constructø(m_pstillApplicationList);
//      constructø(m_pstillPrepareApplications);
//      constructø(m_pstillProjectList);
//      constructø(m_pstillPrepareProjects);
//      constructø(m_pstillCmake);
//      constructø(m_pstillClean);
//
//
//      //      int leftButton = 10;
//      int widthButton = 100;
////      int leftStill = 120;
////      int widthStill = 400;
////
////      int y = 10;
//      int controlHeight = 25;
////      int controlSpacing = 5;
////
////      m_pbuttonCheckout->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
//
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonNewReleasePrefix->create_control(pline, "button_new_release_prefix");
//         m_pbuttonNewReleasePrefix->set_size(::int_size(widthButton, controlHeight));
//         m_pstillNewReleasePrefix->create_control(pline, "still_new_release_prefix");
//         m_pstillNewReleasePrefix->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonCheckout->create_control(pline, "button_checkout");
//         m_pbuttonCheckout->set_size(::int_size(widthButton, controlHeight));
//         m_pstillCheckout->create_control(pline, "still_checkout");
//         m_pstillCheckout->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonApplicationList->create_control(pline, "button_application_list");
//         m_pbuttonApplicationList->set_size(::int_size(widthButton, controlHeight));
//         m_pstillApplicationList->create_control(pline, "still_application_list");
//         m_pstillApplicationList->m_bAutoResize = true;
//
//      }
//
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonPrepareApplications->create_control(pline, "button_prepare_applications");
//         m_pbuttonPrepareApplications->set_size(::int_size(widthButton, controlHeight));
//         m_pstillPrepareApplications->create_control(pline, "still_prepare_applications");
//         m_pstillPrepareApplications->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonProjectList->create_control(pline, "button_project_list");
//         m_pbuttonProjectList->set_size(::int_size(widthButton, controlHeight));
//         m_pstillProjectList->create_control(pline, "still_project_list");
//         m_pstillProjectList->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonPrepareProjects->create_control(pline, "button_prepare_projects");
//         m_pbuttonPrepareProjects->set_size(::int_size(widthButton, controlHeight));
//         m_pstillPrepareProjects->create_control(pline, "still_prepare_projects");
//         m_pstillPrepareProjects->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonCmake->create_control(pline, "button_cmake");
//         m_pbuttonCmake->set_size(::int_size(widthButton, controlHeight));
//         m_pstillCmake->create_control(pline, "still_cmake");
//         m_pstillCmake->m_bAutoResize = true;
//
//      }
//
//      {
//
//         auto pline = create_line_layout(pinteraction, e_orientation_horizontal);
//
//         m_pbuttonClean->create_control(pline, "button_clean");
//         m_pbuttonClean->set_size(::int_size(widthButton, controlHeight));
//         m_pstillClean->create_control(pline, "still_clean");
//         m_pstillClean->m_bAutoResize = true;
//
//
//      }
//
//
//
//      m_pstillNewReleasePrefix->set_window_text("New Release Prefix");
//      m_pstillCheckout->set_window_text("Checkout");
//      m_pstillApplicationList->set_window_text("Application List");
//      m_pstillPrepareApplications->set_window_text("Prepare Applications");
//      m_pstillProjectList->set_window_text("Project List");
//      m_pstillPrepareProjects->set_window_text("Prepare Projects");
//      m_pstillCmake->set_window_text("Cmake");
//      m_pstillClean->set_window_text("Clean");
//
//      auto pintegration = get_integration();
//
//      if (pintegration)
//      {
//
//         m_pbuttonNewReleasePrefix->set_check(pintegration->m_bNewReleasePrefix, ::e_source_initialize);
//         m_pbuttonCheckout->set_check(pintegration->m_bCheckout, ::e_source_initialize);
//         m_pbuttonApplicationList->set_check(pintegration->m_bApplicationList, ::e_source_initialize);
//         m_pbuttonPrepareApplications->set_check(pintegration->m_bPrepareApplications, ::e_source_initialize);
//         m_pbuttonProjectList->set_check(pintegration->m_bProjectList, ::e_source_initialize);
//         m_pbuttonPrepareProjects->set_check(pintegration->m_bPrepareProjects, ::e_source_initialize);
//         m_pbuttonCmake->set_check(pintegration->m_bCmake, ::e_source_initialize);
//         m_pbuttonClean->set_check(pintegration->m_bClean, ::e_source_initialize);
//
//
//         m_pbuttonNewReleasePrefix->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bNewReleasePrefix = m_pbuttonNewReleasePrefix->bcheck();
//                  m_papp->datastream()->set("new_release_prefix", pintegration->m_bNewReleasePrefix);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//         m_pbuttonCheckout->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bCheckout = m_pbuttonCheckout->bcheck();
//                  m_papp->datastream()->set("checkout", pintegration->m_bCheckout);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//         m_pbuttonApplicationList->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bApplicationList = m_pbuttonApplicationList->bcheck();
//                  m_papp->datastream()->set("application_list", pintegration->m_bApplicationList);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//         m_pbuttonPrepareApplications->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bPrepareApplications = m_pbuttonPrepareApplications->bcheck();
//                  m_papp->datastream()->set("prepare_applications", pintegration->m_bPrepareApplications);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//         m_pbuttonProjectList->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bProjectList = m_pbuttonProjectList->bcheck();
//                  m_papp->datastream()->set("project_list", pintegration->m_bProjectList);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//         m_pbuttonPrepareProjects->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bPrepareProjects = m_pbuttonPrepareProjects->bcheck();
//                  m_papp->datastream()->set("prepare_projects", pintegration->m_bPrepareProjects);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//         m_pbuttonCmake->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bCmake = m_pbuttonCmake->bcheck();
//                  m_papp->datastream()->set("cmake", pintegration->m_bCmake);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//         m_pbuttonClean->add_message_handler("on_click",
//            [this](auto pmessage)
//            {
//
//               auto pintegration = get_integration();
//
//               if (pintegration)
//               {
//
//                  pintegration->m_bClean = m_pbuttonClean->bcheck();
//                  m_papp->datastream()->set("clean", pintegration->m_bClean);
//
//               }
//
//               pmessage->m_bRet = true;
//
//            }, false);
//
//
//
//      }
//
//      m_pbuttonNewReleasePrefix->display();
//      m_pbuttonCheckout->display();
//      m_pbuttonApplicationList->display();
//      m_pbuttonPrepareApplications->display();
//      m_pbuttonProjectList->display();
//      m_pbuttonPrepareProjects->display();
//      m_pbuttonCmake->display();
//      m_pbuttonClean->display();
//      m_pstillNewReleasePrefix->display();
//      m_pstillCheckout->display();
//      m_pstillApplicationList->display();
//      m_pstillPrepareApplications->display();
//      m_pstillProjectList->display();
//      m_pstillPrepareProjects->display();
//      m_pstillCmake->display();
//      m_pstillClean->display();
//
//
//      m_pbuttonNewReleasePrefix->set_button_style(::user::button::e_style_push);
//      m_pbuttonCheckout->set_button_style(::user::button::e_style_push);
//      m_pbuttonApplicationList->set_button_style(::user::button::e_style_push);
//      m_pbuttonPrepareApplications->set_button_style(::user::button::e_style_push);
//      m_pbuttonProjectList->set_button_style(::user::button::e_style_push);
//      m_pbuttonPrepareProjects->set_button_style(::user::button::e_style_push);
//      m_pbuttonCmake->set_button_style(::user::button::e_style_push);
//      m_pbuttonClean->set_button_style(::user::button::e_style_push);
//
//
//      m_pstillNewReleasePrefix->m_ealignText = ::e_align_left;
//      m_pstillCheckout->m_ealignText = ::e_align_left;
//      m_pstillApplicationList->m_ealignText = ::e_align_left;
//      m_pstillPrepareApplications->m_ealignText = ::e_align_left;
//      m_pstillProjectList->m_ealignText = ::e_align_left;
//      m_pstillPrepareProjects->m_ealignText = ::e_align_left;
//      m_pstillCmake->m_ealignText = ::e_align_left;
//      m_pstillClean->m_ealignText = ::e_align_left;
//
//      //get_app()->m_pbaseapplication->create_options_impact(this);
//
////      int leftButton = 10;
////      int widthButton = 100;
////      int leftStill = 120;
////      int widthStill = 400;
////
////      int y = 10;
////      int controlHeight = 25;
////      int controlSpacing = 5;
////
////      m_pbuttonCheckout->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillCheckout->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonApplicationList->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillApplicationList->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonPrepareApplications->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillPrepareApplications->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonProjectList->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillProjectList->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonPrepareProjects->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillPrepareProjects->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonCmake->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillCmake->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
////
////      m_pbuttonClean->place(::int_rectangle_dimension(leftButton, y, widthButton, controlHeight));
////      m_pstillClean->place(::int_rectangle_dimension(leftStill, y, widthStill, controlHeight));
////
////      y+=controlHeight+controlSpacing;
//

   }


//   integration* options_impact_handler::get_integration()
//   {
//
//      ::pointer < document > pdocument = m_papp->impact_system("main")->get_document(0);
//
//      if (!pdocument)
//      {
//
//         return nullptr;
//
//      }
//
//      auto pintegration = pdocument->m_pintegration;
//
//      if(!pintegration)
//      {
//
//         return nullptr;
//
//      }
//
//      return pintegration;
//
//   }


} // namespace coding



