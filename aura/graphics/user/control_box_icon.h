#pragma once


namespace user
{


   CLASS_DECL_AURA void draw_close_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item & item, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_switch_icon(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::user::item & item, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_maximize_icon(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & item, const ::user::e_state & estate);
   CLASS_DECL_AURA void draw_minimize_icon(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & item, const ::user::e_state & estate);


} // namespace user



