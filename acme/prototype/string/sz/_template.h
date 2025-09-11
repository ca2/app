// Created by camilo on 2025-09-11 03:04 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_character CHARACTER >
inline character_count _string_get_length2(const CHARACTER * psz, character_count lengthMax) noexcept 
{ 
   
   character_count size = 0;

   while (lengthMax > 0 && *psz) 
   { 
      
      psz++; 
      
      size++; 
      
      lengthMax--; 
   
   }

   return size;

}



