#pragma once


#ifdef __cplusplus


DECLARE_ENUMERATION(e_zorder, enum_zorder);
DECLARE_C_FLAG(e_display, enum_display);
DECLARE_C_FLAG(e_appearance, enum_appearance);


#endif


CLASS_DECL_ACME ::e_display equivalence_sink(const ::e_display & edisplay);

inline bool is_equivalent(const ::e_display & edisplay1, const ::e_display & edisplay2)
{
   return equivalence_sink(edisplay1) == equivalence_sink(edisplay2);
}


inline bool is_visible(const ::e_display & edisplay) { return edisplay.m_cflag > e_display_none || edisplay == e_display_undefined; }
inline bool is_screen_visible(const ::e_display & edisplay) { return is_visible(edisplay) && edisplay != e_display_iconic; }
CLASS_DECL_ACME ::e_display equivalence_sink(const ::e_display & edisplay);
inline bool is_equivalent_in_equivalence_sink(const ::e_display & edisplay1, const ::e_display & edisplay2) { return equivalence_sink(edisplay1) == equivalence_sink(edisplay2); }


CLASS_DECL_ACME bool is_docking(const ::e_display & edisplay);


CLASS_DECL_ACME ::e_display default_equivalence_sink(const ::e_display & edisplay);




inline bool is_docking_appearance(const ::e_display & edisplay) { return (bool) (edisplay & e_display_docking_mask); }
inline bool is_full_screen(const ::e_display & edisplay) { return edisplay == ::e_display_full_screen; }
inline bool is_zoomed(const ::e_display & edisplay) { return edisplay == ::e_display_zoomed; }
inline bool is_iconic(const ::e_display & edisplay) { return edisplay == ::e_display_iconic; }
inline bool window_is_minimal(const ::e_display & edisplay) { return edisplay == ::e_display_minimal; }







