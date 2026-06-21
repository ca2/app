// Created by camilo on 2026-06-21 12:33 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/user/user/_constant.h"


namespace user
{


   class CLASS_DECL_ACME shortcut_key
   {
   public:

      
      ::user::e_key_state        m_ekeystate;
      ::user::e_key              m_ekey;

      bool operator==(const shortcut_key& key) const
      {

         return m_ekeystate == key.m_ekeystate
            && m_ekey == key.m_ekey;


      }

   };


} // namespace user



