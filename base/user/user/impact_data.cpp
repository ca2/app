#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   impact_data::impact_data()
   {

      impact_data_common_construct();

   }


   impact_data::impact_data(const ::atom& atom) :
      ::PARTICLE(atom)
   {

      impact_data_common_construct();

   }


   void impact_data::impact_data_common_construct()
   {

      m_iId = m_atom.is_integer() ? m_atom.i64() : -1;
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



