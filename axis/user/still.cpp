#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif


namespace user
{


   still::still()
   {

      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_iClick = 0;

   }


   still::~still()
   {

      //if (m_pmenuitemThis.is_set())
      //{

      //   m_pmenuitemThis->m_puserinteraction = nullptr;
      //   m_pmenuitemThis->m_pmenu = nullptr;

      //}

   }


   void still::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &still::_001OnCreate);
      //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &still::_001OnLButtonDown);
      //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &still::_001OnLButtonUp);
      //MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &still::_001OnMButtonDown);
      //MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &still::_001OnMButtonUp);
      //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &still::_001OnMouseMove);
      //MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &still::_001OnMouseLeave);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &still::_001OnKeyDown);

   }


   //::e_state still::get_user_state()
   //{


   //}

   void still::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      if (m_estyle == style_image)
      {

         _001OnDrawImage(pgraphics);

      }
      else
      {

         auto psession = Session;

         string strText;

         get_window_text(strText);

         ::rectd rectClient;

         rectClient = get_client_rect();

         auto estate = get_user_state();

         auto color = get_color(pstyle, ::user::e_element_text, estate);

         pgraphics->set_text_color(color);

         //if (!is_window_enabled())
         //{

         //   pgraphics->fill_rect(rectClient, ARGB(255, 192, 192, 192));

         //   pgraphics->set_text_color(ARGB(255, 160, 160, 160));

         //}
         //else if (should_hover() && (m_itemHover.is_set() || psession->m_puiLastLButtonDown == this))
         //{

         //   pgraphics->fill_rect(rectClient, ARGB(255, 200, 200, 230));

         //   pgraphics->set_text_color(ARGB(255, 80, 80, 180));

         //}
         //else
         //{

         //   pgraphics->fill_rect(rectClient, ARGB(255, 255, 255, 255));

         //   pgraphics->set_text_color(ARGB(255, 0, 0, 0));

         //}

         auto rectPadding = get_padding(pstyle);

         rectClient.deflate(rectPadding);

         if (m_estockicon != stock_icon_none)
         {

            ::draw2d::pen_pointer pen(e_create);

            pen->m_color = pgraphics->get_current_brush()->m_color;

            pen->m_dWidth = 1.0;

            pgraphics->set(pen);

            ::rect rectIcon(rectClient);

            rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

            pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         }
         else
         {

            ::e_align ealign = (enum_align)get_int(pstyle, ::user::e_int_edit_text_align, ::e_align(e_align_left_center));

            ::e_draw_text edrawtext = (enum_draw_text)get_int(pstyle, ::user::e_int_edit_draw_text_flags, e_draw_text_single_line);

            pgraphics->set_font(this, ::user::e_element_none);

            pgraphics->draw_text(strText, rectClient, ealign, edrawtext);

         }

      }

   }


   //void still::_001OnLButtonDown(::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

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


   //void still::_001OnMButtonDown(::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point point = pmouse->m_point;

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


   //void still::_001OnMButtonUp(::message::message * pmessage)
   //{

   //   SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   pmessage->previous();

   //   enum_element eelement;

   //   ::point point = pmouse->m_point;

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

   //void still::_001OnLButtonUp(::message::message * pmessage)
   //{

   //   //SCAST_PTR(::message::mouse, pmouse, pmessage);

   //   //enum_element eelement;

   //   //::point point = pmouse->m_point;

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

   //   //         ::user::command command;

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


   //void still::_001OnMouseMove(::message::message * pmessage)
   //{

   //   //SCAST_PTR(::message::mouse, pmouse, pmessage);

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
   //   //      GetParent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //               m_bActionHover = true;
   //   //   }
   //   //   else if (iHover == -1)
   //   //   {
   //   //      ::user::control_event ev;
   //   //      ev.m_puie = this;
   //   //      ev.m_eevent = ::user::e_event_mouse_leave;
   //   //      GetParent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //             m_bActionHover = false;
   //   //   }
   //   //}
   //   //pmessage->m_bRet = false;

   //}


   //void still::_001OnMouseLeave(::message::message * pmessage)
   //{

   //   //SCAST_PTR(::message::base, pbase, pmessage);
   //   //index iOldHover = m_iHover;
   //   //m_iHover = -1;
   //   //if (iOldHover >= 0)
   //   //{
   //   //   set_need_redraw();
   //   //   ::user::control_event ev;
   //   //   ev.m_puie = this;
   //   //   ev.m_eevent = ::user::e_event_mouse_leave;
   //   //   if (GetParent() != nullptr)
   //   //   {
   //   //      GetParent()->send_message(e_message_event, 0, (LPARAM)&ev);
   //   //   }
   //   //}

   //   //pbase->m_bRet = false;

   //}

   //void still::on_hit_test(::user::item & item)
   //{

   //   return control::hit_test(pmouse);

   //   //::rect rectWindow;
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


   ::sized still::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      if (pgraphics.is_null())
      {

         pgraphics = ::draw2d::create_memory_graphics();

      }

      pgraphics->set_font(this, ::user::e_element_none);

      string strText(m_strWindowText);

      auto size = pgraphics->GetTextExtent(strText);

      ::draw2d::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::sized sizeTotal;

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

         ::rect rect(0, 0, 0, 0);

         rect.right = ::i32(size.cx * 1.6);
         rect.bottom = ::i32(size.cy * 1.4);

         layout().sketch() = rect.size();

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


//   ::enum_check still::_001GetCheck()
//   {
//
//      return check::_001GetCheck();
//
//   }


   void still::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      sync_style();

      if (m_pdescriptor->m_setStyle["vertical-align"] == "center")
      {


      }


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

      ::rect rectClient;

      get_client_rect(rectClient);

      ::sized sizeText = _001CalculateFittingSize(pgraphics);

      ::rect rect;

      rect.left = rectClient.left + (rectClient.width() - sizeText.cx) / 2;

      rect.top = rectClient.top + (rectClient.height() - sizeText.cy) / 2;

      rect.right = rect.left + sizeText.cx;

      rect.bottom = rect.top + sizeText.cy;

      m_rectText = rect;

   }


   bool still::create_control(class control_descriptor * pdescriptor)
   {

      return interaction::create_control(pdescriptor);

   }


   ::draw2d::font_pointer still::get_font(style * pstyle, enum_element eelement, estate estate) const
   {

      //if (pstyle)
      //{

      //   if (pstyle->m_pfontStill)
      //   {

      //      return pstyle->m_pfontStill;

      //   }

      //   if (pstyle->m_pfont)
      //   {

      //      return pstyle->m_pfont;

      //   }

      //}

      return nullptr;

   }


   void still::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if(pstyle == nullptr)
      //   return;



      ::rect rectClient;

      get_client_rect(rectClient);

      color32_t crBk;
      if (!is_window_enabled())
      {
         // Backround Disabled
         crBk = ARGB(255, 192, 192, 192);
      }
      else if (is_left_button_pressed())
      {
         // Backround Pressed
         crBk = ARGB(255, 192, 192, 250);
      }
      else if (m_itemHover.is_set())
      {
         crBk = ARGB(255, 220, 220, 250);
      }
      else
      {
         crBk = ARGB(255, 127, 127, 250);
      }

      auto pstyle = get_style(pgraphics);

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         class imaging & imaging = System.imaging();

         imaging.color_blend(
         pgraphics,
         rectClient,
         crBk,
         127);

      }
      else
      {

         pgraphics->fill_rect(rectClient, crBk);

      }


      color32_t crBorder;
      if (!is_window_enabled())
      {
         crBorder = ARGB(255, 127, 127, 127);
      }
      else if (is_left_button_pressed())
      {
         crBorder = ARGB(255, 255, 255, 255);
      }
      else if (m_itemHover.is_set())
      {
         crBorder = ARGB(255, 100, 100, 200);
      }
      else
      {
         crBorder = ARGB(255, 10, 10, 100);
      }

      auto rect = get_border(pstyle);

      if (rect.is_set())
      {

         pgraphics->draw_rect(rectClient, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectClient.left += 3;
      rectClient.top += 3;
      ::rect rectText = m_rectText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pimage->is_ok())
      {
         ::rect rectDib;
         rectDib = m_rectText;
         rectDib.bottom = min(rectText.top + m_pimage->height(), rectText.bottom);
         rectDib.right = min(rectText.left + m_pimage->width(), rectText.right);
         //m_pimage->to(pgraphics, rectDib);
         m_pimage->bitmap_blend(pgraphics, rectDib);
         rectText.left += m_pimage->width();
      }


      ::draw2d::brush_pointer brushText(e_create);


      if (!is_window_enabled())
      {

         //         pgraphics->set_text_color(pstyle->m_crTextDisabled);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_disabled));

      }
      else if (is_left_button_pressed())
      {
         //         pgraphics->set_text_color(pstyle->m_crTextPress);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_pressed));
      }
      else if (m_itemHover.is_set())
      {
         //         pgraphics->set_text_color(pstyle->m_crTextHover);
         brushText->create_solid(get_color(pstyle, e_element_text, e_state_hover));
      }
      else
      {
         //         pgraphics->set_text_color(pstyle->m_crTextNormal);
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

      SCAST_PTR(::message::key, pkey, pmessage);

      ::user::e_key iKey = pkey->m_ekey;

      if (iKey == ::user::key_return || iKey == ::user::key_space)
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

      ::rect rectClient;
      get_client_rect(rectClient);


      //if (pstyle == nullptr)
      //{

      //   if (m_iHover == 0 || psession->m_puiLastLButtonDown == this)
      //   {

      //      pgraphics->fill_rect(rectClient, ARGB(255, 127, 127, 127));

      //   }
      //   else
      //   {

      //      pgraphics->fill_rect(rectClient, ARGB(255, 127, 127, 127));

      //   }

      //}
      //else

      auto pstyle = get_style(pgraphics);

      {
         if (!is_window_enabled())
         {

            pgraphics->fill_rect(rectClient, get_color(pstyle, e_element_background, e_state_disabled));

         }
         else if (m_itemHover.is_set() || is_left_button_pressed())
         {

            //pgraphics->draw3d_rect(rectClient,pstyle->_001GetColor(color_border_hover),pstyle->_001GetColor(color_border_hover));

            //rectClient.deflate(1,1);

            pgraphics->fill_rect(rectClient, get_color(pstyle, e_element_background, e_state_pressed));

         }
         else
         {

            pgraphics->fill_rect(rectClient, get_color(pstyle, e_element_background));

         }

      }


      if (!(m_pimage->is_set() && m_pimage->area() > 0))
         return;

      ASSERT(m_pimage->is_set() && m_pimage->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pimage;

      if (pimage->area() > 0 && rectClient.area() > 0)
      {

         ::rect rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double)rectClient.width() / (double)pimage->width();

         double dH = (double)rectClient.height() / (double)pimage->height();

         double dMin = max(min(dW, dH), 1.0);

         rectAspect.right = (::i32) (pimage->width() * dMin);

         rectAspect.bottom = (::i32) (pimage->height() * dMin);

         rectAspect.Align(e_align_center, rectClient);

         pgraphics->stretch(rectClient, pimage->g(), ::rect(pimage->get_size()));

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

         m_pimage = Application.image().get_image(payload);

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


   void still::BaseToolTipGetRect(RECT32 * prect)

   {
      // use window client rect as the tool rect
      get_client_rect(prect);

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




