#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {

         class view;

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
            public __pointer_array(Item)
         {
         public:
            //i32 FindAbsolute(const char * pszId);

         };


         class CLASS_DECL_CORE list_view :
            public simple_list_view
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


            __pointer(::user::list_cache)                   m_puserlistcache;
            bool                                            m_bKickActive;

            __pointer(::image_list)                           m_pil;
            index                                   m_iParentFolder;
            __pointer(::filemanager::fs::simple::view)      m_pserver;


            i32                                             m_iIconFolder;
            i32                                             m_iIconArtist;
            i32                                             m_iIconSong;
            ItemArray                                       m_itema;

            BuildHelper                                     m_buildhelper;


            list_view();
            virtual ~list_view();


            virtual void assert_valid() const override;
            virtual void dump(dump_context & dumpcontext) const override;


            void install_message_routing(::channel * pchannel) override;



            void fill_task();



            void parse(const char * pszSource);

            void start_build(i32 iItem = -1);

            void PostFillTask(string & strFile, uptr uiTimer);

            virtual void _001OnSort() override;
            bool GetSongPath(string & str, index iItem);

            virtual void _001GetItemImage(::user::mesh_item * pitem) override;
            virtual void _001InsertColumns() override;
            virtual void _001GetItemText(::user::mesh_item * pitem) override;
            virtual count _001GetItemCount() override;
            virtual void _001SearchGetItemText(::user::mesh_item * pitem) override;

            virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

            virtual bool on_click(const ::user::item & item) override;

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

