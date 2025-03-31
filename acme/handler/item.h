// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 21:12 BRT
#pragma once


#include "acme/constant/_constant.h"
#include "acme/constant/element.h"
#include "acme/user/user/_constant.h"


class item;


DECLARE_ENUMERATION(e_item, enum_item);


enum enum_item_flag : long long
{

   e_item_flag_none = 0,
   e_item_flag_double_click_as_second_click = 1,
   e_item_flag_eat_double_click = 2,
   e_item_flag_drag = 4,

};


DECLARE_ENUMERATION(e_item_flag, enum_item_flag);


struct item_t
{


   enum_element                  m_eelement;
   ::collection::index                       m_iItem;
   ::collection::index                       m_iSubItem;
   ::collection::index                       m_iListItem;


   
   constexpr item_t(enum_element eelement = e_element_none, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1) :
      // constexpr item_t(enum_element eelement = e_element_none, ::collection::index iItem = -1) :
      m_eelement(eelement),
      m_iItem(iItem)
      //,m_iSubItem(iSubItem)
      //,m_iListItem(iListItem)
   {
   }

   inline item_t(const ::item_t & item) = default;
   
   inline item_t(const ::item * pitem);

   constexpr bool operator == (const ::item_t & item)  const
   { 
      
      return
         m_eelement == item.m_eelement
         && m_iItem == item.m_iItem
         && m_iSubItem == item.m_iSubItem
         && m_iListItem == item.m_iListItem;
   
   }

   constexpr bool is_item_set() const
   { 
      
      return m_iItem >= 0 || 
         (
            m_eelement != e_element_none 
            && m_eelement != e_element_item
         ); 

   }


   operator hash32() const { return { (const void *)this, sizeof(item_t) }; }

   //constexpr ::collection::index menu_impact_index() const { return (::collection::index) m_iItem; }
   //constexpr ::collection::index menu_impact_group() const { return (::collection::index) m_iSubItem; }
   //constexpr ::collection::index menu_impact_command() const { return (::collection::index) m_iListItem; }

   //constexpr ::collection::index item_index() const { return (::collection::index) m_iItem; }
   //constexpr ::collection::index subitem_index() const { return (::collection::index) m_iSubItem; }
   //constexpr ::collection::index list_item_index() const { return (::collection::index) m_iListItem; }

};

class CLASS_DECL_ACME item :
   virtual public ::matter
{
public:
   

   item_t                        m_item;
   ::e_item                      m_eitem;
   ::e_item_flag                 m_eitemflag;
   
   // a user item is a "pointer"/address to a user interface matter

   //::pointer<::draw2d::graphics>     m_pgraphics;
   //::pointer<::geometry2d::region>     m_pregion;
   //bool                             m_bAnyHoverChange;

   //item(enum_element eelement, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const unsigned long long uFlags = e_flag_none) :
     // item(eelement, iItem, iSubItem, iListItem, uFlags) {}

   
   item(::enum_item_flag eitemflag, enum_element eelement, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const ::atom & atom = ::atom::e_type_null) :
      item(eelement, iItem, iSubItem, iListItem, atom, eitemflag) 
   {

   }

   //item(const ::e_item_flag & eitemflag, enum_element eelement, ::collection::index iItem = -1, const ::atom & atom = ::atom::e_type_null) :
     // item(eelement, iItem, atom, eitemflag) {}

   item(enum_element eelement, const ::atom & atom)
      : item(eelement, atom.is_integer() ? atom.as_index() : -1, -1, -1, atom.is_integer() ? ::atom() : atom)
   {

   }


   item(enum_element eelement, enum_id eid)
      : item(eelement, -1, -1, -1, (const ::atom &) eid)
   {

   }


   item(enum_element eelement = ::e_element_none, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const ::atom & atom = ::atom::e_type_null, ::enum_item_flag eitemflag = ::e_item_flag_none) :
      m_item(eelement, iItem, iSubItem, iListItem),
      m_eitem(e_item_none),
      m_eitemflag(eitemflag)
   {

   }


   item(const ::item_t & item, ::enum_item_flag eitemflag = ::e_item_flag_none) :
      m_item(item),
      m_eitem(e_item_none),
      m_eitemflag(eitemflag)
   {

   }


   // item(::collection::index iItem) :
   // m_item(e_element_none, iItem)
   // {

   //    m_eitem = e_item_none;

   //    m_eitemflag = e_item_flag_none;

   // }


   item(const item & item) :
      subparticle(item),
      particle(item),
      m_item(item.m_item),
      m_eitem(item.m_eitem),
      m_eitemflag(item.m_eitemflag),
      //item_base(item),
      //ITEM_DATA_ADDITIONS(item),
      //item_data(item),
      matter(item)
   {

   }


   item(item && item) :
      subparticle(::transfer(item)),
      particle(::transfer(item)),
      m_item(::transfer(item.m_item)),
      m_eitem(::transfer(item.m_eitem)),
      m_eitemflag(::transfer(item.m_eitemflag)),
      //item_base(::transfer(item)),
      //ITEM_DATA_ADDITIONS(::transfer(item)),
      //item_data(::transfer(item)),
      matter(::transfer(item))
   {

   }


   void get_debug_title(char *sz, character_count c) const override;

   bool _is_set() const override;

   bool is_item_set() const { return m_atomMatterId.is_set() || m_item.m_eelement != ::e_element_none; }

   explicit operator bool() const { return is_item_set(); }

   //operator enum_element() const { return m_item.m_eelement; }

//   template < primitive_integral INTEGRAL >
//   operator INTEGRAL() const { return (INTEGRAL)m_item.m_iItem; }

   virtual bool is_hidden() const;

   virtual ::string get_item_text(::user::item_base * puseritembase, ::collection::index iSubItem = 0);
   virtual ::collection::index get_item_image(::user::item_base * puseritembase, ::collection::index iSubItem = 0);
   virtual ::image::image_list * get_item_image_list(::user::item_base * puseritembase, ::collection::index iSubItem = 0);
   
//   operator const ::item_t &() const {return m_item;}
//   operator ::item_t &() {return m_item;}
//
//   operator const ::item_t *() const {return &m_item;}
//   operator ::item_t *() {return &m_item;}

   //item & operator = (const ::particle & particle) { id() = if ((PARTICLE *) this != (PARTICLE *)&particle) ::memory_copy((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); return *this; }


   //bool operator == (const ::particle & particle)  const { return ((PARTICLE *) this == (PARTICLE *)&particle) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); }
   //bool operator != (const ::particle & particle)  const { return !operator == (particle); }
   //
   //
   //item & operator = (const item_base & itembase) { if ((void *) this != (void *) &itembase) ::memory_copy((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); return *this; }

   //bool operator == (const item_base & itembase)  const { return ((PARTICLE *) this == (PARTICLE *)&itembase) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); }
   //bool operator != (const item_base & itembase)  const { return !operator==(itembase); }
   //
   //

   //item & operator = (const item_data & itemdata) { if ((PARTICLE *) this != (PARTICLE *) &itemdata) ::memory_copy((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   //bool operator == (const item_data & itemdata)  const { return ((PARTICLE *) this == (PARTICLE *) &itemdata) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); }
   //bool operator != (const item_data & itemdata)  const { return !operator==(itemdata); }
   //
   //
   //item & operator = (const ::PARTICLE & particle) { if ((PARTICLE *) this != (PARTICLE *) &particle) ::memory_copy((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); return *this; }

   //
   //bool operator == (const ::PARTICLE & particle)  const { return ((PARTICLE *) this == (PARTICLE *) &particle) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &particle, sizeof(PARTICLE)); }
   //bool operator != (const ::PARTICLE & particle)  const { return !operator == (particle); }


   //item & operator = (const ITEM_BASE_ADDITIONS & itembaseadditions) { if ((ITEM_BASE_ADDITIONS *)this != (ITEM_BASE_ADDITIONS *)&itembaseadditions) ::memory_copy((ITEM_BASE_ADDITIONS *)this, (ITEM_BASE_ADDITIONS *)&itembaseadditions, sizeof(ITEM_BASE_ADDITIONS)); return *this; }

   //bool operator == (const ITEM_BASE_ADDITIONS & itembaseadditions)  const { return ((ITEM_BASE_ADDITIONS *)this == (ITEM_BASE_ADDITIONS *)&itembaseadditions) ? true : !memcmp((ITEM_BASE_ADDITIONS *)this, (ITEM_BASE_ADDITIONS *)&itembaseadditions, sizeof(ITEM_BASE_ADDITIONS)); }
   //bool operator != (const ITEM_BASE_ADDITIONS & itembaseadditions)  const { return !operator==(itembaseadditions); }


   //
   //item & operator = (const ITEM_BASE & itembase) { if ((PARTICLE *) this != (PARTICLE *) &itembase) ::memory_copy((PARTICLE *) this,(PARTICLE *)  &itembase, sizeof(ITEM_BASE)); return *this; }

   //bool operator == (const ITEM_BASE & itembase)  const { return ((PARTICLE *) this == (PARTICLE *) &itembase) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itembase, sizeof(ITEM_BASE)); }
   //bool operator != (const ITEM_BASE & itembase)  const { return !operator==(itembase); }
   //
   //

   //item & operator = (const ITEM_DATA & itemdata) { if ((PARTICLE *) this != (PARTICLE *) &itemdata) ::memory_copy((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); return *this; }

   //bool operator == (const ITEM_DATA & itemdata)  const { return ((PARTICLE *) this == (PARTICLE *) &itemdata) ? true : !memcmp((PARTICLE *) this, (PARTICLE *) &itemdata, sizeof(ITEM_DATA)); }
   //bool operator != (const ITEM_DATA & itemdata)  const { return !operator==(itemdata); }

   //using ITEM::operator=;
   //using ITEM::operator==;
   //using ITEM::operator!=;


   item & operator = (const item & item)
   {

      m_item = item.m_item;
      m_eitem = item.m_eitem;
      m_eitemflag = item.m_eitemflag;

      //m_pgraphics = item.m_pgraphics;

      // m_ppath = item.m_ppath;

      return *this;

   }


   bool operator == (const item & item) const { return m_item == item.m_item; }
   //bool operator != (const item & item) const { return !operator==(item); }


   item& operator = (enum_element eelement);

   bool operator == (enum_element eelement)  const { return m_item.m_eelement == eelement; }
   //bool operator != (enum_element eelement)  const { return !operator==(eelement); }

   item& operator = (const e_element& eelement) { return operator = ((enum_element)eelement); }

   bool operator == (const e_element & eelement)  const { return m_item.m_eelement == eelement; }
//   bool operator != (const e_element & eelement)  const { return !operator==(eelement); }

   item & operator = (::collection::index iItem);

   bool operator == (::collection::index iItem)  const { return m_item.m_iItem == iItem; }
//   bool operator != (::collection::index iItem)  const { return m_iItem != iItem; }

   std::strong_ordering operator <= (::collection::index iItem)  const { return m_item.m_iItem <=> iItem; }
//   bool operator >= (::collection::index iItem)  const { return m_iItem >= iItem; }
//
//   bool operator < (::collection::index iItem)  const { return m_iItem < iItem; }
//   bool operator > (::collection::index iItem)  const { return m_iItem > iItem; }

   ::collection::index operator + (int iItemAdd) { return (::collection::index) (m_item.m_iItem + iItemAdd); }
   ::collection::index operator - (int iItemSub) { return (::collection::index) (m_item.m_iItem - iItemSub); }

   ::collection::index operator + (long long iItemAdd) { return (::collection::index) (m_item.m_iItem + iItemAdd); }
   ::collection::index operator - (long long iItemSub) { return (::collection::index) (m_item.m_iItem - iItemSub); }


   bool in_element_range(enum_element eelement, int iCount) const { return m_item.m_eelement >= eelement && m_item.m_eelement < eelement + iCount; }

   //bool is_valid_item(::collection::count c) const { return m_item.m_iItem >= 0 && m_item.m_iItem < c; }
   
   
   


};


using item_pointer = ::pointer<::item>;


//} // namespace item


inline bool is_item_set(const ::item_t * pitem)
{

   return ::is_set((const void * )pitem) && pitem->is_item_set();

}

inline bool is_item_set(const ::item * pitem)
{

   return ::is_item_set(&pitem->m_item);

}


inline bool is_item_set_and_non_negative(const ::item* pitem)
{

   return ::is_item_set(pitem) && pitem->m_item.m_iItem >= 0;

}


inline bool is_element(const ::item * pitem, ::enum_element eelement)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set() && pitem->m_item.m_eelement == eelement;

}


inline bool is_item(const ::item * pitem, ::collection::index iItem)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set()
      && pitem->m_item.m_iItem == iItem;

}



inline bool is_subitem(const ::item * pitem, ::collection::index iSubItem)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set()
      && pitem->m_item.m_iSubItem == iSubItem;

}


//inline bool subitem_less_than(const ::item * pitem, ::collection::index iSubItem)
//{
//
//   return ::is_set((const void *)pitem) && pitem->is_item_set()
//      && pitem->m_item.m_iSubItem < iSubItem;
//
//}


inline bool in_element_range(const ::item * pitem, enum_element eelement, int iCount)
{

   return ::is_set((const void *)pitem) && pitem->is_item_set() &&
      pitem->in_element_range(eelement, iCount);

}


inline ::pointer<::item>new_item_with_index(::collection::index iIndex)
{

   return __allocate ::item(::e_element_item, iIndex);

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

   return ::is_set(pitem) ? pitem->m_item.m_eelement : e_element_none;

}


inline ::collection::index item_index(const ::item * pitem)
{

   return ::is_set(pitem) ? pitem->m_item.m_iItem : -1;

}


inline bool is_item_index(const ::item * pitem, ::collection::index iItem)
{
   
   return ::is_element(pitem, ::e_element_item) && ::is_item(pitem, iItem);
   
}


inline bool is_item_equivalent(const ::item_t * pitem1, const ::item_t * pitem2)
{

   if (pitem1 == pitem2)
   {

      return true;

   }

   if (!::is_item_set(pitem1))
   {

      if (!::is_item_set(pitem2))
      {

         return true;

      }
      else
      {

         return false;

      }

   }
   else if (!::is_item_set(pitem2))
   {

      return false;

   }

   return *pitem1 == *pitem2;

}


inline item_t::item_t(const ::item * pitem) :
   item_t(::is_set(pitem) ? pitem->m_item : ::item_t())
{

}



using item_array = ::pointer_array < ::item >;


inline bool is_item_equivalent(const ::item * pitem1, const ::item * pitem2)
{
   
   return is_item_equivalent(&pitem1->m_item, &pitem2->m_item);
   
}


template < typename ITEM >
concept prototype_item = ::std::is_base_of_v < ::item, ITEM >;






