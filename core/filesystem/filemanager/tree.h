#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tree :
      virtual public ::userfs::tree,
      virtual public ::filemanager_impact_base
   {
   public:


      enum e_message
      {

         MessageMainPost,

      };

      enum EMessageMainPost
      {

         MessageMainPostCreateImageListItemRedraw,

      };

      enum e_step
      {
         step_start,
         step_image_visible,
         step_has_subdir_visible,
         step_image_hidden,
         step_has_subdir_hidden,
         step_end,
      };



      context_menu            m_contextmenu;


//#ifdef WINDOWS_DESKTOP
//      map < EFolder, IShellFolder * > m_mapFolder;
//#endif


      tree();
      virtual ~tree();


#ifdef _DEBUG


      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif

      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


      virtual void initialize_filemanager_tree(document * pdocument);


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual void _001InsertColumns() override;

      void _001OnTimer(::timer * ptimer) override;


      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context) override;

//#ifdef WINDOWS_DESKTOP
//
//      i32 MapToCSIDL(EFolder efolder);
//
//      IShellFolder * _001GetFolder(EFolder efolder);
//
//#endif


      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      DECLARE_MESSAGE_HANDLER(_001OnMainPostMessage);
      void GetSelectedFilePath(string_array & stra);
      virtual bool _001IsTranslucent() override;


      virtual void browse_sync(const ::action_context & action_context) override;
      virtual void knowledge(const ::file::path & pathUser, const ::action_context & action_context,bool bOnlyParent);
      virtual void knowledge(const ::file::path& pathUser, const ::action_context& action_context) override;
      //virtual void filemanager_tree_insert(const ::file::path & strPath,::file::listing & listingUser, ::file::listing & listingFinal, const ::action_context & action_context,bool bOnlyParent = false, bool bVoidTreeDataChangeEvent = true);
      void _017EnsureVisible(const ::file::path & pathUser, const ::action_context & action_context);



      void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      virtual void handle(::topic * psubject, ::context * pcontext) override;


      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnShellCommand);


      virtual void on_merge_user_tree(::user::tree * pusertree) override;
      virtual void on_bind_user_tree(::user::tree * pusertree) override;


   };


} // namespace filemanager



