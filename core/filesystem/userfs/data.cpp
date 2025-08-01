#include "framework.h"
#include "data.h"
#include "list_data.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/scoped_restore.h"
#include "apex/filesystem/fs/set.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/session.h"
#include "base/user/user/impact.h"


namespace userfs
{


   data::data()
   {

      m_bFullBrowse = false;

   }


   data::~data()
   {

   }


   void data::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::data::data::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      //__construct_new(m_pfsset);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::aura::application * document::get_app() const
   //{

   //   return dynamic_cast < ::base::session * >(get_app()->m_psession)->m_pappCurrent;

   //}


   //bool data::__browse(::pointer<::file::item>pitem, const ::action_context & context)
   //{

   //   if (m_pfsset->m_spafsdata.is_empty())
   //   {

   //      m_pfsset->m_spafsdata.erase_all();

   //      auto psession = session();

   //      m_pfsset->m_spafsdata.add(psession->fs());

   //      ::file::listing listing;

   //      m_pfsset->root_ones(listing);

   //   }

   //   string strOldPath;

   //   if (m_pitem.is_set())
   //   {

   //      strOldPath = m_pitem->user_path();

   //   }

   //      m_pitem = __allocate ::file::item(*pitem);

   //   //   try
   //   //   {

   //   //      //OnFileManagerBrowse(context + ::e_source_sync);

   //   //}
   //   //catch (string & str)
   //   //{

   //   //   if (str == "uifs:// You have not logged in!")
   //   //   {

   //   //      output_error_message("You have not logged in! Cannot access your User Intelligent File System - uifs://");

   //   //      // assume can resume at least from this exception one time

   //   //      // auto pcontext = get_context();

   //   //      m_pitem = __allocate ::file::item(m_papplication->defer_process_matter_path(strOldPath), strOldPath);

   //   //      OnFileManagerBrowse(context + ::e_source_sync);

   //   //   }

   //   //   return false;

   //   //}

   //   //if (m_pfilewatch >= 0)
   //   //{

   //   //   // auto pcontext = get_context();

   //   //   file_watcher()->erase_watch(m_pfilewatch);

   //   //}

   //   //try
   //   //{

   //   //   // auto pcontext = get_context();

   //   //   auto pdir = dir();

   //   //   auto & watcher = pdir->watcher();

   //   //   m_pfilewatch = watcher.add_watch(m_pitem->final_path(), this, false);

   //   //}
   //   //catch (...)
   //   //{

   //   //   m_pfilewatch = -1;

   //   //}

   //   return true;

   //}




//   void document::assert_ok() const
//   {
//
//      ::user::document::assert_ok();
//
//   }
//
//
//   void document::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::document::dump(dumpcontext);
//
//   }


   //string data::get_last_browse_path(::particle * pparticle, const ::scoped_string & scopedstrDefault)
   //{

   //   return {};
   //}

   void data::browse_initial_path(const ::action_context & action_context)
   {

      //CreateImpacts();

      //auto ptopic = create_topic(id_create_bars);

      //ptopic->payload(id_document) = this;

      //::file::path pathInitialBrowse;

      //if (bInitialBrowsePath)
      //{

         //string str;

//      auto pfilemanagerdata = this;
//
//      auto pathInitialBrowse = pfilemanagerdata->get_last_browse_path(this, pfilemanagerdata->m_pathDefault);
//
//      //browse(path, ::e_source_initialize);
//
////         if (get_file.datastream()->get({true, "last_browse_folder"}, str))
////         {
////
////            if (str == "machinefs://")
////            {
////
////               atom idMachine;
////
////#ifdef LINUX
////               idMachine = "Linux";
////#elif defined(WINDOWS_DESKTOP)
////               idMachine = "WindowsDesktop";
////#elif defined(WINDOWS)
////               idMachine = "Metrowin";
////#elif defined(MACOS)
////               idMachine = "macOS";
////#elif defined(__APPLE__)
////               idMachine = "iOS";
////#endif
////
////               if (papp->datastream()->get({true, "last_browse_folder." + as_string(idMachine)}, str))
////               {
////
////                  browse(str, ::e_source_database);
////
////               }
////               else
////               {
////
////                  browse("", ::e_source_system);
////
////               }
////
////            }
////            else
////            {
////
//               //browse(str, ::e_source_database);
//
////            }
//
//         //}
//         //else if (pfilemanagerdata->m_pathDefault.has_character())
//         //{
//
//         //   browse(pfilemanagerdata->m_pathDefault, ::e_source_initialize);
//
//         //}
//         //else
//         //{
//
//         //   browse("", ::e_source_system);
//
//         //}
//
//      //}
//
//      browse(pathInitialBrowse, action_context);

      //ptopic->id() = ;

      //update_all_impacts(pupdate);

   }


   void data::browse(const ::file::path & pathUser, const ::action_context & context)
   {

      information() << "::userfs::data::browse";

      // auto pcontext = get_context();

      ::file::path pathFinal = m_papplication->defer_process_matter_path(pathUser);

      ::pointer<::file::item>pitem = __allocate ::file::item(pathUser, pathFinal);

      browse(pitem, context);

   }


   void data::__browse(::pointer<::file::item>pitem, const ::action_context & context)
   {

      if (m_bFullBrowse)
      {

         return;

      }

      at_end_of_scope
      {

         m_bFullBrowse = false;

      };

      {

         _synchronous_lock synchronouslock(fs_data()->synchronization());

         m_pathFolder = pitem->user_path();

      }

      information() << "::userfs::document::browse pitem user path : " << m_pathFolder;

      if(m_listingRoot2.is_empty())
      {

         information() << "::userfs::document getting root listing";

         ::file::listing listing;

         fs_data()->root_ones(listing);

         {

            _synchronous_lock synchronouslock(fs_data()->synchronization());

            m_listingRoot2 = listing;

         }

         for(auto & path : m_listingRoot2)
         {

            information() << "::userfs::document root listing : " << path;


         }

      }

      ::file::listing listingUser;

      auto papp = get_app();

      listingUser.clear();

      listingUser.m_straTitle.clear();

      ::file::path pathItemUserPath;

      pathItemUserPath = pitem->user_path();

      //__construct_new(m_puserfslistdata);

      if(pathItemUserPath.is_empty())
      {

         listingUser = m_listingRoot2;

         listingUser.m_straPattern = m_listingRoot2.m_straPattern;

         listingUser.m_straIgnoreName = m_listingRoot2.m_straIgnoreName;

         listingUser.m_pathUser.empty();

         listingUser.m_pathFinal.empty();

      }
      else
      {

         auto pathParent = pitem->user_path();

         listingUser.set_listing(pathParent);

         directory()->enumerate(listingUser);

         listingUser.m_pathUser = pitem->user_path();

         {

            ::file::listing listingUserFormatted;

            listingUserFormatted.m_straPattern = listingUser.m_straPattern;

            listingUserFormatted.m_straIgnoreName = listingUser.m_straIgnoreName;

            listingUserFormatted.m_pathUser = pitem->user_path();

            listingUserFormatted.m_pathFinal = listingUser.m_pathFinal;

            listingUserFormatted.m_eflag = ::file::e_flag_file_or_folder;

            for (auto & item : listingUser)
            {

               ::file::path pathUser;

               if (pitem->user_path().case_insensitive_ends("://"))
               {

                  pathUser = string(pitem->user_path()) + item.name();

               }
               else
               {

                  pathUser = pitem->user_path() / item.name();

               }

               pathUser.set_type(item.type());

               listingUserFormatted.defer_add(pathUser);

            }

            listingUser = listingUserFormatted;

         }

      }

      ::file::listing listingFinal;

      listingFinal.m_straPattern = listingUser.m_straPattern;

      listingFinal.m_straIgnoreName = listingUser.m_straIgnoreName;

      listingFinal.m_pathUser = pitem->user_path();

      listingFinal.m_pathFinal = pitem->final_path();

      listingFinal.m_eflag = ::file::e_flag_file_or_folder;

      for (auto & pathItem : listingUser)
      {

         ::file::path pathSemiFinal = pathItem;

         if (listingUser.m_pathFinal.has_character())
         {

            pathSemiFinal = listingUser.m_pathFinal / pathItem.name();

         }

         auto pathToProcess = pathSemiFinal;
         
         pathToProcess.flags() += ::file::e_flag_resolve_alias;

         ::file::path pathFinal = m_papplication->defer_process_path(pathToProcess);

         pathFinal.set_type(pathItem.type());

         listingFinal.defer_add(pathFinal);

         information() << "listing " << pathFinal;

      }

      ::file::listing listingFolderUser;

      ::file::listing listingFolderFinal;

      listingFolderUser.m_eflag = ::file::e_flag_folder;

      listingFolderFinal.m_eflag = ::file::e_flag_folder;

      ASSERT(listingUser.get_count() == listingFinal.get_count());

      for (::collection::index i = 0; i < listingUser.get_count(); i++)
      {

         ::file::path & pathFinal = listingFinal[i];

         ::file::path & pathUser = listingUser[i];

         if (pathFinal.is_file())
         {

            pathUser.set_existent_file();

            continue;

         }

         if (pathFinal.not_file_or_folder())
         {

            auto pathFolderCandidate = pathFinal;

            pathFolderCandidate.flags() += ::file::e_flag_resolve_alias;

            pathFinal.set_type(directory()->file_type(pathFolderCandidate));

         }

         pathUser.set_type(pathFinal.type());

         if (pathFinal.is_file())
         {

            continue;

         }

         auto pathFolderUser = listingUser[i];

         auto pathFolderFinal = listingFinal[i];
         
         auto i1 = listingFolderUser.size();

         listingFolderUser.defer_add(pathFolderUser);
         
         auto i2 = listingFolderUser.size();
         
         if(i2 == i1 + 1
            && i < listingUser.m_straTitle.size()
            && listingUser.m_straTitle[i].has_character())
         {
          
            listingFolderUser.m_straTitle.insert_at(i2, listingUser.m_straTitle[i]);
            
         }

         listingFolderFinal.defer_add(pathFolderFinal);

         information() << "folder user : " << pathFolderUser;

         //auto plistitem = __create_new<list_item>();

         //plistitem->m_pathFinal = pathFinal;

         //plistitem->m_pathUserl = pathFinal;

         //m_puserfslistdata->m_pitema->add_item();

      }


      {

         synchronous_lock synchronouslock(fs_data()->synchronization());

         m_listingUser2 = listingUser;

         m_listingFinal2 = listingFinal;

         m_listingFolderUser2 = listingFolderUser;

         m_listingFolderFinal2 = listingFolderFinal;

      }

      //auto ptopic = create_topic(id_browse);

      //ptopic->m_actioncontext = context + ::e_source_sync;

      //update_all_impacts(ptopic);

      //auto pextendedtopic = create_extended_topic(id_synchronize_path);

      //pextendedtopic->m_pfileitem = pitem;

      //pextendedtopic->m_actioncontext = context + ::e_source_sync;

      //update_all_impacts(pextendedtopic);

      m_pitem = pitem;

      auto ptopic = create_topic(id_browse);

      m_pusercontroller->on_update_data(this, ptopic, context);

   }
::user::document *data:: get_document()
{
 
   return m_pusercontroller.cast <::user::document>();
   
}

   void data::browse(::pointer<::file::item>pitem, const ::action_context & context)
   {

      information() << "::userfs::data::browse pitem";

      if (!fs_data()->is_zero_latency(pitem->final_path()))
      {

         information() << "::userfs::data::browse !is_zero_latency";

         auto ptopic = create_topic(id_synchronize_path);

         ptopic->m_actioncontext = context + ::e_source_sync + ::e_source_system;

         ptopic->_extended_topic()->m_pfileitem = pitem;

         m_pusercontroller->update_all_impacts(ptopic);

      }

      get_document()->m_impacta.first()->post()
         << [this, pitem, context]()
      {

         __browse(pitem, context);

      };

   }


   ::fs::set * data::fs_data()
   {

      if (__defer_construct_new(m_pfsset))
      {


         application()->init_fs_set(m_pfsset);

      }

      return m_pfsset;

   }
//   void data::__full_browse(::pointer<::file::item>pitem, const ::action_context & context)
//   {
//
//      __task_guard(m_bFullBrowse);
//
//#define DBG_BROWSE_LOOP 1
//
//      for (::collection::index i = 0; i < DBG_BROWSE_LOOP; i++)
//      {
//
//         ::userfs::document::browse(pitem, context);
//
//      }
//
//      auto pextendedtopic = create_extended_topic(id_synchronize_path);
//
//      pextendedtopic->m_pfileitem = pitem;
//
//      pextendedtopic->m_actioncontext = context + ::e_source_sync;
//
//      update_all_impacts(pextendedtopic);
//
//   }


} // namespace userfs



