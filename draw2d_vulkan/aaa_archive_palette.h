#pragma once


namespace draw2d_vulkan
{


   class CLASS_DECL_DRAW2D_VULKAN palette :
      virtual public ::draw2d_vulkan::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      virtual ~palette();


      static palette * from_handle(::particle * pparticle, HPALETTE hPalette);

      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      bool CreateHalftonePalette(::image::image *pimage);

      
      operator HPALETTE() const;
      int GetEntryCount();
      unsigned int GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
                             LPPALETTEENTRY lpPaletteColors) const;
      unsigned int SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
                             LPPALETTEENTRY lpPaletteColors);

      
      void AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries,
                          LPPALETTEENTRY lpPaletteColors);
      unsigned int GetNearestPaletteIndex(color32_t crColor) const;
      bool ResizePalette(unsigned int nNumEntries);


   };


} // namespace draw2d_vulkan



