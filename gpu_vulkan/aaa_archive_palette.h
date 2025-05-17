#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS palette :
      virtual public ::draw2d_gdiplus::object,
      virtual public ::draw2d::palette
   {
   public:
      
      
      palette();
      virtual ~palette();


      bool CreatePalette(LPLOGPALETTE pLogPalette);

      bool CreateHalftonePalette(::image::image *pimage);

      
      operator HPALETTE() const;
      int GetEntryCount();
      unsigned int GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
                             LPPALETTEENTRY pPaletteColors) const;

      unsigned int SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
                             LPPALETTEENTRY pPaletteColors);


      
      void AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries,
                          LPPALETTEENTRY pPaletteColors);

      unsigned int GetNearestPaletteIndex(color32_t crColor) const;
      bool ResizePalette(unsigned int nNumEntries);


      static palette * from_handle(::aura::application * papp, HPALETTE hPalette);


   };


} // namespace draw2d_gdiplus


