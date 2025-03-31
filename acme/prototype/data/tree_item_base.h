// Created by camilo on 2025-03-29 22:22 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/user/user/item_base.h"


namespace data
{


   class CLASS_DECL_ACME tree_item_base :
      virtual public ::user::item_base
   {
   protected:


      bool                             m_bPrevious = false;
      bool                             m_bNext = false;

      //::pointer<tree_item>             m_pprevious2;
      //::pointer<tree_item>             m_pnext2;
      //::data::tree_item_ptr_array    m_treeitema2;
      ::collection::index              m_iIndex = -2;

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
         flag_nexts = flag_next | flag_next_or_parent | flag_child_or_next | flag_child_next_or_parent,

      };

      //::pointer<tree_item>             m_phead; // first child
      //::pointer<tree_item>             m_ptail; // last child
      //::pointer < tree_item >          m_pparent;
      ::collection::index              m_iIndexHint;
      //tree  * m_ptree;
      ::collection::index              m_iLevel;
      //::pointer           m_pdataitem;
      uptr                             m_dwUser;
      unsigned int                     m_dwState;
      uptr                             m_dwMetaData;


      tree_item_base();
      ~tree_item_base() override;


#ifdef DEBUG


      virtual long long increment_reference_count() override
      {

         return ::particle::increment_reference_count();

      }

      virtual long long decrement_reference_count() override
      {

         return ::particle::decrement_reference_count();

      }


#endif
      virtual void clear_cache();
      void destroy() override;
      virtual bool erase_item_from_parent();

      virtual tree_item_base * _get_child_by_user_data(unsigned long long ullUserData);
      virtual tree_item_base * _find_next_by_user_data(unsigned long long ullUserData);
      virtual void _get_children(::data::tree_item_base_ptr_array & ptra);
      virtual ::collection::count get_children_count();
      virtual tree_item_base * _get_parent();
      virtual void _set_parent(tree_item_base * _ptreeitembase);
      virtual ::collection::count get_expandable_children_count();
      virtual ::collection::count get_proper_descendant_count();
      virtual tree_item_base * _get_expandable_child(::collection::index iIndex);

      virtual bool _insert(enum_relative erelative, tree_item_base * _pitemNew);

      virtual ::collection::index calc_level();
      virtual ::collection::index get_level();
      virtual ::collection::index get_index();


      virtual tree_item_base * __previous();
      virtual tree_item_base * __next();
      virtual tree_item_base * __head();
      virtual tree_item_base * __tail();



      virtual tree_item_base * _get_previous_or_parent(::collection::index * iLevelOffset = nullptr);
      virtual tree_item_base * _get_previous();


      virtual tree_item_base * _get_next();
      virtual tree_item_base * _get_next_or_parent_next(::collection::index * iLevelOffset = nullptr);
      virtual tree_item_base * _get_child_or_next(::collection::index * iLevelOffset = nullptr);
      virtual tree_item_base * _get_child_next_or_parent(::collection::index * iLevelOffset = nullptr);


      inline const tree_item_base * _get_child_next_or_parent(::collection::index * iLevelOffset = nullptr) const
      {

         return ((tree_item_base *)(this))->_get_child_next_or_parent(iLevelOffset);

      }

      //tree_item_base * _calc_previous(bool bParent = true);

      //tree_item_base * _calc_next(bool bChild, bool bParent = true, ::collection::index * pindexLevel = nullptr);

      virtual tree_item_base * _first_child();

      // [](const ::data::tree_item_base * _pitem1, const ::data::tree_item_base * _pitem2)
      //virtual void sort_children(const ::function < bool(const tree_item_base * _p1, const tree_item_base * _p2) > & functionLess);



      inline tree_item_base * _get_proper_next(::collection::index * pindexLevel = nullptr)
      {

         if ((m_dwState & ::data::e_tree_item_state_expanded))
         {

            return _get_child_next_or_parent(pindexLevel);

         }
         else
         {

            return _get_next_or_parent_next(pindexLevel);

         }

      }

      virtual tree_item_base * _get_item(enum_tree_navigation enavigation, ::collection::index * piLevelOffset = nullptr);
      virtual tree_item_base * _get_item(enum_relative erelative);

      virtual bool _contains(const tree_item_base * _ptreeitem);
      virtual tree_item_base * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel);
      virtual ::collection::index _get_proper_item_index(tree_item_base * _pitem, ::collection::index * piLevel);
      virtual ::collection::count get_proper_item_count();

      virtual tree_base* _get_tree() const =0;
      virtual void _set_tree(tree_base * ptree) =0;

      // void set_item(::item * pitem) override;
      // ::item * item() override;


      // string get_tree_item_text();
      // ::collection::index get_tree_item_image();
      // ::image::image_list * get_tree_item_image_list();


      //void set_parent(tree_item_base * _pparent);

      virtual void erase_tree_item();
      virtual void erase_tree_item_descendants();
      virtual void _erase_child(tree_item_base * _ptreeitem);

      virtual ::collection::index _find_child(tree_item_base * _ptreeitem) const;
      virtual bool _contains_child(tree_item_base * _ptreeitem) const;
      virtual tree_item_base * _child_at(::collection::index i) const;
      virtual void erase_child_at(::collection::index i);
      virtual void _insert_child_at(::collection::index i, tree_item_base * _ptreeitemNew);
      virtual void _add_child(tree_item_base * _ptreeitemNew);
      virtual void _set_child_at(::collection::index i, tree_item_base * _ptreeitemSet);
      virtual void erase_children();

      virtual void _predicate_each(const ::function < bool(tree_item_base *) > & callback);
      virtual ::collection::index _predicate_find_first(const ::function < bool(tree_item_base *) > & callback);

      virtual bool is_expanded() const;
      virtual bool is_expandable() const;

      virtual void on_fill_children();

      virtual bool _is_descendant(tree_item_base * _pitem);
      virtual bool _is_ascendant(tree_item_base * _pitem);


   };



   //template < prototype_item DATA_ITEM > tree_item ::tree_item()
   //{

   //   m_iIndexHint = -1;
   //   m_dwUser = 0;
   //   m_dwState = 0;
   //   m_ptree = nullptr;
   //   m_pparent = nullptr;
   //   m_iLevel = -1;
   //   m_pparent = nullptr;

   //}


   //template < prototype_item DATA_ITEM > tree_item ::~tree_item()
   //{

   //}


   //template < prototype_item DATA_ITEM >
   //tree  * tree_item ::get_tree()
   //{

   //   return m_ptree;

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::set_parent(tree_item_base * _pparent)
   //{

   //   //if(m_pparent == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
   //   if (m_pparent == pparent || pparent == this || is_descendant(pparent))
   //   {

   //      return;

   //   }

   //   if (::is_set(pparent))
   //   {

   //      pparent->m_treeitema2.add_unique(this);

   //   }

   //   m_pparent->m_treeitema2.erase(this);

   //   m_pparent = pparent;

   //   for (auto pitem : m_pparent->m_treeitema2)
   //   {

   //      pitem->clear_cache();

   //   }

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::erase_tree_item()
   //{

   //   erase_tree_item_descendants();

   //   if (m_pparent)
   //   {

   //      m_pparent->erase_child(this);

   //   }

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::erase_child(tree_item_base * _ptreeitem)
   //{

   //   auto iIndex = m_treeitema2.find_first(ptreeitem);

   //   if (iIndex < 0)
   //   {

   //      return;

   //   }

   //   m_treeitema2.erase_at(iIndex);

   //   for (auto pitem : m_treeitema2)
   //   {

   //      pitem->clear_cache();

   //   }

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::erase_tree_item_descendants()
   //{

   //   for (auto & p : m_treeitema2)
   //   {

   //      p->erase_tree_item_descendants();

   //      p->clear_cache();

   //   }

   //   //list_predicate(this, [](auto p) { p->erase_tree_item(); });

   //   //list_erase_all(this);

   //   m_treeitema2.clear();

   //   clear_cache();

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item  * tree_item ::find_next_by_user_data(uptr iUserData)
   //{

   //   auto ptreeitem = this;

   //   while (true)
   //   {

   //      ptreeitem = ptreeitem->get_item(e_tree_navigation_expanded_forward);

   //      if (!ptreeitem)
   //      {

   //         return nullptr;

   //      }

   //      if (ptreeitem->m_dwUser == (unsigned int)iUserData)
   //      {

   //         return ptreeitem;

   //      }

   //   }

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::clear_cache()
   //{

   //   m_bPrevious = false;
   //   m_bNext = false;
   //   m_iIndex = -2;

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::destroy()
   //{

   //   m_pparent.release();

   //   m_treeitema2.destroy();

   //   m_ptree = nullptr;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::erase_item_from_parent()
   //{

   //   tree_item_base * _pitem = this;

   //   if (pitem->m_pparent == nullptr)
   //   {

   //      return true;

   //   }

   //   if (!pitem->m_pparent->m_treeitema2.contains(pitem))
   //   {

   //      // self healing?
   //      pitem->m_pparent = nullptr;

   //      return false;

   //   }

   //   pitem->m_pparent->m_treeitema2.erase(pitem);

   //   for (auto p : pitem->m_pparent->m_treeitema2)
   //   {

   //      p->clear_cache();

   //   }
   //   pitem->m_pparent = nullptr;

   //   return true;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::contains(const tree_item_base * _ptreeitem)
   //{

   //   if (ptreeitem == this)
   //   {

   //      return true;

   //   }

   //   for (auto & p : m_treeitema2)
   //   {

   //      if (p->contains(ptreeitem))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::insert(enum_relative erelative, tree_item_base * _pitemNew)
   //{

   //   if (contains(pitemNew))
   //   {

   //      throw ::exception(error_wrong_state);

   //   }

   //   if (erelative == e_relative_first_child)
   //   {

   //      pitemNew->erase_item_from_parent();

   //      m_treeitema2.insert_at(0, pitemNew);

   //      for (auto & pitem : m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      pitemNew->m_iLevel = m_iLevel + 1;

   //      pitemNew->m_pparent = this;

   //      return true;

   //   }
   //   else if (erelative == e_relative_last_child)
   //   {

   //      pitemNew->erase_item_from_parent();

   //      m_treeitema2.add(pitemNew);

   //      for (auto & pitem : m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      pitemNew->m_iLevel = m_iLevel + 1;

   //      pitemNew->m_pparent = this;

   //      return true;

   //   }
   //   else if (erelative == e_relative_previous_sibling)
   //   {

   //      ASSERT(m_pparent != nullptr);

   //      if (m_pparent == nullptr)
   //      {

   //         return false;

   //      }

   //      auto iFind = m_pparent->m_treeitema2.find_first(this);

   //      if (iFind < 0)
   //      {

   //         // self-healinng
   //         m_pparent = nullptr;

   //         return false;

   //      }

   //      m_pparent->m_treeitema2.insert_at(iFind, pitemNew);

   //      for (auto & pitem : m_pparent->m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      pitemNew->m_iLevel = m_iLevel;

   //      pitemNew->m_pparent = m_pparent;

   //      return true;

   //   }
   //   else if (erelative == e_relative_next_sibling)
   //   {

   //      if (m_pparent == nullptr)
   //      {

   //         return false;

   //      }

   //      auto iFind = m_pparent->m_treeitema2.find_first(this);

   //      if (iFind < 0)
   //      {

   //         // self-healing
   //         m_pparent = nullptr;

   //         return false;

   //      }

   //      m_pparent->m_treeitema2.insert_at(iFind + 1, pitemNew);

   //      for (auto & pitem : m_pparent->m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      pitemNew->m_iLevel = m_iLevel;

   //      pitemNew->m_pparent = m_pparent;

   //      return true;

   //   }
   //   else if (erelative == e_relative_last_sibling)
   //   {

   //      m_pparent->m_treeitema2.add(pitemNew);

   //      for (auto & pitem : m_pparent->m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      pitemNew->m_iLevel = m_iLevel;

   //      pitemNew->m_pparent = m_pparent;

   //      return true;

   //   }
   //   else if (erelative == e_relative_replace)
   //   {

   //      auto iFind = m_pparent->m_treeitema2.find_first(this);

   //      if (iFind < 0)
   //      {

   //         m_pparent = nullptr;

   //         return false;

   //      }

   //      m_pparent->m_treeitema2[iFind] = pitemNew;

   //      for (auto & pitem : m_pparent->m_treeitema2)
   //      {

   //         pitem->clear_cache();

   //      }

   //      m_pparent = nullptr;

   //      erase_tree_item();

   //      return true;

   //   }

   //   return false;

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::sort_children(const ::function < bool(const tree_item_base * _p1, const tree_item_base * _p2) > & functionLess)
   //{

   //   //data_tree_item_list_sort(this, functionLess);

   //   m_treeitema2.predicate_sort(functionLess);

   //   for (auto & pitem : m_treeitema2)
   //   {

   //      pitem->clear_cache();

   //   }


   //}


   //template < prototype_item DATA_ITEM >
   //tree_item  * tree_item ::get_child_by_user_data(uptr iUserData)
   //{

   //   auto iFind = m_treeitema2.predicate_find_first([iUserData](auto p)
   //      {

   //         return p->m_dwUser == iUserData;

   //      });

   //   if (iFind < 0)
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema2[iFind];

   //}


   //template < prototype_item DATA_ITEM >
   //void tree_item ::get_children(tree_item_ptr_array & ptra)
   //{

   //   ptra.append(m_treeitema2);

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::count  tree_item ::get_children_count()
   //{

   //   return m_treeitema2.get_count();

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item  * tree_item ::get_parent()
   //{

   //   return m_pparent;

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::count tree_item ::get_expandable_children_count()
   //{

   //   ::collection::count c = 0;

   //   for (auto & p : m_treeitema2)
   //   {

   //      if (p->get_children_count() > 0)
   //      {

   //         c++;

   //      }

   //   }

   //   return c;

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item  * tree_item ::get_expandable_child(::collection::index iIndex)
   //{

   //   ::collection::count c = 0;

   //   auto iFind = m_treeitema2.predicate_find_first([&c, iIndex](auto & p)
   //      {

   //         if (p->get_children_count() > 0)
   //         {

   //            if (c == iIndex)
   //            {

   //               return true;

   //            }

   //         }

   //         return false;

   //      });

   //   if (iFind < 0)
   //   {

   //      return nullptr;

   //   }

   //   return m_treeitema2[iFind];

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::count tree_item ::get_proper_descendant_count()
   //{

   //   ::collection::count iCount = 0;

   //   ::collection::index iLevel = 0;

   //   tree_item_base * _pitem = this;

   //   for (;;)
   //   {

   //      pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

   //      if (pitem == nullptr || iLevel <= 0)
   //      {

   //         break;

   //      }

   //      iCount++;

   //   }

   //   return iCount;

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_previous_or_parent(::collection::index * piLevel)
   //{

   //   if (____previous())
   //   {

   //      return _previous();

   //   }

   //   if (m_pparent)
   //   {

   //      return m_pparent;

   //      //if (piLevel)
   //      //{

   //      //   (*piLevel)--;

   //      //}

   //      //return m_pparent->get_previous_or_parent(piLevel);

   //   }

   //   return nullptr;

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_previous()
   //{

   //   return _previous();

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_next()
   //{

   //   return _next();

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::index tree_item ::calc_level()
   //{

   //   if (m_iLevel < 0)
   //   {

   //      m_iLevel = -1;

   //      tree_item_base * _p = this;

   //      while (p != nullptr)
   //      {

   //         m_iLevel++;

   //         p = p->m_pparent;

   //      }

   //   }

   //   return m_iLevel;

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::_____previous()
   //{

   //   m_bPrevious = true;

   //   if (::is_null(m_pparent))
   //   {

   //      m_pprevious2.release();

   //      return nullptr;

   //   }

   //   auto iFind = get_index();

   //   if (iFind <= 0)
   //   {

   //      m_pprevious2.release();

   //      return nullptr;

   //   }

   //   return m_pprevious2 = m_pparent->m_treeitema2[iFind - 1];

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item  * tree_item ::_____next()
   //{

   //   m_bNext = true;

   //   if (::is_null(m_pparent))
   //   {

   //      m_pnext2.release();

   //      return nullptr;

   //   }

   //   auto iFind = get_index();

   //   if (iFind < 0 || iFind >= m_pparent->m_treeitema2.get_upper_bound())
   //   {

   //      m_pnext2.release();

   //      return nullptr;

   //   }

   //   return m_pnext2 = m_pparent->m_treeitema2[iFind + 1];

   //}


   ////::data::tree_item_base * _template < prototype_item DATA_ITEM > tree_item ::____head()
   ////{

   ////   if (m_treeitema.is_empty())
   ////   {

   ////      return nullptr;

   ////   }

   ////   return m_treeitema.first();

   ////}


   ////::data::tree_item_base * _template < prototype_item DATA_ITEM > tree_item ::____tail()
   ////{

   ////   if (m_treeitema.is_empty())
   ////   {

   ////      return nullptr;

   ////   }

   ////   return m_treeitema.last();

   ////}


   //template < prototype_item DATA_ITEM >
   //::collection::index tree_item ::_get_index()
   //{

   //   if (m_iIndex >= -1)
   //   {

   //      return m_iIndex;

   //   }

   //   if (m_pparent == nullptr)
   //   {

   //      m_iIndex = -1;

   //      return -1;

   //   }

   //   return m_iIndex = m_pparent->m_treeitema2.find_first(this);

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_next_or_parent_next(::collection::index * piLevel)
   //{

   //   if (____next())
   //   {

   //      return _next();

   //   }

   //   if (!m_pparent)
   //   {

   //      return nullptr;

   //   }

   //   if (piLevel)
   //   {

   //      (*piLevel)--;

   //   }

   //   return m_pparent->get_next_or_parent_next(piLevel);

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_child_or_next(::collection::index * piLevel)
   //{

   //   if (____head())
   //   {

   //      if (piLevel)
   //      {

   //         (*piLevel)++;

   //      }

   //      return _head();

   //   }

   //   return _next();

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_child_next_or_parent(::collection::index * piLevel)
   //{

   //   if (____head())
   //   {

   //      if (piLevel)
   //      {

   //         (*piLevel)++;

   //      }

   //      return _head();

   //   }

   //   return get_next_or_parent_next(piLevel);

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_item(enum_tree_navigation enavigation, ::collection::index * pindexLevel)
   //{

   //   switch (enavigation)
   //   {
   //   case e_tree_navigation_expanded_forward:

   //      return get_child_next_or_parent(pindexLevel);

   //   case e_tree_navigation_proper_forward:

   //      return get_proper_next(pindexLevel);

   //   default:
   //      // Not Expected
   //      ASSERT(false);
   //      return nullptr;
   //   }

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_item(enum_relative erelative)
   //{

   //   switch (erelative)
   //   {
   //   case e_relative_first_child:
   //   {
   //      return _head();
   //   }
   //   break;
   //   case e_relative_last_child:
   //   {
   //      return __tail();
   //   }
   //   case e_relative_parent:
   //   {
   //      return m_pparent;
   //   }
   //   break;
   //   case e_relative_first_sibling:
   //   {
   //      return m_pparent->____head();
   //   }
   //   break;
   //   case e_relative_previous_sibling:
   //   {
   //      return __previous();
   //   }
   //   break;
   //   case e_relative_next_sibling:
   //   {
   //      return __next();
   //   }
   //   break;
   //   case e_relative_last_sibling:
   //   {
   //      return m_pparent->____tail();
   //   }
   //   break;
   //   default:
   //      // Not Expected
   //      ASSERT(false);
   //      return nullptr;
   //   }
   //}



   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::first_child()
   //{

   //   return __head();

   //}


   //template < prototype_item DATA_ITEM >
   //string tree_item ::get_text() const
   //{

   //   if (!m_pdataitem)
   //   {

   //      return "";

   //   }

   //   return m_pdataitem->get_item_text(m_ptree);

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::index tree_item ::get_image() const
   //{

   //   if (!m_pdataitem)
   //   {

   //      return -1;

   //   }

   //   return m_pdataitem->get_item_image(m_ptree);

   //}


   //template < prototype_item DATA_ITEM >
   //::image::image_list * tree_item ::get_image_list() const
   //{

   //   if (!m_pdataitem)
   //   {

   //      return nullptr;

   //   }

   //   return m_pdataitem->get_item_image_list(m_ptree);

   //}


   //template < prototype_item DATA_ITEM >
   //tree_item_base * _tree_item ::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   //{

   //   if (*piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   tree_item_base * _pitem = this;

   //   while (pitem && iIndex >= 0)
   //   {

   //      pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

   //      iIndex--;

   //   }

   //   if (iIndex < 0)
   //   {

   //      return pitem;

   //   }

   //   return nullptr;

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::index tree_item ::get_proper_item_index(tree_item_base * _pitemParam, ::collection::index * piLevel)
   //{

   //   int iIndex = 0;

   //   if (piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   tree_item_base * _pitem = this;

   //   while (pitem)
   //   {

   //      pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

   //      if (pitem == pitemParam)
   //      {

   //         return iIndex;

   //      }

   //      iIndex++;

   //   }

   //   return -1;

   //}


   //template < prototype_item DATA_ITEM >
   //::collection::count tree_item ::get_proper_item_count()
   //{

   //   tree_item_base * _pitem = this;

   //   ::collection::index iLevel = 0;

   //   ::collection::count iCount = -1;

   //   while (pitem)
   //   {

   //      pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

   //      iCount++;

   //      if (iCount >= 65536)
   //      {

   //         break;

   //      }

   //      if (iLevel <= 0)
   //      {

   //         break;

   //      }

   //   }

   //   return iCount;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::is_expanded() const
   //{

   //   return (m_dwState & ::data::e_tree_item_state_expanded) != 0;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::is_expandable() const
   //{

   //   return (m_dwState & ::data::e_tree_item_state_expandable) != 0;

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::is_descendant(tree_item_base * _pitem)
   //{

   //   if (pitem == nullptr)
   //   {

   //      return false;

   //   }

   //   return pitem->is_ascendant(this);

   //}


   //template < prototype_item DATA_ITEM >
   //bool tree_item ::is_ascendant(tree_item_base * _pitem)
   //{

   //   if (pitem == nullptr)
   //   {

   //      return false;

   //   }

   //   tree_item_base * _pparent = m_pparent;

   //   if (pparent == nullptr)
   //   {

   //      return false;

   //   }

   //   while (pparent != nullptr)
   //   {

   //      if (pparent == pitem)
   //         return true;

   //      pparent = pparent->m_pparent;

   //   }

   //   return false;

   //}


   //template < prototype_item DATA_ITEM >
   //void
   //   tree_item ::on_fill_children()
   //{

   //   //if (m_pdataitem)
   //   //{

   //   //   m_pdataitem->data_item_on_fill_children(this);

   //   //}

   //   for (auto & p : m_treeitema2)
   //   {

   //      if (p->is_expanded())
   //      {

   //         p->on_fill_children();

   //      }

   //   };

   //}




   //template < prototype_item DATA_ITEM >
   class tree_item_base_ptr_array :
      public pointer_array < tree_item_base  >
   {
   public:
   };


} // namespace acme


