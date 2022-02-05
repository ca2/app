// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "base/user/user/_user.h"
#include "tab_pane.h"


namespace user
{

   
   tab_pane_composite_array::tab_pane_composite_array()
   {

   }


   tab_pane_composite_array::~tab_pane_composite_array()
   {

   }


   tab_pane * tab_pane_composite_array::get_by_id(atom atom)
   {

      for (i32 i = 0; i < this->get_count(); i++)
      {
         if (this->element_at(i)->m_id == atom)
         {
            return element_at(i);
         }
      }
      return nullptr;
   }

   ::count tab_pane_composite_array::get_visible_count()
   {

      ::count count = 0;

      for (i32 i = 0; i < this->get_count(); i++)
      {
         if (this->element_at(i)->m_bTabPaneVisible)
         {
            count++;
         }
      }

      return count;
   }


} // namespace user



