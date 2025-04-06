//
// Created by camilo on 2025-03-30 23:29 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace user
{

   enum enum_item_state
   {

      e_item_state_none,
      e_item_state_selected = 1,

   };

   DECLARE_ENUMERATION(e_item_state, enum_item_state);

   class CLASS_DECL_ACME item_base :
      virtual public ::particle
   {
   public:


      ::pointer < ::user::item >          m_puseritem;
      //::pointer < ::item >                m_pitem;
      unsigned long long                  m_ullUserData;
      e_item_state                        m_eitemstate;



      item_base();
      ~item_base() override;


      virtual ::item * _item() = 0;
      virtual void _set_item(::item * pitem) = 0;


      virtual string get_user_item_text();
      virtual ::collection::index get_user_item_image();
      virtual ::image::image_list * get_user_item_image_list();


   };


} // namespace user



