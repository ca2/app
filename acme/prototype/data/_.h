#pragma once


using atom_array = ::comparable_array < atom >;


using atom_array_base = ::comparable_array_base < atom >;


namespace data
{

   //class item;

   class tree_base;
   class tree_item_base;
   class tree_item_base_ptr_array;

   class property;


   class property_container;
   class property_listener;

   class property;

   class check;
   class text;


} // namespace data


namespace data
{

   struct property_change
   {

      property_container * m_ppropertycontainer;
      const ::atom_array_base & m_atoma;
      const ::payload & m_payload;
      const ::action_context & m_actioncontext;

   };

   using property_will_change = ::function < bool(property_change &) >;


   //struct property_changed_arguments
   //{

   //   property_container * m_ppropertycontainer;
   //   const ::atom_array & m_atoma;
   //   const ::payload & m_payload;
   //   const ::action_context & m_actioncontext;
   //};

   using property_changed = ::function < void(property_change &) >;


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




