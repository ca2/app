// Created by camilo on 2023-06-10 00:03 <3ThomasBorregaardSorensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


constexpr COLORREF win32_COLORREF(const ::color::color & color)
{

   return RGB(color.m_u8Red, color.m_u8Green, color.m_u8Blue);

}



