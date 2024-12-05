// Created by camilo on 2024-12-04 16:29 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/user.h"
#include "acme/prototype/prototype/enumeration.h"


namespace user
{


   DECLARE_ENUMERATION(e_activation, enum_activation);


   class CLASS_DECL_ACME activation
   {
   public:


      ::user::e_activation       m_eactivation;
      ::task *                   m_ptaskForeground;

      activation() :m_eactivation(::user::e_activation_default),
         m_ptaskForeground{nullptr} {
      }

      activation(const ::user::e_activation & useractivation) :
         m_eactivation(useractivation),
         m_ptaskForeground{nullptr}
      {
         if (m_eactivation == ::user::e_activation_set_foreground)
         {
            if (::is_null(m_ptaskForeground))
            {
               m_ptaskForeground = ::get_task();
            }
         }
      }

      activation(const ::user::e_activation & useractivation, ::task * ptaskForeground) :
         m_eactivation(useractivation),
         m_ptaskForeground(ptaskForeground)
      {
         if (m_eactivation == ::user::e_activation_set_foreground)
         {
            if (::is_null(m_ptaskForeground))
            {
               m_ptaskForeground = ::get_task();
            }
         }
      }


      activation(const ::user::activation & useractivation) :
         m_eactivation(useractivation.m_eactivation),
         m_ptaskForeground(useractivation.m_ptaskForeground)
      {


      }

      bool operator == (const ::user::activation & useractivation) const
      {
         if (m_eactivation == ::user::e_activation_set_foreground)
         {

            if (useractivation.m_eactivation == ::user::e_activation_set_foreground)
            {

               return m_ptaskForeground == useractivation.m_ptaskForeground;

            }

         }

         return m_eactivation == useractivation.m_eactivation;

      }


      ::std::strong_ordering operator <=> (const ::user::activation & useractivation) const
      {

         if (m_eactivation == ::user::e_activation_set_foreground)
         {

            if (useractivation.m_eactivation == ::user::e_activation_set_foreground)
            {

               return m_ptaskForeground <=> useractivation.m_ptaskForeground;

            }

         }

         return m_eactivation <=> useractivation.m_eactivation;

      }

      ::user::activation & operator = (const ::user::activation & useractivation)
      {
         if (this != &useractivation)
         {
            m_eactivation = useractivation.m_eactivation;
            m_ptaskForeground = useractivation.m_ptaskForeground;
         }
         return *this;

      }
      
      ::user::activation & operator |= (const ::user::activation & useractivation)
      {
         if (this != &useractivation)
         {
            m_eactivation |= useractivation.m_eactivation;
            m_ptaskForeground = useractivation.m_ptaskForeground;
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
         m_ptaskForeground = nullptr;

      }


   };


} // namespace user

