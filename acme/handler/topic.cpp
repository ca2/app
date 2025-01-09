// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Changed to -nano- topic on 2022-02-04 18:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "topic.h"
//#include "acme/user/user/check.h"
//#include "acme/user/user/text.h"
#include "acme/user/user/activation_token.h"
#include "acme/user/user/command_update_target.h"
#include "acme/user/user/interaction.h"


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

   return m_puserelement->user_interaction();

}


::acme::user::interaction * topic::acme_user_interaction()
{

   if (::is_null(m_puserelement))
   {

      return nullptr;

   }

   return m_puserelement.cast < ::acme::user::interaction >();

}


::user::activation_token * topic::user_activation_token()
{

   auto puseractivationtoken = m_actioncontext.user_activation_token();

   if (::is_null(puseractivationtoken))
   {

      return nullptr;

   }

   return puseractivationtoken;

}


::atom topic::user_interaction_id() const
{

   auto pacmeuserinteraction = ((topic*)this)->acme_user_interaction();

   if (::is_null(pacmeuserinteraction))
   {

      return ::atom::e_type_null;

   }

   return pacmeuserinteraction->m_atom;

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


bool topic::topic_step()
{

   return false;

}


