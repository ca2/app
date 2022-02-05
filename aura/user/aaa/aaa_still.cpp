#include "framework.h"
#include "axis/user/_user.h"


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

      MESSAGE_LINK(e_message_create, pchannel, this, &still::on_message_create);
      //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &still::on_message_left_button_down);
      //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &still::on_message_left_button_up);
      //MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &still::on_message_middle_button_down);
      //MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &still::on_message_middle_button_up);
      //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &still::on_message_mouse_move);
      //MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &still::on_message_mouse_leave);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &still::on_message_key_down);

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

         string strText;

         get_window_text(strText);

         ::rectangle rectangleClient;

         get_client_rect(rectangleClient);

         //::rectangle rectangleMargin(2, 2,2, 2);

//         ::rectangle rectangleBorder(2, 2,2, 2);

  //       rectangleClient.deflate(rectangleMargin);

    //     rectangleClient.deflate(rectangleBorder);

         //if(pstyle == nullptr)
         //{

         //   if(m_iHover == 0 || psession->m_puiLastLButtonDown == this)
         //   {

         //      pgraphics->fill_rectangle(rectangleClient,argb(255,127,127,127));

         //      pgraphics->set_text_color(argb(255,0,100,255));

         //   }
         //   else
         //   {

         //      pgraphics->fill_rectangle(rectangleClient,argb(255,127,127,127));

         //      pgraphics->set_text_color(argb(255,0,0,0));

         //   }

         //}
         //else
         {
            if (!is_window_enabled())
            {

               pgraphics->fill_rectangle(rectangleClient, argb(255, 192, 192, 192));

               pgraphics->set_text_color(argb(255, 160, 160, 160));

            }
            else if (should_hover() && (m_itemHover.is_set() || psession->m_puiLastLButtonDown == this))
            {

               pgraphics->fill_rectangle(rectangleClient, argb(255, 200, 200, 230));

               pgraphics->set_text_color(argb(255, 80, 80, 180));

            }
            else
            {

               //pgraphics->draw_inset_3d_rectangle(rectangleClient,pstyle->_001GetColor(color_border),pstyle->_001GetColor(color_border));

               //rectangleClient.deflate(1,1);

               pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

               pgraphics->set_text_color(argb(255, 0, 0, 0));

            }

         }

         ::rectangle rectanglePadding(0, 0, 0, 0);

         rectangleClient.deflate(rectanglePadding);

         if (m_estockicon == stock_icon_none)
         {

            int iDrawTextFlags =  get_int(pstyle, ::user::int_edit_draw_text_flags,e_align_left_center, e_draw_text_single_line);

            if(m_pfont)
            {

               pgraphics->set(m_pfont);

            }
            else
            {

               pgraphics->set_font(this, ::e_element_none);

            }

            pgraphics->draw_text(strText, rectangleClient, iDrawTextFlags);

         }
         else
         {

            //auto pbrush = __create < ::draw2d::brush >();

            //pbrush->create_solid(pgraphics->get_current_pen()->m_cr);

            //pgraphics->set(pbrush);

            auto ppen = __create < ::draw2d::pen > ();

            ppen->m_color = pgraphics->get_current_brush()->m_color;

            ppen->m_dWidth = 1.0;

            pgraphics->set(ppen);

            ::rectangle rectangleIcon(rectangleClient);

            rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

            pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

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

   //   //      topic.m_id = ::id_click;

   //   //      route(&topic);

   //   //      pmessage->m_bRet = topic.m_bRet;

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
   //   //      topic.m_id = ::id_mouse_enter;
   //   //      get_parent()->send_message(
   //   //      e_message_event, 0, (LPARAM)&ev);
   //   //      //               m_bActionHover = true;
   //   //   }
   //   //   else if (iHover == -1)
   //   //   {
   //   //      ::topic topic;
   //   //      topic.m_puserinteraction = this;
   //   //      topic.m_id = ::id_mouse_leave;
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
   //   //   topic.m_id = ::id_mouse_leave;
   //   //   if (get_parent() != nullptr)
   //   //   {
   //   //      get_parent()->send_message(e_message_event, 0, (LPARAM)&ev);
   //   //   }
   //   //}

   //   //pusermessage->m_bRet = false;

   //}

   //void still::on_hit_test(::item & item)
   //{

   //   return control::hit_test(pmouse);

   //   //::rectangle rectangleWindow;
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


   ::size still::calc_text_size()
   {

      auto pgraphics = ::draw2d::create_memory_graphics();

      if (pgraphics.is_null())
      {

         return nullptr;

      }

      pgraphics->set_font(this, ::e_element_none);

      string strText(m_strWindowText);

      const ::size & size = pgraphics->get_text_extent(strText);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size sizeTotal;

      sizeTotal.cx = size.cx;

      sizeTotal.cy = tm.tmHeight;

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

         ::rectangle rectangle(0, 0, 0, 0);

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

         auto sizeTotal = calc_text_size();

         sizeTotal.cx = (::i32)(sizeTotal.cx * 1.6);

         sizeTotal.cy = (::i32)(sizeTotal.cy * 1.4);

         layout().sketch() = sizeTotal;

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


//   ::enum_check still::_001GetCheck()
//   {
//
//      return check::_001GetCheck();
//
//   }


   void still::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

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

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);


      ::size sizeText = calc_text_size();

      ::rectangle rectangle;

      rectangle.left = rectangleClient.left + (rectangleClient.width() - sizeText.cx) / 2;

      rectangle.top = rectangleClient.top + (rectangleClient.height() - sizeText.cy) / 2;

      rectangle.right = rectangle.left + sizeText.cx;

      rectangle.bottom = rectangle.top + sizeText.cy;

      m_rectangleText = rectangle;

   }


   bool still::create_control(class control_descriptor * pdescriptor)
   {

      return interaction::create_control(pdescriptor);

   }


   ::write_text::font_pointer still::get_font(style * pstyle, enum_element eelement, estate estate) const
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



      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

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

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         class imaging & imaging = ::aura::get_system()->imaging();

         imaging.color_blend(
         pgraphics,
         rectangleClient,
         crBk,
         127);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, crBk);

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

      if (rectangle.is_set())
      {

         pgraphics->draw_rectangle(rectangleClient, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectangleClient.left += 3;
      rectangleClient.top += 3;
      ::rectangle rectangleText = m_rectangleText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pimage->is_ok())
      {
         ::rectangle rectangleDib;
         rectangleDib = m_rectangleText;
         rectangleDib.bottom = minimum(rectangleText.top + m_pimage->height(), rectangleText.bottom);
         rectangleDib.right = minimum(rectangleText.left + m_pimage->width(), rectangleText.right);
         //m_pimage->to(pgraphics, rectangleDib);
         m_pimage->bitmap_blend(pgraphics, rectangleDib);
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
      else if (m_itemHover.is_set())
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

      pgraphics->set_font(this, ::e_element_none);

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

         ::topic topic;
         topic.m_puserinteraction = this;
         topic.m_id = ::id_click;
         topic.m_pmessage = pmessage;
         route(&topic);
         pmessage->m_bRet = topic.m_bRet;
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

      ::rectangle rectangleClient;
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
         else if (m_itemHover.is_set() || is_left_button_pressed())
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

         ::rectangle rectangleAspect;

         rectangleAspect.left = 0;

         rectangleAspect.top = 0;

         double dW = (double)rectangleClient.width() / (double)pimage->width();

         double dH = (double)rectangleClient.height() / (double)pimage->height();

         double dMin = maximum(minimum(dW, dH), 1.0);

         rectangleAspect.right = (::i32) (pimage->width() * dMin);

         rectangleAspect.bottom = (::i32) (pimage->height() * dMin);

         rectangleAspect.Align(e_align_center, rectangleClient);

        pgraphics->draw(rectangleClient, pimage->g(), ::rectangle(pimage->get_size()));

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

         m_pimage = load_image(payload);

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
      // use window client rectangle as the tool rectangle
      get_client_rect(prect);

   }

   i32 still::BaseToolTipGetIndex()
   {
      // use window dialog control atom as the index
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


   bool still::should_hover()
   {

      return has_link();

   }


   bool still::has_link()
   {

      return m_strLink.has_char();

   }


} // namespace user




