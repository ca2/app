#include "framework.h"
#include "list_data.h"
#include "list_item_array.h"
#include "list_item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/data/listener.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "aura/user/user/shell.h"
#include "aura/user/user/window_util.h"
#include "base/user/user/user.h"
#include "core/user/user/mesh.h"
#include "core/platform/session.h"


string _001FileSizeText(i64 i)
{

   string str;

   if(i < 1024)
   {

      return __string(i)  + "B";

   }

   double d = ((double) i) / 1024.0;

   if(d < 2)
   {

      str.format("%0.1fKB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.format("%0.0fKB", d);

      return str;

   }
   d /= 1024.0;

   if(d < 2)
   {

      str.format("%0.1fMB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.format("%0.0fMB", d);

      return str;

   }
   d /= 1024.0;

   if(d < 2)
   {

      str.format("%0.1fGB", d);

      return str;

   }
   if(d < 1024.0)
   {

      str.format("%0.0fGB", d);

      return str;

   }

   d /= 1024.0;

   str.format("%0.0fTB", d);

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


   ::userfs::list_item * list_data::item(index i)
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

         if (psubitem->m_pitem->m_iItem < 0 || psubitem->m_pitem->m_iItem >= m_pitema->get_size())
         {

            psubitem->m_bOk = false;

            return;

         }

         psubitem->m_bOk = true;

         try
         {

            psubitem->m_strText = m_pitema->get_item((::index)psubitem->m_pitem->m_iItem)->m_strName;

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

         auto pcontext = get_context();

         try
         {

            //::file::path path = pcontext->m_papexcontext->defer_process_path(m_pitema->get_item(pitem->m_iItem)->m_filepathUser);

            //if (!m_pitema->m_parray->contains_index(pitem->m_iItem) || (*m_pitema)[pitem->m_iItem].is_null())
            //{

            //   pitem->m_bOk = false;

            //   return;

            //}

            auto & path = (*m_pitema)[psubitem->m_pitem->m_iItem]->final_path_reference();

            if (path.m_iDir < 0)
            {

               (*m_pitema)[psubitem->m_pitem->m_iItem]->set_final_path_dir(pcontext->m_papexcontext->dir()->is(path) ? 1 : 0);

            }

            if (path.m_iDir > 0)
            {

               psubitem->m_strText.Empty();

            }
            else
            {

               if (path.m_iSize < 0)
               {

                  path.m_iSize = pcontext->m_papexcontext->file()->length(path);

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


   ::count list_data::_001GetItemCount()
   {

      return m_pitema->get_count();

   }


   void list_data::update()
   {

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

               auto & pathFinal = m_pitema->get_item((::index)psubitem->m_pitem->m_iItem)->final_path();

               ::pointer<::core::session>psession = get_session();

               auto puser = psession->user();

               psubitem->m_iImage = puser->shell()->get_file_image(
                  pathFinal,
                  pathFinal.m_iDir == 1 ? ::user::shell::e_file_attribute_directory : ::user::shell::e_file_attribute_normal,
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


