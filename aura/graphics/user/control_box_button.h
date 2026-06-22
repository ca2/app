#pragma once


namespace user
{


   CLASS_DECL_AURA void draw_close_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & item, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon);
   CLASS_DECL_AURA void draw_maximize_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction,  ::user::item & item, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon);
   CLASS_DECL_AURA void draw_minimize_button(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction, ::user::item & item, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon);
   CLASS_DECL_AURA void draw_switch_button(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction, ::user::item & item, const ::user::e_state & estate, ::pointer < ::draw2d::stock_icon > & pstockicon);


} // namespace user



