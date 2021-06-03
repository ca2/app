#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   still::still()
   {

      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_iClick = 0;

      m_flagNonClient -= non_client_background;
      m_flagNonClient -= non_client_focus_rect;

   }


   still::~still()
   {

   }


   void still::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &still::on_message_create);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &still::_001OnKeyDown);

   }


   void still::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

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

         ::rectangle_f64 rectClient;

         rectClient = get_client_rect();

         auto estate = get_user_state();

         auto color = get_color(pstyle, ::user::e_element_text, estate);

         pgraphics->set_text_color(color);

         auto rectPadding = get_padding(pstyle);

         rectClient.deflate(rectPadding);

         if (m_estockicon != stock_icon_none)
         {

            ::draw2d::pen_pointer pen(e_create);

            pen->m_color = pgraphics->get_current_brush()->m_color;

            pen->m_dWidth = 1.0;

            pgraphics->set(pen);

            ::rectangle_i32 rectIcon(rectClient);

            rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

            pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         }
         else
         {

            ::e_align ealign = (enum_align)get_int(pstyle, ::user::e_int_edit_text_align, ::user::e_state_none, e_align_left_center);

            ::e_draw_text edrawtext = (enum_draw_text)get_int(pstyle, ::user::e_int_edit_draw_text_flags, ::user::e_state_none, e_draw_text_single_line);

            pgraphics->set_font(this, ::user::e_element_none);

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->draw_text(strText, rectClient, ealign, edrawtext);

         }

      }

   }


   //void still::on_message_left_button_down(::message::message * pmessage)
   //{

   //   __pointer(::message::mouse) pmouse(pmessage);

   //   pmessage->previous();

   //   auto point = screen_to_client(pmouse->m_point);

   //   if (hit_test(pmouse->)
   //   {

   //      if (!simple_process_system_message(pmessage, ::user::e_event_button_down))
   //      {

   //         psession->m_puiLastLButtonDown = this;

   //         pmouse->m_bRet = true;

   //      }

   //   }

   //}


   //void still::on_message_middle_button_down(::message::message * pmessage)
   //{

   //   __pointer(::message::mouse) pmouse(pmessage);

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point_i32 point = pmouse->m_point;

   //   _001ScreenToClient(point);

   //   if (hit_test(point, eelement) >= 0)
   //   {

   //      if (!simple_process_system_message(pmessage, ::user::e_event_m_button_down))
   //      {

   //         //psession->m_puiLastLButtonDown = this;

   //         pmouse->m_bRet = true;

   //      }

   //   }

   //}


   //void still::on_message_middle_button_up(::message::message * pmessage)
   //{

   //   __pointer(::message::mouse) pmouse(pmessage);

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point_i32 point = pmouse->m_point;

   //   _001ScreenToClient(point);

   //   if (hit_test(point, eelement) >= 0)
   //   {

   //      if (!simple_process_system_message(pmessage, ::user::e_event_m_button_up))
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

   //   //__pointer(::message::mouse) pmouse(pmessage);

   //   //enum_element eelement;

   //   //::point_i32 point = pmouse->m_point;

   //   //_001ScreenToClient(point);

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

   //   //      ::user::control_event ev;

   //   //      ev.m_puie = this;

   //   //      ev.m_eevent = ::user::e_event_button_clicked;

   //   //      on_control_event(&ev);

   //   //      pmessage->m_bRet = ev.m_bRet;

   //   //      if (!pmessage->m_bRet)
   //   //      {

   //   //         ::message::command command;

   //   //         command.m_id = m_id;

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

   //   //__pointer(::message::mouse) pmouse(pmessage);

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
   //   //      ::user::control_event ev;
   //   //      ev.m_puie = this;
   //   //      ev.m_eevent = ::user::e_event_mouse_enter;
   //   //      get_parent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //               m_bActionHover = true;
   //   //   }
   //   //   else if (iHover == -1)
   //   //   {
   //   //      ::user::control_event ev;
   //   //      ev.m_puie = this;
   //   //      ev.m_eevent = ::user::e_event_mouse_leave;
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
   //   //   ::user::control_event ev;
   //   //   ev.m_puie = this;
   //   //   ev.m_eevent = ::user::e_event_mouse_leave;
   //   //   if (get_parent() != nullptr)
   //   //   {
   //   //      get_parent()->send_message(e_message_event, 0, (LPARAM)&ev);
   //   //   }
   //   //}

   //   //pusermessage->m_bRet = false;

   //}

   //void still::on_hit_test(::user::item & item)
   //{

   //   return control::hit_test(pmouse);

   //   //::rectangle_i32 rectWindow;
   //   //get_window_rect(rectWindow);
   //   //if (rectWindow.contains(point))
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

         pgraphics = pdraw2d->create_memory_graphics();

      }

      pgraphics->set_font(this, ::user::e_element_none);

      string strText(m_strWindowText);

      auto size = pgraphics->GetTextExtent(strText);

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

         pgraphics->set_font(this, ::user::e_element_none);

         string str;

         get_window_text(str);

         auto size = pgraphics->GetTextExtent(str);

         ::rectangle_i32 rectangle(0, 0, 0, 0);

         rectangle.right = ::i32(size.cx * 1.6);
         rectangle.bottom = ::i32(size.cy * 1.4);

         layout().sketch() = rectangle.size();

      }
      else if (m_estyle == style_image)
      {

         auto size = m_pimage->size();

         layout().sketch() = size;

      }
      else
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         layout().sketch() = sizeTotal;

      }

   }

   //void still::_001SetButtonText(const char * pcszText)

   //{
   //   m_istrButtonText = pcszText;

   //}



   void still::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      check::_001SetCheck(echeck, context);

   }


   void still::on_message_create(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      sync_style();

      //if (m_pdescriptor->m_setStyle["vertical-align"] == "center")
      //{


      //}


      if (m_id.has_char())
      {

         string strText = _(m_id);

         set_window_text(strText);

      }

      if (m_estyle == style_none)
      {

         set_button_style(style_text);

      }


   }


   void still::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      ::size_f64 sizeText = _001CalculateFittingSize(pgraphics);

      ::rectangle_i32 rectangle;

      rectangle.left = (::i32) (rectClient.left + (rectClient.width() - sizeText.cx) / 2);

      rectangle.top = (::i32) (rectClient.top + (rectClient.height() - sizeText.cy) / 2);

      rectangle.right = (::i32) (rectangle.left + sizeText.cx);

      rectangle.bottom = (::i32) (rectangle.top + sizeText.cy);

      m_rectText = rectangle;

   }


   //bool still::create_interaction(::user::interaction * pinteractionParent, const ::id & id)
   //{

   //   return interaction::create_interaction(pinteractionParent, id);

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

      //if(pstyle == nullptr)
      //   return;



      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      color32_t crBk;
      if (!is_window_enabled())
      {
         // Backround Disabled
         crBk = argb(255, 192, 192, 192);
      }
      else if (is_left_button_pressed())
      {
         // Backround Pressed
         crBk = argb(255, 192, 192, 250);
      }
      else if (m_itemHover.is_set())
      {
         crBk = argb(255, 220, 220, 250);
      }
      else
      {
         crBk = argb(255, 127, 127, 250);
      }

      auto pstyle = get_style(pgraphics);

      auto psystem = m_psystem->m_paurasystem;

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->color_blend(rectClient, crBk, 127);

      }
      else
      {

         pgraphics->fill_rectangle(rectClient, crBk);

      }


      color32_t crBorder;
      if (!is_window_enabled())
      {
         crBorder = argb(255, 127, 127, 127);
      }
      else if (is_left_button_pressed())
      {
         crBorder = argb(255, 255, 255, 255);
      }
      else if (m_itemHover.is_set())
      {
         crBorder = argb(255, 100, 100, 200);
      }
      else
      {
         crBorder = argb(255, 10, 10, 100);
      }

      auto rectangle = get_border(pstyle);

      if (rectangle.is_ok())
      {

         pgraphics->draw_rectangle(rectClient, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectClient.left += 3;
      rectClient.top += 3;
      ::rectangle_i32 rectText = m_rectText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pimage->is_ok())
      {
         ::rectangle_i32 rectDib;
         rectDib = m_rectText;
         rectDib.bottom = minimum(rectText.top + m_pimage->height(), rectText.bottom);
         rectDib.right = minimum(rectText.left + m_pimage->width(), rectText.right);
         //m_pimage->to(pgraphics, rectDib);
         m_pimage->bitmap_blend(pgraphics, rectDib);
         rectText.left += m_pimage->width();
      }


      ::draw2d::brush_pointer brushText(e_create);


      if (!is_window_enabled())
      {

         //         pgraphics->set_text_color(pstyle->m_colorTextDisabled);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_disabled));

      }
      else if (is_left_button_pressed())
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextPress);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_pressed));
      }
      else if (m_itemHover.is_set())
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextHover);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_hover));
      }
      else
      {
         //         pgraphics->set_text_color(pstyle->m_colorTextNormal);
         brushText->create_solid(get_color(pstyle, e_element_text));
      }

      pgraphics->set(brushText);

      string strText(get_window_text());

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->draw_text(strText, rectText, e_align_top_left);

   }


   bool still::keyboard_focus_is_focusable() const
   {

      //return is_window_enabled() && is_window_visible();
      return false;

   }


   void still::_001OnKeyDown(::message::message * pmessage)
   {

      __pointer(::message::key) pkey(pmessage);

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::e_event_button_clicked;
         ev.m_pmessage = pmessage;
         on_control_event(&ev);
         pmessage->m_bRet = ev.m_bRet;
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

      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);


      //if (pstyle == nullptr)
      //{

      //   if (m_iHover == 0 || psession->m_puiLastLButtonDown == this)
      //   {

      //      pgraphics->fill_rectangle(rectClient, argb(255, 127, 127, 127));

      //   }
      //   else
      //   {

      //      pgraphics->fill_rectangle(rectClient, argb(255, 127, 127, 127));

      //   }

      //}
      //else

      auto pstyle = get_style(pgraphics);

      {
         if (!is_window_enabled())
         {

            pgraphics->fill_rectangle(rectClient, get_color(pstyle, e_element_background, e_state_disabled));

         }
         else if (m_itemHover.is_set() || is_left_button_pressed())
         {

            //pgraphics->draw3d_rect(rectClient,pstyle->_001GetColor(color_border_hover),pstyle->_001GetColor(color_border_hover));

            //rectClient.deflate(1,1);

            pgraphics->fill_rectangle(rectClient, get_color(pstyle, e_element_background, e_state_pressed));

         }
         else
         {

            pgraphics->fill_rectangle(rectClient, get_color(pstyle, e_element_background));

         }

      }


      if (!(m_pimage->is_set() && m_pimage->area() > 0))
         return;

      ASSERT(m_pimage->is_set() && m_pimage->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pimage;

      if (pimage->area() > 0 && rectClient.area() > 0)
      {

         ::rectangle_i32 rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double)rectClient.width() / (double)pimage->width();

         double dH = (double)rectClient.height() / (double)pimage->height();

         double dMin = maximum(minimum(dW, dH), 1.0);

         rectAspect.right = (::i32) (pimage->width() * dMin);

         rectAspect.bottom = (::i32) (pimage->height() * dMin);

         rectAspect.Align(e_align_center, rectClient);

         pgraphics->stretch(rectClient, pimage->g(), ::rectangle_i32(pimage->get_size()));

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


   void still::BaseToolTipGetRect(RECTANGLE_I32 * prectangle)

   {
      // use window client rectangle_i32 as the tool rectangle_i32
      get_client_rect(prectangle);

   }

   i32 still::BaseToolTipGetIndex()
   {
      // use window dialog control id as the index
      return (i32)GetDlgCtrlId();
   }



   void still::BaseToolTipRelayEvent(class ::message::message *)
   {

   }





   void still::set_stock_icon(e_stock_icon eicon)
   {

      m_estockicon = eicon;

   }


   e_stock_icon still::get_stock_icon()
   {

      return m_estockicon;

   }


   bool still::has_link() const
   {

      return m_strLink.has_char();

   }


} // namespace user




