#pragma once


#include "acme/prototype/data/item.h"
#include "acme/prototype/data/tree_item_base.h"

template < typename DATA_ITEM >
concept primitive_data_item = ::std::is_base_of_v < ::data::item, DATA_ITEM >;



namespace data
{


   template < primitive_data_item DATA_ITEM >
   class tree_item;

   template < primitive_data_item DATA_ITEM >
   class tree_item_ptr_array;

   template < primitive_data_item DATA_ITEM >
   class tree;


} // namespace data


namespace data
{


   template < primitive_data_item DATA_ITEM >
   class tree_item :
      virtual public tree_item_base
   {
   protected:


      //bool                             m_bPrevious = false;
      //bool                             m_bNext = false;

      ::pointer<tree_item>             m_pprevious2;
      ::pointer<tree_item>             m_pnext2;
      ::pointer_array < tree_item >    m_treeitema2;
      //::collection::index              m_iIndex = -2;

   public:


      //enum enum_flag
      //{

      //   flag_previous_or_parent = 1,
      //   flag_previous = 2,
      //   flag_next = 4,
      //   flag_next_or_parent = 8,
      //   flag_child_or_next = 16,
      //   flag_child_next_or_parent = 32,
      //   flag_previoub = flag_previous_or_parent | flag_previous,
      //   flag_nexts = flag_next | flag_next_or_parent | flag_child_or_next| flag_child_next_or_parent,

      //};

      //::pointer<tree_item>             m_phead; // first child
      //::pointer<tree_item>             m_ptail; // last child
      ::pointer < tree_item >          m_pparent;
      //::collection::index              m_iIndexHint;
      tree < DATA_ITEM > *             m_ptree;
      //::collection::index              m_iLevel;
      ::pointer < DATA_ITEM >          m_pdataitem;
      //uptr                             m_dwUser;
      //unsigned int                     m_dwState;
      //uptr                             m_dwMetaData;


      tree_item();
      ~tree_item() override;


      #ifdef _DEBUG


      virtual long long increment_reference_count() override
      {

         return ::particle::increment_reference_count();

      }

      virtual long long decrement_reference_count() override
      {

         return ::particle::decrement_reference_count();

      }


      #endif
      void clear_cache() override;
      void destroy() override;
      bool erase_item_from_parent() override;

      tree_base * _get_tree() const override;
      void _set_tree(tree_base * ptree) override;


      tree_item * get_child_by_user_data(uptr iUserData);
      tree_item * find_next_by_user_data(uptr iUserData);
      void get_children(::data::tree_item_ptr_array < DATA_ITEM > &ptra);
      ::collection::count get_children_count() override;
      tree_item * get_parent();
      ::collection::count get_expandable_children_count() override;
      ::collection::count get_proper_descendant_count() override;
      virtual tree_item * get_expandable_child(::collection::index iIndex);

      bool insert(enum_relative erelative, tree_item * pitemNew);

      ::collection::index calc_level() override;
      ::collection::index get_level() override { return m_iLevel >= 0 ? m_iLevel : calc_level(); }
      ::collection::index _get_index() override;


      inline auto ____previous()
      {
         return m_bPrevious ? m_pprevious2.m_p : _____previous();
      }
      inline auto ____next()
      {
         return m_bNext ? m_pnext2.m_p : _____next();
      }
      inline auto ____head()
      {
         return m_treeitema2.is_empty() ? nullptr : m_treeitema2.first();
      }
      inline auto ____tail()
      {
         return m_treeitema2.is_empty() ? nullptr : m_treeitema2.last();
      }

      tree_item_base * _get_parent() override;


      virtual tree_item * _____previous();
      virtual tree_item * _____next();
      //virtual ::data::tree_item * _____head();
      //virtual ::data::tree_item * _____tail();



      tree_item_base * __previous() override { return ____previous(); }
      tree_item_base * __next() override { return ____next(); }
      tree_item_base * __head() override { return ____head(); }
      tree_item_base * __tail() override { return ____tail(); }


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
      virtual void sort_children(const ::function < bool(const tree_item * p1, const tree_item * p2) > & functionLess);



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

      virtual tree_item * get_item(enum_tree_navigation enavigation, ::collection::index * piLevelOffset = nullptr);
      virtual tree_item * get_item(enum_relative erelative);

      virtual bool contains(const tree_item * ptreeitem);
      virtual tree_item * get_proper_item(::collection::index iIndex, ::collection::index * piLevel);
      virtual ::collection::index get_proper_item_index(tree_item * pitem, ::collection::index * piLevel);
      ::collection::count get_proper_item_count() override;

      tree < DATA_ITEM > * get_tree();

      string get_text() const override;
      ::collection::index get_image() const override;
      ::image::image_list * get_image_list() const override;


      void set_parent(tree_item * pparent);

      void erase_tree_item() override;
      void erase_tree_item_descendants() override;
      void erase_child(tree_item * ptreeitem);

      bool is_expanded() const override;
      bool is_expandable() const override;

      void on_fill_children() override;

      bool is_descendant(tree_item * pitem);
      bool is_ascendant(tree_item * pitem);
      ::data::item * _data_item() const override;
      ::collection::index _find_child(tree_item_base * ptreeitem) const override
      {
         return m_treeitema2.find_first(dynamic_cast < tree_item <DATA_ITEM >*>(ptreeitem));
      }
      tree_item_base * _child_at(::collection::index i) const override
      {
         return m_treeitema2[i];
      }
      void _erase_child_at(::collection::index i) override
      {
         m_treeitema2.erase_at(i);
      }

      void _insert_child_at(::collection::index i, tree_item_base * ptreeitemNew) override
      {
         m_treeitema2.insert_at(i, dynamic_cast < tree_item < DATA_ITEM > *> (ptreeitemNew));
      }
      void _add_child(tree_item_base * ptreeitemNew) override
      {
         m_treeitema2.add_item(ptreeitemNew);
      }
      void _set_child_at(::collection::index i, tree_item_base * ptreeitemSet) override
      {
         m_treeitema2[i] = ptreeitemSet;
      }

      void _erase_children() override
      {
         m_treeitema2.clear();

      }


   };



   template < primitive_data_item DATA_ITEM > tree_item < DATA_ITEM >::tree_item()
   {

      m_iIndexHint = -1;
      m_dwUser = 0;
      m_dwState = 0;
      m_ptree = nullptr;
      m_pparent = nullptr;
      m_iLevel = -1;
      m_pparent = nullptr;

   }


   template < primitive_data_item DATA_ITEM > tree_item < DATA_ITEM >::~tree_item()
   {

   }


    template < primitive_data_item DATA_ITEM > 
    tree <DATA_ITEM> * tree_item < DATA_ITEM >::get_tree()
   {

      return m_ptree;

   }


   template < primitive_data_item DATA_ITEM >
   void tree_item < DATA_ITEM >::set_parent(tree_item * pparent)
   {

      //if(m_pparent == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
      if (m_pparent == pparent || pparent == this || is_descendant(pparent))
      {

         return;

      }

      if (::is_set(pparent))
      {

         pparent->m_treeitema2.add_unique(this);

      }

      m_pparent->m_treeitema2.erase(this);

      m_pparent = pparent;

      for (auto pitem : m_pparent->m_treeitema2)
      {

         pitem->clear_cache();

      }

   }


   template < primitive_data_item DATA_ITEM >
   void tree_item < DATA_ITEM >::erase_tree_item()
   {

      erase_tree_item_descendants();

      if (m_pparent)
      {

         m_pparent->erase_child(this);

      }

   }


   template < primitive_data_item DATA_ITEM > 
   void tree_item < DATA_ITEM >::erase_child(tree_item * ptreeitem)
   {

      auto iIndex = m_treeitema2.find_first(ptreeitem);

      if (iIndex < 0)
      {

         return;

      }

      m_treeitema2.erase_at(iIndex);

      for (auto pitem : m_treeitema2)
      {

         pitem->clear_cache();

      }

   }


   template < primitive_data_item DATA_ITEM > 
   void tree_item < DATA_ITEM >::erase_tree_item_descendants()
   {

      for (auto & p : m_treeitema2)
      {

         p->erase_tree_item_descendants();

         p->clear_cache();

      }

      //list_predicate(this, [](auto p) { p->erase_tree_item(); });

      //list_erase_all(this);

      m_treeitema2.clear();

      clear_cache();

   }


   template < primitive_data_item DATA_ITEM >
   tree_item <DATA_ITEM> * tree_item < DATA_ITEM >::find_next_by_user_data(uptr iUserData)
   {

      auto ptreeitem = this;

      while (true)
      {

         ptreeitem = ptreeitem->get_item(e_tree_navigation_expanded_forward);

         if (!ptreeitem)
         {

            return nullptr;

         }

         if (ptreeitem->m_dwUser == (unsigned int)iUserData)
         {

            return ptreeitem;

         }

      }

   }


   template < primitive_data_item DATA_ITEM > 
   void tree_item < DATA_ITEM >::clear_cache()
   {

      m_bPrevious = false;
      m_bNext = false;
      m_iIndex = -2;

   }


   template < primitive_data_item DATA_ITEM > 
   void tree_item < DATA_ITEM >::destroy()
   {

      m_pparent.release();

      m_treeitema2.destroy();

      m_ptree = nullptr;

   }

   
   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::erase_item_from_parent()
   {

      tree_item * pitem = this;

      if (pitem->m_pparent == nullptr)
      {

         return true;

      }

      if (!pitem->m_pparent->m_treeitema2.contains(pitem))
      {

         // self healing?
         pitem->m_pparent = nullptr;

         return false;

      }

      pitem->m_pparent->m_treeitema2.erase(pitem);

      for (auto p : pitem->m_pparent->m_treeitema2)
      {

         p->clear_cache();

      }
      pitem->m_pparent = nullptr;

      return true;

   }


   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::contains(const tree_item * ptreeitem)
   {

      if (ptreeitem == this)
      {

         return true;

      }

      for (auto & p : m_treeitema2)
      {

         if (p->contains(ptreeitem))
         {

            return true;

         }

      }

      return false;

   }


   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::insert(enum_relative erelative, tree_item * pitemNew)
   {

      if (contains(pitemNew))
      {

         throw ::exception(error_wrong_state);

      }

      if (erelative == e_relative_first_child)
      {

         pitemNew->erase_item_from_parent();

         m_treeitema2.insert_at(0, pitemNew);

         for (auto & pitem : m_treeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == e_relative_last_child)
      {

         pitemNew->erase_item_from_parent();

         m_treeitema2.add(pitemNew);

         for (auto & pitem : m_treeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == e_relative_previous_sibling)
      {

         ASSERT(m_pparent != nullptr);

         if (m_pparent == nullptr)
         {

            return false;

         }

         auto iFind = m_pparent->m_treeitema2.find_first(this);

         if (iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema2.insert_at(iFind, pitemNew);

         for (auto & pitem : m_pparent->m_treeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if (erelative == e_relative_next_sibling)
      {

         if (m_pparent == nullptr)
         {

            return false;

         }

         auto iFind = m_pparent->m_treeitema2.find_first(this);

         if (iFind < 0)
         {

            // self-healing
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema2.insert_at(iFind + 1, pitemNew);

         for (auto & pitem : m_pparent->m_treeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if (erelative == e_relative_last_sibling)
      {

         m_pparent->m_treeitema2.add(pitemNew);

         for (auto & pitem : m_pparent->m_treeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if (erelative == e_relative_replace)
      {

         auto iFind = m_pparent->m_treeitema2.find_first(this);

         if (iFind < 0)
         {

            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema2[iFind] = pitemNew;

         for (auto & pitem : m_pparent->m_treeitema2)
         {

            pitem->clear_cache();

         }

         m_pparent = nullptr;

         erase_tree_item();

         return true;

      }

      return false;

   }


   template < primitive_data_item DATA_ITEM >
   void tree_item < DATA_ITEM >::sort_children(const ::function < bool(const tree_item * p1, const tree_item * p2) > & functionLess)
   {

      //data_tree_item_list_sort(this, functionLess);

      m_treeitema2.predicate_sort(functionLess);

      for (auto & pitem : m_treeitema2)
      {

         pitem->clear_cache();

      }


   }


   template < primitive_data_item DATA_ITEM > 
   tree_item <DATA_ITEM> * tree_item < DATA_ITEM >::get_child_by_user_data(uptr iUserData)
   {

      auto iFind = m_treeitema2.predicate_find_first([iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_treeitema2[iFind];

   }


   template < primitive_data_item DATA_ITEM >
   void tree_item < DATA_ITEM >::get_children(tree_item_ptr_array<DATA_ITEM> & ptra)
   {

      ptra.append(m_treeitema2);

   }


   template < primitive_data_item DATA_ITEM > 
   ::collection::count  tree_item < DATA_ITEM >::get_children_count()
   {

      return m_treeitema2.get_count();

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item < DATA_ITEM > * tree_item < DATA_ITEM >::get_parent()
   {

      return m_pparent;

   }


   template < primitive_data_item DATA_ITEM >
   ::collection::count tree_item < DATA_ITEM >::get_expandable_children_count()
   {

      ::collection::count c = 0;

      for (auto & p : m_treeitema2)
      {

         if (p->get_children_count() > 0)
         {

            c++;

         }

      }

      return c;

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item <DATA_ITEM>  * tree_item < DATA_ITEM >::get_expandable_child(::collection::index iIndex)
   {

      ::collection::count c = 0;

      auto iFind = m_treeitema2.predicate_find_first([&c, iIndex](auto & p)
         {

            if (p->get_children_count() > 0)
            {

               if (c == iIndex)
               {

                  return true;

               }

            }

            return false;

         });

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_treeitema2[iFind];

   }


   template < primitive_data_item DATA_ITEM > 
   ::collection::count tree_item < DATA_ITEM >::get_proper_descendant_count()
   {

      ::collection::count iCount = 0;

      ::collection::index iLevel = 0;

      tree_item * pitem = this;

      for (;;)
      {

         pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

         if (pitem == nullptr || iLevel <= 0)
         {

            break;

         }

         iCount++;

      }

      return iCount;

   }


   template < primitive_data_item DATA_ITEM > 
   inline tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_previous_or_parent(::collection::index * piLevel)
   {

      auto p = ____previous();

      if(p)
      {

         return p;

      }

      if (m_pparent)
      {

         return m_pparent;

         //if (piLevel)
         //{

         //   (*piLevel)--;

         //}

         //return m_pparent->get_previous_or_parent(piLevel);

      }

      return nullptr;

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_previous()
   {

      return ____previous();

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_next()
   {

      return ____next();

   }


   template < primitive_data_item DATA_ITEM > 
   ::collection::index tree_item < DATA_ITEM >::calc_level()
   {

      if (m_iLevel < 0)
      {

         m_iLevel = -1;

         tree_item * p = this;

         while (p != nullptr)
         {

            m_iLevel++;

            p = p->m_pparent;

         }

      }

      return m_iLevel;

   }



   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::_____previous()
   {

      m_bPrevious = true;

      if (::is_null(m_pparent))
      {

         m_pprevious2.release();

         return nullptr;

      }

      auto iFind = _get_index();

      if (iFind <= 0)
      {

         m_pprevious2.release();

         return nullptr;

      }

      return m_pprevious2 = m_pparent->m_treeitema2[iFind - 1];

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item <DATA_ITEM> * tree_item < DATA_ITEM >::_____next()
   {

      m_bNext = true;

      if (::is_null(m_pparent))
      {

         m_pnext2.release();

         return nullptr;

      }

      auto iFind = _get_index();

      if (iFind < 0 || iFind >= m_pparent->m_treeitema2.get_upper_bound())
      {

         m_pnext2.release();

         return nullptr;

      }

      return m_pnext2 = m_pparent->m_treeitema2[iFind + 1];

   }


   template < primitive_data_item DATA_ITEM >
   tree_item_base * tree_item < DATA_ITEM >::_get_parent()
   {

      return m_pparent;

   }


   //::data::tree_item * template < primitive_data_item DATA_ITEM > tree_item < DATA_ITEM >::____head()
   //{

   //   if (m_treeitema.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema.first();

   //}


   //::data::tree_item * template < primitive_data_item DATA_ITEM > tree_item < DATA_ITEM >::____tail()
   //{

   //   if (m_treeitema.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema.last();

   //}


   template < primitive_data_item DATA_ITEM > 
   ::collection::index tree_item < DATA_ITEM >::_get_index()
   {

      if (m_iIndex >= -1)
      {

         return m_iIndex;

      }

      if (m_pparent == nullptr)
      {

         m_iIndex = -1;

         return -1;

      }

      return m_iIndex = m_pparent->m_treeitema2.find_first(this);

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_next_or_parent_next(::collection::index * piLevel)
   {

      if (____next())
      {

         return ____next();

      }

      if (!m_pparent)
      {

         return nullptr;

      }

      if (piLevel)
      {

         (*piLevel)--;

      }

      return m_pparent->get_next_or_parent_next(piLevel);

   }


   template < primitive_data_item DATA_ITEM >
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_child_or_next(::collection::index * piLevel)
   {

      if (____head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return ____head();

      }

      return ____next();

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_child_next_or_parent(::collection::index * piLevel)
   {

      if (____head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return ____head();

      }

      return get_next_or_parent_next(piLevel);

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_item(enum_tree_navigation enavigation, ::collection::index * pindexLevel)
   {

      switch (enavigation)
      {
      case e_tree_navigation_expanded_forward:

         return get_child_next_or_parent(pindexLevel);

      case e_tree_navigation_proper_forward:

         return get_proper_next(pindexLevel);

      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }

   }


   template < primitive_data_item DATA_ITEM >
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_item(enum_relative erelative)
   {

      switch (erelative)
      {
      case e_relative_first_child:
      {
         return ____head();
      }
      break;
      case e_relative_last_child:
      {
         return ____tail();
      }
      case e_relative_parent:
      {
         return m_pparent;
      }
      break;
      case e_relative_first_sibling:
      {
         return m_pparent->____head();
      }
      break;
      case e_relative_previous_sibling:
      {
         return ____previous();
      }
      break;
      case e_relative_next_sibling:
      {
         return ____next();
      }
      break;
      case e_relative_last_sibling:
      {
         return m_pparent->____tail();
      }
      break;
      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }
   }



   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::first_child()
   {

      return ____head();

   }


   template < primitive_data_item DATA_ITEM >
   string tree_item < DATA_ITEM >::get_text() const
   {

      if (!m_pdataitem)
      {

         return "";

      }

      return m_pdataitem->data_item_get_text(m_ptree);

   }


   template < primitive_data_item DATA_ITEM > 
   ::collection::index tree_item < DATA_ITEM >::get_image() const
   {

      if (!m_pdataitem)
      {

         return -1;

      }

      return m_pdataitem->data_item_get_image(m_ptree);

   }


   template < primitive_data_item DATA_ITEM > 
   ::image::image_list * tree_item < DATA_ITEM >::get_image_list() const
   {

      if (!m_pdataitem)
      {

         return nullptr;

      }

      return m_pdataitem->data_item_get_image_list(m_ptree);

   }


   template < primitive_data_item DATA_ITEM > 
   tree_item<DATA_ITEM> * tree_item < DATA_ITEM >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (*piLevel)
      {

         *piLevel = 0;

      }

      tree_item * pitem = this;

      while (pitem && iIndex >= 0)
      {

         pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

         iIndex--;

      }

      if (iIndex < 0)
      {

         return pitem;

      }

      return nullptr;

   }


   template < primitive_data_item DATA_ITEM >
   ::collection::index tree_item < DATA_ITEM >::get_proper_item_index(tree_item * pitemParam, ::collection::index * piLevel)
   {

      int iIndex = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      tree_item * pitem = this;

      while (pitem)
      {

         pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

         if (pitem == pitemParam)
         {

            return iIndex;

         }

         iIndex++;

      }

      return -1;

   }


   template < primitive_data_item DATA_ITEM > 
   ::collection::count tree_item < DATA_ITEM >::get_proper_item_count()
   {

      tree_item * pitem = this;

      ::collection::index iLevel = 0;

      ::collection::count iCount = -1;

      while (pitem)
      {

         pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

         iCount++;

         if (iCount >= 65536)
         {

            break;

         }

         if (iLevel <= 0)
         {

            break;

         }

      }

      return iCount;

   }


   template < primitive_data_item DATA_ITEM >
   bool tree_item < DATA_ITEM >::is_expanded() const
   {

      return (m_dwState & ::data::e_tree_item_state_expanded) != 0;

   }


   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::is_expandable() const
   {

      return (m_dwState & ::data::e_tree_item_state_expandable) != 0;

   }


   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::is_descendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      return pitem->is_ascendant(this);

   }


   template < primitive_data_item DATA_ITEM > 
   bool tree_item < DATA_ITEM >::is_ascendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      tree_item * pparent = m_pparent;

      if (pparent == nullptr)
      {

         return false;

      }

      while (pparent != nullptr)
      {

         if (pparent == pitem)
            return true;

         pparent = pparent->m_pparent;

      }

      return false;

   }


   template < primitive_data_item DATA_ITEM > 
   void 
      tree_item < DATA_ITEM >::on_fill_children()
   {

      //if (m_pdataitem)
      //{

      //   m_pdataitem->data_item_on_fill_children(this);

      //}

      for (auto & p : m_treeitema2)
      {

         if (p->is_expanded())
         {

            p->on_fill_children();

         }

      };

   }

   template < primitive_data_item DATA_ITEM >
   ::data::item * tree_item < DATA_ITEM >::_data_item() const
   {

      return m_pdataitem;

   }


   template < primitive_data_item DATA_ITEM >
   class tree_item_ptr_array :
      public pointer_array < tree_item < DATA_ITEM > >
   {
   public:
   };


} // namespace acme


