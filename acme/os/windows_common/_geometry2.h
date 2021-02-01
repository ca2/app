#pragma once


#ifdef WINDOWS
rect_type(const D2D1_RECT_F & t) noexcept { ::copy(this, &t); }
//rect_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
//rect_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
//rect_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
#endif


#ifdef WINDOWS

inline void copy(RECTANGLE_F32 * prectDst, const D2D1_RECT_F * prectSrc) { ::copy_rect(prectDst, prectSrc); }

#endif
