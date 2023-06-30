//
//  tab_graphics.cpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/06/23.
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "tab.h"
#include "tab_data.h"
#include "acme/handler/item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "base/user/user/style.h"


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace user
{




   void tab::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      if (!m_bEffectiveVisibleTabs)
      {

         return;

      }

      //if (top_level()->frame_is_transparent())
      //{

      //   return;

      //}

      //point_i32 pointContextOffset = pgraphics->get_origin();

      ::rectangle_f64 rClip;

      pgraphics->get_clip_box(rClip);

      ::pointer<::base::style>pstyle = get_style(pgraphics);

      if (pstyle)
      {

         if (pstyle->_001TabOnDrawSchema01(pgraphics, this))
         {

            return;

         }

      }

      if (pstyle == nullptr)
      {

         _001OnDrawStandard(pgraphics);

         return;

      }


      if (!pstyle->_001TabOnDrawSchema01(pgraphics, this))
      {

         _001OnDrawSchema01(pgraphics);

      }

   }


   void tab::_001OnDrawSchema01(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pstyle = get_style(pgraphics);

      ::index iIndex = 0;

      auto pbrushText = __create < ::draw2d::brush >();

      auto ppenBorder = __create < ::draw2d::pen >();

      for (; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }


         ::user::e_state estate = ::user::e_state_none;

         if (get_data()->m_idaSel.contains(ppane->m_atom))
         {

            estate |= ::user::e_state_selected;

         }

         if (::is_item(m_pitemHover, iIndex))
         {

            estate |= ::user::e_state_hover;

         }

         iIndex++;

         if (!get_element_rectangle(iIndex, rectangle, ::e_element_tab))
         {

            continue;

         }

         if (!get_element_rectangle(iIndex, rectangleBorder, ::e_element_border))
         {

            continue;

         }

         if (!get_element_rectangle(iIndex, rectangleClient, ::e_element_client))
         {

            continue;

         }

         if (get_data()->m_bVertical)
         {

            if (get_element_rectangle(iIndex, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __create < ::draw2d::path >();

            if (true)
            {

               if (get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);

                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleClient.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);

                  ppath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(ppane->m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->draw(ppath);

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleText.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom);

                  ppath->close_figure();

                  if (::is_item(m_pitemHover, iIndex)
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(ppane->m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(ppane->m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if (get_element_rectangle(iIndex, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if (true)
            {

               auto ppath = __create < ::draw2d::path >();

               if (get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

                  ppath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pgraphics->set(ppane->m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

                  ppath->close_figure();

                  if (::is_item(m_pitemHover, iIndex)
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(ppane->m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(ppane->m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  }

               }

            }

         }

         if (true)
         {

            ::pointer<::base::style>pbasestyle = pstyle;

            if (pbasestyle && get_element_rectangle(iIndex, rectangleText, ::e_element_text))
            {

               pbasestyle->_001OnTabPaneDrawTitle(*ppane, this, pgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (get_element_rectangle(iIndex, rectangleClose, ::e_element_close_tab_button))
            {

               pgraphics->set(get_font(pstyle, e_element_close_tab_button));

               if (::is_item(m_pitemHover, iIndex) && ::is_element(m_pitemHover, ::e_element_close_tab_button))
               {

                  pbrushText = get_data()->m_pbrushCloseHover;

               }
               else
               {

                  pbrushText = get_data()->m_pbrushClose;

               }

               pgraphics->set(pbrushText);

               pgraphics->draw_text("x", rectangleClose, e_align_center);

            }

         }

      }

   }


   void tab::_001OnDrawStandard(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      auto pstyle = get_style(pgraphics);

      get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->fill_rectangle(get_data()->m_rectangleTab, argb(0xc0, 250, 255, 255));

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      ::index iVisiblePane = 0;

      auto pbrushText = __create < ::draw2d::brush >();

      for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

         if (!get_element_rectangle(iVisiblePane, rectangle, e_element_tab))
            continue;

         if (!get_element_rectangle(iVisiblePane, rectangleBorder, e_element_border))
         {

            continue;

         }

         if (!get_element_rectangle(iVisiblePane, rectangleClient, e_element_client))
         {

            continue;

         }

         if (get_data()->m_bVertical)
         {

            if (get_element_rectangle(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if (get_data()->m_idaSel.contains(iIndex))
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left + 1, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
               pgraphics->line_to(rectangleClient.left, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

            }
            else
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left + 1, rectangleBorder.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
               pgraphics->line_to(rectangleText.left, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.bottom);

               if (::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText = get_data()->m_pbrushClose;

               }
               else
               {

                  auto pstyle = get_style(pgraphics);

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));


               }

            }

         }
         else
         {

            if (get_element_rectangle(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            if (get_data()->m_idaSel.contains(ppane->m_atom))
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.left, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top);
               pgraphics->line_to(rectangleClient.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));
               pgraphics->line_to(rectangleBorder.right - 1, rectangleClient.bottom);

               auto pstyle = get_style(pgraphics);

               pgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(argb(255, 0, 0, 0));

            }
            else
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1.0, argb(255, 0, 0, 0));

               pgraphics->set(ppen);

               pgraphics->set_current_point(rectangleBorder.left, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleBorder.top);
               pgraphics->line_to(rectangleClient.right, rectangleBorder.top);
               pgraphics->line_to(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));
               pgraphics->line_to(rectangleBorder.right - 1, rectangleClient.bottom);
               pgraphics->line_to(rectangleBorder.left, rectangleClient.bottom);

               if (::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  pgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  pgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

               }

            }

         }

         if (get_element_rectangle(iVisiblePane, rectangleText, e_element_text))
         {

            pgraphics->set(pbrushText);

            pgraphics->_DrawText(ppane->get_title(), rectangleText, e_align_bottom_left);

         }

         if (get_element_rectangle(iVisiblePane, rectangleClose, e_element_close_tab_button))
         {

            pgraphics->set(get_font(pstyle, e_element_close_tab_button));

            if (::is_item(m_pitemHover, iVisiblePane) && ::is_element(m_pitemHover, e_element_close_tab_button))
            {

               pbrushText = get_data()->m_pbrushCloseSel;

               pbrushText->create_solid(argb(0xff, 255, 127, 0));

            }
            else
            {

               pbrushText->create_solid(argb(0xff, 0, 0, 0));

            }

            pgraphics->set(pbrushText);

            pgraphics->draw_text("x", rectangleClose, e_align_center);

         }

         iVisiblePane++;

      }

   }


   void tab::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = client_rectangle(e_layout_sketch);

      if (!rectangleClient)
      {

         return;

      }

      //if (is_top_level_full_screen_or_transparent())
      //{

      //   m_bEffectiveVisibleTabs = false;

      //}

      calculate_tab_visibility();

      ::pointer<::base::style>pstyle = get_style(pgraphics);

      if (pstyle)
      {

         if (pstyle->_001OnTabLayout(pgraphics, this))
         {

            return;

         }

      }

      if (!get_data()->m_bCreated)
      {

         return;

      }

      if (get_data()->m_bVertical)
      {

         get_data()->m_rectangleMargin.set(2, 3, 1, 0);

         get_data()->m_rectangleBorder.set(11, 1, 6, 0);

         get_data()->m_rectangleTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
            get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
            get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right;

      }
      else
      {

         get_data()->m_rectangleMargin.set(3, 2, 0, 1);

         get_data()->m_rectangleBorder.set(0, 1, 11, 6);

         get_data()->m_rectangleTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
            get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
            get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right;

      }

      //defer_handle_auto_hide_tabs(false);

      pgraphics->set(get_font(pstyle, e_element_close_tab_button));

      m_pgraphicsextension->get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, get_data()->m_sizeSep);

      if (get_data()->m_bVertical)
      {

         i32 iTabWidth = 16;

         i32 iTabHeight = 8;

         i32 cx;

         i32 cy;

         for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_pgraphicsextension, pgraphics);

            ::size_f64 size;

            m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {

               size.cx() += ppane->m_pimage->width() + 2;

               size.cy() = maximum(size.cy(), ppane->m_pimage->height());

            }

            cx = (::i32)(size.cx() + 2.0);

            if (!ppane->m_bPermanent)
            {

               cx += 2 + 16 + 2;

            }

            if (cx > iTabWidth)
            {

               iTabWidth = cx;

            }

            cy = (::i32)(size.cy() + 2.0);

            if (cy > iTabHeight)
            {

               iTabHeight = cy;

            }

         }

         cy = 2 + 16 + 2;

         if (cy > iTabHeight)
         {

            iTabHeight = cy;

         }

         iTabWidth += get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right +
            get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right +
            get_data()->m_rectangleTextMargin.left + get_data()->m_rectangleTextMargin.right;

         get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
            get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom +
            get_data()->m_rectangleTextMargin.top + get_data()->m_rectangleTextMargin.bottom;

         get_data()->m_iTabHeight = iTabHeight;

         //::rectangle_i32 rectangleClient;

         //client_rectangle(rectangleClient);

         get_data()->m_rectangleTab.left = rectangleClient.left;
         get_data()->m_rectangleTab.top = rectangleClient.top;
         get_data()->m_rectangleTab.right = get_data()->m_rectangleTab.left + get_data()->m_iTabWidth;
         get_data()->m_rectangleTab.bottom = rectangleClient.bottom;

         get_data()->m_rectangleTabClient.left = m_bEffectiveVisibleTabs ? get_data()->m_rectangleTab.right : rectangleClient.left;
         get_data()->m_rectangleTabClient.top = get_data()->m_rectangleTab.top;
         get_data()->m_rectangleTabClient.right = rectangleClient.right;
         get_data()->m_rectangleTabClient.bottom = get_data()->m_rectangleTab.bottom;

      }
      else
      {

         i32 iTabHeight = 16;

         i32 cy;

         pgraphics->set(get_font(pstyle, e_state_selected));

         //         ::rectangle_i32 rectangleClient;

         //         client_rectangle(rectangleClient);

         int x = rectangleClient.left;

         i32 ixAdd;

         for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_pgraphicsextension, pgraphics);

            ::size_f64 size;

            m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage->is_ok())
            {

               size.cy() = maximum(size.cy(), ppane->m_pimage->size().cy());

            }

            cy = (::i32)(size.cy() + 2.0);

            if (cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            ppane->m_point.x() = x;

            ppane->m_point.y() = rectangleClient.top;

            ixAdd = 5;

            if (ppane->m_pimage->is_set())
            {

               ixAdd += ppane->m_pimage->width() + 2;

            }

            if (!ppane->m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx() = (::i32)(size.cx() + ixAdd
                                 + get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right
                                 + get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right
                                 + get_data()->m_rectangleTextMargin.left + get_data()->m_rectangleTextMargin.right);

            x += ppane->m_size.cx();
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += get_data()->m_rectangleBorder.top + get_data()->m_rectangleBorder.bottom +
            get_data()->m_rectangleMargin.top + get_data()->m_rectangleMargin.bottom + get_data()->m_iHeightAddUp;

         get_data()->m_iTabHeight = iTabHeight;

         for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanecompositea[iIndex].get();

            ppane->m_size.cy() = iTabHeight;

         }

         get_data()->m_rectangleTab.left = rectangleClient.left;
         get_data()->m_rectangleTab.top = rectangleClient.top;
         get_data()->m_rectangleTab.right = rectangleClient.right;
         get_data()->m_rectangleTab.bottom = get_data()->m_rectangleTab.top + get_data()->m_iTabHeight;

         ::rectangle_i32 & rectangleTabClient = get_data()->m_rectangleTabClient;

         rectangleTabClient.left = get_data()->m_rectangleTab.left;
         rectangleTabClient.top = m_bEffectiveVisibleTabs ? get_data()->m_rectangleTab.bottom : rectangleClient.top;
         rectangleTabClient.right = get_data()->m_rectangleTab.right;
         rectangleTabClient.bottom = rectangleClient.bottom;

         //TRACE0("rectangleTabClient");
      }

      {

         //               ::u32 dwTime2= ::time::now();

               //information("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
               //information("usertab::on_layout call time2= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }


      for (i32 iIndex = 0; iIndex < get_data()->m_tabpanecompositea.get_size(); iIndex++)
      {

         if (iIndex != get_current_tab_index())
         {

            layout_pane(iIndex);

         }

      }

      layout_pane(get_current_tab_index(), is_window_visible());

      if (m_pdata->m_bVertical)
      {

         m_sizeBarDragScroll.cy() = (int)m_pdata->m_tabpanecompositea.get_count() * m_pdata->m_iTabHeight;


      }
      else
      {

         m_sizeBarDragScroll.cx() = m_pdata->m_tabpanecompositea.last()->m_point.x() +
            m_pdata->m_tabpanecompositea.last()->m_size.cx();

      }


   }


} // namespace user



