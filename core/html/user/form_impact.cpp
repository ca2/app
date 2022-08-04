#include "framework.h"
#include "_user.h"


html_form_impact::html_form_impact()
{

}


html_form_impact::~html_form_impact()
{

}


void html_form_impact::install_message_routing(::channel * pchannel)
{

   ::user::form_impact::install_message_routing(pchannel);

   //MESSAGE_LINK(e_message_destroy, pchannel, this, &html_form_impact::on_message_destroy);
   //MESSAGE_LINK(e_message_size, pchannel, this, &html_form_impact::on_message_size);

   //MESSAGE_LINK(WM_USER + 177     , this, this, &html_form_impact::_001OnTabClick);
   //add_command_handler(ID_FILE_PRINT, ::user::form_impact::OnFilePrint)
   //add_command_handler(ID_FILE_PRINT_DIRECT, ::user::form_impact::OnFilePrint)
   //add_command_handler(ID_FILE_PRINT_PREVIEW, ::user::form_impact::OnFilePrintThumbnail)
   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::on_message_left_button_up);
   //MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
   //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &html_form_impact::on_message_left_button_down);
   //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &html_form_impact::on_message_mouse_move);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &html_form_impact::on_message_left_button_up);
   //MESSAGE_LINK(e_message_key_down, pchannel, this, &html_form_impact::on_message_key_down);
   MESSAGE_LINK(e_message_set_focus, pchannel, this, &html_form_impact::on_message_set_focus);
   MESSAGE_LINK(e_message_kill_focus, pchannel, this, &html_form_impact::on_message_kill_focus);
   //MESSAGE_LINK(e_message_create, pchannel, this, &html_form_impact::on_message_create);

}


/////////////////////////////////////////////////////////////////////////////
// html_form_impact drawing
void html_form_impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   __UNREFERENCED_PARAMETER(pgraphics);

}


/////////////////////////////////////////////////////////////////////////////
// html_form_impact diagnostics

void html_form_impact::assert_ok() const
{
   ::user::form_impact::assert_ok();
}

void html_form_impact::dump(dump_context & dumpcontext) const
{
   ::user::form_impact::dump(dumpcontext);
}

/////////////////////////////////////////////////////////////////////////////
// html_form_impact message handlers

// vmpLightImpact.cpp : implementation of the html_form_impact class
//


bool html_form_impact::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::form_impact::pre_create_window(pusersystem);

}


string html_form_impact::GetLocationURL()
{

   return m_strPath;

}

bool html_form_impact::Refresh2(i32 i)
{
   __UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_form_impact::Navigate(const ::string & pszUrl)
{
   ASSERT(false);
   /*   if(!open_document(pszUrl))
         return false;*/
   m_strPath = pszUrl;
   return true;
}

void html_form_impact::on_document_complete(const ::string & strUrl)
{
   __UNREFERENCED_PARAMETER(strUrl);
}


void html_form_impact::on_message_set_focus(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   if(get_html_data()->m_pcoredata->m_focusptra.get_size() > 0)
   {

      get_html_data()->m_pcoredata->m_focusptra[0]->set_keyboard_focus();

   }

}


void html_form_impact::on_message_kill_focus(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

}


form_document * html_form_impact::get_document()
{
   return dynamic_cast < form_document * > (::user::form_impact::get_document());
}
