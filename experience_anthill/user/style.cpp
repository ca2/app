#include "framework.h"
#include "style.h"
#include "acme/user/user/tool_item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/drawing.h"
#include "aura/user/user/frame.h"
#include "base/user/menu/central.h"
#include "base/user/user/tab_pane.h"
#include "base/user/user/tab.h"
#include "base/user/user/tab_data.h"
#include "base/user/user/toolbar.h"
#include "base/user/user/split_layout.h"
#include "base/user/user/user.h"
#include "base/platform/system.h"
#include "aura/platform/node.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience_anthill
{


   style::style()
   {

   }


   style::~style()
   {

   }


   void style::initialize_theme()
   {

      ::base::style::initialize_theme();

      __defer_construct(m_pfont);

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 12.0);

   }


   ::color::color style::get_color(::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate)
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_tab)
         {

            if (eelement == ::e_element_item_background)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return argb(128, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return argb(128, 205, 205, 255);

                  }
                  else
                  {

                     return argb(0, 0, 0, 0);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return argb(128, 192, 192, 192);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return argb(128, 205, 205, 255);

                  }
                  else
                  {

                     return argb(0, 0, 0, 0);

                  }

               }

            }
            else if (eelement == ::e_element_item_border)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::color::color(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::color::color(255, 235, 235, 255);

                  }
                  else
                  {

                     return ::color::color(255, 200, 200, 200);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::color::color(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::color::color(255, 20, 20, 20);

                  }
                  else
                  {

                     return ::color::color(255, 55, 55, 55);

                  }

               }

            }
            else if (eelement == ::e_element_item_text)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::color::color(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::color::color(255, 235, 235, 255);

                  }
                  else
                  {

                     return ::color::color(255, 200, 200, 200);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::color::color(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::color::color(255, 20, 20, 20);

                  }
                  else
                  {

                     return ::color::color(255, 100, 100, 100);

                  }

               }

            }

         }

         if (econtroltype == ::user::e_control_type_list)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  return ::color::color(255, 0, 0, 0);

               }
               else
               {

                  return ::color::color(255, 255, 255, 255);

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_button)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  //return ::color::color(255, 0x20, 0x45, 0x60);
                  return pinteraction->top_level_frame()->get_moveable_border_color();

               }
               else
               {

                  //return ::color::color(255, 0x30, 0x75, 0xA0);
                  return pinteraction->top_level_frame()->get_moveable_border_color();

               }


            }

         }
         else if (econtroltype == ::user::e_control_type_toolbar)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  return ::color::color(255, 0, 0, 0);

               }
               else
               {

                  return ::color::color(255, 255, 255, 255);

               }

            }
            else if (eelement == ::e_element_face)
            {

               if (estate & ::user::e_state_disabled)
               {

                  return ::color::color(255, 128, 128, 128);

               }

               if (estate & ::user::e_state_pressed)
               {

                  return ::color::color(255, 0x07, 0x6D, 0x91);

               }

               if (estate & ::user::e_state_hover)
               {

                  auto colorHover = pinteraction->top_level_frame()->get_moveable_border_color();

                  colorHover.lightness_rate(0.2);

                  return colorHover;
                  //return ::color::color(255, 0x55, 0x99, 0xC2);

               }

               //return ::color::color(255, 0x30, 0x75, 0xA0);
               return pinteraction->top_level_frame()->get_moveable_border_color();

            }

         }
         else if (econtroltype == ::user::e_control_type_scroll_bar)
         {

            if(eelement == e_element_background)
            {

               if(is_dark_mode())
               {

                  return ::argb(100, 255, 255, 255);

               }
               else
               {

                  return ::argb(100, 0, 0, 0);

               }


            }

         }

      }

      if (eelement == ::e_element_tab_item_background)
      {

         if (estate & ::user::e_state_selected)
         {

            if (is_dark_mode())
            {

               return ::color::color(255, 185, 185, 180);

            }
            else
            {


               return ::color::color(255, 235, 235, 230);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::color::color(255, 125, 125, 120);

            }
            else
            {


               return ::color::color(255, 175, 175, 170);

            }

         }

      }
      else if (eelement == ::e_element_background
         || eelement == ::e_element_tab_client_background
         || eelement == ::e_element_tab_layout_background)
      {

         if (is_dark_mode())
         {

            return ::color::color(255, 0, 0, 0);

         }
         else
         {

            return ::color::color(255, 255, 255, 255);

         }

      }
      else if (eelement == ::e_element_text)
      {

         if (is_dark_mode())
         {


            if (estate & ::user::e_state_new_input)
            {

               return ::color::color(255, 127, 127, 127);

            }
            else
            {

               return ::color::color(255, 255, 255, 255);

            }

         }
         else
         {

            if (estate & ::user::e_state_new_input)
            {

               return ::color::color(255, 192, 192, 192);

            }
            else
            {

               return ::color::color(255, 0, 0, 0);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         return ::color::color(255, 127, 127, 127);

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_selected)
         {


            if (estate & ::user::e_state_hover)
            {

               if (is_dark_mode())
               {

                  return ::color::color(50, 120, 190, 127);

               }
               else
               {

                  return ::color::color(100, 160, 220, 127);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return ::color::white;

               }
               else
               {

                  return ::color::black;

               }

            }

         }
         else
         {


            if (estate & ::user::e_state_hover)
            {

               if (is_dark_mode())
               {

                  return ::color::color(50, 120, 190, 127);

               }
               else
               {

                  return ::color::color(100, 160, 220, 127);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return ::color::white;

               }
               else
               {

                  return ::color::black;

               }

            }

         }

      }
      else if (eelement == ::e_element_item_background)
      {

         if (estate & ::user::e_state_selected)
         {

            if (estate & ::user::e_state_hover)
            {

               if (is_dark_mode())
               {

                  return ::color::color(100, 110, 120, 127);

               }
               else
               {

                  return ::color::color(180, 190, 200, 127);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return argb(60, 255, 255, 255);

               }
               else
               {

                  return argb(60, 0, 0, 0);

               }

            }

         }
         else
         {

            if (estate & ::user::e_state_hover)
            {

               if (is_dark_mode())
               {

                  return ::color::color(100, 160, 220, 127);

               }
               else
               {

                  return ::color::color(50, 120, 190, 127);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return ::color::black;

               }
               else
               {

                  return ::color::white;

               }

            }

         }

      }
      else if(eelement == e_element_scrollbar_trackbar
      || eelement == e_element_scrollbar_strong)
      {

         if(is_dark_mode())
         {

            return ::argb(100, 255, 255, 255);

         }
         else
         {

            return ::argb(100, 0, 0, 0);

         }


      }

      return ::color::color();

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      ::rectangle_i32 r1 = ptab->get_client_rect();

      ::rectangle_f64 r2;

      pgraphics->get_clip_box(r2);

      auto pstyle = ptab->get_style(pgraphics);

      {

         ::color::color colorBack = ptab->get_color(pstyle, ::e_element_background);

         pgraphics->fill_rectangle(r1, colorBack);

      }

      ptab->get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rcTab;

      rcTab = ptab->get_data()->m_rectangleTab;

      ::rectangle_i32 rcTabs(rcTab);

      ::rectangle_i32 rcClient;

      rcClient = ptab->get_data()->m_rectangleTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectangleBorder.bottom;

      rcClient.top = rcTabs.bottom;

      auto colorBack = ptab->get_color(pstyle, ::e_element_tab_layout_background);

      if (colorBack.is_ok())
      {

         pgraphics->fill_rectangle(rcTabs, colorBack);

      }

      colorBack = ptab->get_color(pstyle, ::e_element_tab_client_background);

      if (colorBack.is_ok())
      {

         pgraphics->fill_rectangle(rcClient, colorBack);

      }

      ::color::color color1 = ptab->get_color(pstyle, ::e_element_tab_item_background);

      ::color::color color2(color1);

      color2.hls_rate(0.0, 0.2, 0.0);

      ::index iTab = -1;

      auto pbrushText = __create < ::draw2d::brush >();

      auto ppenBorder = __create < ::draw2d::pen >();

      for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

         iTab++;

         ::user::e_state estate = ::user::e_state_none;

         if (ptab->get_data()->m_idaSel.contains(ppane->m_atom))
         {

            estate |= ::user::e_state_selected;

         }

         if (::is_item(ptab->m_pitemHover, iTab))
         {

            estate |= ::user::e_state_hover;

         }

         if (!ptab->get_element_rect(iTab, rectangle, ::e_element_tab))
            continue;

         if (!ptab->get_element_rect(iTab, rectangleBorder, ::e_element_border))
            continue;

         if (!ptab->get_element_rect(iTab, rectangleClient, ::e_element_client))
            continue;

         if (ptab->get_data()->m_bVertical)
         {

            if (ptab->get_element_rect(iTab, rectangleIcon, ::e_element_icon))
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

               if (ptab->get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  //ppath->start_figure();

                  ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
                  //ppath->add_line(rectangleClient.right, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
                  ppath->add_line(rectangleClient.left, rectangleBorder.top);
                  ppath->add_line(rectangleBorder.right, rectangleBorder.top);

                  ppath->close_figure();

                  ::color::color colorSel1 = ptab->get_color(pstyle, ::e_element_item_background, ::user::e_state_selected);

                  ::color::color colorSel2(colorSel1);

                  colorSel2.hls_rate(0.0, 0.2, 0.0);

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), colorSel1, colorSel2);

                  pgraphics->set(ppane->m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  if (::is_item(ptab->m_pitemHover, iTab)
                     && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                     && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected | ::user::e_state_hover));

                  }
                  else
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

                  }

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

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

                     ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     pgraphics->set(ppane->m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(ppenBorder);

                     auto pstyle = ptab->get_style(pgraphics);

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_hover));

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  }
                  else
                  {

                     ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                     pgraphics->set(ppane->m_pbrushFill);

                     pgraphics->fill(ppath);

                     ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(ppenBorder);

                     pgraphics->draw(ppath);

                     auto pstyle = ptab->get_style(pgraphics);

                     pgraphics->set(ptab->get_font(pstyle));

                     pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if (ptab->get_element_rect(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            if (iPane == 0)
            {

               if (rcTab.left < rectangleBorder.left)
               {

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw_line(rcTab.left, rectangleClient.bottom, rectangleBorder.left, rectangleClient.bottom);

               }

            }

            if (true)
            {

               //auto ppath = __create < ::draw2d::path > ();

               ::color::color colorBackground = ptab->get_color(pstyle, ::e_element_item_background, estate);

               pgraphics->fill_rectangle(rectangleBorder, colorBackground);

               ::color::color colorBorder = ptab->get_color(pstyle, ::e_element_item_border, estate);

               ppenBorder->create_solid(2.0, colorBorder);

               pgraphics->set(ppenBorder);

               ::size_i32 sizeTopOffset(0, 2);

               pgraphics->set_current_point(rectangleBorder.bottom_right());

               pgraphics->line_to(rectangleBorder.top_right() + sizeTopOffset);

               if (estate & ::user::e_state_selected)
               {

                  pgraphics->line_to(rectangleBorder.top_left() + sizeTopOffset);

               }

               //pgraphics->set(ppenBorder);

               //pgraphics->draw(ppath);

               //auto pstyle = ptab->get_style(pgraphics);

               //if (::is_item(ptab->m_pitemHover, iTab)
               //   && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
               //   && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               //{

               //   pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected | ::user::e_state_hover));

               //}
               //else
               //{

               //   pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

               //}

               ::color::color colorText = ptab->get_color(pstyle, ::e_element_item_text, estate);

               pbrushText->create_solid(colorText);

               //}
               //else
               //{

               //   //ppath->begin_figure(true, ::draw2d::e_fill_mode_winding);

               //   //if (iPane > 0)
               //   //{

               //   //   ppath->add_line(rectangle.left, rectangleClient.bottom, rectangleBorder.left, rectangleClient.bottom);

               //   //}

               //   //ppath->add_line(rectangleBorder.left,rectangleClient.bottom,rectangleBorder.left,rectangleBorder.top);

               //   //ppath->add_line(rectangleClient.right,rectangleBorder.top);

               //   //ppath->add_line(rectangleBorder.right,rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

               //   //ppath->add_line(rectangleBorder.right - 1,rectangleClient.bottom);

               //   //ppath->close_figure();

               //   if (::is_item(ptab->m_pitemHover, iTab)
               //      && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
               //      && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               //   {

               //      ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

               //      pgraphics->set(ppane->m_pbrushFillHover);

               //      //pgraphics->fill(ppath);

               //      ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

               //      pgraphics->set(ppenBorder);

               //      //pgraphics->draw(ppath);

               //      auto pfont = ptab->get_font(pstyle, ::user::e_state_hover);

               //      pgraphics->set(pfont);

               //      pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               //   }
               //   else
               //   {

               //      ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(), color1, color2);

               //      pgraphics->set(ppane->m_pbrushFill);

               //      //pgraphics->fill(ppath);

               //      ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

               //      pgraphics->set(ppenBorder);

               //      //pgraphics->draw(ppath);

               //      auto pfont = ptab->get_font(pstyle);

               //      pgraphics->set(pfont);

               //      pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               //   }

               //}

            }

            if (iPane == ptab->get_data()->m_tabpanecompositea.get_upper_bound())
            {

               if (rectangleBorder.right - 1 < rcTab.right)
               {

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw_line(rectangleBorder.right - 1, rectangleClient.bottom, rcTab.right, rectangleClient.bottom);

               }

            }

         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectangleText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(*ppane, ptab, pgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectangleClose, ::e_element_close_tab_button))
            {

               pgraphics->set(ptab->get_font(pstyle, ::e_element_close_tab_button));

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


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
   {

      auto pstyle = ptab->get_style(pgraphics);

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(pbrushText);

      if (straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), rectangle, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rectangle_i32 rectangleText(rectangle);

         ::write_text::font_pointer pfont;
         pfont = pgraphics->get_current_font();
         size_i32 sSep = ptab->get_data()->m_sizeSep;
         ::rectangle_i32 rectangleEmp;
         for (index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size_i32 s = pane.m_sizeaText[i];
            rectangleText.right = rectangleText.left + s.cx;

            if (estate & ::user::e_state_selected)
            {

               pfont->m_iFontWeight = 800;

            }
            else
            {

               pfont->m_iFontWeight = 400;

            }

            pfont->set_modified();

            pgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);
            rectangleText.left += s.cx;
            if (i < straTitle.get_upper_bound())
            {
               rectangleText.right = rectangleText.left + sSep.cx;
               rectangleEmp = rectangleText;
               rectangleEmp.deflate(1, 1);
               ::draw2d::enum_alpha_mode emode = pgraphics->alpha_mode();
               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
               if (::is_element(ptab->m_pitemHover, (::enum_element)(::e_element_split + i)))
               {

                  pgraphics->fill_rectangle(rectangleEmp, argb(128, 150, 184, 255));

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  pgraphics->set(pbrushText);

               }
               else
               {

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  pgraphics->set(pbrushText);

               }

               pgraphics->set(ptab->get_font(pstyle, ::e_element_close_tab_button));

               pgraphics->set_alpha_mode(emode);

               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);

               rectangleText.left += sSep.cx;

            }

         }

      }

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      auto pstyle = ptab->get_style(pgraphics);

      if (!ptab->get_data()->m_bCreated)
      {

         return false;

      }

      ::user::tab_data * pdata = ptab->get_data();

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

      pdata->m_rectangleMargin = ptab->get_margin(pstyle);

      pdata->m_rectangleBorder = ptab->get_border(pstyle);

      pdata->m_rectangleTextMargin = ptab->get_padding(pstyle);

      int iTextLeftMargin = 4;

      pdata->m_rectangleTextMargin.left += iTextLeftMargin;

      if (pdata->m_bVertical)
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right +
            pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right;

      }
      else
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right +
            pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right;

      }

      ptab->m_pdcextension->get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, ptab->get_data()->m_sizeSep);

      if (ptab->get_data()->m_bVertical)
      {

         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;

         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pdcextension, pgraphics);

            ::size_i32 size;

            ptab->m_pdcextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {
               size.cx += ppane->m_pimage->width() + 2;
               size.cy = maximum(size.cy, ppane->m_pimage->height());
            }

            int iTextLeftMargin = 4;

            cx = size.cx + 2 + iTextLeftMargin;

            if (!ppane->m_bPermanent)
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

         ::rectangle_i32 rectangleClient = ptab->get_client_rect();

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
         //         ::draw2d::graphics_pointer graphics(e_create);
           //       pgraphics->CreateCompatibleDC(nullptr);
             //     ::draw2d::graphics_pointer & pgraphics = graphics;

         pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

         ::rectangle_i32 rectangleClient = ptab->get_client_rect();

         int x = rectangleClient.left;

         i32 ixAdd;

         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return false;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pdcextension, pgraphics);

            size_i32 size;

            ptab->m_pdcextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage)
            {

               size.cy = maximum(size.cy, ppane->m_pimage->height());

            }

            cy = size.cy + 2;

            if (cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            ppane->m_point.x = x;
            ppane->m_point.y = rectangleClient.top;


            //            string str = ppane->get_title();

            //            size_i32 size;

            ixAdd = 5;

            if (ppane->m_pimage->is_set())
            {

               //::image_list::info ii;
               ixAdd += ppane->m_pimage->width() + 2;

            }

            if (!ppane->m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx = size.cx + ixAdd
               + ptab->get_data()->m_rectangleBorder.left + ptab->get_data()->m_rectangleBorder.right
               + ptab->get_data()->m_rectangleMargin.left + ptab->get_data()->m_rectangleMargin.right
               + ptab->get_data()->m_rectangleTextMargin.left + ptab->get_data()->m_rectangleTextMargin.right;

            x += ppane->m_size.cx;

         }

         // close tab button
         cy = 2 + 16 + 2;

         if (cy > iTabHeight)
         {

            iTabHeight = cy;

         }

         auto pdata = ptab->get_data();

         iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom + 
            pdata->m_iHeightAddUp;

         pdata->m_iTabHeight = iTabHeight;

         for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            ppane->m_size.cy = iTabHeight;

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

         auto & rectangleTabClient = ptab->get_data()->m_rectangleTabClient;

         rectangleTabClient.left = ptab->get_data()->m_rectangleTab.left;
         rectangleTabClient.top = ptab->m_bShowTabs ? ptab->get_data()->m_rectangleTab.bottom : rectangleClient.top;
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


   //   bool style::on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow)
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


   bool style::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      _001DrawAnthillToolbarItem(pgraphics, iItem, ptoolbar);

      return true;

   }


   void style::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectangleItem;

      ::rectangle_i32 rectangleImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      auto ptoolitem = ptoolbar->index_tool_item(iItem);

      auto estyle = ptoolbar->tool_item_style(iItem);

      auto puser = user();

      ::pointer<::user::menu_central>pmenucentral = puser->menu();

      ::u32 uImage = pmenucentral->command_image(ptoolitem->m_atom);

      ::user::enum_state estate = ptoolbar->tool_item_user_state(iItem);

      //      ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
      //      ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
      //      ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
      //      if ((nStyle & e_tool_item_style_separator) == 0)
      //      {
      //         if ((nStyle & e_tool_item_style_disabled) == 0)
      //         {
      //            // item is enabled
      //            if (ptoolbar->m_iButtonPressItem >= 0)
      //            {
      //               if (iItem == ptoolbar->m_iButtonPressItem)
      //               {
      //                  if (bHover)
      //                  {
      //                     eelement = ::user::toolbar::element_item_press;
      //                     eelementImage = ::user::toolbar::element_image_press;
      //                     eelementText = ::user::toolbar::element_text_press;
      //                  }
      //                  else
      //                  {
      //                     eelement = ::user::toolbar::element_item_hover;
      //                     eelementImage = ::user::toolbar::element_image_hover;
      //                     eelementText = ::user::toolbar::element_text_hover;
      //                  }
      //               }
      //            }
      //            else if (bHover)
      //            {
      //               eelement = ::user::toolbar::element_item_hover;
      //               eelementImage = ::user::toolbar::element_image_hover;
      //               eelementText = ::user::toolbar::element_text_hover;
      //            }
      //         }
      //         else
      //         {
      //            // item is disabled
      //            eelement = ::user::toolbar::e_element_item;
      //            eelementImage = ::user::toolbar::element_image;
      //            eelementText = ::user::toolbar::e_element_text;
      //         }
      //      }
      //      else
      //      {
      //         eelement = ::user::toolbar::e_element_item;
      //         eelementImage = ::user::toolbar::element_image;
      //         eelementText = ::user::toolbar::e_element_text;
      //      }


            //int iOffsetX = 0;
            //int iOffsetY = 0;

      ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, estate);

      ptoolbar->index_element_rectangle(iItem, rectangleImage, ::e_element_image, estate);

      if ((estyle & e_tool_item_style_separator) != 0)
      {
         ::rectangle_i32 rectangleSeparator;
         rectangleSeparator.left = (rectangleImage.left + rectangleImage.right) / 2 - 1;
         rectangleSeparator.right = rectangleSeparator.left + 2;
         rectangleSeparator.top = rectangleImage.top;
         rectangleSeparator.bottom = rectangleImage.bottom;

         pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));

      }
      else
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_checked)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, estate);

               ptoolbar->index_element_rectangle(iItem, rectangleImage, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_inset_rectangle(rectangleItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_rectangle(rectangleItem, argb(255, 127, 127, 127));

               }

               if (uImage != 0xffffffffu)
               {

                  if (!(estate & ::user::e_state_disabled))
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rectangle_i32 rectangleShadow;

               ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::e_element_item, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  auto ppen = __create < ::draw2d::pen >();

                  ppen->create_solid(1, argb(190, 92, 184, 92));
                  auto pbrush = __create < ::draw2d::brush >();

                  pbrush->create_solid(argb(123, 180, 184, 255));
                  pgraphics->set(ppen);
                  pgraphics->set(pbrush);
                  pgraphics->rectangle(rectangleItem);

               }

               if (ptoolitem->m_pimage->is_set())
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, ::user::e_state_hover);

                  image_source imagesource(ptoolitem->m_pimage, ::rectangle_f64(rectangle.size()));

                  image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.9);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_item, ::user::e_state_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
               }

            }

         }
         else if (estate & ::user::e_state_pressed)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1, argb(255, 92, 92, 92));
               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(argb(255, 255, 255, 255));
               pgraphics->set(ppen);
               pgraphics->set(pbrush);
               pgraphics->rectangle(rectangleItem);

            }

            if (ptoolitem->m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, ::user::e_state_pressed);

               image_source imagesource(ptoolitem->m_pimage, ::rectangle_f64(rectangle.size()));

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }
         else
         {

            if (!(estate & ::user::e_state_disabled))
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, ::user::e_state_none);

               pgraphics->fill_rectangle(rectangleItem, argb(190, 255, 255, 255));

            }

            if (estate & ::user::e_state_checked)
            {

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if (ptoolitem->m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, ::user::e_state_none);

               image_source imagesource(ptoolitem->m_pimage, ::rectangle_f64(rectangle.size()));

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.2);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }

            }

         }

      }

      if (ptoolitem->m_str.has_char())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::rectangle_i32 rectangleText;

         auto pbrushText = __create < ::draw2d::brush >();

         if (!(estyle & e_tool_item_style_disabled))
         {

            pbrushText->create_solid(argb(255, 0, 0, 0));

         }
         else
         {

            pbrushText->create_solid(argb(255, 120, 120, 118));

         }

         pgraphics->set(pbrushText);

         if (ptoolbar->index_element_rectangle(iItem, rectangleText, ::e_element_text, ::user::e_state_none) && rectangleText.right > 0)
         {

            pgraphics->_DrawText(ptoolitem->m_str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }

   void style::_001DrawAnthillToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      auto pstyle = ptoolbar->get_style(pgraphics);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectangleItem;

      ::rectangle_i32 rectangleImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      auto ptoolitem = ptoolbar->index_tool_item(iItem);

      //auto estyle = ptoolbar->get_item_style(iItem);

//      bool bHover = ptoolbar->m_pitemHover == iItem;

      auto puser = user();

      ::pointer<::user::menu_central>pmenucentral = puser->menu();

      ::u32 uImage = pmenucentral->command_image(ptoolitem->m_atom);

      ::user::enum_state estate = ptoolbar->tool_item_user_state(iItem);

      ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, estate);

      ptoolbar->index_element_rectangle(iItem, rectangleImage, ::e_element_image, estate);

      if (ptoolitem->m_atom.compare_ci("separator") == 0)
      {
         /*::rectangle_i32 rectangleSeparator;
         rectangleSeparator.left = (rectangleImage.left + rectangleImage.right) / 2 - 1;
         rectangleSeparator.right = rectangleSeparator.left + 2;
         rectangleSeparator.top = rectangleImage.top;
         rectangleSeparator.bottom = rectangleImage.bottom;*/
         //pgraphics->Draw3dRect(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      }
      else
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_checked)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, estate);

               ptoolbar->index_element_rectangle(iItem, rectangleImage, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_rectangle(rectangleItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

               }

               if (uImage != 0xffffffffu)
               {

                  if (!(estate & ::user::e_state_disabled))
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rectangle_i32 rectangleShadow;

               ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::e_element_item, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  auto ppen = __create < ::draw2d::pen >();

                  ppen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_hover));
                  auto pbrush = __create < ::draw2d::brush >();

                  pbrush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_hover));
                  pgraphics->set(ppen);
                  pgraphics->set(pbrush);
                  pgraphics->rectangle(rectangleItem);

               }

               if (ptoolitem->m_pimage->is_set())
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, ::user::e_state_hover);

                  image_source imagesource(ptoolitem->m_pimage, ::rectangle_f64(rectangle.size()));

                  image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.8);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_item, ::user::e_state_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
               }

            }

         }
         else if (estate & ::user::e_state_pressed)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_pressed));
               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_pressed));
               pgraphics->set(ppen);
               pgraphics->set(pbrush);
               pgraphics->rectangle(rectangleItem);

            }

            if (ptoolitem->m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, ::user::e_state_pressed);

               image_source imagesource(ptoolitem->m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }
         else
         {

            //if (!(estate & ::user::e_state_disabled))
            //{

            //   ptoolbar->index_element_rectangle(iItem, rectangleItem, ::e_element_item, ::user::e_state_none);

            //   pgraphics->fill_rectangle(rectangleItem, ptoolbar->get_color(pstyle, ::e_element_background));

            //}

            if (estate & ::user::e_state_checked)
            {

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __create < ::draw2d::pen >();

               ppen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, estate));
               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, estate));
               pgraphics->set(ppen);
               pgraphics->set(pbrush);
               pgraphics->rectangle(rectangleItem);

            }

            if (ptoolitem->m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::e_element_image, estate);

               image_source imagesource(ptoolitem->m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.20);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }

            }

         }

      }

      if (ptoolitem->m_str.has_char())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::rectangle_i32 rectangleText;

         auto pbrushText = __create < ::draw2d::brush >();

         if (!(estate & ::user::e_state_disabled))
         {

            pbrushText->create_solid(argb(255, 255, 255, 255));

            pgraphics->set_text_color(argb(255, 255, 255, 255));

         }
         else
         {

            pbrushText->create_solid(ptoolbar->get_color(pstyle, ::e_element_background,
               ::user::e_state_disabled));

            pgraphics->set_text_color(ptoolbar->get_color(pstyle, ::e_element_text,
               ::user::e_state_disabled));

         }

         if (ptoolbar->index_element_rectangle(iItem, rectangleText, ::e_element_text, estate) && rectangleText.right > 0)
         {

            pgraphics->set(pbrushText);

            pgraphics->draw_text(ptoolitem->m_str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }


   bool style::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      ::rectangle_i32 rectangleClient = psplitlayout->get_client_rect();

      pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      return true;

   }

   //
   //   bool style::get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext)
   //   {
   //
   //      return ::user::style::get_font(sp, efont, pcontext);
   //
   //   }

   //
   //   bool style::get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext)
   //   {
   //
   //      if (edouble == ::user::double_list_item_height_rate)
   //      {
   //
   //         d = 1.65;
   //
   //         return true;
   //
   //      }
   //
   //      return ::user::style::get_double(d, edouble, pcontext);
   //
   //   }



} // namespace experience_anthill




