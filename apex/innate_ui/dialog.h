// Created by camilo on 2024-09-13 00:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX dialog :
      virtual public ::innate_ui::window
   {
   public:

      
      dialog();
      ~dialog() override;

      
      void create() override;

      //virtual void fit();

   };


} // namespace innate_ui



