#include "framework.h"
#include "product.h"
#include "axis/platform/application.h"
#include "user.h"

//
//  account_license.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 11/12/18.
//


namespace account
{


   product::product()
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

      m_timeRequest = ::earth::time::now();

      m_strAppId = strAppId;

      _do_license(strAppId, bInteractive);

      return m_estatusLicensing == ::success_licensed;

   }


   void product::_do_license(string strAppId, bool bInteractive)
   {

      ::pointer<::axis::application>papp = get_app();

      auto puser = papp->get_user("api.ca2.software", true, bInteractive);

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

      strAuthUrl = "https://api.ca2.software/account/license3?sessid=" + strRequestSessId;

//      throw ::exception(todo("xml->js"));
//
//      property_set set;
//
//      set["post"]["entered_license"] = m_XstrAppId;
//
//      ::payload strAuth = http()->get(strAuthUrl, set);
//
//      xml::document doc;
//
//      doc.load(strAuth);
//
//      m_strGateway.empty();
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
//         if(strId.has_character()
//               && strId == "licensed"
//               && m_XstrAppId == strAppId
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
//            ::kill_timer(get_splash(),123);
//
//         }
//
//         {
//
//            ::PostMessage(get_splash(),e_message_close,0,0);
//
//         }
//
//#endif // WINDOWS
//
//         message_box(nullptr, "No license for using application/feature \"" + string(m_XstrAppId) + "\" by user \"" + puser->m_strLogin + "\".\n\nPlease, subscribe to it at the software gateway <a>\"" + m_strGateway + "\"</a>", nullptr, e_message_box_icon_exclamation);
//
//         return;
//
//      }

   }


   bool product::is_ok()
   {

      if(m_estatus.failed())
      {

         return false;

      }

      if(m_estatusLicensing.failed())
      {

         return false;

      }

      if(m_strAppId.length() <= 3)
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



