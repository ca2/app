#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   form::form()
   {

      m_econtroltype = e_control_type_form;

      m_pform = this;

   }


   form::~form()
   {

   }


   //enum_control_type form::get_control_type() const
   //{

   //   return e_control_type_form;

   //}


   //bool form::create_interaction(::user::interaction * pinteractionParent, const ::id & id)
   //{

   //   return false;

   //}


   //__pointer(control_descriptor) form::new_form_control()
   //{

   //   return nullptr;

   //}


   void form::open_html(const ::string& str)
   {

      return ::error_interface_only;

   }


   void form::open_document(const ::payload& payloadFile)
   {

      return ::error_interface_only;

   }



   void form::soft_reload()
   {

   }


//   ::form_property_set * form::get_form_property_set()
//   {
//
//      if (::is_set(m_pformpropertyset))
//      {
//
//         return m_pformpropertyset;
//
//      }
//
//      return this;
//
//   }


   void form::initialize(::object * pobject)
   {

      auto estatus = ::user::interaction::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void form::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &form::on_message_create);

   }

   
   void form::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();
      
      add_handler(this);

   }



   void form::set_form_callback(::user::form_callback* pcallback)
   {

      auto estatus = __refer(m_pcallback, pcallback);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void form::set_parent_form(::user::form* pform)
   {

      auto estatus = __refer(m_pformParent, pform);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   ::user::form_callback* form::get_form_callback()
   {

      return m_pcallback.get();

   }


   //::handler* form::get_user_callback()
   //{

   //   return get_form_callback();

   //}


   ::user::form * form::get_parent_form()
   {

      return m_pformParent.get();

   }


   bool form::_001AddControl(::user::interaction * pinteraction)
   {

      return false;

   }


} // namespace user







