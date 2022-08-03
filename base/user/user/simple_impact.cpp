#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "simple_view.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace user
{


   simple_view::simple_view()
   {

   }


   simple_view::~simple_view()
   {
   }


   void simple_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

   }


   void simple_view::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void simple_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void simple_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   void simple_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      for (auto & text : m_texta)
      {

         pgraphics->set(text.m_pfont);

         pgraphics->set_text_color(text.m_color.get_rgba());

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->text_out(text.m_point.x, text.m_point.y, text.m_strText);

      }


   }


} // namespace user
