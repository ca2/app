#pragma once


#include "core/user/user/tree_data.h"


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
            public pointer_array < folder >
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
            ::pointer<::filemanager::fs::simple::impact>  m_pserver;
            FolderArray                                  m_foldera;
            i64                                          m_iParentFolder;


            tree();
            virtual ~tree();


            virtual void initialize(::particle * pparticle) override;

            void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;


            void parse(const ::string & pszSource);


            ::pointer<::data::tree_item>FindTreeItem(i64 iFolder);
            ::collection::index _001GetItemImage(::pointer<::data::tree_item>pitem, bool bSelected);


            // void assert_ok() const override;
            // void dump(dump_context & dumpcontext) const override;


         };


      } // namespace simple


   } // namespace fs


} // namespace filemanager



