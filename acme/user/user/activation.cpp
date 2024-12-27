// From activation.h by camilo on 2024-12-27 05:57 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "activation.h"
#include "activation_token.h"


namespace user
{


   activation::activation() :
      m_eactivation(::user::e_activation_default)
   {


   }


   activation::activation(const ::user::e_activation & euseractivation) :
      m_eactivation(euseractivation)
   {

      //if (m_eactivation & ::user::e_activation_set_foreground)
      //{

        // if (!m_pactivationtoken)
         //{

           // throw ::exception(error_wrong_state);

         //}

      //}

   }


   activation::activation(const ::user::e_activation & useractivation, ::user::activation_token * pactivationtoken) :
      m_eactivation(useractivation),
      m_pactivationtoken(pactivationtoken)
   {

      //if (m_eactivation & ::user::e_activation_set_foreground)
      //{

        // if (!m_pactivationtoken)
         //{

           // throw ::exception(error_wrong_state);

         //}

      //}

   }

   activation::activation(const ::user::activation & useractivation) :
      m_eactivation(useractivation.m_eactivation),
      m_pactivationtoken(useractivation.m_pactivationtoken)
   {


   }


   ::std::strong_ordering activation::operator <=> (const ::user::activation & useractivation) const
   {

      return m_eactivation <=> useractivation.m_eactivation;

   }


   ::user::activation & activation::operator |= (const ::user::activation & useractivation)
   {

      if (this != &useractivation)
      {

         m_eactivation |= useractivation.m_eactivation;

         if (useractivation.m_pactivationtoken)
         {

            m_pactivationtoken = useractivation.m_pactivationtoken;

         }

      }

      return *this;

   }


   ::user::activation & activation::operator = (const ::user::activation & useractivation)
   {

      if (this != &useractivation)
      {

         m_eactivation = useractivation.m_eactivation;
         m_pactivationtoken = useractivation.m_pactivationtoken;

      }

      return *this;

   }



   bool activation::operator == (const ::user::activation & useractivation) const
   {

      if (m_eactivation & ::user::e_activation_set_foreground)
      {

         if (useractivation.m_eactivation & ::user::e_activation_set_foreground)
         {

            return m_pactivationtoken->matches(useractivation.m_pactivationtoken);

         }

      }

      return m_eactivation == useractivation.m_eactivation;

   }


   bool activation::is_change_request() const
   {

      return m_eactivation != ::user::e_activation_default;

   }


   bool activation::operator & (const ::user::e_activation & useractivation) const
   {

      return m_eactivation & useractivation;

   }


   void activation::clear()
   {

      m_eactivation = ::user::e_activation_default;
      m_pactivationtoken = nullptr;

   }


} // namespace user



