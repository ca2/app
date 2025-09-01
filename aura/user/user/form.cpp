#include "framework.h"
#include "form.h"
#include "form_callback.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"
#include "acme/platform/system.h"


namespace user
{


   form::form()
   {

      m_econtroltype = e_control_type_form;

      m_pform = this;

      //m_bEatsDoubleClick = false;

   }


   form::~form()
   {


   }


   // ::aura::application *form::get_app()
   // {
   //
   //    return ::is_set(m_papplication) ? m_papplication->m_papplication : nullptr;
   //
   //
   // }
   //
   //
   // ::aura::session *form::get_session()
   // {
   //
   //    return ::is_set(m_papplication) ? m_papplication->m_psession : nullptr;
   //
   //
   // }
   //
   //
   // //::aura::system *formacmesystem()
   // //{
   //
   // //   return ::is_set(system()) ? system() : nullptr;
   //
   //
   // //}
   //
   //
   // ::user::user *form::user()
   // {
   //
   //
   //    return get_session() ? get_session()->user() : nullptr;
   //
   //
   // }


   //enum_control_type form::get_control_type() const
   //{

   //   return e_control_type_form;

   //}


   //bool form::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   return false;

   //}


   //::pointer<control_descriptor>form::new_form_control()
   //{

   //   return nullptr;

   //}


   bool form::open_document(const ::payload &payloadFile)
   {

      throw ::interface_only();

      return false;

   }


   bool form::open_html(const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

      return false;

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


   void form::initialize(::particle *pparticle)
   {

      //auto estatus =

      ::user::interaction::initialize(pparticle);

      /*if (!estatus)
      {

         return estatus;

      }

      return estatus;*/

   }


   void form::install_message_routing(::channel *pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(::user::e_message_create, pchannel, this, &form::on_message_create);

   }


   void form::on_message_create(::message::message *pmessage)
   {

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      add_handler(this);

   }


   void form::set_form_callback(::user::form_callback *pcallback)
   {

      //auto estatus = 

      m_pcallback = pcallback;

      /*     if (!estatus)
           {

              return estatus;

           }

           return estatus;*/

   }


   void form::set_parent_form(::user::form *pform)
   {

      //auto estatus =
      m_pformParent = pform;

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   ::user::form_callback *form::get_form_callback()
   {

      return m_pcallback.get();

   }


   //::handler* form::get_user_callback()
   //{

   //   return get_form_callback();

   //}


   ::user::form *form::get_parent_form()
   {

      return m_pformParent.get();

   }


   bool form::_001AddControl(::user::interaction *pinteraction)
   {

      return false;

   }


//   ::aura::application * form::get_app() const
//   {
//
//      return m_papplication ? m_papplication : nullptr;
//
//   }
//
//
//   ::aura::session * form::get_session() const
//   {
//
//      return m_papplication ? m_papplication : nullptr;
//
//   }


} // namespace user







