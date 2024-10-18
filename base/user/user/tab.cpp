#include "framework.h"
#include "tab.h"
#include "tab_pane_array.h"
#include "tab_pane.h"
#include "tab_data.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/timer.h"
#include "acme/exception/exit.h"
#include "acme/handler/item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/request.h"
#include "aura/graphics/image/context.h"
#include "acme/prototype/data/listener.h"
#include "acme/platform/timer.h"
#include "acme/user/user/drag.h"
#include "aura/graphics/image/list.h"
#include "aura/user/user/frame.h"
#include "aura/user/user/system.h"
#include "aura/user/user/interaction_array.h"
#include "style.h"
#include "aura/message/user.h"
#include "tab_callback.h"
#include "base/platform/application.h"
#include "base/platform/system.h"


//extern CLASS_DECL_BASE thread_int_ptr < DWORD_PTR > t_time1;

// pgraphics->get_text_extent("->:<-"); // oh no!! omg!! The size_i32 is the size_i32 of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace user
{


   tab::tab()
   {

      m_bDefaultClickHandling = true;

      m_bDefaultMouseHoverHandling = true;
      
      //m_bDefaultParentMouseMessageHandling = true;

      m_econtroltype = e_control_type_tab;


      //m_bMouseDown = false;

      m_iTabSize = 0;

      m_estate = e_state_initial;

      m_iRestoredTabCount = 0;

      m_bDisableSavingRestorableTabs = true;

      //m_bShowTabs                      = true;

      //m_bNoTabs                        = false;

      m_bDrawTabAtBackground = true;

      m_bCreatedTabs = false;

      m_bAutoCreateTabsOnCreate = true;

   }


   tab::~tab()
   {

   }


   void tab::on_initialize_particle()
   {

      //auto estatus = 

      ::user::interaction::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      __defer_construct_new(m_pdata);

      //if (estatus == ::success)
      //{

      auto pdata = get_data();

      pdata->m_iHeightAddUp = 0;
      pdata->m_pcallback = nullptr;
      pdata->m_bCreated = false;
      pdata->m_iTabHeight = 16;
      pdata->m_iTabWidth = 48;
      pdata->m_iClickTab = -1;

      //}

      //return estatus;
      
      m_bDefaultParentMouseMessageHandling = true;

   }


   void tab::destroy()
   {

      m_pdata.defer_destroy();

      m_pitemClick.release();

      m_pitemTabNearScroll.release();

      m_pitemTabFarScroll.release();

      m_pfontTab.release();

      m_pgraphicsextension.release();

      ::user::place_holder_container::destroy();

   }


   /*bool tab::add_tab(::u32 uIdTitle, i32 iId)
   {
      get_pane get_pane;
      ppane->m_uiId = uiIdTitle;
      ppane->m_istrTitleEx = L"";
      ppane->m_iId = iId == -1 ? get_data()->m_tabpanea.get_size() : iId;
      if(!ppane->m_wstrTitle.load_string(uiIdTitle))
      {
         return false;
      }*/
      //   ppane->m_pcontainer = pcontainer;
      // ppane->m_type = nullptr;
      /* ppane->m_iImage = -1;

       get_data()->m_tabpanea.add(get_pane);
       return true;
      }*/


   enum_element tab::get_default_element()
   {

      return e_element_tab;

   }


   bool tab::set_title(::collection::index iIndex, const ::string & pcsz)

   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (iIndex < 0)
      {

         return false;

      }

      if (iIndex >= get_data()->m_tabpanea.get_size())
      {

         return false;

      }

      get_data()->m_tabpanea[iIndex]->set_title(pcsz);


      return true;

   }


   bool tab::set_title_by_id(const ::atom & atom, const ::string & pcsz)
   {

      auto iIndex = id_index(atom);

      if (iIndex < 0)
      {

         return false;

      }

      get_data()->m_tabpanea[iIndex]->set_title(pcsz);

      return true;

   }


   //bool tab::set_tab(const ::string & pcsz, const ::atom & atom, bool bVisible)
   //{

   //   return add_tab(pcsz, atom, bVisible, true);

   //}


   bool tab::add_tab(const ::string & strTitle, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pholder)
   {

      ::atom atom(atomImpact);

      auto & ppane = get_data()->m_tabpanea.add_new();

      __construct_new(ppane);

      ppane->initialize_tab_pane(this);

      // second colon starts the text.
      // if the text is a ID, the ID will be result when no translation
      // if the text is a text (in English), the text (in English) will be the result when there is no translation.
      //set_tille("text://hello_multiverse/AKDFJG./:Main Tab"));
      ppane->set_title(strTitle);

      ppane->m_bTabPaneVisible = bVisible;
      ppane->m_bPermanent = bPermanent;
      ppane->m_pplaceholder = pholder;

      _synchronous_lock synchronouslock(this->synchronization());

      if (atom.is_empty())
      {

         atom = get_data()->m_tabpanea.get_size();

      }

      ppane->m_atom = atom;

      on_change_tab_count({ ppane });

      return true;

   }


   bool tab::set_tab(const ::string & strName, const ::atom & atomImpact, bool bVisible)
   {

      return add_tab(strName, atomImpact, bVisible, true);

   }


   bool tab::add_tab_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplaceholder)
   {

      ::atom atom(atomImpact);

      auto & ppane = get_data()->m_tabpanea.add_new();

      __construct_new(ppane);

      ppane->initialize_tab_pane(this);

      ppane->m_bTabPaneVisible = bVisible;
      ppane->m_bPermanent = bPermanent;
      ppane->set_title(strName);

      _synchronous_lock synchronouslock(this->synchronization());

      if (atom.is_empty())
      {

         atom = get_data()->m_tabpanea.get_size();

      }

      ppane->m_atom = atom;
      ppane->m_pplaceholder = pplaceholder;

      ppane->m_pimage = image()->load_image(strIcon, { .sync = false, .cache = false, });

      on_change_tab_count({ ppane });

      return true;

   }


   bool tab::set_tab_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact, bool bVisible)
   {

      return add_tab_with_icon(strName, strIcon, atomImpact, bVisible, true);

   }


   void tab::_001OnRemoveTab(class tab_pane * ptabpane)
   {

      if (matches_restorable_tab(ptabpane->m_atom, ptabpane->m_pplaceholder))
      {

         on_change_tab_count({ nullptr });

      }
      else
      {

         on_change_tab_count();

      }

   }


   bool tab::erase_tab_by_id(const ::atom & atom)
   {

      //bool bRestorableMatch = false;

      for (i32 i = 0; i < get_data()->m_tabpanea.get_count(); i++)
      {

         if (get_data()->m_tabpanea[i]->m_atom == atom)
         {

            //if (!bRestorableMatch && matches_restorable_tab(get_data()->m_tabpanea[i]->m_atom, get_data()->m_tabpanea[i]->m_pplaceholder))
            //{

            //   bRestorableMatch = true;

            //}

            erase_tab(i, false);

            break;

         }

      }

      //if (bRestorableMatch)
      //{

      //   on_change_tab_count({ nullptr });

      //}

      //on_change_tab_count();

      return true;

   }


   //bool tab::set_image_tab(const ::string & pcszTitle, const ::string & pszImage, const ::atom & atom, bool bVisible)
   //{

   //   return add_image_tab(pcszTitle, pszImage, atom, bVisible, true);

   //}


   void tab::erase_tab(::collection::index iIndex, bool bVisible)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (iIndex < 0 || iIndex >= get_data()->m_tabpanea.get_size())
      {

         return;

      }

      if (bVisible)
      {

         for (i32 i = 0; iIndex >= 0 && i < get_data()->m_tabpanea.get_count(); i++)
         {

            if (get_data()->m_tabpanea[i]->m_bTabPaneVisible)
            {

               if (iIndex <= 0)
               {

                  auto ppane = get_data()->m_tabpanea[iIndex];

                  get_data()->m_tabpanea.erase_at(iIndex);

                  _001OnRemoveTab(ppane);

                  //on_change_tab_count();

                  break;

               }
               else
               {

                  iIndex--;

               }

            }

         }

      }
      else
      {

         auto ppane = get_data()->m_tabpanea[iIndex];

         get_data()->m_tabpanea.erase_at(iIndex);

         _001OnRemoveTab(ppane);

         //on_change_tab_count();

      }

   }


   void tab::erase_all_tabs()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      get_data()->m_tabpanea.erase_all();

      on_change_tab_count();

   }




   void tab::get_title(int iIndex, string_array & stra)
   {

      auto ppane = get_data()->m_tabpanea[iIndex].get();

      stra = ppane->m_straTitle;

   }


   void tab::GetTabClientRect(::rectangle_i32 & rectangle)
   {

      rectangle = get_data()->m_rectangleHosting;

   }


   void tab::GetTabClientRect(::rectangle_i64 & rectangle)
   {

      ::rectangle_i32 rectangleHosting;

      GetTabClientRect(rectangleHosting);

      rectangle = rectangleHosting;

   }


   void tab::layout_pane(::collection::index iIndex, bool bDisplay)
   {

      auto ppane = get_tab(iIndex);

      if (::is_null(ppane))
      {

         return;

      }

      auto ppaneSel = get_tab(get_current_tab_index());

      if (::is_null(ppane))
      {

         return;

      }

      auto pholder = ppane->m_pplaceholder;

      if (pholder.is_null())
      {

         return;

      }

      ::rectangle_i32 rectangleChild;

      GetTabClientRect(rectangleChild);

      ::rectangle_i32 rectangleWindow;

      pholder->window_rectangle(rectangleWindow);

      screen_to_client()(rectangleWindow);

      if (bDisplay && iIndex == get_current_tab_index())
      {

         pholder->order(e_zorder_top);

      }

      pholder->place(rectangleChild);

      //pholder->m_rectangleClient2 = rectangleChild;

      //pholder->m_rectangleClient2.offset(-pholder->m_rectangleClient2.top_left());

      if (bDisplay)
      {

         pholder->display(::e_display_normal);

         //         if (ppane->m_bNeedLayout)
         //         {
         //
         //            ppane->m_bNeedLayout = false;
         //
         //            pholder->set_need_layout();
         //
         //         }
         //
         //         pholder->set_need_redraw();
         //
         //         pholder->post_redraw();

      }
      else if (::is_set(ppaneSel) && ppaneSel->m_eflag.has(e_flag_hide_all_others_on_show))
      {

         pholder->hide();

      }

   }


   void tab::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      m_pitemClick = hit_test(pmouse, ::user::e_zorder_any);

      get_data()->m_bDrag = false;

      get_data()->m_iClickTab = -1;

      ///m_pointLeftButtonDown = pmouse->m_point;

      //m_bMouseDown = true;

//      if (::is_element(m_pitemClick, e_element_tab_near_scroll))
//      {
//
//         if (m_pointBarDragScroll.x() > 0)
//         {
//
//            m_pointBarDragScroll.x()--;
//
//            set_need_redraw();
//
//            post_redraw();
//
//            pmouse->m_bRet = true;
//
//            set_mouse_capture();
//
//            return;
//
//         }
//
//      }
//      else if (::is_element(m_pitemClick, e_element_tab_far_scroll))
//      {
//
//         if (m_pointBarDragScroll.x() < m_pointBarDragScrollMax.x())
//         {
//
//            m_pointBarDragScroll.x()++;
//
//            set_need_redraw();
//
//            post_redraw();
//
//            pmouse->m_bRet = true;
//
//            set_mouse_capture();
//
//            return;
//
//         }
//
//      }

      if (::is_set(m_pitemClick) && m_pitemClick->m_item.m_iItem >= 0)
      {

         ::collection::index iIndex = get_current_tab_index();

         if (::is_element(m_pitemClick, e_element_close_tab_button))
         {

            get_data()->m_iClickTab = m_pitemClick->m_item.m_iItem;

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            //set_mouse_capture();

            m_estate = state_close_button_down;

         }
         else if (m_pitemClick->m_item.m_iItem != iIndex)
         {

            get_data()->m_iClickTab = m_pitemClick->m_item.m_iItem;

            //set_mouse_capture();

            //SetTimer(e_timer_drag_start, 300, nullptr);

            //g_tickDragStart.Now();

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

            m_estate = state_other_tab_button_down;

         }
         else
         {

            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

         }

      }

   }


   void tab::on_message_left_button_up(::message::message * pmessage)
   {

      //auto pmouse = pmessage->m_union.m_pmouse;

      //      if(m_bMouseDown)
      //      {
      //
      //         m_bMouseDown = false;
      //
      //         release_mouse_capture();
      //
      //      }

      //auto pitem = hit_test(pmouse, ::user::e_zorder_any);

      //index iClickTab = get_data()->m_iClickTab;

      //if (m_estate == state_other_tab_button_down)
      //{

      //    drag operation was about to start (but ended prematurely)

      //   release_mouse_capture();

      //   KillTimer(e_timer_drag_start);

      //}

      //if (::is_set(pitem))
      //{

      //   if (pitem->m_item.m_iItem >= 0 && iClickTab == pitem->m_item.m_iItem && ::is_same_item(m_pitemClick, pitem))
      //   {

      //      if (::is_element(pitem, e_element_close_tab_button))
      //      {

      //         _001OnTabClose(pitem->m_item.m_iItem);

      //      }
      //      else
      //      {

      //         _001OnTabClick(pitem->m_item.m_iItem);

      //      }

      //                  set_need_redraw();
      //      
      //                  post_redraw();

      //      pmouse->m_bRet = true;

      //      pmouse->m_lresult = 1;

      //   }

      //}

      //get_data()->m_iClickTab = -1;

      //get_data()->m_bDrag = false;

   }


   void tab::on_message_left_button_double_click(::message::message * pmessage)
   {

      pmessage->m_bRet = m_pitemClick.is_set();

   }


   void tab::on_message_mouse_move(::message::message * pmessage)
   {

      ::pointer < ::message::mouse > pmouse(pmessage);

      if (pmessage->previous())
      {

         return;

      }

      if (get_data()->m_iClickTab >= 0)
      {

         if (get_data()->m_pcallback != nullptr)
         {

            get_data()->m_pcallback->_001DropTargetWindowRelay(this);

         }

      }

      auto_hide_on_message_mouse_move(pmessage);

   }


   void tab::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //::pointer<::user::message>pusermessage(pmessage);

   }


   ::i32 tab::auto_hide_threshold_height()
   {

      auto pdata = get_data();

      return pdata->m_iTabHeight;

   }

   //bool tab::has_tab_scrolling() const
   //{

   //   return m_iTabScrollMax > 0;

   //}


   bool tab::get_element_rectangle(::collection::index iIndex, ::rectangle_i32 & rectangle, enum_element eelement)
   {

      point_i32 ptOffset(0, 0);

      auto ptabdata = get_data();

      if (_001HasBarXDragScrolling())
      {

         float fDensity = 1.0f;

         //if (!is_sandboxed())
         {

            if (eelement == e_element_tab_near_scroll)
            {
               
               if (get_data()->m_bVertical)
               {

                  if(m_pointBarDragScroll.y() >= 0)
                  {
                   
                     return false;
                     
                  }

               }
               else
               {

                  if(m_pointBarDragScroll.x() >=  0)
                  {
                     
                     return false;
                     
                  }

               }

               if (ptabdata->m_bVertical)
               {

                  auto & rectangleTab = ptabdata->m_rectangleTab;

                  rectangle.left() = rectangleTab.left();

                  rectangle.top() = rectangleTab.top();

                  rectangle.right() = rectangleTab.right();

                  fDensity = get_density_for_window();

                  rectangle.bottom() = rectangle.top() + (::i32)(8.0f * fDensity);

               }
               else
               {

                  auto & rectangleTab = ptabdata->m_rectangleTab;

                  rectangle.left() = rectangleTab.left();

                  rectangle.top() = rectangleTab.top() + ptabdata->m_rectangleBorder.top();

                  fDensity = get_density_for_window();

                  rectangle.right() = rectangle.left() + (::i32)(16.0f * fDensity);

                  rectangle.bottom() = rectangleTab.bottom() - ptabdata->m_rectangleBorder.bottom();

               }

               return true;

            }
            else if (eelement == e_element_tab_far_scroll)
            {
               
               if (get_data()->m_bVertical)
               {

                  if(m_pointBarDragScroll.y() <= -m_pointBarDragScrollMax.y())
                  {
                   
                     return false;
                     
                  }

               }
               else
               {

                  if(m_pointBarDragScroll.x() <= -m_pointBarDragScrollMax.x())
                  {
                     
                     return false;
                     
                  }

               }


               if (ptabdata->m_bVertical)
               {

                  auto & rectangleTab = ptabdata->m_rectangleTab;

                  rectangle.left() = rectangleTab.left();

                  fDensity = get_density_for_window();

                  rectangle.top() = rectangleTab.bottom() - (::i32)(8.0f * fDensity);

                  rectangle.right() = rectangleTab.right();

                  rectangle.bottom() = rectangleTab.bottom();

               }
               else
               {

                  auto & rectangleTab = ptabdata->m_rectangleTab;

                  fDensity = get_density_for_window();

                  rectangle.left() = rectangleTab.right() - (::i32)(16.0f * fDensity);

                  rectangle.top() = rectangleTab.top()
                  +ptabdata->m_rectangleBorder.top();

                  rectangle.right() = rectangleTab.right();

                  rectangle.bottom() = rectangleTab.bottom() - ptabdata->m_rectangleBorder.bottom();

               }

               return true;

            }

         }

         if (get_data()->m_bVertical)
         {

            ptOffset.y() += 4;

            ptOffset.y() += m_pointBarDragScroll.y();

         }
         else
         {

            ptOffset.x() += 4;

            ptOffset.x() += m_pointBarDragScroll.x();

         }

      }

      if (iIndex < 0)
      {

         return false;

      }

      if (eelement == e_element_border)
      {

         if (!get_element_rectangle(iIndex, rectangle, e_element_tab))
         {

            return false;

         }

         ::deflate(rectangle, ptabdata->m_rectangleMargin);

         return true;

      }

      if (eelement == e_element_client)
      {

         if (!get_element_rectangle(iIndex, rectangle, e_element_border))
         {

            return false;

         }

         ::deflate(rectangle, ptabdata->m_rectangleBorder);

         return true;

      }

      if (eelement == e_element_icon)
      {

         if (ptabdata->m_tabpanea[iIndex]->m_pimage.nok())
         {

            return false;

         }

         if (!get_element_rectangle(iIndex, rectangle, e_element_client))
         {

            return false;

         }

         rectangle.right() = rectangle.left() + ptabdata->m_tabpanea[iIndex]->m_pimage->width();

         rectangle.bottom() = rectangle.top() + ptabdata->m_tabpanea[iIndex]->m_pimage->height();

         return true;

      }
      else if (eelement == e_element_text)
      {

         if (!get_element_rectangle(iIndex, rectangle, e_element_client))
         {

            return false;

         }

         if (ptabdata->m_tabpanea[iIndex]->m_pimage.ok())
         {

            rectangle.left() += ptabdata->m_tabpanea[iIndex]->m_pimage->width() + 2;

         }

         if (!ptabdata->m_tabpanea[iIndex]->m_bPermanent)
         {

            rectangle.right() -= 2 + 16 + 2;

         }

         ::deflate(rectangle, ptabdata->m_rectangleTextMargin);

         return true;

      }
      else if (eelement == e_element_close_tab_button)
      {

         if (iIndex < 0)
         {

            return false;

         }

         if (ptabdata->m_tabpanea[iIndex]->m_bPermanent)
         {

            return false;

         }

         if (ptabdata->get_visible_tab_count() <= 1 && !ptabdata->m_bEnableCloseAll)
         {

            return false;

         }

         if (!get_element_rectangle(iIndex, rectangle, e_element_client))
         {

            return false;

         }

         rectangle.right() = rectangle.right();

         rectangle.left() = rectangle.right() - 20;

         rectangle.top() = rectangle.bottom() - 20;

         return true;

      }

      if (eelement != e_element_tab)
      {

         return false;

      }

      if (ptabdata->m_bVertical)
      {

         auto & rectangleTab = ptabdata->m_rectangleTab;

         rectangle.left() = rectangleTab.left();

         rectangle.top() = (::i32)(rectangleTab.top() + iIndex * ptabdata->m_iTabHeight);

         rectangle.right() = rectangleTab.right();

         rectangle.bottom() = rectangle.top() + ptabdata->m_iTabHeight;

      }
      else
      {

         auto ppane = get_data()->m_tabpanea[iIndex].get();

         rectangle.left() = ppane->m_point.x();

         rectangle.top() = ppane->m_point.y();

         rectangle.right() = rectangle.left() + ppane->m_size.cx();

         rectangle.bottom() = rectangle.top() + ppane->m_size.cy();

      }

      ::offset(rectangle, ptOffset.x(), ptOffset.y());

      return true;

   }


   ::collection::count tab::get_tab_count()
   {

      return get_data()->m_tabpanea.get_size();

   }


   ::collection::count tab::get_visible_tab_count()
   {

      return get_data()->m_tabpanea.predicate_get_count([](auto & pane) {return pane->m_bTabPaneVisible; });

   }


   ::collection::index tab::find_child_pane(::user::interaction * pinteraction)
   {

      ::collection::index iIndex = get_data()->m_tabpanea.predicate_find_first([=](auto & pane)
      {

         return pane->m_pplaceholder && pane->m_pplaceholder->is_ascendant_of(pinteraction, true);

      });

      return iIndex;

   }


   void tab::defer_erase_child_pane(::user::interaction * pinteraction)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::collection::index iIndex = find_child_pane(pinteraction);

      if (iIndex >= 0)
      {

         erase_tab(iIndex, false);

      }

   }


   void tab::on_erase_child(::user::interaction * pinteraction)
   {

      defer_erase_child_pane(pinteraction);

   }


   void tab::on_erase_place_holder_child(::user::interaction * pinteraction)
   {

      defer_erase_child_pane(pinteraction);

   }


   void tab::on_hide_child(::user::interaction * pinteraction)
   {

      //::pointer<::user::interaction>pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != e_updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_erase_child_pane(pinteraction);

      //}

   }


   void tab::on_hide_place_holder_child(::user::interaction * pinteraction)
   {

      //::pointer<::user::interaction>pupdown = pinteraction;

      //if (pupdown.is_set()
      //      && pupdown->m_eupdown != e_updown_normal_frame
      //      && pupdown->m_eupdown != updown_none)
      //{

      //   defer_erase_child_pane(pinteraction);

      //}

   }


   ::item_pointer tab::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   {
      
      if(!should_draw())
      {
       
         auto pitemNone = __allocate ::item(e_element_none);

         return pitemNone;
         
      }

      auto pointCursor = point;

      //_synchronous_lock synchronouslock(this->synchronization());

      ::rectangle_i32 rectangleScroll;

      bool bScroll = _001HasBarXDragScrolling();

      if (bScroll)
      {

//         if (is_sandboxed())
//         {
//
//         }
//         else
         {

            if (get_element_rectangle(-1, rectangleScroll, ::e_element_tab_near_scroll))
            {

               if (rectangleScroll.contains(pointCursor))
               {
                  
                  return m_pitemTabNearScroll;

               }

            }

            if (get_element_rectangle(-1, rectangleScroll, ::e_element_tab_far_scroll))
            {

               if (rectangleScroll.contains(pointCursor))
               {

                  return m_pitemTabFarScroll;

               }

            }

         }

      }

      //point += m_pointDragScroll;

      if (should_draw())
      {

         ::rectangle_i32 rectangle;

         for (i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
         {

            auto ppane = get_data()->m_tabpanea[iIndex].get();

            if (ppane->m_straTitle.get_size() > 1)
            {

               ::rectangle_i32 rectangleText;

               if (get_element_rectangle(iIndex, rectangleText, e_element_text))
               {

                  if (rectangleText.contains(point))
                  {

                     for (int iTitle = 0; iTitle < ppane->m_straTitle.get_size(); iTitle++)
                     {

                        rectangleText.left() += (::i32)(ppane->m_sizeaText[iTitle].cx());

                        rectangleText.right() = (::i32)(rectangleText.left() + get_data()->m_sizeSep.cx());

                        if (rectangleText.contains(point))
                        {

                           return __allocate ::item((enum_element)((int)e_element_split + iTitle), iIndex);

                        }

                        rectangleText.left() += (::i32)(get_data()->m_sizeSep.cx());

                     }

                  }

               }

            }

            if (get_element_rectangle(iIndex, rectangle, e_element_close_tab_button))
            {

               if (rectangle.contains(point))
               {

                  ppane->m_pitemClose->m_item.m_iItem = iIndex;

                  user_item(ppane)->m_rectangle2 = rectangle;

                  return ppane->m_pitemClose;

               }

            }

            if (get_element_rectangle(iIndex, rectangle, e_element_tab))
            {

               if (rectangle.contains(point))
               {

                  ppane->m_item.m_iItem = iIndex;

                  user_item(ppane)->m_rectangle2 = rectangle;

                  return ppane;
                  //return __allocate ::item(e_element_tab, iIndex);

               }

            }

         }

      }

      auto pitemNone = __allocate ::item(e_element_none);

      return pitemNone;

   }


   bool tab::on_drag_start(::point_i32 & pointDrag, ::item * pitem)
   {
      
      if(::user::interaction::on_drag_start(pointDrag, pitem))
      {
         
         return true;
         
      }

      if (pitem->m_item.m_eelement == e_element_tab_near_scroll
          || pitem->m_item.m_eelement == e_element_tab_far_scroll)
      {
         
         //::rectangle_i32 r;

         //get_element_rectangle(0, r, pitem->m_item.m_eelement);
         
         //pointDrag = r.center();
         
         auto pdrag = drag(pitem);
         
         pointDrag = pdrag->m_pointInitial;

         return true;

      }
      
      return false;

   }


   void tab::on_drag_scroll_layout(::draw2d::graphics_pointer & pgraphics)
   {
      
      ::user::interaction::on_drag_scroll_layout(pgraphics);
      
      if(m_pointBarDragScrollMax.x() > 0)
      {
         
         if(!m_pitemTabFarScroll)
         {
            
            m_pitemTabFarScroll = __allocate ::item(::e_element_tab_far_scroll, -1);
            
            enable_drag(m_pitemTabFarScroll, ::user::e_zorder_front);
            
            auto puseritemFarScroll = user_item(m_pitemTabFarScroll);
            
            puseritemFarScroll->m_euseritemflag += ::user::e_item_flag_rectangle_callback;
            
         }
         
         if(!m_pitemTabNearScroll)
         {
            
            m_pitemTabNearScroll = __allocate ::item(::e_element_tab_near_scroll, -1);
            
            enable_drag(m_pitemTabNearScroll, ::user::e_zorder_front);
            
            auto puseritemNearScroll = user_item(m_pitemTabNearScroll);
            
            puseritemNearScroll->m_euseritemflag += ::user::e_item_flag_rectangle_callback;
            
         }
         
      }
      
   }

   
   bool tab::drag_shift(::item * pitem, ::user::mouse * pmouse)
   {

      if (pitem->m_item.m_eelement == e_element_tab_near_scroll
          || pitem->m_item.m_eelement == e_element_tab_far_scroll)
      {
         
         auto pdrag = drag(pitem);

         pdrag->m_ecursor = e_cursor_move;

         auto point = drag_point(pitem, pmouse);

         m_pointBarDragScroll.x() = minimum_maximum(point.x(), -m_pointBarDragScrollMax.x(), 0);
         
         
         set_need_redraw();

         post_redraw();

         return true;
         
      }

      return ::user::interaction::drag_shift(pitem, pmouse);

   }


   ::user::interaction * tab::GetNotifyWnd()
   {

#ifdef UNIVERSAL_WINDOWS

      return nullptr;

#else

      ::user::interaction * puserinteraction;

      if ((puserinteraction = get_parent()->get_wnd()) != nullptr)
      {

         return puserinteraction;

      }

      return nullptr;

#endif

   }

   /*
   bool tab::create(::user::interaction * pchannel, ::u32 uId)
   {
      if(!m_puserinteraction->create(
         pchannel,
         uId))
         return false;
      m_bCreated = true;
      on_layout(pgraphics);
      return true;
   }
   */


   void tab::on_message_create(::message::message * pmessage)
   {

      top_level()->add_handler(this);

      auto_hide_on_message_create(pmessage);

      if (is_sandboxed())
      {

         if (get_data()->m_bVertical)
         {

            m_bEnableVerticalBarDragScroll = true;

         }
         else
         {

            m_bEnableHorizontalBarDragScroll = true;

         }

      }

      auto psystem = system()->m_pbasesystem;

      if (psystem->has_property("no_tabs"))
      {

         m_bForceHiddenControl = false;

      }

      ::pointer<::user::message>pusermessage(pmessage);

      if (pmessage->previous())
      {

         return;

      }

      auto pcursor = get_mouse_cursor(e_cursor_arrow);

      set_default_mouse_cursor(pcursor);

      __construct_new(get_data()->m_pimagelist);

      get_data()->m_pimagelist->create(16, 16, 0, 0, 16);

      //auto pdraw2d = psystem->draw2d();

      //auto pgraphics = pdraw2d->create_memory_graphics(this);

      get_data()->m_bCreated = true;

      pusermessage->m_lresult = 0;

      //SetTimer(e_timer_defer_handle_auto_hide_tabs, 300_ms);

      //post_message(WM_USER + 1342);

      if (m_bAutoCreateTabsOnCreate)
      {

         create_tabs();

      }

   }


   void tab::on_create_tabs()
   {

      auto pextendedtopic = create_extended_topic(::id_on_create_tab);

      pextendedtopic->m_puserelement = this;

      pextendedtopic->m_ptab = this;

      route(pextendedtopic);

   }


   ::collection::count tab::restore_tabs()
   {

      ::collection::count c = 0;

      KEEP(m_bDisableSavingRestorableTabs);

      if (get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         ::payload payload;

         //if(datastream()->get("restore_tab",::payload))
         //{

         //   c = open_tabs(payload.payloada());

         //}

      }

      return c;

   }


   void tab::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //install_hover_default_mouse_handling(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &tab::on_message_create);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &tab::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tab::on_message_left_button_up);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &tab::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &tab::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &tab::on_message_mouse_leave);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &tab::on_message_show_window);
      MESSAGE_LINK(e_message_language, pchannel, this, &tab::_001OnAppLanguage);
      MESSAGE_LINK(message_start_tab_drag, pchannel, this, &tab::_001OnStartTabDrag);

      ////MESSAGE_LINK(e_message_timer, pchannel, this, &tab::_001OnTimer);

   }


   void tab::set_current_tab_by_index(::collection::index iIndex)
{
       
       information() << "tab::set_current_tab_by_index start : " << iIndex;
       
      {

         _synchronous_lock lock(get_data()->synchronization());

         get_data()->m_idaSel.erase_all();

         atom idTab = index_id(iIndex);

         if (!idTab.is_empty())
         {

            get_data()->m_idaSel.add(idTab);

            information() << "tab::set_current_tab_by_index idTab : " << idTab.as_string();

         }

      }

      on_change_cur_sel();

      on_after_change_cur_sel();

      if (m_ewindowflag & ::e_window_flag_window_created)
      {
         
         set_need_redraw();

         post_redraw();

      }

      information() << "tab::set_current_tab_by_index end";

   }


   ::collection::index tab::tab_index(::user::tab_pane * ptabpaneFind)
   {

      if (::is_null(ptabpaneFind))
      {

         return -1;

      }

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      return pdata->m_tabpanea.predicate_find_first([ptabpaneFind](auto & ptabpane)
         {

            return ptabpane == ptabpaneFind;

         });

   }


   ::collection::index tab::visible_index_index(::collection::index iVisibleIndex)
   {

      if (iVisibleIndex < 0)
      {

         return -1;

      }

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      return pdata->m_tabpanea.predicate_index_index(iVisibleIndex, [](auto & ptabpane)
         {

            return ptabpane->m_bTabPaneVisible;

         });

   }


   ::collection::index tab::index_visible_index(::collection::index iIndex)
   {

      if (iIndex < 0)
      {

         return -1;

      }

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      return pdata->m_tabpanea.index_predicate_index(iIndex, [](auto & ptabpane)
         {

            return ptabpane->m_bTabPaneVisible;

         });

   }


   bool tab::contains_tab_with_id(const ::atom & atom)
   {

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      return pdata->m_tabpanea.predicate_contains([atom](auto & ptabpane)
         {

            return ptabpane->m_atom == atom;

         });

   }


   ::collection::index tab::id_index(const ::atom & atom)
   {

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      return pdata->m_tabpanea.predicate_find_first([atom](auto & ptabpane)
         {

            return ptabpane->m_atom == atom;

         });


   }


   ::atom tab::index_id(::collection::index iIndex)
   {

      auto pdata = get_data();

      _synchronous_lock lock(pdata->synchronization());

      if (iIndex < 0 || iIndex >= pdata->m_tabpanea.get_count())
      {

         return -1;

      }

      auto ppane = pdata->m_tabpanea[iIndex];

      if (!ppane)
      {

         return -1;

      }

      return ppane->m_atom;

   }


   ::collection::index tab::id_visible_index(const ::atom & atom)
   {

      auto iIndex = id_index(atom);

      auto iVisibleIndex = index_visible_index(iIndex);

      return iVisibleIndex;

   }


   ::atom tab::visible_index_id(::collection::index iVisibleIndex)
   {

      auto iIndex = visible_index_index(iVisibleIndex);

      auto atom = index_id(iIndex);

      return atom;

   }


   void tab::_001OnAppLanguage(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      set_need_layout();

   }


   void tab::_001SetTabCallback(tab_callback * pcallback)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         delete get_data()->m_pcallback;

      }

      get_data()->m_pcallback = pcallback;

   }


   ::collection::index tab::get_current_tab_index()
   {

      if (get_data()->m_idaSel.get_size() == 1)
      {

         return id_index(get_data()->m_idaSel[0]);

      }
      else
      {

         return -1;

      }

   }


   ::collection::index tab::get_current_visible_tab_index()
   {

      auto iIndex = get_current_tab_index();

      if (iIndex)
      {

         return -1;

      }

      auto iVisibleIndex = index_visible_index(iIndex);

      return iVisibleIndex;

   }


   bool tab::_001IsAddTab(::collection::index iIndex)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         return get_data()->m_pcallback->_001IsAddTab(this, iIndex);

      }
      else
      {

         return false;

      }

   }


   bool tab::on_click(::item * pitem)
   {

      if (::is_element(pitem, e_element_close_tab_button))
      {

         _001OnTabClose(pitem->m_item.m_iItem);

      }
      else if (::is_element(pitem, e_element_tab))
      {

         _001OnTabClick(pitem->m_item.m_iItem);

      }
      else
      {

         return false;

      }

      return true;

   }


   ::user::interaction_array tab::place_holders()
   {

      ::user::interaction_array interactiona;

      auto & panea = get_data()->m_tabpanea;

      for (i32 i = 0; i < panea.get_count(); i++)
      {

         auto ptabpane = panea[i].get();

         if (ptabpane->m_pplaceholder.is_set())
         {

            interactiona.add_interaction(ptabpane->m_pplaceholder);

         }

      }

      sort_children_by_zorder(interactiona);

      return interactiona;

   }

   
   tab_pane * tab::place_holder_pane(::user::place_holder * pplaceholder)
   {

      if (::is_null(pplaceholder))
      {

         return nullptr;

      }

      auto & panea = get_data()->m_tabpanea;

      for (i32 i = 0; i < panea.get_count(); i++)
      {

         auto ptabpane = panea[i].get();

         if (ptabpane->m_pplaceholder.is_set()
            && ptabpane->m_pplaceholder == pplaceholder)
         {

            return ptabpane;

         }

      }

      return nullptr;

   }


   tab_pane * tab::top_pane()
   {

      auto interactiona = place_holders();

      if (!interactiona.has_interaction())
      {

         return nullptr;

      }

      ::pointer < ::user::place_holder > pplaceholder = interactiona.last_interaction();

      if (!pplaceholder)
      {

         return nullptr;

      }

      auto ptabpane = place_holder_pane(pplaceholder);

      if (!ptabpane)
      {

         return nullptr;

      }

      return ptabpane;

   }


   void tab::_001OnTabClick(::collection::index iIndex)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClick(this, iIndex);

      }
      else
      {

         set_current_tab_by_index(iIndex);

      }

   }


   void tab::_001OnTabClose(::collection::index iIndex)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnTabClose(this, iIndex);

      }
      else
      {

         _001CloseTab(iIndex);

      }

   }


   bool tab::show_tab_by_id(const ::atom & atom, bool bShow)
   {

      auto ppane = get_tab_by_id(atom);

      if (ppane == nullptr)
      {

         return false;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::show_pane(::collection::index iIndex, bool bShow)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return !bShow;

      }

      ppane->m_bTabPaneVisible = bShow;

      set_need_layout();

      return true;

   }


   bool tab::hide_tab(::collection::index iIndex)
   {

      if (iIndex < 0)
      {

         return false;

      }

      if (!show_pane(iIndex, false))
      {

         return false;

      }

      return true;

   }


   bool tab::hide_place_holder_by_id(const ::atom & atomTab)
   {

      auto ptabpane = get_tab_by_id(atomTab);

      if (::is_null(ptabpane))
      {

         return false;

      }

      auto pplaceholder = ptabpane->m_pplaceholder;

      if (::is_null(pplaceholder))
      {

         return false;

      }

      pplaceholder->hide();

      //      pplaceholder->set_need_redraw();
      //
      //      pplaceholder->post_redraw();

      return true;

   }


   ::user::interaction * tab::tab_window(::collection::index iIndex)
   {

      ::pointer<place_holder>pholder = tab_holder(iIndex);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::tab_holder(::collection::index iIndex)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   ::user::interaction * tab::pane_window(::collection::index iIndex)
   {

      ::pointer<place_holder>pholder = pane_holder(iIndex);

      if (pholder.is_null())
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   ::user::place_holder * tab::pane_holder(::collection::index iIndex)
   {

      auto ppane = get_tab(iIndex);

      if (ppane == nullptr)
      {

         return nullptr;

      }

      return ppane->m_pplaceholder;

   }


   ::user::tab_pane * tab::get_tab(::collection::index iIndex)
   {

      if (iIndex < 0)
      {

         return nullptr;

      }

      if (iIndex >= get_data()->m_tabpanea.get_count())
      {

         return nullptr;

      }

      return get_data()->m_tabpanea.element_at(iIndex);

   }


   ::user::tab_pane * tab::get_visible_tab(::collection::index iVisibleIndex)
   {

      auto iIndex = visible_index_index(iVisibleIndex);

      if (iIndex < 0)
      {

         return nullptr;

      }

      auto ptabpane = get_tab(iIndex);

      return ptabpane;

   }


   //::user::tab_pane * tab::get_tab(::collection::index iIndex)
   //{

   //   index iIndex = get_pane(iIndex);

   //   if(iIndex < 0)
   //   {

   //      return nullptr;

   //   }

   //   return get_data()->m_tabpanea.element_at(iIndex);

   //}


//   void tab::set_current_tab_by_index(::collection::index iIndex)
//   {
////      if(get_tab_holder(get_current_tab_index()) != nullptr)
//      //    {
//      //     get_tab_holder(get_current_tab_index())->display(e_display_none);
//      // }
//      set_current_tab_by_index(iIndex);
//      // if(get_tab_holder(get_current_tab_index()) != nullptr)
//      //{
//      // get_tab_holder(get_current_tab_index())->display(e_display_normal);
//      // }
//
//      //on_layout(pgraphics);
//
//   }



   //bool tab::are_tabs_visible() const
   //{
   //   
   //   if (m_bHideTabsOnFullScreenOrTransparentFrame)
   //   {

   //      auto bVisible = full_screen_or_transparent_frame_tab_visibility();
   //      
   //      if (is_different(bVisible, m_bCalculatedVisibleTabs))
   //      {

   //         m_timeLastTabVisibilityChange.Now();

   //         if (m_timeLastTabVisibityChange.elapsed() > 2_s)
   //         {

   //            m_bCalculatedVisibleTabs = bVisible;

   //         }

   //      }

   //   }
   //   else if (m_bVisibleTabs)
   //   {

   //      m_bCalculatedVisibleTabs = m_bVisibleTabs;

   //   }

   //   return m_bCalculatedVisibleTabs;

   //}


   void tab::on_change_cur_sel()
   {

      if (get_data()->m_pcallback != nullptr && dynamic_cast <::user::tab *> (get_data()->m_pcallback) != this)
      {

         get_data()->m_pcallback->_001OnShowTab(this);

      }

      ::pointer<::base::application>papp = get_app();

      papp->on_change_cur_sel(this);

   }


   void tab::on_after_change_cur_sel()
   {


   }


   void tab::_001SetVertical(bool bVertical)
   {

      get_data()->m_bVertical = bVertical;

   }


   void tab::_001ConnectParent(::channel * pchannel)
   {

      __UNREFERENCED_PARAMETER(pchannel);

   }


   atom tab::get_current_tab_id()
   {

      return index_id(get_current_tab_index());

   }


   //::collection::index tab::id_index(atom atom)
   //{

   //   index iIndex = -1;

   //   for(::collection::index iIndex = 0; iIndex < get_data()->m_tabpanea.get_size(); iIndex++)
   //   {

   //      if (get_data()->m_tabpanea[iIndex]->m_bTabPaneVisible)
   //      {

   //         iIndex++;

   //      }

   //      if (get_data()->m_tabpanea[iIndex]->m_atom == atom)
   //      {

   //         return iIndex;

   //      }

   //   }

   //   return -1;

   //}



   //atom tab::index_id(::collection::index iIndex)
   //{

   //   for(i32 iIndex = 0; iIndex < get_data()->m_tabpanea.get_count(); iIndex++)
   //   {

   //      if(get_data()->m_tabpanea[iIndex]->m_bTabPaneVisible)
   //      {

   //         if(iIndex <= 0)
   //         {

   //            return get_data()->m_tabpanea[iIndex]->m_atom;

   //         }
   //         else
   //         {

   //            iIndex--;

   //         }

   //      }

   //   }

   //   return atom();

   //}


   bool tab::set_current_tab_by_id(const ::atom & atom, ::request * prequest)
   {

      try
      {

         if (::is_set(prequest))
         {

            m_pusersystem->m_prequest = prequest;

         }

         ::collection::index iIndex = id_index(atom);

         if (iIndex < 0)
         {

            auto ptabpane = create_tab_by_id(atom);

            if (ptabpane == nullptr)
            {

               return false;

            }

            iIndex = id_index(atom);

            if (iIndex < 0)
            {

               return false;

            }

         }

         set_current_tab_by_index(iIndex);

      }
      catch (const ::exit_exception & exception)
      {

         throw exception;

      }
      catch (const ::exception &)
      {

         return false;

      }
      catch (...)
      {

         return false;

      }

      if (::is_set(prequest) && prequest == m_pusersystem->m_prequest)
      {

         m_pusersystem->m_prequest = nullptr;

      }

      return true;

   }


   ::user::tab_pane * tab::get_current_tab()
   {

      auto atom = get_current_tab_id();

      auto ptabpane = get_tab_by_id(atom);

      if (::is_null(ptabpane))
      {

         return nullptr;

      }

      return ptabpane;

   }


   enum_position tab::DragHitTest(const ::point_i32 & point)
   {
      ::rectangle_i32 rectangle;
      GetDragRect(rectangle, e_position_top);
      if (rectangle.contains(point))
      {
         return e_position_top;
      }
      GetDragRect(rectangle, e_position_bottom);

      if (rectangle.contains(point))
      {

         return e_position_bottom;

      }

      GetDragRect(rectangle, e_position_left);

      if (rectangle.contains(point))
      {

         return e_position_left;

      }

      GetDragRect(rectangle, e_position_right);

      if (rectangle.contains(point))
      {

         return e_position_right;

      }

      return e_position_none;

   }


   void tab::GetDragRect(::rectangle_i32 & rectangle, enum_position eposition)
   {

      switch (eposition)
      {
      case e_position_top:
      {

         rectangle.top() = get_data()->m_rectangleHosting.top();

         rectangle.left() = get_data()->m_rectangleHosting.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.right() = rectangle.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.bottom() = rectangle.top() + get_data()->m_rectangleHosting.height() / 3;

      }
      break;
      case e_position_left:
      {
         rectangle.top() = get_data()->m_rectangleHosting.top() + get_data()->m_rectangleHosting.height() / 3;

         rectangle.left() = get_data()->m_rectangleHosting.left();

         rectangle.right() = rectangle.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.bottom() = rectangle.top() + get_data()->m_rectangleHosting.height() / 3;

      }
      break;
      case e_position_right:
      {
         rectangle.top() = get_data()->m_rectangleHosting.top() + get_data()->m_rectangleHosting.height() / 3;

         rectangle.left() = get_data()->m_rectangleHosting.left() + get_data()->m_rectangleHosting.width() * 2 / 3;

         rectangle.right() = rectangle.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.bottom() = rectangle.top() + get_data()->m_rectangleHosting.height() / 3;

      }
      break;
      case e_position_bottom:
      {
         rectangle.top() = get_data()->m_rectangleHosting.top() + get_data()->m_rectangleHosting.height() * 2 / 3;

         rectangle.left() = get_data()->m_rectangleHosting.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.right() = rectangle.left() + get_data()->m_rectangleHosting.width() / 3;

         rectangle.bottom() = rectangle.top() + get_data()->m_rectangleHosting.height() / 3;

      }
      break;
      default:
         break;
      }
   }



   void tab::_001OnDropTab(::collection::index iIndex, enum_position eposition)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001OnDropTab(iIndex, eposition);

      }

   }


   ::user::interaction * tab::get_impact_uie()
   {

      return nullptr;

   }


   void tab::get_child_rect(::rectangle_i32 & rectangle)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      rectangle = get_data()->m_rectangleHosting;

   }


   void tab::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::interaction::handle(ptopic, pcontext);

      ::user::auto_hide::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_get_topic_impact_id)
      {

         ptopic->payload(id_id) = get_current_tab_id();

         ptopic->m_bRet = true;

      }
      else if (ptopic->m_atom == id_set_topic_impact_by_id)
      {

         set_current_tab_by_id(ptopic->payload(id_id));

         ptopic->m_bRet = true;

      }
      else if (ptopic->m_atom == id_place_child_title_change)
      {

         for (auto & ppane : get_data()->m_tabpanea)
         {

            if (ppane->m_pplaceholder == ptopic->m_puserelement)
            {

               auto puserinteractionpointeraChild = ppane->m_pplaceholder->m_puserinteractionpointeraChild;

               auto pchild = puserinteractionpointeraChild->first_interaction();

               if (pchild)
               {

                  string strTitle(pchild->payload("place_child_title").as_string());

                  ppane->set_title(strTitle);

               }

            }

         }

      }

   }


   void tab::rotate()
   {

      throw ::exception(todo);

   }


   void tab::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);

      ::user::auto_hide::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == e_timer_drag_start)
      {
         //auto elapsed = g_tickDragStart.elapsed();
         KillTimer(e_timer_drag_start);

         defer_release_mouse_capture();

         auto pointCursor = mouse_cursor_position();

         auto pitem = hit_test(pointCursor, ::user::e_zorder_any);

         ::collection::index iClickTab = get_data()->m_iClickTab;

         if (::is_item(pitem, iClickTab))
         {

            get_data()->m_bDrag = true;

            m_estate = state_drag_commanded;

            post_message(message_start_tab_drag);

         }
         else
         {

            m_estate = e_state_initial;

         }

      }

   }


   void tab::_001OnStartTabDrag(::message::message * pmessage)
   {

      if (get_data()->m_pcallback != nullptr)
      {

         get_data()->m_pcallback->_001DropTargetWindowInitialize(this);


      }

      if (m_estate == state_drag_commanded)
      {

         m_estate = e_state_initial;

      }

   }


   //void tab::_000OnMouse(::message::mouse * pmouse)
   //{

   //   if(m_bShowTabs)
   //   {

   //      // these try catchs are needed for multi threading supporting: multi threaded windows: an endeavour
   //      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
   //      // to debug, enable catch exceptions in debugger
   //      try
   //      {

   //         ::rectangle_i32 rectangleTabScreen(get_data()->m_rectangleTab);

   //         client_to_screen(rectangleTabScreen);

   //         if ((pmouse->m_atom == e_message_left_button_down || pmouse->m_atom == e_message_left_button_up) && rectangleTabScreen.contains(pmouse->m_point))
   //         {

   //            route_message(pmouse);

   //            if (pmouse->m_lresult != 0)
   //            {

   //               return;

   //            }

   //         }
   //         else if (pmouse->m_atom == e_message_mouse_move)
   //         {

   //            route_message(pmouse);

   //            if (pmouse->m_lresult != 0)
   //            {

   //               return;

   //            }

   //         }

   //      }
   //      catch(...)
   //      {

   //      }

   //   }
   //   else if(pmouse->m_atom == e_message_mouse_move)
   //   {

   //   }

   //   ::pointer<::user::interaction>pinteraction;


   //   while(rget_child(pinteraction))
   //   {

   //      try
   //      {

   //         if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
   //         {

   //            try
   //            {

   //               pinteraction->_000OnMouse(pmouse);

   //               if (pmouse->m_bRet)
   //               {

   //                  return;

   //               }

   //            }
   //            catch(...)
   //            {

   //            }

   //         }

   //      }
   //      catch(...)
   //      {

   //      }

   //   }

   //}


   //tab_data * tab::get_data()
   //{

   //   return m_pdata;

   //}


   ::user::tab_pane * tab::get_tab_by_id(const ::atom & atom)
   {

      return get_data()->get_tab_by_id(atom);

   }


   //::user::tab_pane * tab::create_tab_by_id(atom atom)
   //{

   //   create_tab_by_id(atom);

   //   return get_data()->get_tab_by_id(atom);

   //}


   ::user::tab_pane * tab::create_tab_by_id(const ::atom & atom)
   {

      if (!add_tab("", atom))
      {

         return nullptr;

      }

      ::collection::index iIndex = id_index(atom);

      if (iIndex < 0)
      {

         return nullptr;

      }

      auto ppaneTab = get_tab(iIndex);

      return ppaneTab;

   }


   /// array - if you want, you can hint on_change_tab_count
   /// with added panes info. Pass array with nullptr value to force save restorable tabs
   void tab::on_change_tab_count(array < ::user::tab_pane * > array)
   {

      bool bAny = false;

      for (auto ppane : array)
      {

         if (ppane == nullptr || matches_restorable_tab(ppane->m_atom, ppane->m_pplaceholder))
         {

            bAny = true;

            break;

         }

      }

      if (array.is_empty() || bAny)
      {

         save_restorable_tabs();

      }
      else
      {

         informationf("Yup! Optimized Out a save_restorable_tabs {?A*dev}op! ...... . .");

      }

   }


   void tab::save_restorable_tabs()
   {

      if (m_bDisableSavingRestorableTabs)
      {

         return;

      }

      if (get_data()->m_matchanyRestore.m_itema.get_count() > 0)
      {

         payload_array payloada;

         get_restore_tab(payloada);

         //if (payloada.get_size() > 0)
         //{
         //   informationf(".");
         //   for (::collection::index i = 0; i < 200; i++)
         //   {


         //datastream()->set("restore_tab", payloada);
         //   }
         //}
         //else
         //{
         //   informationf("o");
         //   for (::collection::index i = 0; i < 200; i++)
         //   {


         //      data_save("restore_tab", payloada);
         //   }

         //}

      }


   }


   void tab::get_text_id(string_array & stra)
   {

      get_presuffixed_ci_id(stra, nullptr, nullptr);

   }


   void tab::get_prefixed_ci_id(string_array & stra, const ::string & pszPrefix)
   {

      get_presuffixed_ci_id(stra, pszPrefix, nullptr);

   }


   void tab::get_suffixed_ci_id(string_array & stra, const ::string & pszSuffix)
   {

      get_presuffixed_ci_id(stra, nullptr, pszSuffix);

   }


   void tab::get_presuffixed_ci_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      auto & panea = get_data()->m_tabpanea;

      for (i32 i = 0; i < panea.get_count(); i++)
      {

         auto ppane = panea[i].get();

         strPath = ppane->m_atom;

         if (strPrefix.is_empty() || strPath.case_insensitive_begins(strPrefix))
         {

            if (strSuffix.is_empty() || strPath.case_insensitive_ends(strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   void tab::get_begins_ci_eat_id(string_array & stra, const ::string & pszPrefix)
   {

      get_begins_ends_ci_eat_id(stra, pszPrefix, nullptr);

   }


   void tab::get_ends_ci_eat_id(string_array & stra, const ::string & pszSuffix)
   {

      get_begins_ends_ci_eat_id(stra, nullptr, pszSuffix);

   }


   void tab::get_begins_ends_ci_eat_id(string_array & stra, const ::string & pszPrefix, const ::string & pszSuffix)
   {

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

      string strPath;

      tab_pane_array & panea = get_data()->m_tabpanea;

      for (i32 i = 0; i < panea.get_count(); i++)
      {

         auto ppane = panea[i].get();

         strPath = ppane->m_atom;

         if (strPrefix.is_empty() || strPath.case_insensitive_begins(strPrefix))
         {

            if (strSuffix.is_empty() || strPath.case_insensitive_ends(strSuffix))
            {

               stra.add(strPath);

            }

         }

      }

   }


   bool tab::matches_restorable_tab(const ::payload & varId, ::user::place_holder * pholder)
   {

      ::match::any & matchany = get_data()->m_matchanyRestore;

      if (pholder != nullptr && pholder->payload("void_restore").is_true())
      {

         return false;

      }

      if (!matchany.has_item())
      {

         return false;

      }

      if (!matchany.matches(varId))
      {

         return false;

      }

      return true;

   }

   void tab::get_restore_tab(payload_array & payloada)
   {

      ::payload varId;

      tab_pane_array & panea = get_data()->m_tabpanea;

      for (i32 i = 0; i < panea.get_count(); i++)
      {

         varId = panea[i]->m_atom;

         if (matches_restorable_tab(varId, panea[i]->m_pplaceholder))
         {

            payloada.add(varId);

         }

      }

   }


   void tab::create_tabs()
   {

      m_iRestoredTabCount = restore_tabs();

      on_create_tabs();

      m_bCreatedTabs = true;

   }


   bool tab::has_restore_tab()
   {

      ::match::any & matchany = get_data()->m_matchanyRestore;

      if (matchany.is_there_no_item())
         return false;
      ::payload varId;
      tab_pane_array & panea = get_data()->m_tabpanea;
      for (i32 i = 0; i < panea.get_count(); i++)
      {
         varId = panea[i]->m_atom;
         if (matchany.matches(varId))
         {
            return true;
         }
      }

      return false;

   }


   ::collection::count tab::open_tabs(const payload_array & payloada)
   {

      ::collection::count c = 0;

      string_array stra;

      for (i32 i = 0; i < payloada.get_count(); i++)
      {

         // ODOW : TODO : should create bergedgewrapper to open bergedge inside a window.

         if (payloada[i].get_type() == ::e_type_string && payloada[i].as_string() == "app:bergedge")
            continue;

         if (payloada[i].get_type() == ::e_type_string && payloada[i].as_string() == "app:")
            continue;

         //if(stra.add_unique(payloada[i]) >= 0)
         //{
         //create_tab_by_id(stra.last());

         set_current_tab_by_id(payloada[i].as_atom());

         c++;

         //}

      }

      return c;

   }


   void tab::_001CloseTab(::collection::index iIndex)
   {

      erase_tab_by_id(index_id(iIndex));

   }


   void tab::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //      ::pointer<::message::show_window>pshowwindow(pmessage);

      //      ::user::place_holder * pholder = tab_holder(get_current_tab_index());
      //
      //      if (pholder != nullptr)
      //      {
      //
      //         if (pshowwindow->m_bShow)
      //         {
      //
      //            pholder->display(e_display_normal);
      //
      //         }
      //         else
      //         {
      //
      //            pholder->display(e_display_none);
      //
      //         }
      //
      //      }

   }


   ::rectangle_i32 tab::hosting_rectangle(::user::enum_layout elayout)
   {

      return m_pdata->m_rectangleHosting;

   }



} // namespace base


