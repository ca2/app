// From acme/handler/item.h by camilo on 2023-08-10 16:43 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/handler/item.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace user
{


   //enum enum_item : huge_integer
   //{

   //   e_item_normal = 0,
   //   e_item_tool,

   //};


   DECLARE_ENUMERATION(e_item, enum_item);


   enum enum_item_flag
   {

      e_item_flag_none = 0,
      e_item_flag_drawn = 0x800000,
      e_item_flag_rectangle_callback = 0x4000,

   };

   DECLARE_ENUMERATION(e_item_flag, enum_item_flag);
   

//#pragma pack(push, user_ITEM, 1)
//
//
//   struct CLASS_DECL_ACME ITEM
//   {
//
//
//      union // small 1 bedroom ap
//      {
//         void * m_data[4];
//         struct // this part is structured?!?!?! (hipocritical but ok..)
//         {
//            // they are hipo, so... they think they are aligned...
//            ::user::tool_item * m_ptoolitem;
//            // journalists inventing science that scientists get surprised when we mention to them, you know... - like global warming and ozone layer - so important as these comments... "so a kid is smarter than scientists..." - by lol, what a genius, right?!
//            // universities, media, police, justice, religion and politics, and lately also javascript and invented artificial programming languages, to ensure you give money to professors, journalists and artists, cops and lawyers, juddge, priests and suits, imposed by entertainement, guns, contracts, existence and cheering for a team you just choose. For having few food and fun, you have to give these impostors a lot of money, otherwise instead of movies, they make covid and they work together with universities, media, police, justice and polictis, and religious people obbey laws... ans so on..
//            // wait for the next... they have nothing to do and a lot of time in between to be creative, you know...
//            // journalists could teach to cook... and... universities to build... police muscles for night club entertenament... justice for history... policits for some directions and religion for interpreting the universe... because there are billions of galaxies... because sci-fi is not science, it is a religion of pretending to be better than rich people by knowning some physics... and rich people turn rich on flesh but they are later invited to trampolin to finance the circus above on the shoulders of slaves with some controlled youtube and macdonalds and starbucks...
//         };
//      };
//
//
//      ::item_pointer                m_pitem;
//      ::int_point                   m_pointScreen;
//      ::int_point                   m_pointHost;
//      ::int_point                   m_pointClient;
//      ::int_point                   m_pointHitTest;
//      ::int_rectangle               m_rectangle;
//      ::user::e_item                m_eitem;
//      ::particle_pointer      m_pparticle;
//      ::user::e_zorder              m_ezorder;
//      ::user::e_item_flag           m_euseritemflag;
//
//
//      ITEM(::item * pitem = nullptr) :
//         m_pitem(pitem)
//      {
//
//         m_ezorder = ::user::e_zorder_front;
//
//      }
//
//
//      ~ITEM()
//      {
//
//
//      }
//
//
//      ITEM & operator = (const ITEM & itemdataadditions)
//      {
//
//         m_pointScreen = itemdataadditions.m_pointScreen;
//         m_pointHost = itemdataadditions.m_pointHost;
//         m_pointClient = itemdataadditions.m_pointClient;
//         m_pointHitTest = itemdataadditions.m_pointHitTest;
//         m_rectangle = itemdataadditions.m_rectangle;
//         //m_uFlags = itemdataadditions.m_uFlags;
//         m_pparticle = itemdataadditions.m_pparticle;
//
//         return *this;
//
//      }
//
//
//      inline ::user::tool_item * tool_item() { return ::is_set(m_pitem) && m_pitem->m_eitem == e_item_tool ? m_ptoolitem : nullptr; }
//      inline ::user::tool_item * tool_item() const { return ((::user::ITEM *)this)->tool_item(); }
//
//      bool is_drawn() { return m_euseritemflag & e_item_flag_drawn; }
//
//      void set_drawn() { m_euseritemflag |= e_item_flag_drawn; }
//
//
//
//   };
//
//
//#pragma pack(pop, user_ITEM)


   //struct CLASS_DECL_ACME ITEM_BASE :
   //   public ::particle,
   //   public ::user::ITEM
   //{





   //};






   //class CLASS_DECL_ACME item_base :
   //   virtual public ::matter,
   //   virtual public ITEM_BASE_ADDITIONS
   //{
   //public:


   //   item_base()
   //   {

   //   }


   //   item_base(const item_base & itembase) :
   //      PARTICLE(itembase),
   //      particle(itembase),
   //      ITEM_BASE_ADDITIONS(itembase)
   //   {

   //   }


   //   item_base(item_base && itembase) :
   //      PARTICLE(::transfer(itembase)),
   //      particle(::transfer(itembase)),
   //      ITEM_BASE_ADDITIONS(::transfer(itembase))
   //   {

   //   }


   //   bool _is_set() const override;


   //   inline ::collection::index menu_impact_index() const { return (::collection::index)m_iItem; }
   //   inline ::collection::index menu_impact_group() const { return (::collection::index)m_iSubItem; }
   //   inline ::collection::index menu_impact_command() const { return (::collection::index)m_iListItem; }

   //   inline ::collection::index item_index() const { return (::collection::index)m_iItem; }
   //   inline ::collection::index subitem_index() const { return (::collection::index)m_iSubItem; }
   //   inline ::collection::index list_item_index() const { return (::collection::index)m_iListItem; }


   //   item_base & operator = (const ::matter & particle) { id() = particle.id(); return *this; }


   //   bool operator == (const ::matter & particle) const { return id() == particle.id(); }
   //   bool operator != (const ::matter & particle) const { return !operator == (particle); }


   //   item_base & operator = (const item_base & itembase) { id() = itembase.id(); ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }


   //   bool operator == (const ::item_base & itembase) const { return id() == itembase.id() && ITEM_BASE_ADDITIONS::operator==(itembase); }
   //   bool operator != (const ::item_base & itembase) const { return !operator == (itembase); }


   //   //item_base & operator = (const ::PARTICLE & particle) { id() = particle.id(); return *this; }


   //   //bool operator == (const ::PARTICLE & particle) const { return id() == particle.id(); }
   //   //bool operator != (const ::PARTICLE & particle) const { return !operator == (particle); }


   //   //item_base & operator = (const ITEM_BASE & itembase) { id() = itembase.id(); ((ITEM_BASE_ADDITIONS &)*this) = ((ITEM_BASE_ADDITIONS &)itembase); return *this; }


   //   //bool operator == (const ::ITEM_BASE & itembase) const { return id() == itembase.id() && ITEM_BASE_ADDITIONS::operator == (itembase); }
   //   //bool operator != (const ::ITEM_BASE & itembase) const { return !operator == (itembase); }


   //};


   //struct CLASS_DECL_ACME item_data :
   //   virtual public item_base,
   //   virtual public ITEM_DATA_ADDITIONS
   //{
   //public:


   //   item_data()
   //   {

   //   }


   //   item_data(const item_data & itemdata) :
   //      PARTICLE(itemdata),
   //      particle(itemdata),
   //      ITEM_BASE_ADDITIONS(itemdata),
   //      item_base(itemdata),
   //      ITEM_DATA_ADDITIONS(itemdata)
   //   {

   //   }


   //   item_data(item_data && itemdata) :
   //      PARTICLE(::transfer(itemdata)),
   //      particle(::transfer(itemdata)),
   //      ITEM_BASE_ADDITIONS(::transfer(itemdata)),
   //      item_base(::transfer(itemdata)),
   //      ITEM_DATA_ADDITIONS(::transfer(itemdata))
   //   {

   //   }


   //   item_data & operator = (const ::matter & particle) { id() = particle.id(); return *this; }


   //   item_data & operator = (const item_base & itembase) { item_base::operator=(itembase); return *this; }


   //   item_data & operator = (const item_data & itemdata)
   //   {

   //      item_base::operator=(itemdata);

   //      ITEM_DATA_ADDITIONS::operator=(itemdata);

   //      return *this;

   //   }


   //   //item_data & operator = (const ::matter & particle) { id() = particle.id(); return *this; }


   //   //item_data & operator = (const item_base & itembase) { item_base::operator=(itembase); return *this; }


   //   //item_data & operator = (const ITEM_DATA & itemdata)
   //   //{

   //   //   item_base::operator=(itemdata);

   //   //   ITEM_DATA_ADDITIONS::operator=(itemdata);

   //   //   return *this;

   //   //}


   //};

   ////
   ////namespace geometry2d
   ////{
   ////
   ////   class region;
   ////
   ////} // namespace geometry2d
   ////

   class CLASS_DECL_ACME item :
      virtual public ::particle
  //    virtual public ::user::ITEM
   {
   public:


      //item(enum_element eelement, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const huge_natural uFlags = e_flag_none) :
      //   item(eelement, iItem, iSubItem, iListItem, uFlags) {}

      //item(const ::user::e_flag & eflag, enum_element eelement, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const ::atom & atom = ::atom::e_type_null) :
      //   item(eelement, iItem, iSubItem, iListItem, atom, eflag) {}

      //item(enum_element eelement, const ::atom & atom)
      //   : item(eelement, -1, -1, -1, atom)
      //{

      //}

      //union // small 1 bedroom ap
      //{
      //   void * m_data[4];
      //   struct // this part is structured?!?!?! (hipocritical but ok..)
      //   {
      //      // they are hipo, so... they think they are aligned...
      //      ::user::tool_item * m_ptoolitem;
      //      // journalists inventing science that scientists get surprised when we mention to them, you know... - like global warming and ozone layer - so important as these comments... "so a kid is smarter than scientists..." - by lol, what a genius, right?!
      //      // universities, media, police, justice, religion and politics, and lately also javascript and invented artificial programming languages, to ensure you give money to professors, journalists and artists, cops and lawyers, juddge, priests and suits, imposed by entertainement, guns, contracts, existence and cheering for a team you just choose. For having few food and fun, you have to give these impostors a lot of money, otherwise instead of movies, they make covid and they work together with universities, media, police, justice and polictis, and religious people obbey laws... ans so on..
      //      // wait for the next... they have nothing to do and a lot of time in between to be creative, you know...
      //      // journalists could teach to cook... and... universities to build... police muscles for night club entertenament... justice for history... policits for some directions and religion for interpreting the universe... because there are billions of galaxies... because sci-fi is not science, it is a religion of pretending to be better than rich people by knowning some physics... and rich people turn rich on flesh but they are later invited to trampolin to finance the circus above on the shoulders of slaves with some controlled youtube and macdonalds and starbucks...
      //   };
      //};



      // a user item is a "pointer"/address to a user interface matter

      //::pointer<::draw2d::graphics>     m_pgraphics;
      //::pointer<::geometry2d::region>     m_pregion;
      ::pointer<::draw2d::path>     m_ppath;
      ::pointer<::user::mouse>      m_pmouse;
      //bool                             m_bAnyHoverChange;

      
      ::item_pointer                m_pitem;
      //::int_point                   m_pointScreen;
      ::int_point                   m_pointHost;
      ::int_point                   m_pointClient;
      ::int_point                   m_pointHitTest;
      ::int_rectangle               m_rectangle2;
      ::user::e_item                m_eitem;
      ::particle_pointer      m_pparticle;
      ::user::e_zorder              m_ezorder;
      ::user::e_item_flag           m_euseritemflag;


      item(::item * pitem = nullptr) :
         m_pitem(pitem)
      {

         m_ezorder = ::user::e_zorder_front;

      }


      ~item()
      {


      }


      item & operator = (const item & item)
      {

         //m_pointScreen = item.m_pointScreen;
         m_pointHost = item.m_pointHost;
         m_pointClient = item.m_pointClient;
         m_pointHitTest = item.m_pointHitTest;
         m_rectangle2 = item.m_rectangle2;
         //m_uFlags = itemdataadditions.m_uFlags;
         m_pparticle = item.m_pparticle;
         m_ppath = item.m_ppath;

         return *this;

      }


      //inline ::user::tool_item * tool_item() { return ::is_set(m_pitem) && m_pitem->m_eitem == e_item_tool ? m_ptoolitem : nullptr; }
      //inline ::user::tool_item * tool_item() const { return ((::user::item *)this)->tool_item(); }

      bool is_drawn() { return m_euseritemflag & e_item_flag_drawn; }

      void set_drawn() { m_euseritemflag |= e_item_flag_drawn; }


      //item(::item * pitem = nullptr) :
      //   ITEM(pitem)
      //{

      //}


      //item(enum_element eelement, const enum_id & id)
      //   : item(eelement, -1, -1, -1, id)
      //{

      //}

     /* item(enum_element eelement = ::e_element_none, ::collection::index iItem = -1, ::collection::index iSubItem = -1, ::collection::index iListItem = -1, const ::atom & atom = ::atom::e_type_null, const ::user::e_flag uFlags = ::user::e_flag_none)
      {

         id() = atom;

         m_eelement = eelement;

         m_eitem = e_item_normal;

         m_iItem = iItem >= 0 ? iItem : m_eelement != ::e_element_none ? 0 : iItem;

         m_iSubItem = iSubItem;

         m_iListItem = iListItem;

         m_uFlags = uFlags;

      }*/

      /*item(::collection::index iItem)
      {

         m_eelement = ::e_element_none;

         m_eitem = e_item_normal;

         m_iItem = -1;

         m_iSubItem = -1;

         m_iListItem = -1;

         m_uFlags = 0;

         operator = (iItem);

      }*/


      //item(const item & item) :
      //   PARTICLE(item),
      //   particle(item),
      //   m_pitem(item.m_pitem),
      //   //item_base(item),
      //   //ITEM_DATA_ADDITIONS(item),
      //   //item_data(item),
      //   //matter(item)
      //{

      //}


      //item(item && item) :
      //   PARTICLE(::transfer(item)),
      //   particle(::transfer(item)),
      //   ITEM_BASE_ADDITIONS(::transfer(item)),
      //   item_base(::transfer(item)),
      //   ITEM_DATA_ADDITIONS(::transfer(item)),
      //   item_data(::transfer(item)),
      //   matter(::transfer(item))
      //{

      //}


      //bool is_drawn() { return m_uFlags & ITEM_DRAWN; }

      //void set_drawn() { m_uFlags |= ITEM_DRAWN; }

      

      bool is_item_set() const { return ::is_item_set(m_pitem); }

      explicit operator bool() const { return is_item_set(); }

      enum_element eelement() const { return is_item_set() ? m_pitem->m_item.m_eelement : e_element_none; }

      ::collection::index item_index() const { return is_item_set() ? m_pitem->m_item.m_iItem : -1; }

      template < typename ITEM >
      ::pointer < ITEM > as_item() const { return ((::user::item *)this)->as_item< ITEM >(); }

      template < typename ITEM >
      ::pointer < ITEM > as_item() { return m_pitem.cast < ITEM >(); }


      ::atom atom() const { return is_item_set() ? m_pitem->m_atomMatterId : e_element_none; }

      //template < primitive_integral INTEGRAL >
      //operator INTEGRAL() const { return (INTEGRAL)m_iItem; }

      //bool is_hidden() const;

      //::string get_text(::collection::index iSubItem);


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
      //using item_data::operator!=;


      //item & operator = (const item & item)
      //{

      //   ITEM::operator=(item);

      //   //m_pgraphics = item.m_pgraphics;


      //   return *this;

      //}


      //bool operator == (const item & item) const { return ITEM::operator ==(item); }
      //bool operator != (const item & item) const { return !operator==(item); }


      //item & operator = (enum_element eelement);

      bool operator == (enum_element eelement)  const { return this->eelement() == e_element_none ? false : this->eelement() == eelement; }
      //bool operator != (enum_element eelement)  const { return !operator==(eelement); }

      /*item & operator = (const e_element & eelement) { return operator = ((enum_element)eelement); }

      bool operator == (const e_element & eelement)  const { return m_eelement == eelement; }
      bool operator != (const e_element & eelement)  const { return !operator==(eelement); }*/

      //item & operator = (::collection::index iItem);

      //bool operator == (::collection::index iItem)  const { return m_iItem == iItem; }
      //bool operator != (::collection::index iItem)  const { return m_iItem != iItem; }

      //bool operator <= (::collection::index iItem)  const { return m_iItem <= iItem; }
      //bool operator >= (::collection::index iItem)  const { return m_iItem >= iItem; }

      //bool operator < (::collection::index iItem)  const { return m_iItem < iItem; }
      //bool operator > (::collection::index iItem)  const { return m_iItem > iItem; }

      //::collection::index operator + (int iItemAdd) { return (::collection::index)(m_iItem + iItemAdd); }
      //::collection::index operator - (int iItemSub) { return (::collection::index)(m_iItem - iItemSub); }

      //::collection::index operator + (huge_integer iItemAdd) { return (::collection::index)(m_iItem + iItemAdd); }
      //::collection::index operator - (huge_integer iItemSub) { return (::collection::index)(m_iItem - iItemSub); }


      /*bool in_element_range(enum_element eelement, int iCount) const { return m_eelement >= eelement && m_eelement < eelement + iCount; }

      bool is_valid_item(::collection::count c) const { return m_iItem >= 0 && m_iItem < c; }*/



      //inline ::user::tool_item * tool_item() { return m_eitem == e_item_tool ? m_ptoolitem : nullptr; }
      //inline ::user::tool_item * tool_item() const { return ((::item *)this)->tool_item(); }


   };

   using item_pointer = ::pointer < item >;

   //using item_pointer = ::pointer < ::user::item >;
   using item_array = ::pointer_array < item >;

   using item_map = map < item_t, item_pointer >;

} // namespace user


inline bool is_item_set(const ::user::item * puseritem)
{

   return ::is_set((const void *)puseritem) && puseritem->is_item_set();

}


inline bool is_element(const ::user::item * puseritem, ::enum_element eelement)
{

   return ::is_item_set(puseritem) && puseritem->eelement() == eelement;

}


inline bool is_item(const ::user::item * puseritem, ::collection::index iItem)
{

   return ::is_item_set(puseritem) &&  puseritem->item_index() == iItem;

}



inline bool is_item_index(const ::user::item * pitem, ::collection::index iItem)
{

   return ::is_element(pitem, ::e_element_item) && ::is_item(pitem, iItem);

}


inline bool is_same_item(const ::user::item * pitem1, const ::user::item * pitem2)
{

   if (::is_item_set(pitem1))
   {

      if (::is_item_set(pitem2))
      {

         return ::is_same_item(pitem1->m_pitem, pitem2->m_pitem);

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


CLASS_DECL_ACME bool is_item_equivalent(const ::user::item * pitem1, const ::user::item * pitem2);


inline ::collection::index item_index(const ::user::item * puseritem)
{

   return ::is_item_set(puseritem) ? puseritem->item_index() : -1;

}



