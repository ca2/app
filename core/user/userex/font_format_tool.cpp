#include "framework.h"
#include "core/user/userex/_userex.h"
#include "core/user/rich_text/_rich_text.h"
#include "font_format_tool.h"


#ifdef WINDOWS_DESKTOP
#include <Commdlg.h>
#endif


namespace userex
{


   font_format_tool::font_format_tool()
   {

      m_formata.add(__new(::user::rich_text::format(&m_formata)));

   }


   font_format_tool::~font_format_tool()
   {

   }


   ::user::e_translucency font_format_tool::get_translucency(::user::style* pstyle) const
   {

      return ::user::translucency_present;

   }


   void font_format_tool::install_message_routing(::channel * psender)
   {

      ::user::tool_window::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &::userex::font_format_tool::_001OnCreate);

   }


   void font_format_tool::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
      {

         return;

      }
      int iControl = 0;
      auto estatus = __compose(m_pbuttonBold);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonItalic);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonUnderline);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pcomboFamily);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pcomboSize);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonForeground);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonBackground);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonSubscript);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonSuperscript);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonLineHeight);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignLeft);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignCenter);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignRight);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for font_format_tool (" + __str(iControl) + ")"); return; }

      m_pbuttonBold->create_window(this, "font_bold");
      m_pbuttonBold->LoadBitmaps("matter://fontformat/bold-text-option12.png");
      m_pbuttonBold->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonBold->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonItalic->create_window(this, "font_italic");
      m_pbuttonItalic->LoadBitmaps("matter://fontformat/italicize-text12.png");
      m_pbuttonItalic->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonItalic->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonUnderline->create_window(this, "font_underline");
      m_pbuttonUnderline->LoadBitmaps("matter://fontformat/underline-text-option12.png");
      m_pbuttonUnderline->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonUnderline->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pcomboFamily->create_window(this, "combo_family");
      //auto pfont = m_pcomboFamily->create_point_font(::user::font_plain_edit, "Segoe UI", 9.0);
      //pfont->m_etextrenderinghint = ::draw2d::text_rendering_hint_clear_type_grid_fit;
      //m_pcomboFamily->create_color(::user::color_text, ARGB(255, 80, 80, 80));
      //m_pcomboFamily->create_color(::user::color_background, ARGB(255, 255, 255, 255));

      m_pcomboSize->create_window(this, "combo_size");
      //pfont = m_pcomboSize->create_point_font(::user::font_plain_edit, "Segoe UI", 9.0);
      //pfont->m_etextrenderinghint = ::draw2d::text_rendering_hint_clear_type_grid_fit;
      //m_pcomboSize->create_color(::user::color_text, ARGB(255, 80, 80, 80));
      //m_pcomboSize->create_color(::user::color_background, ARGB(255, 255, 255, 255));
      //::rectd r(2, 2, 2, 2);
      //create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


      m_pcomboSize->m_edatamode = ::user::combo_box::data_mode_string;

      m_pcomboSize->m_bEdit = true;

      m_pcomboSize->AddString("6", "6");
      m_pcomboSize->AddString("6.5", "6.5");
      m_pcomboSize->AddString("7", "7");
      m_pcomboSize->AddString("7.5", "7.5");
      m_pcomboSize->AddString("8", "8");
      m_pcomboSize->AddString("8.5", "8.5");
      m_pcomboSize->AddString("9", "9");
      m_pcomboSize->AddString("10", "10");
      m_pcomboSize->AddString("11", "11");
      m_pcomboSize->AddString("12", "12");
      m_pcomboSize->AddString("14", "14");
      m_pcomboSize->AddString("16", "16");
      m_pcomboSize->AddString("18", "18");
      m_pcomboSize->AddString("21", "21");
      m_pcomboSize->AddString("24", "24");
      m_pcomboSize->AddString("32", "32");
      m_pcomboSize->AddString("36", "36");
      m_pcomboSize->AddString("42", "42");
      m_pcomboSize->AddString("48", "48");
      m_pcomboSize->AddString("56", "56");
      m_pcomboSize->AddString("64", "64");
      m_pcomboSize->AddString("72", "72");
      m_pcomboSize->AddString("144", "144");

      m_pbuttonForeground->create_window(this, "font_foreground");
      m_pbuttonForeground->LoadBitmaps("matter://fontformat/font-foreground12.png");

      m_pbuttonForeground->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonForeground->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonBackground->create_window(this, "font_background");
      m_pbuttonBackground->LoadBitmaps("matter://fontformat/text-background12.png");
      m_pbuttonBackground->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonBackground->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonSubscript->create_window(this, "font_subscript");
      m_pbuttonSubscript->LoadBitmaps("matter://fontformat/x2-symbol-of-a-letter-and-a-number-subscript12.png");
      m_pbuttonSubscript->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonSubscript->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonSuperscript->create_window(this, "font_superscript");
      m_pbuttonSuperscript->LoadBitmaps("matter://fontformat/superscript-text-formatting12.png");
      m_pbuttonSuperscript->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonSuperscript->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonAlignLeft->create_window(this, "align_left");
      m_pbuttonAlignLeft->LoadBitmaps("matter://fontformat/align-to-left12.png");
      m_pbuttonAlignLeft->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignLeft->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonAlignCenter->create_window(this, "align_center");
      m_pbuttonAlignCenter->LoadBitmaps("matter://fontformat/center-text-alignment12.png");
      m_pbuttonAlignCenter->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignCenter->m_flagNonClient.remove(::user::interaction::non_client_background);

      m_pbuttonAlignRight->create_window(this, "align_right");
      m_pbuttonAlignRight->LoadBitmaps("matter://fontformat/align-to-right12.png");
      m_pbuttonAlignRight->m_flagNonClient.remove(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignRight->m_flagNonClient.remove(::user::interaction::non_client_background);

      //create_color(::user::color_background, ARGB(255, 200, 200, 200));
      //create_color(::user::color_button_background, ARGB(0, 0, 0, 0));
      //create_color(::user::color_button_background_hover, ARGB(255, 180, 180, 180));
      //create_color(::user::color_button_background_press, ARGB(255, 160, 160, 160));

   }


   void font_format_tool::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::brush_pointer brBk(e_create);

      ::rect rectClient;

      get_client_rect(rectClient);

      brBk->CreateLinearGradientBrush(rectClient.top_left(), rectClient.bottom_left(),
                                      ARGB(255, 230, 230, 230), ARGB(255, 200, 200, 200));

      pgraphics->fill_rect(rectClient, brBk);

   }


   void font_format_tool::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      m_pbuttonBold->display_child(5, 5, 20, 20);
      m_pbuttonItalic->display_child(25, 5, 20, 20);
      m_pbuttonUnderline->display_child(45, 5, 20, 20);
      m_pcomboFamily->display_child(70, 5, 120, 20);
      m_pcomboSize->display_child(195, 5, 40, 20);

      int x = 245;

      m_pbuttonForeground->display_child(x, 5, 20, 20);
      x += 20;
      m_pbuttonBackground->display_child(x, 5, 20, 20);
      x += 20;
      m_pbuttonSubscript->display_child(x, 5, 20, 20);
      x += 20;
      m_pbuttonSuperscript->display_child(x, 5, 20, 20);
      x += 20;

      x += 10;

      m_pbuttonAlignLeft->display_child(x, 5, 20, 20);
      x += 20;
      m_pbuttonAlignCenter->display_child(x, 5, 20, 20);
      x += 20;
      m_pbuttonAlignRight->display_child(x, 5, 20, 20);
      x += 20;

      //m_pbuttonItalic->
      //m_pbuttonUnderline->
      //m_pbuttonFamily->
      //m_pbuttonForeground->
      //m_pbuttonBackground->
      //m_pbuttonSubscript->
      //m_pbuttonSuperscript->
      //m_pbuttonLineHeight->


   }


   bool font_format_tool::is_showing_for_ui(::user::interaction * pinteraction)
   {

      return GetOwner() == pinteraction;

   }




   void font_format_tool::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_actioncontext.is_user_source())
      {

         if (pevent->m_eevent == ::user::event_button_clicked)
         {

            if (pevent->m_puie->m_id == "font_bold")
            {

               m_pbuttonBold->_001ToggleCheck(::source_user);

               m_eattribute |= ::user::rich_text::attribute_bold;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_italic")
            {

               m_pbuttonItalic->_001ToggleCheck(::source_user);

               m_eattribute |= ::user::rich_text::attribute_italic;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_underline")
            {

               m_pbuttonUnderline->_001ToggleCheck(::source_user);

               m_eattribute |= ::user::rich_text::attribute_underline;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_subscript")
            {

               m_pbuttonSubscript->_001ToggleCheck(::source_user);

               if (m_pbuttonSubscript->echeck() == ::check_checked)
               {

                  m_pbuttonSuperscript->_001SetCheck(::check_unchecked, ::source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_script;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_superscript")
            {

               m_pbuttonSuperscript->_001ToggleCheck(::source_user);

               if (m_pbuttonSuperscript->echeck() == ::check_checked)
               {

                  m_pbuttonSubscript->_001SetCheck(::check_unchecked, ::source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_script;

               update_data(true);

               pevent->Ret();

            }

            else if (pevent->m_puie->m_id == "align_left")
            {

               m_pbuttonAlignLeft->_001SetCheck(::check_checked, ::source_user);

               if (m_pbuttonAlignCenter->echeck() == ::check_checked)
               {

                  m_pbuttonAlignCenter->_001SetCheck(::check_unchecked, ::source_sync);

               }

               if (m_pbuttonAlignRight->echeck() == ::check_checked)
               {

                  m_pbuttonAlignRight->_001SetCheck(::check_unchecked, ::source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "align_center")
            {

               m_pbuttonAlignCenter->_001SetCheck(::check_checked, ::source_user);

               if (m_pbuttonAlignLeft->echeck() == ::check_checked)
               {

                  m_pbuttonAlignLeft->_001SetCheck(::check_unchecked, ::source_sync);

               }

               if (m_pbuttonAlignRight->echeck() == ::check_checked)
               {

                  m_pbuttonAlignRight->_001SetCheck(::check_unchecked, ::source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "align_right")
            {

               m_pbuttonAlignRight->_001SetCheck(::check_checked, ::source_user);

               if (m_pbuttonAlignLeft->echeck() == ::check_checked)
               {

                  m_pbuttonAlignLeft->_001SetCheck(::check_unchecked, ::source_sync);

               }

               if (m_pbuttonAlignCenter->echeck() == ::check_checked)
               {

                  m_pbuttonAlignCenter->_001SetCheck(::check_unchecked, ::source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               pevent->Ret();

            }
            else if (pevent->m_puie->m_id == "font_foreground")
            {

               fork([&]()
               {

#ifdef WINDOWS_DESKTOP
                  CHOOSECOLOR cc;
                  COLORREF crCustColors[16];

                  // init-int this array did not affect the mouse problem
                  // uint idx ;
                  // for (idx=0; idx<16; idx++) {
                  // crCustColors[idx] = RGB(idx, idx, idx) ;
                  // }

                  ZeroMemory(&cc, sizeof(cc));
                  cc.lStructSize = sizeof(CHOOSECOLOR);
                  cc.rgbResult = RGB(0, 0, 0);
                  cc.lpCustColors = crCustColors;

                  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                  cc.hwndOwner = get_safe_handle() ; // this hangs parent, as well as me

                  if (::ChooseColor(&cc))
                  {

                     m_eattribute |= ::user::rich_text::attribute_foreground;

                     m_formata[0]->m_crForeground = cc.rgbResult | (255 << 24);

                     update_data(true);

                  }
#endif
               });

            }

         }
         else if (pevent->m_eevent == ::user::event_after_change_text)
         {

            if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               pevent->Ret();

            }

         }
         else if (pevent->m_eevent == ::user::event_enter_key)
         {

            if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               pevent->Ret();

            }

         }
         else if (pevent->m_eevent == ::user::event_after_change_cur_sel)
         {

            if (pevent->m_puie->m_id == "combo_family")
            {

               m_eattribute |= ::user::rich_text::attribute_family;

               update_data(true);

               pevent->Ret();


            }
            else if (pevent->m_puie->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               pevent->Ret();

            }

         }

      }

      if (pevent->m_bRet)
      {

         return;

      }

      return ::user::tool_window::on_control_event(pevent);

   }


   void font_format_tool::set_font_size(double dFontSize)
   {

      dFontSize = MAX(6.0, MIN(1440.0, dFontSize));

      double dRound = dFontSize - (double)(int)dFontSize;

      int iRound = -1;

      int iDouble = -1;

      string strEdit;

      if (dRound < 0.25)
      {

         iRound = (int) dFontSize;

         m_formata[0]->m_dFontSize = (double)iRound;

         strEdit = __str(iRound);

      }
      else if (dRound >= 0.75)
      {

         iRound = (int) dFontSize;

         iRound++;

         m_formata[0]->m_dFontSize = (double)iRound;

         strEdit = __str(iRound);

      }
      else
      {

         iDouble = (int) ((dFontSize + 0.25) * 2.0);

         m_formata[0]->m_dFontSize = ((double)iRound) / 2.0;

         strEdit = __str(iDouble / 2) + ".5";

      }

      m_pcomboSize->_001SetText(strEdit, ::source_sync);

   }


   bool font_format_tool::update_data(bool bSaveAndValidate)
   {

      if (m_formata.isEmpty() || !m_formata[0])
      {

         return false;

      }

      sync_lock sl(m_formata[0]->mutex());

      if (bSaveAndValidate)
      {

         if (m_pcomboFamily->m_itemCurrent.is_set())
         {

            m_formata[0]->m_strFontFamily = m_pcomboFamily->m_plist.cast <::user::font_list>()->m_pfontlist->m_pitema->element_at(m_pcomboFamily->m_itemCurrent)->m_strName;

         }

         string str;

         m_pcomboSize->_001GetText(str);

         set_font_size(strtod(str, nullptr));

         m_formata[0]->m_bUnderline = m_pbuttonUnderline->echeck() == ::check_checked;
         m_formata[0]->m_bItalic = m_pbuttonItalic->echeck() == ::check_checked;
         m_formata[0]->m_bBold = m_pbuttonBold->echeck() == ::check_checked;
         if (m_pbuttonSuperscript->echeck() == ::check_checked)
         {

            m_formata[0]->m_escript = ::user::rich_text::script_superscript;

         }
         else if (m_pbuttonSubscript->echeck() == ::check_checked)
         {

            m_formata[0]->m_escript = ::user::rich_text::script_subscript;

         }
         else
         {

            m_formata[0]->m_escript = ::user::rich_text::script_normal;

         }
         if (m_pbuttonAlignRight->echeck() == ::check_checked)
         {

            m_formata[0]->m_ealign = align_right;

         }
         else if (m_pbuttonAlignCenter->echeck() == ::check_checked)
         {

            m_formata[0]->m_ealign = align_center;

         }
         else
         {

            m_formata[0]->m_ealign = align_left;

         }

         m_formata[0]->m_bUpdated = false;

         ::user::control_event ev;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_puie = this;

         ev.m_id = m_id;

         route_control_event(&ev);

      }
      else
      {

         index iIndex = m_pcomboFamily->m_plist.cast <::user::font_list>()->m_pfontlist->find_name(m_formata[0]->m_strFontFamily);

         m_pcomboFamily->set_current_item(iIndex, ::source_sync);

         set_font_size(m_formata[0]->m_dFontSize);

         m_pbuttonBold->_001SetCheck(m_formata[0]->m_bBold ? ::check_checked : ::check_unchecked, ::source_sync);
         m_pbuttonItalic->_001SetCheck(m_formata[0]->m_bItalic ? ::check_checked : ::check_unchecked, ::source_sync);
         m_pbuttonUnderline->_001SetCheck(m_formata[0]->m_bUnderline ? ::check_checked : ::check_unchecked, ::source_sync);

         bool bLeft = m_formata[0]->m_ealign == align_left;
         bool bCenter = m_formata[0]->m_ealign == align_center;
         bool bRight = m_formata[0]->m_ealign == align_right;

         m_pbuttonAlignLeft->_001SetCheck(bLeft, ::source_sync);
         m_pbuttonAlignCenter->_001SetCheck(bCenter, ::source_sync);
         m_pbuttonAlignRight->_001SetCheck(bRight, ::source_sync);

      }

      return true;

   }


   void font_format_tool::show_for_ui(::user::interaction* pinteraction)
   {

      ::rect rectOther;
      
      pinteraction->get_window_rect(rectOther);

      SetOwner(pinteraction);

      ::rect rect(rectOther.top_left() - ::size(0, 48), ::size(100, 100));

      ::rect rectWindow;

      get_window_rect(rectWindow);

      ::rect rectRequest;

      rectRequest.left = rect.left - 32;
      rectRequest.top = rect.top - 32;
      rectRequest.right = rectRequest.left + 400;
      rectRequest.bottom = rectRequest.top + 32;

      enable_window();

      place(rectRequest);

      order(zorder_top_most);

      display(display_normal, activation_no_activate);

      set_need_redraw();

      post_redraw();

   }

} // namespace user





//::userex::font_format_tool * simple_frame_window::font_format_tool(bool bCreate)
//{
//
//   sync_lock sl(mutex());
//
//   __pointer(::userex::font_format_tool) pfontformattool = m_ptoolwindowFont;
//
//   if (pfontformattool.is_null() && bCreate)
//   {
//
//      __construct_new < ::userex::font_format_tool> (pfontformattool);
//
//      m_ptoolwindowFont = pfontformattool;
//
//      sl.unlock();
//
//      //pfontformattool->m_ewindowflag |= window_flag_embedded_prodevian;
//      //pfontformattool->m_ewindowflag |= window_flag_satellite_window;
//
//      ::user::create_struct createstruct(WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
//      //::user::create_struct createstruct;
//
//      pfontformattool->create_window_ex(createstruct, nullptr, "textformat_sys_format_tool");
//
//   }
//
//   return pfontformattool;
//
//}
