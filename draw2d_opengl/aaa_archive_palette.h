#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL palette :
      virtual public ::draw2d_opengl::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      virtual ~palette();


      static palette * from_handle(::object * pobject, HPALETTE hPalette);

      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      bool CreateHalftonePalette(::image::image * pimage);

      // Attributes
      operator HPALETTE() const;
      i32 GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                             LPPALETTEENTRY lpPaletteColors);

      // Operations
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                          LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      bool ResizePalette(UINT nNumEntries);


   };


} // namespace draw2d_opengl



