// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:08 <3ThomasBorregaardSørensen!!
#pragma once


#include <glm/glm.hpp>


namespace typeface
{


   /// Holds all state information relevant to a character as loaded using FreeType
   struct character
   {

      ::pointer < ::gpu::pixmap > m_ppixmap;
      int m_iUnicode;
      bool m_bInit;
      //unsigned int TextureID; // ID handle of the glyph texture
      glm::ivec2   Size;      // Size of glyph
      glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
      unsigned int Advance;   // Horizontal offset to advance to next glyph
      character()
      {
         m_bInit = false;
         //TextureID = 0;
         Advance = 0;
      }

   };


} // namespace typeface



