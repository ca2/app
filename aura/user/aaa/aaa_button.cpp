#include "framework.h"
#include "axis/user/_user.h"


namespace user
{


   button::button()
   {

      user_button_construct();

   }


   button::~button()
   {

      //if (m_pmenuitemThis.is_set())
      //{

      //   m_pmenuitemThis->m_puserinteraction = nullptr;
      //   //m_pmenuitemThis->m_pmenu = nullptr;

      //}

      ::acme::del(m_pbitmap);
      ::acme::del(m_plist);
      set_button_style(style_none);

   }


   void button::user_button_construct()
   {

      //m_erectMargin = rect_button_margin;
      //m_erectBorder = rect_button_border;
      //m_erectPadding = rect_button_padding;
      //m_eintTextAlign = int_button_draw_text_flags;


      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_pbitmap = nullptr;
      m_plist = nullptr;
      m_iClick = 0;
      //m_bIdBound = true;

   }


   ::write_text::font_pointer button::get_font(style * pstyle, enum_element eelement, estate estate) const
   {

      if (pstyle)
      {

         if (pstyle->m_pfontButton)
         {

            return pstyle->m_pfontButton;

         }

         if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   enum_translucency button::get_translucency(style * pstyle) const
   {

      if (pstyle)
      {

         if (pstyle->m_etranslucencyButton != e_translucency_undefined)
         {

            return pstyle->m_etranslucencyButton;

         }

      }

      return e_translucency_undefined;

   }



   void button::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create    , pchannel, this, &button::on_message_create);
      MESSAGE_LINK(e_message_key_down   , pchannel, this, &button::on_message_key_down);

      install_simple_ui_default_mouse_handling(pchannel);

   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_estyle == style_push)
      {

         _001OnButtonDrawPush(pgraphics);

      }
      else if (m_estyle == style_list)
      {

         _001OnButtonDrawList(pgraphics);

      }
      else if (m_estyle == style_bitmap)
      {

         _001OnButtonDrawBitmap(pgraphics);

      }
      else if (m_estyle == style_image_and_text)
      {

         _001OnButtonDrawImageAndText(pgraphics);

      }
      else
      {

         _001OnButtonDrawNormal(pgraphics);

      }

   }




   ::size button::calc_text_size()
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


   void button::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_estyle == style_simple)
      {

         pgraphics->set_font(this, ::e_element_none);

         string str;
         get_window_text(str);
         const ::size & size = pgraphics->get_text_extent(str);

         ::rectangle rectangle(0, 0, 0, 0);
         rectangle.right = ::i32(size.cx * 1.6);
         rectangle.bottom = ::i32(size.cy * 1.4);

         set_size(rectangle.size());

      }
      else if (m_estyle == style_bitmap)
      {

         ::size size = m_pbitmap->m_pimage->size();

         set_size(size);

      }
      else
      {

         ::size sizeTotal = calc_text_size();

         sizeTotal.cx = (::i32)(sizeTotal.cx * 1.6);

         sizeTotal.cy = (::i32)(sizeTotal.cy * 1.4);

         set_size(sizeTotal);

      }

   }

   //void button::_001SetButtonText(const ::string & pcszText)

   //{
   //   m_istrButtonText = pcszText;

   //}



   void button::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if (echeck != this->get_echeck())
      {

         check::_001SetCheck(echeck, context);

         set_need_redraw();

         post_redraw();

      }

   }


//   ::enum_check button::_001GetCheck()
//   {
//
//      return check::_001GetCheck();
//
//   }


   void button::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_estyle == style_none)
      {

         set_button_style(style_normal);

      }

      m_ppropertyCheck = fetch_property(m_atom, true);

      if (m_ppropertyCheck)
      {

         add_update_notification(m_ppropertyCheck);

      }

   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient, ::user::e_layout_design);

      ::size sizeText = calc_text_size();

      ::rectangle rectangle;

      rectangle.left = rectangleClient.left + (rectangleClient.width() - sizeText.cx) / 2;

      rectangle.top = rectangleClient.top + (rectangleClient.height() - sizeText.cy) / 2;

      rectangle.right = rectangle.left + sizeText.cx;

      rectangle.bottom = rectangle.top + sizeText.cy;

      m_rectangleText = rectangle;

   }


   bool button::create_control(class control_descriptor * pdescriptor)
   {

      return interaction::create_control(pdescriptor);


   }


   void button::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      color32_t crBk;

      if (!is_window_enabled())
      {

         // Disabled Background
         crBk = argb(255, 127, 127, 127);

      }
      else if (is_left_button_pressed() || echeck() == ::e_check_checked)
      {

         // Pressed Background
         crBk = argb(255, 127, 127, 127);

      }
      else if (::is_set(m_pitemHover))
      {

         // Hover Background
         crBk = argb(255, 80, 80, 80);

      }
      else
      {

         crBk = argb(255, 255, 255, 255);

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
      else if (is_left_button_pressed() || echeck() == ::e_check_checked)
      {

         crBorder = argb(255, 255, 255, 255);

      }
      else if (::is_set(m_pitemHover))
      {

         crBorder = argb(255, 100, 100, 200);

      }
      else
      {

         crBorder = argb(255, 10, 10, 100);

      }

      //if (_001GetFlag(flag_border))
      {

         pgraphics->draw_rectangle(rectangleClient, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectangleClient.left += 3;
      rectangleClient.top += 3;
      ::rectangle rectangleText = m_rectangleText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pbitmap->m_pimage->is_set())
      {
         if (m_pbitmap->m_pimage->width() > 0 && m_pbitmap->m_pimage->height() > 0)
         {
            ::rectangle rectangleDib;
            rectangleDib = m_rectangleText;
            rectangleDib.bottom = minimum(rectangleText.top + m_pbitmap->m_pimage->width(), rectangleText.bottom);
            rectangleDib.right = minimum(rectangleText.left + m_pbitmap->m_pimage->height(), rectangleText.right);
            //m_pimage->to(pgraphics, rectangleDib);
            m_pbitmap->m_pimage->bitmap_blend(pgraphics, rectangleDib);
            rectangleText.left += m_pbitmap->m_pimage->width();
         }

      }

      auto pbrushText = __create < ::draw2d::brush > ();

      pgraphics->set(pbrushText);

      string strText(get_window_text());

      pgraphics->set_font(this, ::e_element_none);

      pgraphics->draw_text(strText, rectangleText, e_align_top_left);

   }


   bool button::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible(::user::e_layout_sketch);

   }


   void button::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         ::topic topic;
         topic.m_puserinteraction = this;
         topic.m_atom = ::id_click;
         topic.m_pmessage = pmessage;
         route(&topic);
         pmessage->m_bRet = topic.m_bRet;
         if (pmessage->m_bRet)
         {
            pkey->m_lresult = 1;
         }

      }

   }


   color32_t button::get_button_text_color()
   {

      color32_t crText;

      if (!is_window_enabled())
      {

         crText = argb(255, 0, 0, 0);

      }
      else if (is_left_button_pressed() || get_echeck() == ::e_check_checked)
      {

         crText = argb(255, 0, 0, 0);

      }
      else if (::is_set(m_pitemHover))
      {

         crText = argb(255, 0, 0, 0);

      }
      else
      {

         crText = argb(255, 0, 0, 0);

      }

      return crText;

   }


   color32_t button::_001GetButtonBackgroundColor()
   {

      color32_t crBackground;

      if (!is_window_enabled())
      {

         crBackground = argb(255, 180, 180, 180);

      }
      else if (is_left_button_pressed() || get_echeck() == ::e_check_checked)
      {

         crBackground = argb(255, 240, 240, 240);

      }
      else if (::is_set(m_pitemHover))
      {

         crBackground = argb(255, 240, 240, 240);

      }
      else
      {

         crBackground = argb(255, 240, 240, 240);

      }

      return crBackground;

   }


   void button::handle(::topic * ptopic, ::context * pcontext)
   {

      interaction::handle(ptopic, pcontext);

   }


   void button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      color32_t crBackground = _001GetButtonBackgroundColor();

      if(get_echeck() == ::e_check_checked)
      {

         ::color::color colorBack(crBackground);

         colorBack.hls_rate(0.0, -0.1, 0.0);

         if (colorref_get_a_value(crBackground) > 0)
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->fill_rectangle(rectangleClient, colorBack);

         }

         ::color::color colorTopLeft(colorBack);

         ::color::color colorBottomRight(colorBack);

         colorTopLeft.hls_rate(0.0, -0.2, 0.0);

         colorBottomRight.hls_rate(0.0, 0.2, 0.0);

         ::rectangle rectanglePush(rectangleClient);

         pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight);

         rectanglePush.deflate(1, 1);

         pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight);

      }
      else
      {

         if (colorref_get_a_value(crBackground) > 0)
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->fill_rectangle(rectangleClient, crBackground);

         }

      }

   }


   void button::_001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECT32 * prectText)

   {

      ::rectangle rectangleText(prectText);


      if (m_estockicon == stock_icon_none)
      {

         string strText;

         get_window_text(strText);

         if (strText.has_char())
         {

            color32_t crText = get_button_text_color();

            pgraphics->set_text_color(crText);

            ::e_align ealign;

            ::e_draw_text edrawtext = e_draw_text_single_line;

            if (m_estyle == style_image_and_text)
            {

               if(m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign =  e_align_bottom_left;

               }

            }
            else
            {

               if(m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign =  e_align_center;

               }

            }

            pgraphics->draw_text(strText, rectangleText, iDrawTextFlags);

         }

      }
      else
      {

         color32_t crText = get_button_text_color();

         pgraphics->set_text_color(crText);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->m_color = crText;

         ppen->m_dWidth = 1.0;

         pgraphics->set(ppen);

         ::rectangle rectangleIcon(rectangleText);

         rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

      }

   }


   void button::_001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      pgraphics->set_font(this, ::e_element_none);

      ::rectangle rectangleMargin(2, 2,2, 2);

      ::rectangle rectangleBorder(2, 2, 2, 2);

      rectangleClient.deflate(rectangleMargin);

      rectangleClient.deflate(rectangleBorder);

      _001OnButtonDrawBackground(pgraphics);

      ::rectangle rectanglePadding(4, 4, 4,4);

      rectangleClient.deflate(rectanglePadding);

      _001OnButtonDrawTextLayer(pgraphics, rectangleClient);

   }


   void button::_001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics)
   {

      _001OnButtonDrawBackground(pgraphics);

      if (!m_pbitmap->m_pimage)
      {

         return;

      }

      ASSERT(m_pbitmap->m_pimage); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pbitmap->m_pimage;

      if(echeck() == ::e_check_checked && ::is_ok(m_pbitmap->m_pimageSel))
         pimage = m_pbitmap->m_pimageSel;
      else if(::is_set(m_pitemHover) && is_window_enabled() && ::is_ok(m_pbitmap->m_pimageHover))
         pimage = m_pbitmap->m_pimageHover;
      else if(psession->get_focus_ui() == this && ::is_ok(m_pbitmap->m_pimageFocus))
         pimage = m_pbitmap->m_pimageFocus;   // third image for focused
      else if(!is_window_enabled() && ::is_ok(m_pbitmap->m_pimageDisabled))
         pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      ::rectangle rectangleMargin(4, 4, 4, 4);

      ::rectangle rectangleBorder(2, 2,2 ,2);

      rectangleClient.deflate(rectangleMargin);

      rectangleClient.deflate(rectangleBorder);

      ::rectangle rectanglePadding(4, 4,4,4);

      rectangleClient.deflate(rectanglePadding);

      if (pimage->area() > 0 && rectangleClient.area() > 0)
      {

         ::rectangle rectangleAspect;

         rectangleAspect.left = 0;

         rectangleAspect.top = 0;

         double dW = (double) rectangleClient.width() / (double)pimage->width();

         double dH = (double) rectangleClient.height() / (double) pimage->height();

         double dMin = minimum(minimum(dW, dH), 1.0);

         rectangleAspect.right = (::i32) (pimage->width() * dMin);

         rectangleAspect.bottom = (::i32) (pimage->height() * dMin);

         rectangleAspect.Align(e_align_center, rectangleClient);

         pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->draw(rectangleAspect, pimage->g(), ::rectangle(pimage->get_size()));

      }

   }


   void button::_001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics)
   {

      _001OnButtonDrawBackground(pgraphics);

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      ::rectangle rectanglePadded(rectangleClient);

      int iPadding = 4;

      rectanglePadded.deflate(iPadding, iPadding);

      ::rectangle rectangleAspect(rectanglePadded);

      if (m_pbitmap->m_pimage)
      {

         ASSERT(m_pbitmap->m_pimage); // required

         // use the main bitmap for up, the selected bitmap for down
         ::image_pointer pimage = m_pbitmap->m_pimage;

         if (echeck() == ::e_check_checked && m_pbitmap->m_pimageSel->is_set() && m_pbitmap->m_pimageSel->area() > 0)
            pimage = m_pbitmap->m_pimageSel;
         else if (::is_set(m_pitemHover) && is_window_enabled() && m_pbitmap->m_pimageHover->is_set() && m_pbitmap->m_pimageHover->area() > 0)
            pimage = m_pbitmap->m_pimageHover;
         else if (psession->get_focus_ui() == this && m_pbitmap->m_pimageFocus->is_set() && m_pbitmap->m_pimageFocus->area() > 0)
           pimage = m_pbitmap->m_pimageFocus;   // third image for focused
         else if (!is_window_enabled() && m_pbitmap->m_pimageDisabled->is_set() && m_pbitmap->m_pimageDisabled->area() > 0)
            pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

         if (pimage->area() > 0 && rectangleClient.area() > 0)
         {

            rectangleAspect.left = 0;

            rectangleAspect.top = 0;

            double dW = (double)rectanglePadded.width() / (double)pimage->width();

            double dH = (double)rectanglePadded.height() / (double)pimage->height();

            double dMin = minimum(minimum(dW, dH), 1.0);

            rectangleAspect.right = (::i32) (pimage->width() * dMin);

           rectangleAspect.bottom = (::i32) (pimage->height() * dMin);

            rectangleAspect.Align(e_align_bottom_left, rectanglePadded);

            pgraphics->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw(rectangleAspect, pimage->g(), ::rectangle(pimage->get_size()));

            rectangleAspect.left = rectangleAspect.right + iPadding;
            rectangleAspect.right = rectanglePadded.right;
            rectangleAspect.top = rectanglePadded.top;
            rectangleAspect.bottom = rectanglePadded.bottom;

         }

      }

      _001OnButtonDrawTextLayer(pgraphics, rectangleAspect);

   }


   void button::_001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      ::rectangle rectangleClient;

      get_client_rect(rectangleClient);

      auto color = get_color(pstyle, e_element_background);

      color32_t color32;

      if(echeck() == ::e_check_checked)
      {

         color.hls_rate(0.0,- 0.2,- 0.3);

      }

      if(::is_set(m_pitemHover))
      {

         color.hls_rate(0.0,0.2,0.0);

      }

      color32 = color;

      class ::color::color colorExt1TL;
      class ::color::color colorExt2TL;
      class ::color::color colorExt1BR;
      class ::color::color colorExt2BR;

      colorExt1TL.set_rgb(color32);
      colorExt2TL.set_rgb(color32);
      colorExt1BR.set_rgb(color32);
      colorExt2BR.set_rgb(color32);

      if(echeck() == ::e_check_checked)
      {

         colorExt1TL.hls_rate(0.0,- 0.5,0.0);
         colorExt2TL.hls_rate(0.0,- 0.2,0.0);
         colorExt2BR.hls_rate(0.0,0.2,0.0);
         colorExt1BR.hls_rate(0.0,0.85,0.0);

      }
      else
      {

         colorExt1TL.hls_rate(0.0,0.85,0.0);
         colorExt2TL.hls_rate(0.0,0.2,0.0);
         colorExt2BR.hls_rate(0.0,- 0.2,0.0);
         colorExt1BR.hls_rate(0.0,- 0.5,0.0);

      }

      class imaging & imaging = ::aura::get_system()->imaging();

      ::rectangle rectangle = rectangleClient;
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,215,colorExt1BR,215);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,210,colorExt1BR,210);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,205,colorExt2BR,205);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,200,colorExt2BR,200);
      rectangle.deflate(1,1,1,1);
      imaging.color_blend(pgraphics,rectangle.left,rectangle.top,rectangle.width(),rectangle.height(),color32,200);
      rectangle.deflate(1,1,1,1);

      i32 x1 = rectangle.left;
      i32 x2 = x1 + rectangle.width() / 3;

      rectangle.left = x1;
      rectangle.right = x2;
      rectangle.bottom = rectangle.top + 5;

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1, colorExt1TL);

      pgraphics->set(ppen);

      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,220,colorExt1BR,220);


   }


   void button::set_button_style(e_style estyle)
   {

      if(m_estyle == estyle)
         return;

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         m_pbitmap = new bitmap();

      }
      else if(estyle == style_list)
      {

         m_plist = new list();

         //m_plist->m_pimagelistNormal         = nullptr;
         //m_plist->m_pimagelistItemHover      = nullptr;
         //m_plist->m_pimagelistSubItemHover   = nullptr;

      }
      else if(estyle == style_push)
      {

         SetTimer(16384,100,nullptr);

      }


   }


   void button::on_exit_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         ::acme::del(m_pbitmap);

      }
      else if(estyle == style_list)
      {

         ::acme::del(m_plist);

      }
      else if(estyle == style_push)
      {

         KillTimer(16384);

      }

   }





   bool button::LoadBitmaps(::payload payload,::payload varSel,::payload varFocus,::payload varDisabled,::payload varHover)
   {

      if (m_estyle != style_bitmap &&
            m_estyle != style_image_and_text)
      {

         set_button_style(style_bitmap);

      }

      if(!payload.is_empty())
      {

         m_pbitmap->m_pimage = load_image(payload);

      }

      if(!varSel.is_empty())
      {

         m_pbitmap->m_pimageSel = load_image(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_pbitmap->m_pimageFocus = load_image(varFocus);

      }


      if(!varDisabled.is_empty())
      {

         m_pbitmap->m_pimageDisabled = load_image(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_pbitmap->m_pimageHover = load_image(varHover);

      }

      return m_pbitmap->m_pimage->is_set() && m_pbitmap->m_pimage->area() > 0;

   }






   void button::pre_translate_message(::message::message * pmessage)
   {

      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pmessage);

      return ::user::interaction::pre_translate_message(pmessage);

   }


   void button::BaseToolTipGetRect(RECT32 * prect)

   {
      // use window client rectangle as the tool rectangle
      get_client_rect(prect);

   }

   i32 button::BaseToolTipGetIndex()
   {
      // use window dialog control atom as the index
      return (i32)GetDlgCtrlId();
   }


   void button::_001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics)
   {
      ::rectangle rectangleClient;
      bool bItemHover;
      bool bSubItemHover;



      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      if(pdrawcontext != nullptr)
      {
         rectangleClient     = pdrawcontext->m_rectangleClient;
         bItemHover     = pdrawcontext->m_bListItemHover;
         bSubItemHover  = pdrawcontext->m_bListSubItemHover;
      }
      else
      {
         if(get_form() != nullptr)
            return;
         get_client_rect(rectangleClient);
         bItemHover     = ::is_set(m_pitemHover);
         bSubItemHover  = bItemHover;
      }

      ::point_i32 point = rectangleClient.top_left();
      point += ::size(1, 1);

      if(bSubItemHover)
      {
         pgraphics->draw_inset_3d_rectangle(
         rectangleClient,
         rgb(255,255,255),
         rgb(155,155,105));

         if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else if(bItemHover)
      {
         if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else
      {
         if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
      }

   }


   void button::BaseToolTipRelayEvent(class ::message::message *)
   {
   }


   bool button::is_custom_draw()
   {

      return m_estyle == style_list;

   }


   //bool button::m_pitemHover
   //{

   //   return m_pitemHover;

   //}

   void button::set_stock_icon(e_stock_icon eicon)
   {

      m_estockicon = eicon;

   }


   e_stock_icon button::get_stock_icon()
   {

      return m_estockicon;

   }


} // namespace user




