#include "framework.h"
#include "document.h"
#include "impact.h"
#include "acme/handler/request.h"


form_document::form_document()
{


}


form_document::~form_document()
{


}


::form_data* form_document::get_form_data()
{

   return nullptr;

}


bool form_document::on_open_document(const ::payload & payloadFile)
{

   auto pformview = get_typed_impact < ::user::form_impact >();

   if(!pformview)
   {

      return false;

   }

   auto pformcallback = pformview->get_form_callback();

   if (m_prequest && ::is_null(pformcallback))
   {

      auto pcallback = m_prequest->m_payloadArguments["form_callback"].cast < ::user::form_callback >();

      if (pcallback)
      {

         pformview->set_form_callback(pcallback);

      }

   }

   //pformview->open_document(payloadFile);

   if(!pformview->open_document(payloadFile))
   {

      return false;

   }

   return true;

}


void form_document::soft_reload()
{

}



