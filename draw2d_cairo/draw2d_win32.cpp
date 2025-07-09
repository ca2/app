//
// Created by camilo on 2025-07-09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "draw2d.h"
#include "acme/_operating_system.h"


namespace draw2d_cairo
{

    void draw2d::adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle)
    {

        nExStyle |= WS_EX_LAYERED;

    }

} // namespace draw2d_cairo


