#include "framework.h"
#include "base/user/simple/scroll_bar.h"

// pgraphics->GetTextExtent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"



namespace experience
{


   namespace aura
   {



   style::style()
   {

      //m_etranslucency = ::user::translucency_total;

      m_colorBackground = __acolor(127, 255, 255, 255);

      //create_translucency(::user::element_none, ::user::translucency_present);
      //create_point_font(::user::font_default, FONT_SANS, 12.0);

      //create_point_font(::user::font_tab, FONT_SANS, 12.0);
      //{
      //   auto font = create_point_font(::user::font_tab_hover, FONT_SANS, 12.0);
      //   font->m_bUnderline = true;
      //}
      //create_point_font(::user::font_tab_sel, FONT_SANS, 12.0, 800);
      //{
      //   auto font = create_point_font(::user::font_tab_sel_hover, FONT_SANS, 12.0, 800);
      //   font->m_bUnderline = true;
      //}
      //create_point_font(::user::font_tab_big_bold, FONT_SANS_EX, 15.0, 800);

      //create_color(::user::color_text, ARGB(255, 0, 0, 0));
      //create_color(::user::color_edit_text, ARGB(255, 0, 0, 0));
      //create_color(::user::color_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_list_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_edit_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_tree_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_view_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_scrollbar_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_tab_layout_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_tab_client_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_split_layout_background, ARGB(255, 255, 255, 255));
      //create_color(::user::color_background_selected, ARGB(255, 155, 185, 255));
      //create_color(::user::color_list_header, ARGB(255, 255, 255, 255));
      //create_color(::user::color_list_header_background, ARGB(255, 0x58, 0x5C, 0x5D));
      //create_color(::user::color_list_item_background, ARGB(30, 0, 0, 0));
      //create_color(::user::color_list_item_background_hover, ARGB(50, 0, 0, 0));
      //create_color(::user::color_list_item_background_selected, ARGB(255, 160, 210, 235));
      //create_color(::user::color_list_item_background_selected_hover, ARGB(255, 160, 220, 255));
      //create_color(::user::color_list_header_separator, 0);
      //create_color(::user::color_toolbar_background, ARGB(255, 0xF3, 0XF5, 0xF5));
      //create_color(::user::color_button_background_disabled, ARGB(255, 128, 128, 128));
      //create_color(::user::color_button_background_hover, ARGB(255, 0x55, 0x99, 0xC2));
      //create_color(::user::color_button_background, ARGB(255, 0x30, 0x75, 0xA0));
      //create_color(::user::color_button_background_press, ARGB(255, 0x07, 0x6D, 0x91));
      //create_color(::user::color_button_text_disabled, ARGB(255, 0xD0, 0xD0, 0xD0));
      //create_color(::user::color_button_text_hover, ARGB(255, 255, 255, 255));
      //create_color(::user::color_button_text, ARGB(255, 255, 255, 255));
      //create_color(::user::color_button_text_press, ARGB(255, 255, 255, 255));

   }


   style::~style()
   {

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::rect rect;
      ::rect rectBorder;
      ::rect rectText;
      ::rect rectClient;
      ::rect rectIcon;
      ::rect rectClose;

      ptab->get_data()->m_pen->create_solid(1,RGB(32,32,32));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      index iTab = -1;

      ::rect rcClient;

      ptab->get_client_rect(rcClient);

      ::draw2d::brush_pointer brushText;

      static int iCurrentTab = -1;

      int iTabWidth = 0;

      int iTabHeight = 0;

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

         if(!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if(!ptab->get_element_rect(iTab,rect, ::user::element_tab))
            continue;

         if(!ptab->get_element_rect(iTab,rectBorder, ::user::element_border))
            continue;

         if(rectBorder.right > iTabWidth)
         {

            iTabWidth = rectBorder.right;

         }

         if(rectBorder.bottom > iTabHeight)
         {

            iTabHeight = rectBorder.bottom;

         }

         if(!ptab->get_element_rect(iTab,rectClient, ::user::element_client))
            continue;

         bool bTextRect = ptab->get_element_rect(iTab, rectText, ::user::element_text);

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }

            ::draw2d::path_pointer path(e_create);

            if(ptab->get_data()->m_idaSel.contains(pane.m_id))
            {

               path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);

               path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectClient.left));

               path->add_line(rectClient.left,rectBorder.top);

               path->add_line(rectBorder.right,rectBorder.top);

               path->close_figure();

               pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,235,235,230),ARGB(250,255,255,250));

               pgraphics->set(pane.m_brushFillSel);

               pgraphics->fill_path(path);

               pgraphics->set(ptab->get_data()->m_penBorderSel);

               pgraphics->draw_path(path);

               //auto pstyle = ptab->get_style(pgraphics);

               if (ptab->m_itemHover == iTab
                  && ptab->m_itemHover != ::user::element_close_tab_button
                  && !ptab->m_itemHover.in_range(::user::element_split, 100))
               {

                  pgraphics->set_font(ptab, ::user::e_state_selected | ::user::e_state_hover);

               }
               else
               {

                  pgraphics->set_font(ptab, ::user::e_state_selected);

               }

               brushText = ptab->get_data()->m_brushTextSel;

            }
            else
            {

               //path->start_figure();

               path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
               path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectClient.left));
               path->add_line(bTextRect ? rectText.left : rectBorder.left,rectBorder.top);
               path->add_line(rectBorder.right,rectBorder.top);
               path->add_line(rectBorder.right,rectBorder.bottom);

               path->close_figure();

               if(ptab->m_itemHover == iTab
                  && ptab->m_itemHover != ::user::element_close_tab_button
                  && !ptab->m_itemHover.in_range(::user::element_split, 100))
               {

                  pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                  pgraphics->set(pane.m_brushFillHover);

                  pgraphics->fill_path(path);

                  pgraphics->set(ptab->get_data()->m_penBorderHover);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab, ::user::e_state_hover);

                  brushText = ptab->get_data()->m_brushTextHover;

               }
               else
               {

                  pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,175,175,170),ARGB(250,195,195,190));

                  pgraphics->set(pane.m_brushFill);

                  pgraphics->fill_path(path);

                  pgraphics->set(ptab->get_data()->m_penBorder);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab);

                  brushText = ptab->get_data()->m_brushText;

               }

            }

         }
         else
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }

            ::draw2d::path_pointer path(e_create);

            if(ptab->get_data()->m_idaSel.contains(pane.m_id))
            {

               if (iPane != iCurrentTab)
               {

                  iCurrentTab = iPane;

                  // output_debug_string("test");

               }

               path->add_line(rectBorder.left,rectClient.bottom,rectBorder.left,rectBorder.top);

               path->add_line(rectClient.right,rectBorder.top);

               path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectClient.right));

               path->add_line(rectBorder.right - 1,rectClient.bottom);

               //path->end_figure(false);

               pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,235,235,230),ARGB(250,255,255,250));

               pgraphics->set(pane.m_brushFillSel);

               pgraphics->fill_path(path);

               ptab->get_data()->m_penBorderSel->create_solid(1.0,ARGB(255,0,0,0));

               pgraphics->set(ptab->get_data()->m_penBorderSel);

               pgraphics->draw_path(path);

               if (ptab->m_itemHover == iTab
                  && ptab->m_itemHover != ::user::element_close_tab_button
                  && !ptab->m_itemHover.in_range(::user::element_split, 100))
               {

                  pgraphics->set_font(ptab, ::user::e_state_selected | ::user::e_state_hover);

               }
               else
               {

                  pgraphics->set_font(ptab, ::user::e_state_selected);

               }

               brushText = ptab->get_data()->m_brushTextSel;

            }
            else
            {

               //path->begin_figure(true, ::draw2d::fill_mode_winding);

               path->add_line(rectBorder.left,rectClient.bottom,rectBorder.left,rectBorder.top);

               path->add_line(rectClient.right,rectBorder.top);

               path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectClient.right));

               path->add_line(rectBorder.right - 1,rectClient.bottom);

               path->close_figure();

               if (ptab->m_itemHover == iTab
                  && ptab->m_itemHover != ::user::element_close_tab_button
                  && !ptab->m_itemHover.in_range(::user::element_split, 100))
               {

                  pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                  pgraphics->set(pane.m_brushFillHover);

                  pgraphics->fill_path(path);

                  pgraphics->set(ptab->get_data()->m_penBorderHover);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab, ::user::e_state_hover);

                  brushText = ptab->get_data()->m_brushTextHover;

               }
               else
               {

                  pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,175,175,170),ARGB(250,195,195,190));

                  pgraphics->set(pane.m_brushFill);

                  pgraphics->fill_path(path);

                  pgraphics->set(ptab->get_data()->m_penBorder);

                  pgraphics->draw_path(path);

                  pgraphics->set_font(ptab);

                  auto& b = ptab->get_data()->m_brushTextSel;

                  brushText = b;

               }

            }

         }

         if(bTextRect)
         {

            _001OnTabPaneDrawTitle(pane,ptab,pgraphics,rectText,brushText);

         }

         if(ptab->get_element_rect(iTab,rectClose, ::user::element_close_tab_button))
         {

            pgraphics->set_font(ptab, ::user::element_close_tab_button);

            if (ptab->m_itemHover == iTab
               && ptab->m_itemHover == ::user::element_close_tab_button)
            {

               brushText = ptab->get_data()->m_brushCloseHover;

            }
            else
            {

               brushText = ptab->get_data()->m_brushClose;

            }

            pgraphics->set(brushText);

            pgraphics->draw_text("x",rectClose,DT_CENTER | DT_VCENTER);

         }

      }

      ::rect rectScroll;

      bool bScroll = ptab->has_tab_scrolling();

      if(bScroll)
      {

         if(ptab->get_element_rect(-1,rectScroll, ::user::element_tab_near_scroll))
         {

            pgraphics->fill_rect(rectScroll, ARGB(255, 255, 255, 255));

         }

         if(ptab->get_element_rect(-1,rectScroll, ::user::element_tab_far_scroll))
         {

            pgraphics->fill_rect(rectScroll, ARGB(255, 255, 255, 255));

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::rect & rect,::draw2d::brush_pointer & brushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), rect, DT_LEFT | DT_BOTTOM | DT_NOPREFIX);

      }
      else
      {

         ::rect rectText(rect);

         ::draw2d::font_pointer font;
         font = pgraphics->get_current_font();
         size sSep = ptab->get_data()->m_sizeSep;
         ::rect rectEmp;
         for(index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size s = pane.m_sizeaText[i];
            rectText.right =rectText.left + s.cx;
            pgraphics->_DrawText(str,rectText,DT_LEFT | DT_BOTTOM | DT_NOPREFIX);
            rectText.left += s.cx;
            if(i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1,1);
               ::draw2d::e_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               ::color colorText;

               if(ptab->m_itemHover == (::index) ::user::element_split + i)
               {

                  pgraphics->fill_rect(rectEmp,ARGB(128, 150, 184, 255));

                  colorText = ptab->get_color(this, ::user::element_item_text, ::user::e_state_hover);

               }
               else
               {

                  colorText = ptab->get_color(this, ::user::element_item_text);

               }

               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(colorText);

               pgraphics->set(brush);

               pgraphics->set_font(ptab, ::user::element_close_tab_button);
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText,DT_CENTER | DT_VCENTER | DT_NOPREFIX);
               rectText.left += sSep.cx;
            }
         }

      }

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab)
   {

      if (!ptab->get_data()->m_bCreated)
      {

         return false;

      }

      auto * pdata = ptab->get_data();

      if (pdata->m_bVertical)
      {

         pdata->m_rectMargin.set(2, 3, 1, 0);

         pdata->m_rectBorder.set(11, 1, 6, 0);

         pdata->m_rectTextMargin.set(3, 0, 1, 0);

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata->m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata->m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata->m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata->m_rectMargin.right;

      }
      else
      {

         pdata->m_rectMargin.set(3, 2, 0, 1);

         pdata->m_rectBorder.set(0, 1, 11, 6);

         pdata->m_rectTextMargin.set(3, 0, 1, 0);

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata->m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata->m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata->m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata->m_rectMargin.right;

      }

      ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set_font(ptab, ::user::e_state_selected);

      ptab->m_dcextension.GetTextExtent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);

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

            tab_pane.do_split_layout(ptab->m_dcextension, pgraphics);

            ::size size;

            ptab->m_dcextension.GetTextExtent(pgraphics,str,size);



            if(tab_pane.m_pimage->is_set())
            {
               size.cx += tab_pane.m_pimage->width() + 2;
               size.cy = max(size.cy,tab_pane.m_pimage->height());
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

         iTabWidth += ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right +
                      ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right +
                      ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data()->m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom +
                       ptab->get_data()->m_rectTextMargin.top + ptab->get_data()->m_rectTextMargin.bottom;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::rect rectClient = ptab->get_client_rect();

         ptab->get_data()->m_rectTab.left       = rectClient.left;
         ptab->get_data()->m_rectTab.top        = rectClient.top;
         ptab->get_data()->m_rectTab.right      = ptab->get_data()->m_rectTab.left + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom     = rectClient.bottom;

         /*      m_puserinteraction->set_window_pos(
         zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left       = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.right : rectClient.left;
         ptab->get_data()->m_rectTabClient.top        = ptab->get_data()->m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right      = rectClient.right;
         ptab->get_data()->m_rectTabClient.bottom     = ptab->get_data()->m_rectTab.bottom;

      }
      else
      {

         i32 iTabHeight = 16;

         i32 cy;

         pgraphics->set_font(ptab, ::user::e_state_selected);

         ::rect rectClient = ptab->get_client_rect();
         //ptab->get_client_rect(rectClient);
         int x = rectClient.left;

         i32 ixAdd;
         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               return false;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension, pgraphics);

            size size;

            ptab->m_dcextension.GetTextExtent(pgraphics, str, size);

            if(::is_ok(tab_pane.m_pimage))
            {

               size.cy = max(size.cy,tab_pane.m_pimage->size().cy);

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            tab_pane.m_point.x = x;
            tab_pane.m_point.y = rectClient.top;


            //            string str = tab_pane.get_title();

            //            size size;

            ixAdd = 5;

            if(::is_ok(tab_pane.m_pimage))
            {
               //::image_list::info ii;
               ixAdd += tab_pane.m_pimage->width() + 2;
            }

            if(!tab_pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            tab_pane.m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

            x += tab_pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data()->m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            tab_pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left       = rectClient.left;
         ptab->get_data()->m_rectTab.top        = rectClient.top;
         ptab->get_data()->m_rectTab.right      = rectClient.right;
         ptab->get_data()->m_rectTab.bottom     = ptab->get_data()->m_rectTab.top + ptab->get_data()->m_iTabHeight;

         /*      set_window_pos(
         zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         rect & rectTabClient = ptab->get_data()->m_rectTabClient;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->GetTopLevelFrame()->layout().is_full_screen();
         bool bTabbedClient = ptab->m_bShowTabs;

         rectTabClient.left = ptab->get_data()->m_rectTab.left;
         rectTabClient.top = bTabbedClient ? ptab->get_data()->m_rectTab.bottom : rectClient.top;
         rectTabClient.right = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom = rectClient.bottom;


         //TRACE0("rectTabClient");
      }

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         if(iPane != ptab->_001GetSel())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->_001GetSel(), ptab->is_this_visible());

      ::rect rcClient;

      ptab->get_client_rect(rcClient);

      if(ptab->get_data()->m_bVertical)
      {

         ptab->m_iTabSize = (int) (ptab->get_data()->m_panea.get_count() * ptab->get_data()->m_iTabHeight);

         ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.height();

      }
      else
      {

         ptab->m_iTabSize = ptab->get_data()->m_panea.last()->m_point.x +
         ptab->get_data()->m_panea.last()->m_size.cx;

         ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.width();

      }


      return true;

   }


   ::color style::get_color(const ::user::interaction* pinteraction, ::user::e_element eelement, ::user::estate estate) const
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::control_type_list)
         {

            if (eelement == ::user::element_background)
            {

               return ::color(0, 0, 0, 0);

            }
            else if (eelement == ::user::element_item_background)
            {

               return ::color(0, 0, 0, 0);

            }
            else if (eelement == ::user::element_item_text)
            {

               return __acolor(255, 40, 40, 40);

            }

         }
         else if (econtroltype == ::user::control_type_tab)
         {
            if (eelement == ::user::element_item_text)
            {

               if(estate & ::user::e_state_hover)
               {

                  return ::color(255, 120, 150, 200);

               }
               else
               {

                  return ::color(255, 0, 0, 0);

               }

            }
            else if (eelement == ::user::element_item_background)
            {

               return ::color(0, 0, 0, 0);

            }


         }

      }

      if (eelement == ::user::element_scrollbar)
      {

         return __acolor(100, 192, 192, 192);

      }
      else if (eelement == ::user::element_scrollbar_rect)
      {

         return __acolor(160, 140, 140, 140);

      }
      else if (eelement == ::user::element_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            return __acolor(255, 192, 192, 192);

         }
         else
         {

            return __acolor(255, 0, 0, 0);

         }

      }

      return ::color();

   }



   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pscrollbar)
   {

      ::color colorBackground = pscrollbar->get_color(this, ::user::element_scrollbar);

      ::rect rectClient = pscrollbar->get_client_rect();

      if (colorBackground.m_iA != 0)
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         if (Session.savings().is_trying_to_save(::aura::resource_processing))
         {

            colorBackground.m_iA = 255;

         }

         pgraphics->fill_rect(rectClient, colorBackground);

      }

      ::rect rectTrack;

      pscrollbar->GetTrackRect(rectTrack);

      ::rect rectWindow;

      pscrollbar->get_window_rect(rectWindow);

      ::color colorBorder = pscrollbar->scrollbar_border_color(this, ::user::element_scrollbar_rect);

      auto pbar = pscrollbar->cast < ::simple_scroll_bar >();

      ::draw2d::pen_pointer penDraw(e_create);

      penDraw->create_solid(1, colorBorder);

      ::color colorTrack = pscrollbar->scrollbar_color(this, ::user::element_scrollbar_rect);

      ::draw2d::brush_pointer brushDraw(e_create);

      brushDraw->create_solid(colorTrack);

      pgraphics->set(penDraw);

      pgraphics->set(brushDraw);

      pgraphics->rectangle(rectTrack);

      if (pbar->m_bTracking || pbar->is_true("tracking_on"))
      {

         DWORD tickFadeIn = 490;

         DWORD tickFadeOut = 490;

         byte uchAlpha = max(0u, min(255u, (byte) pbar->find_u32("tracking_alpha")));

         if (pbar->m_bTracking)
         {

            if (!pbar->is_true("tracking_on"))
            {

               pbar->value("tracking_on") = true;
               pbar->value("tracking_start") = (u32)(::get_tick() + uchAlpha * tickFadeIn / 255);
               pbar->value("tracking_fade_in") = true;
               pbar->value("tracking_fade_out") = false;
               pbar->value("tracking_simple") = __random(1, 2) == 1;

            }

         }
         else
         {

            if (!pbar->value("tracking_fade_out"))
            {

               pbar->value("tracking_fade_in") = false;
               pbar->value("tracking_fade_out") = true;
               pbar->value("tracking_start") = (u32)(::get_tick() + (255 - uchAlpha) * tickFadeOut / 255);

            }

         }

         ::point point1 = rectTrack.top_left() + pbar->m_sizeTrackOffset;

         pbar->_001ClientToScreen(point1);

         ::point point2;

         Session.get_cursor_pos(&point2);

         pbar->_001ClientToScreen(point1);

         //      prop("tracking_window").cast < trw >()->point1 = point1;

         //    prop("tracking_window").cast < trw >()->point2 = point2;

         if (pbar->is_true("tracking_fade_in"))
         {

            auto tickFade = pbar->value("tracking_start").tick().elapsed();

            if (tickFade < tickFadeIn)
            {

               uchAlpha = __byte(tickFade * 255 / tickFadeIn);

            }
            else
            {

               uchAlpha = 255;

               pbar->value("tracking_fade_in") = false;

            }

         }
         else if (pbar->is_true("tracking_fade_out"))
         {

            auto dwFade = pbar->value("tracking_start").tick().elapsed();

            if (dwFade < tickFadeOut)
            {

               uchAlpha = __byte(dwFade * 255 / tickFadeOut);

            }
            else
            {

               uchAlpha = 0;

               pbar->value("tracking_on") = false;

               pbar->value("tracking_fade_out") = false;

            }

         }
         else
         {
            uchAlpha = 255;
         }

         ::rect rectMachineThumb;

         bool bSimple = pbar->is_true("tracking_simple");

         if (bSimple)
         {

            int iSize = rectTrack.size().get_normal(pbar->m_eorientation) * 6 / 8;

            rectMachineThumb.top_left() = rectTrack.top_left() + pbar->m_sizeTrackOffset - size(iSize / 2, iSize / 2);

            rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

            ::rect rectIntersect;

            rectIntersect.intersect(rectMachineThumb, rectTrack);

            i32 iArea = (i32)(max(1, rectIntersect.area()));

            rectMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

         }
         else
         {

            int iSize = rectTrack.size().get_normal(pbar->m_eorientation);

            rectMachineThumb.top_left() = rectTrack.top_left() + pbar->m_sizeTrackOffset - size(iSize / 2, iSize / 2);

            rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

            rectMachineThumb.assign_normal(rectTrack, pbar->m_eorientation);

            rectMachineThumb.constraint_v7(rectTrack);

            rectMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

         }

         pbar->value("tracking_alpha") = uchAlpha;

      }

      ::draw2d::pen_pointer penGrip(e_create);

      penGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::user::element_scrollbar_rect));

      pgraphics->set(penGrip);

      ::point pointCenter = rectTrack.center();

      if (pbar->m_eorientation == orientation_horizontal)
      {


         pgraphics->move_to(pointCenter.x - 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x - 5, pointCenter.y + 5);
         pgraphics->move_to(pointCenter.x, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x, pointCenter.y + 5);
         pgraphics->move_to(pointCenter.x + 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y + 5);


      }
      else
      {
         pgraphics->move_to(pointCenter.x - 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y - 5);
         pgraphics->move_to(pointCenter.x - 5, pointCenter.y);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y);
         pgraphics->move_to(pointCenter.x - 5, pointCenter.y + 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y + 5);

      }


      ::draw2d::pen_pointer penArrow(e_create);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::element_scrollbar_rectA));

      pgraphics->set(penArrow);

      pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::element_scrollbar_rectA));

      pgraphics->set(pbar->m_brushDraw);

      pgraphics->rectangle(pbar->m_rectA);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::element_scrollbar_rectB));

      pgraphics->set(penArrow);

      pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::element_scrollbar_rectB));

      pgraphics->set(pbar->m_brushDraw);

      pgraphics->rectangle(pbar->m_rectB);

      ::rect rect;

      if (pbar->m_itemCurrent == ::user::element_scrollbar_pageA || pbar->m_itemHover == ::user::element_scrollbar_pageA)
      {

         pbar->GetPageARect(rectClient, rectTrack, rect);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::element_scrollbar_pageA));

         pgraphics->set(pbar->m_brushDraw);

         pgraphics->fill_rect(rect);

      }
      else if (pbar->m_itemCurrent == ::user::element_scrollbar_pageB || pbar->m_itemHover == ::user::element_scrollbar_pageB)
      {

         pbar->GetPageBRect(rectClient, rectTrack, rect);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::element_scrollbar_pageB));

         pgraphics->set(pbar->m_brushDraw);

         pgraphics->fill_rect(rect);


      }


      penArrow->m_elinecapBeg = ::draw2d::pen::line_cap_round;
      penArrow->m_elinecapEnd = ::draw2d::pen::line_cap_round;
      penArrow->m_elinejoin = ::draw2d::pen::line_join_round;

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::element_scrollbar_rectA));

      pgraphics->set(penArrow);

      pgraphics->Polyline(pbar->m_ptaA, 3);

      penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::element_scrollbar_rectB));

      pgraphics->set(penArrow);

      pgraphics->Polyline(pbar->m_ptaB, 3);



      return true;



   }


   //bool style::get_color(COLORREF & cr, ::user::e_color ecolor, ::user::style_context * pcontext)
   //{

   //   if (ecolor == ::user::color_background)
   //   {

   //      if (pcontext->m_pstyleSource->get_control_type() != ::user::control_type_none)
   //      {

   //         cr = ARGB(80, 255, 255, 255);

   //      }
   //      else
   //      {

   //         cr = 0;

   //      }

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_background_hover)
   //   {

   //      cr = ARGB(120, 110, 100, 200);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_split_layout_background)
   //   {

   //      cr = ARGB(0, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_list_background)
   //   {

   //      cr = ARGB(80, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_edit_background)
   //   {

   //      cr = ARGB(80, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_edit_background_selected)
   //   {

   //      cr = ARGB(120, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_text)
   //   {

   //      cr = ARGB(255, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_text_selected)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_background_selected)
   //   {

   //      cr = ARGB(128, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_text_highlight)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_background_highlight)
   //   {

   //      cr = ARGB(215, 60, 140, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_text_selected_highlight)
   //   {

   //      cr = ARGB(255, 100, 150, 200);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_background_selected_highlight)
   //   {

   //      cr = ARGB(215, 20, 100, 205);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_edit_text)
   //   {

   //      cr = ARGB(255, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_edit_text_selected)
   //   {

   //      cr = ARGB(255, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_tree_background)
   //   {

   //      cr = ARGB(80, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_view_background)
   //   {

   //      cr = ARGB(80, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_scrollbar_background)
   //   {

   //      cr = ARGB(80, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_list_header)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_list_header_background)
   //   {

   //      cr = ARGB(255, 0x58, 0x5C, 0x5D);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_list_item_background)
   //   {

   //      cr = ARGB(90, 0, 0, 0);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_list_header_separator)
   //   {

   //      cr = 0;

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_toolbar_background)
   //   {

   //      cr = ARGB(80, 0xF3, 0XF5, 0xF5);

   //      return true;


   //   }
   //   else if (ecolor == ::user::color_button_background_disabled)
   //   {

   //      cr = ARGB(255, 128, 128, 128);

   //      return true;


   //   }
   //   else if (ecolor == ::user::color_button_background_hover)
   //   {

   //      cr = ARGB(255, 0x55, 0x99, 0xC2);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_button_background)
   //   {

   //      cr = ARGB(255, 0x30, 0x75, 0xA0);

   //      return true;
   //   }
   //   else if (ecolor == ::user::color_button_background_press)
   //   {

   //      cr = ARGB(255, 0x07, 0x6D, 0x91);

   //      return true;
   //   }
   //   else if (ecolor == ::user::color_button_text_disabled)
   //   {

   //      cr = ARGB(255, 0x80, 0x80, 0x80);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_button_text_hover)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_button_text)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }
   //   else if (ecolor == ::user::color_button_text_press)
   //   {

   //      cr = ARGB(255, 255, 255, 255);

   //      return true;

   //   }

   //   return ::user::style::get_color(cr, ecolor, pcontext);

   //}



   } // namespace aura


} // namespace experience



