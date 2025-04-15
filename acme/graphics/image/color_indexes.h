// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


//#pragma pack(push, color_indexes, 1)


struct color_indexes
{

   union
   {

      unsigned char m_ba[4];

      // m_ba[0] red index
      // m_ba[1] green index
      // m_ba[2] blue index
      // m_ba[3] opacity index


      struct
      {

         unsigned char m_uchIndexRed;
         unsigned char m_uchIndexGreen;
         unsigned char m_uchIndexBlue;
         unsigned char m_uchIndexOpacity;

      };

      unsigned int m_ui;

   };


   constexpr color_indexes();

   constexpr color_indexes(const color_indexes & indexes) = default;
   //{

   //   m_uchIndexOpacity = indexes.m_uchIndexOpacity;
   //   m_uchIndexRed = indexes.m_uchIndexRed;
   //   m_uchIndexGreen = indexes.m_uchIndexGreen;
   //   m_uchIndexBlue = indexes.m_uchIndexBlue;

   //}


   constexpr color_indexes(
      unsigned char u8IndexRed,
      unsigned char u8IndexGreen,
      unsigned char u8IndexBlue,
      unsigned char u8IndexOpacity) :
      m_uchIndexRed(u8IndexRed),
      m_uchIndexGreen(u8IndexGreen),
      m_uchIndexBlue(u8IndexBlue),
      m_uchIndexOpacity(u8IndexOpacity)
   {

   }


   constexpr unsigned char red() const { return m_ba[0]; }
   constexpr unsigned char green() const { return m_ba[1]; }
   constexpr unsigned char blue() const { return m_ba[2]; }
   constexpr unsigned char opacity() const { return m_ba[3]; }


   constexpr unsigned char operator[](unsigned char u) const { return m_ba[u]; }


};


//#pragma pack(pop, color_indexes)


constexpr inline color_indexes bgra_indexes() { return { 2, 1, 0, 3 }; }
constexpr inline color_indexes rgba_indexes() { return { 0, 1, 2, 3 }; }
constexpr inline color_indexes rbga_indexes() { return { 0, 2, 1, 3 }; }


#include "_configuration.h"


constexpr color_indexes::color_indexes() :
   color_indexes(common_system_image_color_indexes())
{

}



