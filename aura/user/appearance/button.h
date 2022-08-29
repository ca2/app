// Created by camilo on 2022-03-19 04:51 <3ThomasBorregaardSørensen!!
#pragma once


#include "appearance.h"


namespace appearance
{


   class CLASS_DECL_AURA button :
      virtual public ::appearance::appearance
   {
   public:


      __pointer(::user::button)      m_pbutton;


      button();
      ~button() override;





   };


} // namespace appearance



