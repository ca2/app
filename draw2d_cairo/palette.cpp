#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


namespace draw2d_cairo
{


   palette::palette()
   {

   }


   palette::~palette()
   {

   }


   // palette
   /*   palette::operator HPALETTE() const
      {

         //return (HPALETTE)(this == nullptr ? nullptr : get_os_data());

         return nullptr;

      }
   */



   /*

      int_bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
      {

      //   return Attach(::CreatePalette(lpLogPalette));

         return false;

      }

   */



   /*

      int_bool palette::CreateHalftonePalette(::image * pimage)
      {

         //ASSERT(pgraphics != nullptr && (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() != nullptr);
         //return Attach(::CreateHalftonePalette((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1()));

         return false;

      }

   */

   /*
      ::u32 palette::GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors) const
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      ::u32 palette::SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      void palette::AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);

         //::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

      }


      ::u32 palette::GetNearestPaletteIndex(color32_t crColor) const
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);

         return 0;

      }
   */

   /*

      int_bool palette::ResizePalette(::u32 nNumEntries)
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries);

         return false;

      }

   */

   /*
      i32 palette::GetEntryCount()
      {

         //ASSERT(get_os_data() != nullptr);

         //::u16 nEntries;

         //::GetObject(get_os_data(), sizeof(::u16), &nEntries); return (i32)nEntries;

         return 0;

      }
   */


} // namespace mac







