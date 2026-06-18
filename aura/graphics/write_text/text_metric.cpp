// Created by camilo on 2026-06-11 09:17 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "text_metric.h"


namespace write_text
{


   text_metric::text_metric()
   {


      m_dHeight = 0.;
      m_dAscent = 0.;
      m_dDescent = 0.;
      m_dInternalLeading = 0.;
      m_dExternalLeading = 0.;
      m_dWeight = 0.;
      m_dOverhang = 0.;
      m_dDigitizedAspectX = 0.;
      m_dDigitizedAspectY = 0.;
       m_wchFirstChar = 0;
       m_wchLastChar = 0;
       m_wchDefaultChar = 0;
       m_wchBreakChar= 0;
     m_bItalic = false;
     m_bUnderlined = false;
     m_bStruckOut = false;
     m_u8PitchAndFamily = 0;
     m_u8CharSet = 0;
   }


}