#pragma once


#include "impact_base.h"
#include "core/filesystem/userfs/tree_data.h"


namespace filemanager
{


   class CLASS_DECL_CORE tree_data :
      virtual public ::userfs::tree_data,
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



      ::pointer<context_menu>      m_pcontextmenu;


//#ifdef WINDOWS_DESKTOP
//      map < EFolder, IShellFolder * > m_mapFolder;
//#endif


      tree_data();
      ~tree_data();

      
      void destroy() override;


#ifdef _DEBUG


      virtual i64 increment_reference_count() override;
      virtual i64 decrement_reference_count() override;
      virtual i64 release() override;


#endif

      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();


      virtual void initialize_filemanager_tree(document * pdocument);


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual void on_insert_columns() override;

      void _001OnTimer(::timer * ptimer) override;
      virtual void add_path(bool bExpandAscendants, const ::file::path & path, const ::scoped_string & scopedstrName);

      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      //virtual void _017OpenFolder(::pointer<::file::item>pitem, const ::action_context & action_context) override;

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


      void browse_sync(const ::action_context & action_context) override;
      virtual void knowledge(const ::file::path & pathUser, const ::action_context & action_context,bool bOnlyParent);
      virtual void knowledge(const ::file::path& pathUser, const ::action_context& action_context) override;
      //virtual void filemanager_tree_insert(const ::file::path & strPath,::file::listing & listingUser, ::file::listing & listingFinal, const ::action_context & action_context,bool bOnlyParent = false, bool bVoidTreeDataChangeEvent = true);
      void _017EnsureVisible(const ::file::path & pathUser, const ::action_context & action_context);



      void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      void handle(::topic * ptopic, ::context * pcontext) override;


      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnShellCommand);


      virtual void on_merge_user_tree(::user::tree * pusertree) override;
      virtual void on_bind_user_tree(::user::tree * pusertree) override;


   };


} // namespace filemanager



