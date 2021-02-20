#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
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


         ::e_status tree::initialize(::layered * pobjectContext)
         {

            auto estatus = ::user::tree_data::initialize(pobjectContext);

            if (!estatus)
            {

               return estatus;

            }

            __compose_new(m_pimagelist);

            m_pimagelist->create(16, 16);

            m_iIconFolderNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_normal->ico");
            m_iIconFolderSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_folder_selected->ico");
            m_iIconArtistNormal = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_normal->ico");
            m_iIconArtistSelected = m_pimagelist->add_matter_icon("mplite/vmskarlib_artist_selected->ico");

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


         void tree::parse(const char * pszSource)
         {

            string str;

            xml::document doc;

            if(doc.load(pszSource))
            {

               str  = doc.get_xml();

            }
            else
            {

               System.message_box("error"); // simple parsing error check

               return;

            }

            m_iParentFolder = doc.root()->attribute("id");

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

            __pointer(::xml::node) pnodeFolder = doc.root()->get_child("folder");


            //         xml::node::array childs(get_object());

            //         string wstrType;
            // method 3: Selected Childs with GetChilds()
            // Result: Person, Person, Person
            //         index iNode = 0;
            for(i32 i = 0 ; i < pnodeFolder->get_children_count(); i++)
            {

               __pointer(::xml::node) pnodeItem = pnodeFolder->child_at(i);

               ::index iFolder = pnodeItem->attribute("id");

               index iNewItem = m_foldera.find_absolute(iFolder);

               __pointer(folder) pfolder;

               if (iNewItem < 0)
               {

                  pfolder = __new(folder);

                  m_foldera.add(pfolder);

               }
               else
               {

                  pfolder = m_foldera[iFolder];

               }

               pfolder->m_iFolder = iFolder;

               pfolder->m_strName = pnodeItem->attribute("name");

               string strType(pnodeItem->attribute("type"));

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



