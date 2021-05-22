#include "framework.h"
#include "_user.h"


html_view::html_view()
{

   auto pform = m_pform;

   output_debug_string("html_view::on_message_create");

}


html_view::~html_view()
{

}


void html_view::install_message_routing(::channel * pchannel)
{

   html_form::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_destroy, pchannel, this, &html_view::_001OnDestroy);
   MESSAGE_LINK(e_message_create, pchannel, this, &html_view::on_message_create);
   MESSAGE_LINK(e_message_context_menu, pchannel, this, &html_view::_001OnContextMenu);
   MESSAGE_LINK(e_message_set_cursor, pchannel, this, &html_view::_001OnSetCursor);

}


void html_view::assert_valid() const
{

   ::user::impact::assert_valid();

}


void html_view::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}


bool html_view::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::impact::pre_create_window(pusersystem);

}


void html_view::_001OnDestroy(::message::message * pmessage)
{

   ::user::impact::_001OnDestroy(pmessage);

}


void html_view::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

   auto pform = m_pform;

   output_debug_string("html_view::on_message_create");

}


void html_view::_001OnContextMenu(::message::message * pmessage)
{

}


void html_view::_001OnSetCursor(::message::message * pmessage)
{

   __pointer(::message::set_cursor) psetcursor(pmessage);

   auto psession = get_session();

   auto puser = psession->user();

   auto pwindowing = puser->windowing();

   auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

   psetcursor->m_pcursor = pcursor;

   pmessage->m_lresult = 1;

   pmessage->m_bRet = true;

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

   if (!get_document()->on_open_document(pszUrl))
   {

      return false;

   }

   m_strLocationURL = pszUrl;

   return true;

}


void html_view::on_document_complete(const char * pszUrl)
{

   UNREFERENCED_PARAMETER(pszUrl);

}


