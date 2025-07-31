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


            long long            m_iFolder;
            string         m_strName;
            EFolderType    m_etype;
            int            m_iImage;
            int            m_iImageSelected;


         };


         class FolderArray :
            public pointer_array < folder >
         {
         public:


            int find_absolute(long long iFolder);


         };


         class CLASS_DECL_CORE tree :
            virtual public ::user::tree_data < ::item>
         {
         public:


            int                                          m_iIconFolderNormal;
            int                                          m_iIconFolderSelected;
            int                                          m_iIconArtistNormal;
            int                                          m_iIconArtistSelected;
            ::pointer<::filemanager::fs::simple::impact>  m_pserver;
            FolderArray                                  m_foldera;
            long long                                          m_iParentFolder;


            tree();
            virtual ~tree();


            virtual void initialize(::particle * pparticle) override;

            void _001OnItemExpand(::data::tree_item_base * ptreeitembase, const ::action_context & action_context) override;


            void parse(const ::scoped_string & scopedstrSource);


            ::pointer<::data::tree_item<::item>> FindTreeItem(long long iFolder);
            ::collection::index _001GetItemImage(::pointer<::data::tree_item<::item>>pitem, bool bSelected);


            // void assert_ok() const override;
            // void dump(dump_context & dumpcontext) const override;


         };


      } // namespace simple


   } // namespace fs


} // namespace filemanager



