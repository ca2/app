#include "framework.h"


namespace filehandler
{


   frame::frame(::particle * pparticle) :
      ::object(pparticle),
      simple_frame_window(pparticle)
   {

      window_enable_full_screen();

      set_translucent();

   }


   frame::~frame()
   {

   }


   void frame::assert_ok() const
   {

      simple_frame_window::assert_ok();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


} // namespace filehandler




