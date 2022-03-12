// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Changed to -nano- topic on 2022-02-04 18:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/user/user/check.h"
#include "acme/user/user/text.h"
#include "acme/user/user/element.h"


//
//
//::extended_topic * topic::_extended_topic()
//{
//
//   return nullptr;
//
//}
//
//
//const ::extended_topic * topic::_extended_topic() const
//{
//
//   return nullptr;
//
//}
//
//

//
//
//void topic_extension::Nok()
//{
//
//   m_bOk = false;
//
//   m_bRet = true;
//
//}
//
//void topic_extension::Ret()
//{
//
//   m_bRet = true;
//
//}
//
//void topic_extension::Ok()
//{
//
//   m_bOk = true;
//
//   m_bRet = true;
//
//}
//
//
////::topic_extension * topic_extension::get_extended_topic()
////{
////
////   return this;



::user::interaction * topic::user_interaction()
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement->m_puserinteraction;

}




::atom topic::user_element_id() const
{

   if (::is_null(m_puserelement))
   {

      return ::atom::e_type_null;

   }

   return m_puserelement->m_atom;

}


::user::form * topic::get_form() const
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement->get_form();

}


::user::element * topic::get_form_user_element() const
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement->get_form_user_element();

}


bool topic::is_about(::user::element * pelement) const
{

   auto pform = get_form();

   if (::is_null(pform))
   {

      return false;

   }

   if (get_form_user_element() == pelement)
   {

      return true;

   }

   return false;

}