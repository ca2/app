#pragma once


#include "acme/prototype/data/data.h"
#include "acme/prototype/data/tree_item.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace data
{


   class CLASS_DECL_ACME tree :
      virtual public ::data::data,
      virtual public tree_item
   {
   public:


      pointer_array < tree >                    m_treea;
      //::pointer<tree_item>               m_proot;
      bool                                m_bFill;
      index_array                         m_iaLevelNext;




      tree();
      ~tree() override;

      void destroy() override;

      virtual void on_insert_tree(tree * ptree);

      virtual long long increment_reference_count() override
      {
         return ::matter::increment_reference_count();
      }

      virtual long long decrement_reference_count() override
      {
         return ::matter::decrement_reference_count();
      }


      virtual void erase_all();

      virtual void update_tree();

      virtual tree_item * find(const item * pitem, ::collection::index * piIndex = nullptr);
      virtual bool contains(const item * pitem);

      bool contains(const tree_item * pitem) override;

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context, ::user::element * ptree, const ::int_point & point);

      virtual void erase(tree_item_ptr_array & itemptra);
      virtual void erase(tree_item * pitem);
      virtual void erase(item * pitem, ::collection::index i = 0);


      ::data::tree_item * _____previous() override;
      ::data::tree_item * _____next() override;
      //template < typename PRED >
      //void sort_children(PRED pred)
      //{

      //   tree_sort(this, pred);

      //}
      void sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess) override;

      virtual tree_item * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      virtual tree_item* get_proper_item(::collection::index iIndex, ::collection::index * piLevel) override;
      virtual ::collection::index get_proper_item_index(tree_item * pitemParam, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
//      virtual ::collection::count get_proper_item_count() override;

      virtual void update_levels();

      virtual tree_item * get_base_item();

      virtual const tree_item * get_base_item() const;

      virtual tree_item * insert_item(item * pitemdataNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      virtual bool insert_item(tree_item * pitemNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      ::image::image_list * get_image_list() const override;

      virtual void _001ExpandItem(tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(::data::tree_item * pitem);
      virtual void _001SelectItem(::data::tree_item * pitem);

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const;
      virtual bool is_selected(const ::data::tree_item * pitem) const;
      virtual bool is_selected(const ::data::item * pitem) const;

      virtual ::collection::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::collection::index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);


      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void on_fill_children() override;
      //virtual void start_fill_children();

      virtual void on_tree_layout();

      virtual void fill_children();


      //virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace acme

//
//
//inline stream & operator <<(stream & s, const ::data::tree & tree);
//
//inline stream & operator >>(stream & s, ::data::tree & tree);
//
//

