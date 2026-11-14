#include "platform.h"
#include "acme/handler/topic.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/button.h"
#include "aura/user/user/plain_edit.h"
#include "berg/user/form/document.h"
#include "berg/user/form/impact.h"
#include "berg/user/simple/frame_window.h"
#include "berg/user/experience/frame.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/user/user/interaction_array.h"
#include "core/platform/session.h"
#include "core/user/user/user.h"

#include "acme/constant/id.h"
#include "dialog.h"
//#include "user.h"


namespace userex
{
   dialog::dialog()
   {

      m_pformdocument = nullptr;
      m_pframe = nullptr;

   }


   dialog::dialog(const ::scoped_string & scopedstrMatter, ::pointer<::user::interaction>puiParent)
   {

      initialize(puiParent);
      m_pdialogOwner = puiParent;

      m_strMatter = scopedstrMatter;
      m_pformdocument    = nullptr;
      m_pframe       = nullptr;

   }


   dialog::~dialog()
   {
      if(m_pformdocument != nullptr)
      {
         m_pformdocument->on_close_document();
         m_pformdocument = nullptr;
      }
      if(m_pframe != nullptr)
      {
         //      m_pframe->DestroyWindow();
         // m_pframe = nullptr;
      }
   }


   void dialog::set_action_button(::user::button * pbutton)
   {
      auto previous = payload("dialog_action_button").cast<::user::button>();
      if (previous) previous->m_callbackOnAction = {};
      payload("dialog_action_button") = pbutton;
      if (pbutton)
      {
         pbutton->m_callbackOnAction = [this](::user::interaction *, ::item * pitem,
            ::user::activation_token * puseractivationtoken)
         {
            return on_action(pitem, puseractivationtoken);
         };
      }
   }


   void dialog::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (!ptopic->m_bRet && ptopic->id() == ::id_enter_key && m_pform)
      {
         ::cast < ::user::plain_edit > pedit = ptopic->user_interaction();
         if (pedit && !pedit->m_bMultiLine)
         {
            ::user::interaction * pinteraction = pedit;
            for (auto parent = pinteraction->get_parent(); parent; parent = parent->get_parent())
            {
               if (parent != m_pform) continue;
               auto pbutton = payload("dialog_action_button").cast<::user::button>();
               if (pbutton && pbutton->is_window_enabled() && pbutton->is_window_visible(::user::e_layout_sketch))
               {
                  ptopic->m_bRet = pbutton->on_action(nullptr, ptopic->m_actioncontext.user_activation_token());
               }
               break;
            }
         }
      }

      if(::is_set(ptopic->user_interaction()) && m_pform == nullptr)
      {

         if(ptopic->id() == ::id_create)
         {

            m_pform = ptopic->user_interaction();

         }

      }

   }


   bool dialog::show(const ::scoped_string & scopedstrMatter)
   {

      string strMatter(scopedstrMatter);

      strMatter.trim();

      auto pcontext = m_papplication;

      auto psession = pcontext->m_psession;

      auto puser = psession->m_puser;

      if (strMatter.has_character())
      {

         if (!case_insensitive_string_begins(strMatter, "matter://"))
         {

            strMatter = "matter://" + strMatter;

         }

         m_strMatter = ::file::path(strMatter);

         ::payload payload;

         payload["url"] = strMatter;

         payload["hold"] = false;

         ::payload varArgs;

         varArgs["window_frame"] = true;
         varArgs["dialog_owner"] = m_pdialogOwner;

         m_pformdocument = puser->create_form(this, nullptr, this, psession->get_user_interaction_host(), payload, varArgs);

         if (m_pformdocument == nullptr)
         {

            string str;

            str.formatf("Could not show dialog %s", scopedstrMatter.as_string().c_str());

            informationf(str);

            return false;

         }

      }
      else
      {

         ::payload args;
         args["window_frame"] = true;
         args["dialog_owner"] = m_pdialogOwner;
         m_pformdocument = puser->create_form(this, nullptr, this, psession->get_user_interaction_host(),
            ::e_type_empty_argument, args);

         if (m_pformdocument == nullptr)
         {

            string str;

            str.formatf("Could not show dialog %s", scopedstrMatter.as_string().c_str());

            informationf(str);

            return false;

         }

      }


      auto pimpact = m_pformdocument->get_impact();
      if (!pimpact) return false;
      m_pframe = pimpact->parent_frame();
      m_pform = m_pformdocument->get_typed_impact<::user::form_impact>();
      if (!m_pframe || !m_pform) return false;

      m_pframe->m_bCloseApplicationIfLastVisibleFrame = false;
      // A dialog has a Close button, rather than the application window's full control box.
      for (int i = ::experience::e_button_begin; i <= ::experience::e_button_end; ++i)
      {
         auto button = (::experience::enum_button)i;
         if (button != ::experience::e_button_close) m_pframe->m_ebuttonaHide.add_unique(button);
      }
      m_pframe->disable_dock();
      m_pframe->enable_size(m_bResizable);
      m_pframe->m_bTransparentFrameEnable = false;
      m_pframe->m_bFullScreenEnable = false;
      m_pframe->erase_appearance(e_appearance_transparent_frame);

      //m_pframe->add_each_routine_from(DIALOG_RESULT_PROCESS, this);

      m_pform->payload("tab_focus_scope") = true;
      m_pform->set_form_callback(this);
      bool bInitialized;
      try { bInitialized = on_init_dialog(); }
      catch (...)
      {
         m_pform->set_form_callback(nullptr);
         m_pformdocument->on_close_document();
         m_pform.release();
         m_pframe.release();
         m_pformdocument.release();
         throw;
      }
      if (!bInitialized)
      {
         m_pform->set_form_callback(nullptr);
         m_pformdocument->on_close_document();
         m_pform.release();
         m_pframe.release();
         m_pformdocument.release();
         return false;
      }
      m_pform->set_need_layout();
      m_pframe->set_need_layout();
      on_position_parent_frame();

      on_show(m_strMatter);

      //m_pframe->_001FancyInitialFramePlacement();
      //
      //m_pframe->RunModalLoop();

      //m_pframe->DestroyWindow();

      //m_pformdocument->close_document();

      //m_pform.release();

      //m_pframe.release();

      //m_pformdocument.release();

      return true;

   }


   void dialog::on_show(const ::scoped_string & scopedstrMatter)
   {

      m_pform->display(e_display_normal);
      m_pform->set_need_layout();
      m_pform->set_need_redraw();

      m_pform->post_redraw();

   }


   void dialog::EndModalLoop(atom idResult)
   {

      if (m_pframe == nullptr)
      {

         return;

      }

      if (m_pform) m_pform->set_form_callback(nullptr);
      m_pframe->display(e_display_none);

      m_pframe->set_need_redraw();

      m_pframe->post_redraw();

      m_pframe->set_dialog_response(idResult);

   }







   namespace
   {
      void fit_dialog_control(::user::interaction * control, ::draw2d::graphics_pointer & graphics)
      {
         for_user_interaction_children(child, control) fit_dialog_control(child, graphics);
         control->resize_to_fit(graphics);
      }
   }

   ::i32_size dialog::calculate_client_size(::draw2d::graphics_pointer & graphics)
   {
      ::i32_size size;
      for_user_interaction_children(child, m_pform)
      {
         if (!child->is_this_visible(::user::e_layout_sketch)) continue;
         fit_dialog_control(child, graphics);
         auto rectangle = child->parent_client_rectangle(::user::e_layout_sketch);
         size.cx = maximum(size.cx, rectangle.right + 16);
         size.cy = maximum(size.cy, rectangle.bottom + 16);
      }
      return size;
   }

   void dialog::on_position_parent_frame()
   {

      ::i32_rectangle rectangleOpen;

      m_pframe->best_monitor(&rectangleOpen);

      ::i32 iWidth = rectangleOpen.width();

      ::i32 iHeight = rectangleOpen.height();

      auto graphics = m_pframe->create_memory_graphics();
      auto sizeClient = m_strMatter.is_empty() ? calculate_client_size(graphics) : ::i32_size();
      if (sizeClient.cx > 0 && sizeClient.cy > 0)
      {
         auto sizeWindow = sizeClient;
         if (m_pframe->m_pframe)
         {
            m_pframe->m_pframe->calculate_caption_height(graphics);
            sizeWindow.cx = m_pframe->m_pframe->adjust_client_width(sizeClient.cx);
            sizeWindow.cy = m_pframe->m_pframe->adjust_client_height(sizeClient.cy);
         }
         auto sizeMinimum = m_pframe->get_window_minimum_size();
         sizeWindow.cx = minimum(iWidth, maximum(sizeMinimum.cx, sizeWindow.cx));
         sizeWindow.cy = minimum(iHeight, maximum(sizeMinimum.cy, sizeWindow.cy));
         auto x = rectangleOpen.left + (iWidth - sizeWindow.cx) / 2;
         auto y = rectangleOpen.top + (iHeight - sizeWindow.cy) / 2;
         rectangleOpen = {x, y, x + sizeWindow.cx, y + sizeWindow.cy};
      }
      else
      {
         rectangleOpen.deflate(iWidth / 5, iHeight / 5);
      }

      m_pframe->order(e_zorder_top);

      m_pframe->place(rectangleOpen);

      m_pframe->ActivateFrame();

      m_pframe->set_need_layout();

      m_pframe->set_need_redraw();

      m_pframe->add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);
      m_pframe->display(e_display_normal);
      m_pframe->post_redraw();

   }

   void dialog::OnCancel()
   {
      EndModalLoop("cancel");
   }

   void dialog::OnOK()
   {
      EndModalLoop("ok");
   }

   void dialog::form_from_user()
   {
   }

   void dialog::form_to_user()
   {
   }


   void dialog::do_data_exchange(::user::data_exchange * pdx)
   {
   }


   ::i32_bool dialog::on_init_dialog()
   {

      if (m_pform) m_pform->set_form_callback(this);


      return true;

   }


} // namespace userex



CLASS_DECL_CORE void DDX_Control(::user::data_exchange * pdx, atom idControl, ::user::interaction & control)
{
}

CLASS_DECL_CORE void DDX_Text(::user::data_exchange * pdx, atom idControl, string & str)
{
}

CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, ::i32 iMax)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, ::i32 & iBool)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, bool & b)
{
}


