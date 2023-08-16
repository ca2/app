// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 21:12 BRT
#pragma once


#include "acme/constant/_constant.h"


DECLARE_ENUMERATION(e_item, enum_item);


////#include "acme/primitive/primitive/matter.h"
//#include "acme/primitive/geometry2d/point.h"
//#include "acme/primitive/geometry2d/rectangle.h"
//#include "acme/primitive/geometry2d/region.h"
#include "acme/constant/element.h"
#include "acme/user/user/_constant.h"


class item;


enum enum_item_flag : ::i64
{

   e_item_flag_none = 0,
   e_item_flag_double_click_as_second_click = 1,
   e_item_flag_eat_double_click = 2,

};




DECLARE_ENUMERATION(e_item_flag, enum_item_flag);


#pragma pack(push, handler_ITEM, 1)



struct CLASS_DECL_ACME ITEM
{


   enum_element                  m_eelement;
   ::index                       m_iItem;
   ::index                       m_iSubItem;
   ::index                       m_iListItem;


   
   ITEM()
   {
      m_eelement = e_element_none;
      m_iItem = -1;
      m_iSubItem = -1;
      m_iListItem = -1;
   }
   
   inline ITEM(const ::item * pitem);

   constexpr bool operator == (const ::ITEM & item)  const
   { 
      
      return
         m_eelement == item.m_eelement
         && m_iItem == item.m_iItem
         && m_iSubItem == item.m_iSubItem
         && m_iListItem == item.m_iListItem;
   
   }



   ///constexpr ::index item_index() const { return m_iItem; }

   constexpr bool is_item_set() const 
   { 
      
      return m_iItem >= 0 || 
         (
            m_eelement != e_element_none 
            && m_eelement != e_element_item
         ); 

   }


   operator u32hash() const { return { (const void *)this, sizeof(ITEM) }; }

   constexpr ::index menu_impact_index() const { return (::index) m_iItem; }
   constexpr ::index menu_impact_group() const { return (::index) m_iSubItem; }
   constexpr ::index menu_impact_command() const { return (::index) m_iListItem; }

   constexpr ::index item_index() const { return (::index) m_iItem; }
   constexpr ::index subitem_index() const { return (::index) m_iSubItem; }
   constexpr ::index list_item_index() const { return (::index) m_iListItem; }

};


//struct CLASS_DECL_ACME ITEM_BASE :
//   public PARTICLE,
//   public ITEM
//{
//
//
//};
//
#pragma pack(pop, handler_ITEM)


//struct CLASS_DECL_ACME ITEM_DATA :
//   public PARTICLE,
//   public ITEM_BASE_ADDITIONS,
//   public ITEM_DATA_ADDITIONS
//{
//
//
//
//};



//#define ITEM_DRAWN 0x800000


//class CLASS_DECL_ACME item_base :
//   virtual public ::matter,
//   virtual public ITEM
//{
//public:
//   
//
//   item_base()
//   {
//
//   }
//
//
//   item_base(const item_base & itembase) :
//      PARTICLE(itembase),
//      particle(itembase),
//      ITEM_BASE(itembase)
//   {
//
//   }
//
//
//   item_base(item_base && itembase) :
//      PARTICLE(::transfer(itembase)),
//      particle(::transfer(itembase)),
//      ITEM_BASE(::transfer(itembase))
//   {
//
//   }
//
//
//   bool _is_set() const override;
//
//   
//   inline ::index menu_impact_index() const { return (::index) m_iItem; }
//   inline ::index menu_impact_group() const { return (::index) m_iSubItem; }
//   inline ::index menu_impact_command() const { return (::index) m_iListItem; }
//
//   inline ::index item_index() const { return (::index) m_iItem; }
//   inline ::index subitem_index() const { return (::index) m_iSubItem; }
//   inline ::index list_item_index() const { return (::index) m_iListItem; }
//
//   
//   item_base & operator = (const ::matter & particle) { m_atom = particle.m_atom; return *this; }
//
//
//   bool operator == (const ::matter & particle) const { return m_atom == particle.m_atom; }
//   bool operator != (const ::matter & particle) const { return !operator == (particle); }
//
//   
//   item_base & operator = (const item_base & itembase) { m_atom = itembase.m_atom; ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }
//
//
//   bool operator == (const ::item_base & itembase) const { return m_atom == itembase.m_atom && ITEM_BASE_ADDITIONS::operator==(itembase); }
//   bool operator != (const ::item_base & itembase) const { return !operator == (itembase); }
//   
//
//   //item_base & operator = (const ::PARTICLE & particle) { m_atom = particle.m_atom; return *this; }
//
//
//   //bool operator == (const ::PARTICLE & particle) const { return m_atom == particle.m_atom; }
//   //bool operator != (const ::PARTICLE & particle) const { return !operator == (particle); }
//
//   
//   //item_base & operator = (const ITEM_BASE & itembase) { m_atom = itembase.m_atom; ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }
//
//
//   //bool operator == (const ::ITEM_BASE & itembase) const { return m_atom == itembase.m_atom && ITEM_BASE_ADDITIONS::operator == (itembase); }
//   //bool operator != (const ::ITEM_BASE & itembase) const { return !operator == (itembase); }
//
//
//};


//struct CLASS_DECL_ACME item_data :
//   virtual public item_base,
//   virtual public ITEM_DATA_ADDITIONS
//{
//public:
//
//
//   item_data()
//   {
//
//   }
//
//
//   item_data(const item_data & itemdata) :
//      PARTICLE(itemdata),
//      particle(itemdata),
//      ITEM_BASE_ADDITIONS(itemdata),
//      item_base(itemdata),
//      ITEM_DATA_ADDITIONS(itemdata)
//   {
//
//   }
//
//
//   item_data(item_data && itemdata) :
//      PARTICLE(::transfer(itemdata)),
//      particle(::transfer(itemdata)),
//      ITEM_BASE_ADDITIONS(::transfer(itemdata)),
//      item_base(::transfer(itemdata)),
//      ITEM_DATA_ADDITIONS(::transfer(itemdata))
//   {
//
//   }
//   
//   
//   item_data & operator = (const ::matter & particle) { m_atom = particle.m_atom; return *this; }
//
//   
//   item_data & operator = (const item_base & itembase) { item_base::operator=(itembase); return *this; }
//   
//   
//   item_data & operator = (const item_data & itemdata) 
//   { 
//      
//      item_base::operator=(itemdata); 
//      
//      ITEM_DATA_ADDITIONS::operator=(itemdata);
//      
//      return *this; 
//   
//   }
//
//
//   //item_data & operator = (const ::matter & particle) { m_atom = particle.m_atom; return *this; }
//   
//   
//   //item_data & operator = (const item_base & itembase) { item_base::operator=(itembase); return *this; }
//   
//
//   //item_data & operator = (const ITEM_DATA & itemdata)
//   //{
//
//   //   item_base::operator=(itemdata);
//
//   //   ITEM_DATA_ADDITIONS::operator=(itemdata);
//
//   //   return *this;
//
//   //}
//
//
//};

//
//namespace geometry2d
//{
//
//   class region;
//
//} // namespace geometry2d
//



class CLASS_DECL_ACME item :
   virtual public ::matter,
   virtual public ::ITEM
{
public:


   ::e_item                      m_eitem;
   ::e_item_flag                 m_eitemflag;
   
   // a user item is a "pointer"/address to a user interface matter

   //::pointer<::draw2d::graphics>     m_pgraphics;
   //::pointer<::geometry2d::region>     m_pregion;
   //bool                             m_bAnyHoverChange;

   //item(enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::u64 uFlags = e_flag_none) :
   //   item(eelement, iItem, iSubItem, iListItem, uFlags) {}

   item(const ::e_item_flag & eitemflag, enum_element eelement, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null) :
      item(eelement, iItem, iSubItem, iListItem, atom, eitemflag) {}

   item(enum_element eelement, const ::atom & atom)
      : item(eelement, -1, -1, -1, atom)
   {

   }


   item(enum_element eelement, const enum_id & id)
      : item(eelement, -1, -1, -1, id)
   {

   }

   item(enum_element eelement = ::e_element_none, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1, const ::atom & atom = ::atom::e_type_null, const ::e_item_flag eitemflag = ::e_item_flag_none)
   {

      m_atom = atom;

      m_eelement = eelement;
      
      m_eitem = e_item_none;

      m_iItem = iItem >= 0 ? iItem : m_eelement != ::e_element_none ? 0 : iItem;

      m_iSubItem = iSubItem;

      m_iListItem = iListItem;

      m_eitemflag = eitemflag;

   }

   item(::index iItem)
   {

      m_eelement = ::e_element_none;
      
      m_eitem = e_item_none;

      m_iItem = -1;

      m_iSubItem = -1;

      m_iListItem = -1;

      m_eitemflag = e_item_flag_none;

      operator = (iItem);

   }


   item(const item & item) :
      PARTICLE(item),
      particle(item),
      ITEM(item),
      //item_base(item),
      //ITEM_DATA_ADDITIONS(item),
      //item_data(item),
      matter(item)
   {

   }


   item(item && item) :
      PARTICLE(::transfer(item)),
      particle(::transfer(item)),
      ITEM(::transfer(item)),
      //item_base(::transfer(item)),
      //ITEM_DATA_ADDITIONS(::transfer(item)),
      //item_data(::transfer(item)),
      matter(::transfer(item))
   {

   }


   bool _is_set() const override;

   bool is_item_set() const { return m_atom.is_set() || m_eelement != ::e_element_none; }

   explicit operator bool() const { return is_item_set(); }

   operator enum_element() const { return m_eelement; }

   template < primitive_integral INTEGRAL >
   operator INTEGRAL() const { return (INTEGRAL)m_iItem; }

   virtual bool is_hidden() const;

   virtual ::string get_text(::index iSubItem);

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

   using ITEM::operator=;
   using ITEM::operator==;
   //using ITEM::operator!=;


   item & operator = (const item & item)
   {

      ITEM::operator=(item);

      m_eitemflag = item.m_eitemflag;
      m_eelement = item.m_eelement;
      m_eitem = item.m_eitem;

      //m_pgraphics = item.m_pgraphics;

      // m_ppath = item.m_ppath;

      return *this;

   }


   bool operator == (const item & item) const { return ITEM::operator ==(item); }
   //bool operator != (const item & item) const { return !operator==(item); }


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


using item_pointer = ::pointer<::item>;


//} // namespace item


inline bool is_item_set(const ::ITEM * pitem)
{

   return ::is_set((const void * )pitem) && pitem->is_item_set();

}


inline bool is_item_set_and_non_negative(const ::item* pitem)
{

   return ::is_item_set(pitem) && pitem->m_iItem >= 0;

}


inline bool is_element(const ::item * pitem, ::enum_element eelement)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set() && pitem->m_eelement == eelement;

}


inline bool is_item(const ::item * pitem, ::index iItem)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set()
      && pitem->m_iItem == iItem;

}



inline bool is_subitem(const ::item * pitem, ::index iSubItem)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set()
      && pitem->m_iSubItem == iSubItem;

}


inline bool subitem_less_than(const ::item * pitem, ::index iSubItem)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set()
      && pitem->m_iSubItem < iSubItem;

}


inline bool in_element_range(const ::item * pitem, enum_element eelement, int iCount)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set() &&
      pitem->in_element_range(eelement, iCount);

}


inline ::pointer<::item>new_item_with_index(::index iIndex)
{

   return __new(::item(::e_element_item, iIndex));

}


inline bool is_same_item(const ::item * pitem1, const ::item * pitem2)
{

   if (::is_item_set(pitem1))
   {

      if (::is_item_set(pitem2))
      {

         return *pitem1 == *pitem2;

      }
      else
      {

         return false;

      }

   }
   else if (::is_item_set(pitem2))
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


inline bool is_item_index(const ::item * pitem, ::index iItem)
{
   
   return ::is_element(pitem, ::e_element_item) && ::is_item(pitem, iItem);
   
}


inline bool is_item_equivalent(const ::item_t * pitem1, const ::item_t * pitem2)
{

   if (!::is_item_set(pitem1) || !::is_item_set(pitem2))
   {

      return false;

   }

   if (pitem1 == pitem2)
   {

      return true;

   }


   return *pitem1 == *pitem2;

}


inline ITEM::ITEM(const ::item * pitem) :
   ITEM(*pitem)
{


}



using item_array = ::pointer_array < ::item >;


