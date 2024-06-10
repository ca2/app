#pragma once


using atom_array = ::comparable_array < atom >;


namespace data
{


   class tree_item;
   class tree_item_ptr_array;


   class tree;


   class property;


   class property_container;
   class property_listener;

   class property;

   class check;
   class text;


} // namespace data


namespace data
{

   using property_will_change = ::function < bool(property_container *, const ::atom_array &, const ::payload &, const ::action_context &) >;

   using property_changed = ::function < void(property_container *, const ::atom_array &, const ::payload &, const ::action_context &) >;


} // namespace data



namespace xml
{


   class node;


} // namespace xml


//#include "data.h"
//#include "container.h"
//#include "listener.h"
//#include "item.h"
//
//
//#include "node.h"




