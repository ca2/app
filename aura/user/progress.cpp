#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "progress.h"


namespace user
{


   progress::progress(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

   }

   progress::~progress()
   {
   }


   void progress::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

   }


   void progress::assert_valid() const
   {

      ::user::interaction::assert_valid();

   }


   void progress::dump(dump_context & dumpcontext) const
   {

      ::user::interaction::dump(dumpcontext);

   }




   void progress::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_dRate = m_pscalar->get_rate();

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      pgraphics->fill_rect(rectangle, ARGB(255, 235, 235, 235));

      pgraphics->draw_rect(rectangle, ARGB(255, 128, 128, 128));

      rectangle.deflate(1, 1);

      rectangle.right = (::i32) (rectangle.width() * m_dRate + rectangle.left);

      pgraphics->fill_rect(rectangle, ARGB(255, 100, 220,180));

   }


} // namespace user
