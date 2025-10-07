// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


#include "tab_pane.h"


namespace user
{


   class CLASS_DECL_BERG tab_pane_array :
      public ::pointer_array < tab_pane >
   {
   public:


      tab_pane_array();
      ~tab_pane_array() override;


      virtual tab_pane * get_by_id(atom atom);
      ::collection::count get_visible_count();

   };


} // namespace user



