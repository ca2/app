#include "framework.h"
#include "base/user/simple/scroll_bar.h"


// pgraphics->GetTextExtent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience
{


   namespace core
   {


      style::style()
      {

         //m_colorBackground = __acolor(127, 255, 255, 255);

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

         auto pstyle = ptab->get_style(pgraphics);

         ::draw2d::brush_pointer brushText(e_create);

         ::draw2d::pen_pointer penBorder(e_create);

         static int iCurrentTab = -1;

         int iTabWidth = 0;

         int iTabHeight = 0;

         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

            if(!pane.m_bTabPaneVisible)
               continue;

            iTab++;

            if(!ptab->get_element_rect(iTab,rect, ::user::e_element_tab))
               continue;

            if(!ptab->get_element_rect(iTab,rectBorder, ::user::e_element_border))
               continue;

            if(rectBorder.right > iTabWidth)
            {

               iTabWidth = rectBorder.right;

            }

            if(rectBorder.bottom > iTabHeight)
            {

               iTabHeight = rectBorder.bottom;

            }

            if(!ptab->get_element_rect(iTab,rectClient, ::user::e_element_client))
               continue;

            bool bTextRect = ptab->get_element_rect(iTab, rectText, ::user::e_element_text);

            if(ptab->get_data()->m_bVertical)
            {

               if(ptab->get_element_rect(iTab,rectIcon, ::user::e_element_icon))
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

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border, ::user::e_state_selected));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::user::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::user::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::user::e_element_none, (::user::e_state_selected | ::user::e_state_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_selected);

                  }

                  brushText->create_solid(ptab->get_color(pstyle, ::user::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(bTextRect ? rectText.left : rectBorder.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.bottom);

                  path->close_figure();

                  if(ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::user::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::user::e_element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border, ::user::e_state_hover));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_hover);

                     brushText->create_solid(ptab->get_color(pstyle, ::user::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,175,175,170),ARGB(250,195,195,190));

                     pgraphics->set(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::user::e_element_none);

                     brushText->create_solid(ptab->get_color(pstyle, ::user::e_element_item_text));

                  }

               }

            }
            else
            {

               if(ptab->get_element_rect(iTab,rectIcon, ::user::e_element_icon))
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

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border, ::user::e_state_hover));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::user::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::user::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_selected | ::user::e_state_hover);

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_selected);

                  }

                  brushText->create_solid(ptab->get_color(pstyle, ::user::e_element_item_text, ::user::e_state_selected));

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
                     && ptab->m_itemHover != ::user::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::user::e_element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border, ::user::e_state_hover));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_hover);

                     brushText->create_solid(ptab->get_color(pstyle, ::user::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ::draw2d::brush_pointer brushFill(e_create);

                     brushFill->CreateLinearGradientBrush(
                        rectBorder.top_left(),
                        rectBorder.bottom_left(),
                        ARGB(230, 175, 175, 170),
                        ARGB(250, 195, 195, 190)); //*/

                        // brushFill->create_solid(::color::white);

                     pgraphics->set(brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::user::e_element_border));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::user::e_element_none);

                     auto colorText = ptab->get_color(pstyle, ::user::e_element_item_text);

                     brushText->create_solid(colorText);

                  }

               }

            }

            if(bTextRect)
            {

               _001OnTabPaneDrawTitle(pane,ptab,pgraphics,rectText,brushText);

            }

            if(ptab->get_element_rect(iTab,rectClose, ::user::e_element_close_tab_button))
            {

               pgraphics->set_font(ptab, ::user::e_element_close_tab_button);

               if (ptab->m_itemHover == iTab
                  && ptab->m_itemHover == ::user::e_element_close_tab_button)
               {

                  brushText = ptab->get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = ptab->get_data()->m_brushClose;

               }

               pgraphics->set(brushText);

               pgraphics->draw_text("x",rectClose,e_align_center);

            }

         }

         ::rect rectScroll;

         bool bScroll = ptab->has_tab_scrolling();

         if(bScroll)
         {

            if(ptab->get_element_rect(-1,rectScroll, ::user::e_element_tab_near_scroll))
            {

               pgraphics->fill_rect(rectScroll, ARGB(255, 255, 255, 255));

            }

            if(ptab->get_element_rect(-1,rectScroll, ::user::e_element_tab_far_scroll))
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

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->_DrawText(pane.get_title(), rect, e_align_bottom_left, e_draw_text_no_prefix);

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

               pgraphics->_DrawText(str,rectText, e_align_bottom_left, e_draw_text_no_prefix);

               rectText.left += s.cx;

               if(i < straTitle.get_upper_bound())
               {

                  rectText.right = rectText.left + sSep.cx;

                  rectEmp = rectText;

                  rectEmp.deflate(1, 1);

                  ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;

                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                  ::color colorText;

                  if(ptab->m_itemHover == (::index) ::user::e_element_split + i)
                  {

                     pgraphics->fill_rect(rectEmp,ARGB(128, 150, 190, 255));

                     colorText = ptab->get_color(this, ::user::e_element_item_text, ::user::e_state_hover);

                  }
                  else
                  {

                     colorText = ptab->get_color(this, ::user::e_element_item_text);

                  }

                  ::draw2d::brush_pointer brush(e_create);

                  brush->create_solid(colorText);

                  pgraphics->set(brush);

                  pgraphics->set_font(ptab, ::user::e_element_close_tab_button);

                  pgraphics->set_alpha_mode(emode);

                  pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText, e_align_center, e_draw_text_no_prefix);

                  rectText.left += sSep.cx;

               }

            }

         }

      }


      bool style::_001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
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

         pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_selected);

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

            pgraphics->set_font(ptab, ::user::e_element_none, ::user::e_state_selected);

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

            //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
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


      ::color style::get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate) const
      {

         if (::is_set(pinteraction))
         {

            string strType = pinteraction->type_c_str();

            if (strType.contains("form"))
            {

               output_debug_string("form");

            }

            auto econtroltype = pinteraction->get_control_type();

            if (econtroltype == ::user::e_control_type_form)
            {

               if (eelement == ::user::e_element_background)
               {

                  if (::user::is_app_dark_mode())
                  {

                     return ::color(80, 80, 80, 127);

                  }
                  else
                  {

                     return ::color(255, 255, 255, 127);

                  }

               }

            }
            else if (econtroltype == ::user::e_control_type_edit)
            {

               if (estate & ::user::e_state_selected)
               {

                  if (eelement == ::user::e_element_background)
                  {

                     if (::user::is_app_dark_mode())
                     {

                        return ::color(255, 255, 255, 127);

                     }
                     else
                     {

                        return ::color(80, 80, 80, 127);

                     }

                  }
                  else if (eelement == ::user::e_element_text)
                  {

                     if (::user::is_app_dark_mode())
                     {

                        return ::color(80, 80, 80, 255);

                     }
                     else
                     {

                        return ::color(255, 255, 255, 255);

                     }

                  }

               }
               else
               {

                  if (eelement == ::user::e_element_background)
                  {

                     if (::user::is_app_dark_mode())
                     {

                        return ::color(80, 80, 80, 127);

                     }
                     else
                     {

                        return ::color(255, 255, 255, 127);

                     }

                  }
                  else if (eelement == ::user::e_element_text)
                  {

                     if (::user::is_app_dark_mode())
                     {

                        return ::color(255, 255, 255, 255);

                     }
                     else
                     {

                        return ::color(80, 80, 80, 255);

                     }

                  }

               }

            }
            else if (econtroltype == ::user::e_control_type_list
            || econtroltype == ::user::e_control_type_tree)
            {

               if (eelement == ::user::e_element_background)
               {

                  if (::user::is_app_dark_mode())
                  {

                     return ::color(80, 80, 80, 127);

                  }
                  else
                  {

                     return ::color(255, 255, 255, 127);

                  }
               }
               else if (eelement == ::user::e_element_item_background)
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return __acolor(127, 0, 0, 0);

                  }
                  else
                  {

                     return ::color(0, 0, 0, 0);

                  }

               }
               else if (eelement == ::user::e_element_item_text)
               {

                  if (::user::is_app_dark_mode())
                  {

                     return __acolor(255, 230, 230, 230);

                  }
                  else
                  {

                     return __acolor(255, 40, 40, 40);

                  }

               }

            }
            else if (econtroltype == ::user::e_control_type_tab)
            {

               if (eelement == ::user::e_element_item_text)
               {

                  if(estate & ::user::e_state_hover)
                  {

                     return ::color(255, 120, 150, 200);

                  }
                  else
                  {

                     if (::user::is_app_dark_mode())
                     {

                        return __acolor(255, 230, 230, 230);

                     }
                     else
                     {

                        return __acolor(255, 40, 40, 40);

                     }

                  }

               }
               else if (eelement == ::user::e_element_item_background)
               {

                  return ::color(0, 0, 0, 0);

               }

            }

         }
         
         if (eelement == ::user::e_element_check)
         {

            //if (estate & ::user::e_state_hover)
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 255, 255, 255);

               }
               else
               {

                  return __acolor(255, 0, 0, 0);

               }

            }

         }
         else if (eelement == ::user::e_element_border)
         {

            if (estate & ::user::e_state_hover)
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 255, 255, 255);

               }
               else
               {

                  return __acolor(255, 0, 0, 0);

               }

            }
            else if (estate & ::user::e_state_selected)
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 255, 255, 255);

               }
               else
               {

                  return __acolor(255, 0, 0, 0);

               }

            }
            else
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 210, 210, 200);

               }
               else
               {

                  return __acolor(255, 90, 90, 80);

               }

            }

         }
         else if (eelement == ::user::e_element_scrollbar)
         {

            return __acolor(100, 192, 192, 192);

         }
         else if (eelement == ::user::e_element_scrollbar_rect)
         {

            return __acolor(160, 140, 140, 140);

         }
         else if (eelement == ::user::e_element_item_text)
         {

            if (estate & ::user::e_state_new_input)
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 130, 130, 130);

               }
               else
               {

                  return __acolor(255, 192, 192, 192);

               }

            }
            else
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 230, 230, 230);

               }
               else
               {

                  return __acolor(255, 40, 40, 40);

               }

            }

         }
         else if (eelement == ::user::e_element_text)
         {

            if (estate & ::user::e_state_new_input)
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 130, 130, 130);

               }
               else
               {

                  return __acolor(255, 192, 192, 192);

               }

            }
            else
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 230, 230, 230);

               }
               else
               {

                  return __acolor(255, 40, 40, 40);

               }

            }

        }
        else if (eelement == ::user::e_element_background)
        {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(127, 80, 80, 80);

               }
               else
               {

                  return __acolor(127, 210, 210, 210);

               }

            }
            else
            {

               if (::user::is_app_dark_mode())
               {

                  return __acolor(255, 230, 230, 230);

               }
               else
               {

                  return __acolor(255, 40, 40, 40);

               }

            }

         return ::color();

      }


      bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pscrollbar)
      {

         ::color colorBackground = pscrollbar->get_color(this, ::user::e_element_scrollbar);

         ::rect rectClient = pscrollbar->get_client_rect();

         if (colorBackground.m_iA != 0)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            auto psession = Session;

            if (psession->savings().is_trying_to_save(::e_resource_processing))
            {

               colorBackground.m_iA = 255;

            }

            pgraphics->fill_rect(rectClient, colorBackground);

         }

         ::rect rectTrack;

         pscrollbar->GetTrackRect(rectTrack, pgraphics);

         ::rect rectWindow;

         pscrollbar->get_window_rect(rectWindow);

         ::color colorBorder = pscrollbar->scrollbar_border_color(this, ::user::e_element_scrollbar_rect);

         auto pbar = pscrollbar->cast < ::simple_scroll_bar >();

         ::draw2d::pen_pointer penDraw(e_create);

         penDraw->create_solid(1, colorBorder);

         ::color colorTrack = pscrollbar->scrollbar_color(this, ::user::e_element_scrollbar_rect);

         ::draw2d::brush_pointer brushDraw(e_create);

         brushDraw->create_solid(colorTrack);

         pgraphics->set(penDraw);

         pgraphics->set(brushDraw);

         pgraphics->rectangle(rectTrack);

         if (pbar->m_bTracking || pbar->is_true("tracking_on"))
         {

            ::u32 tickFadeIn = 490;

            ::u32 tickFadeOut = 490;

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

            auto psession = Session;

            psession->get_cursor_pos(&point2);

            pbar->_001ClientToScreen(point1);

            //      prop("tracking_window").cast < trw >()->point1 = point1;

            //    prop("tracking_window").cast < trw >()->point2 = point2;

            if (pbar->is_true("tracking_fade_in"))
            {

               auto tickFade = pbar->value("tracking_start").millis().elapsed();

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

               auto dwFade = pbar->value("tracking_start").millis().elapsed();

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

         penGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::user::e_element_scrollbar_rect));

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

         penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::e_element_scrollbar_rectA));

         pgraphics->set(penArrow);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::e_element_scrollbar_rectA));

         pgraphics->set(pbar->m_brushDraw);

         pgraphics->rectangle(pbar->m_rectA);

         penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::e_element_scrollbar_rectB));

         pgraphics->set(penArrow);

         pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::e_element_scrollbar_rectB));

         pgraphics->set(pbar->m_brushDraw);

         pgraphics->rectangle(pbar->m_rectB);

         ::rect rect;

         if (pbar->m_itemCurrent == ::user::e_element_scrollbar_pageA || pbar->m_itemHover == ::user::e_element_scrollbar_pageA)
         {

            pbar->GetPageARect(rectClient, rectTrack, rect, pgraphics);

            pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::e_element_scrollbar_pageA));

            pgraphics->set(pbar->m_brushDraw);

            pgraphics->fill_rect(rect);

         }
         else if (pbar->m_itemCurrent == ::user::e_element_scrollbar_pageB || pbar->m_itemHover == ::user::e_element_scrollbar_pageB)
         {

            pbar->GetPageBRect(rectClient, rectTrack, rect, pgraphics);

            pbar->m_brushDraw->create_solid(pbar->scrollbar_color(this, ::user::e_element_scrollbar_pageB));

            pgraphics->set(pbar->m_brushDraw);

            pgraphics->fill_rect(rect);

         }

         penArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
         penArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
         penArrow->m_elinejoin = ::draw2d::e_line_join_round;

         penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::e_element_scrollbar_rectA));

         pgraphics->set(penArrow);

         pgraphics->polyline(pbar->m_ptaA, 3);

         penArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::user::e_element_scrollbar_rectB));

         pgraphics->set(penArrow);

         pgraphics->polyline(pbar->m_ptaB, 3);

         return true;

      }


   } // namespace core


} // namespace experience



