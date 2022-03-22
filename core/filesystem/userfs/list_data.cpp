#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif
#include "aura/user/user/shell.h"


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

      defer_create_mutex();

   }


   list_data::~list_data()
   {

   }


   void list_data::_001GetItemText(::user::mesh_item * pitem)
   {

      synchronous_lock synchronouslock(mutex());

//      if(is_locked())
//         return;

      if(pitem->m_iSubItem == m_iNameSubItemText)
      {

         if (pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
         {

            pitem->m_bOk = false;

            return;

         }

         pitem->m_bOk = true;

         try
         {

            pitem->m_strText = m_itema.get_item((::index) pitem->m_iItem)->m_strName;

         }
         catch (...)
         {

            pitem->m_bOk = false;

         }

         return;

      }
      else if(pitem->m_iSubItem == m_iSizeSubItem)
      {
         /*      bool bPendingSize = false;

               bool bGet;
               bGet = psystem->get_fs_size(str, m_itema.get_item(iItem).m_strPath, bPendingSize);
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
                  schedule_file_size(m_itema.get_item(iItem).m_strPath);
                  m_bPendingSize = true;
               }*/

         auto pcontext = get_context();

         try
         {

            //::file::path path = pcontext->m_papexcontext->defer_process_path(m_itema.get_item(pitem->m_iItem)->m_filepathUser);

            //if (!m_itema.m_parray->contains_index(pitem->m_iItem) || m_itema[pitem->m_iItem].is_null())
            //{

            //   pitem->m_bOk = false;

            //   return;

            //}

            ::file::path & path = m_itema[pitem->m_iItem]->m_filepathFinal;

            if (path.m_iDir < 0)
            {

               path.m_iDir = pcontext->m_papexcontext->dir().is(path) ? 1 : 0;

            }

            if (path.m_iDir > 0)
            {

               pitem->m_strText.Empty();

            }
            else
            {

               if (path.m_iSize < 0)
               {

                  pcontext->m_papexcontext->file().length(path).as(path.m_iSize);

               }

               if (path.m_iSize >= 0)
               {

                  pitem->m_strText = _001FileSizeText(path.m_iSize);

               }
               else
               {

                  //pitem->m_strText;

               }

            }

         }
         catch (...)
         {

            pitem->m_bOk = false;

         }

         pitem->m_bOk = true;
         return;
      }
      //else if(m_bStatic)
      //{
      // return ::user::list::_001GetItemText(str, iItem, iSubItem, iListItem);
      //}
      else
         return_(pitem->m_bOk, false);

   }


   ::count list_data::_001GetItemCount()
   {

      return m_itema.get_count();

   }


   void list_data::update()
   {

   }


   void list_data::_001GetItemImage(::user::mesh_item * pitem)
   {

      synchronous_lock synchronouslock(mutex());
//      if(is_locked())
      //return;
      if(pitem->m_iSubItem == m_iNameSubItemText)
      {

         if (pitem->m_iItem < 0 || pitem->m_iItem >= m_itema.get_size())
         {

            pitem->m_bOk = false;

            return;

         }

         pitem->m_bOk = true;

         try
         {

            ::file::path & pathFinal = m_itema.get_item((::index) pitem->m_iItem)->m_filepathFinal;

            __pointer(::core::session) psession = get_session();

            auto puser = psession->user();

            pitem->m_iImage = puser->shell()->get_file_image(
                              pathFinal,
                              pathFinal.m_iDir == 1 ? ::user::shell::e_file_attribute_directory : ::user::shell::e_file_attribute_normal,
                              ::user::shell::e_icon_normal);

            if(pitem->m_iImage < 0)
            {


               puser->shell()->warn_when_ok(pathFinal, {pitem->m_pmesh});


            }

         }
         catch (...)
         {

            pitem->m_bOk = false;

         }

         return;

      }
      else
      {
         return_(pitem->m_bOk, false);
      }

   }


} // namespace userfs


