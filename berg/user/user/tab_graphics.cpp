//
//  tab_graphics.cpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/06/23.
//  Copyright (c) 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "platform.h"
#include "tab.h"
#include "tab_data.h"
#include "acme/handler/item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "berg/user/user/style.h"


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace user
{


   void tab::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      if (!should_draw())
      {

         return;

      }

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      //if (top_level()->frame_is_transparent())
      //{

      //   return;

      //}

      //i32_point pointContextOffset = pdraw2dgraphics->get_origin();

      ::f64_rectangle rClip;

      pdraw2dgraphics->get_clip_box(rClip);

      _001TabOnDrawSchema01(pdraw2dgraphics);

   }


   void tab::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::pointer<::berg::style>pstyle = get_style(pdraw2dgraphics);

      if (pstyle)
      {

         if (pstyle->_001TabOnDrawSchema01(pdraw2dgraphics, this))
         {

            return;

         }

      }

      if (pstyle == nullptr)
      {

         _001OnDrawStandard(pdraw2dgraphics);

         return;

      }


      if (!pstyle->_001TabOnDrawSchema01(pdraw2dgraphics, this))
      {

         _001OnDrawSchema01(pdraw2dgraphics);

      }

   }


   void tab::_001OnDrawSchema01(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::i32_rectangle rectangle;
      ::i32_rectangle rectangleBorder;
      ::i32_rectangle rectangleText;
      ::i32_rectangle rectangleX;
      ::i32_rectangle rectangleIcon;
      ::i32_rectangle rectangleClose;

      get_data()->m_pdraw2dpen->create_solid(1, rgb(32, 32, 32));

      pdraw2dgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto pstyle = get_style(pdraw2dgraphics);

      ::collection::index iIndex = 0;

      auto pbrushText = createø < ::draw2d::brush >();

      auto ppenBorder = createø < ::draw2d::pen >();

      for (; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanea[iIndex].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }


         ::user::e_state estate = ::user::e_state_none;

         if (get_data()->m_idaSel.contains(ppane->id()))
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

         if (!get_element_rectangle(iIndex, rectangleX, ::e_element_client))
         {

            continue;

         }

         if (get_data()->m_bVertical)
         {

            if (get_element_rectangle(iIndex, rectangleIcon, ::e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            auto pdraw2dpath = createø < ::draw2d::path >();

            if (true)
            {

               if (get_data()->m_idaSel.contains(ppane->id()))
               {

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleX.left));
                  pdraw2dpath->add_line(rectangleX.left, rectangleBorder.top);
                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);

                  pdraw2dpath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pdraw2dgraphics->set(ppane->m_pbrushFillSel);

                  pdraw2dgraphics->fill(pdraw2dpath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pdraw2dgraphics->draw(pdraw2dpath);

                  pdraw2dgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
                  pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleX.left));
                  pdraw2dpath->add_line(rectangleText.left, rectangleBorder.top);
                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);
                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom);

                  pdraw2dpath->close_figure();

                  if (::is_item(m_pitemHover, iIndex)
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pdraw2dgraphics->set(ppane->m_pbrushFillHover);

                     pdraw2dgraphics->fill(pdraw2dpath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pdraw2dgraphics->set(ppenBorder);

                     pdraw2dgraphics->draw(pdraw2dpath);

                     pdraw2dgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pdraw2dgraphics->set(ppane->m_pbrushFill);

                     pdraw2dgraphics->fill(pdraw2dpath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border));

                     pdraw2dgraphics->set(ppenBorder);

                     pdraw2dgraphics->draw(pdraw2dpath);

                     pdraw2dgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if (get_element_rectangle(iIndex, rectangleIcon, ::e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            if (true)
            {

               auto pdraw2dpath = createø < ::draw2d::path >();

               if (get_data()->m_idaSel.contains(ppane->id()))
               {

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleX.bottom, rectangleBorder.left, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));

                  pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);

                  pdraw2dpath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  pdraw2dgraphics->set(ppane->m_pbrushFillSel);

                  pdraw2dgraphics->fill(pdraw2dpath);

                  ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pdraw2dgraphics->set(ppenBorder);

                  pdraw2dgraphics->draw(pdraw2dpath);

                  pdraw2dgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleX.bottom, rectangleBorder.left, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));

                  pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);

                  pdraw2dpath->close_figure();

                  if (::is_item(m_pitemHover, iIndex)
                     && !::is_element(m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(m_pitemHover, ::e_element_split, 100))
                  {

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pdraw2dgraphics->set(ppane->m_pbrushFillHover);

                     pdraw2dgraphics->fill(pdraw2dpath);

                     pdraw2dgraphics->set(ppenBorder);

                     pdraw2dgraphics->draw(pdraw2dpath);

                     pdraw2dgraphics->set(get_font(pstyle, e_state_hover));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pdraw2dgraphics->set(ppane->m_pbrushFill);

                     pdraw2dgraphics->fill(pdraw2dpath);

                     ppenBorder->create_solid(1.0, get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                     pdraw2dgraphics->set(ppenBorder);

                     pdraw2dgraphics->draw(pdraw2dpath);

                     pdraw2dgraphics->set(get_font(pstyle));

                     pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

                  }

               }

            }

         }

         if (true)
         {

            ::pointer<::berg::style>pbergstyle = pstyle;

            if (pbergstyle && get_element_rectangle(iIndex, rectangleText, ::e_element_text))
            {

               pbergstyle->_001OnTabPaneDrawTitle(*ppane, this, pdraw2dgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (get_element_rectangle(iIndex, rectangleClose, ::e_element_close_tab_button))
            {

               pdraw2dgraphics->set(get_font(pstyle, e_element_close_tab_button));

               if (::is_item(m_pitemHover, iIndex) && ::is_element(m_pitemHover, ::e_element_close_tab_button))
               {

                  pbrushText = get_data()->m_pbrushCloseHover;

               }
               else
               {

                  pbrushText = get_data()->m_pbrushClose;

               }

               pdraw2dgraphics->set(pbrushText);

               pdraw2dgraphics->draw_text("x", rectangleClose, e_align_center);

            }

         }

      }

   }


   void tab::_001OnDrawStandard(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      ::i32_rectangle rectangle;
      ::i32_rectangle rectangleBorder;
      ::i32_rectangle rectangleText;
      ::i32_rectangle rectangleX;
      ::i32_rectangle rectangleIcon;
      ::i32_rectangle rectangleClose;

      auto pstyle = get_style(pdraw2dgraphics);

      get_data()->m_pdraw2dpen->create_solid(1, rgb(32, 32, 32));

      pdraw2dgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pdraw2dgraphics->fill_rectangle(get_data()->m_rectangleTab, argb(0xc0, 250, 255, 255));

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      ::collection::index iVisiblePane = 0;

      auto pbrushText = createø < ::draw2d::brush >();

      for (::i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
      {

         auto ppane = get_data()->m_tabpanea[iIndex].get();

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

         if (!get_element_rectangle(iVisiblePane, rectangleX, e_element_client))
         {

            continue;

         }

         if (get_data()->m_bVertical)
         {

            if (get_element_rectangle(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            if (get_data()->m_idaSel.contains(iIndex))
            {

               auto pdraw2dpen = createø < ::draw2d::pen >();

               pdraw2dpen->create_solid(1.0, argb(255, 0, 0, 0));

               pdraw2dgraphics->set(pdraw2dpen);

               auto pdraw2dpath = createø<::draw2d::path>();

               pdraw2dpath->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pdraw2dpath->add_line(rectangleBorder.left + 1, rectangleBorder.bottom);
               pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleX.left));
               pdraw2dpath->add_line(rectangleX.left, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);

               pdraw2dgraphics->draw(pdraw2dpath);

               auto pstyle = get_style(pdraw2dgraphics);

               pdraw2dgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

            }
            else
            {

               auto pdraw2dpen = createø < ::draw2d::pen >();

               pdraw2dpen->create_solid(1.0, argb(255, 0, 0, 0));

               pdraw2dgraphics->set(pdraw2dpen);

               auto pdraw2dpath = createø<::draw2d::path>();

               pdraw2dpath->set_current_point(rectangleBorder.right, rectangleBorder.bottom);
               pdraw2dpath->add_line(rectangleBorder.left + 1, rectangleBorder.bottom);
               pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleX.left));
               pdraw2dpath->add_line(rectangleText.left, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom);

               pdraw2dgraphics->draw(pdraw2dpath);

               if (::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  auto pstyle = get_style(pdraw2dgraphics);

                  pdraw2dgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText = get_data()->m_pbrushClose;

               }
               else
               {

                  auto pstyle = get_style(pdraw2dgraphics);

                  auto pwritetextfont = get_font(pstyle, e_state_hover);

                  pdraw2dgraphics->set(pwritetextfont);

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));


               }

            }

         }
         else
         {

            if (get_element_rectangle(iVisiblePane, rectangleIcon, e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            if (get_data()->m_idaSel.contains(ppane->id()))
            {

               auto pdraw2dpen = createø < ::draw2d::pen >();

               pdraw2dpen->create_solid(1.0, argb(255, 0, 0, 0));

               pdraw2dgraphics->set(pdraw2dpen);

               auto pdraw2dpath = createø<::draw2d::path >();

               pdraw2dpath->set_current_point(rectangleBorder.left, rectangleX.bottom);
               pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));
               pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);

               pdraw2dgraphics->draw(pdraw2dpath);

               auto pstyle = get_style(pdraw2dgraphics);

               pdraw2dgraphics->set(get_font(pstyle, e_state_selected));

               pbrushText->create_solid(argb(255, 0, 0, 0));

            }
            else
            {

               auto pdraw2dpen = createø < ::draw2d::pen >();

               pdraw2dpen->create_solid(1.0, argb(255, 0, 0, 0));

               pdraw2dgraphics->set(pdraw2dpen);

               auto pdraw2dpath = createø<::draw2d::path >();

               pdraw2dpath->set_current_point(rectangleBorder.left, rectangleX.bottom);
               pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);
               pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));
               pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);
               pdraw2dpath->add_line(rectangleBorder.left, rectangleX.bottom);

               pdraw2dgraphics->draw(pdraw2dpath);

               if (::is_item(m_pitemHover, iVisiblePane) && !::is_element(m_pitemHover, e_element_close_tab_button))
               {

                  pdraw2dgraphics->set(get_font(pstyle, e_state_hover));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  pdraw2dgraphics->set(get_font(pstyle));

                  pbrushText->create_solid(get_color(pstyle, ::e_element_item_text));

               }

            }

         }

         if (get_element_rectangle(iVisiblePane, rectangleText, e_element_text))
         {

            pdraw2dgraphics->set(pbrushText);

            pdraw2dgraphics->_DrawText(ppane->get_title(), rectangleText, e_align_bottom_left);

         }

         if (get_element_rectangle(iVisiblePane, rectangleClose, e_element_close_tab_button))
         {

            pdraw2dgraphics->set(get_font(pstyle, e_element_close_tab_button));

            if (::is_item(m_pitemHover, iVisiblePane) && ::is_element(m_pitemHover, e_element_close_tab_button))
            {

               pbrushText = get_data()->m_pbrushCloseSel;

               pbrushText->create_solid(argb(0xff, 255, 127, 0));

            }
            else
            {

               pbrushText->create_solid(argb(0xff, 0, 0, 0));

            }

            pdraw2dgraphics->set(pbrushText);

            pdraw2dgraphics->draw_text("x", rectangleClose, e_align_center);

         }

         iVisiblePane++;

      }

   }


   void tab::on_perform_top_down_layout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      auto rectangleX = this->rectangle(e_layout_sketch);

      if (!rectangleX)
      {

         return;

      }

      //if (is_top_level_full_screen_or_transparent())
      //{

      //   m_bEffectiveVisibleTabs = false;

      //}

      auto_hide_calculate_control_visibility();

      _001OnTabLayout(pdraw2dgraphics);

   }


   void tab::_001OnTabLayout(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

       auto rectangleX = this->rectangle(e_layout_sketch);

      if (!rectangleX)
      {

         return;

      }

      ::pointer<::berg::style>pstyle = get_style(pdraw2dgraphics);

      if (pstyle)
      {

         if (pstyle->_001OnTabLayout(pdraw2dgraphics, this))
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

      pdraw2dgraphics->set(get_font(pstyle, e_element_close_tab_button));

      m_pgraphicsextension->get_text_extent(pdraw2dgraphics, MAGIC_PALACE_TAB_SIZE, get_data()->m_sizeSep);

      if (get_data()->m_bVertical)
      {

         ::i32 iTabWidth = 16;

         ::i32 iTabHeight = 8;

         ::i32 cx;

         ::i32 cy;

         for (::i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_pgraphicsextension, pdraw2dgraphics);

            ::f64_size size;

            m_pgraphicsextension->get_text_extent(pdraw2dgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {

               size.cx += ppane->m_pimage->width() + 2;

               size.cy = maximum(size.cy, ppane->m_pimage->height());

            }

            cx = (::i32)(size.cx + 2.0);

            if (!ppane->m_bPermanent)
            {

               cx += 2 + 16 + 2;

            }

            if (cx > iTabWidth)
            {

               iTabWidth = cx;

            }

            cy = (::i32)(size.cy + 2.0);

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

         //::i32_rectangle rectangleX;

         //this->rectangle(rectangleX);

         get_data()->m_rectangleTab.left = rectangleX.left;
         get_data()->m_rectangleTab.top = rectangleX.top;
         get_data()->m_rectangleTab.right = get_data()->m_rectangleTab.left + get_data()->m_iTabWidth;
         get_data()->m_rectangleTab.bottom = rectangleX.bottom;

         get_data()->m_rectangleHosting.left = m_bEffectiveVisibleControl ? get_data()->m_rectangleTab.right : rectangleX.left;
         get_data()->m_rectangleHosting.top = get_data()->m_rectangleTab.top;
         get_data()->m_rectangleHosting.right = rectangleX.right;
         get_data()->m_rectangleHosting.bottom = get_data()->m_rectangleTab.bottom;

      }
      else
      {

         ::i32 iTabHeight = 16;

         ::i32 cy;

         pdraw2dgraphics->set(get_font(pstyle, e_state_selected));

         //         ::i32_rectangle rectangleX;

         //         this->rectangle(rectangleX);

         ::i32 x = rectangleX.left;

         ::i32 ixAdd;

         for (::i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanea[iIndex].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(m_pgraphicsextension, pdraw2dgraphics);

            ::f64_size size;

            m_pgraphicsextension->get_text_extent(pdraw2dgraphics, str, size);

            if (ppane->m_pimage->is_ok())
            {

               size.cy = maximum(size.cy, ppane->m_pimage->size().cy);

            }

            cy = (::i32)(size.cy + 2.0);

            if (cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            ppane->m_point.x = x;

            ppane->m_point.y = rectangleX.top;

            ixAdd = 5;

            if (ppane->m_pimage->is_set())
            {

               ixAdd += ppane->m_pimage->width() + 2;

            }

            if (!ppane->m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx = (::i32)(size.cx + ixAdd
                                         + get_data()->m_rectangleBorder.left + get_data()->m_rectangleBorder.right
                                         + get_data()->m_rectangleMargin.left + get_data()->m_rectangleMargin.right
                                         + get_data()->m_rectangleTextMargin.left + get_data()->m_rectangleTextMargin.right);

            x += ppane->m_size.cx;
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

         for (::i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanea[iIndex].get();

            ppane->m_size.cy = iTabHeight;

         }

         get_data()->m_rectangleTab.left = rectangleX.left;
         get_data()->m_rectangleTab.top = rectangleX.top;
         get_data()->m_rectangleTab.right = rectangleX.right;
         get_data()->m_rectangleTab.bottom = get_data()->m_rectangleTab.top + get_data()->m_iTabHeight;

         ::i32_rectangle & rectangleHosting = get_data()->m_rectangleHosting;

         rectangleHosting.left = get_data()->m_rectangleTab.left;
         rectangleHosting.top = m_bEffectiveVisibleControl ? get_data()->m_rectangleTab.bottom : rectangleX.top;
         rectangleHosting.right = get_data()->m_rectangleTab.right;
         rectangleHosting.bottom = rectangleX.bottom;

         //TRACE0("rectangleHosting");
      }

      {

         //               ::u32 dwTime2= ::time::now();

         //informationf("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //informationf("usertab::on_layout call time2= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }

      for (::i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
      {

         if (iIndex != get_current_tab_index())
         {

            layout_pane(iIndex);

         }

      }

      layout_pane(get_current_tab_index(), is_window_visible());

      if (m_pdata->m_bVertical)
      {

         m_sizeBarDragScroll.cy = (::i32)m_pdata->m_tabpanea.get_count() * m_pdata->m_iTabHeight;


      }
      else
      {

         m_sizeBarDragScroll.cx = m_pdata->m_tabpanea.last()->m_point.x +
                                    m_pdata->m_tabpanea.last()->m_size.cx;

      }

   }


} // namespace user



