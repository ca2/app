//
// Created by camilo on 30/12/2021 18:51 BRT <3ThomasBorregaardSorensen""
//
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA text_metric
   {
      public:


      ::f64         m_dHeight;
      ::f64         m_dAscent;
      ::f64         m_dDescent;
      ::f64         m_dInternalLeading;
      ::f64         m_dExternalLeading;
      ::f64         m_dWeight;
      ::f64         m_dOverhang;
      ::f64         m_dDigitizedAspectX;
      ::f64         m_dDigitizedAspectY;
      ::wide_character       m_wchFirstChar;
      ::wide_character       m_wchLastChar;
      ::wide_character       m_wchDefaultChar;
      ::wide_character       m_wchBreakChar;
      bool           m_bItalic;
      bool           m_bUnderlined;
      bool           m_bStruckOut;
      ::u8           m_u8PitchAndFamily;
      ::u8           m_u8CharSet;


      ::f64 get_line_height() const
      {

         return m_dInternalLeading + m_dAscent + m_dDescent + m_dExternalLeading;

      }

   };


} // namespace write_text



