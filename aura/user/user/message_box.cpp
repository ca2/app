//
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "message_box.h"
#include "button.h"
#include "still.h"
#include "interaction_scaler.h"
#include "user.h"
#include "style.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/platform/sequencer.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"


namespace user
{


   //default_message_box::message_box(const ::string & strMessageParam, const ::string & strTitle, const ::e_message_box & emessagebox) :
   default_message_box::default_message_box() :
      m_strFontName("serif"),
      m_size(100, 40),
      m_bOsUserThemeColorModified(false),
      m_bInvalidated(false)
   {

      common_construct();

      auto pitemClient = __allocate< ::item >(e_element_client);

      enable_drag(pitemClient, e_zorder_back);

      auto pitemResize = __allocate< ::item >(e_element_resize);

      enable_drag(pitemResize, e_zorder_back);

      m_bDefaultClickHandling = true;

      m_bDefaultMouseHoverHandling = true;

   }


   pointer< ::sequencer < ::conversation > > message_box::show(::user::interaction * puserinteraction, const string & strMessageParam, const string & strTitle, const ::e_message_box & emessagebox)
   {

      auto emessageboxType = emessagebox & e_message_box_type_mask;

      switch (emessageboxType)
      {
      case e_message_box_ok_cancel:
         add_button("OK", e_dialog_result_ok);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_abort_retry_ignore:
         add_button("Abort", e_dialog_result_abort);
         add_button("Retry", e_dialog_result_retry);
         add_button("Ignore", e_dialog_result_ignore);
         break;
      case e_message_box_yes_no_cancel:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_yes_no:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         break;
      case e_message_box_retry_cancel:
         add_button("Retry", e_dialog_result_retry);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_cancel_try_continue:
         add_button("Cancel", e_dialog_result_cancel);
         add_button("Try", e_dialog_result_retry);
         add_button("Continue", e_dialog_result_continue);
         break;
      default:
         add_button("OK", e_dialog_result_ok);
         break;
      }

      return nullptr;

   }


   void default_message_box::add_button(const ::string & strTitle, enum_dialog_result edialogresult)
   {

      m_buttona.add(__allocate< ::user::button >(strTitle, edialogresult));

      //return ::success;

   }


   pointer< ::sequencer < ::conversation > > default_message_box::show(::user::interaction * puserinteraction, const string& strMessageParam, const string& strTitle, const ::e_message_box& emessagebox)
   {

      auto psequencer = __allocate< ::sequencer <::conversation > >();

      psequencer->m_psequence = this;

      payload("sequence<conversation>") = psequencer;

      string strMessage(strMessageParam);

      m_strTitle = strTitle;

      strMessage.case_insensitive_replace_with(" \n", "<br>");

      __construct_new(m_pstill);

      m_pstill->set_window_text(strMessage);

      m_stra.add_lines(strMessage);

      m_pbuttonClose = __allocate< ::user::button >("", e_dialog_result_close);

      m_pbuttonClose->set_button_style(::user::button::e_style_stock_icon);

      m_pbuttonClose->set_stock_icon(::e_stock_icon_close);

      m_pbuttonClose->m_flagNonClient -= e_non_client_background;
      m_pbuttonClose->m_flagNonClient -= e_non_client_focus_rect;

      ::user::message_box::show(puserinteraction, strMessageParam, strTitle, emessagebox);

      m_pbuttonClose->initialize(this);

      m_pbuttonClose->add_handler(this);

      for (auto& pbutton : m_buttona)
      {

         pbutton->initialize(this);

         pbutton->add_handler(this);

      }

      set_tool_window();

      display(::e_display_normal);

      do_layout();

      //auto estatus = 
      
      //create_host(e_parallelization_synchronous);

      create_host();

      //if (!estatus)
      //{

      //   pfuture->set_status(error_failed);

      //   return pfuture;

      //}

      do_show();

      return psequencer;

   }


   void default_message_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &default_message_box::on_message_create);

   }


   i64 default_message_box::increment_reference_count()
   {

      return ::user::interaction::increment_reference_count();

   }


   i64 default_message_box::decrement_reference_count()
   {

      return ::user::interaction::decrement_reference_count();

   }


   i64 default_message_box::release()
   {

      return ::user::interaction::release();

   }


   void default_message_box::common_construct()
   {

      m_bFirstLayoutDone = false;
      m_iMarginTop = 20;
      m_iMarginLeft = 20;
      m_iMarginRight = 20;
      m_iLineSpacing = 4;
      m_iButtonHSpacing = 20;
      m_iButtonHPadding = 20;
      m_iButtonVPadding = 8;
      m_iMidSpacing = 20;
      m_iMarginBottom = 20;

   }


   void default_message_box::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      m_pbuttonClose->create_child(this);

      for (auto & pbutton : m_buttona)
      {

         pbutton->create_child(this);

      }

      m_pstill->create_child(this);

   }


   default_message_box::~default_message_box()
   {


   }


   void default_message_box::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_user_style_change)
      {

         m_bOsUserThemeColorModified = true;

         invalidate();

      }
      else if (ptopic->m_atom == ::id_click)
      {

         m_payloadResult = ptopic->m_puserelement->m_atom;

         m_estatus = ::success;

         set_finish();

      }

      ::user::interaction::handle(ptopic, pcontext);

   }


   void default_message_box::invalidate()
   {

      m_bInvalidated = true;

   }


   void default_message_box::do_show()
   {

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }

//
//   void default_message_box::on_layout(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      int iMaxWidth = 100;
//
//      for (auto& pbutton : m_buttona)
//      {
//
//         pbutton->resize_to_fit(pgraphics);
//
//         if (pbutton->width() > iMaxWidth)
//         {
//
//            iMaxWidth = pbutton->width();
//
//         }
//
//      }
//
//      ::rectangle_i32 rectangleMonitor;
//
//      auto psession = get_session();
//
//      auto puser = psession->user();
//
//      puser->windowing()->display()->get_main_monitor(rectangleMonitor);
//
//      int iButtonGroupWidth = (int) (iMaxWidth * 1.25 * m_buttona.get_count());
//
//      int iWidth = maximum((int)(iButtonGroupWidth * 1.1), rectangleMonitor.width() / 2);
//
//      m_pstill->place({ 10, 10, iWidth - 20, 200 });
//
//      m_pstill->display();
//
//      int right = (int) (iWidth - 10);
//
//      int iButton = (int) m_buttona.get_upper_bound();
//
//      while(iButton>= 0)
//      {
//
//         auto pbutton = m_buttona[iButton];
//
//         pbutton->place({ right - iMaxWidth, 210, right, 280 });
//         pbutton->display();
//         right -= (int) (iMaxWidth * 1.25);
//         iButton--;
//      }
//
//      ::rectangle_i32 r;
//
//      r.set_dim(0, 0, iWidth, 300);
//
//      r.Align(e_align_center, rectangleMonitor);
//
//      if (r != screen_rect())
//      {
//
//         place(r);
//
//         if (!m_bFirstLayoutDone)
//         {
//
//            m_bFirstLayoutDone = true;
//
//            set_need_layout();
//
//            set_need_redraw();
//
//            post_redraw();
//
//         }
//
//      }
//
//   }


   void default_message_box::do_layout()
   {

      ::draw2d::graphics_pointer pgraphics;

      __construct(pgraphics);

      pgraphics->create_memory_graphics();

      pgraphics->m_pdraw2dhost = this;

      m_pinteractionScaler = __allocate< ::user::interaction_scaler >();

      m_pinteractionScaler->on_display_change(this);

      int iMaxWidth = 100;

      for (auto& pbutton : m_buttona)
      {

         pbutton->resize_to_fit(pgraphics);

         if (pbutton->width() > iMaxWidth)
         {

            iMaxWidth = pbutton->width();

         }

      }

      ::rectangle_i32 rectangleMonitor;

      auto psession = get_session();

      auto puser = psession->user();

      puser->windowing()->display()->get_main_monitor(rectangleMonitor);

      int iButtonGroupWidth = (int) ((iMaxWidth + 30 * screen_scaler()) * m_buttona.get_count());

      int iWidth = maximum((int)(iButtonGroupWidth + 20 * screen_scaler()), rectangleMonitor.width() / 2);

      m_pstill->place({ 30 * screen_scaler(), 10 * screen_scaler(), iWidth - 60 * screen_scaler(), 200 * screen_scaler() });

      m_pstill->display();

      int right = (int) (iWidth - 20);

      int iButton = (int) m_buttona.get_upper_bound();

      while(iButton>= 0)
      {

         auto pbutton = m_buttona[iButton];

         pbutton->place({ right - iMaxWidth, 230 * screen_scaler(), right, 280 * screen_scaler() });
         pbutton->display();
         right -= (int) (iMaxWidth + 20 * screen_scaler());
         iButton--;

      }

      ::rectangle_i32 r;

      r.set_dimension(0, 0, iWidth, (::i32) (300 * screen_scaler()));

      m_pbuttonClose->place({iWidth - 25, 1, iWidth - 1, 25});

      m_pbuttonClose->display();

      r.Align(e_align_horizontal_center, rectangleMonitor);

      r.offset_y((rectangleMonitor.height() - r.height()) * 2 / 5);

      if (r != this->screen_rectangle())
      {

         place(r);

//         if (!m_bFirstLayoutDone)
//         {
//
//            m_bFirstLayoutDone = true;
//
//            set_need_layout();
//
//            set_need_redraw();
//
//            post_redraw();
//
//         }

      }

   }


   ////bool default_message_box::process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
   //void default_message_box::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   if (ptopic->m_atom == ::id_click)
   //   {

   //      m_edialogresult = (enum_dialog_result) ptopic->m_puserelement->m_atom.i64();

   //      ::extended::asynchronous <::conversation>::sequence()->set_status(::success);

   //      set_finish();

   //   }

   //}


   void default_message_box::close_window()
   {


   }


   bool default_message_box::on_click(int iResult)
   {

      m_iResult = iResult;

      close_window();

      return true;

   }


   void default_message_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      auto rectangleX = this->rectangle();

      auto pstyle = get_style(pgraphics);

      auto colorBorder = pstyle->get_color(this, e_element_border);

      colorBorder.m_u8Opacity = 100;

      pgraphics->draw_inset_rectangle(rectangleX, colorBorder, 1.0);

   }


} // namespace user


namespace aura
{


   //pointer< ::extended::future < ::conversation > > system::message_box(oswindow oswindow, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
   //{

   //   auto pnode = m_pnode->m_pauranode;

   //   auto pfuture = pnode->_message_box(oswindow, strMessage, strTitle, emessagebox);

   //   //auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::future();

   //   //pmessagebox->show(pszMessage, pszTitle, emessagebox);

   //   return pfuture;

   //}


} // namespace aura



