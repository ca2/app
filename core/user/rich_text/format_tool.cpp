#include "framework.h"
#include "format_tool.h"
#include "format.h"
#include "selection.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/content.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font_list.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/user/user/frame_interaction.h"
#include "core/user/user/color_selector_popup.h"
#include "core/user/user/font_list.h"
#include "core/user/user/font_combo_box.h"
#include "aura/message/user.h"
#include "aura/user/user/button.h"


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


      void format_tool::initialize(::particle * pparticle)
      {

         //auto estatus = 

         ::user::tool_window::initialize(pparticle);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 

         //ødefer_construct_new(m_pformathost);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //auto pformat = øcreate_new < ::user::rich_text::format >();

         //if (!pformat)
         //{

         //   return pformat;

         //}

         //estatus = 

         //pformat->initialize_user_rich_text_format(m_pformathost);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //m_pformathost->add(pformat);

         //return estatus;

      }


      ::user::enum_translucency format_tool::get_translucency(::user::style * pstyle)
      {

         return ::user::e_translucency_present;

      }


      void format_tool::install_message_routing(::channel * psender)
      {

         ::user::tool_window::install_message_routing(psender);

         USER_MESSAGE_LINK(::user::e_message_create, psender, this, &format_tool::on_message_create);

      }


      void format_tool::on_message_create(::message::message * pmessage)
      {

         ::pointer<::message::create>pcreate(pmessage);

         pcreate->previous();

         if (pcreate->m_bRet)
         {

            return;

         }
         int iControl = 0;
         øconstruct(m_pbuttonBold);
         iControl++;
         øconstruct(m_pbuttonItalic);
         iControl++;
         øconstruct(m_pbuttonUnderline);
         iControl++;
         øconstruct(m_pcomboFamily);
         iControl++;
         øconstruct(m_pcomboSize);
         iControl++;
         øconstruct(m_pbuttonForeground);
         iControl++;
         øconstruct(m_pbuttonBackground);
         iControl++;
         øconstruct(m_pbuttonSubscript);
         iControl++;
         øconstruct(m_pbuttonSuperscript);
         iControl++;
         øconstruct(m_pbuttonLineHeight);
         iControl++;
         øconstruct(m_pbuttonAlignLeft);
         iControl++;
         øconstruct(m_pbuttonAlignCenter);
         iControl++;
         øconstruct(m_pbuttonAlignRight);
         iControl++;

         m_pbuttonBold->create_control(this, "font_bold");
         m_pbuttonBold->LoadBitmaps("matter://fontformat/bold-text-option12.png");
         m_pbuttonBold->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonBold->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonBold->add_handler(this);

         m_pbuttonItalic->create_control(this, "font_italic");
         m_pbuttonItalic->LoadBitmaps("matter://fontformat/italicize-text12.png");
         m_pbuttonItalic->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonItalic->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonItalic->add_handler(this);

         m_pbuttonUnderline->create_control(this, "font_underline");
         m_pbuttonUnderline->LoadBitmaps("matter://fontformat/underline-text-option12.png");
         m_pbuttonUnderline->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonUnderline->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonUnderline->add_handler(this);

         m_pcomboFamily->create_control(this, "combo_family");
         //auto pfont = m_pcomboFamily->create_point_font(::user::font_plain_edit, pnode->font_name(e_font_sans_ui), 9.0);
         //pfont->m_ewritetextrendering = ::write_text::e_rendering_clear_type_grid_fit;
         //m_pcomboFamily->create_color(::user::color_text, argb(255, 80, 80, 80));
         //m_pcomboFamily->create_color(::user::color_background, argb(255, 255, 255, 255));
         m_pcomboFamily->add_handler(this);

         m_pcomboSize->create_control(this, "combo_size");
         //pfont = m_pcomboSize->create_point_font(::user::font_plain_edit, pnode->font_name(e_font_sans_ui), 9.0);
         //pfont->m_ewritetextrendering = ::write_text::e_rendering_clear_type_grid_fit;
         //m_pcomboSize->create_color(::user::color_text, argb(255, 80, 80, 80));
         //m_pcomboSize->create_color(::user::color_background, argb(255, 255, 255, 255));
         //::double_rectangle r(2, 2, 2, 2);
         //create_rect(::user::rect_edit_padding, r, ::draw2d::e_unit_pixel);
         //bm_pcomboSize->m_edatamode = ::user::combo_box::data_mode_string;
         m_pcomboSize->m_bEdit = true;
         m_pcomboSize->add_item("6", "6");
         m_pcomboSize->add_item("6.5", "6.5");
         m_pcomboSize->add_item("7", "7");
         m_pcomboSize->add_item("7.5", "7.5");
         m_pcomboSize->add_item("8", "8");
         m_pcomboSize->add_item("8.5", "8.5");
         m_pcomboSize->add_item("9", "9");
         m_pcomboSize->add_item("10", "10");
         m_pcomboSize->add_item("11", "11");
         m_pcomboSize->add_item("12", "12");
         m_pcomboSize->add_item("14", "14");
         m_pcomboSize->add_item("16", "16");
         m_pcomboSize->add_item("18", "18");
         m_pcomboSize->add_item("21", "21");
         m_pcomboSize->add_item("24", "24");
         m_pcomboSize->add_item("32", "32");
         m_pcomboSize->add_item("36", "36");
         m_pcomboSize->add_item("42", "42");
         m_pcomboSize->add_item("48", "48");
         m_pcomboSize->add_item("56", "56");
         m_pcomboSize->add_item("64", "64");
         m_pcomboSize->add_item("72", "72");
         m_pcomboSize->add_item("144", "144");
         m_pcomboSize->add_handler(this);

         m_pbuttonForeground->create_control(this, "font_foreground");
         m_pbuttonForeground->LoadBitmaps("matter://fontformat/font-foreground12.png");
         m_pbuttonForeground->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonForeground->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonForeground->add_handler(this);


         m_pbuttonBackground->create_control(this, "font_background");
         m_pbuttonBackground->LoadBitmaps("matter://fontformat/text-background12.png");
         m_pbuttonBackground->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonBackground->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonBackground->add_handler(this);


         m_pbuttonSubscript->create_control(this, "font_subscript");
         m_pbuttonSubscript->LoadBitmaps("matter://fontformat/x2-symbol-of-a-letter-and-a-number-subscript12.png");
         m_pbuttonSubscript->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonSubscript->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonSubscript->add_handler(this);

         m_pbuttonSuperscript->create_control(this, "font_superscript");
         m_pbuttonSuperscript->LoadBitmaps("matter://fontformat/superscript-text-formatting12.png");
         m_pbuttonSuperscript->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonSuperscript->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonSuperscript->add_handler(this);

         m_pbuttonAlignLeft->create_control(this, "e_align_left");
         m_pbuttonAlignLeft->LoadBitmaps("matter://fontformat/align-to-left12.png");
         m_pbuttonAlignLeft->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonAlignLeft->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonAlignLeft->add_handler(this);

         m_pbuttonAlignCenter->create_control(this, "e_align_center");
         m_pbuttonAlignCenter->LoadBitmaps("matter://fontformat/center-text-alignment12.png");
         m_pbuttonAlignCenter->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonAlignCenter->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonAlignCenter->add_handler(this);

         m_pbuttonAlignRight->create_control(this, "e_align_right");
         m_pbuttonAlignRight->LoadBitmaps("matter://fontformat/align-to-right12.png");
         m_pbuttonAlignRight->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);
         m_pbuttonAlignRight->m_flagNonClient.erase(::user::interaction::e_non_client_background);
         m_pbuttonAlignRight->add_handler(this);

         //create_color(::user::color_background, argb(255, 200, 200, 200));
         //create_color(::user::color_button_background, argb(0, 0, 0, 0));
         //create_color(::user::color_button_background_hover, argb(255, 180, 180, 180));
         //create_color(::user::color_button_background_press, argb(255, 160, 160, 160));

      }


      void format_tool::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         auto pbrushBk = øcreate < ::draw2d::brush >();

         auto rectangleX = this->rectangle();

         pbrushBk->CreateLinearGradientBrush(rectangleX.top_left(), rectangleX.bottom_left(),
                                         argb(255, 230, 230, 230), argb(255, 200, 200, 200));

         pgraphics->fill_rectangle(rectangleX, pbrushBk);

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


      void format_tool::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         if (ptopic->m_actioncontext.is_user_source())
         {

            if (ptopic->id() == ::id_click)
            {

               if (ptopic->user_interaction()->id() == "font_bold")
               {

                  m_pbuttonBold->toggle_check(::e_source_user);

                  m_eattribute |= ::user::rich_text::e_attribute_bold;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "font_italic")
               {

                  m_pbuttonItalic->toggle_check(::e_source_user);

                  m_eattribute |= ::user::rich_text::e_attribute_italic;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "font_underline")
               {

                  m_pbuttonUnderline->toggle_check(::e_source_user);

                  m_eattribute |= ::user::rich_text::e_attribute_underline;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "font_subscript")
               {

                  m_pbuttonSubscript->toggle_check(::e_source_user);

                  if (m_pbuttonSubscript->echeck() == ::e_check_checked)
                  {

                     m_pbuttonSuperscript->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  m_eattribute |= ::user::rich_text::e_attribute_script;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "font_superscript")
               {

                  m_pbuttonSuperscript->toggle_check(::e_source_user);

                  if (m_pbuttonSuperscript->echeck() == ::e_check_checked)
                  {

                     m_pbuttonSubscript->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  m_eattribute |= ::user::rich_text::e_attribute_script;

                  update_data(true);

                  ptopic->Ret();

               }

               else if (ptopic->user_interaction()->id() == "e_align_left")
               {

                  m_pbuttonAlignLeft->set_check(::e_check_checked, ::e_source_user);

                  if (m_pbuttonAlignCenter->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignCenter->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  if (m_pbuttonAlignRight->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignRight->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  m_eattribute |= ::user::rich_text::e_attribute_align;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "e_align_center")
               {

                  m_pbuttonAlignCenter->set_check(::e_check_checked, ::e_source_user);

                  if (m_pbuttonAlignLeft->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignLeft->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  if (m_pbuttonAlignRight->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignRight->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  m_eattribute |= ::user::rich_text::e_attribute_align;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "e_align_right")
               {

                  m_pbuttonAlignRight->set_check(::e_check_checked, ::e_source_user);

                  if (m_pbuttonAlignLeft->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignLeft->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  if (m_pbuttonAlignCenter->echeck() == ::e_check_checked)
                  {

                     m_pbuttonAlignCenter->set_check(::e_check_unchecked, ::e_source_sync);

                  }

                  m_eattribute |= ::user::rich_text::e_attribute_align;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "font_foreground")
               {

                  ::int_point pointShowPopup(ptopic->user_interaction()->left(), ptopic->user_interaction()->bottom());

                  ptopic->user_interaction()->get_parent()->client_to_screen()(pointShowPopup);

                  //fork([this, pointShowPopup]()
                  //{

                  auto elapsedLostFocus = m_pcolorselectorpopupForeground ?
                     m_pcolorselectorpopupForeground->m_timeLostFocus.elapsed() :
                     0_s;

                  if (m_pcolorselectorpopupForeground &&
                     (m_pcolorselectorpopupForeground->is_this_visible()
                        || elapsedLostFocus < 300_ms))
                  {

                     //information() << "hiding m_pcolorselectorpopupForeground";

                     //information() << "hiding m_pcolorselectorpopupForeground visible : " << m_pcolorselectorpopupForeground->is_this_visible();

                     //information() << "hiding m_pcolorselectorpopupForeground elapsedLostFocus (ms) : " << elapsedLostFocus.floating_millisecond();

                     m_pcolorselectorpopupForeground->hide_popup();

                  }
                  else
                  {

                     auto set_color_and_show = [this, pointShowPopup]()
                     {

                        m_pcolorselectorpopupForeground->set_sel_color(m_hlsForeground);

                        m_pcolorselectorpopupForeground->show_popup(pointShowPopup);

                     };

                     if (!m_pcolorselectorpopupForeground)
                     {

                        m_pcolorselectorpopupForeground = øcreate_new < ::user::color_selector_popup >();

                        m_pcolorselectorpopupForeground->m_bCompact = true;

                        m_pcolorselectorpopupForeground->m_callbackHls = [this](auto hls, bool bFinal)
                           {

                              this->m_hlsForeground = hls;

                              this->m_eattribute |= ::user::rich_text::e_attribute_foreground;

                              this->update_data(true);

                              if (bFinal)
                              {

                                 m_pcolorselectorpopupForeground->hide_popup();

                              }

                           };

                        m_pcolorselectorpopupForeground->m_procedureOnAfterCreate = set_color_and_show;

                        m_pcolorselectorpopupForeground->set_owner(this);

                        //m_pcolorselectorpopupForeground->create_host(::e_parallelization_asynchronous);

                        m_pcolorselectorpopupForeground->create_window();

                     }
                     else
                     {

                        m_pcolorselectorpopupForeground->user_post(set_color_and_show);

                     }


                  }

                  //});

                  ptopic->Ret();

               }

            }
            else if (ptopic->id() == ::id_after_change_text)
            {

               //if (ptopic->user_interaction()->id() == "combo_size")
               //{

               //   m_eattribute |= ::user::rich_text::e_attribute_size;

               //   update_data(true);

               //   ptopic->Ret();

               //}

            }
            else if (ptopic->id() == ::id_enter_key)
            {

               if (ptopic->user_interaction()->id() == "combo_size")
               {

                  m_eattribute |= ::user::rich_text::e_attribute_size;

                  update_data(true);

                  ptopic->Ret();

               }

            }
            else if (ptopic->id() == ::id_after_change_cur_sel)
            {

               if (ptopic->user_interaction()->id() == "combo_family")
               {

                  m_eattribute |= ::user::rich_text::e_attribute_family;

                  update_data(true);

                  ptopic->Ret();

               }
               else if (ptopic->user_interaction()->id() == "combo_size")
               {

                  m_eattribute |= ::user::rich_text::e_attribute_size;

                  update_data(true);

                  ptopic->Ret();

               }

            }

         }

         if (ptopic->m_bRet)
         {

            return;

         }

         return ::user::tool_window::handle(ptopic, phandlercontext);

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

            iRound = (int)dFontSize;

            m_pformat->m_dFontSize = (double)iRound;

            strEdit = ::as_string(iRound);

         }
         else if (dRound >= 0.75)
         {

            iRound = (int)dFontSize;

            iRound++;

            m_pformat->m_dFontSize = (double)iRound;

            strEdit = ::as_string(iRound);

         }
         else
         {

            iDouble = (int)((dFontSize + 0.25) * 2.0);

            m_pformat->m_dFontSize = ((double)iRound) / 2.0;

            strEdit = ::as_string(iDouble / 2) + ".5";

         }

         m_pcomboSize->set_text(strEdit, ::e_source_sync);

      }


      void format_tool::update_data(bool bSaveAndValidate)
      {

         if (!m_pformat)
         {

            throw ::exception(error_failed);

         }

         if (bSaveAndValidate)
         {

            if (m_pcomboFamily->main_content().m_pitemCurrent.is_set())
            {

               auto pcombolistbox = m_pcomboFamily->m_plistbox;

               auto pitemCurrent = m_pcomboFamily->main_content().m_pitemCurrent;

               ::pointer<::user::font_list>pfontlist = pcombolistbox;

               auto pfontenumerationitema = pfontlist->m_pfontlist->m_pfontenumerationitema;

               auto pfontenumerationitem = pfontenumerationitema->element_at(pitemCurrent->m_item.m_iItem);

               m_pformat->m_strFontFamily = pfontenumerationitem->m_strName;

            }

            string str;

            m_pcomboSize->get_text(str);

            set_font_size(strtod(str, nullptr));

            m_pformat->m_bUnderline = m_pbuttonUnderline->echeck() == ::e_check_checked;

            m_pformat->m_bItalic = m_pbuttonItalic->echeck() == ::e_check_checked;

            m_pformat->m_bBold = m_pbuttonBold->echeck() == ::e_check_checked;

            if (m_pbuttonSuperscript->echeck() == ::e_check_checked)
            {

               m_pformat->m_escript = ::user::rich_text::e_script_superscript;

            }
            else if (m_pbuttonSubscript->echeck() == ::e_check_checked)
            {

               m_pformat->m_escript = ::user::rich_text::e_script_subscript;

            }
            else
            {

               m_pformat->m_escript = ::user::rich_text::e_script_normal;

            }

            if (m_pbuttonAlignRight->echeck() == ::e_check_checked)
            {

               m_pformat->m_ealign = e_align_right;

            }
            else if (m_pbuttonAlignCenter->echeck() == ::e_check_checked)
            {

               m_pformat->m_ealign = e_align_center;

            }
            else
            {

               m_pformat->m_ealign = e_align_left;

            }

            if (m_pcolorselectorpopupForeground)
            {

               m_pformat->m_colorForeground = m_pcolorselectorpopupForeground->m_hls;

            }

            m_pformat->m_bUpdated = false;

            auto ptopic = create_topic(::id_after_change_cur_sel);

            ptopic->m_puserelement = this;

            //topic.id() = id();

            route(ptopic);

         }
         else
         {

            auto pcombolistbox = m_pcomboFamily->m_plistbox;

            ::pointer<::user::font_list>pfontlist = pcombolistbox;

            ::collection::index iIndex = pfontlist->m_pfontlist->find_name(m_pformat->m_strFontFamily);

            m_pcomboFamily->set_current_item_by_index(iIndex, ::e_source_sync);

            set_font_size(m_pformat->m_dFontSize);

            m_pbuttonBold->set_check(m_pformat->m_bBold ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);
            m_pbuttonItalic->set_check(m_pformat->m_bItalic ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);
            m_pbuttonUnderline->set_check(m_pformat->m_bUnderline ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);
            bool bLeft = m_pformat->m_ealign == e_align_left;
            bool bCenter = m_pformat->m_ealign == e_align_center;
            bool bRight = m_pformat->m_ealign == e_align_right;

            m_pbuttonAlignLeft->set_check(bLeft, ::e_source_sync);
            m_pbuttonAlignCenter->set_check(bCenter, ::e_source_sync);
            m_pbuttonAlignRight->set_check(bRight, ::e_source_sync);

            m_hlsForeground = m_pformat->m_colorForeground.get_hls();
            m_hlsBackground = m_pformat->m_colorBackground.get_hls();

         }

      }


      void format_tool::show_for_ui(::user::interaction * puserinteraction, ::user::rich_text::selection * pselection)
      {

         information() << "show_for_ui";

         m_pformat = pselection->get_selection_common_format();

         ::int_rectangle rectangleOther;

         puserinteraction->window_rectangle(rectangleOther);

         auto puserinteractionTopLevel = puserinteraction->top_level();

         set_owner(puserinteractionTopLevel);

         set_tool_window();

         add_handler(puserinteraction);

         ::int_rectangle rectangle(rectangleOther.top_left() - ::int_size(0, 48), ::int_size(100, 100));

         ::int_rectangle rectangleWindow;

         window_rectangle(rectangleWindow);

         ::int_rectangle rectangleRequest;

         rectangleRequest.left = rectangle.left - 32;

         rectangleRequest.top = rectangle.top - 32;

         rectangleRequest.right = rectangleRequest.left + 400;

         rectangleRequest.bottom = rectangleRequest.top + 32;

         information() << "show_for_ui place(rectangleRequest) : " << rectangleRequest;

         add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

         place(rectangleRequest);

         enable_window();

         order(e_zorder_top_most);

         display(e_display_normal, { ::user::e_activation_no_activate });

         set_need_redraw();

         post_redraw();

      }


   } // namespace rich_text


} // namespace user


