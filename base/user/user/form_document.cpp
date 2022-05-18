#include "framework.h"
//#include "base/user/user/_user.h"


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

   auto pformview = get_type_impact < ::user::form_view >();

   if(!pformview)
   {

      return false;

   }

   auto pformcallback = pformview->get_form_callback();

   if (m_pcreate && ::is_null(pformcallback))
   {

      auto pcallback = m_pcreate->m_payloadArgs["form_callback"].cast < ::user::form_callback >();

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



