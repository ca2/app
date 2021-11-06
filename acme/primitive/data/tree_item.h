#pragma once


class image_list;


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

   if (plist->m_phead == pitemA)
   {

      plist->m_phead = pitemB;

   }
   else if (plist->m_phead == pitemB)
   {

      plist->m_phead = pitemA;

   }

   if (plist->m_ptail == pitemA)
   {

      plist->m_ptail = pitemB;

   }
   else if (plist->m_ptail == pitemB)
   {

      plist->m_ptail = pitemA;

   }

   auto pitem = pitemA->m_pprevious;

   if (pitem == pitemB)
   {

      // b was immediatelly before a

      // now, make b imediatelly after a

      pitemB->m_pnext = pitemA->m_pnext;

      pitemA->m_pprevious = pitemB->m_pprevious;

      pitemB->m_pprevious = pitemA;

      pitemA->m_pnext = pitemB;

   }
   else
   {

      pitemA->m_pprevious = pitemB->m_pprevious;

      pitemB->m_pprevious = pitem;

      pitem = pitemA->m_pnext;

      if (pitem == pitemB)
      {

         // b was immediatelly after a

         // now, make a imediatelly before a

         pitemB->m_pnext = pitemA->m_pnext;

         pitemA->m_pprevious = pitemB->m_pprevious;

         pitemB->m_pprevious = pitemA;

         pitemA->m_pnext = pitemB;

      }
      else
      {

         pitemA->m_ppnext = pitemB->m_ppnext;

         pitemB->m_ppnext = pitem;

      }

   }


}


template < typename LIST_ITEM, typename PRED >
void list_sort(LIST_ITEM* pitem, PRED pred)
{

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
      iMPos = iLowerBound;
      iUPos = iUpperBound;
      while (true)
      {
         while (true)
         {
            if (iMPos == iUPos)
               goto break_mid_loop;
            if (pred(iUPos->m_value, iMPos->m_value))
            {
               list_swap(pitem, iMPos, iUPos);
               break;
            }
            iUPos = iUPos->m_pprevious;
         }
         iMPos = iUPos;
         while (true)
         {
            if (iMPos == iLPos)
               goto break_mid_loop;
            if (pred(iMPos->m_value, iLPos->m_value))
            {
               list_swap(pitem, iLPos, iMPos);
               break;
            }
            iLPos = iLPos->m_pnext;
         }
         iMPos = iLPos;
      }
   break_mid_loop:
      if (iLowerBound != iMPos->m_pprevious)
      {
         stackLowerBound.push(iLowerBound);
         stackUpperBound.push(iMPos->m_pprevious);
      }
      if (iMPos->m_pnext != iUpperBound)
      {
         stackLowerBound.push(iMPos->m_pnext);
         stackUpperBound.push(iUpperBound);
      }
      if (stackLowerBound.get_size() == 0)
         break;
   }

}


namespace data
{


   class tree_item_ptr_array;
   class tree;


   enum ERelative
   {
      RelativeParent,
      RelativeFirstChild,
      RelativeLastChild,
      RelativeFirstSibling,
      RelativePreviousSibling,
      RelativeNextSibling,
      RelativeLastSibling,
      RelativeReplace,
      RelativeMacroRecord
   };


   enum ETreeNavigation
   {
      TreeNavigationExpandedForward,
      TreeNavigationProperForward,
   };


   enum e_tree_item_state
   {
      tree_item_state_expandable = 1,
      tree_item_state_expanded   = 2,
      tree_item_state_selected   = 4,
   };


   class CLASS_DECL_ACME tree_item :
      virtual public matter
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

      __pointer(tree_item)             m_phead; // first child
      __pointer(tree_item)             m_ptail; // last child
      __pointer(tree_item)             m_pprevious;
      __pointer(tree_item)             m_pnext;
      __pointer(tree_item)             m_pparent;
      index                            m_iIndexHint;
      tree *                           m_ptree;
      index                            m_iLevel;
      __pointer(::data::item)          m_pdataitem;
      uptr                             m_dwUser;
      u32                              m_dwState;
      uptr                             m_dwMetaData;


      tree_item();
      virtual ~tree_item();


      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {

         return ::matter::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
      {

         return ::matter::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

      virtual bool      erase_item_from_parent();

      tree_item * get_child_by_user_data(uptr iUserData);
      tree_item * find_next_by_user_data(uptr iUserData);
      void get_children(::data::tree_item_ptr_array &ptra);
      ::count get_children_count();
      tree_item * get_parent();
      ::count get_expandable_children_count();
      ::count get_proper_descendant_count();
      tree_item * get_expandable_child(index iIndex);

      bool insert(ERelative erelative, ::data::tree_item * pitemNew);

      index calc_level();
      index get_level() { return m_iLevel >= 0 ? m_iLevel : calc_level(); }
      index _get_index();


      tree_item * get_previous_or_parent(index * iLevelOffset = nullptr);
      tree_item * get_previous();


      tree_item * get_next();
      tree_item * get_next_or_parent_next(index * iLevelOffset = nullptr);
      tree_item * get_child_or_next(index * iLevelOffset = nullptr);
      tree_item * get_child_next_or_parent(index * iLevelOffset = nullptr);


      inline const tree_item * get_child_next_or_parent(index * iLevelOffset = nullptr) const
      {

         return ((tree_item*)(this))->get_child_next_or_parent(iLevelOffset);

      }

      //tree_item * calc_previous(bool bParent = true);

      //tree_item * calc_next(bool bChild, bool bParent = true, index * pindexLevel = nullptr);

      tree_item * first_child();

      // [](const ::data::tree_item * pitem1, const ::data::tree_item * pitem2)
      template < typename PRED >
      void sort_children(PRED pred)
      {

         list_sort(this, pred);

      }



      inline tree_item * get_proper_next(index* pindexLevel = nullptr)
      {

         if ((m_dwState & ::data::tree_item_state_expanded))
         {

            return get_child_next_or_parent(pindexLevel);

         }
         else
         {

            return get_next_or_parent_next(pindexLevel);

         }

      }

      tree_item * get_item(ETreeNavigation enavigation, index * piLevelOffset = nullptr);
      tree_item * get_item(ERelative erelative);

      virtual tree_item * get_proper_item(index iIndex, index * piLevel);
      virtual index get_proper_item_index(tree_item * pitem, index * piLevel);
      virtual ::count get_proper_item_count();

      virtual tree * get_tree();

      virtual string get_text() const;
      virtual index get_image() const;
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


   class CLASS_DECL_ACME tree_item_ptr_array :
      public __pointer_array(tree_item)
   {
   public:
   };


} // namespace acme


