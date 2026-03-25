#include "framework.h"
// From impact.cpp by camilo on 2024-05-03 18:48 <3ThomasBorregaardSorensen!!
#define SUMMARY_TOPIC12 "a summary - Tab with quite few redrawing for more CPU for building."
#include "coding.h"
//#include "document.h"
#include "group.h"
#include "group_netnode.h"
#include "summary.h"
#include "item.h"
//#include "tab_impact.h"
//#include "task_group.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/timer.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/timer.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/node.h"
#include "axis/user/user/list_box.h"
#include "aqua/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/button.h"
//#include "aura/user/user/check_box.h"
/////////////////////#include "aura/user/user/frame_interaction.h"
//#include "aura/user/user/still.h"
#if INTEGRATION_INTEGRATION_HAS_AUDIO
#include "aqua/audio/audio.h"
#endif // INTEGRATION_INTEGRATION_HAS_AUDIO
#include "aura/message/user.h"
//#include "aura/user/user/plain_edit.h"
//

namespace coding
{


   summary::summary()
   {


   }


   summary::~summary()
   {

   }



   void summary::install_message_routing(::channel* pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &summary::on_message_create);

   }


   void summary::on_message_create(::message::message* pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      defer_constructø(m_pfontTopic);

      m_pfontTopic->create_font(e_font_sans_ui, 21_pt, e_font_weight_heavy);


      defer_constructø(m_pfontTopic2);

      m_pfontTopic2->create_font(e_font_sans_ui, 14_pt, e_font_weight_heavy);


      fork([this]()
         {

            while (true)
            {

               update_designed_for_rare_calling();

               for (int i = 0; i < 3 * 30; i++)
               {

                  preempt(333_ms);

                  if (!::task_get_run())
                  {

                     return;

                  }

               }


            }

         });

   }


   void summary::update_designed_for_rare_calling()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::string str1;
      ::string_array straPinned;
      ::string strElapsed;
      int iMinute = 0;

      if (get_document())
      {

         auto pintegration = get_document()->m_pintegration;

         if (pintegration)
         {

            iMinute = (int) ( (pintegration->get_build_elapsed_time() .m_iSecond + 30) / 60);


            if (iMinute <= 0)
            {


            }
            else if (iMinute == 1)
            {

               strElapsed.formatf("1 minute elapsed");

            }
            else
            {

               strElapsed.formatf("%d minutes elapsed", iMinute);

            }

            auto ptaskRunning = pintegration->running_task_group();

            if (ptaskRunning)
            {

               str1 = ptaskRunning->m_strTopic1;

               straPinned.append(ptaskRunning->m_straPinnedLast2);

            }

         }

      }

      if (iMinute <= 2)
      {

         straPinned.insert_at(0, SUMMARY_TOPIC12);

      }

      if (str1.is_empty())
      {
         
         str1 = "Summary";

      }

      //if (str12.is_empty())
      {
         
        

      }

      m_strTopicSlowImprecise1 = str1;
      m_straPinned = straPinned;

      m_strElapsedSlowImprecise = strElapsed;

      set_need_redraw();

      post_redraw();

   }
   //   {
   //
   //      erase_children();
   //      //m_papp->m_pintegration->m_pimpactinterface = this;
   //
   //      int y = 10;
   //
   //      constructø(m_pfontNormal);
   //
   //      constructø(m_pfontFinished);
   //
   //      constructø(m_pfontBold);
   //
   //      constructø(m_pfontStatus);
   //
   //      constructø(m_pfontElapsed);
   //
   //      m_iLeftMargin = 10;
   //      m_iLeftWidth = 300;
   //
   //      auto strFont = node()->font_name(e_font_sans_ui);
   //
   //      m_pfontNormal->create_font(e_font_sans_ui, 14_px, e_font_weight_normal);
   //
   //      m_pfontFinished->create_font(e_font_sans_ui, 10_px, e_font_weight_bold);
   //
   //      m_pfontBold->create_font(e_font_sans_ui, 14_px, e_font_weight_bold);
   //
   //      m_pfontStatus->create_font(e_font_sans_ui, 10_px, e_font_weight_bold);
   //
   //      m_pfontElapsed->create_font(e_font_sans_ui, 10_px, e_font_weight_light);
   //
   //      constructø(m_pplaineditRepositoryPath);
   //
   //      /*m_pplaineditRepositoryPath->m_strEmtpyText = "Enter Repository Path";
   //
   //      m_pplaineditRepositoryPath->add_handler(this);
   //
   //      m_pplaineditRepositoryPath->create_control(this, "repository_path");
   //
   //      m_pplaineditRepositoryPath->place(::int_rectangle_dimension(m_iLeftMargin + m_iLeftWidth + 10, y + 10, 400, 28));
   //
   //      m_pplaineditRepositoryPath->display();*/
   //
   //      //get_app()->datastream()->get("repository_path", m_strRepositoryPath);
   //
   //      //m_pplaineditRepositoryPath->set_text(m_strRepositoryPath, ::e_source_initialize);
   //
   //      //constructø(m_pbuttonBrowseRepositoryPath);
   //
   //      //m_pbuttonBrowseRepositoryPath->add_handler(this);
   //
   //      //m_pbuttonBrowseRepositoryPath->create_control(this, "browse_repository_path");
   //
   //      //m_pbuttonBrowseRepositoryPath->place(::int_rectangle_dimension(m_iLeftMargin + m_iLeftWidth + 420, y, 200, 40));
   //
   //      //m_pbuttonBrowseRepositoryPath->set_window_text("Browse Repository Path");
   //
   //      //m_pbuttonBrowseRepositoryPath->display();
   //
   //      constructø(m_pbuttonStartBuild);
   //
   //      m_pbuttonStartBuild->add_handler(this);
   //
   //      m_pbuttonStartBuild->create_control(this, "start_build");
   //
   //      //int yStartBuild = y;
   //
   //      m_pbuttonStartBuild->place(::int_rectangle_dimension(10, y, 200, 40));
   //
   //      m_pbuttonStartBuild->set_window_text("Start Integration");
   //
   //      m_pbuttonStartBuild->display();
   //
   //      m_pbuttonStartBuild->set_need_layout();
   //
   //      m_pbuttonStartBuild->set_need_redraw();
   //
   //      {
   //
   //         constructø(m_pstillTopic);
   //
   //         m_pstillTopic->create_control(this, "topic_still");
   //
   //         m_pstillTopic->m_ealignText = e_align_left;
   //
   //         //m_pstillTopic->set_window_text_source([this]() {return m_pintegration->m_strFinishedStatus; });
   //
   //         m_pstillTopic->display();
   //
   //         //m_pstillFinished->set_need_layout();
   //
   //         //m_pstillFinished->set_need_redraw();
   //
   //         defer_constructø(m_pfontTopic);
   ////
   //         m_pfontTopic->create_font(e_font_sans_ui, 21_pt, e_font_weight_heavy);
   //
   //         m_pstillTopic->m_pfont = m_pfontTopic;
   //
   //         m_pstillTopic->set_text_color(argb(255, 89, 89, 89));
   //
   //      }
   //
   //      {
   //
   //         constructø(m_pstillTopic2);
   //
   //         m_pstillTopic2->create_control(this, "topic2_still");
   //
   //         m_pstillTopic2->m_ealignText = e_align_left;
   //
   //         //m_pstillTopic->set_window_text_source([this]() {return m_pintegration->m_strFinishedStatus; });
   //
   //         m_pstillTopic2->display();
   //
   //         //m_pstillFinished->set_need_layout();
   //
   //         //m_pstillFinished->set_need_redraw();
   //
            //defer_constructø(m_pfontTopic2);

            //m_pfontTopic2->create_font(e_font_sans_ui, 14_pt, e_font_weight_heavy);
   //
   //         m_pstillTopic2->m_pfont = m_pfontTopic2;
   //
   //         m_pstillTopic2->set_text_color(argb(255, 168, 168, 168));
   //
   //      }
   //
   //      set_topic_text("Are you ready to start building?");
   //
   //      auto pintegration = get_document()->m_pintegration;
   //
   //      m_yStart = 80;
   //
   //      y = m_yStart + 9;
   //
   //      for (auto pitem : pintegration->m_itema)
   //      {
   //
   //         auto eintegrate = pitem->m_eintegrate;
   //
   //         auto bCheck = pitem->m_bInitialCheck;
   //
   //         constructø(pitem->m_pcheckbox);
   //
   //         pitem->m_pcheckbox->create_control(this, (int)check_box_base + (int)eintegrate);
   //
   //         pitem->m_pcheckbox->place(::int_rectangle_dimension(m_iLeftMargin, y + 2, 20, 20));
   //
   //         if (!bCheck)
   //         {
   //
   //            get_app()->datastream()->get(pitem->m_pcheckbox->m_atom, bCheck);
   //
   //         }
   //
   //         pitem->m_pcheckbox->set_check(bCheck, e_source_sync);
   //
   //         pitem->m_pcheckbox->display();
   //
   //         pitem->m_pcheckbox->set_need_layout();
   //
   //         pitem->m_pcheckbox->set_need_redraw();
   //
   //         pitem->m_pcheckbox->add_handler(this);
   //
   //         //#ifdef INTEGRATE_LINUX
   //         //
   //         //            if (strDistro == "ubuntu")
   //         //            {
   //         //
   //         //               if (strBranch == "kde")
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_kubuntu)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //               else
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_ubuntu)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //
   //         //            }
   //         //            else if (strDistro == "fedora")
   //         //            {
   //         //
   //         //               if (strBranch == "kde")
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_kfedora)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //               else
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_fedora)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //
   //         //            }
   //         //            else if (strDistro == "opensuse-tumbleweed")
   //         //            {
   //         //
   //         //               if (strBranch == "kde")
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_opensuse_tumbleweed)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //               else
   //         //               {
   //         //
   //         //                  if (eintegrate == e_integrate_opensuseg_tumbleweed)
   //         //                  {
   //         //
   //         //                     pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //         //
   //         //                  }
   //         //
   //         //               }
   //         //
   //         //            }
   //         //
   //         //#endif
   //
   //#ifdef INTEGRATE_WINDOWS
   //
   //            ////if (strSystemDistro == "windows")
   //            //{
   //
   //            //   if (eintegrate == e_integrate_windows)
   //            //   {
   //
   //            //      pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //
   //            //   }
   //
   //            //}
   //
   //#endif
   //
   //#ifdef INTEGRATE_MACOS
   //
   //#ifdef __APPLE__
   //
   //         {
   //
   //            if (eintegrate == e_integrate_macos)
   //            {
   //
   //               pitem->m_pcheckbox->set_check(e_check_checked, e_source_initialize);
   //
   //            }
   //
   //         }
   //
   //#endif
   //
   //#endif
   //
   //
   //
   //         ::string strShortName = pitem->m_strShortName;
   //
   //         constructø(pitem->m_pstill);
   //
   //         pitem->m_pstill->m_bDefaultClickHandling = true;
   //
   //         pitem->m_pstill->create_control(this, (int)still_base + (int)eintegrate);
   //
   //         pitem->m_pstill->place(::int_rectangle_dimension(m_iLeftMargin + 25, y, m_iLeftWidth - 25, 20));
   //
   //         pitem->m_pstill->set_window_text(strShortName);
   //
   //         pitem->m_pstill->m_ealignText = e_align_left;
   //
   //         //pitem->m_pstill->set_window_text_source(
   //            //[pitem]()
   //            //{ 
   //
   //               //return pitem->get_integrate_item_name(); 
   //
   //            //});
   //
   //         pitem->m_pstill->display();
   //
   //         pitem->m_pstill->set_need_layout();
   //
   //         pitem->m_pstill->set_need_redraw();
   //
   //         pitem->m_pstill->add_handler(this);
   //
   //         pitem->m_pstill->m_pfont = m_pfontNormal;
   //
   //         {
   //
   //            constructø(pitem->m_pstillStatus);
   //
   //            //pstill->m_bClickDefaultMouseHandling = true;
   //
   //            pitem->m_pstillStatus->create_control(this, (int)still_status_base + (int)eintegrate);
   //
   //            pitem->m_pstillStatus->place(::int_rectangle_dimension(m_iLeftMargin + 25, y + 18, m_iLeftWidth - 25, 12));
   //
   //            pitem->m_pstillStatus->m_ealignText = e_align_left;
   //
   //            //pstill->set_window_text(m_pintegration->get_name(eintegrate));
   //
   //            pitem->m_pstillStatus->display();
   //
   //            pitem->m_pstillStatus->set_need_layout();
   //
   //            pitem->m_pstillStatus->set_need_redraw();
   //
   //            //pstill->add_handler(this);
   //
   //            pitem->m_pstillStatus->m_pfont = m_pfontStatus;
   //
   //         }
   //
   //         {
   //
   //            constructø(pitem->m_pstillElapsed);
   //
   //            //pstill->m_bClickDefaultMouseHandling = true;
   //
   //            pitem->m_pstillElapsed->create_control(this, (int)still_elapsed_base + (int)eintegrate);
   //
   //            pitem->m_pstillElapsed->place(::int_rectangle_dimension(m_iLeftMargin + 25, y + 30, m_iLeftWidth - 25, 12));
   //
   //            //pstill->set_window_text(m_pintegration->get_name(eintegrate));
   //
   //            pitem->m_pstillElapsed->m_ealignText = e_align_left;
   //
   //            pitem->m_pstillElapsed->display();
   //
   //            pitem->m_pstillElapsed->set_need_layout();
   //
   //            pitem->m_pstillElapsed->set_need_redraw();
   //
   //            //pstill->add_handler(this);
   //
   //            pitem->m_pstillElapsed->m_pfont = m_pfontElapsed;
   //
   //         }
   //
   //         y += 55;
   //
   //      }
   //
   //      pintegration->m_straLine2.add("integration_integration");
   //      pintegration->m_straLine2.add("The build log follows...");
   //
   //      y += 50;
   //
   //      constructø(m_pstillFinished);
   //
   //      m_pstillFinished->create_control(this, "finished_still");
   //
   //      m_pstillFinished->place(::int_rectangle_dimension(10, y, 200, 40));
   //
   //      m_pstillFinished->set_window_text_source([this]() {return get_document()->m_pintegration->m_strFinishedStatus; });
   //
   //      m_pstillFinished->hide();
   //
   //      //m_pstillFinished->set_need_layout();
   //
   //      //m_pstillFinished->set_need_redraw();
   //
   //      m_pstillFinished->m_pfont = m_pfontFinished;
   //
   //      int iButton = 0;
   //
   //      if (pintegration && pintegration->m_pgroupnetnode)
   //      {
   //
   //         if (m_papp->m_strAppId.case_insensitive_ends("/handler"))
   //         {
   //
   //            for (auto& strNetnode : pintegration->m_pgroupnetnode->m_straNetnode)
   //            {
   //
   //               auto pbuttonHandlePulseCallIntegration = create_newø < ::user::button >();
   //
   //               pbuttonHandlePulseCallIntegration->add_handler(this);
   //
   //               pbuttonHandlePulseCallIntegration->create_control(this, "pulse_" + strNetnode);
   //
   //               pbuttonHandlePulseCallIntegration->place(::int_rectangle_dimension(10, iButton * (40 * 2) + m_yStart, 200, 40));
   //
   //               pbuttonHandlePulseCallIntegration->set_window_text("Pulse " + pintegration->netnode_short_name(strNetnode));
   //
   //               pbuttonHandlePulseCallIntegration->enable_window(false);
   //
   //               pbuttonHandlePulseCallIntegration->display();
   //
   //               pbuttonHandlePulseCallIntegration->set_need_layout();
   //
   //               pbuttonHandlePulseCallIntegration->set_need_redraw();
   //
   //               m_buttonaHandlePulseCallIntegration.add(pbuttonHandlePulseCallIntegration);
   //
   //               iButton++;
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //void summary::defer_auto_start_integration()
   //{

   //   auto pintegration = get_document()->m_pintegration;

   //   auto bAnyBuildSelected = pintegration->has_selected_build();

   //   information() << "any build selected : " << bAnyBuildSelected;

   //   information() << "repository path : " << pintegration->m_strRepositoryPath;

   //   auto pathHost = pintegration->host_integration_folder();

   //   information() << "host path : " << pathHost;

   //   pintegration->m_pathStartBuild = pathHost / "start_build.txt";

   //   information() << "start build path : " << pintegration->m_pathStartBuild;

   //   pintegration->m_pathBuildThenPowerOff = pathHost / "build_then_power_off.txt";

   //   information() << "build then power off path : " << pintegration->m_pathBuildThenPowerOff;

   //   if (pintegration->m_itema.get_size() == 1)
   //   {

   //      auto bCheckoutForAnotherSystem = pintegration->m_itema.first()->m_eintegrate == e_integrate_checkout_for_another_system;

   //      if (bCheckoutForAnotherSystem)
   //      {

   //         information() << "Check for Another System!!";

   //         start_integration();

   //         return;

   //      }

   //   }

   //   if (bAnyBuildSelected)
   //   {

   //      information() << "any build selected";

   //      auto strSlashedIntegration = pintegration->m_poperatingsystemsummary->m_strSlashedIntegration;

   //      top_level_frame()->set_window_text("integration - " + strSlashedIntegration);

   //      if (file_system()->exists(pintegration->m_pathBuildThenPowerOff))
   //      {

   //         information() << "build_then_power_off.txt exists : Going to start build and then power off...";

   //         pintegration->main_status("Current task: build_then_power_off : \"" + strSlashedIntegration + "\"");

   //         start_integration();

   //      }
   //      else if (file_system()->exists(pintegration->m_pathStartBuild))
   //      {

   //         information() << "start_build.txt exists : Going to start build...";

   //         pintegration->main_status("Current task: build : \"" + strSlashedIntegration + "\"");

   //         start_integration();

   //      }

   //      //::string strIntegration = file_system()->as_string(pathStartBuild);

   //      //if (strIntegration.is_empty())
   //      //{

   //      //   strIntegration = file_system()->exists(pathStartOperatingSystemBuild);

   //      //}

   //   }

   //   information() << "defer_auto_start_integration end";

   //}


   //::string _017ElapsedTime(const class ::time& time)
   //{

   //   ::string strElapsedTime;

   //   if (time < 1_s)
   //   {

   //      strElapsedTime.formatf("0''%03d", time.m_iNanosecond / 1'000'000);

   //   }
   //   else if (time < 60_s)
   //   {

   //      strElapsedTime.formatf("%d''%03d", time.m_iSecond, time.m_iNanosecond / 1'000'000);

   //   }
   //   else if (time < 1_hour)
   //   {

   //      strElapsedTime.formatf("%d'%02d''%03d", time.integral_minute(), time.m_iSecond % 60, time.m_iNanosecond / 1'000'000);

   //   }
   //   else if (time < 24_hour)
   //   {

   //      strElapsedTime.formatf("%dh%02d'%02d''%03d", time.integral_hour(), time.integral_minute() % 60, time.m_iSecond % 60, time.m_iNanosecond / 1'000'000);

   //   }
   //   else if (time < 365_day)
   //   {

   //      strElapsedTime.formatf("%dd%02dh%02d'%02d''%03d", time.integral_day(), time.integral_hour() % 24, time.integral_minute() % 60, time.m_iSecond % 60, time.m_iNanosecond / 1'000'000);

   //   }
   //   else
   //   {

   //      strElapsedTime = "more than 365 days?!?";

   //   }

   //   return strElapsedTime;

   //}


   document* summary::get_document()
   {

      return m_pdocument.cast < document >();

   }


   void summary::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {
      information() << "integration impact::_001OnDraw";

      auto rectangleClient = this->rectangle();

      ::int_point p;

      p.x = m_iLeftMargin + m_iLeftWidth + 10;

      p.y = rectangleClient.height();

      auto pintegration = get_document()->m_pintegration;
      auto pstyle = get_style(pgraphics);
      auto colorBackground = get_color(pstyle, e_element_background);
      pgraphics->fill_solid_rectangle(rectangleClient, colorBackground);

      //if(!m_pstillTopic12)
      //{

      //   return;

      //}

      ::string strTopic1;
      ::string strElapsed;
      ::string_array straPinned;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         strTopic1 = m_strTopicSlowImprecise1;

         strElapsed = m_strElapsedSlowImprecise;

         straPinned = m_straPinned;

      }

      pgraphics->set(m_pfontTopic);

      ::double_point p1(p.x, 10);

      pgraphics->set_text_color(argb(255, 89, 89, 89));

      pgraphics->text_out(p1, strTopic1);

      ::double_point p2(p.x, 50);

      pgraphics->set(m_pfontTopic2);

      pgraphics->set_text_color(argb(255, 168, 168, 168));

      pgraphics->text_out(p2, strElapsed);


      ::double_point p5(p.x, 200);

      pgraphics->set(m_pfontTopic2);

      pgraphics->set_text_color(argb(255, 168, 168, 168));

      for (auto& s : straPinned)
      {

         pgraphics->text_out(p5, s);

         p5.y += 25;

      }


      //}


      //information() << "integration summary::_001OnDraw (2)";

      ////auto yTopic2Bottom = m_pstillTopic2->bottom();

      //auto yTopic2Bottom = 100;
      //if (ptaskgroup)
      //{

      //   _synchronous_lock synchronouslock(pintegration->m_pmutexLines);

      //   //string_array & straLine = m_pintegration->m_straLine;

      //   //file()->get_lines(straLine, directory_system()->home() /"build.log");

      //   pgraphics->set_text_color(argb(255, 89, 89, 89));

      //   ::write_text::font_pointer pfont;

      //   constructø(pfont);

      //   pfont->create_font("Helvetica", 12_pt);

      //   pfont->m_bCacheLayout = false;

      //   pgraphics->set(pfont);

      //   auto& straunion = ptaskgroup->m_straunion;

      //   if (straunion.has_element())
      //   {

      //      int iAlpha = 255;

      //      for (auto i = straunion.get_upper_bound();
      //         i >= 0; i--)
      //      {

      //         p.y() -= 20;

      //         if (p.y() < yTopic2Bottom + 5)
      //         {

      //            break;

      //         }
      //         else if (p.y() < yTopic2Bottom + 25)
      //         {

      //            iAlpha = 89;

      //         }
      //         else if (p.y() < yTopic2Bottom + 45)
      //         {

      //            iAlpha = 198;

      //         }


      //         string strLine = straunion[i];

      //         if (strLine.begins_eat("I: "))
      //         {

      //            pgraphics->set_text_color(argb(iAlpha, 89, 89, 200));

      //         }
      //         else if (strLine.begins_eat("E: "))
      //         {

      //            pgraphics->set_text_color(argb(iAlpha, 200, 89, 89));

      //         }
      //         else
      //         {

      //            pgraphics->set_text_color(argb(iAlpha, 89, 89, 89));

      //         }

      //         pgraphics->text_out(p, strLine);

      //      }

      //   }

      //}

      //return;


      //p.x() = 20;

      //p.y() = m_pstillFinished->bottom() + 10;

      //{

      //   _synchronous_lock synchronouslock(pintegration->synchronization());

      //   for (auto& itemtime : pintegration->m_itemtimeaSummary)
      //   {

      //      auto& strItem = itemtime.m_strItem;

      //      if (strItem.contains("✓"))
      //      {

      //         pgraphics->set_text_color(argb(255, 89, 200, 89));

      //      }
      //      else if (strItem.contains("✗")
      //         || strItem.contains("📦")
      //         || strItem.contains("🏪")
      //         || strItem.contains("🔼"))
      //      {

      //         pgraphics->set_text_color(argb(255, 200, 89, 89));

      //      }
      //      else
      //      {

      //         pgraphics->set_text_color(argb(255, 89, 89, 89));

      //      }

      //      string strTime;

      //      auto elapsed = itemtime.m_time;

      //      pgraphics->text_out(p, strItem + " " + _017ElapsedTime(elapsed));

      //      p.y() += 20;

      //   }

      //   /*if (m_pintegration->m_strTopic.has_character())
      //   {

      //      ::write_text::font_pointer pfont;

      //      constructø(pfont);

      //      pfont->create_font("Helvetica", 20_pt, e_font_weight_heavy);

      //      pfont->m_bCacheLayout = false;

      //      pgraphics->set(pfont);

      //      pgraphics->set_text_color(argb(255, 89, 89, 89));

      //      ::string strTopic;

      //      if (m_pintegration->m_timeTopicStart > 0_s)
      //      {

      //         auto elapsed = m_pintegration->m_timeTopicStart.elapsed();

      //         strTopic.format("%s %s", m_pintegration->m_strTopic.c_str(), _017ElapsedTime(elapsed).c_str());

      //      }
      //      else
      //      {

      //         strTopic = m_pintegration->m_strTopic;

      //      }

      //      pgraphics->text_out({ 230, 45 }, strTopic);

      //   }*/

      //   //if (m_pintegration->m_strTopic2.has_character())
      //   //{

      //   //   ::write_text::font_pointer pfont;

      //   //   constructø(pfont);

      //   //   pfont->create_font("Helvetica", 12_pt, e_font_weight_light);

      //   //   pfont->m_bCacheLayout = false;

      //   //   pgraphics->set(pfont);

      //   //   pgraphics->set_text_color(argb(255, 168, 168, 168));

      //   //   ::string strTopic2 = m_pintegration->m_strTopic2;

      //   //   pgraphics->text_out({ 230, 75 }, strTopic2);

      //   //}

      //}

   }

//
//   string summary::get_windows_prompt()
//   {
//
//      return "Windows";
//
//   }
//
//
//   void summary::on_integrate_change()
//   {
//
//      auto pintegration = get_document()->m_pintegration;
//
//      for (auto& pitem : pintegration->m_itema)
//      {
//
//         if (::is_null(pitem))
//         {
//
//            continue;
//
//         }
//
//         bool bChanged = false;
//
//         if (pintegration->m_pitem == pitem)
//         {
//
//            ::set_if_different(bChanged, pitem->m_pstill->m_pfont, m_pfontBold);
//
//         }
//         else
//         {
//
//            ::set_if_different(bChanged, pitem->m_pstill->m_pfont, m_pfontNormal);
//
//         }
//
//         if (bChanged)
//         {
//
//            pitem->m_pstill->set_need_layout();
//
//            pitem->m_pstill->set_need_redraw();
//
//            pitem->m_pstill->post_redraw();
//
//         }
//
//      }
//
//      if (pintegration->m_eintegrate == e_integrate_finished)
//      {
//
//         if (!m_pstillFinished->is_window_visible())
//         {
//
//            m_pfontFinished->set_bold();
//
//            m_pstillFinished->display();
//
//            m_pstillFinished->set_window_text(get_document()->m_pintegration->m_strFinishedStatus);
//
//            m_pbuttonStartBuild->enable_window(false);
//
//         }
//
//      }
//      else
//      {
//
//         if (m_pstillFinished->is_window_visible())
//         {
//
//            m_pfontFinished->set_bold(false);
//
//            m_pstillFinished->hide();
//
//            m_pstillFinished->set_need_layout();
//
//         }
//
//      }
//
//      try
//      {
//
//         if (pintegration->m_eintegrate == e_integrate_finished)
//         {
//
//#if INTEGRATION_INTEGRATION_HAS_AUDIO
//
//            system()->defer_audio();
//
//            auto paudio = system()->audio();
//
//            ::file::path path;
//
//            if (pintegration->m_straError.has_element())
//            {
//
//               path = "matter://twilight.wav";
//
//            }
//            else
//            {
//
//               path = "matter://production_ready.wav";
//
//            }
//
//            auto pfile = file()->get_reader(path);
//
//            paudio->play_audio(pfile);
//
//            if (pintegration->m_straError.has_element())
//            {
//
//               preempt(2.5_s);
//
//               for (auto& strError : pintegration->m_straError)
//               {
//
//                  paudio->speak(strError);
//
//               }
//
//            }
//
//#endif // INTEGRATION_INTEGRATION_HAS_AUDIO
//
//            pintegration->on_finished_finish_animations();
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//   void summary::enable_pulse(const ::scoped_string& scopedstr)
//   {
//
//      auto strId = "pulse_" + scopedstr;
//
//      auto p = get_child_by_id(strId);
//
//      if (p)
//      {
//
//         p->enable_window(true);
//
//      }
//
//   }
//
//
//   void summary::on_lines_change()
//   {
//
//      set_need_layout();
//
//      set_need_redraw();
//
//      post_redraw();
//
//   }
//
//
//   void summary::start_integration()
//   {
//
//#if 0
//      node()->shutdown(true);
//#endif
//
//      m_pbuttonStartBuild->enable_window(false);
//
//      fork([this]()
//         {
//
//            //add_prodevian(m_pintegration);
//
//            auto pintegration = get_document()->m_pintegration;
//
//            set_timer(e_timer_main_impact_update, 100_ms);
//
//            //pintegration->m_pathBuildFolder = m_strRepositoryPath;
//
//            ::file::path pathHost;
//
//            try
//            {
//
//               pintegration->run();
//
//            }
//            catch (...)
//            {
//
//            }
//
//            KillTimer(e_timer_main_impact_update);
//
//            m_pbuttonStartBuild->enable_window();
//
//         });
//
//      set_need_redraw();
//
//      post_redraw();
//
//   }
//
//
//   void summary::set_topic_text(const ::scoped_string& scopedstr)
//   {
//
//      //m_pstillTopic->set_window_text(scopedstr);
//
//      //auto pframe = top_level_frame();
//
//      //auto papp = m_papp;
//
//      //if (pframe && papp)
//      //{
//
//      //   pframe->set_window_text(papp->m_strAppId + " - " + scopedstr);
//
//      //}
//
//   }
//
//
//   void summary::set_topic_text2(const ::scoped_string& scopedstr)
//   {
//
//      //m_pstillTopic2->set_window_text(scopedstr);
//
//   }
//
//
//
//   void summary::_001OnTimer(::timer* ptimer)
//   {
//
//      if (ptimer->m_etimer == e_timer_main_impact_update)
//      {
//
//         update_elapsed_still();
//
//      }
//
//      ::user::impact::_001OnTimer(ptimer);
//
//   }
//
//
//   void summary::update_elapsed_still()
//   {
//
//      auto pintegration = get_document()->m_pintegration;
//
//      if (!pintegration)
//      {
//
//         return;
//
//      }
//
//      auto elapsed = pintegration->get_build_elapsed_time();
//
//      if (!pintegration->m_bEnableUpdateElapsed || elapsed < 0_s)
//      {
//
//         return;
//
//      }
//
//      auto pitem = pintegration->m_pitem;
//
//      if (!pitem)
//      {
//
//         return;
//
//      }
//
//      auto pstill = pitem->m_pstillElapsed;
//
//      if (!pstill)
//      {
//
//         return;
//
//      }
//
//      pstill->set_window_text(::as_string(elapsed.floating_minute()) + " minute(s)");
//
//   }
//
//
//   void summary::on_perform_top_down_layout(::draw2d::graphics_pointer& pgraphics)
//   {
//
//      auto rectangleClient = this->rectangle(::user::e_layout_layout);
//
//      if (rectangleClient.is_empty())
//      {
//
//         return;
//
//      }
//
//      //if (m_pfontTopic && m_pstillTopic)
//      //{
//
//      //   auto fontHeight = m_pfontTopic->get_height(pgraphics);
//
//      //   auto w = rectangleClient.width();
//
//      //   auto h = fontHeight;
//
//      //   {
//
//      //      auto rectanglePlacement = ::int_rectangle_dimension(m_iLeftMargin + m_iLeftWidth + 10, m_yStart,
//      //         w - (m_iLeftMargin + m_iLeftWidth + 10), h);
//
//      //      if (w < 500)
//      //      {
//
//      //         information() << "w < 500";
//
//      //      }
//
//      //      m_pstillTopic->place(rectanglePlacement);
//
//      //   }
//
//      //   if (m_pfontTopic2 && m_pstillTopic2)
//      //   {
//
//      //      auto fontHeight = m_pfontTopic2->get_height(pgraphics);
//
//      //      auto rectanglePlacement = ::int_rectangle_dimension(m_iLeftMargin + m_iLeftWidth + 10, m_yStart + h,
//      //         rectangleClient.width() -
//      //         (m_iLeftMargin + m_iLeftWidth + 10), fontHeight);
//
//      //      m_pstillTopic2->place(rectanglePlacement);
//
//      //   }
//
//      //}
//
//   }
//
//
//   task_group* summary::task_group()
//   {
//
//      return get_document()->m_pintegration->m_taskgroup[m_etaskGroupDisplay];
//
//   }
//
//
//   void summary::on_start_task_group(enum_task etaskGroup)
//   {
//
//      impact_interface::on_start_task_group(etaskGroup);
//
//      m_plistTaskGroup->set_current_item_by_atom((enum_impact)etaskGroup, e_source_sync);
//
//      m_plistTaskGroup->set_need_redraw();
//
//      m_plistTaskGroup->post_redraw();
//
//   }
//

} // namespace coding



