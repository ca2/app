#include "platform.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "tooltip.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"


namespace user
{


   tooltip::tooltip()
   {

      m_bError = false;

   }

   tooltip::~tooltip()
   {
   }



   //void tooltip::assert_ok() const
   //{
   //   ::user::interaction::assert_ok();
   //}

   //void tooltip::dump(dump_context & dumpcontext) const
   //{
   //   ::user::interaction::dump(dumpcontext);
   //}


   void tooltip::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&tooltip::on_message_create);
      //

   }


   void tooltip::on_message_create(::message::message * pmessage)
   {

      constructø(m_pwritetextfont);

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      //auto psystem = system();

      //auto pnode = psystem->node();

      //auto strFontName = pnode->font_name(e_font_sans_ex);

      m_pwritetextfont->create_font(e_font_sans_ex, 12_pt);

   }



   void tooltip::operator()(::timer * ptimer)
   {

      ::user::interaction::operator()(ptimer);


   }


   //bool tooltip::get_translucency(::user::enum_translucency  & etranslucency, const ::e_element & eelement, style_context * pcontext)
   //{

   //   etranslucency = ::user::e_translucency_present;

   //   return true;

   //}


   void tooltip::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      pdraw2dgraphics->reset_clip();

      auto rectangleX = this->rectangle();

      auto pdraw2dpath = createø < ::draw2d::path > ();

      pdraw2dpath->set_current_point(rectangleX.left, rectangleX.bottom);

      ::i32_rectangle rectangleBody;

      rectangleBody = rectangleX;

      rectangleBody.left += 16;
      rectangleBody.bottom -= 16;

      pdraw2dpath->add_line(rectangleBody.left, rectangleBody.top + rectangleBody.height()/2);
      pdraw2dpath->add_line(rectangleBody.left,rectangleBody.top);
      pdraw2dpath->add_line(rectangleBody.right,rectangleBody.top);
      pdraw2dpath->add_line(rectangleBody.right,rectangleBody.bottom);
      pdraw2dpath->add_line(rectangleBody.left + rectangleBody.height() / 2,rectangleBody.bottom);
      pdraw2dpath->close_figure();

      ::draw2d::brush_pointer b(e_create, this);

      b->create_solid(argb(190, 255, 255, 123));

      pdraw2dgraphics->set(b);

      pdraw2dgraphics->fill(pdraw2dpath);

      auto pdraw2dpen = createø < ::draw2d::pen > ();

      pdraw2dgraphics->set(pdraw2dpen);

      pdraw2dpen->create_solid(1.0, argb(190, 120, 120, 255));

      pdraw2dgraphics->draw(pdraw2dpath);

      pdraw2dgraphics->set_solid_color(argb(255, 120, 120, 255));

      //::i32_rectangle rectangle;

      //rectangleText.left = 0;

      //rectangleText.top = 0;

      //rectangleText.right = m_size.cx;

      //rectangleText.bottom = m_size.cy;

      pdraw2dgraphics->set(m_pwritetextfont);

      rectangleBody.offset(4,0);

      pdraw2dgraphics->draw_text(m_str,rectangleBody,e_align_vertical_center);

   }

   i32_size tooltip::CalcSize()
   {

      string_array_base stra;

      stra.add_lines(m_str);

      ::i32_size size(0,0);

      ::i32_size sizeLine;

      auto g = createø<::draw2d::graphics>();

      g->create_memory_graphics({ 256, 256 }, this);

      g->set(m_pwritetextfont);

      for(auto strLine : stra)
      {

         sizeLine = g->get_text_extent(strLine);

         size.cx = maximum(size.cx,sizeLine.cx);

         size.cy += sizeLine.cy;

      }

      size.cx += 16 + 16;
      size.cy += 16 + 16;


      m_size = size;

      return size;

   }


   ::user::enum_window_type tooltip::get_window_type()
   {

      return e_window_type_frame;

   }


} // namespace veritile



