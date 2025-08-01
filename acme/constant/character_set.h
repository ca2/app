// Refactored to generate text from enum by camilo on 2023-06-07 04:17 <3ThomasBorregaardSorensen!!
#pragma once


enum enum_character_set : int
{


#define DO_ENUM(e) e,
#include "character_set.enum"
#undef DO_ENUM


};


inline const_char_pointer  enum_character_set_text(enum_character_set echaracterset)
{

   switch (echaracterset)
   {

#define DO_ENUM(e) case e: return #e;
#include "character_set.enum"
#undef DO_ENUM

   default: 
      return nullptr;

   }

}



