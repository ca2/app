// Created by camilo on 2022-03-19 01:46 <3ThomasBorregaardSorensen!!
#pragma once


//#include "_nano2d_config.h"


//#include "nano2d.h"


inline ::color::color as_color(::nano2d::color color)
{

   return { color.r, color.g, color.b, color.a };

}


inline ::nano2d::color as_nano2d_color(const ::color::color & color)
{

   return { color.fr(), color.fg(), color.fb(), color.fa()};

}


//#include "font_sink.h"


//#include "context.h"
//#include "draw2d_context.h"



