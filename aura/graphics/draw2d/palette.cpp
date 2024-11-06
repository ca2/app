#include "framework.h"
#include "palette.h"
#include "acme/exception/interface_only.h"


namespace draw2d
{


   palette::palette()
   {

   }


   palette::~palette()
   {

   }


//   bool palette::CreatePalette(LPLOGPALETTE pLogPalette)
//
//   {
//      __UNREFERENCED_PARAMETER(pLogPalette);
//
//      throw ::interface_only();
//      return false;
//   }


//   bool palette::CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      __UNREFERENCED_PARAMETER(pgraphics);
//
//      throw ::interface_only();
//
//      return false;
//
//   }


//   unsigned int palette::GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors) const
//
//   {
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//      return 0;
//   }

//   unsigned int palette::SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors)
//
//   {
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//      return 0;
//   }


//   void palette::AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries, LPPALETTEENTRY pPaletteColors)
//   {
//
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//
//   }


   unsigned int palette::GetNearestPaletteIndex(const ::color::color & color) const
   {

      __UNREFERENCED_PARAMETER(color);
      
      throw ::interface_only();
      
      return 0;

   }


//   bool palette::ResizePalette(unsigned int nNumEntries)
//   {
//
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      throw ::interface_only();
//      return false;
//
//   }


   int palette::GetEntryCount()
   {

      throw ::interface_only();
      return 0;

   }


} // namespace draw2d



