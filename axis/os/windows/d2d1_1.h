#pragma once

#undef new

#include <D2d1_1.h>

#define new AURA_NEW

inline void copy(D2D1_RECT_F * prectTarget, const RECT * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(D2D1_RECT_U * prectTarget, const RECT * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(D2D1_RECT_L * prectTarget, const RECT * prectSource) { ::copy_rect(prectTarget, prectSource); }


inline void copy(D2D1_RECT_F * prectTarget, const RECTD * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(D2D1_RECT_U * prectTarget, const RECTD * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(D2D1_RECT_L * prectTarget, const RECTD * prectSource) { ::copy_rect(prectTarget, prectSource); }



inline void copy(RECT * prectTarget, const D2D1_RECT_F * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(RECT * prectTarget, const D2D1_RECT_U * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(RECT * prectTarget, const D2D1_RECT_L * prectSource) { ::copy_rect(prectTarget, prectSource); }


inline void copy(RECTD * prectTarget, const D2D1_RECT_F * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(RECTD * prectTarget, const D2D1_RECT_U * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(RECTD * prectTarget, const D2D1_RECT_L * prectSource) { ::copy_rect(prectTarget, prectSource); }



