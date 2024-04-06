#include "framework.h"


namespace draw2d_gdiplus
{


   palette::palette()
   {

   }


   palette::~palette()
   {

   }


   palette::operator HPALETTE() const
   {

      return (HPALETTE)(this == nullptr ? nullptr : get_os_data());

   }


   palette* palette::from_handle(::aura::application * papp, HPALETTE hPalette)
   {
      //return dynamic_cast < palette * > (::draw2d_gdiplus::object::from_handle(papp, hPalette));
      return nullptr;
   }
   bool palette::CreatePalette(LPLOGPALETTE pLogPalette)

   {
      //return attach(::CreatePalette(pLogPalette));

      return false;
   }
   bool palette::CreateHalftonePalette(::image * pimage)
   {
      //ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_gdiplus::graphics * >(pgraphics))->get_handle1() != nullptr);
      //return attach(::CreateHalftonePalette((dynamic_cast<::draw2d_gdiplus::graphics * >(pgraphics))->get_handle1()));
      return false;

   }
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY pPaletteColors) const

   {
      ASSERT(get_os_data() != nullptr); return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, pPaletteColors);

   }
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY pPaletteColors)

   {
      ASSERT(get_os_data() != nullptr); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, pPaletteColors);

   }
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                                LPPALETTEENTRY pPaletteColors)

   {
      ASSERT(get_os_data() != nullptr); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
            pPaletteColors);

   }
   UINT palette::GetNearestPaletteIndex(::color::color crColor) const
   { ASSERT(get_os_data() != nullptr); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor); }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      ASSERT(get_os_data() != nullptr);
      return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != false;
   }

   i32 palette::GetEntryCount()
   {
      ASSERT(get_os_data() != nullptr); WORD nEntries;
      ::GetObject((HANDLE) get_os_data(), sizeof(WORD), &nEntries); return (i32)nEntries;
   }

} // namespace draw2d_gdiplus
