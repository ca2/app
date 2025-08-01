#pragma once


#include "core/user/user/tree_data.h"
#include "apex/message/channel.h"


namespace userfs
{


   class main_impact;


   class CLASS_DECL_CORE tree_data :
      virtual public ::user::tree_data,
      virtual public ::channel
   {
   public:
      

      bool                       m_bCreateImageList;
      bool                       m_bCreateImageListRedraw;
      int                        m_iAnimate;
      bool                       m_bTimer123;
      string_array               m_straUpdatePtrFilter;


      tree_data();
      ~tree_data() override;



      ::core::application* get_app();
      ::core::session* get_session();
      ::core::system* get_system();


#ifdef _DEBUG
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
      virtual long long release() override;
#endif


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void update_list();


      void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;


      ::userfs::document * get_document();


      virtual void on_insert_columns();



      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      virtual void _017OpenFolder(::pointer<::file::item>pitem, const ::action_context & action_context);

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
      void clear(const ::scoped_string & scopedstrPreserve1, const ::scoped_string & scopedstrPreserve2);

      void arrange(::fs::e_arrange earrange);

      void on_timer(::timer * ptimer);


      void RenameFile(int iLine, string & str, const ::action_context & action_context);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnShellCommand);



   };


} // namespace userfs



