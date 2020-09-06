#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   style::style()
   {

      m_puserstyle = this;
      m_pgraphics = nullptr;

      default_style_construct();

   }


   style::style(::object * pobject) :
      ::object(pobject)
   {

      m_puserstyle = this;
      m_pgraphics = nullptr;

      default_style_construct();

   }


   style::~style()
   {

   }


   void style::default_style_construct()
   {

      m_pfont = ::draw2d::point_font("Segoe UI", 14.0);
      //m_pfontMenu;
      //m_pfontButton;
      //m_pfontList;
      //m_pfontTree;
      //m_pfontStill;
      //m_pfontEdit;
      //m_pfontCombo;

   }


   ::estatus style::initialize_style()
   {

      return ::success;

   }


   //void style::select_default()
   //{

   //   if (pstyle.is_set())
   //   {

   //      m_puserstyleSelect = pstyle;

   //   }
   //   else
   //   {

   //      m_puserstyleSelect = this;

   //   }

   //}








   //void style::initialize_style()
   //{

   //   ::user::style::initialize_style();

   //   color color;
   //   color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));

   //   class color colorHover(color);
   //   colorHover.hls_rate(0.0, 0.3, 0.0);

   //   class color colorPress(color);
   //   colorPress.hls_rate(0.0, 0.7, 0.0);

   //   m_eschema = schema_default;

   //   create_opaque_color(color_text, ::color_black);

   //}


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame * pframe)
   {

      return false;

   }


   bool style::draw_check(::enum_check echeck, const ::rect & rect, ::draw2d::graphics_pointer & pgraphics)

   {

      if (echeck == ::check_tristate || echeck == ::check_checked)
      {

         int w = rect.width();

         int h = rect.height();

         ::draw2d::pen_pointer pen(e_create);

         bool bHover = pgraphics->m_pdrawcontext != nullptr && pgraphics->m_pdrawcontext->is_control_hover();

         if (bHover)
         {

            pen->create_solid(1 * (w + h) / 30, echeck == ::check_checked ? ARGB(255, 50, 80, 160) : ARGB(255, 80, 120, 200));

         }
         else
         {

            pen->create_solid(1 * (w + h) / 30, echeck == ::check_checked ? ARGB(255, 0, 0, 0) : ARGB(255, 96, 96, 96));

         }

         pgraphics->set(pen);

         pgraphics->move_to(2 * w / 15, 8 * h / 15);
         pgraphics->line_to(6 * w / 15, 12 * h / 15);
         pgraphics->line_to(13 * w / 15, 5 * h / 15);
         pgraphics->move_to(2 * w / 15, 9 * h / 15);
         pgraphics->line_to(6 * w / 15, 13 * h / 15);
         pgraphics->line_to(13 * w / 15, 6 * h / 15);

      }

      return true;

   }




   //bool style::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   bool style::simple_ui_draw_focus_rect(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics)
   {

      bool bError = pinteraction->m_ptooltip.is_set() && pinteraction->m_ptooltip->is_window_visible(layout_sketch);

      ::draw2d::savedc savedc(pgraphics);

      ::rect rectClient = pinteraction->::user::interaction::get_client_rect();

      double dRotate = pinteraction->get_rotate();

      if (dRotate != 0.)
      {

         ::draw2d::matrix mRot;

         mRot.append(::draw2d::matrix::rotation(dRotate));

         pgraphics->prepend(mRot);

         ::draw2d::matrix mTrans;

         auto offset = rectClient.center();

         mTrans.append(::draw2d::matrix::translation(offset.x, offset.y));

         pgraphics->append(mTrans);

         rectClient -= offset;

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      i32 iStyle = 1;

      rectClient.left--;

      rectClient.top--;

      if (get_context_application() != nullptr && (pinteraction->hover_item().is_set() || pinteraction->has_focus()))
      {

         ::draw2d::brush_pointer brush(e_create);

         if (pinteraction->hover_item().is_set() && !pinteraction->has_text_input())
         {

            brush->create_solid(pinteraction->get_color(this, element_background, e_state_hover));

            pgraphics->set(brush);

            pgraphics->fill_rect(rectClient);

         }

         if (iStyle == 1)
         {

            bool bHover = pinteraction->hover_item().is_set();

            if (bHover)
            {

               ::draw2d::pen_pointer& pen = m_penFocusRect0;

               if (!pen)
               {

                  pen.create();

                  pen->create_solid(1.0, pinteraction->get_color(this, element_border, e_state_hover));

               }

               pgraphics->draw_rect(rectClient, pen);

            }
            else
            {

               ::draw2d::pen_pointer& pen = m_penFocusRect1;

               if (!pen)
               {

                  pen.create();

                  pen->create_solid(1.0, ARGB(190, 90, 90, 80));

               }

               pgraphics->draw_rect(rectClient, pen);

            }

#ifdef WINDOWS_DESKTOP

            oswindow hwndFocus = ::get_focus();

            oswindow hwndThis = pinteraction->get_handle();

#endif

            if (pinteraction->has_focus())
            {

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::pen_pointer& pen = m_penFocusRect2;

                  if (!pen)
                  {

                     pen.create();

                     pen->create_solid(1.0, bError ? ARGB(195, 255, 130, 120) : bHover ? ARGB(220, 120, 190, 255) : ARGB(220, 150, 190, 235));

                  }

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::pen_pointer& pen = m_penFocusRect3;

                  if (!pen)
                  {

                     pen.create();

                     pen->create_solid(1.0, bError ? ARGB(155, 255, 150, 140) : bHover ? ARGB(200, 140, 200, 255) : ARGB(200, 150, 210, 235));

                  }

                  pgraphics->set(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  //::draw2d::path_pointer & pathRound = m_pathFocusRect1;
                  //
                  //if (!pathRound)
                  //{

                  //   pathRound.create();

                  //   pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //   pathRound->add_round_rect(rectClient, 1 * 2);

                  //   pathRound->end_figure(true);

                  //}

                  ::draw2d::pen_pointer& pen = m_penFocusRect4;

                  if (!pen)
                  {

                     pen.create();

                     pen->create_solid(1.0, bError ? ARGB(135, 255, 170, 160) : bHover ? ARGB(160, 160, 210, 255) : ARGB(160, 180, 220, 255));

                  }

                  pgraphics->set(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, ARGB(60, 108, 149, 255));
                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1.0, bError ? ARGB(105, 255, 190, 180) : bHover ? ARGB(120, 180, 220, 255) : ARGB(120, 200, 230, 235));

                  pgraphics->set(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }


               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, ARGB(48, 108, 149, 255));
                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1.0, bError ? ARGB(75, 255, 210, 200) : bHover ? ARGB(80, 200, 230, 255) : ARGB(80, 220, 231, 235));

                  pgraphics->set(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }



               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, ARGB(36, 108, 149, 255));
                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1.0, bError ? ARGB(45, 255, 230, 220) : bHover ? ARGB(40, 220, 240, 255) : ARGB(40, 230, 235, 240));

                  pgraphics->set(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }




            }

         }
         else
         {

            ::draw2d::pen_pointer pen(e_create);

            pen->create_solid(3.0, ARGB(255, 90, 80, 255));

            pgraphics->draw_rect(rectClient, pen);

         }

      }
      else
      {

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1.0, pinteraction->get_color(this, element_border));

         pgraphics->draw_rect(rectClient, pen);

      }

      return true;

   }


   //bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, tab * ptab)
   //{

   //   return false;

   //}


   //bool style::_001OnDrawMenuInteraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * pinteraction)
   //{

   //   return false;

   //}


   //void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText)
   //{

   //   Session._001OnDefaultTabPaneDrawTitle(pane, ptab, pgraphics, rect, brushText);

   //}


   //bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab)
   //{

   //   return false;

   //}


   //   bool style::_001GetMainFrameTranslucency(::user::e_translucency & etranslucency)
   //   {
   //
   //      return false;
   //
   //   }


   //   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame_window * pframe)
   //   {
   //
   //      return false;
   //
   //   }


   //bool style::_001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox)
   //{

   //   return false;

   //}


   bool style::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
   {

      return false;

   }


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   bool style::_001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   //__pointer(::user::menu_interaction) style::create_menu_button(::user::style_pointer & pstyle, menu_item * pitem)
   //{

   //   return Session.create_menu_button(pstyle, pitem);

   //}


   //bool style::prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem)
   //{

   //   if (!prepare_menu_button(pgraphics,pitem))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem)
   //{

   //   pgraphics->m_puserstyle = this;

   //   Session.prepare_menu_button(pgraphics, pitem);

   //   return true;

   //}


   //bool style::create_color(e_color ecolor, COLORREF cr)
   //{

   //   if (userstyle()->m_mapColor.is_null())
   //   {

   //      userstyle()->m_mapColor = __new(color_map);

   //   }

   //   (*userstyle()->m_mapColor)[ecolor] = cr;

   //   return true;

   //}


  // ::draw2d::font_pointer style::create_point_font(e_font efont, const char * pszFamilyName, double dFontSize, int iFontWeight)
  // {

  //    if (userstyle()->m_mapFont.is_null())
  //    {

  //       userstyle()->m_mapFont = __new(font_map);

  //    }

  //    auto & font = (*userstyle()->m_mapFont)[efont];

  ///*    if (font.is_null())
  //    {*/

  //    __defer_construct(font);

  //  //  }

  //    font->create_point_font(pszFamilyName, dFontSize, iFontWeight);

  //    return font;

  // }


   //bool style::create_opaque_color(e_color ecolor, COLORREF cr)
   //{

   //   if (!create_color(ecolor, opaque_color(cr)))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_opaque_color(e_color eusercolor, ::e_color ecolor)
   //{

   //   if (!create_color(eusercolor, opaque_color(ecolor)))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_session_default_opaque_color(e_color eusercolor, u64 ui)
   //{

   //   if (!create_opaque_color(eusercolor, Session.get_default_color(ui)))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_session_default_color(e_color eusercolor, BYTE bAlpha, u64 ui)
   //{

   //   if (!create_color(eusercolor, alpha_color(bAlpha, Session.get_default_color(ui))))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_translucency(e_element eelement, e_translucency etranslucency)
   //{

   //   if (userstyle()->m_mapTranslucency.is_null())
   //   {

   //      userstyle()->m_mapTranslucency = __new(translucency_map);

   //   }

   //   (*userstyle()->m_mapTranslucency)[eelement] = etranslucency;

   //   return true;

   //}


   //bool style::create_flag(e_flag eflag, bool bFlag)
   //{

   //   if (userstyle()->m_mapFlag.is_null())
   //   {

   //      userstyle()->m_mapFlag = __new(translucency_map);

   //   }

   //   (*userstyle()->m_mapFlag)[eflag] = bFlag;

   //   return true;

   //}


   //bool style::create_pixel_rect_coord(e_rect erect, double l, double t, double r, double b)
   //{

   //   return create_rect_coord(erect, l, t, r, b, ::draw2d::unit_pixel);

   //}


   //bool style::create_pixel_rect_dim(e_rect erect, double l, double t, double w, double h)
   //{

   //   return create_rect_dim(erect, l, t, w, h, ::draw2d::unit_pixel);

   //}


   //bool style::create_pixel_rect(e_rect erect, rectd r)
   //{

   //   return create_rect(erect, r, ::draw2d::unit_pixel);

   //}


   //bool style::create_point_rect_coord(e_rect erect, double l, double t, double r, double b)
   //{

   //   return create_rect_coord(erect, l, t, r, b, ::draw2d::unit_point);

   //}


   //bool style::create_point_rect_dim(e_rect erect, double l, double t, double w, double h)
   //{

   //   return create_rect_dim(erect, l, t, w, h, ::draw2d::unit_point);

   //}


   //bool style::create_point_rect(e_rect erect, rectd r)
   //{

   //   return create_rect(erect, r, ::draw2d::unit_point);

   //}


   //bool style::create_rect_coord(e_rect erect, double l, double t, double r, double b, ::draw2d::e_unit eunit)
   //{

   //   if (userstyle()->m_mapRect.is_null())
   //   {

   //      userstyle()->m_mapRect = __new(rect_map);

   //   }

   //   (*userstyle()->m_mapRect)[erect].set_rect_coord(l, t, r, b, eunit);

   //   return true;

   //}


   //bool style::create_rect_dim(e_rect erect, double l, double t, double w, double h, ::draw2d::e_unit eunit)
   //{

   //   return create_rect_coord(erect, l, t, l + w, t + h, eunit);

   //}


   //bool style::create_rect(e_rect erect, ::rectd rect, ::draw2d::e_unit eunit)
   //{

   //   return create_rect_coord(erect, rect.left, rect.top, rect.right, rect.bottom, eunit);

   //}


   //bool style::create_int(e_int eint, int i)
   //{

   //   if (userstyle()->m_mapInt.is_null())
   //   {

   //      userstyle()->m_mapInt = __new(::user::int_map);

   //   }

   //   (*userstyle()->m_mapInt)[eint] = i;

   //   return true;

   //}


   //bool style::create_double(e_double edouble, double d)
   //{

   //   if (userstyle()->m_mapDouble.is_null())
   //   {

   //      userstyle()->m_mapDouble = __new(::user::double_map);

   //   }

   //   (*userstyle()->m_mapDouble)[edouble] = d;

   //   return true;

   //}

   e_control_type style::get_control_type() const
   {

      return control_type_none;

   }


   ::color style::get_color(const ::user::interaction* pinteraction, ::user::e_element eelement, ::user::estate estate) const
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::control_type_list)
         {

            if (eelement == ::user::element_background)
            {

               return ::color(0, 0, 0, 0);

            }

         }

      }

      return ::color();

   }


   //void style::nextstyle(style_context * pcontext)
   //{

   //   if (::is_set(m_pgraphics) && ::is_set(m_pgraphics->m_puserinteraction))
   //   {

   //      m_pgraphics->m_puserinteraction->nextstyle(pcontext);

   //   }
   //   else
   //   {

   //      pcontext->pstyle.release();

   //   }

   //}


   //void style::defer_create_user_schema(::user::e_schema eschema)
   //{

   //   ::user::style * puserstyle = pstyle;

   //   if (puserstyle == nullptr)
   //   {

   //      puserstyle = this;

   //   }

   //   if (eschema == schema_default)
   //   {

   //      m_puserstyleSelect = puserstyle;

   //   }
   //   else
   //   {

   //      auto & spuserstyle = puserstyle->m_map[eschema];

   //      if (spuserstyle.is_null())
   //      {

   //         spuserstyle = __new(style(get_object()));

   //      }

   //      m_puserstyleSelect = spuserstyle;

   //   }

   //}


   //void style::select_user_schema()
   //{

   //   auto eschema = m_eschema;

   //   ::user::style * puserstyle = pstyle;

   //   if (puserstyle == nullptr)
   //   {

   //      puserstyle = this;

   //   }

   //   if (eschema == schema_default)
   //   {

   //      m_puserstyleSelect = puserstyle;

   //   }
   //   else
   //   {

   //      auto & spuserstyle = puserstyle->m_map[eschema];

   //      if (spuserstyle.is_set())
   //      {

   //         m_puserstyleSelect = spuserstyle;

   //      }
   //      else
   //      {

   //         m_puserstyleSelect = puserstyle;

   //      }

   //   }

   //}


   //void style::set_user_schema(::user::e_schema eschema)
   //{

   //   m_eschema = eschema;

   //}


   //style * style::style_get(::user::e_schema eschema)
   //{

   //   if (eschema == schema_default)
   //   {

   //      return this;

   //   }

   //   style_pointer pstyle;

   //   if (m_map.lookup(eschema, pstyle))
   //   {

   //      return pstyle;

   //   }

   //   return this;

   //}


   void style::select(::draw2d::graphics_pointer & pgraphics)
   {

      m_pgraphics = pgraphics;

   }


   ::draw2d::graphics * style::style_get_graphics()
   {

      return m_pgraphics;

   }


   style * style::userstyle()
   {

      return m_puserstyle;

   }


   //style_context::style_context()
   //{


   //}


   //style_context::~style_context()
   //{


   //}


} // namespace user



