#include "framework.h"
#include "code_frame.h"


namespace coding
{


   frame::frame()
   {

      //m_bDefaultCreateToolbar = false;

   }


   frame::~frame()
   {

   }


   //void frame::assert_ok() const
   //{

   //   simple_frame_window::assert_ok();

   //}


   //void frame::dump(dump_context & dumpcontext) const
   //{

   //   simple_frame_window::dump(dumpcontext);

   //}


   ::user::enum_translucency frame::get_translucency(::user::style * pstyle)
   {

      return ::user::e_translucency_present;

   }


} // namespace coding



