#include "framework.h"
#include "core/user/simple_ui/_simple_ui.h"

void maximum_line_length(string_array & stra, int iLen)
{

   for(::collection::index i = 0; i < stra.get_size(); i++)
   {

      string & strLine = stra[i];

      if(strLine.length() > iLen - 16)
      {

         stra.insert_at(i + 1, strLine.substr(iLen));

         strLine.truncate(iLen);

      }

   }

}


namespace simple_ui
{


   message_box::message_box(::particle * pparticle, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::duration durationTimeout):
      ::object(pparticle)
   {

      auto estatus = initialize(pparticle);

      if (!estatus)
      {

         throw ::exception(estatus);

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


   void message_box::create_a_button(atom atom, const ::string & pszText)
   {

      create_button(m_tapaA,atom,pszText);

   }


   void message_box::create_b_button(atom atom, const ::string & pszText)
   {

      create_button(m_tapaB,atom,pszText);

   }


   void message_box::create_button(pointer_array < tap > & tapa,atom atom, const ::string & pszText)
   {

      auto ptap = __allocate< ::simple_ui::tap >();

      ptap->create_child(this);

      ptap->set_window_text(pszText);

      tapa.add(ptap);

   }


   i32 message_box::show()
   {

      ::rectangle_i32 rectangleDesktop;

      string_array stra;

      stra.add("\r");

      stra.add("\n");

      stra.add("\r\n");

      m_stra.add_smallest_tokens(m_strMessage,stra);

      maximum_line_length(m_stra, 100);

      auto psession = get_session();

      ::user::interaction * puiParent = psession->cast < ::user::interaction > ("plugin_parent");

      if(puiParent != nullptr)
      {

         puiParent->window_rectangle(rectangleDesktop);

      }
      else
      {

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         pdisplay->get_main_monitor(rectangleDesktop);

      }

      string strTitle = m_strTitle;

      set_window_text(strTitle);

      ::rectangle_i32 rectangleFontopus;

      int stdw = 800;

      int stdh = 400;

      int w = stdw;

      int h = stdh;

      if(w > rectangleDesktop.width())
      {

         w = rectangleDesktop.width();

      }

      if(h > rectangleDesktop.height())
      {

         h = rectangleDesktop.height();

      }

      rectangleFontopus.left() = rectangleDesktop.left() + (rectangleDesktop.width() - w) / 2;

      rectangleFontopus.top() = rectangleDesktop.top() + (rectangleDesktop.height() - h) / 3;

      rectangleFontopus.right() = rectangleFontopus.left() + w;

      rectangleFontopus.bottom() = rectangleFontopus.top() + h;

      //auto pusersystem = __allocate< ::user::system  >(WS_EX_LAYERED, nullptr, nullptr, 0, rectangleFontopus);

      if(!create_interaction(puiParent))
      {

         throw ::exception(::exception("not excepted! Failing Message box!!"));

      }

      informationf("(1) Just after create_window_ex for message_box (m_pimpl.m_p) : %" PRIxPTR, m_pimpl.m_p);

      informationf("(2) Just after create_window_ex for message_box (m_pimpl->m_puserinteraction) : %" PRIxPTR, m_pimpl->m_puserinteraction.m_p);

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

      informationf("(3) Just after create_window_ex for message_box (m_pimpl.m_p) : %" PRIxPTR, m_pimpl.m_p);

      informationf("(4) Just after create_window_ex for message_box (m_pimpl->m_puserinteraction) : %" PRIxPTR, m_pimpl->m_puserinteraction.m_p);

      order(e_zorder_top);

      place(rectangleFontopus);

      display(e_display_normal,XXXe_activation_set_foreground);

      RunModalLoop();

      return m_iResult;

   }


   void message_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleX;

      this->rectangle(rectangleX);

      auto pnode = Node;

      color32_t crBk = pnode->get_simple_ui_color(::e_element_background);

      pgraphics->fill_rectangle(rectangleX,crBk);

      ::pointer<::write_text::font>font(e_create);

      pfont->create_point_font(pnode->font_name(e_font_sans),12);

      pgraphics->set(pfont);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      color32_t crText = pnode->get_simple_ui_color(::e_element_text);

      pgraphics->set_text_color(crText);

      string strMessage = m_stra.implode("\n");

      ::rectangle_i32 rectangle(rectangleX);

      rectangle.deflate(10, 10);

      pgraphics->draw_text(strMessage, rectangle, e_align_top_left, e_draw_text_expand_tabs);

   }


   void message_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if(rectangleX.is_empty())
      {

         return;

      }

      int cx = 100;

      int cy = 25;

      int margin = 10;

      int x = rectangleX.left() + margin;

      int y = rectangleX.bottom() - cy - margin;

      for(::collection::index i = 0; i < m_tapaA.get_count(); i++)
      {

         ::pointer<tap>ptap = m_tapaA[i];

         ptap->order(e_zorder_top);

         ptap->set_dim(x, y, cx, cy);

         ptap->display();

         ptap->set_need_redraw();

         x += cx + margin;

      }

      x = rectangleX.right() - margin - cx;

      for(::collection::index i = m_tapaB.get_upper_bound(); i >= 0; i--)
      {

         ::pointer<tap>ptap = m_tapaB[i];

         ptap->order(e_zorder_top);

         ptap->set_dim(x, y, cx, cy);

         ptap->display();

         ptap->set_need_redraw();

         x -= cx + margin;

      }

   }


   bool message_box::on_action(const ::string & pszId)
   {

      if(case_insensitive_ansi_compare(pszId,"ok") == 0)
      {

         m_iResult = e_dialog_result_ok;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"yes") == 0)
      {

         m_iResult = e_dialog_result_yes;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"no") == 0)
      {

         m_iResult = e_dialog_result_no;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"cancel") == 0)
      {

         m_iResult = e_dialog_result_cancel;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"abort") == 0)
      {

         m_iResult = e_dialog_result_abort;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"retry") == 0)
      {

         m_iResult = e_dialog_result_retry;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"ignore") == 0)
      {

         m_iResult = e_dialog_result_ignore;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"try") == 0)
      {

         m_iResult = e_dialog_result_try_again;

         EndModalLoop(e_dialog_result_ok);

         return true;

      }
      else if(case_insensitive_ansi_compare(pszId,"continue") == 0)
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


   //i64 message_box::increment_reference_count()
   //{

   //   return simple_ui::top::increment_reference_count();

   //}


   //i64 message_box::decrement_reference_count()
   //{

   //   return simple_ui::top::decrement_reference_count();

   //}


} // namespace simple_ui

// message_box_synchronous / with async response wrapper
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
// should be completely compatible to message_box_synchronous (like Yes/No/Cancel/Try...)
// except for the timeout feature (standard behavior/API to be defined).


// message_box with async response
// defaults to ui_message_box
// It fallbacks to message_box_synchronous (with no timeout) when
// user interaction isn't available.


//extern "C"
//CLASS_DECL_CORE void system_message_box(oswindow oswindow, const ::string & pszText, const ::string & pszCaption,u32 uFlags)
//{
//
//   return message_box_synchronous(oswindow, pszText, pszCaption, uFlags, function);
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


//i32 ui_message_box(oswindow oswindow, const ::string & pszMessage, const ::string & pszTitle, u32 uFlags, const ::function_arg & function)
//{
//
//   i32 iResult = 0;
//
//   {
//
//      ::pointer<::simple_ui::message_box>pmessagebox = __allocate< ::simple_ui::message_box >(get_app(),pText,lpCaption,uFlags);
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



