//
// Created by camilo on 2025-07-10 00:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application_sink.h"
#include "message_sink.h"
#include "acme/filesystem/file/byte2_stream.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/windowing/message/types.h"


namespace platform
{


   ::pointer<application_sink> g_papplicationsink;


   application_sink::application_sink()
   {
      m_iWidth = 0;
      m_iHeight = 0;

      m_lMemFreeAvailableKb = 0;

      m_bRedraw = false;
      m_bSetApplicationReady = false;

   }


   application_sink::~application_sink()
   {


   }

   application_sink * application_sink::get()
   {

      return g_papplicationsink;

   }


   void application_sink::set(application_sink * papplicationsink)
   {

      g_papplicationsink = papplicationsink;

   }


   void application_sink::exchange1()
   {


   }


   void application_sink::after_exchange()
   {


   }


   void application_sink::post_media_store_operation(::data::block * pdatablock)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      byte2_stream & operator >>(string & str);
      byte2_stream & operator << (string & str);
      m_datablockaMediaStore.add(pdatablock);

   }


   void application_sink::on_main_task_iteration()
   {


   }

//   void application_sink::set_data(const ::scoped_string & scopedstrRelativeName,
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
//::string application_sink::get_data(const ::scoped_string & scopedstrRelativeName,
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
   application_sink::post_message_box(::message_box * pmessagebox)
   {

      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

      //synchronous_lock synchronouslock(this->synchronization());

      auto pmessage = message_sink().create_message(::e_message_message_box);

      output_byte2_stream stream(pmessage->m_memory);

      ::message::message_box box(pmessagebox);

      stream << box;

      message_sink().post_message(pmessage);

   }


//   ::pointer<::message_box> application_sink::pick_message_box()
//   {
//
//      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_messageboxa.is_empty()) {
//
//         return nullptr;
//
//      }
//
//      auto psequencer = m_messageboxa.pop_first();
//
//      return psequencer;
//
//   }


   ::pointer<::data::block> application_sink::pick_media_store_operation()
   {

      //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

      synchronous_lock synchronouslock(this->synchronization());

      if (m_datablockaMediaStore.is_empty()) {

         return nullptr;

      }

      auto pdatablock = m_datablockaMediaStore.pop_first();

      return pdatablock;

   }


   void application_sink::defer_post_all_media_store_operations()
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

   void application_sink::on_media_store_operation(::data::block * pdatablock)
   {

   }

//
//   void application_sink::on_write_input_output_data_block(::data::block * pdatablock)
//   {
//
//
//   }
//
//
//   void application_sink::on_read_input_output_data_block(::data::block * pdatablock)
//   {
//
//
//   }

   void application_sink::open_url(const ::scoped_string & scopedstrOpenUrl)
   {

      synchronous_lock lock(this->synchronization());

      m_straOpenUrl.add(scopedstrOpenUrl);

   }


   void application_sink::list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate)
   {

      //synchronous_lock lock(m_pparticleMutexListFileEnumerate);
      synchronous_lock lock(this->synchronization());

      m_straListFileEnumerate.add(scopedstrListFileEnumerate);

   }

//   ::file::path application_sink::synchronously_getDocumentFolder(const class ::time & timeOut)
//   {
//
//      return {};
//
//   }

//
// ::pointer < ::data::block > application_sink::post_media_store_operation(
//    ::data::block * pdatablock)
// {
//
//    return {};
//
// }
// ::pointer < ::data::block >application_sink:: media_store_get_data(const ::scoped_string & scopedstrPath)
// {
//
//      return {};
//
// }
void application_sink::context_on_size_changed()
   {

   }

} // namespace platform



