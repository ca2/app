// Created by camilo on 2022-03-19 01:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "_nano2d_config.h"


#include "nanovg.h"


inline ::color::color __color(NANO2D_COLOR color)
{

   return { color.r, color.g, color.b, color.a };

}


#include "font_sink.h"


#include "context.h"
#include "draw2d_context.h"



