#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_CORE tree_draw_item
   {
   public:
      __pointer(::data::tree_item)      m_pitem;
      ::draw2d::graphics* m_pdc;
      index                      m_iItem;
      index                      m_iIndentation;
      index                      m_iItemHeight;
      ::rect                     m_rectClient;
      ::rect                     m_rect;
   };





   class CLASS_DECL_CORE tree_data:
      virtual public ::data::tree
   {
   public:


      __pointer_array(::user::tree)       m_usertreea;
      __pointer_array(::user::tree)       m_usertreeaBound;
      __composite(::image_list)           m_pimagelist;



      tree_data();
      virtual ~tree_data();



      virtual ::count           get_data_bound_view_count() const override;
      virtual ::user::impact *  get_data_bound_view(index iView) override;



      virtual void _001OnTreeDataChange() override;

      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context,::user::tree * ptree,const ::point & point);

      ::image_list * get_image_list() const override;

      virtual void _001ExpandItem(::data::tree_item * pitem, const ::action_context & action_context,bool bExpand = true,bool bRedraw = true,bool bLayout = true) override;
      virtual void _001EnsureVisible(::data::tree_item * pitem) override;
      virtual void _001SelectItem(::data::tree_item * pitem) override;

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const override;
      virtual bool is_selected(const ::data::tree_item * pitem) const override;
      virtual bool is_selected(const ::data::item * pitem) const override;

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra) override;
      virtual bool      selection_set(::data::tree_item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      virtual bool      selection_set(::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      virtual bool      selection_set(index iIndex,::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void on_fill_children() override;

      virtual void on_tree_layout() override;

      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);


   };


} // namespace aura



