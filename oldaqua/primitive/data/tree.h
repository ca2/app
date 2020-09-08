#pragma once



namespace data
{


   class CLASS_DECL_AQUA tree :
      virtual public ::data::data,
      virtual public tree_item
   {
   public:


      __pointer_array(tree)                    m_treea;
      __pointer(tree_item)                m_proot;
      bool                                m_bFill;
      index_array                         m_iaLevelNext;


      tree();
      virtual ~tree();

      virtual void on_insert_tree(tree * ptree);

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }


      virtual void remove_all();

      virtual void update_tree();

      virtual tree_item * find(const item * pitem, index * piIndex = nullptr);
      virtual bool contains(const item * pitem);

      virtual bool contains(const tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context, ::user::primitive * ptree, const ::point & point);

      virtual void remove(tree_item_ptr_array & itemptra);
      virtual void remove(tree_item * pitem);
      virtual void remove(item * pitem, index i = 0);



      template < typename PRED >
      void sort_children(PRED pred)
      {

         tree_sort(m_proot, pred);

      }


      virtual tree_item * _get_proper_item(index iIndex, index * piLevel, index * piCount = nullptr);
      virtual tree_item* get_proper_item(index iIndex, index* piLevel) override;
      virtual index get_proper_item_index(tree_item * pitemParam, index * piLevel, index * piCount = nullptr);
      virtual ::count get_proper_item_count() override;

      virtual void update_levels();

      virtual tree_item * get_base_item();

      virtual const tree_item * get_base_item() const;

      virtual tree_item * insert_item(item * pitemdataNew, ERelative erelativeNewItem = RelativeLastChild, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      virtual bool insert_item(tree_item * pitemNew, ERelative erelativeNewItem = RelativeLastChild, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      image_list * get_image_list() const override;

      virtual void _001ExpandItem(tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(::data::tree_item * pitem);
      virtual void _001SelectItem(::data::tree_item * pitem);

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const;
      virtual bool is_selected(const ::data::tree_item * pitem) const;
      virtual bool is_selected(const ::data::item * pitem) const;

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual void update(::update * pupdate) override;


      virtual void on_fill_children() override;
      virtual void start_fill_children();

      virtual void fill_children();


      virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace aqua



inline stream & operator <<(stream & s, const ::data::tree & tree);

inline stream & operator >>(stream & s, ::data::tree & tree);



