#pragma once


namespace userfs
{


   class main_view;


   class CLASS_DECL_CORE tree :
      virtual public ::user::tree_data
   {
   public:
      

      bool                       m_bCreateImageList;
      bool                       m_bCreateImageListRedraw;
      i32                        m_iAnimate;
      bool                       m_bTimer123;
      string_array               m_straUpdatePtrFilter;


      tree();
      virtual ~tree();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      void update_list();

      void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;

      ::userfs::document * get_document();

      virtual void _001InsertColumns();



      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context);

      virtual COLORREF get_background_color();

      void TakeAnimationSnapshot();
      virtual void StartAnimation(::user::interaction * pinteraction);
      void GetSelectedFilePath(string_array & stra);
      virtual bool _001IsTranslucent();

      virtual void browse_sync(const ::action_context & action_context);
      void _017EnsureVisible(const ::file::path & pathUser, const ::action_context & action_context);

      ::data::tree_item * find_item_by_user_path(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);

      ::data::tree_item * find_absolute(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);
      ::data::tree_item * find_user_path(const ::file::path & pathUser, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);
      void clear(const char * pcszPreserve1, const char * lpcszPreserve2);

      void arrange(::fs::e_arrange earrange);

      void _001OnTimer(::timer * ptimer);


      void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      virtual void update(::update * pupdate) override;

      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShellCommand);



   };


} // namespace userfs



