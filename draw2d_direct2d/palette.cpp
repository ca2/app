#include "framework.h"


namespace draw2d_direct2d
{


   palette::palette()
   {

   }


   palette::~palette()
   {

   }


   palette::operator HPALETTE() const
   {

      return nullptr;

   }


   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   {

      //return Attach(::CreatePalette(lpLogPalette));

      return FALSE;

   }


   bool palette::CreateHalftonePalette(::image * pimage)
   {
      //ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1() != nullptr);
      //return Attach(::CreateHalftonePalette((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1()));
      return FALSE;

   }
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors) const
   {

//#ifdef WINDOWS_DESKTOP
//      ASSERT(get_os_data() != nullptr);
//      return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);
//#else
//      __throw(todo());
//#endif

      return 0;

   }
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(get_os_data() != nullptr); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
//                                            nNumEntries, lpPaletteColors);
//#else
//      __throw(todo());
//#endif

      return 0;

   }
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                                LPPALETTEENTRY lpPaletteColors)
   {
      __throw(todo());

      //   ASSERT(get_os_data() != nullptr); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
      //lpPaletteColors);

   }

   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {

      __throw(todo());

      /*   ASSERT(get_os_data() != nullptr); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);
      */
   }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      __throw(todo());

      //ASSERT(get_os_data() != nullptr);
      //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != FALSE;
   }

   int palette::GetEntryCount()
   {
      __throw(todo());

      //   ASSERT(get_os_data() != nullptr); WORD nEntries;
      //::GetObject((HANDLE) get_os_data(), sizeof(WORD), &nEntries); return (int)nEntries;

   }

} // namespace draw2d_direct2d