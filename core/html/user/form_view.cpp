#include "framework.h"
#include "_user.h"


html_form_view::html_form_view()
{

}


html_form_view::~html_form_view()
{

}


void html_form_view::install_message_routing(::channel * pchannel)
{

   ::user::form_view::install_message_routing(pchannel);

   //MESSAGE_LINK(e_message_destroy, pchannel, this, &html_form_view::on_message_destroy);
   //MESSAGE_LINK(e_message_size, pchannel, this, &html_form_view::on_message_size);

   //MESSAGE_LINK(WM_USER + 177     , this, this, &html_form_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, ::user::form_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::user::form_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::user::form_view::OnFilePrintPreview)
   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::on_message_left_button_up);
   //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
   //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &html_form_view::on_message_left_button_down);
   //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &html_form_view::on_message_mouse_move);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &html_form_view::on_message_left_button_up);
   //MESSAGE_LINK(e_message_key_down, pchannel, this, &html_form_view::on_message_key_down);
   MESSAGE_LINK(e_message_set_focus, pchannel, this, &html_form_view::_001OnSetFocus);
   MESSAGE_LINK(e_message_kill_focus, pchannel, this, &html_form_view::_001OnKillFocus);
   //MESSAGE_LINK(e_message_create, pchannel, this, &html_form_view::on_message_create);

}


/////////////////////////////////////////////////////////////////////////////
// html_form_view drawing
void html_form_view::OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   UNREFERENCED_PARAMETER(pgraphics);

}


/////////////////////////////////////////////////////////////////////////////
// html_form_view diagnostics

void html_form_view::assert_valid() const
{
   ::user::form_view::assert_valid();
}

void html_form_view::dump(dump_context & dumpcontext) const
{
   ::user::form_view::dump(dumpcontext);
}

/////////////////////////////////////////////////////////////////////////////
// html_form_view message handlers

// vmpLightView.cpp : implementation of the html_form_view class
//


bool html_form_view::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::form_view::pre_create_window(pusersystem);

}


string html_form_view::GetLocationURL()
{

   return m_strPath;

}

bool html_form_view::Refresh2(i32 i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_form_view::Navigate(const char * pszUrl)
{
   ASSERT(false);
   /*   if(!open_document(pszUrl))
         return false;*/
   m_strPath = pszUrl;
   return true;
}

void html_form_view::on_document_complete(const char * pszUrl)
{
   UNREFERENCED_PARAMETER(pszUrl);
}


void html_form_view::_001OnSetFocus(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   if(get_html_data()->m_pcoredata->m_focusptra.get_size() > 0)
   {

      get_html_data()->m_pcoredata->m_focusptra[0]->set_keyboard_focus();

   }

}


void html_form_view::_001OnKillFocus(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


form_document * html_form_view::get_document()
{
   return dynamic_cast < form_document * > (::user::form_view::get_document());
}
