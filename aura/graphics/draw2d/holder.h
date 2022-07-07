// Created by camilo on 2022-06-23 20:13 <3ThomasBorregaardSørensen!!
#pragma once


#include "holdee.h"


namespace draw2d
{


   class CLASS_DECL_AURA holder :
      virtual public element
   {
   public:


      holdee      m_holdee;


      holder();
      ~holder() override;


   };


} // namespace draw2d



