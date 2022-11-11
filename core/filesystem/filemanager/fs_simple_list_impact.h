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
            i64     m_iParent;
            i64     m_iFolder;
            string      m_strTitle;
            string      m_strFileName;
            string      m_strExtension;
            i32         m_iId;
            EItemType   m_etype;
            i32         m_iImage;

            bool IsFolder();
         };

         class ItemArray :
            public pointer_array < Item >
         {
         public:
            //i32 FindAbsolute(const ::string & pszId);

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
               ::u32              m_uiTimer;

            };


            class BuildHelper
            {
            public:


               ::index      m_iTopIndex;
               ::count      m_iDisplayItemCount;
               ::index      m_iStep;
               bool                 m_bActive;


               BuildHelper();


            };


            ::pointer<::user::list_cache>                  m_puserlistcache;
            bool                                            m_bKickActive;

            ::pointer<::image_list>                          m_pimagelist;
            index                                   m_iParentFolder;
            ::pointer<::filemanager::fs::simple::impact>     m_pserver;


            i32                                             m_iIconFolder;
            i32                                             m_iIconArtist;
            i32                                             m_iIconSong;
            ItemArray                                       m_itema;

            BuildHelper                                     m_buildhelper;


            list_impact();
            ~list_impact() override;


            // void assert_ok() const override;
            // void dump(dump_context & dumpcontext) const override;


            void install_message_routing(::channel * pchannel) override;



            void fill_task();



            void parse(const ::string & pszSource);

            void start_build(i32 iItem = -1);

            void PostFillTask(string & strFile, uptr uiTimer);

            void _001OnSort() override;
            bool GetSongPath(string & str, index iItem);

            void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;
            void _001InsertColumns() override;
            void _001GetSubItemText(::user::mesh_subitem * psubitem) override;
            count _001GetItemCount() override;
            void _001SearchGetSubItemText(::user::mesh_subitem * psubitem) override;

            virtual void handle(::topic * ptopic, ::context * pcontext) override;

            virtual bool on_click(::item * pitem) override;

            DECLARE_MESSAGE_HANDLER(on_message_create);
            DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
            void _001OnTimer(::timer * ptimer) override;
            DECLARE_MESSAGE_HANDLER(on_message_size);
            DECLARE_MESSAGE_HANDLER(on_message_context_menu);
            DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
            DECLARE_MESSAGE_HANDLER(_001OnFillTaskResponse);

         };


      } // simple


   } // namespace fs


} // namespace filemanager

