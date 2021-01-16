// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


namespace user
{


   class CLASS_DECL_BASE tab_pane_array :
      public __pointer_array(tab_pane)
   {
   public:


      tab_pane_array();
      virtual ~tab_pane_array();


      virtual tab_pane * get_by_id(id id);
      ::count get_visible_count();

   };


} // namespace user



