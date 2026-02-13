// Created by camilo with Mom and Bilbo support on
// 2025-06-02 03:08 <3ThomasBorregaardSørensen!!
#pragma once

namespace typeface
{


   /// Holds all state information relevant to a character as loaded using FreeType
   struct character
   {

      ::pointer < ::gpu::pixmap > m_ppixmapOptional;
      ::memory m_memory;
      int m_iUnicode;
      bool m_bInit;
      //unsigned int TextureID; // ID handle of the glyph texture
      int_sequence2   Size;      // Size of glyph
      int_sequence2   Bearing;   // Offset from baseline to left/top of glyph
      unsigned int Advance;   // Horizontal offset to advance to next glyph
      int aHeight2=0;
      character()
      {
         m_bInit = false;
         //TextureID = 0;
         Advance = 0;
      }

      virtual ::gpu::pixmap * get_gpu_pixmap(::gpu::renderer * pgpurenderer);

   };


} // namespace typeface



