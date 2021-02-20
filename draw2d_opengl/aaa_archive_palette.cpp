#include "framework.h"


namespace draw2d_opengl
{


   palette::palette()
   { 
   
   }


   palette::~palette()
   {
   
   }


   // palette
   palette::operator HPALETTE() const
   {
      return (HPALETTE)(this == nullptr ? nullptr : get_os_data());
   }
   palette* palette::from_handle(::object * pobject, HPALETTE hPalette)
   {
      //return dynamic_cast < palette * > (::draw2d_opengl::object::from_handle(papp, hPalette));
      return nullptr;
   }
   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   {
      //return attach(::CreatePalette(lpLogPalette));
      return false;
   }
   bool palette::CreateHalftonePalette(::image * pimage)
   {
      //ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1() != nullptr);
      //return attach(::CreateHalftonePalette((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1()));
      return false;

   }
   ::u32 palette::GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors) const
   {
      ASSERT(get_os_data() != nullptr); return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, lpPaletteColors);
   }
   ::u32 palette::SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors)
   {
      ASSERT(get_os_data() != nullptr); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, lpPaletteColors);
   }
   void palette::AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries,
                                LPPALETTEENTRY lpPaletteColors)
   {
      ASSERT(get_os_data() != nullptr); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
            lpPaletteColors);
   }
   ::u32 palette::GetNearestPaletteIndex(color32_t crColor) const
   { ASSERT(get_os_data() != nullptr); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor); }

   bool palette::ResizePalette(::u32 nNumEntries)
   {
      ASSERT(get_os_data() != nullptr);
      return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != false;
   }

   i32 palette::GetEntryCount()
   {
      ASSERT(get_os_data() != nullptr); ::u16 nEntries;
      ::GetObject((HANDLE) get_os_data(), sizeof(::u16), &nEntries); return (i32)nEntries;
   }

} // namespace draw2d_opengl