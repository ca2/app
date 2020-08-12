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
      return FALSE;
   }
   bool palette::CreateHalftonePalette(::image * pimage)
   {
      //ASSERT(pgraphics != nullptr && (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1() != nullptr);
      //return attach(::CreateHalftonePalette((dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_handle1()));
      return FALSE;

   }
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors) const
   {
      ASSERT(get_os_data() != nullptr); return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, lpPaletteColors);
   }
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
                                   LPPALETTEENTRY lpPaletteColors)
   {
      ASSERT(get_os_data() != nullptr); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
                                            nNumEntries, lpPaletteColors);
   }
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries,
                                LPPALETTEENTRY lpPaletteColors)
   {
      ASSERT(get_os_data() != nullptr); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
            lpPaletteColors);
   }
   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   { ASSERT(get_os_data() != nullptr); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor); }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      ASSERT(get_os_data() != nullptr);
      return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != FALSE;
   }

   i32 palette::GetEntryCount()
   {
      ASSERT(get_os_data() != nullptr); WORD nEntries;
      ::GetObject((HANDLE) get_os_data(), sizeof(WORD), &nEntries); return (i32)nEntries;
   }

} // namespace draw2d_opengl