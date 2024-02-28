#pragma once

// HDC GetDC(oswindow hwnd);
// HFONT CreateFontIndirect(const LOGFONT * lf);
// HPEN CreatePen(int iPenStyle, int iWidth, color32_t crColor);
// HGDIOBJ GetStockObject(int iStockObject);
// int_bool SelectObject(HDC hdc, HGDIOBJ hgdiobj);
// int_bool Rectangle(HDC hdc, int x1, int y1, int x2, int y2);
// int_bool DeleteObject(HGDIOBJ hgdiobj);
// HDC CreateCompatibleDC(HDC hdc);
// HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, ::u32 usage, void **ppvBits, HANDLE hSection, ::u32 offset);
// int_bool SetTextColor(HDC hdc, color32_t color32);
// int_bool SetBkMode(HDC hdc, int iMode);
// int_bool DeleteDC(HDC hdc);
// int_bool AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn);
// int_bool GetObject(HGDIOBJ hgdiobj, int iSize, void * matter);
// int_bool GetTextExtentPoint(HDC hdc, const ::scoped_string & scopedstrText, int iSize, ::size_i32 * psize);
/*int_bool WINAPI TransparentBlt(HDC hdcDest,
    __in int xoriginDest,
    __in int yoriginDest,
    __in int wDest,
    __in int hDest,
    __in HDC hdcSrc,
    __in int xoriginSrc,
    __in int yoriginSrc,
    __in int wSrc,
    __in int hSrc,
    __in ::u32 crTransparent);

*/
