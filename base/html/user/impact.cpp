#include "framework.h"
#include "impact.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "axis/html/html/data.h"


html_impact::html_impact()
{

   auto pform = m_pform;

   infomration("html_impact::on_message_create");

}


html_impact::~html_impact()
{

}


void html_impact::initialize(::particle * pparticle)
{

   ::user::form_impact::initialize(pparticle);

   ::html_form::initialize(pparticle);

}


void html_impact::install_message_routing(::channel * pchannel)
{

   ::user::form_impact::install_message_routing(pchannel);

   ::html_form::install_message_routing(pchannel);

   MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &html_impact::on_message_destroy);
   MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &html_impact::on_message_create);
   MESSAGE_LINK(e_message_context_menu, pchannel, this, &html_impact::on_message_context_menu);
   //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &html_impact::on_message_set_cursor);

}


//void html_impact::assert_ok() const
//{
//
//   ::user::impact::assert_ok();
//
//}
//
//
//void html_impact::dump(dump_context & dumpcontext) const
//{
//
//   ::user::impact::dump(dumpcontext);
//
//}


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

   infomration("html_impact::on_message_create");

}


void html_impact::on_message_context_menu(::message::message * pmessage)
{

}


//void html_impact::on_message_set_cursor(::message::message * pmessage)
//{
//
//   ::pointer<::message::set_cursor>psetcursor(pmessage);
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

   UNREFERENCED_PARAMETER(i);

   get_document()->on_open_document(GetLocationURL());

   return true;

}


bool html_impact::browse(const ::string & pszUrl)
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

   UNREFERENCED_PARAMETER(strUrl);

}



//
//void html_impact::handle(::topic * ptopic, ::context * pcontext)
//{
//
//   ::html_form::handle(ptopic, pcontext);
//
//   ////__update(::update)
//   {
//
//      if (ptopic->m_atom == id_document_complete)
//      {
//
//         {
//
//            synchronous_lock synchronouslock(this->synchronization());
//
//            if (get_html_data() == nullptr)
//            {
//
//               return;
//
//            }
//
//            get_html_data()->implement(this);
//
//         }
//
//         on_document_complete(ptopic->payload(id_url));
//
//         set_need_layout();
//
//         set_need_redraw();
//
//      }
//
//   }
//
//}


void html_impact::handle(::topic * ptopic, ::context * pcontext)
{

   ::user::form_impact::handle(ptopic, pcontext);

   if (ptopic->m_bRet)
   {

      return;

   }

   ::html_form::handle(ptopic, pcontext);

   ////__update(::update)
   {

      if (ptopic->m_atom == id_document_complete)
      {

         {

            synchronous_lock synchronouslock(this->synchronization());

            if (get_html_data() == nullptr)
            {

               return;

            }

            get_html_data()->implement(this);

         }

         on_document_complete(ptopic->payload(id_url));

         set_need_layout();

         set_need_redraw();

      }

   }

}


bool html_impact::open_document(const ::payload & payloadFile)
{

   return html_form::open_document(payloadFile);

}


bool html_impact::open_html(const ::string & strHtml)
{

   return html_form::open_html(strHtml);

}


void html_impact::soft_reload()
{

   html_form::soft_reload();

}


void html_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::html_form::_001OnDraw(pgraphics);

}


void html_impact::on_form_implemented()
{

   ::html_form::on_form_implemented();

   auto pdocument = get_document();

   if (::is_set(pdocument))
   {

      pdocument->call_procedures("load");

   }

}


void html_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::html_form::on_layout(pgraphics);

}


void html_impact::set_need_load_form_data()
{

   ::html_form::set_need_load_form_data();

}



