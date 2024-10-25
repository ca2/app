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


   }


   handler::~handler()
   {


   }


   void handler::destroy()
   {


      m_requestaPending.clear();

      for (auto& r: m_requestaHistory)
      {

         r.defer_destroy();

      }

      m_requestaHistory.clear();

      ::matter::destroy();

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

         m_requestaPending.add(prequest);

      }

      kick_idle();

   }


   bool handler::contains(::request* prequest) const
   {

      if (::is_null(prequest))
      {

         return false;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      return m_requestaPending.predicate_contains([&prequest](auto& p) { return p.get() == prequest; })
             || m_requestaHistory.predicate_contains([&prequest](auto& p) { return p.get() == prequest; })
             || m_prequest.get() == prequest;

   }


   string handler::command_line_text() const
   {

      if (!m_prequest)
      {

         return "";

      }

      //if (!m_prequest->m_pcommandline)
      //{

      //   return "";

      //}

      return m_prequest->m_strCommandLine;

   }


   bool handler::on_idle()
   {

      if (post_next_pending_request())
      {

         return true;

      }

      return false;

   }


   // CLASS_DECL_ACME void __call(handler* phandler, const ::atom& atom, i64 wParam, i64 lParam, ::matter* pmatter)
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

   void handler::call(const ::atom& atom, ::wparam wparam, ::lparam lparam, ::particle* pparticle)
   {


   }


   //
   // void handler::call(enum_id eid, i64 iData, ::matter* pmatter)
   // {
   //
   //    return __call(this, eid, iData, pmatter);
   //
   // }
   //
   //
   // void handler::call(const ::atom& atom, i64 wParam, i64 lParam, ::matter* pmatter)
   // {
   //
   //    return __call(this, atom, wParam, lParam, pmatter);
   //
   // }


   void handler::handle(::topic* ptopic, ::context* pcontext)
   {


   }


   void handler::handle(::message::message* pmessage)
   {


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
   // void handler::call(enum_id eid, i64 iData, ::matter* pmatter)
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







   bool handler::post_next_pending_request()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_requestaPending.has_element())
      {

         return false;

      }

      auto prequest = m_requestaPending.pick_first();

      m_requestaHistory.add(prequest);

      post_request(prequest);

      return true;

   }


} // namespace handler




