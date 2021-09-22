#include "framework.h"
#include "axis/user/_user.h"


namespace axis
{


   style::style()
   {

      m_puserstyle = this;
      m_pgraphics = nullptr;

      default_style_construct();

   }




   void style::default_style_construct()
   {

      //m_pfont = ::write_text::point_font(pnode->font_name(e_font_sans_ex), 14.0);
      //m_pfontMenu;
      //m_pfontButton;
      //m_pfontList;
      //m_pfontTree;
      //m_pfontStill;
      //m_pfontEdit;
      //m_pfontCombo;

   }


   ::e_status style::initialize_style()
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

   //   ::color::color color;
   //   color.set_rgb(psession->get_default_color(COLOR_HIGHLIGHT));

   //   class ::color::color colorHover(color);
   //   colorHover.hls_rate(0.0, 0.3, 0.0);

   //   class ::color::color colorPress(color);
   //   colorPress.hls_rate(0.0, 0.7, 0.0);

   //   m_eschema = schema_default;

   //   create_opaque_color(color_text, ::color_black);

   //}


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame * pframe)
   {

      return false;

   }


   bool style::draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics)
   {

      if (echeck == ::check_tristate || echeck == ::check_checked)
      {

         int w = rectangle.width();

         int h = rectangle.height();

         auto ppen = __create < ::draw2d::pen > ();

         bool bHover = pgraphics->m_pdrawcontext != nullptr && pgraphics->m_pdrawcontext->is_control_hover();

         if (bHover)
         {

            ppen->create_solid(1 * (w + h) / 30, echeck == ::check_checked ? argb(255, 50, 80, 160) : argb(255, 80, 120, 200));

         }
         else
         {

            ppen->create_solid(1 * (w + h) / 30, echeck == ::check_checked ? argb(255, 0, 0, 0) : argb(255, 96, 96, 96));

         }

         ::user::e_state estate;

         if (bHover)
         {

            estate |= ::user::e_state_hover;

         }

         if (echeck == ::check_checked)
         {

            estate |= ::user::e_state_checked;

         }

         //if (bHover)
         //{
         //   echeck == ::check_checked


         //}
         //else
         //{

         //   ppen->create_solid(1 * (w + h) / 30, echeck == ::check_checked ? argb(255, 0, 0, 0) : argb(255, 96, 96, 96));

         //}pinteraction->get ? argb(255, 50, 80, 160) : argb(255, 80, 120, 200)

         auto colorCheck = pinteraction->get_color(this, estate);

         ppen->create_solid(1 * (w + h) / 30, colorCheck);

         pgraphics->set(ppen);

         pgraphics->move_to(2 * w / 15, 8 * h / 15);
         pgraphics->line_to(6 * w / 15, 12 * h / 15);
         pgraphics->line_to(13 * w / 15, 5 * h / 15);
         pgraphics->move_to(2 * w / 15, 9 * h / 15);
         pgraphics->line_to(6 * w / 15, 13 * h / 15);
         pgraphics->line_to(13 * w / 15, 6 * h / 15);

      }

      return true;

   }




   //bool style::on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction)
   //{

   //   return false;

   //}


   bool style::simple_ui_draw_focus_rect(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics)
   {

      bool bError = pinteraction->m_ptooltip.is_set() && pinteraction->m_ptooltip->is_window_visible(::user::e_layout_sketch);

      ::draw2d::savedc savedc(pgraphics);

      ::rectangle_i32 rectangleClient = pinteraction->::user::interaction::get_client_rect();

      double dRotate = pinteraction->get_rotate();

      if (dRotate != 0.)
      {

         ::draw2d::matrix mRot;

         mRot.append(::draw2d::matrix::rotation(dRotate));

         pgraphics->prepend(mRot);

         ::draw2d::matrix mTrans;

         auto offset = rectangleClient.center();

         mTrans.append(::draw2d::matrix::translation(offset.x, offset.y));

         pgraphics->append(mTrans);

         rectangleClient -= offset;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      i32 iStyle = 1;

      rectangleClient.left--;

      rectangleClient.top--;

      if (get_application() != nullptr && (pinteraction->hover_item().is_set() || pinteraction->has_keyboard_focus()))
      {

         auto pbrush = __create < ::draw2d::brush >();

         if (!pinteraction->m_flagNonClient.has(::user::interaction::non_client_hover_rect) && pinteraction->hover_item().is_set() && !pinteraction->has_text_input())
         {

            pbrush->create_solid(pinteraction->get_color(this, ::e_element_background, ::user::e_state_hover));

            pgraphics->set(pbrush);

            pgraphics->fill_rectangle(rectangleClient);

         }

         if (iStyle == 1)
         {

            bool bHover = pinteraction->hover_item().is_set();

            if (bHover)
            {

               ::draw2d::pen_pointer & ppen = m_ppenFocusRect0;

               if (!ppen)
               {

                  ppen.create(this);

                  ppen->create_solid(1.0, pinteraction->get_color(this, ::e_element_border, ::user::e_state_hover));

               }

               pgraphics->draw_rectangle(rectangleClient, ppen);

            }
            else
            {

               ::draw2d::pen_pointer & ppen = m_ppenFocusRect1;

               if (!ppen)
               {

                  ppen.create(this);

                  ppen->create_solid(1.0, argb(190, 90, 90, 80));

               }

               pgraphics->draw_rectangle(rectangleClient, ppen);

            }

            __pointer(::axis::session) psession = get_session();

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pwindowFocus = pwindowing->get_keyboard_focus(pinteraction->m_pthreadUserInteraction);

            auto pwindowThis = pinteraction->get_window();

            if (pinteraction->has_keyboard_focus())
            {

               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  ::draw2d::pen_pointer & ppen = m_ppenFocusRect2;

                  if (!ppen)
                  {

                     ppen.create(this);

                     ppen->create_solid(1.0, bError ? argb(195, 255, 130, 120) : bHover ? argb(220, 120, 190, 255) : argb(220, 150, 190, 235));

                  }

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }

               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  ::draw2d::pen_pointer & ppen = m_ppenFocusRect3;

                  if (!ppen)
                  {

                     ppen.create(this);

                     ppen->create_solid(1.0, bError ? argb(155, 255, 150, 140) : bHover ? argb(200, 140, 200, 255) : argb(200, 150, 210, 235));

                  }

                  pgraphics->set(ppen);

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }

               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  //::draw2d::path_pointer & pathRound = m_pathFocusRect1;
                  //
                  //if (!pathRound)
                  //{

                  //   pathRound.create();

                  //   pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //   pathRound->add_round_rect(rectangleClient, 1 * 2);

                  //   pathRound->end_figure(true);

                  //}

                  ::draw2d::pen_pointer & ppen = m_ppenFocusRect4;

                  if (!ppen)
                  {

                     ppen.create(this);

                     ppen->create_solid(1.0, bError ? argb(135, 255, 170, 160) : bHover ? argb(160, 160, 210, 255) : argb(160, 180, 220, 255));

                  }

                  pgraphics->set(ppen);

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }

               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectangleClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, argb(60, 108, 149, 255));
                  auto ppen = __create < ::draw2d::pen > ();

                  ppen->create_solid(1.0, bError ? argb(105, 255, 190, 180) : bHover ? argb(120, 180, 220, 255) : argb(120, 200, 230, 235));

                  pgraphics->set(ppen);

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }


               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectangleClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, argb(48, 108, 149, 255));
                  auto ppen = __create < ::draw2d::pen > ();

                  ppen->create_solid(1.0, bError ? argb(75, 255, 210, 200) : bHover ? argb(80, 200, 230, 255) : argb(80, 220, 231, 235));

                  pgraphics->set(ppen);

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }



               rectangleClient.left--;
               rectangleClient.right++;
               rectangleClient.top--;
               rectangleClient.bottom++;

               {

                  //::draw2d::path_pointer pathRound(e_create);

                  //pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  //pathRound->add_round_rect(rectangleClient, 1 * 2);

                  //pathRound->end_figure(true);

                  //::draw2d::pen_pointer pen(pgraphics, 1.0, argb(36, 108, 149, 255));
                  auto ppen = __create < ::draw2d::pen > ();

                  ppen->create_solid(1.0, bError ? argb(45, 255, 230, 220) : bHover ? argb(40, 220, 240, 255) : argb(40, 230, 235, 240));

                  pgraphics->set(ppen);

                  pgraphics->draw_rectangle(rectangleClient, ppen);

               }




            }

         }
         else
         {

            auto ppen = __create < ::draw2d::pen > ();

            ppen->create_solid(3.0, argb(255, 90, 80, 255));

            pgraphics->draw_rectangle(rectangleClient, ppen);

         }

      }
      else
      {

         auto ppen = __create < ::draw2d::pen >();

         ppen->create_solid(1.0, pinteraction->get_color(this, ::e_element_border));

         pgraphics->draw_rectangle(rectangleClient, ppen);

      }

      return true;

   }


   //bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, tab * ptab)
   //{

   //   return false;

   //}


   //bool style::_001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * pinteraction)
   //{

   //   return false;

   //}


   //void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText)
   //{

   //   psession->_001OnDefaultTabPaneDrawTitle(pane, ptab, pgraphics, rectangle, pbrushText);

   //}


   //bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab)
   //{

   //   return false;

   //}


   //   bool style::_001GetMainFrameTranslucency(::user::enum_translucency & etranslucency)
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

   //   return psession->create_menu_button(pstyle, pitem);

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

   //   psession->prepare_menu_button(pgraphics, pitem);

   //   return true;

   //}


   //bool style::create_color(e_color ecolor, ::color32_t color32)
   //{

   //   if (userstyle()->m_mapColor.is_null())
   //   {

   //      userstyle()->m_mapColor = __new(color_map);

   //   }

   //   (*userstyle()->m_mapColor)[ecolor] = color32;

   //   return true;

   //}


  // ::write_text::font_pointer style::create_point_font(e_font efont, const ::string & pszFamilyName, double dFontSize, int iFontWeight)
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

  //    pfont->create_point_font(pszFamilyName, dFontSize, iFontWeight);

  //    return font;

  // }


   //bool style::create_opaque_color(e_color ecolor, ::color32_t color32)
   //{

   //   if (!create_color(ecolor, opaque_color(color32)))
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


   //bool style::create_session_default_opaque_color(e_color eusercolor, u64 u)
   //{

   //   if (!create_opaque_color(eusercolor, psession->get_default_color(u)))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_session_default_color(e_color eusercolor, byte bAlpha, u64 u)
   //{

   //   if (!create_color(eusercolor, alpha_color(bAlpha, psession->get_default_color(u))))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool style::create_translucency(enum_element eelement, enum_translucency etranslucency)
   //{

   //   if (userstyle()->m_mapTranslucency.is_null())
   //   {

   //      userstyle()->m_mapTranslucency = __new(translucency_map);

   //   }

   //   (*userstyle()->m_mapTranslucency)[eelement] = etranslucency;

   //   return true;

   //}


   //bool style::create_flag(enum_flag eflag, bool bFlag)
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


   //bool style::create_pixel_rect(e_rect erect, rectangle_f64 r)
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


   //bool style::create_point_rect(e_rect erect, rectangle_f64 r)
   //{

   //   return create_rect(erect, r, ::draw2d::unit_point);

   //}


   //bool style::create_rect_coord(e_rect erect, double l, double t, double r, double b, ::draw2d::enum_unit eunit)
   //{

   //   if (userstyle()->m_mapRect.is_null())
   //   {

   //      userstyle()->m_mapRect = __new(rect_map);

   //   }

   //   (*userstyle()->m_mapRect)[erect].set_rect_coord(l, t, r, b, eunit);

   //   return true;

   //}


   //bool style::create_rect_dim(e_rect erect, double l, double t, double w, double h, ::draw2d::enum_unit eunit)
   //{

   //   return create_rect_coord(erect, l, t, l + w, t + h, eunit);

   //}


   //bool style::create_rect(e_rect erect, ::rectangle_f64 rectangle, ::draw2d::enum_unit eunit)
   //{

   //   return create_rect_coord(erect, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, eunit);

   //}


   //bool style::create_int(e_int eint, int i)
   //{

   //   if (userstyle()->m_mapInt.is_null())
   //   {

   //      userstyle()->m_mapInt = __new(::user::i32_map);

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


   ::user::enum_control_type style::get_control_type() const
   {

      return ::user::e_control_type_none;

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

               return ::color::color(0, 0, 0, 0);

            }

         }

      }

      return ::color::color();

   }





//void style::nextstyle(style_context * pcontext)
   //{

   //   if (::is_set(m_pgraphics) && ::is_set(m_pgraphics->m_puserinteraction))
   //   {

   //      m_pgraphics->m_puserinteraction->nextstyle(pcontext);

   //   }
   //   else
   //   {

   //      pcontext->m_papexcontext->pstyle.release();

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

   //         spuserstyle = __new(style(this));

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


   //style * style::userstyle()
   //{

   //   return m_pstyle;

   //}


   //style_context::style_context()
   //{


   //}


   //style_context::~style_context()
   //{


   //}


      style::~style()
      {

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

      //   ::color::color color;
      //   color.set_rgb(psession->get_default_color(COLOR_HIGHLIGHT));

      //   class ::color::color colorHover(color);
      //   colorHover.hls_rate(0.0, 0.3, 0.0);

      //   class ::color::color colorPress(color);
      //   colorPress.hls_rate(0.0, 0.7, 0.0);

      //   m_eschema = schema_default;

      //   create_opaque_color(color_text, ::color_black);

      //}



      //bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, tab * ptab)
      //{

      //   return false;

      //}


      //bool style::_001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * pinteraction)
      //{

      //   return false;

      //}


      //void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText)
      //{

      //   psession->_001OnDefaultTabPaneDrawTitle(pane, ptab, pgraphics, rectangle, pbrushText);

      //}


      //bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab)
      //{

      //   return false;

      //}


      //   bool style::_001GetMainFrameTranslucency(::user::enum_translucency & etranslucency)
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


      //__pointer(::user::menu_interaction) style::create_menu_button(::user::style_pointer & pstyle, menu_item * pitem)
      //{

      //   return psession->create_menu_button(pstyle, pitem);

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

      //   psession->prepare_menu_button(pgraphics, pitem);

      //   return true;

      //}


      //bool style::create_color(e_color ecolor, ::color32_t color32)
      //{

      //   if (userstyle()->m_mapColor.is_null())
      //   {

      //      userstyle()->m_mapColor = __new(color_map);

      //   }

      //   (*userstyle()->m_mapColor)[ecolor] = color32;

      //   return true;

      //}


     // ::write_text::font_pointer style::create_point_font(e_font efont, const ::string & pszFamilyName, double dFontSize, int iFontWeight)
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

     //    pfont->create_point_font(pszFamilyName, dFontSize, iFontWeight);

     //    return font;

     // }


      //bool style::create_opaque_color(e_color ecolor, ::color32_t color32)
      //{

      //   if (!create_color(ecolor, opaque_color(color32)))
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


      //bool style::create_session_default_opaque_color(e_color eusercolor, u64 u)
      //{

      //   if (!create_opaque_color(eusercolor, psession->get_default_color(u)))
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //bool style::create_session_default_color(e_color eusercolor, byte bAlpha, u64 u)
      //{

      //   if (!create_color(eusercolor, alpha_color(bAlpha, psession->get_default_color(u))))
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //bool style::create_translucency(enum_element eelement, enum_translucency etranslucency)
      //{

      //   if (userstyle()->m_mapTranslucency.is_null())
      //   {

      //      userstyle()->m_mapTranslucency = __new(translucency_map);

      //   }

      //   (*userstyle()->m_mapTranslucency)[eelement] = etranslucency;

      //   return true;

      //}


      //bool style::create_flag(enum_flag eflag, bool bFlag)
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


      //bool style::create_pixel_rect(e_rect erect, rectangle_f64 r)
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


      //bool style::create_point_rect(e_rect erect, rectangle_f64 r)
      //{

      //   return create_rect(erect, r, ::draw2d::unit_point);

      //}


      //bool style::create_rect_coord(e_rect erect, double l, double t, double r, double b, ::draw2d::enum_unit eunit)
      //{

      //   if (userstyle()->m_mapRect.is_null())
      //   {

      //      userstyle()->m_mapRect = __new(rect_map);

      //   }

      //   (*userstyle()->m_mapRect)[erect].set_rect_coord(l, t, r, b, eunit);

      //   return true;

      //}


      //bool style::create_rect_dim(e_rect erect, double l, double t, double w, double h, ::draw2d::enum_unit eunit)
      //{

      //   return create_rect_coord(erect, l, t, l + w, t + h, eunit);

      //}


      //bool style::create_rect(e_rect erect, ::rectangle_f64 rectangle, ::draw2d::enum_unit eunit)
      //{

      //   return create_rect_coord(erect, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, eunit);

      //}


      //bool style::create_int(e_int eint, int i)
      //{

      //   if (userstyle()->m_mapInt.is_null())
      //   {

      //      userstyle()->m_mapInt = __new(::user::i32_map);

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



      //void style::nextstyle(style_context * pcontext)
      //{

      //   if (::is_set(m_pgraphics) && ::is_set(m_pgraphics->m_puserinteraction))
      //   {

      //      m_pgraphics->m_puserinteraction->nextstyle(pcontext);

      //   }
      //   else
      //   {

      //      pcontext->m_papexcontext->pstyle.release();

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

      //         spuserstyle = __new(style(this));

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






} // namespace axis



