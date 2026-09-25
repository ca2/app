// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


//#pragma pack(push, color_indexes, 1)


struct CLASS_DECL_ACME color_indexes
{

   union
   {

      ::u8 m_ba[4];

      // m_ba[0] red index
      // m_ba[1] green index
      // m_ba[2] blue index
      // m_ba[3] opacity index


      struct
      {

         ::u8 m_u8IndexRed;
         ::u8 m_u8IndexGreen;
         ::u8 m_u8IndexBlue;
         ::u8 m_u8IndexOpacity;

      };

      ::u32 m_u32;

   };


   color_indexes();

   constexpr color_indexes(const color_indexes & indexes) = default;
   //{

   //   m_u8IndexOpacity = indexes.m_u8IndexOpacity;
   //   m_u8IndexRed = indexes.m_u8IndexRed;
   //   m_u8IndexGreen = indexes.m_u8IndexGreen;
   //   m_u8IndexBlue = indexes.m_u8IndexBlue;

   //}


   constexpr color_indexes(
      ::u8 u8IndexRed,
      ::u8 u8IndexGreen,
      ::u8 u8IndexBlue,
      ::u8 u8IndexOpacity) :
      m_u8IndexRed(u8IndexRed),
      m_u8IndexGreen(u8IndexGreen),
      m_u8IndexBlue(u8IndexBlue),
      m_u8IndexOpacity(u8IndexOpacity)
   {

   }


   constexpr ::u8 red() const { return m_ba[0]; }
   constexpr ::u8 green() const { return m_ba[1]; }
   constexpr ::u8 blue() const { return m_ba[2]; }
   constexpr ::u8 opacity() const { return m_ba[3]; }


   constexpr ::u8 operator[](::u8 u) const { return m_ba[u]; }


};


//#pragma pack(pop, color_indexes)


#include "_configuration.h"




