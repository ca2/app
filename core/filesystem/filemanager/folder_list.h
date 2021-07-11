#pragma once


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
         i32        m_iImage;


      };


      class FolderArray :
         protected array < Folder, Folder & >
      {
      public:


         void AddFolder(Folder & folder);
         ::count GetFolderCount();
//#ifdef WINDOWS_DESKTOP
//         void clear(LPITEMIDLIST piidlPreserve1, LPITEMIDLIST lpiidlPreserve2);
//
//#endif
         void clear();
         Folder & GetFolder(index i);


      };

      FolderArray                      m_foldera;
      map < ::draw2d::icon *, i32 >    m_iconmap;


      folder_list ();
      virtual ~folder_list ();

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;



      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnCancelMode);


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;



      ::file::item * filemanager_item();

      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      virtual void _001CreateImageList(::user::list_column * column) override;
      virtual void browse_sync(const ::action_context & action_context) override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;
      virtual void _001InsertColumns() override;

      virtual ::color::color get_background_color();

   };


} // namespace filemanager




