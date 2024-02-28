// Created by camilo on 2023-10-09 ~12:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "popup.h"
#include "acme/constant/message.h"


namespace user
{


   popup::popup()
   {

      //m_bHideOnLostFocus = true;

      m_bHideOnLostFocus = false;

   }


   popup::~popup()
   {


   }


   void popup::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &popup::on_message_kill_focus);

   }


   void popup::on_message_kill_focus(::message::message * pmessage)
   {

      if (!is_this_visible())
      {

         information() << "on_message_kill_focus and not visible";

         return;

      }

      m_timeLostFocus.Now();

      if (m_bHideOnLostFocus)
      {

         hide();

         set_need_redraw();

         post_redraw();

      }

   }


   void popup::show_popup(const ::point_i32 & point)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      m_sizeMinimum.cx() = 300;

      m_sizeMinimum.cy() = 150;

      order(e_zorder_top_most);

      place(point.x(), point.y(), 400, 200);

      display(e_display_normal, e_activation_set_popup);

      set_need_redraw();

      post_redraw();

      //}
      //else
      //{
      //
      //   pframe->order(e_zorder_top_most);
      //
      //   pframe->display();
      //
      //}


            //bool bNew = m_pdocument == nullptr;

            //if (bNew)
            //{

            //   auto pcontext = m_pcontext;

            //   auto psession = pcontext->m_pacmesession->m_pcoresession;

            //   auto puser = psession->m_puser->m_pcoreuser;

            //   puser->will_use_impact_hint(COLORSEL_IMPACT);

            //   m_pdocument = puser->m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(get_app(), ::e_type_null, __visible(false).is_true());

            //   m_pimpact = m_pdocument->get_typed_impact < ::userex::color_impact >();

            //   m_pimpact->m_bCompact = true;

            //   psession->set_bound_ui(COLORSEL_IMPACT, this);

            //   m_pframewindow = dynamic_cast <::simple_frame_window *> (m_pimpact->top_level_frame());

            //   m_pframewindow->set_owner(this);

            //   m_pframewindow->m_ebuttonaHide.add(::experience::e_button_dock);
            //   m_pframewindow->m_ebuttonaHide.add(::experience::e_button_down);
            //   m_pframewindow->m_ebuttonaHide.add(::experience::e_button_up);
            //   m_pframewindow->m_ebuttonaHide.add(::experience::e_button_minimize);

            //}

            //m_pimpact->m_hls = m_hls;

            //auto pframe = frame();

            //if (bNew)
            //{

            //   ::rectangle_i32 rectangleWindow;

            //   window_rectangle(rectangleWindow);

            //   pframe->m_sizeMinimum.cx() = 300;

            //   pframe->m_sizeMinimum.cy() = 150;

            //   pframe->order(e_zorder_top_most);

            //   pframe->place(rectangleWindow.left(), rectangleWindow.bottom(), 400, 200);

            //   pframe->display();

            //}
            //else
            //{

            //   pframe->order(e_zorder_top_most);

            //   pframe->display();

            //}


   }


   void popup::hide_popup()
   {

      hide();

      set_need_redraw();

      post_redraw();

   }


} // namespace user


