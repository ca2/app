#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         class impact;

         enum EFolderType
         {
            FolderTypeNormal,
            FolderTypeArtist,
         };
         
         
         class folder :
            virtual public matter
         {
         public:


            i64            m_iFolder;
            string         m_strName;
            EFolderType    m_etype;
            i32            m_iImage;
            i32            m_iImageSelected;


         };


         class FolderArray :
            public __pointer_array(folder)
         {
         public:


            i32 find_absolute(i64 iFolder);


         };


         class CLASS_DECL_CORE tree :
            virtual public ::user::tree_data
         {
         public:


            i32                                          m_iIconFolderNormal;
            i32                                          m_iIconFolderSelected;
            i32                                          m_iIconArtistNormal;
            i32                                          m_iIconArtistSelected;
            __pointer(::filemanager::fs::simple::impact)   m_pserver;
            FolderArray                                  m_foldera;
            i64                                          m_iParentFolder;


            tree();
            virtual ~tree();


            virtual ::e_status initialize(::object * pobject) override;

            void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;


            void parse(const ::string & pszSource);


            __pointer(::data::tree_item) FindTreeItem(i64 iFolder);
            index _001GetItemImage(__pointer(::data::tree_item) pitem, bool bSelected);


            virtual void assert_valid() const override;
            virtual void dump(dump_context & dumpcontext) const override;


         };


      } // namespace simple


   } // namespace fs


} // namespace filemanager



