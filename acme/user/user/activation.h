// Created by camilo on 2024-12-04 16:29 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/user.h"
#include "acme/prototype/prototype/enumeration.h"


namespace user
{


   DECLARE_ENUMERATION(e_activation, enum_activation);


   class activation_token :
      virtual public ::particle
   {
   public:


      virtual bool matches(const activation_token * pactivationtoken) const { return false; }


   };


   class CLASS_DECL_ACME activation
   {
   public:


      ::user::e_activation                      m_eactivation;
      ::pointer < ::user::activation_token >    m_pactivationtoken;
      // ::task *                   m_ptaskForeground;
      // ::huge_integer             m_iTime;

      activation() :
         m_eactivation(::user::e_activation_default),
         m_pactivationtoken{}
      {
      }

      // activation(const ::user::e_activation & euseractivation) :
      //    m_eactivation(euseractivation),
      //    m_pactivationtoken{nullptr}
      // {
      //    if (m_eactivation == ::user::e_activation_set_foreground)
      //    {
      //       if (::is_null(m_ptaskForeground))
      //       {
      //          m_ptaskForeground = ::get_task();
      //       }
      //    }
      // }

      activation(const ::user::e_activation & useractivation, ::user::activation_token * pactivationtoken) :
         m_eactivation(useractivation),
         m_pactivationtoken(pactivationtoken)
      {

         if (m_eactivation == ::user::e_activation_set_foreground)
         {

            if (!m_pactivationtoken)
            {

               throw ::exception(error_wrong_state);

            }

         }
      }


      activation(const ::user::activation & useractivation) :
         m_eactivation(useractivation.m_eactivation),
         m_pactivationtoken(useractivation.m_pactivationtoken)
      {


      }

      bool operator == (const ::user::activation & useractivation) const
      {
         if (m_eactivation == ::user::e_activation_set_foreground)
         {

            if (useractivation.m_eactivation == ::user::e_activation_set_foreground)
            {

               return m_pactivationtoken->matches(useractivation.m_pactivationtoken);

            }

         }

         return m_eactivation == useractivation.m_eactivation;

      }


      // ::std::strong_ordering operator <=> (const ::user::activation & useractivation) const
      // {
      //
      //    if (m_eactivation == ::user::e_activation_set_foreground)
      //    {
      //
      //       if (useractivation.m_eactivation == ::user::e_activation_set_foreground)
      //       {
      //
      //          if (m_ptaskForeground == useractivation.m_ptaskForeground)
      //          {
      //
      //             return m_iTime <=> useractivation.m_iTime;
      //
      //          }
      //          else
      //          {
      //
      //             return m_ptaskForeground <=> useractivation.m_ptaskForeground;
      //
      //          }
      //
      //       }
      //
      //    }
      //
      //    return m_eactivation <=> useractivation.m_eactivation;
      //
      // }

      ::user::activation & operator = (const ::user::activation & useractivation)
      {
         if (this != &useractivation)
         {
            m_eactivation = useractivation.m_eactivation;
            m_pactivationtoken = useractivation.m_pactivationtoken;
         }
         return *this;

      }
      
      ::user::activation & operator |= (const ::user::activation & useractivation)
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

      bool is_change_request() const
      {
         return m_eactivation != ::user::e_activation_default;
      }

      bool operator & (const ::user::e_activation & useractivation) const
      {

         return m_eactivation & useractivation;

      }


      void clear()
      {

         m_eactivation = ::user::e_activation_default;
         m_pactivationtoken = nullptr;

      }


   };


} // namespace user

