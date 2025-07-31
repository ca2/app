//
// Created by camilo on 2024-10-28 00:41 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME axis_session_layer_t
   {


      ::pointer<::account::department>                m_paccount;


   };


   class CLASS_DECL_ACME axis_session_layer
   {
   public:


      //virtual ::user::style* user_style() override;

      virtual ::account::department * account();

      virtual void on_user_logon(::account::user * puser);

      //::axis::user * axisuser() override;

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual void on_erase_user(::account::user * puser);

      //virtual bool is_licensed(const ::scoped_string & scopedstrId, bool bInteractive = true) override;

      //virtual bool get_auth(const ::scoped_string & scopedstrForm, string & strUsername, string & strPassword) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      //::aura::application * application_get(const ::scoped_string & scopedstrAppId, bool bCreate, bool bSynch, ::request * prequest) override;

      //virtual void install_message_routing(::channel * pchannel) override;


      //virtual bool InitializeLocalDataCentral() override;



   };


} // namespace platform



