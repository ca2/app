//
// Created by camilo on 2025-07-10 00:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application_state.h"
#include "acme/parallelization/manual_reset_happening.h"

namespace platform
{


   ::pointer<application_state> g_papplicationstate;


   application_state::application_state()
   {
      m_iWidth = 0;
      m_iHeight = 0;

      m_lMemFreeAvailableKb = 0;

      m_bRedraw = false;
      m_bSetApplicationReady = false;

   }


   application_state::~application_state()
   {


   }

   application_state * application_state::get()
   {

      return g_papplicationstate;

   }


   void application_state::set(application_state * papplicationstate)
   {

      g_papplicationstate = papplicationstate;

   }


   void application_state::exchange1()
   {


   }


   void application_state::after_exchange()
   {


   }


   void application_state::post_media_store_operation(::data::block * pdatablock)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_datablockaMediaStore.add(pdatablock);

   }

//   void application_state::set_data(const ::scoped_string & scopedstrRelativeName,
//                                 const ::scoped_string & scopedstrMimeType,
//                                 const ::block & block)
//{
//
//           auto pdatablock = øcreate_new<::data::block>();
//   pdatablock->m_bWrite = true;
//   pdatablock->m_strPath = scopedstrRelativeName;
//   pdatablock->m_strMime = scopedstrMimeType;
//   pdatablock->m_memory = block;
//
//   {
//      _synchronous_lock synchronouslock(this->synchronization());
//      m_datablockaInputOutput.add(pdatablock);
//
//   }
//
//}
//
//
//::string application_state::get_data(const ::scoped_string & scopedstrRelativeName,
//                                 const ::scoped_string & scopedstrMimeType,
//                                 const class ::time & timeTimeout)
//{
//
//      manual_reset_happening happening;
//
//         bool bRead = false;
//
//   auto pdatablock = øcreate_new<::data::block>();
//   pdatablock->m_bWrite = false;
//   pdatablock->m_strPath = scopedstrRelativeName;
//   pdatablock->m_strMime = scopedstrMimeType;
//   pdatablock->lockm_procedureOnRead = [&happening, &bRead]()
//   {
//bRead = true;
//      happening.set_happening();
//
//   };
//   {
//      _synchronous_lock synchronouslock(this->synchronization());
//      m_datablockaInputOutput.add(pdatablock);
//
//
//   }
//   happening.wait(timeTimeout);
//   if(!bRead)
//   {throw ::exception(error_timeout, "timeout");
//     } else{
//      return pdatablock->m_memory;
//   }
//}
//

   void
   application_state::queue_message_box(::message_box * pmessagebox)
   {

      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

      synchronous_lock synchronouslock(this->synchronization());

      m_messageboxa.add(pmessagebox);

   }


   ::pointer<::message_box> application_state::pick_message_box()
   {

      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

      synchronous_lock synchronouslock(this->synchronization());

      if (m_messageboxa.is_empty()) {

         return nullptr;

      }

      auto psequencer = m_messageboxa.pop_first();

      return psequencer;

   }


   ::pointer<::data::block> application_state::pick_media_store_operation()
   {

      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

      synchronous_lock synchronouslock(this->synchronization());

      if (m_datablockaMediaStore.is_empty()) {

         return nullptr;

      }

      auto pdatablock = m_datablockaMediaStore.pop_first();

      return pdatablock;

   }


   void application_state::defer_post_all_media_store_operations()
   {

      while (true) {

         auto pdatablock = pick_media_store_operation();

         if (!pdatablock) {

            return;

         }

         on_media_store_operation(pdatablock);

      }
      //defer_process_all_input_output_data_blocks();

   }

   void application_state::on_media_store_operation(::data::block * pdatablock)
   {

   }

//
//   void application_state::on_write_input_output_data_block(::data::block * pdatablock)
//   {
//
//
//   }
//
//
//   void application_state::on_read_input_output_data_block(::data::block * pdatablock)
//   {
//
//
//   }

   void application_state::open_url(const ::scoped_string & scopedstrOpenUrl)
   {

      synchronous_lock lock(this->synchronization());

      m_straOpenUrl.add(scopedstrOpenUrl);

   }


   void application_state::list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate)
   {

      //synchronous_lock lock(m_pparticleMutexListFileEnumerate);
      synchronous_lock lock(this->synchronization());

      m_straListFileEnumerate.add(scopedstrListFileEnumerate);

   }

//   ::file::path application_state::synchronously_getDocumentFolder(const class ::time & timeOut)
//   {
//
//      return {};
//
//   }

//
// ::pointer < ::data::block > application_state::post_media_store_operation(
//    ::data::block * pdatablock)
// {
//
//    return {};
//
// }
// ::pointer < ::data::block >application_state:: media_store_get_data(const ::scoped_string & scopedstrPath)
// {
//
//      return {};
//
// }

} // namespace platform



