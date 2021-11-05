#pragma once

/*HDC GetDC(oswindow hwnd);
HFONT CreateFontIndirect(const LOGFONT * lf);
HPEN CreatePen(i32 iPenStyle, i32 iWidth, color32_t crColor);
HGDIOBJ GetStockObject(i32 iStockObject);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
int_bool Rectangle(HDC hdc, i32 x1, i32 y1, i32 x2, i32 y2);
int_bool DeleteObject(HGDIOBJ hgdiobj);
HDC CreateCompatibleDC(HDC hdc);
//HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, ::u32 usage, void **ppvBits, HANDLE hSection, ::u32 offset);
int_bool SetTextColor(HDC hdc, color32_t color32);
int_bool SetBkMode(HDC hdc, i32 iMode);
int_bool DeleteDC(HDC hdc);
int_bool AlphaBlend(HDC hdcDest, i32 xoriginDest, i32 yoriginDest, i32 wDest, i32 hDest, HDC hdcSrc, i32 xoriginSrc, i32 yoriginSrc, i32 wSrc, i32 hSrc, BLENDFUNCTION ftn);
int_bool GetObject(HGDIOBJ hgdiobj, i32 iSize, void * object);
int_bool GetTextExtentPoint(HDC hdc, const ::string & pszText, i32 iSize, SIZE_I32 * psize);
/*int_bool WINAPI TransparentBlt(HDC hdcDest,
    __in i32 xoriginDest,
    __in i32 yoriginDest,
    __in i32 wDest,
    __in i32 hDest,
    __in HDC hdcSrc,
    __in i32 xoriginSrc,
    __in i32 yoriginSrc,
    __in i32 wSrc,
    __in i32 hSrc,
    __in ::u32 crTransparent);

*/
