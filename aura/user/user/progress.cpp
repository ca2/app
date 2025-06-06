#include "framework.h"
#include "progress.h"
#include "aura/graphics/draw2d/graphics.h"


namespace user
{


   progress::progress()
   {

   }


   progress::~progress()
   {
   }


   void progress::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

   }


//   void progress::assert_ok() const
//   {
//
//      ::user::interaction::assert_ok();
//
//   }
//
//
//   void progress::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::interaction::dump(dumpcontext);
//
//   }




   void progress::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_dRate = m_scalar.get_rate();

      auto rectangle = this->rectangle();

      pgraphics->fill_rectangle(rectangle, argb(255, 235, 235, 235));

      pgraphics->draw_inset_rectangle(rectangle, argb(255, 128, 128, 128), 1.0);

      rectangle.deflate(1, 1);

      rectangle.right() = (int) (rectangle.width() * m_dRate + rectangle.left());

      pgraphics->fill_rectangle(rectangle, argb(255, 100, 220,180));

   }


} // namespace user
