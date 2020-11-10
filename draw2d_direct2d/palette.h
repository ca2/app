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
      ::u32 GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
      ::u32 SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors);

      void AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors);
      ::u32 GetNearestPaletteIndex(color32_t crColor) const;
      bool ResizePalette(::u32 nNumEntries);


   };


} // namespace draw2d_direct2d




