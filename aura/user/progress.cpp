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

      ::rect rect;

      get_client_rect(rect);

      pgraphics->fill_rect(rect, ARGB(255, 235, 235, 235));

      pgraphics->draw_rect(rect, ARGB(255, 128, 128, 128));

      rect.deflate(1, 1);

      rect.right = (LONG) (rect.width() * m_dRate + rect.left);

      pgraphics->fill_rect(rect, ARGB(255, 100, 220,180));

   }


} // namespace user
