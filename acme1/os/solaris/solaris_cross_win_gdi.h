#pragma once

/*HDC GetDC(oswindow hwnd);
HFONT CreateFontIndirect(const LOGFONT * lf);
HPEN CreatePen(i32 iPenStyle, i32 iWidth, COLORREF crColor);
HGDIOBJ GetStockObject(i32 iStockObject);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
WINBOOL Rectangle(HDC hdc, i32 x1, i32 y1, i32 x2, i32 y2);
WINBOOL DeleteObject(HGDIOBJ hgdiobj);
HDC CreateCompatibleDC(HDC hdc);
//HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
WINBOOL SetTextColor(HDC hdc, COLORREF cr);
WINBOOL SetBkMode(HDC hdc, i32 iMode);
WINBOOL DeleteDC(HDC hdc);
WINBOOL AlphaBlend(HDC hdcDest, i32 xoriginDest, i32 yoriginDest, i32 wDest, i32 hDest, HDC hdcSrc, i32 xoriginSrc, i32 yoriginSrc, i32 wSrc, i32 hSrc, BLENDFUNCTION ftn);
WINBOOL GetObject(HGDIOBJ hgdiobj, i32 iSize, void * generic);
WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, i32 iSize, SIZE * psize);
/*WINBOOL WINAPI TransparentBlt(HDC hdcDest,
    __in i32 xoriginDest,
    __in i32 yoriginDest,
    __in i32 wDest,
    __in i32 hDest,
    __in HDC hdcSrc,
    __in i32 xoriginSrc,
    __in i32 yoriginSrc,
    __in i32 wSrc,
    __in i32 hSrc,
    __in UINT crTransparent);

*/
