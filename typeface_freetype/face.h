// Created by camilo (from https://learnopengl.com/code_viewer_gh.php?code=src/7.in_practice/2.text_rendering/text_rendering.cpp
// with interaction with v0idsEmbrace in twitch chat)
// on 2025-06-01 22:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"
#include <ft2build.h>
#include FT_FREETYPE_H


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE face :
      virtual public ::typeface::face
   {
   public:


      bool m_bFace;
      FT_Face m_face;
      int m_iCapHeight = -1;
      ::memory m_memoryFace;


      face();
      ~face() override;


      void initialize(::particle * pparticle) override;


      void create_character(::typeface::character& ch, const ::scoped_string& scopedstr) override;


      void get_text_metric(::write_text::text_metric* ptextmetrics);

   };


} // namespace typeface_freetype

