#include "framework.h"
#include "style.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "apex/platform/savings.h"
#include "acme/prototype/mathematics/_random.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/user/user/content.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/write_text/font.h"
#include "base/platform/session.h"
#include "base/user/simple/scroll_bar.h"
#include "base/user/user/tab.h"
#include "base/user/user/tab_data.h"
#include "base/user/user/tab_pane.h"



// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The int_size is the int_size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace experience_nanoui
{

   style::style()
   {

   }


   style::~style()
   {


   }


   void style::on_initialize_particle()
   {

      ::base::style::on_initialize_particle();

      if (::is_null(m_pfont))
      {

         __øconstruct(m_pfont);

         m_pfont->create_font(e_font_sans_ui, 12_pt, e_font_weight_normal);

      }

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::int_rectangle rectangle;
      ::int_rectangle rectangleBorder;
      ::int_rectangle rectangleText;
      ::int_rectangle rectangleX;
      ::int_rectangle rectangleIcon;
      ::int_rectangle rectangleClose;

      //return true;

      ptab->get_data()->m_ppen->create_solid(1,rgb(32,32,32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::collection::index iTab = -1;

      ::int_rectangle rcClient;

      rcClient = ptab->rectangle();

      auto pstyle = ptab->get_style(pgraphics);

      auto pbrushText = __øcreate < ::draw2d::brush > ();

      auto ppenBorder = __øcreate < ::draw2d::pen > ();

      static int iCurrentTab = -1;

      int iTabWidth = 0;

      int iTabHeight = 0;

      for(int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
      {
            
         auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

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

         if (!ptab->get_element_rectangle(iTab, rectangle, ::e_element_tab))
         {

            continue;

         }

         if (!ptab->get_element_rectangle(iTab, rectangleBorder, ::e_element_border))
         {

            continue;

         }

         if(rectangleBorder.right() > iTabWidth)
         {

            iTabWidth = rectangleBorder.right();

         }

         if(rectangleBorder.bottom() > iTabHeight)
         {

            iTabHeight = rectangleBorder.bottom();

         }

         if(!ptab->get_element_rectangle(iTab,rectangleX, ::e_element_client))
            continue;

         bool bTextRect = ptab->get_element_rectangle(iTab, rectangleText, ::e_element_text);

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rectangle(iTab,rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __øcreate < ::draw2d::path > ();

            if(ptab->get_data()->m_idaSel.contains(ppane->m_atom))
            {

               ppath->begin_figure();

               ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom(),rectangleBorder.left() + 1,rectangleBorder.bottom());

               ppath->add_line(rectangleBorder.left(),rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));

               ppath->add_line(rectangleX.left(),rectangleBorder.top());

               ppath->add_line(rectangleBorder.right(),rectangleBorder.top());

               ppath->close_figure();

               ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

               pgraphics->set(ppane->m_pbrushFillSel);

               pgraphics->fill(ppath);

               ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

               pgraphics->set(ppenBorder);

               pgraphics->draw(ppath);

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

               pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

            }
            else
            {

               ppath->begin_figure();

               ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom(),rectangleBorder.left() + 1,rectangleBorder.bottom());
               ppath->add_line(rectangleBorder.left(),rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
               ppath->add_line(bTextRect ? rectangleText.left() : rectangleBorder.left(),rectangleBorder.top());
               ppath->add_line(rectangleBorder.right(),rectangleBorder.top());
               ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom());

               ppath->close_figure();

               if(::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                  pgraphics->set(ppane->m_pbrushFillHover);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                  pgraphics->set(ppane->m_pbrushFill);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set_font(ptab, ::e_element_none);

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text));

               }

            }

         }
         else
         {

            if(ptab->get_element_rectangle(iTab,rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __øcreate < ::draw2d::path >();

            if(ptab->get_data()->m_idaSel.contains(ppane->m_atom))
            {

               if (iPane != iCurrentTab)
               {

                  iCurrentTab = iPane;

               }

               ppath->add_line(rectangleBorder.left(),rectangleX.bottom(),rectangleBorder.left(),rectangleBorder.top());

               ppath->add_line(rectangleX.right(),rectangleBorder.top());

               ppath->add_line(rectangleBorder.right(),rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

               ppath->add_line(rectangleBorder.right() - 1,rectangleX.bottom());

               ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

               pgraphics->set(ppane->m_pbrushFillSel);

               pgraphics->fill(ppath);

               ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

               pgraphics->set(ppenBorder);

               pgraphics->draw(ppath);

               if (::is_item(ptab->m_pitemHover, iTab)
                  && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected | ::user::e_state_hover);

               }
               else
               {

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

               }

               pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected));

            }
            else
            {

               ppath->add_line(rectangleBorder.left(),rectangleX.bottom(),rectangleBorder.left(),rectangleBorder.top());

               ppath->add_line(rectangleX.right(),rectangleBorder.top());

               ppath->add_line(rectangleBorder.right(),rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

               ppath->add_line(rectangleBorder.right() - 1,rectangleX.bottom());

               ppath->close_figure();

               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                  pgraphics->set(ppane->m_pbrushFillHover);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  auto pbrushFill = __øcreate < ::draw2d::brush >();

                  pbrushFill->CreateLinearGradientBrush(
                     rectangleBorder.top_left(),
                     rectangleBorder.bottom_left(),
                     argb(230, 175, 175, 170),
                     argb(250, 195, 195, 190)); //*/

                     // pbrushFill->create_solid(::color::color::white);

                  pgraphics->set(pbrushFill);

                  pgraphics->fill(ppath);

                  ppenBorder->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                  pgraphics->set(ppenBorder);

                  pgraphics->draw(ppath);

                  pgraphics->set_font(ptab, ::e_element_none);

                  auto colorText = ptab->get_color(pstyle, ::e_element_item_text);

                  pbrushText->create_solid(colorText);

               }

            }

         }

         if(bTextRect)
         {

            _001OnTabPaneDrawTitle(*ppane,ptab,pgraphics,rectangleText, pbrushText, estate);

         }

         if(ptab->get_element_rectangle(iTab,rectangleClose, ::e_element_close_tab_button))
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

            pgraphics->draw_text("x",rectangleClose,e_align_center);

         }

      }

      ::int_rectangle rectangleScroll;

      bool bScroll = ptab->_001HasBarXDragScrolling() || ptab->_001HasBarYDragScrolling();

      if(bScroll)
      {

         if(ptab->get_element_rectangle(-1,rectangleScroll, ::e_element_tab_near_scroll))
         {

            pgraphics->fill_rectangle(rectangleScroll, argb(255, 255, 255, 255));

         }

         if(ptab->get_element_rectangle(-1,rectangleScroll, ::e_element_tab_far_scroll))
         {

            pgraphics->fill_rectangle(rectangleScroll, argb(255, 255, 255, 255));

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle,::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->set(pbrushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->_DrawText(pane.get_title(), rectangle, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::int_rectangle rectangleText(rectangle);

         ::write_text::font_pointer pfont;

         pfont = pgraphics->get_current_font();

         int_size sSep = ptab->get_data()->m_sizeSep;

         ::int_rectangle rectangleEmp;

         for(::collection::index i = 0; i < straTitle.get_size(); i++)
         {

            string str = straTitle[i];

            int_size s = pane.m_sizeaText[i];

            rectangleText.right() =rectangleText.left() + s.cx();

            pgraphics->_DrawText(str,rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

            rectangleText.left() += s.cx();

            if(i < straTitle.get_upper_bound())
            {

               rectangleText.right() = rectangleText.left() + sSep.cx();

               rectangleEmp = rectangleText;

               rectangleEmp.deflate(1, 1);

               ::draw2d::enum_alpha_mode emode = pgraphics->alpha_mode();

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               status < ::color::color > colorText;

               if(::is_item(ptab->m_pitemHover,(::collection::index) ::e_element_split + i))
               {

                  pgraphics->fill_rectangle(rectangleEmp,argb(128, 150, 190, 255));

                  colorText = ptab->get_color(this, ::e_element_item_text, ::user::e_state_hover);

               }
               else
               {

                  colorText = ptab->get_color(this, ::e_element_item_text);

               }

               auto pbrush = __øcreate < ::draw2d::brush >();

               pbrush->create_solid(colorText);

               pgraphics->set(pbrush);

               pgraphics->set_font(ptab, ::e_element_close_tab_button);

               pgraphics->set_alpha_mode(emode);

               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectangleText, e_align_center, e_draw_text_no_prefix);

               rectangleText.left() += sSep.cx();

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

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
                                 pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right() +
                                 pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right();

      }
      else
      {

         pdata->m_rectangleMargin.set(3, 2, 0, 1);

         pdata->m_rectangleBorder.set(0, 1, 11, 6);

         pdata->m_rectangleTextMargin.set(3, 0, 1, 0);

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
                                 pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right() +
                                 pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right();

      }

      //ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

      ptab->m_pgraphicsextension->get_text_extent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);

      if(ptab->get_data()->m_bVertical)
      {
         int iTabWidth = 16;
         int iTabHeight = 8;
         double cx;
         double cy;
         for(int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

            if(!ppane->m_bTabPaneVisible)
               continue;

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pgraphics);

            ::double_size size;

            ptab->m_pgraphicsextension->get_text_extent(pgraphics,str, size);

            if(ppane->m_pimage->is_set())
            {
               size.cx() += ppane->m_pimage->width() + 2;
               size.cy() = maximum(size.cy(),ppane->m_pimage->height());
            }
            cx = size.cx() + 2.0;

            if(!ppane->m_bPermanent)
            {
               cx += 2.0 +16.0 + 2.0;
            }

            if(cx > iTabWidth)
            {
               iTabWidth =(int) cx;
            }
            cy = size.cy() + 2;
            if(cy > iTabHeight)
            {
               iTabHeight =(int) cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight =(int) cy;
         }

         iTabWidth += ptab->get_data()->m_rectangleBorder.left() + ptab->get_data()->m_rectangleBorder.right() +
                        ptab->get_data()->m_rectangleMargin.left() + ptab->get_data()->m_rectangleMargin.right() +
                        ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data()->m_rectangleTextMargin.right();

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectangleBorder.top() + ptab->get_data()->m_rectangleBorder.bottom() +
                        ptab->get_data()->m_rectangleMargin.top() + ptab->get_data()->m_rectangleMargin.bottom() +
                        ptab->get_data()->m_rectangleTextMargin.top() + ptab->get_data()->m_rectangleTextMargin.bottom();

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::int_rectangle rectangleX = ptab->rectangle();

         ptab->get_data()->m_rectangleTab.left()       = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top()        = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right()      = ptab->get_data()->m_rectangleTab.left() + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectangleTab.bottom()     = rectangleX.bottom();

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         ptab->get_data()->m_rectangleHosting.left()       = ptab->m_bEffectiveVisibleControl ? ptab->get_data()->m_rectangleTab.right() : rectangleX.left();
         ptab->get_data()->m_rectangleHosting.top()        = ptab->get_data()->m_rectangleTab.top();
         ptab->get_data()->m_rectangleHosting.right()      = rectangleX.right();
         ptab->get_data()->m_rectangleHosting.bottom()     = ptab->get_data()->m_rectangleTab.bottom();

      }
      else
      {

         int iTabHeight = 16;

         int cy;

         pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::int_rectangle rectangleX = ptab->rectangle();
         //ptab->rectangle(rectangleX);
         int x = rectangleX.left();

         int ixAdd;
         for(int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
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

            if(ppane->m_pimage.ok())
            {

               size.cy() = maximum(size.cy(),ppane->m_pimage->size().cy());

            }

            cy = (int) ( size.cy() + 2.0);

            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            ppane->m_point.x() = x;
            ppane->m_point.y() = rectangleX.top();


            //            string str = ppane->get_title();

            //            int_size size;

            ixAdd = 5;

            if(ppane->m_pimage.ok())
            {
               //::image::image_list::info ii;
               ixAdd += ppane->m_pimage->width() + 2;
            }

            if(!ppane->m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            ppane->m_size.cx() = (int) ( size.cx() + ixAdd
                                 + ptab->get_data()->m_rectangleBorder.left() + ptab->get_data()->m_rectangleBorder.right()
                                 + ptab->get_data()->m_rectangleMargin.left() + ptab->get_data()->m_rectangleMargin.right()
                                 + ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data()->m_rectangleTextMargin.right());

            x += ppane->m_size.cx();
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectangleBorder.top() + ptab->get_data()->m_rectangleBorder.bottom() +
                        ptab->get_data()->m_rectangleMargin.top() + ptab->get_data()->m_rectangleMargin.bottom() + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         for(int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = ptab->get_data()->m_tabpanea[iPane].get();

            ppane->m_size.cy() = iTabHeight;

         }




         ptab->get_data()->m_rectangleTab.left()       = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top()        = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right()      = rectangleX.right();
         ptab->get_data()->m_rectangleTab.bottom()     = ptab->get_data()->m_rectangleTab.top() + ptab->get_data()->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         int_rectangle & rectangleHosting = ptab->get_data()->m_rectangleHosting;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
         bool bTabbedClient = ptab->m_bEffectiveVisibleControl;

         rectangleHosting.left() = ptab->get_data()->m_rectangleTab.left();
         rectangleHosting.top() = bTabbedClient ? ptab->get_data()->m_rectangleTab.bottom() : rectangleX.top();
         rectangleHosting.right() = ptab->get_data()->m_rectangleTab.right();
         rectangleHosting.bottom() = rectangleX.bottom();


         //TRACE0("rectangleHosting");
      }

      for(int iPane = 0; iPane < ptab->get_data()->m_tabpanea.get_size(); iPane++)
      {

         if(iPane != ptab->get_current_tab_id())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->get_current_tab_index(), ptab->is_this_visible());

      ::int_rectangle rcClient;

      rcClient = ptab->rectangle();

      if(ptab->get_data()->m_bVertical)
      {

         ptab->m_iTabSize = (int) (ptab->get_data()->m_tabpanea.get_count() * ptab->get_data()->m_iTabHeight);

         //ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.height();

      }
      else
      {

         ptab->m_iTabSize = ptab->get_data()->m_tabpanea.last()->m_point.x() +
         ptab->get_data()->m_tabpanea.last()->m_size.cx();

         //ptab->m_iTabScrollMax = ptab->m_iTabSize - rcClient.width();

      }


      return true;

   }


   ::color::color style::get_color(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate)
   {

      if (::is_set(pinteraction))
      {

         //string strType = ::type(pinteraction).name();

//            if (strType.contains("form"))
//            {
//
//               informationf("form");
//
//            }

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_form)
         {

            if (eelement == ::e_element_background)
            {

               if (is_dark_mode())
               {

                  return ::rgba(80, 80, 80, 127);

               }
               else
               {

                  return ::rgba(255, 255, 255, 127);

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

                     return ::rgba(255, 255, 255, 127);

                  }
                  else
                  {

                     return ::rgba(80, 80, 80, 127);

                  }

               }
               else if (eelement == ::e_element_text)
               {

                  if (is_dark_mode())
                  {

                     return ::rgba(80, 80, 80, 255);

                  }
                  else
                  {

                     return ::rgba(255, 255, 255, 255);

                  }

               }

            }
            else
            {

               if (eelement == ::e_element_background)
               {

                  if (is_dark_mode())
                  {

                     return ::rgba(80, 80, 80, 127);

                  }
                  else
                  {

                     return ::rgba(255, 255, 255, 127);

                  }

               }
               else if (eelement == ::e_element_text)
               {

                  if (is_dark_mode())
                  {

                     return ::rgba(255, 255, 255, 255);

                  }
                  else
                  {

                     return ::rgba(80, 80, 80, 255);

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

                  return ::rgba(127, 0, 0, 0);

               }
               else
               {

                  return ::rgba(0, 0, 0, 0);

               }

            }
            else if (eelement == ::e_element_item_text)
            {

               if (is_dark_mode())
               {

                  return ::rgba(255, 230, 230, 230);

               }
               else
               {

                  return ::rgba(255, 40, 40, 40);

               }

            }

         }
         else if (econtroltype == ::user::e_control_type_tab)
         {

            if (eelement == ::e_element_item_text)
            {

               if(estate & ::user::e_state_hover)
               {

                  return ::rgba(255, 120, 150, 200);

               }
               else
               {

                  if (is_dark_mode())
                  {

                     return ::rgba(255, 230, 230, 230);

                  }
                  else
                  {

                     return ::rgba(255, 40, 40, 40);

                  }

               }

            }
            else if (eelement == ::e_element_item_background)
            {

               return ::rgba(0, 0, 0, 0);

            }

         }

      }
         
      if (eelement == ::e_element_check)
      {

         //if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 255, 255, 255);

            }
            else
            {

               return ::rgba(255, 0, 0, 0);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 255, 255, 255);

            }
            else
            {

               return ::rgba(255, 0, 0, 0);

            }

         }
         else if (estate & ::user::e_state_selected)
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 255, 255, 255);

            }
            else
            {

               return ::rgba(255, 0, 0, 0);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 210, 210, 200);

            }
            else
            {

               return ::rgba(255, 90, 90, 80);

            }

         }

      }
      else if (eelement == ::e_element_scrollbar)
      {

         return ::rgba(100, 192, 192, 192);

      }
      else if (eelement == ::e_element_scrollbar_trackbar)
      {

         return ::rgba(160, 140, 140, 140);

      }
      else if (eelement == ::e_element_item_text)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 130, 130, 130);

            }
            else
            {

               return ::rgba(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 230, 230, 230);

            }
            else
            {

               return ::rgba(255, 40, 40, 40);

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

                  return ::rgba(255, 150, 150, 150);

               }
               else
               {

                  return ::rgba(255, 160, 160, 160);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return ::rgba(255, 110, 110, 110);

               }
               else
               {

                  return ::rgba(255, 200, 200, 200);

               }

            }

         }
         else
         {

            if (estate & ::user::e_state_selected)
            {

               if (is_dark_mode())
               {

                  return ::rgba(255, 130, 130, 130);

               }
               else
               {

                  return ::rgba(255, 180, 180, 180);

               }

            }
            else
            {

               if (is_dark_mode())
               {

                  return ::rgba(255, 80, 80, 80);

               }
               else
               {

                  return ::rgba(255, 255, 255, 255);

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

               return ::rgba(255, 130, 130, 130);

            }
            else
            {

               return ::rgba(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 230, 230, 230);

            }
            else
            {

               return ::rgba(255, 40, 40, 40);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_new_input)
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 130, 130, 130);

            }
            else
            {

               return ::rgba(255, 192, 192, 192);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return ::rgba(255, 230, 230, 230);

            }
            else
            {

               return ::rgba(255, 40, 40, 40);

            }

         }

      }
      else if (eelement == ::e_element_background)
      {

         if (is_dark_mode())
         {

            if (estate & ::user::e_state_hover)
            {

               return ::rgba(127, 120, 120, 120);

            }
            else
            {

               return ::rgba(127, 80, 80, 80);

            }

         }
         else
         {

            if (estate & ::user::e_state_hover)
            {

               return ::rgba(127, 230, 230, 230);

            }
            else
            {

               return ::rgba(127, 210, 210, 210);

            }


         }

      }
      else
      {

         if (is_dark_mode())
         {

            return ::rgba(255, 50, 50, 50);

         }
         else
         {

            return ::rgba(255, 40, 40, 40);

         }

      }

      return ::color::color();

   }


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pscrollbar)
   {

      ::color::color colorBackground = pscrollbar->get_color(this, ::e_element_scrollbar);

      ::int_rectangle rectangleX = pscrollbar->rectangle();

      if (colorBackground.has_opacity())
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         

         if (session()->savings()->is_trying_to_save(::e_resource_processing))
         {

            colorBackground.set_opaque();

         }

         pgraphics->fill_rectangle(rectangleX, colorBackground);

      }

      auto rectangleTrack = pscrollbar->get_track_rectangle(::user::e_layout_design);

      ::int_rectangle rectangleWindow;

      rectangleWindow = pscrollbar->window_rectangle();

      ::color::color colorBorder = pscrollbar->scrollbar_border_color(this, ::e_element_scrollbar_trackbar);

      ::pointer < ::simple_scroll_bar > pbar = pscrollbar;

      auto ppenDraw = __øcreate < ::draw2d::pen > ();

      ppenDraw->create_solid(1, colorBorder);

      ::color::color colorTrack = pscrollbar->scrollbar_color(this, ::e_element_scrollbar_trackbar);

      auto pbrushDraw = __øcreate < ::draw2d::brush > ();

      pbrushDraw->create_solid(colorTrack);

      pgraphics->set(ppenDraw);

      pgraphics->set(pbrushDraw);

      pgraphics->rectangle(rectangleTrack);

      if (pbar->m_bTracking || pbar->is_true("tracking_on"))
      {

         auto periodFadeIn = 490_ms;

         auto periodFadeOut = 490_ms;

         double dRate = maximum(0u, minimum(1.0, pbar->find_unsigned_int("tracking_alpha")/255.0));

         if (pbar->m_bTracking)
         {

            if (!pbar->is_true("tracking_on"))
            {

               pbar->payload("tracking_on") = true;
               pbar->payload("tracking_start_time") = ::time::now() + dRate * periodFadeIn;
               pbar->payload("tracking_fade_in") = true;
               pbar->payload("tracking_fade_out") = false;
               pbar->payload("tracking_simple") = mathematics()->random(1, 2) == 1;

            }

         }
         else
         {

            if (!pbar->payload("tracking_fade_out"))
            {

               pbar->payload("tracking_fade_in") = false;
               pbar->payload("tracking_fade_out") = true;
               pbar->payload("tracking_start_time") = ::time::now() + (1.0 - dRate) * periodFadeOut;

            }

         }

         ::int_point point1 = rectangleTrack.top_left() + pbar->m_sizeTrackOffset;

         pbar->client_to_screen()(point1);

         //

         //auto puser = user();

         //auto pwindowing = system()->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         pbar->client_to_screen()(point1);

         //      prop("tracking_window").cast < trw >()->point1 = point1;

         //    prop("tracking_window").cast < trw >()->point2 = pointCursor;

         unsigned char uchAlpha;

         if (pbar->is_true("tracking_fade_in"))
         {

            auto elapsed = pbar->payload("tracking_start_time").as_time().elapsed();

            if (elapsed < periodFadeIn)
            {

               uchAlpha = ::as_byte(elapsed * 255 / periodFadeIn);

            }
            else
            {

               uchAlpha = 255;

               pbar->payload("tracking_fade_in") = false;

            }

         }
         else if (pbar->is_true("tracking_fade_out"))
         {

            auto elapsed = pbar->payload("tracking_start_time").as_time().elapsed();

            if (elapsed < periodFadeOut)
            {

               uchAlpha = as_byte((periodFadeOut - elapsed) * 255 / periodFadeOut);

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

         ::int_rectangle rectangleMachineThumb;

         bool bSimple = pbar->is_true("tracking_simple");

         if (bSimple)
         {

            int iSize = (int) (rectangleTrack.size().get_normal_dimension(pbar->m_eorientation) * 6 / 8);

            rectangleMachineThumb.top_left() = rectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::int_size(iSize / 2, iSize / 2);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::int_size(iSize, iSize);

            ::int_rectangle rectangleIntersect;

            rectangleIntersect.intersect(rectangleMachineThumb, rectangleTrack);

            int iArea = (int)(maximum(1, rectangleIntersect.area()));

            rectangleMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

         }
         else
         {

            int iSize = (int) rectangleTrack.size().get_normal_dimension(pbar->m_eorientation);

            rectangleMachineThumb.top_left() = rectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::int_size(iSize / 2, iSize / 2);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::int_size(iSize, iSize);

            rectangleMachineThumb.assign_normal(rectangleTrack, pbar->m_eorientation);

            rectangleMachineThumb._007Constrain(rectangleTrack);

            rectangleMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pgraphics, rectangleMachineThumb, rectangleTrack, uchAlpha);

         }

         pbar->payload("tracking_alpha") = uchAlpha;

      }

      auto ppenGrip = __øcreate < ::draw2d::pen > ();

      ppenGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_trackbar));

      pgraphics->set(ppenGrip);

      ::int_point pointCenter = rectangleTrack.center();

      if (pbar->m_eorientation == e_orientation_horizontal)
      {

         pgraphics->set_current_point(pointCenter.x() - 5, pointCenter.y() - 5);
         pgraphics->line_to(pointCenter.x() - 5, pointCenter.y() + 5);
         pgraphics->set_current_point(pointCenter.x(), pointCenter.y() - 5);
         pgraphics->line_to(pointCenter.x(), pointCenter.y() + 5);
         pgraphics->set_current_point(pointCenter.x() + 5, pointCenter.y() - 5);
         pgraphics->line_to(pointCenter.x() + 5, pointCenter.y() + 5);

      }
      else
      {

         pgraphics->set_current_point(pointCenter.x() - 5, pointCenter.y() - 5);
         pgraphics->line_to(pointCenter.x() + 5, pointCenter.y() - 5);
         pgraphics->set_current_point(pointCenter.x() - 5, pointCenter.y());
         pgraphics->line_to(pointCenter.x() + 5, pointCenter.y());
         pgraphics->set_current_point(pointCenter.x() - 5, pointCenter.y() + 5);
         pgraphics->line_to(pointCenter.x() + 5, pointCenter.y() + 5);

      }

      auto ppenArrow = __øcreate < ::draw2d::pen > ();

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(ppenArrow);

      pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(pbar->m_pbrushDraw);

      auto rectangleA = pbar->get_buttonA_rectangle(rectangleX);

      pgraphics->rectangle(rectangleA);

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(ppenArrow);

      pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(pbar->m_pbrushDraw);

      auto rectangleB = pbar->get_buttonB_rectangle(rectangleX);

      pgraphics->rectangle(rectangleB);

      ::status < ::int_rectangle > rectangle;

      if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageA)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageA))
      {

         rectangle = pbar->get_pageA_rectangle(rectangleX, rectangleTrack);

         if (rectangle)
         {

            pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageA));

            pgraphics->set(pbar->m_pbrushDraw);

            pgraphics->fill_rectangle(rectangle);

         }

      }
      else if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageB)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageB))
      {

         auto rectangle = pbar->get_pageB_rectangle(rectangleX, rectangleTrack);

         if(rectangle)
         {

            pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageB));

            pgraphics->set(pbar->m_pbrushDraw);

            pgraphics->fill_rectangle(rectangle);

         }

      }

      ppenArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
      ppenArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
      ppenArrow->m_elinejoin = ::draw2d::e_line_join_round;

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

      pgraphics->set(ppenArrow);

      auto arrowA = pbar->get_arrowA(rectangleX);

      pgraphics->polyline(arrowA);

      ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

      pgraphics->set(ppenArrow);

      auto arrowB = pbar->get_arrowA(rectangleX);

      pgraphics->polyline(arrowB);

      return true;

   }


} // namespace experience_nanoui



