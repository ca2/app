#include "framework.h"
#include "style.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "acme/prototype/mathematics/_random.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/user/user/content.h"
#include "apex/platform/savings.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/user/user/frame_interaction.h"
#include "base/user/simple/scroll_bar.h"
#include "base/user/user/tab.h"
#include "base/user/user/tab_data.h"
#include "base/user/user/tab_pane.h"
#include "base/platform/session.h"


// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The int_size is the int_size of the alien!!
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


   void style::on_initialize_particle()
   {

      ::base::style::on_initialize_particle();

      if (::is_null(m_pfont))
      {

         __øconstruct(m_pfont);

         //auto pnode = node();

         m_pfont->create_font(e_font_sans_ui, 12_pt, e_font_weight_normal);

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

      ::int_rectangle rectangle;
      ::int_rectangle rectangleBorder;
      ::int_rectangle rectangleText;
      ::int_rectangle rectangleX;
      ::int_rectangle rectangleIcon;
      ::int_rectangle rectangleClose;

      //return true;
      
      ::draw2d::save_context savecontext(pgraphics);
      
//      if (pdata->m_bVertical)
//      {
//         
//         pgraphics->offset_origin(0., -ptab->m_iVerticalDragScroll);
//         
//      }
//      else
//      {
//         
//         pgraphics->offset_origin(-ptab->m_iHorizontalDragScroll, 0.);
//         
//      }

      auto pdata = ptab->get_data();

      pdata->m_ppen->create_solid(1, rgb(32, 32, 32));

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::collection::index iTab = -1;

      ::int_rectangle rcClient;

      rcClient = ptab->rectangle(::user::e_layout_sketch);
      
      if(rcClient.is_empty())
      {
         
         informationf("style::_001TabOnDrawSchema01 Tab Client Rect is empty\n");
         
         return true;
         
      }
      
      //informationf("style::_001TabOnDrawSchema01\n");

      auto pstyle = ptab->get_style(pgraphics);

      ::draw2d::brush_pointer pbrushText;

      static int iCurrentTab = -1;

      int iTabWidth = 0;

      int iTabHeight = 0;

      auto & holdeeTab = pdata->m_holdee;

      auto & groupTabTheme = holdeeTab.m_map[::draw2d::e_change_theme][0];

      for (int iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
      {

         auto ppane = pdata->m_tabpanea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

         auto & groupPaneLayout = ppane->m_holdee.m_map[::draw2d::e_change_layout][0];

         ::user::e_state estate = ::user::e_state_none;

         if (pdata->m_idaSel.contains(ppane->id()))
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

         if (rectangleBorder.right() > iTabWidth)
         {

            iTabWidth = rectangleBorder.right();

         }

         if (rectangleBorder.bottom() > iTabHeight)
         {

            iTabHeight = rectangleBorder.bottom();

         }

         if (!ptab->get_element_rectangle(iTab, rectangleX, ::e_element_client))
            continue;

         bool bTextRect = ptab->get_element_rectangle(iTab, rectangleText, ::e_element_text);

         if (pdata->m_bVertical)
         {

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            auto ppath = __øcreate < ::draw2d::path >();

            if (pdata->m_idaSel.contains(ppane->id()))
            {

               ppath->begin_figure();

               ppath->add_line(rectangleBorder.right(), rectangleBorder.bottom(), rectangleBorder.left() + 1, rectangleBorder.bottom());

               ppath->add_line(rectangleBorder.left(), rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));

               ppath->add_line(rectangleX.left(), rectangleBorder.top());

               ppath->add_line(rectangleBorder.right(), rectangleBorder.top());

               ppath->close_figure();

               ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

               pgraphics->set(ppane->m_pbrushFillSel);

               pgraphics->fill(ppath);

               {

                  auto & ppen = groupTabTheme.m_pena[__e_selected];

                  if (!ppen)
                  {

                     __øconstruct(ppen);

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

               ppath->add_line(rectangleBorder.right(), rectangleBorder.bottom(), rectangleBorder.left() + 1, rectangleBorder.bottom());
               ppath->add_line(rectangleBorder.left(), rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
               ppath->add_line(bTextRect ? rectangleText.left() : rectangleBorder.left(), rectangleBorder.top());
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

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_hover];

                     if (!ppen)
                     {

                        __øconstruct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pgraphics->set(ppen);

                     pgraphics->draw(ppath);

                  }

                  pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  {

                     auto& pbrush = groupTabTheme.m_brusha[__e_hover];

                     if (!pbrush)
                     {

                        __defer_construct(pbrush);

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover);

                        pbrush->create_solid(colorText);

                     }

                     pbrushText = pbrush;

                  }

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

                        __øconstruct(ppen);

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

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

            bool bPaneSelected = pdata->m_idaSel.contains(ppane->id());

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

                  __øconstruct(ppath);

                  ppath->m_pointUserOffset = ptab->m_pointBarDragScroll;

                  ppath->add_line(rectangleBorder.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleBorder.top());

                  ppath->add_line(rectangleX.right(), rectangleBorder.top());

                  ppath->add_line(rectangleBorder.right(), rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

                  ppath->add_line(rectangleBorder.right() - 1, rectangleX.bottom());

               }

               {

                  auto & pbrush = groupPaneLayout.m_brusha[__e_selected];

                  if (!pbrush)
                  {

                     __øconstruct(pbrush);

                     pbrush->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 235, 235, 230), argb(250, 255, 255, 250));

                  }

                  pgraphics->set(pbrush);

                  auto offset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                  pgraphics->x_offset(offset);

                  pgraphics->fill(ppath);

                  pgraphics->x_offset(-offset);

               }

               {

                  auto & ppen = groupTabTheme.m_pena[__e_hover];

                  if (!ppen)
                  {

                     __øconstruct(ppen);

                     ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                  }

                  pgraphics->set(ppen);

                  auto offset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                  pgraphics->x_offset(offset);

                  pgraphics->draw(ppath);

                  pgraphics->x_offset(-offset);

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

                  __øconstruct(ppath);

                  ppath->m_pointUserOffset = ptab->m_pointBarDragScroll;

                  ppath->add_line(rectangleBorder.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleBorder.top());

                  ppath->add_line(rectangleX.right(), rectangleBorder.top());

                  ppath->add_line(rectangleBorder.right(), rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

                  ppath->add_line(rectangleBorder.right() - 1, rectangleX.bottom());

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

                        __øconstruct(pbrush);

                        pbrush->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     }

                     pgraphics->set(pbrush);

                     auto offset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                     pgraphics->x_offset(offset);

                     pgraphics->fill(ppath);

                     pgraphics->x_offset(-offset);

                  }

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_hover];

                     if (!ppen)
                     {

                        __øconstruct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pgraphics->set(ppen);

                     auto xoffset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                     pgraphics->x_offset(xoffset);

                     pgraphics->draw(ppath);

                     pgraphics->x_offset(-xoffset);

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

                        __øconstruct(pbrush);

                        pbrush->CreateLinearGradientBrush(
                           rectangleBorder.top_left(),
                           rectangleBorder.bottom_left(),
                           argb(230, 175, 175, 170),
                           argb(250, 195, 195, 190)); //*/

                     }

                     // pbrushFill->create_solid(::color::color::white);

                     pgraphics->set(pbrush);

                     auto xoffset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                     pgraphics->x_offset(xoffset);

                     pgraphics->fill(ppath);

                     pgraphics->x_offset(-xoffset);

                  }

                  {

                     auto & ppen = groupTabTheme.m_pena[__e_none];

                     if (!ppen)
                     {

                        __øconstruct(ppen);

                        ppen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     }

                     pgraphics->set(ppen);

                     auto xoffset = ptab->m_pointBarDragScroll.x() - ppath->m_pointUserOffset.x();

                     pgraphics->x_offset(xoffset);

                     pgraphics->draw(ppath);

                     pgraphics->x_offset(-xoffset);

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

         if (ptab->get_element_rectangle(iTab, rectangleClose, ::e_element_close_tab_button))
         {

            pgraphics->set_font(ptab, ::e_element_close_tab_button);

            if (::is_item(ptab->m_pitemHover, iTab)
               && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button))
            {

               pbrushText = pdata->m_pbrushCloseHover;

            }
            else
            {

               pbrushText = pdata->m_pbrushClose;

            }

            pgraphics->set(pbrushText);

            pgraphics->draw_text("x", rectangleClose, e_align_center);

         }

      }

      ::int_rectangle rectangleScroll;

      bool bScroll = ptab->_001HasBarXDragScrolling();

      if (bScroll)
      {

         if (ptab->get_element_rectangle(-1, rectangleScroll, ::e_element_tab_near_scroll))
         {

            if (is_dark_mode())
            {
               
               pgraphics->fill_rectangle(rectangleScroll, argb(127, 255, 255, 255));
               
            }
            else
            {
               
               if(ptab->m_pdata->m_bVertical)
               {
                  
                  pgraphics->fill_rectangle(rectangleScroll, argb(127, 0, 0, 0));
                  
               }
               else
               {
                
                  
                  auto ppath = __øcreate < ::draw2d::path >();
                  
                  ppath->begin_figure();
                  
                  ppath->set_current_point(rectangleScroll.top_left());
                  
                  ppath->add_line(rectangleScroll.bottom_left());
                  
                  ppath->add_line({rectangleScroll.right(), rectangleScroll.center().y()});
                  
                  ppath->close_figure();
                  
                  auto pbrush = __øcreate < ::draw2d::brush >();
                  
                  pbrush->create_solid( argb(127, 0, 0, 0));
                  
                  pgraphics->fill(ppath, pbrush);
                  
               }

            }

         }

         if (ptab->get_element_rectangle(-1, rectangleScroll, ::e_element_tab_far_scroll))
         {

            if (is_dark_mode())
            {
               
               pgraphics->fill_rectangle(rectangleScroll, argb(127, 255, 255, 255));
               
            }
            else
            {
               
               if(ptab->m_pdata->m_bVertical)
               {
                  
                  pgraphics->fill_rectangle(rectangleScroll, argb(127, 0, 0, 0));
                  
               }
               else
               {
                  
                  auto ppath = __øcreate < ::draw2d::path >();
                  
                  ppath->begin_figure();
                  
                  ppath->set_current_point(rectangleScroll.top_right());
                  
                  ppath->add_line(rectangleScroll.bottom_right());
                  
                  ppath->add_line({rectangleScroll.left(), rectangleScroll.center().y()});
                  
                  ppath->close_figure();
                  
                  auto pbrush = __øcreate < ::draw2d::brush >();
                  
                  pbrush->create_solid( argb(127, 0, 0, 0));
                  
                  pgraphics->fill(ppath, pbrush);
                  
               }

            }

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
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

         ::int_rectangle rectangleText(rectangle);

         ::write_text::font_pointer pfont;

         pfont = pgraphics->get_current_font();

         auto pdata = ptab->get_data();

         int_size sSep = pdata->m_sizeSep;

         ::int_rectangle rectangleEmp;

         for (::collection::index i = 0; i < straTitle.get_size(); i++)
         {

            string str = straTitle[i];

            int_size s = pane.m_sizeaText[i];

            rectangleText.right() = rectangleText.left() + s.cx();

            pgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

            rectangleText.left() += s.cx();

            if (i < straTitle.get_upper_bound())
            {

               rectangleText.right() = rectangleText.left() + sSep.cx();

               rectangleEmp = rectangleText;

               rectangleEmp.deflate(1, 1);

               ::draw2d::enum_alpha_mode emode = pgraphics->alpha_mode();

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               status < ::color::color > colorText;

               if (::is_item(ptab->m_pitemHover, (::collection::index) ::e_element_split + i))
               {

                  pgraphics->fill_rectangle(rectangleEmp, argb(128, 150, 190, 255));

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

               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);

               rectangleText.left() += sSep.cx();

            }

         }

      }

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab)
   {

      auto pdata = ptab->get_data();

      if (!pdata->m_bCreated)
      {

         return false;

      }

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

      // ptab->defer_handle_auto_hide_tabs(false);

      pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

      ptab->m_pgraphicsextension->get_text_extent(pgraphics, MAGIC_PALACE_TAB_SIZE, pdata->m_sizeSep);

      if (pdata->m_bVertical)
      {
         int iTabWidth = 16;
         int iTabHeight = 8;
         int cx;
         int cy;
         for (int iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
               continue;

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pgraphics);

            ::double_size size;

            ptab->m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {

               size.cx() += ppane->m_pimage->width() + 2;

               size.cy() = maximum(size.cy(), ppane->m_pimage->height());

            }

            cx = (int) (size.cx() + 2);

            if (!ppane->m_bPermanent)
            {
               
               cx += 2 + 16 + 2;

            }

            if (cx > iTabWidth)
            {
               
               iTabWidth = cx;

            }

            cy = (int) ( size.cy() + 2);

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

         iTabWidth += pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right() +
            pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right() +
            pdata->m_rectangleTextMargin.left() + pdata->m_rectangleTextMargin.right();

         pdata->m_iTabWidth = iTabWidth;

         iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
            pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom() +
            pdata->m_rectangleTextMargin.top() + pdata->m_rectangleTextMargin.bottom();

         pdata->m_iTabHeight = iTabHeight;

         ::int_rectangle rectangleX = ptab->rectangle(::user::e_layout_sketch);

         pdata->m_rectangleTab.left() = rectangleX.left();
         pdata->m_rectangleTab.top() = rectangleX.top();
         pdata->m_rectangleTab.right() = pdata->m_rectangleTab.left() + pdata->m_iTabWidth;
         pdata->m_rectangleTab.bottom() = rectangleX.bottom();

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         pdata->m_rectangleHosting.left() = ptab->m_bEffectiveVisibleControl ? pdata->m_rectangleTab.right() : rectangleX.left();
         pdata->m_rectangleHosting.top() = pdata->m_rectangleTab.top();
         pdata->m_rectangleHosting.right() = rectangleX.right();
         pdata->m_rectangleHosting.bottom() = pdata->m_rectangleTab.bottom();

      }
      else
      {

         int iTabHeight = 16;

         int cy;

         pgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::int_rectangle rectangleX = ptab->rectangle(::user::e_layout_sketch);
         //ptab->rectangle(rectangleX);
         int x = rectangleX.left();

         int ixAdd;
         for (int iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return false;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pgraphics);

            double_size size;

            ptab->m_pgraphicsextension->get_text_extent(pgraphics, str, size);

            if (ppane->m_pimage.ok())
            {

               size.cy() = maximum(size.cy(), ppane->m_pimage->size().cy());

            }

            cy = (int)(size.cy() + 2);

            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            ppane->m_point.x() = x;
            ppane->m_point.y() = rectangleX.top();


            //            string str = ppane->get_title();

            //            int_size size;

            ixAdd = 5;

            if (ppane->m_pimage.ok())
            {
               //::image::image_list::info ii;
               ixAdd += ppane->m_pimage->width() + 2;
            }

            if (!ppane->m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            ppane->m_size.cx() = (int) (size.cx() + ixAdd
               + pdata->m_rectangleBorder.left() + pdata->m_rectangleBorder.right()
               + pdata->m_rectangleMargin.left() + pdata->m_rectangleMargin.right()
               + pdata->m_rectangleTextMargin.left() + pdata->m_rectangleTextMargin.right());

            x += ppane->m_size.cx();
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += pdata->m_rectangleBorder.top() + pdata->m_rectangleBorder.bottom() +
            pdata->m_rectangleMargin.top() + pdata->m_rectangleMargin.bottom() + pdata->m_iHeightAddUp;

         pdata->m_iTabHeight = iTabHeight;

         for (int iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            ppane->m_size.cy() = iTabHeight;

         }




         pdata->m_rectangleTab.left() = rectangleX.left();
         pdata->m_rectangleTab.top() = rectangleX.top();
         pdata->m_rectangleTab.right() = rectangleX.right();
         pdata->m_rectangleTab.bottom() = pdata->m_rectangleTab.top() + pdata->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         int_rectangle & rectangleHosting = pdata->m_rectangleHosting;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
         //bool bTabbedClient = ptab->m_bShowTabs;

         rectangleHosting.left() = pdata->m_rectangleTab.left();
         rectangleHosting.top() = ptab->m_bEffectiveVisibleControl ? pdata->m_rectangleTab.bottom() : rectangleX.top();
         rectangleHosting.right() = pdata->m_rectangleTab.right();
         rectangleHosting.bottom() = rectangleX.bottom();

         //ptab->m_rectangleHosting = rectangleHosting;

         //information() << "rectangleHosting";

      }

      for (int iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
      {

         if (iPane != ptab->get_current_tab_id())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->get_current_tab_index(), ptab->is_this_visible());

      ::int_rectangle rcClient;

      rcClient = ptab->rectangle(::user::e_layout_sketch);

      if (pdata->m_bVertical)
      {

         ptab->m_iTabSize = (int)(pdata->m_tabpanea.get_count() * pdata->m_iTabHeight);

//         ptab->m_pointDragScrollMax.y() = ptab->m_sizeDragScroll.cy() - rcClient.height();

         ptab->m_sizeBarDragScroll.cy() = (int)ptab->m_pdata->m_tabpanea.get_count() * ptab->m_pdata->m_iTabHeight;

      }
      else
      {

         ptab->m_iTabSize = pdata->m_tabpanea.last()->m_point.x() +
            pdata->m_tabpanea.last()->m_size.cx();

         //ptab->m_pointDragScrollMax.x() = ptab->m_sizeDragScroll.cx() - rcClient.width();

         ptab->m_sizeBarDragScroll.cx() = ptab->m_pdata->m_tabpanea.last()->m_point.x() +
            ptab->m_pdata->m_tabpanea.last()->m_size.cx();

         //if (m_pdata->m_bVertical)
         //{


         //}
         //else
         //{


         //}
      }

      return true;

   }


   ::color::color style::get_color(::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate)
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

                  return argb(127, 0, 0, 0);

               }
               else
               {

                  return argb(0, 0, 0, 0);

               }

            }
            else if (eelement == ::e_element_item_text)
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
         else if (econtroltype == ::user::e_control_type_tab)
         {

            if (eelement == ::e_element_item_text)
            {

               if (estate & ::user::e_state_hover)
               {

                  return argb(255, 120, 150, 200);

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

               return argb(0, 0, 0, 0);

            }

         }

      }

      if (eelement == ::e_element_check)
      {

         //if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
            {

               return argb(255, 255, 255, 255);

            }
            else
            {

               return argb(255, 0, 0, 0);

            }

         }

      }
      else if (eelement == ::e_element_border)
      {

         if (estate & ::user::e_state_hover)
         {

            if (is_dark_mode())
            {

               return argb(255, 255, 255, 255);

            }
            else
            {

               return argb(255, 0, 0, 0);

            }

         }
         else if (estate & ::user::e_state_selected)
         {

            if (is_dark_mode())
            {

               return argb(255, 255, 255, 255);

            }
            else
            {

               return argb(255, 0, 0, 0);

            }

         }
         else
         {

            if (is_dark_mode())
            {

               return argb(255, 210, 210, 200);

            }
            else
            {

               return argb(255, 90, 90, 80);

            }

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

      return ::color::color();

   }


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pscrollbar)
   {

      ::color::color colorBackground = pscrollbar->get_color(this, ::e_element_scrollbar);

      ::int_rectangle rectangleX = pscrollbar->rectangle();

      if (colorBackground.m_uchOpacity != 0)
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         

         if (session()->savings()->is_trying_to_save(::e_resource_processing))
         {

            colorBackground.m_uchOpacity = 255;

         }

         pgraphics->fill_rectangle(rectangleX, colorBackground);

      }

      auto statusrectangleTrack = pscrollbar->get_track_rectangle(::user::e_layout_design);

      //::int_rectangle rectangleWindow;

      //pscrollbar->window_rectangle(rectangleWindow);

      ::color::color colorBorder = pscrollbar->scrollbar_border_color(this, ::e_element_scrollbar_trackbar);

      ::pointer < ::simple_scroll_bar > pbar = pscrollbar;

      auto ppenDraw = __øcreate < ::draw2d::pen >();

      ppenDraw->create_solid(1, colorBorder);

      ::color::color colorTrack = pscrollbar->scrollbar_color(this, ::e_element_scrollbar_trackbar);

      auto pbrushDraw = __øcreate < ::draw2d::brush >();

      pbrushDraw->create_solid(colorTrack);

      pgraphics->set(ppenDraw);

      pgraphics->set(pbrushDraw);

      pgraphics->rectangle(statusrectangleTrack);

      if (pbar->m_bTracking || pbar->is_true("tracking_on"))
      {

         auto periodFadeIn = 490_ms;

         auto periodFadeOut = 490_ms;

         double dRate = maximum(0u, minimum(1.0, pbar->get_unsigned_int("tracking_alpha") / 255.0));

         if (pbar->m_bTracking)
         {

            if (!pbar->is_true("tracking_on"))
            {

               pbar->payload("tracking_on") = true;
               pbar->payload("tracking_start_time") = (class ::time)now_t{} + dRate * periodFadeIn;
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
               pbar->payload("tracking_start_time") = (class ::time)now_t{} + (1.0 - dRate) * periodFadeOut;

            }

         }

         //::int_point point1 = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset;

         //pbar->client_to_screen()(point1);

         //

         //auto puser = user();

         //auto pwindowing = system()->windowing();

         //auto point = pwindowing->get_cursor_position();

         //pbar->client_to_screen()(point1);

         //      prop("tracking_window").cast < trw >()->point1 = point1;

         //    prop("tracking_window").cast < trw >()->point2 = point;

         unsigned char uchAlpha;

         if (pbar->is_true("tracking_fade_in"))
         {

            auto elapsed = pbar->payload("tracking_start_time").as_time().elapsed();

            if (elapsed < periodFadeIn)
            {

               uchAlpha = as_byte(255 * (elapsed / periodFadeIn));

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

               uchAlpha = as_byte(255 * ((periodFadeOut - elapsed) / periodFadeOut));

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

            auto dSize = statusrectangleTrack.size().get_normal_dimension(pbar->m_eorientation) * 6 / 8;

            rectangleMachineThumb.top_left() = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::double_size(dSize / 2.0, dSize / 2.0);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::double_size(dSize, dSize);

            ::int_rectangle rectangleIntersect;

            rectangleIntersect.intersect(rectangleMachineThumb, statusrectangleTrack);

            int iArea = (int)(maximum(1, rectangleIntersect.area()));

            rectangleMachineThumb.inflate(1 + dSize * (dSize * dSize) * 4 / (iArea * 5), 1 + dSize * (dSize * dSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pgraphics, rectangleMachineThumb, statusrectangleTrack, uchAlpha);

         }
         else
         {

            auto dSize = statusrectangleTrack.size().get_normal_dimension(pbar->m_eorientation);

            rectangleMachineThumb.top_left() = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::double_size(dSize / 2., dSize / 2.);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::double_size(dSize, dSize);

            rectangleMachineThumb.assign_normal(statusrectangleTrack, pbar->m_eorientation);

            rectangleMachineThumb._007Constrain(statusrectangleTrack);

            rectangleMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pgraphics, rectangleMachineThumb, statusrectangleTrack, uchAlpha);

         }

         pbar->payload("tracking_alpha") = uchAlpha;

      }

      auto ppenGrip = __øcreate < ::draw2d::pen >();

      ppenGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_trackbar));

      pgraphics->set(ppenGrip);

      ::int_point pointCenter = statusrectangleTrack.center();

      if (pbar->m_eorientation == e_orientation_horizontal)
      {

         pgraphics->line(pointCenter.x() - 5, pointCenter.y() - 5,
                     pointCenter.x() - 5, pointCenter.y() + 5);
         pgraphics->line(pointCenter.x(), pointCenter.y() - 5,
             pointCenter.x(), pointCenter.y() + 5);
         pgraphics->line(pointCenter.x() + 5, pointCenter.y() - 5,
         pointCenter.x() + 5, pointCenter.y() + 5);

      }
      else
      {

         pgraphics->line(pointCenter.x() - 5, pointCenter.y() - 5,
         pointCenter.x() + 5, pointCenter.y() - 5);
         pgraphics->line(pointCenter.x() - 5, pointCenter.y(),
         pointCenter.x() + 5, pointCenter.y());
         pgraphics->line(pointCenter.x() - 5, pointCenter.y() + 5,
         pointCenter.x() + 5, pointCenter.y() + 5);

      }

      {

         auto rectangleA = pbar->get_buttonA_rectangle(rectangleX);

         auto ppenArrow = __øcreate < ::draw2d::pen >();

         ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

         pgraphics->set(ppenArrow);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectA));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->rectangle(rectangleA);

      }

      {

         auto rectangleB = pbar->get_buttonB_rectangle(rectangleX);

         auto ppenArrow = __øcreate < ::draw2d::pen >();

         ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

         pgraphics->set(ppenArrow);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectB));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->rectangle(rectangleB);

      }

      if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageA)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageA))
      {

         auto statusrectanglePageA = pbar->get_pageA_rectangle(rectangleX, statusrectangleTrack);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageA));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->fill_rectangle(statusrectanglePageA);

      }
      else if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageB)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageB))
      {

         auto statusrectanglePageB = pbar->get_pageB_rectangle(rectangleX, statusrectangleTrack);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageB));

         pgraphics->set(pbar->m_pbrushDraw);

         pgraphics->fill_rectangle(statusrectanglePageB);

      }

      {

         auto ppenArrow = __øcreate < ::draw2d::pen >();

         ppenArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
         ppenArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
         ppenArrow->m_elinejoin = ::draw2d::e_line_join_round;

         {

            auto pointaA = pbar->get_arrowA(rectangleX);

            ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

            pgraphics->set(ppenArrow);

            pgraphics->polyline(pointaA);

         }

         {

            auto pointaB = pbar->get_arrowB(rectangleX);

            ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

            pgraphics->set(ppenArrow);

            pgraphics->polyline(pointaB);

         }

      }

      return true;

   }


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pinteraction)
   {

      ::draw2d::save_context savecontext(pgraphics);

      pgraphics->m_pdraw2dhost = pinteraction;

      if (pinteraction->is_top_level())
      {

         //      if (!pframe->is_custom_draw() && pgraphics != nullptr && pgraphics->m_pnext == nullptr)
         //      {
         //
         //         pframe->set_context_org(pgraphics);
         //
         //      }

         ::int_rectangle rectangleX;

         rectangleX = pinteraction->rectangle();

         auto pstyle = pinteraction->get_style(pgraphics);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         ::string strType =  ::type(pinteraction).name();


         if (strType.case_insensitive_contains("menu"))
         {

            printf_line("menu");

         }

         status < ::color::color > crBackground = pinteraction->get_color(pstyle, ::e_element_background);

         //crBackground = argb(255, 200, 180, 180);

         // xxx xxx xxx
         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         pgraphics->fill_rectangle(rectangleX, crBackground);

      }

      return true;

   }


} // namespace experience



