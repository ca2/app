#pragma once


#include "acme/os/windows/_.h"


CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW* lpLogFont = nullptr);

CLASS_DECL_APEX HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc);


#include "windowing.h"



