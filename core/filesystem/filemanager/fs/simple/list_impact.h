#pragma once


#include "core/user/simple/list_impact.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {

         class impact;

         enum EItemType
         {
            ItemTypeFolder,
            ItemTypeArtist,
            ItemTypeSong,
         };
         class Item :
            virtual public object
         {
         public:
            huge_integer     m_iParent;
            huge_integer     m_iFolder;
            string      m_strTitle;
            string      m_strFileName;
            string      m_strExtension;
            int         m_iId;
            EItemType   m_etype;
            int         m_iImage;

            bool IsFolder();
         };

         class ItemArray :
            public pointer_array < Item >
         {
         public:
            //int FindAbsolute(const ::string & pszId);

         };


         class CLASS_DECL_CORE list_impact :
            public simple_list_impact
         {
         public:



            enum EFieldIndex
            {
               FieldIndexNone = -1,
               FieldIndexId = 0,
               FieldIndexTitle,
               FieldIndexArtist,
               FieldIndexFileName,
               FieldIndexFilePath,
            };

            enum ESubItem
            {
               SubItemId,
               SubItemTitle,
               SubItemArtist,
               SubItemFileName,
               SubItemFilePath,
            };


            class FillTask
            {
            public:

               string             m_strFile;
               unsigned int              m_uiTimer;

            };


            class BuildHelper
            {
            public:


               ::collection::index      m_iTopIndex;
               ::collection::count      m_iDisplayItemCount;
               ::collection::index      m_iStep;
               bool                 m_bActive;


               BuildHelper();


            };


            ::pointer<::user::list_cache>                  m_puserlistcache;
            bool                                            m_bKickActive;

            ::image::image_list_pointer                           m_pimagelist;
            ::collection::index                                   m_iParentFolder;
            ::pointer<::filemanager::fs::simple::impact>     m_pserver;


            int                                             m_iIconFolder;
            int                                             m_iIconArtist;
            int                                             m_iIconSong;
            ItemArray                                       m_itema;

            BuildHelper                                     m_buildhelper;


            list_impact();
            ~list_impact() override;


            // void assert_ok() const override;
            // void dump(dump_context & dumpcontext) const override;


            void install_message_routing(::channel * pchannel) override;



            void fill_task();



            void parse(const ::string & pszSource);

            void start_build(int iItem = -1);

            void PostFillTask(string & strFile, uptr uiTimer);

            void _001OnSort() override;
            bool GetSongPath(string & str, ::collection::index iItem);

            void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;
            void on_insert_columns() override;
            void _001GetSubItemText(::user::mesh_subitem * psubitem) override;
            ::collection::count _001GetItemCount() override;
            void _001SearchGetSubItemText(::user::mesh_subitem * psubitem) override;

            void handle(::topic * ptopic, ::context * pcontext) override;

            bool on_click(::item * pitem, ::user::mouse * pmouse) override;

            DECLARE_MESSAGE_HANDLER(on_message_create);
            DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
            void on_timer(::timer * ptimer) override;
            DECLARE_MESSAGE_HANDLER(on_message_size);
            DECLARE_MESSAGE_HANDLER(on_message_context_menu);
            DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
            DECLARE_MESSAGE_HANDLER(_001OnFillTaskResponse);

         };


      } // simple


   } // namespace fs


} // namespace filemanager

