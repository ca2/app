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

      bool CreateHalftonePalette(::image * pimage);

      
      operator HPALETTE() const;
      i32 GetEntryCount();
      ::u32 GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                             LPPALETTEENTRY pPaletteColors) const;

      ::u32 SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                             LPPALETTEENTRY pPaletteColors);


      
      void AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries,
                          LPPALETTEENTRY pPaletteColors);

      ::u32 GetNearestPaletteIndex(color32_t crColor) const;
      bool ResizePalette(::u32 nNumEntries);


      static palette * from_handle(::aura::application * papp, HPALETTE hPalette);


   };


} // namespace draw2d_gdiplus


