#pragma once


#include "acme/prototype/collection/array_base.h"
#include "acme/prototype/collection/comparable_eq_array.h"
#include "acme/prototype/collection/comparable_array.h"
#include "acme/prototype/collection/pointer_array.h"


#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME hwnd_array :
      public ::comparable_array < HWND >
   {
   public:


      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();


   };


   class CLASS_DECL_ACME hwnd_tree :
      virtual public particle
   {
   public:


      class CLASS_DECL_ACME Array :
         public pointer_array < hwnd_tree >
      {
      public:


         bool erase(HWND hwnd);
         ::collection::index find(HWND hwnd);
         void EnumDescendants();
         Array & operator = (hwnd_array & hwnda);


      };


      HWND           m_hwnd;
      ::u32            m_dwUser;
      HWND           m_pvoidUser;
      Array          m_hwndtreea;


      hwnd_tree();
      hwnd_tree(HWND interaction_impl);
      hwnd_tree(const hwnd_tree & tree);


      void EnumDescendants();


      hwnd_tree & operator = (const hwnd_tree & tree);


      static ::collection::index compare_hwnd(const hwnd_tree * ptree1, const hwnd_tree * ptree2);


   };



   class CLASS_DECL_ACME window_util
   {
   public:


      //#ifdef WINDOWS
      //      static HRGN GetAClipRgn(hwnd hwnd, const i32_point & pointOffset, bool bExludeChilren);
      //      static void ExcludeChildren(hwnd hwnd, HRGN hrgn, const i32_point & pointOffset);
      //#endif



      window_util();
      virtual ~window_util();


      /*static void send_message_to_descendants(hwnd hwnd, const ::atom & atom,
      wparam wParam, lparam lParam, bool bDeep, bool bOnlyPerm);*/
      static void send_message_to_descendants(HWND hwnd, ::u32 message, wparam wParam, lparam lParam, bool bDeep);
      static bool IsAscendant(HWND hwndAscendant, HWND hwndDescendant);

      static ::i32 GetZOrder(HWND hwnd);
      static void GetZOrder(HWND hwnd, ::i32_array_base & ia);

      //      static HRGN GetAClipRgn(hwnd hwnd, const i32_point & pointOffset, bool bExludeChilren);
      //      static void ExcludeChildren(hwnd hwnd, HRGN hrgn, const i32_point & pointOffset);

      //static void SortByZOrder(comparable_array < ::windowing::window *, ::windowing::window * > & wndpa);
      //static void SortByZOrder(comparable_array < hwnd, hwnd > & hwnda);
      //static void EnumChildren(hwnd hwnd, comparable_array < hwnd, hwnd > & hwnda);

      static void ContraintPosToParent(HWND hwnd);
      static void EnumChildren(HWND hwnd, hwnd_array & hwnda);
      /*static void ExcludeChild(interaction_array & wndpa);*/
      /*static void SortByZOrder(interaction_array & wndpa);*/
      static void SortByZOrder(hwnd_array & hwnda);

   };


   

} // namespace windows





