#include "framework.h"
#include "impact_data.h"
#include "aura/user/user/system.h"
#include "aura/message/user.h"


namespace user
{


   impact_data::impact_data()
   {

      impact_data_common_construct();

   }


   impact_data::impact_data(const ::atom& atom) //:
      //::PARTICLE(atom)
   {

      m_atom = atom;

      impact_data_common_construct();

   }


   void impact_data::impact_data_common_construct()
   {

      m_iId = m_atom.is_integer() ? m_atom.as_i64() : -1;
      m_iExtendOnParent = 0;
      m_pimpactdata = nullptr;
      m_bOk = false;

   }


   impact_data::~impact_data()
   {

   }


   /*::user::interaction* get_place_holder() const;
   void set_place_holder(::user::place_holder* pdocument);

   ::user::interaction* get_user_interaction() const;


   ::user::interaction* impact_data::get_user_interaction() const
   {

      if (m_puserinteraction)
      {

         return m_puserinteraction;

      }

      try
      {

         if (m_puserinteraction && m_puserinteraction->m_uiptraChild.get_count() == 1)
         {

            return m_pholder->m_uiptraChild[0];

         }

      }
      catch (...)
      {

      }

      return nullptr;

   }


   void impact_data::set_user_interaction(::user::interaction* pdocument);
   {

      auto estatus = __refer(m_pdocument, pdocument);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::user::document* impact_data::get_document() const
   {

      return m_pcontroller.cast < ::user::document >();

   }


   void impact_data::set_document(::user::document* pdocument)
   {

      auto estatus = __refer(m_pdocument, pdocument);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }*/


} // namespace user


::user::impact_data * __impact_data(::user::system * pusersystem)
{

   return ::is_set(pusersystem) ? pusersystem->m_pimpactdata.cast < ::user::impact_data >() : nullptr;

}


CLASS_DECL_BASE::user::impact_data * __impact_data(::message::create * pmessagecreate)
{

   auto pimpactdata = ::is_set(pmessagecreate) ? pmessagecreate->get_impact_data() : nullptr;

   if (!pimpactdata)
   {

      return nullptr;

   }

   return dynamic_cast <::user::impact_data *>(pimpactdata);

}



