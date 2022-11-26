// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


#pragma pack(push, color_indexes, 1)


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

   color_indexes(byte bA, byte bR, byte bG, byte bB) : a(bA), r(bR), g(bG), b(bB) { }

};


#pragma pack(pop, color_indexes)


inline color_indexes bgra_indexes() { return { 3, 2, 1, 0 }; }
inline color_indexes rgba_indexes() { return { 3, 0, 1, 2 }; }

