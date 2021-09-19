#include "framework.h"
#include "base/user/user/tab_pane.h"
//#include "core/user/userex/_userex.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience
{


namespace tranquillum

{


   style::style()
      //m_fontEdit(e_create),
      //m_fontList(e_create)
   {

//      m_fontEdit->create_point_font("MS Sans Serif", 9.0);

      //    m_fontList->create_point_font(pnode->font_name(e_font_sans_ui), 10, e_font_weight_bold);

      //theme_current_control(::user::control_none);

      //create_translucency(::e_element_none, ::user::e_translucency_none);

      //create_point_font(::user::font_default,pnode->font_name(e_font_sans_ui), 12.0);
      //create_point_font(::user::font_button, pnode->font_name(e_font_sans_ui), 12.0, 800);
      //create_point_font(::user::font_plain_edit, pnode->font_name(e_font_sans_ui), 12.0, 800);
      //create_point_font(::user::font_list_header, pnode->font_name(e_font_sans_ui), 12.0, 800);

      //create_point_font(::user::font_tab, pnode->font_name(e_font_sans_ui), 13.0, 400);
      //{
      //   auto font = create_point_font(::user::font_tab_hover, pnode->font_name(e_font_sans_ui), 13.0, 400);
      //   font->m_bUnderline = true;
      //}
      //create_point_font(::user::font_tab_sel, pnode->font_name(e_font_sans_ui), 13.0, 800);
      //{
      //   auto font = create_point_font(::user::font_tab_sel_hover, pnode->font_name(e_font_sans_ui), 13.0, 800);
      //   font->m_bUnderline = true;
      //}
      //create_point_font(::user::font_tab_big_bold, pnode->font_name(e_font_sans_ui), 13.0, 800);

      //create_rect_coord(::user::rect_edit_padding, 0.2, 0.2, 0.2, 0.2);

      //create_double(::user::double_list_item_height_rate, 1.65);

      //create_pixel_rect_coord(::user::rect_menu_item_padding, 5, 5, 5, 5);

      //create_int(::user::int_element_padding, 4);

      //m_colorBackground = argb(255, 255, 255, 255);
      //m_colorText = argb(255, 0, 0, 0);


      //create_color(::user::color_background, argb(255, 255, 255, 255));
      //create_color(::user::color_text, argb(255, 0, 0, 0));
      //create_color(::user::color_edit_text, argb(255, 0, 0, 0));
      //create_color(::user::color_edit_text_selected, argb(255, 255, 255, 255));
      //create_color(::user::color_edit_background_selected, argb(255, 100, 150, 230));
      //create_color(::user::color_text_selected, argb(255, 255, 255, 255));
      //create_color(::user::color_text_selected_highlight, argb(255, 255, 255, 255));
      //create_color(::user::color_text_highlight, argb(255, 255, 255, 255));
      //create_color(::user::color_text_hover, argb(255, 20, 55, 255));
      //create_color(::user::color_background_selected, argb(255, 100, 150, 230));
      //create_color(::user::color_background_selected_highlight, argb(255, 110, 180, 240));
      //create_color(::user::color_background_highlight, argb(255, 120, 200, 250));
      //create_color(::user::color_background_hover, argb(255, 120, 200, 250));
      //create_color(::user::color_background_selected_hover, argb(255, 130, 220, 252));
      //create_color(::user::color_background, argb(255, 255, 255, 255));
      //create_color(::user::color_button_text, argb(255, 255, 255, 255));
      //create_color(::user::color_list_header, argb(255, 40, 40, 40));
      //create_color(::user::color_list_header_background, argb(255, 230, 230, 230));
      //create_color(::user::color_list_background, argb(255, 255, 255, 255));
      //create_color(::user::color_list_item_text, argb(255, 50, 50, 50));
      //create_color(::user::color_list_item_text_hover, argb(255, 50, 50, 50));
      //create_color(::user::color_list_item_text_selected, argb(255, 250, 250, 250));
      //create_color(::user::color_list_item_text_selected_hover, argb(255, 250, 250, 250));
      //create_color(::user::color_list_item_background, argb(255, 255, 255, 255));
      //create_color(::user::color_list_item_background_hover, argb(255, 205, 235, 255));
      //create_color(::user::color_list_item_background_selected, argb(255, 100, 150, 230));
      //create_color(::user::color_list_item_background_selected_hover, argb(255, 130, 180, 240));
      //create_color(::user::color_button_background, argb(255, 80, 150, 220));
      //create_color(::user::color_button_background_hover, argb(255, 110, 180, 240));
      //create_color(::user::color_button_background_press, argb(255, 95, 165, 230));
      //create_color(::user::color_button_background_disabled, argb(255, 160, 160, 160));
      //create_color(::user::color_button_text, argb(255, 255, 255, 255));
      //create_color(::user::color_button_text_hover, argb(255, 255, 255, 255));
      //create_color(::user::color_button_text_press, argb(255, 255, 255, 255));
      //create_color(::user::color_button_text_disabled, argb(255, 200, 210, 220));
      //create_color(::user::color_scrollbar_strong, argb(255, 210, 210, 210));
      //create_color(::user::color_scrollbar_strong_hover, argb(255, 200, 200, 200));
      //create_color(::user::color_scrollbar, argb(255, 230, 230, 230));
      //create_color(::user::color_scrollbar_hover, argb(255, 225, 225, 225));


   }


   style::~style()
   {

   }


   ::color::color style::get_color(const ::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate) const
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_tab)
         {

         }
         else if (econtroltype == ::user::e_control_type_button)
         {

            if (eelement == ::e_element_background)
            {

               return argb(255, 116, 160, 220);

            }

         }
         else if (econtroltype == ::user::e_control_type_list)
         {

            if (eelement == ::e_element_background)
            {

               if (estate & ::user::e_state_selected)
               {

                  return argb(255, 80, 80, 80);

               }
               else
               {

                  return ::color::color(0, 0, 0, 0);

               }

            }

         }

      }

      if (eelement == ::e_element_background)
      {

         if (estate & ::user::e_state_selected)
         {

            return argb(255, 80, 80, 80);

         }
         else
         {

            return ::color::color(255, 255, 255, 255);

         }


         
      }
      else if (eelement == ::e_element_text)
      {



         if (estate & ::user::e_state_new_input)
         {
            return argb(255, 192, 192, 192);

         }
         else if (estate & ::user::e_state_selected)
         {

            return argb(255, 255, 255, 255);

         }
         else
         {

            return argb(255, 80, 80, 80);

         }

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            return argb(255, 192, 192, 192);

         }
         else if (estate & ::user::e_state_selected)
         {

            return argb(255, 255, 255, 255);

         }
         else
         {

            return argb(255, 80, 80, 80);

         }

      }
      else if (eelement == ::e_element_item_background)
      {

         if (estate & ::user::e_state_new_input)
         {

            return argb(255, 192, 192, 192);

         }
         else if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_selected)
            {

               return argb(255, 40, 40, 80);

            }
            else
            {
               return argb(255, 120, 120, 180);

            }

         }
         else if (estate & ::user::e_state_selected)
         {

            return argb(255, 40, 40, 40);

         }
         else
         {

            return argb(255, 255, 255, 255);

         }

      }


      return ::base::style::get_color(pinteraction, eelement, estate);

   }


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame * pframe)
   {


      ::draw2d::savedc k(pgraphics);

      pgraphics->m_puserinteraction = pframe;

      if (!pframe->is_custom_draw() && pgraphics != nullptr && pgraphics->m_pnext == nullptr)
      {

         pframe->set_viewport_org(pgraphics);

      }

      auto rectangleClient = pframe->get_client_rect();

      auto pstyle = pframe->get_style(pgraphics);

      status < ::color::color > crBackground = pframe->get_color(pstyle, ::e_element_background);

      //crBackground = argb(255, 200, 180, 180);

      pgraphics->fill_rectangle(rectangleClient, crBackground);

      return true;

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab)
   {

      if (!ptab->get_data()->m_bCreated)
         return false;

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

      ptab->m_dcextension.get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, ptab->get_data()->m_sizeSep);

      if (ptab->get_data()->m_bVertical)
      {
         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;
         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto & pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            if (!pane.m_bTabPaneVisible)
            {

               continue;

            }

            string str = pane.get_title();

            pane.do_split_layout(ptab->m_dcextension, pgraphics);

            ::size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics, str, size);



            if (pane.m_pimage->is_set())
            {
               size.cx += pane.m_pimage->width() + 2;
               size.cy = maximum(size.cy, pane.m_pimage->height());
            }
            cx = size.cx + 2;

            if (!pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if (cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy + 2;
            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
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

         ::rectangle_i32 rectangleClient;
         ptab->get_client_rect(rectangleClient);

         ptab->get_data()->m_rectTab.left = rectangleClient.left;
         ptab->get_data()->m_rectTab.top = rectangleClient.top;
         ptab->get_data()->m_rectTab.right = ptab->get_data()->m_rectTab.left + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom = rectangleClient.bottom;

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.right : rectangleClient.left;
         ptab->get_data()->m_rectTabClient.top = ptab->get_data()->m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right = rectangleClient.right;
         ptab->get_data()->m_rectTabClient.bottom = ptab->get_data()->m_rectTab.bottom;

      }
      else
      {
         i32 iTabHeight = 16;
         i32 cy;
         pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::rectangle_i32 rectangleClient;
         ptab->get_client_rect(rectangleClient);
         int x = rectangleClient.left;

         i32 ixAdd;
         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto & pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            if (!pane.m_bTabPaneVisible)
            {

               return false;

            }

            string str = pane.get_title();

            pane.do_split_layout(ptab->m_dcextension, pgraphics);

            ::size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics, str, size);

            ::write_text::text_metric metric;

            pgraphics->get_text_metrics(&metric);

            if (pane.m_pimage->is_set())
            {

               size.cy = (::i32) maximum(maximum(size.cy, pane.m_pimage->size().cy), metric.get_line_spacing());

            }

            cy = size.cy + 2;

            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            pane.m_point.x = x;
            pane.m_point.y = rectangleClient.top;


            //            string str = pane.get_title();

            //            ::size_i32 size;

            ixAdd = 5;

            if (pane.m_pimage->is_set())
            {
               //::image_list::info ii;
               ixAdd += pane.m_pimage->width() + 2;
            }

            if (!pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            pane.m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

            x += pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data()->m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight + 8;

         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto & pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left = rectangleClient.left;
         ptab->get_data()->m_rectTab.top = rectangleClient.top;
         ptab->get_data()->m_rectTab.right = rectangleClient.right;
         ptab->get_data()->m_rectTab.bottom = ptab->get_data()->m_rectTab.top + ptab->get_data()->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         rectangle_i32 & rectTabClient = ptab->get_data()->m_rectTabClient;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
         bool bTabbedClient = ptab->m_bShowTabs;

         rectTabClient.left = ptab->get_data()->m_rectTab.left;
         rectTabClient.top = bTabbedClient ? ptab->get_data()->m_rectTab.bottom : rectangleClient.top;
         rectTabClient.right = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom = rectangleClient.bottom;


         //TRACE0("rectTabClient");

      }

      for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         if (iPane != ptab->get_current_tab_index())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->get_current_tab_index(), ptab->is_window_visible());

      return true;

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectBorder;
      ::rectangle_i32 rectText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectIcon;
      ::rectangle_i32 rectClose;

      ::rectangle_i32 r1;
      ptab->get_client_rect(r1);

      if (!ptab->get_data()->m_bNoClient)
      {

         pgraphics->fill_rectangle(r1, argb(255, 255, 255, 255));

      }

      ptab->get_data()->m_pen->create_solid(1, rgb(32, 32, 32));

      //pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rcTab;

      rcTab = ptab->get_data()->m_rectTab;

      if (ptab->get_data()->m_bNoClient)
      {

         pgraphics->fill_rectangle(rcTab, argb(255, 255, 255, 255));

      }
      ::rectangle_i32 rcTape(rcTab);

      rcTape.top = rcTape.bottom - 8;

      pgraphics->fill_rectangle(rcTape, argb(255, 192, 192, 192));


      ::rectangle_i32 rcTabs(rcTab);

      ::rectangle_i32 rcClient;

      rcClient = ptab->get_data()->m_rectTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectBorder.bottom;

      rcClient.top = rcTabs.bottom;

      auto pstyle = ptab->get_style(pgraphics);

      auto crbk = ptab->get_color(pstyle, ::e_element_tab_layout_background);

      pgraphics->fill_rectangle(rcTabs, crbk);

      crbk = ptab->get_color(pstyle, ::e_element_tab_client_background);

      pgraphics->fill_rectangle(rcClient, crbk);

      ::index iTab = -1;

      ::draw2d::brush_pointer brushText(e_create);

      ::draw2d::pen_pointer penBorder(e_create);

      for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         auto & pane = *ptab->get_data()->m_tabpanecompositea[iPane];

         if (!pane.m_bTabPaneVisible)
         {

            continue;

         }

         iTab++;

         if (!ptab->get_element_rect(iTab, rectangle, ::e_element_tab))
         {

            continue;

         }

         if (!ptab->get_element_rect(iTab, rectBorder, ::e_element_border))
         {

            continue;

         }

         if (!ptab->get_element_rect(iTab, rectangleClient, ::e_element_client))
         {

            continue;

         }

         if (ptab->get_data()->m_bVertical)
         {

            if (ptab->get_element_rect(iTab, rectIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pane.m_pimage);

               image_drawing_options imagedrawingoptions(rectIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            ::draw2d::path_pointer path(e_create);

            if (true)
            {

               if (ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  ::rectangle_i32 rSel;

                  rSel = rectangleClient;

                  rSel.bottom = rectangleClient.top + 3;

                  pgraphics->fill_rectangle(rSel, argb(255, 120, 155, 240));

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected | ::user::e_state_hover);

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

                  }

                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  pgraphics->set(brushText);

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right, rectBorder.bottom, rectBorder.left + 1, rectBorder.bottom);
                  path->add_line(rectBorder.left, rectBorder.top - (rectBorder.left - rectangleClient.left));
                  path->add_line(rectText.left, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.bottom);

                  path->close_figure();

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                     pgraphics->set(brushText);

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::e_element_none);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if (ptab->get_element_rect(iTab, rectIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pane.m_pimage);

               image_drawing_options imagedrawingoptions(rectIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            //if (iPane == 0)
            //{

            //   if (rcTab.left < rectBorder.left)
            //   {

            //      pgraphics->set(ptab->get_data()->m_penBorder);

            //      pgraphics->draw_line(rcTab.left, rectangleClient.bottom, rectBorder.left, rectangleClient.bottom);

            //   }

            //}

            if (true)
            {

               ::draw2d::path_pointer path(e_create);

               if (ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  ::rectangle_i32 rSel;

                  rSel = rectangle;

                  rSel.bottom = rectangleClient.top + 3;

                  pgraphics->fill_rectangle(rSel, argb(255, 120, 155, 240));

                  pane.m_brushFillSel->create_solid(argb(255, 255, 255, 255));

                  pgraphics->set(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);


                  }

                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));
                     
                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab, ::e_element_none);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

            ::rectangle_i32 rVertLine;

            rVertLine = rectangle;

            rVertLine.left = rVertLine.right - 1;
            pgraphics->fill_rectangle(rVertLine, argb(127, 80, 80, 80));

            //if (iPane == ptab->get_data()->m_panea.get_upper_bound())
            //{

            //   if (rectBorder.right - 1 < rcTab.right)
            //   {

            //      pgraphics->set(ptab->get_data()->m_penBorder);

            //      pgraphics->draw_line(rectBorder.right - 1, rectangleClient.bottom, rcTab.right, rectangleClient.bottom);

            //   }

            //}


         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(pane, ptab, pgraphics, rectText, brushText);

            }

         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectClose, ::e_element_close_tab_button))
            {

               pgraphics->set_font(ptab, ::e_element_close_tab_button);

               if (ptab->m_itemHover == iTab
                  && ptab->m_itemHover == ::e_element_close_tab_button)
               {

                  brushText = ptab->get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = ptab->get_data()->m_brushClose;

               }

               pgraphics->set(brushText);

               pgraphics->draw_text("x", rectClose, e_align_center);

            }

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::rectangle_i32 & rectParam,::draw2d::brush_pointer & brushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), rectParam, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rectangle_i32 rectText(rectParam);

         ::write_text::font_pointer font;

         font = pgraphics->get_current_font();

         size_i32 sSep = ptab->get_data()->m_sizeSep;

         auto pstyle = ptab->get_style(pgraphics);

         ::rectangle_i32 rectEmp;

         for(index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size_i32 s = pane.m_sizeaText[i];
            rectText.right =rectText.left + s.cx;
            pgraphics->_DrawText(str,rectText,e_align_bottom_left, e_draw_text_no_prefix);
            rectText.left += s.cx;
            if(i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1,1);
               ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
               if(ptab->m_itemHover.m_iItem == ((int) ::e_element_split) + i)
               {
                  
                  pgraphics->fill_rectangle(rectEmp,argb(128,149,184,255));
                  
                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));
                  
                  pgraphics->set(brushText);

               }
               else
               {

                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));
                  
                  pgraphics->set(brushText);

               }

               pgraphics->set_font(ptab, ::e_element_close_tab_button);
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText, e_align_center, e_draw_text_no_prefix);
               rectText.left += sSep.cx;

            }

         }

      }

   }





//   bool style::on_ui_event(::enum_subject esubject, ::user::e_object eobject, ::user::interaction * pframewindow)
//   {
//
//      if (eevent == ::e_subject_calc_item_height)
//      {
//
//         pframewindow->m_iItemHeight += 8;
//
//         return true;
//
//      }
//
//      return false;
//
//   }


//   bool style::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
//   {
//
////      if (1)
//      {
//
//         _001DrawTranquillumToolbarItem(pgraphics, iItem, ptoolbar);
//
//      }
////      else
////      {
////
////         _001DrawSimpleToolbarItem(pgraphics, iItem, ptoolbar);
////
////      }
//
//      return true;
//
//   }


   //void style::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
   //{

   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   ::rectangle_i32 rectItem;

   //   ::rectangle_i32 rectImage;

   //   pgraphics->set_font(ptoolbar);

   //   ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

   //   ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

   //   bool bHover = ptoolbar->m_itemHover == iItem;

   //   ::u32 uImage = psession->userex()->menu()->command_image(item.m_id);

   //   ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
   //   ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
   //   ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
   //   if ((nStyle & e_toolbar_item_style_separator) == 0)
   //   {
   //      if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //      {
   //         // item is enabled
   //         if (ptoolbar->m_iButtonPressItem >= 0)
   //         {
   //            if (iItem == ptoolbar->m_iButtonPressItem)
   //            {
   //               if (bHover)
   //               {
   //                  eelement = ::user::toolbar::element_item_press;
   //                  eelementImage = ::user::toolbar::element_image_press;
   //                  eelementText = ::user::toolbar::element_text_press;
   //               }
   //               else
   //               {
   //                  eelement = ::user::toolbar::element_item_hover;
   //                  eelementImage = ::user::toolbar::element_image_hover;
   //                  eelementText = ::user::toolbar::element_text_hover;
   //               }
   //            }
   //         }
   //         else if (bHover)
   //         {
   //            eelement = ::user::toolbar::element_item_hover;
   //            eelementImage = ::user::toolbar::element_image_hover;
   //            eelementText = ::user::toolbar::element_text_hover;
   //         }
   //      }
   //      else
   //      {
   //         // item is disabled
   //         eelement = ::user::toolbar::e_element_item;
   //         eelementImage = ::user::toolbar::element_image;
   //         eelementText = ::user::toolbar::e_element_text;
   //      }
   //   }
   //   else
   //   {
   //      eelement = ::user::toolbar::e_element_item;
   //      eelementImage = ::user::toolbar::element_image;
   //      eelementText = ::user::toolbar::e_element_text;
   //   }


   //   //int iOffsetX = 0;
   //   //int iOffsetY = 0;

   //   ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

   //   ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

   //   if ((nStyle & e_toolbar_item_style_separator) != 0)
   //   {
   //      ::rectangle_i32 rectSeparator;
   //      rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
   //      rectSeparator.right = rectSeparator.left + 2;
   //      rectSeparator.top = rectImage.top;
   //      rectSeparator.bottom = rectImage.bottom;
   //      pgraphics->draw3d_rect(rectSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
   //   }
   //   else
   //   {
   //      if (eelement == ::user::toolbar::element_item_hover)
   //      {
   //         if ((nStyle & TBBS_CHECKED) != 0)
   //         {

   //            ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::e_element_item);

   //            ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

   //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //            {
   //               psystem->imaging().color_blend(
   //               pgraphics,
   //               rectItem.left,
   //               rectItem.top,
   //               rectItem.width(),
   //               rectItem.height(),
   //               rgb(255, 255, 250), 208);

   //               pgraphics->draw3d_rect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

   //            }

   //            if (uImage != 0xffffffffu)
   //            {

   //               if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //               {

   //                  // button is enabled
   //                  psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //               }
   //               else
   //               {

   //                  // button is disabled
   //                  psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //               }

   //            }

   //         }
   //         else
   //         {

   //            ::rectangle_i32 rectShadow;

   //            ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::element_item_hover);

   //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //            {

   //               ::draw2d::pen_pointer pen(e_create);

   //               pen->create_solid(1, argb(184, 92, 184, 92));

   //               ::draw2d::brush_pointer brush(e_create);

   //               brush->create_solid(argb(123, 177, 184, 255));

   //               ::draw2d::pen * ppenOld = pgraphics->set(pen);
   //               ::draw2d::brush * pbrushOld = pgraphics->set(brush);
   //               pgraphics->rectangle(rectItem);
   //               pgraphics->set(ppenOld);
   //               pgraphics->set(pbrushOld);

   //            }

   //            if (item.m_pimage->is_set())
   //            {

   //               ::rectangle_i32 rectangle;

   //               ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image_hover);

   //               pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.80);

   //            }
   //            else if (uImage != 0xffffffffu)
   //            {

   //               ::rectangle_i32 rectangle;

   //               ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_item_hover);

   //               psession->userex()->menu()->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

   //               psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
   //            }

   //         }

   //      }
   //      else if (eelement == ::user::toolbar::element_item_press)
   //      {

   //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //         {

   //            ::draw2d::pen_pointer pen(e_create);

   //            pen->create_solid(1, argb(255, 92, 92, 92));
   //            ::draw2d::brush_pointer brush(e_create);

   //            brush->create_solid(argb(255, 255, 255, 255));
   //            ::draw2d::pen * ppenOld = pgraphics->set(pen);
   //            ::draw2d::brush * pbrushOld = pgraphics->set(brush);
   //            pgraphics->rectangle(rectItem);
   //            pgraphics->set(ppenOld);
   //            pgraphics->set(pbrushOld);

   //         }

   //         if (item.m_pimage->is_set())
   //         {

   //            ::rectangle_i32 rectangle;

   //            ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image_press);

   //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 1.0);

   //         }
   //         else if (uImage != 0xffffffff)
   //         {

   //            psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //         }

   //      }
   //      else
   //      {

   //         if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //         {

   //            ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::e_element_item);

   //            pgraphics->fill_rectangle(rectItem, argb(184, 255, 255, 255));

   //         }

   //         if ((nStyle & TBBS_CHECKED) != 0)
   //         {

   //            pgraphics->draw3d_rect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

   //         }

   //         if (item.m_pimage->is_set())
   //         {

   //            ::rectangle_i32 rectangle;

   //            ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image);

   //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.20);

   //         }
   //         else if (uImage != 0xffffffff)
   //         {

   //            if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //            {

   //               psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //            }
   //            else
   //            {

   //               psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //            }

   //         }

   //      }

   //   }

   //   if (item.m_str.has_char())
   //   {

   //      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

   //      ::rectangle_i32 rectText;

   //      ::draw2d::brush_pointer brushText(e_create);

   //      if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //      {

   //         brushText->create_solid(argb(255, 0, 0, 0));

   //      }
   //      else
   //      {

   //         brushText->create_solid(argb(255, 123, 123, 118));

   //      }

   //      pgraphics->set(brushText);

   //      if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
   //      {

   //         pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, e_align_bottom_left, e_draw_text_no_prefix);

   //      }

   //   }

   //}


   //void style::_001DrawTranquillumToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
   //{

   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   ::rectangle_i32 rectItem;

   //   ::rectangle_i32 rectImage;

   //   ptoolbar->select_font(pgraphics, ::user::font_toolbar);

   //   ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

   //   ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

   //   bool bHover = ptoolbar->m_itemHover == iItem;

   //   ::u32 uImage = psession->userex()->menu()->command_image(item.m_id);

   //   ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
   //   ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
   //   ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
   //   if ((nStyle & e_toolbar_item_style_separator) == 0)
   //   {
   //      if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //      {
   //         // item is enabled
   //         if (ptoolbar->m_iButtonPressItem >= 0)
   //         {
   //            if (iItem == ptoolbar->m_iButtonPressItem)
   //            {
   //               if (bHover)
   //               {
   //                  eelement = ::user::toolbar::element_item_press;
   //                  eelementImage = ::user::toolbar::element_image_press;
   //                  eelementText = ::user::toolbar::element_text_press;
   //               }
   //               else
   //               {
   //                  eelement = ::user::toolbar::element_item_hover;
   //                  eelementImage = ::user::toolbar::element_image_hover;
   //                  eelementText = ::user::toolbar::element_text_hover;
   //               }
   //            }
   //         }
   //         else if (bHover)
   //         {
   //            eelement = ::user::toolbar::element_item_hover;
   //            eelementImage = ::user::toolbar::element_image_hover;
   //            eelementText = ::user::toolbar::element_text_hover;
   //         }
   //      }
   //      else
   //      {
   //         // item is disabled
   //         eelement = ::user::toolbar::e_element_item;
   //         eelementImage = ::user::toolbar::element_image;
   //         eelementText = ::user::toolbar::e_element_text;
   //      }
   //   }
   //   else
   //   {
   //      eelement = ::user::toolbar::e_element_item;
   //      eelementImage = ::user::toolbar::element_image;
   //      eelementText = ::user::toolbar::e_element_text;
   //   }


   //   //int iOffsetX = 0;
   //   //int iOffsetY = 0;

   //   ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

   //   ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

   //   if (item.m_id.compare_ci("separator") == 0)
   //   {
   //      /*::rectangle_i32 rectSeparator;
   //      rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
   //      rectSeparator.right = rectSeparator.left + 2;
   //      rectSeparator.top = rectImage.top;
   //      rectSeparator.bottom = rectImage.bottom;*/
   //      //pgraphics->Draw3dRect(rectSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
   //   }
   //   else
   //   {
   //      if (eelement == ::user::toolbar::element_item_hover)
   //      {
   //         if ((nStyle & TBBS_CHECKED) != 0)
   //         {

   //            ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::e_element_item);

   //            ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

   //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //            {
   //               psystem->imaging().color_blend(
   //               pgraphics,
   //               rectItem.left,
   //               rectItem.top,
   //               rectItem.width(),
   //               rectItem.height(),
   //               rgb(255, 255, 250), 208);

   //               pgraphics->draw3d_rect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

   //            }

   //            if (uImage != 0xffffffffu)
   //            {

   //               if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //               {

   //                  // button is enabled
   //                  psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //               }
   //               else
   //               {

   //                  // button is disabled
   //                  psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //               }

   //            }

   //         }
   //         else
   //         {

   //            ::rectangle_i32 rectShadow;

   //            ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::element_item_hover);

   //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //            {

   //               ::draw2d::pen_pointer pen(e_create);

   //               pen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_hover));
   //               ::draw2d::brush_pointer brush(e_create);

   //               brush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_hover));
   //               ::draw2d::pen * ppenOld = pgraphics->set(pen);
   //               ::draw2d::brush * pbrushOld = pgraphics->set(brush);
   //               pgraphics->rectangle(rectItem);
   //               pgraphics->set(ppenOld);
   //               pgraphics->set(pbrushOld);

   //            }

   //            if (item.m_pimage->is_set())
   //            {

   //               ::rectangle_i32 rectangle;

   //               ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image_hover);

   //               pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.80);

   //            }
   //            else if (uImage != 0xffffffffu)
   //            {

   //               ::rectangle_i32 rectangle;

   //               ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_item_hover);

   //               psession->userex()->menu()->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

   //               psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
   //            }

   //         }

   //      }
   //      else if (eelement == ::user::toolbar::element_item_press)
   //      {

   //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //         {

   //            ::draw2d::pen_pointer pen(e_create);

   //            pen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_press));
   //            ::draw2d::brush_pointer brush(e_create);

   //            brush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_press));
   //            ::draw2d::pen * ppenOld = pgraphics->set(pen);
   //            ::draw2d::brush * pbrushOld = pgraphics->set(brush);
   //            pgraphics->rectangle(rectItem);
   //            pgraphics->set(ppenOld);
   //            pgraphics->set(pbrushOld);

   //         }

   //         if (item.m_pimage->is_set())
   //         {

   //            ::rectangle_i32 rectangle;

   //            ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image_press);

   //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 1.0);

   //         }
   //         else if (uImage != 0xffffffff)
   //         {

   //            psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //         }

   //      }
   //      else
   //      {

   //         if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //         {

   //            ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::e_element_item);

   //            pgraphics->fill_rectangle(rectItem, argb(184, 255, 255, 255));

   //         }

   //         if ((nStyle & TBBS_CHECKED) != 0)
   //         {

   //            pgraphics->draw3d_rect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

   //         }

   //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
   //         {

   //            ::draw2d::pen_pointer pen(e_create);

   //            pen->create_solid(1, ptoolbar->_001GetColor(
   //                              (nStyle & e_toolbar_item_style_disabled) == 0 ?
   //                              ::user::color_button_background :
   //                              ::user::color_button_background_disabled));
   //            ::draw2d::brush_pointer brush(e_create);

   //            brush->create_solid(ptoolbar->_001GetColor(
   //                                (nStyle & e_toolbar_item_style_disabled) == 0 ?
   //                                ::user::color_button_background :
   //                                ::user::color_button_background_disabled));
   //            ::draw2d::pen * ppenOld = pgraphics->set(pen);
   //            ::draw2d::brush * pbrushOld = pgraphics->set(brush);
   //            pgraphics->rectangle(rectItem);
   //            pgraphics->set(ppenOld);
   //            pgraphics->set(pbrushOld);

   //         }

   //         if (item.m_pimage->is_set())
   //         {

   //            ::rectangle_i32 rectangle;

   //            ptoolbar->_001GetElementRect(iItem, rectangle, ::user::toolbar::element_image);

   //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.20);

   //         }
   //         else if (uImage != 0xffffffff)
   //         {

   //            if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //            {

   //               psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //            }
   //            else
   //            {

   //               psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

   //            }

   //         }

   //      }

   //   }

   //   if (item.m_str.has_char())
   //   {

   //      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

   //      ::rectangle_i32 rectText;

   //      ::draw2d::brush_pointer brushText(e_create);

   //      if ((nStyle & e_toolbar_item_style_disabled) == 0)
   //      {

   //         brushText->create_solid(argb(255, 255, 255, 255));

   //         pgraphics->set_text_color(argb(255, 255, 255, 255));

   //      }
   //      else
   //      {

   //         brushText->create_solid(::user::color_button_text_disabled);

   //         pgraphics->set_text_color(ptoolbar->_001GetColor(

   //                                   ::user::color_button_text_disabled));

   //      }

   //      if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
   //      {

   //         pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, e_align_bottom_left, e_draw_text_no_prefix);

   //      }

   //   }

   //}


   bool style::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      ::rectangle_i32 rectangleClient;

      psplitlayout->get_client_rect(rectangleClient);

      pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      return true;

   }


         } // namespace tranquillum

   } // namespace experience



