#include "framework.h"
#include "document.h"
#include "group.h"
#include "group_netnode.h"
#include "log_impact.h"
#include "item.h"
#include "application.h"
#include "impact_interface.h"
#include "integration.h"
#include "task.h"
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
//#include "apex/platform/os_context.h"

#include "aqua/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/still.h"
#if INTEGRATION_INTEGRATION_HAS_AUDIO
#include "aqua/audio/audio.h"
#endif // INTEGRATION_INTEGRATION_HAS_AUDIO
#include "aura/message/user.h"
#include "aura/user/user/plain_edit.h"


namespace coding
{


   log_impact::log_impact()
   {


   }


   log_impact::~log_impact()
   {

   }


   void log_impact::handle(::topic* ptopic, ::handler_context* phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

      if (ptopic->id() == id_initial_update)
      {

         auto pintegration = get_document()->m_pintegration;

         if (pintegration)
         {

            update_impact();

         }

      }


   }


   log_interface* log_impact::get_log()
   {

      auto pintegration = get_document()->m_pintegration;
      
      auto etaskGroupDisplay = pintegration->m_pimpactinterface->m_etaskGroupDisplay;

      auto etask = (enum_task)(m_etaskOrdinal | etaskGroupDisplay);

      return pintegration->task_log(etask);

   }


   void log_impact::install_message_routing(::channel* pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &log_impact::on_message_create);

   }


   void log_impact::on_message_create(::message::message* pmessage)
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

         defer_constructø(m_pfontLog);

         m_pfontLog->m_bCacheLayout = false;

         m_pfontLog->create_font(e_font_monospace_fx, 12_pt, e_font_weight_normal);

   }

   document* log_impact::get_document()
   {

      return m_pdocument.cast < document >();

   }


   void log_impact::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      information() << "integration log_impact::_001OnDraw";

      auto rectangleClient = this->rectangle();

      ::int_point p;

      p.x = m_iLeftMargin + m_iLeftWidth + 10;

      p.y = rectangleClient.height();

      auto pintegration = get_document()->m_pintegration;

      auto pstyle = get_style(pgraphics);
      auto colorBackground = get_color(pstyle, e_element_background);


      pgraphics->fill_solid_rectangle(rectangleClient, colorBackground);

      information() << "integration log_impact::_001OnDraw (2)";

      auto plog = get_log();

      if(!plog)
      {

         return;

      }

      _synchronous_lock synchronouslock(plog->synchronization());

      pgraphics->set(m_pfontTopic);

      ::double_point p1(p.x, 10);

      pgraphics->set_text_color(argb(255, 89, 89, 89));

      pgraphics->text_out(p1, plog->m_ptask->m_strTopic1);

      ::double_point p2(p.x, 50);

      pgraphics->set(m_pfontTopic2);

      pgraphics->set_text_color(argb(255, 168, 168, 168));

      pgraphics->text_out(p2, plog->m_ptask->m_strTopic12);

      int yTopic2Bottom = 100;

      {


         //string_array & straLine = m_pintegration->m_straLine;

         //file()->get_lines(straLine, directory_system()->home() /"build.log");

         pgraphics->set_text_color(argb(255, 89, 89, 89));

         pgraphics->set(m_pfontLog);

         if (plog->m_straLog.has_element())
         {

            if (plog->m_straLog.size() > 2000)
            {

               plog->m_straLog.erase_at(0, plog->m_straLog.size() - 1000);

            }

            int iAlpha = 255;

            for (auto i = plog->m_straLog.get_upper_bound();
               i >= 0; i--)
            {

               p.y -= 20;

               if (p.y < yTopic2Bottom + 5)
               {

                  break;

               }
               else if (p.y < yTopic2Bottom + 25)
               {

                  iAlpha = 89;

               }
               else if (p.y < yTopic2Bottom + 45)
               {

                  iAlpha = 198;

               }


               string strLine = plog->m_straLog[i];

               if (strLine.begins_eat("W: "))
               {

                     pgraphics->set_text_color(argb(iAlpha, 89, 89, 200));

               }
               else if (strLine.begins_eat("F: "))
               {

                     pgraphics->set_text_color(argb(iAlpha, 200, 89, 89));

               }
               else
               {

                  pgraphics->set_text_color(argb(iAlpha, 89, 89, 89));

               }

               pgraphics->text_out(p, strLine);

            }

         }

      }


   }





   void log_impact::on_lines_change()
   {

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }



   //void log_impact::set_topic_text(const ::scoped_string& scopedstr)
   //{

   //   m_pstillTopic->set_window_text(scopedstr);

   //   auto pframe = top_level_frame();

   //   auto papp = m_papp;

   //   if (pframe && papp)
   //   {

   //      pframe->set_window_text(papp->m_strAppId + " - " + scopedstr);

   //   }

   //}


   //void log_impact::set_topic_text2(const ::scoped_string& scopedstr)
   //{

   //   m_pstillTopic2->set_window_text(scopedstr);

   //}



   void log_impact::on_timer(::timer* ptimer)
   {

      if (ptimer->m_etimer == e_timer_main_impact_update)
      {

         update_elapsed_still();

      }

      ::user::impact::on_timer(ptimer);

   }


   void log_impact::update_elapsed_still()
   {

      auto pintegration = get_document()->m_pintegration;

      if (!pintegration)
      {

         return;

      }

      auto elapsed = pintegration->get_build_elapsed_time();

      if (!pintegration->m_bEnableUpdateElapsed || elapsed < 0_s)
      {

         return;

      }

      auto pitem = pintegration->m_pitem;

      if (!pitem)
      {

         return;

      }
      
      auto elapsedStatus = pintegration->get_topic_elapsed_time();

      auto pstill = pitem->m_pstillElapsed;

      if (!pstill)
      {

         return;

      }

      pstill->set_window_text(::as_string(elapsed.floating_minute()) + " minute(s)");

      auto pstillStatusElapsed = pitem->m_pstillStatusElapsed;
      
      if (!pstillStatusElapsed)
      {

         return;

      }
      
      

      pstillStatusElapsed->set_window_text(::as_string(elapsedStatus.floating_minute()) + " minute(s)");

   }


   void log_impact::on_perform_top_down_layout(::draw2d::graphics_pointer& pgraphics)
   {

      auto rectangleClient = this->rectangle(::user::e_layout_layout);

      if (rectangleClient.is_empty())
      {

         return;

      }

   }


} // namespace coding



