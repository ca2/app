#pragma once


namespace draw2d
{

   class CLASS_DECL_AURA font_effects :
      virtual public ::object
   {
   public:


      enum Effects
      {
         EffectSimple = 0,
         EffectEmbossed = 1
      };

      ::draw2d::text_metric			m_tm;

      i32						m_iFontHiHeight;
      ::draw2d::graphics *			m_pDC;

      glyph_set						m_glyphset;

      ::draw2d::font_pointer				m_pfont;
      ::draw2d::font *				m_pfontOld;

      byte *						m_lpBitmap;


      font(::layered * pobjectContext);
      virtual ~font();

      glyph * GetGlyph(WCHAR wchar);
      glyph * GetGlyph(CHAR ch);
      glyph * GetGlyph(UINT ui);
      //glyph * GetNewGlyph();

      void OnUpdateFont();
      void OnSetFont();
      i32 GetMegaHeight();
      void AddGlyphs(const char * pStr);

      bool AddGlyph(WCHAR wchar);
      bool AddGlyph(CHAR ch);
      bool AddGlyph(UINT ui);


      void AddXFGlyphs(string2a & str2aTokens);
      //void OffsetDataPointers(LPVOID pData);



      void UnselectFont();
      void ClearDC();
      void SelectFont();
      void SetDC(::draw2d::graphics_pointer & pgraphics);
      void EmbossedTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &               pcrect,

      double               dRateX,
      double               dHeight,
      string                 &str);

      void EmbossedTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &               pcrect,

      double               dRateX,
      double               dHeight,
      string                 &str,
      LPINT                 piCharsPositions,

      i32                     iCharsPositions,
      i32                  iOffset);

      void SimpleTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      i32                     x,
      i32                     y,
      string                 &str,
      LPINT                piCharsPositions,

      i32                     iCharsPositions);

      void TextOutEx(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &               pcrect,

      double               dRateX,
      double               dHeight,
      string              &str,
      LPINT                  piCharsPositions,

      i32                  iCharsPositions,
      i32                  iOffset,
      i32                  iEffect);

      ::draw2d::font * GetFont();
      void clear();

   };


} // namespace draw2d
