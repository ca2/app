#include "framework.h"
#include "base/user/menu/central.h"
#include "base/user/user/tab_pane.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience
{


   namespace anthill
   {


      style::style()
      {

         m_pfont.create(e_create);

      }


      style::~style()
      {

      }


      void style::initialize_theme()
      {

         ::base::style::initialize_theme();

         auto psystem = m_psystem->m_paurasystem;

         auto pnode = psystem->node();

         m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 12.0);

      }

   
      ::color::color style::get_color(const ::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate) const
      {

         if (::is_set(pinteraction))
         {

            auto econtroltype = pinteraction->get_control_type();

            if (econtroltype == ::user::e_control_type_list)
            {

               if (eelement == ::e_element_background)
               {

               if (is_dark_mode())
                  {

                     return __acolor(255, 0, 0, 0);

                  }
                  else
                  {

                     return __acolor(255, 255, 255, 255);

                  }

               }

            }
            else if (econtroltype == ::user::e_control_type_button)
            {

               if (eelement == ::e_element_background)
               {

               if (is_dark_mode())
                  {

                     //return __acolor(255, 0x20, 0x45, 0x60);
                     return pinteraction->top_level_frame()->get_moveable_border_color();

                  }
                  else
                  {

                     //return __acolor(255, 0x30, 0x75, 0xA0);
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

                     return __acolor(255, 0, 0, 0);

                  }
                  else
                  {

                     return __acolor(255, 255, 255, 255);

                  }

               }
               else if (eelement == ::e_element_face)
               {
                  
                  if(estate & ::user::e_state_disabled)
                  {
                     
                     return __acolor(255, 128, 128, 128);
                     
                  }

                  if(estate & ::user::e_state_pressed)
                  {
                     
                     return __acolor(255, 0x07, 0x6D, 0x91);
                     
                  }

                  if(estate & ::user::e_state_hover)
                  {
                     
                     auto colorHover = pinteraction->top_level_frame()->get_moveable_border_color();

                     colorHover.lightness_rate(0.2);

                     return colorHover;
                     //return __acolor(255, 0x55, 0x99, 0xC2);
                     
                  }

                  //return __acolor(255, 0x30, 0x75, 0xA0);
                  return pinteraction->top_level_frame()->get_moveable_border_color();

               }

            }

         }

         if (eelement == ::e_element_tab_item_background)
         {

            if (estate & ::user::e_state_selected)
            {

                              if (is_dark_mode())
               {

                  return __acolor(255, 185, 185, 180);

               }
               else
               {


                  return __acolor(255, 235, 235, 230);

               }

            }
            else
            {

                              if (is_dark_mode())
               {

                  return __acolor(255, 125, 125, 120);

               }
               else
               {


                  return __acolor(255, 175, 175, 170);

               }

            }

         }
         else if (eelement == ::e_element_background
            || eelement == ::e_element_tab_client_background
            || eelement == ::e_element_tab_layout_background)
         {

                           if (is_dark_mode())
            {

               return __acolor(255, 0, 0, 0);

            }
            else
            {

               return __acolor(255, 255, 255, 255);

            }

         }
         else if (eelement == ::e_element_text)
         {
            
                           if (is_dark_mode())
            {


               if (estate & ::user::e_state_new_input)
               {

                  return __acolor(255, 127, 127, 127);

               }
               else
               {

                  return __acolor(255, 255, 255, 255);

               }

            }
            else
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

         }
         else if (eelement == ::e_element_border)
         {

            return __acolor(255, 127, 127, 127);
         
         }
         else if (eelement == ::e_element_item_text)
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

                     return ::color::black;

                  }
                  else
                  {

                     return ::color::white;

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

         return ::color::color();

      }
   

   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectBorder;
      ::rectangle_i32 rectText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectIcon;
      ::rectangle_i32 rectClose;

      ::rectangle_i32 r1 = ptab->get_client_rect();

      ::rectangle_f64 r2;

      pgraphics->get_clip_box(&r2);

      auto pstyle = ptab->get_style(pgraphics);

      {

         ::color::color colorBack = ptab->get_color(pstyle, ::e_element_background);

         pgraphics->fill_rectangle(r1, colorBack);

      }

      ptab->get_data()->m_pen->create_solid(1,rgb(32,32,32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rcTab;

      rcTab = ptab->get_data()->m_rectTab;

      ::rectangle_i32 rcTabs(rcTab);
      
      ::rectangle_i32 rcClient;

      rcClient = ptab->get_data()->m_rectTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectBorder.bottom;

      rcClient.top = rcTabs.bottom;
      
      auto colorBack = ptab->get_color(pstyle, ::e_element_tab_layout_background);
      
      if(colorBack.is_ok())
      {

         pgraphics->fill_rectangle(rcTabs, colorBack);
         
      }

      colorBack = ptab->get_color(pstyle, ::e_element_tab_client_background);
      
      if(colorBack.is_ok())
      {

         pgraphics->fill_rectangle(rcClient, colorBack);
         
      }

      ::color::color color1 = ptab->get_color(pstyle, ::e_element_tab_item_background);

      ::color::color color2(color1);

      color2.hls_rate(0.0, 0.2, 0.0);

      ::index iTab = -1;

      ::draw2d::brush_pointer brushText(e_create);

      ::draw2d::pen_pointer penBorder(e_create);

      for(i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {
          
            continue;

         }

         iTab++;

         if(!ptab->get_element_rect(iTab,rectangle,::e_element_tab))
            continue;

         if(!ptab->get_element_rect(iTab,rectBorder, ::e_element_border))
            continue;

         if(!ptab->get_element_rect(iTab,rectangleClient, ::e_element_client))
            continue;

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            ::draw2d::path_pointer path(e_create);

            if(true)
            {

               if(ptab->get_data()->m_idaSel.contains(ppane->m_id))
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  //path->add_line(rectangleClient.right, rectBorder.top);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectangleClient.left));
                  path->add_line(rectangleClient.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);

                  path->close_figure();

                  ::color::color colorSel1 = ptab->get_color(pstyle, ::e_element_tab_item_background, ::user::e_state_selected);

                  ::color::color colorSel2(colorSel1);

                  colorSel2.hls_rate(0.0, 0.2, 0.0);

                  ppane->m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),colorSel1,colorSel2);

                  pgraphics->set(ppane->m_brushFillSel);

                  pgraphics->fill_path(path);

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected | ::user::e_state_hover));

                  }
                  else
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

                  }

                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectangleClient.left));
                  path->add_line(rectText.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.bottom);

                  path->close_figure();

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     ppane->m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->set(ppane->m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(penBorder);
                     
                     auto pstyle = ptab->get_style(pgraphics);

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_hover));

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  }
                  else
                  {

                     ppane->m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                     pgraphics->set(ppane->m_brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(penBorder);
                     
                     pgraphics->draw_path(path);

                     auto pstyle = ptab->get_style(pgraphics);

                     pgraphics->set(ptab->get_font(pstyle));

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  }

               }

            }

         }
         else
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            if (iPane == 0)
            {

               if (rcTab.left < rectBorder.left)
               {

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(penBorder);

                  pgraphics->draw_line(rcTab.left, rectangleClient.bottom, rectBorder.left, rectangleClient.bottom);

               }

            }

            if(true)
            {

               ::draw2d::path_pointer path(e_create);

               if(ptab->get_data()->m_idaSel.contains(ppane->m_id))
               {

                  if (iPane > 0)
                  {

                     path->add_line(rectangle.left, rectangleClient.bottom, rectBorder.left, rectangleClient.bottom);

                  }

                  path->add_line(rectBorder.left,rectangleClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectangleClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectangleClient.right));

                  path->add_line(rectBorder.right - 1,rectangleClient.bottom);

                  path->close_figure();

                  ::color::color colorSel1 = ptab->get_color(pstyle, ::e_element_tab_item_background, ::user::e_state_selected);

                  ::color::color colorSel2(colorSel1);

                  colorSel2.hls_rate(0.0, 0.2, 0.0);

                  ppane->m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),colorSel1, colorSel2);

                  pgraphics->set(ppane->m_brushFillSel);

                  pgraphics->fill_path(path);

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  pgraphics->set(penBorder);

                  pgraphics->draw_path(path);
                  
                  auto pstyle = ptab->get_style(pgraphics);

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected | ::user::e_state_hover));

                  }
                  else
                  {

                     pgraphics->set(ptab->get_font(pstyle, ::user::e_state_selected));

                  }

                  ::color::color colorText = ptab->get_color(pstyle, ::e_element_text);

                  brushText->create_solid(colorText);

               }
               else
               {

                  //path->begin_figure(true, ::draw2d::fill_mode_winding);

                  if (iPane > 0)
                  {

                     path->add_line(rectangle.left, rectangleClient.bottom, rectBorder.left, rectangleClient.bottom);

                  }

                  path->add_line(rectBorder.left,rectangleClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectangleClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectangleClient.right));

                  path->add_line(rectBorder.right - 1,rectangleClient.bottom);

                  path->close_figure();

                  if (ptab->m_itemHover == iTab
                     && ptab->m_itemHover != ::e_element_close_tab_button
                     && !ptab->m_itemHover.in_range(::e_element_split, 100))
                  {

                     ppane->m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->set(ppane->m_brushFillHover);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     auto pfont = ptab->get_font(pstyle, ::user::e_state_hover);

                     pgraphics->set(pfont);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  }
                  else
                  {

                     ppane->m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(), color1, color2);

                     pgraphics->set(ppane->m_brushFill);

                     pgraphics->fill_path(path);

                     penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     pgraphics->set(penBorder);

                     pgraphics->draw_path(path);

                     auto pfont = ptab->get_font(pstyle);

                     pgraphics->set(pfont);

                     brushText->create_solid(ptab->get_color(pstyle, ::e_element_item, ::user::e_state_hover));

                  }

               }

            }

            if (iPane == ptab->get_data()->m_tabpanecompositea.get_upper_bound())
            {

               if (rectBorder.right - 1 < rcTab.right)
               {

                  penBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(penBorder);

                  pgraphics->draw_line(rectBorder.right - 1, rectangleClient.bottom, rcTab.right, rectangleClient.bottom);

               }

            }

         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(*ppane,ptab,pgraphics,rectText,brushText);

            }

         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectClose, ::e_element_close_tab_button))
            {

               pgraphics->set(ptab->get_font(pstyle, ::e_element_close_tab_button));

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

               pgraphics->draw_text("x",rectClose,e_align_center);

            }

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & brushText)
   {

      auto pstyle = ptab->get_style(pgraphics);

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), rectangle, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rectangle_i32 rectText(rectangle);

         ::write_text::font_pointer font;
         font = pgraphics->get_current_font();
         size_i32 sSep = ptab->get_data()->m_sizeSep;
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
               if(ptab->m_itemHover == (::enum_element)(::e_element_split + i))
               {

                  pgraphics->fill_rectangle(rectEmp,argb(128, 150, 184, 255));

                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

                  pgraphics->set(brushText);

               }
               else
               {
                  
                  brushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

                  pgraphics->set(brushText);

               }

               pgraphics->set(ptab->get_font(pstyle, ::e_element_close_tab_button));

               pgraphics->set_alpha_mode(emode);

               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText, e_align_center, e_draw_text_no_prefix);

               rectText.left += sSep.cx;

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

      pdata->m_rectMargin = ptab->get_margin(pstyle);

      pdata->m_rectBorder = ptab->get_border(pstyle);

      pdata->m_rectTextMargin = ptab->get_padding(pstyle);

      if (pdata->m_bVertical)
      {

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata->m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata->m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata->m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata->m_rectMargin.right;

      }
      else
      {

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata->m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata->m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata->m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata->m_rectMargin.right;

      }

      ptab->m_dcextension.get_text_extent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);

      if(ptab->get_data()->m_bVertical)
      {

         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;

         for(i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               continue;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_dcextension,pgraphics);

            ::size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics,str, size);

            if(ppane->m_pimage->is_set())
            {
               size.cx += ppane->m_pimage->width() + 2;
               size.cy = maximum(size.cy,ppane->m_pimage->height());
            }
            cx = size.cx + 2;

            if(!ppane->m_bPermanent)
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

         ::rectangle_i32 rectangleClient = ptab->get_client_rect();

         ptab->get_data()->m_rectTab.left       = rectangleClient.left;
         ptab->get_data()->m_rectTab.top        = rectangleClient.top;
         ptab->get_data()->m_rectTab.right      = ptab->get_data()->m_rectTab.left + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom     = rectangleClient.bottom;

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left       = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.right : rectangleClient.left;
         ptab->get_data()->m_rectTabClient.top        = ptab->get_data()->m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right      = rectangleClient.right;
         ptab->get_data()->m_rectTabClient.bottom     = ptab->get_data()->m_rectTab.bottom;

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

         for(i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return false;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_dcextension,pgraphics);

            size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics,str, size);

            if(ppane->m_pimage)
            {

               size.cy = maximum(size.cy,ppane->m_pimage->height());

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {
               
               iTabHeight = cy;

            }

            ppane->m_point.x = x;
            ppane->m_point.y = rectangleClient.top;


            //            string str = ppane->get_title();

            //            size_i32 size;

            ixAdd = 5;

            if(ppane->m_pimage->is_set())
            {
               
               //::image_list::info ii;
               ixAdd += ppane->m_pimage->width() + 2;

            }

            if(!ppane->m_bPermanent)
            {
               
               ixAdd += 2 + 16 + 2;

            }

            ppane->m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

            x += ppane->m_size.cx;

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

         for(i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            ppane->m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left       = rectangleClient.left;
         ptab->get_data()->m_rectTab.top        = rectangleClient.top;
         ptab->get_data()->m_rectTab.right      = rectangleClient.right;
         ptab->get_data()->m_rectTab.bottom     = ptab->get_data()->m_rectTab.top + ptab->get_data()->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         auto & rectTabClient = ptab->get_data()->m_rectTabClient;

         rectTabClient.left       = ptab->get_data()->m_rectTab.left;
         rectTabClient.top        = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.bottom : rectangleClient.top;
         rectTabClient.right      = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom     = rectangleClient.bottom;

         //TRACE0("rectTabClient");

      }

      for(i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         if(iPane != ptab->get_current_tab_index())
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


   bool style::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      _001DrawAnthillToolbarItem(pgraphics, iItem, ptoolbar);

      return true;

   }


   void style::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectItem;

      ::rectangle_i32 rectImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      auto estyle = ptoolbar->get_item_style(iItem);

      auto puser = user();

      __pointer(::user::menu_central) pmenucentral = puser->menu();

      ::u32 uImage = pmenucentral->command_image(item.m_id);
      
      ::user::enum_state estate = ptoolbar->get_item_user_state(iItem);

//      ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
//      ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
//      ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
//      if ((nStyle & e_toolbar_item_style_separator) == 0)
//      {
//         if ((nStyle & e_toolbar_item_style_disabled) == 0)
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

      ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, estate);

      ptoolbar->_001GetElementRect(iItem, rectImage, ::e_element_image, estate);

      if ((estyle & e_toolbar_item_style_separator) != 0)
      {
         ::rectangle_i32 rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;
         
         pgraphics->draw_inset_3drect(rectSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
         
      }
      else
      {

         if (estate & ::user::e_state_hover)
         {

            if (estate & ::user::e_state_checked)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, estate);

               ptoolbar->_001GetElementRect(iItem, rectImage, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_inset_rectangle(rectItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_rectangle(rectItem, argb(255, 127, 127, 127));
                  
               }

               if (uImage != 0xffffffffu)
               {

                  if (!(estate & ::user::e_state_disabled))
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rectangle_i32 rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::e_element_item, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1, argb(190, 92, 184, 92));
                  ::draw2d::brush_pointer brush(e_create);

                  brush->create_solid(argb(123, 180, 184, 255));
                  pgraphics->set(pen);
                  pgraphics->set(brush);
                  pgraphics->rectangle(rectItem);

               }

               if (item.m_pimage->is_set())
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, ::user::e_state_hover);

                  image_source imagesource(item.m_pimage, ::rectangle_f64(rectangle.size()));

                  image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.9);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_item, ::user::e_state_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (estate & ::user::e_state_pressed)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, argb(255, 92, 92, 92));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(argb(255, 255, 255, 255));
               pgraphics->set(pen);
               pgraphics->set(brush);
               pgraphics->rectangle(rectItem);

            }

            if (item.m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, ::user::e_state_pressed);

               image_source imagesource(item.m_pimage, ::rectangle_f64(rectangle.size()));

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            if (!(estate & ::user::e_state_disabled))
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, ::user::e_state_none);

               pgraphics->fill_rectangle(rectItem, argb(190, 255, 255, 255));

            }

            if (estate & ::user::e_state_checked)
            {

               pgraphics->draw_inset_3drect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if (item.m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, ::user::e_state_none);

               image_source imagesource(item.m_pimage, ::rectangle_f64(rectangle.size()));

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.2);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::rectangle_i32 rectText;

         ::draw2d::brush_pointer brushText(e_create);

         if (!(estyle & e_toolbar_item_style_disabled))
         {

            brushText->create_solid(argb(255, 0, 0, 0));

         }
         else
         {

            brushText->create_solid(argb(255, 120, 120, 118));

         }

         pgraphics->set(brushText);

         if (ptoolbar->_001GetElementRect(iItem, rectText, ::e_element_text, ::user::e_state_none) && rectText.right > 0)
         {

            pgraphics->_DrawText(item.m_str, rectText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }

   void style::_001DrawAnthillToolbarItem(::draw2d::graphics_pointer & pgraphics, ::index iItem, ::user::toolbar * ptoolbar)
   {

      auto pstyle = ptoolbar->get_style(pgraphics);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectItem;

      ::rectangle_i32 rectImage;

      pgraphics->set_font(ptoolbar, ::e_element_none);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      auto estyle = ptoolbar->get_item_style(iItem);

//      bool bHover = ptoolbar->m_itemHover == iItem;

      auto puser = user();

      __pointer(::user::menu_central) pmenucentral = puser->menu();

      ::u32 uImage = pmenucentral->command_image(item.m_id);

      ::user::enum_state estate = ptoolbar->get_item_user_state(iItem);

      ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, estate);

      ptoolbar->_001GetElementRect(iItem, rectImage, ::e_element_image, estate);

      if (item.m_id.compare_ci("separator") == 0)
      {
         /*::rectangle_i32 rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;*/
         //pgraphics->Draw3dRect(rectSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      }
      else
      {
         
         if (estate & ::user::e_state_hover)
         {
            
            if (estate & ::user::e_state_checked)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, estate);

               ptoolbar->_001GetElementRect(iItem, rectImage, ::e_element_image, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  pgraphics->fill_rectangle(rectItem, argb(208, 255, 255, 250));

                  pgraphics->draw_inset_3drect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

               }

               if (uImage != 0xffffffffu)
               {

                  if (!(estate & ::user::e_state_disabled))
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rectangle_i32 rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::e_element_item, estate);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_hover));
                  ::draw2d::brush_pointer brush(e_create);

                  brush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_hover));
                  pgraphics->set(pen);
                  pgraphics->set(brush);
                  pgraphics->rectangle(rectItem);

               }

               if (item.m_pimage->is_set())
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, ::user::e_state_hover);

                  image_source imagesource(item.m_pimage, ::rectangle_f64(rectangle.size()));

                  image_drawing_options imagedrawingoptions(rectangle);

                  imagedrawingoptions.opacity(0.8);

                  image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pgraphics->draw(imagedrawing);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rectangle_i32 rectangle;

                  ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_item, ::user::e_state_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (estate & ::user::e_state_pressed)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_pressed));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, ::user::e_state_pressed));
               pgraphics->set(pen);
               pgraphics->set(brush);
               pgraphics->rectangle(rectItem);

            }

            if (item.m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, ::user::e_state_pressed);

               image_source imagesource(item.m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            //if (!(estate & ::user::e_state_disabled))
            //{

            //   ptoolbar->_001GetElementRect(iItem, rectItem, ::e_element_item, ::user::e_state_none);

            //   pgraphics->fill_rectangle(rectItem, ptoolbar->get_color(pstyle, ::e_element_background));

            //}

            if (estate & ::user::e_state_checked)
            {

               pgraphics->draw_inset_3drect(rectItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ptoolbar->get_color(pstyle, ::e_element_face, estate));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ptoolbar->get_color(pstyle, ::e_element_face, estate));
               pgraphics->set(pen);
               pgraphics->set(brush);
               pgraphics->rectangle(rectItem);

            }

            if (item.m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               ptoolbar->_001GetElementRect(iItem, rectangle, ::e_element_image, estate);

               image_source imagesource(item.m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.20);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffff)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         pgraphics->set_font(ptoolbar, ::e_element_none);

         ::rectangle_i32 rectText;

         ::draw2d::brush_pointer brushText(e_create);

         if (!(estate & ::user::e_state_disabled))
         {

            brushText->create_solid(argb(255, 255, 255, 255));

            pgraphics->set_text_color(argb(255, 255, 255, 255));

         }
         else
         {

            brushText->create_solid(ptoolbar->get_color(pstyle, ::e_element_background,
            ::user::e_state_disabled));

            pgraphics->set_text_color(ptoolbar->get_color(pstyle, ::e_element_text,
            ::user::e_state_disabled));

         }

         if (ptoolbar->_001GetElementRect(iItem, rectText, ::e_element_text, estate) && rectText.right > 0)
         {

            pgraphics->set(brushText);

            pgraphics->draw_text(item.m_str, rectText, e_align_bottom_left, e_draw_text_no_prefix);

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



         } // namespace anthill


   } // namespace experience




