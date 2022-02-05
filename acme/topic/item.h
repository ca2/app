// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 21:12 BRT
#pragma once


template < typename T >
class ___stack
{
public:

   
   T & m_reference;
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


#define __stack(xxxx, aaaa) auto stack_at_line ## LINE_NUMBER = ::___stack < ::erase_reference< decltype(xxxx) >::TYPE > (xxxx, aaaa);


#pragma pack(push, user_ITEM, 1)


struct ITEM_BASE_ADDITIONS
{
   

   enum_element                  m_eelement;
   ::index                       m_iItem;
   ::index                       m_iSubItem;
   ::index                       m_iListItem;
   
   
};


struct ITEM_DATA_ADDITIONS
{

   
   ::point_i32                   m_pointScreen;
   ::point_i32                   m_pointHost;
   ::point_i32                   m_pointClient;
   ::point_i32                   m_pointHitTest;
   ::rectangle_i32               m_rectangle;
   u64                           m_uFlags;
   
   
};


struct ITEM_BASE :
   public TOPIC,
   public ITEM_BASE_ADDITIONS
{


};


struct ITEM_DATA :
   public TOPIC,
   public ITEM_BASE_ADDITIONS,
   public ITEM_DATA_ADDITIONS
{


};


#pragma pack(pop, user_ITEM)


#define ITEM_DRAWN 0x800000


class CLASS_DECL_ACME item_base :
   virtual public ::topic,
   virtual public ITEM_BASE_ADDITIONS
{
   
   
   inline ::index menu_view_index() const { return (::index) m_iItem; }
   inline ::index menu_view_group() const { return (::index) m_iSubItem; }
   inline ::index menu_view_command() const { return (::index) m_iListItem; }

   inline ::index item_index() const { return (::index) m_iItem; }
   inline ::index subitem_index() const { return (::index) m_iSubItem; }
   inline ::index list_item_index() const { return (::index) m_iListItem; }

   
   item_base & operator = (const ::topic & topic) { if ((TOPIC *) this != (TOPIC *) &topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }


   bool operator == (const ::topic & topic)  const { return ((TOPIC *)this == (TOPIC *)&topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::topic & topic)  const { return !operator == (topic); }

   
   item_base & operator = (const item_base & itembase) { if ((TOPIC *) this != (TOPIC *) &itembase) memcpy((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); return *this; }


   bool operator == (const ::item_base & itembase)  const { return ((TOPIC *)this == (TOPIC *)&itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const ::item_base & itembase)  const { return !operator == (itembase); }
   

   item_base & operator = (const ::TOPIC & topic) { if ((TOPIC *) this != (TOPIC *) &topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }


   bool operator == (const ::TOPIC & topic)  const { return ((TOPIC *)this == (TOPIC *)&topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::TOPIC & topic)  const { return !operator == (topic); }

   
   item_base & operator = (const ITEM_BASE & itembase) { if ((TOPIC *)this != (TOPIC *)&itembase) memcpy((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); return *this; }


   bool operator == (const ::ITEM_BASE & itembase)  const { return ((TOPIC *)this == (TOPIC *)&itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const ::ITEM_BASE & itembase)  const { return !operator == (itembase); }


};


struct CLASS_DECL_ACME item_data :
   virtual public ITEM_DATA_ADDITIONS,
   virtual public item_base
{
   
   
   item_data & operator = (const ::topic & topic) { if ((TOPIC*) this != (TOPIC *) &topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }


   bool operator == (const ::topic & topic)  const { return ((TOPIC *)this == (TOPIC *)&topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::topic & topic)  const { return !operator == (topic); }
   
   
   item_data & operator = (const item_base & itembase) { if ((TOPIC *) this != (TOPIC *) &itembase) memcpy((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); return *this; }

   bool operator == (const item_base & itembase)  const { return ((TOPIC *)this == (TOPIC *)&itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const item_base & itembase)  const { return !operator==(itembase); }
   
   
   item_data & operator = (const item_data & itemdata) { if ((TOPIC *) this != (TOPIC *)&itemdata) memcpy((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   bool operator == (const item_data & itemdata)  const { return ((TOPIC *) this == (TOPIC *)&itemdata) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); }
   bool operator != (const item_data & itemdata)  const { return !operator==(itemdata); }


   item_data & operator = (const ::TOPIC & topic) { if ((TOPIC *)this != (TOPIC *)&topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }


   bool operator == (const ::TOPIC & topic)  const { return ((TOPIC *)this == (TOPIC *)&topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::TOPIC & topic)  const { return !operator == (topic); }
   
   
   item_data & operator = (const ITEM_BASE & itembase) { if ((TOPIC *) this != (TOPIC *) &itembase) memcpy((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); return *this; }

   bool operator == (const ITEM_BASE & itembase)  const { return ((TOPIC *)this == (TOPIC *)&itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const ITEM_BASE & itembase)  const { return !operator==(itembase); }
   
   

   item_data & operator = (const ITEM_DATA & itemdata) { if ((TOPIC *)this != (TOPIC *)&itemdata) memcpy((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   bool operator == (const ITEM_DATA & itemdata)  const { return ((TOPIC *)this == (TOPIC *)&itemdata) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); }
   bool operator != (const ITEM_DATA & itemdata)  const { return !operator==(itemdata); }


};



class CLASS_DECL_ACME item :
   virtual public item_data,
   virtual public ::matter
{
public:

   // a user item is a "pointer"/address to a user interface matter

   matter_pointer                m_pDraw2dGraphics;
   matter_pointer                m_pDraw2dPath;
   //::user::mouse *      m_pmouse;

   //item(enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::u64 uFlags = e_flag_none) :
   //   item(eelement, iItem, iSubItem, iListItem, uFlags) {}

   item(const ::user::e_flag & eflag, enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null) :
      item(eelement, iItem, iSubItem, iListItem, atom, eflag) {}

   item(enum_element eelement, const ::atom & atom)
      : item(eelement, -1, -1, -1, atom)
   {

   }

   item(enum_element eelement = ::e_element_none, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null, const ::user::e_flag uFlags = ::user::e_flag_none)
   {

      m_id = atom;

      m_eelement = eelement;

      m_iItem = iItem >= 0 ? iItem : m_eelement != ::e_element_none ? 0 : iItem;

      m_iSubItem = iSubItem;

      m_iListItem = iListItem;

      m_uFlags = uFlags;

   }

   item(::index iItem)
   {

      m_eelement = ::e_element_none;

      m_iItem = -1;

      m_iSubItem = -1;

      m_iListItem = -1;

      m_uFlags = 0;

      operator = (iItem);

   }


   item(const item & item):
      item_data(item),
      matter(item)
   {

   }


   item(item && item):
      item_data(item),
      matter(::move(item))
   {

   }
   

   bool is_drawn() { return m_uFlags & ITEM_DRAWN;  }

   void set_drawn() { m_uFlags |= ITEM_DRAWN; }

   bool is_set() const { return m_eelement != ::e_element_none; }

   operator bool() const { return is_set(); }

   operator enum_element() const { return m_eelement; }

   template < primitive_integral INTEGRAL >
   operator INTEGRAL() const { return (INTEGRAL) m_iItem; }
   
   
   
   item & operator = (const ::topic & topic) { if ((TOPIC *) this != (TOPIC *)&topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }


   bool operator == (const ::topic & topic)  const { return ((TOPIC *) this == (TOPIC *)&topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::topic & topic)  const { return !operator == (topic); }
   
   
   item & operator = (const item_base & itembase) { if ((void *) this != (void *) &itembase) memcpy((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); return *this; }

   bool operator == (const item_base & itembase)  const { return ((TOPIC *) this == (TOPIC *)&itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const item_base & itembase)  const { return !operator==(itembase); }
   
   

   item & operator = (const item_data & itemdata) { if ((TOPIC *) this != (TOPIC *) &itemdata) memcpy((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   bool operator == (const item_data & itemdata)  const { return ((TOPIC *) this == (TOPIC *) &itemdata) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); }
   bool operator != (const item_data & itemdata)  const { return !operator==(itemdata); }
   
   
   item & operator = (const ::TOPIC & topic) { if ((TOPIC *) this != (TOPIC *) &topic) memcpy((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); return *this; }

   
   bool operator == (const ::TOPIC & topic)  const { return ((TOPIC *) this == (TOPIC *) &topic) ? true : !memcmp((TOPIC *) this, (TOPIC *) &topic, sizeof(TOPIC)); }
   bool operator != (const ::TOPIC & topic)  const { return !operator == (topic); }
   
   
   item & operator = (const ITEM_BASE & itembase) { if ((TOPIC *) this != (TOPIC *) &itembase) memcpy((TOPIC *) this,(TOPIC *)  &itembase, sizeof(ITEM_BASE)); return *this; }

   bool operator == (const ITEM_BASE & itembase)  const { return ((TOPIC *) this == (TOPIC *) &itembase) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itembase, sizeof(ITEM_BASE)); }
   bool operator != (const ITEM_BASE & itembase)  const { return !operator==(itembase); }
   
   

   item & operator = (const ITEM_DATA & itemdata) { if ((TOPIC *) this != (TOPIC *) &itemdata) memcpy((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   bool operator == (const ITEM_DATA & itemdata)  const { return ((TOPIC *) this == (TOPIC *) &itemdata) ? true : !memcmp((TOPIC *) this, (TOPIC *) &itemdata, sizeof(ITEM_DATA)); }
   bool operator != (const ITEM_DATA & itemdata)  const { return !operator==(itemdata); }


   item & operator = (const item & item) { if ((TOPIC *) this != (TOPIC *) &item) memcpy((TOPIC *) this, (TOPIC *) &item, sizeof(ITEM_DATA)); return *this; }

   bool operator == (const item & item)  const { return ((TOPIC *) this == (TOPIC *) &item) ? true : !memcmp((TOPIC *) this, (TOPIC *) &item, sizeof(ITEM_DATA)); }
   bool operator != (const item & item)  const { return !operator==(item); }

   item& operator = (enum_element eelement);

   bool operator == (enum_element eelement)  const { return m_eelement == eelement; }
   bool operator != (enum_element eelement)  const { return !operator==(eelement); }

   item& operator = (const e_element& eelement) { return operator = ((enum_element)eelement); }

   bool operator == (const e_element & eelement)  const { return m_eelement == eelement; }
   bool operator != (const e_element & eelement)  const { return !operator==(eelement); }

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


   bool in_range(enum_element eelement, int iCount) const { return m_eelement >= eelement && m_eelement < eelement + iCount; }

   bool is_valid_item(::count c) const { return m_iItem >= 0 && m_iItem < c; }


};


//} // namespace item


inline bool is_set(const ::item * pitem)
{

   return ::is_set((const void * )pitem) && pitem->is_set();

}



