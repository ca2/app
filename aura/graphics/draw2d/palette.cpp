#include "framework.h"


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
//      ::exception::throw_interface_only();
//      return false;
//   }


//   bool palette::CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      __UNREFERENCED_PARAMETER(pgraphics);
//
//      ::exception::throw_interface_only();
//
//      return false;
//
//   }


//   ::u32 palette::GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors) const
//
//   {
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      ::exception::throw_interface_only();
//      return 0;
//   }

//   ::u32 palette::SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors)
//
//   {
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      ::exception::throw_interface_only();
//      return 0;
//   }


//   void palette::AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY pPaletteColors)
//   {
//
//      __UNREFERENCED_PARAMETER(nStartIndex);
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      __UNREFERENCED_PARAMETER(pPaletteColors);
//
//      ::exception::throw_interface_only();
//
//   }


   ::u32 palette::GetNearestPaletteIndex(const ::color::color & color) const
   {

      __UNREFERENCED_PARAMETER(color);
      
      ::exception::throw_interface_only();
      
      return 0;

   }


//   bool palette::ResizePalette(::u32 nNumEntries)
//   {
//
//      __UNREFERENCED_PARAMETER(nNumEntries);
//      ::exception::throw_interface_only();
//      return false;
//
//   }


   i32 palette::GetEntryCount()
   {

      ::exception::throw_interface_only();
      return 0;

   }


} // namespace draw2d



