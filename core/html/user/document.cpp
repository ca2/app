#include "framework.h"
#include "_user.h"
#include "aura/update.h"
#include "acme/const/id.h"


html_document::html_document()
{

}


bool html_document::on_new_document()
{

   get_html_data()->m_pcoredata->m_pform = get_typed_view < ::html_form >();

   if (::is_set(get_html_data()->m_pcoredata->m_pform))
   {

      if (get_html_data()->m_pcoredata->m_pform->m_pathDefaultDocument.has_char())
      {

         return on_open_document(get_html_data()->m_pcoredata->m_pform->m_pathDefaultDocument);

      }

   }

   if (!::user::document::on_new_document())
   {

      return false;

   }

   update_all_views(nullptr, NEW_DOCUMENT_UPDATE);

   return true;

}


html_document::~html_document()
{

}


void html_document::assert_valid() const
{

   ::user::document::assert_valid();

}


void html_document::dump(dump_context & dumpcontext) const
{

   ::user::document::dump(dumpcontext);

}



::e_status html_document::create_html_data()
{

   auto estatus = __compose_new(m_phtmldata);

   if (!estatus)
   {

      return estatus;

   }

   auto pdata = get_html_data();

   pdata->m_pdocument = this;

   pdata->m_pcoredata = new ::html::core_data;

   pdata->m_pcoredata->initialize_html_data(pdata);

   pdata->m_pimplHtml = ::move(pdata->m_pcoredata);

   pdata->::form_data::m_pimpl = pdata->m_pimplHtml;

   set_data("html", pdata);

   pdata->m_pcoredata->m_puserinteraction = get_typed_view < ::user::form_view >();

   pdata->m_pcoredata->m_pcallback = this;

   return ::success;

}


void html_document::data_on_after_change(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


void html_document::form_document_set_property_set(const property_set & set)
{

   get_html_data()->get_property_set() = set;

}


property_set * html_document::form_document_get_property_set()
{

   return &get_html_data()->get_property_set();

}


//bool html_document::open_document(::create * pcreate)
//{
//
//   auto phtmlform = get_typed_view < ::html_form >();
//
//   if (!phtmlform)
//   {
//
//      auto pform = get_typed_view < ::user::form_view >();
//
//      if (!pform)
//      {
//
//         return false;
//
//      }
//
//      pform->create_child_form <html_view>();
//
//      phtmlform = pform->m_pformChild;
//
//      phtmlform->m_pcallback = pform;
//
//   }
//
//   get_html_data()->m_pcoredata->m_pform = phtmlform;
//
//   if(::is_null(get_html_data()->m_pcoredata->m_pform))
//   {
//
//      return false;
//
//   }
//
//   if(::is_null(phtmlform->m_pcallback))
//   {
//
//      auto pcallback = pcreate->m_varArgs["form_callback"].cast < ::user::form_callback >();
//
//      if(pcallback)
//      {
//
//         phtmlform->m_pcallback = pcallback;
//
//      }
//
//   }
//
//   return open_document(pcreate->m_pcommandline->m_varFile);
//
//}


bool html_document::on_open_document(const ::payload & varFile)
{

   auto phtmlform = get_typed_view < ::html_form >();

   if (!phtmlform)
   {

      auto pform = get_typed_view < ::user::form_view >();

      if (!pform)
      {

         return false;

      }

      pform->create_child_form <html_view>();

      phtmlform = pform->m_pform;

      phtmlform->set_form_callback(pform);

   }

   if (!get_html_data())
   {

      create_html_data();

   }

   get_html_data()->m_pcoredata->m_pform = phtmlform;

   if (::is_null(get_html_data()->m_pcoredata->m_pform))
   {

      return false;

   }

   if (::is_null(phtmlform->get_form_callback()))
   {

      auto pcallback = varFile["form_callback"].cast < ::user::form_callback >();

      if (pcallback)
      {

         phtmlform->set_form_callback(pcallback);

      }

   }



   if(!get_html_data()->open_document(varFile))
   {

      return false;

   }

   set_path_name(get_html_data()->m_pcoredata->m_strPathName);

   auto psubject = fork_subject(id_document_complete);

   psubject->payload(id_url) = varFile;

   update_all_views(psubject);

   //data_set({ "LastOpenedFile", true }, get_file_path());

   //Application.data_set({"LastOpenedFile", true}, get_file_path());

   return true;

}


void html_document::soft_reload()
{

   auto psync = get_html_data()->mutex();

   sync_lock lock(psync);

   string str = get_html_data()->m_pcoredata->m_strSource;

   auto pform = get_html_data()->m_pcoredata->m_pform;

   property_set_replace(str);

   TRACE("%s", str.c_str());

   get_html_data()->load(str);

   pform->set_need_layout();

   pform->set_need_redraw();

   pform->post_redraw();

//   auto pupdate = new_update();
//
//   psubject->id() = id_document_complete;
//
//   psubject->payload(id_url) = get_file_path();
//
//   update_all_views(pupdate);

}


::form_data * html_document::get_form_data()
{

   return get_html_data();

}


::html_data * html_document::get_html_data()
{

   return m_phtmldata;

   //auto pdata = m_datamap.get < ::html_data >();

   //if (pdata.is_set())
   //{

   //   return pdata;

   //}


}


void html_document::on_command_probe(::user::command * pcommand)
{

   if(pcommand->m_id == "viewindefaultbrowser")
   {

      pcommand->enable();

      pcommand->m_bRet = true;

      return;

   }

}


void html_document::on_command(::user::command * pcommand)
{

   if(pcommand->m_id == "viewindefaultbrowser")
   {

      property_set propertyset;

      Application.dialog_box("html_reader\\going_to_open_in_default_browser.xml", propertyset);

#ifndef _UWP

      ::apex::shell_launcher launcher(nullptr, "open", get_file_path(), nullptr, get_file_path().folder(), e_display_normal);

      launcher.execute();

#endif

      pcommand->m_bRet = true;

      return;

   }

}


bool html_document::open_document(const ::payload & varFile)
{

   return on_open_document(varFile) != false;

}


bool html_document::load_html(const string & str)
{

   get_html_data()->load(str);

   return true;

}


__pointer(::user::interaction) html_document::get_frame()
{

   return get_html_data()->get_frame();

}




void html_document::form_document_set_view(::user::form * pview)
{

   get_html_data()->m_pcoredata->m_pform = dynamic_cast < ::html_form *> (pview);

}


void html_document::form_document_set_callback(form_callback * pcallback)
{

   get_html_data()->m_pcoredata->m_pform->set_form_callback(pcallback);

}








CLASS_DECL_CORE ::type __form_document_type()
{

   return __type(::html_document);

}
