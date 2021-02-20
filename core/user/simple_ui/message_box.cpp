#include "framework.h"
#include "core/user/simple_ui/_simple_ui.h"

void maximum_line_length(string_array & stra, int iLen)
{

   for(index i = 0; i < stra.get_size(); i++)
   {

      string & strLine = stra[i];

      if(strLine.length() > iLen - 16)
      {

         stra.insert_at(i + 1, strLine.Mid(iLen));

         strLine.truncate(iLen);

      }

   }

}


namespace simple_ui
{


   message_box::message_box(::object * pobject,const char * pszMessage,const char * pszTitle, const ::e_message_box & emessagebox, ::duration durationTimeout):
      ::object(pobject)
   {

      auto estatus = initialize(pobject);

      if (!estatus)
      {

         __throw(::status_exception(estatus));

      }

      layout().sketch() = e_activation_on_center_of_screen;

      m_evReady.ResetEvent();

      m_strMessage      = pszMessage;
      m_strTitle        = pszTitle;
      m_emessagebox     = emessagebox;
      m_durationTimeout = durationTimeout;
      m_iResult         = 0;

   }


   message_box::~message_box()
   {

   }


   void message_box::create_a_button(id id,const char * pszText)
   {

      create_button(m_tapaA,id,pszText);

   }


   void message_box::create_b_button(id id,const char * pszText)
   {

      create_button(m_tapaB,id,pszText);

   }


   void message_box::create_button(__pointer_array(tap) & tapa,id id,const char * pszText)
   {

      auto ptap = __new(::simple_ui::tap);

      ptap->create_child(this);

      ptap->set_window_text(pszText);

      tapa.add(ptap);

   }


   i32 message_box::show()
   {

      ::rectangle_i32 rectDesktop;

      string_array stra;

      stra.add("\r");

      stra.add("\n");

      stra.add("\r\n");

      m_stra.add_smallest_tokens(m_strMessage,stra);

      maximum_line_length(m_stra, 100);

      auto psession = Session;

      ::user::interaction * puiParent = psession->cast < ::user::interaction > ("plugin_parent");

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else
      {

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectDesktop);

      }

      string strTitle = m_strTitle;

      set_window_text(strTitle);

      ::rectangle_i32 rectFontopus;

      int stdw = 800;

      int stdh = 400;

      int w = stdw;

      int h = stdh;

      if(w > rectDesktop.width())
      {

         w = rectDesktop.width();

      }

      if(h > rectDesktop.height())
      {

         h = rectDesktop.height();

      }

      rectFontopus.left = rectDesktop.left + (rectDesktop.width() - w) / 2;

      rectFontopus.top = rectDesktop.top + (rectDesktop.height() - h) / 3;

      rectFontopus.right = rectFontopus.left + w;

      rectFontopus.bottom = rectFontopus.top + h;

      //auto pusersystem = __new(::user::system (WS_EX_LAYERED, nullptr, nullptr, 0, rectFontopus));

      if(!create_interaction(puiParent))
      {

         __throw(::exception::exception("not excepted! Failing Message box!!"));

      }

      TRACE("(1) Just after create_window_ex for message_box (m_pimpl.m_p) : %" PRIxPTR, m_pimpl.m_p);

      TRACE("(2) Just after create_window_ex for message_box (m_pimpl->m_puserinteraction) : %" PRIxPTR, m_pimpl->m_puserinteraction.m_p);

      auto emessagebox = m_emessagebox & e_message_box_type_mask;

      switch(emessagebox)
      {
      case e_message_box_ok_cancel:
         create_a_button("ok","OK");
         create_a_button("cancel","Cancel");
         break;
      case e_message_box_abort_retry_ignore:
         create_a_button("abort","Abort");
         create_a_button("retry","Retry");
         create_a_button("ignore","Ignore");
         break;
      case e_message_box_yes_no_cancel:
         create_a_button("yes","Yes");
         create_a_button("no","No");
         create_a_button("cancel","Cancel");
         break;
      case e_message_box_yes_no:
         create_a_button("yes","Yes");
         create_a_button("no","No");
         break;
      case e_message_box_retry_cancel:
         create_a_button("retry","Retry");
         create_a_button("cancel","Cancel");
         break;
      case e_message_box_cancel_try_continue:
         create_a_button("cancel","Cancel");
         create_a_button("try","Try");
         create_a_button("continue","Continue");
         break;
      default:
         create_a_button("ok","OK");
         break;
      }

      TRACE("(3) Just after create_window_ex for message_box (m_pimpl.m_p) : %" PRIxPTR, m_pimpl.m_p);

      TRACE("(4) Just after create_window_ex for message_box (m_pimpl->m_puserinteraction) : %" PRIxPTR, m_pimpl->m_puserinteraction.m_p);

      order(e_zorder_top);

      place(rectFontopus);

      display(e_display_normal, e_activation_set_foreground);

      RunModalLoop();

      return m_iResult;

   }


   void message_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      auto pnode = Node;

      color32_t crBk = pnode->get_simple_ui_color(::user::e_element_background);

      pgraphics->fill_rectangle(rectClient,crBk);

      __pointer(::write_text::font) font(e_create);

      font->create_point_font(os_font_name(e_font_sans),12);

      pgraphics->set(font);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      color32_t crText = pnode->get_simple_ui_color(::user::e_element_text);

      pgraphics->set_text_color(crText);

      string strMessage = m_stra.implode("\n");

      ::rectangle_i32 rectangle(rectClient);

      rectangle.deflate(10, 10);

      pgraphics->draw_text(strMessage, rectangle, e_align_top_left, e_draw_text_expand_tabs);

   }


   void message_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectClient = get_client_rect();

      if(rectClient.is_empty())
      {

         return;

      }

      int cx = 100;

      int cy = 25;

      int margin = 10;

      int x = rectClient.left + margin;

      int y = rectClient.bottom - cy - margin;

      for(index i = 0; i < m_tapaA.get_count(); i++)
      {

         __pointer(tap) ptap = m_tapaA[i];

         ptap->order(e_zorder_top);

         ptap->set_dim(x, y, cx, cy);

         ptap->display();

         ptap->set_need_redraw();

         x += cx + margin;

      }

      x = rectClient.right - margin - cx;

      for(index i = m_tapaB.get_upper_bound(); i >= 0; i--)
      {

         __pointer(tap) ptap = m_tapaB[i];

         ptap->order(e_zorder_top);

         ptap->set_dim(x, y, cx, cy);

         ptap->display();

         ptap->set_need_redraw();

         x -= cx + margin;

      }

   }


   bool message_box::on_action(const char * pszId)
   {

      if(ansi_compare_ci(pszId,"ok") == 0)
      {

         m_iResult = e_dialog_result_ok;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"yes") == 0)
      {

         m_iResult = e_dialog_result_yes;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"no") == 0)
      {

         m_iResult = e_dialog_result_no;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"cancel") == 0)
      {

         m_iResult = e_dialog_result_cancel;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"abort") == 0)
      {

         m_iResult = e_dialog_result_abort;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"retry") == 0)
      {

         m_iResult = e_dialog_result_retry;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"ignore") == 0)
      {

         m_iResult = e_dialog_result_ignore;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"try") == 0)
      {

         m_iResult = e_dialog_result_try_again;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(ansi_compare_ci(pszId,"continue") == 0)
      {

         m_iResult = e_dialog_result_continue;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }


      return false;

   }


   void message_box::pre_translate_message(::message::message * pmessage)
   {

      user::interaction::pre_translate_message(pmessage);

   }


   bool message_box::has_pending_graphical_update()
   {

      return ::simple_ui::top::has_pending_graphical_update();

   }


   //i64 message_box::add_ref()
   //{

   //   return simple_ui::top::add_ref(OBJ_REF_DBG_ARGS);

   //}


   //i64 message_box::dec_ref()
   //{

   //   return simple_ui::top::dec_ref(OBJ_REF_DBG_ARGS);

   //}


} // namespace simple_ui

// os_message_box / with async response wrapper
// TODO: clip functionality to common behavior from
// all native message boxes at each platform.
// MessageBox that doesn't need user::interaction
//
// Windows MessageBox doesn't need user::interaction
// MacOS MessageBox doesn't need user::interaction
// Linux NotUsed-Toolkits:MessageBoxes ShouldImplementMessageWithNoUIDependency
// Android (Java:MessageBoxes doesn't need user::interaction)?
// iOS (iOS:MessageBoxes)?
// UWP MessageBox doesn't need user::interaction


// ui_message_box with async response
// PLAN: it should be same implementation relying on user::interaction
// should be completely compatible to os_message_box (like Yes/No/Cancel/Try...)
// except for the timeout feature (standard behavior/API to be defined).


// message_box with async response
// defaults to ui_message_box
// It fallbacks to os_message_box (with no timeout) when
// user interaction isn't available.


//extern "C"
//CLASS_DECL_CORE void system_message_box(oswindow oswindow, const char * pszText, const char * pszCaption,u32 uFlags)
//{
//
//   return os_message_box(oswindow, pszText, pszCaption, uFlags, function);
//
//}


//void ui_message_box(::simple_ui::message_box * pmessagebox)
//{
//
//   try
//   {
//
//      pmessagebox->show();
//
//   }
//   catch(...)
//   {
//
//   }
//
//   try
//   {
//
//      pmessagebox->DestroyWindow();
//
//   }
//   catch(...)
//   {
//
//   }
//
//   pmessagebox->m_evReady.SetEvent();
//
//}


//i32 ui_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, u32 uFlags, const ::function_arg & function)
//{
//
//   i32 iResult = 0;
//
//   {
//
//      __pointer(::simple_ui::message_box) pmessagebox = __new(::simple_ui::message_box(get_context_application(),pText,lpCaption,uFlags));
//
//      try
//      {
//
//         ui_message_box(pmessagebox);
//
//         iResult = pmessagebox->m_iResult;
//
//      }
//      catch(...)
//      {
//
//      }
//
//   }
//
//   return iResult;
//
//}



