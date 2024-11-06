#pragma once


#include "object.h"


namespace draw2d
{


   class CLASS_DECL_AURA palette :
      virtual public ::draw2d::object
   {
   public:


      palette();
      ~palette() override;


      //virtual bool CreatePalette(LPLOGPALETTE pLogPalette);

      //virtual bool CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics);


      virtual int GetEntryCount();
      //virtual ::u32 GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors) const;

      //virtual ::u32 SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors);






      //virtual void AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors);

      virtual ::u32 GetNearestPaletteIndex(const ::color::color & color) const;
      //virtual bool ResizePalette(::u32 nNumEntries);


   };


   typedef ::pointer<palette>palette_pointer;


} // namespace draw2d



