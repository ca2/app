// Created by camilo on 2024-09-13 00:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX button :
      virtual public ::innate_ui::window
   {
   protected:
      ::procedure          m_callbackOnClick;
   public:





      button();
      ~button() override;


      virtual void set_callback_on_click(const ::procedure & callbackOnClick);
   virtual void call_on_click();
   };



} // namespace innate_ui



