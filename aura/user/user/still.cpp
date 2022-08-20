#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_component.h"
#endif
#include "aura/graphics/write_text/text_out_array.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/context_image.h"


namespace user
{


   still::still()
   {

      m_etextwrap = e_text_wrap_word_then_character;

      m_ptextouta = nullptr;
      m_estockicon = e_stock_icon_none;
      m_estyle = style_none;
      m_iClick = 0;
      m_ealignText = e_align_center;

      m_flagNonClient -= non_client_background;
      m_flagNonClient -= non_client_focus_rect;
      
      //m_bEatsDoubleClick = false;

   }


   still::~still()
   {


      ::release(m_ptextouta);

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


   void still::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if (m_pstillappearance)
      //{

      //   m_pstillappearance->_001OnDraw(pgraphics);

      //   return;

      //}

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      auto pstyle = get_style(pgraphics);

      if (m_estyle == style_image)
      {

         _001OnDrawImage(pgraphics);

      }
      else
      {

         auto psession = get_session();

         string strText;

         get_window_text(strText);

         ::rectangle_f64 rectangleClient;

         rectangleClient = get_client_rect();

         auto estate = get_user_state();

         auto color = get_color(pstyle, ::e_element_text, estate);

         pgraphics->set_text_color(color);

         auto rectanglePadding = get_padding(pstyle);

         rectangleClient.deflate(rectanglePadding);

         if (m_estockicon != e_stock_icon_none)
         {

            auto ppen = __create < ::draw2d::pen > ();

            ppen->m_color = pgraphics->get_current_brush()->m_color;

            ppen->m_dWidth = 1.0;

            pgraphics->set(ppen);

            ::rectangle_i32 rectangleIcon(rectangleClient);

            rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

            pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         }
         else
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw(*m_ptextouta);

            //pgraphics->draw_text(strText, rectangleClient, ealign, edrawtext);

            //m_rectangleTextBoundingBox.left = 0;

            //m_rectangleTextBoundingBox.top = 0;

            //m_rectangleTextBoundingBox.set_size(pgraphics->get_text_extent(strText));

            //m_rectangleTextBoundingBox.Align(ealign, rectangleClient);

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

   //   screen_to_client(point);

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

   //   screen_to_client(point);

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

   //   //screen_to_client(point);

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

   //   //__pointer(::user::message) pusermessage(pmessage);
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

   //::item_pointer still::on_hit_test(const ::point_i32 &point)
   //{

   //   return control::hit_test(pmouse);

   //   //::rectangle_i32 rectangleWindow;
   //   //get_window_rect(rectangleWindow);
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


   ::size_f64 still::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      if (pgraphics.is_null())
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         pgraphics = pdraw2d->create_memory_graphics(this);

      }

      pgraphics->set_font(this, ::e_element_none);

      string strText(m_strWindowText);

      auto size = pgraphics->get_text_extent(strText);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size_f64 sizeTotal;

      sizeTotal.cx = size.cx;

      sizeTotal.cy = tm.get_line_spacing();

      return sizeTotal;

   }

   


   void still::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_estyle == style_text)
      {

         pgraphics->set_font(this, ::e_element_none);

         string str;

         get_window_text(str);

         auto size = pgraphics->get_text_extent(str);

         ::rectangle_i32 rectangle(0, 0, 0, 0);

         rectangle.right = ::i32(size.cx * 1.6);
         rectangle.bottom = ::i32(size.cy * 1.4);

         const_layout().sketch().size() = rectangle.size();

      }
      else if (m_estyle == style_image)
      {

         auto size = m_pimage->size();

         set_size(size);

      }
      else
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         set_size(sizeTotal);

      }

   }

   //void still::_001SetButtonText(const ::string & pcszText)

   //{
   //   m_istrButtonText = pcszText;

   //}



   void still::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      check::_001SetCheck(echeck, context);

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

         string strText = _(m_atom);

         set_window_text(strText);

      }

      if (m_estyle == style_none)
      {

         set_button_style(style_text);

      }


   }


   void still::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      ::size_f64 sizeText = _001CalculateFittingSize(pgraphics);

      ::rectangle_i32 rectangle;

      rectangle.left = (::i32) (rectangleClient.left + (rectangleClient.width() - sizeText.cx) / 2);

      rectangle.top = (::i32) (rectangleClient.top + (rectangleClient.height() - sizeText.cy) / 2);

      rectangle.right = (::i32) (rectangle.left + sizeText.cx);

      rectangle.bottom = (::i32) (rectangle.top + sizeText.cy);

      m_rectangleText = rectangle;

      string strText;

      get_window_text(strText);

      auto pstyle = get_style(pgraphics);

      ::e_align ealign = (enum_align)get_int(pstyle, ::user::e_int_edit_text_align, ::user::e_state_none, m_ealignText);

      ::e_draw_text edrawtext = (enum_draw_text)get_int(pstyle, ::user::e_int_edit_draw_text_flags, ::user::e_state_none, e_draw_text_none);

      ::enum_text_wrap etextwrap = m_etextwrap;

      if(::is_null(m_ptextouta))
      {

         m_ptextouta = new write_text::text_out_array;

      }

      m_ptextouta->text_outa().erase_all();

      __pointer(::write_text::font) pfont;
      
      if (m_pfont)
      {

         pfont = m_pfont;

      }
      else
      {

         pfont = get_font(pstyle, ::e_element_none);

      }

      pgraphics->create_simple_multiline_layout(*m_ptextouta, strText, rectangleClient, pfont, ealign, etextwrap);

   }


   //bool still::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   return interaction::create_interaction(pinteractionParent, atom);

   //}


   ::write_text::font_pointer still::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      if(m_pfont)
      {

         return m_pfont;

      }

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void still::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

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

      auto psystem = m_psystem->m_paurasystem;

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->fill_rectangle(rectangleClient, colorBackground & 0.5_opacity);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, colorBackground);

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

         pgraphics->draw_inset_rectangle(rectangleClient, colorBorder);

      }

//      rectangleClient.left += 3;
//
//      rectangleClient.top += 3;

      ::rectangle_i32 rectangleText = m_rectangleText;

      //      string str = utf8_to_unicode(str);

      if (m_pimage->is_ok())
      {
         ::rectangle_i32 rectangleDib;
         rectangleDib = m_rectangleText;
         rectangleDib.bottom = minimum(rectangleText.top + m_pimage->height(), rectangleText.bottom);
         rectangleDib.right = minimum(rectangleText.left + m_pimage->width(), rectangleText.right);
         //m_pimage->to(pgraphics, rectangleDib);

         {

            image_source imagesource(m_pimage);

            auto rectangle = rectangleDib;

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

         rectangleText.left += m_pimage->width();

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


   bool still::keyboard_focus_is_focusable() const
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

      string strText;

      get_window_text(strText);

      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);


      //if (pstyle == nullptr)
      //{

      //   if (m_iHover == 0 || psession->m_puiLastLButtonDown == this)
      //   {

      //      pgraphics->fill_rectangle(rectangleClient, argb(255, 127, 127, 127));

      //   }
      //   else
      //   {

      //      pgraphics->fill_rectangle(rectangleClient, argb(255, 127, 127, 127));

      //   }

      //}
      //else

      auto pstyle = get_style(pgraphics);

      {
         if (!is_window_enabled())
         {

            pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, e_element_background, e_state_disabled));

         }
         else if ((m_pitemHover && m_pitemHover->is_set()) || is_left_button_pressed())
         {

            //pgraphics->draw_inset_3d_rectangle(rectangleClient,pstyle->_001GetColor(color_border_hover),pstyle->_001GetColor(color_border_hover));

            //rectangleClient.deflate(1,1);

            pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, e_element_background, e_state_pressed));

         }
         else
         {

            pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, e_element_background));

         }

      }


      if (!(m_pimage->is_set() && m_pimage->area() > 0))
         return;

      ASSERT(m_pimage->is_set() && m_pimage->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pimage;

      if (pimage->area() > 0 && rectangleClient.area() > 0)
      {

         ::rectangle_i32 rectangleAspect;

         rectangleAspect.left = 0;

         rectangleAspect.top = 0;

         double dW = (double)rectangleClient.width() / (double)pimage->width();

         double dH = (double)rectangleClient.height() / (double)pimage->height();

         double dMin = maximum(minimum(dW, dH), 1.0);

         rectangleAspect.right = (::i32) (pimage->width() * dMin);

         rectangleAspect.bottom = (::i32) (pimage->height() * dMin);

         rectangleAspect.Align(e_align_center, rectangleClient);

         {

            image_source imagesource(pimage, ::rectangle_f64(pimage->get_size()));

            rectangle_f64 rectangle(rectangleClient);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void still::set_button_style(e_style estyle)
   {

      if (m_estyle == estyle)
         return;

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void still::on_enter_button_style(e_style estyle)
   {



   }


   void still::on_exit_button_style(e_style estyle)
   {

   }





   bool still::LoadBitmaps(::payload payload, ::payload varSel, ::payload varFocus, ::payload varDisabled, ::payload varHover)
   {

      set_button_style(style_image);

      if (!payload.is_empty())
      {

         auto pcontext = m_pcontext->m_pauracontext;

         auto pcontextimage = pcontext->context_image();

         m_pimage = pcontextimage->get_image(payload);

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


   ::item_pointer still::on_hit_test(const ::point_i32 & point)
   {

      auto iItem = m_ptextouta->hit_test(point);

      if (iItem < 0)
      {

         auto pitemNone = __new(::item(e_element_none));

         return pitemNone;

      }

      return __new(::item(e_hit_test_client));

   }


   void still::BaseToolTipGetRect(RECTANGLE_I32 * prectangle)
   {

      // use window client rectangle_i32 as the tool rectangle_i32
      get_client_rect(prectangle);

   }

   i32 still::BaseToolTipGetIndex()
   {
      // use window dialog control atom as the index
      return (i32)GetDlgCtrlId();
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


   bool still::has_link() const
   {

      return m_strLink.has_char();

   }


} // namespace user




