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
   

   bool operator == (const ::ITEM_BASE_ADDITIONS & itembaseadditions)  const
   { 
      
      return m_eelement == itembaseadditions.m_eelement
         && m_iItem == itembaseadditions.m_iItem
         && m_iSubItem == itembaseadditions.m_iSubItem
         && m_iListItem == itembaseadditions.m_iListItem;
   
   }


   
};


struct ITEM_DATA_ADDITIONS
{

   
   ::point_i32                   m_pointScreen;
   ::point_i32                   m_pointHost;
   ::point_i32                   m_pointClient;
   ::point_i32                   m_pointHitTest;
   ::rectangle_i32               m_rectangle;
   u64                           m_uFlags;
   __pointer(::element)          m_pelement;
   void *                        m_data[4];
   

   ITEM_DATA_ADDITIONS & operator = (const ITEM_DATA_ADDITIONS & itemdataadditions)
   { 

      m_pointScreen = itemdataadditions.m_pointScreen;
      m_pointHost = itemdataadditions.m_pointHost;
      m_pointClient = itemdataadditions.m_pointClient;
      m_pointHitTest = itemdataadditions.m_pointHitTest;
      m_rectangle = itemdataadditions.m_rectangle;
      m_uFlags = itemdataadditions.m_uFlags;
      m_pelement = itemdataadditions.m_pelement;

      return *this;
      
   }


};


struct ITEM_BASE :
   public PARTICLE,
   public ITEM_BASE_ADDITIONS
{


};


struct ITEM_DATA :
   public PARTICLE,
   public ITEM_BASE_ADDITIONS,
   public ITEM_DATA_ADDITIONS
{



};


#pragma pack(pop, user_ITEM)


#define ITEM_DRAWN 0x800000


class CLASS_DECL_ACME item_base :
   virtual public ::particle,
   virtual public ITEM_BASE_ADDITIONS
{
public:
   

   item_base()
   {

   }


   item_base(const item_base & itembase) :
      PARTICLE(itembase),
      particle(itembase),
      ITEM_BASE_ADDITIONS(itembase)
   {

   }


   item_base(item_base && itembase) :
      PARTICLE(::move(itembase)),
      particle(::move(itembase)),
      ITEM_BASE_ADDITIONS(::move(itembase))
   {

   }
   
   inline ::index menu_impact_index() const { return (::index) m_iItem; }
   inline ::index menu_impact_group() const { return (::index) m_iSubItem; }
   inline ::index menu_impact_command() const { return (::index) m_iListItem; }

   inline ::index item_index() const { return (::index) m_iItem; }
   inline ::index subitem_index() const { return (::index) m_iSubItem; }
   inline ::index list_item_index() const { return (::index) m_iListItem; }

   
   item_base & operator = (const ::particle & particle) { m_atom = particle.m_atom; return *this; }


   bool operator == (const ::particle & particle) const { return m_atom == particle.m_atom; }
   bool operator != (const ::particle & particle) const { return !operator == (particle); }

   
   item_base & operator = (const item_base & itembase) { m_atom = itembase.m_atom; ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }


   bool operator == (const ::item_base & itembase) const { return m_atom == itembase.m_atom && ITEM_BASE_ADDITIONS::operator==(itembase); }
   bool operator != (const ::item_base & itembase) const { return !operator == (itembase); }
   

   item_base & operator = (const ::PARTICLE & particle) { m_atom = particle.m_atom; return *this; }


   bool operator == (const ::PARTICLE & particle) const { return m_atom == particle.m_atom; }
   bool operator != (const ::PARTICLE & particle) const { return !operator == (particle); }

   
   item_base & operator = (const ITEM_BASE & itembase) { m_atom = itembase.m_atom; ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }


   bool operator == (const ::ITEM_BASE & itembase) const { return m_atom == itembase.m_atom && ITEM_BASE_ADDITIONS::operator == (itembase); }
   bool operator != (const ::ITEM_BASE & itembase) const { return !operator == (itembase); }


};


struct CLASS_DECL_ACME item_data :
   virtual public item_base,
   virtual public ITEM_DATA_ADDITIONS
{
public:


   item_data()
   {

   }


   item_data(const item_data & itemdata) :
      PARTICLE(itemdata),
      particle(itemdata),
      ITEM_BASE_ADDITIONS(itemdata),
      item_base(itemdata),
      ITEM_DATA_ADDITIONS(itemdata)
   {

   }


   item_data(item_data && itemdata) :
      PARTICLE(::move(itemdata)),
      particle(::move(itemdata)),
      ITEM_BASE_ADDITIONS(::move(itemdata)),
      item_base(::move(itemdata)),
      ITEM_DATA_ADDITIONS(::move(itemdata))
   {

   }
   
   
   item_data & operator = (const ::particle & particle) { m_atom = particle.m_atom; return *this; }

   
   item_data & operator = (const item_base & itembase) { item_base::operator=(itembase); return *this; }
   
   
   item_data & operator = (const item_data & itemdata) 
   { 
      
      item_base::operator=(itemdata); 
      
      ITEM_DATA_ADDITIONS::operator=(itemdata);
      
      return *this; 
   
   }


   item_data & operator = (const ::PARTICLE & particle) { m_atom = particle.m_atom; return *this; }
   
   
   item_data & operator = (const ITEM_BASE & itembase) { item_base::operator=(itembase); return *this; }
   

   item_data & operator = (const ITEM_DATA & itemdata)
   {

      item_base::operator=(itemdata);

      ITEM_DATA_ADDITIONS::operator=(itemdata);

      return *this;

   }


};


class CLASS_DECL_ACME item :
   virtual public item_data,
   virtual public ::matter
{
public:

   // a user item is a "pointer"/address to a user interface matter

   __pointer(::draw2d::graphics)    m_pgraphics;
   __pointer(::draw2d::path)        m_ppath;
   __pointer(::user::mouse)         m_pmouse;
   bool                             m_bAnyHoverChange;

   //item(enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::u64 uFlags = e_flag_none) :
   //   item(eelement, iItem, iSubItem, iListItem, uFlags) {}

   item(const ::user::e_flag & eflag, enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null) :
      item(eelement, iItem, iSubItem, iListItem, atom, eflag) {}

   item(enum_element eelement, const ::atom & atom)
      : item(eelement, -1, -1, -1, atom)
   {

   }


   item(enum_element eelement, const enum_id & id)
      : item(eelement, -1, -1, -1, id)
   {

   }

   item(enum_element eelement = ::e_element_none, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null, const ::user::e_flag uFlags = ::user::e_flag_none)
   {

      m_atom = atom;

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


   item(const item & item) :
      PARTICLE(item),
      particle(item),
      ITEM_BASE_ADDITIONS(item),
      item_base(item),
      ITEM_DATA_ADDITIONS(item),
      item_data(item),
      matter(item)
   {

   }


   item(item && item) :
      PARTICLE(::move(item)),
      particle(::move(item)),
      ITEM_BASE_ADDITIONS(::move(item)),
      item_base(::move(item)),
      ITEM_DATA_ADDITIONS(::move(item)),
      item_data(::move(item)),
      matter(::move(item))
   {

   }


   bool is_drawn() { return m_uFlags & ITEM_DRAWN; }

   void set_drawn() { m_uFlags |= ITEM_DRAWN; }

   bool is_set() const { return m_atom.is_set() || m_eelement != ::e_element_none; }

   operator bool() const { return is_set(); }

   operator enum_element() const { return m_eelement; }

   template < primitive_integral INTEGRAL >
   operator INTEGRAL() const { return (INTEGRAL)m_iItem; }



   //item & operator = (const ::particle & particle) { m_atom = if ((PARTICLE *) this != (PARTICLE *)&particle) memcpy((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); return *this; }


   //bool operator == (const ::particle & particle)  const { return ((PARTICLE *) this == (PARTICLE *)&particle) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); }
   //bool operator != (const ::particle & particle)  const { return !operator == (particle); }
   //
   //
   //item & operator = (const item_base & itembase) { if ((void *) this != (void *) &itembase) memcpy((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); return *this; }

   //bool operator == (const item_base & itembase)  const { return ((PARTICLE *) this == (PARTICLE *)&itembase) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); }
   //bool operator != (const item_base & itembase)  const { return !operator==(itembase); }
   //
   //

   //item & operator = (const item_data & itemdata) { if ((PARTICLE *) this != (PARTICLE *) &itemdata) memcpy((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   //bool operator == (const item_data & itemdata)  const { return ((PARTICLE *) this == (PARTICLE *) &itemdata) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); }
   //bool operator != (const item_data & itemdata)  const { return !operator==(itemdata); }
   //
   //
   //item & operator = (const ::PARTICLE & particle) { if ((PARTICLE *) this != (PARTICLE *) &particle) memcpy((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); return *this; }

   //
   //bool operator == (const ::PARTICLE & particle)  const { return ((PARTICLE *) this == (PARTICLE *) &particle) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); }
   //bool operator != (const ::PARTICLE & particle)  const { return !operator == (particle); }


   //item & operator = (const ITEM_BASE_ADDITIONS & itembaseadditions) { if ((ITEM_BASE_ADDITIONS *)this != (ITEM_BASE_ADDITIONS *)&itembaseadditions) memcpy((ITEM_BASE_ADDITIONS *)this, (ITEM_BASE_ADDITIONS *)&itembaseadditions, sizeof(ITEM_BASE_ADDITIONS)); return *this; }

   //bool operator == (const ITEM_BASE_ADDITIONS & itembaseadditions)  const { return ((ITEM_BASE_ADDITIONS *)this == (ITEM_BASE_ADDITIONS *)&itembaseadditions) ? true : !memcmp((ITEM_BASE_ADDITIONS *)this, (ITEM_BASE_ADDITIONS *)&itembaseadditions, sizeof(ITEM_BASE_ADDITIONS)); }
   //bool operator != (const ITEM_BASE_ADDITIONS & itembaseadditions)  const { return !operator==(itembaseadditions); }


   //
   //item & operator = (const ITEM_BASE & itembase) { if ((PARTICLE *) this != (PARTICLE *) &itembase) memcpy((PARTICLE *) this,(PARTICLE *)  &itembase, sizeof(ITEM_BASE)); return *this; }

   //bool operator == (const ITEM_BASE & itembase)  const { return ((PARTICLE *) this == (PARTICLE *) &itembase) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); }
   //bool operator != (const ITEM_BASE & itembase)  const { return !operator==(itembase); }
   //
   //

   //item & operator = (const ITEM_DATA & itemdata) { if ((PARTICLE *) this != (PARTICLE *) &itemdata) memcpy((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   //bool operator == (const ITEM_DATA & itemdata)  const { return ((PARTICLE *) this == (PARTICLE *) &itemdata) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); }
   //bool operator != (const ITEM_DATA & itemdata)  const { return !operator==(itemdata); }

   using item_data::operator=;
   using item_data::operator==;
   using item_data::operator!=;


   item & operator = (const item & item)
   {

      item_data::operator=(item);

      m_pgraphics = item.m_pgraphics;

      m_ppath = item.m_ppath;

      return *this;

   }


   bool operator == (const item & item) const { return item_base::operator ==(item); }
   bool operator != (const item & item) const { return !operator==(item); }


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


   bool in_element_range(enum_element eelement, int iCount) const { return m_eelement >= eelement && m_eelement < eelement + iCount; }

   bool is_valid_item(::count c) const { return m_iItem >= 0 && m_iItem < c; }


};


using item_pointer = __pointer(::item);


//} // namespace item


inline bool is_set(const ::item * pitem)
{

   return ::is_set((const void * )pitem) && pitem->is_set();

}


inline bool is_element(const ::item * pitem, ::enum_element eelement)
{

   return ::is_set((const void *)pitem) && pitem->is_set() && pitem->m_eelement == eelement;

}


inline bool is_item(const ::item * pitem, ::index iItem)
{

   return ::is_set((const void *)pitem) && pitem->is_set()
      && pitem->m_iItem == iItem;

}


inline bool is_subitem(const ::item * pitem, ::index iSubItem)
{

   return ::is_set((const void *)pitem) && pitem->is_set()
      && pitem->m_iSubItem == iSubItem;

}

inline bool subitem_less_than(const ::item * pitem, ::index iSubItem)
{

   return ::is_set((const void *)pitem) && pitem->is_set()
      && pitem->m_iSubItem < iSubItem;

}


inline bool in_element_range(const ::item * pitem, enum_element eelement, int iCount)
{

   return ::is_set((const void *)pitem) && pitem->is_set() &&
      pitem->in_element_range(eelement, iCount);

}


inline __pointer(::item) new_item_with_index(::index iIndex)
{

   return __new(::item(::e_element_item, iIndex));

}


inline bool is_same_item(const ::item * pitem1, const ::item * pitem2)
{

   if (::is_set(pitem1))
   {

      if (::is_set(pitem2))
      {

         return *pitem1 == *pitem2;

      }
      else
      {

         return false;

      }

   }
   else if (::is_set(pitem2))
   {

      return false;

   }
   else
   {

      return true;

   }

}


inline enum_element item_element(const ::item * pitem)
{

   return ::is_set(pitem) ? pitem->m_eelement : e_element_none;

}


inline ::index item_index(const ::item * pitem)
{

   return ::is_set(pitem) ? pitem->item_index() : -1;

}



