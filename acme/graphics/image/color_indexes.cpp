//
// Created by camilo on 2026-09-22 18:58 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "platform.h"
#include "color_indexes.h"


static color_indexes g_colorindexes;


color_indexes::color_indexes() :
   color_indexes(common_system_image_color_indexes())
{

}


color_indexes common_system_image_color_indexes()
{

   return g_colorindexes;

}


void set_common_system_image_color_indexes(const ::color_indexes & colorindexes)
{

   g_colorindexes = colorindexes;

}



