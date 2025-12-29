// Created by camilo (from https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp
// with interaction with v0idsEmbrace in twitch chat)
// on 2025-06-01 22:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "../face.h"
#include <ft2build.h>
#include FT_FREETYPE_H


namespace draw2d_gpu
{


   class face_freetype :
      virtual public ::draw2d_gpu::face
   {
   public:


      bool m_bFace;
      FT_Face m_face;

      face_freetype();
      ~face_freetype() override;

      void create_character(::typeface::character& ch, const ::scoped_string& scopedstr) override;


   };


} // namespace draw2d_gpu

