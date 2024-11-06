#include "framework.h"
#include "style.h"
#include "acme/user/user/tool_item.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/user/user/frame_interaction.h"
#include "base/user/menu/central.h"
#include "base/user/user/tab_pane.h"
#include "base/user/user/tab.h"
#include "base/user/user/tab_data.h"
#include "base/user/user/toolbar.h"
#include "base/user/user/split_layout.h"
#include "base/user/user/user.h"
#include "base/platform/system.h"
#include "aura/platform/node.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The int_size is the int_size of the alien!!
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

//      auto psystem = system();
//
//      auto pnode = psystem->node();

      m_pfont->create_font(e_font_sans_ui, 12_pt);

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

                     return ::argb(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::argb(255, 235, 235, 255);

                  }
                  else
                  {

                     return ::argb(255, 200, 200, 200);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::argb(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::argb(255, 20, 20, 20);

                  }
                  else
                  {

                     return ::argb(255, 55, 55, 55);

                  }

               }

            }
            else if (eelement == ::e_element_item_text)
            {

               if (is_dark_mode())
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::argb(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::argb(255, 235, 235, 255);

                  }
                  else
                  {

                     return ::argb(255, 200, 200, 200);

                  }

               }
               else
               {

                  if (estate & ::user::e_state_selected)
                  {

                     return ::argb(255, 255, 255, 255);

                  }
                  else if (estate & ::user::e_state_hover)
                  {

                     return ::argb(255, 20, 20, 20);

                  }
                  else
                  {

                     return ::argb(255, 100, 100, 100);

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

                  return ::argb(255, 0, 0, 0);

               }
               else
               {

                  return ::argb(255, 255, 255, 255);

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_button)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  //return ::argb(255, 0x20, 0x45, 0x60);
                  return pinteraction->top_level_frame()->get_moveable_border_color();

               }
               else
               {

                  //return ::argb(255, 0x30, 0x75, 0xA0);
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

                  return ::argb(255, 0, 0, 0);

               }
               else
               {

                  return ::argb(255, 255, 255, 255);

               }

            }
            else if (eelement == ::e_element_face)
            {

               if (estate & ::user::e_state_disabled)
               {

                  return ::argb(255, 128, 128, 128);

               }

               if (estate & ::user::e_state_pressed)
               {

                  return ::argb(255, 0x07, 0x6D, 0x91);

               }

               if (estate & ::user::e_state_hover)
               {

                  auto colorHover = pinteraction->top_level_frame()->get_moveable_border_color();

                  colorHover.lightness_rate(0.2);

                  return colorHover;
                  //return ::argb(255, 0x55, 0x99, 0xC2);

               }

               //return ::argb(255, 0x30, 0x75, 0xA0);
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

               return ::argb(255, 185, 185, 180);

            }
            else
            {


               return ::argb(255, 235, 235, 230);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::argb(255, 125, 125, 120);

            }
            else
            {


               return ::argb(255, 175, 175, 170);

            }

         }

      }
      else if (eelement == ::e_element_background
         || eelement == ::e_element_tab_client_background
         || eelement == ::e_element_tab_layout_background)
      {

         if (is_dark_mode())
         {

            return ::argb(255, 0, 0, 0);

         }
         else
         {

            return ::argb(255, 255, 255, 255);

         }

      }
      else if (eelement == ::e_element_text)
      {

         if (is_dark_mode())
         {


            if (estate & ::user::e_state_new_input)
            {

               return ::argb(255, 127, 127, 127);

            }
            else
            {

               return ::argb(255, 255, 255, 255);

            }

         }
         else
         {

            if (estate & ::user::e_state_new_input)
            {

               return ::argb(255, 192, 192, 192);

            }
            else
            {

               return ::argb(255, 0, 0, 0);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         return ::argb(255, 127, 127, 127);

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_selected)
         {


            if (estate & ::user::e_state_hover)
            {

               if (is_dark_mode())
               {

                  return ::rgba(50, 120, 190, 127);

               }
               else
               {

                  return ::rgba(100, 160, 220, 127);

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

                  return ::rgba(50, 120, 190, 127);

               }
               else
               {

                  return ::rgba(100, 160, 220, 127);

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

                  return ::rgba(100, 110, 120, 127);

               }
               else
               {

                  return ::rgba(180, 190, 200, 127);

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

                  return ::rgba(100, 160, 220, 127);

               }
               else
               {

                  return ::rgba(50, 120, 190, 50);

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
      else if (eelement == ::e_element_scrollbar)
      {

         return argb(100, 192, 192, 192);

      }
      else if (eelement == ::e_element_scrollbar_trackbar)
      {

         return argb(160, 140, 140, 140);

      }
      else if (eelement == ::e_element_scrollbar_rectA)
      {

         return argb(160, 140, 140, 140);

      }
      else if (eelement == ::e_element_scrollbar_rectB)
      {

         return argb(160, 140, 140, 140);

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
            {

               return argb(255, 130, 130, 130);

            }
            else
            {

               return argb(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return argb(255, 230, 230, 230);

            }
            else
            {

               return argb(255, 40, 40, 40);

            }

         }

      }
      else if (eelement == ::e_element_item_background)
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_selected)
            {

               if (is_dark_mode())
               {

                  return argb(255, 150, 150, 150);

               }
               else
               {

                  return argb(255, 160, 160, 160);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return argb(255, 110, 110, 110);

               }
               else
               {

                  return argb(255, 200, 200, 200);

               }

            }

         }
         else
         {

            if (estate & ::user::e_state_selected)
            {

               if (is_dark_mode())
               {

                  return argb(255, 130, 130, 130);

               }
               else
               {

                  return argb(255, 180, 180, 180);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return argb(255, 80, 80, 80);

               }
               else
               {

                  return argb(255, 255, 255, 255);

               }

            }

         }

         }
      else if (eelement == ::e_element_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
            {

               return argb(255, 130, 130, 130);

            }
            else
            {

               return argb(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return argb(255, 230, 230, 230);

            }
            else
            {

               return argb(255, 40, 40, 40);

            }

         }

         }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
            {

               return argb(255, 130, 130, 130);

            }
            else
            {

               return argb(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return argb(255, 230, 230, 230);

            }
            else
            {

               return argb(255, 40, 40, 40);

            }

         }

         }
      else if (eelement == ::e_element_background)
      {

         if (is_dark_mode())
         {

            if (estate & ::user::e_state_hover)
            {

               return argb(127, 120, 120, 120);

            }
            else
            {

               return argb(127, 80, 80, 80);

            }

         }
         else
         {

            if (estate & ::user::e_state_hover)
            {

               return argb(127, 230, 230, 230);

            }
            else
            {

               return argb(127, 210, 210, 210);

            }


         }

         }
      else
      {

         if (is_dark_mode())
         {

            return argb(255, 50, 50, 50);

         }
         else
         {

            return argb(255, 40, 40, 40);

         }

      }


      return {};

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      ::int_rectangle rectangle;
      ::int_rectangle rectangleBorder;
      ::int_rectangle rectangleText;
      ::int_rectangle rectangleX;
      ::int_rectangle rectangleIcon;
      ::int_rectangle rectangleClose;

      ::int_rectangle r1 = ptab->rectangle();

      ::double_rectangle r2;

      pgraphics->get_clip_box(r2);

      auto pstyle = ptab->get_style(pgraphics);

      {

         ::color::color colorBack = ptab->get_color(pstyle, ::e_element_background);

         pgraphics->fill_rectangle(r1, colorBack);

      }

      ptab->get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_rectangle rcTab;

      rcTab = ptab->get_data()->m_rectangleTab;

      ::int_rectangle rcTabs(rcTab);

      ::int_rectangle rcClient;

      rcClient = ptab->get_data()->m_rectangleHosting;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top();

      rcTabs.bottom() = rcTabs.top() + iTabHeight - ptab->get_data()->m_rectangleBorder.bottom();

      rcClient.top() = rcTabs.bottom();

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

      ::collection::index iTab = -1;

      auto pbrushText = __create < ::draw2d::brush >();

      auto ppenBorder = __create < ::draw2d::pen >();

      for (int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
      {

         auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

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

         if (!ptab->get_element_rectangle(iTab, rectangle, ::e_element_tab))
            continue;

         if (!ptab->get_element_rectangle(iTab, rectangleBorder, ::e_element_border))
            continue;

         if (!ptab->get_element_rectangle(iTab, rectangleX, ::e_element_client))
            continue;

         if (ptab->get_data()->m_bVertical)
         {

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __create < ::draw2d::path >();

            if (true)
            {

               if (ptab->get_data()->m_idaSel.contains(ppane->m_atom))
               {

                  //ppath->start_figure();

                  ppath->add_line(rectangleBorder.right(), rectangleBorder.bottom(), rectangleBorder.left() + 1, rectangleBorder.bottom());
                  //ppath->add_line(rectangleX.right(), rectangleBorder.top());
                  ppath->add_line(rectangleBorder.left(), rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
                  ppath->add_line(rectangleX.left(), rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(), rectangleBorder.top());

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

                  ppath->add_line(rectangleBorder.right(), rectangleBorder.bottom(), rectangleBorder.left() + 1, rectangleBorder.bottom());
                  ppath->add_line(rectangleBorder.left(), rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
                  ppath->add_line(rectangleText.left(), rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(), rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(), rectangleBorder.bottom());

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

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            if (iPane == 0)
            {

               if (rcTab.left() < rectangleBorder.left())
               {

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw_line(rcTab.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleX.bottom());

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

               ::int_size sizeTopOffset(0, 2);

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

               //   //   ppath->add_line(rectangle.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleX.bottom());

               //   //}

               //   //ppath->add_line(rectangleBorder.left(),rectangleX.bottom(),rectangleBorder.left(),rectangleBorder.top());

               //   //ppath->add_line(rectangleX.right(),rectangleBorder.top());

               //   //ppath->add_line(rectangleBorder.right(),rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

               //   //ppath->add_line(rectangleBorder.right() - 1,rectangleX.bottom());

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

            if (iPane == ptab->get_data()->m_tabpanea.get_upper_bound())
            {

               if (rectangleBorder.right() - 1 < rcTab.right())
               {

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw_line(rectangleBorder.right() - 1, rectangleX.bottom(), rcTab.right(), rectangleX.bottom());

               }

            }

         }

         if (true)
         {

            if (ptab->get_element_rectangle(iTab, rectangleText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(*ppane, ptab, pgraphics, rectangleText, pbrushText, estate);

            }

         }

         if (true)
         {

            if (ptab->get_element_rectangle(iTab, rectangleClose, ::e_element_close_tab_button))
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


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
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

         ::int_rectangle rectangleText(rectangle);

         ::write_text::font_pointer pfont;
         pfont = pgraphics->get_current_font();
         int_size sSep = ptab->get_data()->m_sizeSep;
         ::int_rectangle rectangleEmp;
         for (::collection::index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            int_size s = pane.m_sizeaText[i];
            rectangleText.right() = rectangleText.left() + s.cx();

            if (estate & ::user::e_state_selected)
            {

               pfont->m_fontweight = e_font_weight_bold;

            }
            else
            {

               pfont->m_fontweight = e_font_weight_normal;

            }

            pfont->set_modified();

            pgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);
            rectangleText.left() += s.cx();
            if (i < straTitle.get_upper_bound())
            {
               rectangleText.right() = rectangleText.left() + sSep.cx();
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

               rectangleText.left() += sSep.cx();

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

      //ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

      pdata->m_rectangleMargin = ptab->get_margin(pstyle);

      pdata->m_rectangleBorder = ptab->get_border(pstyle);

      pdata->m_rectangleTextMargin = ptab->get_padding(pstyle);

      int iTextLeftMargin = 4;

      pdata->m_rectangleTextMargin.left() += iTextLeftMargin;

      if (pdata->m_bVertical)
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
            pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right() +
            pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right();

      }
      else
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
            pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right() +
            pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right();

      }

      ptab->m_pgraphicsextension->get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, ptab->get_data()->m_sizeSep);

      if (ptab->get_data()->m_bVertical)
      {

         int iTabWidth = 16;
         int iTabHeight = 8;
         int cx;
         int cy;

         for (int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pgraphics);

            ::double_size size;

            ptab->m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {
               size.cx() += ppane->m_pimage->width() + 2;
               size.cy() = maximum(size.cy(), ppane->m_pimage->height());
            }

            int iTextLeftMargin = 4;

            cx = (int) ( size.cx() + 2 + iTextLeftMargin);

            if (!ppane->m_bPermanent)
            {

               cx += 2 + 16 + 2;

            }

            if (cx > iTabWidth)
            {

               iTabWidth = cx;

            }

            cy = (int) (size.cy() + 2);

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

         iTabWidth += ptab->get_data()->m_rectangleBorder.left() + ptab->get_data()->m_rectangleBorder.right() +
            ptab->get_data()->m_rectangleMargin.left() + ptab->get_data()->m_rectangleMargin.right() +
            ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data()->m_rectangleTextMargin.right();

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectangleBorder.top() + ptab->get_data()->m_rectangleBorder.bottom() +
            ptab->get_data()->m_rectangleMargin.top() + ptab->get_data()->m_rectangleMargin.bottom() +
            ptab->get_data()->m_rectangleTextMargin.top() + ptab->get_data()->m_rectangleTextMargin.bottom();

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::int_rectangle rectangleX = ptab->rectangle(::user::e_layout_lading);

         ptab->get_data()->m_rectangleTab.left() = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top() = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right() = ptab->get_data()->m_rectangleTab.left() + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectangleTab.bottom() = rectangleX.bottom();

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         ptab->get_data()->m_rectangleHosting.left() = ptab->m_bEffectiveVisibleControl ? ptab->get_data()->m_rectangleTab.right() : rectangleX.left();
         ptab->get_data()->m_rectangleHosting.top() = ptab->get_data()->m_rectangleTab.top();
         ptab->get_data()->m_rectangleHosting.right() = rectangleX.right();
         ptab->get_data()->m_rectangleHosting.bottom() = ptab->get_data()->m_rectangleTab.bottom();

      }
      else
      {
         int iTabHeight = 16;
         int cy;
         //         ::draw2d::graphics_pointer graphics(e_create);
           //       pgraphics->CreateCompatibleDC(nullptr);
             //     ::draw2d::graphics_pointer & pgraphics = graphics;

         pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

         ::int_rectangle rectangleX = ptab->rectangle(::user::e_layout_lading);

         int x = rectangleX.left();

         int ixAdd;

         for (int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return false;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pgraphics);

            double_size size;

            ptab->m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage)
            {

               size.cy() = maximum(size.cy(), ppane->m_pimage->height());

            }

            cy = (int) (size.cy() + 2);

            if (cy > iTabHeight)
            {

               iTabHeight = cy;

            }

            ppane->m_point.x() = x;
            ppane->m_point.y() = rectangleX.top();


            //            string str = ppane->get_title();

            //            int_size size;

            ixAdd = 5;

            if (ppane->m_pimage->is_set())
            {

               //::image::image_list::info ii;
               ixAdd += ppane->m_pimage->width() + 2;

            }

            if (!ppane->m_bPermanent)
            {

               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx() = (int) (size.cx() + ixAdd
               + ptab->get_data()->m_rectangleBorder.left() + ptab->get_data()->m_rectangleBorder.right()
               + ptab->get_data()->m_rectangleMargin.left() + ptab->get_data()->m_rectangleMargin.right()
               + ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data()->m_rectangleTextMargin.right());

            x += ppane->m_size.cx();

         }

         // close tab button
         cy = 2 + 16 + 2;

         if (cy > iTabHeight)
         {

            iTabHeight = cy;

         }

         auto pdata = ptab->get_data();

         iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
            pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom() + 
            pdata->m_iHeightAddUp;

         pdata->m_iTabHeight = iTabHeight;

         for (int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

            ppane->m_size.cy() = iTabHeight;

         }




         ptab->get_data()->m_rectangleTab.left() = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top() = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right() = rectangleX.right();
         ptab->get_data()->m_rectangleTab.bottom() = ptab->get_data()->m_rectangleTab.top() + ptab->get_data()->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         auto & rectangleHosting = ptab->get_data()->m_rectangleHosting;

         rectangleHosting.left() = ptab->get_data()->m_rectangleTab.left();
         rectangleHosting.top() = ptab->m_bEffectiveVisibleControl ? ptab->get_data()->m_rectangleTab.bottom() : rectangleX.top();
         rectangleHosting.right() = ptab->get_data()->m_rectangleTab.right();
         rectangleHosting.bottom() = rectangleX.bottom();

         //TRACE0("rectangleHosting");

      }

      for (int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
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


   bool style::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar)
   {

      _001DrawAnthillToolbarItem(pgraphics, iItem, ptoolbar);

      return true;

   }


   void style::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_rectangle rectangleItem;

      ::int_rectangle rectangleImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      auto ptoolitem = ptoolbar->tool_item_at(iItem);

      auto estyle = ptoolbar->tool_item_style(iItem);

      auto puser = user();

      ::pointer<::user::menu_central>pmenucentral = puser->menu();

      unsigned int uImage = pmenucentral->command_image(ptoolitem->m_atom);

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

      rectangleItem = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

      rectangleImage = ptoolbar->index_element_rectangle(iItem, ::e_element_image, estate);

      if ((estyle & e_tool_item_style_separator) != 0)
      {
         ::int_rectangle rectangleSeparator;
         rectangleSeparator.left() = (rectangleImage.left() + rectangleImage.right()) / 2 - 1;
         rectangleSeparator.right() = rectangleSeparator.left() + 2;
         rectangleSeparator.top() = rectangleImage.top();
         rectangleSeparator.bottom() = rectangleImage.bottom();

         pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255), 1.0);

      }
      else
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_checked)
            {

               rectangleItem = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

               rectangleImage = ptoolbar->index_element_rectangle(iItem, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_inset_rectangle(rectangleItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_rectangle(rectangleItem, argb(255, 127, 127, 127), 1.0);

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

               //auto rectangleShadow = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

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

                  auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, ::user::e_state_hover);

                  ::image::image_source imagesource(ptoolitem->m_pimage, ::double_rectangle(rectangle.size()));

                  ::image::image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.9);

                  ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_item, ::user::e_state_hover);

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

               auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, ::user::e_state_pressed);

               ::image::image_source imagesource(ptoolitem->m_pimage, ::double_rectangle(rectangle.size()));

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

               rectangleItem = ptoolbar->index_element_rectangle(iItem, ::e_element_item, ::user::e_state_none);

               pgraphics->fill_rectangle(rectangleItem, argb(190, 255, 255, 255));

            }

            if (estate & ::user::e_state_checked)
            {

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255), 1.0);

            }

            if (ptoolitem->m_pimage->is_set())
            {

               auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, ::user::e_state_none);

               ::image::image_source imagesource(ptoolitem->m_pimage, ::double_rectangle(rectangle.size()));

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.2);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

      if (ptoolitem->m_str.has_character())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::status < ::int_rectangle > rectangleText;

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

         rectangleText = ptoolbar->index_element_rectangle(iItem, ::e_element_text, ::user::e_state_none);

         if (rectangleText.ok() && rectangleText.right() > 0)
         {

            pgraphics->_DrawText(ptoolitem->m_str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }

   void style::_001DrawAnthillToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar)
   {

      auto pstyle = ptoolbar->get_style(pgraphics);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_rectangle rectangleItem;

      ::int_rectangle rectangleImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      auto ptoolitem = ptoolbar->tool_item_at(iItem);

      //auto estyle = ptoolbar->get_item_style(iItem);

//      bool bHover = ptoolbar->m_pitemHover == iItem;

      auto puser = user();

      ::pointer<::user::menu_central>pmenucentral = puser->menu();

      unsigned int uImage = pmenucentral->command_image(ptoolitem->m_atom);

      ::user::enum_state estate = ptoolbar->tool_item_user_state(iItem);

      rectangleItem = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

      rectangleImage = ptoolbar->index_element_rectangle(iItem, ::e_element_image, estate);

      if (ptoolitem->m_atom.case_insensitive_order("separator") == 0)
      {
         /*::int_rectangle rectangleSeparator;
         rectangleSeparator.left() = (rectangleImage.left() + rectangleImage.right()) / 2 - 1;
         rectangleSeparator.right() = rectangleSeparator.left() + 2;
         rectangleSeparator.top() = rectangleImage.top();
         rectangleSeparator.bottom() = rectangleImage.bottom();*/
         //pgraphics->Draw3dRect(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      }
      else
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_checked)
            {

               rectangleItem = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

               rectangleImage = ptoolbar->index_element_rectangle(iItem, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_rectangle(rectangleItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255), 1.0);

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

               //auto rectangleShadow = ptoolbar->index_element_rectangle(iItem, ::e_element_item, estate);

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

                  auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, ::user::e_state_hover);

                  ::image::image_source imagesource(ptoolitem->m_pimage, ::double_rectangle(rectangle.size()));

                  ::image::image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.8);

                  ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_item, ::user::e_state_hover);

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

               auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, ::user::e_state_pressed);

               ::image::image_source imagesource(ptoolitem->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255), 1.0);

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

               auto rectangle = ptoolbar->index_element_rectangle(iItem, ::e_element_image, estate);

               ::image::image_source imagesource(ptoolitem->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.20);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

      if (ptoolitem->m_str.has_character())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::status < ::int_rectangle > rectangleText;

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

         rectangleText = ptoolbar->index_element_rectangle(iItem, ::e_element_text, estate);

         if (rectangleText.ok() && rectangleText.right() > 0)
         {

            pgraphics->set(pbrushText);

            pgraphics->draw_text(ptoolitem->m_str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }


   bool style::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      ::int_rectangle rectangleX = psplitlayout->rectangle();

      pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

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




