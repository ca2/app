//
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   //message_box::message_box(const string & strMessageParam, const string & strTitle, const ::e_message_box & emessagebox) :
   message_box::message_box() :
      m_strFontName("serif"),
      m_size(100, 40),
      m_bOsUserThemeColorModified(false),
      m_bInvalidated(false)
   {

      common_construct();

      enable_drag_move();

      m_bClickDefaultMouseHandling = true;

      m_bHoverDefaultMouseHandling = true;

   }


   ::e_status message_box::show(const string& strMessageParam, const string& strTitle, const ::e_message_box& emessagebox)
   {

      ///acme_defer_os_init_windowing();

      string strMessage(strMessageParam);

      m_strTitle = strTitle;

      strMessage.replace_ci("<br>", " \n");

      __construct_new(m_pstill);

      m_pstill->set_window_text(strMessage);

      m_stra.add_lines(strMessage);

      auto emessageboxType = emessagebox & e_message_box_type_mask;

      switch (emessageboxType)
      {
      case e_message_box_ok_cancel:
         m_buttona.add(__new(::user::button("OK", e_dialog_result_ok)));
         m_buttona.add(__new(::user::button("Cancel", e_dialog_result_cancel)));
         break;
      case e_message_box_abort_retry_ignore:
         m_buttona.add(__new(::user::button("Abort", e_dialog_result_abort)));
         m_buttona.add(__new(::user::button("Retry", e_dialog_result_retry)));
         m_buttona.add(__new(::user::button("Ignore", e_dialog_result_ignore)));
         break;
      case e_message_box_yes_no_cancel:
         m_buttona.add(__new(::user::button("Yes", e_dialog_result_yes)));
         m_buttona.add(__new(::user::button("No", e_dialog_result_no)));
         m_buttona.add(__new(::user::button("Cancel", e_dialog_result_cancel)));
         break;
      case e_message_box_yes_no:
         m_buttona.add(__new(::user::button("Yes", e_dialog_result_yes)));
         m_buttona.add(__new(::user::button("No", e_dialog_result_no)));
         break;
      case e_message_box_retry_cancel:
         m_buttona.add(__new(::user::button("Retry", e_dialog_result_retry)));
         m_buttona.add(__new(::user::button("Cancel", e_dialog_result_cancel)));
         break;
      case e_message_box_cancel_try_continue:
         m_buttona.add(__new(::user::button("Cancel", e_dialog_result_cancel)));
         m_buttona.add(__new(::user::button("Try", e_dialog_result_retry)));
         m_buttona.add(__new(::user::button("Continue", e_dialog_result_continue)));
         break;
      default:
         m_buttona.add(__new(::user::button("OK", e_dialog_result_ok)));
         break;
      }

      for (auto& pbutton : m_buttona)
      {

         pbutton->initialize(this);

         pbutton->add_control_event_handler(this);

      }

      set_tool_window();

      display(::e_display_normal);

      do_layout();

      auto estatus = create_host();

      if (!estatus)
      {

         return estatus;

      }

      do_show();

      return estatus;

   }


   void message_box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &message_box::on_message_create);

   }


   i64 message_box::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::user::interaction::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 message_box::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::user::interaction::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 message_box::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::user::interaction::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   void message_box::common_construct()
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


   void message_box::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      for (auto & pbutton : m_buttona)
      {

         pbutton->create_child(this);

      }

      m_pstill->create_child(this);

   }


   message_box::~message_box()
   {


   }


   void message_box::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      if (psubject->id() == id_os_user_theme)
      {

         m_bOsUserThemeColorModified = true;

         invalidate();

      }

   }


   void message_box::invalidate()
   {

      m_bInvalidated = true;

   }


   void message_box::do_show()
   {

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }

//
//   void message_box::on_layout(::draw2d::graphics_pointer & pgraphics)
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


   void message_box::do_layout()
   {

      ::draw2d::graphics_pointer pgraphics;

      pgraphics.create(this);

      pgraphics->create_memory_graphics();

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

      int iButtonGroupWidth = (int) (iMaxWidth * 1.25 * m_buttona.get_count());

      int iWidth = maximum((int)(iButtonGroupWidth * 1.1), rectangleMonitor.width() / 2);

      m_pstill->place({ 10, 10, iWidth - 20, 200 });

      m_pstill->display();

      int right = (int) (iWidth - 10);

      int iButton = (int) m_buttona.get_upper_bound();

      while(iButton>= 0)
      {

         auto pbutton = m_buttona[iButton];

         pbutton->place({ right - iMaxWidth, 210, right, 280 });
         pbutton->display();
         right -= (int) (iMaxWidth * 1.25);
         iButton--;

      }

      ::rectangle_i32 r;

      r.set_dim(0, 0, iWidth, 300);

      r.Align(e_align_horizontal_center, rectangleMonitor);

      r.offset_y((rectangleMonitor.height() - r.height()) * 2 / 5);

      if (r != this->screen_rect())
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


   //bool message_box::process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
   void message_box::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_button_clicked)
      {

         m_edialogresult = (enum_dialog_result) pevent->m_id.i64();

         ::extended::asynchronous <::conversation>::future()->set_status(::success);

         finish();

      }

   }


   void message_box::close_window()
   {


   }


   bool message_box::on_click(int iResult)
   {

      m_iResult = iResult;

      close_window();

      return true;

   }


} // namespace user




namespace aura
{


   __pointer(::extended::future < ::conversation >) system::_message_box(::object * pobject, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox)
   {

      auto pmessagebox = pobject->__create_new < ::user::message_box >();

      auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::future();

      pmessagebox->show(pszMessage, pszTitle, emessagebox);

      return pfuture;

   }


} // namespace aura



