#include "framework.h"


namespace draw2d
{


   buffered_graphics::buffered_graphics()
   {

   }


   buffered_graphics::~buffered_graphics()
   {

   }


   void buffered_graphics::Prepare(const rectangle_i32 & rectangleParam)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      m_p->SetViewportOrg(rectangle.top_left());

      m_pbitmap->CreateCompatibleBitmap(*this, rectangle.width(), rectangle.height());

      m_pbitmapBlend->CreateBitmap(
      *this,
      rectangle.size(),
      1,
      32,
      nullptr,
      rectangle.width() * sizeof(::color32_t));

      /*#define argb(a, rectangle,g,b)          ((::color::color)(((byte)(rectangle)|((::u16)((byte)(g))<<8))|(((u32)(byte)(b))<<16)|((u32)(byte)(a))<<24)))
         set(m_bitmapBlend);
         fill_rectangle(rectangle, argb(0, 0, 0, 0));*/

   }


} // namespace draw2d



