#pragma once


#ifdef __cplusplus


using edisplay = cflag < enum_display >;
using useractivation = cflag < enum_activation >;
using eappearance = cflag < enum_appearance >;


#endif


inline bool is_visible(const ::e_display & edisplay) { return edisplay > e_display_none || edisplay == e_display_undefined; }
inline bool is_screen_visible(const ::e_display & edisplay) { return is_visible(edisplay) && edisplay != e_display_iconic; }
CLASS_DECL_AURA enum_display equivalence_sink(const ::e_display & edisplay);
inline bool is_equivalent(const  ::e_display & edisplay1, const  ::e_display & edisplay2) { return equivalence_sink(edisplay1) == equivalence_sink(edisplay2); }


inline bool is_docking_appearance(const ::e_display & edisplay) { return edisplay > e_display_none && edisplay & ::e_display_docking_mask; }
inline bool is_full_screen(const ::e_display & edisplay) { return edisplay == ::e_display_full_screen; }
inline bool is_zoomed(const ::e_display & edisplay) { return edisplay == ::e_display_zoomed; }
inline bool is_iconic(const ::e_display & edisplay) { return edisplay == ::e_display_iconic; }
inline bool window_is_minimal(const ::e_display & edisplay) { return edisplay == ::e_display_minimal; }


CLASS_DECL_AURA ::i32 windows_show_window(const ::e_display & edisplay, enum_activation useractivation);
CLASS_DECL_AURA enum_display windows_show_window_to_edisplay(::i32 iShowWindow, enum_activation & useractivation);


CLASS_DECL_AURA string as_string(const ::e_display & edisplay);
inline string as_string(const ::e_display & edisplay);



