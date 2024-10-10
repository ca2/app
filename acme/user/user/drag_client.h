// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSorensen
#pragma once


#include "container.h"
#include "acme/constant/element.h"
////#include "acme/prototype/prototype/object.h"


namespace user
{


   class CLASS_DECL_ACME drag_client :
      virtual public ::user::acme_container
   {
   public:


      map < ::item_t, ::pointer<::user::drag >>       m_mapDrag;
      ::pointer<::user::drag>                         m_pdragCurrent;


      drag_client();
      ~drag_client() override;


      void destroy() override;


      virtual void enable_drag(::item * pitem, ::user::e_zorder ezorder);
      virtual ::user::drag * drag(::item * pitem) const;
      virtual bool has_drag(::item * pitem) const;


      virtual bool drag_on_button_down(::item * pitem);
      virtual bool drag_on_button_down(::item * pitem, ::user::mouse * pmouse);
      virtual bool drag_on_mouse_move(::user::mouse * pmouse);
      virtual bool drag_on_mouse_hover(::item * pitem);
      virtual bool drag_on_button_up(::user::mouse * pmouse);


      virtual void drag_set_capture() = 0;
      virtual bool on_drag_start(::point_i32 & point, ::item * pitem) = 0;
      virtual ::point_i32 drag_mouse_cursor_position(::item * pitem, const ::point_i32 & point) = 0;
      virtual bool drag_shift(::item * pitem, ::user::mouse * pmouse) = 0;
      virtual bool drag_hover(::item * pitem) = 0;
      virtual void drag_release_capture() = 0;
      virtual void drag_set_cursor(::item * pitem) = 0;

      virtual ::point_i32 drag_point(::item * pitem, ::user::mouse * pmouse);


      //virtual ::user::item & user_item(const ::item * pitem) = 0;


   };


} // namespace user



