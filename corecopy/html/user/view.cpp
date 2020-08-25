#include "framework.h"
#include "internal.h"

//   // BEGIN_MESSAGE_MAP(html_view, ::user::impact)
//{{__MSG_MAP(html_view)
/*
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_PAINT()

ON_WM_CONTEXTMENU()
ON_WM_SETCURSOR()
ON_WM_ERASEBKGND()
//}}__MSG_MAP
// Standard printing commands
ON_MESSAGE(WM_USER + 177, OnTabClick)
ON_COMMAND(ID_FILE_PRINT, ::user::impact::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)
*/
// // END_MESSAGE_MAP()


html_view::html_view()
{

}


html_view::~html_view()
{

}


void html_view::install_message_routing(::channel * pchannel)
{
   html_form::install_message_routing(pchannel);

   IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &html_view::_001OnDestroy);
   //IGUI_MSG_LINK(WM_SIZE, pchannel, this, &html_view::_001OnSize);
   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &html_view::_001OnCreate);
   IGUI_MSG_LINK(WM_CONTEXTMENU, pchannel, this, &html_view::_001OnContextMenu);
   IGUI_MSG_LINK(WM_SETCURSOR, pchannel, this, &html_view::_001OnSetCursor);

   //   IGUI_MSG_LINK(WM_USER + 177     , this, this, &html_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)
   //   IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &::user::interaction::_001OnLButtonDown);
   //   IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &::user::interaction::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
   //IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &::user::interaction::_001OnKeyUp);

   //IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &html_view::_001OnLButtonDown);
   //IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &html_view::_001OnMouseMove);
   //IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &html_view::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &html_view::_001OnKeyDown);

}

/////////////////////////////////////////////////////////////////////////////
// html_view diagnostics


void html_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void html_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}



bool html_view::pre_create_window(::user::create_struct& cs)
{
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::user::impact::pre_create_window(cs);
}



void html_view::_001OnDestroy(::message::message * pmessage)
{

   ::user::impact::_001OnDestroy(pmessage);

}


void html_view::_001OnCreate(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }


//   if (get_html_data() == nullptr)
//   {
//
//      return;
//
//   }
//
//   get_html_data()->m_pcoredata->m_puserinteraction = this;
//
//   get_html_data()->m_pcoredata->m_strPathName = get_document()->get_file_path();

}


void html_view::_001OnContextMenu(::message::message * pmessage)
{

}


void html_view::_001OnSetCursor(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   pmouse->m_ecursor = cursor_arrow;

   pmessage->previous();

}



string html_view::GetLocationURL()
{

   return m_strLocationURL;

}


bool html_view::Refresh2(i32 i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_view::Navigate(const char * pszUrl)
{
   if(!get_document()->on_open_document(pszUrl))
      return false;
   m_strLocationURL = pszUrl;
   return true;
}

void html_view::on_document_complete(const char * pszUrl)
{
   UNREFERENCED_PARAMETER(pszUrl);
}


