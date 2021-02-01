#include "framework.h"


namespace draw2d
{


   buffered_graphics::buffered_graphics()
   {

   }


   buffered_graphics::~buffered_graphics()
   {

   }


   void buffered_graphics::Prepare(const rectangle_i32 & rectParam)
   {
      ::rectangle_i32 rectangle(rectParam);
      m_p->SetViewportOrg(rectangle.top_left());
      m_pbitmap->CreateCompatibleBitmap(*this, rectangle.width(), rectangle.height());
      m_pbitmapBlend->CreateBitmap(
      *this,
      rectangle.size(),
      1,
      32,
      nullptr,
      rectangle.width() * sizeof(color32_t));
      /*#define ARGB(a, rectangle_i32,g,b)          ((color32_t)(((byte)(rectangle)|((::u16)((byte)(g))<<8))|(((u32)(byte)(b))<<16)|((u32)(byte)(a))<<24)))
         set(m_bitmapBlend);
         fill_rect(rectangle, ARGB(0, 0, 0, 0));*/
   }

} // namespace draw2d
