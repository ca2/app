#include "framework.h"
#include "buffered_graphics.h"
#include "aura/graphics/draw2d/graphics.h"
//#include "_defer.h"

namespace draw2d
{


   buffered_graphics::buffered_graphics()
   {

   }


   buffered_graphics::~buffered_graphics()
   {

   }


   void buffered_graphics::Prepare(const int_rectangle & rectangleParam)
   {

      ::int_rectangle rectangle(rectangleParam);

      m_p->set_origin(rectangle.top_left());

      m_pbitmap->CreateCompatibleBitmap(*this, rectangle.width(), rectangle.height());

      m_pbitmapBlend->CreateBitmap(
      *this,
      rectangle.size(),
      1,
      32,
      nullptr,
      rectangle.width() * sizeof(::color32_t));

      /*#define argb(a, rectangle,g,b)          ((::color::color)(((unsigned char)(rectangle)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned int)(unsigned char)(b))<<16)|((unsigned int)(unsigned char)(a))<<24)))
         set(m_bitmapBlend);
         fill_rectangle(rectangle, argb(0, 0, 0, 0));*/

   }


} // namespace draw2d



