#include "framework.h"
#include "acme/handler/item.h"
#include "base/user/simple/scroll_bar.h"
#include "base/user/user/tab_pane.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/user/user/frame.h"
#include "style.h"
#include "base/user/user/tab.h"
#include "base/user/user/tab_data.h"
#include "base/user/user/split_layout.h"
#include "base/platform/session.h"
//#include "core/user/userex/_userex.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience_tranquillum
{

   style::style()
   {



   }


   style::~style()
   {

   }


   ::color::color style::get_color(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate)
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_tab)
         {


            if (eelement == ::e_element_tab_layout_background)
            {

               if (is_dark_mode())
               {

                  return argb(255, 51, 51, 45);

               }
               else
               {

                  return argb(255, 255, 255, 255);

               }

            }
            else if (eelement == ::e_element_tab_client_background)
            {

               if (is_dark_mode())
               {

                  return argb(255, 51, 51, 51);

               }
               else
               {

                  return argb(255, 255, 255, 255);

               }


            }
            else if (eelement == ::e_element_item_text)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_new_input)
                  {

                     return argb(255, 128, 128, 128);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return argb(255, 80, 80, 255);


                  }
                  else if (estate & ::user::e_state_selected)
                  {

                     return argb(255, 40, 40, 40);

                  }
                  else
                  {

                     return argb(255, 200, 200, 200);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return argb(255, 80, 80, 120);

                  }
                  else
                  {

                     return argb(255, 80, 80, 80);

                  }

               }

            }
            else if (eelement == ::e_element_item_background)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_hover)
                  {

                     if (estate & ::user::e_state_selected)
                     {

                        return argb(255, 200, 200, 240);

                     }
                     else
                     {
                        return argb(255, 220, 220, 220);

                     }

                  }
                  else if (estate & ::user::e_state_selected)
                  {

                     return argb(255, 200, 200, 200);

                  }
                  else
                  {

                     return argb(255, 40, 40, 40);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_hover)
                  {

                     if (estate & ::user::e_state_selected)
                     {

                        return argb(255, 200, 200, 240);

                     }
                     else
                     {
                        return argb(255, 220, 220, 220);

                     }

                  }
                  else if (estate & ::user::e_state_selected)
                  {

                     return argb(255, 200, 200, 200);

                  }
                  else
                  {

                     return argb(255, 200, 200, 200);

                  }

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_button)
         {

            if (eelement == ::e_element_background)
            {

               return argb(255, 116, 160, 220);

            }
            else if (eelement == ::e_element_text)
            {

               return argb(255, 255, 255, 255);

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

      if (eelement == ::e_element_check)
      {

         if (is_dark_mode())
         {
            return argb(255, 215, 215, 215);

         }
         else
         {

            return argb(255, 40, 40, 40);

         }

      }
      else if (eelement == ::e_element_background)
      {

         if (is_dark_mode())
         {

            if (estate & ::user::e_state_selected)
            {

               return argb(255, 120, 120, 120);

            }
            else
            {

               return argb(255, 51, 51, 51);

            }

         }
         else
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

      }
      else if (eelement == ::e_element_text)
      {


         if (is_dark_mode())
         {

            if (estate & ::user::e_state_new_input)
            {
               return argb(255, 128, 128, 128);

            }
            else if (estate & ::user::e_state_selected)
            {

               return argb(255, 40, 40, 40);

            }
            else
            {

               return argb(255, 200, 200, 200);

            }


         }
         else
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

      }
      else if (eelement == ::e_element_item_text)
      {

         if (is_dark_mode())
         {

            if (estate & ::user::e_state_new_input)
            {

               return argb(255, 128, 128, 128);

            }
            else if (estate & ::user::e_state_hover)
            {

               return argb(255, 30, 30, 30);


            }
            else if (estate & ::user::e_state_selected)
            {

               return argb(255, 40, 40, 40);

            }
            else
            {

               return argb(255, 200, 200, 200);

            }

         }
         else
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

      }
      else if (eelement == ::e_element_item_background)
      {

         if (is_dark_mode())
         {
            if (estate & ::user::e_state_new_input)
            {

               return argb(255, 128, 128, 128);

            }
            else if (estate & ::user::e_state_hover)
            {

               if (estate & ::user::e_state_selected)
               {

                  return argb(255, 200, 200, 240);

               }
               else
               {
                  return argb(255, 220, 220, 220);

               }

            }
            else if (estate & ::user::e_state_selected)
            {

               return argb(255, 200, 200, 200);

            }
            else
            {

               return argb(255, 40, 40, 40);



            }
         }
         else
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

      }


      return ::base::style::get_color(pinteraction, eelement, estate);

   }


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer& pgraphics, ::user::frame* pframe)
   {

      ::draw2d::savedc k(pgraphics);

      pgraphics->m_pdraw2dhost = pframe;

      if (!pframe->is_custom_draw() && pgraphics != nullptr && pgraphics->m_pnext == nullptr)
      {

         pframe->set_context_org(pgraphics);

      }

      ::rectangle_i32 rectangleClient;

      pframe->client_rectangle(rectangleClient);

      auto pstyle = pframe->get_style(pgraphics);

      status < ::color::color > crBackground = pframe->get_color(pstyle, ::e_element_background);

      //crBackground = argb(255, 200, 180, 180);

      pgraphics->fill_rectangle(rectangleClient, crBackground);

      return true;

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab* ptab)
   {

      if (!ptab->get_data()->m_bCreated)
      {

         return false;

      }

      ptab->get_data()->m_rectangleTextMargin.left = 4;

      ptab->get_data()->m_rectangleTextMargin.right = 4;

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

      ptab->m_pdcextension->get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, ptab->get_data()->m_sizeSep);

      if (ptab->get_data()->m_bVertical)
      {
         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;
         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto& pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            if (!pane.m_bTabPaneVisible)
            {

               continue;

            }

            string str = pane.get_title();

            pane.do_split_layout(ptab->m_pdcextension, pgraphics);

            ::size_i32 size;

            ptab->m_pdcextension->get_text_extent(pgraphics, str, size);



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

         iTabWidth += ptab->get_data()->m_rectangleBorder.left + ptab->get_data()->m_rectangleBorder.right +
            ptab->get_data()->m_rectangleMargin.left + ptab->get_data()->m_rectangleMargin.right +
            ptab->get_data()->m_rectangleTextMargin.left + ptab->get_data()->m_rectangleTextMargin.right;

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectangleBorder.top + ptab->get_data()->m_rectangleBorder.bottom +
            ptab->get_data()->m_rectangleMargin.top + ptab->get_data()->m_rectangleMargin.bottom +
            ptab->get_data()->m_rectangleTextMargin.top + ptab->get_data()->m_rectangleTextMargin.bottom;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::rectangle_i32 rectangleClient;
         ptab->client_rectangle(rectangleClient);

         ptab->get_data()->m_rectangleTab.left = rectangleClient.left;
         ptab->get_data()->m_rectangleTab.top = rectangleClient.top;
         ptab->get_data()->m_rectangleTab.right = ptab->get_data()->m_rectangleTab.left + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectangleTab.bottom = rectangleClient.bottom;

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left,
         m_rectangleTab.top,
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         ptab->get_data()->m_rectangleTabClient.left = ptab->m_bShowTabs ? ptab->get_data()->m_rectangleTab.right : rectangleClient.left;
         ptab->get_data()->m_rectangleTabClient.top = ptab->get_data()->m_rectangleTab.top;
         ptab->get_data()->m_rectangleTabClient.right = rectangleClient.right;
         ptab->get_data()->m_rectangleTabClient.bottom = ptab->get_data()->m_rectangleTab.bottom;

      }
      else
      {
         i32 iTabHeight = 16;
         i32 cy;
         pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::rectangle_i32 rectangleClient;
         ptab->client_rectangle(rectangleClient);
         int x = rectangleClient.left;

         i32 ixAdd;
         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto& pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            if (!pane.m_bTabPaneVisible)
            {

               return false;

            }

            string str = pane.get_title();

            pane.do_split_layout(ptab->m_pdcextension, pgraphics);

            ::size_i32 size;

            ptab->m_pdcextension->get_text_extent(pgraphics, str, size);

            ::write_text::text_metric metric;

            pgraphics->get_text_metrics(&metric);

            if (pane.m_pimage->is_set())
            {

               size.cy = (::i32)maximum(maximum(size.cy, pane.m_pimage->size().cy), metric.get_line_spacing());

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
               + ptab->get_data()->m_rectangleBorder.left + ptab->get_data()->m_rectangleBorder.right
               + ptab->get_data()->m_rectangleMargin.left + ptab->get_data()->m_rectangleMargin.right
               + ptab->get_data()->m_rectangleTextMargin.left + ptab->get_data()->m_rectangleTextMargin.right;

            x += pane.m_size.cx;

         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectangleBorder.top + ptab->get_data()->m_rectangleBorder.bottom +
            ptab->get_data()->m_rectangleMargin.top + ptab->get_data()->m_rectangleMargin.bottom + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight + 8;

         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto& pane = *ptab->get_data()->m_tabpanecompositea[iPane];

            pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectangleTab.left = rectangleClient.left;
         ptab->get_data()->m_rectangleTab.top = rectangleClient.top;
         ptab->get_data()->m_rectangleTab.right = rectangleClient.right;
         ptab->get_data()->m_rectangleTab.bottom = ptab->get_data()->m_rectangleTab.top + ptab->get_data()->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left,
         m_rectangleTab.top,
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         rectangle_i32& rectangleTabClient = ptab->get_data()->m_rectangleTabClient;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
         bool bTabbedClient = ptab->m_bShowTabs;

         rectangleTabClient.left = ptab->get_data()->m_rectangleTab.left;
         rectangleTabClient.top = bTabbedClient ? ptab->get_data()->m_rectangleTab.bottom : rectangleClient.top;
         rectangleTabClient.right = ptab->get_data()->m_rectangleTab.right;
         rectangleTabClient.bottom = rectangleClient.bottom;


         //TRACE0("rectangleTabClient");

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


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer& pgraphics, ::user::tab* ptab)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      ::rectangle_i32 r1;
      ptab->client_rectangle(r1);

      //if (!ptab->get_data()->m_bNoClient)
      //{

      //   pgraphics->fill_rectangle(r1, argb(255, 255, 255, 255));

      //}

      ptab->get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      //pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rcTab;

      rcTab = ptab->get_data()->m_rectangleTab;

      if (!ptab->get_data()->m_bNoClient)
      {

         pgraphics->fill_rectangle(rcTab, argb(255, 255, 255, 255));

      }
      ::rectangle_i32 rcTape(rcTab);

      rcTape.top = rcTape.bottom - 8;


      ::rectangle_i32 rcTabs(rcTab);

      ::rectangle_i32 rcClient;

      rcClient = ptab->get_data()->m_rectangleTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectangleBorder.bottom;

      rcClient.top = rcTabs.bottom;

      auto pstyle = ptab->get_style(pgraphics);

      auto crbk = ptab->get_color(pstyle, ::e_element_tab_layout_background);

      pgraphics->fill_rectangle(rcTabs, crbk);

      crbk = ptab->get_color(pstyle, ::e_element_tab_client_background);

      pgraphics->fill_rectangle(rcClient, crbk);

      pgraphics->fill_rectangle(rcTape, argb(255, 192, 192, 192));



      ::index iTab = -1;

      auto pbrushText = __create < ::draw2d::brush >();

      auto ppenBorder = __create < ::draw2d::pen >();

      for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         auto& pane = *ptab->get_data()->m_tabpanecompositea[iPane];

         if (!pane.m_bTabPaneVisible)
         {

            continue;

         }

         iTab++;

         if (!ptab->get_element_rect(iTab, rectangle, ::e_element_tab))
         {

            continue;

         }

         ::user::e_state estate = ::user::e_state_none;

         if (ptab->get_data()->m_idaSel.contains(pane.m_atom))
         {

            estate |= ::user::e_state_selected;

         }

         if (::is_item(ptab->m_pitemHover, iTab))
         {

            estate |= ::user::e_state_hover;

         }

         pane.m_pbrushFill->create_solid(ptab->get_color(pstyle, ::e_element_item_background, estate));

         pgraphics->set(pane.m_pbrushFill);

         pgraphics->fill_rectangle(rectangle);

         if (!ptab->get_element_rect(iTab, rectangleBorder, ::e_element_border))
         {

            continue;

         }

         if (!ptab->get_element_rect(iTab, rectangleClient, ::e_element_client))
         {

            continue;

         }

         if (ptab->get_data()->m_bVertical)
         {

            if (ptab->get_element_rect(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pane.m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __create < ::draw2d::path >();

            if (true)
            {

               if (ptab->get_data()->m_idaSel.contains(pane.m_atom))
               {

                  ::rectangle_i32 rSel;

                  rSel = rectangleClient;

                  rSel.bottom = rectangleClient.top + 3;

                  pgraphics->fill_rectangle(rSel, argb(255, 120, 155, 240));

                  pane.m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(pane.m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  if (::is_item(ptab->m_pitemHover, iTab)
                     && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected | ::user::e_state_hover);

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

                  }

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  pgraphics->set(pbrushText);

               }
               else
               {

                  //ppath->start_figure();

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleText.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom);

                  ppath->close_figure();

                  if (::is_item(ptab->m_pitemHover, iTab)
                     && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
                  {

                     pane.m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(pane.m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                     pgraphics->set(pbrushText);

                  }
                  else
                  {

                     pane.m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(pane.m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab, ::e_element_none);

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            // Horizontal

            if (ptab->get_element_rect(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(pane.m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            //if (iPane == 0)
            //{

            //   if (rcTab.left < rectangleBorder.left)
            //   {

            //      pgraphics->set(ptab->get_data()->m_ppenBorder);

            //      pgraphics->draw_line(rcTab.left, rectangleClient.bottom, rectangleBorder.left, rectangleClient.bottom);

            //   }

            //}

            if (true)
            {

               //auto ppath = __create < ::draw2d::path > ();

               if (ptab->get_data()->m_idaSel.contains(pane.m_atom))
               {

                  ::rectangle_i32 rSel;

                  rSel = rectangle;

                  rSel.bottom = rectangleClient.top + 3;

                  pgraphics->fill_rectangle(rSel, argb(255, 120, 155, 240));

                  pane.m_pbrushFillSel->create_solid(argb(255, 255, 255, 255));

                  pgraphics->set(pane.m_pbrushFillSel);

                  //pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  pgraphics->set(ppenBorder);

                  //pgraphics->draw(ppath);

                  if (::is_item(ptab->m_pitemHover, iTab)
                     && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  }
                  else
                  {

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);


                  }

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  if (::is_item(ptab->m_pitemHover, iTab)
                     && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
                  {

                     pane.m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(pane.m_pbrushFillHover);

                     //pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     //pgraphics->draw(ppath);

                     pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  }
                  else
                  {

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(ppenBorder);

                     //pgraphics->draw(ppath);

                     pgraphics->set_font(ptab, ::e_element_none);

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

            ::rectangle_i32 rVertLine;

            rVertLine = rectangle;

            rVertLine.left = rVertLine.right - 1;
            pgraphics->fill_rectangle(rVertLine, argb(127, 80, 80, 80));

            //if (iPane == ptab->get_data()->m_panea.get_upper_bound())
            //{

            //   if (rectangleBorder.right - 1 < rcTab.right)
            //   {

            //      pgraphics->set(ptab->get_data()->m_ppenBorder);

            //      pgraphics->draw_line(rectangleBorder.right - 1, rectangleClient.bottom, rcTab.right, rectangleClient.bottom);

            //   }

            //}


         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectangleText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(pane, ptab, pgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectangleClose, ::e_element_close_tab_button))
            {

               pgraphics->set_font(ptab, ::e_element_close_tab_button);

               if (::is_item(ptab->m_pitemHover, iTab)
                  && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button))
               {

                  pbrushText = ptab->get_data()->m_pbrushCloseHover;

               }
               else
               {

                  pbrushText = ptab->get_data()->m_pbrushClose;

               }

               pgraphics->set(pbrushText);

               pgraphics->draw_text("x", rectangleClose, e_align_center);

            }

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer& pgraphics, const ::rectangle_i32& rectangleParam, ::draw2d::brush_pointer& pbrushText, const ::user::e_state& estate)
   {

      string_array& straTitle = pane.m_straTitle;

      pgraphics->set(pbrushText);

      if (straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), rectangleParam, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rectangle_i32 rectangleText(rectangleParam);

         ::write_text::font_pointer pfont;

         pfont = pgraphics->get_current_font();

         size_i32 sSep = ptab->get_data()->m_sizeSep;

         auto pstyle = ptab->get_style(pgraphics);

         ::rectangle_i32 rectangleEmp;

         for (index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size_i32 s = pane.m_sizeaText[i];
            rectangleText.right = rectangleText.left + s.cx;
            pgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);
            rectangleText.left += s.cx;
            if (i < straTitle.get_upper_bound())
            {
               rectangleText.right = rectangleText.left + sSep.cx;
               rectangleEmp = rectangleText;
               rectangleEmp.deflate(1, 1);
               ::draw2d::enum_alpha_mode emode = pgraphics->alpha_mode();
               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
               if (::is_item(ptab->m_pitemHover, (::index)::e_element_split + i))
               {

                  pgraphics->fill_rectangle(rectangleEmp, argb(128, 149, 184, 255));

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  pgraphics->set(pbrushText);

               }
               else
               {

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  pgraphics->set(pbrushText);

               }

               pgraphics->set_font(ptab, ::e_element_close_tab_button);
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);
               rectangleText.left += sSep.cx;

            }

         }

      }

   }





   //   bool style::on_ui_event(::enum_topic etopic, ::user::e_object eobject, ::user::interaction * pframewindow)
   //   {
   //
   //      if (eevent == ::id_calc_item_height)
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

      //   ::rectangle_i32 rectangleItem;

      //   ::rectangle_i32 rectangleImage;

      //   pgraphics->set_font(ptoolbar);

      //   ::user::tool_item & item = ptoolbar->m_itema(iItem);

      //   ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

      //   bool bHover = ptoolbar->m_pitemHover == iItem;

      //   ::u32 uImage = psession->userex()->menu()->command_image(item.m_atom);

      //   ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
      //   ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
      //   ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
      //   if ((nStyle & e_tool_item_style_separator) == 0)
      //   {
      //      if ((nStyle & e_tool_item_style_disabled) == 0)
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

      //   ptoolbar->index_element_rectangle(iItem, rectangleItem, eelement);

      //   ptoolbar->index_element_rectangle(iItem, rectangleImage, eelementImage);

      //   if ((nStyle & e_tool_item_style_separator) != 0)
      //   {
      //      ::rectangle_i32 rectangleSeparator;
      //      rectangleSeparator.left = (rectangleImage.left + rectangleImage.right) / 2 - 1;
      //      rectangleSeparator.right = rectangleSeparator.left + 2;
      //      rectangleSeparator.top = rectangleImage.top;
      //      rectangleSeparator.bottom = rectangleImage.bottom;
      //      pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      //   }
      //   else
      //   {
      //      if (eelement == ::user::toolbar::element_item_hover)
      //      {
      //         if ((nStyle & TBBS_CHECKED) != 0)
      //         {

      //            ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

      //            ptoolbar->index_element_rectangle(iItem, rectangleImage, ::user::toolbar::element_image);

      //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //            {
      //               psystem->imaging().color_blend(
      //               pgraphics,
      //               rectangleItem.left,
      //               rectangleItem.top,
      //               rectangleItem.width(),
      //               rectangleItem.height(),
      //               rgb(255, 255, 250), 208);

      //               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

      //            }

      //            if (uImage != 0xffffffffu)
      //            {

      //               if ((nStyle & e_tool_item_style_disabled) == 0)
      //               {

      //                  // button is enabled
      //                  psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //               }
      //               else
      //               {

      //                  // button is disabled
      //                  psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //               }

      //            }

      //         }
      //         else
      //         {

      //            ::rectangle_i32 rectangleShadow;

      //            ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::user::toolbar::element_item_hover);

      //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //            {

      //               auto ppen = __create < ::draw2d::pen > ();

      //               ppen->create_solid(1, argb(184, 92, 184, 92));

      //               auto pbrush = __create < ::draw2d::brush >();

      //               pbrush->create_solid(argb(123, 177, 184, 255));

      //               ::draw2d::pen * ppenOld = pgraphics->set(ppen);
      //               ::draw2d::brush * pbrushOld = pgraphics->set(pbrush);
      //               pgraphics->rectangle(rectangleItem);
      //               pgraphics->set(ppenOld);
      //               pgraphics->set(pbrushOld);

      //            }

      //            if (item.m_pimage->is_set())
      //            {

      //               ::rectangle_i32 rectangle;

      //               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_hover);

      //               pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.80);

      //            }
      //            else if (uImage != 0xffffffffu)
      //            {

      //               ::rectangle_i32 rectangle;

      //               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_item_hover);

      //               psession->userex()->menu()->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

      //               psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
      //            }

      //         }

      //      }
      //      else if (eelement == ::user::toolbar::element_item_press)
      //      {

      //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //         {

      //            auto ppen = __create < ::draw2d::pen > ();

      //            ppen->create_solid(1, argb(255, 92, 92, 92));
      //            auto pbrush = __create < ::draw2d::brush >();

      //            pbrush->create_solid(argb(255, 255, 255, 255));
      //            ::draw2d::pen * ppenOld = pgraphics->set(ppen);
      //            ::draw2d::brush * pbrushOld = pgraphics->set(pbrush);
      //            pgraphics->rectangle(rectangleItem);
      //            pgraphics->set(ppenOld);
      //            pgraphics->set(pbrushOld);

      //         }

      //         if (item.m_pimage->is_set())
      //         {

      //            ::rectangle_i32 rectangle;

      //            ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_press);

      //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 1.0);

      //         }
      //         else if (uImage != 0xffffffff)
      //         {

      //            psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //         }

      //      }
      //      else
      //      {

      //         if ((nStyle & e_tool_item_style_disabled) == 0)
      //         {

      //            ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

      //            pgraphics->fill_rectangle(rectangleItem, argb(184, 255, 255, 255));

      //         }

      //         if ((nStyle & TBBS_CHECKED) != 0)
      //         {

      //            pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

      //         }

      //         if (item.m_pimage->is_set())
      //         {

      //            ::rectangle_i32 rectangle;

      //            ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image);

      //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.20);

      //         }
      //         else if (uImage != 0xffffffff)
      //         {

      //            if ((nStyle & e_tool_item_style_disabled) == 0)
      //            {

      //               psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //            }
      //            else
      //            {

      //               psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //            }

      //         }

      //      }

      //   }

      //   if (item.m_str.has_char())
      //   {

      //      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      //      ::rectangle_i32 rectangleText;

      //      auto pbrushText = __create < ::draw2d::brush > ();

      //      if ((nStyle & e_tool_item_style_disabled) == 0)
      //      {

      //         pbrushText->create_solid(argb(255, 0, 0, 0));

      //      }
      //      else
      //      {

      //         pbrushText->create_solid(argb(255, 123, 123, 118));

      //      }

      //      pgraphics->set(pbrushText);

      //      if (ptoolbar->index_element_rectangle(iItem, rectangleText, eelementText) && rectangleText.right > 0)
      //      {

      //         pgraphics->_DrawText(item.m_str, item.m_str.length(), rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

      //      }

      //   }

      //}


      //void style::_001DrawTranquillumToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
      //{

      //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //   ::rectangle_i32 rectangleItem;

      //   ::rectangle_i32 rectangleImage;

      //   ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      //   ::user::tool_item & item = ptoolbar->m_itema(iItem);

      //   ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

      //   bool bHover = ptoolbar->m_pitemHover == iItem;

      //   ::u32 uImage = psession->userex()->menu()->command_image(item.m_atom);

      //   ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
      //   ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
      //   ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
      //   if ((nStyle & e_tool_item_style_separator) == 0)
      //   {
      //      if ((nStyle & e_tool_item_style_disabled) == 0)
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

      //   ptoolbar->index_element_rectangle(iItem, rectangleItem, eelement);

      //   ptoolbar->index_element_rectangle(iItem, rectangleImage, eelementImage);

      //   if (item.m_atom.case_insensitive_order("separator") == 0)
      //   {
      //      /*::rectangle_i32 rectangleSeparator;
      //      rectangleSeparator.left = (rectangleImage.left + rectangleImage.right) / 2 - 1;
      //      rectangleSeparator.right = rectangleSeparator.left + 2;
      //      rectangleSeparator.top = rectangleImage.top;
      //      rectangleSeparator.bottom = rectangleImage.bottom;*/
      //      //pgraphics->Draw3dRect(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      //   }
      //   else
      //   {
      //      if (eelement == ::user::toolbar::element_item_hover)
      //      {
      //         if ((nStyle & TBBS_CHECKED) != 0)
      //         {

      //            ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

      //            ptoolbar->index_element_rectangle(iItem, rectangleImage, ::user::toolbar::element_image);

      //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //            {
      //               psystem->imaging().color_blend(
      //               pgraphics,
      //               rectangleItem.left,
      //               rectangleItem.top,
      //               rectangleItem.width(),
      //               rectangleItem.height(),
      //               rgb(255, 255, 250), 208);

      //               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

      //            }

      //            if (uImage != 0xffffffffu)
      //            {

      //               if ((nStyle & e_tool_item_style_disabled) == 0)
      //               {

      //                  // button is enabled
      //                  psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //               }
      //               else
      //               {

      //                  // button is disabled
      //                  psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //               }

      //            }

      //         }
      //         else
      //         {

      //            ::rectangle_i32 rectangleShadow;

      //            ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::user::toolbar::element_item_hover);

      //            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //            {

      //               auto ppen = __create < ::draw2d::pen > ();

      //               ppen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_hover));
      //               auto pbrush = __create < ::draw2d::brush >();

      //               pbrush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_hover));
      //               ::draw2d::pen * ppenOld = pgraphics->set(ppen);
      //               ::draw2d::brush * pbrushOld = pgraphics->set(pbrush);
      //               pgraphics->rectangle(rectangleItem);
      //               pgraphics->set(ppenOld);
      //               pgraphics->set(pbrushOld);

      //            }

      //            if (item.m_pimage->is_set())
      //            {

      //               ::rectangle_i32 rectangle;

      //               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_hover);

      //               pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.80);

      //            }
      //            else if (uImage != 0xffffffffu)
      //            {

      //               ::rectangle_i32 rectangle;

      //               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_item_hover);

      //               psession->userex()->menu()->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

      //               psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
      //            }

      //         }

      //      }
      //      else if (eelement == ::user::toolbar::element_item_press)
      //      {

      //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //         {

      //            auto ppen = __create < ::draw2d::pen > ();

      //            ppen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_press));
      //            auto pbrush = __create < ::draw2d::brush >();

      //            pbrush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_press));
      //            ::draw2d::pen * ppenOld = pgraphics->set(ppen);
      //            ::draw2d::brush * pbrushOld = pgraphics->set(pbrush);
      //            pgraphics->rectangle(rectangleItem);
      //            pgraphics->set(ppenOld);
      //            pgraphics->set(pbrushOld);

      //         }

      //         if (item.m_pimage->is_set())
      //         {

      //            ::rectangle_i32 rectangle;

      //            ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_press);

      //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 1.0);

      //         }
      //         else if (uImage != 0xffffffff)
      //         {

      //            psession->userex()->menu()->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //         }

      //      }
      //      else
      //      {

      //         if ((nStyle & e_tool_item_style_disabled) == 0)
      //         {

      //            ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

      //            pgraphics->fill_rectangle(rectangleItem, argb(184, 255, 255, 255));

      //         }

      //         if ((nStyle & TBBS_CHECKED) != 0)
      //         {

      //            pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

      //         }

      //         if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
      //         {

      //            auto ppen = __create < ::draw2d::pen > ();

      //            ppen->create_solid(1, ptoolbar->_001GetColor(
      //                              (nStyle & e_tool_item_style_disabled) == 0 ?
      //                              ::user::color_button_background :
      //                              ::user::color_button_background_disabled));
      //            auto pbrush = __create < ::draw2d::brush >();

      //            pbrush->create_solid(ptoolbar->_001GetColor(
      //                                (nStyle & e_tool_item_style_disabled) == 0 ?
      //                                ::user::color_button_background :
      //                                ::user::color_button_background_disabled));
      //            ::draw2d::pen * ppenOld = pgraphics->set(ppen);
      //            ::draw2d::brush * pbrushOld = pgraphics->set(pbrush);
      //            pgraphics->rectangle(rectangleItem);
      //            pgraphics->set(ppenOld);
      //            pgraphics->set(pbrushOld);

      //         }

      //         if (item.m_pimage->is_set())
      //         {

      //            ::rectangle_i32 rectangle;

      //            ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image);

      //            pgraphics->color_blend(rectangle.top_left(), rectangle.size(), item.m_pimage->g(), nullptr, 0.20);

      //         }
      //         else if (uImage != 0xffffffff)
      //         {

      //            if ((nStyle & e_tool_item_style_disabled) == 0)
      //            {

      //               psession->userex()->menu()->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //            }
      //            else
      //            {

      //               psession->userex()->menu()->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

      //            }

      //         }

      //      }

      //   }

      //   if (item.m_str.has_char())
      //   {

      //      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      //      ::rectangle_i32 rectangleText;

      //      auto pbrushText = __create < ::draw2d::brush > ();

      //      if ((nStyle & e_tool_item_style_disabled) == 0)
      //      {

      //         pbrushText->create_solid(argb(255, 255, 255, 255));

      //         pgraphics->set_text_color(argb(255, 255, 255, 255));

      //      }
      //      else
      //      {

      //         pbrushText->create_solid(::user::color_button_text_disabled);

      //         pgraphics->set_text_color(ptoolbar->_001GetColor(

      //                                   ::user::color_button_text_disabled));

      //      }

      //      if (ptoolbar->index_element_rectangle(iItem, rectangleText, eelementText) && rectangleText.right > 0)
      //      {

      //         pgraphics->_DrawText(item.m_str, item.m_str.length(), rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

      //      }

      //   }

      //}


   bool style::_001OnDrawSplitLayout(::draw2d::graphics_pointer& pgraphics, ::user::split_layout* psplitlayout)
   {

      ::rectangle_i32 rectangleClient;

      psplitlayout->client_rectangle(rectangleClient);

      pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      return true;

   }


} // namespace experience_tranquillum



