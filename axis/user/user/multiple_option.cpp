#include "framework.h"
#include "multiple_option.h"
#include "list_box.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/geometry2d/_text_stream.h"
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


   multiple_option::multiple_option()
   {

      user_multiple_option_common_construct();

   }


   void multiple_option::user_multiple_option_common_construct()
   {

      m_econtroltype                         = e_control_type_multiple_option;
      m_bDefaultParentMouseMessageHandling   = false;

   }


   multiple_option::~multiple_option()
   {



   }


   ::pointer < ::particle > multiple_option::clone()
   {

      auto pmultipleoptionClone = m_pcontext->__create_new < multiple_option >();

      return pmultipleoptionClone;

   }


   void multiple_option::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &multiple_option::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &multiple_option::on_message_mouse_leave);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &multiple_option::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &multiple_option::on_message_left_button_up);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&multiple_option::on_message_key_down);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&multiple_option::on_message_key_up);
      //MESSAGE_LINK(e_message_set_focus,pchannel,this,&multiple_option::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &multiple_option::on_message_kill_focus);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &multiple_option::on_message_show_window);
      MESSAGE_LINK(e_message_reposition, pchannel, this, &multiple_option::on_message_move);

   }


   void multiple_option::_001OnDrawStaticText(::draw2d::graphics_pointer & pgraphics)
   {

      string strText;

      if (m_bEdit)
      {

         strText = as_text();

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


   enum_input_type multiple_option::preferred_input_type()
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


   void multiple_option::get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa)
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


   void multiple_option::_001OnDrawCombo(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      auto pbrush = __create < ::draw2d::brush > ();

      //if(m_bEdit)
      {

         ::user::interaction::_001OnDraw(pgraphics);

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


   bool multiple_option::should_show_keyboard_focus()
   {

      return has_keyboard_focus() || (m_plistbox && m_plistbox->should_show_keyboard_focus());

   }


   ::write_text::font_pointer multiple_option::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
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


   void multiple_option::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw(pgraphics);

   }


   void multiple_option::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      _001OnDrawCombo(pgraphics);

   }


   void multiple_option::_001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnNcPostDraw(pgraphics);

   }


//   void multiple_option::get_text(string & str)
//   {
//
//      ::user::interaction::get_text(str);
//
////      if(m_bEdit)
////      {
////
////         if(!m_pitemCurrent.is_set())
////         {
////
////            ::user::interaction::get_text(str);
////
////         }
////         else
////         {
////
////            _001GetListText(m_pitemCurrent, str);
////
////         }
////
////      }
////      else
////      {
////
////         if(!m_pitemCurrent.is_set())
////         {
////
////            str = m_strText;
////
////         }
////         else
////         {
////
////            _001GetListText(m_pitemCurrent, str);
////
////         }
////
////      }
//
//   }


//   void multiple_option::set_text(const ::string & str, const ::action_context & context)
//   {
//
//      //if(m_bEdit)
//      //{
//
//         ::user::interaction::set_text(str, context);
//
////      }
////      else
////      {
////
////         m_strText = str;
////
////         auto psystem = system()->m_paurasystem;
////
////         auto pdraw2d = psystem->draw2d();
////
////         auto pgraphics = pdraw2d->create_memory_graphics();
////
////         plain_edit_on_after_change_text(pgraphics, context);
////
////      }
//
//   }


   ::collection::index multiple_option::_001GetListCount() const
   {

      return m_plistbox->_001GetListCount();

   }


   bool multiple_option::get_element_rectangle(::rectangle_i32 & rectangle, enum_element eelement)

   {

      if(eelement == e_element_text)
      {

         eelement = e_element_combo_edit;

      }

      return interaction::get_element_rectangle(rectangle, eelement);

   }


   ::item_pointer multiple_option::on_hit_test(const ::point_i32& point, ::user::e_zorder ezorder)
   {

      ::rectangle_i32 rectangleElement;

      if(get_element_rectangle(rectangleElement, e_element_drop_down))
      {

         if (rectangleElement.contains(point))
         {

            auto pitem = __allocate< ::item >(e_element_drop_down);

            auto puseritem = user_item(pitem);
            
            puseritem->m_rectangle2 = rectangleElement;

            return pitem;

         }

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.contains(point))
      {

         auto pitem = __allocate< ::item >(e_element_text);

         auto puseritem = user_item(pitem);
            
         puseritem->m_rectangle2 = rectangleElement;

         return pitem;

      }
      
      auto pitemNone = __allocate< ::item >(e_element_none);
      
      return pitemNone;

   }


   void multiple_option::on_message_show_window(::message::message * pmessage)
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


   void multiple_option::on_message_move(::message::message * pmessage)
   {

      _on_reposition();

   }


   void multiple_option::on_reposition()
   {

      _on_reposition();

   }


   void multiple_option::_on_reposition()
   {

      if (is_drop_down())
      {

         ::rectangle_i32 rectangleWindow;

         window_rectangle(rectangleWindow, ::user::e_layout_sketch);

         m_plistbox->on_drop_down(rectangleWindow, m_sizeFull);

      }

   }


   void multiple_option::on_message_key_down(::message::message * pmessage)
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


   void multiple_option::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool multiple_option::plain_edit_is_enabled()
   {

      return m_bEdit;

   }


   void multiple_option::on_message_mouse_move(::message::message * pmessage)
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


   void multiple_option::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_pitemHover = nullptr;

      set_need_redraw();

   }


   void multiple_option::on_message_left_button_down(::message::message * pmessage)
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

         bool bDropDownListBoxShown = false;

         if (m_plistbox.is_null() || timeLastVisibilityChangeElapsed > 300_ms)
         {

            bDropDownListBoxShown = _001ToggleDropDown();

         }
         else if (!m_plistbox->const_layout().sketch().is_screen_visible())
         {

            //informationf("test");

         }

         if (!bDropDownListBoxShown)
         {

            set_keyboard_focus();

            set_active_window();

         }

         set_need_redraw();

         post_redraw();

         pmouse->m_bRet = true;

      }

   }


   void multiple_option::on_message_left_button_up(::message::message * pmessage)
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


   void multiple_option::on_set_keyboard_focus()
   {

      if(m_bEdit)
      {

         plain_edit::on_set_keyboard_focus();

      }

   }


   void multiple_option::on_kill_keyboard_focus()
   {

      if (::is_set(m_plistbox) && m_plistbox->is_window())
      {

         m_plistbox->post_message(MESSAGE_CLOSE);

      }

   }


   bool multiple_option::_001ToggleDropDown()
   {

      defer_create_list_box();

      if (m_plistbox.is_set())
      {

         if (_001ShowDropDown(!m_plistbox->is_window_visible(::user::e_layout_sketch)))
         {

            return true;

         }

      }

      return false;

   }


   bool multiple_option::_001ShowDropDown(bool bShow)
   {

      //if (m_plistbox)
      //{

      //   m_plistbox->m_bPendingKillFocusHiding = false;

      //}

      if(bShow)
      {

         m_timeShowComboList.Now();

         defer_create_list_box();

         auto psession = get_session();

         psession->on_show_user_input_popup(m_plistbox);

         auto psystem = system()->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pgraphics = pdraw2d->create_memory_graphics(this);

         m_plistbox->query_full_size(pgraphics, &m_sizeFull);

         ::rectangle_i32 rectangleWindow;

         window_rectangle(rectangleWindow, ::user::e_layout_sketch);

         information() << "plisbox->on_drop_down (a) : " << rectangleWindow;

         m_plistbox->on_drop_down(rectangleWindow, m_sizeFull);

         return true;

      }
      else
      {

         if(m_plistbox.is_set())
         {

            m_plistbox->hide();

//         m_plistbox->set_need_redraw();
//
//         m_plistbox->post_redraw();

         }

      }

      return false;

   }


   void multiple_option::defer_create_list_box()
   {

      if(!m_plistbox)
      {

         auto plistbox = __id_create(m_typeatomListBox);

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


   void multiple_option::set_current_item(::item * pitem, const ::action_context & actioncontext)
   {

      if (::is_same_item(current_item(), pitem))
      {

         return;

      }

      if (m_plistbox)
      {

         m_plistbox->main_content().m_pitemCurrent = pitem;

      }

      ::user::interaction::set_current_item(pitem, actioncontext);

      if (!is_window())
      {

         //return ::success;

         return;

      }

      string strItem;

      if (::is_set(pitem))
      {

         _001GetListText(pitem->m_item.m_iItem, strItem);

      }

      set_text(strItem, actioncontext);

      //return ::success;

   }


   void multiple_option::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_bEdit)
      {

         ::user::interaction::on_layout(pgraphics);

      }


      /*      ::write_text::font_pointer fontxyz(e_create);

            auto rectangleX = this->rectangle();

            fontxyz->m_dFontSize = rectangleX.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::e_unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/



   }


   void multiple_option::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext)
   {

      if(actioncontext.is_user_source())
      {

         string str;

         //if(m_bEdit)
         //{

         // ::user::interaction::get_text(str);
         str = as_text();

         //      }
         //      else
         //      {
         //
         //         str = m_strText;
         //
         //      }

         auto itemCurrent = _001FindListText(str);

         set_current_item(__allocate< ::item >(e_element_item, itemCurrent), actioncontext);

      }

   }


   void multiple_option::handle(::topic * ptopic, ::context * pcontext)
   {

      ////if(m_bEdit)
      //{

      //   ::user::interaction::handle(ptopic, pcontext);

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


   //bool multiple_option::create_interaction(::user::interaction * puiParent, const ::atom & atom)
   //{

   //   if (!::user::interaction::create_interaction(puiParent, atom))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


//#ifdef WINDOWS_DESKTOP
//   //Derived class is responsible for implementing these handlers
//   //for owner/self draw controls (except for the optional DeleteItem)
//   void multiple_option::DrawItem(LPDRAWITEMSTRUCT)
//   { ASSERT(false); }
//   void multiple_option::MeasureItem(LPMEASUREITEMSTRUCT)
//   { ASSERT(false); }
//   i32 multiple_option::CompareItem(LPCOMPAREITEMSTRUCT)
//   { ASSERT(false); return 0; }
//   void multiple_option::DeleteItem(LPDELETEITEMSTRUCT)
//   { /* default to nothing */ }
//#endif

//   bool multiple_option::OnChildNotify(::user::message * pusermessage)
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

   void multiple_option::GetLBText(::collection::index nIndex, string & rString)
   {

      ASSERT(is_window());

      GetLBText(nIndex, rString.get_buffer(GetLBTextLen(nIndex)));

      rString.release_buffer();

   }


   //::collection::count multiple_option::get_count()
   // { ASSERT(is_window()); return (count)send_message( CB_GETCOUNT, 0, 0); }
   //index multiple_option::current_index()
   // { ASSERT(is_window()); return (index)send_message( CB_GETCURSEL, 0, 0); }
   //index multiple_option::set_current_item(index nSelect)
   // { ASSERT(is_window()); return (index)send_message( CB_SETCURSEL, nSelect, 0); }
   //IA64: Assuming retval of CB_GETEDITSEL won't be expanded
   bool multiple_option::GetEditSel(strsize & nStartChar, strsize & nEndChar)
   {
      /*      ASSERT(is_window()); u32 dw = u32(send_message( CB_GETEDITSEL, 0, 0));
            nStartChar = LOWORD(dw);
            nEndChar = LOWORD(dw);*/
      return true;
   }
   bool multiple_option::LimitText(strsize nMaxChars)
   {
      //ASSERT(is_window());
      //return send_message( CB_LIMITTEXT, nMaxChars, 0) != false;
      return true;
   }

   bool multiple_option::SetEditSel(strsize nStartChar, strsize nEndChar)
   {
      //ASSERT(is_window());
      //return send_message( CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar)) != false;
      return true;
   }

   uptr multiple_option::GetItemData(::collection::index nIndex)
   {

      //ASSERT(is_window());

      //return send_message( CB_GETITEMDATA, nIndex, 0);
      return 0;

   }

   ::collection::index multiple_option::SetItemData(::collection::index nIndex, uptr dwItemData)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

      return -1;

   }

   void * multiple_option::GetItemDataPtr(::collection::index nIndex)
   {

      //ASSERT(is_window()); return (LPVOID)GetItemData(nIndex);

      return nullptr;

   }

   ::collection::index multiple_option::SetItemDataPtr(::collection::index nIndex, void * pData)
   {

      //ASSERT(is_window());

      //return SetItemData(nIndex, (uptr)(LPVOID)pData);

      return -1;

   }

   ::collection::index multiple_option::GetLBText(::collection::index nIndex, char * pszText)

   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETLBTEXT, nIndex, (LPARAM)pszText);


      return -1;

   }

   strsize multiple_option::GetLBTextLen(::collection::index nIndex)
   {

      //ASSERT(is_window());

      //return (strsize)send_message( CB_GETLBTEXTLEN, nIndex, 0);

      return -1;

   }


   void multiple_option::ShowDropDown(bool bShowIt)
   {

      _001ShowDropDown(bShowIt);

   }


   ::collection::index multiple_option::erase_item_at(::collection::index nIndex)
   {

      auto iIndex = m_plistbox->erase_item_at(nIndex);

      return iIndex;

   }


   ::collection::index multiple_option::insert_item_at(::collection::index nIndex, const ::string & pszString)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);

      auto iIndex= m_plistbox->insert_item_at(nIndex, pszString);
      return iIndex;
      //return -1;

   }


   void multiple_option::reset_content()
   {

      if (!m_plistbox)
      {

         return;

      }

      m_plistbox->reset_content();

   }


   ::collection::index multiple_option::Dir(::collection::index attr, const ::string & pszWildCard)
   {

//      ASSERT(is_window());

//      return (index)send_message( CB_DIR, attr, (LPARAM)pszWildCard);


      return -1;

   }


   void multiple_option::clear()
   {

      //ASSERT(is_window());

      //send_message(WM_CLEAR, 0, 0);

   }


   void multiple_optioncopy()
   {

      //ASSERT(is_window());

      //send_message(WM_COPY, 0, 0);

   }


   void multiple_option::Cut()
   {

      //ASSERT(is_window());

      //send_message( WM_CUT, 0, 0);

   }


   void multiple_option::Paste()
   {

      //ASSERT(is_window());

      //send_message( WM_PASTE, 0, 0);

   }


   i32 multiple_option::SetItemHeight(::collection::index nIndex, ::u32 cyItemHeight)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));

      return -1;

   }


   i32 multiple_option::GetItemHeight(::collection::index nIndex)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_GETITEMHEIGHT, nIndex, 0L);

      return -1;

   }


   ::collection::index multiple_option::FindStringExact(::collection::index nIndexStart, const ::string & pszFind)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)pszFind);


      return -1;

   }


   i32 multiple_option::SetExtendedUI(bool bExtended)
   {

      //ASSERT(is_window());

      //return (i32)send_message( CB_SETEXTENDEDUI, bExtended, 0L);

      return -1;

   }


   bool multiple_option::GetExtendedUI()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETEXTENDEDUI, 0, 0L) != 0;

      return false;

   }


   void multiple_option::GetDroppedControlRect(::rectangle_i32 * prectangle)
   {

      //ASSERT(is_window());

      //send_message( CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)prectangle);


   }


   bool multiple_option::GetDroppedState()
   {

      //ASSERT(is_window());

      //return send_message( CB_GETDROPPEDSTATE, 0, 0L) != 0;

      return false;

   }


//   LCID multiple_option::GetLocale()
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
//   LCID multiple_option::SetLocale(LCID nNewLocale)
//   {
//
//      //ASSERT(is_window());
//
//      //return (LCID)send_message( CB_SETLOCALE, (WPARAM)nNewLocale, 0);
//
//      return nNewLocale; // set where it is
//
//   }


   ::collection::index multiple_option::GetTopIndex()
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_GETTOPINDEX, 0, 0);

      return -1;

   }


   ::collection::index multiple_option::SetTopIndex(::collection::index nIndex)
   {

      //ASSERT(is_window());

      //return (index)send_message( CB_SETTOPINDEX, nIndex, 0);

      return -1;

   }


   ::collection::count multiple_option::InitStorage(::collection::count nItems, ::u32 nBytes)
   {

      //ASSERT(is_window());

      //return (count)send_message( CB_INITSTORAGE, (WPARAM)nItems, nBytes);

      return -1;

   }

   void multiple_option::SetHorizontalExtent(::u32 nExtent)
   {

      //ASSERT(is_window());

      //send_message( CB_SETHORIZONTALEXTENT, nExtent, 0);

   }


   ::u32 multiple_option::GetHorizontalExtent()
   {

      //ASSERT(is_window());

      //return (::u32)send_message( CB_GETHORIZONTALEXTENT, 0, 0);

      return 0;

   }


   i32 multiple_option::SetDroppedWidth(::u32 nWidth)
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_SETDROPPEDWIDTH, nWidth, 0);

      return -1;

   }


   i32 multiple_option::GetDroppedWidth()
   {

//      ASSERT(is_window());

//      return (i32)send_message( CB_GETDROPPEDWIDTH, 0, 0);

      return -1;

   }


   bool multiple_option::_001GetListText(::collection::index iSel,string & str) const
   {

      return m_plistbox->_001GetListText(iSel, str);

   }


   ::collection::index multiple_option::_001FindListText(const ::string & str) const
   {

      return m_plistbox->_001FindListText(str);

   }

   ::collection::index multiple_option::add_item(const ::scoped_string& scopedstr, const ::atom & atom)
   {

      _synchronous_lock synchronouslock(this->synchronization());

//      ASSERT(m_edatamode == data_mode_opaque);
//
//      if (m_edatamode != data_mode_opaque)
//      {
//
//         return -1;
//
//      }

      defer_create_list_box();

      return m_plistbox->add_item(scopedstr, atom);

   }

   //::collection::index multiple_option::add_string(const ::string & pszString,uptr dwItemData)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   ASSERT(m_edatamode == data_mode_opaque);

   //   if (m_edatamode != data_mode_opaque)
   //   {

   //      return -1;

   //   }

   //   defer_create_list_box();

   //   return m_plistbox->add_item(pszString, dwItemData);

   //}


   //::collection::index multiple_option::add_string(const ::string & pszString, const ::string & strValue)
   //{

   //   ASSERT(m_edatamode == data_mode_string);

   //   if (m_edatamode != data_mode_string)
   //   {

   //      return -1;

   //   }

   //   defer_create_list_box();

   //   auto iIndex = m_plistbox->add_string(pszString, strValue);

   //   return iIndex;

   //}


   bool multiple_option::has_action_hover()
   {

      return ::is_set(m_pitemHover) || is_drop_down();

   }


   bool multiple_option::has_text_input()
   {

      return m_bEdit && ::user::interaction::has_text_input();

   }


   void multiple_option::set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext)
   {

      m_plistbox->set_current_item_by_text(scopedstr, actioncontext);

   }


   void multiple_option::set_current_item_by_index(::collection::index iIndex, const ::action_context & action_context)
   {

      m_plistbox->set_current_item_by_index(iIndex, action_context);

   }


   void multiple_option::set_current_item_by_atom(const ::atom & atom, const ::action_context & context)
   {

      m_plistbox->set_current_item_by_atom(atom, context);

   }


   string multiple_option::get_current_item_text()
   {

      if (::is_null(m_plistbox))
      {

         return {};

      }

      return m_plistbox->get_current_item_text();

   }


   ::atom multiple_option::get_current_item_atom()
   {

      if (::is_null(m_plistbox))
      {

         return {};

      }

      return m_plistbox->get_current_item_atom();

   }


   bool multiple_option::keyboard_focus_is_focusable()
   {

      // return m_bEdit && is_window_enabled() && is_window_visible(e_layout_sketch);
      return is_window_enabled() && is_window_visible(e_layout_sketch);

   }


   bool multiple_option::is_drop_down()
   {

      return m_plistbox != nullptr && m_plistbox->is_window_visible(e_layout_sketch);

   }


} // namespace user



