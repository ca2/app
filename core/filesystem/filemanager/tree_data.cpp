#include "framework.h"
#include "tree_data.h"
#include "document.h"
#include "data.h"
#include "context_menu.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "acme/platform/timer.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/set.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/list.h"
#include "aura/user/user/shell.h"
#include "aura/template/list.h"
#include "base/user/user/user.h"
#include "aura/message/user.h"
#include "aura/windowing/window.h"
#include "core/filesystem/userfs/item.h"
#include "core/user/user/tree.h"


template < typename LIST_ITEM >
void check_list(LIST_ITEM * plist)
{

#ifdef DEBUG

   if (::is_null(plist->m_ptail))
   {
      if (::is_set(plist->m_phead))
      {

         throw "error";

      }

   }
   else if (::is_null(plist->m_phead))
   {

      throw "error";

   }

   auto p = plist->m_phead;

   while(true)
   {

      if (is_null(p->m_pdataitem))
      {

         throw "error";

      }

      if (p == plist->m_ptail)
      {

         break;

      }

      p = p->m_pnext;

   } 

   auto p2 = plist->m_ptail;

   while (true)
   {

      if (is_null(p->m_pdataitem))
      {

         throw "error";

      }

      if (p == plist->m_phead)
      {

         break;

      }

      p = p->m_pprevious;

   }

#endif


}

namespace filemanager
{


   tree_data::tree_data()
   {

   }


   tree_data::~tree_data()
   {

   }


   void tree_data::destroy()
   {

      ::userfs::tree_data::destroy();
      ::filemanager_impact_base::destroy();


   }


   // ::core::application* tree_data::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* tree_data::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return pacmesession ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* tree_data::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


#ifdef _DEBUG


   long long tree_data::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long tree_data::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


   long long tree_data::release()
   {

      return ::object::release();

   }

#endif


   void tree_data::initialize_filemanager_tree(document * pdocument)
   {

      //auto estatus = 
      
      initialize_impact(pdocument);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      pdocument->add_data(this);

      //m_pdatacontainerbase = pdocument;

      defer_create_synchronization();

      m_iAnimate = 0;

      auto puser = user();

      m_pimagelist = puser->shell()->GetImageList(16);

      //return estatus;

   }


   void tree_data::_017EnsureVisible(const ::file::path & pathUser, const ::action_context & context)
   {

      synchronous_lock synchronouslock(m_usertreea.has_elements() ? m_usertreea[0]->synchronization() : nullptr);

      string_array stra;

      auto pitem = find_item_by_user_path(pathUser);

      if (!pitem)
      {

         return;

      }

      if(!(pitem->m_dwState & ::data::e_tree_item_state_expanded))
      {

         _001ExpandItem(pitem,context,true,false,false);

      }

      m_straUpdatePtrFilter.erase_all();

      _001EnsureVisible(pitem);

   }


   void tree_data::knowledge(const ::file::path& pathUser, const ::action_context& context)
   {

      knowledge(pathUser, context, false);

   }


   void tree_data::knowledge(const ::file::path & pathUser, const ::action_context & context,bool bOnlyParent)
   {

      if (bOnlyParent && pathUser.has_character() && find_item_by_user_path(pathUser))
      {

         return;

      }

      auto pitemParent = find_item_by_user_path(pathUser);

      ::file::listing listing;

      ::file::listing listingFinal;

      ::file::path strDir;

      auto papp = get_app();

      auto pcontext = m_papplication;
      
      bool bRoot = false;

      if(bOnlyParent && pathUser.has_character())
      {

         strDir = pathUser.folder();

         auto & path = listing.add_get(pathUser);

         path.set_existent_folder();
         
      }
      else if (pathUser.is_empty())
      {

         filemanager_data()->fs_data()->root_ones(listing);
         
         bRoot = true;

      }
      else
      {

         strDir = pathUser;

         listing.set_listing(pathUser);

         directory()->enumerate(listing);

      }

      for (::collection::index i = 0; i < listing.size(); i++)
      {

         ::string strTitle;
         
         if (i < listing.m_straTitle.size())
         {

            strTitle = listing.m_straTitle[i];

         }

         auto & item = listing[i];

         ::file::path pathFinal = m_papplication->defer_process_matter_path(item);

         if(pathFinal.is_folder())
         {

            auto pathUser = pitemParent->m_pdataitem.cast <::file::item>()->user_path() /
               item.name();
            //listingFinal.defer_add(pathFinal);

            if (strTitle.is_empty())
            {

               strTitle = pathUser.name();

               if (strTitle.is_empty())
               {

                  strTitle = pathUser;

               }

            }

            add_path(!bRoot, pathUser, strTitle);

         }

      }

      //filemanager_tree_insert(strDir, listing, listingFinal, context, bOnlyParent);

      auto pitem = find_item_by_user_path(pathUser);

      if(pitem != nullptr)
      {

         if(listing.has_elements())
         {

            pitem->m_dwState |= ::data::e_tree_item_state_expanded;

            pitem->m_dwState |= ::data::e_tree_item_state_expandable;

         }

      }

      if(!bOnlyParent)
      {

         arrange(::fs::arrange_by_name);

      }

      m_usertreea.predicate_each([](auto & ptree)
      {

         ptree->set_need_layout();

      });

   }


   void tree_data::browse_sync(const ::action_context & context)
   {
      
      // add root items

      {

         ::file::listing & listing = filemanager_data()->m_listingRoot2;

         for (::collection::index i = 0; i < listing.size(); i++)
         {

            ::string strTitle = listing.m_straTitle[i];

            auto & item = listing[i];

            if (strTitle.is_empty())
            {

               strTitle = item.name();

               if (strTitle.is_empty())
               {

                  strTitle = item;

               }

            }

            add_path(false, item, strTitle);

         }

      }

      // add folder ascendants

      {

         add_path(true, filemanager_item()->user_path(), "");

      }

      // add sibling folders

      {

         ::file::listing & listingUser = filemanager_data()->m_listingFolderUser2;

         for (auto & path : listingUser)
         {

            add_path(true, path, "");

         }

      }

      //auto pparticleSynchronization = m_usertreea.has_elements() ? m_usertreea[0]->synchronization() : nullptr;

      //synchronous_lock synchronouslock(pparticleSynchronization);

      //// auto pcontext = get_context();

      //auto pointOffset = get_context_offset();

      //::file::path pathUser = filemanager_path();

      //// Add parent path ascendant tree_data items
      //{

      //   ::file::path path = filemanager_path();

      //   ::pointer<::userfs::item>pitemChild;

      //   if (directory()->is(pathUser))
      //   {

      //      ::data::tree_item * ptreeitemParent = get_base_item();

      //      ::file::path_array patha;

      //      ascendants_path(pathUser, patha);

      //      for (auto & pathAscendant : patha)
      //      {

      //         ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathAscendant);

      //         string strName;

      //         strName = pcontext->defer_get_file_title(pathAscendant);

      //         if (pathAscendant.has_character() && strName.has_character())
      //         {

      //            if (ptreeitemChild == nullptr)
      //            {

      //               pitemChild = __allocate ::userfs::item(this);

      //               pitemChild->set_user_path(pathAscendant);

      //               pitemChild->set_final_path(m_papplication->defer_process_matter_path(pathAscendant));

      //               pitemChild->m_strName = strName;

      //               pitemChild->m_flags.add(::file::e_flag_folder);

      //               ptreeitemChild = insert_item(pitemChild, ::data::e_relative_last_child, ptreeitemParent);

      //               if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
      //               {

      //                  ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

      //               }

      //            }
      //            else
      //            {

      //               ptreeitemChild->set_parent(ptreeitemParent);

      //            }

      //         }

      //         ptreeitemParent = ptreeitemChild;

      //      }

      //   }

      //}

      //// Add child folder-like tree_data items
      //{

      //   ::file::path path = filemanager_path();

      //   //::data::tree_item * ptreeitemChild;

      //   ::data::tree_item * ptreeitemParent = find_item_by_user_path(pathUser);

      //   if (ptreeitemParent == nullptr)
      //   {

      //      ptreeitemParent = get_base_item();

      //   }

      //   ::file::listing & listingUser = filemanager_data()->m_listingFolderUser2;

      //   ::file::listing & listingFinal = filemanager_data()->m_listingFolderFinal2;

      //   pointer_array < ::data::tree_item > childrenNew;

      //   auto cListingUser = listingUser.get_count();

      //   for(::collection::index i = 0; i < cListingUser; i++)
      //   {

      //      ::file::path pathUser = listingUser[i];

      //      ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathUser);

      //      if (ptreeitemChild.is_null())
      //      {

      //         ptreeitemChild = __allocate ::data::tree_item();

      //         ptreeitemChild->m_ptree = this;

      //         ptreeitemChild->m_pparent = ptreeitemParent;

      //      }
      //      else
      //      {

      //         ptreeitemChild->set_parent(ptreeitemParent);

      //      }

      //      ::file::path pathFinal = listingFinal[i];

      //      string strName;

      //      strName = pcontext->defer_get_file_title(pathUser);

      //      auto pitemChild = ptreeitemChild->m_pdataitem.cast < ::userfs::item >();

      //      if (!pitemChild)
      //      {

      //         pitemChild = __allocate ::userfs::item(this);

      //         ptreeitemChild->m_pdataitem = pitemChild;

      //      }

      //      pitemChild->set_user_path(pathUser);

      //      pitemChild->set_final_path(m_papplication->defer_process_matter_path(pathFinal));

      //      pitemChild->m_strName = strName;

      //      pitemChild->m_flags.add(::file::e_flag_folder);

      //      if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
      //      {

      //         ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

      //      }

      //      childrenNew.add_unique(ptreeitemChild);

      //   }

      //   if (childrenNew.get_count() <= 80)
      //   {

      //      list_set_children(ptreeitemParent, childrenNew);

      //   }

      //}


      //// Add root immediate children folder-like tree_data items
      //{

      //   // ::file::path path = filemanager_path();

      //   //::data::tree_item * ptreeitemChild;

      //   auto ptreeitemParent = get_base_item();

      //  pointer_array < ::data::tree_item > childrenNew;

      //   auto cListingUser = listingUser.get_count();

      //   for (::collection::index i = 0; i < cListingUser; i++)
      //   {

      //      ::file::path pathUser = listingUser[i];

      //      ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathUser);

      //      if (ptreeitemChild.is_null())
      //      {

      //         ptreeitemChild = __allocate ::data::tree_item();

      //         ptreeitemChild->m_ptree = this;

      //         ptreeitemChild->m_pparent = ptreeitemParent;

      //      }
      //      else
      //      {

      //         ptreeitemChild->set_parent(ptreeitemParent);

      //      }

      //      string strName;

      //      strName = pcontext->defer_get_file_title(pathUser);

      //      auto pitemChild = ptreeitemChild->m_pdataitem.cast < ::userfs::item >();

      //      if (!pitemChild)
      //      {

      //         pitemChild = __allocate ::userfs::item(this);

      //         ptreeitemChild->m_pdataitem = pitemChild;

      //      }

      //      pitemChild->set_user_path(pathUser);

      //      //pitemChild->set_final_path(m_papplication->defer_process_matter_path(pathFinal));

      //      pitemChild->m_strName = strName;

      //      pitemChild->m_flags.add(::file::e_flag_folder);

      //      if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
      //      {

      //         ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

      //      }

      //      childrenNew.add_unique(ptreeitemChild);

      //   }

      //   if (childrenNew.get_count() <= 80)
      //   {

      //      list_set_children(ptreeitemParent, childrenNew);

      //   }

      //}

//      {
//
//         if (!context.is_user_source())
//         {
//
//            //knowledge("", context, true);
//
//            if (pathUser.has_character())
//            {
//
//               ::file::path_array filepatha;
//
//               ascendants_path(pathUser, filepatha);
//
//               for (::collection::index i = 0; i < filepatha.get_size(); i++)
//               {
//
//                  ::file::path pathUser = filepatha[i];
//
//                  knowledge(pathUser, context, true);
//
//               }
//
//            }
//
//         }
//
//         //if (get_document() != nullptr && get_document()->m_ptreeFileTreeMerge != nullptr
//         //      && !(dynamic_cast <::user::tree_data *> (get_document()->m_ptreeFileTreeMerge))->m_ptree->contains(this))
//         //{
//
//         //   get_document()->m_ptreeFileTreeMerge->m_ptreedata->insert_item(this, ::data::e_relative_first_child);
//
//         //}
//
//      }
//
//      {
//
//         string_array straChildItem;
//
//         string str;
//
//         //::file::listing & listingUser = ::userfs::tree_data::filemanager_data()->m_listingFolderUser2;
//
//         //::file::listing & listingFinal = ::userfs::tree_data::filemanager_data()->m_listingFolderFinal2;
//
//         if (!context.is(::e_source_system))
//         {
//
//            //filemanager_tree_insert(filepath, listingUser, listingFinal, context, true);
//
//            _017EnsureVisible(pathUser, context);
//
//            ::pointer<::data::tree_item>ptreeitem = find_item_by_user_path(pathUser);
//
//            _001SelectItem(ptreeitem);
//
//            auto iMaxLevel = ptreeitem ? ptreeitem->m_iLevel + 2 : -1;
//
//            // erase level 3 with that aren't expanded.
//
//            while (ptreeitem)
//            {
//
//               ::pointer<::data::tree_item>ptreeitemNext = ptreeitem->get_child_next_or_parent();
//
//               if (ptreeitem->m_iLevel >= iMaxLevel && !ptreeitem->is_expanded())
//               {
//
//                  list_erase_all(ptreeitem);
//
//                  if(::is_set(ptreeitem->m_pparent))
//                  {
//
//                     list_erase(ptreeitem->m_pparent, ptreeitem);
//
//                  }
//
//               }
//
//               ptreeitem = ptreeitemNext;
//
//            }
//
//            _001OnTreeDataChange();
//
//         }
//
//         arrange(::fs::arrange_by_name);
//
//         //if (m_usertreea.has_elements())
//         //{
//
//         //   _polishing_start(m_usertreea[0]);
//
//         //}
//
//      }
//
//      //queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
//        // {
//
////            set_context_offset(pgraphics, pointOffset.x(), pointOffset.y());
//
//         //});
//
      //set_context_offset(pointOffset);

auto path = filemanager_data()->m_pitem->user_path();
auto pchild = find_item_by_user_path(path);
_001SelectItem(pchild);

      auto puser = user();

      if (::is_null(m_pimagelist))
      {

         m_pimagelist = puser->shell()->GetImageList(get_document()->m_iIconSize);

      }

      m_usertreea.predicate_each([](auto & ptree)
      {

         ptree->set_need_layout();

      });

   }


   void tree_data::on_insert_columns()
   {

   }


   void tree_data::add_path(bool bExpandAscendants, const ::file::path & pathAdd, const ::scoped_string & scopedstrName)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::file::path_array patha;
      
      if(bExpandAscendants)
      {
         
         ascendants_path(pathAdd, patha);
         
         information() << "tree_data::add_path expanding ascendants of : " << pathAdd;
         
      }
      else
      {
         
         patha.add(pathAdd);
         
         information() << "tree_data::add_path gonna try add : " << pathAdd;

      }

      auto pparent = get_base_item();

      for (::collection::index i = 0; i < patha.get_size(); i++)
      {

         auto & path = patha[i];
         
         ::file::path pathFinal = m_papplication->defer_process_path(path);

         if(bExpandAscendants && (filemanager_data()->m_listingRoot2.find_first_contains(path) >= 0
         || filemanager_data()->m_listingRoot2.find_first_contains(pathFinal) >= 0)
            )
         {
          
            pparent = find_item_by_user_path(path);
            
            continue;
            
         }
         
         information() << "user path : " << path;
         
         information() << "final path : " << pathFinal;

         auto pchild = find_item_by_user_path(path);

         if (!pchild)
         {

            auto pitemNew = __allocate ::userfs::item(this);

            pitemNew->set_user_path(path);

            pitemNew->set_final_path(pathFinal);

            if (filemanager_data()->fs_data()->is_dir(pitemNew->final_path()))
            {

               pitemNew->m_flags |= ::file::e_flag_folder;

            }

            if (i == patha.get_upper_bound() && scopedstrName.has_character())
            {

               pitemNew->m_strName = scopedstrName;

            }
            else
            {

               pitemNew->m_strName = path.name();

            }

            pchild = insert_item(pitemNew, ::data::e_relative_last_child, pparent);

            if (filemanager_data()->fs_data()->fast_has_subdir(pitemNew->final_path()))
            {

               pchild->m_dwState |= ::data::e_tree_item_state_expandable;

            }

         }

         pparent = pchild;

      }


      for (::collection::index i = patha.get_upper_bound(); i >= 0; i--)
      {

         auto & path = patha[i];

         auto p = find_item_by_user_path(path);

         if (p)
         {

            p->sort_children([](auto p1, auto p2)
               {

                     auto pfileitem1 = p1->m_pdataitem.template cast < ::file::item>();

                     auto pfileitem2 = p2->m_pdataitem.template cast < ::file::item>();

                  /*   if (::is_null(pfileitem1))
                     {

                        if (::is_null(pfileitem2))
                        {

                           return false;

                        }
                        else
                        {

                           return true;
                        }
                     }
                     else if (::is_null(pfileitem2))
                     {

                        return false;

                     }*/


                     return pfileitem1->m_strName
                        .case_insensitive_order(pfileitem2->m_strName) < 0;

   });
         }

      }


   //auto pparticleSynchronization = m_usertreea.has_elements() ? m_usertreea[0]->synchronization() : nullptr;

   //synchronous_lock synchronouslock(pparticleSynchronization);

   //// auto pcontext = get_context();

   //auto pointOffset = get_context_offset();

   //::file::path pathUser = filemanager_path();

   //// Add parent path ascendant tree_data items
   //{

   //   ::file::path path = filemanager_path();

   //   ::pointer<::userfs::item>pitemChild;

   //   if (directory()->is(pathUser))
   //   {

   //      ::data::tree_item * ptreeitemParent = get_base_item();

   //      ::file::path_array patha;

   //      ascendants_path(pathUser, patha);

   //      for (auto & pathAscendant : patha)
   //      {

   //         ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathAscendant);

   //         string strName;

   //         strName = pcontext->defer_get_file_title(pathAscendant);

   //         if (pathAscendant.has_character() && strName.has_character())
   //         {

   //            if (ptreeitemChild == nullptr)
   //            {

   //               pitemChild = __allocate ::userfs::item(this);

   //               pitemChild->set_user_path(pathAscendant);

   //               pitemChild->set_final_path(m_papplication->defer_process_matter_path(pathAscendant));

   //               pitemChild->m_strName = strName;

   //               pitemChild->m_flags.add(::file::e_flag_folder);

   //               ptreeitemChild = insert_item(pitemChild, ::data::e_relative_last_child, ptreeitemParent);

   //               if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
   //               {

   //                  ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

   //               }

   //            }
   //            else
   //            {

   //               ptreeitemChild->set_parent(ptreeitemParent);

   //            }

   //         }

   //         ptreeitemParent = ptreeitemChild;

   //      }

   //   }

   //}

   //// Add child folder-like tree_data items
   //{

   //   ::file::path path = filemanager_path();

   //   //::data::tree_item * ptreeitemChild;

   //   ::data::tree_item * ptreeitemParent = find_item_by_user_path(pathUser);

   //   if (ptreeitemParent == nullptr)
   //   {

   //      ptreeitemParent = get_base_item();

   //   }

   //   ::file::listing & listingUser = filemanager_data()->m_listingFolderUser2;

   //   ::file::listing & listingFinal = filemanager_data()->m_listingFolderFinal2;

   //   pointer_array < ::data::tree_item > childrenNew;

   //   auto cListingUser = listingUser.get_count();

   //   for(::collection::index i = 0; i < cListingUser; i++)
   //   {

   //      ::file::path pathUser = listingUser[i];

   //      ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathUser);

   //      if (ptreeitemChild.is_null())
   //      {

   //         ptreeitemChild = __allocate ::data::tree_item();

   //         ptreeitemChild->m_ptree = this;

   //         ptreeitemChild->m_pparent = ptreeitemParent;

   //      }
   //      else
   //      {

   //         ptreeitemChild->set_parent(ptreeitemParent);

   //      }

   //      ::file::path pathFinal = listingFinal[i];

   //      string strName;

   //      strName = pcontext->defer_get_file_title(pathUser);

   //      auto pitemChild = ptreeitemChild->m_pdataitem.cast < ::userfs::item >();

   //      if (!pitemChild)
   //      {

   //         pitemChild = __allocate ::userfs::item(this);

   //         ptreeitemChild->m_pdataitem = pitemChild;

   //      }

   //      pitemChild->set_user_path(pathUser);

   //      pitemChild->set_final_path(m_papplication->defer_process_matter_path(pathFinal));

   //      pitemChild->m_strName = strName;

   //      pitemChild->m_flags.add(::file::e_flag_folder);

   //      if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
   //      {

   //         ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

   //      }

   //      childrenNew.add_unique(ptreeitemChild);

   //   }

   //   if (childrenNew.get_count() <= 80)
   //   {

   //      list_set_children(ptreeitemParent, childrenNew);

   //   }

   //}


   //// Add root immediate children folder-like tree_data items
   //{

   
   }


   void tree_data::GetSelectedFilePath(string_array & stra)
   {

      ::data::tree_item_ptr_array< ::userfs::item > itemptraSelected;

      get_selection(itemptraSelected);

      for(int i = 0; i < itemptraSelected.get_size(); i++)
      {

         stra.add(((itemptraSelected[0]->m_pdataitem.cast < ::userfs::item > ()))->user_path());

      }

   }



   void tree_data::_001OnMainPostMessage(::message::message * pmessage)
   {
      
      ::pointer<::user::message>pusermessage(pmessage);
      
      switch(pusermessage->m_wparam)
      {
      case MessageMainPostCreateImageListItemRedraw:
      {

         auto puserinteraction = pusermessage->m_pwindow->user_interaction();
            
         puserinteraction->set_need_redraw();

         puserinteraction->kill_timer(123);

         /*
         ::int_rectangle rectangle;
         int iArrange = (int) lparam;

         if(_001IsItemVisible(iArrange))
         {
         m_bCreateImageListRedraw = true;
         index_item_rectangle(iArrange, iArrange, rectangle);
         set_need_redraw(rectangle);
         m_bCreateImageListRedraw = false;
         }*/
      }
      break;
      }

      pusermessage->m_lresult = 0;

      pusermessage->m_bRet = true;

   }


   void tree_data::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::userfs::tree_data::install_message_routing(pchannel);

      MESSAGE_LINK(MessageMainPost, pchannel,  this,  &tree_data::_001OnMainPostMessage);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &tree_data::on_message_context_menu);
      MESSAGE_LINK(e_message_create, pchannel, this, &tree_data::on_message_create);

   }


   void tree_data::StartAnimation()
   {
      
      m_iAnimate = 1;
      
      m_usertreea[0]->set_timer(1234567, 50_ms, nullptr);

   }


   void tree_data::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree_data::_001OnDraw(m_gimageuffer.GetBuffer());
   }


//#ifdef WINDOWS_DESKTOP
//
//   IShellFolder * tree_data::_001GetFolder(EFolder efolder)
//   {
//      IShellFolder * psf;
//
//      if(m_mapFolder.lookup(efolder, psf))
//      {
//         return psf;
//      }
//      else
//      {
//         int iCSIDL = MapToCSIDL(efolder);
//
//         ASSERT(iCSIDL >= 0);
//
//         if(iCSIDL < 0)
//            return nullptr;
//
//         IShellFolder * psfDesktop = nullptr;
//         HRESULT hr = SHGetDesktopFolder(&psfDesktop);
//         LPITEMIDLIST pidl;
//
//
//         hr = SHGetSpecialFolderLocation(
//              nullptr,
//              iCSIDL,
//              &pidl);
//
//
//         if(FAILED(hr))
//            return nullptr;
//
//         hr = psfDesktop->BindToObject(
//              pidl,
//
//              nullptr,
//              IID_IShellFolder,
//              (void **) &psf);
//
//         if(FAILED(hr))
//            return nullptr;
//
//         m_mapFolder.set_at(efolder, psf);
//
//         psf->AddRef();
//         psfDesktop->Release();
//         return psf;
//      }
//
//   }

   //int tree_data::MapToCSIDL(EFolder efolder)
   //{
   //   switch(efolder)
   //   {
   //   case FolderMyComputer:
   //      return CSIDL_DRIVES;
   //   default:
   //      return -1;
   //   }
   //}


//#endif


   void tree_data::_001OnItemExpand(::data::tree_item<::userfs::item> * pitem, const ::action_context & context)
   {

      auto puserfsitem = pitem->m_pdataitem.cast <::userfs::item>();

      if(puserfsitem)
      {

         knowledge(puserfsitem->user_path(), context);

      }

   }


   void tree_data::_001OnItemCollapse(::data::tree_item<::userfs::item> * pitem, const ::action_context & context)
   {

      __UNREFERENCED_PARAMETER(pitem);

   }


   bool tree_data::_001IsTranslucent()
   {

      return filemanager_data()->m_bTransparentBackground;

   }


   void tree_data::_001OnOpenItem(::data::tree_item<::userfs::item> * pitem, const ::action_context & context)
   {

      information() << "tree_data::_001OnOpenItem";

      auto puserfsitem = pitem->m_pdataitem.cast < ::userfs::item > ();

      auto pfileitem = __allocate ::file::item(*puserfsitem);

      filemanager_document()->browse(pfileitem, context);

   }


   //void tree_data::_017OpenFolder(::pointer<::file::item>pitem, const ::action_context & context)
   //{

   //   filemanager_data()->browse(pitem,context);

   //}


   void tree_data::on_timer(::timer * ptimer)
   {

      ::userfs::tree_data::on_timer(ptimer);

      if (ptimer->m_uTimer == 1234567)
      {

         m_iAnimate += 2;

         if (m_iAnimate >= 11)
         {

            m_iAnimate = 0;

            ptimer->m_ptimercallback->erase_timer(ptimer);

         }

         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();

      }
      else if (ptimer->m_uTimer == 123)
      {

         m_usertreea.predicate_each([](auto & ptree)
            {

               ptree->set_need_redraw();

            });

         m_bTimer123 = false;

         ptimer->m_ptimercallback->get_user_interaction()->kill_timer(123);

      }

   }


//   void tree_data::assert_ok() const
//   {
//
//      ::data::tree_data::assert_ok();
//
//   }
//
//
//   void tree_data::dump(dump_context & dumpcontext) const
//   {
//
//      ::data::tree_data::dump(dumpcontext);
//
//   }




   void tree_data::on_message_context_menu(::message::message * pmessage)
   {

   }


   void tree_data::_001OnShellCommand(::message::message * pmessage)
   {

      m_pcontextmenu->OnCommand(pmessage->GetId());

   }


   void tree_data::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   //void tree_data::on_merge_user_tree(::user::tree * pusertree)
   //{

   //}


   //void tree_data::on_bind_user_tree(::user::tree * pusertree)
   //{

   //   __UNREFERENCED_PARAMETER(pusertree);

   //}


   void tree_data::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      if (ptopic->id() == id_browse)
      {

         auto pfilemanagerdata = filemanager_data();

         auto pitem = pfilemanagerdata->m_pitem;

         if (pitem)
         {

            auto path = pitem->user_path();

            browse_sync(ptopic->m_actioncontext);
            //while (true)
            //{

            //   knowledge(path, ptopic->m_actioncontext, true);

            //   if (path.is_empty())
            //   {

            //      break;

            //   }

            //   path = path.folder();

            //}

         }
         
      }

   }


} // namespace filemanager



