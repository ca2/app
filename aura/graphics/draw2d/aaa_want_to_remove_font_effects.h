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

      ::write_text::text_metric			m_tm;

      i32						m_iFontHiHeight;
      ::draw2d::graphics *			m_pDC;

      glyph_set						m_glyphset;

      ::write_text::font_pointer				m_pfont;
      ::write_text::font *				m_pfontOld;

      byte *						m_lpBitmap;


      font(::object * pobject);
      virtual ~font();

      glyph * GetGlyph(WCHAR wchar);
      glyph * GetGlyph(char ch);
      glyph * GetGlyph(::u32 u);
      //glyph * GetNewGlyph();

      void OnUpdateFont();
      void OnSetFont();
      i32 GetMegaHeight();
      void AddGlyphs(const char * pStr);

      bool AddGlyph(WCHAR wchar);
      bool AddGlyph(char ch);
      bool AddGlyph(::u32 u);


      void AddXFGlyphs(string2a & str2aTokens);
      //void OffsetDataPointers(LPVOID pData);



      void UnselectFont();
      void ClearDC();
      void SelectFont();
      void SetDC(::draw2d::graphics_pointer & pgraphics);
      void embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const rectangle &               pcrect,

      double               dRateX,
      double               dHeight,
      string                 &str);

      void embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const rectangle &               pcrect,

      double               dRateX,
      double               dHeight,
      string                 &str,
      LPINT                 piCharsPositions,

      i32                     iCharsPositions,
      i32                  iOffset);

      void simple_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      i32                     x,
      i32                     y,
      string                 &str,
      LPINT                piCharsPositions,

      i32                     iCharsPositions);

      void TextOutEx(
      ::draw2d::graphics_pointer & pgraphics,
      const rectangle &               pcrect,

      double               dRateX,
      double               dHeight,
      string              &str,
      LPINT                  piCharsPositions,

      i32                  iCharsPositions,
      i32                  iOffset,
      i32                  iEffect);

      ::write_text::font * GetFont();
      void clear();

   };


} // namespace draw2d
