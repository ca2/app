//
// Created by camilo on 28/01/2021. 03:28 CamiloSasukeThomasBorregaardSørensen
//
#pragma once


using color32_t = unsigned int;


#pragma pack( push , color32, 1 )


class COLOR32
{
public:


   union
   {

      ::u32       u32;

      struct
      {

         unsigned char        red;
         unsigned char        green;
         unsigned char        blue;
         unsigned char        alpha;

      };

   };

};


#pragma pack( pop , color32 )


#ifndef CLASS_DECL_ACME

#define CLASS_DECL_ACME

#endif


CLASS_DECL_ACME color32_t make_colorref(i32 a, i32 r, i32 g, i32 b);

CLASS_DECL_ACME color32_t argb_swap_rb(color32_t cr);


typedef struct tagWINRGBQUAD {
   byte    rgbBlue;
   byte    rgbGreen;
   byte    rgbRed;
   byte    rgbReserved;
} WINRGBQUAD, * LPWINRGBQUAD;



typedef WINRGBQUAD * LPWINRGBQUAD;




