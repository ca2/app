#include "framework.h"


namespace filehandler
{


   frame::frame(::context_object * pcontextobject) :
      ::object(pobject),
      simple_frame_window(pobject)
   {

      window_enable_full_screen();

      set_translucent();

   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


} // namespace filehandler




