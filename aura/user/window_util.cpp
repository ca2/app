#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#ifdef APPLEIOS
oswindow GetWindow(oswindow window, int iParentHood);
#endif


#ifdef WINDOWS_DESKTOP


#define MESSAGE_WINDOW_PARENT HWND_MESSAGE


#endif


namespace user
{


   void oswindow_array::SortByZOrder()
   {

      window_util::SortByZOrder(*this);

   }


   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void oswindow_array::SortSiblingsByZOrder()
   {

      oswindow oswindowSwap;

      for (i32 i = 0; i < this->get_size(); i++)
      {

         for (i32 j = i + 1; j < this->get_size(); j++)
         {

            if (window_util::GetZOrder(this->element_at(i)) > window_util::GetZOrder(this->element_at(j)))
            {

               oswindowSwap = this->element_at(i);
               this->element_at(i) = this->element_at(j);
               this->element_at(j) = oswindowSwap;

            }

         }

      }

   }


   void oswindow_array::top_windows_by_z_order()
   {

#ifdef WINDOWS_DESKTOP

      i32 iOrder = 0;
      oswindow oswindowOrder = ::get_desktop_window();
      oswindowOrder = ::GetWindow(oswindowOrder, GW_CHILD);
      while (oswindowOrder != nullptr
             && ::is_window(oswindowOrder))
      {
         add(oswindowOrder);
         oswindowOrder = ::GetWindow(oswindowOrder, GW_HWNDNEXT);
         iOrder++;
      }

#else

      ::exception::throw_not_implemented();

#endif

   }


   window_util::window_util()
   {

   }

   window_util::~window_util()
   {

   }

   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent interaction_impl associated object
   // and that all interaction_impl array pointers
   // are pointers to permanent objects.
   /*void window_util::SortByZOrder(Carray < ::user::interaction_impl *, ::user::interaction_impl * > & wndpa)
   {
   if(wndpa.get_size() <= 0)
   return;

   Carray < ::user::interaction_impl *, ::user::interaction_impl * > wndpa2;

   ::user::interaction_impl * pwnd = wndpa[0];

   ::user::interaction_impl * pwndChild = pwnd->GetWindow(GW_HWNDFIRST);

   while(pwndChild != nullptr
   && ::is_window(pwndChild->GetSafeoswindow_()))
   {
   pwnd = interaction_impl::FromHandlePermanent(pwndChild->GetSafeoswindow_());
   if(pwnd == nullptr)
   {
   CTransparentWndInterface * ptwi = nullptr;
   CTransparentWndInterface::CGetProperty getp;
   getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
   pwndChild->SendMessage(CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
   ptwi = getp.m_pinterface;
   if(ptwi != nullptr)
   {
   pwnd = ptwi->TwiGetWnd();
   if(pwnd != nullptr)
   {
   wndpa2.add(pwnd);
   }
   }

   }
   else
   {
   wndpa2.add(pwnd);
   }
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }

   Carray < ::user::interaction_impl *, ::user::interaction_impl * > wndpa3;
   Carray < ::user::interaction_impl *, ::user::interaction_impl * > wndpa4;

   for(i32 i = 0; i < wndpa2.get_size(); i++)
   {
   if(wndpa.find_first(wndpa2[i]) >= 0)
   {
   wndpa3.add(wndpa2[i]);
   }
   }

   for(i = 0; i < wndpa.get_size(); i++)
   {
   if(wndpa3.find_first(wndpa[i]) < 0)
   {
   wndpa3.add(wndpa[i]);
   }
   }

   wndpa.copy(wndpa3);

   }*/

   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent interaction_impl associated object
   // and that all interaction_impl array pointers
   // are pointers to permanent objects.
   /*void window_util::SortByZOrder(Carray < oswindow, oswindow > & oswindowa)
   {
   if(oswindowa.get_size() <= 0)
   return;

   Carray < oswindow, oswindow > oswindowa2;

   oswindow oswindow = oswindowa[0];

   oswindow oswindowChild = ::GetWindow(oswindow, GW_HWNDFIRST);

   while(oswindowChild != nullptr
   && ::is_window(oswindowChild))
   {
   oswindowa2.add(oswindowChild);
   oswindowChild = ::GetWindow(oswindowChild, GW_HWNDNEXT);
   }

   Carray < oswindow, oswindow > oswindowa3;
   Carray < oswindow, oswindow > oswindowa4;

   for(i32 i = 0; i < oswindowa2.get_size(); i++)
   {
   if(oswindowa.find_first(oswindowa2[i]) >= 0)
   {
   oswindowa3.add(oswindowa2[i]);
   }
   }

   for(i = 0; i < oswindowa.get_size(); i++)
   {
   if(oswindowa3.find_first(oswindowa[i]) < 0)
   {
   oswindowa3.add(oswindowa[i]);
   }
   }

   oswindowa.copy(oswindowa3);

   }*/


   /*void window_util::EnumChildren(oswindow oswindow, Carray < oswindow, oswindow > & oswindowa)
   {
   if(!::is_window)
   return;
   oswindow oswindowChild = ::GetTopWindow;
   while(oswindowChild != nullptr)
   {
   oswindowa.add(oswindowChild);
   oswindowChild = ::GetWindow(oswindowChild, GW_HWNDNEXT);
   }
   }

   void window_util::ExcludeChildren(oswindow oswindow, HRGN hrgn, const point & pointOffset)
   {


   Carray < oswindow, oswindow > oswindowa;

   EnumChildren(oswindow, oswindowa);

   for(i32 i = 0; i < oswindowa.get_size(); i++)
   {
   oswindow oswindowChild = oswindowa[i];
   ::rect rectChild;
   ::get_client_rect(oswindowChild, rectChild);
   ::_001ClientToScreen(oswindowChild, &rectChild.top_left());
   ::_001ClientToScreen(oswindowChild, &rectChild.bottom_right());
   ::_001ScreenToClient(oswindow, &rectChild.top_left());
   ::_001ScreenToClient(oswindow, &rectChild.bottom_right());
   rectChild.offset(pointOffset);
   HRGN hrgnChild = ::create_rect(rectChild);
   ::CombineRgn(hrgn, hrgn, hrgnChild, ::draw2d::region::combine_exclude);
   ::DeleteObject(hrgnChild);
   }




   }*/

   /*HRGN window_util::GetAClipRgn(oswindow oswindow, const point & pointOffset, bool bExludeChildren)
   {
   ::rect rectWnd;
   ::get_client_rect(oswindow, rectWnd);
   rectWnd.offset(pointOffset);
   HRGN hrgn = ::create_rect(rectWnd);

   if(bExludeChildren)
   {
   ExcludeChildren(oswindow, hrgn, pointOffset);
   }

   return hrgn;
   }*/




   void oswindow_tree::EnumDescendants()
   {

#ifdef WINDOWS_DESKTOP

      ::oswindow oswindow = m_oswindow;

      if (!::is_window(oswindow))
         return;

      ::oswindow oswindowChild = ::GetTopWindow(oswindow);

      while (oswindowChild != nullptr)
      {
         m_oswindowtreea.add_new(this);
         oswindow_tree & oswindowtreeChild = m_oswindowtreea.last_ref();
         oswindowtreeChild.m_oswindow = oswindowChild;
         oswindowtreeChild.m_dwUser = 0;
         oswindowtreeChild.m_pvoidUser = nullptr;
         oswindowtreeChild.EnumDescendants();
         oswindowChild = ::GetWindow(oswindowChild, GW_HWNDNEXT);
      }

#else

      __throw(not_implemented());

#endif

   }


   void oswindow_tree::Array::EnumDescendants()
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         this->element_at(i)->EnumDescendants();

      }

   }


   oswindow_tree::oswindow_tree(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

      m_oswindow = nullptr;

   }


   oswindow_tree::oswindow_tree(oswindow interaction_impl) :
      m_oswindow(interaction_impl)
   {

   }


   oswindow_tree::oswindow_tree(const oswindow_tree & tree)
   {
      operator =(tree);
   }


   oswindow_tree & oswindow_tree::operator = (const oswindow_tree & tree)
   {
      m_oswindow = tree.m_oswindow;
      m_oswindowtreea.copy(&tree.m_oswindowtreea);
      return *this;
   }

   index oswindow_tree::compare_oswindow(const ::user::oswindow_tree * ptree1, const ::user::oswindow_tree * ptree2)
   {
      return (index)((u8 *)(void *)ptree1->m_oswindow - (u8 *)(void *)ptree2->m_oswindow);
   }


   index oswindow_tree::Array::find(oswindow oswindow)
   {

      return comp_find_first(oswindow_tree(oswindow), &::user::oswindow_tree::compare_oswindow);

   }


   bool oswindow_tree::Array::remove(oswindow oswindow)
   {
      if (oswindow == nullptr)
         return true;
      i32 i;
      for (i = 0; i < this->get_size();)
      {
         oswindow_tree & tree = *this->element_at(i);
         if (tree.m_oswindow == oswindow)
         {
            remove_at(i);
            return true;
         }
         else
         {
            i++;
         }
      }
      for (i = 0; i < this->get_size(); i++)
      {
         oswindow_tree & tree = *this->element_at(i);
         if (tree.m_oswindowtreea.remove(oswindow))
         {
            return true;
         }
      }
      return false;
   }

   oswindow_tree::Array &
   oswindow_tree::Array::
   operator = (oswindow_array & oswindowa)
   {
      remove_all();
      oswindow_tree oswindowtree;
      for (i32 i = 0; i < oswindowa.get_size(); i++)
      {
         oswindowtree.m_oswindow = oswindowa[i];
         add(new oswindow_tree(oswindowtree));
      }
      return *this;
   }



   // This function get all child windows of
   // the interaction_impl pointed by pwnd and add it
   // to the interaction_impl array wndpa. The top
   // windows come first in the enumeration.

   /*void window_util::EnumChildren(::user::interaction_impl * pwnd, interaction_pointer_array & wndpa)
   {
   if(!::is_window(pwnd->GetSafeoswindow_()))
   return;
   ::user::interaction_impl * pwndChild = pwnd->GetTopWindow();
   while(pwndChild != nullptr)
   {
   wndpa.add(pwndChild);
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }
   }*/

   // This function get all child windows of
   // the interaction_impl pointed by pwnd and add it
   // to the interaction_impl array wndpa. The top
   // windows come first in the enumeration.

   void window_util::EnumChildren(oswindow oswindow, oswindow_array & oswindowa)
   {

#ifdef WINDOWS_DESKTOP

      if (!::is_window(oswindow))
         return;

      ::oswindow oswindowChild = ::GetTopWindow(oswindow);

      while (oswindowChild != nullptr)
      {

         oswindowa.add(oswindowChild);

         oswindowChild = ::GetWindow(oswindowChild, GW_HWNDNEXT);

      }

#else

      __throw(todo());

#endif

   }


   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings,
   // have a permanent interaction_impl associated object
   // and that all interaction_impl array pointers
   // are pointers to permanent objects.
   /*void window_util::SortByZOrder(interaction_pointer_array & wndpa)
   {
   if(wndpa.get_size() <= 0)
   return;

   interaction_pointer_array wndpa2;

   ::user::interaction_impl * pwnd = wndpa[0];

   ::user::interaction_impl * pwndChild = pwnd->GetWindow(GW_HWNDFIRST);

   while(pwndChild != nullptr)
   {
   pwnd = interaction_impl::FromHandlePermanent(pwndChild->GetSafeoswindow_());
   if(pwnd == nullptr)
   {
   wndpa2.add(pwnd);
   }
   pwndChild = pwndChild->GetWindow(GW_HWNDNEXT);
   }

   interaction_pointer_array wndpa3;
   interaction_pointer_array wndpa4;

   i32 i;
   for( i = 0; i < wndpa2.get_size(); i++)
   {
   if(wndpa.find_first(wndpa2[i]) >= 0)
   {
   wndpa3.add(wndpa2[i]);
   }
   }

   for(i = 0; i < wndpa.get_size(); i++)
   {
   if(wndpa3.find_first(wndpa[i]) < 0)
   {
   wndpa3.add(wndpa[i]);
   }
   }

   wndpa.copy(wndpa3);

   }*/

   /*void window_util::ExcludeChild(interaction_pointer_array & wndpa)
   {

   for(i32 i = 0; i < wndpa.get_size();)
   {
   if(wndpa[i]->get_parent() != nullptr)
   {
   wndpa.remove_at(i);
   }
   else
   {
   i++;
   }
   }

   }
   */



   void window_util::ContraintPosToParent(oswindow oswindow)
   {
      //#if !defined(_UWP) && !defined(APPLE_IOS)
      //      ::rect rectMajor;
      //      ::oswindow oswindowParent = ::GetParent(oswindow);
      //      if(oswindowParent == nullptr)
      //      {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //         rectMajor.left = 0;
      //         rectMajor.top = 0;
      //         rectMajor.right = GetSystemMetrics(SM_CXSCREEN);
      //         rectMajor.bottom = GetSystemMetrics(SM_CYSCREEN);
      //
      //#else
      //
      //         __throw(todo());
      //
      //#endif
      //
      //      }
      //      else
      //      {
      //         ::get_client_rect(oswindowParent, rectMajor);
      //      }
      //
      //      ::rect rect;
      //      ::get_client_rect(oswindow, rect);
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      ::_001ClientToScreen(oswindow, &rect.top_left());
      //
      //      ::_001ClientToScreen(oswindow, &rect.bottom_right());
      //
      //      if(oswindowParent != nullptr)
      //      {
      //
      //         ::_001ScreenToClient(oswindowParent, &rect.top_left());
      //
      //         ::_001ScreenToClient(oswindowParent, &rect.bottom_right());
      //
      //      }
      //
      //#else
      //
      //      __throw(todo());
      //
      //#endif
      //
      //      bool bModified = false;
      //
      //      if(rect.left > rectMajor.right)
      //      {
      //         rect.offset(- rect.width() - (rect.left - rectMajor.right), 0);
      //         bModified = true;
      //      }
      //      if(rect.right < rectMajor.left)
      //      {
      //         rect.offset(rect.width() + (rectMajor.left - rect.right), 0);
      //         bModified = true;
      //      }
      //      if(rect.top > rectMajor.bottom)
      //      {
      //         rect.offset(0, - rect.height() - (rect.top - rectMajor.bottom));
      //         bModified = true;
      //      }
      //
      //      if(rect.bottom < rectMajor.top)
      //      {
      //
      //         rect.offset(0, rect.height() + (rectMajor.top - rect.bottom));
      //
      //         bModified = true;
      //
      //      }
      //
      //
      //#ifdef WINDOWS
      //
      //      if(bModified)
      //      {
      //
      //         ::set_window_pos(oswindow, HWND_TOP, rect.left, rect.top, rect.width(), rect.height(), 0);
      //
      //      }
      //
      //#else
      //
      //      __throw(todo());
      //
      //#endif
      //#endif

   }

   /*void window_util::send_message_to_descendants(oswindow oswindow, const ::id & id,
   WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm)
   {
   // walk through HWNDs to avoid creating temporary interaction_impl objects
   // unless we need to call this function recursively
   for (oswindow oswindow_Child = ::GetTopWindow; oswindow_Child != nullptr;
   oswindow_Child = ::GetNextWindow(oswindow_Child, GW_HWNDNEXT))
   {
   // if bOnlyPerm is TRUE, don't send to non-permanent windows
   if (bOnlyPerm)
   {
   ::user::interaction_impl * pwindow = interaction_impl::FromHandlePermanent(oswindow_Child);
   if (pwindow != nullptr)
   {
   // call interaction_impl proc directly since it is a C++ interaction_impl
   __call_window_procedure(pwindow, pwindow->m_oswindow_, message, wParam, lParam);
   }
   }
   else
   {
   // send message with Windows SendMessage API
   ::SendMessage(oswindow_Child, message, wParam, lParam);
   }
   if (bDeep && ::GetTopWindow(oswindow_Child) != nullptr)
   {
   // send to child windows after parent
   send_message_to_descendants(oswindow_Child, message, wParam, lParam,
   bDeep, bOnlyPerm);
   }
   }
   }*/


   void window_util::send_message_to_descendants(oswindow oswindow, ::u32 message, WPARAM wParam, LPARAM lParam, bool bDeep)
   {

#if defined(WINDOWS_DESKTOP)

      // walk through HWNDs to avoid creating temporary interaction_impl objects
      // unless we need to call this function recursively
      for (::oswindow oswindow_Child = ::GetTopWindow(oswindow); oswindow_Child != nullptr; oswindow_Child = ::GetNextWindow(oswindow_Child, GW_HWNDNEXT))
      {

         // send message with Windows SendMessage API
         try
         {

            ::SendMessage(oswindow_Child, message, wParam, lParam);

         }
         catch (...)
         {

         }

         if (bDeep && ::GetTopWindow(oswindow_Child) != nullptr)
         {

            // send to child windows after parent
            try
            {

               send_message_to_descendants(oswindow_Child, message, wParam, lParam, bDeep);

            }
            catch (...)
            {

            }

         }

      }

#else

      __throw(todo());

#endif

   }

   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void window_util::SortByZOrder(oswindow_array & oswindowa)
   {
      if (oswindowa.get_size() <= 0)
         return;

      int_array ia1;
      int_array ia2;
      oswindow oswindowSwap;

      for (i32 i = 0; i < oswindowa.get_size(); i++)
      {
         for (i32 j = i + 1; j < oswindowa.get_size(); j++)
         {
            try
            {
               GetZOrder(oswindowa[i], ia1);
               GetZOrder(oswindowa[j], ia2);
               if (ia1.Cmp(ia2) > 0)
               {
                  oswindowSwap = oswindowa[i];
                  oswindowa[i] = oswindowa[j];
                  oswindowa[j] = oswindowSwap;
               }
            }
            catch (...)
            {
            }
         }
      }

   }

   i32 window_util::GetZOrder(oswindow oswindow)
   {

#ifdef _UWP

      return 0;

#else

      ::oswindow oswindowOrder = nullptr;

      if (!::is_window(oswindow))
      {

         return 0x7fffffff;

      }
      
#ifdef WINDOWS_DESKTOP

      if (::GetParent(oswindow) == MESSAGE_WINDOW_PARENT)
         return 0x7fffffff;
      
#endif

      try
      {

         oswindowOrder = ::get_window(oswindow, e_relative_first_child);

      }
      catch (...)
      {

         return 0x7fffffff;

      }

      i32 iOrder = 0;

      while (oswindowOrder != nullptr && ::is_window(oswindowOrder))
      {

         if (oswindow == oswindowOrder)
            return iOrder;

         oswindowOrder = ::get_window(oswindowOrder, e_relative_next_sibling);

         iOrder++;

      }

      return 0x7fffffff;

#endif

   }


   void window_util::GetZOrder(oswindow oswindow, int_array & ia)
   {

      if (!is_window(oswindow))
      {

         return;

      }

      i32 iOrder;
      ia.remove_all();
      while (true)
      {

         if (oswindow == nullptr || !::is_window(oswindow))
         {

            break;

         }

         iOrder = GetZOrder(oswindow);
         if (iOrder == 0x7fffffff)
            break;
         ia.insert_at(0, iOrder);
         
#ifdef WINDOWS_DESKTOP
         oswindow = ::GetParent(oswindow);
#else
         break;
#endif
         
      }

   }


   /*void window_util::EnumChildren(oswindow oswindow, oswindow_array & oswindowa)
   {
   if(!::is_window)
   return;
   oswindow oswindowChild = ::GetTopWindow;
   while(oswindowChild != nullptr)
   {
   oswindowa.add(oswindowChild);
   oswindowChild = ::GetWindow(oswindowChild, GW_HWNDNEXT);
   }
   }*/

//   void window_util::ExcludeChildren(oswindow oswindow, HRGN hrgn, const point & pointOffset)
//   {
//
//
//#ifdef WINDOWS_DESKTOP
//
//      oswindow_array oswindowa;
//
//      EnumChildren(oswindow, oswindowa);
//
//      for (i32 i = 0; i < oswindowa.get_size(); i++)
//      {
//
//         ::oswindow oswindowChild = oswindowa[i];
//
//         ::rect rectChild;
//
//         ::GetClientRect(oswindowChild, rectChild);
//
//         ::ClientToScreen(oswindowChild, &rectChild.top_left());
//
//         ::ClientToScreen(oswindowChild, &rectChild.bottom_right());
//
//         ::ScreenToClient(oswindow, &rectChild.top_left());
//
//         ::ScreenToClient(oswindow, &rectChild.bottom_right());
//
//         rectChild.offset(pointOffset);
//
//         HRGN hrgnChild = ::CreateRectRgnIndirect(rectChild);
//
//         ::CombineRgn(hrgn, hrgn, hrgnChild, ::draw2d::e_combine_exclude);
//
//         ::DeleteObject(hrgnChild);
//
//      }
//
//#else
//
//      __throw(todo());
//
//#endif
//
//
//   }

//   HRGN window_util::GetAClipRgn(oswindow oswindow, const point & pointOffset, bool bExludeChildren)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      ::rect rectWnd;
//
//      ::GetClientRect(oswindow, rectWnd);
//
//      rectWnd.offset(pointOffset);
//
//      HRGN hrgn = ::CreateRectRgnIndirect(rectWnd);
//
//      if (bExludeChildren)
//      {
//
//         ExcludeChildren(oswindow, hrgn, pointOffset);
//
//      }
//
//      return hrgn;
//
//#else
//
//      __throw(todo());
//
//#endif
//
//   }

   bool window_util::IsAscendant(oswindow oswindowAscendant, oswindow oswindowDescendant)
   {
#ifdef WINDOWS_DESKTOP
      while (true)
      {
         oswindowDescendant = ::GetParent(oswindowDescendant);
         if (oswindowDescendant == nullptr)
            return false;
         if (oswindowDescendant == oswindowAscendant)
            return true;
      }
#else
      return false;
#endif
   }








   interaction_ptra & interaction_ptra::operator=(const interaction_array & a)
   {

      for (index i = 0; i < a.interaction_count(); i++)
      {

         add(a.get_interaction(i));

      }

      return *this;

   }



   oswindow_array interaction_ptra::get_hwnda()
   {

      oswindow_array oswindowa;

      for (i32 i = 0; i < this->get_size(); i++)
      {

         oswindowa.add(this->element_at(i)->get_handle());

      }

      return oswindowa;

   }


   ::user::interaction * interaction_ptra::find_first_typed(const ::type & type)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         ::user::interaction * pinteraction = this->element_at(i);

         if (type == pinteraction)
         {

            return pinteraction;

         }

      }

      return nullptr;

   }


   ::user::interaction * interaction_ptra::find_first(oswindow oswindow)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i)->get_safe_handle() == oswindow)
         {

            return this->element_at(i);
         }
      }

      return nullptr;

   }

   bool interaction_ptra::get_child(__pointer(::user::interaction) & pinteraction)
   {

      //sync_lock sl(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = element_at(0);

         return true;

      }
      else
      {

         for (index i = get_upper_bound(); i >= 0; i--)
         {

            if (element_at(i) == pinteraction)
            {

               i++;

               if (i < get_count())
               {

                  pinteraction = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }

   bool interaction_ptra::rget_child(__pointer(::user::interaction) & pinteraction)
   {

      //sync_lock sl(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = last();

         return true;

      }
      else
      {

         for (index i = 0; i < get_size(); i++)
         {

            if (element_at(i) == pinteraction)
            {

               i--;

               if (i >= 0)
               {

                  pinteraction = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }



   primitive_ptra & primitive_ptra::operator=(const primitive_ptra & a)
   {

      remove_all();

      for (index i = 0; i < a.get_count(); i++)
      {

         add(a.element_at(i));

      }

      return *this;

   }


   oswindow_array primitive_ptra::get_hwnda()
   {

      oswindow_array oswindowa;

      for (i32 i = 0; i < this->get_size(); i++)
      {

         oswindowa.add(this->element_at(i)->get_handle());

      }

      return oswindowa;

   }


   ::user::primitive * primitive_ptra::find_first_typed(const ::type & type)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         ::user::primitive * pprimitive = this->element_at(i);

         if (type == pprimitive)
         {

            return pprimitive;

         }

      }

      return nullptr;

   }


   ::user::primitive * primitive_ptra::find_first(oswindow oswindow)
   {

      for (i32 i = 0; i < this->get_size(); i++)
      {

         if (this->element_at(i)->get_safe_handle() == oswindow)
         {

            return this->element_at(i);
         }
      }

      return nullptr;

   }



   bool primitive_ptra::get_child(__pointer(::user::primitive) & pprimitive)
   {

      //sync_lock sl(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pprimitive == nullptr)
      {

         pprimitive = element_at(0);

         return true;

      }
      else
      {

         for (index i = get_upper_bound(); i >= 0; i--)
         {

            if (element_at(i) == pprimitive)
            {

               i++;

               if (i < get_count())
               {

                  pprimitive = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }

   bool primitive_ptra::rget_child(__pointer(::user::primitive) & pprimitive)
   {

      //sync_lock sl(mutex());

      if (get_count() <= 0)
      {

         return false;

      }

      if (pprimitive == nullptr)
      {

         pprimitive = last();

         return true;

      }
      else
      {

         for (index i = 0; i < get_size(); i++)
         {

            if (element_at(i) == pprimitive)
            {

               i--;

               if (i >= 0)
               {

                  pprimitive = element_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }

















































   interaction_array::interaction_array()
   {

   }


   //interaction_pointer_array::interaction_pointer_array(::layered * pobjectContext) :
   //   ::object(pobject)
   //{

   //}


   interaction_array::interaction_array(const address_array < ::user::interaction * > & ptra)
   {

      for (index i = 0; i < ptra.get_count(); i++)
      {

         try
         {

            add_interaction(ptra[i]);

         }
         catch (...)
         {

         }

      }

   }


   //__pointer(::user::interaction) interaction_pointer_array::find_first_typed(::type info)
   //{

   //   for (i32 i = 0; i < this->get_size(); i++)
   //   {

   //      ::user::interaction * pinteraction = this->element_at(i);

   //      if (typeid(*pinteraction).name() == info->name())
   //      {

   //         return this->element_at(i);

   //      }

   //   }

   //   return nullptr;

   //}


   __pointer(::user::interaction) interaction_array::find_first(oswindow oswindow)
   {

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         if (this->interaction_at(i)->get_safe_handle() == oswindow)
         {

            return this->interaction_at(i);

         }

      }

      return nullptr;

   }


   interaction_array& interaction_array::operator = (const __pointer_array(::user::interaction) & a)
   {

      m_interactiona.copy(a);

      return *this;

   }


   interaction_array & interaction_array::operator = (const interaction_array& a)
   {

      m_interactiona.copy(a.m_interactiona);

      return *this;

   }


   oswindow_array interaction_array::get_hwnda()
   {

      oswindow_array oswindowa;

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         oswindowa.add(this->interaction_at(i)->get_handle());

      }

      return oswindowa;

   }


   void interaction_array::send_message(const ::id & id, WPARAM wparam, LPARAM lparam)

   {
      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message(id, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }


   void interaction_array::send_message_to_descendants(const ::id & id, WPARAM wparam, LPARAM lparam, bool bRecursive)
   {

      for (i32 i = 0; i < this->interaction_count(); i++)
      {

         try
         {

            this->interaction_at(i)->send_message_to_descendants(id, wparam, lparam, bRecursive);

         }
         catch (...)
         {

         }

      }

   }


   bool interaction_array::get_child(__pointer(::user::interaction) & pinteraction)
   {

      if (interaction_count() <= 0)
      {

         return false;

      }

      if (pinteraction.is_null())
      {

         pinteraction = interaction_at(0);

         return true;

      }
      else
      {

         for (index i = this->interaction_last_index(); i >= 0; i--)
         {

            if (interaction_at(i) == pinteraction)
            {

               i++;

               if (i < interaction_count())
               {

                  pinteraction = interaction_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }


   bool interaction_array::rget_child(__pointer(::user::interaction) & pinteraction)
   {

      if (interaction_count() <= 0)
      {

         return false;

      }

      if (pinteraction == nullptr)
      {

         pinteraction = last_interaction();

         return true;

      }
      else
      {

         for (index i = 0; i < interaction_count(); i++)
         {

            if (interaction_at(i) == pinteraction)
            {

               i--;

               if (i >= 0)
               {

                  pinteraction = interaction_at(i);

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }


} // namespace user



