#include "framework.h"


namespace draw2d
{


   buffered_graphics::buffered_graphics()
   {

   }


   buffered_graphics::~buffered_graphics()
   {

   }


   void buffered_graphics::Prepare(const rect & rectParam)
   {
      ::rect rect(rectParam);
      m_p->SetViewportOrg(rect.top_left());
      m_pbitmap->CreateCompatibleBitmap(*this, rect.width(), rect.height());
      m_pbitmapBlend->CreateBitmap(
      *this,
      rect.size(),
      1,
      32,
      nullptr,
      rect.width() * sizeof(COLORREF));
      /*#define ARGB(a, rect,g,b)          ((COLORREF)(((BYTE)(rect)|((WORD)((BYTE)(g))<<8))|(((u32)(BYTE)(b))<<16)|((u32)(BYTE)(a))<<24)))
         set(m_bitmapBlend);
         fill_rect(rect, ARGB(0, 0, 0, 0));*/
   }

} // namespace draw2d
