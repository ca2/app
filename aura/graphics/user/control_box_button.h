#pragma once


namespace user
{


   CLASS_DECL_AURA void draw_close_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::item * pitem, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_maximize_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::item* pitem, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_minimize_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::item * pitem, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_switch_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::item* pitem, const ::user::e_state & estate);


} // namespace user



