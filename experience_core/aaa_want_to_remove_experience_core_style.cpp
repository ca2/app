#include "framework.h"

// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"





namespace experience_lite
{


   user_style::user_style()
   {

      m_etranslucency      = ::user::e_translucency_present;
      m_pfont.create(this);



   }


   user_style::~user_style()
   {

   }


   bool user_style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::rectangle rectangle;
      ::rectangle rectBorder;
      ::rectangle rectText;
      ::rectangle rectangleClient;
      ::rectangle rectIcon;
      ::rectangle rectClose;

      ptab->get_data()->m_pen->create_solid(1,rgb(32,32,32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      i32 iTab = -1;

      ::draw2d::brush_pointer brushText;

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

         if(!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if(!ptab->get_element_rect(iTab,rectangle, ::user::e_element_tab))
            continue;

         if(!ptab->get_element_rect(iTab,rectBorder, ::user::e_element_border))
            continue;

         if(!ptab->get_element_rect(iTab,rectangleClient, ::user::e_element_client))
            continue;

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
/*               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }

            ::draw2d::path_pointer path(this_create);

            if(true)
            {

               if(ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  //path->add_line(rectangleClient.right, rectBorder.top);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectangleClient.left));
                  path->add_line(rectangleClient.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);

                  path->end_figure(false);

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab->get_data()->m_font);

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectangleClient.left));
                  path->add_line(rectText.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.bottom);

                  path->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::e_element_close_tab_button && ptab->m_eelementHover < ::user::e_element_split && ptab->m_eelementHover >(::user::e_element_split + 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->get_data()->m_fontUnderline);

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->get_data()->m_font);

                     brushText = ptab->get_data()->m_brushText;

                  }

               }

            }

         }
         else
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

/*               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }

            if(true)
            {

               ::draw2d::path_pointer path(this_create);

               if(ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  path->add_line(rectBorder.left,rectangleClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectangleClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectangleClient.right));

                  path->add_line(rectBorder.right - 1,rectangleClient.bottom);

                  path->end_figure(false);

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  ptab->get_data()->m_penBorderSel->create_solid(1.0,argb(255,0,0,0));

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab->get_data()->m_font);

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {

                  //path->begin_figure(true, ::draw2d::fill_mode_winding);

                  path->add_line(rectBorder.left,rectangleClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectangleClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectangleClient.right));

                  path->add_line(rectBorder.right - 1,rectangleClient.bottom);

                  path->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::e_element_close_tab_button && (ptab->m_eelementHover < ::user::e_element_split || ptab->m_eelementHover >(::user::e_element_split + 100)))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->get_data()->m_fontUnderline);

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->get_data()->m_font);

                     brushText = ptab->get_data()->m_brushTextSel;

                  }

               }

            }

         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectText, ::user::e_element_text))
            {

               _001OnTabPaneDrawTitle(pane,ptab,pgraphics,rectText,brushText);

            }

         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectClose, ::user::e_element_close_tab_button))
            {

               pgraphics->set_font(ptab->get_data()->m_fontBold);

               if(iTab == ptab->m_iHover && ptab->m_eelementHover == ::user::e_element_close_tab_button)
               {

                  brushText = ptab->get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = ptab->get_data()->m_brushClose;

               }

               pgraphics->SelectObject(brushText);

               pgraphics->draw_text("x",rectClose,e_align_center);

            }

         }

      }

      return true;

   }


   void user_style::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,LPCRECT32 lpcrect,::draw2d::brush_pointer & brushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->SelectObject(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(),*lpcrect,e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rectangle rectText(lpcrect);

         ::write_text::font_pointer font;
         font = pgraphics->get_current_font();
         size sSep = ptab->get_data()->m_sizeSep;
         ::rectangle rectEmp;
         for(index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size s = pane.m_sizeaText[i];
            rectText.right =rectText.left + s.cx;
            pgraphics->_DrawText(str,rectText,e_align_bottom_left, e_draw_text_no_prefix);
            rectText.left += s.cx;
            if(i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1,1);
               ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
               if(ptab->m_eelementHover == (int)::user::e_element_split + i)
               {
                  pgraphics->FillSolidRect(rectEmp,argb(128,149,184,255));
                  pgraphics->SelectObject(ptab->get_data()->m_brushTextHover);
               }
               else
               {
                  //pgraphics->FillSolidRect(rectEmp,argb(128,208,223,233));
                  pgraphics->SelectObject(ptab->get_data()->m_brushText);
               }
               pgraphics->set_font(ptab->get_data()->m_fontBigBold);
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText, e align_center, e_draw_text_no_prefix);
               rectText.left += sSep.cx;
               pgraphics->selectFont(font);
               pgraphics->SelectObject(brushText);
            }
         }

      }

   }



   bool user_style::_001OnTabLayout(::user::tab * ptab)
   {


      {

         //         ::u32 dwTime2= ::millis::now();

         //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //TRACE("usertab::on_layout call time1= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }
      if(!ptab->get_data()->m_bCreated)
         return false;

      ptab->defer_handle_auto_hide_tabs(false);

      ::draw2d::memory_graphics pgraphics(this_create);
      pgraphics->SelectObject(ptab->get_data()->m_fontBold);

      ptab->m_dcextension.get_text_extent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);



      if(ptab->get_data()->m_bVertical)
      {
         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;
         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               continue;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            ::size size;

            ptab->m_dcextension.get_text_extent(pgraphics,str,size);



/*            if(tab_pane.m_pimage->is_set())
            {
/*               size.cx += tab_pane.m_pimage->width() + 2;
/*               size.cy = maximum(size.cy,tab_pane.m_pimage->height());
            }
            cx = size.cx + 2;

            if(!tab_pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if(cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy + 2;
            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabWidth += ptab->get_data()->m_rectBorder.left + ptab->get_data().m_rectBorder.right +
                      ptab->get_data()->m_rectMargin.left + ptab->get_data().m_rectMargin.right +
                      ptab->get_data()->m_rectTextMargin.left + ptab->get_data().m_rectTextMargin.right;

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data().m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data().m_rectMargin.bottom +
                       ptab->get_data()->m_rectTextMargin.top + ptab->get_data().m_rectTextMargin.bottom;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::rectangle rectangleClient;
         ptab->GetClientRect(rectangleClient);

         ptab->get_data()->m_rectTab.left       = rectangleClient.left;
         ptab->get_data()->m_rectTab.top        = rectangleClient.top;
         ptab->get_data()->m_rectTab.right      = ptab->get_data()->m_rectTab.left + ptab->get_data().m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom     = rectangleClient.bottom;

         /*      m_puserinteraction->set_window_position(
         ZORDER_TOP,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left       = ptab->m_bShowTabs ? ptab->get_data().m_rectTab.right : rectangleClient.left;
         ptab->get_data()->m_rectTabClient.top        = ptab->get_data().m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right      = rectangleClient.right;
         ptab->get_data()->m_rectTabClient.bottom     = ptab->get_data().m_rectTab.bottom;

      }
      else
      {
         i32 iTabHeight = 16;
         i32 cy;
         ::draw2d::graphics_pointer graphics(this_create);
         pgraphics->CreateCompatibleDC(NULL);
         ::draw2d::graphics_pointer & pgraphics = graphics;
         pgraphics->SelectObject(ptab->get_data()->m_fontBold);

         ::rectangle rectangleClient;
         ptab->GetClientRect(rectangleClient);
         int x = rectangleClient.left;

         i32 ixAdd;
         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               return false;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            size size;

            ptab->m_dcextension.get_text_extent(pgraphics,str,size);

/*            if(tab_pane.m_pimage->m_p != NULL)
            {
/*               size.cy = maximum(size.cy,tab_pane.m_pimage->size()->cy);
            }
            cy = size.cy + 2;

            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            tab_pane.m_point.x = x;
            tab_pane.m_point.y = rectangleClient.top;


            //            string str = tab_pane.get_title();

            //            size size;

            ixAdd = 5;

/*            if(tab_pane.m_pimage->is_set())
            {
               //::image_list::info ii;
/*               ixAdd += tab_pane.m_pimage->width() + 2;
            }

            if(!tab_pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            tab_pane.m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data().m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data().m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data().m_rectTextMargin.right;

            x += tab_pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data().m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom + ptab->get_data().m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            tab_pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left       = rectangleClient.left;
         ptab->get_data()->m_rectTab.top        = rectangleClient.top;
         ptab->get_data()->m_rectTab.right      = rectangleClient.right;
         ptab->get_data()->m_rectTab.bottom     = ptab->get_data()->m_rectTab.top + ptab->get_data().m_iTabHeight;

         /*      set_window_position(
         ZORDER_TOP,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         rectangle & rectTabClient = ptab->get_data()->m_rectTabClient;

         rectTabClient.left       = ptab->get_data()->m_rectTab.left;
         rectTabClient.top        = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.bottom : rectangleClient.top;
         rectTabClient.right      = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom     = rectangleClient.bottom;

         //TRACE0("rectTabClient");
      }

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         if(iPane != ptab->_001GetSel())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->_001GetSel(), ptab->is_window_visible());

      return true;

   }


   bool user_style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, simple_scroll_bar * pbar)
   {

      color32_t crBackground = 0;

      pbar->get_color(crBackground, ::user::color_scrollbar_background);

      ::rectangle rectangleClient;

      pbar->GetClientRect(rectangleClient);

      if ((crBackground & argb(255, 0, 0, 0)) != 0)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         if (psession->savings().is_trying_to_save(::e_resource_processing))
         {

            pgraphics->FillSolidRect(rectangleClient, rgb(255, 255, 255));

         }
         else
         {

            pgraphics->FillSolidRect(rectangleClient, argb(255, 210, 210, 210));

         }

      }

      ::rectangle rectTrack;

      pbar->GetTrackRect(rectTrack);

      ::rectangle rectWindow;

      pbar->GetWindowRect(rectWindow);

      pbar->m_penDraw->create_solid(1, pbar->scrollbar_border_color(::user::e_element_scrollbar_rect));

      pbar->m_brushDraw->create_solid(pbar->scrollbar_color(::user::e_element_scrollbar_rect));

      pgraphics->SelectObject(pbar->m_penDraw);

      pgraphics->SelectObject(pbar->m_brushDraw);

      pgraphics->Rectangle(rectTrack);

      if (pbar->m_bTracking || (bool)pbar->prop("tracking_on"))
      {

         ::u32 tickFadeIn = 490;

         ::u32 tickFadeOut = 490;

         byte uchAlpha = maximum(0, minimum(255, pbar->prop("tracking_alpha").::u32()));

         if (pbar->m_bTracking)
         {

            if (!(bool)pbar->prop("tracking_on"))
            {

               pbar->prop("tracking_on") = true;
               pbar->prop("tracking_start") = (u32)(::get_tick() + uchAlpha * tickFadeIn / 255);
               pbar->prop("tracking_fade_in") = true;
               pbar->prop("tracking_fade_out") = false;
               pbar->prop("tracking_simple") = __random(1, 2) == 1;
               //prop("tracking_window") = __alloc(new trw(this));
            }
         }
         else
         {
            if (!(bool)pbar->prop("tracking_fade_out"))
            {
               pbar->prop("tracking_fade_in") = false;
               pbar->prop("tracking_fade_out") = true;
               pbar->prop("tracking_start") = (u32)(::get_tick() + (255 - uchAlpha) * tickFadeOut / 255);
            }

         }

         point pt1 = rectTrack.top_left() + pbar->m_pointTrackOffset;

         pbar->client_to_screen(pt1);

         point pt2;

         psession->get_cursor_position(&pt2);

         pbar->client_to_screen(pt1);

         //      prop("tracking_window").cast < trw >()->pt1 = pt1;

         //    prop("tracking_window").cast < trw >()->pt2 = pt2;

         if ((bool)pbar->prop("tracking_fade_in"))
         {
            ::u32 dwFade = pbar->prop("tracking_start").millis().elapsed();
            if (dwFade < tickFadeIn)
            {
               uchAlpha = (byte)minimum(255, maximum(0, (dwFade * 255 / tickFadeIn)));
            }
            else
            {
               uchAlpha = 255;
               pbar->prop("tracking_fade_in") = false;
            }

         }
         else if ((bool)pbar->prop("tracking_fade_out"))
         {
            ::u32 dwFade = pbar->prop("tracking_start").millis().elapsed();
            if (dwFade < tickFadeOut)
            {
               uchAlpha = (byte)(255 - minimum(255, maximum(0, (dwFade * 255 / tickFadeOut))));
            }
            else
            {
               uchAlpha = 0;
               pbar->prop("tracking_on") = false;
               pbar->prop("tracking_fade_out") = false;
            }

         }
         else
         {
            uchAlpha = 255;
         }

         ::rectangle rectMachineThumb;

         bool bSimple = (bool)pbar->prop("tracking_simple");

         if (bSimple)
         {

            int iSize = rectTrack.size().get_normal(pbar->m_eorientation) * 6 / 8;

            rectMachineThumb.top_left() = rectTrack.top_left() + pbar->m_pointTrackOffset - size(iSize / 2, iSize / 2);

            rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

            ::rectangle rectIntersect;

            rectIntersect.intersect(rectMachineThumb, rectTrack);

            i32 iArea = (i32)(maximum(1, rectIntersect.area()));

            rectMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

         }
         else
         {

            int iSize = rectTrack.size().get_normal(pbar->m_eorientation);

            rectMachineThumb.top_left() = rectTrack.top_left() + pbar->m_pointTrackOffset - size(iSize / 2, iSize / 2);

            rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

            rectMachineThumb.assign_normal(rectTrack, pbar->m_eorientation);

            rectMachineThumb.constraint_v7(rectTrack);

            rectMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

         }

         pbar->prop("tracking_alpha") = uchAlpha;

      }



      ::draw2d::pen_pointer penGrip(this_create);

      penGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(::user::e_element_scrollbar_rect));

      pgraphics->SelectObject(penGrip);

      point ptCenter = rectTrack.center();

      if (pbar->m_eorientation == e_orientation_horizontal)
      {


         pgraphics->MoveTo(ptCenter.x - 5, ptCenter.y - 5);
         pgraphics->LineTo(ptCenter.x - 5, ptCenter.y + 5);
         pgraphics->MoveTo(ptCenter.x, ptCenter.y - 5);
         pgraphics->LineTo(ptCenter.x, ptCenter.y + 5);
         pgraphics->MoveTo(ptCenter.x + 5, ptCenter.y - 5);
         pgraphics->LineTo(ptCenter.x + 5, ptCenter.y + 5);


      }
      else
      {
         pgraphics->MoveTo(ptCenter.x - 5, ptCenter.y - 5);
         pgraphics->LineTo(ptCenter.x + 5, ptCenter.y - 5);
         pgraphics->MoveTo(ptCenter.x - 5, ptCenter.y);
         pgraphics->LineTo(ptCenter.x + 5, ptCenter.y);
         pgraphics->MoveTo(ptCenter.x - 5, ptCenter.y + 5);
         pgraphics->LineTo(ptCenter.x + 5, ptCenter.y + 5);

      }


      ::draw2d::pen_pointer penArrow(this_create);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(::user::e_element_scrollbar_rectA));

      pgraphics->SelectObject(penArrow);

      pbar->m_brushDraw->create_solid(pbar->scrollbar_color(::user::e_element_scrollbar_rectA));

      pgraphics->SelectObject(pbar->m_brushDraw);

      pgraphics->Rectangle(pbar->m_rectA);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(::user::e_element_scrollbar_rectB));

      pgraphics->SelectObject(penArrow);

      pbar->m_brushDraw->create_solid(pbar->scrollbar_color(::user::e_element_scrollbar_rectB));

      pgraphics->SelectObject(pbar->m_brushDraw);

      pgraphics->Rectangle(pbar->m_rectB);

      ::rectangle rectangle;

      if (pbar->m_eelement == ::user::e_element_scrollbar_pageA || pbar->m_eelementHover == ::user::e_element_scrollbar_pageA)
      {

         pbar->GetPageARect(rectangleClient, rectTrack, rectangle);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(::user::e_element_scrollbar_pageA));

         pgraphics->SelectObject(pbar->m_brushDraw);

         pgraphics->FillRectangle(rectangle);

      }
      else if (pbar->m_eelement == ::user::e_element_scrollbar_pageB || pbar->m_eelementHover == ::user::e_element_scrollbar_pageB)
      {

         pbar->GetPageBRect(rectangleClient, rectTrack, rectangle);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(::user::e_element_scrollbar_pageB));

         pgraphics->SelectObject(pbar->m_brushDraw);

         pgraphics->FillRectangle(rectangle);


      }


      penArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
      penArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
      penArrow->m_elinejoin = ::draw2d::e_line_join_round;

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(::user::e_element_scrollbar_rectA));

      pgraphics->SelectObject(penArrow);

      pgraphics->polyline(pbar->m_ptaA, 3);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(::user::e_element_scrollbar_rectB));

      pgraphics->SelectObject(penArrow);

      pgraphics->polyline(pbar->m_ptaB, 3);



      return true;



   }




   bool user_style::get_color(color32_t & color32, ::user::e_color ecolor)
   {

      if (ecolor == ::user::color_background)
      {

         color32 = 0;

         return true;

      }
      else if (ecolor == ::user::color_background_hover)
      {

         color32 = argb(120, 110, 100, 200);

         return true;

      }
      else if (ecolor == ::user::color_split_layout_background)
      {

         color32 = argb(0, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_list_background)
      {

         color32 = argb(80, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_edit_background)
      {

         color32 = argb(80, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_edit_background_selected)
      {

         color32 = argb(120, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_text)
      {

         color32 = argb(255, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_text_selected)
      {

         color32 = argb(255, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_text_highlight)
      {

         color32 = argb(255, 50, 150, 150);

         return true;

      }
      else if (ecolor == ::user::color_text_selected_highlight)
      {

         color32 = argb(255, 20, 90, 100);

         return true;

      }
      else if (ecolor == ::user::color_edit_text)
      {

         color32 = argb(255, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_edit_text_selected)
      {

         color32 = argb(255, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_tree_background)
      {

         color32 = argb(80, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_view_background)
      {

         color32 = argb(80, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_scrollbar_background)
      {

         color32 = argb(80, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_background_selected)
      {

         color32 = argb(255, 155, 185, 255);

         return true;

      }
      else if (ecolor == ::user::color_list_header)
      {

         color32 = argb(255, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_list_header_background)
      {

         color32 = argb(255, 0x58, 0x5C, 0x5D);

         return true;

      }
      else if (ecolor == ::user::color_list_item_background)
      {

         color32 = argb(30, 0, 0, 0);

         return true;

      }
      else if (ecolor == ::user::color_list_header_separator)
      {

         color32 = 0;

         return true;

      }
      else if (ecolor == ::user::color_toolbar_background)
      {

         color32 = argb(80, 0xF3, 0XF5, 0xF5);

         return true;


      }
      else if (ecolor == ::user::color_button_background_disabled)
      {

         color32 = argb(255, 128, 128, 128);

         return true;


      }
      else if (ecolor == ::user::color_button_background_hover)
      {

         color32 = argb(255, 0x55, 0x99, 0xC2);

         return true;

      }
      else if (ecolor == ::user::color_button_background)
      {

         color32 = argb(255, 0x30, 0x75, 0xA0);

         return true;
      }
      else if (ecolor == ::user::color_button_background_press)
      {

         color32 = argb(255, 0x07, 0x6D, 0x91);

         return true;
      }
      else if (ecolor == ::user::color_button_text_disabled)
      {

         color32 = argb(255, 0x80, 0x80, 0x80);

         return true;

      }
      else if (ecolor == ::user::color_button_text_hover)
      {

         color32 = argb(255, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_button_text)
      {

         color32 = argb(255, 255, 255, 255);

         return true;

      }
      else if (ecolor == ::user::color_button_text_press)
      {

         color32 = argb(255, 255, 255, 255);

         return true;

      }

      bool bOk = m_mapColor.lookup(ecolor, color32);

      if (!bOk)
      {

         output_debug_string("\nUnknown color: code=" + __str((int) ecolor));

      }

      return bOk;

   }


} // namespace experience_lite









