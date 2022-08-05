#include "framework.h"
#include "_user.h"


html_impact::html_impact()
{

   auto pform = m_pform;

   output_debug_string("html_impact::on_message_create");

}


html_impact::~html_impact()
{

}


void html_impact::install_message_routing(::channel * pchannel)
{

   html_form::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_destroy, pchannel, this, &html_impact::on_message_destroy);
   MESSAGE_LINK(e_message_create, pchannel, this, &html_impact::on_message_create);
   MESSAGE_LINK(e_message_context_menu, pchannel, this, &html_impact::on_message_context_menu);
   //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &html_impact::on_message_set_cursor);

}


void html_impact::assert_ok() const
{

   ::user::impact::assert_ok();

}


void html_impact::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}


bool html_impact::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::impact::pre_create_window(pusersystem);

}


void html_impact::on_message_destroy(::message::message * pmessage)
{

   ::user::impact::on_message_destroy(pmessage);

}


void html_impact::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

   auto pform = m_pform;

   output_debug_string("html_impact::on_message_create");

}


void html_impact::on_message_context_menu(::message::message * pmessage)
{

}


//void html_impact::on_message_set_cursor(::message::message * pmessage)
//{
//
//   __pointer(::message::set_cursor) psetcursor(pmessage);
//
//   auto psession = get_session();
//
//   auto puser = psession->user();
//
//   auto pwindowing = puser->windowing();
//
//   auto pcursor = pwindowing->get_cursor(e_cursor_arrow);
//
//   psetcursor->m_pcursor = pcursor;
//
//   pmessage->m_lresult = 1;
//
//   pmessage->m_bRet = true;
//
//}


string html_impact::GetLocationURL()
{

   return m_strLocationURL;

}


bool html_impact::Refresh2(i32 i)
{

   __UNREFERENCED_PARAMETER(i);

   get_document()->on_open_document(GetLocationURL());

   return true;

}


bool html_impact::Navigate(const ::string & pszUrl)
{

   if (!get_document()->on_open_document(pszUrl))
   {

      return false;

   }

   m_strLocationURL = pszUrl;

   return true;

}


void html_impact::on_document_complete(const ::string & strUrl)
{

   __UNREFERENCED_PARAMETER(strUrl);

}


