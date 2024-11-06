//
// Created by camilo on 28/01/2021. 03:28 CamiloSasukeThomasBorregaardSorensen
//
#pragma once


//COLOR32_T_ENDIANESS             (*(const char*)&(const int){0xAABBGGRR})



struct color32_t
{

   //static inline const int m_iRedIndex = ENDIAN_ARRAY[0];
   //static inline const int m_iGreenIndex = ENDIAN_ARRAY[1];
   //static inline const int m_iBlueIndex = ENDIAN_ARRAY[2];
   //static inline const int m_iOpacityIndex = ENDIAN_ARRAY[3];

   union
   {

      unsigned int m_u32;

      struct
      {

         unsigned char  m_u8Red;
         unsigned char  m_u8Green;
         unsigned char  m_u8Blue;
         unsigned char  m_u8Opacity;

      };

      unsigned char m_ua[4];

   };


   constexpr unsigned char u8_red() const { return m_u8Red; }
   constexpr unsigned char u8_green() const { return m_u8Green; }
   constexpr unsigned char u8_blue() const { return m_u8Blue; }
   constexpr unsigned char u8_opacity() const { return m_u8Opacity; }


   constexpr unsigned char & u8_red() { return m_u8Red; }
   constexpr unsigned char & u8_green() { return m_u8Green; }
   constexpr unsigned char & u8_blue() { return m_u8Blue; }
   constexpr unsigned char & u8_opacity() { return m_u8Opacity; }


   constexpr ::f32 f32_red() const { return m_u8Red / 255.f; }
   constexpr ::f32 f32_green() const { return m_u8Green / 255.f; }
   constexpr ::f32 f32_blue() const { return m_u8Blue / 255.f; }
   constexpr ::f32 f32_opacity() const { return m_u8Opacity / 255.f; }


};



#pragma pack( push , color32, 1 )


class COLOR32
{
public:


   union
   {

      unsigned int       m_u32;

      struct
      {

         unsigned char           m_u8Red;
         unsigned char           m_u8Green;
         unsigned char           m_u8Blue;
         unsigned char           m_u8Opacity;

      };

   };


   inline bool operator == (const COLOR32 & color) const { return m_u32 == color.m_u32; }


};


#pragma pack( pop , color32 )


#ifndef CLASS_DECL_ACME

#define CLASS_DECL_ACME

#endif


CLASS_DECL_ACME color32_t make_colorref(int a, int r, int g, int b);

CLASS_DECL_ACME color32_t argb_swap_red_blue(color32_t color32);


typedef struct tagWINRGBQUAD {
   unsigned char    rgbBlue;
   unsigned char    rgbGreen;
   unsigned char    rgbRed;
   unsigned char    rgbReserved;
} WINRGBQUAD, * LPWINRGBQUAD;



typedef WINRGBQUAD * LPWINRGBQUAD;




