#include "framework.h"


namespace draw2d_xlib
{


   palette::palette(::object * pobject) :
      ::object(pobject)
   {

   }


   palette::~palette()
   {

   }


   /*   // palette
      palette::operator HPALETTE() const
      {

         //return (HPALETTE)(this == nullptr ? nullptr : get_os_data());

         return nullptr;

      }

   */
   /*

      palette* PASCAL palette::from_handle(::object * pobject, HPALETTE hPalette)
      {

         //return dynamic_cast < palette * > (::win::object::from_handle(papp, hPalette));

         return nullptr;

      }

   */


   /*

      int_bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
      {

      //   return Attach(::CreatePalette(lpLogPalette));

         return FALSE;

      }

   */



   /*

      int_bool palette::CreateHalftonePalette(::image * pimage)
      {

         //ASSERT(pgraphics != nullptr && (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() != nullptr);
         //return Attach(::CreateHalftonePalette((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1()));

         return FALSE;

      }

   */


   /*   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);
         //return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

         return 0;

      }


      void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
      {

         //ASSERT(get_os_data() != nullptr);

         //::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors);

      }


      UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor);

         return 0;

      }*/


   /*

      int_bool palette::ResizePalette(UINT nNumEntries)
      {

         //ASSERT(get_os_data() != nullptr);

         //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries);

         return FALSE;

      }

   */

   /*
      i32 palette::GetEntryCount()
      {

         //ASSERT(get_os_data() != nullptr);

         //WORD nEntries;

         //::GetObject(get_os_data(), sizeof(WORD), &nEntries); return (i32)nEntries;

         return 0;

      }
   */

} // namespace mac







