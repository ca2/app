#include "framework.h"
#include "_.h"


namespace userpresence
{


   presence::presence(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

      m_iShortStatusWayTag = status_online;

   }


   presence::~presence()
   {

   }


   void presence::report_activity()
   {

      m_tickLastActivity = ::get_tick();

   }


   void presence::defer_pulse_user_presence()
   {

      int iStatus = (int) m_iShortStatusWayTag;
      if(m_tickLastActivity.elapsed() < ((5000) * 4))
      {
         iStatus = status_online;
      }
      /*else if(m_tickLastActivity.elapsed() < ((5000) * 10))
      {
         m_iShortStatusWayTag = status_away;
      }*/
      else
      {
         iStatus = status_offline;
      }

      if(iStatus == m_iShortStatusWayTag && (m_tickLastPulse.elapsed()) <((5000) * 2))
         return;

      m_iShortStatusWayTag = iStatus;

      pulse_user_presence();

   }


   void presence::pulse_user_presence()
   {

      m_tickLastPulse = ::get_tick();

      //if(System.m_strAppName == "netnode" || System.m_strAppName == "simpledbcfg")
        // return;

      string strHost = Context.file().as_string(Context.dir().appdata() / "database\\text\\last_good_known_account_com.txt");
      string_array straRequestingServer;
      straRequestingServer.add("api.ca2.cc");
      straRequestingServer.add("eu-api.ca2.cc");
      straRequestingServer.add("asia-api.ca2.cc");
      if(!straRequestingServer.contains_ci(strHost))
      {
         strHost = "api.ca2.cc";
      }

      string strUrl = "https://" + strHost + "/i2com/pulse_user_presence";
      System.url().string_set(strUrl, "short_status", __str(m_iShortStatusWayTag));
      System.url().string_set(strUrl, "long_status", m_strLongStatus);

      property_set set;

      Context.http().get(strUrl, set);

   }


   bool presence::on_ui_mouse_message(::user::mouse * pmouse)
   {

      // user presence status activity reporting
      if (pmouse->get_message() == WM_LBUTTONDOWN
          || pmouse->get_message() == WM_RBUTTONDOWN
          || pmouse->get_message() == WM_MBUTTONDOWN
          || pmouse->get_message() == e_message_mouse_move)
      {

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



