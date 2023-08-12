// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/user/user/item.h"


namespace user
{


   class CLASS_DECL_ACME container :
      virtual public ::item
   {
   public:


      ::item_pointer                               m_pitemCurrent;
      ::item_pointer                               m_pitemHover;
      //::user<::item_pointer>                     m_puseritemHoverMouse;
      ::item_pointer                               m_pitemPressed;
      ::item_array                                 m_itema;
      //map < ITEM, ::index >                        m_itemmap;
      ::user::item_map                             m_useritemmap;



      container();
      ~container() override;


      virtual ::count item_count() const;

      virtual ::item * item_at(::index iIndex);

      virtual void default_set_item_at(::index iIndex, ::item * pitem);

      virtual void default_add_item(::item * pitem);

      virtual ::index add_item(::item * pitem);

      virtual ::user::item * user_item_at(::index iIndex);

      virtual ::index item_index(const ::item * pitem);

      virtual ::user::item * user_item(const ::item * pitem);

      virtual ::user::item * user_item(const ::atom & atom);

      virtual ::item_pointer item(const ::atom & atom);

      using ::item::item_index;

      virtual ::index item_index(const ::atom & atom) const;

      virtual bool is_item_pressed(const ::atom & atom) const;

      virtual bool is_item_hover(const ::atom & atom) const;

      virtual bool is_item_pressed_by_index(::index iIndex) const;

      virtual bool is_item_hover_by_index(::index iIndex) const;


      virtual bool is_item_selected(::item* pitem);
      virtual ::item_pointer selected_item();

      virtual bool is_item_hover(::item* pitem);
      virtual ::item_pointer hover_item();


      virtual void on_item_selected(::item* pitem);
      virtual void on_item_hover(::item* pitem);

      virtual ::item_pointer get_child_as_item(::index iIndex);
      virtual ::count get_child_as_item_count();


   };


} // namespace user



