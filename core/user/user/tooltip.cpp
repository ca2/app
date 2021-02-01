#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


namespace user
{


   tooltip::tooltip(::layered * pobjectContext):
      ::object(pobjectContext),
      m_font(e_create)
   {

      m_font->create_point_font(os_font_name(e_font_sans_ex),12.0);

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

      MESSAGE_LINK(e_message_create,pchannel,this,&tooltip::_001OnCreate);
      //

   }


   void tooltip::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

      if(pmessage->m_bRet)
         return;

   }



   void tooltip::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   //bool tooltip::get_translucency(::user::enum_translucency  & etranslucency, ::user::enum_element eelement, style_context * pcontext)
   //{

   //   etranslucency = ::user::e_translucency_present;

   //   return true;

   //}


   void tooltip::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->reset_clip();

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      ::draw2d::path_pointer path(e_create);

      path->set_current_point(rectClient.left, rectClient.bottom);

      ::rectangle_i32 rectBody;

      rectBody = rectClient;

      rectBody.left += 16;
      rectBody.bottom -= 16;

      path->add_line(rectBody.left, rectBody.top + rectBody.height()/2);
      path->add_line(rectBody.left,rectBody.top);
      path->add_line(rectBody.right,rectBody.top);
      path->add_line(rectBody.right,rectBody.bottom);
      path->add_line(rectBody.left + rectBody.height() / 2,rectBody.bottom);
      path->close_figure();

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(ARGB(190, 255, 255, 123));

      pgraphics->set(b);

      pgraphics->fill_path(path);

      ::draw2d::pen_pointer point_i32(e_create);

      pgraphics->set(point);

      point_i32->create_solid(1.0, ARGB(190, 120, 120, 255));

      pgraphics->draw_path(path);

      pgraphics->set_text_color(ARGB(255, 120, 120, 255));

      //::rectangle_i32 rectangle;

      //rectText.left = 0;

      //rectText.top = 0;

      //rectText.right = m_size.cx;

      //rectText.bottom = m_size.cy;

      pgraphics->set(m_font);

      rectBody.offset(4,0);

      pgraphics->draw_text(m_str,rectBody,e_align_vertical_center);

   }

   size_i32 tooltip::CalcSize()
   {

      string_array stra;

      stra.add_lines(m_str);

      ::size_i32 size_i32(0,0);

      ::size_i32 sizeLine;

      ::draw2d::graphics_pointer g(e_create);

      g->CreateCompatibleDC(nullptr);

      g->set(m_font);

      for(auto strLine : stra)
      {

         sizeLine = g->GetTextExtent(strLine);

         size.cx = max(size.cx,sizeLine.cx);

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



