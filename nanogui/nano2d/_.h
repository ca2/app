// Created by camilo on 2022-03-19 01:46 <3ThomasBorregaardS�rensen!!
#pragma once


#include "_nano2d_config.h"


#include "nanovg.h"


inline ::color::color __color(NANO2D_COLOR color)
{

   return { color.r, color.g, color.b, color.a };

}


inline NANO2D_COLOR __nano2d_color(const ::color::color & color)
{

   return { color.fr(), color.fg(), color.fb(), color.fa()};

}


//#include "font_sink.h"


//#include "context.h"
//#include "draw2d_context.h"



