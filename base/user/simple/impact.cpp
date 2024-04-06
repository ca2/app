#include "framework.h"
#include "impact.h"
#include "aura/graphics/draw2d/graphics.h"


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


void simple_impact::handle(::topic * ptopic, ::context * pcontext)
{

   ::user::impact::handle(ptopic, pcontext);

}


void simple_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   for (auto & text : m_texta)
   {

      pgraphics->set(text.m_pfont);

      pgraphics->set_text_color(text.m_color);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->text_out(text.m_point.x(), text.m_point.y(), text.m_strText);

   }


}

