#pragma once



#ifdef WINDOWS_DESKTOP

#undef new

#define min MIN
#define max MAX

#include <gdiplus.h>

#define new ACME_NEW

#undef min
#undef max

using namespace Gdiplus;


inline auto left(const Gdiplus::Rect * prect) { return prect->X; }
inline auto top(const Gdiplus::Rect * prect) { return prect->Y; }
inline auto left(const Gdiplus::RectF * prect) { return prect->X; }
inline auto top(const Gdiplus::RectF * prect) { return prect->Y; }


inline auto width(const Gdiplus::Rect * prect) { return prect->Width; }
inline auto height(const Gdiplus::Rect * prect) { return prect->Height; }
inline auto width(const Gdiplus::RectF * prect) { return prect->Width; }
inline auto height(const Gdiplus::RectF * prect) { return prect->Height; }


template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(Rect * p, L l, T t, W w, H h) { return set_XYWH_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(RectF * p, L l, T t, W w, H h) { return set_XYWH_dim(p, l, t, w, h); }


inline auto copy(Gdiplus::Rect * prectTarget, const RECT * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::Rect * prectTarget, const RECTD * prectSource) { return _001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::RectF * prectTarget, const RECT * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::RectF * prectTarget, const RECTD * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }


inline auto copy(RECT * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTD * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECT * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTD * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }

#endif


inline void copy(Gdiplus::Point * ppoint1, const POINTD * ppoint2)
{

   ppoint1->X = (INT)ppoint2->x;
   ppoint1->Y = (INT)ppoint2->y;

}


inline void copy(Gdiplus::Point * ppoint1, const POINT * ppoint2)
{

   ppoint1->X = (INT)ppoint2->x;
   ppoint1->Y = (INT)ppoint2->y;

}


inline void copy(Gdiplus::PointF * ppoint1, const POINTD * ppoint2)
{

   ppoint1->X = (REAL)ppoint2->x;
   ppoint1->Y = (REAL)ppoint2->y;

}



