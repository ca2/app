//
// Created by camilo on 2025-09-02 04:02 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "message.h"
#include "message_sink.h"
#include "acme/filesystem/file/byte2_stream.h"
#include "acme/prototype/data/block.h"
#include "acme/windowing/windowing.h"


message_sink::message_sink()
{


}


message_sink::~message_sink()
{


}


void message_sink::on_initialize_particle()
{

   ::particle::on_initialize_particle();

   defer_create_synchronization();

}


::pointer < ::platform::message > message_sink::create_message(::enum_message emessage, long long llWparam, long long llLparam)
{

   auto pmessage = øallocate ::platform::message();

   pmessage->initialize(this);

   pmessage->initialize_message(emessage, llWparam, llLparam);

   return pmessage;

}


void message_sink::post_simple_message(enum_message emessage)
{

   auto pmessage = øcreate_new < ::platform::message >();

   pmessage->m_emessage = emessage;

   post_message(pmessage);

}

void message_sink::post_message(::platform::message * pmessage)
{

   //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //m_messagea.add(pmessage);

   auto psystem = ::system();

   auto pacmewindowing = psystem->acme_windowing();

   auto p = ::as_pointer(pmessage);

   pacmewindowing->_main_post(
      [this, p]()
      {

         dispatch_message(p);

      });

}


void message_sink::post_data_block_message(::enum_message emessage, ::data::block * pdatablock)
{

   auto pmessage = øcreate_new < ::platform::message >();

   pmessage->m_emessage = emessage;

   output_byte2_stream stream(pmessage->m_memory);

   stream << *pdatablock;

   post_message(pmessage);

}


//::pointer < ::platform::message > message_sink::pick_message_to_post()
//{
//
//   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   if(m_messagea.is_empty())
//   {
//
//      return nullptr;
//
//   }
//
//   auto pmessage = m_messagea.pick_first();
//
//   return pmessage;
//
//}



//void message_sink::dispatch_posted_messages()
//{
//
//   while(true)
//   {
//
//      auto pmessage = pick_message_to_post();
//
//      if(!pmessage)
//      {
//
//         break;
//
//      }
//
//      dispatch_message(pmessage);
//
//   }
//
//}


void message_sink::dispatch_message(::platform::message * pmessage)
{

//   ::cast < ::jni_context_impl > pjnicontext = ::jni_context::get();
//
//   auto pcontext = pjnicontext->m_pjnicontext;
//
//   if(!m_pmethodPostApplicationMessage)
//   {
//
//      m_pmethodPostApplicationMessage=
//         method(
//            jni_method::e_call_void_method,
//            "post_application_message",
//            "(Lplatform/platform/message_sink)V");
//
//   }
//
//   ::cast < ::jni_method_impl > pmethod =m_pmethodPostApplicationMessage;
//
////   jclass  jclassDataBlock= pcontext->FindClass("platform/platform/data_block");
//  // jmethodID jmethodDataBlockConstructor = pcontext->GetMethodID(jclassDataBlock, "<init>",
//                                                                 //"(Ljava/lang/String;Ljava/lang/String;[B)V");
//
//
//   ::pointer < ::jni_object_impl > pobject =
//      øallocate jni_application_message(pmessage);
//
//   pobject->initialize(this);
//
//   call(pmethod, pobject->m_jobject);

}