// From font.h by camilo on 2022-08-28 18:01 <3ThomasBorregaardSørensen!! søndag
#pragma once


#include "acme/constant/character_set.h"


enum enum_font_weight
{

   e_font_weight_dont_care = 0,
   e_font_weight_thin = 100,
   e_font_weight_extra_light = 200,
   e_font_weight_light = 300,
   e_font_weight_normal = 400,
   e_font_weight_medium = 500,
   e_font_weight_semibold = 600,
   e_font_weight_bold = 700,
   e_font_weight_extra_bold = 800,
   e_font_weight_heavy = 900,

};

typedef comparable_array < enum_character_set > enum_character_set_array;

