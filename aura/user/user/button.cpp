#include "framework.h"
#include "button.h"
#include "style.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h" 
#include "acme/platform/context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/context_image.h"
#include "aura/windowing/windowing.h"
#include "aura/user/appearance/appearance.h"
#include "aura/message/user.h"


namespace user
{


   button::button()
   {

      user_button_construct();

   }


   button::button(const ::string & pszName, const ::atom & atom)
   {

      user_button_construct();

      m_strWindowText2 = pszName;

      m_atom = atom;

   }


   button::~button()
   {

   }


   void button::user_button_construct()
   {

      m_bClickDefaultMouseHandling = true;

      m_econtroltype = e_control_type_button;

      m_bMouseHoverOnCapture = true;

      m_estockicon = e_stock_icon_none;

      m_estyle = e_style_none;

      m_pbitmap = nullptr;

      m_plist = nullptr;

      m_iClick = 0;

      m_bClickDefaultMouseHandling = true;

   }


   ::particle_pointer button::clone() const
   {

      auto pcheckbox = m_pcontext->__create_new < ::user::button >();

      return pcheckbox;

   }


   ::write_text::font_pointer button::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
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


   enum_translucency button::get_translucency(style * pstyle)
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

      MESSAGE_LINK(MESSAGE_CREATE    , pchannel, this, &button::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &button::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_key_down  , pchannel, this, &button::on_message_key_down);

      //install_click_default_mouse_handling(pchannel);
      
   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      if (m_estyle == e_style_push || m_estyle == e_style_push_group)
      {

         _001OnButtonDrawPush(pgraphics);

         _001OnButtonDrawImageAndText(pgraphics, false);

      }
      else if (m_estyle == e_style_list)
      {

         _001OnButtonDrawList(pgraphics);

         _001OnButtonDrawImageAndText(pgraphics, false);

      }
      else if (m_estyle == e_style_image)
      {

         _001OnButtonDrawBitmap(pgraphics);

      }
      else if (m_estyle == e_style_image_and_text)
      {

         _001OnButtonDrawImageAndText(pgraphics, true);

      }
      else
      {

         _001OnButtonDrawNormal(pgraphics);

      }

   }


   ::size_f64 button::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      if (pgraphics.is_null())
      {

         auto psystem = acmesystem()->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         pgraphics = pdraw2d->create_memory_graphics(this);

      }

      pgraphics->set_font(this, ::e_element_none);

      string strText(get_window_text());

      const ::size_i32 & size = pgraphics->get_text_extent(strText);

      ::write_text::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size_i32 sizeTotal;

      sizeTotal.cx() = (::i32) size.cx();

      sizeTotal.cy() = (::i32)tm.get_line_spacing();

      return sizeTotal;

   }


   void button::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_estyle == e_style_simple)
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         set_size(sizeTotal);

      }
      else if (m_estyle == e_style_image)
      {

         ::size_i32 sizeTotal = m_pbitmap->m_pimage->size();

         set_size(sizeTotal);

      }
      else if (m_estockicon != e_stock_icon_none)
      {

         set_size({24, 24});

      }
      else
      {

         auto sizeTotal = _001CalculateAdjustedFittingSize(pgraphics);

         set_size(sizeTotal);

      }

   }


   void button::_001SetCheck(const ::e_check & echeck, const ::action_context & context)
   {

      if (echeck != this->get_echeck())
      {

         check::_001SetCheck(echeck, context);

         auto pappearance = get_appearance();

         if (pappearance)
         {

            pappearance->call_check(echeck);

         }

         set_need_redraw();

         post_redraw();

      }

   }


   void button::on_message_create(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (m_estyle == e_style_none)
      {

         set_button_style(e_style_normal);

      }

      m_linkedpropertyCheck = fetch_property(m_atom, true);

   }


   void button::on_message_left_button_double_click(::message::message * pmessage)
   {
   
      pmessage->m_bRet = true;

   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      auto sizeText = _001CalculateAdjustedFittingSize(pgraphics);

      ::rectangle_i32 rectangle;

      rectangle.left = (::i32)(rectangleClient.left + (rectangleClient.width() - sizeText.cx()) / 2);

      rectangle.top = (::i32)(rectangleClient.top + (rectangleClient.height() - sizeText.cy()) / 2);

      rectangle.right = (::i32)(rectangle.left + sizeText.cx());

      rectangle.bottom = (::i32)(rectangle.top + sizeText.cy());

      m_rectangleText = rectangle;

   }


   void button::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      ::color::color crBk;

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
      else if (m_pitemHover && m_pitemHover->is_set())
      {

         // Hover Background
         crBk = argb(255, 80, 80, 80);

      }
      else
      {

         crBk = argb(255, 255, 255, 255);

      }

      auto pstyle = get_style(pgraphics);

      auto psystem = acmesystem()->m_paurasystem;

      if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->fill_rectangle(rectangleClient, ::color::color(crBk) & 127_opacity);

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, crBk);

      }

      ::color::color crBorder;

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

         pgraphics->draw_inset_rectangle(rectangleClient, crBorder, 1.0);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectangleClient.left += 3;
      rectangleClient.top += 3;
      ::rectangle_i32 rectangleText = m_rectangleText;
      //      string str = utf8_to_unicode(str);
      if (m_pbitmap->m_pimage->is_set())
      {
         if (m_pbitmap->m_pimage->width() > 0 && m_pbitmap->m_pimage->height() > 0)
         {
            ::rectangle_i32 rectangleDib;
            rectangleDib = m_rectangleText;
            rectangleDib.bottom = minimum(rectangleText.top + m_pbitmap->m_pimage->width(), rectangleText.bottom);
            rectangleDib.right = minimum(rectangleText.left + m_pbitmap->m_pimage->height(), rectangleText.right);
            //m_pimage->to(pgraphics, rectangleDib);

            {

               image_source imagesource(m_pbitmap->m_pimage);

               auto rectangle = rectangleDib;

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

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

      return is_window_enabled() && is_window_visible(::user::e_layout_sketch) && !windowing()->is_sandboxed();

   }


   void button::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      ::user::enum_key iKey = pkey->m_ekey;

      if (iKey == ::user::e_key_return || iKey == ::user::e_key_space)
      {

         auto ptopic = create_topic(::id_click);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext.m_pmessage = pkey;

         ptopic->m_actioncontext.add(e_source_user);

         route(ptopic);

         pmessage->m_bRet = ptopic->m_bRet;

         if (pmessage->m_bRet)
         {

            pkey->m_lresult = 1;

         }

      }

   }


   void button::on_message_key_up(::message::message * pmessage)
   {

      if (m_estyle == e_style_push)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey->m_ekey == ::user::e_key_space)
         {

            _001ToggleCheck(::e_source_user);

         }

      }
      else if (m_estyle == e_style_push_group)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey->m_ekey == ::user::e_key_space)
         {

            _001SetCheck(::e_check_checked, ::e_source_user);

         }

      }

   }


   ::color::color button::_001GetButtonBackgroundColor()
   {

      ::color::color crBackground;

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


   void button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, ::e_element_background, get_state());

      auto & linkedpropertyCheck = m_linkedpropertyCheck;

      auto echeck = get_echeck();

      if(echeck == ::e_check_checked)
      {
         
         if(windowing()->is_sandboxed())
         {

            ::rectangle_i32 rectanglePush(rectangleClient);
            
            rectanglePush.inflate(2);

            ::color::color colorBack(colorBackground);

            colorBack.hls_rate(0.0, -0.2, 0.0);

            rectanglePush.deflate(0, 0, 1, 1);

            ::color::color colorTopLeft(colorBack);

            ::color::color colorBottomRight(colorBack);

            colorTopLeft = argb(1.0, 0.2, 0.5, 0.8);

            colorBottomRight = argb(1.0, 0.2, 0.5, 0.8);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

            rectanglePush.deflate(1, 1, 0, 1);

            pgraphics->fill_rectangle(rectanglePush, colorBack);

         }
         
      }
   }


   void button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, ::e_element_background, get_state());

      //::color::color crBackground = _001GetButtonBackgroundColor();

      auto & linkedpropertyCheck = m_linkedpropertyCheck;

      auto echeck = get_echeck();

      if(echeck == ::e_check_checked)
      {
         
         if(windowing()->is_sandboxed())
         {
            

            
         }
         else
         {
            
            ::rectangle_i32 rectanglePush(rectangleClient);

            ::color::color colorBack(colorBackground);

            colorBack.hls_rate(0.0, -0.2, 0.0);

            rectanglePush.deflate(0, 0, 1, 1);

            ::color::color colorTopLeft(colorBack);

            ::color::color colorBottomRight(colorBack);

            colorTopLeft.hls_rate(0.0, -0.65, 0.0);

            colorBottomRight.hls_rate(0.0, 0.75, 0.0);

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

            rectanglePush.deflate(1, 1);

            pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

            rectanglePush.deflate(1, 1);

            pgraphics->draw_inset_3d_rectangle(rectanglePush, colorTopLeft, colorBottomRight, 1.0);

            rectanglePush.deflate(1, 1, 0, 1);

            pgraphics->fill_rectangle(rectanglePush, colorBack);
               
         }

      }
      else
      {

         if (colorBackground.non_transparent())
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->fill_rectangle(rectangleClient, colorBackground);

         }

      }

   }


   void button::_001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, ::rectangle_i32 & rectText)
   {

      ::rectangle_i32 rectangleText(rectText);

      if (m_estockicon == e_stock_icon_none)
      {

         auto strWindowText = get_window_text();

         //get_window_text(strText);

         if (strWindowText.has_char())
         {

            auto pstyle = get_style(pgraphics);

            auto estate = get_state();

            ::color::color colorText = get_color(pstyle, e_element_text, estate);

            pgraphics->set_text_color(colorText);

            ::e_align ealign;

            ::e_draw_text edrawtext;

            if (m_estyle == e_style_image_and_text)
            {

               if (m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign = e_align_top_left;

               }

            }
            else
            {

               if (m_ealignText)
               {

                  ealign = m_ealignText;

               }
               else
               {

                  ealign = e_align_center;

               }
            }

            edrawtext = e_draw_text_single_line;

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pgraphics->draw_text(strWindowText, rectangleText, ealign, edrawtext);

         }

      }
      else
      {

         auto pstyle = get_style(pgraphics);

         ::color::color colorText = get_color(pstyle, e_element_text, get_state());

         pgraphics->set_text_color(colorText);

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1.0, colorText);

         pgraphics->set(ppen);

         ::rectangle_i32 rectangleIcon(rectangleText);

         rectangleIcon.deflate(rectangleIcon.width() / 16, rectangleIcon.height() / 16);

         pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

      }

   }


   void button::_001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle();

      pgraphics->set_font(this, ::e_element_none);

      ::rectangle_i32 rectangleMargin(2, 2, 2, 2);

      ::rectangle_i32 rectangleBorder(2, 2, 2, 2);

      rectangleClient.deflate(rectangleMargin);

      rectangleClient.deflate(rectangleBorder);

      if(m_estyle != e_style_stock_icon)
      {

         _001OnButtonDrawBackground(pgraphics);

      }

//      if(m_pitemHover)
//      {
//
//         pgraphics->fill_rectangle(::rectangle_i32(0, 0, 20, 20), argb(255, 255, 0, 0));
//
//      }

      ::rectangle_i32 rectanglePadding(4, 4, 4,4);

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

      auto psession = get_session();

      if(echeck() == ::e_check_checked && m_pbitmap->m_pimageSel.ok())
         pimage = m_pbitmap->m_pimageSel;
      else if(::is_set(m_pitemHover) && is_window_enabled() && m_pbitmap->m_pimageHover.ok())
         pimage = m_pbitmap->m_pimageHover;
      else if(m_pbitmap->m_pimageFocus.ok() && has_keyboard_focus())
         pimage = m_pbitmap->m_pimageFocus;   // third image for focused
      else if(!is_window_enabled() && m_pbitmap->m_pimageDisabled.ok())
         pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

      auto rectangleClient = client_rectangle();

      ::rectangle_i32 rectangleMargin(4, 4, 4, 4);

      ::rectangle_i32 rectangleBorder(2, 2,2 ,2);

      rectangleClient.deflate(rectangleMargin);

      rectangleClient.deflate(rectangleBorder);

      ::rectangle_i32 rectanglePadding(4, 4,4,4);

      rectangleClient.deflate(rectanglePadding);

      if (pimage->area() > 0 && rectangleClient.area() > 0)
      {

         ::rectangle_i32 rectangleAspect;

         rectangleAspect.left = 0;

         rectangleAspect.top = 0;

         double dW = (double) rectangleClient.width() / (double)pimage->width();

         double dH = (double) rectangleClient.height() / (double) pimage->height();

         double dMin = minimum(minimum(dW, dH), 1.0);

         rectangleAspect.right = (::i32) (pimage->width() * dMin);

         rectangleAspect.bottom = (::i32) (pimage->height() * dMin);

         rectangleAspect.Align(e_align_center, rectangleClient);

         pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         {

            image_source imagesource(pimage, ::rectangle_i32(pimage->get_size()));

            rectangle_f64 rectangle(rectangleAspect);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }

      }

   }


   void button::_001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics, bool bDecoration)
   {

      if (bDecoration)
      {

         _001OnButtonDrawBackground(pgraphics);

      }

      auto rectangleClient = client_rectangle();

      ::rectangle_i32 rectanglePadded(rectangleClient);

      int iPadding = 4;

      rectanglePadded.deflate(iPadding, iPadding);

      ::rectangle_i32 rectangleAspect(rectanglePadded);

      if (m_pbitmap)
      {
         if (m_pbitmap->m_pimage)
         {

            ASSERT(m_pbitmap->m_pimage); // required

            // use the main bitmap for up, the selected bitmap for down
            ::image_pointer pimage = m_pbitmap->m_pimage;

            auto psession = get_session();

            if (echeck() == ::e_check_checked && m_pbitmap->m_pimageSel.ok())
               pimage = m_pbitmap->m_pimageSel;
            else if (::is_set(m_pitemHover) && is_window_enabled() && m_pbitmap->m_pimageHover.ok())
               pimage = m_pbitmap->m_pimageHover;
            else if (m_pbitmap->m_pimageFocus.ok() && has_keyboard_focus())
               pimage = m_pbitmap->m_pimageFocus;   // third image for focused
            else if (!is_window_enabled() && m_pbitmap->m_pimageDisabled.ok())
               pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

            if (pimage->area() > 0 && rectangleClient.area() > 0)
            {

               rectangleAspect.left = 0;

               rectangleAspect.top = 0;

               double dW = (double)rectanglePadded.width() / (double)pimage->width();

               double dH = (double)rectanglePadded.height() / (double)pimage->height();

               double dMin = minimum(minimum(dW, dH), 1.0);

               rectangleAspect.right = (::i32)(pimage->width() * dMin);

               rectangleAspect.bottom = (::i32)(pimage->height() * dMin);

               rectangleAspect.Align(e_align_bottom_left, rectanglePadded);

               pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               {

                  image_source imagesource(pimage, ::rectangle_i32(pimage->get_size()));

                  rectangle_f64 rectangle(rectangleAspect);

                  image_drawing_options imagedrawingoptions(rectangle);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }

               rectangleAspect.left = rectangleAspect.right + iPadding;
               rectangleAspect.right = rectanglePadded.right;
               rectangleAspect.top = rectanglePadded.top;
               rectangleAspect.bottom = rectanglePadded.bottom;

            }

         }

      }

      _001OnButtonDrawTextLayer(pgraphics, rectangleAspect);

   }


   void button::_001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto rectangleClient = client_rectangle();

      auto color = get_color(pstyle, e_element_background);

      status < ::color::color > color32;

      if(echeck() == ::e_check_checked)
      {

         color.hls_rate(0.0,- 0.2,- 0.3);

      }

      if(::is_set(m_pitemHover))
      {

         color.hls_rate(0.0,0.2,0.0);

      }

      color32 = color;

      ::color::color colorExt1TL;
      ::color::color colorExt2TL;
      ::color::color colorExt1BR;
      ::color::color colorExt2BR;

      colorExt1TL = color32;
      colorExt2TL = color32;
      colorExt1BR = color32;
      colorExt2BR = color32;

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

      auto psystem = acmesystem()->m_paurasystem;

      ::rectangle_i32 rectangle = rectangleClient;
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,215,colorExt1BR,215);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt1TL,210,colorExt1BR,210);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,205,colorExt2BR,205);
      rectangle.deflate(1,1,1,1);
      pgraphics->color_blend_3dRect(rectangle,colorExt2TL,200,colorExt2BR,200);
      rectangle.deflate(1,1,1,1);
      pgraphics->fill_rectangle(rectangle,color32 & ::opacity(200));
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


   void button::set_button_style(enum_style estyle)
   {

      if (m_estyle == estyle)
      {

         return;

      }

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(enum_style estyle)
   {

      if(estyle == e_style_image || estyle == e_style_image_and_text)
      {

         m_pbitmap = memory_new bitmap();

      }
      else if(estyle == e_style_list)
      {

         m_plist = memory_new list();

         //m_plist->m_pimagelistNormal         = nullptr;
         //m_plist->m_pimagelistItemHover      = nullptr;
         //m_plist->m_pimagelistSubItemHover   = nullptr;

      }
      else if(estyle == e_style_push || estyle == e_style_push_group)
      {

         SetTimer(16384,100_ms,nullptr);

         MESSAGE_LINK(e_message_key_up, this, this, &button::on_message_key_up);

      }


   }


   void button::on_exit_button_style(enum_style estyle)
   {

      if(estyle == e_style_image|| estyle == e_style_image_and_text)
      {

         m_pbitmap.release();

      }
      else if(estyle == e_style_list)
      {

         m_plist.release();

      }
      else if(estyle == e_style_push || estyle == e_style_push_group)
      {

         KillTimer(16384);

      }

   }


   bool button::LoadBitmaps(::payload payload,::payload varSel,::payload varFocus,::payload varDisabled,::payload varHover)
   {

      if (m_estyle != e_style_image &&
            m_estyle != e_style_image_and_text)
      {

         set_button_style(e_style_image);

      }

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      if(!payload.is_empty())
      {

         m_pbitmap->m_pimage = pcontextimage->get_image(payload);

      }

      if(!varSel.is_empty())
      {

         m_pbitmap->m_pimageSel = pcontextimage->get_image(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_pbitmap->m_pimageFocus = pcontextimage->get_image(varFocus);

      }


      if(!varDisabled.is_empty())
      {
         
         m_pbitmap->m_pimageDisabled = pcontextimage->get_image(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_pbitmap->m_pimageHover = pcontextimage->get_image(varHover);

      }

      return m_pbitmap->m_pimage->is_set() && m_pbitmap->m_pimage->area() > 0;

   }


   void button::pre_translate_message(::message::message * pmessage)
   {

      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pmessage);

      return ::user::interaction::pre_translate_message(pmessage);

   }


   void button::BaseToolTipGetRect(::rectangle_i32 & rectangle)
   {

      // use window client rectangle_i32 as the tool rectangle_i32
      rectangle = client_rectangle();

   }


   i32 button::BaseToolTipGetIndex()
   {

      // use window dialog control atom as the index
      return GetDlgCtrlId().as_i32();
   }


   void button::_001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics)
   {
      ::rectangle_i32 rectangleClient;
      bool bItemHover;
      bool bSubItemHover;

      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      if(pdrawcontext != nullptr)
      {

         bItemHover     = pdrawcontext->m_bListItemHover;

         bSubItemHover  = pdrawcontext->m_bListSubItemHover;

      }
      else
      {

         if (get_form() != nullptr)
         {

            return;

         }

         bItemHover     = ::is_set(m_pitemHover);

         bSubItemHover  = bItemHover;

      }

      rectangleClient = client_rectangle();

      ::point_i32 point = rectangleClient.top_left();

      point += ::size_i32(1, 1);

      if(bSubItemHover)
      {
         pgraphics->draw_inset_3d_rectangle(
         rectangleClient,
         rgb(255,255,255),
         rgb(155,155,105),
            1.0);

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

      return m_estyle == e_style_list;

   }


   void button::set_stock_icon(enum_stock_icon estockicon)
   {

      m_estockicon = estockicon;

   }


   enum_stock_icon button::get_stock_icon()
   {

      return m_estockicon;

   }


   bool button::on_click_generation(::item * pitem)
   {

      if (m_estyle == e_style_push)
      {

         _001ToggleCheck(::e_source_user);

      }
      else if (m_estyle == e_style_push_group)
      {

         _001SetCheck(::e_check_checked, ::e_source_user);

      }

      return ::user::interaction::on_click_generation(pitem);

   }


//   bool button::on_click(::item * pitem)
//   {
//
//
//      return ::user::interaction::on_click(pitem);
//
//   }


} // namespace user



