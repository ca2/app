// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "target.h"
#include "communication.h"


namespace interprocess
{


   target::target()
   {

      //sm_phandler = nullptr;

   }


   target::~target()
   {


   }


   void target::on_initialize_particle()
   {

      //fork([this]()
      //   {

      //      task_dispatch();

      //   });

      //return ::success;

   }


   void target::create(const ::string & strChannel)
   {

      //return true;

   }


   void target::destroy()
   {

      //auto estatus = 
      base::destroy();

      //return estatus;

   }


   bool target::_handle_uri(const ::string & strUri)
   {

      for (auto & phandler : m_particleaHandler)
      {

         try
         {

            if (phandler->_handle_uri(strUri))
            {

               return true;

            }

         }
         catch (...)
         {

         }

      }

      //return m_phandler->_handle_uri(blockUri);

      return false;

   }


   //bool target::on_interprocess_handle(const ::string & strUri)
   //{

   //   string strUri = blockUri;

   //   information() << "::interprocess::target::on_interprocess_handle " << strUri;


   //   //   if(!strMessage.begins_eat("call "))
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   ::i64 iCall = ::str::consume_natural(strMessage);
   //   //
   //   //   if(!strMessage.begins_eat(" from "))
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   string strAppFrom;
   //   //
   //   //   strMessage.eat_before(strAppFrom, ":");
   //   //
   //   //   string strAppPid;
   //   //
   //   //   strMessage.eat_before(strAppPid, " ");
   //   //
   //   //   if(strAppFrom.is_empty())
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   if (strAppPid.is_empty())
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //#if !defined(UNIVERSAL_WINDOWS)
   //   //
   //   //   auto iPid = atoll(strAppPid);
   //   //
   //   //   if(iPid == 0)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //#endif
   //   //
   //   //   auto pFind = strMessage.find(":");
   //   //
   //   //   string str1;
   //   //
   //   //   string strObject;
   //   //
   //   //   string strMember;
   //   //
   //   //   string_array stra;
   //   //
   //   //   property_set propertyset;
   //   //
   //   //   if(::is_set(pFind) && iFind <= 3)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   if(iFind > 3)
   //   //   {
   //   //
   //   //      str1 = strMessage(0, pFind);
   //   //
   //   //   }
   //   //   else
   //   //   {
   //   //
   //   //      str1 = strMessage;
   //   //
   //   //   }
   //   //
   //   //   str1.trim();
   //   //
   //   //   strsize iFind2 = str1.find(".");
   //   //
   //   //   if(iFind2 < 0)
   //   //   {
   //   //
   //   //      return;
   //   //
   //   //   }
   //   //
   //   //   strObject = str1.left(iFind2);
   //   //
   //   //   strMember = str1.substr(iFind2 + 1);
   //   //
   //   //   if(::is_set(pFind))
   //   //   {
   //   //
   //   //      str1 = strMessage(pFind + 1);
   //   //
   //   //      str1.trim();
   //   //
   //   //      memory_stream stream;
   //   //
   //   //      stream->get_primitive_memory()->from_hex(str1);
   //   //
   //   //      stream->seek_to_begin();
   //   //
   //   //      stream.set_loading();
   //   //
   //   //      __io_array(stream, payloada);
   //   //
   //   //   }


   //   string strObject = system()->url()->get_server(strUri);

   //   string strMember = system()->url()->get_script(strUri);

   //   strMember.trim_left("/");

   //   string strNetworkArguments = system()->url()->get_query(strUri);

   //   ::property_set propertyset;

   //   propertyset.parse_network_arguments(strNetworkArguments);

   //   ::payload payloadReply;

   //   bool bShouldContinueTryingToHandle = m_phandler->handle_call(payloadReply, strObject, strMember, propertyset);

   //   if (bShouldContinueTryingToHandle)
   //   {

   //      if (!strMember.case_insensitive_begins("reply."))
   //      {

   //         string strOrigin = propertyset["protocol"]["origin"].get_string();

   //         string strOriginObject = propertyset["protocol"]["origin_object"].get_string();

   //         auto iCallId = propertyset["protocol"]["call_id"].i64();

   //         auto pcall = m_pcommunication->create_call(strOrigin, strOriginObject, "reply." + strMember);

   //         (*pcall)["protocol"]["call_id"] = iCallId;

   //         (*pcall)["protocol"]["reply"] = payloadReply;

   //         //pcall->set_timeout(1_minute);

   //         fork([pcall, strOriginObject]()
   //            {

   //               pcall->send(strOriginObject);

   //            });

   //      }

   //   }

   //   return bShouldContinueTryingToHandle;

   //}


   //bool target::on_interprocess_handle(const ::string & strUri)
   //{

   //   //if (string_begins_ci(strMessage, "synch_"))
   //   //{

   //   //   if (m_phandler != nullptr)
   //   //   {

   //   m_phandler->on_interprocess_handle(this, Uri);

   //   return false;

   //   //   }

   //   //}
   //   //else
   //   //{

   //   //   dispatch_message(::transfer(strMessage));
   //   //   //get_app()->fork([this, prx, strMessage]()
   //   //   //{

   //   //   //   if (m_phandler != nullptr)
   //   //   //   {

   //   //   //      m_phandler->on_interprocess_receive(prx, strMessage);

   //   //   //   }

   //   //   //});

   //   //}

   //   //// ODOW - on date of writing : return ignored by this windows implementation

   //   ////return nullptr;

   //}


   //void target::on_interprocess_receive(int message, ::memory && memory)
   //{

   //   ///memory memory(pdata, len);

   //   dispatch_message(message, ::transfer(memory));

   //   //if (m_phandler != nullptr)
   //   //{

   //     // m_phandler->on_interprocess_receive(prx, message, pdata, len);

   //   //}

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   //return nullptr;

   //}


   //void target::on_interprocess_post(i64 a, i64 b)
   //{

   //   if (m_phandler != nullptr)
   //   {

   //      m_phandler->on_interprocess_post(this, a, b);

   //   }

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   //return nullptr;

   //}


   bool target::on_idle()
   {

      return false;

   }


   bool target::is_target_ok()
   {

      return false;

   }


   //void target::dispatch_message(::string && strMessage)
   //{

   //   auto pdispatchitem = __allocate< class dispatch_item >(::transfer(strMessage));

   //   dispatch_item(::transfer(pdispatchitem));

   //}


   //void target::dispatch_message(::u64 uData, ::memory && memory)
   //{

   //   auto pdispatchitem = __allocate< class dispatch_item >(uData, ::transfer(memory));

   //   dispatch_item(::transfer(pdispatchitem));

   //}


   //void target::dispatch_item(::pointer<class dispatch_item> && pdispatchitem)
   //{

   //   synchronous_lock synchronouslock(m_pmutexDispatch);

   //   bool bWasEmpty = m_dispatchitema.is_empty();

   //   m_dispatchitema.add(::transfer(pdispatchitem));

   //   if (bWasEmpty)
   //   {

   //      m_evDispatchItemNew.SetEvent();

   //   }

   //}


   //void target::task_dispatch()
   //{

   //   auto ptask = ::get_task();

   //   single_lock singlelock(m_pmutexDispatch);

   //   while (ptask->task_get_run())
   //   {

   //      if (m_evDispatchItemNew._wait(1_s))
   //      {

   //         singlelock.lock();

   //         while (m_dispatchitema.has_element()
   //            && ptask->task_get_run())
   //         {

   //            {

   //               auto pdispatchitem = m_dispatchitema.pick_first();

   //               singlelock.unlock();

   //               try
   //               {

   //                  m_phandler->on_interprocess_receive(this, ::transfer(pdispatchitem));

   //               }
   //               catch (...)
   //               {

   //               }

   //            }

   //            singlelock.lock();

   //         }

   //         m_evDispatchItemNew.ResetEvent();

   //         singlelock.unlock();

   //      }

   //   }

   //}


   void target::add_handler(::particle * pparticle)
   {

      m_particleaHandler.add_unique(pparticle);

   }



} // namespace interprocess



