// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
// reengaged on 2024-10-25 02:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "handler.h"
#include "request.h"
#include "topic.h"
#include "extended_topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"


namespace handler
{


   handler::handler()
   {

      m_bReadyToAttendRequests = false;
      m_hnHandlerFlag = 0;

   }


   handler::~handler()
   {


   }


   void handler::on_initialize_particle()
   {

      ::matter::on_initialize_particle();

      defer_create_synchronization();

   }


   void handler::update_new_main_loop_happening()
   {

      if (has_main_loop_happening())
      {

         new_main_loop_happening()->set_happening();

      }
      else
      {

         new_main_loop_happening()->reset_happening();

      }

   }


   void handler::destroy()
   {

      m_requestaPosted.clear();

      for (auto & r : m_requestaHistory)
      {

         r.defer_destroy();

      }

      m_requestaHistory.clear();

      ::matter::destroy();

   }


   ::manual_reset_happening * handler::new_main_loop_happening()
   {

      __defer_construct_new(m_pmanualresethappeningMainLoop);

      return m_pmanualresethappeningMainLoop;

   }


   bool handler::has_main_loop_happening()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      return m_requestaPosted.has_element();

   }


   void handler::defer_reset_main_loop_happening()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!has_main_loop_happening())
      {

         new_main_loop_happening()->reset_happening();

      }

   }


   void handler::post_request(::request* prequest)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (::is_null(prequest) || contains(prequest))
         {

            throw ::exception(error_bad_argument);

         }

         prequest->m_bNew = true;

         m_requestaPosted.add(prequest);

         new_main_loop_happening()->set_happening();

         //update_new_main_loop_happening();

      }

      //kick_idle();

   }


   bool handler::pick_next_posted_request()
   {

      if (!m_bReadyToAttendRequests)
      {

         return false;

      }
      
      if(m_prequestBeingAttended)
      {
         
         return false;
         
      }

      _synchronous_lock synchronouslock(this->synchronization());

      while (true)
      {

         if (m_requestaPosted.is_empty())
         {

            return false;

         }

         auto prequest = m_requestaPosted.pick_first();

         defer_reset_main_loop_happening();

         if (::is_null(prequest))
         {

            continue;

         }

         //if (m_requestaPosted.is_empty())
         //{

         //   new_request_posted()->reset_happening();

         //}

         //m_requestaHistory.add(prequest);

         m_prequestHandler = prequest;

         return true;

      }

   }


   bool handler::handle_next_posted_request()
   {

      if (!m_bReadyToAttendRequests)
      {

         return true;

      }

      while (pick_next_posted_request())
      {

         handle(m_prequestHandler);

         m_requestaHistory.add(m_prequestHandler);

         m_prequestHandler.release();

      }

      return true;

   }


   bool handler::contains(::request* prequest) const
   {

      if (::is_null(prequest))
      {

         return false;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      return m_requestaPosted.predicate_contains([&prequest](auto& p) { return p.get() == prequest; })
             || m_requestaHistory.predicate_contains([&prequest](auto& p) { return p.get() == prequest; })
             || m_prequestHandler.get() == prequest;

   }


   string handler::command_line_text() const
   {

      if (!m_prequestHandler)
      {

         return "";

      }

      //if (!m_prequestHandler->m_pcommandline)
      //{

      //   return "";

      //}

      return m_prequestHandler->m_strCommandLine;

   }


   bool handler::on_idle()
   {

      if (handle_next_posted_request())
      {

         return true;

      }

      return false;

   }


   // CLASS_DECL_ACME void __call(handler* phandler, const ::atom& atom, long long wParam, long long lParam, ::matter* pmatter)
   // {
   //
   //    if (::is_null(pmatter))
   //    {
   //
   //       auto psystem = system();
   //
   //       auto ptopic = psystem->create_topic(atom);
   //
   //       if (wParam != 0 || lParam != 0)
   //       {
   //
   //          ptopic->payload("wparam") = wParam;
   //          ptopic->payload("lparam") = lParam;
   //
   //       }
   //
   //       phandler->handle(ptopic, nullptr);
   //
   //    }
   //    else
   //    {
   //
   //       auto pextendedtopic = pmatter->create_extended_topic(atom);
   //
   //       if (wParam != 0 || lParam != 0)
   //       {
   //
   //          pextendedtopic->payload("wparam") = wParam;
   //          pextendedtopic->payload("lparam") = lParam;
   //
   //       }
   //
   //       pextendedtopic->m_pmatter = pmatter;
   //
   //       phandler->handle(pextendedtopic, nullptr);
   //
   //    }
   //
   // }


   //

   void handler::call_message(const ::enum_message & emessage, ::wparam wparam, ::lparam lparam, ::particle* pparticle)
   {


   }


   //
   // void handler::call(enum_id eid, long long iData, ::matter* pmatter)
   // {
   //
   //    return __call(this, eid, iData, pmatter);
   //
   // }
   //
   //
   // void handler::call(const ::atom& atom, long long wParam, long long lParam, ::matter* pmatter)
   // {
   //
   //    return __call(this, emessage, wparam, lparam, pmatter);
   //
   // }


   void handler::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {


   }


   void handler::handle(::message::message* pmessage)
   {


   }


   void handler::handle(::request * prequest)
   {

      m_prequestHandler = prequest;
      
      request(prequest);

   }

   
   void handler::call_request(::request* prequest)
   {

      if (prequest->m_bPreferSync)
      {

         request(prequest);

      }
      else
      {

         post_request(prequest);

      }


   }


   void handler::request(::request * prequest)
   {
      
      ASSERT(m_prequestBeingAttended.is_null());
      
      m_prequestBeingAttended = prequest;

      try
      {
         
         on_request(prequest);
         
      }
      catch(...)
      {
         
      }
      
      // Maybe it means that other request should'nt
      // be made to this handler while one request
      // is being attended.
      ASSERT(m_prequestBeingAttended == prequest);
      
      m_prequestBeingAttended.release();
      
   }


   bool handler::_handle_uri(const block& blockUri)
   {

      return false;

   }


   bool handler::_handle_call(::payload& payload, const ::block& blockObject, const ::block& blockMember,
                              ::property_set& propertyset)
   {

      return false;

   }


   // bool handler::_handle_call(::payload& payload, const ::block& blockObject, const ::block& blockMember,
   //                            ::property_set& propertyset)
   // {
   //
   //    return false;
   //
   // }


   // bool handler::_handle_uri(const ::block& blockUri)
   // {
   //
   //    return false;
   //
   // }


   // //
   // void handler::call(enum_id eid, long long iData, ::matter* pmatter)
   // {
   //
   //    return __call(this, eid, iData, pmatter);
   //
   // }


//    bool handler::on_interprocess_handle(::interprocess::target * ptarget, const ::block & blockUri)
// {
//
//    return handle_uri(blockUri);
//
// }


} // namespace handler




