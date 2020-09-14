#include "framework.h"
//#include "aura/xml/_.h"

//
//  account_license.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 11/12/18.
//


namespace account
{


   product::product(::layered * pcontextobject) :
      ::object(pcontextobject)
   {

      m_estatus = error_none;
      m_estatusLicensing = error_none;


   }


   product::~product()
   {

   }


   void product::license(string strAppId, bool bInteractive)
   {

      do_license(strAppId, bInteractive);

   }


   bool product::do_license(string strAppId, bool bInteractive)
   {

      m_timeRequest = ::datetime::time::get_current_time();

      m_strAppId = strAppId;

      _do_license(strAppId, bInteractive);

      return m_estatusLicensing == ::success_licensed;

   }


   void product::_do_license(string strAppId, bool bInteractive)
   {

      auto puser = Application.get_user("api.ca2.cc", true, bInteractive);

      if(::is_null(puser) || !puser->is_authenticated())
      {

         if(puser != nullptr)
         {


         }
         else
         {

            m_estatusLicensing = error_licensing_no_user;

         }

         return;

      }

      string strRequestSessId;

      strRequestSessId = puser->m_strSessId;

      string strAuthUrl;

      strAuthUrl = "https://api.ca2.cc/account/license3?sessid=" + strRequestSessId;

//      __throw(todo("xml->js"));
//
//      property_set set;
//
//      set["post"]["entered_license"] = m_strAppId;
//
//      var strAuth = Context.http().get(strAuthUrl, set);
//
//      xml::document doc;
//
//      doc.load(strAuth);
//
//      m_strGateway.Empty();
//
//      if(doc.get_name() == "response")
//      {
//
//         string strDecrypt;
//
//         string strId = doc.attribute("id");
//
//         string strAppId = doc.attribute("license");
//
//         string strResponseSessId = doc.attribute("sessid");
//
//         if(strId.has_char()
//               && strId == "licensed"
//               && m_strAppId == strAppId
//               && strResponseSessId == strRequestSessId)
//         {
//
//            string strLogStats = doc.attribute("stats");
//
//            return;
//
//         }
//
//         m_strGateway = doc.attribute("gateway");
//
//      }
//
//      if(bInteractive)
//      {
//
//#ifdef WINDOWS_DESKTOP
//
//         if(get_splash() != nullptr)
//         {
//
//            ::KillTimer(get_splash(),123);
//
//         }
//
//         {
//
//            ::PostMessage(get_splash(),WM_CLOSE,0,0);
//
//         }
//
//#endif // WINDOWS
//
//         Application.message_box(nullptr, "No license for using application/feature \"" + string(m_strAppId) + "\" by user \"" + puser->m_strLogin + "\".\n\nPlease, subscribe to it at the software gateway <a>\"" + m_strGateway + "\"</a>", nullptr, message_box_icon_exclamation);
//
//         return;
//
//      }

   }


   bool product::is_ok()
   {

      if(::failed(m_estatus))
      {

         return false;

      }

      if(::failed(m_estatusLicensing))
      {

         return false;

      }

      if(m_strAppId.get_length() <= 3)
      {

         return false;

      }

      return true;


   }

   bool product::is_licensed()
   {

      return m_estatusLicensing == ::success_licensed;

   }



} // namespace account



