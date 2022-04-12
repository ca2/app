//
// from _.h in same folder by camilo on 11/04-April/2022. 10:50 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace x11
{


   enum enum_atom
   {

      e_atom_net_wm_state,
      e_atom_net_wm_state_above,
      e_atom_net_wm_state_first = e_atom_net_wm_state_above,
      e_atom_net_wm_state_below,
      e_atom_net_wm_state_hidden,
      e_atom_net_wm_state_maximized_horz,
      e_atom_net_wm_state_maximized_vert,
      e_atom_net_wm_state_fullscreen,
      e_atom_net_wm_state_skip_taskbar,
      e_atom_net_wm_state_last = e_atom_net_wm_state_skip_taskbar,
      e_atom_wm_name,
      e_atom_wm_state,
      e_atom_net_active_window,
      e_atom_net_client_list_stacking,
      e_atom_net_client_list,
      e_atom_net_wm_window_type,
      e_atom_net_wm_window_type_normal,
      e_atom_net_wm_window_type_splash,
      e_atom_net_wm_cm_s0,
      e_atom_count

   };


   const char * atom_name(enum_atom eatom);

   int atom_count();


} // namespace x11



