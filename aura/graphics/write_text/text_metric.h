//
// Created by camilo on 30/12/2021 18:51 BRT <3ThomasBorregaardSorensen""
//
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA text_metric
   {
      public:


      double         m_dHeight;
      double         m_dAscent;
      double         m_dDescent;
      double         m_dInternalLeading;
      double         m_dExternalLeading;
      double         m_dWeight;
      double         m_dOverhang;
      double         m_dDigitizedAspectX;
      double         m_dDigitizedAspectY;
      ::wide_character       m_wchFirstChar;
      ::wide_character       m_wchLastChar;
      ::wide_character       m_wchDefaultChar;
      ::wide_character       m_wchBreakChar;
      bool           m_bItalic;
      bool           m_bUnderlined;
      bool           m_bStruckOut;
      byte           m_uchPitchAndFamily;
      byte           m_uchCharSet;


      double get_line_spacing() const
      {

         return m_dInternalLeading + m_dAscent + m_dDescent + m_dExternalLeading;

      }

   };


} // namespace write_text



