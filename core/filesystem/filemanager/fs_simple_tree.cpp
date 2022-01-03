#include "framework.h"
#include "aura/graphics/draw2d/image_list.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "_data.h"
#include "aqua/xml.h"
#include "core/user/user/_tree.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         tree::tree()
         {

         }


         tree::~tree()
         {

         }


         ::e_status tree::initialize(::object * pobject)
         {

            auto estatus = ::user::tree_data::initialize(pobject);

            if (!estatus)
            {

               return estatus;

            }

            __compose_new(m_pimagelist);

            m_pimagelist->create(16, 16);

//#ifdef WINDOWS
//
//            m_iIconFolderNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_normal.ico");
//            m_iIconFolderSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_selected.ico");
//            m_iIconArtistNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_normal.ico");
//            m_iIconArtistSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_selected.ico");
//
//#endif

            m_iIconFolderNormal = m_pimagelist->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_folder_normal"));
            m_iIconFolderSelected = m_pimagelist->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_folder_selected"));
            m_iIconArtistNormal = m_pimagelist->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_artist_normal"));
            m_iIconArtistSelected = m_pimagelist->add(icon_payload(this, "icon://app-veriwell/musical_player_lite/karaoke_library_artist_selected"));
            return estatus;

         }


         void tree::assert_valid() const
         {

            ::data::tree::assert_valid();

         }


         void tree::dump(dump_context & dumpcontext) const
         {

            ::data::tree::dump(dumpcontext);

         }


         void tree::parse(const ::string & pszSource)
         {

            string str;

            auto pxmldocument = __create_new < ::xml::document >();

            if(pxmldocument->load(pszSource))
            {

               str  = pxmldocument->get_xml();

            }
            else
            {

               output_error_message("error"); // simple parsing error check

               return;

            }

            pxmldocument->root()->attribute("id").as(m_iParentFolder);

            __pointer(::data::tree_item) ptreeitemParent;

            __pointer(::data::tree_item) ptreeitemChild;

            ptreeitemParent = FindTreeItem(m_iParentFolder);

            if(ptreeitemParent == nullptr)
            {

               ptreeitemParent = get_base_item();

            }

            xml::node::array childs;

            string wstrType;

            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            index iNode = 0;

            auto pnodeFolder = pxmldocument->root()->get_child("folder");


            //         xml::node::array childs(this);

            //         string wstrType;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            //         index iNode = 0;
            for(i32 i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {

               auto pnodeItem = pnodeFolder->child_at(i);

               auto iFolder = pnodeItem->attribute("id").iptr();

               index iNewItem = m_foldera.find_absolute(iFolder);

               __pointer(folder) pfolder;

               if (iNewItem < 0)
               {

                  pfolder = __create_new<folder>();

                  m_foldera.add(pfolder);

               }
               else
               {

                  pfolder = m_foldera[iFolder];

               }

               pfolder->m_iFolder = iFolder;

               pfolder->m_strName = pnodeItem->attribute("name");

               string strType(pnodeItem->attribute("type").get_string());

               if(strType == "normal")
               {

                  pfolder->m_etype = FolderTypeNormal;

               }
               else if(strType == "artist")
               {

                  pfolder->m_etype = FolderTypeArtist;

               }
               else
               {

                  // unknown folder type
                  ASSERT(false);

               }

               switch(pfolder->m_etype)
               {
               case FolderTypeNormal:
                  pfolder->m_iImage = m_iIconFolderNormal;
                  pfolder->m_iImageSelected = m_iIconFolderSelected;
                  break;
               case FolderTypeArtist:
                  pfolder->m_iImage = m_iIconArtistNormal;
                  pfolder->m_iImageSelected = m_iIconArtistSelected;
                  break;
               default:
                  // unknown folder type
                  break;

               }

               ptreeitemChild = ptreeitemParent->get_child_by_user_data((uptr) iNewItem);

               if(ptreeitemChild)
               {

                  ptreeitemChild = insert_item(__new(::data::simple_item(this)), ::data::RelativeLastChild, ptreeitemParent);

               }

               if(!ptreeitemChild->m_pdataitem)
               {

                  ptreeitemChild->m_pdataitem = __new(::data::simple_item(this));

               }

               ptreeitemParent->m_pdataitem.cast < ::data::simple_item >()->m_str = pfolder->m_strName;

               ptreeitemParent->m_dwUser = (uptr) iNewItem;

               iNode++;

            }

         }


         __pointer(::data::tree_item) tree::FindTreeItem(i64 iFolder)
         {
            i32 iUser;

            if (iFolder < 0)
            {

               return nullptr;

            }

            iUser = m_foldera.find_absolute(iFolder);

            if(iUser >= 0)
            {

               return get_base_item()->find_next_by_user_data(iUser);

            }

            return nullptr;

         }


         i32 FolderArray::find_absolute(i64 iFolder)
         {

            for(i32 i = 0; i < this->get_size(); i++)
            {

               if (this->element_at(i)->m_iFolder == iFolder)
               {

                  return i;

               }

            }

            return -1;

         }


         index tree::_001GetItemImage(__pointer(::data::tree_item) pitem, bool bSelected)
         {

            if(bSelected)
            {

               return m_foldera.element_at(pitem->m_dwUser)->m_iImageSelected;

            }
            else
            {

               return m_foldera.element_at(pitem->m_dwUser)->m_iImage;

            }

         }


         void tree::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
         {

            m_pserver->open_folder(m_foldera[pitem->m_dwUser]->m_iFolder);

         }


      } // namespace simple


   } // namespace library


} // namespace mplite



