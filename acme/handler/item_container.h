// From acme/user/user/container.h by camilo on 2023-07-21 12:05 <3ThomasBorregaardSorensen!!
// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/handler/item.h"


class CLASS_DECL_ACME item_container :
   virtual public ::item
{
public:


   ::item_pointer                               m_pitemCurrent;
   ::pointer < ::item_array >                   m_pitema;


   item_container();
   ~item_container() override;


   bool _is_set() const override;


   virtual ::collection::count item_count() const;

   virtual void clear_items();

   //virtual ::item * item_at(::collection::index iIndex);

   virtual void indexed_set_item_at(::collection::index iIndex, ::item * pitem);

   virtual void indexed_add_item(::item * pitem);

   virtual ::collection::index add_item(::item * pitem);

   virtual ::item_pointer add_item(enum_element eelement, ::collection::index iItem = -1);

   //virtual ::user::item * user_item_at(::collection::index iIndex);

   virtual ::collection::index item_index(const ::item * pitem);


   inline ::item * item_at(::collection::index iIndex)
   {
      if (!m_pitema) return nullptr;
      return m_pitema->element_at(iIndex);
   }
   
   
   inline const ::item * item_at(::collection::index iIndex) const
   {
      if (!m_pitema) return nullptr;
      return m_pitema->element_at(iIndex);
   }


   //virtual ::collection::index content_item_index(const ::item * pitem);

   //virtual ::user::item * user_item(const ::item * pitem);

   //virtual ::user::item * user_item(const ::atom & atom);

   virtual ::item_pointer item(const ::atom & atom);

   virtual const ::item * item(const ::atom & atom) const;

   virtual bool contains_item(const ::atom & atom) const;

   virtual ::item_pointer find_item(enum_element eelement, ::collection::index iItem = -1);

   virtual ::item_pointer defer_item(enum_element eelement, ::collection::index iItem = -1);

   virtual ::collection::index item_index() const;

   virtual ::collection::index item_index(const ::atom & atom) const;

   //virtual bool is_item_pressed_by_index(::collection::index iIndex) const;

   //virtual bool is_item_hover_by_index(::collection::index iIndex) const;


   virtual bool is_item_selected(::item * pitem);
   virtual ::item_pointer selected_item();

   virtual bool is_item_hover(::item * pitem);
   virtual ::item_pointer hover_item();


   virtual void on_item_selected(::item * pitem);
   virtual void on_item_hover(::item * pitem);

   virtual ::item_pointer get_child_as_item(::collection::index iIndex);
   virtual ::collection::count get_child_as_item_count();


};


