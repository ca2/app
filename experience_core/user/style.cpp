#include "platform.h"
#include "style.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "acme/prototype/mathematics/_random.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/user/user/content.h"
#include "apex/platform/savings.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/user/user/frame_interaction.h"
#include "berg/user/simple/scroll_bar.h"
#include "berg/user/user/tab.h"
#include "berg/user/user/tab_data.h"
#include "berg/user/user/tab_pane.h"
#include "berg/platform/session.h"


// pdraw2dgraphics->get_text_extent("->:<-"); // oh no!! omg!! The i32_size is the i32_size of the alien!!
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

      ::berg::style::on_initialize_particle();

      if (::is_null(m_pwritetextfont))
      {

         constructø(m_pwritetextfont);

         //auto pnode = node();

         m_pwritetextfont->create_font(e_font_sans_ui, 12_pt, e_font_weight_normal);

      }

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::tab * ptab)
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

      ::i32_rectangle rectangle;
      ::i32_rectangle rectangleBorder;
      ::i32_rectangle rectangleText;
      ::i32_rectangle rectangleX;
      ::i32_rectangle rectangleIcon;
      ::i32_rectangle rectangleClose;

      //return true;
      
      ::draw2d::save_context savecontext(pdraw2dgraphics);
      
//      if (pdata->m_bVertical)
//      {
//         
//         pdraw2dgraphics->offset_origin(0., -ptab->m_iVerticalDragScroll);
//         
//      }
//      else
//      {
//         
//         pdraw2dgraphics->offset_origin(-ptab->m_iHorizontalDragScroll, 0.);
//         
//      }

      auto pdata = ptab->get_data();

      pdata->m_pdraw2dpen->create_solid(1, rgb(32, 32, 32));

      pdraw2dgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::collection::index iTab = -1;

      ::i32_rectangle rcClient;

      rcClient = ptab->rectangle(::user::e_layout_sketch);
      
      if(rcClient.is_empty())
      {
         
         informationf("style::_001TabOnDrawSchema01 Tab Client Rect is empty\n");
         
         return true;
         
      }
      
      //informationf("style::_001TabOnDrawSchema01\n");

      auto pstyle = ptab->get_style(pdraw2dgraphics);

      ::draw2d::brush_pointer pbrushText;

      static ::i32 iCurrentTab = -1;

      ::i32 iTabWidth = 0;

      ::i32 iTabHeight = 0;

      auto & pholdeeTab = pdata->m_pholdee;

      defer_construct_newø(pholdeeTab);

      auto & pgroupTabTheme = pholdeeTab->m_map[::draw2d::e_change_theme][0];

      defer_construct_newø(pgroupTabTheme);

      for (::i32 iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
      {

         auto ppane = pdata->m_tabpanea[iPane].get();

         if (!ppane->m_bTabPaneVisible)
         {

            continue;

         }

         auto & pholdee = ppane->m_pholdee;

         defer_construct_newø(pholdee);

         auto & pgroupPaneLayout = pholdee->m_map[::draw2d::e_change_layout][0];

         defer_construct_newø(pgroupPaneLayout);

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

         if (rectangleBorder.right > iTabWidth)
         {

            iTabWidth = rectangleBorder.right;

         }

         if (rectangleBorder.bottom > iTabHeight)
         {

            iTabHeight = rectangleBorder.bottom;

         }

         if (!ptab->get_element_rectangle(iTab, rectangleX, ::e_element_client))
            continue;

         bool bTextRect = ptab->get_element_rectangle(iTab, rectangleText, ::e_element_text);

         bool bPaneSelected = pdata->m_idaSel.contains(ppane->id());

         auto & pdraw2dpath = pgroupPaneLayout->m_patha.element_at_grow(
            bPaneSelected ?
            __e_selected :
            __e_none);

         if (pdata->m_bVertical)
         {

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            if (bPaneSelected)
            {

               if(defer_constructø(pdraw2dpath)) {

                  pdraw2dpath->begin_figure();

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom,
                                  rectangleBorder.left + 1, rectangleBorder.bottom);

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top -
                                                          (rectangleBorder.left -
                                                           rectangleX.left));

                  pdraw2dpath->add_line(rectangleX.left, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);

                  pdraw2dpath->close_figure();

                  ppane->m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(),
                                                                    rectangleBorder.bottom_left(),
                                                                    argb(230, 235, 235, 230),
                                                                    argb(250, 255, 255, 250));

               }

               pdraw2dgraphics->set(ppane->m_pbrushFillSel);

               pdraw2dgraphics->fill(pdraw2dpath);

               {

                  auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_selected);

                  if (defer_constructø(pdraw2dpen))
                  {

                     pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_selected));

                  }

                  pdraw2dgraphics->set(pdraw2dpen);

                  pdraw2dgraphics->draw(pdraw2dpath);

               }


               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  pdraw2dgraphics->set_font(ptab, ::e_element_none, (::user::e_state_selected | ::user::e_state_hover));

               }
               else
               {

                  pdraw2dgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

               }

               {

                  auto & pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_selected);

                  if (defer_constructø(pdraw2dbrush))
                  {

                     auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected);

                     pdraw2dbrush->create_solid(colorText);

                  }

                  pbrushText = pdraw2dbrush;

               }

            }
            else
            {

               if (defer_constructø(pdraw2dpath))
               {

                  pdraw2dpath->begin_figure();

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom, rectangleBorder.left + 1,
                                  rectangleBorder.bottom);
                  pdraw2dpath->add_line(rectangleBorder.left, rectangleBorder.top - (rectangleBorder.left - rectangleX.left));
                  pdraw2dpath->add_line(bTextRect ? rectangleText.left : rectangleBorder.left, rectangleBorder.top);
                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top);
                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.bottom);

                  pdraw2dpath->close_figure();
                
               }

               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  ppane->m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                  pdraw2dgraphics->set(ppane->m_pbrushFillHover);

                  pdraw2dgraphics->fill(pdraw2dpath);

                  {

                     auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_hover);

                     if (defer_constructø(pdraw2dpen))
                     {

                        pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pdraw2dgraphics->set(pdraw2dpen);

                     pdraw2dgraphics->draw(pdraw2dpath);

                  }

                  pdraw2dgraphics->set_font(ptab, ::e_element_none, ::user::e_state_hover);

                  {

                     auto& pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_hover);

                     if (defer_constructø(pdraw2dbrush))
                     {

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover);

                        pdraw2dbrush->create_solid(colorText);

                     }

                     pbrushText = pdraw2dbrush;

                  }

                  pbrushText->create_solid(ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover));

               }
               else
               {

                  ppane->m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 175, 175, 170), argb(250, 195, 195, 190));

                  pdraw2dgraphics->set(ppane->m_pbrushFill);

                  pdraw2dgraphics->fill(pdraw2dpath);

                  {

                     auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_none);

                     if (defer_constructø(pdraw2dpen))
                     {

                        pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border));

                     }

                     pdraw2dgraphics->set(pdraw2dpen);

                     pdraw2dgraphics->draw(pdraw2dpath);

                  }

                  {

                     auto & pwritetextfont = pgroupTabTheme->m_fonta.element_at_grow(__e_none);

                     if (!pwritetextfont)
                     {

                        pwritetextfont = pstyle->get_font(ptab, e_element_none);

                     }

                     pdraw2dgraphics->set(pwritetextfont);

                  }

                  {

                     auto & pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_none);

                     if (defer_constructø(pdraw2dbrush))
                     {

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text);

                        pdraw2dbrush->create_solid(colorText);

                     }

                     pbrushText = pdraw2dbrush;

                  }

               }

            }

         }
         else
         {

            // Horizontal Tab

            if (ptab->get_element_rectangle(iTab, rectangleIcon, ::e_element_icon))
            {

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               ::image::image_source imagesource(ppane->m_pimage);

               ::image::image_drawing_options imagedrawingoptions(rectangleIcon);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pdraw2dgraphics->draw(imagedrawing);

            }

            if (bPaneSelected)
            {

               if (iPane != iCurrentTab)
               {

                  iCurrentTab = iPane;

               }

               if (defer_constructø(pdraw2dpath))
               {

                  pdraw2dpath->m_pointUserOffset = ptab->m_pointBarDragScroll;

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleX.bottom, rectangleBorder.left, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));

                  pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);

               }

               {

                  auto & pdraw2dbrush = pgroupPaneLayout->m_brusha.element_at_grow(__e_selected);

                  defer_constructø(pdraw2dbrush);

                  pdraw2dbrush->CreateLinearGradientBrush(
                     rectangleBorder.top_left(), 
                     rectangleBorder.bottom_left(), 
                     argb(230, 235, 235, 230), 
                     argb(250, 255, 255, 250));

                  pdraw2dgraphics->set(pdraw2dbrush);

                  auto offset = ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x;

                  auto targetscope = pdraw2dgraphics->target_scope();

                  targetscope += offset;

                  pdraw2dgraphics->fill(pdraw2dpath);

               }

               {

                  auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_hover);

                  if (defer_constructø(pdraw2dpen))
                  {

                     pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                  }

                  pdraw2dgraphics->set(pdraw2dpen);

                  auto offset = ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x;

                  auto targetscope = pdraw2dgraphics->target_scope();

                  targetscope += offset;

                  pdraw2dgraphics->draw(pdraw2dpath);

               }

               if (::is_item(ptab->m_pitemHover, iTab)
                  && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  auto & pwritetextfont = pgroupTabTheme->m_fonta.element_at_grow(__e_selected_hover);

                  if (!pwritetextfont)
                  {

                     pwritetextfont = pstyle->get_font(ptab, e_element_tab, ::user::e_state_selected | ::user::e_state_hover);

                  }

                  pdraw2dgraphics->set(pwritetextfont);


//                  pdraw2dgraphics->set_font(ptab, ::e_element_none,);

               }
               else
               {

                  auto & pwritetextfont = pgroupTabTheme->m_fonta.element_at_grow(__e_selected);

                  if (!pwritetextfont)
                  {

                     pwritetextfont = pstyle->get_font(ptab, e_element_tab, ::user::e_state_selected);

                  }

                  pdraw2dgraphics->set(pwritetextfont);

               }

               {

                  auto & pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_selected);

                  if (defer_constructø(pdraw2dbrush))
                  {

                     auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_selected);

                     pdraw2dbrush->create_solid(colorText);

                  }

                  pbrushText = pdraw2dbrush;

               }

            }
            else
            {

               // Normal (NOT Selected)

               if (defer_constructø(pdraw2dpath))
               {

                  pdraw2dpath->m_pointUserOffset = ptab->m_pointBarDragScroll;

                  pdraw2dpath->add_line(rectangleBorder.left, rectangleX.bottom, rectangleBorder.left, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleX.right, rectangleBorder.top);

                  pdraw2dpath->add_line(rectangleBorder.right, rectangleBorder.top + (rectangleBorder.right - rectangleX.right));

                  pdraw2dpath->add_line(rectangleBorder.right - 1, rectangleX.bottom);

                  pdraw2dpath->close_figure();

               }

               if (::is_item(ptab->m_pitemHover, iTab)
                  && !::is_element(ptab->m_pitemHover, ::e_element_close_tab_button)
                  && !::in_element_range(ptab->m_pitemHover, ::e_element_split, 100))
               {

                  {

                     auto & pdraw2dbrush = pgroupPaneLayout->m_brusha.element_at_grow(__e_hover);

                     if (defer_constructø(pdraw2dbrush))
                     {

                        pdraw2dbrush->CreateLinearGradientBrush(rectangleBorder.top_left(), rectangleBorder.bottom_left(), argb(230, 215, 215, 210), argb(250, 235, 235, 230));

                     }

                     pdraw2dgraphics->set(pdraw2dbrush);

                     auto targetscope = pdraw2dgraphics->target_scope();

                     targetscope.offset_x(ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x);

                     pdraw2dgraphics->fill(pdraw2dpath);

                  }

                  {

                     auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_hover);

                     if (defer_constructø(pdraw2dpen))
                     {

                        pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_border, ::user::e_state_hover));

                     }

                     pdraw2dgraphics->set(pdraw2dpen);

                     auto targetscope = pdraw2dgraphics->target_scope();

                     targetscope.offset_x(ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x);

                     pdraw2dgraphics->draw(pdraw2dpath);

                     {

                        auto & pwritetextfont = pgroupTabTheme->m_fonta.element_at_grow(__e_hover);

                        if (!pwritetextfont)
                        {

                           pwritetextfont = pstyle->get_font(ptab, e_element_tab, ::user::e_state_hover);

                        }

                        pdraw2dgraphics->set(pwritetextfont);

                     }

                  }

                  {

                     auto & pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_hover);

                     if (defer_constructø(pdraw2dbrush))
                     {

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text, ::user::e_state_hover);

                        pdraw2dbrush->create_solid(colorText);

                     }

                     pbrushText = pdraw2dbrush;

                  }

               }
               else
               {

                  {

                     auto & pdraw2dbrush = pgroupPaneLayout->m_brusha.element_at_grow(__e_none);

                     if (defer_constructø(pdraw2dbrush))
                     {

                        pdraw2dbrush->CreateLinearGradientBrush(
                           rectangleBorder.top_left(),
                           rectangleBorder.bottom_left(),
                           argb(230, 175, 175, 170),
                           argb(250, 195, 195, 190)); //*/

                     }

                     // pbrushFill->create_solid(::color::color::white);

                     pdraw2dgraphics->set(pdraw2dbrush);

                     auto targetscope = pdraw2dgraphics->target_scope();

                     targetscope.offset_x(ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x);

                     pdraw2dgraphics->fill(pdraw2dpath);

                  }

                  {

                     auto & pdraw2dpen = pgroupTabTheme->m_pena.element_at_grow(__e_none);

                     if (defer_constructø(pdraw2dpen))
                     {

                        pdraw2dpen->create_solid(1.0, ptab->get_color(pstyle, ::e_element_item_border));

                     }

                     pdraw2dgraphics->set(pdraw2dpen);

                     auto targetscope = pdraw2dgraphics->target_scope();

                     targetscope.offset_x(ptab->m_pointBarDragScroll.x - pdraw2dpath->m_pointUserOffset.x);

                     pdraw2dgraphics->draw(pdraw2dpath);

                  }

                  {

                     auto & pwritetextfont = pgroupTabTheme->m_fonta.element_at_grow(__e_none);

                     if (!pwritetextfont)
                     {

                        pwritetextfont = pstyle->get_font(ptab, e_element_none);

                     }

                     pdraw2dgraphics->set(pwritetextfont);

                  }

                  {

                     auto & pdraw2dbrush = pgroupTabTheme->m_brusha.element_at_grow(__e_none);

                     if (!pdraw2dbrush)
                     {

                        defer_constructø(pdraw2dbrush);

                        auto colorText = ptab->get_color(pstyle, ::e_element_item_text);

                        pdraw2dbrush->create_solid(colorText);

                     }

                     pbrushText = pdraw2dbrush;

                  }

               }

            }

         }

         if (bTextRect)
         {

            _001OnTabPaneDrawTitle(*ppane, ptab, pdraw2dgraphics, rectangleText, pbrushText, estate);

         }

         if (ptab->get_element_rectangle(iTab, rectangleClose, ::e_element_close_tab_button))
         {

            pdraw2dgraphics->set_font(ptab, ::e_element_close_tab_button);

            if (::is_item(ptab->m_pitemHover, iTab)
               && ::is_element(ptab->m_pitemHover, ::e_element_close_tab_button))
            {

               pbrushText = pdata->m_pbrushCloseHover;

            }
            else
            {

               pbrushText = pdata->m_pbrushClose;

            }

            pdraw2dgraphics->set(pbrushText);

            pdraw2dgraphics->draw_text("x", rectangleClose, e_align_center);

         }

      }

      ::i32_rectangle rectangleScroll;

      bool bScroll = ptab->_001HasBarXDragScrolling();

      if (bScroll)
      {

         if (ptab->get_element_rectangle(-1, rectangleScroll, ::e_element_tab_near_scroll))
         {

            if (is_dark_mode())
            {
               
               pdraw2dgraphics->fill_rectangle(rectangleScroll, argb(127, 255, 255, 255));
               
            }
            else
            {
               
               if(ptab->m_pdata->m_bVertical)
               {
                  
                  pdraw2dgraphics->fill_rectangle(rectangleScroll, argb(127, 0, 0, 0));
                  
               }
               else
               {
                
                  
                  auto pdraw2dpath = createø < ::draw2d::path >();
                  
                  pdraw2dpath->begin_figure();
                  
                  pdraw2dpath->set_current_point(rectangleScroll.top_left());
                  
                  pdraw2dpath->add_line(rectangleScroll.bottom_left());
                  
                  pdraw2dpath->add_line({rectangleScroll.right, rectangleScroll.center().y});
                  
                  pdraw2dpath->close_figure();
                  
                  auto pdraw2dbrush = createø < ::draw2d::brush >();
                  
                  pdraw2dbrush->create_solid( argb(127, 0, 0, 0));
                  
                  pdraw2dgraphics->fill(pdraw2dpath, pdraw2dbrush);
                  
               }

            }

         }

         if (ptab->get_element_rectangle(-1, rectangleScroll, ::e_element_tab_far_scroll))
         {

            if (is_dark_mode())
            {
               
               pdraw2dgraphics->fill_rectangle(rectangleScroll, argb(127, 255, 255, 255));
               
            }
            else
            {
               
               if(ptab->m_pdata->m_bVertical)
               {
                  
                  pdraw2dgraphics->fill_rectangle(rectangleScroll, argb(127, 0, 0, 0));
                  
               }
               else
               {
                  
                  auto pdraw2dpath = createø < ::draw2d::path >();
                  
                  pdraw2dpath->begin_figure();
                  
                  pdraw2dpath->set_current_point(rectangleScroll.top_right());
                  
                  pdraw2dpath->add_line(rectangleScroll.bottom_right());
                  
                  pdraw2dpath->add_line({rectangleScroll.left, rectangleScroll.center().y});
                  
                  pdraw2dpath->close_figure();
                  
                  auto pdraw2dbrush = createø < ::draw2d::brush >();
                  
                  pdraw2dbrush->create_solid( argb(127, 0, 0, 0));
                  
                  pdraw2dgraphics->fill(pdraw2dpath, pdraw2dbrush);
                  
               }

            }

         }

      }

      return true;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pdraw2dgraphics, const ::i32_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate)
   {

      string_array_base & straTitle = pane.m_straTitle;

      pdraw2dgraphics->set(pbrushText);

      if (straTitle.get_count() <= 1)
      {

         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         ::string strTitle = pane.get_title();

         if (strTitle == "Options")
         {

            warningf("Options");

         }

         pdraw2dgraphics->_DrawText(strTitle, rectangle, e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::i32_rectangle rectangleText(rectangle);

         ::write_text::font_pointer pwritetextfont;

         pwritetextfont = pdraw2dgraphics->get_current_font();

         auto pdata = ptab->get_data();

         i32_size sSep = pdata->m_sizeSep;

         ::i32_rectangle rectangleEmp;

         for (::collection::index i = 0; i < straTitle.get_size(); i++)
         {

            string str = straTitle[i];

            i32_size s = pane.m_sizeaText[i];

            rectangleText.right = rectangleText.left + s.cx;

            pdraw2dgraphics->_DrawText(str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

            rectangleText.left += s.cx;

            if (i < straTitle.get_upper_bound())
            {

               rectangleText.right = rectangleText.left + sSep.cx;

               rectangleEmp = rectangleText;

               rectangleEmp.deflate(1, 1);

               ::draw2d::enum_alpha_mode emode = pdraw2dgraphics->alpha_mode();

               pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               status < ::color::color > colorText;

               if (::is_item(ptab->m_pitemHover, (::collection::index) ::e_element_split + i))
               {

                  pdraw2dgraphics->fill_rectangle(rectangleEmp, argb(128, 150, 190, 255));

                  colorText = ptab->get_color(this, ::e_element_item_text, ::user::e_state_hover);

               }
               else
               {

                  colorText = ptab->get_color(this, ::e_element_item_text);

               }

               auto pdraw2dbrush = createø < ::draw2d::brush >();

               pdraw2dbrush->create_solid(colorText);

               pdraw2dgraphics->set(pdraw2dbrush);

               pdraw2dgraphics->set_font(ptab, ::e_element_close_tab_button);

               pdraw2dgraphics->set_alpha_mode(emode);

               pdraw2dgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);

               rectangleText.left += sSep.cx;

            }

         }

      }

   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::tab * ptab)
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

      // ptab->defer_handle_auto_hide_tabs(false);

      pdraw2dgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

      ptab->m_pgraphicsextension->get_text_extent(pdraw2dgraphics, MAGIC_PALACE_TAB_SIZE, pdata->m_sizeSep);

      if (pdata->m_bVertical)
      {
         ::i32 iTabWidth = 16;
         ::i32 iTabHeight = 8;
         ::i32 cx;
         ::i32 cy;
         for (::i32 iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
               continue;

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pdraw2dgraphics);

            ::f64_size size;

            ptab->m_pgraphicsextension->get_text_extent(pdraw2dgraphics, str, size);

            if (ppane->m_pimage->is_set())
            {

               size.cx += ppane->m_pimage->width() + 2;

               size.cy = maximum(size.cy, ppane->m_pimage->height());

            }

            cx = (::i32) (size.cx + 2);

            if (!ppane->m_bPermanent)
            {
               
               cx += 2 + 16 + 2;

            }

            if (cx > iTabWidth)
            {
               
               iTabWidth = cx;

            }

            cy = (::i32) ( size.cy + 2);

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

         iTabWidth += pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right +
            pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right +
            pdata->m_rectangleTextMargin.left + pdata->m_rectangleTextMargin.right;

         pdata->m_iTabWidth = iTabWidth;

         iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom +
            pdata->m_rectangleTextMargin.top + pdata->m_rectangleTextMargin.bottom;

         pdata->m_iTabHeight = iTabHeight;

         ::i32_rectangle rectangleX = ptab->rectangle(::user::e_layout_sketch);

         pdata->m_rectangleTab.left = rectangleX.left;
         pdata->m_rectangleTab.top = rectangleX.top;
         pdata->m_rectangleTab.right = pdata->m_rectangleTab.left + pdata->m_iTabWidth;
         pdata->m_rectangleTab.bottom = rectangleX.bottom;

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left,
         m_rectangleTab.top,
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         pdata->m_rectangleHosting.left = ptab->m_bEffectiveVisibleControl ? pdata->m_rectangleTab.right : rectangleX.left;
         pdata->m_rectangleHosting.top = pdata->m_rectangleTab.top;
         pdata->m_rectangleHosting.right = rectangleX.right;
         pdata->m_rectangleHosting.bottom = pdata->m_rectangleTab.bottom;

      }
      else
      {

         ::i32 iTabHeight = 16;

         ::i32 cy;

         pdraw2dgraphics->set_font(ptab, ::e_element_none, ::user::e_state_selected);

         ::i32_rectangle rectangleX = ptab->rectangle(::user::e_layout_sketch);
         //ptab->rectangle(rectangleX);
         ::i32 x = rectangleX.left;

         ::i32 ixAdd;
         for (::i32 iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            if (!ppane->m_bTabPaneVisible)
            {

               return false;

            }

            string str = ppane->get_title();

            ppane->do_split_layout(ptab->m_pgraphicsextension, pdraw2dgraphics);

            ::f64_size size;

            ptab->m_pgraphicsextension->get_text_extent(pdraw2dgraphics, str, size);

            if (ppane->m_pimage.ok())
            {

               size.cy = maximum(size.cy, ppane->m_pimage->size().cy);

            }

            cy = (::i32)(size.cy + 2);

            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            ppane->m_point.x = x;
            ppane->m_point.y = rectangleX.top;


            //            string str = ppane->get_title();

            //            i32_size size;

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




            ppane->m_size.cx = (::i32) (size.cx + ixAdd
               + pdata->m_rectangleBorder.left + pdata->m_rectangleBorder.right
               + pdata->m_rectangleMargin.left + pdata->m_rectangleMargin.right
               + pdata->m_rectangleTextMargin.left + pdata->m_rectangleTextMargin.right);

            x += ppane->m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += pdata->m_rectangleBorder.top + pdata->m_rectangleBorder.bottom +
            pdata->m_rectangleMargin.top + pdata->m_rectangleMargin.bottom + pdata->m_iHeightAddUp;

         pdata->m_iTabHeight = iTabHeight;

         for (::i32 iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
         {

            auto ppane = pdata->m_tabpanea[iPane].get();

            ppane->m_size.cy = iTabHeight;

         }




         pdata->m_rectangleTab.left = rectangleX.left;
         pdata->m_rectangleTab.top = rectangleX.top;
         pdata->m_rectangleTab.right = rectangleX.right;
         pdata->m_rectangleTab.bottom = pdata->m_rectangleTab.top + pdata->m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left,
         m_rectangleTab.top,
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         i32_rectangle & rectangleHosting = pdata->m_rectangleHosting;

         //bool bTabbedClient = ptab->m_bShowTabs && !ptab->top_level_frame()->layout().is_full_screen();
         //bool bTabbedClient = ptab->m_bShowTabs;

         rectangleHosting.left = pdata->m_rectangleTab.left;
         rectangleHosting.top = ptab->m_bEffectiveVisibleControl ? pdata->m_rectangleTab.bottom : rectangleX.top;
         rectangleHosting.right = pdata->m_rectangleTab.right;
         rectangleHosting.bottom = rectangleX.bottom;

         //ptab->m_rectangleHosting = rectangleHosting;

         //information() << "rectangleHosting";

      }

      for (::i32 iPane = 0; iPane < pdata->m_tabpanea.get_size(); iPane++)
      {

         if (iPane != ptab->get_current_tab_id())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->get_current_tab_index(), ptab->is_this_visible());

      ::i32_rectangle rcClient;

      rcClient = ptab->rectangle(::user::e_layout_sketch);

      if (pdata->m_bVertical)
      {

         ptab->m_iTabSize = (::i32)(pdata->m_tabpanea.get_count() * pdata->m_iTabHeight);

//         ptab->m_pointDragScrollMax.y = ptab->m_sizeDragScroll.cy - rcClient.height();

         ptab->m_sizeBarDragScroll.cy = (::i32)ptab->m_pdata->m_tabpanea.get_count() * ptab->m_pdata->m_iTabHeight;

      }
      else
      {

         ptab->m_iTabSize = pdata->m_tabpanea.last()->m_point.x +
            pdata->m_tabpanea.last()->m_size.cx;

         //ptab->m_pointDragScrollMax.x = ptab->m_sizeDragScroll.cx - rcClient.width();

         ptab->m_sizeBarDragScroll.cx = ptab->m_pdata->m_tabpanea.last()->m_point.x +
            ptab->m_pdata->m_tabpanea.last()->m_size.cx;

         //if (m_pdata->m_bVertical)
         //{


         //}
         //else
         //{


         //}
      }

      return true;

   }


   ::color::color style::get_color(::user::interaction * pinteraction, const ::e_element & eelement, const ::user::e_state & estate)
   {

      if (::is_set(pinteraction))
      {

         //string strType = ::platform::type(pinteraction).name();

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

            if (eelement == ::e_element_item_border)
            {
               if (is_dark_mode())
               {

                  return argb(255, 255, 255,  255);

               }
               else
               {

                  return argb(255, 25, 25, 25);

               }

            }
            else if (eelement == ::e_element_item_text)
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

               if (estate & ::user::e_state_disabled)
               {
                  return argb(255, 128, 128, 128);
               }
               else
               {
                  return argb(255, 230, 230, 230);
               }

            }
            else
            {

               if (estate & ::user::e_state_disabled)
               {
                  return argb(255, 128, 128, 128);
               }
               else
               {
                  return argb(255, 40, 40, 40);
               }

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


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::scroll_bar * pscrollbar)
   {

      ::color::color colorBackground = pscrollbar->get_color(this, ::e_element_scrollbar);

      ::i32_rectangle rectangleX = pscrollbar->rectangle();

      if (colorBackground.m_u8Opacity != 0)
      {

         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         

         if (session()->savings()->is_trying_to_save(::e_resource_processing))
         {

            colorBackground.m_u8Opacity = 255;

         }

         pdraw2dgraphics->fill_rectangle(rectangleX, colorBackground);

      }

      auto statusrectangleTrack = pscrollbar->get_track_rectangle(::user::e_layout_design);

      //::i32_rectangle rectangleWindow;

      //pscrollbar->window_rectangle(rectangleWindow);

      ::color::color colorBorder = pscrollbar->scrollbar_border_color(this, ::e_element_scrollbar_trackbar);

      ::pointer < ::simple_scroll_bar > pbar = pscrollbar;

      auto ppenDraw = createø < ::draw2d::pen >();

      ppenDraw->create_solid(1, colorBorder);

      ::color::color colorTrack = pscrollbar->scrollbar_color(this, ::e_element_scrollbar_trackbar);

      auto pbrushDraw = createø < ::draw2d::brush >();

      pbrushDraw->create_solid(colorTrack);

      pdraw2dgraphics->set(ppenDraw);

      pdraw2dgraphics->set(pbrushDraw);

      pdraw2dgraphics->rectangle(statusrectangleTrack);

      if (pbar->m_bTracking || pbar->is_true("tracking_on"))
      {

         auto periodFadeIn = 490_ms;

         auto periodFadeOut = 490_ms;

         ::f64 dRate = maximum(0u, minimum(1.0, pbar->get_u32("tracking_alpha") / 255.0));

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

         //::i32_point point1 = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset;

         //pbar->client_to_screen()(point1);

         //

         //auto puser = user();

         //auto pwindowing = system()->windowing();

         //auto point = pwindowing->get_cursor_position();

         //pbar->client_to_screen()(point1);

         //      prop("tracking_window").cast < trw >()->point1 = point1;

         //    prop("tracking_window").cast < trw >()->point2 = point;

         ::u8 uchAlpha;

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

         ::i32_rectangle rectangleMachineThumb;

         bool bSimple = pbar->is_true("tracking_simple");

         if (bSimple)
         {

            auto dSize = statusrectangleTrack.size().get_normal_dimension(pbar->m_eorientation) * 6 / 8;

            rectangleMachineThumb.top_left() = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::f64_size(dSize / 2.0, dSize / 2.0);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::f64_size(dSize, dSize);

            ::i32_rectangle rectangleIntersect;

            rectangleIntersect.intersect(rectangleMachineThumb, statusrectangleTrack);

            ::i32 iArea = (::i32)(maximum(1, rectangleIntersect.area()));

            rectangleMachineThumb.inflate(1 + dSize * (dSize * dSize) * 4 / (iArea * 5), 1 + dSize * (dSize * dSize) * 2 / (iArea * 3));

            pbar->draw_mac_thumb_simple(pdraw2dgraphics, rectangleMachineThumb, statusrectangleTrack, uchAlpha);

         }
         else
         {

            auto dSize = statusrectangleTrack.size().get_normal_dimension(pbar->m_eorientation);

            rectangleMachineThumb.top_left() = statusrectangleTrack.top_left() + pbar->m_sizeTrackOffset - ::f64_size(dSize / 2., dSize / 2.);

            rectangleMachineThumb.bottom_right() = rectangleMachineThumb.top_left() + ::f64_size(dSize, dSize);

            rectangleMachineThumb.assign_normal(statusrectangleTrack, pbar->m_eorientation);

            rectangleMachineThumb._007Constrain(statusrectangleTrack);

            rectangleMachineThumb.deflate(1, 1);

            pbar->draw_mac_thumb_dots(pdraw2dgraphics, rectangleMachineThumb, statusrectangleTrack, uchAlpha);

         }

         pbar->payload("tracking_alpha") = uchAlpha;

      }

      auto ppenGrip = createø < ::draw2d::pen >();

      ppenGrip->create_solid(2.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_trackbar));

      pdraw2dgraphics->set(ppenGrip);

      ::i32_point pointCenter = statusrectangleTrack.center();

      if (pbar->m_eorientation == e_orientation_horizontal)
      {

         pdraw2dgraphics->line(pointCenter.x - 5, pointCenter.y - 5,
                     pointCenter.x - 5, pointCenter.y + 5);
         pdraw2dgraphics->line(pointCenter.x, pointCenter.y - 5,
             pointCenter.x, pointCenter.y + 5);
         pdraw2dgraphics->line(pointCenter.x + 5, pointCenter.y - 5,
         pointCenter.x + 5, pointCenter.y + 5);

      }
      else
      {

         pdraw2dgraphics->line(pointCenter.x - 5, pointCenter.y - 5,
         pointCenter.x + 5, pointCenter.y - 5);
         pdraw2dgraphics->line(pointCenter.x - 5, pointCenter.y,
         pointCenter.x + 5, pointCenter.y);
         pdraw2dgraphics->line(pointCenter.x - 5, pointCenter.y + 5,
         pointCenter.x + 5, pointCenter.y + 5);

      }

      {

         auto rectangleA = pbar->get_buttonA_rectangle(rectangleX);

         auto ppenArrow = createø < ::draw2d::pen >();

         ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

         pdraw2dgraphics->set(ppenArrow);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectA));

         pdraw2dgraphics->set(pbar->m_pbrushDraw);

         pdraw2dgraphics->rectangle(rectangleA);

      }

      {

         auto rectangleB = pbar->get_buttonB_rectangle(rectangleX);

         auto ppenArrow = createø < ::draw2d::pen >();

         ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

         pdraw2dgraphics->set(ppenArrow);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_rectB));

         pdraw2dgraphics->set(pbar->m_pbrushDraw);

         pdraw2dgraphics->rectangle(rectangleB);

      }

      if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageA)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageA))
      {

         auto statusrectanglePageA = pbar->get_pageA_rectangle(rectangleX, statusrectangleTrack);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageA));

         pdraw2dgraphics->set(pbar->m_pbrushDraw);

         pdraw2dgraphics->fill_rectangle(statusrectanglePageA);

      }
      else if (::is_element(pbar->main_content().m_pitemCurrent, ::e_element_scrollbar_pageB)
         || ::is_element(pbar->m_pitemHover, ::e_element_scrollbar_pageB))
      {

         auto statusrectanglePageB = pbar->get_pageB_rectangle(rectangleX, statusrectangleTrack);

         pbar->m_pbrushDraw->create_solid(pbar->scrollbar_color(this, ::e_element_scrollbar_pageB));

         pdraw2dgraphics->set(pbar->m_pbrushDraw);

         pdraw2dgraphics->fill_rectangle(statusrectanglePageB);

      }

      {

         auto ppenArrow = createø < ::draw2d::pen >();

         ppenArrow->m_elinecapBeg = ::draw2d::e_line_cap_round;
         ppenArrow->m_elinecapEnd = ::draw2d::e_line_cap_round;
         ppenArrow->m_elinejoin = ::draw2d::e_line_join_round;

         {

            auto pointaA = pbar->get_arrowA(rectangleX);

            ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectA));

            pdraw2dgraphics->set(ppenArrow);

            pdraw2dgraphics->polyline(pointaA);

         }

         {

            auto pointaB = pbar->get_arrowB(rectangleX);

            ppenArrow->create_solid(1.0, pbar->scrollbar_lite_border_color(this, ::e_element_scrollbar_rectB));

            pdraw2dgraphics->set(ppenArrow);

            pdraw2dgraphics->polyline(pointaB);

         }

      }

      return true;

   }


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pdraw2dgraphics, ::user::interaction * pinteraction)
   {

      ::draw2d::save_context savecontext(pdraw2dgraphics);

      pdraw2dgraphics->m_pacmeuserinteractionAffinity = pinteraction;

      if (pinteraction->is_top_level())
      {

         //      if (!pframe->is_custom_draw() && pdraw2dgraphics != nullptr && pdraw2dgraphics->m_pnext == nullptr)
         //      {
         //
         //         pframe->set_context_org(pdraw2dgraphics);
         //
         //      }

         ::i32_rectangle rectangleX;

         rectangleX = pinteraction->rectangle();

         auto pstyle = pinteraction->get_style(pdraw2dgraphics);

         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         ::string strType =  ::platform::type(pinteraction).name();

         if (strType.case_insensitive_contains("menu"))
         {

            printf_line("menu");

         }

         status < ::color::color > crBackground = pinteraction->get_color(pstyle, ::e_element_background);

         //crBackground = argb(255, 200, 180, 180);

         // xxx xxx xxx
         
         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
         
         pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

         pdraw2dgraphics->fill_rectangle(rectangleX, crBackground);

      }

      return true;

   }


} // namespace experience



