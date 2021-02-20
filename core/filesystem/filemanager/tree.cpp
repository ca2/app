#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "aura/user/shell.h"
#include "_data.h"
#include "aura/template/list.h"
#include "core/user/user/_tree.h"


namespace filemanager
{


   tree::tree()
   {

   }


   tree::~tree()
   {

   }


   ::e_status tree::initialize_filemanager_tree(document * pdocument)
   {

      auto estatus = initialize_view(pdocument);

      if (!estatus)
      {

         return estatus;

      }

      pdocument->add_data(this);

      m_pdatacontainerbase = pdocument;

      defer_create_mutex();

      m_iAnimate = 0;

      auto puser = User;

      __compose(m_pimagelist, puser->shell()->GetImageList(16));

      return estatus;

   }


   void tree::_017EnsureVisible(const ::file::path & pathUser, const ::action_context & context)
   {

      synchronization_lock synchronizationlock(m_usertreea.has_elements() ? m_usertreea[0]->mutex() : nullptr);

      string_array stra;

      auto pitem = find_item_by_user_path(pathUser);

      if (!pitem)
      {

         return;

      }

      if(!(pitem->m_dwState & ::data::tree_item_state_expanded))
      {

         _001ExpandItem(pitem,context,true,false,false);

      }

      m_straUpdatePtrFilter.remove_all();

      _001EnsureVisible(pitem);

   }


   void tree::knowledge(const ::file::path & pathUser, const ::action_context & context,bool bOnlyParent)
   {

      if (bOnlyParent && pathUser.has_char() && find_item_by_user_path(pathUser))
      {

         return;

      }

      ::file::listing listing;

      ::file::listing listingFinal;

      ::file::path strDir;

      if(bOnlyParent && pathUser.has_char())
      {

         strDir = pathUser.folder();

         auto & path = listing.add_get(pathUser);

         path.m_iDir = 1;

      }
      else
      {

         strDir = pathUser;

         Application.dir().ls(listing, pathUser);

      }

      for (auto & item : listing)
      {

         ::file::path pathFinal = Context.defer_process_path(item);

         listingFinal.add(pathFinal);

      }

      //filemanager_tree_insert(strDir, listing, listingFinal, context, bOnlyParent);

      ::data::tree_item * pitem = find_item_by_user_path(pathUser);

      if(pitem != nullptr)
      {

         if(listing.has_elements())
         {

            pitem->m_dwState |= ::data::tree_item_state_expanded;

            pitem->m_dwState |= ::data::tree_item_state_expandable;

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




   void tree::browse_sync(const ::action_context & context)
   {

      synchronization_object *pm = m_usertreea.has_elements() ? m_usertreea[0]->mutex() : nullptr;

      synchronization_lock synchronizationlock(pm);

      auto pointOffset = get_viewport_offset();

      ::file::path pathUser = filemanager_path();

      // Add parent path ascendant tree items
      {

         ::file::path path = filemanager_path();

         __pointer(::userfs::item) pitemChild;

         ::data::tree_item * ptreeitemParent = get_base_item();

         ::file::patha patha;

         pathUser.ascendants_path(patha);

         for (auto & pathAscendant : patha)
         {

            __pointer(::data::tree_item) ptreeitemChild = find_item_by_user_path(pathAscendant);

            string strName;

            strName = Context.defer_get_file_title(pathAscendant);

            if (pathAscendant.has_char() && strName.has_char())
            {

               if (ptreeitemChild == nullptr)
               {

                  pitemChild = __new(::userfs::item(this));

                  pitemChild->m_filepathUser = pathAscendant;

                  pitemChild->m_filepathFinal = Context.defer_process_path(pathAscendant);

                  pitemChild->m_strName = strName;

                  pitemChild->m_flags.add(::file::e_flag_folder);

                  ptreeitemChild = insert_item(pitemChild, ::data::RelativeLastChild, ptreeitemParent);

                  if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
                  {

                     ptreeitemChild->m_dwState |= ::data::tree_item_state_expandable;

                  }

               }
               else
               {

                  ptreeitemChild->set_parent(ptreeitemParent);

               }

            }

            ptreeitemParent = ptreeitemChild;

         }

      }

      // Add child folder-like tree items
      {

         ::file::path path = filemanager_path();

         //::data::tree_item * ptreeitemChild;

         ::data::tree_item * ptreeitemParent = find_item_by_user_path(pathUser);

         if (ptreeitemParent == nullptr)
         {

            ptreeitemParent = get_base_item();

         }

         ::file::listing & listingUser = ::userfs::tree::get_document()->m_listingFolderUser2;

         ::file::listing & listingFinal = ::userfs::tree::get_document()->m_listingFolderFinal2;

         __pointer_array(::data::tree_item) childrenNew;

         for(index i = 0; i < listingUser.get_count(); i++)
         {

            ::file::path pathUser = listingUser[i];

            __pointer(::data::tree_item) ptreeitemChild = find_item_by_user_path(pathUser);

            if (ptreeitemChild.is_null())
            {

               ptreeitemChild = __new(::data::tree_item);

               ptreeitemChild->m_ptree = this;

               ptreeitemChild->m_pparent = ptreeitemParent;

            }
            else
            {

               ptreeitemChild->set_parent(ptreeitemParent);

            }

            ::file::path pathFinal = listingFinal[i];

            string strName;

            strName = Context.defer_get_file_title(pathUser);

            auto pitemChild = ptreeitemChild->m_pdataitem.cast < ::userfs::item >();

            if (!pitemChild)
            {

               pitemChild = __new(::userfs::item(this));

               ptreeitemChild->m_pdataitem = pitemChild;

            }

            pitemChild->m_filepathUser = pathUser;

            pitemChild->m_filepathFinal = Context.defer_process_path(pathFinal);

            pitemChild->m_strName = strName;

            pitemChild->m_flags.add(::file::e_flag_folder);

            if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
            {

               ptreeitemChild->m_dwState |= ::data::tree_item_state_expandable;

            }

            childrenNew.add_unique(ptreeitemChild);

         }

         if (childrenNew.get_count() <= 80)
         {

            list_set_children(ptreeitemParent, childrenNew);

         }

      }


      {

         if (!context.is_user_source())
         {

            //knowledge("", context, true);

            if (pathUser.has_char())
            {

               ::file::patha filepatha;

               pathUser.ascendants_path(filepatha);

               for (index i = 0; i < filepatha.get_size(); i++)
               {

                  ::file::path pathUser = filepatha[i];

                  knowledge(pathUser, context, true);

               }

            }

         }

         if (filemanager_data() != nullptr && filemanager_data()->m_ptreeFileTreeMerge != nullptr
               && !(dynamic_cast <::user::tree *> (filemanager_data()->m_ptreeFileTreeMerge))->m_ptree->contains(this))
         {

            filemanager_data()->m_ptreeFileTreeMerge->m_ptree->insert_item(this, ::data::RelativeFirstChild);

         }

      }

      {

         string_array straChildItem;

         string str;

         //::file::listing & listingUser = ::userfs::tree::get_document()->m_listingFolderUser2;

         //::file::listing & listingFinal = ::userfs::tree::get_document()->m_listingFolderFinal2;

         if (!context.is(::e_source_system))
         {

            //filemanager_tree_insert(filepath, listingUser, listingFinal, context, true);

            _017EnsureVisible(pathUser, context);

            auto ptreeitem = find_item_by_user_path(pathUser);

            _001SelectItem(ptreeitem);

            auto iMaxLevel = ptreeitem ? ptreeitem->m_iLevel + 2 : -1;

            // remove level 3 with that aren't expanded.

            while (ptreeitem)
            {

               auto ptreeitemNext = ptreeitem->get_child_next_or_parent();

               if (ptreeitem->m_iLevel >= iMaxLevel && !ptreeitem->is_expanded())
               {

                  list_remove_all(ptreeitem);

                  list_remove(ptreeitem->m_pparent, ptreeitem);

               }

               ptreeitem = ptreeitemNext;

            }

            _001OnTreeDataChange();

         }

         arrange(::fs::arrange_by_name);

         //if (m_usertreea.has_elements())
         //{

         //   _polishing_start(m_usertreea[0]);

         //}

      }

      queue_graphics_call([this, pointOffset](::draw2d::graphics_pointer & pgraphics)
         {

            set_viewport_offset(pgraphics, pointOffset.x, pointOffset.y);

         });

      auto puser = User;

      __compose(m_pimagelist, puser->shell()->GetImageList(filemanager_data()->m_iIconSize));;

      m_usertreea.predicate_each([](auto & ptree)
      {

         ptree->set_need_layout();

      });

   }


   void tree::_001InsertColumns()
   {

   }


   void tree::GetSelectedFilePath(string_array & stra)
   {

      ::data::tree_item_ptr_array itemptraSelected;

      get_selection(itemptraSelected);

      for(i32 i = 0; i < itemptraSelected.get_size(); i++)
      {

         stra.add(((itemptraSelected[0]->m_pdataitem.cast < ::userfs::item > ()))->m_filepathUser);

      }

   }



   void tree::_001OnMainPostMessage(::message::message * pmessage)
   {
      
      __pointer(::user::message) pusermessage(pmessage);
      
      switch(pusermessage->m_wparam)
      {
      case MessageMainPostCreateImageListItemRedraw:
      {

         pusermessage->userinteraction()->set_need_redraw();

         pusermessage->userinteraction()->KillTimer(123);

         /*
         ::rectangle_i32 rectangle;
         i32 iArrange = (i32) lparam;

         if(_001IsItemVisible(iArrange))
         {
         m_bCreateImageListRedraw = true;
         _001GetItemRect(iArrange, iArrange, rectangle);
         set_need_redraw(rectangle);
         m_bCreateImageListRedraw = false;
         }*/
      }
      break;
      }

      pusermessage->m_lresult = 0;

      pusermessage->m_bRet = true;

   }


   void tree::install_message_routing(::channel * pchannel)
   {

      ::userfs::tree::install_message_routing(pchannel);

      MESSAGE_LINK(MessageMainPost, pchannel,  this,  &tree::_001OnMainPostMessage);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &tree::_001OnContextMenu);
      MESSAGE_LINK(e_message_create, pchannel, this, &tree::_001OnCreate);

   }


   void tree::StartAnimation()
   {
      m_iAnimate = 1;
      m_usertreea[0]->SetTimer(1234567, 50, nullptr);

   }

   void tree::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gimageuffer.GetBuffer());
   }


//#ifdef WINDOWS_DESKTOP
//
//   IShellFolder * tree::_001GetFolder(EFolder efolder)
//   {
//      IShellFolder * psf;
//
//      if(m_mapFolder.lookup(efolder, psf))
//      {
//         return psf;
//      }
//      else
//      {
//         i32 iCSIDL = MapToCSIDL(efolder);
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

   //i32 tree::MapToCSIDL(EFolder efolder)
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


   void tree::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
   {

      auto puserfsitem = pitem->m_pdataitem.cast <::userfs::item>();

      if(puserfsitem)
      {

         knowledge(puserfsitem->m_filepathUser,context);

      }

   }


   void tree::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(pitem);

   }


   bool tree::_001IsTranslucent()
   {

      return filemanager_data()->m_bTransparentBackground;

   }


   void tree::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   {

      auto puserfsitem = pitem->m_pdataitem.cast < ::userfs::item > ();

      auto pfileitem = __new(::file::item(*puserfsitem));

      _017OpenFolder(pfileitem, context);

   }


   void tree::_017OpenFolder(__pointer(::file::item) pitem, const ::action_context & context)
   {

      filemanager_document()->browse(pitem,context);

   }


   void tree::_001OnTimer(::timer * ptimer)
   {

      ::userfs::tree::_001OnTimer(ptimer);

      if (ptimer->m_uEvent == 1234567)
      {

         m_iAnimate += 2;

         if (m_iAnimate >= 11)
         {

            m_iAnimate = 0;

            ptimer->m_ptimercallback->remove_timer(ptimer);

         }

         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();

      }
      else if (ptimer->m_uEvent == 123)
      {

         m_usertreea.predicate_each([](auto & ptree)
            {

               ptree->set_need_redraw();

            });

         m_bTimer123 = false;

         ptimer->m_ptimercallback->get_user_interaction()->KillTimer(123);

      }

   }


   void tree::assert_valid() const
   {

      ::data::tree::assert_valid();

   }


   void tree::dump(dump_context & dumpcontext) const
   {

      ::data::tree::dump(dumpcontext);

   }




   void tree::_001OnContextMenu(::message::message * pmessage)
   {

   }


   void tree::_001OnShellCommand(::message::message * pmessage)
   {

      m_contextmenu.OnCommand(pmessage->GetId());

   }


   void tree::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void tree::on_merge_user_tree(::user::tree * pusertree)
   {

   }


   void tree::on_bind_user_tree(::user::tree * pusertree)
   {

      UNREFERENCED_PARAMETER(pusertree);

   }


   void tree::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::filemanager::impact::on_subject(psubject, pcontext);

   }


} // namespace filemanager



