#include "framework.h"


namespace user
{


   progress::progress(::object * pobject) :
      ::object(pobject)
   {

   }

   progress::~progress()
   {
   }


   void progress::install_message_routing(::channel * pchannel)
   {

      ::user::control::install_message_routing(pchannel);

   }


   void progress::assert_valid() const
   {

      ::user::control::assert_valid();

   }


   void progress::dump(dump_context & dumpcontext) const
   {

      ::user::control::dump(dumpcontext);

   }




   void progress::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_dRate = m_pscalar->get_rate();

      ::rect rect;

      get_client_rect(rect);

      pgraphics->fill_rect(rect, ARGB(255, 235, 235, 235));

      pgraphics->draw3d_rect(rect, ARGB(255, 128, 128, 128), ARGB(255, 128, 128, 128));

      rect.deflate(1, 1);

      rect.right = (LONG) (rect.width() * m_dRate + rect.left);

      pgraphics->fill_rect(rect, ARGB(255, 100, 220,180));

   }


} // namespace user
