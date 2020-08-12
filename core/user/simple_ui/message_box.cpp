#include "framework.h"


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


   message_box::message_box(::object * pobject,const char * pszMessage,const char * pszTitle, ::emessagebox emessagebox, ::duration durationTimeout):
      ::object(pobject)
   {

      auto estatus = initialize(pobject);

      if (!estatus)
      {

         __throw(::exception::exception(estatus));

      }

      request_state().m_eactivation = activation_on_center_of_screen;

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

      ptap->create_window(this, id);

      ptap->set_window_text(pszText);

      tapa.add(ptap);

   }


   i32 message_box::show()
   {

      ::rect rectDesktop;

      string_array stra;

      stra.add("\r");

      stra.add("\n");

      stra.add("\r\n");

      m_stra.add_smallest_tokens(m_strMessage,stra);
      
      maximum_line_length(m_stra, 100);

      ::user::interaction * puiParent = Session.cast < ::user::interaction > ("plugin_parent");

      if(puiParent != nullptr)
      {

         puiParent->get_window_rect(rectDesktop);

      }
      else
      {

         Session.get_main_monitor(rectDesktop);

      }

      string strTitle = m_strTitle;

      set_window_text(strTitle);

      ::rect rectFontopus;

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

      ::user::create_struct createstruct(WS_EX_LAYERED, nullptr, nullptr, 0, rectFontopus);

      if(!create_window_ex(createstruct, puiParent))
      {

         __throw(::exception::exception("not excepted! Failing Message box!!"));

      }

      TRACE("(1) Just after create_window_ex for message_box (m_pimpl.m_p) : %" PRIxPTR, m_pimpl.m_p);

      TRACE("(2) Just after create_window_ex for message_box (m_pimpl->m_puserinteraction) : %" PRIxPTR, m_pimpl->m_puserinteraction.m_p);

      u32 uiType = m_emessagebox & MB_TYPEMASK;

      switch(uiType)
      {
      case MB_OKCANCEL:
         create_a_button("ok","OK");
         create_a_button("cancel","Cancel");
         break;
      case MB_ABORTRETRYIGNORE:
         create_a_button("abort","Abort");
         create_a_button("retry","Retry");
         create_a_button("ignore","Ignore");
         break;
      case MB_YESNOCANCEL:
         create_a_button("yes","Yes");
         create_a_button("no","No");
         create_a_button("cancel","Cancel");
         break;
      case MB_YESNO:
         create_a_button("yes","Yes");
         create_a_button("no","No");
         break;
      case MB_RETRYCANCEL:
         create_a_button("retry","Retry");
         create_a_button("cancel","Cancel");
         break;
      case MB_CANCELTRYCONTINUE:
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

      order(zorder_top);

      place(rectFontopus);

      display(display_normal, activation_set_foreground);

      RunModalLoop();

      return m_iResult;

   }


   void message_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      COLORREF crBk = get_simple_ui_color(::user::element_background);

      pgraphics->fill_solid_rect(rectClient,crBk);

      __pointer(::draw2d::font) font(e_create);

      font->create_point_font(FONT_SANS,12);

      pgraphics->set(font);

      ::draw2d::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      COLORREF crText = get_simple_ui_color(::user::element_text);

      pgraphics->set_text_color(crText);

      string strMessage = m_stra.implode("\n");

      ::rect rect(rectClient);

      rect.deflate(10, 10);

      pgraphics->draw_text(strMessage, rect,DT_LEFT | DT_TOP | DT_EXPANDTABS);

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

         ptap->order(zorder_top);

         ptap->set_dim(x, y, cx, cy);

         ptap->display();

         ptap->set_need_redraw();

         x += cx + margin;

      }

      x = rectClient.right - margin - cx;

      for(index i = m_tapaB.get_upper_bound(); i >= 0; i--)
      {

         __pointer(tap) ptap = m_tapaB[i];

         ptap->order(zorder_top);

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

         m_iResult = IDOK;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"yes") == 0)
      {

         m_iResult = IDYES;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"no") == 0)
      {

         m_iResult = IDNO;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"cancel") == 0)
      {

         m_iResult = IDCANCEL;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"abort") == 0)
      {

         m_iResult = IDABORT;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"retry") == 0)
      {

         m_iResult = IDRETRY;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"ignore") == 0)
      {

         m_iResult = IDIGNORE;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"try") == 0)
      {

         m_iResult = IDTRYAGAIN;

         EndModalLoop(IDOK);

         return true;

      }
      else if(ansi_compare_ci(pszId,"continue") == 0)
      {

         m_iResult = IDCONTINUE;

         EndModalLoop(IDOK);

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
//CLASS_DECL_CORE void system_message_box(oswindow oswindow, const char * pszText, const char * pszCaption,u32 uiFlags)
//{
//
//   return os_message_box(oswindow, pszText, pszCaption, uiFlags, function);
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


//i32 ui_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, u32 uiFlags, const ::function_arg & function)
//{
//
//   i32 iResult = 0;
//
//   {
//
//      __pointer(::simple_ui::message_box) pmessagebox = __new(::simple_ui::message_box(get_context_application(),pText,lpCaption,uiFlags));
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



