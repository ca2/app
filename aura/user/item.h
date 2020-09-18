#pragma once

template < typename T >
class ___stack
{
public:

   T& m_reference;
   T m_tPrevious;

   ___stack(T& reference, const T& tStack) :
      m_reference(reference)
   {
      m_tPrevious = reference;
      reference = tStack;
   }

   ~___stack()
   {
      m_reference = m_tPrevious;

   }

};


#define __stack(xxxx, aaaa) auto stack_at_line ## LINE_NUMBER = ::___stack < ::remove_reference< decltype(xxxx) >::TYPE > (xxxx, aaaa);

namespace user
{

#pragma pack(push, user_ITEM, 1)

   struct CLASS_DECL_AURA ITEM
   {

      e_element          m_eelement;
      ::index            m_iItem;
      ::index            m_iSubItem;
      ::index            m_iListItem;


      inline ::index  menu_view_index() const { return (::index) m_iItem; }
      inline ::index  menu_view_group() const { return (::index) m_iSubItem; }
      inline ::index  menu_view_command() const { return (::index) m_iListItem; }

      inline ::index item_index() const { return (::index) m_iItem; }
      inline ::index subitem_index() const { return (::index) m_iSubItem; }
      inline ::index list_item_index() const { return (::index) m_iListItem; }


      bool operator == (const ITEM & item)  const { return !memcmp(this, &item, sizeof(ITEM)); }
      bool operator != (const ITEM & item)  const { return !operator == (item); }

   };

#pragma pack(pop, user_ITEM)

#define ITEM_DRAWN 0x800000


   struct CLASS_DECL_AURA item_data :
      public ITEM
   {
    
      ::point                       m_pointScreen;
      ::point                       m_pointClient;
      ::point                       m_pointHitTest;
      ::rect                        m_rect;
      ::user::e_event               m_eevent;
      u64                           m_uFlags;
      
      item_data & operator = (const item_data& item) { if (this != &item) memcpy(this, &item, sizeof(item_data)); return *this; }

      bool operator == (const item_data & item)  const { return ITEM::operator==(item); }
      bool operator != (const item_data & item)  const { return ITEM::operator!=(item); }

      
   };

   class CLASS_DECL_AURA item :
      virtual public item_data,
      virtual public ::generic
   {
   public:

      // a user item is a "pointer"/address to a user interface element

      ::draw2d::graphics_pointer    m_pgraphics;
      ::draw2d::path_pointer        m_ppath;
      //::user::mouse *      m_pmouse;

      //item(e_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::u64 uFlags = flag_none) :
      //   item(eelement, iItem, iSubItem, iListItem, uFlags) {}

      item(const ::u64 uFlags, e_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, ::user::e_event eevent = ::user::event_none) :
         item(eelement, iItem, iSubItem, iListItem, eevent, uFlags) {}

      item(e_element eelement, ::user::e_event eevent)
         : item(eelement, -1, -1, -1, eevent)
      {

      }

      item(e_element eelement = ::user::element_none, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, ::user::e_event eevent = event_none, const ::u64 uFlags = flag_none)
      {

         m_eevent = eevent;

         m_eelement = eelement;

         m_iItem = iItem >= 0 ? iItem : m_eelement != ::user::element_none ? 0 : iItem;

         m_iSubItem = iSubItem;

         m_iListItem = iListItem;

         m_uFlags = uFlags;

      }

      item(::index iItem)
      {

         m_eevent = ::user::event_none;

         m_eelement = ::user::element_none;

         m_iItem = -1;

         m_iSubItem = -1;

         m_iListItem = -1;

         m_uFlags = 0;

         operator = (iItem);

      }

      bool is_drawn() { return m_uFlags & ITEM_DRAWN;  }

      void set_drawn() { m_uFlags |= ITEM_DRAWN; }

      bool is_set() const { return m_eelement != ::user::element_none; }

      operator bool() const { return is_set(); }

      operator e_element() const { return m_eelement; }

      operator i32() const { return (::i32) m_iItem; }

      operator i64() const { return (::i64) m_iItem; }

      item& operator = (const item & item) { item_data::operator=(item); return *this; }

      bool operator == (const item & item)  const { return ITEM::operator==(item); }
      bool operator != (const item & item)  const { return ITEM::operator!=(item); }

      item & operator = (e_element eelement);

      bool operator == (e_element eelement)  const { return m_eelement == eelement; }
      bool operator != (e_element eelement)  const { return !operator==(eelement); }

      item & operator = (::index iItem);

      bool operator == (::index iItem)  const { return m_iItem == iItem; }
      bool operator != (::index iItem)  const { return m_iItem != iItem; }

      bool operator <= (::index iItem)  const { return m_iItem <= iItem; }
      bool operator >= (::index iItem)  const { return m_iItem >= iItem; }

      bool operator < (::index iItem)  const { return m_iItem < iItem; }
      bool operator > (::index iItem)  const { return m_iItem > iItem; }

      ::index operator + (::i32 iItemAdd) { return (::index) (m_iItem + iItemAdd); }
      ::index operator - (::i32 iItemSub) { return (::index) (m_iItem - iItemSub); }

      ::index operator + (::i64 iItemAdd) { return (::index) (m_iItem + iItemAdd); }
      ::index operator - (::i64 iItemSub) { return (::index) (m_iItem - iItemSub); }


      bool in_range(e_element eelement, int iCount) const { return m_eelement >= eelement && m_eelement < eelement + iCount; }

      bool is_valid_item(::count c) const { return m_iItem >= 0 && m_iItem < c; }


   };


} // namespace item


