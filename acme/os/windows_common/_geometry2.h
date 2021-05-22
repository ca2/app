#pragma once


#ifdef WINDOWS
rectangle_type(const D2D1_RECT_F & t) noexcept { ::copy(this, &t); }
//rectangle_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
//rectangle_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
//rectangle_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
#endif


#ifdef WINDOWS

inline void copy(RECTANGLE_F32 * prectDst, const D2D1_RECT_F * prectSrc) { ::copy_rect(prectDst, prectSrc); }

#endif
