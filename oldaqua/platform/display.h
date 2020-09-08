#pragma once


#ifdef __cplusplus


using edisplay = cflag < e_display >;
using eactivation = cflag < e_activation >;
using eappearance = cflag < e_appearance >;


#endif


inline bool is_visible(e_display edisplay) { return edisplay > display_none || edisplay == display_undefined; }
inline bool is_screen_visible(e_display edisplay) { return is_visible(edisplay) && edisplay != display_iconic; }
CLASS_DECL_AQUA e_display equivalence_sink(e_display edisplay);
inline bool is_equivalent(e_display edisplay1, e_display edisplay2) { return equivalence_sink(edisplay1) == equivalence_sink(edisplay2); }


inline bool is_docking_appearance(e_display edisplay) { return edisplay > display_none && edisplay & ::display_docking_mask; }
inline bool is_full_screen(e_display edisplay) { return edisplay == ::display_full_screen; }
inline bool is_zoomed(e_display edisplay) { return edisplay == ::display_zoomed; }
inline bool is_iconic(e_display edisplay) { return edisplay == ::display_iconic; }
inline bool window_is_minimal(e_display edisplay) { return edisplay == ::display_minimal; }


CLASS_DECL_AQUA int windows_show_window(e_display edisplay, e_activation eactivation);
CLASS_DECL_AQUA e_display windows_show_window_to_edisplay(int iShowWindow, e_activation & eactivation);


CLASS_DECL_AQUA string __str(e_display edisplay);
inline string __str(const ::edisplay & edisplay);



