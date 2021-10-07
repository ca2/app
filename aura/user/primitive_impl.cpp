#include "framework.h"
#include "aura/user/_user.h"
#include "aura/id.h"
#include "interaction_thread.h"
#include "call_message_handler_task.h"
#include "acme/node/operating_system/_user.h"


namespace user
{


   iptr_map < string > * g_p = nullptr;


   primitive_impl::primitive_impl()
   {

      m_pinteractionimpl = nullptr;
      m_pinteractionchild = nullptr;
      //m_bDestroying = false;
      m_bDestroyImplOnly = false;
      m_iPendingRectMatch = -1;
      m_bPendingRedraw = false;
      m_puserinteraction = nullptr;
      m_bIgnoreSizeEvent = false;
      m_bIgnoreMoveEvent = false;
      m_bUserElementOk = true;

   }


   primitive_impl::~primitive_impl()
   {

   }


   bool primitive_impl::create_message_queue(::user::interaction * pinteraction, const ::string & lpszName)
   {

      throw ::interface_only_exception();

      return true;

   }


   //bool primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * pparent)
   //{

   //   throw ::interface_only_exception();

   //   return true;

   //}


   //bool primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * puiParent)

   //{

   //   throw ::interface_only_exception();

   //   return false;

   //}


   //bool primitive_impl::create_window_ex(::user::interaction * pinteraction, __pointer(::user::system) pcs, ::user::primitive * puiParent, id id)
   //{

   //   throw ::interface_only_exception();

   //   return true;

   //}


   //bool primitive_impl::create_interaction(::user::interaction * pinteraction, ::user::primitive * pparent)
   //{

   //   throw ::interface_only_exception();

   //   return true;

   //}

   ::user::interaction_impl * primitive_impl::get_user_interaction_impl()
   {

      return nullptr;

   }


   ::user::interaction_child * primitive_impl::get_user_interaction_child()
   {

      return nullptr;

   }



   void primitive_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

      if (m_puserinteraction->m_puserinteractionParent != nullptr)
      {

         m_puserinteraction->m_puserinteractionParent->set_need_layout();

      }

   }


   void primitive_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //m_puserinteraction->message_call(e_message_size, 0, process_state().m_size.lparam());

      //m_puserinteraction->m_durationLastVisualChange.Now();

      //m_puserinteraction->m_bSizeMove = true;


   }


   void primitive_impl::on_reposition()
   {

   }


   void primitive_impl::on_show_window()
   {

   }


   ::e_status primitive_impl::destroy()
   {

      ::user::primitive::destroy();

      auto estatus = m_puserinteraction.release();

      return estatus;

   }


   //void primitive_impl::finish()
   //{

   //   ::user::primitive::finish();

   //}


   bool primitive_impl::prodevian_update_screen()
   {

      return true;

   }


   void primitive_impl::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, id idLeft, ::u32 nFlags, RECTANGLE_I32 * prectParam, const rectangle_i32 & rectangleClient, bool bStretch)
   {

      if (!_is_window())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(nIDFirst);

      __UNREFERENCED_PARAMETER(nIDLast);

      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || (nFlags & ~reposNoPosLeftOver) == reposExtra);

      SIZEPARENTPARAMS sizeparentparams;

      __pointer(::user::interaction) puiLeft;

      sizeparentparams.bStretch = bStretch;

      sizeparentparams.sizeTotal.cx = sizeparentparams.sizeTotal.cy = 0;

      if (rectangleClient != nullptr)
      {

         sizeparentparams.rectangle = rectangleClient;

      }
      else
      {

         m_puserinteraction->get_client_rect(&sizeparentparams.rectangle);

      }

      if (::is_empty(sizeparentparams.rectangle))
      {

         return;

      }

      __pointer(::user::interaction) pinteraction;

      while (m_puserinteraction->get_child(pinteraction))
      {

         id id = pinteraction->GetDlgCtrlId();

         if (id == idLeft)
         {

            puiLeft = pinteraction;

         }
         else
         {

            pinteraction->send_message(e_message_size_parent, 0, (lparam)& sizeparentparams);

         }

      }

      if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
      {

         ASSERT(prectParam != nullptr);

         if (bStretch)
         {

            ::copy(prectParam, &sizeparentparams.rectangle);

         }
         else
         {

            prectParam->left = prectParam->top = 0;

            prectParam->right = sizeparentparams.sizeTotal.cx;

            prectParam->bottom = sizeparentparams.sizeTotal.cy;


         }

         return;

      }


      if (!idLeft.is_empty() && puiLeft != nullptr)
      {

         if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {

            ASSERT(prectParam != nullptr);


            sizeparentparams.rectangle.left += prectParam->left;

            sizeparentparams.rectangle.top += prectParam->top;

            sizeparentparams.rectangle.right -= prectParam->right;

            sizeparentparams.rectangle.bottom -= prectParam->bottom;


         }

         if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
         {

            //puiLeft->CalcWindowRect(&sizeparentparams.rectangle);

            puiLeft->place(sizeparentparams.rectangle);

            puiLeft->display();

         }

      }

   }


   bool primitive_impl::window_move(i32 x, i32 y)
   {

      return true;

   }


   //::e_status primitive_impl::main_async(const promise::routine & routine, enum_priority epriority)
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return ::error_failed;

   //   }

   //   auto puserinteraction = m_puserinteraction->get_wnd();

   //   if (!puserinteraction)
   //   {

   //       return ::error_failed;

   //   }

   //   return puserinteraction->post_routine(routine, epriority);

   //}


   void primitive_impl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void primitive_impl::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_puserinteraction)
      {

         return;

      }

      string strType = ::str::demangle(m_puserinteraction->type_name());

      if (strType.contains("list_box"))
      {

         output_debug_string("list_box");

      }

      windowing_output_debug_string("\ninteraction_impl_base::_001Print");

      m_puserinteraction->_001Print(pgraphics);

   }


   void primitive_impl::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_000CallOnDraw(pgraphics);

      }

   }


   void primitive_impl::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_001DrawThis(pgraphics);

      }

   }


   void primitive_impl::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->_001DrawChildren(pgraphics);

      }

   }


   void primitive_impl::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->draw_control_background(pgraphics);

      }

   }


   void primitive_impl::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void primitive_impl::viewport_client_to_screen(POINT_I32 * ppt)
   {

      if (m_puserinteraction)
      {

         ::point_add(ppt, m_puserinteraction->layout().design().origin());

      }

   }


   void primitive_impl::viewport_screen_to_client(POINT_I32 * ppt)
   {

      if (m_puserinteraction)
      {

         ::point_sub(ppt, m_puserinteraction->layout().design().origin());

      }

   }


   void primitive_impl::viewport_client_to_screen(RECTANGLE_I32 * prectangle)
   {

      viewport_client_to_screen((POINT_I32 *)& prectangle->left);
      viewport_client_to_screen((POINT_I32 *)& prectangle->right);

   }


   void primitive_impl::viewport_screen_to_client(RECTANGLE_I32 * prectangle)
   {

      viewport_screen_to_client((POINT_I32 *)& prectangle->left);
      viewport_screen_to_client((POINT_I32 *)& prectangle->right);

   }


   bool primitive_impl::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   //u32 primitive_impl::GetStyle() const
   //{

   //   return get_window_long(GWL_STYLE);

   //}


   //u32 primitive_impl::GetExStyle() const
   //{

   //   return get_window_long(GWL_EXSTYLE);

   //}


   //bool primitive_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   ::i32 l = GetStyle();

   //   l |= dwAdd;

   //   ::i32 lRemove = ~dwRemove;

   //   l &= lRemove;

   //   set_window_long(GWL_STYLE, l);

   //   return true;

   //}


   //bool primitive_impl::ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   set_window_long(GWL_EXSTYLE, (GetExStyle() | dwAdd) & ~dwRemove);

   //   return true;

   //}


//   ::i32 primitive_impl::get_window_long(i32 nIndex) const
//   {
//
//      return (::i32)get_window_long_ptr(nIndex);
//
//   }
//
//
//   ::i32 primitive_impl::set_window_long(i32 nIndex, ::i32 lValue)
//   {
//
//      return (::i32)set_window_long_ptr(nIndex, lValue);
//
//   }
//
//
//   iptr primitive_impl::get_window_long_ptr(i32 nIndex) const
//   {
//
////      return 0;
//////
//////      if (nIndex == GWL_STYLE)
//////      {
//////
//////         return  m_uStyle;
//////
//////      }
//////      else if (nIndex == GWL_EXSTYLE)
//////      {
//////
//////         return  m_uExStyle;
//////
//////      }
//////
//////      synchronous_lock synchronouslock(&((primitive_impl *)this)->m_mutexLongPtr);
//////
//////      return (LONG_PTR)m_longptr[nIndex];
////
//      return m_iptrmap[nIndex];
//
//   }
//
//
//   ::e_status primitive_impl::set_window_long_ptr(i32 nIndex, iptr lValue)
//   {
//
////      if (nIndex == GWL_STYLE)
////      {
////
////         return m_uStyle = lValue;
////
////      }
////      else if (nIndex == GWL_EXSTYLE)
////      {
////
////         return m_uExStyle = lValue;
////
////      }
////
////      synchronous_lock synchronouslock(&m_mutexLongPtr);
////
////      m_longptr[nIndex] = lValue;
////
////      return lValue;
//
//      //return lValue;
//
//      return m_iptrmap[nIndex] = lValue;
//
//   }


   id primitive_impl::GetDlgCtrlId() const
   {

      if (!m_puserinteraction)
      {

         return ::id::e_type_null;

      }

      return m_puserinteraction->GetDlgCtrlId();

   }


   id primitive_impl::SetDlgCtrlId(id id)
   {

      if (!m_puserinteraction)
      {

         return id::e_type_null;

      }

      return m_puserinteraction->SetDlgCtrlId(id);

   }



   ::user::interaction * primitive_impl::first_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * primitive_impl::top_child()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->first_child();

   }


   ::user::interaction * primitive_impl::under_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling();

   }


   ::user::interaction * primitive_impl::above_sibling()
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling();

   }


   ::user::interaction * primitive_impl::above_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->above_sibling(pinteraction);

   }


   ::user::interaction * primitive_impl::under_sibling(::user::interaction * pinteraction)
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->under_sibling(pinteraction);

   }


   ::u32 primitive_impl::ArrangeIconicWindows()
   {

      //      return m_puserinteraction->ArrangeIconicWindows();
      return 0;

   }


   bool primitive_impl::is_ascendant(const ::user::primitive * puiIsAscendant, bool bIncludeSelf) const
   {

      if (::is_null(puiIsAscendant))
      {

         return false;

      }

      return puiIsAscendant->is_descendant(m_puserinteraction, bIncludeSelf);

   }


   bool primitive_impl::is_parent(const ::user::primitive * puiIsParent) const
   {

      if (puiIsParent == nullptr)
      {

         return false;

      }

      return puiIsParent->is_child(m_puserinteraction);

   }


   bool primitive_impl::is_child(const ::user::primitive * puiIsChild) const
   {

      if (puiIsChild == nullptr)
      {

         return false;

      }

      ::user::interaction * puiProbe = puiIsChild->get_parent();

      return puiProbe == m_puserinteraction;

   }


   bool primitive_impl::is_descendant(const ::user::primitive * puiIsDescendant, bool bIncludeSelf) const
   {

      const ::user::primitive * puiProbe;

      if (bIncludeSelf)
      {

         puiProbe = puiIsDescendant;

      }
      else
      {

         puiProbe = puiIsDescendant->get_parent();

      }

      if (::is_null(puiProbe))
      {

         return false;

      }

      do
      {

         if (puiProbe == m_puserinteraction.m_p)
         {

            return true;

         }

         puiProbe = puiProbe->get_parent();

      } while (puiProbe != nullptr);

      return false;

   }


   ::user::interaction * primitive_impl::get_wnd() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd();

   }


   ::user::interaction * primitive_impl::get_wnd(::u32 nCmd) const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_wnd(nCmd);

   }


   //::user::interaction * primitive_impl::GetTopWindow() const
   //{

   //   auto pinteraction = get_wnd();

   //   if (!pinteraction)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetTopWindow();

   //}


   ::user::interaction * primitive_impl::get_parent() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent();

   }


   ::user::interaction * primitive_impl::get_owner() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->m_puserinteractionOwner;

   }


   ::user::frame * primitive_impl::frame() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->frame();

   }


   ::user::frame * primitive_impl::get_parent_frame() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_frame();

   }


   ::user::interaction * primitive_impl::get_parent_owner() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_owner();

   }


   ::user::interaction * primitive_impl::get_parent_or_owner() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_parent_or_owner();

   }


   ::user::interaction * primitive_impl::get_top_level_owner() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_top_level_owner();

   }


   ::user::frame * primitive_impl::top_level_frame() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->top_level_frame();

   }


   ::user::interaction * primitive_impl::get_top_level() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      return m_puserinteraction->get_top_level();

   }


   lresult primitive_impl::message_call(const ::id & id, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      ___pointer < ::message::message > pmessage;

      if (m_puserinteraction)
      {

         pmessage = m_puserinteraction->get_message(id, wparam, lparam);

      }
      else
      {

         pmessage = get_message(id, wparam, lparam);

      }

      return message_call(pmessage);

   }


   lresult primitive_impl::message_call(::message::message * pmessage)
   {

      if (m_puserinteraction == nullptr)
      {

         message_handler(pmessage);

         return pmessage->m_lresult;

      }

      if (m_puserinteraction->layout().is_moving())
      {
         
         TRACE("moving: skip walk pre translate tree");

      }
      else if (m_puserinteraction->layout().is_sizing())
      {
         
         TRACE("sizing: skip walk pre translate tree");

      }
      else
      {

         m_puserinteraction->walk_pre_translate_tree(pmessage);

         if (pmessage->m_bRet)
         {

            return pmessage->m_lresult;

         }

      }

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void primitive_impl::send_message_to_descendants(const ::id & id, wparam wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {

      return m_puserinteraction->send_message_to_descendants(id, wparam, lparam, bDeep, bOnlyPerm);

   }


   void primitive_impl::pre_translate_message(::message::message * pmessage)
   {

      m_puserinteraction->pre_translate_message(pmessage);

   }


   //bool primitive_impl::set_capture(::user::interaction * pinteraction)
   //{

   //   return get_host_window()->set_capture(pinteraction);

   //}


   //::user::interaction * primitive_impl::get_capture() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_capture();

   //}


   //bool primitive_impl::set_keyboard_focus(::user::interaction * pinteraction)
   //{

   //   return get_host_window()->set_keyboard_focus(pinteraction);

   //}


   //::user::interaction * primitive_impl::get_keyboard_focus() const
   //{

   //   ::user::interaction * pinteraction = get_wnd();

   //   if (pinteraction == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_keyboard_focus();

   //}


   bool primitive_impl::get_rect_normal(RECTANGLE_I32 * prectangle)
   {

      *prectangle = m_puserinteraction->screen_rect();

      return true;

   }


   bool primitive_impl::SetTimer(uptr uEvent, ::duration millisEllapse, PFN_TIMER pfnTimer)
   {

      if (millisEllapse < 500_ms)
      {

         //         string str;
         //
         //         str.Format("creating fast timer: %d\n", nEllapse);
         //
         //         ::output_debug_string(str);

      }

      if (m_ptimerarray.is_null())
      {

         __compose_new(m_ptimerarray);

         m_ptimerarray->m_pcallback = m_puserinteraction;

         //m_ptimerarray->set_context_thread(m_puserinteraction->m_pthreadUserInteraction);

      }

      return m_ptimerarray->create_timer(this, uEvent, millisEllapse, pfnTimer, true);

   }


   bool primitive_impl::KillTimer(uptr uEvent)
   {

      if (m_ptimerarray.is_null())
      {

         return true;

      }

      return m_ptimerarray->delete_timer(uEvent);

   }


   void primitive_impl::_001OnTimer(::timer * ptimer)
   {

      if (m_puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteraction->_001OnTimer(ptimer);

   }


   //void primitive_impl::defer_start_prodevian()
   //{

   //   m_puserinteraction->post_simple_command(e_simple_command_defer_start_prodevian);

   //}


   //void primitive_impl::_defer_start_prodevian()
   //{

   //}

   bool primitive_impl::destroy_impl_only()
   {

      auto pinteraction = m_puserinteraction;

      m_bDestroyImplOnly = true;

      if (::is_set(m_puserinteraction))
      {

//         m_puserinteraction->transfer_receiver(m_idroute, this);
//
         auto puserinteraction = m_puserinteraction->get_wnd();

         if (::is_set(puserinteraction))
         {

            auto pimpl2 = puserinteraction->m_pimpl2;

            if (pimpl2)
            {

               synchronous_lock synchronouslock(pimpl2->mutex());

               pimpl2->m_userinteractionaMouseHover.erase(m_puserinteraction);

            }

         }

         m_puserinteraction->m_puserinteractionParent = nullptr;

      }

      m_puserinteraction = nullptr;

      bool bOk = start_destroying_window();

      //TRACE("destroy_impl_only DestroyWindow %d", bOk != false);

      return bOk;

   }


   bool primitive_impl::start_destroying_window()
   {

      if (!m_bUserElementOk)
      {

         return true;

      }

      m_bUserElementOk = false;

      if (m_puserinteraction == nullptr && !m_bDestroyImplOnly)
      {

         return false;

      }

      __pointer(::user::primitive_impl) pimplThis = this;

      __pointer(::user::interaction) puiThis = m_puserinteraction;

      if(puiThis)
      {

         try
         {

            puiThis->send_message(e_message_destroy);

         }
         catch (...)
         {

         }

         try
         {

            puiThis->send_message(e_message_non_client_destroy);

         }
         catch (...)
         {

         }

      }

      return true;

   }


   bool primitive_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      ::user::interaction * pinteraction = get_host_window();

      if (!pinteraction)
      {

         return false;

      }

      auto bOk = pinteraction->mouse_hover_add(pinterface);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   bool primitive_impl::mouse_hover_erase(::user::interaction * pinterface)
   {

      ::user::interaction * pinteraction = get_host_window();

      if (pinteraction != nullptr)
      {

         return pinteraction->mouse_hover_erase(pinterface);

      }

      return false;

   }


   void primitive_impl::register_drop_target()
   {
   }


   ::user::primitive * primitive_impl::get_keyboard_focus()
   {

      return nullptr;

   }


   ::e_status primitive_impl::set_keyboard_focus(::user::primitive * pprimitive)
   {

      __UNREFERENCED_PARAMETER(pprimitive);

      return ::error_failed;

   }


   ::e_status primitive_impl::erase_keyboard_focus(::user::primitive * pprimitive)
   {

      __UNREFERENCED_PARAMETER(pprimitive);

      return ::error_failed;

   }


   ::e_status primitive_impl::clear_keyboard_focus()
   {

      return ::error_failed;

   }


   ::e_status primitive_impl::impl_set_keyboard_focus(::user::primitive * pprimitive)
   {

      return ::error_failed;

   }


   ::e_status primitive_impl::impl_erase_keyboard_focus(::user::primitive * pprimitive)
   {

      return ::error_failed;

   }


   ::e_status primitive_impl::impl_clear_keyboard_focus()
   {

      return ::error_failed;

   }


   bool primitive_impl::post_message(const ::id & id, wparam wparam, lparam lparam)
   {

      if (::is_null(m_puserinteraction))
      {

         return false;

      }

      m_puserinteraction->post_routine(__new(call_message_handler_task(m_puserinteraction, id, wparam, lparam)));

      return true;

   }


   void primitive_impl::post_non_client_destroy()
   {

      __pointer(primitive_impl) pimpl = this;

      {

         synchronous_lock synchronouslock(mutex());

         try
         {

            erase_all_routes();

         }
         catch (...)
         {

         }

      }

      //::channel::on_finish();

      if (!m_bDestroyImplOnly && m_puserinteraction)
      {

         m_puserinteraction->post_non_client_destroy();

      }

      ::user::primitive::post_non_client_destroy();



      //if (m_puserinteraction->m_pthreadUserInteraction)
      //{

      //   auto pthread = m_puserinteraction->m_pthreadUserInteraction.cast < thread >();
      //
      //   if (pthread)
      //   {

      //      if (pthread->m_pimpl == this)
      //      {

      //         pthread->m_pimpl.release();

      //         pthread->finish();

      //      }

      //   }

      //}

      if (!m_bDestroyImplOnly)
      {

         m_puserinteraction.release();

      }

   }



   void primitive_impl::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      m_puserinteraction->set_need_redraw();

   }


   void primitive_impl::_001OnPrioCreate(::message::message * pmessage)
   {

      if (!m_puserinteraction)
      {

         return;

      }

      m_puserinteraction->run_property("on_create");
      m_puserinteraction->call_routine(CREATE_ROUTINE);

   }


   void primitive_impl::on_message_destroy(::message::message * pmessage)
   {

      //synchronous_lock synchronouslock(mutex());

      //try
      //{

      //   if (m_ptimerarray)
      //   {

      //      m_ptimerarray->destroy();

      //      m_ptimerarray.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(""));

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void primitive_impl::on_message_non_client_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && ::str::demangle(m_puserinteraction->type_name()).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

      post_non_client_destroy();

   }


   void primitive_impl::prio_install_message_routing(::channel * pchannel)
   {

      //if (g_p == nullptr)
      //{

      //   g_p = new iptr_map < string >;

      //}

      //g_p->set_at((iptr)this, ::str::demangle(m_puserinteraction->type_name()) + "xxx" + type_name());
      MESSAGE_LINK(e_message_show_window, pchannel, this, &primitive_impl::on_message_show_window);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &primitive_impl::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_destroy, pchannel, this, &primitive_impl::on_message_non_client_destroy);
      MESSAGE_LINK(e_message_create, pchannel, this, &primitive_impl::_001OnPrioCreate);

      if (m_puserinteraction && ::str::demangle(m_puserinteraction->type_name()).contains("notify_icon"))
      {

         INFORMATION("notify_icon");

      }

   }


   void primitive_impl::last_install_message_routing(::channel * pchannel)
   {


   }


   void primitive_impl::show_task(bool bShow)
   {

      __UNREFERENCED_PARAMETER(bShow);

   }


   void primitive_impl::redraw_add(::object * point_i32)
   {

   }


   void primitive_impl::redraw_erase(::object * point_i32)
   {

   }


   bool primitive_impl::has_redraw()
   {

      return false;

   }


   void primitive_impl::queue_message_handler(::message::message * pmessage)
   {

      return m_puserinteraction->message_handler(pmessage);

   }


   //bool primitive_impl::has_keyboard_focus() const
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   __pointer(::user::interaction) pinteraction = m_puserinteraction->get_host_window();

   //   if (pinteraction.is_null())
   //   {

   //      return false;

   //   }

   //   if (pinteraction == this)
   //   {

   //      return false;

   //   }

   //   if (!pinteraction->has_keyboard_focus())
   //   {

   //      return false;

   //   }

   //   __pointer(::user::interaction_impl) pimpl = pinteraction->m_pimpl;

   //   if (pimpl.is_null())
   //   {

   //      return false;

   //   }

   //   return pimpl->m_pprimitiveFocus == m_puserinteraction;

   //}


   //bool primitive_impl::is_active()
   //{

   //   if (m_puserinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction == m_puserinteraction->GetActiveWindow();

   //}


   bool primitive_impl::create_host(::user::interaction * puserinteraction)
   {

      return false;

   }


   bool primitive_impl::create_child(::user::interaction * puserinteraction, ::user::primitive * puserprimitiveParent)
   {

      return false;

   }


   //bool primitive_impl::is_this_enabled() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return false;

   //   }

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   // void primitive_impl::SetWindowDisplayChanged()
   // {

   // }


   void primitive_impl::window_show_change_visibility(::e_display edisplay, ::e_activation eactivation)
   {

   }


   bool primitive_impl::start_window_visual()
   {

      return true;

   }


   bool primitive_impl::enable_window(bool bEnable)
   {

      bool bWasDisabled = !(m_puserinteraction->m_ewindowflag & e_window_flag_enable);

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      return bWasDisabled;

   }


   ::e_status primitive_impl::show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd)
   {

      return error_interface_only;

   }


   ::e_status primitive_impl::hide_software_keyboard(::user::primitive * pprimitive)
   {

      return error_interface_only;

   }


   void primitive_impl::user_interaction_on_hide()
   {


   }


   i32 primitive_impl::GetUpdateRgn(class draw2d::region *,bool)
   {

      return 0;

   }


   void primitive_impl::Invalidate(bool)
   {


   }


   void primitive_impl::InvalidateRect(class rectangle_type<struct RECTANGLE_I32,struct POINT_I32,struct SIZE_I32> const &,bool)
   {


   }


   void primitive_impl::InvalidateRgn(class draw2d::region *,bool)
   {


   }


   void primitive_impl::ValidateRect(class rectangle_type<struct RECTANGLE_I32,struct POINT_I32,struct SIZE_I32> const &)
   {


   }


   void primitive_impl::ValidateRgn(class draw2d::region *)
   {


   }


   void primitive_impl::ShowOwnedPopups(bool)
   {


   }


   ::graphics::graphics * primitive_impl::get_window_graphics(void)
   {

      return nullptr;

   }


   bool primitive_impl::is_composite()
   {

      return false;

   }

   
   void primitive_impl::_task_transparent_mouse_event()
   {

   }


   bool primitive_impl::IsTopParentActive()
   {

      return false;

   }

} // namespace user



