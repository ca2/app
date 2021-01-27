#pragma once



#ifdef WINDOWS_DESKTOP

#undef new

#define min min
#define max max

#include <gdiplus.h>

#define new ACME_NEW

#undef min
#undef max

//using namespace Gdiplus;
//
//
//inline auto left(const Gdiplus::Rect * prect) { return prect->X; }
//inline auto top(const Gdiplus::Rect * prect) { return prect->Y; }
//inline auto left(const Gdiplus::RectF * prect) { return prect->X; }
//inline auto top(const Gdiplus::RectF * prect) { return prect->Y; }


//inline auto width(const Gdiplus::Rect * prect) { return prect->Width; }
//inline auto height(const Gdiplus::Rect * prect) { return prect->Height; }
//inline auto width(const Gdiplus::RectF * prect) { return prect->Width; }
//inline auto height(const Gdiplus::RectF * prect) { return prect->Height; }




inline auto copy(RECT32 * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTD * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECT32 * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTD * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }

#endif



