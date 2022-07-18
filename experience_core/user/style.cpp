#include "framework.h"
#include "base/user/simple/scroll_bar.h"
#include "base/user/user/tab_pane.h"
#include "aura/graphics/draw2d/_draw2d.h"


// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience_core
{


   style::style()
   {

   }


   style::~style()
   {


   }


   void style::on_initialize_object()
   {

      ::base::style::on_initialize_object();

      if (::is_null(m_pfont))
      {

         m_pfont.create(this);

         auto pnode = m_psystem->node();

         m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 12, e_font_weight_normal);

      }

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      enum
      {

         __e_none = 0,
         __e_hover = 1,
         __e_selected = 2,
         __e_selected_hover = 3,
         __e_alternate_none = 4,
         __e_alternate_hover = 5,
         __e_alternate_selected = 6,
         __e_alternate_selected_hover = 7,

      };

      ::rectangle_i32 rectangle;
      ::rectangle_i32 rectangleBorder;
      ::rectangle_i32 rectangleText;
      ::rectangle_i32 rectangleClient;
      ::rectangle_i32 rectangleIcon;
      ::rectangle_i32 rectangleClose;

      //return true;
      
      ::draw2d::savedc savedc(pgraphics);
      
      if (ptab->get_data()->m_bVertical)
      {
         
         pgraphics->OffsetViewportOrg(0., -ptab->m_iTabScroll);
         
      }
      else
      {
         
         pgraphics->OffsetViewportOrg(-ptab->m_iTabScroll, 0.);
         
      }

      ptab->get_data()->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      index iTab = -1;

      ::rectangle_i32 rcClient;

      ptab->get_client_rect(rcClient);
      
      if(rcClient.is_empty())
      {
         
         output_debug_string("style::_001TabOnDrawSchema01 Tab Client Rect is empty\n");
         
         return true;
         
      }
      
      //output_debug_string("style::_001TabOnDrawSchema01\n");

      auto pstyle = ptab->get_style(pgraphics);

      ::draw2d::brush_pointer pbrushText;

      static int iCurrentTab = -1;

      int iTabWidth = 0;

      int iTabHeight = 0;

      auto & holdeeTab = ptab->get_data()->m_holdee;

      auto & groupTabTheme = holdeeTab.m_map[::draw2d::e_change_theme][0];

      for (i32 iPane = 0; iPane < ptab->get_data()->m_tabpanecompositea.get_size(); iPane++)
      {

         auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

         auto & groupPaneLayout = ppane->m_holdee.m_map[::draw2d::e_change_layout][0];

         ::user::e_state estate = ::user::e_state_none;

         if (ptab->get_data()->m_idaSel.contains(ppane->m_atom))
         {

            estate |= ::user::e_state_selected;

         }

         if (::is_item(ptab->m_pitemHover, iTab))
         {

            estate |= ::user::e_state_hover;

         }

         iTab++;

         if (!ptab->get_element_rect(iTab, rectangle, ::e_element_tab))
         {

            continue;

         }

         if (!ptab->get_element_rect(iTab, rectangleBorder, ::e_element_border))
         {

            continue;

         }

         if (rectangleBorder.right > iTabWidth)
         {

            iTabWidth = rectangleBorder.right;

         }

         if (rectangleBorder.bottom > iTabHeight)
         {

            iTabHeight = rectangleBorder.bottom;

         }

         if (!ptab->get_element_rect(iTab, rectangleClient, ::e_element_client))
            continue;

         bool bTextRect = ptab->get_element_rect(iTab, rectangleText, ::e_element_text);

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

            if (ptab->get_data()->m_idaSel.contains(ppane->m_atom))
            {

               ppath->begin_figure();

               ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);

               ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));

               ppath->add_line(rectangleClient.left, rectangleBorder.top);

               ppath->add_line(rectangleBorder.right, rectangleBorder.top);

               ppath->close_figure();

               ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

               pgraphics->set(ppane->m_pbrushFillSel);

               pgraphics->fill(ppath);

               {

                  auto & ppen = groupTabTheme.m_pena[__e_selected];

                  if (!ppen)
                  {

                     __construct(ppen);

                     ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  }

                  pgraphics->set(ppen);

                  pgraphics->draw(ppath);

               }


               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  pgraphics->set_font(ptab, ::e_element_none, (::user::e_state_selected | ::user::e_state_hover));

               }
               else
               {

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

               }

               {

                  auto & pbrush = groupTabTheme.m_brusha[__e_selected];

                  if (!pbrush)
                  {

                     __defer_construct(pbrush);

                     auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected);

                     pbrush->create_solid(colorText);

                  }

                  pbrushText = pbrush;

               }

            }
            else
            {

               ppath->begin_figure();

               ppath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1, rectangleBorder.bottom);
               ppath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleClient.left));
               ppath->add_line(bTextRect ? rectangleText.left : rectangleBorder.left, rectangleBorder.top);
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

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_hover];

                     if (!ppen)
                     {

                        __construct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pgraphics->set(ppen);

                     pgraphics->draw(ppath);

                  }


                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                  pgraphics->set(ppane->m_pbrushFill);

                  pgraphics->fill(ppath);

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_none];

                     if (!ppen)
                     {

                        __construct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     }

                     pgraphics->set(ppen);

                     pgraphics->draw(ppath);

                  }

                  {

                     auto & pfont = groupTabTheme.m_fonta[__e_none];

                     if (!pfont)
                     {

                        pfont = ptab->get_font(pstyle, e_element_none);

                     }

                     pgraphics->set(pfont);

                  }

                  {

                     auto & pbrush = groupTabTheme.m_brusha[__e_none];

                     if (!pbrush)
                     {

                        __defer_construct(pbrush);

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text);

                        pbrush->create_solid(colorText);

                     }

                     pbrushText = pbrush;

                  }

               }

            }

         }
         else
         {

            // Horizontal Tab

            if (ptab->get_element_rect(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               image_source imagesource(ppane->m_pimage);

               image_drawing_options imagedrawingoptions(rectangleIcon);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            bool bPaneSelected = ptab->get_data()->m_idaSel.contains(ppane->m_atom);

            auto & ppath = groupPaneLayout.m_patha[
               bPaneSelected ? 
                  __e_selected : 
                  __e_none];

            if (bPaneSelected)
            {

               if (iPane != iCurrentTab)
               {

                  iCurrentTab = iPane;

               }

               if (!ppath)
               {

                  __construct(ppath);

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

               }

               {

                  auto & pbrush = groupPaneLayout.m_brusha[__e_selected];

                  if (!pbrush)
                  {

                     __construct(pbrush);

                     pbrush->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  }

                  pgraphics->set(pbrush);

                  pgraphics->fill(ppath);

               }

               {

                  auto & ppen = groupTabTheme.m_pena[__e_hover];

                  if (!ppen)
                  {

                     __construct(ppen);

                     ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                  }

                  pgraphics->set(ppen);

                  pgraphics->draw(ppath);

               }

               if (::is_item(ptab->m_pitemHover, iTab)
                  && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  auto & pfont = groupTabTheme.m_fonta[__e_selected_hover];

                  if (!pfont)
                  {

                     pfont = ptab->get_font(pstyle, e_element_none, ::user::e_state_selected | ::user::e_state_hover);

                  }

                  pgraphics->set(pfont);


//                  pgraphics->set_font(ptab, ::e_element_none,);

               }
               else
               {

                  auto & pfont = groupTabTheme.m_fonta[__e_selected];

                  if (!pfont)
                  {

                     pfont = ptab->get_font(pstyle, e_element_none, ::user::e_state_selected);

                  }

                  pgraphics->set(pfont);

               }

               {

                  auto & pbrush = groupTabTheme.m_brusha[__e_selected];

                  if (!pbrush)
                  {

                     __defer_construct(pbrush);

                     auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected);

                     pbrush->create_solid(colorText);

                  }

                  pbrushText = pbrush;

               }

            }
            else
            {

               // Normal (NOT Selected)

               if (!ppath)
               {

                  __construct(ppath);

                  ppath->add_line(rectangleBorder.left, rectangleClient.bottom, rectangleBorder.left, rectangleBorder.top);

                  ppath->add_line(rectangleClient.right, rectangleBorder.top);

                  ppath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleClient.right));

                  ppath->add_line(rectangleBorder.right - 1, rectangleClient.bottom);

                  ppath->close_figure();

               }

               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  {

                     auto & pbrush = groupPaneLayout.m_brusha[__e_hover];

                     if (!pbrush)
                     {

                        __construct(pbrush);

                        pbrush->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     }

                     pgraphics->set(pbrush);

                     pgraphics->fill(ppath);

                  }

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_hover];

                     if (!ppen)
                     {

                        __construct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pgraphics->set(ppen);

                     pgraphics->draw(ppath);

                     {

                        auto & pfont = groupTabTheme.m_fonta[__e_hover];

                        if (!pfont)
                        {

                           pfont = ptab->get_font(pstyle, e_element_none, ::user::e_state_hover);

                        }

                        pgraphics->set(pfont);

                     }

                  }

                  {

                     auto & pbrush = groupTabTheme.m_brusha[__e_hover];

                     if (!pbrush)
                     {

                        __defer_construct(pbrush);

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover);

                        pbrush->create_solid(colorText);

                     }

                     pbrushText = pbrush;

                  }

               }
               else
               {

                  {

                     auto & pbrush = groupPaneLayout.m_brusha[__e_none];

                     if (!pbrush)
                     {

                        __construct(pbrush);

                        pbrush->CreateLinearGradientBrush(
                           rectangleBorder.top_left(),
                           rectangleBorder.bottom_left(),
                           argb(230, 175, 175, 170),
                           argb(250, 195, 195, 190)); //*/

                     }

                     // pbrushFill->create_solid(::color::color::white);

                     pgraphics->set(pbrush);

                     pgraphics->fill(ppath);

                  }

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_none];

                     if (!ppen)
                     {

                        __construct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     }

                     pgraphics->set(ppen);

                     pgraphics->draw(ppath);

                  }

                  {

                     auto & pfont = groupTabTheme.m_fonta[__e_none];

                     if (!pfont)
                     {

                        pfont = ptab->get_font(pstyle, e_element_none);

                     }

                     pgraphics->set(pfont);

                  }

                  {

                     auto & pbrush = groupTabTheme.m_brusha[__e_none];

                     if (!pbrush)
                     {

                        __defer_construct(pbrush);

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text);

                        pbrush->create_solid(colorText);

                     }

                     pbrushText = pbrush;

                  }

               }

            }

         }

         if (bTextRect)
         {

            _001OnTabPaneDrawTitle(*ppane, ptab, pgraphics, rectangleText, pbrushText, estate);

         }

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

      ::rectangle_i32 rectangleScroll;

      bool bScroll = ptab->_001HasTabScrolling();

      if (bScroll)
      {

         if (ptab->get_element_rect(-1, rectangleScroll, ::e_element_tab_near_scroll))
         {

            pgraphics->fill_rectangle(rectangleScroll, argb(255, 255, 255, 255));

         }

         if (ptab->get_element_rect(-1, rectangleScroll, ::e_element_tab_far_scroll))
         {

            pgraphics->fill_rectangle(rectangleScroll, argb(255, 255, 255, 255));

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(pbrushText);

      if (straTitle.get_count() <= 1)
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

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

            pgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

            rectangleText.left += s.cx;

            if (i < straTitle.get_upper_bound())
            {

               rectangleText.right = rectangleText.left + sSep.cx;

               rectangleEmp = rectangleText;

               rectangleEmp.deflate(1, 1);

               ::draw2d::enum_alpha_mode emode = pgraphics->alpha_mode();

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               status < ::color::color > colorText;

               if (::is_item(ptab->m_pitemHover, (::index) ::e_element_split + i))
               {

                  pgraphics->fill_rectangle(rectangleEmp, argb(128, 150, 190, 255));

                  colorText = ptab->get_color(this, ::e_element_item_text, ::user::e_state_hover);

               }
               else
               {

                  colorText = ptab->get_color(this, ::e_element_item_text);

               }

               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(colorText);

               pgraphics->set(pbrush);

               pgraphics->set_font(ptab, ::e_element_close_tab_button);

               pgraphics->set_alpha_mode(emode);

               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);

               rectangleText.left += sSep.cx;

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

         pdata->m_rectangleMargin.set(2, 3, 1, 0);

         pdata->m_rectangleBorder.set(11, 1, 6, 0);

         pdata->m_rectangleTextMargin.set(3, 0, 1, 0);

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right +
            pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right;

      }
      else
      {

         pdata->m_rectangleMargin.set(3, 2, 0, 1);

         pdata->m_rectangleBorder.set(0, 1, 11, 6);

         pdata->m_rectangleTextMargin.set(3, 0, 1, 0);

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right +
            pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right;

      }

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

            auto ppane = ptab->get_data()->m_tabpanecompositea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
               continue;

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_dcextension, pgraphics);

            ::size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics, str, size);



            if (ppane->m_pimage->is_set())
            {
               size.cx += ppane->m_pimage->width() + 2;
               size.cy = maximum(size.cy, ppane->m_pimage->height());
            }
            cx = size.cx + 2;

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

         pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::rectangle_i32 rectangleClient = ptab->get_client_rect();
         //ptab->get_client_rect(rectangleClient);
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

            ppane->do_split_layout(ptab->m_dcextension, pgraphics);

            size_i32 size;

            ptab->m_dcextension.get_text_extent(pgraphics, str, size);

            if (::is_ok(ppane->m_pimage))
            {

               size.cy = maximum(size.cy, ppane->m_pimage->size().cy);

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

            if (::is_ok(ppane->m_pimage))
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

         iTabHeight += ptab->get_data()->m_rectangleBorder.top + ptab->get_data()->m_rectangleBorder.bottom +
            ptab->get_data()->m_rectangleMargin.top + ptab->get_data()->m_rectangleMargin.bottom + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

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

         rectangle_i32 & rectangleTabClient = ptab->get_data()->m_rectangleTabClient;

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

         if (iPane != ptab->get_current_tab_id())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->get_current_tab_index(), ptab->is_this_visible());

      ::rectangle_i32 rcClient;

      ptab->get_client_rect(rcClient);

      if (ptab->get_data()->m_bVertical)
      {

         ptab->m_iTabSize = (int)(ptab->get_data()->m_tabpanecompositea.get_count() * ptab->get_data()->m_iTabHeight);

         ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.height();

      }
      else
      {

         ptab->m_iTabSize = ptab->get_data()->m_tabpanecompositea.last()->m_point.x +
            ptab->get_data()->m_tabpanecompositea.last()->m_size.cx;

         ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.width();

      }


      return true;

   }


   ::color::color style::get_color(const ::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate) const
   {

      if (::is_set(pinteraction))
      {

         //string strType = __type_name(pinteraction);

//            if (strType.contains("form"))
//            {
//
//               output_debug_string("form");
//
//            }

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_form)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  return ::color::color(80, 80, 80, 127);

               }
               else
               {

                  return ::color::color(255, 255, 255, 127);

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_edit)
         {

            if (estate & ::user::e_state_selected)
            {

               if (eelement == ::e_element_background)
               {

                  if (is_dark_mode())
                  {

                     return ::color::color(255, 255, 255, 127);

                  }
                  else
                  {

                     return ::color::color(80, 80, 80, 127);

                  }

               }
               else if (eelement == ::e_element_text)
               {

                  if (is_dark_mode())
                  {

                     return ::color::color(80, 80, 80, 255);

                  }
                  else
                  {

                     return ::color::color(255, 255, 255, 255);

                  }

               }

            }
            else
            {

               if (eelement == ::e_element_background)
               {

                  if (is_dark_mode())
                  {

                     return ::color::color(80, 80, 80, 127);

                  }
                  else
                  {

                     return ::color::color(255, 255, 255, 127);

                  }

               }
               else if (eelement == ::e_element_text)
               {

                  if (is_dark_mode())
                  {

                     return ::color::color(255, 255, 255, 255);

                  }
                  else
                  {

                     return ::color::color(80, 80, 80, 255);

                  }

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_list
            || econtroltype == ::user::e_control_type_tree)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  return argb(180, 80, 80, 80);

               }
               else
               {

                  return argb(127, 255, 255, 255);

               }

            }
            else if (eelement == ::e_element_item_background)
            {

               if (estate & ::user::e_state_selected)
               {

                  return __acolor(127, 0, 0, 0);

               }
               else
               {

                  return ::color::color(0, 0, 0, 0);

               }

            }
            else if (eelement == ::e_element_item_text)
            {

               if (is_dark_mode())
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

            if (eelement == ::e_element_item_text)
            {

               if (estate & ::user::e_state_hover)
               {

                  return ::color::color(255, 120, 150, 200);

               }
               else
               {

                  if (is_dark_mode())
                  {

                     return __acolor(255, 230, 230, 230);

                  }
                  else
                  {

                     return __acolor(255, 40, 40, 40);

                  }

               }

            }
            else if (eelement == ::e_element_item_background)
            {

               return ::color::color(0, 0, 0, 0);

            }

         }

      }

      if (eelement == ::e_element_check)
      {

         //if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
            {

               return __acolor(255, 255, 255, 255);

            }
            else
            {

               return __acolor(255, 0, 0, 0);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
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

            if (is_dark_mode())
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

            if (is_dark_mode())
            {

               return __acolor(255, 210, 210, 200);

            }
            else
            {

               return __acolor(255, 90, 90, 80);

            }

         }

      }
      else if (eelement == ::e_element_scrollbar)
      {

         return __acolor(100, 192, 192, 192);

      }
      else if (eelement == ::e_element_scrollbar_trackbar)
      {

         return __acolor(160, 140, 140, 140);

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
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

            if (is_dark_mode())
            {

               return __acolor(255, 230, 230, 230);

            }
            else
            {

               return __acolor(255, 40, 40, 40);

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

                  return __acolor(255, 150, 150, 150);

               }
               else
               {

                  return __acolor(255, 160, 160, 160);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return __acolor(255, 110, 110, 110);

               }
               else
               {

                  return __acolor(255, 200, 200, 200);

               }

            }

         }
         else
         {

            if (estate & ::user::e_state_selected)
            {

               if (is_dark_mode())
               {

                  return __acolor(255, 130, 130, 130);

               }
               else
               {

                  return __acolor(255, 180, 180, 180);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return __acolor(255, 80, 80, 80);

               }
               else
               {

                  return __acolor(255, 255, 255, 255);

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

               return __acolor(255, 130, 130, 130);

            }
            else
            {

               return __acolor(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return __acolor(255, 230, 230, 230);

            }
            else
            {

               return __acolor(255, 40, 40, 40);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
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

            if (is_dark_mode())
            {

               return __acolor(255, 230, 230, 230);

            }
            else
            {

               return __acolor(255, 40, 40, 40);

            }

         }

      }
      else if (eelement == ::e_element_background)
      {

         if (is_dark_mode())
         {

            if (estate & ::user::e_state_hover)
            {

               return __acolor(127, 120, 120, 120);

            }
            else
            {

               return __acolor(127, 80, 80, 80);

            }

         }
         else
         {

            if (estate & ::user::e_state_hover)
            {

               return __acolor(127, 230, 230, 230);

            }
            else
            {

               return __acolor(127, 210, 210, 210);

            }


         }

      }
      else
      {

         if (is_dark_mode())
         {

            return __acolor(255, 50, 50, 50);

         }
         else
         {

            return __acolor(255, 40, 40, 40);

         }

      }

      return ::color::color();

   }


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pscrollbar)
   {

      ::color::color colorBackground = pscrollbar->get_color(this, ::e_element_scrollbar);

      ::rectangle_i32 rectangleClient = pscrollbar->get_client_rect();

      if (colorBackground.alpha != 0)
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto psession = get_session();

         if (psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing))
         {

            colorBackground.alpha = 255;

         }

         pgraphics->fill_rectangle(rectangleClient, colorBackground);

      }

      ::rectangle_i32 rectangleTrack;

      pscrollbar->GetTrackRect(rectangleTrack, pgraphics);

      ::rectangle_i32 rectangleWindow;

      pscrollbar->get_window_rect(rectangleWindow);

      ::color::color colorBorder = pscrollbar->scrollbar_border_color(this, ::e_element_scrollbar_trackbar);

      auto pbar = pscrollbar->cast < ::simple_scroll_bar >();

      auto ppenDraw = __create < ::draw2d::pen >();

      ppenDraw->create_solid(1, colorBorder);

      ::color::color colorTrack = pscrollbar->scrollbar_color(this, ::e_element_scrollbar_trackbar);

      auto pbrushDraw = __create < ::draw2d::brush >();

      pbrushDraw->create_solid(colorTrack);

      pgraphics->set(ppenDraw);

      pgraphics->set(pbrushDraw);

      pgraphics->rectangle(rectangleTrack);

      if (pbar->m_bTracking || pbar->is_true("tracking_on"))
      {

         auto periodFadeIn = 490_ms;

         auto periodFadeOut = 490_ms;

         double dRate = maximum(0u, minimum(1.0, pbar->find_u32("tracking_alpha") / 255.0));

         if (pbar->m_bTracking)
         {

            if (!pbar->is_true("tracking_on"))
            {

               pbar->payload("tracking_on") = true;
               pbar->payload("tracking_start_time") = duration(e_now) + dRate * periodFadeIn;
               pbar->payload("tracking_fade_in") = true;
               pbar->payload("tracking_fade_out") = false;
               pbar->payload("tracking_simple") = __random(1, 2) == 1;

            }

         }
         else
         {

            if (!pbar->payload("tracking_fade_out"))
            {

               pbar->payload("tracking_fade_in") = false;
               pbar->payload("tracking_fade_out") = true;
               pbar->payload("tracking_start_time") = duration(e_now) + (1.0 - dRate) * periodFadeOut;

            }

         }

         ::point_i32 point1 = rectangleTrack.top_left() + pbar->m_sizeTrackOffset;

         pbar->client_to_screen(point1);

         //auto psession = get_session();

         //auto puser = psession->user();

         //auto pwindowing = puser->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         pbar->client_to_screen(point1);

         //      prop("tracking_window").cast < trw >()->point1 = point1;

         //    prop("tracking_window").cast < trw >()->point2 = pointCursor;

         byte uchAlpha;

         if (pbar->is_true("tracking_fade_in"))
         {

            auto elapsed = pbar->payload("tracking_start_time").duration().elapsed();

            if (elapsed < periodFadeIn)
            {

               uchAlpha = __byte(elapsed.integral_millisecond().m_i * 255 / periodFadeIn.m_i);

            }
            else
            {

               uchAlpha = 255;

               pbar->payload("tracking_fade_in") = false;

            }

         }
         else if (pbar->is_true("tracking_fade_out"))
         {

            auto elapsed = pbar->payload("tracking_start_time").duration().elapsed().integral_millisecond();

            if (elapsed < periodFadeOut)
            {

               uchAlpha = __byte((periodFadeOut.m_i - elapsed.m_i) * 255 / periodFadeOut.m_i);

            }
            else
            {

               uchAlpha = 0;

               pbar->payload("tracking_on") = false;

               pbar->payload("tracking_fade_out") = false;

            }

         }
         else
         {
            uchAlpha = 255;
         }

         ::rectangle_i32 rectangleMachineThumb;

         bool bSimple = pbar->is_true("tracking_simple");

         if (bSimple)
         {

            int iSize = rectangleTrack.size().get_normal(pbar->m_eorientation) * 6 / 8;

            rectangleMachineThumb.top_left() = rectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::size_i32(iSize / 2, iSize / 2);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::size_i32(iSize, iSize);

            ::rectangle_i32 rectangleIntersect;

            rectangleIntersect.intersect(rectangleMachineThumb, rectangleTrack);

            i32 iArea = (i32)(maximum(1, rectangleIntersect.area()));

            rectangleMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

         }
         else
         {

            int iSize = rectangleTrack.size().get_normal(pbar->m_eorientation);

            rectangleMachineThumb.top_left() = rectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::size_i32(iSize / 2, iSize / 2);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::size_i32(iSize, iSize);

            rectangleMachineThumb.assign_normal(rectangleTrack, pbar->m_eorientation);

            rectangleMachineThumb._007Constrain(rectangleTrack);

            rectangleMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

         }

         pbar->payload("tracking_alpha") = uchAlpha;

      }

      auto ppenGrip = __create < ::draw2d::pen >();

      ppenGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_trackbar));

      pgraphics->set(ppenGrip);

      ::point_i32 pointCenter = rectangleTrack.center();

      if (pbar->m_eorientation == e_orientation_horizontal)
      {

         pgraphics->set_current_point(pointCenter.x - 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x - 5, pointCenter.y + 5);
         pgraphics->set_current_point(pointCenter.x, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x, pointCenter.y + 5);
         pgraphics->set_current_point(pointCenter.x + 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y + 5);

      }
      else
      {

         pgraphics->set_current_point(pointCenter.x - 5, pointCenter.y - 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y - 5);
         pgraphics->set_current_point(pointCenter.x - 5, pointCenter.y);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y);
         pgraphics->set_current_point(pointCenter.x - 5, pointCenter.y + 5);
         pgraphics->line_to(pointCenter.x + 5, pointCenter.y + 5);

      }

      auto ppenArrow = __create < ::draw2d::pen >();

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(ppenArrow);

      pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(pbar->m_pbrushDraw);

      pgraphics->rectangle(pbar->m_rectangleA);

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(ppenArrow);

      pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(pbar->m_pbrushDraw);

      pgraphics->rectangle(pbar->m_rectangleB);

      ::rectangle_i32 rectangle;

      if (::is_element(pbar->m_pitemCurrent, ::e_element_scrollbar_pageA)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageA))
      {

         pbar->GetPageARect(rectangleClient, rectangleTrack, rectangle, pgraphics);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageA));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->fill_rectangle(rectangle);

      }
      else if (::is_element(pbar->m_pitemCurrent, ::e_element_scrollbar_pageB)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageB))
      {

         pbar->GetPageBRect(rectangleClient, rectangleTrack, rectangle, pgraphics);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageB));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->fill_rectangle(rectangle);

      }

      ppenArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
      ppenArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
      ppenArrow->m_elinejoin = ::draw2d::e_line_join_round;

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(ppenArrow);

      pgraphics->polyline(pbar->m_pointaA, 3);

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(ppenArrow);

      pgraphics->polyline(pbar->m_pointaB, 3);

      return true;

   }


} // namespace experience



