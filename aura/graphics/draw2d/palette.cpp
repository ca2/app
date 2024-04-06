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
//      UNREFERENCED_PARAMETER(pLogPalette);
//
//      throw ::interface_only();
//      return false;
//   }


//   bool palette::CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      UNREFERENCED_PARAMETER(pgraphics);
//
//      throw ::interface_only();
//
//      return false;
//
//   }


//   ::u32 palette::GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors) const
//
//   {
//      UNREFERENCED_PARAMETER(nStartIndex);
//      UNREFERENCED_PARAMETER(nNumEntries);
//      UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//      return 0;
//   }

//   ::u32 palette::SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors)
//
//   {
//      UNREFERENCED_PARAMETER(nStartIndex);
//      UNREFERENCED_PARAMETER(nNumEntries);
//      UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//      return 0;
//   }


//   void palette::AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors)
//   {
//
//      UNREFERENCED_PARAMETER(nStartIndex);
//      UNREFERENCED_PARAMETER(nNumEntries);
//      UNREFERENCED_PARAMETER(pPaletteColors);
//
//      throw ::interface_only();
//
//   }


   ::u32 palette::GetNearestPaletteIndex(const ::color::color & color) const
   {

      UNREFERENCED_PARAMETER(color);
      
      throw ::interface_only();
      
      return 0;

   }


//   bool palette::ResizePalette(::u32 nNumEntries)
//   {
//
//      UNREFERENCED_PARAMETER(nNumEntries);
//      throw ::interface_only();
//      return false;
//
//   }


   i32 palette::GetEntryCount()
   {

      throw ::interface_only();
      return 0;

   }


} // namespace draw2d



