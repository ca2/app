//
// Created by camilo on 2024-10-28 00:44 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "session_axis.h"


namespace platform
{


      //virtual ::user::style* user_style() override;

      ::account::department * axis_session_layer::account()
      {

         return nullptr;

      }

      
      void axis_session_layer::on_user_logon(::account::user * puser)
      {



      }



      //::axis::user * axisuser() override;

      ::account::user * axis_session_layer::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
      {

         return nullptr;

      }


      void axis_session_layer::on_erase_user(::account::user * puser)
      {


      }

      //virtual bool is_licensed(const ::string & pszId, bool bInteractive = true) override;

      //virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword) override;

      void axis_session_layer::interactive_credentials(::account::credentials * pcredentials)
      {


      }

      //::aura::application * application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::request * prequest) override;

      //virtual void install_message_routing(::channel * pchannel) override;


      //virtual bool InitializeLocalDataCentral() override;



   //};


} // namespace platform



