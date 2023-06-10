//
// Created by camilo on 28/01/2021. 03:28 CamiloSasukeThomasBorregaardSorensen
//
#pragma once


struct color32_t
{


   ::u32 m_u32;



   constexpr ::u8 u8_red()const { return lower_u8(m_u32); }
   constexpr ::u8 u8_green()const { return lower_u8(m_u32 >> 8); }
   constexpr ::u8 u8_blue()const { return lower_u8(m_u32 >> 16); }
   constexpr ::u8 u8_opacity()const { return lower_u8(m_u32 >> 24); }



};



#pragma pack( push , color32, 1 )


class COLOR32
{
public:


   union
   {

      ::u32       m_u32;

      struct
      {

         ::u8           m_u8Red;
         ::u8           m_u8Green;
         ::u8           m_u8Blue;
         ::u8           m_u8Opacity;

      };

   };


   inline bool operator == (const COLOR32 & color) const { return m_u32 == color.m_u32; }


};


#pragma pack( pop , color32 )


#ifndef CLASS_DECL_ACME

#define CLASS_DECL_ACME

#endif


CLASS_DECL_ACME color32_t make_colorref(i32 a, i32 r, i32 g, i32 b);

CLASS_DECL_ACME color32_t argb_swap_red_blue(color32_t color32);


typedef struct tagWINRGBQUAD {
   ::u8    rgbBlue;
   ::u8    rgbGreen;
   ::u8    rgbRed;
   ::u8    rgbReserved;
} WINRGBQUAD, * LPWINRGBQUAD;



typedef WINRGBQUAD * LPWINRGBQUAD;




