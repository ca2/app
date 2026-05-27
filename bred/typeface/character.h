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
      ::i32 m_iUnicode;
      bool m_bInit;
      //::u32 TextureID; // ID handle of the glyph texture
      i32_sequence2   Size;      // Size of glyph
      i32_sequence2   Bearing;   // Offset from baseline to left/top of glyph
      ::u32 Advance;   // Horizontal offset to advance to next glyph
      ::i32 aHeight2=0;
      character()
      {
         m_bInit = false;
         //TextureID = 0;
         Advance = 0;
      }

      virtual ::gpu::pixmap * get_gpu_pixmap(::gpu::renderer * pgpurenderer);

   };


} // namespace typeface



