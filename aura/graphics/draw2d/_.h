#pragma once


namespace draw2d
{


   class cursor;


} // namespace draw2d


namespace write_text
{


   struct font_descriptor
   {

      string      m_strFace;
      float       m_fSize;

   };


} // namespace write_text


CLASS_DECL_AURA void vertical_swap_copy_colorref_swap_red_blue(::color32_t * pcolorrefDst, int cxParam, int cyParam, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);




