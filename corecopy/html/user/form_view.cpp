#include "framework.h"
#include "internal.h"


html_form_view::html_form_view()
{

}


html_form_view::~html_form_view()
{

}


void html_form_view::install_message_routing(::channel * pchannel)
{

   ::user::form_view::install_message_routing(pchannel);

   //IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &html_form_view::_001OnDestroy);
   //IGUI_MSG_LINK(WM_SIZE, pchannel, this, &html_form_view::_001OnSize);

   //IGUI_MSG_LINK(WM_USER + 177     , this, this, &html_form_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, ::user::form_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::user::form_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::user::form_view::OnFilePrintPreview)
   //IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &::user::interaction::_001OnLButtonDown);
   //IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &::user::interaction::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
   //IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &::user::interaction::_001OnKeyUp);

   //IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &html_form_view::_001OnLButtonDown);
   //IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &html_form_view::_001OnMouseMove);
   //IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &html_form_view::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &html_form_view::_001OnKeyDown);
   IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &html_form_view::_001OnSetFocus);
   IGUI_MSG_LINK(WM_KILLFOCUS, pchannel, this, &html_form_view::_001OnKillFocus);
   //IGUI_MSG_LINK(WM_CREATE, pchannel, this, &html_form_view::_001OnCreate);

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


bool html_form_view::pre_create_window(::user::create_struct& cs)
{
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::user::form_view::pre_create_window(cs);
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
   ASSERT(FALSE);
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

      Session.set_keyboard_focus(get_html_data()->m_pcoredata->m_focusptra[0]);

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