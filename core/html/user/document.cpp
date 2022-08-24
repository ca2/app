#include "framework.h"
#include "_user.h"
//#include "aura/update.h"
#include "acme/id.h"


html_document::html_document()
{

}


bool html_document::on_new_document()
{

   auto phtmlform = get_type_impact < ::html_form >();

   auto phtmldata = phtmlform->get_html_data();

   if (::is_set(phtmlform) && ::is_set(phtmldata))
   {

      if (phtmlform->m_pathDefaultDocument.has_char())
      {

         return phtmldata->open_document(phtmlform->m_pathDefaultDocument);

      }

   }

   if (!::user::document::on_new_document())
   {

      return false;

   }

   update_all_impacts(nullptr, NEW_DOCUMENT_UPDATE);

   return true;

}


html_document::~html_document()
{

}


void html_document::assert_ok() const
{

   ::user::document::assert_ok();

}


void html_document::dump(dump_context & dumpcontext) const
{

   ::user::document::dump(dumpcontext);

}



//void html_document::create_html_data()
//{
//
//   auto estatus = __compose_new(m_phtmldata);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   auto pdata = get_html_data();
//
//   pdata->m_pdocument = this;
//
//   pdata->m_pcoredata = __new(::html::core_data);
//
//   pdata->m_pcoredata->initialize_html_data(pdata);
//
//   pdata->m_pimplHtml = pdata->m_pcoredata;
//
//   pdata->::form_data::m_pimpl = pdata->m_pimplHtml;
//
//   set_data("html", pdata);
//
//   pdata->m_pcoredata->m_puserinteraction = get_type_impact < ::user::form_impact >();
//
//   pdata->m_pcoredata->m_pcallback = this;
//
//   return ::success;
//
//}


void html_document::data_on_after_change(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

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
//   auto phtmlform = get_type_impact < ::html_form >();
//
//   if (!phtmlform)
//   {
//
//      auto pform = get_type_impact < ::user::form_impact >();
//
//      if (!pform)
//      {
//
//         return false;
//
//      }
//
//      pform->create_child_form <html_impact>();
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
//   return open_document(pcreate->m_payloadFile);
//
//}


bool html_document::on_open_document(const ::payload & payloadFile)
{

   auto phtmlform = get_type_impact < ::html_form >();

   if (!phtmlform)
   {

      auto pform = get_type_impact < ::user::form_impact >();

      if (!pform)
      {

         return false;

      }

      pform->create_child_form <html_impact>();

      phtmlform = pform->m_pform;

      phtmlform->set_form_callback(pform);

   }

   auto phtmldata = get_html_data();

   phtmldata->m_pcoredata->m_pform = phtmlform;

   if (::is_null(phtmldata->m_pcoredata->m_pform))
   {

      return false;

   }

   if (::is_null(phtmlform->get_form_callback()))
   {

      auto pcallback = payloadFile["form_callback"].cast < ::user::form_callback >();

      if (pcallback)
      {

         phtmlform->set_form_callback(pcallback);

      }

   }

   if(!phtmldata->open_document(payloadFile))
   {

      return false;

   }

   set_path_name(phtmldata->m_pcoredata->m_strPathName);

   auto phtmldocument = this;

   auto ptopic = create_topic(id_document_complete);

   ptopic->payload(id_url) = payloadFile;

   phtmldocument->update_all_impacts(ptopic);

   //data_set({ "LastOpenedFile", true }, get_file_path());

   //papp->data_set({"LastOpenedFile", true}, get_file_path());

   return true;

}


void html_document::soft_reload()
{

   auto psync = get_html_data()->mutex();

   synchronous_lock lock(psync);

   string str = get_html_data()->m_pcoredata->m_strSource;

   auto pform = get_html_data()->m_pcoredata->m_pform;

   property_set_replace(str);

   FORMATTED_TRACE("%s", str.c_str());

   get_html_data()->load(str);

   pform->set_need_layout();

   pform->set_need_redraw();

   pform->post_redraw();

//   auto pupdate = new_update();
//
//   ptopic->m_atom = id_document_complete;
//
//   ptopic->payload(id_url) = get_file_path();
//
//   update_all_impacts(pupdate);

}


::form_data * html_document::get_form_data()
{

   return get_html_data();

}


::html_data * html_document::get_html_data()
{

   auto phtmlform = get_type_impact < ::html_form >();

   if (::is_null(phtmlform))
   {

      return nullptr;

   }

   auto phtmldata = phtmlform->get_html_data();

   if (::is_null(phtmldata))
   {

      return nullptr;

   }

   return phtmldata;

   //auto pdata = m_datamap.get < ::html_data >();

   //if (pdata.is_set())
   //{

   //   return pdata;

   //}


}


//
//::html_data * html_document::get_html_data()
//{
//
//   return m_phtmldata;
//
//   //auto pdata = m_datamap.get < ::html_data >();
//
//   //if (pdata.is_set())
//   //{
//
//   //   return pdata;
//
//   //}
//
//
//}


void html_document::on_command_probe(::message::command * pcommand)
{

   if(pcommand->m_atom == "viewindefaultbrowser")
   {

      pcommand->enable();

      pcommand->m_bRet = true;

      return;

   }

}


void html_document::on_command(::message::command * pcommand)
{

   auto papp = get_app();

   if(pcommand->m_atom == "viewindefaultbrowser")
   {

      property_set propertyset;

      papp->dialog_box("html_reader\\going_to_open_in_default_browser.xml", propertyset);

#ifndef _UWP

      auto plauncher = __new(::apex::shell_launcher);
      
      plauncher->setup(nullptr, "open", get_file_path(), nullptr, get_file_path().folder(), e_display_restored);

      plauncher->launch();

#endif

      pcommand->m_bRet = true;

      return;

   }

}


bool html_document::open_document(const ::payload & payloadFile)
{

   return on_open_document(payloadFile) != false;

}


bool html_document::load_html(const ::string & str)
{

   get_html_data()->load(str);

   return true;

}


__pointer(::user::interaction) html_document::get_frame()
{

   return get_html_data()->get_frame();

}




void html_document::form_document_set_impact(::user::form * pimpact)
{

   get_html_data()->m_pcoredata->m_pform = dynamic_cast < ::html_form *> (pimpact);

}


void html_document::form_document_set_callback(form_callback * pcallback)
{

   get_html_data()->m_pcoredata->m_pform->set_form_callback(pcallback);

}








CLASS_DECL_CORE ::type __form_document_type()
{

   return __type(::html_document);

}
