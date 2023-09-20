#include "framework.h"
#include "combo_box.h"
#include "list_box.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/_constant.h"
#include "acme/user/user/content.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"


namespace user
{


   combo_box::combo_box()
   {

      user_combo_box_common_construct();

   }


   void combo_box::user_combo_box_common_construct()
   {

      m_econtroltype                         = e_control_type_combo_box;
      m_typeListBox                          = ::type < ::user::list_box >();
      m_estyle                               = style_simply;
      m_bEdit                                = true;
      m_edatamode                            = data_mode_opaque;
      m_bMultiLine                           = false;
      m_bDefaultParentMouseMessageHandling   = false;

   }


   combo_box::~combo_box()
   {

      if(m_plistbox.is_set())
      {

         if(m_plistbox->is_window())
         {

            m_plistbox->destroy_window();

         }

      }

   }


   void combo_box::install_message_routing(::channel * pchannel)
   {

      //if(m_bEdit)
      {

         ::user::plain_edit::install_message_routing(pchannel);

      }
      //else
      {

        // ::user::interaction::install_message_routing(pchannel);

      }

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &combo_box::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &combo_box::on_message_mouse_leave);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &combo_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &combo_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&combo_box::on_message_key_down);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&combo_box::on_message_key_up);
      //MESSAGE_LINK(e_message_set_focus,pchannel,this,&combo_box::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &combo_box::on_message_kill_focus);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &combo_box::on_message_show_window);
      MESSAGE_LINK(e_message_reposition, pchannel, this, &combo_box::on_message_move);

   }


   void combo_box::_001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics)
   {

      string strText;

      if (m_bEdit)
      {

         _001GetText(strText);

      }
      else
      {

         _001GetListText(current_item()->m_item.m_iItem, strText);

      }

      auto rectangleClinet = this->rectangle();
      //::user::e_::color::color colorText = color_text;

      ::color::color colorText = ::color::black;

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::rgba(192, 192, 192, 255);

      //      }
      //      else
      //      {

      //         colorText = ::rgba(255, 255, 255, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorText = ::rgba(80, 80, 80, 255);;

      //      }
      //      else
      //      {

      //         colorText = ::rgba(80, 80, 80, 255);;

      //      }

      //   }

      //}

      //if(!select_text_color(pgraphics, colorText))
      //{

         pgraphics->set_text_color(colorText);

      //}

      ::rectangle_i32 rectangleText;

      get_element_rectangle(rectangleText, e_element_text);

      pgraphics->set_font(this, ::e_element_none);

      ::e_align ealign = e_align_left_center;

      pgraphics->draw_text(strText, rectangleText, ealign);

   }


   enum_input_type combo_box::preferred_input_type()
   {

      if (m_bEdit)
      {

         return e_input_type_text;

      }
      else
      {

         return e_input_type_list;

      }

   }


   void combo_box::get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa)
   {

      ::rectangle_i32 rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      i32 cx = rectangleDropDown.width() / 3;

      i32 cy = cx * 2 / 3;

      ::point_i32 pointCenter = rectangleDropDown.center();

      pointa.add(pointCenter.x() - cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x() + cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x(), pointCenter.y() + cy / 2);

   }


   void combo_box::_001OnDrawCombo(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      auto pbrush = __create < ::draw2d::brush > ();

      //if(m_bEdit)
      {

         ::user::plain_edit::_001OnDraw(pgraphics);

      }
//      else
//      {
//
//         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//         _001OnDrawStaticText(pgraphics);
//
//      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::rectangle_i32 rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      ::rectangle_i32 rectangleDropIn(rectangleDropDown);

      //::user::e_::color::color colorDropDown = color_button_background_disabled;
      ::color::color colorDropDown = ::color::gray;

      //if (m_pdrawcontext != nullptr)
      //{

      //   if (m_pdrawcontext->is_control_selected())
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::rgba(80, 80, 180, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::rgba(100, 100, 200, 255);

      //      }

      //   }
      //   else
      //   {

      //      if (m_pdrawcontext->is_control_hover())
      //      {

      //         colorDropDown = ::rgba(200, 200, 250, 255);

      //      }
      //      else
      //      {

      //         colorDropDown = ::rgba(192, 192, 192, 255);

      //      }

      //   }

      //}
      //else
      {

         bool bHasFocus = has_keyboard_focus();

         if(bHasFocus)
         {

            if (::is_set(m_pitemHover))
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }

         }
         else
         {

            if (::is_set(m_pitemHover))
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }
            else
            {

               colorDropDown = ::rgba(200, 200, 250, 255);

            }

         }

      }

      ::color::color color(colorDropDown);

      color.hls_rate(0.0, 0.5, 0.1);

      pbrush->create_solid(color);

      pgraphics->set(pbrush);

      pgraphics->fill_rectangle(rectangleDropIn);

      auto ppath = __create < ::draw2d::path > ();

      point_f64_array pointa;

      get_simple_drop_down_open_arrow_polygon(pointa);

      pbrush->create_solid(argb(210, 0, 0, 0));

      pgraphics->set(pbrush);

      pgraphics->fill_polygon(pointa);

      //pgraphics->fill_rectangle({0, 0, 200, 100}, color::green);

   }


   ::write_text::font_pointer combo_box::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      //if (pstyle)
      //{

      //   if (pstyle->m_pfontCombo)
      //   {

      //      return pstyle->m_pfontCombo;

      //   }
      //   else if (pstyle->m_pfont)
      //   {

      //      return pstyle->m_pfont;

      //   }

      //}

      return ::user::interaction::get_font(pstyle, eelement, estate);

   }


   void combo_box::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::plain_edit::_000OnDraw(pgraphics);

   }


   void combo_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      _001OnDrawCombo(pgraphics);

   }


   void combo_box::_001GetText(string & str)
   {

      ::user::plain_edit::_001GetText(str);

//      if(m_bEdit)
//      {
//
//         if(!m_pitemCurrent.is_set())
//         {
//
//            ::user::plain_edit::_001GetText(str);
//
//         }
//         else
//         {
//
//            _001GetListText(m_pitemCurrent, str);
//
//         }
//
//      }
//      else
//      {
//
//         if(!m_pitemCurrent.is_set())
//         {
//
//            str = m_strText;
//
//         }
//         else
//         {
//
//            _001GetListText(m_pitemCurrent, str);
//
//         }
//
//      }

   }


   void combo_box::_001SetText(const ::string & str, const ::action_context & context)
   {

      //if(m_bEdit)
      //{

         ::user::plain_edit::_001SetText(str, context);

//      }
//      else
//      {
//
//         m_strText = str;
//
//         auto psystem = acmesystem()->m_paurasystem;
//
//         auto pdraw2d = psystem->draw2d();
//
//         auto pgraphics = pdraw2d->create_memory_graphics();
//
//         plain_edit_on_after_change_text(pgraphics, context);
//
//      }

   }


   index combo_box::_001GetListCount() const
   {

      return m_plistbox->_001GetListCount();

   }


   bool combo_box::get_element_rectangle(::rectangle_i32 & rectangle, enum_element eelement)

   {

      if(eelement == e_element_text)
      {

         eelement = e_element_combo_edit;

      }

      return interaction::get_element_rectangle(rectangle, eelement);

   }


   ::item_pointer combo_box::on_hit_test(const ::point_i32& point, ::user::e_zorder ezorder)
   {

      ::rectangle_i32 rectangleElement;

      if(get_element_rectangle(rectangleElement, e_element_drop_down))
      {

         if (rectangleElement.contains(point))
         {

            auto pitem = __new(::item(e_element_drop_down));

            auto puseritem = user_item(pitem);
            
            puseritem->m_rectangle = rectangleElement;

            return pitem;

         }

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.contains(point))
      {

         auto pitem = __new(::item(e_element_text));

         auto puseritem = user_item(pitem);
            
         puseritem->m_rectangle = rectangleElement;

         return pitem;

      }
      
      auto pitemNone = __new(::item(e_element_none));
      
      return pitemNone;

   }


   void combo_box::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (!pshowwindow->m_bShow)
      {

         if (m_plistbox.is_set() && m_plistbox->is_window())
         {

            m_plistbox->post_message(MESSAGE_CLOSE);

         }

      }

   }


   void combo_box::on_message_move(::message::message * pmessage)
   {

      if (is_drop_down())
      {

         ::rectangle_i32 rectangleWindow;

         window_rectangle(rectangleWindow, ::user::e_layout_sketch);

         m_plistbox->on_drop_down(rectangleWindow, m_sizeFull);

      }

   }


   void combo_box::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_down)
      {

         if(!is_drop_down())
         {

            _001ShowDropDown();

         }

      }

   }


   void combo_box::on_message_key_up(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   bool combo_box::plain_edit_is_enabled()
   {

      return m_bEdit;

   }


   void combo_box::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      if (is_window_enabled())
      {

         if (!m_bEdit || (::is_set(m_pitemHover) && m_pitemHover->m_item.m_eelement == e_element_drop_down))
         {

            auto pwindowing = windowing();

            auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

            user_mouse_set_cursor(pmouse, pcursor);

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_message_mouse_leave(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      m_pitemHover = nullptr;

      set_need_redraw();

   }


   void combo_box::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_window_enabled())
      {

         return;

      }

      auto pitemHit = hit_test(pmouse, e_zorder_any);

      if (::is_set(pitemHit) && (!m_bEdit || pitemHit->m_item.m_eelement == e_element_drop_down))
      {

         class ::time timeLastVisibilityChangeElapsed;

         if (m_plistbox.is_set())
         {

            timeLastVisibilityChangeElapsed = m_plistbox->m_timeLastVisibilityChange.elapsed();

         }

         if (m_plistbox.is_null() || timeLastVisibilityChangeElapsed > 300_ms)
         {

            _001ToggleDropDown();

         }
         else if (!m_plistbox->const_layout().sketch().is_screen_visible())
         {

            //information("test");

         }

         pmouse->m_bRet = true;

      }

   }


   void combo_box::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         auto pitemHit = hit_test(pmouse, e_zorder_any);

         if (::is_set(pitemHit) && (!m_bEdit || pitemHit->m_item.m_eelement == e_element_drop_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void combo_box::on_set_keyboard_focus()
   {

   }


   void combo_box::on_kill_keyboard_focus()
   {

      if (m_plistbox != nullptr)
      {

         m_plistbox->post_message(MESSAGE_CLOSE);

      }

   }


   void combo_box::_001ToggleDropDown()
   {

      defer_create_list_box();

      if (m_plistbox.is_set())
      {

         _001ShowDropDown(!m_plistbox->is_window_visible(::user::e_layout_sketch));

      }

   }


   void combo_box::_001ShowDropDown(bool bShow)
   {

      if (m_plistbox)
      {

         m_plistbox->m_bPendingKillFocusHiding = false;

      }

      if(bShow)
      {

         m_timeShowComboList.Now();

         defer_create_list_box();

         auto psession = get_session();

         psession->on_show_user_input_popup(m_plistbox);

         auto psystem = acmesystem()->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(this);

         m_plistbox->query_full_size(pgraphics, &m_sizeFull);

         ::rectangle_i32 rectangleWindow;

         window_rectangle(rectangleWindow, ::user::e_layout_sketch);

         m_plistbox->on_drop_down(rectangleWindow, m_sizeFull);

      }
      else
      {

         if(m_plistbox.is_set())
         {

            m_plistbox->hide();

            m_plistbox->set_need_redraw();

            m_plistbox->post_redraw();

         }

         set_keyboard_focus();

         set_active_window();

      }

   }


   void combo_box::defer_create_list_box()
   {

      if(!m_plistbox)
      {

         auto plistbox = __id_create < list_box >(m_typeListBox);

         m_plistbox = plistbox;

         if(m_plistbox == nullptr)
         {

            throw ::exception(error_resource);

         }

         m_plistbox->m_pcombo = this;

      }

      auto rectangleX = this->rectangle();

      m_plistbox->m_dItemHeight = minimum(24, rectangleX.height());

   }


   void combo_box::set_current_item(::item * pitem, const ::action_context & actioncontext)
   {

      if (::is_same_item(current_item(), pitem))
      {

         return;

      }

      if (m_plistbox)
      {

         m_plistbox->main_content().m_pitemCurrent = pitem;

      }

      ::user::plain_edit::set_current_item(pitem, actioncontext);

      if (!is_window())
      {

         //return ::success;

         return;

      }

      string strItem;

      _001GetListText(pitem->m_item.m_iItem, strItem);

      _001SetText(strItem, actioncontext);

      //return ::success;

   }


   void combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_bEdit)
      {

         ::user::plain_edit::on_layout(pgraphics);

      }


      /*      ::write_text::font_pointer fontxyz(e_create);

            auto rectangleX = this->rectangle();

            fontxyz->m_dFontSize = rectangleX.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::e_unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/



   }


   void combo_box::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext)
   {

      if(actioncontext.is_user_source())
      {

         string str;

         //if(m_bEdit)
         //{

         // ::user::plain_edit::_001GetText(str);
         ::user::plain_edit::_001GetText(str);

         //      }
         //      else
         //      {
         //
         //         str = m_strText;
         //
         //      }

         auto itemCurrent = _001FindListText(str);

         set_current_item(__new(::item(e_element_item, itemCurrent)), actioncontext);

      }

   }


   void combo_box::handle(::topic * ptopic, ::context * pcontext)
   {

      ////if(m_bEdit)
      //{

      //   ::user::plain_edit::handle(ptopic, pcontext);

      //}

      if (ptopic->m_atom == ::id_after_change_cur_sel)
      {

         auto puserinteraction = ptopic->user_interaction();

         if (puserinteraction == m_plistbox)
         {

            set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

            _001ShowDropDown(false);

            ptopic->Ret();

            set_need_redraw();

            post_redraw();

            keyboard_set_focus_next();

            return;

         }

      }

   }


   //bool combo_box::create_interaction(::user::interaction * puiParent, const ::atom & atom)
   //{

   //   if (!::user::plain_edit::create_interaction(puiParent, atom))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


//#ifdef WINDOWS_DESKTOP
//   //Derived class is responsible for implementing these handlers
//   //for owner/self draw controls (except for the optional DeleteItem)
//   void combo_box::DrawItem(LPDRAWITEMSTRUCT)
//   { ASSERT(false); }
//   void combo_box::MeasureItem(LPMEASUREITEMSTRUCT)
//   { ASSERT(false); }
//   i32 combo_box::CompareItem(LPCOMPAREITEMSTRUCT)
//   { ASSERT(false); return 0; }
//   void combo_box::DeleteItem(LPDELETEITEMSTRUCT)
//   { /* default to nothing */ }
//#endif

//   bool combo_box::OnChildNotify(::user::message * pusermessage)
//   {
//
//#ifdef WINDOWS_DESKTOP
//      switch (pusermessage->m_atom)
//      {
//      case WM_DRAWITEM:
//#ifdef WINDOWSEX
//         DrawItem((LPDRAWITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case e_message_measure_item:
//#ifdef WINDOWSEX
//         MeasureItem((LPMEASUREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case WM_COMPAREITEM:
//#ifdef WINODWSEX
//         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case WM_DELETEITEM:
//#ifdef WINODWSEX
//         DeleteItem((LPDELETEITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      default:
//         return ::user::interaction::OnChildNotify(pusermessage);
//      }
//#endif
//
//      return true;
//   }
//

   void combo_box::GetLBText(index nIndex, string & rString)
   {

      ASSERT(is_window());

      GetLBText(nIndex, rString.get_buffer(GetLBTextLen(nIndex)));

      rString.release_buffer();

   }


   //::count combo_box::get_count()
   // { ASSERT(is_window()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index combo_box::current_index()
   // { ASSERT(is_window()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index combo_box::set_current_item(index nSelect)
   // { ASSERT(is_window()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool combo_box::GetEditSel(strsize & nStartChar, strsize & nEndChar)
   {
      /*      ASSERT(is_window()); u32 dw = u32(send_message( CB_GETEDITSEL, 0, 0));
            nStartChar = LOWORD(dw);
            nEndChar = LOWORD(dw);*/
      return true;
   }
   bool combo_box::LimitText(strsize nMaxChars)
   {
      //ASSERT(is_window());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != false;
      return true;
   }

   bool combo_box::SetEditSel(strsize nStartChar, strsize nEndChar)
   {
      //ASSERT(is_window());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != false;
      return true;
   }

   uptr combo_box::GetItemData(index nIndex)
   {

      //ASSERT(is_window());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   index combo_box::SetItemData(index nIndex, uptr dwItemData)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

      return -1;

   }

   void * combo_box::GetItemDataPtr(index nIndex)
   {

      //ASSERT(is_window()); return (LPVOID)GetItemData(nIndex);

      return nullptr;

   }

   index combo_box::SetItemDataPtr(index nIndex, void * pData)
   {

      //ASSERT(is_window());

      //return SetItemData(nIndex, (uptr)(LPVOID)pData);

      return -1;

   }

   index combo_box::GetLBText(index nIndex, char * pszText)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)pszText);


      return -1;

   }

   strsize combo_box::GetLBTextLen(index nIndex)
   {

      //ASSERT(is_window());

      //return (strsize)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }


   void combo_box::ShowDropDown(bool bShowIt)
   {

      _001ShowDropDown(bShowIt);

   }


   index combo_box::delete_string(index nIndex)
   {

      auto iIndex = m_plistbox->delete_string(nIndex);

      return iIndex;

   }


   index combo_box::insert_string(index nIndex, const ::string & pszString)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);


      return -1;

   }


   void combo_box::reset_content()
   {

      if (!m_plistbox)
      {

         return;

      }

      m_plistbox->reset_content();

   }


   index combo_box::Dir(index attr, const ::string & pszWildCard)
   {

//      ASSERT(is_window());

//      return (index)send_message( CB_DIR, attr, (LPARAM)pszWildCard);


      return -1;

   }


   void combo_box::clear()
   {

      //ASSERT(is_window());

      //send_message(WM_CLEAR, 0, 0);

   }


   void combo_boxcopy()
   {

      //ASSERT(is_window());

      //send_message(WM_COPY, 0, 0);

   }


   void combo_box::Cut()
   {

      //ASSERT(is_window());

      //send_message( WM_CUT, 0, 0);

   }


   void combo_box::Paste()
   {

      //ASSERT(is_window());

      //send_message( WM_PASTE, 0, 0);

   }


   i32 combo_box::SetItemHeight(index nIndex, ::u32 cyItemHeight)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }


   i32 combo_box::GetItemHeight(index nIndex)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }


   index combo_box::FindStringExact(index nIndexStart, const ::string & pszFind)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)pszFind);


      return -1;

   }


   i32 combo_box::SetExtendedUI(bool bExtended)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }


   bool combo_box::GetExtendedUI()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }


   void combo_box::GetDroppedControlRect(::rectangle_i32 * prectangle)
   {

      //ASSERT(is_window());

      //send_message( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)prectangle);


   }


   bool combo_box::GetDroppedState()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETDROPPEDSTATE, 0, 0L) != 0;

      return false;

   }


//   LCID combo_box::GetLocale()
//   {
//
//      //ASSERT(is_window());
//
//      //return (LCID)send_message( CB_GETLOCALE, 0, 0);
//
//      return -1; // everywhere
//
//   }
//
//   LCID combo_box::SetLocale(LCID nNewLocale)
//   {
//
//      //ASSERT(is_window());
//
//      //return (LCID)send_message( CB_SETLOCALE, (WPARAM)nNewLocale, 0);
//
//      return nNewLocale; // set where it is
//
//   }


   index combo_box::GetTopIndex()
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }


   index combo_box::SetTopIndex(index nIndex)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }


   ::count combo_box::InitStorage(::count nItems, ::u32 nBytes)
   {

      //ASSERT(is_window());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void combo_box::SetHorizontalExtent(::u32 nExtent)
   {

      //ASSERT(is_window());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }


   ::u32 combo_box::GetHorizontalExtent()
   {

      //ASSERT(is_window());

      //return (::u32)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }


   i32 combo_box::SetDroppedWidth(::u32 nWidth)
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

      return -1;

   }


   i32 combo_box::GetDroppedWidth()
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_GETDROPPEDWIDTH, 0, 0);

      return -1;

   }


   bool combo_box::_001GetListText(index iSel,string & str) const
   {

      return m_plistbox->_001GetListText(iSel, str);

   }


   index combo_box::_001FindListText(const ::string & str) const
   {

      return m_plistbox->_001FindListText(str);

   }


   index combo_box::add_string(const ::string & pszString,uptr dwItemData)
   {

      synchronous_lock synchronouslock(this->synchronization());

      ASSERT(m_edatamode == data_mode_opaque);

      if (m_edatamode != data_mode_opaque)
      {

         return -1;

      }

      defer_create_list_box();

      return m_plistbox->add_string(pszString, dwItemData);

   }


   index combo_box::add_string(const ::string & pszString, const ::string & strValue)
   {

      ASSERT(m_edatamode == data_mode_string);

      if (m_edatamode != data_mode_string)
      {

         return -1;

      }

      defer_create_list_box();

      auto iIndex = m_plistbox->add_string(pszString, strValue);

      return iIndex;

   }


   bool combo_box::has_action_hover()
   {

      return ::is_set(m_pitemHover) || is_drop_down();

   }


   bool combo_box::has_text_input()
   {

      return m_bEdit && ::user::plain_edit::has_text_input();

   }


   void combo_box::set_current_item_by_string_value(const ::string & strValue, const ::action_context & actioncontext)
   {

      m_plistbox->set_current_item_by_string_value(strValue, actioncontext);

   }


   void combo_box::set_current_item_by_index(::index iIndex, const ::action_context & action_context)
   {

      m_plistbox->set_current_item_by_index(iIndex, action_context);

   }


   void combo_box::set_current_item_by_data(uptr u, const ::action_context & context)
   {

      m_plistbox->set_current_item_by_data(u, context);

   }


   string combo_box::get_current_item_string_value()
   {

      if (::is_null(m_plistbox))
      {

         return {};

      }

      return m_plistbox->get_current_item_string_value();

   }


   bool combo_box::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible(e_layout_sketch);

   }


   bool combo_box::is_drop_down()
   {

      return m_plistbox != nullptr && m_plistbox->is_window_visible(e_layout_sketch);

   }


} // namespace user



