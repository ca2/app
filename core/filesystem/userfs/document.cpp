#include "framework.h"
#include "aura/update.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif

#include "acme/constant/id.h"


namespace userfs
{


   document::document()
   {

   }


   document::~document()
   {

   }


   void document::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::user::document::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __compose_new(m_pfsset);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::aura::application * document::get_application() const
   //{

   //   return dynamic_cast < ::base::session * >(get_application()->m_psession)->m_papplicationCurrent;

   //}


   void document::assert_valid() const
   {

      ::user::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      {

         synchronous_lock synchronouslock(fs_data()->mutex());

         m_pathFolder = pitem->m_filepathUser;

      }

      if(m_listingRoot.is_empty())
      {

         ::file::listing listing;

         fs_data()->root_ones(listing);

         {

            synchronous_lock synchronouslock(fs_data()->mutex());

            m_listingRoot = listing;

         }

      }

      ::file::listing listingUser;

      auto papplication = get_application();

      auto pcontext = m_pcontext;

      if(strlen(pitem->m_filepathUser) == 0)
      {

         listingUser = m_listingRoot;

         listingUser.m_straPattern = m_listingRoot.m_straPattern;

         listingUser.m_straIgnoreName = m_listingRoot.m_straIgnoreName;

         listingUser.m_pathUser.Empty();

         listingUser.m_pathFinal.Empty();

      }
      else
      {

         pcontext->m_papexcontext->dir().ls(listingUser, pitem->m_filepathFinal);

         listingUser.m_pathUser = pitem->m_filepathUser;

         {

            ::file::listing listingUserFormatted;

            listingUserFormatted.m_straPattern = listingUser.m_straPattern;

            listingUserFormatted.m_straIgnoreName = listingUser.m_straIgnoreName;

            listingUserFormatted.m_pathUser = pitem->m_filepathUser;

            listingUserFormatted.m_pathFinal = listingUser.m_pathFinal;

            for (auto & item : listingUser)
            {

               ::file::path pathUser;

               if (pitem->m_filepathUser.ends_ci("://"))
               {

                  pathUser = string(pitem->m_filepathUser) + item.name();

               }
               else
               {

                  pathUser = pitem->m_filepathUser / item.name();

               }

               pathUser.m_iDir = item.m_iDir;

               listingUserFormatted.add(pathUser);

            }

            listingUser = listingUserFormatted;

         }

      }

      ::file::listing listingFinal;

      listingFinal.m_straPattern = listingUser.m_straPattern;

      listingFinal.m_straIgnoreName = listingUser.m_straIgnoreName;

      listingFinal.m_pathUser = pitem->m_filepathUser;

      listingFinal.m_pathFinal = pitem->m_filepathFinal;

      for (auto & pathItem : listingUser)
      {

         ::file::path pathSemiFinal = pathItem;

         if (listingUser.m_pathFinal.has_char())
         {

            pathSemiFinal = listingUser.m_pathFinal / pathItem.name();

         }

         ::file::path pathFinal  = pcontext->m_papexcontext->defer_process_path(pathSemiFinal | ::file::e_flag_resolve_alias);

         pathFinal.m_iDir = pathItem.m_iDir;

         listingFinal.add(pathFinal);

      }

      ::file::listing listingFolderUser;

      ::file::listing listingFolderFinal;

      ASSERT(listingUser.get_count() == listingFinal.get_count());

      for (index i = 0; i < listingUser.get_count(); i++)
      {

         ::file::path & pathFinal = listingFinal[i];

         ::file::path & pathUser = listingUser[i];

         if (pathFinal.m_iDir == 0)
         {

            pathUser.m_iDir = 0;

            continue;

         }

         if (pathFinal.m_iDir < 0)
         {

            pathFinal.m_iDir = pcontext->m_papexcontext->dir().is(pathFinal | ::file::e_flag_resolve_alias) ? 1 : 0;

         }

         pathUser.m_iDir = pathFinal.m_iDir;

         if (pathFinal.m_iDir == 0)
         {

            continue;

         }

         auto pathFolderUser = listingUser[i];

         auto pathFolderFinal = listingFinal[i];

         listingFolderUser.add(pathFolderUser);

         listingFolderFinal.add(pathFolderFinal);

      }


      {

         synchronous_lock synchronouslock(fs_data()->mutex());

         m_listingUser2 = listingUser;

         m_listingFinal2 = listingFinal;

         m_listingFolderUser2 = listingFolderUser;

         m_listingFolderFinal2 = listingFolderFinal;

      }

      ::topic topic(id_synchronize_path);

      topic.m_pfileitem = pitem;

      topic.m_actioncontext = context + ::e_source_sync;

      update_all_views(&topic);

      return true;

   }


} // namespace userfs



