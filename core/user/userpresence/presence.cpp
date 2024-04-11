#include "framework.h"
#include "presence.h"
#include "acme/constant/message.h"
#include "acme/primitive/primitive/url.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "acme/user/user/mouse.h"
#include "axis/account/department.h"
#include "axis/platform/session.h"


namespace userpresence
{


   presence::presence(::particle * pparticle)
   {

      initialize(pparticle);

      m_iShortStatusWayTag = status_online;

   }


   presence::~presence()
   {

   }


   void presence::report_activity()
   {

      m_timeLastActivity= ::time::now();

   }


   void presence::defer_pulse_user_presence()
   {

      int iStatus = (int) m_iShortStatusWayTag;
      if(m_timeLastActivity.elapsed() < 20_s)
      {
         iStatus = status_online;
      }
      /*else if(m_timeLastActivity.elapsed() < ((5000) * 10))
      {
         m_iShortStatusWayTag = status_away;
      }*/
      else
      {
         iStatus = status_offline;
      }

      if(iStatus == m_iShortStatusWayTag && (m_timeLastPulse.elapsed()) < 10_s)
         return;

      m_iShortStatusWayTag = iStatus;

      pulse_user_presence();

   }


   void presence::pulse_user_presence()
   {

      m_timeLastPulse= ::time::now();

      //if(psystem->m_strAppName == "netnode" || psystem->m_strAppName == "simpledbcfg")
        // return;

      auto pcontext = m_pcontext;

      string strHost = pcontext->m_papexcontext->file()->as_string(dir()->appdata() / "database\\text\\last_good_known_account_com.txt");
      string_array straRequestingServer;
      straRequestingServer.add("api.ca2.software");
      straRequestingServer.add("eu-api.ca2.software");
      straRequestingServer.add("asia-api.ca2.software");
      if(!straRequestingServer.case_insensitive_contains(strHost))
      {
         strHost = "api.ca2.software";
      }

      string strUrl = "https://" + strHost + "/i2com/pulse_user_presence";

      url()->string_set(strUrl, "short_status", ::as_string(m_iShortStatusWayTag));
      url()->string_set(strUrl, "long_status", m_strLongStatus);

      property_set set;

      pcontext->m_papexcontext->http().get(strUrl, set);

   }


   bool presence::on_ui_mouse_message(::user::mouse * pmouse)
   {

      // user presence status activity reporting
      if (pmouse->get_message() == e_message_left_button_down
          || pmouse->get_message() == e_message_right_button_down
          || pmouse->get_message() == e_message_middle_button_down
          || pmouse->get_message() == e_message_mouse_move)
      {

         auto psession = session()->m_paxissession;

         if (psession->account() != nullptr && psession->account()->get_user() != nullptr)
         {

            try
            {

               report_activity();

            }
            catch (...)
            {

            }

         }

      }

      return true;

   }


} // namespace userpresence



