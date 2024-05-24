// Now based on ::item_container and also named item_container from own user::container by camilo on 2023-07-21 12:07 <3ThomasBorregaardSorensen!!
// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "item.h"
#include "acid/handler/item_container_map.h"


namespace user
{


   class CLASS_DECL_ACID ace_container :
      virtual public ::item_container_map
   {
   public:


      ::user::item_map                             m_useritemmap;
      ::pointer < ace_tool >                      m_pacetool;
      ::pointer < ace_content >                   m_pacecontentMain;
      ::item_pointer                               m_pitemHover;
      ::item_pointer                               m_pitemPressed;


      ace_container();
      ~ace_container() override;


      void destroy() override;


      bool _is_set() const override;

      
      inline ace_tool & tool() { if (!m_pacetool) create_tool(); return *m_pacetool; }
      inline ace_content & main_content() { if (!m_pacecontentMain) create_main_content(); return *m_pacecontentMain; }


      virtual void create_tool();
      virtual void create_main_content();



      virtual bool is_item_pressed(const ::item_t & item) const;
      virtual bool is_item_hover(const ::item_t & item) const;

      virtual ::item_pointer pressed_item();
      virtual ::item_pointer hover_item();
      virtual ::item_pointer selected_item();

      //virtual ::collection::count item_count() const;

      //virtual void clear_items();

      //virtual ::item * item_at(::collection::index iIndex);

      //virtual void default_set_item_at(::collection::index iIndex, ::item * pitem);

      //virtual void default_add_item(::item * pitem);

      //virtual ::collection::index add_item(::item * pitem);

      //virtual ::item_pointer add_item(const ::item_t & item);

      //virtual ::user::item * user_item_at(::collection::index iIndex);

      //virtual ::collection::index item_index(const ::item * pitem);

      //virtual ::collection::index content_item_index(const ::item * pitem);

      virtual ::user::item * user_item(const ::item * pitem);

      //virtual ::user::item * user_item(const ::atom & atom);

      //virtual ::item_pointer item(const ::atom & atom);

      //virtual ::item_pointer item(const item_t & item);

      //virtual ::item_pointer defer_item(const item_t & item);

      //virtual ::collection::index item_index() const;

      //static ::collection::index item_index(::item_array * pitema, const ::atom & atom);

      //virtual ::collection::index item_index(const ::atom & atom) const;

      //virtual bool is_item_pressed(const ::atom & atom) const;

      //virtual bool is_item_hover(const ::atom & atom) const;

      //virtual bool is_item_pressed_by_index(::collection::index iIndex) const;

      //virtual bool is_item_hover_by_index(::collection::index iIndex) const;


      virtual bool is_item_selected(::item * pitem);
      //virtual ::item_pointer selected_item();

      virtual bool is_item_hover(::item * pitem);
      //virtual ::item_pointer hover_item();


      //virtual void on_item_selected(::item * pitem);
      virtual void on_item_hover(::item * pitem);

      //virtual ::item_pointer get_child_as_item(::collection::index iIndex);
      //virtual ::collection::count get_child_as_item_count();


   };


} // namespace user

 

