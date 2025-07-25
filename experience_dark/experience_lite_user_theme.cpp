#include "framework.h" 
#include "aura/user/menu/user_menu_central.h"
#include "core/user/userex/userex.h"
// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The int_size is the int_size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"





namespace lite

{


   theme::theme(::particle * pparticle):
      object(pparticle),
      ::user::style(pparticle),
      ::user::theme(pparticle)
   {

      create_translucency(::e_element_none, ::user::e_translucency_present);

      create_point_font(::user::font_default,pnode->font_name(e_font_sans_ui), 12.0);

      userstyle()->m_mapFont->operator[](::user::font_default)->m_ewritetextrendering = ::write_text::e_rendering_clear_type_grid_fit;

      create_color(::user::color_text, argb(255, 0, 0, 0));
      create_color(::user::color_edit_text, argb(255, 0, 0, 0));
      create_color(::user::color_background, argb(255, 255, 255, 255));
      create_color(::user::color_face, argb(192, 192, 192, 192));
      create_color(::user::color_list_background, argb(255, 255, 255, 255));
      create_color(::user::color_edit_background, argb(255, 255, 255, 255));
      create_color(::user::color_tree_background, argb(255, 255, 255, 255));
      create_color(::user::color_impact_background, argb(255, 255, 255, 255));
      create_color(::user::color_scrollbar_background, argb(255, 255, 255, 255));
      create_color(::user::color_tab_layout_background, argb(255, 255, 255, 255));
      create_color(::user::color_tab_client_background, argb(255, 255, 255, 255));
      create_color(::user::color_split_layout_background, argb(255, 255, 255, 255));
      create_color(::user::color_background_selected, argb(255, 155, 185, 255));
      create_color(::user::color_list_header, argb(255, 255, 255, 255));
      create_color(::user::color_list_header_background, argb(255, 0x58, 0x5C, 0x5D));
      create_color(::user::color_list_item_text, argb(255, 0, 0, 0));
      create_color(::user::color_list_item_text_hover, argb(255, 100, 150, 200));
      create_color(::user::color_list_item_background, argb(30, 0, 0, 0));
      create_color(::user::color_list_item_background_hover, argb(50, 0, 0, 0));
      create_color(::user::color_list_item_background_selected, argb(255, 160, 210, 235));
      create_color(::user::color_list_item_background_selected_hover, argb(255, 160, 220, 255));
      create_color(::user::color_list_header_separator, 0);
      create_color(::user::color_toolbar_background, argb(255, 0xF3, 0XF5, 0xF5));
      create_color(::user::color_button_background_disabled, argb(255, 128, 128, 128));
      create_color(::user::color_button_background_hover, argb(255, 0x55, 0x99, 0xC2));
      create_color(::user::color_button_background, argb(255, 0x30, 0x75, 0xA0));
      create_color(::user::color_button_background_press, argb(255, 0x07, 0x6D, 0x91));
      create_color(::user::color_button_text_disabled, argb(255, 0xD0, 0xD0, 0xD0));
      create_color(::user::color_button_text_hover, argb(255, 255, 255, 255));
      create_color(::user::color_button_text, argb(255, 255, 255, 255));
      create_color(::user::color_button_text_press, argb(255, 255, 255, 255));
      create_color(::user::color_text_selected_highlight, argb(255, 150, 200, 250));
      create_color(::user::color_text_highlight, argb(255, 100, 150, 200));



      create_rect_coord(::user::rect_tab_padding, 0.4, 0.4, 0.4, 0.4);

      create_int(::user::int_button_press_shift_cx, 4);
      create_int(::user::int_button_press_shift_cy, 4);


   }


   theme::~theme()
   {

   }


   bool theme::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::int_rectangle rectangle;
      ::int_rectangle rectangleBorder;
      ::int_rectangle rectangleText;
      ::int_rectangle rectangleX;
      ::int_rectangle rectangleIcon;
      ::int_rectangle rectangleClose;

      ::int_rectangle r1;
      ptab->rectangle(r1);

      pgraphics->fill_rectangle(r1, argb(255, 255, 255, 255));

      ptab->get_data()->m_ppen->create_solid(1,rgb(32,32,32));

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

      color32_t crbk = ptab->_001GetColor(::user::color_tab_layout_background);

      pgraphics->fill_rectangle(rcTabs, crbk);

      crbk= ptab->_001GetColor(::user::color_tab_client_background);

      pgraphics->fill_rectangle(rcClient, crbk);

      int iTab = -1;

      ::draw2d::brush_pointer pbrushText;

      for(int iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

         if(!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if(!ptab->get_element_rectangle(iTab,rectangle,::e_element_tab))
            continue;

         if(!ptab->get_element_rectangle(iTab,rectangleBorder, ::e_element_border))
            continue;

         if(!ptab->get_element_rectangle(iTab,rectangleX, ::e_element_client))
            continue;

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rectangle(iTab,rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
/*               pane.m_pimage->bitmap_blend(pgraphics,rectangleIcon);

            }

            auto ppath = __øcreate < ::draw2d::path > ();

            if(true)
            {

               if(ptab->get_data()->m_idaSel.contains(pane.id()))
               {

                  //ppath->start_figure();

                  ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom(),rectangleBorder.left() + 1,rectangleBorder.bottom());
                  //ppath->add_line(rectangleX.right(), rectangleBorder.top());
                  ppath->add_line(rectangleBorder.left(),rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
                  ppath->add_line(rectangleX.left(),rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(),rectangleBorder.top());

                  ppath->end_figure(false);

                  pane.m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

                  pgraphics->SelectObject(pane.m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  pgraphics->SelectObject(ptab->get_data()->m_ppenBorderSel);

                  pgraphics->draw(ppath);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::e_element_close_tab_button && (ptab->m_eelementHover < ::e_element_split || ptab->m_eelementHover >(::e_element_split + 100)))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));

                  }

                  pbrushText = ptab->get_data()->m_pbrushTextSel;

               }
               else
               {

                  //ppath->start_figure();

                  ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom(),rectangleBorder.left() + 1,rectangleBorder.bottom());
                  ppath->add_line(rectangleBorder.left(),rectangleBorder.top() - (rectangleBorder.left() - rectangleX.left()));
                  ppath->add_line(rectangleText.left(),rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(),rectangleBorder.top());
                  ppath->add_line(rectangleBorder.right(),rectangleBorder.bottom());

                  ppath->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::e_element_close_tab_button && (ptab->m_eelementHover < ::e_element_split || ptab->m_eelementHover >(::e_element_split + 100)))
                  {

                     pane.m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->SelectObject(pane.m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     pgraphics->SelectObject(ptab->get_data()->m_ppenBorderHover);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     pbrushText = ptab->get_data()->m_pbrushTextHover;

                  }
                  else
                  {

                     pane.m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                     pgraphics->SelectObject(pane.m_pbrushFill);

                     pgraphics->fill(ppath);

                     pgraphics->SelectObject(ptab->get_data()->m_ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     pbrushText = ptab->get_data()->m_pbrushText;

                  }

               }

            }

         }
         else
         {

            if(ptab->get_element_rectangle(iTab,rectangleIcon, ::e_element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

/*               pane.m_pimage->bitmap_blend(pgraphics,rectangleIcon);

            }
            if (iPane == 0)
            {

               if (rcTab.left() < rectangleBorder.left())
               {

                  pgraphics->SelectObject(ptab->get_data()->m_ppenBorder);

                  pgraphics->line(rcTab.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleX.bottom());

               }

            }

            if(true)
            {

               auto ppath = __øcreate < ::draw2d::path > ();

               if(ptab->get_data()->m_idaSel.contains(pane.id()))
               {

                  if (iPane > 0)
                  {

                     ppath->add_line(rectangle.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleX.bottom());

                  }

                  ppath->add_line(rectangleBorder.left(),rectangleX.bottom(),rectangleBorder.left(),rectangleBorder.top());

                  ppath->add_line(rectangleX.right(),rectangleBorder.top());

                  ppath->add_line(rectangleBorder.right(),rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

                  ppath->add_line(rectangleBorder.right() - 1,rectangleX.bottom());

                  ppath->end_figure(false);

                  //pane.m_pbrushFillSel->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,235,235,230),argb(250,255,255,250));

                  pane.m_pbrushFillSel->create_solid(argb(255, 255, 255, 255));

                  pgraphics->SelectObject(pane.m_pbrushFillSel);

                  pgraphics->fill(ppath);

                  ptab->get_data()->m_ppenBorderSel->create_solid(1.0,argb(255,0,0,0));

                  pgraphics->SelectObject(ptab->get_data()->m_ppenBorderSel);

                  pgraphics->draw(ppath);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::e_element_close_tab_button &&( ptab->m_eelementHover < ::e_element_split || ptab->m_eelementHover >(::e_element_split + 100)))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));

                  }

                  pbrushText = ptab->get_data()->m_pbrushTextSel;

               }
               else
               {

                  //ppath->begin_figure(true, ::draw2d::e_fill_mode_winding);

                  if (iPane > 0)
                  {

                     ppath->add_line(rectangle.left(), rectangleX.bottom(), rectangleBorder.left(), rectangleX.bottom());

                  }

                  ppath->add_line(rectangleBorder.left(),rectangleX.bottom(),rectangleBorder.left(),rectangleBorder.top());

                  ppath->add_line(rectangleX.right(),rectangleBorder.top());

                  ppath->add_line(rectangleBorder.right(),rectangleBorder.top() + (rectangleBorder.right() - rectangleX.right()));

                  ppath->add_line(rectangleBorder.right() - 1,rectangleX.bottom());

                  ppath->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::e_element_close_tab_button && (ptab->m_eelementHover < ::e_element_split || ptab->m_eelementHover >(::e_element_split + 100)))
                  {

                     pane.m_pbrushFillHover->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,215,215,210),argb(250,235,235,230));

                     pgraphics->SelectObject(pane.m_pbrushFillHover);

                     pgraphics->fill(ppath);

                     pgraphics->SelectObject(ptab->get_data()->m_ppenBorderHover);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     pbrushText = ptab->get_data()->m_pbrushTextHover;

                  }
                  else
                  {

                     pane.m_pbrushFill->CreateLinearGradientBrush(rectangleBorder.top_left(),rectangleBorder.bottom_left(),argb(230,175,175,170),argb(250,195,195,190));

                     pgraphics->SelectObject(pane.m_pbrushFill);

                     pgraphics->fill(ppath);

                     pgraphics->SelectObject(ptab->get_data()->m_ppenBorder);

                     pgraphics->draw(ppath);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     pbrushText = ptab->get_data()->m_pbrushTextSel;

                  }

               }

            }

            if (iPane == ptab->get_data()->m_panea.get_upper_bound())
            {

               if (rectangleBorder.right() - 1 < rcTab.right())
               {

                  pgraphics->SelectObject(ptab->get_data()->m_ppenBorder);

                  pgraphics->line(rectangleBorder.right() - 1, rectangleX.bottom(), rcTab.right(), rectangleX.bottom());

               }

            }


         }

         if(true)
         {

            if(ptab->get_element_rectangle(iTab,rectangleText, ::e_element_text))
            {

               _001OnTabPaneDrawTitle(pane,ptab,pgraphics,rectangleText, pbrushText);

            }

         }

         if(true)
         {

            if(ptab->get_element_rectangle(iTab,rectangleClose, ::e_element_close_tab_button))
            {

               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));

               if(iTab == ptab->m_iHover && ptab->m_eelementHover == ::e_element_close_tab_button)
               {

                  pbrushText = ptab->get_data()->m_pbrushCloseHover;

               }
               else
               {

                  pbrushText = ptab->get_data()->m_pbrushClose;

               }

               pgraphics->SelectObject(pbrushText);

               pgraphics->draw_text("x",rectangleClose,e_align_center);

            }

         }

      }

      return true;

   }


   void theme::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::int_rectangle * lpcrect,::draw2d::brush_pointer & pbrushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->SelectObject(pbrushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(),*lpcrect,e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::int_rectangle rectangleText(lpcrect);

         ::write_text::font_pointer pfont;
         font = pgraphics->get_current_font();
         int_size sSep = ptab->get_data()->m_sizeSep;
         ::int_rectangle rectangleEmp;
         for(::collection::index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            int_size s = pane.m_sizeaText[i];
            rectangleText.right() =rectangleText.left() + s.cx();
            pgraphics->_DrawText(str,rectangleText,e_align_bottom_left, e_draw_text_no_prefix);
            rectangleText.left() += s.cx();
            if(i < straTitle.get_upper_bound())
            {
               rectangleText.right() = rectangleText.left() + sSep.cx();
               rectangleEmp = rectangleText;
               rectangleEmp.deflate(1,1);
               ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
               if(ptab->m_eelementHover == (int)::e_element_split + i)
               {
                  pgraphics->fill_rectangle(rectangleEmp,argb(128,149,184,255));
                  pgraphics->SelectObject(ptab->get_data()->m_pbrushTextHover);
               }
               else
               {
                  //pgraphics->FillSolidRect(rectangleEmp,argb(128,208,223,233));
                  pgraphics->SelectObject(ptab->get_data()->m_pbrushText);
               }
               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectangleText, e align_center, e_draw_text_no_prefix);
               rectangleText.left() += sSep.cx();
               pgraphics->selectFont(font);
               pgraphics->SelectObject(pbrushText);
            }
         }

      }

   }



   bool theme::_001OnTabLayout(::user::tab * ptab)
   {


      {

         //         unsigned int dwTime2= ::time::now();

         //informationf("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //informationf("usertab::on_layout call time1= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }
      if(!ptab->get_data()->m_bCreated)
         return false;

      ::user::tab_data * pdata = ptab->get_data();

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      auto pgraphics = create_memory_graphics();

      pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

      ptab->select(pgraphics);

      pdata->m_rectangleMargin = ptab._001GetRect(::user::rect_tab_margin);

      pdata->m_rectangleBorder = ptab._001GetRect(::user::rect_tab_border);

      pdata->m_rectangleTextMargin = ptab._001GetRect(::user::rect_tab_padding);

      if (pdata->m_bVertical)
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata.m_rectangleBorder.bottom() +
                                pdata->m_rectangleMargin.top() + pdata.m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata.m_rectangleBorder.right() +
                               pdata->m_rectangleMargin.left() + pdata.m_rectangleMargin.right();

      }
      else
      {

         pdata->m_iTabHeight += pdata->m_rectangleBorder.top() + pdata.m_rectangleBorder.bottom() +
                                pdata->m_rectangleMargin.top() + pdata.m_rectangleMargin.bottom();

         pdata->m_iTabWidth += pdata->m_rectangleBorder.left() + pdata.m_rectangleBorder.right() +
                               pdata->m_rectangleMargin.left() + pdata.m_rectangleMargin.right();

      }


      ptab->m_dcextension.get_text_extent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);



      if(ptab->get_data()->m_bVertical)
      {
         int iTabWidth = 16;
         int iTabHeight = 8;
         int cx;
         int cy;
         for(int iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               continue;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            ::int_size size;

            ptab->m_dcextension.get_text_extent(pgraphics,str, size);



/*            if(tab_pane.m_pimage->is_set())
            {
/*               size.cx() += tab_pane.m_pimage->width() + 2;
/*               size.cy() = maximum(size.cy(),tab_pane.m_pimage->height());
            }
            cx = size.cx() + 2;

            if(!tab_pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if(cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy() + 2;
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

         iTabWidth += ptab->get_data()->m_rectangleBorder.left() + ptab->get_data().m_rectangleBorder.right() +
                      ptab->get_data()->m_rectangleMargin.left() + ptab->get_data().m_rectangleMargin.right() +
                      ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data().m_rectangleTextMargin.right();

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectangleBorder.top() + ptab->get_data().m_rectangleBorder.bottom() +
                       ptab->get_data()->m_rectangleMargin.top() + ptab->get_data().m_rectangleMargin.bottom() +
                       ptab->get_data()->m_rectangleTextMargin.top() + ptab->get_data().m_rectangleTextMargin.bottom();

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::int_rectangle rectangleX;
         ptab->rectangle(rectangleX);

         ptab->get_data()->m_rectangleTab.left()       = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top()        = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right()      = ptab->get_data()->m_rectangleTab.left() + ptab->get_data().m_iTabWidth;
         ptab->get_data()->m_rectangleTab.bottom()     = rectangleX.bottom();

         /*      m_puserinteraction->set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         ptab->get_data()->m_rectangleHosting.left()       = ptab->m_bShowTabs ? ptab->get_data().m_rectangleTab.right() : rectangleX.left();
         ptab->get_data()->m_rectangleHosting.top()        = ptab->get_data().m_rectangleTab.top();
         ptab->get_data()->m_rectangleHosting.right()      = rectangleX.right();
         ptab->get_data()->m_rectangleHosting.bottom()     = ptab->get_data().m_rectangleTab.bottom();

      }
      else
      {
         int iTabHeight = 16;
         int cy;
         ::draw2d::graphics_pointer graphics(e_create);
         pgraphics->CreateCompatibleDC(nullptr);
         ::draw2d::graphics_pointer & pgraphics = graphics;

         pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

         ::int_rectangle rectangleX;
         ptab->rectangle(rectangleX);
         int x = rectangleX.left();

         int ixAdd;
         for(int iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               return false;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            int_size size;

            ptab->m_dcextension.get_text_extent(pgraphics,str, size);

/*            if(tab_pane.m_pimage)
            {

/*               size.cy() = maximum(size.cy(),tab_pane.m_pimage->height());

            }

            cy = size.cy() + 2;

            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            tab_pane.m_point.x() = x;
            tab_pane.m_point.y() = rectangleX.top();


            //            string str = tab_pane.get_title();

            //            int_size size;

            ixAdd = 5;

/*            if(tab_pane.m_pimage->is_set())
            {
               //::image::image_list::info ii;
/*               ixAdd += tab_pane.m_pimage->width() + 2;
            }

            if(!tab_pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            tab_pane.m_size.cx() = size.cx() + ixAdd
                                 + ptab->get_data()->m_rectangleBorder.left() + ptab->get_data().m_rectangleBorder.right()
                                 + ptab->get_data()->m_rectangleMargin.left() + ptab->get_data().m_rectangleMargin.right()
                                 + ptab->get_data()->m_rectangleTextMargin.left() + ptab->get_data().m_rectangleTextMargin.right();

            x += tab_pane.m_size.cx();
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectangleBorder.top() + ptab->get_data().m_rectangleBorder.bottom() +
                       ptab->get_data()->m_rectangleMargin.top() + ptab->get_data()->m_rectangleMargin.bottom() + ptab->get_data().m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         for(int iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            tab_pane.m_size.cy() = iTabHeight;

         }




         ptab->get_data()->m_rectangleTab.left()       = rectangleX.left();
         ptab->get_data()->m_rectangleTab.top()        = rectangleX.top();
         ptab->get_data()->m_rectangleTab.right()      = rectangleX.right();
         ptab->get_data()->m_rectangleTab.bottom()     = ptab->get_data()->m_rectangleTab.top() + ptab->get_data().m_iTabHeight;

         /*      set_window_position(
         e_zorder_top,
         m_rectangleTab.left(),
         m_rectangleTab.top(),
         m_rectangleTab.width(),
         m_rectangleTab.height(),
         0);*/

         int_rectangle & rectangleHosting = ptab->get_data()->m_rectangleHosting;

         rectangleHosting.left()       = ptab->get_data()->m_rectangleTab.left();
         rectangleHosting.top()        = ptab->m_bShowTabs ? ptab->get_data()->m_rectangleTab.bottom() : rectangleX.top();
         rectangleHosting.right()      = ptab->get_data()->m_rectangleTab.right();
         rectangleHosting.bottom()     = rectangleX.bottom();

         //TRACE0("rectangleHosting");

      }

      for(int iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         if(iPane != ptab->_001GetSel())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->_001GetSel(), ptab->is_window_visible());

      return true;

   }


   bool theme::on_ui_event(::user::e_happening ehappening, ::user::e_object eobject, ::user::interaction * pframewindow)
   {

      if (ehappening == ::id_calc_item_height)
      {

         pframewindow->m_iItemHeight += 8;

         return true;

      }

      return false;

   }


   bool theme::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar)
   {

      _001DrawLiteToolbarItem(pgraphics, iItem, ptoolbar);

      return true;

   }


   void theme::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_rectangle rectangleItem;

      ::int_rectangle rectangleImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::tool_item & item = ptoolbar->m_itema(iItem);

      unsigned int nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      ::pointer<::user::menu_central>pmenucentral = psession->userex()->menu();

      unsigned int uImage = pmenucentral->command_image(item.id());

      ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
      ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;
      if ((nStyle & e_tool_item_style_separator) == 0)
      {
         if ((nStyle & e_tool_item_style_disabled) == 0)
         {
            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::element_item_press;
                     eelementImage = ::user::toolbar::element_image_press;
                     eelementText = ::user::toolbar::element_text_press;
                  }
                  else
                  {
                     eelement = ::user::toolbar::element_item_hover;
                     eelementImage = ::user::toolbar::element_image_hover;
                     eelementText = ::user::toolbar::element_text_hover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::element_item_hover;
               eelementImage = ::user::toolbar::element_image_hover;
               eelementText = ::user::toolbar::element_text_hover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::e_element_item;
            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::e_element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::e_element_item;
         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::e_element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->index_element_rectangle(iItem, rectangleItem, eelement);

      ptoolbar->index_element_rectangle(iItem, rectangleImage, eelementImage);

      if ((nStyle & e_tool_item_style_separator) != 0)
      {
         ::int_rectangle rectangleSeparator;
         rectangleSeparator.left() = (rectangleImage.left() + rectangleImage.right()) / 2 - 1;
         rectangleSeparator.right() = rectangleSeparator.left() + 2;
         rectangleSeparator.top() = rectangleImage.top();
         rectangleSeparator.bottom() = rectangleImage.bottom();
         pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));
      }
      else
      {
         if (eelement == ::user::toolbar::element_item_hover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

               ptoolbar->index_element_rectangle(iItem, rectangleImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  psystem->imaging().color_blend(
                  pgraphics,
                  rectangleItem.left(),
                  rectangleItem.top(),
                  rectangleItem.width(),
                  rectangleItem.height(),
                  rgb(255, 255, 250), 208);

                  pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));
               }

               if (uImage != 0xffffffffu)
               {

                  if ((nStyle & e_tool_item_style_disabled) == 0)
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

               ::int_rectangle rectangleShadow;

               ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::user::toolbar::element_item_hover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  auto ppen = __øcreate < ::draw2d::pen > ();

                  ppen->create_solid(1, argb(184, 92, 184, 92));
                  auto pbrush = __øcreate < ::draw2d::brush >();

                  pbrush->create_solid(argb(123, 177, 184, 255));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectangleItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

               if (item.m_pimage->is_set())
               {

                  ::int_rectangle rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_hover);

                  pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 0->84);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::int_rectangle rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_item_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::element_item_press)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __øcreate < ::draw2d::pen > ();

               ppen->create_solid(1, argb(255, 92, 92, 92));
               auto pbrush = __øcreate < ::draw2d::brush >();

               pbrush->create_solid(argb(255, 255, 255, 255));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectangleItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

            if (item.m_pimage->is_set())
            {

               ::int_rectangle rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_press);

               pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 1->0);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & e_tool_item_style_disabled) == 0)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

               pgraphics->fill_rectangle(rectangleItem, argb(184, 255, 255, 255));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if (item.m_pimage->is_set())
            {

               ::int_rectangle rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image);

               pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 0->23);

            }
            else if (uImage != 0xffffffff)
            {

               if ((nStyle & e_tool_item_style_disabled) == 0)
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

      if (item.m_str.has_character())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         ::int_rectangle rectangleText;

         auto pbrushText = __øcreate < ::draw2d::brush > ();

         if ((nStyle & e_tool_item_style_disabled) == 0)
         {

            pbrushText->create_solid(argb(255, 0, 0, 0));

         }
         else
         {

            pbrushText->create_solid(argb(255, 123, 123, 118));

         }

         pgraphics->SelectObject(pbrushText);

         if (ptoolbar->index_element_rectangle(iItem, rectangleText, eelementText) && rectangleText.right() > 0)
         {

            pgraphics->_DrawText(item.m_str, item.m_str.length(), rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }

   void theme::_001DrawLiteToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::int_rectangle rectangleItem;

      ::int_rectangle rectangleImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::tool_item & item = ptoolbar->m_itema(iItem);

      unsigned int nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      ::pointer<::user::menu_central>pmenucentral = psession->userex()->menu();

/*      unsigned int uImage = pmenucentral->command_image(item.id());

      ::user::toolbar::enum_element eelement = ::user::toolbar::e_element_item;
/*      ::user::toolbar::enum_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::enum_element eelementText = ::user::toolbar::e_element_text;

      if ((nStyle & e_tool_item_style_separator) == 0)
      {

         if ((nStyle & e_tool_item_style_disabled) == 0)
         {

            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::element_item_press;
                     eelementImage = ::user::toolbar::element_image_press;
                     eelementText = ::user::toolbar::element_text_press;
                  }
                  else
                  {
                     eelement = ::user::toolbar::element_item_hover;
                     eelementImage = ::user::toolbar::element_image_hover;
                     eelementText = ::user::toolbar::element_text_hover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::element_item_hover;
               eelementImage = ::user::toolbar::element_image_hover;
               eelementText = ::user::toolbar::element_text_hover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::e_element_item;
/*            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::e_element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::e_element_item;
/*         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::e_element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->index_element_rectangle(iItem, rectangleItem, eelement);

      ptoolbar->index_element_rectangle(iItem, rectangleImage, eelementImage);

      if (item.id().case_insensitive_order("separator") == 0)
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
         if (eelement == ::user::toolbar::element_item_hover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

/*               ptoolbar->index_element_rectangle(iItem, rectangleImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  psystem->imaging().color_blend(
                  pgraphics,
                  rectangleItem.left(),
                  rectangleItem.top(),
                  rectangleItem.width(),
                  rectangleItem.height(),
                  rgb(255, 255, 250), 208);

                  pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));
               }

               if (uImage != 0xffffffffu)
               {

                  if ((nStyle & e_tool_item_style_disabled) == 0)
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

               ::int_rectangle rectangleShadow;

               ptoolbar->index_element_rectangle(iItem, rectangleShadow, ::user::toolbar::element_item_hover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  auto ppen = __øcreate < ::draw2d::pen > ();

                  ppen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_hover));
                  auto pbrush = __øcreate < ::draw2d::brush >();

                  pbrush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_hover));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectangleItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

/*               if (item.m_pimage->is_set())
               {

                  ::int_rectangle rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_hover);

/*                  pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 0->84);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::int_rectangle rectangle;

                  ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_item_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::element_item_press)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __øcreate < ::draw2d::pen > ();

               ppen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_press));
               auto pbrush = __øcreate < ::draw2d::brush >();

               pbrush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_press));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectangleItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

/*            if (item.m_pimage->is_set())
            {

               ::int_rectangle rectangle;

               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image_press);

/*               pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 1->0);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & e_tool_item_style_disabled) == 0)
            {

               ptoolbar->index_element_rectangle(iItem, rectangleItem, ::user::toolbar::e_element_item);

               pgraphics->fill_rectangle(rectangleItem, _001GetColor(::user::color_button_background));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __øcreate < ::draw2d::pen > ();

               ppen->create_solid(1, ptoolbar->_001GetColor(
                                 (nStyle & e_tool_item_style_disabled) == 0 ?
                                 ::user::color_button_background :
                                 ::user::color_button_background_disabled));
               auto pbrush = __øcreate < ::draw2d::brush >();

               pbrush->create_solid(ptoolbar->_001GetColor(
                                   (nStyle & e_tool_item_style_disabled) == 0 ?
                                   ::user::color_button_background :
                                   ::user::color_button_background_disabled));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectangleItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

/*            if (item.m_pimage->is_set())
            {

               ::int_rectangle rectangle;

/*               ptoolbar->index_element_rectangle(iItem, rectangle, ::user::toolbar::element_image);

/*               pgraphics->color_blend(rectangle.top_left(), rectangle.get_size(), item.m_pimage->g(), ::int_point(), 0->23);

            }
            else if (uImage != 0xffffffff)
            {

               if ((nStyle & e_tool_item_style_disabled) == 0)
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

      if (item.m_str.has_character())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         ::int_rectangle rectangleText;

         auto pbrushText = __øcreate < ::draw2d::brush > ();

         if ((nStyle & e_tool_item_style_disabled) == 0)
         {

            pbrushText->create_solid(argb(255, 255, 255, 255));

            pgraphics->set_text_color(argb(255, 255, 255, 255));

         }
         else
         {

            pbrushText->create_solid(ptoolbar->_001GetColor(

                                    ::user::color_button_text_disabled));

            pgraphics->set_text_color(ptoolbar->_001GetColor(

                                      ::user::color_button_text_disabled));

         }

         if (ptoolbar->index_element_rectangle(iItem, rectangleText, eelementText) && rectangleText.right() > 0)
         {

            pgraphics->SelectObject(pbrushText);

            pgraphics->draw_text(item.m_str, item.m_str.length(), rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }


   bool theme::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      ::int_rectangle rectangleX;

      psplitlayout->rectangle(rectangleX);

      pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

      return true;

   }


   bool theme::get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext)
   {

      return ::user::theme::get_font(sp, efont, pcontext);

   }


   bool theme::get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext)
   {

      if (edouble == ::user::double_list_item_height_rate)
      {

         d = 1.65;

         return true;

      }

      return ::user::style::get_double(d, edouble, pcontext);

   }


} // namespace lite




