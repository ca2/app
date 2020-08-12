#pragma once


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D palette :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      virtual ~palette();


      //      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      //      bool CreateHalftonePalette(::image::image * pimage);

      // Attributes
//      operator HPALETTE() const;
      i32 GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors);

      // Operations
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                          LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      //      bool ResizePalette(UINT nNumEntries);

      // Implementation
   };


} // namespace draw2d_quartz2d




