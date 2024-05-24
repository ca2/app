#pragma once


//#include "acid/primitive/collection/pointer_array.h"


class image_list;


template < typename LIST_ITEM >
bool list_item_is_before(const LIST_ITEM * pitem1, const LIST_ITEM * pitem2)
{

   if (::is_null(pitem2))
   {

      return false;

   }

   if (pitem1 == pitem2)
   {

      return false;

   }

   while (::is_set(pitem1))
   {

      if (pitem1->m_pnext == pitem2)
      {

         return true;

      }

      pitem1 = pitem1->m_pnext;

   }

   return false;

}


template < typename LIST_ITEM >
const LIST_ITEM * list_item_calculate_head(const LIST_ITEM * pitem)
{

   if (::is_null(pitem))
   {

      return nullptr;

   }

   while(true)
   {

      if (::is_null(pitem->m_pprevious))
      {

         return pitem;

      }

      pitem = pitem->m_pprevious;

   }

}


template < typename LIST_ITEM >
const LIST_ITEM * list_item_calculate_tail(const LIST_ITEM * pitem)
{

   if (::is_null(pitem))
   {

      return nullptr;

   }

   while (true)
   {

      if (::is_null(pitem->m_pnext))
      {

         return pitem;

      }

      pitem = pitem->m_pnext;

   }

}


template < typename LIST_ITEM, typename ARRAY >
void list_set_children(LIST_ITEM* plist, const ARRAY& a)
{

   list_erase_all(plist);

   if (a.is_empty())
   {

      return;

   }

   plist->m_phead = a.first();

   plist->m_ptail = a.last();

   LIST_ITEM* pprevious = nullptr;

   for (auto& p : a)
   {

      if (pprevious)
      {

         pprevious->m_pnext = p;

      }

      p->m_pprevious = pprevious;

      pprevious = p;

   }

   if (pprevious)
   {

      pprevious->m_pnext = nullptr;

   }

}

template < typename LIST_ITEM >
void list_swap(LIST_ITEM* plist, LIST_ITEM* pitemA, LIST_ITEM* pitemB)
{

   auto pitemAPrevious = pitemA->m_pprevious;

   auto pitemANext = pitemA->m_pnext;

   auto pitemBPrevious = pitemB->m_pprevious;

   auto pitemBNext = pitemB->m_pnext;

   if (pitemAPrevious == pitemB)
   {

      if (pitemB->m_pnext != pitemA)
      {

         throw "error";

      }

      pitemANext->m_pprevious = pitemB;

      pitemBPrevious->m_pnext = pitemA;

      pitemA->m_pprevious = pitemB->m_pprevious;

      pitemB->m_pnext = pitemA->m_pnext;

      pitemA->m_pnext = pitemB;

      pitemB->m_pprevious = pitemA;

   }
   else if (pitemANext == pitemB)
   {

      if (pitemB->m_pprevious != pitemA)
      {

         throw "error";

      }

      pitemAPrevious->m_pnext = pitemB;

      pitemBNext->m_pprevious = pitemA;

      pitemA->m_pnext = pitemB->m_pnext;

      pitemB->m_pprevious = pitemA->m_pprevious;

      pitemA->m_pprevious = pitemB;

      pitemB->m_pnext = pitemA;

   }
   else
   {

      pitemA->m_pprevious = pitemBPrevious;

      pitemA->m_pnext = pitemBNext;

      pitemB->m_pprevious = pitemAPrevious;

      pitemB->m_pnext = pitemANext;

      if (::is_set(pitemAPrevious))
      {

         pitemAPrevious->m_pnext = pitemB;

      }

      if (::is_set(pitemANext))
      {

         pitemANext->m_pprevious = pitemB;

      }

      if (::is_set(pitemBPrevious))
      {

         pitemBPrevious->m_pnext = pitemA;

      }

      if (::is_set(pitemBNext))
      {

         pitemBNext->m_pprevious = pitemA;

      }

   }

}



template < typename LIST_ITEM, typename PRED >
void list_sort(LIST_ITEM* pitem, PRED pred)
{

   if (::is_null(pitem->m_phead) || ::is_null(pitem->m_ptail))
   {

      return;

   }

   ::raw_array < LIST_ITEM* > stackLowerBound;
   ::raw_array < LIST_ITEM* > stackUpperBound;

   LIST_ITEM* iLowerBound;
   LIST_ITEM* iUpperBound;
   LIST_ITEM* iLPos, * iUPos, * iMPos;

   stackLowerBound.push(pitem->m_phead);
   stackUpperBound.push(pitem->m_ptail);
   while (true)
   {
      iLowerBound = stackLowerBound.pop();
      iUpperBound = stackUpperBound.pop();
      iLPos = iLowerBound;
      iUPos = iUpperBound;
      auto p1 = iLPos;
      auto p2 = iUPos;
      iMPos = p1;
      while (p1 != p2)
      {
         p2 = p2->m_pprevious;
         if (p1 == p2)
         {
            iMPos = p1;
            break;
         }
         p1 = p1->m_pnext;
         if (p1 == p2)
         {
            iMPos = p1;
            break;
         }
      }
      while (true)
      {
         while (true)
         {
            if (iMPos == iUPos)
               break;
            if (pred(iMPos, iUPos))
            {
               iUPos = iUPos->m_pprevious;
            }
            else
            {
               list_swap(pitem, iMPos, iUPos);
               break;
            }
         }
         if (iMPos == iUPos)
            break;
         iMPos = iUPos;
         while (true)
         {
            if (iMPos == iLPos)
               break;
            if (pred(iLPos, iMPos))
            {
               iLPos = iLPos->m_pnext;
            }
            else
            {
               list_swap(pitem, iLPos, iMPos);
               break;
            }
         }
         if (iMPos == iLPos)
            break;
         iMPos = iLPos;
      }
      if (list_item_is_before(iLowerBound, (const LIST_ITEM *) iMPos->m_pprevious))
      {
         stackLowerBound.push(iLowerBound);
         stackUpperBound.push(iMPos->m_pprevious);
      }
      if (list_item_is_before((const LIST_ITEM *)iMPos->m_pnext, iUpperBound))
      {
         stackLowerBound.push(iMPos->m_pnext);
         stackUpperBound.push(iUpperBound);
      }
      if (stackLowerBound.get_size() == 0)
         break;
   }
   pitem->m_phead = list_item_calculate_head((const LIST_ITEM *)pitem->m_phead);
   pitem->m_ptail = list_item_calculate_tail((const LIST_ITEM *)pitem->m_ptail);
}


namespace data
{


   class tree_item_ptr_array;
   class tree;



   class CLASS_DECL_ACID tree_item :
      virtual public particle
   {
   public:


      enum enum_flag
      {

         flag_previous_or_parent = 1,
         flag_previous = 2,
         flag_next = 4,
         flag_next_or_parent = 8,
         flag_child_or_next = 16,
         flag_child_next_or_parent = 32,
         flag_previoub = flag_previous_or_parent | flag_previous,
         flag_nexts = flag_next | flag_next_or_parent | flag_child_or_next| flag_child_next_or_parent,

      };

      //::pointer<tree_item>             m_phead; // first child
      //::pointer<tree_item>             m_ptail; // last child
      //::pointer<tree_item>             m_pprevious;
      //::pointer<tree_item>             m_pnext;
      ::pointer_array < tree_item >    m_treeitema;
      ::pointer<tree_item>             m_pparent;
      ::collection::index                            m_iIndexHint;
      tree *                           m_ptree;
      ::collection::index                            m_iLevel;
      ::pointer<::data::item>          m_pdataitem;
      uptr                             m_dwUser;
      u32                              m_dwState;
      uptr                             m_dwMetaData;


      tree_item();
      ~tree_item() override;


      #ifdef _DEBUG


      virtual i64 increment_reference_count() override
      {

         return ::particle::increment_reference_count();

      }

      virtual i64 decrement_reference_count() override
      {

         return ::particle::decrement_reference_count();

      }


      #endif


      virtual bool      erase_item_from_parent();

      tree_item * get_child_by_user_data(uptr iUserData);
      tree_item * find_next_by_user_data(uptr iUserData);
      void get_children(::data::tree_item_ptr_array &ptra);
      ::collection::count get_children_count();
      tree_item * get_parent();
      ::collection::count get_expandable_children_count();
      ::collection::count get_proper_descendant_count();
      tree_item * get_expandable_child(::collection::index iIndex);

      bool insert(enum_relative erelative, ::data::tree_item * pitemNew);

      ::collection::index calc_level();
      ::collection::index get_level() { return m_iLevel >= 0 ? m_iLevel : calc_level(); }
      ::collection::index _get_index();


      virtual ::data::tree_item * ____previous();
      virtual ::data::tree_item * ____next();
      virtual ::data::tree_item * ____head();
      virtual ::data::tree_item * ____tail();


      tree_item * get_previous_or_parent(::collection::index * iLevelOffset = nullptr);
      tree_item * get_previous();


      tree_item * get_next();
      tree_item * get_next_or_parent_next(::collection::index * iLevelOffset = nullptr);
      tree_item * get_child_or_next(::collection::index * iLevelOffset = nullptr);
      tree_item * get_child_next_or_parent(::collection::index * iLevelOffset = nullptr);


      inline const tree_item * get_child_next_or_parent(::collection::index * iLevelOffset = nullptr) const
      {

         return ((tree_item*)(this))->get_child_next_or_parent(iLevelOffset);

      }

      //tree_item * calc_previous(bool bParent = true);

      //tree_item * calc_next(bool bChild, bool bParent = true, ::collection::index * pindexLevel = nullptr);

      tree_item * first_child();

      // [](const ::data::tree_item * pitem1, const ::data::tree_item * pitem2)
      virtual void sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess);



      inline tree_item * get_proper_next(::collection::index * pindexLevel = nullptr)
      {

         if ((m_dwState & ::data::e_tree_item_state_expanded))
         {

            return get_child_next_or_parent(pindexLevel);

         }
         else
         {

            return get_next_or_parent_next(pindexLevel);

         }

      }

      tree_item * get_item(enum_tree_navigation enavigation, ::collection::index * piLevelOffset = nullptr);
      tree_item * get_item(enum_relative erelative);

      virtual bool contains(const tree_item * ptreeitem);
      virtual tree_item * get_proper_item(::collection::index iIndex, ::collection::index * piLevel);
      virtual ::collection::index get_proper_item_index(tree_item * pitem, ::collection::index * piLevel);
      virtual ::collection::count get_proper_item_count();

      virtual tree * get_tree();

      virtual string get_text() const;
      virtual ::collection::index get_image() const;
      virtual ::image_list * get_image_list() const;


      void set_parent(tree_item * pparent);

      void erase_tree_item();
      void erase_tree_item_descendants();


      virtual bool is_expanded() const;
      virtual bool is_expandable() const;

      virtual void on_fill_children();

      virtual bool is_descendant(tree_item * pitem);
      virtual bool is_ascendant(tree_item * pitem);


   };


   class CLASS_DECL_ACID tree_item_ptr_array :
      public pointer_array < tree_item >
   {
   public:
   };


} // namespace acid


