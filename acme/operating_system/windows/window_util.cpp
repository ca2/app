#include "platform.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "window_util.h"
#include "acme/windowing/window.h"
//#include "aura/user/user/interaction_array.h"
//#include "aura/user/user/interaction.h"


#ifdef APPLEIOS
HWND GetWindow(HWND window, ::i32 iParentHood);
#endif


#ifdef WINDOWS_DESKTOP


#define MESSAGE_WINDOW_PARENT HWND_MESSAGE


#endif


namespace windows
{



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
   /*void window_util::SortByZOrder(Carray < ::windowing::window *, ::windowing::window * > & wndpa)
   {
   if(wndpa.get_size() <= 0)
   return;

   Carray < ::windowing::window *, ::windowing::window * > wndpa2;

   ::windowing::window * puserinteraction = wndpa[0];

   ::windowing::window * puserinteractionChild = puserinteraction->GetWindow(GW_HWNDFIRST);

   while(puserinteractionChild != nullptr
   && ::IsWindow(puserinteractionChild->GetSafehwnd_()))
   {
   puserinteraction = interaction_impl::FromHandlePermanent(puserinteractionChild->GetSafehwnd_());
   if(puserinteraction == nullptr)
   {
   CTransparentWndInterface * ptwi = nullptr;
   CTransparentWndInterface::CGetProperty getp;
   getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
   puserinteractionChild->SendMessage(CTransparentWndInterface::MessageGetProperty, 0, (lparam) &getp);
   ptwi = getp.m_pinterface;
   if(ptwi != nullptr)
   {
   puserinteraction = ptwi->TwiGetWnd();
   if(puserinteraction != nullptr)
   {
   wndpa2.add(puserinteraction);
   }
   }

   }
   else
   {
   wndpa2.add(puserinteraction);
   }
   puserinteractionChild = puserinteractionChild->GetWindow(GW_HWNDNEXT);
   }

   Carray < ::windowing::window *, ::windowing::window * > wndpa3;
   Carray < ::windowing::window *, ::windowing::window * > wndpa4;

   for(::i32 i = 0; i < wndpa2.get_size(); i++)
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
   /*void window_util::SortByZOrder(Carray < HWND, HWND > & hwnda)
   {
   if(hwnda.get_size() <= 0)
   return;

   Carray < HWND, HWND > hwnda2;

   HWND hwnd = hwnda[0];

   HWND hwndChild = ::GetWindow(hwnd, GW_HWNDFIRST);

   while(hwndChild != nullptr
   && ::IsWindow(hwndChild))
   {
   hwnda2.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }

   Carray < HWND, HWND > hwnda3;
   Carray < HWND, HWND > hwnda4;

   for(::i32 i = 0; i < hwnda2.get_size(); i++)
   {
   if(hwnda.find_first(hwnda2[i]) >= 0)
   {
   hwnda3.add(hwnda2[i]);
   }
   }

   for(i = 0; i < hwnda.get_size(); i++)
   {
   if(hwnda3.find_first(hwnda[i]) < 0)
   {
   hwnda3.add(hwnda[i]);
   }
   }

   hwnda.copy(hwnda3);

   }*/


   /*void window_util::EnumChildren(HWND hwnd, Carray < HWND, HWND > & hwnda)
   {
   if(!::IsWindow)
   return;
   HWND hwndChild = ::GetTopWindow;
   while(hwndChild != nullptr)
   {
   hwnda.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }
   }

   void window_util::ExcludeChildren(HWND hwnd, HRGN hrgn, const i32_point & pointOffset)
   {


   Carray < HWND, HWND > hwnda;

   EnumChildren(hwnd, hwnda);

   for(::i32 i = 0; i < hwnda.get_size(); i++)
   {
   HWND hwndChild = hwnda[i];
   ::i32_rectangle rectangleChild;
   ::this->rectangle(hwndChild, rectangleChild);
   ::_001ClientToScreen(hwndChild, &rectangleChild.top_left());
   ::_001ClientToScreen(hwndChild, &rectangleChild.bottom_right());
   ::_001ScreenToClient(hwnd, &rectangleChild.top_left());
   ::_001ScreenToClient(hwnd, &rectangleChild.bottom_right());
   rectangleChild.offset(pointOffset);
   HRGN hrgnChild = ::create_rect(rectangleChild);
   ::CombineRgn(hrgn, hrgn, hrgnChild, ::draw2d::region::combine_exclude);
   ::DeleteObject(hrgnChild);
   }




   }*/

   /*HRGN window_util::GetAClipRgn(HWND hwnd, const i32_point & pointOffset, bool bExludeChildren)
   {
   ::i32_rectangle rectangleWnd;
   ::this->rectangle(hwnd, rectangleWnd);
   rectangleWnd.offset(pointOffset);
   HRGN hrgn = ::create_rect(rectangleWnd);

   if(bExludeChildren)
   {
   ExcludeChildren(hwnd, hrgn, pointOffset);
   }

   return hrgn;
   }*/




   // This function get all child windows of
   // the interaction_impl pointed by puserinteraction and add it
   // to the interaction_impl array wndpa. The top
   // windows come first in the enumeration.

   /*void window_util::EnumChildren(::windowing::window * puserinteraction, interaction_pointer_array & wndpa)
   {
   if(!::IsWindow(puserinteraction->GetSafehwnd_()))
   return;
   ::windowing::window * puserinteractionChild = puserinteraction->GetTopWindow();
   while(puserinteractionChild != nullptr)
   {
   wndpa.add(puserinteractionChild);
   puserinteractionChild = puserinteractionChild->GetWindow(GW_HWNDNEXT);
   }
   }*/


   // This function get all child windows of
   // the interaction_impl pointed by puserinteraction and add it
   // to the interaction_impl array wndpa. The top
   // windows come first in the enumeration.
   void window_util::EnumChildren(HWND hwnd, hwnd_array & hwnda)
   {

#ifdef WINDOWS_DESKTOP

      if (!::IsWindow(hwnd))
         return;

      HWND hwndChild = ::GetTopWindow(hwnd);

      while (hwndChild != nullptr)
      {

         hwnda.add(hwndChild);

         hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);

      }

#else

      throw ::exception(todo);

#endif

   }



   void hwnd_array::SortByZOrder()
   {

      window_util::SortByZOrder(*this);

   }


   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void hwnd_array::SortSiblingsByZOrder()
   {

      HWND hwndSwap;

      for (::i32 i = 0; i < this->get_size(); i++)
      {

         for (::i32 j = i + 1; j < this->get_size(); j++)
         {

            if (window_util::GetZOrder(this->element_at(i)) > window_util::GetZOrder(this->element_at(j)))
            {

               hwndSwap = this->element_at(i);
               this->element_at(i) = this->element_at(j);
               this->element_at(j) = hwndSwap;

            }

         }

      }

   }



   void hwnd_tree::EnumDescendants()
   {

      HWND hwnd = m_hwnd;

      if (!::IsWindow((HWND)hwnd))
      {

         return;

      }

      HWND hwndChild = ::GetTopWindow(hwnd);

      while (hwndChild != nullptr)
      {
         m_hwndtreea.add_construct(this);
         hwnd_tree & hwndtreeChild = m_hwndtreea.last_ref();
         hwndtreeChild.m_hwnd = hwndChild;
         hwndtreeChild.m_dwUser = 0;
         hwndtreeChild.m_pvoidUser = nullptr;
         hwndtreeChild.EnumDescendants();
         hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
      }


   }


   void hwnd_tree::Array::EnumDescendants()
   {

      for (::i32 i = 0; i < this->get_size(); i++)
      {

         this->element_at(i)->EnumDescendants();

      }

   }


   hwnd_tree::hwnd_tree()
   {

      m_hwnd = nullptr;

   }


   hwnd_tree::hwnd_tree(HWND interaction_impl) :
      m_hwnd(interaction_impl)
   {

   }


   hwnd_tree::hwnd_tree(const hwnd_tree & tree)
   {
      operator =(tree);
   }


   hwnd_tree & hwnd_tree::operator = (const hwnd_tree & tree)
   {
      m_hwnd = tree.m_hwnd;
      m_hwndtreea.copy(tree.m_hwndtreea);
      return *this;
   }

   ::collection::index hwnd_tree::compare_hwnd(const hwnd_tree * ptree1, const hwnd_tree * ptree2)
   {
      return (::collection::index)((::u8 *)(void *)ptree1->m_hwnd - (::u8 *)(void *)ptree2->m_hwnd);
   }


   ::collection::index hwnd_tree::Array::find(HWND hwnd)
   {

      return comp_find_first(hwnd_tree(hwnd), &hwnd_tree::compare_hwnd);

   }


   bool hwnd_tree::Array::erase(HWND hwnd)
   {
      if (hwnd == nullptr)
         return true;
      ::i32 i;
      for (i = 0; i < this->get_size();)
      {
         hwnd_tree & tree = *this->element_at(i);
         if (tree.m_hwnd == hwnd)
         {
            erase_at(i);
            return true;
         }
         else
         {
            i++;
         }
      }
      for (i = 0; i < this->get_size(); i++)
      {
         hwnd_tree & tree = *this->element_at(i);
         if (tree.m_hwndtreea.erase(hwnd))
         {
            return true;
         }
      }
      return false;
   }

   hwnd_tree::Array &
      hwnd_tree::Array::
      operator = (hwnd_array & hwnda)
   {
      erase_all();
      hwnd_tree hwndtree;
      for (::i32 i = 0; i < hwnda.get_size(); i++)
      {
         hwndtree.m_hwnd = hwnda[i];
         add(___new hwnd_tree(hwndtree));
      }
      return *this;
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

   ::windowing::window * puserinteraction = wndpa[0];

   ::windowing::window * puserinteractionChild = puserinteraction->GetWindow(GW_HWNDFIRST);

   while(puserinteractionChild != nullptr)
   {
   puserinteraction = interaction_impl::FromHandlePermanent(puserinteractionChild->GetSafehwnd_());
   if(puserinteraction == nullptr)
   {
   wndpa2.add(puserinteraction);
   }
   puserinteractionChild = puserinteractionChild->GetWindow(GW_HWNDNEXT);
   }

   interaction_pointer_array wndpa3;
   interaction_pointer_array wndpa4;

   ::i32 i;
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

   for(::i32 i = 0; i < wndpa.get_size();)
   {
   if(wndpa[i]->get_parent() != nullptr)
   {
   wndpa.erase_at(i);
   }
   else
   {
   i++;
   }
   }

   }
   */



   void window_util::ContraintPosToParent(HWND hwnd)
   {
      //#if !defined(UNIVERSAL_WINDOWS) && !defined(APPLE_IOS)
      //      ::i32_rectangle rectangleMajor;
      //      HWND hwndParent = ::get_parent(hwnd);
      //      if(hwndParent == nullptr)
      //      {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //         rectangleMajor.left = 0;
      //         rectangleMajor.top = 0;
      //         rectangleMajor.right = GetSystemMetrics(SM_CXSCREEN);
      //         rectangleMajor.bottom = GetSystemMetrics(SM_CYSCREEN);
      //
      //#else
      //
      //         throw ::exception(todo);
      //
      //#endif
      //
      //      }
      //      else
      //      {
      //         ::this->rectangle(hwndParent, rectangleMajor);
      //      }
      //
      //      ::i32_rectangle rectangle;
      //      ::this->rectangle(hwnd, rectangle);
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      ::_001ClientToScreen(hwnd, &rectangle.top_left());
      //
      //      ::_001ClientToScreen(hwnd, &rectangle.bottom_right());
      //
      //      if(hwndParent != nullptr)
      //      {
      //
      //         ::_001ScreenToClient(hwndParent, &rectangle.top_left());
      //
      //         ::_001ScreenToClient(hwndParent, &rectangle.bottom_right());
      //
      //      }
      //
      //#else
      //
      //      throw ::exception(todo);
      //
      //#endif
      //
      //      bool bModified = false;
      //
      //      if(rectangle.left > rectangleMajor.right)
      //      {
      //         rectangle.offset(- rectangle.width() - (rectangle.left - rectangleMajor.right), 0);
      //         bModified = true;
      //      }
      //      if(rectangle.right < rectangleMajor.left)
      //      {
      //         rectangle.offset(rectangle.width() + (rectangleMajor.left - rectangle.right), 0);
      //         bModified = true;
      //      }
      //      if(rectangle.top > rectangleMajor.bottom)
      //      {
      //         rectangle.offset(0, - rectangle.height() - (rectangle.top - rectangleMajor.bottom));
      //         bModified = true;
      //      }
      //
      //      if(rectangle.bottom < rectangleMajor.top)
      //      {
      //
      //         rectangle.offset(0, rectangle.height() + (rectangleMajor.top - rectangle.bottom));
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
      //         ::set_window_position(hwnd, HWND_TOP, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), 0);
      //
      //      }
      //
      //#else
      //
      //      throw ::exception(todo);
      //
      //#endif
      //#endif

   }

   /*void window_util::send_message_to_descendants(HWND hwnd, const ::atom & atom,
   wparam wParam, lparam lParam, bool bDeep, bool bOnlyPerm)
   {
   // walk through HWNDs to avoid creating temporary interaction_impl objects
   // unless we need to call this function recursively
   for (HWND hwnd_Child = ::GetTopWindow; hwnd_Child != nullptr;
   hwnd_Child = ::GetNextWindow(hwnd_Child, GW_HWNDNEXT))
   {
   // if bOnlyPerm is true, don't send to non-permanent windows
   if (bOnlyPerm)
   {
   ::windowing::window * pwindow = interaction_impl::FromHandlePermanent(hwnd_Child);
   if (pwindow != nullptr)
   {
   // call interaction_impl proc directly since it is a C++ interaction_impl
   __call_window_procedure(pwindow, pwindow->m_hwnd_, message, wParam, lParam);
   }
   }
   else
   {
   // send message with Windows SendMessage API
   ::SendMessage(hwnd_Child, message, wParam, lParam);
   }
   if (bDeep && ::GetTopWindow(hwnd_Child) != nullptr)
   {
   // send to child windows after parent
   send_message_to_descendants(hwnd_Child, message, wParam, lParam,
   bDeep, bOnlyPerm);
   }
   }
   }*/


   void window_util::send_message_to_descendants(HWND hwnd, ::u32 message, wparam wParam, lparam lParam, bool bDeep)
   {

#if defined(WINDOWS_DESKTOP)

      // walk through HWNDs to avoid creating temporary interaction_impl objects
      // unless we need to call this function recursively
      for (HWND hwnd_Child = ::GetTopWindow(hwnd); hwnd_Child != nullptr; hwnd_Child = ::GetNextWindow(hwnd_Child, GW_HWNDNEXT))
      {

         // send message with Windows SendMessage API
         try
         {

            ::SendMessage(hwnd_Child, message, wParam, lParam);

         }
         catch (...)
         {

         }

         if (bDeep && ::GetTopWindow(hwnd_Child) != nullptr)
         {

            // send to child windows after parent
            try
            {

               send_message_to_descendants(hwnd_Child, message, wParam, lParam, bDeep);

            }
            catch (...)
            {

            }

         }

      }

#else

      throw ::exception(todo);

#endif

   }

   // This function sort the interaction_impl array
   // by ascending z order.

   // This implementation relays in the fact
   // that all windows are siblings
   void window_util::SortByZOrder(hwnd_array & hwnda)
   {
      if (hwnda.get_size() <= 0)
         return;

      ::i32_array_base ia1;
      ::i32_array_base ia2;
      HWND hwndSwap;

      for (::i32 i = 0; i < hwnda.get_size(); i++)
      {
         for (::i32 j = i + 1; j < hwnda.get_size(); j++)
         {
            try
            {
               GetZOrder(hwnda[i], ia1);
               GetZOrder(hwnda[j], ia2);
               if (ia1.Cmp(ia2) > 0)
               {
                  hwndSwap = hwnda[i];
                  hwnda[i] = hwnda[j];
                  hwnda[j] = hwndSwap;
               }
            }
            catch (...)
            {
            }
         }
      }

   }

   ::i32 window_util::GetZOrder(HWND hwnd)
   {

#ifdef UNIVERSAL_WINDOWS

      return 0;

#else

      HWND hwndOrder = nullptr;

      if (!::IsWindow((HWND) hwnd))
      {

         return I32_MAXIMUM;

      }

#ifdef WINDOWS_DESKTOP

      if (::GetParent(hwnd) == MESSAGE_WINDOW_PARENT)
      {

         return I32_MAXIMUM;

      }

#endif

      try
      {

         hwndOrder = ::GetWindow(hwnd, e_relative_first_child);

      }
      catch (...)
      {

         return I32_MAXIMUM;

      }

      ::i32 iOrder = 0;

      while (hwndOrder != nullptr && ::IsWindow(hwndOrder))
      {

         if (hwnd == hwndOrder)
            return iOrder;

         hwndOrder = ::GetWindow(hwndOrder, e_relative_next_sibling);

         iOrder++;

      }

      return I32_MAXIMUM;

#endif

   }


   void window_util::GetZOrder(HWND hwnd, ::i32_array_base & ia)
   {

      if (!IsWindow(hwnd))
      {

         return;

      }

      ::i32 iOrder;
      ia.erase_all();
      while (true)
      {

         if (hwnd == nullptr || !::IsWindow((HWND) hwnd))
         {

            break;

         }

         iOrder = GetZOrder(hwnd);
         if (iOrder == I32_MAXIMUM)
            break;
         ia.insert_at(0, iOrder);

#ifdef WINDOWS_DESKTOP
         hwnd = ::GetParent(hwnd);
#else
         break;
#endif

      }

   }


   /*void window_util::EnumChildren(HWND hwnd, hwnd_array & hwnda)
   {
   if(!::IsWindow)
   return;
   hwnd hwndChild = ::GetTopWindow;
   while(hwndChild != nullptr)
   {
   hwnda.add(hwndChild);
   hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
   }
   }*/

   //   void window_util::ExcludeChildren(HWND hwnd, HRGN hrgn, const i32_point & pointOffset)
   //   {
   //
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      hwnd_array hwnda;
   //
   //      EnumChildren(hwnd, hwnda);
   //
   //      for (::i32 i = 0; i < hwnda.get_size(); i++)
   //      {
   //
   //         HWND hwndChild = hwnda[i];
   //
   //         ::i32_rectangle rectangleChild;
   //
   //         ::GetClientRect(hwndChild, rectangleChild);
   //
   //         ::ClientToScreen(hwndChild, &rectangleChild.top_left());
   //
   //         ::ClientToScreen(hwndChild, &rectangleChild.bottom_right());
   //
   //         ::ScreenToClient(hwnd, &rectangleChild.top_left());
   //
   //         ::ScreenToClient(hwnd, &rectangleChild.bottom_right());
   //
   //         rectangleChild.offset(pointOffset);
   //
   //         HRGN hrgnChild = ::CreateRectRgnIndirect(rectangleChild);
   //
   //         ::CombineRgn(hrgn, hrgn, hrgnChild, ::draw2d::e_combine_exclude);
   //
   //         ::DeleteObject(hrgnChild);
   //
   //      }
   //
   //#else
   //
   //      throw ::exception(todo);
   //
   //#endif
   //
   //
   //   }

   //   HRGN window_util::GetAClipRgn(HWND hwnd, const i32_point & pointOffset, bool bExludeChildren)
   //   {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      ::i32_rectangle rectangleWnd;
   //
   //      ::GetClientRect(hwnd, rectangleWnd);
   //
   //      rectangleWnd.offset(pointOffset);
   //
   //      HRGN hrgn = ::CreateRectRgnIndirect(rectangleWnd);
   //
   //      if (bExludeChildren)
   //      {
   //
   //         ExcludeChildren(hwnd, hrgn, pointOffset);
   //
   //      }
   //
   //      return hrgn;
   //
   //#else
   //
   //      throw ::exception(todo);
   //
   //#endif
   //
   //   }

   bool window_util::IsAscendant(HWND hwndAscendant, HWND hwndDescendant)
   {
#ifdef WINDOWS_DESKTOP
      while (true)
      {

         hwndDescendant = ::GetParent(hwndDescendant);

         if (hwndDescendant == nullptr)
         {

            return false;

         }

         if (hwndDescendant == hwndAscendant)
         {

            return true;

         }

      }
#else
      return false;
#endif
   }




















   void hwnd_array::top_windows_by_z_order()
   {

      ::i32 iOrder = 0;
      HWND hwndOrder = ::GetDesktopWindow();
      hwndOrder = ::GetWindow(hwndOrder, GW_CHILD);
      while (hwndOrder != nullptr
         && ::IsWindow(hwndOrder))
      {
         add(hwndOrder);
         hwndOrder = ::GetWindow(hwndOrder, GW_HWNDNEXT);
         iOrder++;
      }
//
//#else
//
//      throw ::interface_only();
//
//#endif

   }



} // windowing_win32



