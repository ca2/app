#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{


   tooltip::tooltip()
   {

      m_bError = false;

   }

   tooltip::~tooltip()
   {
   }



   void tooltip::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }

   void tooltip::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);
   }


   void tooltip::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&tooltip::on_message_create);
      //

   }


   void tooltip::on_message_create(::message::message * pmessage)
   {

      __construct(m_pfont);

      pmessage->previous();

      if (pmessage->m_bRet)
      {

         return;

      }

      auto psystem = m_psystem->m_paurasystem;

      auto pnode = psystem->node();

      auto strFontName = pnode->font_name(e_font_sans_ex);

      m_pfont->create_point_font(strFontName, 12.0);

   }



   void tooltip::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   //bool tooltip::get_translucency(::user::enum_translucency  & etranslucency, ::enum_element eelement, style_context * pcontext)
   //{

   //   etranslucency = ::user::e_translucency_present;

   //   return true;

   //}


   void tooltip::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->reset_clip();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      auto ppath = __create < ::draw2d::path > ();

      ppath->set_current_point(rectangleClient.left, rectangleClient.bottom);

      ::rectangle_i32 rectangleBody;

      rectangleBody = rectangleClient;

      rectangleBody.left += 16;
      rectangleBody.bottom -= 16;

      ppath->add_line(rectangleBody.left, rectangleBody.top + rectangleBody.height()/2);
      ppath->add_line(rectangleBody.left,rectangleBody.top);
      ppath->add_line(rectangleBody.right,rectangleBody.top);
      ppath->add_line(rectangleBody.right,rectangleBody.bottom);
      ppath->add_line(rectangleBody.left + rectangleBody.height() / 2,rectangleBody.bottom);
      ppath->close_figure();

      ::draw2d::brush_pointer b(e_create, this);

      b->create_solid(argb(190, 255, 255, 123));

      pgraphics->set(b);

      pgraphics->fill_path(ppath);

      auto ppen = __create < ::draw2d::pen > ();

      pgraphics->set(ppen);

      ppen->create_solid(1.0, argb(190, 120, 120, 255));

      pgraphics->draw_path(ppath);

      pgraphics->set_text_color(argb(255, 120, 120, 255));

      //::rectangle_i32 rectangle;

      //rectangleText.left = 0;

      //rectangleText.top = 0;

      //rectangleText.right = m_size.cx;

      //rectangleText.bottom = m_size.cy;

      pgraphics->set(m_pfont);

      rectangleBody.offset(4,0);

      pgraphics->draw_text(m_str,rectangleBody,e_align_vertical_center);

   }

   size_i32 tooltip::CalcSize()
   {

      string_array stra;

      stra.add_lines(m_str);

      ::size_i32 size(0,0);

      ::size_i32 sizeLine;

      ::draw2d::graphics_pointer g(e_create, this);

      g->CreateCompatibleDC(nullptr);

      g->set(m_pfont);

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


   ::user::interaction::enum_type tooltip::get_window_type()
   {

      return type_frame;

   }


} // namespace veritile



