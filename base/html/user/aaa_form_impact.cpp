#include "framework.h"
#include "form_impact.h"
#include "document.h"
#include "acme/constant/happening.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "aura/user/user/frame.h"


html_form_impact::html_form_impact()
{

}


html_form_impact::~html_form_impact()
{

}


void html_form_impact::install_message_routing(::channel * pchannel)
{

   ::user::show < ::html_form>::install_message_routing(pchannel);

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


void html_form_impact::on_form_implemented()
{

   ::html_form::on_form_implemented();

   auto pdocument = get_document();

   if (::is_set(pdocument))
   {

      pdocument->call_procedures(e_happening_load);

   }

}

///////////////////////////////////////////////////////////////////////////////
//// html_form_impact drawing
//void html_form_impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
//{
//
//   UNREFERENCED_PARAMETER(pgraphics);
//
//}


/////////////////////////////////////////////////////////////////////////////
// html_form_impact diagnostics

//void html_form_impact::assert_ok() const
//{
//   ::user::show <::html_form>::assert_ok();
//}
//
//void html_form_impact::dump(dump_context & dumpcontext) const
//{
//   ::user::show <::html_form>::dump(dumpcontext);
//}



// vmpLightImpact.cpp : implementation of the html_form_impact class
//


bool html_form_impact::pre_create_window(::user::system * pusersystem)
{

#ifdef WINDOWS_DESKTOP



#endif

   return ::user::show <::html_form>::pre_create_window(pusersystem);

}


string html_form_impact::GetLocationURL()
{

   return m_strPath;

}

bool html_form_impact::Refresh2(i32 i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}


bool html_form_impact::browse(const ::string & pszUrl)
{
   ASSERT(false);
   /*   if(!open_document(pszUrl))
         return false;*/
   m_strPath = pszUrl;
   return true;
}

void html_form_impact::on_document_complete(const ::string & strUrl)
{
   UNREFERENCED_PARAMETER(strUrl);
}


void html_form_impact::on_message_set_focus(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   if(get_html_data()->m_pcoredata->m_focusptra.get_size() > 0)
   {

      get_html_data()->m_pcoredata->m_focusptra[0]->set_keyboard_focus();

   }

}


void html_form_impact::on_message_kill_focus(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


form_document * html_form_impact::get_document()
{
   return dynamic_cast < form_document * > (::user::show <::html_form>::get_document());
}


void html_form_impact::handle(::topic * ptopic, ::context * pcontext)
{

   ::html_form::handle(ptopic, pcontext);

   ////__update(::update)
   {

      if (ptopic->m_atom == id_document_complete)
      {

         ASSERT(get_html_data() != nullptr);

         defer_implement();

         _001InitializeFormPreData();

         _001UpdateFunctionStatic();

         for (auto pinteraction : proper_children())
         {

            _001Update(pinteraction);

         }

         defer_html_layout();

         on_document_complete(ptopic->payload(id_url));

         parent_frame()->set_active_impact(this);

         set_keyboard_focus();

      }

   }

   ////__update(::update)
   {

      if (ptopic->m_atom == ID_BROWSE)
      {

         if (!ptopic->payload(id_form).is_empty())
         {

            ::file::path matter;

            auto pcontext = get_context();

            matter = pcontext->m_papexcontext->dir()->matter(ptopic->payload(id_form));

            if (get_document()->on_open_document(matter))
            {

               m_strPath = ptopic->payload(id_form);

            }

         }
         else if (ptopic->m_atom == id_get_form_impact)
         {

            ptopic->payload(id_form) = this;

         }

      }

      if (m_pcallback != nullptr)
      {

         ptopic->payload(id_form) = this;

         m_pcallback->handle(ptopic, pcontext);

      }

   }

}


