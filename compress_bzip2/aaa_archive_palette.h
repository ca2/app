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
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY pPaletteColors) const;

      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY pPaletteColors);


      
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                          LPPALETTEENTRY pPaletteColors);

      UINT GetNearestPaletteIndex(::color::color crColor) const;
      bool ResizePalette(UINT nNumEntries);


      static palette * from_handle(::aura::application * papp, HPALETTE hPalette);


   };


} // namespace draw2d_gdiplus


