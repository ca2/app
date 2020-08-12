#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D palette :
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      virtual ~palette();


      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      bool CreateHalftonePalette(::image * pimage);

      operator HPALETTE() const;
      int GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);

      void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      bool ResizePalette(UINT nNumEntries);


   };


} // namespace draw2d_direct2d




