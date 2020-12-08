#pragma once


#ifdef __cplusplus


using edisplay = cflag < enum_display >;
using eactivation = cflag < enum_activation >;
using eappearance = cflag < enum_appearance >;


#endif


inline bool is_visible(enum_display edisplay) { return edisplay > e_display_none || edisplay == e_display_undefined; }
inline bool is_screen_visible(enum_display edisplay) { return is_visible(edisplay) && edisplay != e_display_iconic; }
CLASS_DECL_ACME enum_display equivalence_sink(enum_display edisplay);
inline bool is_equivalent(enum_display edisplay1, enum_display edisplay2) { return equivalence_sink(edisplay1) == equivalence_sink(edisplay2); }


inline bool is_docking_appearance(enum_display edisplay) { return edisplay > e_display_none && edisplay & ::e_display_docking_mask; }
inline bool is_full_screen(enum_display edisplay) { return edisplay == ::e_display_full_screen; }
inline bool is_zoomed(enum_display edisplay) { return edisplay == ::e_display_zoomed; }
inline bool is_iconic(enum_display edisplay) { return edisplay == ::e_display_iconic; }
inline bool window_is_minimal(enum_display edisplay) { return edisplay == ::e_display_minimal; }


CLASS_DECL_ACME int windows_show_window(enum_display edisplay, enum_activation eactivation);
CLASS_DECL_ACME enum_display windows_show_window_to_edisplay(int iShowWindow, enum_activation & eactivation);


CLASS_DECL_ACME string __str(enum_display edisplay);
inline string __str(const ::edisplay & edisplay);



