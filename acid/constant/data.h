// Created by camilo on 2022-10-06 12:51 <3ThomasBorregaardSorensen!!
#pragma once


namespace data
{


   enum enum_relative
   {
      e_relative_parent,
      e_relative_first_child,
      e_relative_last_child,
      e_relative_first_sibling,
      e_relative_previous_sibling,
      e_relative_next_sibling,
      e_relative_last_sibling,
      e_relative_replace,
      e_relative_macro_record
   };


   enum enum_tree_navigation
   {

      e_tree_navigation_expanded_forward,
      e_tree_navigation_proper_forward,

   };


   enum enum_tree_item_state
   {

      e_tree_item_state_expandable = 1,
      e_tree_item_state_expanded = 2,
      e_tree_item_state_selected = 4,

   };



} // namespace data




