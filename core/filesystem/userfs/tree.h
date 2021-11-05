#pragma once


namespace userfs
{


   class main_impact;


   class CLASS_DECL_CORE tree :
      virtual public ::user::tree_data,
      virtual public ::channel
   {
   public:
      

      bool                       m_bCreateImageList;
      bool                       m_bCreateImageListRedraw;
      i32                        m_iAnimate;
      bool                       m_bTimer123;
      string_array               m_straUpdatePtrFilter;


      tree();
      ~tree() override;



      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


#ifdef _DEBUG
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      void update_list();


      void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;


      ::userfs::document * get_document();


      virtual void _001InsertColumns();



      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context);

      virtual ::color::color get_background_color();

      void TakeAnimationSnapshot();
      virtual void StartAnimation(::user::interaction * pinteraction);
      void GetSelectedFilePath(string_array & stra);
      virtual bool _001IsTranslucent();

      virtual void browse_sync(const ::action_context & action_context);
      void _017EnsureVisible(const ::file::path & pathUser, const ::action_context & action_context);

      ::data::tree_item * find_item_by_user_path(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);

      ::data::tree_item * find_absolute(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);
      ::data::tree_item * find_user_path(const ::file::path & pathUser, bool bPointerFromPathFromItemFromOwnTree = false, ::data::tree_item * pitemStart = nullptr);
      void clear(const ::string & pcszPreserve1, const ::string & lpcszPreserve2);

      void arrange(::fs::e_arrange earrange);

      void _001OnTimer(::timer * ptimer);


      void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnShellCommand);



   };


} // namespace userfs



