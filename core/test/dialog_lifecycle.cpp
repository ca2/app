#include "core/platform.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "aura/message/user.h"
#include "acme/handler/topic.h"
#include "acme/constant/id.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "core/user/userex/dialog.h"
#include "core/user/user/user.h"
#include "berg/user/form/document.h"
#include "berg/user/form/impact.h"
#include "berg/user/simple/frame_window.h"
#include "berg/user/experience/size_manager.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"

namespace
{
   class test_form : public ::user::form_impact
   {
   public:
      ::simple_frame_window * m_frame = nullptr;
      ::user::interaction * m_root = nullptr;
      ::user::interaction * first_child() override { return m_root; }
      ::user::interaction * next_sibling(::user::interaction *) override { return nullptr; }
      ::user::frame_interaction * parent_frame() override { return m_frame; }
   };
   class submit_edit : public ::user::plain_edit
   {
   public:
      ::user::interaction * m_parent = nullptr;
      ::user::interaction * get_parent() override { return m_parent; }
   };
   class submit_button : public ::user::button
   {
   public:
      bool m_bEnabled = true;
      bool m_bVisible = true;
      bool is_window_enabled() override { return m_bEnabled; }
      bool is_this_visible(::user::enum_layout) override { return m_bVisible; }
   };
   class measured_control : public ::user::interaction
   {
   public:
      ::f64_size m_desired;
      bool m_bVisible = true;
      ::f64_size get_preferred_size(::draw2d::graphics_pointer &) override { return m_desired; }
      bool is_this_visible(::user::enum_layout) override { return m_bVisible; }
      ::user::interaction * first_child() override { return nullptr; }
      void resize_to_fit(::draw2d::graphics_pointer &) override {}
   };
   class measured_line : public ::user::line_layout
   {
   public:
      ::user::interaction * m_first = nullptr;
      ::user::interaction * m_second = nullptr;
      ::user::interaction * m_third = nullptr;
      ::i32_rectangle m_bounds = {16, 16, 16, 16};
      ::user::interaction * first_child() override { return m_first; }
      ::user::interaction * next_sibling(::user::interaction * item) override
      {
         return item == m_first ? m_second : item == m_second ? m_third : nullptr;
      }
      bool is_this_visible(::user::enum_layout) override { return true; }
      void resize_to_fit(::draw2d::graphics_pointer & graphics) override
      {
         auto size = get_preferred_size(graphics);
         m_bounds.right = m_bounds.left + (::i32)size.cx;
         m_bounds.bottom = m_bounds.top + (::i32)size.cy;
      }
      ::i32_rectangle parent_client_rectangle(::user::enum_layout) override { return m_bounds; }
   };
   class test_document : public ::form_document
   {
   public:
      int m_iClosed = 0;
      void on_close_document() override { ++m_iClosed; }
   };
   class test_user : public ::core::user
   {
   public:
      ::pointer < test_document > m_document;
      bool m_bWindowFrame = false;
      ::user::interaction * m_owner = nullptr;
      ::pointer < ::form_document > create_form(::particle *, ::user::form *, ::user::form_callback *,
         ::user::element *, const ::payload &, const ::payload & args) override
      {
         m_bWindowFrame = args["window_frame"].as_bool();
         m_owner = args["dialog_owner"].cast<::user::interaction>();
         return m_document;
      }
   };
   class test_session : public ::platform::session
   {
   public:
      ::user::interaction_base * get_user_interaction_host() override { return nullptr; }
   };
   class test_dialog : public ::userex::dialog
   {
   public:
      int m_iStage = 0;
      bool m_bInitialize = true;
      bool m_bThrow = false;
      ::i32_bool on_init_dialog() override
      {
         if (!m_pform || !m_pframe) return false;
         m_iStage = 1;
         if (m_bThrow) throw ::exception(error_failed);
         return m_bInitialize;
      }
      void on_position_parent_frame() override { if (m_iStage == 1) m_iStage = 2; }
      void on_show(const ::scoped_string &) override { if (m_iStage == 2) m_iStage = 3; }
   };
}

int main()
{
   ::platform::system runtime;
   ::exception::s_bEnableCallStackBackTrace = false;
   ::pointer < ::platform::application > app(allocate_t{});
   app->m_papplication = app;
   ::pointer < test_session > session(allocate_t{});
   app->m_psession = session;
   ::pointer < test_user > user(allocate_t{});
   session->m_puser = user;
   ::pointer < test_document > document(allocate_t{});
   user->m_document = document;
   ::pointer < ::simple_frame_window > frame(allocate_t{});
   ::pointer < test_form > form(allocate_t{});
   form->m_papplication = app;
   frame->m_papplication = app;
   form->m_frame = frame;
   document->m_impacta.add(form);
   ::pointer < test_dialog > dialog(allocate_t{});
   dialog->m_papplication = app;
   dialog->m_pdialogOwner = frame;
   dialog->m_bResizable = false;
   if (!dialog->show() || dialog->m_iStage != 3 || !user->m_bWindowFrame) return 1;
   if (form->get_form_callback() != dialog.get() || user->m_owner != frame.get()) return 2;
   if (frame->m_bSizeEnable) return 13;
   ::experience::size_manager sizeManager;
   sizeManager.m_pframewindow = frame;
   sizeManager.SetGripMask(::e_grip_all);
   if (sizeManager.GetGripMask() != ::e_grip_none) return 14;
   frame->m_bEnableFrameExperience = true;
   frame->m_bWindowFrame = true;
   frame->enable_size(true);
   if (sizeManager.GetGripMask() != ::e_grip_all) return 15;
   frame->enable_size(false);
   for (int i = ::experience::e_button_begin; i <= ::experience::e_button_end; ++i)
      if (frame->m_ebuttonaHide.contains((::experience::enum_button)i) != (i != ::experience::e_button_close)) return 7;
   if (frame->m_bDockEnable || frame->m_bTransparentFrameEnable || frame->m_bFullScreenEnable) return 8;
   ::pointer<submit_button> submit(allocate_t{});
   ::pointer<submit_edit> input(allocate_t{});
   submit->m_papplication = input->m_papplication = app;
   ::pointer<::user::interaction> submitLayout(allocate_t{});
   submitLayout->m_papplication = app;
   submitLayout->m_puserinteractionParent = form;
   input->m_parent = submitLayout;
   input->m_puserinteractionParent = submitLayout;
   input->m_bMultiLine = false;
   int submissions = 0;
   dialog->m_callbackOnAction = [&](::user::interaction *, ::item *, ::user::activation_token *) { ++submissions; return true; };
   dialog->set_action_button(submit);
   auto enter = input->create_topic(::id_enter_key);
   enter->m_puserelement = input;
   form->handle(enter, nullptr);
   if (!enter->m_bRet || submissions != 1) return 16;
   if (!submit->on_action() || submissions != 2) return 22;
   ::message::key enterKey;
   enterKey.m_union.m_pkey = &enterKey;
   enterKey.m_ekey = ::user::e_key_return;
   input->on_message_key_down(&enterKey);
   if (submissions != 3) return 23;
   submissions = 1;
   enter->m_bRet = false;
   submit->m_bEnabled = false;
   form->handle(enter, nullptr);
   if (enter->m_bRet || submissions != 1) return 17;
   submit->m_bEnabled = true;
   submit->m_bVisible = false;
   form->handle(enter, nullptr);
   if (submissions != 1) return 18;
   submit->m_bVisible = true;
   input->m_bMultiLine = true;
   form->handle(enter, nullptr);
   if (submissions != 1) return 19;
   input->m_bMultiLine = false;
   enter->m_bRet = true;
   dialog->handle(enter, nullptr);
   if (submissions != 1) return 20;
   input->m_parent = nullptr;
   input->m_puserinteractionParent.release();
   enter->m_bRet = false;
   dialog->handle(enter, nullptr);
   if (submissions != 1) return 21;
   dialog->set_action_button(nullptr);
   // Break the owner/callback cycle just as EndModalLoop does, without a native window.
   form->set_form_callback(nullptr);
   dialog->m_pformdocument.release();
   dialog->m_pform.release();
   dialog->m_pframe.release();

   dialog->m_bInitialize = false;
   dialog->m_iStage = 0;
   if (dialog->show() || dialog->m_iStage != 1 || document->m_iClosed != 1) return 3;
   if (dialog->m_pframe || dialog->m_pform || dialog->m_pformdocument || form->get_form_callback()) return 4;

   dialog->m_bThrow = true;
   try { dialog->show(); return 5; }
   catch (const ::exception &) {}
   if (document->m_iClosed != 2 || form->get_form_callback()) return 6;
   ::pointer < measured_control > label(allocate_t{}), edit(allocate_t{}), ok(allocate_t{}), cancel(allocate_t{});
   label->m_desired = {140, 24};
   edit->m_desired = {360, 32};
   ok->m_desired = cancel->m_desired = {72, 28};
   ::pointer < measured_line > buttons(allocate_t{}), column(allocate_t{});
   buttons->m_eorientation = e_orientation_horizontal;
   buttons->m_first = ok;
   buttons->m_second = cancel;
   column->m_eorientation = e_orientation_vertical;
   column->m_first = label;
   column->m_second = edit;
   column->m_third = buttons;
   form->m_root = column;
   dialog->m_pform = form;
   ::draw2d::graphics_pointer graphics;
   if (dialog->calculate_client_size(graphics) != ::i32_size(392, 122)) return 9;
   edit->m_rectangleMargin1 = {3, 4, 5, 6};
   if (dialog->calculate_client_size(graphics) != ::i32_size(400, 132)) return 12;
   edit->m_rectangleMargin1 = {};
   label->m_desired = {500, 48};
   if (dialog->calculate_client_size(graphics) != ::i32_size(532, 146)) return 10;
   label->m_bVisible = false;
   if (dialog->calculate_client_size(graphics) != ::i32_size(392, 96)) return 11;
   form->m_root = nullptr;
   dialog->m_pform.release();
   document->m_impacta.erase_all();
   session->m_puser.release();
   return 0;
}
