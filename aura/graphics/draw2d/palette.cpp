#include "framework.h"


namespace draw2d
{


   palette::palette()
   {

   }


   palette::~palette()
   {

   }


   bool palette::CreatePalette(LPLOGPALETTE pLogPalette)

   {
      UNREFERENCED_PARAMETER(pLogPalette);

      ::exception::throw_interface_only();
      return false;
   }


   bool palette::CreateHalftonePalette(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

      ::exception::throw_interface_only();

      return false;

   }


   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors) const

   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(pPaletteColors);

      ::exception::throw_interface_only();
      return 0;
   }

   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors)

   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(pPaletteColors);

      ::exception::throw_interface_only();
      return 0;
   }

   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY pPaletteColors)

   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(pPaletteColors);

      ::exception::throw_interface_only();

   }

   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {
      UNREFERENCED_PARAMETER(crColor);
      ::exception::throw_interface_only();
      return 0;
   }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      UNREFERENCED_PARAMETER(nNumEntries);
      ::exception::throw_interface_only();
      return false;
   }

   i32 palette::GetEntryCount()
   {
      ::exception::throw_interface_only();
      return 0;
   }


} // namespace draw2d








