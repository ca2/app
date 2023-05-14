#include "framework.h"
#include "tree.h"
#include "document.h"
#include "data.h"
#include "context_menu.h"
#include "acme/platform/application.h"
#include "acme/constant/message.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "acme/platform/timer.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/list.h"
#include "aura/user/user/shell.h"
#include "aura/template/list.h"
#include "core/filesystem/userfs/item.h"
#include "base/user/user/user.h"
#include "core/user/user/tree.h"
#include "aura/message/user.h"


namespace filemanager
{


   tree::tree()
   {

   }


   tree::~tree()
   {

   }


   ::core::application* tree::get_app()
   {

      auto pacmeapplication = acmeapplication();

      return ::is_set(pacmeapplication) ? pacmeapplication->m_pcoreapplication : nullptr;

   }


   ::core::session* tree::get_session()
   {

      auto pacmesession = acmesession();

      return pacmesession ? pacmesession->m_pcoresession : nullptr;

   }


   ::core::system* tree::get_system()
   {

      auto pacmesystem = acmesystem();

      return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   }


#ifdef _DEBUG


   i64 tree::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 tree::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 tree::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

#endif


   void tree::initialize_filemanager_tree(document * pdocument)
   {

      //auto estatus = 
      
      initialize_impact(pdocument);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      pdocument->add_data(this);

      m_pdatacontainerbase = pdocument;

      defer_create_synchronization();

      m_iAnimate = 0;

      auto puser = user();

      __construct(m_pimagelist, puser->shell()->GetImageList(16));

      //return estatus;

   }


   void tree::_017EnsureVisible(const ::file::path & pathUser, const ::action_context & context)
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


   void tree::knowledge(const ::file::path& pathUser, const ::action_context& context)
   {

      knowledge(pathUser, context, false);

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

      auto papp = get_app();

      auto pcontext = m_pcontext;

      if(bOnlyParent && pathUser.has_char())
      {

         strDir = pathUser.folder();

         auto & path = listing.add_get(pathUser);

         path.m_iDir = 1;

      }
      else
      {

         strDir = pathUser;

         listing.set_listing(pathUser);

         dir()->enumerate(listing);

      }

      for (auto & item : listing)
      {

         ::file::path pathFinal = pcontext->m_papexcontext->defer_process_path(item);

         if(pathFinal.m_iDir >= 0)
         {

            listingFinal.defer_add(pathFinal);

         }

      }

      //filemanager_tree_insert(strDir, listing, listingFinal, context, bOnlyParent);

      ::data::tree_item * pitem = find_item_by_user_path(pathUser);

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


   void tree::browse_sync(const ::action_context & context)
   {

      auto pparticleSynchronization = m_usertreea.has_elements() ? m_usertreea[0]->synchronization() : nullptr;

      synchronous_lock synchronouslock(pparticleSynchronization);

      auto pcontext = get_context();

      auto pointOffset = get_context_offset();

      ::file::path pathUser = filemanager_path();

      // Add parent path ascendant tree items
      {

         ::file::path path = filemanager_path();

         ::pointer<::userfs::item>pitemChild;

         if (dir()->is(pathUser))
         {

            ::data::tree_item * ptreeitemParent = get_base_item();

            ::file::path_array patha;

            ascendants_path(pathUser, patha);

            for (auto & pathAscendant : patha)
            {

               ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathAscendant);

               string strName;

               strName = pcontext->m_papexcontext->defer_get_file_title(pathAscendant);

               if (pathAscendant.has_char() && strName.has_char())
               {

                  if (ptreeitemChild == nullptr)
                  {

                     pitemChild = __new(::userfs::item(this));

                     pitemChild->set_user_path(pathAscendant);

                     pitemChild->set_final_path(pcontext->m_papexcontext->defer_process_path(pathAscendant));

                     pitemChild->m_strName = strName;

                     pitemChild->m_flags.add(::file::e_flag_folder);

                     ptreeitemChild = insert_item(pitemChild, ::data::e_relative_last_child, ptreeitemParent);

                     if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
                     {

                        ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

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

         pointer_array < ::data::tree_item > childrenNew;

         auto cListingUser = listingUser.get_count();

         for(index i = 0; i < cListingUser; i++)
         {

            ::file::path pathUser = listingUser[i];

            ::pointer<::data::tree_item>ptreeitemChild = find_item_by_user_path(pathUser);

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

            strName = pcontext->m_papexcontext->defer_get_file_title(pathUser);

            auto pitemChild = ptreeitemChild->m_pdataitem.cast < ::userfs::item >();

            if (!pitemChild)
            {

               pitemChild = __new(::userfs::item(this));

               ptreeitemChild->m_pdataitem = pitemChild;

            }

            pitemChild->set_user_path(pathUser);

            pitemChild->set_final_path(pcontext->m_papexcontext->defer_process_path(pathFinal));

            pitemChild->m_strName = strName;

            pitemChild->m_flags.add(::file::e_flag_folder);

            if (pitemChild->m_flags.has(::file::e_flag_has_subfolder))
            {

               ptreeitemChild->m_dwState |= ::data::e_tree_item_state_expandable;

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

               ::file::path_array filepatha;

               ascendants_path(pathUser, filepatha);

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

            filemanager_data()->m_ptreeFileTreeMerge->m_ptree->insert_item(this, ::data::e_relative_first_child);

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

            ::pointer<::data::tree_item>ptreeitem = find_item_by_user_path(pathUser);

            _001SelectItem(ptreeitem);

            auto iMaxLevel = ptreeitem ? ptreeitem->m_iLevel + 2 : -1;

            // erase level 3 with that aren't expanded.

            while (ptreeitem)
            {

               ::pointer<::data::tree_item>ptreeitemNext = ptreeitem->get_child_next_or_parent();

               if (ptreeitem->m_iLevel >= iMaxLevel && !ptreeitem->is_expanded())
               {

                  list_erase_all(ptreeitem);

                  if(::is_set(ptreeitem->m_pparent))
                  {

                     list_erase(ptreeitem->m_pparent, ptreeitem);

                  }

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

            set_context_offset(pgraphics, pointOffset.x, pointOffset.y);

         });

      auto puser = user();

      if (::is_null(m_pimagelist))
      {

         __construct(m_pimagelist, puser->shell()->GetImageList(filemanager_data()->m_iIconSize));;

      }

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

         stra.add(((itemptraSelected[0]->m_pdataitem.cast < ::userfs::item > ()))->user_path());

      }

   }



   void tree::_001OnMainPostMessage(::message::message * pmessage)
   {
      
      ::pointer<::user::message>pusermessage(pmessage);
      
      switch(pusermessage->m_wparam)
      {
      case MessageMainPostCreateImageListItemRedraw:
      {

         auto puserinteraction = ::user::message_user_interaction(pusermessage);
            
         puserinteraction->set_need_redraw();

         puserinteraction->KillTimer(123);

         /*
         ::rectangle_i32 rectangle;
         i32 iArrange = (i32) lparam;

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


   void tree::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::userfs::tree::install_message_routing(pchannel);

      MESSAGE_LINK(MessageMainPost, pchannel,  this,  &tree::_001OnMainPostMessage);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &tree::on_message_context_menu);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &tree::on_message_create);

   }


   void tree::StartAnimation()
   {
      
      m_iAnimate = 1;
      
      m_usertreea[0]->SetTimer(1234567, 50_ms, nullptr);

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

         knowledge(puserfsitem->user_path(), context);

      }

   }


   void tree::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   {

      __UNREFERENCED_PARAMETER(pitem);

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


   void tree::_017OpenFolder(::pointer<::file::item>pitem, const ::action_context & context)
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

            ptimer->m_ptimercallback->erase_timer(ptimer);

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


//   void tree::assert_ok() const
//   {
//
//      ::data::tree::assert_ok();
//
//   }
//
//
//   void tree::dump(dump_context & dumpcontext) const
//   {
//
//      ::data::tree::dump(dumpcontext);
//
//   }




   void tree::on_message_context_menu(::message::message * pmessage)
   {

   }


   void tree::_001OnShellCommand(::message::message * pmessage)
   {

      m_pcontextmenu->OnCommand(pmessage->GetId());

   }


   void tree::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void tree::on_merge_user_tree(::user::tree * pusertree)
   {

   }


   void tree::on_bind_user_tree(::user::tree * pusertree)
   {

      __UNREFERENCED_PARAMETER(pusertree);

   }


   void tree::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

   }


} // namespace filemanager



