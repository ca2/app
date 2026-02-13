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


      ::user::e_activation                      m_eactivation;
      ::pointer < ::user::activation_token >    m_pactivationtoken;
      // ::task *                               m_ptaskForeground;
      // long long                         m_iTime;


      activation();
      activation(::user::enum_activation euseractivation);
      activation(const ::user::e_activation & euseractivation);
      activation(const ::user::e_activation & euseractivation, ::user::activation_token * pactivationtoken);


      activation(const ::user::activation & useractivation);

      bool operator == (const ::user::activation & useractivation) const;


      ::std::strong_ordering operator <=> (const ::user::activation & useractivation) const;


      ::user::activation & operator = (const ::user::activation & useractivation);

      ::user::activation & operator |= (const ::user::activation & useractivation);

      bool is_change_request() const;


      bool operator & (const ::user::e_activation & useractivation) const;
      

      void clear();


   };


} // namespace user

