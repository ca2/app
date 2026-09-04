#include "platform.h"
#include "impact.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


simple_impact::simple_impact()
{

}


simple_impact::~simple_impact()
{
}


void simple_impact::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);

}


//void simple_impact::assert_ok() const
//{
//
//   ::user::impact::assert_ok();
//
//}
//
//
//void simple_impact::dump(dump_context & dumpcontext) const
//{
//
//   ::user::impact::dump(dumpcontext);
//
//}


void simple_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
{

   ::user::impact::handle(ptopic, phandlercontext);

}


void simple_impact::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
{

   for (auto & text : m_texta)
   {

      pdraw2dgraphics->set(text.m_pwritetextfont);

      pdraw2dgraphics->set_solid_color(text.m_color);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->text_out(text.m_point.x, text.m_point.y, text.m_strText);

   }


}

