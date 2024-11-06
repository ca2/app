#include "framework.h"
#include "list_data.h"
#include "list_item_array.h"
#include "list_item.h"
#include "data.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/set.h"
#include "aura/user/user/shell.h"
#include "aura/user/user/interaction_array.h"
#include "base/user/user/user.h"
#include "core/user/user/mesh.h"
#include "core/platform/session.h"


string _001FileSizeText(huge_integer i)
{

   string str;

   if(i < 1024)
   {

      return as_string(i)  + "B";

   }

   double d = ((double) i) / 1024.0;

   if(d < 2)
   {

      str.formatf("%0.1fKB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.formatf("%0.0fKB", d);

      return str;

   }
   d /= 1024.0;

   if(d < 2)
   {

      str.formatf("%0.1fMB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.formatf("%0.0fMB", d);

      return str;

   }
   d /= 1024.0;

   if(d < 2)
   {

      str.formatf("%0.1fGB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.formatf("%0.0fGB", d);

      return str;

   }

   d /= 1024.0;

   str.formatf("%0.0fTB", d);

   return str;

}


namespace userfs
{


   list_data::list_data()
   {

      m_iNameSubItem = -1;

      m_iNameSubItemText = -1;

      m_iSizeSubItem = -1;

      m_iSelectionSubItem = -1;

      defer_create_synchronization();

   }


   list_data::~list_data()
   {

   }


   void list_data::initialize(::particle * pparticle)
   {

      ::user::list_data::initialize(pparticle);

      __construct_new(m_pitema);

   }


   ::userfs::list_item * list_data::item(::collection::index i)
   { 
      
      return m_pitema->get_item(i); 
   
   }


   void list_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      //synchronous_lock synchronouslock(this->synchronization());

//      if(is_locked())
//         return;

      if(psubitem->m_iSubItem == m_iNameSubItemText)
      {

         auto c = m_pitema->get_size();

         if (psubitem->m_pitem->m_iItem < 0 || psubitem->m_pitem->m_iItem >= c)
         {

            psubitem->m_bOk = false;

            return;

         }

         psubitem->m_bOk = true;

         try
         {

            psubitem->m_strText = m_pitema->get_item((::collection::index)psubitem->m_pitem->m_iItem)->m_strName;

         }
         catch (...)
         {

            psubitem->m_bOk = false;

         }

         return;

      }
      else if(psubitem->m_iSubItem == m_iSizeSubItem)
      {
         /*      bool bPendingSize = false;

               bool bGet;
               bGet = psystem->get_fs_size(str, m_pitema->get_item(iItem).m_strPath, bPendingSize);
               if(bGet)
               {
                  m_straFileSize.set_at_grow(iItem, str);
               }
               else
               {
                  if(iItem < m_straFileSize.get_size())
                  {
                     str = m_straFileSize[iItem];
                  }
               }
               if(bPendingSize)
               {
                  schedule_file_size(m_pitema->get_item(iItem).m_strPath);
                  m_bPendingSize = true;
               }*/

         // auto pcontext = get_context();

         try
         {

            //::file::path path = m_papplication->defer_process_matter_path(m_pitema->get_item(pitem->m_item.m_iItem)->m_filepathUser);

            //if (!m_pitema->m_parray->contains_index(pitem->m_item.m_iItem) || (*m_pitema)[pitem->m_item.m_iItem].is_null())
            //{

            //   pitem->m_bOk = false;

            //   return;

            //}
            
            ::pointer < list_item > plistitem;
            
            auto iItem = psubitem->m_pitem->m_iItem;
            
            if(iItem >= 0 && iItem < m_pitema->size())
            {
             
               plistitem = (*m_pitema)[iItem];
               
            }
            
            if(plistitem)
            {
               
               auto & path = plistitem->final_path_reference();
               
               if (path.not_file_or_folder())
               {
                  
                  plistitem->set_final_path_type(directory()->file_type(path));
                  
               }
               
               if (path.is_folder())
               {

                  psubitem->m_strText.empty();

               }
               else
               {

                  if (path.m_iSize < 0)
                  {

                     path.m_iSize = file()->length(path);

                  }

                  if (path.m_iSize >= 0)
                  {

                     psubitem->m_strText = _001FileSizeText(path.m_iSize);

                  }
                  else
                  {

                     //pitem->m_strText;

                  }
               
               }

            }
            else
            {
              
               psubitem->m_strText.empty();
               
            }

         }
         catch (...)
         {

            psubitem->m_bOk = false;

         }

         psubitem->m_bOk = true;

         return;

      }
      //else if(m_bStatic)
      //{
      // return ::user::list::_001GetItemText(str, iItem, iSubItem, iListItem);
      //}
      else
      {

         return_(psubitem->m_bOk, false);

      }

   }


   ::collection::count list_data::_001GetItemCount()
   {

      return m_pitema->get_count();

   }


   void list_data::update(::userfs::data * puserfsdata)
   {

      //ASSERT(listingUser.get_count() == listingFinal.get_count());

      //for (::collection::index i = 0; i < listingUser.get_count(); i++)
      //{

      //   ::file::path & pathFinal = listingFinal[i];

      //   ::file::path & pathUser = listingUser[i];

      //   if (pathFinal.m_iDir == 0)
      //   {

      //      pathUser.m_iDir = 0;

      //      continue;

      //   }

      //   if (pathFinal.m_iDir < 0)
      //   {

      //      auto pathFolderCandidate = pathFinal;

      //      pathFolderCandidate.flags() += ::file::e_flag_resolve_alias;

      //      pathFinal.m_iDir = directory()->is(pathFolderCandidate) ? 1 : 0;

      //   }

      //   pathUser.m_iDir = pathFinal.m_iDir;

      //   if (pathFinal.m_iDir == 0)
      //   {

      //      continue;

      //   }

      //   auto pathFolderUser = listingUser[i];

      //   auto pathFolderFinal = listingFinal[i];

      //   listingFolderUser.defer_add(pathFolderUser);

      //   listingFolderFinal.defer_add(pathFolderFinal);

      //   auto plistitem = __create_new<list_item>();

      //   plistitem->m_pathFinal = pathFinal;

      //   plistitem->m_pathUserl = pathFinal;

      //   m_puserfslistdata->m_pitema->add_item();

      //}

      __construct_new(m_pitema);

      information() << "::userfs::list update";

      auto & listingUser = puserfsdata->m_listingUser2;

      auto & listingFinal = puserfsdata->m_listingFinal2;

      for (::collection::index i = 0; i < listingUser.get_count(); i++)
      {

         ::file::path & pathFinal = listingFinal[i];

         ::file::path & pathUser = listingUser[i];

         auto plistitem = __create_new<list_item>();

         plistitem->final_path_reference() = pathFinal;

         plistitem->user_path_reference() = pathUser;

         plistitem->m_strName = pathUser.name();

         information() << "pathUser : " << pathUser;

         if (puserfsdata->m_pfsset->is_dir(pathFinal))
         {

            plistitem->m_flags += ::file::e_flag_folder;

         }

         m_pitema->add_item(plistitem);

      }

      m_pitema->predicate_sort([](auto pitem1, auto pitem2)
         {

            if (is_different(pitem1->IsFolder(), pitem2->IsFolder()))
            {

               return pitem1->IsFolder();

            }

            return (bool) ( pitem1->m_strName.case_insensitive_order(pitem2->m_strName) < 0);

               });

   }


   void list_data::_001GetSubItemImage(::user::mesh_subitem * psubitem)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if(psubitem->m_iSubItem == m_iNameSubItemText)
      {

         if (psubitem->m_pitem->m_iItem < 0 || psubitem->m_pitem->m_iItem >= m_pitema->get_size())
         {

            psubitem->m_bOk = false;

            return;

         }

         psubitem->m_bOk = true;

         try
         {

            if (psubitem->m_iImage < 0)
            {

               auto & pathFinal = m_pitema->get_item((::collection::index)psubitem->m_pitem->m_iItem)->final_path();

               auto psession = session();

               auto puser = user();

               psubitem->m_iImage = puser->shell()->get_file_image(
                  pathFinal,
                  pathFinal.is_folder() ? ::user::shell::e_file_attribute_directory : ::user::shell::e_file_attribute_normal,
                  ::user::shell::e_icon_normal);

               if (psubitem->m_iImage < 0)
               {


                  puser->shell()->warn_when_ok(pathFinal, { psubitem->m_pitem->m_pmesh });


               }

            }

         }
         catch (...)
         {

            psubitem->m_bOk = false;

         }

         return;

      }
      else
      {

         return_(psubitem->m_bOk, false);

      }

   }


} // namespace userfs


