#pragma once


#include "acme/handler/item.h"
#include "acme/prototype/data/tree_item_base.h"




namespace data
{


   template < prototype_item ITEM >
   class tree_item;

   template < prototype_item ITEM >
   class tree_item_ptr_array;

   template < prototype_item ITEM >
   class tree;


} // namespace data


namespace data
{


   template < prototype_item ITEM >
   class tree_item :
      virtual public tree_item_base
   {
   protected:


      //bool                             m_bPrevious = false;
      //bool                             m_bNext = false;

      ::pointer<tree_item>                            m_pprevious2;
      ::pointer<tree_item>                            m_pnext2;
      ::pointer < ::pointer_array < tree_item > >     m_ptreeitema2;
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
      ::pointer < tree_item >          m_ptreeitemParent;
      //::collection::index              m_iIndexHint;
      tree < ITEM > *                  m_ptree;
      //::collection::index              m_iLevel;
      ::pointer < ITEM >               m_pitem;
      //uptr                             m_dwUser;
      //unsigned int                     m_etreeitemstate;
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
      void get_children(::data::tree_item_ptr_array < ITEM > & ptra);
      ::collection::count get_children_count() override;
      tree_item * get_parent();
      ::collection::count get_expandable_children_count() override;
      ::collection::count get_proper_descendant_count() override;
      virtual tree_item * get_expandable_child(::collection::index iIndex);

      bool insert(enum_relative erelative, tree_item * pitemNew);

      ::collection::index calc_level() override;
      ::collection::index get_level() override;
      ::collection::index get_index() override;


      inline auto previous()
      {
         return m_bPrevious ? m_pprevious2.m_p : _previous();
      }
      inline auto next()
      {
         return m_bNext ? m_pnext2.m_p : _next();
      }
      inline auto head()
      {
         return !m_ptreeitema2 || m_ptreeitema2->is_empty() ? nullptr : m_ptreeitema2->first();
      }
      inline auto tail()
      {
         return !m_ptreeitema2 || m_ptreeitema2->is_empty() ? nullptr : m_ptreeitema2->last();
      }

      tree_item_base * _get_parent() override;


      ::pointer_array < tree_item > * itema() { return m_ptreeitema2; }


      tree_item_base * __previous() override { return previous(); }
      tree_item_base * __next() override { return next(); }
      tree_item_base * __head() override { return head(); }
      tree_item_base * __tail() override { return tail(); }

      virtual tree_item * _previous();
      virtual tree_item * _next();
      virtual tree_item * _head();
      virtual tree_item * _tail();


      tree_item * get_previous_or_parent(::collection::index * iLevelOffset = nullptr);
      tree_item * get_previous();


      tree_item * get_next();
      tree_item * get_next_or_parent_next(::collection::index * iLevelOffset = nullptr);
      tree_item * get_child_or_next(::collection::index * iLevelOffset = nullptr);
      tree_item * get_child_next_or_parent(::collection::index * iLevelOffset = nullptr);


      inline const tree_item * get_child_next_or_parent(::collection::index * iLevelOffset = nullptr) const
      {

         return ((tree_item *)(this))->get_child_next_or_parent(iLevelOffset);

      }

      //tree_item * calc_previous(bool bParent = true);

      //tree_item * calc_next(bool bChild, bool bParent = true, ::collection::index * pindexLevel = nullptr);

      tree_item * first_child();

      // [](const ::data::tree_item * pitem1, const ::data::tree_item * pitem2)
      virtual void sort_children(const ::function < bool(const tree_item * p1, const tree_item * p2) > & functionLess);



      inline tree_item * get_proper_next(::collection::index * pindexLevel = nullptr)
      {

         if ((m_etreeitemstate & ::data::e_tree_item_state_expanded))
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

      tree < ITEM > * get_tree();

      // string get_text() const override;
      // ::collection::index get_image() const override;
      // ::image::image_list * get_image_list() const override;


      void set_parent(tree_item * pparent);

      void erase_tree_item() override;
      void erase_tree_item_descendants() override;
      void erase_child(tree_item * ptreeitem);

      bool is_expanded() const override;
      bool is_expandable() const override;

      void on_fill_children() override;


      bool is_descendant(tree_item * pitem);
      bool is_ascendant(tree_item * pitem);


      ::item * _item() override;
      void _set_item(::item * pitem) override;


      ::collection::index _find_child(tree_item_base * ptreeitem) const override
      {
         if (!m_ptreeitema2)
         {

            return -1;

         }
         return m_ptreeitema2->find_first(dynamic_cast <tree_item <ITEM >*>(ptreeitem));
      }


      tree_item_base * _child_at(::collection::index i) const override
      {

         if (!m_ptreeitema2)
         {

            return nullptr;

         }

         return m_ptreeitema2->element_at(i);
      }
      void erase_child_at(::collection::index i) override
      {

         if (!m_ptreeitema2)
         {

            return;

         }

         m_ptreeitema2->erase_at(i);
      }


      void _insert_child_at(::collection::index i, tree_item_base * ptreeitemNew) override
      {

         ødefer_construct_new(m_ptreeitema2);

         m_ptreeitema2->insert_at(i, dynamic_cast <tree_item < ITEM > *> (ptreeitemNew));

      }


      void _add_child(tree_item_base * ptreeitemNew) override
      {

         ødefer_construct_new(m_ptreeitema2);

         m_ptreeitema2->add_item(ptreeitemNew);

      }


      void _set_child_at(::collection::index i, tree_item_base * ptreeitemSet) override
      {

         ødefer_construct_new(m_ptreeitema2);

         m_ptreeitema2->set_at_grow(i, dynamic_cast <::data::tree_item < ITEM > *>(ptreeitemSet));

      }


      void erase_children() override
      {

         if (!m_ptreeitema2)
         {

            return;

         }

         m_ptreeitema2->clear();

      }


   };



   template < prototype_item ITEM >
   tree_item < ITEM >::tree_item()
   {

      m_iIndexHint = -1;
      m_dwUser = 0;
      m_ptree = nullptr;
      m_iLevel = -1;

   }


   template < prototype_item ITEM >
   tree_item < ITEM >::~tree_item()
   {

   }


   template < prototype_item ITEM >
   tree <ITEM> * tree_item < ITEM >::get_tree()
   {

      return m_ptree;

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::set_parent(tree_item * pparent)
   {

      //if(m_ptreeitemParent == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
      if (m_ptreeitemParent == pparent || pparent == this || is_descendant(pparent))
      {

         return;

      }

      if (::is_set(pparent))
      {

         pparent->m_ptreeitema2->add_unique(this);

      }

      m_ptreeitemParent->m_ptreeitema2->erase(this);

      m_ptreeitemParent = pparent;

      for (auto pitem : *m_ptreeitemParent->m_ptreeitema2)
      {

         pitem->clear_cache();

      }

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::erase_tree_item()
   {

      erase_tree_item_descendants();

      if (m_ptreeitemParent)
      {

         m_ptreeitemParent->erase_child(this);

      }

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::erase_child(tree_item * ptreeitem)
   {

      if (!m_ptreeitema2)
      {

         return;

      }

      auto iIndex = m_ptreeitema2->find_first(ptreeitem);

      if (iIndex < 0)
      {

         return;

      }

      m_ptreeitema2->erase_at(iIndex);

      for (auto pitem : *m_ptreeitema2)
      {

         pitem->clear_cache();

      }

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::erase_tree_item_descendants()
   {

      if (!m_ptreeitema2)
      {

         return;

      }


      for (auto & p : *m_ptreeitema2)
      {

         p->erase_tree_item_descendants();

         p->clear_cache();

      }

      //list_predicate(this, [](auto p) { p->erase_tree_item(); });

      //list_erase_all(this);

      m_ptreeitema2->clear();

      clear_cache();

   }


   template < prototype_item ITEM >
   tree_item <ITEM> * tree_item < ITEM >::find_next_by_user_data(uptr iUserData)
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


   template < prototype_item ITEM >
   void tree_item < ITEM >::clear_cache()
   {

      m_bPrevious = false;
      m_bNext = false;
      m_iIndex = -2;

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::destroy()
   {

      m_ptreeitemParent.release();

      if (m_ptreeitema2)
      {

         m_ptreeitema2.defer_destroy();

      }

      m_ptree = nullptr;

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::erase_item_from_parent()
   {

      auto ptreeitemParent = m_ptreeitemParent;

      if (!ptreeitemParent)
      {

         return true;

      }

      auto ptreeitema = ptreeitemParent->m_ptreeitema2;

      if (!ptreeitema)
      {

         return true;

      }

      if (!ptreeitema->contains(this))
      {

         // self healing?
         m_ptreeitemParent = nullptr;

         return false;

      }

      ptreeitema->erase(this);

      for (auto p : *ptreeitema)
      {

         p->clear_cache();

      }

      m_ptreeitemParent = nullptr;

      return true;

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::contains(const tree_item * ptreeitem)
   {

      if (ptreeitem == this)
      {

         return true;

      }

      if (!m_ptreeitema2)
      {

         return false;

      }

      for (auto & p : *m_ptreeitema2)
      {

         if (p->contains(ptreeitem))
         {

            return true;

         }

      }

      return false;

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::insert(enum_relative erelative, tree_item * pitemNew)
   {

      if (contains(pitemNew))
      {

         throw ::exception(error_wrong_state);

      }

      if (erelative == e_relative_first_child)
      {

         pitemNew->erase_item_from_parent();
         
         ødefer_construct_new(m_ptreeitema2);

         m_ptreeitema2->insert_at(0, pitemNew);

         for (auto & pitem : *m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_ptreeitemParent = this;

         return true;

      }
      else if (erelative == e_relative_last_child)
      {

         pitemNew->erase_item_from_parent();

         ødefer_construct_new(m_ptreeitema2);

         m_ptreeitema2->add(pitemNew);

         for (auto & pitem : *m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_ptreeitemParent = this;

         return true;

      }
      else if (erelative == e_relative_previous_sibling)
      {

         ASSERT(m_ptreeitemParent != nullptr);

         if (m_ptreeitemParent == nullptr)
         {

            return false;

         }

         auto iFind = m_ptreeitemParent->m_ptreeitema2->find_first(this);

         if (iFind < 0)
         {

            // self-healinng
            m_ptreeitemParent = nullptr;

            return false;

         }

         m_ptreeitemParent->m_ptreeitema2->insert_at(iFind, pitemNew);

         for (auto & pitem : *m_ptreeitemParent->m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_ptreeitemParent = m_ptreeitemParent;

         return true;

      }
      else if (erelative == e_relative_next_sibling)
      {

         if (m_ptreeitemParent == nullptr)
         {

            return false;

         }

         auto iFind = m_ptreeitemParent->m_ptreeitema2->find_first(this);

         if (iFind < 0)
         {

            // self-healing
            m_ptreeitemParent = nullptr;

            return false;

         }

         m_ptreeitemParent->m_ptreeitema2->insert_at(iFind + 1, pitemNew);

         for (auto & pitem : *m_ptreeitemParent->m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_ptreeitemParent = m_ptreeitemParent;

         return true;

      }
      else if (erelative == e_relative_last_sibling)
      {

         m_ptreeitemParent->ødefer_construct_new(m_ptreeitemParent->m_ptreeitema2);

         m_ptreeitemParent->m_ptreeitema2->add(pitemNew);

         for (auto & pitem : *m_ptreeitemParent->m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_ptreeitemParent = m_ptreeitemParent;

         return true;

      }
      else if (erelative == e_relative_replace)
      {

         ødefer_construct_new(m_ptreeitemParent->m_ptreeitema2);

         auto iFind = m_ptreeitemParent->m_ptreeitema2->find_first(this);

         if (iFind < 0)
         {

            m_ptreeitemParent = nullptr;

            return false;

         }

         m_ptreeitemParent->m_ptreeitema2->element_at(iFind) = pitemNew;

         for (auto & pitem : *m_ptreeitemParent->m_ptreeitema2)
         {

            pitem->clear_cache();

         }

         m_ptreeitemParent = nullptr;

         erase_tree_item();

         return true;

      }

      return false;

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::sort_children(const ::function < bool(const tree_item * p1, const tree_item * p2) > & functionLess)
   {

      if (!m_ptreeitema2)
      {

         return;

      }

      //data_tree_item_list_sort(this, functionLess);

      m_ptreeitema2->predicate_sort(functionLess);

      for (auto & pitem : *m_ptreeitema2)
      {

         pitem->clear_cache();

      }


   }


   template < prototype_item ITEM >
   tree_item <ITEM> * tree_item < ITEM >::get_child_by_user_data(uptr iUserData)
   {

      if (!m_ptreeitema2)
      {

         return  nullptr;

      }

      auto iFind = m_ptreeitema2->predicate_find_first([iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_ptreeitema2->element_at(iFind);

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::get_children(tree_item_ptr_array<ITEM> & ptra)
   {

      if (m_ptreeitema2)
      {

         ptra.append(*m_ptreeitema2);

      }

   }


   template < prototype_item ITEM >
   ::collection::count  tree_item < ITEM >::get_children_count()
   {

      if (!m_ptreeitema2)
      {

         return  0;

      }

      return m_ptreeitema2->get_count();

   }


   template < prototype_item ITEM >
   tree_item < ITEM > * tree_item < ITEM >::get_parent()
   {

      return m_ptreeitemParent;

   }


   template < prototype_item ITEM >
   ::collection::count tree_item < ITEM >::get_expandable_children_count()
   {

      if (!m_ptreeitema2)
      {

         return  0;

      }


      ::collection::count c = 0;

      for (auto & p : *m_ptreeitema2)
      {

         if (p->get_children_count() > 0)
         {

            c++;

         }

      }

      return c;

   }


   template < prototype_item ITEM >
   tree_item <ITEM> * tree_item < ITEM >::get_expandable_child(::collection::index iIndex)
   {


      if (!m_ptreeitema2)
      {

         return  nullptr;

      }

      ::collection::count c = 0;

      auto iFind = m_ptreeitema2->predicate_find_first([&c, iIndex](auto & p)
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

      return m_ptreeitema2->element_at(iFind);

   }


   template < prototype_item ITEM >
   ::collection::count tree_item < ITEM >::get_proper_descendant_count()
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


   template < prototype_item ITEM >
   inline tree_item<ITEM> * tree_item < ITEM >::get_previous_or_parent(::collection::index * piLevel)
   {

      auto p = previous();

      if (p)
      {

         return p;

      }

      if (m_ptreeitemParent)
      {

         return m_ptreeitemParent;

         //if (piLevel)
         //{

         //   (*piLevel)--;

         //}

         //return m_ptreeitemParent->get_previous_or_parent(piLevel);

      }

      return nullptr;

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_previous()
   {

      return previous();

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_next()
   {

      return next();

   }


   template < prototype_item ITEM >
   ::collection::index tree_item < ITEM >::calc_level()
   {

      if (m_iLevel < 0)
      {

         m_iLevel = -1;

         tree_item * p = this;

         while (p != nullptr)
         {

            m_iLevel++;

            p = p->m_ptreeitemParent;

         }

      }

      return m_iLevel;

   }


   template < prototype_item ITEM >
   ::collection::index tree_item < ITEM >::get_level()
   {

      return m_iLevel >= 0 ? m_iLevel : calc_level();

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::_previous()
   {

      m_bPrevious = true;

      if (::is_null(m_ptreeitemParent))
      {

         m_pprevious2.release();

         return nullptr;

      }

      auto iFind = get_index();

      if (iFind <= 0)
      {

         m_pprevious2.release();

         return nullptr;

      }

      return m_pprevious2 = m_ptreeitemParent->m_ptreeitema2->element_at(iFind - 1);

   }


   template < prototype_item ITEM >
   tree_item <ITEM> * tree_item < ITEM >::_next()
   {

      m_bNext = true;

      if (::is_null(m_ptreeitemParent))
      {

         m_pnext2.release();

         return nullptr;

      }

      auto iFind = get_index();

      if (iFind < 0 || iFind >= m_ptreeitemParent->m_ptreeitema2->get_upper_bound())
      {

         m_pnext2.release();

         return nullptr;

      }

      return m_pnext2 = m_ptreeitemParent->m_ptreeitema2->element_at(iFind + 1);

   }



   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::_head()
   {

      if (::is_null(m_ptreeitema2))
      {

         return nullptr;

      }

      return m_ptreeitema2->first();

   }


   template < prototype_item ITEM >
   tree_item <ITEM> * tree_item < ITEM >::_tail()
   {

      if (::is_null(m_ptreeitema2))
      {

         return nullptr;

      }

      return m_ptreeitema2->last();

   }


   template < prototype_item ITEM >
   tree_item_base * tree_item < ITEM >::_get_parent()
   {

      return m_ptreeitemParent;

   }


   //::data::tree_item * template < prototype_item ITEM > tree_item < ITEM >::head()
   //{

   //   if (m_treeitema.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema.first();

   //}


   //::data::tree_item * template < prototype_item ITEM > tree_item < ITEM >::tail()
   //{

   //   if (m_treeitema.is_empty())
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema.last();

   //}


   template < prototype_item ITEM >
   ::collection::index tree_item < ITEM >::get_index()
   {

      if (m_iIndex >= -1)
      {

         return m_iIndex;

      }

      if (m_ptreeitemParent == nullptr)
      {

         m_iIndex = -1;

         return -1;

      }

      return m_iIndex = m_ptreeitemParent->m_ptreeitema2->find_first(this);

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_next_or_parent_next(::collection::index * piLevel)
   {

      if (next())
      {

         return next();

      }

      if (!m_ptreeitemParent)
      {

         return nullptr;

      }

      if (piLevel)
      {

         (*piLevel)--;

      }

      return m_ptreeitemParent->get_next_or_parent_next(piLevel);

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_child_or_next(::collection::index * piLevel)
   {

      if (head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return head();

      }

      return next();

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_child_next_or_parent(::collection::index * piLevel)
   {

      if (head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return head();

      }

      return get_next_or_parent_next(piLevel);

   }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_item(enum_tree_navigation enavigation, ::collection::index * pindexLevel)
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


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_item(enum_relative erelative)
   {

      switch (erelative)
      {
      case e_relative_first_child:
      {
         return head();
      }
      break;
      case e_relative_last_child:
      {
         return tail();
      }
      case e_relative_parent:
      {
         return m_ptreeitemParent;
      }
      break;
      case e_relative_first_sibling:
      {
         return m_ptreeitemParent->head();
      }
      break;
      case e_relative_previous_sibling:
      {
         return previous();
      }
      break;
      case e_relative_next_sibling:
      {
         return next();
      }
      break;
      case e_relative_last_sibling:
      {
         return m_ptreeitemParent->tail();
      }
      break;
      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }
   }



   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::first_child()
   {

      return head();

   }


   // template < prototype_item ITEM >
   // string tree_item < ITEM >::get_text() const
   // {
   //
   //    if (!m_pitem)
   //    {
   //
   //       return "";
   //
   //    }
   //
   //    return m_pitem->data_item_get_text(m_ptree);
   //
   // }
   //
   //
   // template < prototype_item ITEM >
   // ::collection::index tree_item < ITEM >::get_image() const
   // {
   //
   //    if (!m_pitem)
   //    {
   //
   //       return -1;
   //
   //    }
   //
   //    return m_pitem->data_item_get_image(m_ptree);
   //
   // }
   //
   //
   // template < prototype_item ITEM >
   // ::image::image_list * tree_item < ITEM >::get_image_list() const
   // {
   //
   //    if (!m_pitem)
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //    return m_pitem->data_item_get_image_list(m_ptree);
   //
   // }


   template < prototype_item ITEM >
   tree_item<ITEM> * tree_item < ITEM >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
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


   template < prototype_item ITEM >
   ::collection::index tree_item < ITEM >::get_proper_item_index(tree_item * pitemParam, ::collection::index * piLevel)
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


   template < prototype_item ITEM >
   ::collection::count tree_item < ITEM >::get_proper_item_count()
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


   template < prototype_item ITEM >
   bool tree_item < ITEM >::is_expanded() const
   {

      return (m_etreeitemstate & ::data::e_tree_item_state_expanded) != 0;

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::is_expandable() const
   {

      return (m_etreeitemstate & ::data::e_tree_item_state_expandable) != 0;

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::is_descendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      return pitem->is_ascendant(this);

   }


   template < prototype_item ITEM >
   bool tree_item < ITEM >::is_ascendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      tree_item * pparent = m_ptreeitemParent;

      if (pparent == nullptr)
      {

         return false;

      }

      while (pparent != nullptr)
      {

         if (pparent == pitem)
            return true;

         pparent = pparent->m_ptreeitemParent;

      }

      return false;

   }


   template < prototype_item ITEM >
   void
      tree_item < ITEM >::on_fill_children()
   {

      //if (m_pitem)
      //{

      //   m_pitem->data_item_on_fill_children(this);

      //}

      for (auto & p : *m_ptreeitema2)
      {

         if (p->is_expanded())
         {

            p->on_fill_children();

         }

      };

   }


   template < prototype_item ITEM >
   ::item * tree_item < ITEM >::_item()
   {

      return m_pitem;

   }


   template < prototype_item ITEM >
   void tree_item < ITEM >::_set_item(::item * pitem)
   {

      m_pitem = pitem;

   }


   template < prototype_item ITEM >
   class tree_item_ptr_array :
      public pointer_array < tree_item < ITEM > >
   {
   public:
   };


} // namespace acme


