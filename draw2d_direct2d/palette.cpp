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

      return false;

   }


   bool palette::CreateHalftonePalette(::image * pimage)
   {
      //ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1() != nullptr);
      //return Attach(::CreateHalftonePalette((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1()));
      return false;

   }
   ::u32 palette::GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors) const
   {

//#ifdef WINDOWS_DESKTOP
//      ASSERT(get_os_data() != nullptr);
//      return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);
//#else
//      __throw(todo);
//#endif

      return 0;

   }
   ::u32 palette::SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(get_os_data() != nullptr); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
//                                            nNumEntries, lpPaletteColors);
//#else
//      __throw(todo);
//#endif

      return 0;

   }
   void palette::AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries,
                                LPPALETTEENTRY lpPaletteColors)
   {
      __throw(todo);

      //   ASSERT(get_os_data() != nullptr); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
      //lpPaletteColors);

   }

   ::u32 palette::GetNearestPaletteIndex(color32_t crColor) const
   {

      __throw(todo);

      /*   ASSERT(get_os_data() != nullptr); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);
      */
   }

   bool palette::ResizePalette(::u32 nNumEntries)
   {
      __throw(todo);

      //ASSERT(get_os_data() != nullptr);
      //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != false;
   }

   int palette::GetEntryCount()
   {
      __throw(todo);

      //   ASSERT(get_os_data() != nullptr); ::u16 nEntries;
      //::GetObject((HANDLE) get_os_data(), sizeof(::u16), &nEntries); return (int)nEntries;

   }

} // namespace draw2d_direct2d