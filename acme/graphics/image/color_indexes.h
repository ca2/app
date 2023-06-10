// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


#pragma pack(push, color_indexes, 1)


struct color_indexes
{

   union
   {

      ::u8 m_ba[4];

      struct
      {

         ::u8 m_u8IndexOpacity;
         ::u8 m_u8IndexRed;
         ::u8 m_u8IndexGreen;
         ::u8 m_u8IndexBlue;

      };

   };

   
   color_indexes(
      ::u8 u8IndexOpacity, 
      ::u8 u8IndexRed,
      ::u8 u8IndexGreen,
      ::u8 u8IndexBlue) : 
      m_u8IndexOpacity(u8IndexOpacity),
      m_u8IndexRed(u8IndexRed), 
      m_u8IndexGreen(u8IndexGreen),
      m_u8IndexBlue(u8IndexBlue) 
   {
   
   }

};


#pragma pack(pop, color_indexes)


inline color_indexes bgra_indexes() { return { 3, 2, 1, 0 }; }
inline color_indexes rgba_indexes() { return { 3, 0, 1, 2 }; }

