#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "core/user/rich_text/_rich_text.h"


namespace user
{


   namespace rich_text
   {

      
   format_tool::format_tool()
   {

   }


   format_tool::~format_tool()
   {

   }


   e_status format_tool::initialize(::object * pobject)
   {

      auto estatus = ::user::tool_window::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __defer_construct_new(m_pformata);

      if (!estatus)
      {

         return estatus;

      }

      auto pformat = __create_new < ::user::rich_text::format > ();

      if (!pformat)
      {

         return pformat;

      }

      estatus = pformat->initialize_user_rich_text_format(m_pformata);

      if (!estatus)
      {

         return estatus;

      }

      m_pformata->add(pformat);

      return estatus;

   }




   ::user::enum_translucency format_tool::get_translucency(::user::style* pstyle) const
   {

      return ::user::e_translucency_present;

   }


   void format_tool::install_message_routing(::channel * psender)
   {

      ::user::tool_window::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &format_tool::on_message_create);

   }


   void format_tool::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
      {

         return;

      }
      int iControl = 0;
      auto estatus = __compose(m_pbuttonBold);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonItalic);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonUnderline);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pcomboFamily);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pcomboSize);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonForeground);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonBackground);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonSubscript);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonSuperscript);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonLineHeight);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignLeft);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignCenter);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }
      estatus = __compose(m_pbuttonAlignRight);
      iControl++; if (!estatus) { pcreate->failed("Failed to create control for format_tool (" + __string(iControl) + ")"); return; }

      m_pbuttonBold->create_control(this, "font_bold");
      m_pbuttonBold->LoadBitmaps("matter://fontformat/bold-text-option12.png");
      m_pbuttonBold->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonBold->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonItalic->create_control(this, "font_italic");
      m_pbuttonItalic->LoadBitmaps("matter://fontformat/italicize-text12.png");
      m_pbuttonItalic->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonItalic->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonUnderline->create_control(this, "font_underline");
      m_pbuttonUnderline->LoadBitmaps("matter://fontformat/underline-text-option12.png");
      m_pbuttonUnderline->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonUnderline->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pcomboFamily->create_control(this, "combo_family");
      //auto pfont = m_pcomboFamily->create_point_font(::user::font_plain_edit, pnode->font_name(e_font_sans_ui), 9.0);
      //pfont->m_ewritetextrendering = ::write_text::e_rendering_clear_type_grid_fit;
      //m_pcomboFamily->create_color(::user::color_text, argb(255, 80, 80, 80));
      //m_pcomboFamily->create_color(::user::color_background, argb(255, 255, 255, 255));

      m_pcomboSize->create_control(this, "combo_size");
      //pfont = m_pcomboSize->create_point_font(::user::font_plain_edit, pnode->font_name(e_font_sans_ui), 9.0);
      //pfont->m_ewritetextrendering = ::write_text::e_rendering_clear_type_grid_fit;
      //m_pcomboSize->create_color(::user::color_text, argb(255, 80, 80, 80));
      //m_pcomboSize->create_color(::user::color_background, argb(255, 255, 255, 255));
      //::rectangle_f64 r(2, 2, 2, 2);
      //create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);


      m_pcomboSize->m_edatamode = ::user::combo_box::data_mode_string;

      m_pcomboSize->m_bEdit = true;

      m_pcomboSize->add_string("6", "6");
      m_pcomboSize->add_string("6.5", "6.5");
      m_pcomboSize->add_string("7", "7");
      m_pcomboSize->add_string("7.5", "7.5");
      m_pcomboSize->add_string("8", "8");
      m_pcomboSize->add_string("8.5", "8.5");
      m_pcomboSize->add_string("9", "9");
      m_pcomboSize->add_string("10", "10");
      m_pcomboSize->add_string("11", "11");
      m_pcomboSize->add_string("12", "12");
      m_pcomboSize->add_string("14", "14");
      m_pcomboSize->add_string("16", "16");
      m_pcomboSize->add_string("18", "18");
      m_pcomboSize->add_string("21", "21");
      m_pcomboSize->add_string("24", "24");
      m_pcomboSize->add_string("32", "32");
      m_pcomboSize->add_string("36", "36");
      m_pcomboSize->add_string("42", "42");
      m_pcomboSize->add_string("48", "48");
      m_pcomboSize->add_string("56", "56");
      m_pcomboSize->add_string("64", "64");
      m_pcomboSize->add_string("72", "72");
      m_pcomboSize->add_string("144", "144");

      m_pbuttonForeground->create_control(this, "font_foreground");
      m_pbuttonForeground->LoadBitmaps("matter://fontformat/font-foreground12.png");

      m_pbuttonForeground->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonForeground->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonBackground->create_control(this, "font_background");
      m_pbuttonBackground->LoadBitmaps("matter://fontformat/text-background12.png");
      m_pbuttonBackground->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonBackground->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonSubscript->create_control(this, "font_subscript");
      m_pbuttonSubscript->LoadBitmaps("matter://fontformat/x2-symbol-of-a-letter-and-a-number-subscript12.png");
      m_pbuttonSubscript->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonSubscript->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonSuperscript->create_control(this, "font_superscript");
      m_pbuttonSuperscript->LoadBitmaps("matter://fontformat/superscript-text-formatting12.png");
      m_pbuttonSuperscript->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonSuperscript->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonAlignLeft->create_control(this, "e_align_left");
      m_pbuttonAlignLeft->LoadBitmaps("matter://fontformat/align-to-left12.png");
      m_pbuttonAlignLeft->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignLeft->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonAlignCenter->create_control(this, "e_align_center");
      m_pbuttonAlignCenter->LoadBitmaps("matter://fontformat/center-text-alignment12.png");
      m_pbuttonAlignCenter->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignCenter->m_flagNonClient.erase(::user::interaction::non_client_background);

      m_pbuttonAlignRight->create_control(this, "e_align_right");
      m_pbuttonAlignRight->LoadBitmaps("matter://fontformat/align-to-right12.png");
      m_pbuttonAlignRight->m_flagNonClient.erase(::user::interaction::non_client_focus_rect);
      m_pbuttonAlignRight->m_flagNonClient.erase(::user::interaction::non_client_background);

      //create_color(::user::color_background, argb(255, 200, 200, 200));
      //create_color(::user::color_button_background, argb(0, 0, 0, 0));
      //create_color(::user::color_button_background_hover, argb(255, 180, 180, 180));
      //create_color(::user::color_button_background_press, argb(255, 160, 160, 160));

   }


   void format_tool::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pbrushBk = __create < ::draw2d::brush > ();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      pbrushBk->CreateLinearGradientBrush(rectangleClient.top_left(), rectangleClient.bottom_left(),
                                      argb(255, 230, 230, 230), argb(255, 200, 200, 200));

      pgraphics->fill_rectangle(rectangleClient, pbrushBk);

   }


   void format_tool::on_layout(::draw2d::graphics_pointer & pgraphics)
   {
      
      //throw "create line layout";

      m_pbuttonBold->display_child(5, 5, 20, 20);
      m_pbuttonItalic->display_child(25, 5, 20, 20);
      m_pbuttonUnderline->display_child(45, 5, 20, 20);
      m_pcomboFamily->display_child(70, 5, 120, 20);
      m_pcomboSize->display_child(195, 5, 40, 20);

      int x = 245;
      //throw "create line layout";
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


   bool format_tool::is_showing_for_ui(::user::interaction * pinteraction)
   {

      return get_owner() == pinteraction;

   }




   void format_tool::handle(::subject * psubject, ::context * pcontext)
   {

      if (psubject->m_actioncontext.is_user_source())
      {

         if (psubject->m_id == ::e_subject_click)
         {

            if (psubject->user_interaction()->m_id == "font_bold")
            {

               m_pbuttonBold->_001ToggleCheck(::e_source_user);

               m_eattribute |= ::user::rich_text::attribute_bold;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "font_italic")
            {

               m_pbuttonItalic->_001ToggleCheck(::e_source_user);

               m_eattribute |= ::user::rich_text::attribute_italic;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "font_underline")
            {

               m_pbuttonUnderline->_001ToggleCheck(::e_source_user);

               m_eattribute |= ::user::rich_text::attribute_underline;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "font_subscript")
            {

               m_pbuttonSubscript->_001ToggleCheck(::e_source_user);

               if (m_pbuttonSubscript->echeck() == ::check_checked)
               {

                  m_pbuttonSuperscript->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_script;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "font_superscript")
            {

               m_pbuttonSuperscript->_001ToggleCheck(::e_source_user);

               if (m_pbuttonSuperscript->echeck() == ::check_checked)
               {

                  m_pbuttonSubscript->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_script;

               update_data(true);

               psubject->Ret();

            }

            else if (psubject->user_interaction()->m_id == "e_align_left")
            {

               m_pbuttonAlignLeft->_001SetCheck(::check_checked, ::e_source_user);

               if (m_pbuttonAlignCenter->echeck() == ::check_checked)
               {

                  m_pbuttonAlignCenter->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               if (m_pbuttonAlignRight->echeck() == ::check_checked)
               {

                  m_pbuttonAlignRight->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "e_align_center")
            {

               m_pbuttonAlignCenter->_001SetCheck(::check_checked, ::e_source_user);

               if (m_pbuttonAlignLeft->echeck() == ::check_checked)
               {

                  m_pbuttonAlignLeft->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               if (m_pbuttonAlignRight->echeck() == ::check_checked)
               {

                  m_pbuttonAlignRight->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "e_align_right")
            {

               m_pbuttonAlignRight->_001SetCheck(::check_checked, ::e_source_user);

               if (m_pbuttonAlignLeft->echeck() == ::check_checked)
               {

                  m_pbuttonAlignLeft->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               if (m_pbuttonAlignCenter->echeck() == ::check_checked)
               {

                  m_pbuttonAlignCenter->_001SetCheck(::check_unchecked, ::e_source_sync);

               }

               m_eattribute |= ::user::rich_text::attribute_align;

               update_data(true);

               psubject->Ret();

            }
            else if (psubject->user_interaction()->m_id == "font_foreground")
            {

               fork([&]()
               {

               });

            }

         }
         else if (psubject->m_id == ::e_subject_after_change_text)
         {

            if (psubject->user_interaction()->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               psubject->Ret();

            }

         }
         else if (psubject->m_id == ::e_subject_enter_key)
         {

            if (psubject->user_interaction()->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               psubject->Ret();

            }

         }
         else if (psubject->m_id == ::e_subject_after_change_cur_sel)
         {

            if (psubject->user_interaction()->m_id == "combo_family")
            {

               m_eattribute |= ::user::rich_text::attribute_family;

               update_data(true);

               psubject->Ret();


            }
            else if (psubject->user_interaction()->m_id == "combo_size")
            {

               m_eattribute |= ::user::rich_text::attribute_size;

               update_data(true);

               psubject->Ret();

            }

         }

      }

      if (psubject->m_bRet)
      {

         return;

      }

      return ::user::tool_window::handle(psubject, pcontext);

   }


   void format_tool::set_font_size(double dFontSize)
   {

      dFontSize = maximum(6.0, minimum(1440.0, dFontSize));

      double dRound = dFontSize - (double)(int)dFontSize;

      int iRound = -1;

      int iDouble = -1;

      string strEdit;

      if (dRound < 0.25)
      {

         iRound = (int) dFontSize;

         m_pformata->first()->m_dFontSize = (double)iRound;

         strEdit = __string(iRound);

      }
      else if (dRound >= 0.75)
      {

         iRound = (int) dFontSize;

         iRound++;

         m_pformata->first()->m_dFontSize = (double)iRound;

         strEdit = __string(iRound);

      }
      else
      {

         iDouble = (int) ((dFontSize + 0.25) * 2.0);

         m_pformata->first()->m_dFontSize = ((double)iRound) / 2.0;

         strEdit = __string(iDouble / 2) + ".5";

      }

      m_pcomboSize->_001SetText(strEdit, ::e_source_sync);

   }


   bool format_tool::update_data(bool bSaveAndValidate)
   {

      if (m_pformata->is_empty() || !m_pformata->first())
      {

         return false;

      }

      synchronous_lock synchronouslock(m_pformata->first()->mutex());

      if (bSaveAndValidate)
      {

         if (m_pcomboFamily->m_itemCurrent.is_set())
         {

            auto pcombolistbox = m_pcomboFamily->m_plistbox;

            auto itemCurrent = m_pcomboFamily->m_itemCurrent;

            __pointer(::user::font_list) pfontlist = pcombolistbox;

            auto pfontenumerationitema = pfontlist->m_pfontlist->m_pfontenumerationitema;

            auto pfontenumerationitem = pfontenumerationitema->element_at(itemCurrent);

            m_pformata->first()->m_strFontFamily = pfontenumerationitem->m_strName;

         }

         string str;

         m_pcomboSize->_001GetText(str);

         set_font_size(strtod(str, nullptr));

         m_pformata->first()->m_bUnderline = m_pbuttonUnderline->echeck() == ::check_checked;
         m_pformata->first()->m_bItalic = m_pbuttonItalic->echeck() == ::check_checked;
         m_pformata->first()->m_bBold = m_pbuttonBold->echeck() == ::check_checked;
         if (m_pbuttonSuperscript->echeck() == ::check_checked)
         {

            m_pformata->first()->m_escript = ::user::rich_text::script_superscript;

         }
         else if (m_pbuttonSubscript->echeck() == ::check_checked)
         {

            m_pformata->first()->m_escript = ::user::rich_text::script_subscript;

         }
         else
         {

            m_pformata->first()->m_escript = ::user::rich_text::script_normal;

         }
         if (m_pbuttonAlignRight->echeck() == ::check_checked)
         {

            m_pformata->first()->m_ealign = e_align_right;

         }
         else if (m_pbuttonAlignCenter->echeck() == ::check_checked)
         {

            m_pformata->first()->m_ealign = e_align_center;

         }
         else
         {

            m_pformata->first()->m_ealign = e_align_left;

         }

         m_pformata->first()->m_bUpdated = false;

         ::subject subject;

         subject.m_id = ::e_subject_after_change_cur_sel;

         subject.m_puserelement = this;

         //subject.m_id = m_id;

         route(&subject);

      }
      else
      {

         auto pcombolistbox = m_pcomboFamily->m_plistbox;

         __pointer(::user::font_list) pfontlist = pcombolistbox;

         index iIndex = pfontlist->m_pfontlist->find_name(m_pformata->first()->m_strFontFamily);

         m_pcomboFamily->set_current_item(iIndex, ::e_source_sync);

         set_font_size(m_pformata->first()->m_dFontSize);

         m_pbuttonBold->_001SetCheck(m_pformata->first()->m_bBold ? ::check_checked : ::check_unchecked, ::e_source_sync);
         m_pbuttonItalic->_001SetCheck(m_pformata->first()->m_bItalic ? ::check_checked : ::check_unchecked, ::e_source_sync);
         m_pbuttonUnderline->_001SetCheck(m_pformata->first()->m_bUnderline ? ::check_checked : ::check_unchecked, ::e_source_sync);

         bool bLeft = m_pformata->first()->m_ealign == e_align_left;
         bool bCenter = m_pformata->first()->m_ealign == e_align_center;
         bool bRight = m_pformata->first()->m_ealign == e_align_right;

         m_pbuttonAlignLeft->_001SetCheck(bLeft, ::e_source_sync);
         m_pbuttonAlignCenter->_001SetCheck(bCenter, ::e_source_sync);
         m_pbuttonAlignRight->_001SetCheck(bRight, ::e_source_sync);

      }

      return true;

   }


   void format_tool::show_for_ui(::user::interaction* pinteraction)
   {

      ::rectangle_i32 rectangleOther;
      
      pinteraction->get_window_rect(rectangleOther);

      set_owner(pinteraction);

      ::rectangle_i32 rectangle(rectangleOther.top_left() - ::size_i32(0, 48), ::size_i32(100, 100));

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow);

      ::rectangle_i32 rectangleRequest;

      rectangleRequest.left = rectangle.left - 32;
      rectangleRequest.top = rectangle.top - 32;
      rectangleRequest.right = rectangleRequest.left + 400;
      rectangleRequest.bottom = rectangleRequest.top + 32;

      enable_window();

      place(rectangleRequest);

      order(e_zorder_top_most);

      display(e_display_normal, e_activation_no_activate);

      set_need_redraw();

      post_redraw();

   }

//} // namespace user
//




//::userex::format_tool * simple_frame_window::format_tool(bool bCreate)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   __pointer(::userex::format_tool) pfontformattool = m_ptoolwindowFont;
//
//   if (pfontformattool.is_null() && bCreate)
//   {
//
//      __construct_new < ::userex::format_tool> (pfontformattool);
//
//      m_ptoolwindowFont = pfontformattool;
//
//      synchronouslock.unlock();
//
//      //pfontformattool->m_ewindowflag |= e_window_flag_embedded_prodevian;
//      //pfontformattool->m_ewindowflag |= e_window_flag_satellite_window;
//
//      ::user::system createstruct(WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
//      //::user::system createstruct;
//
//      pfontformattool->create_window_ex(createstruct, nullptr, "textformat_sys_format_tool");
//
//   }
//
//   return pfontformattool;
//
//}


   } // namespace rich_text


} // namespace user


