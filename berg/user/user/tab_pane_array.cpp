// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "tab_pane.h"
#include "tab_pane_array.h"


namespace user
{

   
   tab_pane_array::tab_pane_array()
   {

   }


   tab_pane_array::~tab_pane_array()
   {

   }


   tab_pane * tab_pane_array::get_by_id(atom atom)
   {

      for (int i = 0; i < this->get_count(); i++)
      {
         if (this->element_at(i)->id() == atom)
         {
            return element_at(i);
         }
      }
      return nullptr;
   }

   ::collection::count tab_pane_array::get_visible_count()
   {

      ::collection::count count = 0;

      for (int i = 0; i < this->get_count(); i++)
      {
         if (this->element_at(i)->m_bTabPaneVisible)
         {
            count++;
         }
      }

      return count;
   }


} // namespace user



