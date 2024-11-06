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
      //virtual unsigned int GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors) const;

      //virtual unsigned int SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors);






      //virtual void AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors);

      virtual unsigned int GetNearestPaletteIndex(const ::color::color & color) const;
      //virtual bool ResizePalette(unsigned int nNumEntries);


   };


   typedef ::pointer<palette>palette_pointer;


} // namespace draw2d



