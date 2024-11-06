#pragma once


#include "core/filesystem/filemanager/impact_base.h"
#include "core/user/user/list.h"


namespace filemanager
{


   class CLASS_DECL_CORE folder_list :
      virtual public ::filemanager_show < ::user::show < ::user::list > >
   {
   public:


      enum EMode
      {
         ModeNormal, // a bit ridiculous that folder list
         ModeConfigurationItem,
      };


      class Folder
      {
      public:


         string         m_strFolderPath;
         string         m_strName;
         int        m_iImage;


      };


      class FolderArray :
         protected array < Folder, Folder & >
      {
      public:


         void AddFolder(Folder & folder);
         ::collection::count GetFolderCount();
//#ifdef WINDOWS_DESKTOP
//         void clear(LPITEMIDLIST piidlPreserve1, LPITEMIDLIST lpiidlPreserve2);
//
//#endif
         void clear();
         Folder & GetFolder(::collection::index i);


      };

      FolderArray                      m_foldera;
      map < ::image::icon *, int >    m_iconmap;


      folder_list ();
      virtual ~folder_list ();

      void install_message_routing(::channel * pchannel) override;
      void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;



      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnCancelMode);


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;



      ::file::item * filemanager_item();

      virtual void _001CreateImageList(::user::list_column * column) override;
      virtual void browse_sync(const ::action_context & action_context) override;

      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;
      void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;


      virtual ::collection::count _001GetItemCount() override;
      virtual void on_insert_columns() override;

      virtual ::color::color get_background_color();

   };


} // namespace filemanager




