#pragma once


#include "acme/filesystem/filesystem/path.h"
#include "acme/graphics/write_text/font_weight.h"


namespace write_text
{


   struct CLASS_DECL_AURA font_face_request
   {

      ::string       m_strFamily;
      font_weight    m_fontweight = e_font_weight_normal;
      bool           m_bItalic = false;

   };


   struct CLASS_DECL_AURA font_face_source
   {

      ::file::path   m_path;
      int            m_iFaceIndex = 0;
      ::string       m_strResolvedFamily;

   };


} // namespace write_text
