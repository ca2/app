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
      rect.width() * sizeof(color32_t));
      /*#define ARGB(a, rect,g,b)          ((color32_t)(((byte)(rect)|((::u16)((byte)(g))<<8))|(((u32)(byte)(b))<<16)|((u32)(byte)(a))<<24)))
         set(m_bitmapBlend);
         fill_rect(rect, ARGB(0, 0, 0, 0));*/
   }

} // namespace draw2d
