#include "framework.h"
#include "still.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/string/international.h"
#include "aura/graphics/write_text/text_out.h"
#include "aura/graphics/write_text/text_out_array.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"


namespace user
{


   still::still()
   {

      m_etextwrap = e_text_wrap_word_then_character;

      m_ptextouta = nullptr;
      m_estockicon = e_stock_icon_none;
      m_estill = e_still_none;
      m_iClick = 0;
      m_ealignText = e_align_center;

      m_flagNonClient -= e_non_client_background;
      m_flagNonClient -= e_non_client_focus_rect;
      
      //m_bEatsDoubleClick = false;

   }


   still::~still()
   {

   }


   ::appearance::appearance * still::get_appearance()
   {
      
      return ::user::interaction::get_appearance();
   
   }


   void still::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &still::on_message_create);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &still::on_message_key_down);

   }


   void still::set_text_align(::e_align ealignText)
   {

      m_ealignText = ealignText;

   }


   void still::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if (m_pstillappearance)
      //{

      //   m_pstillappearance->_001OnDraw(pgraphics);

      //   return;

      //}

      if (m_bAutoResize)
      {

         //informationf("m_bAutoResize");

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      auto pstyle = get_style(pgraphics);

      if (m_estill == e_still_image)
      {

         _001OnDrawImage(pgraphics);

      }
      else
      {

         auto psession = get_session();

         auto strWindowText = get_window_text();

         //get_window_text(strText);

         ::rectangle_f64 rectangleX;

         rectangleX = this->rectangle();

         auto estate = get_user_state();

         auto color = get_color(pstyle, ::e_element_text, estate);

         pgraphics->set_text_color(color);

         auto rectanglePadding = get_padding(pstyle);

         rectangleX.deflate(rectanglePadding);

         if (m_estockicon != e_stock_icon_none)
         {

            auto ppen = __create < ::draw2d::pen > ();

            ppen->m_color = pgraphics->get_current_brush()->m_color;

            ppen->m_dWidth = 1.0;

            pgraphics->set(ppen);

            ::rectangle_i32 rectangleIcon(rectangleX);

            rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

            pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         }
         else
         {


            //auto pbrushText = __create < ::draw2d::brush >();


            //if (!is_window_enabled())
            //{

            //   //         pgraphics->set_text_color(pstyle->m_colorTextDisabled);
            //   pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_disabled));

            //}
            //else if (is_left_button_pressed())
            //{
            //   //         pgraphics->set_text_color(pstyle->m_colorTextPress);
            //   pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_pressed));
            //}
            //else if (m_pitemHover && m_pitemHover->is_set())
            //{
            //   //         pgraphics->set_text_color(pstyle->m_colorTextHover);
            //   pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_hover));
            //}
            //else
            //{
            //   //         pgraphics->set_text_color(pstyle->m_colorTextNormal);
            //   pbrushText->create_solid(get_color(pstyle, e_element_text));
            //}

            //pgraphics->set(pbrushText);


            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            defer_update_text_out_array(pgraphics);

            if(m_ptextouta)
            {

               pgraphics->draw(*m_ptextouta);

            }

            //pgraphics->draw_text(strText, rectangleX, ealign, edrawtext);

            //m_rectangleTextBoundingBox.left() = 0;

            //m_rectangleTextBoundingBox.top() = 0;

            //m_rectangleTextBoundingBox.set_size(pgraphics->get_text_extent(strText));

            //m_rectangleTextBoundingBox.Align(ealign, rectangleX);

         }

      }

   }


   //void still::on_message_left_button_down(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->previous();

   //   auto point = screen_to_client(pmouse->m_point);

   //   if (hit_test(pmouse->)
   //   {

   //      if (!simple_process_system_message(pmessage, ::id_button_down))
   //      {

   //         psession->m_puiLastLButtonDown = this;

   //         pmouse->m_bRet = true;

   //      }

   //   }

   //}


   //void still::on_message_middle_button_down(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point_i32 point = pmouse->m_point;

   //   screen_to_client()(point);

   //   if (hit_test(point, eelement) >= 0)
   //   {

   //      if (!simple_process_system_message(pmessage, ::id_m_button_down))
   //      {

   //         //psession->m_puiLastLButtonDown = this;

   //         pmouse->m_bRet = true;

   //      }

   //   }

   //}


   //void still::on_message_middle_button_up(::message::message * pmessage)
   //{

   //   auto pmouse = pmessage->m_union.m_pmouse;

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point_i32 point = pmouse->m_point;

   //   screen_to_client()(point);

   //   if (hit_test(point, eelement) >= 0)
   //   {

   //      if (!simple_process_system_message(pmessage, ::id_m_button_up))
   //      {

   //         //psession->m_puiLastLButtonDown = this;

   //         pmouse->m_bRet = true;

   //      }



   //   }

   //}

   ////bool still::is_pressed()
   ////{
   ////   return psession->m_puiLastLButtonDown == this;
   ////}

   //void still::on_message_left_button_up(::message::message * pmessage)
   //{

   //   //auto pmouse = pmessage->m_union.m_pmouse;

   //   //enum_element eelement;

   //   //::point_i32 point = pmouse->m_point;

   //   //screen_to_client()(point);

   //   //if (hit_test(point, eelement) >= 0 && psession->m_puiLastLButtonDown == this)
   //   //{

   //   //   psession->m_puiLastLButtonDown = nullptr;

   //   //   pmessage->m_bRet = on_click(item);

   //   //   if (pmessage->m_bRet)
   //   //   {

   //   //      pmouse->set_lresult(1);

   //   //   }
   //   //   else
   //   //   {

   //   //      ::topic topic;

   //   //      topic.m_puserinteraction = this;

   //   //      topic.m_atom = ::id_click;

   //   //      route(&topic);

   //   //      pmessage->m_bRet = topic.m_bRet;

   //   //      if (!pmessage->m_bRet)
   //   //      {

   //   //         ::message::command command;

   //   //         command.m_atom = m_atom;

   //   //         command.m_puiOther = this;

   //   //         route_command_message(&command);

   //   //         pmessage->m_bRet = command.m_bRet;

   //   //      }

   //   //      if (pmessage->m_bRet)
   //   //      {

   //   //         pmouse->set_lresult(1);

   //   //      }

   //   //   }

   //   //}

   //}


   //void still::on_message_mouse_move(::message::message * pmessage)
   //{

   //   //auto pmouse = pmessage->m_union.m_pmouse;

   //   //enum_element eelement;

   //   //index iHover = hit_test(pmouse->m_point, eelement);
   //   //if (iHover != m_iHover)
   //   //{
   //   //   index iOldHover = m_iHover;
   //   //   m_iHover = iHover;
   //   //   set_need_redraw();

   //   //   if (iHover >= 0)
   //   //   {

   //   //      track_mouse_hover();

   //   //   }


   //   //   if (iOldHover == -1)
   //   //   {
   //   //      ::topic topic;
   //   //      topic.m_puserinteraction = this;
   //   //      topic.m_atom = ::id_mouse_enter;
   //   //      get_parent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //               m_bActionHover = true;
   //   //   }
   //   //   else if (iHover == -1)
   //   //   {
   //   //      ::topic topic;
   //   //      topic.m_puserinteraction = this;
   //   //      topic.m_atom = ::id_mouse_leave;
   //   //      get_parent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //             m_bActionHover = false;
   //   //   }
   //   //}
   //   //pmessage->m_bRet = false;

   //}


   //void still::on_message_mouse_leave(::message::message * pmessage)
   //{

   //   //::pointer<::user::message>pusermessage(pmessage);
   //   //index iOldHover = m_iHover;
   //   //m_iHover = -1;
   //   //if (iOldHover >= 0)
   //   //{
   //   //   set_need_redraw();
   //   //   ::topic topic;
   //   //   topic.m_puserinteraction = this;
   //   //   topic.m_atom = ::id_mouse_leave;
   //   //   if (get_parent() != nullptr)
   //   //   {
   //   //      get_parent()->send_message(e_message_event, 0, (LPARAM)&ev);
   //   //   }
   //   //}

   //   //pusermessage->m_bRet = false;

   //}

   //::item_pointer still::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
   //{

   //   return control::hit_test(pmouse);

   //   //::rectangle_i32 rectangleWindow;
   //   //window_rectangle(rectangleWindow);
   //   //if (rectangleWindow.contains(point))
   //   //{
   //   //   eelement = element_area;
   //   //   return 0;
   //   //}
   //   //else
   //   //{
   //   //   eelement = e_element_none;
   //   //   return -1;
   //   //}
   //}


   ::size_f64 still::get_fitting_size(::draw2d::graphics_pointer & pgraphics)
   {

      if (pgraphics.is_null())
      {

         auto psystem = system();

         auto pdraw2d = psystem->draw2d();

         pgraphics = pdraw2d->create_memory_graphics(this);

      }

      pgraphics->set_font(this, ::e_element_none);

      auto strWindowText = get_window_text();

      auto size = pgraphics->get_text_extent(strWindowText);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size_f64 sizeTotal;

      sizeTotal.cx() = size.cx();

      sizeTotal.cy() = tm.get_line_height();

      return sizeTotal;

   }

   
   void still::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_estill == e_still_text)
      {

         pgraphics->set_font(this, ::e_element_none);

         auto strWindowText = get_window_text();

         //get_window_text(str);

         auto size = pgraphics->get_text_extent(strWindowText);

         ::rectangle_i32 rectangle(0, 0, 0, 0);

         rectangle.right() = ::i32(size.cx() * 1.6);
         rectangle.bottom() = ::i32(size.cy() * 1.4);

         const_layout().sketch().size() = rectangle.size();

      }
      else if (m_estill == e_still_image)
      {

         auto size = m_pimage->size();

         set_size(size);

      }
      else
      {

         auto sizeTotal = get_adjusted_fitting_size(pgraphics);

         set_size(sizeTotal);

      }

   }

   //void still::_001SetButtonText(const ::string & pcszText)

   //{
   //   m_istrButtonText = pcszText;

   //}


   //void still::set_check(const ::e_check & echeck, const ::action_context & context)
   //{

   //   check::set_check(echeck, context);

   //}


   ::status < ::color::color > still::get_color(::user::style* pstyle, enum_element eelement, ::user::enum_state elayout)
   {


      //if (eelement == e_element_text)
      //{

      //   if (m_statuscolorText.ok())
      //   {

      //      return m_statuscolorText;

      //   }

      //}

      return ::user::interaction::get_color(pstyle, eelement, elayout);

   }


   void still::set_text_color(::status < ::color::color > statuscolor)
   {

      m_statuscolorText = statuscolor;

   }


   void still::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      sync_style();

      //if (m_pdescriptor->m_setStyle["vertical-align"] == "center")
      //{


      //}


      if (m_atom.has_char())
      {

         //string strText = _(m_atom);

         set_window_text(m_atom);

      }

      if (m_estill == e_still_none)
      {

         set_still_type(e_still_text);

      }

   }


   void still::defer_update_text_out_array(::draw2d::graphics_pointer & pgraphics)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::pointer<::write_text::font>pfont;

      auto pstyle = get_style(pgraphics);

      if (m_pfont)
      {

         pfont = m_pfont;

      }
      else
      {

         pfont = get_font(pstyle, ::e_element_none);

      }

      ::string strWindowText = get_window_text();

      if(strWindowText.is_empty())
      {

         if(m_ptextouta)
         {

            m_ptextouta = nullptr;

         }

         return;

      }

      pgraphics->set_font(this, ::e_element_none);

      auto pOsData = pgraphics->get_current_font()->get_os_data(pgraphics, 0);

      if(m_ptextouta && m_ptextouta->is_updated(strWindowText, pOsData))
      {

         return;

      }

      //auto pstyle = get_style(pgraphics);

      auto rectangleX = this->rectangle();

      ::e_align ealign = (enum_align)get_int(pstyle, ::user::e_int_edit_text_align, ::user::e_state_none, m_ealignText);

      ::e_draw_text edrawtext = (enum_draw_text)get_int(pstyle, ::user::e_int_edit_draw_text_flags, ::user::e_state_none, e_draw_text_none);

      ::enum_text_wrap etextwrap = m_etextwrap;

      if(::is_null(m_ptextouta))
      {

         m_ptextouta = __allocate write_text::text_out_array();

      }

      m_ptextouta->text_outa().erase_all();

      pgraphics->create_simple_multiline_layout(*m_ptextouta, strWindowText, rectangleX, pgraphics->get_current_font(), ealign, etextwrap);

      m_ptextouta->m_strLast = strWindowText;

      m_ptextouta->m_pLastOsData = pOsData;

      //if (m_bAutoResize)
      //{

      //   set_size(m_rectangleText.size());

      //}

   }


   void still::on_set_window_text()
   {

      ::user::interaction::on_set_window_text();

      if (m_bAutoResize)
      {

         m_bNeedAutoResizePerformLayout = true;

      }

      set_need_redraw();

      post_redraw();

   }


   bool still::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bNeedAutoResizePerformLayout)
      {

         _synchronous_lock synchronouslock(this->synchronization());

         //::pointer<::write_text::font>pfont;

         //auto pstyle = get_style(pgraphics);

         //if (m_pfont)
         //{

         //   pfont = m_pfont;

         //}
         //else
         //{

         //   pfont = get_font(pstyle, ::e_element_none);

         //}

         ::string strWindowText = get_window_text();

         if (strWindowText.is_empty())
         {

            if (m_ptextouta)
            {

               m_ptextouta = nullptr;

            }

            return false;

         }

         pgraphics->set_font(this, ::e_element_none);

         auto pOsData = pgraphics->get_current_font()->get_os_data(pgraphics, 0);

         if (m_ptextouta && m_ptextouta->is_updated(strWindowText, pOsData))
         {

            return false;

         }

         auto rectangleX = this->rectangle();

         ::size_f64 sizeText = get_fitting_size(pgraphics);

         //::rectangle_i32 rectangle;

         //rectangle.left() = (::i32)(rectangleX.left() + (rectangleX.width() - sizeText.cx()) / 2);

         //rectangle.top() = (::i32)(rectangleX.top() + (rectangleX.height() - sizeText.cy()) / 2);

         //rectangle.right() = (::i32)(rectangle.left() + sizeText.cx());

         //rectangle.bottom() = (::i32)(rectangle.top() + sizeText.cy());

         //m_rectangleText = rectangle;

         set_size(::ceil(sizeText), ::user::e_layout_layout, pgraphics);

         return true;

      }

      return false;

   }


   void still::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      defer_update_text_out_array(pgraphics);

   }


   //bool still::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   return interaction::create_interaction(pinteractionParent, atom);

   //}


   ::write_text::font_pointer still::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if(m_pfont)
      {

         return m_pfont;

      }

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void still::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      ::color::color colorBackground;

      if (!is_window_enabled())
      {
         
         // Still Disabled Background
         colorBackground = argb(255, 192, 192, 192);

      }
      else if (is_left_button_pressed())
      {
         
         // Still Pressed Background
         colorBackground = argb(255, 192, 192, 250);

      }
      else if (m_pitemHover && m_pitemHover->is_set())
      {

         // Still Mouse Over Background
         colorBackground = argb(255, 220, 220, 250);

      }
      else
      {

         // Still Normal Background
         colorBackground = argb(255, 127, 127, 250);

      }

      auto pstyle = get_style(pgraphics);

      auto psystem = system();

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->fill_rectangle(rectangleX, colorBackground & 0.5_opacity);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleX, colorBackground);

      }

      ::color::color colorBorder;

      if (!is_window_enabled())
      {

         colorBorder = argb(255, 127, 127, 127);

      }
      else if (is_left_button_pressed())
      {
         
         colorBorder = argb(255, 255, 255, 255);

      }
      else if (m_pitemHover && m_pitemHover->is_set())
      {
         
         colorBorder = argb(255, 100, 100, 200);

      }
      else
      {
         
         colorBorder = argb(255, 10, 10, 100);

      }

      auto rectangle = get_border(pstyle);

      if (rectangle.is_ok())
      {

         pgraphics->draw_inset_rectangle(rectangleX, colorBorder, 1.0);

      }

//      rectangleX.left() += 3;
//
//      rectangleX.top() += 3;

      //::rectangle_i32 rectangleText = m_rectangleText;

      auto rectangleText = this->rectangle();

      //      string str = utf8_to_unicode(str);

      if (m_pimage->is_ok())
      {
         
         ::rectangle_i32 rectangleDib;

         rectangleDib = rectangleText;
         rectangleDib.bottom() = minimum(rectangleText.top() + m_pimage->height(), rectangleText.bottom());
         rectangleDib.right() = minimum(rectangleText.left() + m_pimage->width(), rectangleText.right());
         //m_pimage->to(pgraphics, rectangleDib);

         {

            ::image::image_source imagesource(m_pimage);

            auto rectangle = rectangleDib;

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

         rectangleText.left() += m_pimage->width();

      }


      auto pbrushText = __create < ::draw2d::brush > ();


      if (!is_window_enabled())
      {

         //         pgraphics->set_text_color(pstyle->m_colorTextDisabled);
         pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_disabled));

      }
      else if (is_left_button_pressed())
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextPress);
         pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_pressed));
      }
      else if (m_pitemHover && m_pitemHover->is_set())
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextHover);
         pbrushText->create_solid(get_color(pstyle, e_element_text, e_state_hover));
      }
      else
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextNormal);
         pbrushText->create_solid(get_color(pstyle, e_element_text));
      }

      pgraphics->set(pbrushText);   

      string strText(get_window_text());

      if (m_pfont)
      {

         pgraphics->set(m_pfont);

      }
      else
      {

         pgraphics->set_font(this, ::e_element_none);

      }

      pgraphics->draw_text(strText, rectangleText, e_align_top_left);

   }


   bool still::keyboard_focus_is_focusable()
   {

      //return is_window_enabled() && is_window_visible();
      return false;

   }


   void still::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         auto ptopic = create_topic(::id_click);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext.m_pmessage = pmessage;

         ptopic->m_actioncontext.add(e_source_user);

         route(ptopic);

         pmessage->m_bRet = ptopic->m_bRet;

         if (pmessage->m_bRet)
         {

            pkey->m_lresult = 1;

         }

      }

   }


   void still::_001OnDrawImage(::draw2d::graphics_pointer & pgraphics)
   {

      auto strWindowText = get_window_text();

      auto rectangleX = this->rectangle();


      //if (pstyle == nullptr)
      //{

      //   if (m_iHover == 0 || psession->m_puiLastLButtonDown == this)
      //   {

      //      pgraphics->fill_rectangle(rectangleX, argb(255, 127, 127, 127));

      //   }
      //   else
      //   {

      //      pgraphics->fill_rectangle(rectangleX, argb(255, 127, 127, 127));

      //   }

      //}
      //else

      auto pstyle = get_style(pgraphics);

      {
         if (!is_window_enabled())
         {

            pgraphics->fill_rectangle(rectangleX, get_color(pstyle, e_element_background, e_state_disabled));

         }
         else if ((m_pitemHover && m_pitemHover->is_set()) || is_left_button_pressed())
         {

            //pgraphics->draw_inset_3d_rectangle(rectangleX,pstyle->_001GetColor(color_border_hover),pstyle->_001GetColor(color_border_hover));

            //rectangleX.deflate(1,1);

            pgraphics->fill_rectangle(rectangleX, get_color(pstyle, e_element_background, e_state_pressed));

         }
         else
         {

            pgraphics->fill_rectangle(rectangleX, get_color(pstyle, e_element_background));

         }

      }


      if (!(m_pimage->is_set() && m_pimage->area() > 0))
         return;

      ASSERT(m_pimage->is_set() && m_pimage->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image::image_pointer pimage = m_pimage;

      if (pimage->area() > 0 && rectangleX.area() > 0)
      {

         ::rectangle_i32 rectangleAspect;

         rectangleAspect.left() = 0;

         rectangleAspect.top() = 0;

         double dW = (double)rectangleX.width() / (double)pimage->width();

         double dH = (double)rectangleX.height() / (double)pimage->height();

         double dMin = maximum(minimum(dW, dH), 1.0);

         rectangleAspect.right() = (::i32) (pimage->width() * dMin);

         rectangleAspect.bottom() = (::i32) (pimage->height() * dMin);

         rectangleAspect.Align(e_align_center, rectangleX);

         {

            ::image::image_source imagesource(pimage, ::rectangle_f64(pimage->get_size()));

            rectangle_f64 rectangle(rectangleX);

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void still::set_still_type(enum_still estill)
   {

      if (m_estill == estill)
      {

         return;

      }

      on_exit_still_style(m_estill);

      m_estill = estill;

      on_enter_still_style(m_estill);

   }


   enum_still still::get_still_type() const
   {

      return m_estill;

   }



   void still::on_enter_still_style(enum_still estill)
   {



   }


   void still::on_exit_still_style(enum_still estill)
   {

   }


   ::image::icon * still::still_get_icon()
   {

      return m_estill == e_still_icon ? m_picon : nullptr;

   }



   bool still::LoadBitmaps(::payload payload, ::payload varSel, ::payload varFocus, ::payload varDisabled, ::payload varHover)
   {

      set_still_type(e_still_image);

      if (!payload.is_empty())
      {

         m_pimage = image()->get_image(payload);

      }

      //if (!varSel.is_empty())
      //{

      //   m_pbitmap->m_pimageSel->create(this);

      //   m_pbitmap->m_pimageSel->load_image(varSel);

      //}


      //if (!varFocus.is_empty())
      //{

      //   m_pbitmap->m_pimageFocus->create(this);

      //   m_pbitmap->m_pimageFocus->load_image(varFocus);

      //}


      //if (!varDisabled.is_empty())
      //{

      //   m_pbitmap->m_pimageDisabled->create(this);

      //   m_pbitmap->m_pimageDisabled->load_image(varDisabled);

      //}


      //if (!varHover.is_empty())
      //{

      //   m_pbitmap->m_pimageHover->create(this);

      //   m_pbitmap->m_pimageHover->load_image(varHover);

      //}

      return m_pimage->is_set() && m_pimage->area() > 0;

   }






   void still::pre_translate_message(::message::message * pmessage)
   {

      // Relay events from this still to the tool tip tool handler
      BaseToolTipRelayEvent(pmessage);

      return ::user::interaction::pre_translate_message(pmessage);

   }


   ::item_pointer still::on_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      ::collection::index iItem = -1;

      if(!m_ptextouta || ::not_found(iItem = m_ptextouta->hit_test(point, ezorder)))
      {

         auto pitemNone = __allocate ::item(e_element_none);

         return pitemNone;

      }

      return __allocate ::item(e_element_client);

   }


   void still::BaseToolTipGetRect(::rectangle_i32 & rectangle)
   {

      // use window client rectangle_i32 as the tool rectangle_i32
      rectangle = this->rectangle();

   }


   i32 still::BaseToolTipGetIndex()
   {
      // use window dialog control atom as the index
      return GetDlgCtrlId().as_i32();
   }



   void still::BaseToolTipRelayEvent(class ::message::message *)
   {

   }





   void still::set_stock_icon(enum_stock_icon estockicon)
   {

      m_estockicon = estockicon;

   }


   enum_stock_icon still::get_stock_icon()
   {

      return m_estockicon;

   }


   bool still::has_link()
   {

      return m_strLink.has_char();

   }


} // namespace user




