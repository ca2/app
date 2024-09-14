// Created by camilo on 2024-09-13 00:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX button :
      virtual public ::innate_ui::window
   {
   public:


      ::procedure          m_callbackOnClick;


      button();
      ~button() override;

   
   };



} // namespace innate_ui



