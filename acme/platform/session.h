//
//  session.h
//  acme
//
//  Created by camilo on 2022-12-01 11:27 BRT <3TBS_!!
//
#pragma once


//#include "context.h"
#include "acme/handler/handler.h"
#include "application_container.h"
#include "acme/user/user/key_state.h"

#include "session_acme.h"
#include "session_apex.h"
#include "session_aqua.h"
#include "session_aura.h"
#include "session_axis.h"


namespace platform
{


   class CLASS_DECL_ACME session :
      virtual public ::task,
      virtual public ::handler::handler,
      virtual public ::platform::application_container,
      virtual public ::user::key_state,
      virtual public ::platform::acme_session_layer_t,
      virtual public ::platform::apex_session_layer_t,
      virtual public ::platform::aqua_session_layer_t,
      virtual public ::platform::aura_session_layer_t,
      virtual public ::platform::axis_session_layer_t,
      virtual public ::platform::acme_session_layer,
      virtual public ::platform::apex_session_layer,
      virtual public ::platform::aqua_session_layer,
      virtual public ::platform::aura_session_layer,
      virtual public ::platform::axis_session_layer
   {
   public:


      ::collection::index             m_iEdge;



      // ::apex::session* m_papexsession;
      // ::aqua::session* m_paquasession;
      // ::aura::session* m_paurasession;
      // ::axis::session* m_paxissession;
      // ::berg::session* m_pbasesession;
      // ::bred::session* m_pbredsession;
      // ::core::session* m_pcoresession;


      ::pointer<::text::context>                     m_ptextcontext;



      ::payload                                                   m_varCurrentImpactFile;


      session();
      ~session() override;


      void destroy() override;

      virtual ::text::context* text_context();


      virtual class ::user::user * user() override;


      void on_request(::request* prequest) override;


      virtual void init_task() override;

      virtual void term_task() override;

      virtual void process_init();

      virtual void init1();

      virtual void init2();

      virtual void init_session();

      virtual void init();

      virtual void term();

      virtual void term1();

      virtual void term2();

      virtual void process_term();

      virtual void term_session();

      void main() override;


   };


} // namespace platform



