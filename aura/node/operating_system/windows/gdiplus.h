#pragma once



#ifdef WINDOWS_DESKTOP

#undef new

#define minimum minimum
#define maximum maximum

#include <gdiplus.h>

#define new ACME_NEW

#undef minimum
#undef maximum

//using namespace Gdiplus;
//
//
//inline auto left(const Gdiplus::Rect * prectangle) { return prectangle->X; }
//inline auto top(const Gdiplus::Rect * prectangle) { return prectangle->Y; }
//inline auto left(const Gdiplus::RectF * prectangle) { return prectangle->X; }
//inline auto top(const Gdiplus::RectF * prectangle) { return prectangle->Y; }


//inline auto width(const Gdiplus::Rect * prectangle) { return prectangle->Width; }
//inline auto height(const Gdiplus::Rect * prectangle) { return prectangle->Height; }
//inline auto width(const Gdiplus::RectF * prectangle) { return prectangle->Width; }
//inline auto height(const Gdiplus::RectF * prectangle) { return prectangle->Height; }




inline auto copy(RECTANGLE_I32 * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTANGLE_F64 * prectTarget, const Gdiplus::Rect * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTANGLE_I32 * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(RECTANGLE_F64 * prectTarget, const Gdiplus::RectF * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }

#endif



