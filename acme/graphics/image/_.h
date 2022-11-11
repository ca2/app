// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


struct color_indexes
{
   
   union
   {

      byte m_ba[4];

      struct
      {

         byte a;
         byte r;
         byte g;
         byte b;

      };

   };

   color_indexes(byte bA, byte bR, byte bG, byte bB): a(bA), r(bG), g(bG),  b(bB) { }

};


inline color_indexes bgra_indexes() { return { 3, 2, 1, 0 }; }
inline color_indexes rgba_indexes() { return { 3, 0, 1, 2 }; }



#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD)


inline color_indexes common_system_image_color_indexes() { return bgra_indexes(); }


#else

inline color_indexes common_system_image_color_indexes() { return rgba_indexes(); }


#endif



